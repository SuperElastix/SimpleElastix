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
  this->m_FixedMask = 0;
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
  ParameterMapType parameterMap;

  parameterMap["Optimizer"]                     = "AdaptiveStochasticGradientDescent";
  parameterMap["Interpolator"]                  = "LinearInterpolator";
  parameterMap["ResampleInterpolator"]          = "FinalBSplineResampleInterpolator";

  switch name
  {
    case "rigid":
        parameterMap[ "Registration" ]          = "MultiResolutionRegistration";
        parameterMap[ "Transform" ]             = "AffineTransform";
        parameterMap[ "Metric" ]                = "MattesMutualInformationMetric";
        parameterMap[ "MaximumNumberOfSamples"] = "8192";

      break;
    case "nonrigid":
        parameterMap[ "Registration" ]          = "MultiMetricMultiResolutionRegistration";
      break;
    case "groupwise":
        parameterMap[ "Registration" ]          = "MultiResolutionRegistration";
      break;
    default :
      sitkExceptionMacro( "No default parameter map named \"" << name << "\"." );
  }


  return parameterMap;
}



// Procedural interface 



Image
elastix( Image fixedImage, Image movingImage, std::string defaultParameterMapName, bool logToConsole, bool logToDisk, std::string outputFolder )
{
  SimpleElastix::ParameterMapListType parameterMapList;
  return elastix( fixedImage, movingImage, GetDefaultParameterMap( defaultParameterMapName ), logToConsole, logToDisk, outputFolder );
}



Image
elastix( Image fixedImage, Image movingImage, std::string defaultParameterMapName, bool logToConsole, bool logToDisk, std::string outputFolder )
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
  SimpleElastix::ParameterMapListType parameterMapList;
  return elastix( fixedImage, movingImage, GetDefaultParameterMap( defaultParameterMapName ), fixedMask, movingMask, logToConsole, logToDisk, outputFolder );
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



typename SimpleElastix::ParameterMapType
ReadParameterFile( const std::string filename )
{
  SimpleElastix selx;
  return selx.ParameterFileReader( filename );
}



} // end namespace simple
} // end namespace itk

#endif // __selxsimpleelastix_cxx_