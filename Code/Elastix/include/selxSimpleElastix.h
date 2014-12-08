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
    void SetMovingImage( Image* movingImage );

    void SetFixedMask( Image* fixedMask );
    void SetMovingMask( Image* movingMask );
    void ClearFixedMask( void );
    void ClearMovingMask( void );

    // Register images
    Image Execute( void );

    // Get result
    Image GetResultImage( void );

    // Output
    void SetOutputFolder( const std::string folder );
    void LogToDisk( bool );
    void LogToDiskOn( void );
    void LogToDiskOff( void );
    void LogToConsole( bool );
    void LogToConsoleOn( void );
    void LogToConsoleOff( void );

    // Paramete Map interface
    void SetParameterMapList( ParameterMapListType parameterMapList );
    void SetParameterMap( ParameterMapType parameterMap );
    ParameterMapListType GetParameterMapList( void );

    void SetTransformParameterMapList( ParameterMapListType parameterMapList );
    void SetTransformParameterMap( ParameterMapType parameterMap );
    ParameterMapListType GetTransformParameterMapList( void );

    ParameterMapType ParameterFileReader( const std::string filename );

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
SELX_EXPORT Image elastix( Image fixedImage, Image movingImage, SimpleElastix::ParameterMapType parameterMap, bool logToConsole = false, bool logToDisk = false, std::string outputFolder = "" );
SELX_EXPORT Image elastix( Image fixedImage, Image movingImage, SimpleElastix::ParameterMapListType parameterMapList, bool logToConsole = false, bool logToDisk = false, std::string outputFolder = "" );
SELX_EXPORT Image elastix( Image fixedImage, Image movingImage, SimpleElastix::ParameterMapType parameterMap, Image fixedMask, Image movingMask, bool logToConsole = false, bool logToDisk = false, std::string outputFolder = "" );
SELX_EXPORT Image elastix( Image fixedImage, Image movingImage, SimpleElastix::ParameterMapListType parameterMapList, Image fixedMask, Image movingMask, bool logToConsole = false, bool logToDisk = false, std::string outputFolder = "" );
SELX_EXPORT SimpleElastix::ParameterMapType ReadParameterFile( const std::string filename );

} // end namespace simple
} // end namespace itk

// This would be the only feature depending on C++11 so we choose to avoid this dependency
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