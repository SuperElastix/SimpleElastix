#ifndef __selxsimpleelastix_cxx_
#define __selxsimpleelastix_cxx_

#include "SimpleITK.h"

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
::SetParameterMap( std::string filename )
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

  this->m_ParameterMap = parser->GetParameterMap();
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
      this->m_ParameterMap,
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
    ITKImageType* resultImage;
    resultImage = dynamic_cast< ITKImageType* >( this->m_Elastix->GetResultImage().GetPointer() );
    return Image( resultImage );
  }
  else
  {
    std::cout << "No result image. Errors occured during registration or you need to run Run() first." << std::endl;
  }
}

/** Procedural interface */

const std::string HelloWorld( void )
{
  SimpleElastix elastix;
  return elastix.GetName();
}

const std::string ReadParameterMap( const std::string filename )
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

  this->m_ParameterMap = parser->GetParameterMap();
}

} // end namespace simple
} // end namespace itk

#endif // __selxsimpleelastix_cxx_