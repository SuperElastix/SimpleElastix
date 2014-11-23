#ifndef __selxsimpleelastix_h_
#define __selxsimpleelastix_h_

#include "sitkSimpleElastix.h"
#include "SimpleITK.h"
#include "elastixlib.h"

namespace itk {
  namespace simple {

class SELX_EXPORT SimpleElastix
{
  public:

    // typedefs inherited from elastix library api
    typedef elastix::ELASTIX                      ElastixLibType;
    typedef ElastixLibType::ParameterMapType      ParameterMapType;
    typedef ElastixLibType::ParameterMapListType  ParameterMapListType;
    typedef itk::ParameterFileParser              ParameterFileParserType;
    typedef ParameterFileParserType::Pointer      ParameterFileParserPointer;

    // typedefs for images
    typedef itk::Image< float, 3u >               ITKImageType;

    SimpleElastix( void );
    ~SimpleElastix( void );

    const std::string GetName( void );

    void SetFixedImage( Image fixedImage );
    void SetMovingImage( Image movingImage );
    void SetParameterMap( std::string filename );

    void Run( void );

    Image GetResultImage( void );

  protected:

  private:

    ElastixLibType* m_Elastix;

    Image               m_FixedImage;
    Image               m_MovingImage;
    ParameterMapType    m_ParameterMap;
    Image               m_FixedMask;
    Image               m_MovingMask;

};

SELX_EXPORT const std::string HelloWorld( void );

/** Procedural Interface 

SELX_EXPORT Image elastix( Image fixedImage, Image movingImage, ParameterMapType parameterMap, bool logToConsole = false, std::string logToFile = "" );
SELX_EXPORT Image elastix( Image fixedImage, Image movingImage, ParameterMapType parameterMap, Image fixedMask, Image movingMask, bool logToConsole = false, std::string logToFile = "" );
*/

} // end namespace simple
} // end namespace itk

#endif // __selxsimpleelastix_h_