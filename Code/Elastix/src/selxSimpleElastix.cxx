#ifndef __selxsimpleelastix_cxx_
#define __selxsimpleelastix_cxx_

#include "selxSimpleElastix.h"

namespace itk {
  namespace simple {

SimpleElastix
::SimpleElastix( void )
{
  this->m_Elastix = new ElastixLibType();
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
::Run( void )
{
  int isError;
  try
  {
    isError = this->m_Elastix->RegisterImages(
      static_cast< typename itk::DataObject::Pointer >( this->m_FixedImage.GetITKBase() ),
      static_cast< typename itk::DataObject::Pointer >( this->m_MovingImage.GetITKBase() ),
      this->m_ParameterMapList,
      "",
      false,
      false,
      0,
      0
    );
  }
  catch( itk::ExceptionObject &e )
  {
    std::cout << e.what() << std::endl;
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
    std::cout << "No result image. Errors occured during registration or you need to run Run() first." << std::endl;
  }
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

/** Procedural interface */

const std::string
HelloWorld( void )
{
  SimpleElastix elastix;
  return elastix.GetName();
}

SimpleElastix::ParameterMapType
ReadParameterMap( const std::string filename )
{
  SimpleElastix elastix;
  return elastix.ReadParameterMap( filename );
}

} // end namespace simple
} // end namespace itk

#endif // __selxsimpleelastix_cxx_