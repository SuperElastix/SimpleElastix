#ifndef __selxsimpleelastix_cxx_
#define __selxsimpleelastix_cxx_

#include "selxSimpleElastix.h"

namespace itk {
  namespace simple {

SimpleElastix
::SimpleElastix( void )
{
  this->m_Elastix = new ElastixLibType();
  this->m_FixedMask = 0;
  this->m_MovingImage = 0;
  this->m_FixedMask = 0;
  this->m_MovingMask = 0;
  this->m_ParameterMapList = ParameterMapListType();
  this->m_LogFileName = "";
  this->m_LogToConsole = false;
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
::SetFixedImage( Image& fixedImage )
{
  std::cout << "Setting fixed image ... " << std::endl;
  this->m_FixedImage = &fixedImage;
}

void 
SimpleElastix
::SetMovingImage( Image& movingImage )
{
  std::cout << "Setting moving image ... " << std::endl;
  this->m_MovingImage = &movingImage;
}

void 
SimpleElastix
::SetFixedMask( Image& fixedMask )
{
  this->m_FixedMask = &fixedMask;
}

void 
SimpleElastix
::SetMovingMask( Image& movingMask )
{
  this->m_MovingMask = &movingMask;
}

Image* 
SimpleElastix
::GetFixedImage( void )
{
  std::cout << "Returning fixed image ... " << std::endl;
  return this->m_FixedImage;
}

void
SimpleElastix
::SetParameterMap( ParameterMapListType parameterMapList )
{
  std::cout << "Setting ParameterMap ... " << std::endl;
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
::ReadParameterFile( const std::string filename)
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
  std::cout << "Setting images ... " << std::endl;

  itk::DataObject::Pointer fixedImage = 0;
  if( this->m_FixedImage )
  {
    fixedImage = static_cast< typename itk::DataObject::Pointer >( this->m_FixedImage->GetITKBase() );
  }
  else
  {
    sitkExceptionMacro( << "Fixed image is not set. Use SetFixedImage() or Help() to get information on how to use this module." );
  }

  itk::DataObject::Pointer movingImage = 0;
  if( this->m_MovingImage )
  {
    movingImage = static_cast< typename itk::DataObject::Pointer >( this->m_MovingImage->GetITKBase() );
  }
  else
  {
    sitkExceptionMacro( << "Moving image is not set. Use SetMovingImage() or Help() to get information on how to use this module." );
  }

  itk::DataObject::Pointer fixedMask = 0;
  if( this->m_FixedMask )
  {
    fixedMask = static_cast< typename itk::DataObject::Pointer >( this->m_FixedMask->GetITKBase() );
  }

  itk::DataObject::Pointer movingMask = 0;
  if( this->m_MovingMask )
  {
    movingMask = static_cast< typename itk::DataObject::Pointer >( this->m_MovingMask->GetITKBase() );
  }

  std::cout << "Invoking RegisterImages() ... " << std::endl;

  std::string fn = std::string("parameterfile.bending.txt");
  ParameterMapType p = this->ReadParameterFile(fn);

  int isError = 1;
  try
  {
    isError = this->m_Elastix->RegisterImages(
      fixedImage,
      movingImage,
      p, // this->m_ParameterMapList,
      this->m_LogFileName,
      this->m_LogFileName != "",
      this->m_LogToConsole,
      fixedMask,
      movingMask
    );
  }
  catch( itk::ExceptionObject &e )
  {
    sitkExceptionMacro( << e.what() );
  }

  if( isError != 0 )
  {
    sitkExceptionMacro( << "Errors occured during registration. Switch on logging to inspect." );
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
::LogFileName( const std::string filename )
{
  this->m_LogFileName = filename;
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
ReadParameterFile( const std::string filename )
{
  SimpleElastix elastix;
  return elastix.ReadParameterFile( filename );
}

} // end namespace simple
} // end namespace itk

#endif // __selxsimpleelastix_cxx_