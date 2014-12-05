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

    ParameterMapType ParameterFileReader( const std::string filename );
    ParameterMapType ParameterFileWriter( const std::string filename );

    unsigned int GetNumberOfParameterMaps( void );
    unsigned int GetNumberOfTransformparameterMaps( void );
    
    ParameterMapType GetDefaultRigidParameterMap( void ) {};
    ParameterMapType GetDefaultAffineParameterMap( void ) {};
    ParameterMapType GetDefaultNonRigidAffineParameterMap( void ) {};
    ParameterMapType GetDefaultGroupwiseNonRigidParameterMap( void ) {};

  protected:

    // CRUD internal interface

    void Create( ParameterMapListType parameterMapList );                                       // Create parameter map list
    void Create( ParameterMapType parameterMap );                                               // Append parameter map to list
    void Create( ParameterMapType* parameterMap, std::string key, ParameterValuesType value );  // Create parameter in nth map
    void Create( ParameterMapType* parameterMap, std::string key, std::string value );          // Create parameter in nth map (casts to vector)

    ParameterMapListType* ReadParameterMapList( void );                                         // Return pointer to parameter map list
    ParameterMapType* ReadParameterMap( unsigned int n );                                       // Return pointer to nth parameter map
    ParameterValuesType* ReadParameter( ParameterMapType* parameterMap, std::string key );      // Return pointer to parameter "key"

    void Update( ParameterMapType* parameterMap, ParameterMapType parameterMap );               // Update nth map with entries in parameterMap
    void Update( ParameterMapType* parameterMap, std::string key, ParameterValuesType value );  // Update nth map
    void Update( ParameterMapType* parameterMap, std::string key, std::string value );          // Update nth map (casts to vector)

    void Delete( void );
    void Delete( unsigned int n );
    void Delete( ParameterMapType* parameterMap, std::string key );
    void Delete( ParameterMapType* parameterMap, std::string key );

    void Put( ParameterMapListType );
    void Put( ParameterMapType );
    void Put( ParameterMapType* parameterMap, std::string key, ParameterValuesType value );
    void Put( ParameterMapType* parameterMap, std::string key, std::string value );

    // TODO: Make private
    ParameterMapListType m_ParameterMapList;
    ParameterMapListType m_TransformParameterMapList;

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