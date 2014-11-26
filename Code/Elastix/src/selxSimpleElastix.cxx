#ifndef __selxsimpleelastix_cxx_
#define __selxsimpleelastix_cxx_

#include "selxSimpleElastix.h"


namespace itk {
  namespace simple {



SimpleElastix
::SimpleElastix( void )
{
  // Register this class with SimpleITK
  //m_DualMemberFactory.reset( new detail::DualMemberFunctionFactory< MemberFunctionType >( this ) );
  //m_DualMemberFactory->RegisterMemberFunctions< PixelIDTypeList, PixelIDTypeList, 3, SimpleElastixAddressor< MemberFunctionType > >();
  //m_DualMemberFactory->RegisterMemberFunctions< PixelIDTypeList, PixelIDTypeList, 2, SimpleElastixAddressor< MemberFunctionType > >();

  // This class holds data and configuration that is passed to elastix API when executed
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
::GetParameterMap( int n )
{
  return this->m_ParameterMapList[ n ];
}



typename SimpleElastix::ParameterMapType
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



typename SimpleElastix::ParameterMapType
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


/*
Image
SimpleElastix
::Execute( void )
{

  const PixelIDValueEnum FixedImagePixelType = this->m_FixedImage->GetPixelID();
  const unsigned int FixedImageDimension = this->m_FixedImage->GetDimension();
  const PixelIDValueEnum MovingImagePixelType = this->m_FixedImage->GetPixelID();

  if (this->m_DualMemberFactory->HasMemberFunction( FixedImagePixelType, MovingImagePixelType,  FixedImageDimension ) )
  {
    return this->m_DualMemberFactory->GetMemberFunction(
      FixedImagePixelType, 
      MovingImagePixelType, 
      FixedImageDimension
    )
    ( 
      this->m_FixedImage, 
    );
  }

  sitkExceptionMacro( << "SimpleElastix does not support the combination of fixed image type \""
                      << itk::simple::GetPixelIDValueAsString (FixedImagePixelType) << "\" and moving image type \""
                      << itk::simple::GetPixelIDValueAsString (MovingImagePixelType) << "\"." );

}
*/


Image*
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



typename SimpleElastix::ParameterMapType
SimpleElastix
::GetTransformParameterMap( void )
{
  return this->m_Elastix->GetTransformParameterMap();
}



typename SimpleElastix::ParameterMapListType
SimpleElastix
::GetTransformParameterMapList( void )
{
  return this->m_Elastix->GetTransformParameterMapList();
}

/** Procedural interface */
/*

typename ::ParameterMapType
ReadParameterFile( const std::string filename )
{
   elastix;
  return elastix.ReadParameterFile( filename );
}
*/

} // end namespace simple
} // end namespace itk

#endif // __selxsimpleelastix_cxx_