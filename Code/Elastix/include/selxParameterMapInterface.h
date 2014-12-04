#ifndef __selxparametermapinterface_h_
#define __selxparametermapinterface_h_

// SimpleITK
#include "sitkSimpleElastix.h"

// SimpleElastix
#include "elastixlib.h"

namespace itk {
  namespace simple {

class ParameterMapInterface
{
  public:

    typedef ParameterMapInterface Self;
    ParameterMapInterface( void );
    ~ParameterMapInterface( void );

    // typedefs inherited from elastix library api
    typedef itk::ParameterFileParser::ParameterMapType      ParameterMapType;
    typedef ParameterMapType::iterator                      ParameterMapIterator;
    typedef std::vector< ParameterMapType >                 ParameterMapListType;
    typedef ParameterMapListType::iterator                  ParameterMapListIterator;
    typedef std::string                                     ParameterKeyType;
    typedef itk::ParameterFileParser::ParameterValuesType   ParameterValuesType;
    typedef itk::ParameterFileParser                        ParameterFileParserType;
    typedef ParameterFileParserType::Pointer                ParameterFileParserPointer;

    void SetParameterMapList( ParameterMapListType parameterMapList );
    void SetParameterMap( ParameterMapType parameterMap );

    void AddParameterMapList( ParameterMapListType parameterMapList );
    void AddParameterMap( ParameterMapType parameterMap );

    ParameterMapListType GetParameterMapList( void );
    ParameterMapType GetParameterMap( unsigned int n );
    ParameterMapType GetParameterMap( void );

    void DeleteParameterMapList( void );
    void DeleteParameterMap( unsigned int n );
    void DeleteParameterMap( void );

    ParameterMapType ParameterFileReader( const std::string filename );
    unsigned int GetNumberOfParameterMaps( void );
    
/*
    ParameterMapType GetDefaultRigidParameterMap( void );
    ParameterMapType GetDefaultAffineParameterMap( void );
    ParameterMapType GetDefaultNonRigidAffineParameterMap( void );
    ParameterMapType GetDefaultGroupwiseNonRigidParameterMap( void );
*/

  protected:

    

    // CRUD internal interface

    void Create( ParameterMapListType parameterMapList );                       // Create parameter map list
    void Create( ParameterMapType parameterMap );                               // Append parameter map to list
    void Create( unsigned int n, std::string key, ParameterValuesType value );  // Create parameter in nth map
    void Create( std::string key, ParameterValuesType value );                  // Create parameter in all maps
    void Create( unsigned int n, std::string key, std::string value );          // Create parameter in nth map (casts to vector)
    void Create( std::string key, std::string value );                          // Create parameter in all maps (casts to vector)

    ParameterMapListType ReadParameterMapList( void );                          // Return parameter map list
    ParameterMapType ReadParameterMap( unsigned int n );                        // Return nth parameter map
    ParameterValuesType ReadParameter( unsigned int n, std::string key );       // Return parameter "key" in nth map
    ParameterValuesType ReadParameter( std::string key );                       // Return parameter "key" in last map

    void Update( unsigned int n, ParameterMapType parameterMap );               // Update nth map with entries in parameterMap
    void Update( ParameterMapType parameterMap );                               // Update all map with entries in parameterMap
    void Update( unsigned int n, std::string key, ParameterValuesType value );  // Update nth map
    void Update( std::string key, ParameterValuesType value );                  // Update all maps
    void Update( unsigned int n, std::string key, std::string value );          // Update nth map (casts to vector)
    void Update( std::string key, std::string value );                          // Update all maps (casts to vector)

    void Delete( void );
    void Delete( unsigned int n );
    void Delete( unsigned int n, std::string key );
    void Delete( std::string key );

    void Put( ParameterMapListType );
    void Put( ParameterMapType );
    void Put( unsigned int n, std::string key, ParameterValuesType value );
    void Put( std::string key, ParameterValuesType value );
    void Put( unsigned int n, std::string key, std::string value );
    void Put( std::string key, std::string value );

    // TODO: Make private
    ParameterMapListType m_ParameterMapList;

};

SELX_EXPORT typename ParameterMapInterface::ParameterMapType ReadParameterFile( const std::string filename );

} // end namespace simple
} // end namespace itk

// Avoid dependency on c++0x and above
namespace std
{
  template < typename T > std::string to_string( const T& n )
  {
    std::ostringstream stm;
    stm << n;
    return stm.str();
  }
}

#endif // __selxsimpleelastix_h_