#ifndef __sitksimpleelastix_cxx_
#define __sitksimpleelastix_cxx_

#include "sitkSimpleElastix.h"
#include "sitkSimpleElastix.hxx"

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



SimpleElastix::Self& 
SimpleElastix
::SetFixedImage( const Image& fixedImage )
{
  this->m_FixedImage = fixedImage;
  return *this;
}



Image&
SimpleElastix
::GetFixedImage( void )
{
  return this->m_FixedImage;
}



SimpleElastix::Self& 
SimpleElastix
::SetMovingImage( const Image& movingImage )
{
  this->m_MovingImage = movingImage;
  return *this;
}



Image&
SimpleElastix
::GetMovingImage( void )
{
  return this->m_MovingImage;
}



SimpleElastix::Self& 
SimpleElastix
::SetFixedMask( const Image& fixedMask )
{
  this->m_FixedMask = fixedMask;
  return *this;
}



Image&
SimpleElastix
::GetFixedMask( void )
{
  return this->m_FixedMask;
}



SimpleElastix::Self& 
SimpleElastix
::DeleteFixedMask( void )
{
  this->m_FixedMask = Image();
  return *this;
}



SimpleElastix::Self& 
SimpleElastix
::SetMovingMask( const Image& movingMask )
{
  this->m_MovingMask = movingMask;
  return *this;
}



Image&
SimpleElastix
::GetMovingMask( void )
{
  return this->m_MovingMask;
}



SimpleElastix::Self& 
SimpleElastix
::DeleteMovingMask( void )
{
  this->m_MovingMask = Image();
  return *this;
}



SimpleElastix::Self& 
SimpleElastix
::SetParameterMap( const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapList )
{
  this->m_ParameterMaps = parameterMapList;
  return *this;
}



SimpleElastix::Self& 
SimpleElastix
::SetParameterMap( const std::map< std::string, std::vector< std::string > > parameterMap )
{
  ParameterMapListType parameterMapList = ParameterMapListType( 1 );
  parameterMapList[ 0 ] = parameterMap;
  this->SetParameterMap( parameterMapList );
  return *this;
}



std::vector< std::map< std::string, std::vector< std::string > > > 
SimpleElastix
::GetParameterMap( void )
{
  return this->m_ParameterMaps;
}



std::vector< std::map< std::string, std::vector< std::string > > > 
SimpleElastix
::GetTransformParameterMap( void )
{
  return this->m_TransformParameterMaps;
}



std::map< std::string, std::vector< std::string > >
SimpleElastix
::ReadParameterFile( const std::string filename )
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



SimpleElastix::Self&
SimpleElastix
::WriteParameterFile( std::map< std::string, std::vector< std::string > > const parameterMap, const std::string filename )
{
  std::ofstream parameterFile;
  parameterFile.open( filename.c_str(), std::ofstream::out );

  ParameterMapConstIterator parameterMapIterator = parameterMap.begin();
  ParameterMapConstIterator parameterMapIteratorEnd = parameterMap.end();
  while( parameterMapIterator != parameterMapIteratorEnd )
  {
    parameterFile << "(" << parameterMapIterator->first;

    ParameterValuesType parameterMapValues = parameterMapIterator->second;
    for( unsigned int i = 0; i < parameterMapValues.size(); ++i )
    {
      std::stringstream stream( parameterMapValues[ i ] );
      float number;
      stream >> number;
      if( stream.fail() || stream.bad() ) {
         parameterFile << " \"" << parameterMapValues[ i ] << "\"";
      }
      else
      {
        parameterFile << " " << number;
      }      
    }
      
    parameterFile << ")" << std::endl;
    parameterMapIterator++;
  }

  parameterFile.close();

  return *this;
}



