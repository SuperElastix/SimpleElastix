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
 
    // typedefs inherited from SimpleITK
    typedef BasicPixelIDTypeList PixelIDTypeList;

    // typedefs inherited from elastix library api
    typedef elastix::ELASTIX                                libelastix;
    typedef itk::ParameterFileParser::ParameterMapType      ParameterMapType;
    typedef ParameterMapType::iterator                      ParameterMapIterator;
    typedef ParameterMapType::const_iterator                ParameterMapConstIterator;
    typedef std::vector< ParameterMapType >                 ParameterMapListType;
    typedef ParameterMapListType::iterator                  ParameterMapListIterator;
    typedef ParameterMapListType::const_iterator            ParameterMapListonstIterator;
    typedef std::string                                     ParameterKeyType;
    typedef itk::ParameterFileParser::ParameterValuesType   ParameterValuesType;
    typedef itk::ParameterFileParser                        ParameterFileParserType;
    typedef ParameterFileParserType::Pointer                ParameterFileParserPointer;

    /** To be wrapped by SWIG */ 

    const std::string GetName( void );

    // Images
    void SetFixedImage( const Image& fixedImage );
    Image GetFixedImage( void );

    void SetMovingImage( const Image& movingImage );
    Image GetMovingImage( void );
    
    void SetFixedMask( const Image& fixedMask );
    Image GetFixedMask( void );
    void DeleteFixedMask( void );

    void SetMovingMask( const Image& movingMask );
    Image GetMovingMask( void );
    void DeleteMovingMask( void );

    // Paramete Map interface (SWIG behaves better if external interface is explicitely typed out)
    void SetParameterMapList( std::vector< std::map< std::string, std::vector< std::string > > > const parameterMapList );
    void SetParameterMap( std::map< std::string, std::vector< std::string > > const parameterMap );
    std::vector< std::map< std::string, std::vector< std::string > > > GetParameterMapList( void );
    std::map< std::string, std::vector< std::string > > ParameterFileReader( const std::string filename );
    std::map< std::string, std::vector< std::string > > GetDefaultParameterMap( const std::string name );
    void PrettyPrint( std::map< std::string, std::vector< std::string > > const parameterMap );
    void PrettyPrint( std::vector< std::map< std::string, std::vector< std::string > > > const parameterMapList );

    // Register images
    Image Execute( void );

    // Get result
    Image GetResultImage( void );
    std::vector< std::map< std::string, std::vector< std::string > > > GetTransformParameterMapList( void );

    // Output
    void LogToFolder( const std::string folder );
    void LogToFolderOff( void );
    void LogToConsole( bool );
    void LogToConsoleOn( void );
    void LogToConsoleOff( void );

  private:

    bool isEmpty( const Image& image );

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

    // This class holds data that is passed to elastix API when run
    Image                  m_FixedImage;
    Image                  m_MovingImage;
    ParameterMapListType   m_ParameterMaps;
    std::string            m_OutputFolder;
    bool                   m_LogToConsole;
    Image                  m_FixedMask;
    Image                  m_MovingMask;
    Image                  m_ResultImage;
    ParameterMapListType   m_TransformParameterMaps;

};

// Procedural Interface 
SELX_EXPORT std::map< std::string, std::vector< std::string > > GetDefaultParameterMap( const std::string filename );
SELX_EXPORT std::map< std::string, std::vector< std::string > > ReadParameterFile( const std::string filename );
SELX_EXPORT Image elastix( const Image& fixedImage, const Image& movingImage, const std::string defaultParameterMapName);
SELX_EXPORT Image elastix( const Image& fixedImage, const Image& movingImage, const std::map< std::string, std::vector< std::string > > parameterMap);
SELX_EXPORT Image elastix( const Image& fixedImage, const Image& movingImage, const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapList);
SELX_EXPORT Image elastix( const Image& fixedImage, const Image& movingImage, const std::string defaultParameterMapName, const Image& fixedMask, const Image& movingMask);
SELX_EXPORT Image elastix( const Image& fixedImage, const Image& movingImage, const std::map< std::string, std::vector< std::string > > parameterMap, const Image& fixedMask, const Image& movingMask);
SELX_EXPORT Image elastix( const Image& fixedImage, const Image& movingImage, const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapList, const Image& fixedMask, const Image& movingMask);
SELX_EXPORT Image elastix( const Image& fixedImage, const Image& movingImage, const std::string defaultParameterMapName, const bool logToConsole, const std::string outputFolder );
SELX_EXPORT Image elastix( const Image& fixedImage, const Image& movingImage, const std::map< std::string, std::vector< std::string > > parameterMap, const bool logToConsole, const std::string outputFolder );
SELX_EXPORT Image elastix( const Image& fixedImage, const Image& movingImage, const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapList, const bool logToConsole, const std::string outputFolder );
SELX_EXPORT Image elastix( const Image& fixedImage, const Image& movingImage, const std::string defaultParameterMapName, const Image& fixedMask, const Image& movingMask, const bool logToConsole, const std::string outputFolder );
SELX_EXPORT Image elastix( const Image& fixedImage, const Image& movingImage, const std::map< std::string, std::vector< std::string > >, const Image& fixedMask, const Image& movingMask, const bool logToConsole, const std::string outputFolder );
SELX_EXPORT Image elastix( const Image& fixedImage, const Image& movingImage, const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapList, const Image& fixedMask, const Image& movingMask, const bool logToConsole, const std::string outputFolder );

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