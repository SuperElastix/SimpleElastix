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

  // This class holds image data that is passed to elastix API when executed
  this->m_FixedMask = 0;
  this->m_MovingImage = 0;
  this->m_FixedMask = 0;
  this->m_MovingMask = 0;
  this->m_ResultImage = Image();
  this->m_LogFileName = "output_path_not_set";
  this->m_LogToConsole = false;
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
::SetMovingMask()
{
  this->m_MovingMask = movingMask;
}



void
SimpleElastix
::DeleteFixedMask( void )
{
  this->m_FixedMask = 0;
}



void
SimpleElastix
::DeleteMovingMask( void )
{
  this->m_MovingMask = 0;
}



void
SimpleElastix
::SetParameterMapList( ParameterMapListType parameterMapList )
{
  this->Put( parameterMapList );
}



void
SimpleElastix
::SetParameterMap( ParameterMapType parameterMap )
{
  this->Put( parameterMap );
}



void
SimpleElastix
::AddParameterMapList( ParameterMapListType parameterMapList )
{
  this->Create( parameterMapList );
}



void
SimpleElastix
::AddParameterMap( ParameterMapType parameterMap )
{
  this->Create( parameterMap );
}



SimpleElastix::ParameterMapListType
SimpleElastix
::GetParameterMapList( void )
{
  return this->ReadParameterMapList();
}



SimpleElastix::ParameterMapType
SimpleElastix
::GetParameterMap( unsigned int n )
{
  return this->ReadParameterMap( n );
}



SimpleElastix::ParameterMapType
SimpleElastix
::GetParameterMap( void )
{
  return this->ReadParameterMap( this->GetNumberOfParameterMaps()-1 );
}



void
SimpleElastix
::DeleteParameterMapList( void )
{
    this->Delete();
}



void
SimpleElastix
::DeleteParameterMap( unsigned int n )
{
    this->Delete( this->ReadParameterMapList(), n );
}



void
SimpleElastix
::DeleteParameterMap( void )
{
    this->DeleteParameterMap( this->GetNumberOfParameterMaps()-1 );
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

  sitkExceptionMacro( << "SimpleElastix does not support image type \""
                      << GetPixelIDValueAsString( FixedImagePixelEnum ) << "\" ("
                      << GetPixelIDValueAsElastixParameter( FixedImagePixelEnum ) << ")." );
}



Image 
SimpleElastix
::GetResultImage( void )
{
  return this->m_ResultImage;
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
::SetLogFileName( const std::string filename )
{
  this->m_LogFileName = filename;
}



/**
 * Procedural interface 
 */



Image
elastix( Image fixedImage, Image movingImage, ParameterMapInterface::ParameterMapType parameterMap, bool logToConsole, bool outputToFolder, std::string logFileName )
{
  ParameterMapInterface::ParameterMapListType parameterMapList;
  parameterMapList.push_back( parameterMap );
  return elastix( fixedImage, movingImage, parameterMapList, logToConsole, logFileName );
}


Image
elastix( Image fixedImage, Image movingImage, ParameterMapInterface::ParameterMapListType parameterMapList, bool logToConsole, bool outputToFolder, std::string logFileName )
{
  SimpleElastix selx;
  selx.SetFixedImage( &fixedImage );
  selx.SetMovingImage( &movingImage );
  selx.SetParameterMapList( parameterMapList );

  if( logToConsole )
  {
    selx.LogToConsoleOn();
  }

  if( outputToFolder )
  {
    selx.OutoutToFolderOn();
  }

  if( logFileName != "" )
  {
     selx.SetLogFileName( logFileName );
  }

  return selx.Execute();



Image
elastix( Image fixedImage, Image movingImage, ParameterMapInterface::ParameterMapType parameterMap, Image fixedMask, Image movingMask, bool logToConsole, bool outputToFolder, std::string logFileName )
{
  ParameterMapInterface::ParameterMapListType parameterMapList;
  parameterMapList.push_back( parameterMap );
  return elastix( fixedImage, movingImage, parameterMapList, fixedMask, movingMask, logToConsole, logFileName );
}



Image
elastix( Image fixedImage, Image movingImage, ParameterMapInterface::ParameterMapListType parameterMapList, Image fixedMask, Image movingMask, bool logToConsole, bool outputToFolder, std::string logFileName )
{
  SimpleElastix selx;
  selx.SetFixedImage( &fixedImage );
  selx.SetMovingImage( &movingImage );
  selx.SetParameterMapList( parameterMapList );
  selx.SetFixedMask( &fixedMask );
  selx.SetMovingMask( &movingMask );

  if( logToConsole )
  {
    selx.LogToConsoleOn();
  }

  if( outputToFolder )
  {
    selx.OutoutToFolderOn();
  }

  if( logFileName != "" )
  {
     selx.SetLogFileName( logFileName );
  }

  return selx.Execute();
}



} // end namespace simple
} // end namespace itk

#endif // __selxsimpleelastix_cxx_