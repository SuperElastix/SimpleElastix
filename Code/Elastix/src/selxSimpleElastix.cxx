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

  // This class holds data that is passed to elastix API when run
  this->m_FixedImage = Image();
  this->m_MovingImage = Image();
  this->m_ParameterMaps = ParameterMapListType();
  this->m_FixedMask = Image();
  this->m_MovingMask = Image();
  this->m_OutputFolder = "";
  this->m_LogToConsole = false;
  this->m_ResultImage = Image();
  this->m_TransformParameterMaps = ParameterMapListType();
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
::SetFixedImage( const Image& fixedImage )
{
  this->m_FixedImage = fixedImage;
}



Image&
SimpleElastix
::GetFixedImage( void )
{
  return this->m_FixedImage;
}



void
SimpleElastix
::SetMovingImage( const Image& movingImage )
{
  this->m_MovingImage = movingImage;
}



Image&
SimpleElastix
::GetMovingImage( void )
{
  return this->m_MovingImage;
}



void
SimpleElastix
::SetFixedMask( const Image& fixedMask )
{
  this->m_FixedMask = fixedMask;
}



Image&
SimpleElastix
::GetFixedMask( void )
{
  return this->m_FixedMask;
}



void
SimpleElastix
::DeleteFixedMask( void )
{
  this->m_FixedMask = Image();
}



void
SimpleElastix
::SetMovingMask( const Image& movingMask )
{
  this->m_MovingMask = movingMask;
}



Image&
SimpleElastix
::GetMovingMask( void )
{
  return this->m_MovingMask;
}



void
SimpleElastix
::DeleteMovingMask( void )
{
  this->m_MovingMask = Image();
}



void
SimpleElastix
::SetParameterMapList( const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapList )
{
  this->m_ParameterMaps = parameterMapList;
}



void
SimpleElastix
::SetParameterMap( const std::map< std::string, std::vector< std::string > > parameterMap )
{
  ParameterMapListType parameterMapList = ParameterMapListType( 1 );
  parameterMapList[ 0 ] = parameterMap;
  this->SetParameterMapList( parameterMapList );
}



std::vector< std::map< std::string, std::vector< std::string > > > 
SimpleElastix
::GetParameterMapList( void )
{
  return this->m_ParameterMaps;
}



std::vector< std::map< std::string, std::vector< std::string > > > 
SimpleElastix
::GetTransformParameterMapList( void )
{
  return this->m_TransformParameterMaps;
}



std::map< std::string, std::vector< std::string > >
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



