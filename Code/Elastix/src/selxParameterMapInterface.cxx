#ifndef __selxparametermapinterface_cxx_
#define __selxparametermapinterface_cxx_

#include "SimpleITK.h"
#include "selxParameterMapInterface.h"

namespace itk {
  namespace simple {



ParameterMapInterface
::ParameterMapInterface( void )
{
    // This class holds image data that is passed to elastix API when executed
    this->m_ParameterMapList = ParameterMapListType();
}



ParameterMapInterface
::~ParameterMapInterface( void )
{
}



/**
 * Elastix-style external interface
 */



void
ParameterMapInterface
::SetParameterMapList( ParameterMapListType parameterMapList )
{
  this->Put( parameterMapList );
}



void
ParameterMapInterface
::SetParameterMap( ParameterMapType parameterMap )
{
  this->Put( parameterMap );
}



void
ParameterMapInterface
::AddParameterMapList( ParameterMapListType parameterMapList )
{
  this->Create( parameterMapList );
}



void
ParameterMapInterface
::AddParameterMap( ParameterMapType parameterMap )
{
  this->Create( parameterMap );
}



ParameterMapInterface::ParameterMapListType
ParameterMapInterface
::GetParameterMapList( void )
{
  return this->ReadParameterMapList();
}



ParameterMapInterface::ParameterMapType
ParameterMapInterface
::GetParameterMap( unsigned int n )
{
  return this->ReadParameterMap( n );
}



ParameterMapInterface::ParameterMapType
ParameterMapInterface
::GetParameterMap( void )
{
  return this->ReadParameterMap( this->GetNumberOfParameterMaps()-1 );
}



void
ParameterMapInterface
::DeleteParameterMapList( void )
{
    this->Delete();
}



void
ParameterMapInterface
::DeleteParameterMap( unsigned int n )
{
    this->Delete( n );
}



void
ParameterMapInterface
::DeleteParameterMap( void )
{
    this->DeleteParameterMap( this->GetNumberOfParameterMaps()-1 );
}



unsigned int
ParameterMapInterface
::GetNumberOfParameterMaps( void )
{
  return this->ReadParameterMapList().size();
}



ParameterMapInterface::ParameterMapType
ParameterMapInterface
::ParameterFileReader( const std::string filename )
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



/**
 * CRUD-style internal interface 
 */



void 
ParameterMapInterface
::Create( ParameterMapListType parameterMapList )
{
    this->ReadParameterMapList().insert( this->ReadParameterMapList().end(), 
                                         parameterMapList.begin(), 
                                         parameterMapList.end() );
}



void
ParameterMapInterface
::Create( ParameterMapType parameterMap )
{
    ParameterMapListType parameterMapList;
    parameterMapList.push_back( parameterMap );
    this->Create( parameterMapList );
}



void
ParameterMapInterface
::Create( std::string key, ParameterValuesType value )
{
    for( unsigned int i = 0; i < this->ReadParameterMapList().size(); ++i )
    {
        this->Create( i, key, value );
    }
}



void
ParameterMapInterface
::Create( unsigned int n, std::string key, ParameterValuesType value )
{
    std::pair< ParameterMapIterator, bool > isError;
    isError = this->ReadParameterMap( n ).insert( std::make_pair( key, value ) );
    if( !isError.second ) 
    {
        sitkExceptionMacro( << "Error creating parameter: Parameter already exists." );
    }
}



void
ParameterMapInterface
::Create( unsigned int n, std::string key, std::string value )
{
    ParameterValuesType vectorValue;
    vectorValue.push_back( value );
    this->Create( n, key, vectorValue );
}



void
ParameterMapInterface
::Create( std::string key, std::string value )
{
    ParameterValuesType vectorValue;
    vectorValue.push_back( value );
    this->Create( key, vectorValue );
}



typename ParameterMapInterface::ParameterMapListType
ParameterMapInterface
::ReadParameterMapList( void )
{
    return this->m_ParameterMapList;
}



typename ParameterMapInterface::ParameterMapType
ParameterMapInterface
::ReadParameterMap( unsigned int n )
{
    if( !(this->m_ParameterMapList.size() < n) )
    {
        sitkExceptionMacro( << "Error: Parameter map id exceeds number of parameter maps in list." );
    }
    return this->m_ParameterMapList[ n ];
}



typename ParameterMapInterface::ParameterValuesType
ParameterMapInterface
::ReadParameter( unsigned int n, std::string key )
{
    if( !(this->ReadParameterMapList().size() < n) )
    {
        sitkExceptionMacro( << "Error: Parameter map id exceeds number of parameter maps in list." );
    }
    return this->ReadParameterMap( n )[ key ];
}



typename ParameterMapInterface::ParameterValuesType
ParameterMapInterface
::ReadParameter( std::string key )
{
    return this->ReadParameterMap( this->GetNumberOfParameterMaps()-1 )[ key ];
}



void 
ParameterMapInterface
::Update( unsigned int n, ParameterMapType parameterMap )
{
    if( !(this->GetNumberOfParameterMaps() < n) )
    {
        sitkExceptionMacro( << "Error: Parameter map id exceeds number of parameter maps in list." );
    }

    ParameterMapIterator iterator = parameterMap.begin();
    ParameterMapIterator iteratorEnd = parameterMap.end();
    while( iterator != iteratorEnd )
    {
        ParameterMapIterator pos = this->ReadParameterMap( n ).find( iterator->first );
        if( pos != iteratorEnd )
        {
            this->ReadParameterMap( n )[ iterator->first ] = iterator->second;
        }
        else
        {
            sitkExceptionMacro( << "Error updating parameter: \"" << iterator->first << "\" does not exist in parameter map " << n << "." );
        }
        
    }
}



void 
ParameterMapInterface
::Update( ParameterMapType parameterMap )
{
    for( unsigned int i = 0; this->ReadParameterMapList().size(); ++i )
    {
        this->Update( i, parameterMap );
    }
}



void
ParameterMapInterface
::Update( unsigned int n, std::string key, ParameterValuesType value )
{
    ParameterMapType parameterMap;
    parameterMap.insert( std::make_pair( key, value ) );
    this->Update( n, parameterMap );
}



void
ParameterMapInterface
::Update( std::string key, ParameterValuesType value )
{
    ParameterMapType parameterMap;
    parameterMap.insert( std::make_pair( key, value )  );

    for( unsigned int i = 0; this->ReadParameterMapList().size(); ++i )
    {
        this->Update( i, parameterMap );
    }
}



void
ParameterMapInterface
::Update( unsigned int n, std::string key, std::string value )
{
    ParameterValuesType vectorValue;
    vectorValue.push_back( value );
    this->Update( n, key, vectorValue );
}



void
ParameterMapInterface
::Update( std::string key, std::string value )
{
    ParameterValuesType vectorValue;
    vectorValue.push_back( value );
    this->Update( key, vectorValue );
}



void 
ParameterMapInterface
::Delete( void )
{
    this->ReadParameterMapList().clear();
}



void 
ParameterMapInterface
::Delete( unsigned int n )
{
    if( !(this->GetNumberOfParameterMaps() < n) )
    {
        sitkExceptionMacro( << "Error: Parameter map id exceeds number of parameter maps in list." );
    }
    this->ReadParameterMapList().erase( this->ReadParameterMapList().begin()+n );
}



void 
ParameterMapInterface
::Delete( unsigned int n, std::string key )
{
    this->ReadParameterMap( n ).erase( key );
}



void 
ParameterMapInterface
::Delete( std::string key )
{
    for( unsigned int i = 0; i < this->ReadParameterMapList().size(); ++i )
    {
        this->Delete( i, key );
    }
}



void 
ParameterMapInterface
::Put( ParameterMapListType parameterMapList )
{
    this->Delete();
    this->Create( parameterMapList );
}



void 
ParameterMapInterface
::Put( ParameterMapType parameterMap)
{
    this->Delete();
    this->Create( parameterMap );
}



void
ParameterMapInterface
::Put( unsigned int n, std::string key, ParameterValuesType value )
{
    this->Delete( n, key );
    this->Create( n, key, value );
}



void
ParameterMapInterface
::Put( std::string key, ParameterValuesType value )
{
    for( unsigned int i = 0; i < this->ReadParameterMapList().size(); ++i )
    {
        this->Put( i, key, value );
    }
}



void
ParameterMapInterface
::Put( unsigned int n, std::string key, std::string value )
{
    this->Delete( n, key );
    this->Create( n, key, value );
}



void
ParameterMapInterface
::Put( std::string key, std::string value )
{
    for( unsigned int i = 0; i < this->ReadParameterMapList().size(); ++i )
    {
        this->Put( i, key, value );
    }
}



/**
 * Procedural interface 
 */



typename ParameterMapInterface::ParameterMapType
ReadParameterFile( const std::string filename )
{
  ParameterMapInterface parameterMapInterface;
  return parameterMapInterface.ParameterFileReader( filename );
}



} // end namespace simple
} // end namespace itk

#endif // __selxsimpleelastix_h_