std::map< std::string, std::vector< std::string > >
SimpleElastix
::GetDefaultParameterMap( const std::string transform, const unsigned int numberOfResolutions, const double finalGridSpacingInPhysicalUnits )
{ 

  // Parameters that depend on size and number of resolutions
  ParameterMapType parameterMap                     = ParameterMapType();

  // Common Components
  parameterMap[ "FixedImagePyramid" ]                 = ParameterValuesType( 1, "FixedSmoothingImagePyramid" );
  parameterMap[ "MovingImagePyramid" ]                = ParameterValuesType( 1, "MovingSmoothingImagePyramid" );
  parameterMap[ "Interpolator"]                       = ParameterValuesType( 1, "LinearInterpolator");
  parameterMap[ "Optimizer" ]                         = ParameterValuesType( 1, "AdaptiveStochasticGradientDescent" );
  parameterMap[ "Resampler"]                          = ParameterValuesType( 1, "DefaultResampler" );
  parameterMap[ "ResampleInterpolator"]               = ParameterValuesType( 1, "FinalBSplineInterpolator" );
  parameterMap[ "FinalBSplineInterpolationOrder" ]    = ParameterValuesType( 1, "2" );
  parameterMap[ "NumberOfResolutions" ]               = ParameterValuesType( 1, std::to_string( numberOfResolutions ) );

  // Image Sampler
  parameterMap[ "ImageSampler" ]                      = ParameterValuesType( 1, "RandomCoordinate" ); 
  parameterMap[ "NumberOfSpatialSamples"]             = ParameterValuesType( 1, "2048" );
  parameterMap[ "CheckNumberOfSamples" ]              = ParameterValuesType( 1, "true" );
  parameterMap[ "MaximumNumberOfSamplingAttempts" ]   = ParameterValuesType( 1, "8" );
  parameterMap[ "NewSamplesEveryIteration" ]          = ParameterValuesType( 1, "true");

  // Optimizer
  parameterMap[ "NumberOfSamplesForExactGradient" ]   = ParameterValuesType( 1, "4096" );
  parameterMap[ "DefaultPixelValue" ]                 = ParameterValuesType( 1, "0" );
  parameterMap[ "AutomaticParameterEstimation" ]      = ParameterValuesType( 1, "true" );

  // Output
  parameterMap[ "WriteResultImage" ]                  = ParameterValuesType( 1, "true" );

  // Transforms
  if( transform == "translation" )
  {
    parameterMap[ "Registration" ]                    = ParameterValuesType( 1, "MultiResolutionRegistration" );
    parameterMap[ "Transform" ]                       = ParameterValuesType( 1, "TranslationTransform" );
    parameterMap[ "Metric" ]                          = ParameterValuesType( 1, "AdvancedMattesMutualInformation" );
    parameterMap[ "MaximumNumberOfIterations" ]       = ParameterValuesType( 1, "64" );
  }
  else if( transform == "rigid" )
  {
    parameterMap[ "Registration" ]                    = ParameterValuesType( 1, "MultiResolutionRegistration" );
    parameterMap[ "Transform" ]                       = ParameterValuesType( 1, "EulerTransform" );
    parameterMap[ "Metric" ]                          = ParameterValuesType( 1, "AdvancedMattesMutualInformation" );
    parameterMap[ "MaximumNumberOfIterations" ]       = ParameterValuesType( 1, "64" );
  }
  else if( transform == "affine" )
  {
    parameterMap[ "Registration" ]                    = ParameterValuesType( 1, "MultiResolutionRegistration" );
    parameterMap[ "Transform" ]                       = ParameterValuesType( 1, "AffineTransform" );
    parameterMap[ "Metric" ]                          = ParameterValuesType( 1, "AdvancedMattesMutualInformation" );
    parameterMap[ "MaximumNumberOfIterations" ]       = ParameterValuesType( 1, "128" );
  }
  else if( transform == "nonrigid" )
  {
    parameterMap[ "Registration" ]                    = ParameterValuesType( 1, "MultiMetricMultiResolutionRegistration" );
    parameterMap[ "Transform" ]                       = ParameterValuesType( 1, "BSplineTransform" );
    parameterMap[ "Metric" ]                          = ParameterValuesType( 1, "AdvancedMattesMutualInformation" );
    parameterMap[ "Metric" ]                            .push_back( "TransformBendingEnergyPenalty" );
    parameterMap[ "Metric0Weight" ]                   = ParameterValuesType( 1, "0.0001" );
    parameterMap[ "Metric1Weight" ]                   = ParameterValuesType( 1, "0.9999" );
    parameterMap[ "MaximumNumberOfIterations" ]       = ParameterValuesType( 1, "256" );
  }
  else if( transform == "groupwise" )
  {
    parameterMap[ "Registration" ]                    = ParameterValuesType( 1, "MultiResolutionRegistration" );
    parameterMap[ "Transform" ]                       = ParameterValuesType( 1, "BSplineStackTransform" );
    parameterMap[ "Metric" ]                          = ParameterValuesType( 1, "VarianceOverLastDimensionMetric" );
    parameterMap[ "MaximumNumberOfIterations" ]       = ParameterValuesType( 1, "512" );
  }
  else
  {
    sitkExceptionMacro( "No default parameter map \"" << transform << "\"." );
  }

  // B-spline transforms settings 
  if( transform == "nonrigid" || transform == "groupwise")
  {
    ParameterValuesType gridSpacingSchedule = ParameterValuesType();
    for( unsigned int resolution = 0; resolution < numberOfResolutions; ++resolution )
    {
      gridSpacingSchedule.insert( gridSpacingSchedule.begin(), std::to_string( pow( 2, resolution ) ) ); 
    }

    parameterMap[ "GridSpacingSchedule" ] = gridSpacingSchedule;
    parameterMap[ "FinalGridSpacingInVoxels" ] = ParameterValuesType( 1, std::to_string( finalGridSpacingInPhysicalUnits ) );;
  }

  // Fixed image pyramid has to be FixedRecursiveImagePyramid in 2D
  if( !isEmpty( this->m_FixedImage ) )
  {
    if( this->m_FixedImage.GetDimension() == 2 )
    {
      parameterMap[ "FixedImagePyramid" ] = ParameterValuesType( 1, "FixedRecursiveImagePyramid" );
    }
  }

  // Moving image pyramid has to be MovingRecursiveImagePyramid in 2D
  if( !isEmpty( this->m_MovingImage ) )
  {
    if( this->m_MovingImage.GetDimension() == 2 )
    {
      parameterMap[ "MovingImagePyramid" ] = ParameterValuesType( 1, "MovingRecursiveImagePyramid" );
    }
  }

  return parameterMap;
}