std::map< std::string, std::vector< std::string > >
SimpleElastix
::GetDefaultParameterMap( const std::string name )
{ 

  // Defaults
  unsigned int resolutions         = 4;
  unsigned int dimension           = 3;
  std::vector<unsigned int> siz    = std::vector<unsigned int>( dimension, 256 );
  std::vector<unsigned int> knots  = std::vector<unsigned int>( dimension, 16 );

  // Image parameters
  if( !isEmpty( this->m_FixedImage ) )
  {
    siz = this->m_FixedImage.GetSize();
    dimension = this->m_FixedImage.GetDimension();
  }

  // Parameters that depend on size and number of resolutions
  ParameterMapType parameterMap                     = ParameterMapType();
  ParameterValuesType gridSpacingSchedule           = ParameterValuesType();
  ParameterValuesType imagePyramidSchedule          = ParameterValuesType();
  for( unsigned int res = 0; res < resolutions; ++res )
  {
    for( unsigned int dim = 0; dim < dimension; ++dim )
    {
      gridSpacingSchedule.insert( gridSpacingSchedule.begin(), std::to_string( pow( 2, res ) ) ); 
      imagePyramidSchedule.insert( imagePyramidSchedule.begin(), std::to_string( pow( 2, res ) ) ); 
    }
  }

  ParameterValuesType finalGridSpacingInVoxels      = ParameterValuesType();
  for( unsigned int dim = 0; dim < dimension; ++dim )
  {
    finalGridSpacingInVoxels.push_back( std::to_string( siz[ dim ] / knots[ dim ] ) );
  }

  // Common Components
  parameterMap[ "FixedImagePyramid" ]               = ParameterValuesType( 1, "FixedSmoothingImagePyramid" );
  parameterMap[ "MovingImagePyramid" ]              = ParameterValuesType( 1, "MovingSmoothingImagePyramid" );
  parameterMap[ "Interpolator"]                     = ParameterValuesType( 1, "LinearInterpolator");
  parameterMap[ "Optimizer" ]                       = ParameterValuesType( 1, "AdaptiveStochasticGradientDescent" );
  parameterMap[ "Resampler"]                        = ParameterValuesType( 1, "DefaultResampler" );
  parameterMap[ "ResampleInterpolator"]             = ParameterValuesType( 1, "FinalBSplineInterpolator" );
  parameterMap[ "FinalBSplineInterpolationOrder" ]  = ParameterValuesType( 1, "2" );
  parameterMap[ "FixedImagePyramidSchedule" ]       = imagePyramidSchedule;
  parameterMap[ "MovingImagePyramidSchedule" ]      = imagePyramidSchedule;
  parameterMap[ "NumberOfResolutions" ]             = ParameterValuesType( 1, std::to_string( resolutions ) );

  // Image Sampler
  parameterMap[ "ImageSampler" ]                    = ParameterValuesType( 1, "RandomCoordinate" ); 
  parameterMap[ "NumberOfSpatialSamples"]           = ParameterValuesType( 1, "4096" );
  parameterMap[ "CheckNumberOfSamples" ]            = ParameterValuesType( 1, "true" );
  parameterMap[ "MaximumNumberOfSamplingAttempts" ] = ParameterValuesType( 1, "8" );
  parameterMap[ "NewSamplesEveryIteration" ]        = ParameterValuesType( 1, "true");

  // Optimizer
  parameterMap[ "NumberOfSamplesForExactGradient" ] = ParameterValuesType( 1, "4096" );
  parameterMap[ "DefaultPixelValue" ]               = ParameterValuesType( 1, "0" );
  parameterMap[ "AutomaticParameterEstimation" ]    = ParameterValuesType( 1, "true" );

  // Output
  parameterMap[ "WriteResultImage" ]                = ParameterValuesType( 1, "true" );

  if( name == "translation" )
  {
    parameterMap[ "Registration" ]                  = ParameterValuesType( 1, "MultiResolutionRegistration" );
    parameterMap[ "Transform" ]                     = ParameterValuesType( 1, "TranslationTransform" );
    parameterMap[ "Metric" ]                        = ParameterValuesType( 1, "AdvancedMattesMutualInformation" );
    parameterMap[ "MaximumNumberOfIterations" ]     = ParameterValuesType( 1, "32" );
  }
  else if( name == "rigid" )
  {
    parameterMap[ "Registration" ]                  = ParameterValuesType( 1, "MultiResolutionRegistration" );
    parameterMap[ "Transform" ]                     = ParameterValuesType( 1, "EulerTransform" );
    parameterMap[ "Metric" ]                        = ParameterValuesType( 1, "AdvancedMattesMutualInformation" );
    parameterMap[ "MaximumNumberOfIterations" ]     = ParameterValuesType( 1, "64" );
  }
  else if( name == "affine" )
  {
    parameterMap[ "Registration" ]                  = ParameterValuesType( 1, "MultiResolutionRegistration" );
    parameterMap[ "Transform" ]                     = ParameterValuesType( 1, "AffineTransform" );
    parameterMap[ "Metric" ]                        = ParameterValuesType( 1, "AdvancedMattesMutualInformation" );
    parameterMap[ "MaximumNumberOfIterations" ]     = ParameterValuesType( 1, "128" );
  }
  else if( name == "nonrigid" )
  {
    parameterMap[ "Registration" ]                  = ParameterValuesType( 1, "MultiMetricMultiResolutionRegistration" );
    parameterMap[ "Transform" ]                     = ParameterValuesType( 1, "BSplineTransform" );
    parameterMap[ "Transform" ]                       .push_back( "TransformBendingEnergyPenalty" );
    parameterMap[ "Metric" ]                        = ParameterValuesType( 1, "AdvancedMattesMutualInformation" );
    parameterMap[ "Metric0Weight" ]                 = ParameterValuesType( 1, "0.001" );
    parameterMap[ "Metric1Weight" ]                 = ParameterValuesType( 1, "0.999" );
    parameterMap[ "FinalGridSpacingInVoxels" ]      = finalGridSpacingInVoxels;
    parameterMap[ "GridSpacingSchedule" ]           = gridSpacingSchedule;
    parameterMap[ "MaximumNumberOfIterations" ]     = ParameterValuesType( 1, "256" );
  }
  else if( name == "groupwise" )
  {
    parameterMap[ "Registration" ]                  = ParameterValuesType( 1, "MultiResolutionRegistration" );
    parameterMap[ "Transform" ]                     = ParameterValuesType( 1, "BSplineStackTransform" );
    parameterMap[ "Metric" ]                        = ParameterValuesType( 1, "VarianceOverLastDimensionMetric" );
    parameterMap[ "FinalGridSpacingInVoxels" ]      = finalGridSpacingInVoxels;
    parameterMap[ "GridSpacingSchedule" ]           = gridSpacingSchedule;
    parameterMap[ "MaximumNumberOfIterations" ]     = ParameterValuesType( 1, "512" );
  }
  else
  {
    sitkExceptionMacro( "No default parameter map \"" << name << "\"." );
  }

  // Required for 2D
  if( dimension == 2 )
  {
    parameterMap[ "FixedImagePyramid" ]             = ParameterValuesType( 1, "FixedRecursiveImagePyramid" );
    parameterMap[ "MovingImagePyramid" ]            = ParameterValuesType( 1, "MovingRecursiveImagePyramid" );    
  }

  return parameterMap;
}



