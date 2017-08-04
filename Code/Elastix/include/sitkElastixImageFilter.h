#ifndef __sitkelastiximagefilter_h_
#define __sitkelastiximagefilter_h_

#include "sitkCommon.h"
#include "sitkImage.h"

namespace itk { 
  namespace simple {

/** \class ElastixImageFilter
* \brief The class that wraps the elastix registration library.
*/
class SITKCommon_EXPORT ElastixImageFilter
{
  public:

    ElastixImageFilter( void );
    ~ElastixImageFilter( void );

    typedef ElastixImageFilter Self;                                

    typedef std::vector< Image >                                    VectorOfImage;

    typedef std::string                                             ParameterKeyType;
    typedef std::string                                             ParameterValueType;
    typedef std::vector< ParameterValueType >                       ParameterValueVectorType;
    typedef ParameterValueVectorType::iterator                      ParameterValueVectorIterator;
    typedef std::map< ParameterKeyType, ParameterValueVectorType >  ParameterMapType;
    typedef std::vector< ParameterMapType >                         ParameterMapVectorType;
    typedef ParameterMapType::iterator                              ParameterMapIterator;
    typedef ParameterMapType::const_iterator                        ParameterMapConstIterator;

    const std::string GetName( void );

    /** \brief Sets a fixed image.
     *
     * @{
     */
    Self& SetFixedImage( const Image& fixedImage );
    /**@}*/

    /** \brief Sets multiple fixed images.
     *
     * @{
     */
    Self& SetFixedImage( const VectorOfImage& fixedImages );
    /**@}*/
    
    // TODO: Add Doxygen documentation for all methods.
    Self& AddFixedImage( const Image& fixedImage );
    

    Image& GetFixedImage( const unsigned long index );
    VectorOfImage& GetFixedImage( void );
    Self& RemoveFixedImage( const unsigned long index );
    Self& RemoveFixedImage( void );
    unsigned int GetNumberOfFixedImages();

    Self& SetMovingImage( const Image& movingImages );
    Self& SetMovingImage( const VectorOfImage& movingImage );
    Self& AddMovingImage( const Image& movingImage );
    Image& GetMovingImage( const unsigned long index );
    VectorOfImage& GetMovingImage( void );
    Self& RemoveMovingImage( const unsigned long index );
    Self& RemoveMovingImage( void );
    unsigned int GetNumberOfMovingImages();

    Self& SetFixedMask( const Image& fixedMask );
    Self& SetFixedMask( const VectorOfImage& fixedMasks );
    Self& AddFixedMask( const Image& fixedMask );
    Image& GetFixedMask( const unsigned long index );
    VectorOfImage& GetFixedMask( void );
    Self& RemoveFixedMask( const unsigned long index );
    Self& RemoveFixedMask( void );
    unsigned int GetNumberOfFixedMasks();

    Self& SetMovingMask( const Image& movingMask );
    Self& SetMovingMask( const VectorOfImage& movingMasks );
    Self& AddMovingMask( const Image& movingMask );
    Image& GetMovingMask( const unsigned long index );
    VectorOfImage& GetMovingMask( void );
    Self& RemoveMovingMask( const unsigned long index );
    Self& RemoveMovingMask( void );
    unsigned int GetNumberOfMovingMasks();

    Self& SetFixedPointSetFileName( const std::string movingPointSetFileName );
    std::string GetFixedPointSetFileName( void );
    Self& RemoveFixedPointSetFileName( void );

    Self& SetMovingPointSetFileName( const std::string movingPointSetFileName );
    std::string GetMovingPointSetFileName( void );
    Self& RemoveMovingPointSetFileName( void );

    Self& SetOutputDirectory( const std::string outputDirectory );
    std::string GetOutputDirectory( void );
    Self& RemoveOutputDirectory( void );

    Self& SetLogFileName( const std::string logFileName );
    std::string GetLogFileName( void );
    Self& RemoveLogFileName( void );

    Self& SetLogToFile( const bool logToFile );
    bool GetLogToFile( void );
    Self& LogToFileOn( void );
    Self& LogToFileOff( void );

    Self& SetLogToConsole( bool );
    bool GetLogToConsole( void );
    Self& LogToConsoleOn();
    Self& LogToConsoleOff();

    Self& SetParameterMap( const std::string transformName, const unsigned int numberOfResolutions = 4u, const double finalGridSpacingInPhysicalUnits = 10.0 );
    Self& SetParameterMap( const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapVector );
    Self& SetParameterMap( const std::map< std::string, std::vector< std::string > > parameterMap );
    Self& AddParameterMap( const std::map< std::string, std::vector< std::string > > parameterMap );
    std::vector< std::map< std::string, std::vector< std::string > > > GetParameterMap( void );
    std::map< std::string, std::vector< std::string > > GetDefaultParameterMap( const std::string transformName, const unsigned int numberOfResolutions = 4, const double finalGridSpacingInPhysicalUnits = 10.0 );
    unsigned int GetNumberOfParameterMaps( void );

