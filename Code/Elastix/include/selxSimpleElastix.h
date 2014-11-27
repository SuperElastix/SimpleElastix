#ifndef __selxsimpleelastix_h_
#define __selxsimpleelastix_h_

// SimpleITK
#include "sitkImage.h"
#include "sitkPixelIDTokens.h"
#include "sitkDualMemberFunctionFactory.h"
#include "sitkSimpleElastix.h"

// SimpleElastix
#include "elastixlib.h"

namespace itk {
  namespace simple {

class SELX_EXPORT SimpleElastix
{
  public:

    typedef SimpleElastix Self;
    SimpleElastix( void );
    ~SimpleElastix( void );

    // Define the pixels types supported by this filter
    typedef BasicPixelIDTypeList  PixelIDTypeList;

    // typedefs inherited from elastix library api
    typedef elastix::ELASTIX                      ElastixLibType;
    typedef ElastixLibType::ParameterMapType      ParameterMapType;
    typedef ElastixLibType::ParameterMapListType  ParameterMapListType;
    typedef itk::ParameterFileParser              ParameterFileParserType;
    typedef ParameterFileParserType::Pointer      ParameterFileParserPointer;

    // To be wrapped by SWIG

    const std::string GetName( void );

    // Images
    void SetFixedImage( Image* fixedImage );
    void SetMovingImage( Image* movingImage );
    void SetFixedMask( Image* fixedMask );
    void SetMovingMask( Image* movingMask );

    // Parameter Maps
    void SetParameterMapList( ParameterMapListType parameterMapList );
    void SetParameterMap( ParameterMapType parameterMap );
    void AddParameterMapList( ParameterMapListType parameterMapList );
    void AddParameterMap( ParameterMapType parameterMap );
    ParameterMapListType GetParameterMapList( void );
    ParameterMapType GetParameterMap( void );
    int GetNumberOfParameterMaps( void );
    ParameterMapType ReadParameterFile( const std::string filename );

    // Register images
    Image Execute( void );

    // Get resultpyh
    ParameterMapType GetTransformParameterMap( void );
    ParameterMapListType GetTransformParameterMapList( void );

    // Logging
    void LogToConsoleOn( void );
    void LogToConsoleOff( void );
    void LogFileName( const std::string filename ); 
 
  private:

    template< class TImageType >
    static typename TImageType::Pointer CastImageToITK( Image* image )
    {
      typename TImageType::Pointer itkImage = dynamic_cast< TImageType* >( image->GetITKBase() );
 
      if ( itkImage.IsNull() )
      {
        sitkExceptionMacro( "Error casting image to internal type." );
      }

      return itkImage;
    }

    template< class TImageType >
    static Image CastITKToImage( TImageType* itkImage )
    {
      return Image( itkImage );
    }

    template< typename TFixedImage, typename TMovingImage >
    Image ExecuteInternal( const Image* fixedImage );

    // An addressor of this class to be utilized with registering member functions with the factory.
    #ifndef SWIG
      template < class TMemberFunctionPointer >
      struct SimpleElastixAddressor
      {
        typedef typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType ObjectType;

        template< typename TFixedImage, typename TMovingImage >
        TMemberFunctionPointer operator() ( void ) const
        {
          return &ObjectType::template ExecuteInternal< TFixedImage, TMovingImage >;
        }
      };
    #endif


    // Functions to register SimpleElastix with SimpleITK member factory
    typedef Image ( Self::*MemberFunctionType )( const Image* fixedImage );
    std::auto_ptr< detail::DualMemberFunctionFactory< MemberFunctionType > > m_DualMemberFactory;

    // This class holds data and configuration that is passed to elastix API when run
    Image*                 m_FixedImage;
    Image*                 m_MovingImage;
    ParameterMapListType   m_ParameterMapList;
    ParameterMapListType   m_TransformParameters;
    std::string            m_LogFileName;
    bool                   m_LogToConsole;
    Image*                 m_FixedMask;
    Image*                 m_MovingMask;
    Image                  m_ResultImage;

};

// SELX_EXPORT elastix::ELASTIX::ParameterMapType ReadParameterFile( const std::string filename );

/** Procedural Interface 

SELX_EXPORT Image elastix( Image fixedImage, Image movingImage, ParameterMapType parameterMap, bool logToConsole = false, std::string logFileName = "" );
SELX_EXPORT Image elastix( Image fixedImage, Image movingImage, ParameterMapType parameterMap, Image fixedMask, Image movingMask, bool logToConsole = false, std::string logFileName = "" );
*/

} // end namespace simple
} // end namespace itk

#endif // __selxsimpleelastix_h_