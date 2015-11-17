#ifndef __sitksimpletransformix_h_
#define __sitksimpletransformix_h_

// SimpleITK
#include "sitkCommon.h"
#include "sitkMemberFunctionFactory.h"
#include "sitkImage.h"

// SimpleTransformix
#include "transformixlib.h"

namespace itk { 
  namespace simple {

class SITKCommon_EXPORT SimpleTransformix
{
  public:

    SimpleTransformix( void );
    ~SimpleTransformix( void );

    typedef SimpleTransformix Self;

    // typedefs inherited from elastix library api
    typedef transformix::TRANSFORMIX                        libtransformix;
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
    Self& SetInputImage( const Image& inputImage );
    Image& GetInputImage( void );

    // Parameter map interface 
    Self& SetTransformParameterMap( std::vector< std::map< std::string, std::vector< std::string > > > parameterMapList );
    Self& SetTransformParameterMap( std::map< std::string, std::vector< std::string > > parameterMap );
    std::map< std::string, std::vector< std::string > > ReadParameterFile( const std::string filename );
    Self& WriteParameterFile( std::map< std::string, std::vector< std::string > > const parameterMap, const std::string filename );
    Self& PrettyPrint( void );
    Self& PrettyPrint( std::map< std::string, std::vector< std::string > > const parameterMap );
    Self& PrettyPrint( std::vector< std::map< std::string, std::vector< std::string > > > const parameterMapList );

    // Warp images
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
      struct SimpleTransformixAddressor
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

    // This class holds configuration and pointers to data that is passed to transformix API when run
    Image                  m_InputImage;
    Image                  m_ResultImage;
    std::string            m_OutputFolder;
    bool                   m_LogToConsole;
    ParameterMapListType   m_TransformParameterMaps;

};

// Procedural Interface 
SITKCommon_EXPORT Image Transformix( const Image& inputImage, const std::map< std::string, std::vector< std::string > > parameterMap, const bool logToConsole = false, const std::string outputFolder = "" );
SITKCommon_EXPORT Image Transformix( const Image& inputImage, const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapList, const bool logToConsole = false, const std::string outputFolder = "" );

} // end namespace simple
} // end namespace itk

#endif // __sitksimpletransformix_h_