    Self& SetParameter( const std::string key, const std::string value );
    Self& SetParameter( const std::string key, const std::vector< std::string > value );
    Self& SetParameter( const unsigned int index, const std::string key, const std::string value );
    Self& SetParameter( const unsigned int index, const std::string key, const std::vector< std::string > value );
    Self& AddParameter( const std::string key, const std::string value );
    Self& AddParameter( const unsigned int index, const std::string key, const std::string value );
    Self& AddParameter( const std::string key, const std::vector< std::string > value );
    Self& AddParameter( const unsigned int index, const std::string key, const std::vector< std::string > value );
    std::vector< std::string > GetParameter( const std::string key );
    std::vector< std::string > GetParameter( const unsigned int index, const std::string key );
    Self& RemoveParameter( const std::string key );
    Self& RemoveParameter( const unsigned int index, const std::string key );

    Self& SetInitialTransformParameterFileName( const std::string initialTransformParmaterFileName );
    std::string GetInitialTransformParameterFileName( void );
    Self& RemoveInitialTransformParameterFileName( void );

    std::map< std::string, std::vector< std::string > > ReadParameterFile( const std::string filename );
    Self& WriteParameterFile( const std::map< std::string, std::vector< std::string > > parameterMap, const std::string filename );
    
    Image Execute( void );
    std::vector< std::map< std::string, std::vector< std::string > > > GetTransformParameterMap( void );
    std::map< std::string, std::vector< std::string > > GetTransformParameterMap( const unsigned int index );
    Image GetResultImage( void );

    std::vector< std::map< std::string, std::vector< std::string > > > ExecuteInverse( void );
    std::vector< std::map< std::string, std::vector< std::string > > > ExecuteInverse( std::map< std::string, std::vector< std::string > > inverseParameterMap );
    std::vector< std::map< std::string, std::vector< std::string > > > ExecuteInverse( std::vector< std::map< std::string, std::vector< std::string > > > inverseParameterMapVector );
    std::vector< std::map< std::string, std::vector< std::string > > > GetInverseTransformParameterMap( void );

    Self& PrintParameterMap( void );
    Self& PrintParameterMap( const ParameterMapType parameterMapVector );
    Self& PrintParameterMap( const ParameterMapVectorType parameterMapVector );

  private:

    struct ElastixImageFilterImpl;
    ElastixImageFilterImpl* m_Pimple;
    
};

// Procedural Interface 
SITKCommon_EXPORT std::map< std::string, std::vector< std::string > > GetDefaultParameterMap( const std::string transform, const unsigned int numberOfResolutions = 4, const double finalGridSpacingInPhysicalUnits = 8.0 );
SITKCommon_EXPORT std::map< std::string, std::vector< std::string > > ReadParameterFile( const std::string filename );
SITKCommon_EXPORT void WriteParameterFile( const std::map< std::string, std::vector< std::string > > parameterMap, const std::string filename );
SITKCommon_EXPORT void PrintParameterMap( const std::map< std::string, std::vector< std::string > > parameterMap );
SITKCommon_EXPORT void PrintParameterMap( const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapVector );
SITKCommon_EXPORT Image Elastix( const Image& fixedImage, const Image& movingImage, const bool logToConsole = false, const bool logToFile = false, const std::string outputDirectory = "." );
SITKCommon_EXPORT Image Elastix( const Image& fixedImage, const Image& movingImage, const Image& fixedMask, const Image& movingMask, const bool logToConsole = false, const bool logToFile = false, const std::string outputDirectory = "." );
SITKCommon_EXPORT Image Elastix( const Image& fixedImage, const Image& movingImage, const std::string defaultParameterMapName, const bool logToConsole = false, const bool logToFile = false, const std::string outputDirectory = "." );
SITKCommon_EXPORT Image Elastix( const Image& fixedImage, const Image& movingImage, const std::map< std::string, std::vector< std::string > > parameterMap, const bool logToConsole = false, const bool logToFile = false, const std::string outputDirectory = "." );
SITKCommon_EXPORT Image Elastix( const Image& fixedImage, const Image& movingImage, const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapVector, const bool logToConsole = false, const bool logToFile = false, const std::string outputDirectory = "." );
SITKCommon_EXPORT Image Elastix( const Image& fixedImage, const Image& movingImage, const std::string defaultParameterMapName, const Image& fixedMask, const Image& movingMask, const bool logToConsole = false, const bool logToFile = false, const std::string outputDirectory = "." );
SITKCommon_EXPORT Image Elastix( const Image& fixedImage, const Image& movingImage, const std::map< std::string, std::vector< std::string > >, const Image& fixedMask, const Image& movingMask, const bool logToConsole = false, const bool logToFile = false, const std::string outputDirectory = "." );
SITKCommon_EXPORT Image Elastix( const Image& fixedImage, const Image& movingImage, std::vector< std::map< std::string, std::vector< std::string > > > parameterMapVector, const Image& fixedMask, const Image& movingMask, const bool logToConsole = false, const bool logToFile = false, const std::string outputDirectory = "." );

} // end namespace simple
} // end namespace itk

#endif // __sitkelastiximagefilter_h_