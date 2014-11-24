#ifndef __selxsimpleelastix_cxx_
#define __selxsimpleelastix_cxx_

#include "selxSimpleElastix.h"

namespace itk {
  namespace simple {

SimpleElastix
::SimpleElastix( void )
{
  this->m_Elastix = new ElastixLibType();

  this->m_LogFileName = "";
}

SimpleElastix
::~SimpleElastix( void )
{
  delete this->m_Elastix;
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
::SetFixedImage( Image fixedImage )
{
  this->m_FixedImage = fixedImage;
}

void 
SimpleElastix
::SetMovingImage( Image movingImage )
{
  this->m_MovingImage = movingImage;
}

void 
SimpleElastix
::SetFixedMask( Image fixedMask )
{
  this->m_FixedMask = fixedMask;
}

void 
SimpleElastix
::SetMovingMask( Image movingMask )
{
  this->m_MovingMask = movingMask;
}

void
SimpleElastix
::SetParameterMap( ParameterMapListType parameterMapList )
{
  this->m_ParameterMapList = parameterMapList;
}

void
SimpleElastix
::SetParameterMap( ParameterMapType parameterMap )
{
  ParameterMapListType parameterMapList;
  parameterMapList.push_back( parameterMap );
  this->SetParameterMap( parameterMapList );
}

void
SimpleElastix
::AppendParameterMap( ParameterMapListType parameterMapList )
{
  this->m_ParameterMapList.insert( this->m_ParameterMapList.end(), 
                                   parameterMapList.begin(),
                                   parameterMapList.end() );
}

void
SimpleElastix
::AppendParameterMap( ParameterMapType parameterMap )
{
  ParameterMapListType parameterMapList;
  parameterMapList.push_back( parameterMap );
  this->AppendParameterMap( parameterMapList );
}

SimpleElastix::ParameterMapListType
SimpleElastix
::GetParameterMapList( void )
{
  return this->m_ParameterMapList;
}


SimpleElastix::ParameterMapType
SimpleElastix
::GetParameterMap( int n )
{
  return this->m_ParameterMapList[ n ];
}

SimpleElastix::ParameterMapType
SimpleElastix
::GetParameterMap( void )
{
  return this->GetParameterMap( this->m_ParameterMapList.size()-1 );
}

int
SimpleElastix
::GetNumberOfParameterMaps( void )
{
  return this->m_ParameterMapList.size();
}

SimpleElastix::ParameterMapType
SimpleElastix
::ReadParameterMap( const std::string filename)
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

void
SimpleElastix
::Run( void )
{
  bool logToFile = false;
  if( this->m_LogFileName != "" )
  {
    logToFile = true;
  }

  int isError = 1;
  try
  {
    isError = this->m_Elastix->RegisterImages(
      static_cast< typename itk::DataObject::Pointer >( this->m_FixedImage.GetITKBase() ),
      static_cast< typename itk::DataObject::Pointer >( this->m_MovingImage.GetITKBase() ),
      this->m_ParameterMapList,
      this->m_LogFileName,
      logToFile,
      false,
      0,
      0
    );
  }
  catch( itk::ExceptionObject &e )
  {
    std::cout << e.what() << std::endl;
  }

  if( isError != 0 )
  {
    std::cout << "Errors occured during registration. ";

    if( this->m_LogFileName == "" && this->m_LogToConsole == false )
    {
      std::cout << "Switch on logging to inspect.";
    }

    std::cout << std::endl;
  }
}

Image
SimpleElastix
::GetResultImage( void )
{
  if( this->m_Elastix->GetResultImage().IsNotNull() )
  {
    std::cout << "TODO: Return image" << std::cout;
    //ITKImageType* resultImage;
    //resultImage = dynamic_cast< ITKImageType* >( this->m_Elastix->GetResultImage().GetPointer() );
    //return Image( resultImage );
  }
  else
  {
    std::cout << "No result image found. Errors occured during registration or you need to call Run()." << std::endl;
  }
}

SimpleElastix::ParameterMapType
SimpleElastix
::GetTransformParameterMap( void )
{
  return this->m_Elastix->GetTransformParameterMap();
}

SimpleElastix::ParameterMapListType
SimpleElastix
::GetTransformParameterMapList( void )
{
  return this->m_Elastix->GetTransformParameterMapList();
}

/** Procedural interface */

SimpleElastix::ParameterMapType
ReadParameterMap( const std::string filename )
{
  SimpleElastix elastix;
  return elastix.ReadParameterMap( filename );
}

} // end namespace simple
} // end namespace itk

#endif // __selxsimpleelastix_cxx_