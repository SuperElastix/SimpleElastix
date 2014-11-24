#ifndef __selxsimpleelastix_h_
#define __selxsimpleelastix_h_

#include "sitkSimpleElastix.h"
#include "sitkImage.h"
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

    // To be wrapped by SWIG

    SimpleElastix( void );
    ~SimpleElastix( void );

    const std::string GetName( void );

    // Images
    void SetFixedImage( Image& fixedImage );
    void SetMovingImage( Image& movingImage );
    void SetFixedMask( Image& fixedMask );
    void SetMovingMask( Image& movingMask );

    Image* GetFixedImage( void );

    // Parameter Maps
    void SetParameterMap( ParameterMapType parameterMap );
    void SetParameterMap( ParameterMapListType parameterMapList );
    void AppendParameterMap( ParameterMapType parameterMap );
    void AppendParameterMap( ParameterMapListType parameterMapList );
    ParameterMapListType GetParameterMapList( void );
    ParameterMapType GetParameterMap( int n );
    ParameterMapType GetParameterMap( void );
    int GetNumberOfParameterMaps( void );
    ParameterMapType ReadParameterFile( const std::string filename );

    // Register images
    void Run( void );

    // Get result
    Image GetResultImage( void );
    ParameterMapType GetTransformParameterMap( void );
    ParameterMapListType GetTransformParameterMapList( void );

    // Logging
    void LogToConsoleOn( void );
    void LogToConsoleOff( void );
    void LogFileName( const std::string filename );

  protected:

  private:

    ElastixLibType*         m_Elastix;

    Image*                  m_FixedImage;
    Image*                  m_MovingImage;
    ParameterMapListType    m_ParameterMapList;
    std::string             m_LogFileName;
    bool                    m_LogToConsole;
    Image*                  m_FixedMask;
    Image*                  m_MovingMask;

};

SELX_EXPORT SimpleElastix::ParameterMapType ReadParameterFile( const std::string filename );

/** Procedural Interface 

SELX_EXPORT Image elastix( Image fixedImage, Image movingImage, ParameterMapType parameterMap, bool logToConsole = false, std::string logFileName = "" );
SELX_EXPORT Image elastix( Image fixedImage, Image movingImage, ParameterMapType parameterMap, Image fixedMask, Image movingMask, bool logToConsole = false, std::string logFileName = "" );
*/

} // end namespace simple
} // end namespace itk

#endif // __selxsimpleelastix_h_