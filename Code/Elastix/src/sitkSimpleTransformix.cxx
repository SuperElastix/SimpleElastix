#ifndef __sitksimpletransformix_cxx_
#define __sitksimpletransformix_cxx_

#include "sitkSimpleTransformix.h"
#include "sitkSimpleTransformix.hxx"

namespace itk {
  namespace simple {



SimpleTransformix
::SimpleTransformix( void )
{
  // Register this class with SimpleITK
  m_MemberFactory.reset( new detail::MemberFunctionFactory< MemberFunctionType >( this ) );
  m_MemberFactory->RegisterMemberFunctions< BasicPixelIDTypeList, 3, SimpleTransformixAddressor< MemberFunctionType > >();
  m_MemberFactory->RegisterMemberFunctions< BasicPixelIDTypeList, 2, SimpleTransformixAddressor< MemberFunctionType > >();

  // This class holds configuration and pointers to data that is passed to Transformix API when run
  this->m_InputImage = Image();
  this->m_TransformParameterMaps = ParameterMapListType();
  this->m_ResultImage = Image();
  this->m_OutputFolder = "";
  this->m_LogToConsole = false;
}



SimpleTransformix
::~SimpleTransformix( void )
{
}



const std::string 
SimpleTransformix
::GetName( void )
{ 
  const std::string name = std::string( "SimpleTransformix" );
  return name;
}



SimpleTransformix::Self&
SimpleTransformix
::SetInputImage( const Image& inputImage )
{
  this->m_InputImage = inputImage;
  return *this;
}



Image
SimpleTransformix
::GetInputImage( void )
{
  return this->m_InputImage;
}



Image
SimpleTransformix
::GetResultImage( void )
{
  return this->m_ResultImage;
}



Image
SimpleTransformix
::Execute( void )
{
  const PixelIDValueEnum InputImagePixelEnum = this->m_InputImage.GetPixelID();
  const unsigned int InputImageDimension = this->m_InputImage.GetDimension();

  if (this->m_MemberFactory->HasMemberFunction( InputImagePixelEnum, InputImageDimension ) )
  {
    return this->m_MemberFactory->GetMemberFunction( InputImagePixelEnum, InputImageDimension )();
  }

  sitkExceptionMacro( << "SimpleITK does not support the combination of image type \""
                      << GetPixelIDValueAsString( InputImagePixelEnum ) << "\" ("
                      << GetPixelIDValueAsElastixParameter( InputImagePixelEnum ) << ") and dimension "
                      << InputImageDimension << "." );
}



SimpleTransformix::Self&
SimpleTransformix
::LogToFolder( const std::string folder )
{
  this->m_OutputFolder = folder;
  return *this;
}



SimpleTransformix::Self&
SimpleTransformix
::LogToFolderOff()
{
  this->m_OutputFolder = "";
  return *this;
}



SimpleTransformix::Self&
SimpleTransformix
::LogToConsole( bool logToConsole )
{
  this->m_LogToConsole = logToConsole;
  return *this;
}



SimpleTransformix::Self&
SimpleTransformix
::SetTransformParameterMap( std::vector< std::map< std::string, std::vector< std::string > > > parameterMapList )
{
  this->m_TransformParameterMaps = parameterMapList;
  return *this;
}



SimpleTransformix::Self&
SimpleTransformix
::SetTransformParameterMap( std::map< std::string, std::vector< std::string > > parameterMap )
{
  ParameterMapListType parameterMapList;
  parameterMapList.push_back( parameterMap );
  this->SetTransformParameterMap( parameterMapList );
  return *this;
}



std::vector< std::map< std::string, std::vector< std::string > > > 
SimpleTransformix
::GetTransformParameterMap( void )
{
  return this->m_TransformParameterMaps;
}



std::map< std::string, std::vector< std::string > > 
SimpleTransformix
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



SimpleTransformix::Self&
SimpleTransformix
::WriteParameterFile( std::map< std::string, std::vector< std::string > > const parameterMap, const std::string filename )
{
  std::ofstream parameterFile;
  parameterFile << std::fixed;

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



SimpleTransformix::Self& 
SimpleTransformix
::PrettyPrint( void )
{
  this->PrettyPrint( this->GetTransformParameterMap() );
  return *this;
}



SimpleTransformix::Self& 
SimpleTransformix
::PrettyPrint( const std::map< std::string, std::vector< std::string > > parameterMap )
{
  ParameterMapListType parameterMapList = ParameterMapListType( 1 );
  parameterMapList[ 0 ] = parameterMap;
  this->PrettyPrint( parameterMapList );
  return *this;
}



SimpleTransformix::Self& 
SimpleTransformix
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



bool
SimpleTransformix
::IsEmpty( const Image& image )
{
  bool isEmpty = image.GetWidth() == 0 && image.GetHeight() == 0;
  return isEmpty;
}



// Procedural interface



Image
Transformix( const Image& inputImage, std::map< std::string, std::vector< std::string > > parameterMap, const bool logToConsole, const std::string outputFolder )
{
  SimpleTransformix::ParameterMapListType parameterMapList;
  parameterMapList.push_back( parameterMap );
  return Transformix( inputImage, parameterMapList, logToConsole, outputFolder );
}



Image
Transformix( const Image& inputImage, std::vector< std::map< std::string, std::vector< std::string > > > parameterMapList, const bool logToConsole, const std::string outputFolder )
{
  SimpleTransformix stfx;
  stfx.SetInputImage( inputImage );
  stfx.SetTransformParameterMap( parameterMapList );
  stfx.LogToFolder( outputFolder );
  stfx.LogToConsole( logToConsole );

  return stfx.Execute();
}



} // end namespace simple
} // end namespace itk

#endif // __sitksimpletransformix_cxx_