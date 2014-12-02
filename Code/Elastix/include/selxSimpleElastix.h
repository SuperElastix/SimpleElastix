#ifndef __selxsimpleelastix_h_
#define __selxsimpleelastix_h_

// SimpleITK
#include "sitkSimpleElastix.h"
#include "sitkPixelIDTokens.h"
#include "sitkImage.h"
#include "sitkMemberFunctionFactory.h"

// SimpleElastix
#include "selxParameterMapInterface.h"
#include "elastixlib.h"

namespace itk { 
  namespace simple {

class SELX_EXPORT SimpleElastix : ParameterMapInterface
{
  public:

    typedef SimpleElastix Self;
    SimpleElastix( void );
    ~SimpleElastix( void );
 
    // typedefs inherited from SimpleITK
    typedef BasicPixelIDTypeList PixelIDTypeList;

    // typedefs inherited from elastix library api
    typedef elastix::ELASTIX libelastix;

    // To be wrapped by SWIG

    const std::string GetName( void );

    // Images
    void SetFixedImage( Image* fixedImage );
    void SetMovingImage( Image* movingImage );
    void SetFixedMask( Image* fixedMask );
    void SetMovingMask( Image* movingMask );

    // Register images
    Image Execute( void );

    // Get result
    Image GetResultImage( void );
    ParameterMapType GetParameterMap( void );
    ParameterMapListType GetParameterMapList( void );

    // TODO: Move to common class
    void LogToConsoleOn( void );
    void LogToConsoleOff( void );
    void LogFileName( const std::string filename );
 
  private:

    template< typename TResultImage >
    Image ExecuteInternal( void );

    // An addressor of this class to be utilized with registering member functions with the factory.
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

    // This class holds data and configuration that is passed to elastix API when run
    Image*                 m_FixedImage;
    Image*                 m_MovingImage;
    std::string            m_LogFileName;
    bool                   m_LogToConsole;
    Image*                 m_FixedMask;
    Image*                 m_MovingMask;
    Image                  m_ResultImage;

};


SELX_EXPORT ParameterMapInterface::ParameterMapType ReadParameterFile( const std::string filename );

/** Procedural Interface 


SELX_EXPORT Image elastix( Image fixedImage, Image movingImage, ParameterMapType parameterMap, bool logToConsole = false, std::string logFileName = "" );
SELX_EXPORT Image elastix( Image fixedImage, Image movingImage, ParameterMapType parameterMap, Image fixedMask, Image movingMask, bool logToConsole = false, std::string logFileName = "" );
*/

} // end namespace simple
} // end namespace itk

#endif // __selxsimpleelastix_h_