SimpleElastix::Self&
SimpleElastix
::PrettyPrint( void )
{
  this->PrettyPrint( this->GetParameterMap() );
  return *this;
}



SimpleElastix::Self& 
SimpleElastix
::PrettyPrint( const std::map< std::string, std::vector< std::string > > parameterMap )
{
  ParameterMapListType parameterMapList = ParameterMapListType( 1 );
  parameterMapList[ 0 ] = parameterMap;
  this->PrettyPrint( parameterMapList );
  return *this;
}



SimpleElastix::Self& 
SimpleElastix
::PrettyPrint( const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapList )
{
  for( unsigned int i = 0; i < parameterMapList.size(); ++i )
  {
    std::cout << "ParameterMap " << i << ": " << std::endl;
    ParameterMapConstIterator parameterMapIterator = parameterMapList[ i ].begin();
    ParameterMapConstIterator parameterMapIteratorEnd = parameterMapList[ i ].end();
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

  return *this;
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
                      << "with the desired pixel type or cast the SimpleITK image. Supported types are "
                      << "sitkUInt8, sitkInt8, sitkUInt16, sitkInt16, sitkUInt32, sitkInt32, "
                      << "sitkInt64, sitkUInt64, sitkFloat32 or sitkFloat64." );
}



Image&
SimpleElastix
::GetResultImage( void )
{
  return this->m_ResultImage;
}



SimpleElastix::Self& 
SimpleElastix
::LogToFolder( const std::string folder )
{
  this->m_OutputFolder = folder;
  return *this;
}



SimpleElastix::Self& 
SimpleElastix
::LogToFolderOff( void )
{
  this->m_OutputFolder = "";
  return *this;
}



SimpleElastix::Self& 
SimpleElastix
::LogToConsole( bool logToConsole )
{
  this->m_LogToConsole = logToConsole;
  return *this;
}



bool
SimpleElastix
::isEmpty( const Image& image )
{
  return( image.GetWidth() == 0 && image.GetHeight() == 0 );
}



/**
 * Procedural interface 
 */



