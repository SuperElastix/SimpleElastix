#ifndef __selxparametermapinterface_h_
#define __selxparametermapinterface_h_

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

    ParameterMapListType& GetParameterMapList( void );
    ParameterMapType GetParameterMap( void );

    void DeleteParameterMapList( void );
    void DeleteParameterMap( void );

  protected:

    int GetNumberOfParameterMaps( void );
    ParameterMapType ReadParameterFile( const std::string filename );

    void Create( ParameterMapListType parameterMapList );
    void Create( ParameterMapType parameterMap );
    void Create( unsigned int n, std::string key, ParameterValuesType value );
    void Create( std::string key, ParameterValuesType value );
    void Create( unsigned int n, std::string key, std::string value );
    void Create( std::string key, std::string value );

    ParameterMapListType ReadParameterMapList( void );
    ParameterMapType ReadParameterMap( void );
    std::string ReadParameter( std::string key );
    std::string ReadParameter( unsigned int n, std::string key );

    void Update( unsigned int n, ParameterMapType parameterMap );
    void Update( ParameterMapType parameterMap );
    void Update( unsigned int n, ParameterValuesType value );
    void Update( ParameterValuesType value );
    void Update( unsigned int n, std::string key, std::string value );
    void Update( std::string key, std::string value );

    void Delete( void );
    void Delete( unsigned int n, std::string key );
    void Delete( std::string key );

    void Put( ParameterMapListType );
    void Put( ParameterMapType );
    void Put( unsigned int n, std::string key, ParameterValuesType value );
    void Put( std::string key, ParameterValuesType value );
    void Put( unsigned int n, std::string key, std::string value );
    void Put( std::string key, std::string value );

    // TODO: pass to elastix api via getter
    ParameterMapListType m_ParameterMapList;

};

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