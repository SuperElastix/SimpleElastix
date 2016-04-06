#ifndef __sitksimpleelastix_h_
#define __sitksimpleelastix_h_

// SimpleITK
#include "sitkCommon.h"
#include "sitkMemberFunctionFactory.h"
#include "sitkDualMemberFunctionFactory.h"
#include "sitkImage.h"

// Elastix
#include "elxElastixFilter.h"
#include "elxParameterObject.h"

namespace itk { 
  namespace simple {

class SITKCommon_EXPORT SimpleElastix
{
  public:

    SimpleElastix( void );
    ~SimpleElastix( void );

    typedef SimpleElastix Self;                                

    typedef std::vector< Image >                                VectorOfImage;

    typedef elastix::ParameterObject                            ParameterObjectType;
    typedef ParameterObjectType::Pointer                        ParameterObjectPointer;
    typedef ParameterObjectType::ParameterMapType               ParameterMapType;
    typedef ParameterObjectType::ParameterMapVectorType         ParameterMapVectorType;
    typedef ParameterMapType::iterator                          ParameterMapIterator;
    typedef ParameterMapType::const_iterator                    ParameterMapConstIterator;
    typedef itk::ParameterFileParser                            ParameterFileParserType;
    typedef ParameterFileParserType::Pointer                    ParameterFileParserPointer;
    typedef ParameterObjectType::ParameterKeyType               ParameterKeyType;
    typedef ParameterObjectType::ParameterValueType             ParameterValueType;
    typedef ParameterObjectType::ParameterValueVectorType       ParameterValueVectorType;
    typedef ParameterObjectType::ParameterValueVectorIterator   ParameterValueVectorIterator;

    const std::string GetName( void );

    Self& SetFixedImage( const Image& fixedImage );
    Self& SetFixedImage( const VectorOfImage& fixedImages );
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

    Self& SetInitialTransformParameterFileName( const std::string initialTransformParmaterFileName );
    std::string GetInitialTransformParameterFileName( void );
    Self& RemoveInitialTransformParameterFileName( void );

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

    std::map< std::string, std::vector< std::string > > ReadParameterFile( const std::string filename );
    Self& WriteParameterFile( const std::map< std::string, std::vector< std::string > > parameterMap, const std::string filename );

    Self& PrettyPrint( void );
    Self& PrettyPrint( const std::map< std::string, std::vector< std::string > > parameterMap );
    Self& PrettyPrint( const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapVector );

    Image Execute( void );
    std::vector< std::map< std::string, std::vector< std::string > > > GetTransformParameterMap( void );
    Image GetResultImage( void );

    // std::vector< std::map< std::string, std::vector< std::string > > > ExecuteInverse( void );
    // std::vector< std::map< std::string, std::vector< std::string > > > GetInverseTransformParameterMap( void );

  private:

    bool IsEmpty( const Image& image );

    // Definitions for SimpleITK member factory
    typedef Image ( Self::*MemberFunctionType )( void );
    friend struct detail::DualExecuteInternalAddressor< MemberFunctionType >;
    template< class TFixedImage, class TMovingImage > Image DualExecuteInternal ( void );
    std::auto_ptr< detail::DualMemberFunctionFactory< MemberFunctionType > > m_DualMemberFactory;

    VectorOfImage           m_FixedImages;
    VectorOfImage           m_MovingImages;
    VectorOfImage           m_FixedMasks;
    VectorOfImage           m_MovingMasks;

    std::string             m_InitialTransformParameterMapFileName;
    std::string             m_FixedPointSetFileName;
    std::string             m_MovingPointSetFileName;

    ParameterMapVectorType  m_ParameterMapVector;
    ParameterMapVectorType  m_TransformParameterMapVector;
    ParameterMapVectorType  m_InverseTransformParameterMapVector;

    std::string             m_OutputDirectory;
    std::string             m_LogFileName;

    bool                    m_LogToFile;
    bool                    m_LogToConsole;
    
    Image                   m_ResultImage;
};

// Procedural Interface 
SITKCommon_EXPORT std::map< std::string, std::vector< std::string > > GetDefaultParameterMap( const std::string transform, const unsigned int numberOfResolutions = 4, const double finalGridSpacingInPhysicalUnits = 8.0 );
SITKCommon_EXPORT std::map< std::string, std::vector< std::string > > ReadParameterFile( const std::string filename );
SITKCommon_EXPORT void WriteParameterFile( const std::map< std::string, std::vector< std::string > > parameterMap, const std::string filename );
SITKCommon_EXPORT void PrettyPrint( const std::map< std::string, std::vector< std::string > > parameterMap );
SITKCommon_EXPORT void PrettyPrint( const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapVector );
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

#endif // __sitksimpleelastix_h_