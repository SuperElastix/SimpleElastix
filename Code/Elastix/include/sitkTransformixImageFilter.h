#ifndef __sitktransformiximagefilter_h_
#define __sitktransformiximagefilter_h_

#include "sitkCommon.h"
#include "sitkImage.h"

namespace itk { 
  namespace simple {

class SITKCommon_EXPORT TransformixImageFilter
{
  public:

    TransformixImageFilter( void );
    ~TransformixImageFilter( void );

    typedef TransformixImageFilter Self;                                

    typedef std::string                                             ParameterKeyType;
    typedef std::string                                             ParameterValueType;
    typedef std::vector< ParameterValueType >                       ParameterValueVectorType;
    typedef ParameterValueVectorType::iterator                      ParameterValueVectorIterator;
    typedef std::map< ParameterKeyType, ParameterValueVectorType >  ParameterMapType;
    typedef std::vector< ParameterMapType >                         ParameterMapVectorType;
    typedef ParameterMapType::iterator                              ParameterMapIterator;
    typedef ParameterMapType::const_iterator                        ParameterMapConstIterator;

    const std::string GetName( void );

    Self& SetMovingImage( const Image& movingImage );
    Image& GetMovingImage( void );
    Self& RemoveMovingImage( void );

    Self& SetFixedPointSetFileName( const std::string movingPointSetFileName );
    std::string GetFixedPointSetFileName( void );
    Self& RemoveFixedPointSetFileName( void );

    Self& SetComputeSpatialJacobian( const bool );
    bool GetComputeSpatialJacobian( void );
    Self& ComputeSpatialJacobianOn( void );
    Self& ComputeSpatialJacobianOff( void );

    Self& SetComputeDeterminantOfSpatialJacobian( const bool );
    bool GetComputeDeterminantOfSpatialJacobian( void );
    Self& ComputeDeterminantOfSpatialJacobianOn( void );
    Self& ComputeDeterminantOfSpatialJacobianOff( void );

    Self& SetComputeDeformationField( bool );
    bool GetComputeDeformationField( void );
    Self& ComputeDeformationFieldOn( void );
    Self& ComputeDeformationFieldOff( void );

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

    Self& SetLogToConsole( const bool logToConsole );
    bool GetLogToConsole( void );
    Self& LogToConsoleOn();
    Self& LogToConsoleOff();

    Self& SetTransformParameterMap( const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapVector );
    Self& SetTransformParameterMap( const std::map< std::string, std::vector< std::string > > parameterMap );
    Self& AddTransformParameterMap( const std::map< std::string, std::vector< std::string > > parameterMap );
    std::vector< std::map< std::string, std::vector< std::string > > > GetTransformParameterMap( void );
    unsigned int GetNumberOfTransformParameterMaps( void );

    Self& SetTransformParameter( const std::string key, const std::string value );
    Self& SetTransformParameter( const std::string key, const std::vector< std::string > value );
    Self& SetTransformParameter( const unsigned int index, const std::string key, const std::string value );
    Self& SetTransformParameter( const unsigned int index, const std::string key, const std::vector< std::string > value );
    Self& AddTransformParameter( const std::string key, const std::string value );
    Self& AddTransformParameter( const unsigned int index, const std::string key, const std::string value );
    std::vector< std::string > GetTransformParameter( const std::string key );
    std::vector< std::string > GetTransformParameter( const unsigned int index, const std::string key );
    Self& RemoveTransformParameter( const std::string key );
    Self& RemoveTransformParameter( const unsigned int index, const std::string key );

    std::map< std::string, std::vector< std::string > > ReadParameterFile( const std::string parameterFileName );
    Self& WriteParameterFile( const std::map< std::string, std::vector< std::string > > parameterMap, const std::string parameterFileName );

    Self& PrintParameterMap( void );
    Self& PrintParameterMap( const std::map< std::string, std::vector< std::string > > parameterMap );
    Self& PrintParameterMap( const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapVector );

    Image Execute( void );

    Image GetResultImage( void );

  private:

    struct TransformixImageFilterImpl;
    TransformixImageFilterImpl* m_Pimple;
    
};

// Procedural Interface 
SITKCommon_EXPORT Image Transformix( const Image& movingImage, const std::map< std::string, std::vector< std::string > > parameterMap, const bool logToConsole = false, const std::string outputDirectory = "." );
SITKCommon_EXPORT Image Transformix( const Image& movingImage, const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapVector, const bool logToConsole = false, const std::string outputDirectory = "." );

} // end namespace simple
} // end namespace itk

#endif // __sitktransformiximagefilter_h_
