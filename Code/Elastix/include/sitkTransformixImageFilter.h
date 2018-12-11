#ifndef __sitktransformiximagefilter_h_
#define __sitktransformiximagefilter_h_

#include "sitkCommon.h"
#include "sitkImage.h"

namespace itk { 
  namespace simple {

class SITKCommon_EXPORT TransformixImageFilter
{
public:

  TransformixImageFilter();
  ~TransformixImageFilter();

  typedef TransformixImageFilter Self;                                

  typedef std::string                                             ParameterKeyType;
  typedef std::string                                             ParameterValueType;
  typedef std::vector< ParameterValueType >                       ParameterValueVectorType;
  typedef ParameterValueVectorType::iterator                      ParameterValueVectorIterator;
  typedef std::map< ParameterKeyType, ParameterValueVectorType >  ParameterMapType;
  typedef std::vector< ParameterMapType >                         ParameterMapVectorType;
  typedef ParameterMapType::iterator                              ParameterMapIterator;
  typedef ParameterMapType::const_iterator                        ParameterMapConstIterator;

  const std::string GetName();

  Self& SetMovingImage( const Image& movingImage );
  Image& GetMovingImage();
  Self& RemoveMovingImage();

  Self& SetFixedPointSetFileName( const std::string movingPointSetFileName );
  std::string GetFixedPointSetFileName();
  Self& RemoveFixedPointSetFileName();

  Self& SetComputeSpatialJacobian( const bool );
  bool GetComputeSpatialJacobian();
  Self& ComputeSpatialJacobianOn();
  Self& ComputeSpatialJacobianOff();

  Self& SetComputeDeterminantOfSpatialJacobian( const bool );
  bool GetComputeDeterminantOfSpatialJacobian();
  Self& ComputeDeterminantOfSpatialJacobianOn();
  Self& ComputeDeterminantOfSpatialJacobianOff();

  Self& SetComputeDeformationField( bool );
  bool GetComputeDeformationField();
  Self& ComputeDeformationFieldOn();
  Self& ComputeDeformationFieldOff();

  Self& SetOutputDirectory( const std::string outputDirectory );
  std::string GetOutputDirectory();
  Self& RemoveOutputDirectory();

  Self& SetLogFileName( const std::string logFileName );
  std::string GetLogFileName();
  Self& RemoveLogFileName();

  Self& SetLogToFile( const bool logToFile );
  bool GetLogToFile();
  Self& LogToFileOn();
  Self& LogToFileOff();

  Self& SetLogToConsole( const bool logToConsole );
  bool GetLogToConsole();
  Self& LogToConsoleOn();
  Self& LogToConsoleOff();

  Self& SetTransformParameterMap( const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapVector );
  Self& SetTransformParameterMap( const std::map< std::string, std::vector< std::string > > parameterMap );
  Self& AddTransformParameterMap( const std::map< std::string, std::vector< std::string > > parameterMap );
  std::vector< std::map< std::string, std::vector< std::string > > > GetTransformParameterMap();
   unsigned int GetNumberOfTransformParameterMaps();

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

  Self& PrintParameterMap();
  Self& PrintParameterMap( const std::map< std::string, std::vector< std::string > > parameterMap );
  Self& PrintParameterMap( const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapVector );

  Image Execute();

  Image GetResultImage();
  Image GetDeformationField();

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
