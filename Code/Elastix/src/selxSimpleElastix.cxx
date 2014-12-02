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

  // This class holds data and configuration that is passed to elastix API when executed
  this->m_FixedMask = 0;
  this->m_MovingImage = 0;
  this->m_FixedMask = 0;
  this->m_MovingMask = 0;
  this->m_ResultImage = Image();
  this->m_ParameterMapList = ParameterMapListType();
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



void
SimpleElastix
::SetParameterMapList( ParameterMapListType parameterMapList )
{
  this->m_ParameterMapList = parameterMapList;
}



void
SimpleElastix
::SetParameterMap( ParameterMapType parameterMap )
{
  ParameterMapListType parameterMapList;
  parameterMapList.push_back( parameterMap );
  this->SetParameterMapList( parameterMapList );
}



void
SimpleElastix
::AddParameterMapList( ParameterMapListType parameterMapList )
{
  this->m_ParameterMapList.insert( this->m_ParameterMapList.end(), 
                                   parameterMapList.begin(),
                                   parameterMapList.end() );
}



void
SimpleElastix
::AddParameterMap( ParameterMapType parameterMap )
{
  ParameterMapListType parameterMapList;
  parameterMapList.push_back( parameterMap );
  this->AddParameterMapList( parameterMapList );
}



typename SimpleElastix::ParameterMapListType
SimpleElastix
::GetParameterMapList( void )
{
  return this->m_ParameterMapList;
}



typename SimpleElastix::ParameterMapType
SimpleElastix
::GetParameterMap( void )
{
  return this->m_ParameterMapList[ this->m_ParameterMapList.size()-1 ];
}



int
SimpleElastix
::GetNumberOfParameterMaps( void )
{
  return this->m_ParameterMapList.size();
}



typename SimpleElastix::ParameterMapType
SimpleElastix
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



Image
SimpleElastix
::Execute( void )
{
  const PixelIDValueEnum FixedImagePixelType = this->m_FixedImage->GetPixelID();
  const unsigned int FixedImageDimension = this->m_FixedImage->GetDimension();

  if (this->m_MemberFactory->HasMemberFunction( FixedImagePixelType, FixedImageDimension ) )
  {
    return this->m_MemberFactory->GetMemberFunction( FixedImagePixelType, FixedImageDimension )();
  }

  sitkExceptionMacro( << "SimpleElastix does not support image type \""
                      << GetPixelIDValueAsString(FixedImagePixelType) << "\" ("
                      << GetPixelIDValueAsElastixParameter(FixedImagePixelType << ")." );
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



typename SimpleElastix::ParameterMapType
SimpleElastix
::GetTransformParameterMap( void )
{
  return this->GetTransformParameterMapList()[ this->GetTransformParameterMapList().size()-1 ];
}



typename SimpleElastix::ParameterMapListType
SimpleElastix
::GetTransformParameterMapList( void )
{
  return this->GetTransformParameterMapList();
}

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
}



/**
 * Procedural interface 
 */



typename SimpleElastix::ParameterMapType
ReadParameterFile( const std::string filename )
{
  SimpleElastix elastix;
  return elastix.ReadParameterFile( filename );
}


} // end namespace simple
} // end namespace itk

#endif // __selxsimpleelastix_cxx_