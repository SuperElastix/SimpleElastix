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
::SetMovingMask( Image* movingMask )
{
  this->m_MovingMask = movingMask;
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
::LogFileName( const std::string filename )
{
  this->m_LogFileName = filename;
}



typename ParameterMapInterface::ParameterMapListType
SimpleElastix
::GetParameterMapList( void )
{
  return this->ReadParameterMapList();
}



typename ParameterMapInterface::ParameterMapType
ParameterMapInterface
::GetParameterMap( void )
{
  return this->ReadParameterMap();
}



/*
void
SimpleElastix
::Put(ParameterMapType* parameterMap, ParameterKeyType key, const std::string value)
{
  ParameterValuesType parameterValue;
  parameterValue.push_back( value );
  std::pair< ParameterKeyType, ParameterValuesType > parameter = std::make_pair< ParameterKeyType, ParameterValuesType >( key, parameterValue );
  std::pair< ParameterMapIterator, bool > result;
  result = parameterMap->insert( parameter );
  if( !result.second )
  {
    result.first->second = parameterValue;
  }
}*/



/**
 * Procedural interface 
 */


} // end namespace simple
} // end namespace itk

#endif // __selxsimpleelastix_cxx_