#ifndef __selxsimpletransformix_cxx_
#define __selxsimpletransformix_cxx_

#include "selxSimpleTransformix.h"
#include "selxSimpleTransformix.hxx"

namespace itk {
  namespace simple {



SimpleTransformix
::SimpleTransformix( void )
{
  // Register this class with SimpleITK
  m_MemberFactory.reset( new detail::MemberFunctionFactory< MemberFunctionType >( this ) );
  m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 3, SimpleTransformixAddressor< MemberFunctionType > >();
  m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 2, SimpleTransformixAddressor< MemberFunctionType > >();

  // This class holds configuration and pointers to data that is passed to Transformix API when run
  this->m_InputImage = 0;
  this->m_TransformParameterMaps = ParameterMapListType();
  this->m_ResultImage = Image();
  this->m_OutputFolder = "";
  this->m_LogToDisk = false;
  this->m_LogToConsole = true;
}



SimpleTransformix
::~SimpleTransformix( void )
{
}



const std::string 
SimpleTransformix
::GetName( void )
{ 
  const std::string name = std::string("SimpleTransformix");
  return name;
}



void 
SimpleTransformix
::SetInputImage( Image* inputImage )
{
  this->m_InputImage = inputImage;
}



Image
SimpleTransformix
::Execute( void )
{
  const PixelIDValueEnum InputImagePixelEnum = this->m_InputImage->GetPixelID();
  const unsigned int InputImageDimension = this->m_InputImage->GetDimension();

  if (this->m_MemberFactory->HasMemberFunction( InputImagePixelEnum, InputImageDimension ) )
  {
    return this->m_MemberFactory->GetMemberFunction( InputImagePixelEnum, InputImageDimension )();
  }

  sitkExceptionMacro( << "SimpleTransformix does not support the combination of image type \""
                      << GetPixelIDValueAsString( InputImagePixelEnum ) << "\" ("
                      << GetPixelIDValueAsElastixParameter( InputImagePixelEnum ) << ") and dimension "
                      << InputImageDimension << "." );
}



Image 
SimpleTransformix
::GetResultImage( void )
{
  return this->m_ResultImage;
}



void
SimpleTransformix
::SetOutputFolder( const std::string folder )
{
  this->m_OutputFolder = folder;
}



void
SimpleTransformix
::LogToDisk( bool logToDisk )
{
  this->m_LogToDisk = logToDisk;
}



void
SimpleTransformix
::LogToDiskOn( void )
{
  this->m_LogToDisk = true;
}



void
SimpleTransformix
::LogToDiskOff( void )
{
  this->m_LogToDisk = false;
}



void
SimpleTransformix
::LogToConsole( bool logToConsole )
{
  this->m_LogToConsole = logToConsole;
}




void
SimpleTransformix
::LogToConsoleOn( void )
{
  this->m_LogToConsole = true;
}



void
SimpleTransformix
::LogToConsoleOff( void )
{
  this->m_LogToConsole = false;
}



void
SimpleTransformix
::SetTransformParameterMapList( std::vector< std::map< std::string, std::vector< std::string > > > parameterMapList )
{
  this->m_TransformParameterMaps = parameterMapList;
}



void
SimpleTransformix
::SetTransformParameterMap( std::map< std::string, std::vector< std::string > > parameterMap )
{
  ParameterMapListType parameterMapList;
  parameterMapList.push_back( parameterMap );
  this->SetTransformParameterMapList( parameterMapList );
}



SimpleTransformix::ParameterMapListType
SimpleTransformix
::GetTransformParameterMapList( void )
{
  return this->m_TransformParameterMaps;
}



SimpleTransformix::ParameterMapType
SimpleTransformix
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



Image
transformix( Image inputImage, SimpleTransformix::ParameterMapType parameterMap, bool logToConsole, bool logToDisk, std::string outputFolder )
{
  SimpleTransformix::ParameterMapListType parameterMapList;
  parameterMapList.push_back( parameterMap );
  return transformix( inputImage, parameterMapList, logToConsole, logToDisk, outputFolder );
}



Image
transformix( Image inputImage, SimpleTransformix::ParameterMapListType parameterMapList, bool logToConsole, bool logToDisk, std::string outputFolder )
{
  SimpleTransformix stfx;
  stfx.SetInputImage( &inputImage );
  stfx.SetTransformParameterMapList( parameterMapList );
  stfx.SetOutputFolder( outputFolder );
  stfx.LogToDisk( logToDisk );
  stfx.LogToConsole( logToConsole );

  return stfx.Execute();
}



} // end namespace simple
} // end namespace itk

#endif // __selxsimpletransformix_cxx_