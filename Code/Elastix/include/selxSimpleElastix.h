#ifndef __selxsimpleelastix_h_
#define __selxsimpleelastix_h_

// SimpleITK
#include "sitkSimpleElastix.h"
#include "sitkPixelIDTokens.h"
#include "sitkImage.h"
#include "sitkMemberFunctionFactory.h"

// SimpleElastix
#include "elastixlib.h"

namespace itk { 
  namespace simple {

class SELX_EXPORT SimpleElastix
{
  public:

    SimpleElastix( void );
    ~SimpleElastix( void );

    typedef SimpleElastix Self;
    typedef itk::ParameterFileParser::ParameterMapType      ParameterMapType;
    typedef ParameterMapType::iterator                      ParameterMapIterator;
    typedef std::vector< ParameterMapType >                 ParameterMapListType;
    typedef ParameterMapListType::iterator                  ParameterMapListIterator;
    typedef std::string                                     ParameterKeyType;
    typedef itk::ParameterFileParser::ParameterValuesType   ParameterValuesType;
    typedef itk::ParameterFileParser                        ParameterFileParserType;
    typedef ParameterFileParserType::Pointer                ParameterFileParserPointer;
 
    // typedefs inherited from SimpleITK
    typedef BasicPixelIDTypeList PixelIDTypeList;

    // typedefs inherited from elastix library api
    typedef elastix::ELASTIX libelastix;

    /** To be wrapped by SWIG */ 

    const std::string GetName( void );

    // Images
    void SetFixedImage( Image* fixedImage );
    Image* GetFixedImage( void );

    void SetMovingImage( Image* movingImage );
    Image* GetMovingImage( void );
    
    void SetFixedMask( Image* fixedMask );
    Image* GetFixedMask( void );
    void ClearFixedMask( void );

    void SetMovingMask( Image* movingMask );
    Image* GetMovingMask( void );
    void ClearMovingMask( void );

    // Paramete Map interface (SWIG behaves better if external interface is explicitely typed out)
    void SetParameterMapList( std::vector< std::map< std::string, std::vector< std::string > > > parameterMapList );
    void SetParameterMap( std::map< std::string, std::vector< std::string > > parameterMap );
    std::vector< std::map< std::string, std::vector< std::string > > > GetParameterMapList( void );

    std::map< std::string, std::vector< std::string > > GetDefaultParameterMap( const std::string name );
    std::map< std::string, std::vector< std::string > > ParameterFileReader( const std::string filename );

    // Register images
    Image Execute( void );

    // Get result
    Image GetResultImage( void );
    std::vector< std::map< std::string, std::vector< std::string > > > GetTransformParameterMapList( void );

    // Output
    void SetOutputFolder( const std::string folder );
    void LogToDisk( bool );
    void LogToDiskOn( void );
    void LogToDiskOff( void );
    void LogToConsole( bool );
    void LogToConsoleOn( void );
    void LogToConsoleOff( void );

  private:

    template< typename TResultImage >
    Image ExecuteInternal( void );

    // Addressor of this class for member function factory
    #ifndef SWIG
      template < class TMemberFunctionPointer >
      struct SimpleElastixAddressor
      {
        typedef typename ::detail::FunctionTraits< TMemberFunctionPointer >::ClassType ObjectType;

        template< typename TResultImage >
        TMemberFunctionPointer operator() ( void ) const
        {
          return &ObjectType::template ExecuteInternal< TResultImage >;
        }
      };
    #endif

    // Functions to register SimpleElastix with SimpleITK member factory
    typedef Image ( Self::*MemberFunctionType )( void );
    std::auto_ptr< detail::MemberFunctionFactory< MemberFunctionType > > m_MemberFactory;

    // This class holds configuration and pointers to data that is passed to elastix API when run
    Image*                 m_FixedImage;
    Image*                 m_MovingImage;
    std::string            m_OutputFolder;
    bool                   m_LogToDisk;
    bool                   m_LogToConsole;
    Image*                 m_FixedMask;
    Image*                 m_MovingMask;
    Image                  m_ResultImage;
    ParameterMapListType   m_ParameterMaps;
    ParameterMapListType   m_TransformParameterMaps;

};

// Procedural Interface 
SELX_EXPORT std::map< std::string, std::vector< std::string > > GetDefaultParameterMap( const std::string filename );
SELX_EXPORT std::map< std::string, std::vector< std::string > > ReadParameterFile( const std::string filename );
SELX_EXPORT Image elastix( Image fixedImage, Image movingImage, SimpleElastix::ParameterMapType parameterMap, bool logToConsole = false, bool logToDisk = false, std::string outputFolder = "" );
SELX_EXPORT Image elastix( Image fixedImage, Image movingImage, SimpleElastix::ParameterMapListType parameterMapList, bool logToConsole = false, bool logToDisk = false, std::string outputFolder = "" );
SELX_EXPORT Image elastix( Image fixedImage, Image movingImage, SimpleElastix::ParameterMapType parameterMap, Image fixedMask, Image movingMask, bool logToConsole = false, bool logToDisk = false, std::string outputFolder = "" );
SELX_EXPORT Image elastix( Image fixedImage, Image movingImage, SimpleElastix::ParameterMapListType parameterMapList, Image fixedMask, Image movingMask, bool logToConsole = false, bool logToDisk = false, std::string outputFolder = "" );

} // end namespace simple
} // end namespace itk

namespace std
{
  template < typename T > string to_string( const T& n )
  {
    ostringstream stm;
    stm << n;
    return stm.str();
  }
}

#endif // __selxsimpleelastix_h_