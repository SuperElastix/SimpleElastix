#ifndef __sitksimpleelastix_h_
#define __sitksimpleelastix_h_

// SimpleITK
#include "sitkCommon.h"
#include "sitkMemberFunctionFactory.h"
#include "sitkImage.h"

// SimpleElastix
#include "elastixlib.h"

namespace itk { 
  namespace simple {

class SITKCommon_EXPORT SimpleElastix
{
  public:

    SimpleElastix( void );
    ~SimpleElastix( void );

    typedef SimpleElastix Self;

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
    Self& SetFixedImage( const Image& fixedImage );
    Image& GetFixedImage( void );

    Self& SetMovingImage( const Image& movingImage );
    Image& GetMovingImage( void );
    
    Self& SetFixedMask( const Image& fixedMask );
    Image& GetFixedMask( void );
    Self& DeleteFixedMask( void );

    Self& SetMovingMask( const Image& movingMask );
    Image& GetMovingMask( void );
    Self& DeleteMovingMask( void );

    // Parameter Map interface
    Self& SetParameterMap( std::vector< std::map< std::string, std::vector< std::string > > > const parameterMapList );
    Self& SetParameterMap( std::map< std::string, std::vector< std::string > > const parameterMap );
    std::vector< std::map< std::string, std::vector< std::string > > > GetParameterMap( void );
    std::map< std::string, std::vector< std::string > > GetDefaultParameterMap( const std::string name, const unsigned int numberOfResolutions = 4, const double finalGridSpacingInPhysicalUnits = 8.0 );
    std::map< std::string, std::vector< std::string > > ReadParameterFile( const std::string filename );
    Self& WriteParameterFile( std::map< std::string, std::vector< std::string > > const parameterMap, const std::string filename );
    Self& PrettyPrint( void );
    Self& PrettyPrint( std::map< std::string, std::vector< std::string > > const parameterMap );
    Self& PrettyPrint( std::vector< std::map< std::string, std::vector< std::string > > > const parameterMapList );

    // Register images
    Image Execute( void );

    // Get result
    Image& GetResultImage( void );
    std::vector< std::map< std::string, std::vector< std::string > > > GetTransformParameterMap( void );

    // Output
    Self& LogToFolder( const std::string folder );
    Self& LogToFolderOff( void );
    Self& LogToConsole( bool );
    Self& LogToConsoleOn( void ) { return this->LogToConsole( true ); }
    Self& LogToConsoleOff( void ) { return this->LogToConsole( false ); }

  private:

    bool IsEmpty( const Image& image );

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
SITKCommon_EXPORT std::map< std::string, std::vector< std::string > > GetDefaultParameterMap( const std::string transform, const unsigned int numberOfResolutions = 4, const double finalGridSpacingInPhysicalUnits = 8.0 );
SITKCommon_EXPORT std::map< std::string, std::vector< std::string > > ReadParameterFile( const std::string filename );
SITKCommon_EXPORT void WriteParameterFile( const std::map< std::string, std::vector< std::string > > parameterMap, const std::string filename );
SITKCommon_EXPORT void PrettyPrint( const std::map< std::string, std::vector< std::string > > parameterMap );
SITKCommon_EXPORT void PrettyPrint( const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapList );
SITKCommon_EXPORT Image Elastix( const Image& fixedImage, const Image& movingImage, const std::string defaultParameterMapName, const bool logToConsole = false, const std::string outputFolder = "" );
SITKCommon_EXPORT Image Elastix( const Image& fixedImage, const Image& movingImage, const std::map< std::string, std::vector< std::string > > parameterMap, const bool logToConsole = false, const std::string outputFolder = "" );
SITKCommon_EXPORT Image Elastix( const Image& fixedImage, const Image& movingImage, const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapList, const bool logToConsole = false, const std::string outputFolder = "" );
SITKCommon_EXPORT Image Elastix( const Image& fixedImage, const Image& movingImage, const std::string defaultParameterMapName, const Image& fixedMask, const Image& movingMask, const bool logToConsole = false, const std::string outputFolder = "" );
SITKCommon_EXPORT Image Elastix( const Image& fixedImage, const Image& movingImage, const std::map< std::string, std::vector< std::string > >, const Image& fixedMask, const Image& movingMask, const bool logToConsole = false, const std::string outputFolder = "" );
SITKCommon_EXPORT Image Elastix( const Image& fixedImage, const Image& movingImage, std::vector< std::map< std::string, std::vector< std::string > > > parameterMapList, const Image& fixedMask, const Image& movingMask, const bool logToConsole = false, const std::string outputFolder = "" );

template < typename T > std::string to_string( const T& n )
{
  std::ostringstream stm;
  stm << n;
  return stm.str();
}

} // end namespace simple
} // end namespace itk

#endif // __sitksimpleelastix_h_