std::map< std::string, std::vector< std::string > >
GetDefaultParameterMap( std::string transform, const unsigned int numberOfResolutions, const double finalGridSpacingInPhysicalUnits )
{
  SimpleElastix selx;
  SimpleElastix::ParameterMapType parameterMap = selx.GetDefaultParameterMap( transform, numberOfResolutions, finalGridSpacingInPhysicalUnits );
  return parameterMap;
}



std::map< std::string, std::vector< std::string > >
ReadParameterFile( const std::string filename )
{
  SimpleElastix selx;
  SimpleElastix::ParameterMapType parameterMap = selx.ReadParameterFile( filename );
  return parameterMap;
}



void
WriteParameterFile( std::map< std::string, std::vector< std::string > > const parameterMap, const std::string filename )
{
  SimpleElastix selx;
  selx.WriteParameterFile( parameterMap, filename );
}




void 
PrettyPrint( std::map< std::string, std::vector< std::string > > const parameterMap )
{
  SimpleElastix::ParameterMapListType parameterMapList = SimpleElastix::ParameterMapListType( 1 );
  parameterMapList[ 0 ] = parameterMap;
  PrettyPrint( parameterMapList );
}



void
PrettyPrint( std::vector< std::map< std::string, std::vector< std::string > > > const parameterMapList )
{
  SimpleElastix selx;
  selx.PrettyPrint( parameterMapList );
}



Image
Elastix( const Image& fixedImage, const Image& movingImage, const std::string defaultParameterMapName, const bool logToConsole, const std::string outputFolder )
{
  return Elastix( fixedImage, movingImage, GetDefaultParameterMap( defaultParameterMapName ), logToConsole, outputFolder );
}



Image
Elastix( const Image& fixedImage, const Image& movingImage, const std::map< std::string, std::vector< std::string > > parameterMap, const bool logToConsole, const std::string outputFolder )
{
  SimpleElastix::ParameterMapListType parameterMapList = SimpleElastix::ParameterMapListType( 1 );
  parameterMapList[ 0 ] = parameterMap;
  return Elastix( fixedImage, movingImage, parameterMapList, logToConsole, outputFolder );
}



Image
Elastix( const Image& fixedImage, const Image& movingImage, const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapList, const bool logToConsole, const std::string outputFolder )
{
  SimpleElastix selx;
  selx.SetFixedImage( fixedImage );
  selx.SetMovingImage( movingImage );
  selx.SetParameterMap( parameterMapList );
  selx.LogToFolder( outputFolder );
  selx.LogToConsole( logToConsole );

  return selx.Execute();
}



Image
Elastix( const Image& fixedImage, const Image& movingImage, const std::string defaultParameterMapName, const Image& fixedMask, const Image& movingMask, const bool logToConsole, const std::string outputFolder )
{
  return Elastix( fixedImage, movingImage, GetDefaultParameterMap( defaultParameterMapName ), fixedMask, movingMask, logToConsole, outputFolder );
}




Image
Elastix( const Image& fixedImage, const Image& movingImage, const std::map< std::string, std::vector< std::string > > parameterMap, const Image& fixedMask, const Image& movingMask, bool logToConsole, std::string outputFolder )
{
  SimpleElastix::ParameterMapListType parameterMapList = SimpleElastix::ParameterMapListType( 1 );
  parameterMapList[ 0 ] = parameterMap;
  return Elastix( fixedImage, movingImage, parameterMapList, fixedMask, movingMask, logToConsole, outputFolder );
}



Image
Elastix( const Image& fixedImage, const Image& movingImage, const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapList, const Image& fixedMask, const Image& movingMask, bool logToConsole, std::string outputFolder )
{
  SimpleElastix selx;
  selx.SetFixedImage( fixedImage );
  selx.SetMovingImage( movingImage );
  selx.SetParameterMap( parameterMapList );
  selx.SetFixedMask( fixedMask );
  selx.SetMovingMask( movingMask );
  selx.LogToFolder( outputFolder );
  selx.LogToConsole( logToConsole );

  return selx.Execute();
}


} // end namespace simple
} // end namespace itk

#endif // __sitksimpleelastix_cxx_