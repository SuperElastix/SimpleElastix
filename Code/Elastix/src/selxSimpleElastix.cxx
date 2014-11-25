#ifndef __selxsimpleelastix_cxx_
#define __selxsimpleelastix_cxx_

#include "selxSimpleElastix.h"

// tmp
#include "itkImage.h"
#include "itkImageFileReader.h"

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

Image*
SimpleElastix
::GetFixedImage( void )
{
  return this->m_FixedImage;
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

  itk::DataObject::Pointer fixedImage = 0;
  if( this->m_FixedImage->GetITKBase() )
  {
    typedef itk::ImageFileReader< TFixedImage > ReaderType;
   
    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName("01001_t1_cma.hdr");

    fixedImage = static_cast< typename itk::DataObject::Pointer >( reader->GetOutput() );
    fixedImage->SetRequestedRegionToLargestPossibleRegion();
    fixedImage->Update();
  }
  else
  {
    sitkExceptionMacro( << "Fixed image is not set. Use SetFixedImage() or run Help() to get information on how to use this module." );
  }

  itk::DataObject::Pointer movingImage = 0;
  if( this->m_MovingImage->GetITKBase() )
  {
    // TODO: Template casting away
    itk::simple::CastImageFilter caster;
    caster.SetOutputPixelType( itk::simple::sitkFloat32 );
    (*this->m_MovingImage) = caster.Execute( (*this->m_MovingImage) );

    TMovingImage::Pointer itkImage = CastImageToITK< TMovingImage >( this->m_MovingImage );
    movingImage = static_cast< typename itk::DataObject::Pointer >( itkImage );
  }
  else
  {
    sitkExceptionMacro( << "Moving image is not set. Use SetMovingImage() or run Help() to get information on how to use this module." );
  }

  itk::DataObject::Pointer fixedMask = 0;
  itk::DataObject::Pointer movingMask = 0;

  int isError = 1;
  try
  {
    isError = this->m_Elastix->RegisterImages(
      fixedImage,
      movingImage,
      this->m_ParameterMapList,
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

void
SimpleElastix
::GetResultImage( void )
{
  if( this->m_Elastix->GetResultImage().IsNotNull() )
  {
    // TODO:
    //return CastITKToImage( this->m_Elastix->GetResultImage() );
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