void
SimpleElastix
::PrettyPrint( const std::map< std::string, std::vector< std::string > > parameterMap )
{
  ParameterMapListType parameterMapList = ParameterMapListType( 1 );
  parameterMapList[ 0 ] = parameterMap;
  PrettyPrint( parameterMapList );
}



void
SimpleElastix
::PrettyPrint( const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapList )
{
  for( unsigned int i = 0; i < parameterMapList.size(); ++i )
  {
    std::cout << "ParameterMap " << i << ": " << std::endl;
    ParameterMapConstIterator parameterMapIterator = parameterMapList[ 0 ].begin();
    ParameterMapConstIterator parameterMapIteratorEnd = parameterMapList[ 0 ].end();
    while( parameterMapIterator != parameterMapIteratorEnd )
    {
      std::cout << "  (" << parameterMapIterator->first;
      ParameterValuesType parameterMapValues = parameterMapIterator->second;
      
      for(unsigned int j = 0; j < parameterMapValues.size(); ++j)
      {
        std::stringstream stream( parameterMapValues[ j ] );
        float number;
        stream >> number;
        if( stream.fail() ) {
           std::cout << " \"" << parameterMapValues[ j ] << "\"";
        }
        else
        {
          std::cout << " " << number;
        }      
      }
      
      std::cout << ")" << std::endl;
      parameterMapIterator++;
    }
  }
}



Image
SimpleElastix
::Execute( void )
{
  const PixelIDValueEnum FixedImagePixelEnum = this->m_FixedImage.GetPixelID();
  const unsigned int FixedImageDimension = this->m_FixedImage.GetDimension();

  if (this->m_MemberFactory->HasMemberFunction( FixedImagePixelEnum, FixedImageDimension ) )
  {
    return this->m_MemberFactory->GetMemberFunction( FixedImagePixelEnum, FixedImageDimension )();
  }

  sitkExceptionMacro( << "SimpleElastix does not support the combination of image type \""
                      << GetPixelIDValueAsString( FixedImagePixelEnum ) << "and dimension "
                      << FixedImageDimension << ". For elastix support, recompile elastix "
                      << "with the desired pixel type and cast the SimpleITK image. Supported types are "
                      << "sitkUInt8, sitkInt8, sitkUInt16, sitkInt16, sitkUInt32, sitkInt32, "
                      << "sitkInt64, sitkUInt64, sitkFloat32 or sitkFloat64." );
}



