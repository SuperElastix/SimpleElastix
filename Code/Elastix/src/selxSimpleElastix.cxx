#ifndef __selxsimpleelastix_cxx_
#define __selxsimpleelastix_cxx_

#include "selxSimpleElastix.h"
#include "selxSimpleElastix.hxx"

namespace itk {
  namespace simple {



SimpleElastix
::SimpleElastix( void )
{
  // Register this class with SimpleITK
  m_MemberFactory.reset( new detail::MemberFunctionFactory< MemberFunctionType >( this ) );
  m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 3, SimpleElastixAddressor< MemberFunctionType > >();
  m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 2, SimpleElastixAddressor< MemberFunctionType > >();

  // This class holds configuration and pointers to data that is passed to elastix API when run
  this->m_FixedImage = 0;
  this->m_MovingImage = 0;
  this->m_ParameterMaps = ParameterMapListType();
  this->m_TransformParameterMaps = ParameterMapListType();
  this->m_FixedMask = 0;
  this->m_MovingMask = 0;
  this->m_ResultImage = Image();
  this->m_OutputFolder = "";
  this->m_LogToDisk = false;
  this->m_LogToConsole = true;
}



SimpleElastix
::~SimpleElastix( void )
{
}



const std::string 
SimpleElastix
::GetName( void )
{ 
  const std::string name = std::string("SimpleElastix");
  return name;
}



void 
SimpleElastix
::SetFixedImage( Image* fixedImage )
{
  this->m_FixedImage = fixedImage;
}



void
SimpleElastix
::SetMovingImage( Image* movingImage )
{
  this->m_MovingImage = movingImage;
}



void
SimpleElastix
::SetFixedMask( Image* fixedMask )
{
  this->m_FixedMask = fixedMask;
}



void
SimpleElastix
::SetMovingMask( Image* movingMask )
{
  this->m_MovingMask = movingMask;
}



void
SimpleElastix
::ClearFixedMask( void )
{
  this->m_FixedMask = 0;
}



void
SimpleElastix
::ClearMovingMask( void )
{
  this->m_MovingMask = 0;
}



Image
SimpleElastix
::Execute( void )
{
  const PixelIDValueEnum FixedImagePixelEnum = this->m_FixedImage->GetPixelID();
  const unsigned int FixedImageDimension = this->m_FixedImage->GetDimension();

  if (this->m_MemberFactory->HasMemberFunction( FixedImagePixelEnum, FixedImageDimension ) )
  {
    return this->m_MemberFactory->GetMemberFunction( FixedImagePixelEnum, FixedImageDimension )();
  }

  sitkExceptionMacro( << "SimpleElastix does not support the combination of image type \""
                      << GetPixelIDValueAsString( FixedImagePixelEnum ) << "\" ("
                      << GetPixelIDValueAsElastixParameter( FixedImagePixelEnum ) << ") and dimension "
                      << FixedImageDimension << "." );
}



Image 
SimpleElastix
::GetResultImage( void )
{
  return this->m_ResultImage;
}



void
SimpleElastix
::SetOutputFolder( const std::string folder )
{
  this->m_OutputFolder = folder;
}



void
SimpleElastix
::LogToDisk( bool logToDisk )
{
  this->m_LogToDisk = logToDisk;
}



void
SimpleElastix
::LogToDiskOn( void )
{
  this->m_LogToDisk = true;
}



void
SimpleElastix
::LogToDiskOff( void )
{
  this->m_LogToDisk = false;
}



void
SimpleElastix
::LogToConsole( bool logToConsole )
{
  this->m_LogToConsole = logToConsole;
}




void
SimpleElastix
::LogToConsoleOn( void )
{
  this->m_LogToConsole = true;
}



void
SimpleElastix
::LogToConsoleOff( void )
{
  this->m_LogToConsole = false;
}



void
SimpleElastix
::SetParameterMapList( ParameterMapListType parameterMapList )
{
  this->m_ParameterMaps = parameterMapList;
}



void
SimpleElastix
::SetParameterMap( ParameterMapType parameterMap )
{
  ParameterMapListType parameterMapList;
  parameterMapList.push_back( parameterMap );
  this->SetParameterMapList( parameterMapList );
}



SimpleElastix::ParameterMapListType
SimpleElastix
::GetParameterMapList( void )
{
  return this->m_ParameterMaps;
}



void
SimpleElastix
::SetTransformParameterMapList( ParameterMapListType parameterMapList )
{
  this->m_TransformParameterMaps = parameterMapList;
}



void
SimpleElastix
::SetTransformParameterMap( ParameterMapType parameterMap )
{
  ParameterMapListType parameterMapList;
  parameterMapList.push_back( parameterMap );
  this->SetTransformParameterMapList( parameterMapList );
}



SimpleElastix::ParameterMapListType
SimpleElastix
::GetTransformParameterMapList( void )
{
  return this->m_TransformParameterMaps;
}




SimpleElastix::ParameterMapType
SimpleElastix
::ParameterFileReader( const std::string filename )
{
  ParameterFileParserPointer parser = ParameterFileParserType::New();
  parser->SetParameterFileName( filename );
  try
  {
    parser->ReadParameterFile();
  }
  catch( itk::ExceptionObject &e )
  {
    std::cout << e.what() << std::endl;
  }

  return parser->GetParameterMap();
}



SimpleElastix::ParameterMapType
SimpleElastix
::GetDefaultParameterMap( const std::string name )
{ 

  // Defaults
  unsigned int resolution          = 3;
  unsigned int dimension           = 3;
  std::vector<unsigned int> siz    = std::vector<unsigned int>( resolution, 256 );
  std::vector<unsigned int> knots  = std::vector<unsigned int>( resolution, 16 );

  // Image parameters
  if( this->m_FixedImage != 0 )
  {
    siz = this->m_FixedImage->GetSize();
    dimension = this->m_FixedImage->GetDimension();
  }

  // Parameters that depend on size and number of resolutions
  ParameterMapType parameterMap                     = ParameterMapType();
  ParameterValuesType finalGridSpacingInVoxels      = ParameterValuesType();
  ParameterValuesType gridSpacingSchedule           = ParameterValuesType();
  ParameterValuesType movingImagePyramidSchedule    = ParameterValuesType();
  for( unsigned int dim = 0; dim < dimension; ++dim )
  {
    finalGridSpacingInVoxels.push_back( std::to_string( siz[ dim ] / knots[ dim ] ) );
    for( unsigned int res = 0; res < resolution; ++res )
    {
      gridSpacingSchedule.insert( gridSpacingSchedule.begin(), std::to_string( pow( 2, dim ) ) );               // (4, 4, 4, 2, 2, 2, 1, 1, 1)
      movingImagePyramidSchedule.insert( movingImagePyramidSchedule.begin(), std::to_string( pow( 2, dim ) ) ); // (4, 4, 4, 2, 2, 2, 1, 1, 1)
    }
  }

  // Common Components
  parameterMap[ "FixedImagePyramid" ]               = ParameterValuesType( 1, "FixedSmoothingImagePyramid" );
  parameterMap[ "MovingImagePyramid" ]              = ParameterValuesType( 1, "MovingSmoothingImagePyramid" );
  parameterMap[ "Interpolator "]                    = ParameterValuesType( 1, "LinearInterpolator");
  parameterMap[ "Optimizer" ]                       = ParameterValuesType( 1, "AdaptiveStochasticGradientDescent" );
  parameterMap[ "ResampleInterpolator "]            = ParameterValuesType( 1, "FinalBSplineResampleInterpolator" );
  parameterMap[ "FinalBSplineInterpolationOrder" ]  = ParameterValuesType( 1, "2" );
  parameterMap[ "FixedImagePyramidSchedule"]        = ParameterValuesType( resolution * dimension, "0" );
  parameterMap[ "MovingImagePyramidSchedule"]       = movingImagePyramidSchedule;
  parameterMap[ "NumberOfResolutions" ]             = ParameterValuesType( 1, std::to_string( resolution ) );

  // Image Sampler
  parameterMap[ "ImageSampler" ]                    = ParameterValuesType( 1, "Random" ); 
  parameterMap[ "NumberOfSpatialSamples"]           = ParameterValuesType( 1, "4096" );
  parameterMap[ "CheckNumberOfSamples" ]            = ParameterValuesType( 1, "true" );
  parameterMap[ "MaximumNumberOfSamplingAttemts" ]  = ParameterValuesType( 1, "8" );
  parameterMap[ "NewSamplesEveryIteration" ]        = ParameterValuesType( 1, "true");

  // Optimizer
  parameterMap[ "MaximumNumberOfIterations" ]       = ParameterValuesType( 1, "256" );
  parameterMap[ "NumberOfSamplesForExactGradient" ] = ParameterValuesType( 1, "4096" );
  parameterMap[ "DefaultPixelValue" ]               = ParameterValuesType( 1, "0" );
  parameterMap[ "AutomaticParameterEstimation" ]    = ParameterValuesType( 1, "true" );

  if( name == "translation" )
  {
    parameterMap[ "Registration" ]                  = ParameterValuesType( 1, "MultiResolutionRegistration" );
    parameterMap[ "Transform" ]                     = ParameterValuesType( 1, "TranslationTransform" );
    parameterMap[ "Metric" ]                        = ParameterValuesType( 1, "MattesMutualInformationMetric" );
  }
  else if( name == "rigid" )
  {
    parameterMap[ "Registration" ]                  = ParameterValuesType( 1, "MultiResolutionRegistration" );
    parameterMap[ "Transform" ]                     = ParameterValuesType( 1, "EulerTransform" );
    parameterMap[ "Metric" ]                        = ParameterValuesType( 1, "MattesMutualInformationMetric" );
  }
  else if( name == "affine" )
  {
    parameterMap[ "Registration" ]                  = ParameterValuesType( 1, "MultiResolutionRegistration" );
    parameterMap[ "Transform" ]                     = ParameterValuesType( 1, "AffineTransform" );
    parameterMap[ "Metric" ]                        = ParameterValuesType( 1, "MattesMutualInformationMetric" );
  }
  else if( name == "nonrigid" )
  {
    parameterMap[ "Registration" ]                  = ParameterValuesType( 1, "MultiMetricMultiResolutionRegistration" );
    parameterMap[ "Transform" ]                     = ParameterValuesType( 1, "BSplineTransform" );
    parameterMap[ "Metric" ]                        = ParameterValuesType( 1, "MattesMutualInformationMetric" );
    parameterMap[ "Metric" ]                        .push_back( "TransformBendingEnergyPenalty" );
    parameterMap[ "Metric0Weight" ]                 = ParameterValuesType( 1, "0.01" );
    parameterMap[ "Metric1Weight" ]                 = ParameterValuesType( 1, "0.99" );
    parameterMap[ "FinalGridSpacingInVoxels" ]      = finalGridSpacingInVoxels;
    parameterMap[ "GridSpacingSchedule" ]           = gridSpacingSchedule;
  }
  else if( name == "groupwise" )
  {
    parameterMap[ "Registration" ]                  = ParameterValuesType( 1, "MultiResolutionRegistration" );
    parameterMap[ "Transform" ]                     = ParameterValuesType( 1, "BSplineStackTransform" );
    parameterMap[ "Metric" ]                        = ParameterValuesType( 1, "VarianceOverLastDimensionMetric" );
    parameterMap[ "FinalGridSpacingInVoxels" ]      = finalGridSpacingInVoxels;
    parameterMap[ "GridSpacingSchedule" ]           = gridSpacingSchedule;
  }
  else
  {
    sitkExceptionMacro( "No default parameter map named \"" << name << "\"." );
  }

  // Required for 2D
  if( dimension == 2 )
  {
    parameterMap[ "FixedImagePyramid" ]             = ParameterValuesType( 1, "FixedRecursiveImagePyramid" );
    parameterMap[ "MovingImagePyramid" ]            = ParameterValuesType( 1, "MovingRecursiveImagePyramid" );    
  }

  return parameterMap;
}



// Procedural interface 



typename SimpleElastix::ParameterMapType
ReadParameterFile( const std::string filename )
{
  SimpleElastix selx;
  return selx.ParameterFileReader( filename );
}



SimpleElastix::ParameterMapType
GetDefaultParameterMap( std::string defaultParameterMapName )
{
  SimpleElastix selx;
  SimpleElastix::ParameterMapType parameterMap = selx.GetDefaultParameterMap( defaultParameterMapName );
  return parameterMap;
}



Image
elastix( Image fixedImage, Image movingImage, std::string defaultParameterMapName, bool logToConsole, bool logToDisk, std::string outputFolder )
{
  SimpleElastix selx;
  SimpleElastix::ParameterMapType parameterMap = selx.GetDefaultParameterMap( defaultParameterMapName );
  return elastix( fixedImage, movingImage, parameterMap, logToConsole, logToDisk, outputFolder );
}



Image
elastix( Image fixedImage, Image movingImage, SimpleElastix::ParameterMapType parameterMap, bool logToConsole, bool logToDisk, std::string outputFolder )
{
  SimpleElastix::ParameterMapListType parameterMapList;
  parameterMapList.push_back( parameterMap );
  return elastix( fixedImage, movingImage, parameterMapList, logToConsole, logToDisk, outputFolder );
}



Image
elastix( Image fixedImage, Image movingImage, SimpleElastix::ParameterMapListType parameterMapList, bool logToConsole, bool logToDisk, std::string outputFolder )
{
  SimpleElastix selx;
  selx.SetFixedImage( &fixedImage );
  selx.SetMovingImage( &movingImage );
  selx.SetParameterMapList( parameterMapList );
  selx.SetOutputFolder( outputFolder );
  selx.LogToDisk( logToDisk );
  selx.LogToConsole( logToConsole );

  return selx.Execute();
}



Image
elastix( Image fixedImage, Image movingImage, std::string defaultParameterMapName, Image fixedMask, Image movingMask, bool logToConsole, bool logToDisk, std::string outputFolder )
{
  SimpleElastix selx;
  SimpleElastix::ParameterMapType parameterMap = selx.GetDefaultParameterMap( defaultParameterMapName );
  return elastix( fixedImage, movingImage, parameterMap, fixedMask, movingMask, logToConsole, logToDisk, outputFolder );
}




Image
elastix( Image fixedImage, Image movingImage, SimpleElastix::ParameterMapType parameterMap, Image fixedMask, Image movingMask, bool logToConsole, bool logToDisk, std::string outputFolder )
{
  SimpleElastix::ParameterMapListType parameterMapList;
  parameterMapList.push_back( parameterMap );
  return elastix( fixedImage, movingImage, parameterMapList, fixedMask, movingMask, logToConsole, logToDisk, outputFolder );
}



Image
elastix( Image fixedImage, Image movingImage, SimpleElastix::ParameterMapListType parameterMapList, Image fixedMask, Image movingMask, bool logToConsole, bool logToDisk, std::string outputFolder )
{
  SimpleElastix selx;
  selx.SetFixedImage( &fixedImage );
  selx.SetMovingImage( &movingImage );
  selx.SetParameterMapList( parameterMapList );
  selx.SetFixedMask( &fixedMask );
  selx.SetMovingMask( &movingMask );
  selx.SetOutputFolder( outputFolder );
  selx.LogToDisk( logToDisk );
  selx.LogToConsole( logToConsole );

  return selx.Execute();
}


} // end namespace simple
} // end namespace itk

#endif // __selxsimpleelastix_cxx_