Image&
SimpleElastix
::GetResultImage( void )
{
  return this->m_ResultImage;
}



void
SimpleElastix
::LogToFolder( const std::string folder )
{
  this->m_OutputFolder = folder;
}



void
SimpleElastix
::LogToFolderOff( void )
{
  this->m_OutputFolder = "";
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



bool
SimpleElastix
::isEmpty( const Image& image )
{
  return( image.GetWidth() == 0 && image.GetHeight() == 0 );
}



// Procedural interface 



std::map< std::string, std::vector< std::string > >
GetDefaultParameterMap( std::string name )
{
  SimpleElastix selx;
  SimpleElastix::ParameterMapType parameterMap = selx.GetDefaultParameterMap( name );
  return parameterMap;
}



std::map< std::string, std::vector< std::string > >
ReadParameterFile( const std::string filename )
{
  SimpleElastix selx;
  SimpleElastix::ParameterMapType parameterMap = selx.ParameterFileReader( filename );
  return parameterMap;
}



Image
elastix( const Image& fixedImage, const Image& movingImage, const std::string defaultParameterMapName, const bool logToConsole, const std::string outputFolder )
{
  return elastix( fixedImage, movingImage, GetDefaultParameterMap( defaultParameterMapName ), logToConsole, outputFolder );
}



Image
elastix( const Image& fixedImage, const Image& movingImage, const std::map< std::string, std::vector< std::string > > parameterMap, const bool logToConsole, const std::string outputFolder )
{
  SimpleElastix::ParameterMapListType parameterMapList = SimpleElastix::ParameterMapListType( 1 );
  parameterMapList[ 0 ] = parameterMap;
  return elastix( fixedImage, movingImage, parameterMapList, logToConsole, outputFolder );
}



Image
elastix( const Image& fixedImage, const Image& movingImage, const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapList, const bool logToConsole, const std::string outputFolder )
{
  SimpleElastix selx;
  selx.SetFixedImage( fixedImage );
  selx.SetMovingImage( movingImage );
  selx.SetParameterMapList( parameterMapList );
  selx.LogToFolder( outputFolder );
  selx.LogToConsole( logToConsole );

  return selx.Execute();
}



Image
elastix( const Image& fixedImage, const Image& movingImage, const std::string defaultParameterMapName, const Image& fixedMask, const Image& movingMask, const bool logToConsole, const std::string outputFolder )
{
  return elastix( fixedImage, movingImage, GetDefaultParameterMap( defaultParameterMapName ), fixedMask, movingMask, logToConsole, outputFolder );
}




Image
elastix( const Image& fixedImage, const Image& movingImage, const std::map< std::string, std::vector< std::string > > parameterMap, const Image& fixedMask, const Image& movingMask, bool logToConsole, std::string outputFolder )
{
  SimpleElastix::ParameterMapListType parameterMapList = SimpleElastix::ParameterMapListType( 1 );
  parameterMapList[ 0 ] = parameterMap;
  return elastix( fixedImage, movingImage, parameterMapList, fixedMask, movingMask, logToConsole, outputFolder );
}



Image
elastix( const Image& fixedImage, const Image& movingImage, const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapList, const Image& fixedMask, const Image& movingMask, bool logToConsole, std::string outputFolder )
{
  SimpleElastix selx;
  selx.SetFixedImage( fixedImage );
  selx.SetMovingImage( movingImage );
  selx.SetParameterMapList( parameterMapList );
  selx.SetFixedMask( fixedMask );
  selx.SetMovingMask( movingMask );
  selx.LogToFolder( outputFolder );
  selx.LogToConsole( logToConsole );

  return selx.Execute();
}


} // end namespace simple
} // end namespace itk

#endif // __selxsimpleelastix_cxx_