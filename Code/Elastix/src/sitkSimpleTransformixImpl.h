#ifndef __sitksimpletransformiximpl_h_
#define __sitksimpletransformiximpl_h_

// SimpleITK
#include "sitkSimpleTransformix.h"
#include "sitkMemberFunctionFactory.h"

// Transformix
#include "elxTransformixFilter.h"
#include "elxParameterObject.h"

namespace itk { 
  namespace simple {

struct SimpleTransformix::SimpleTransformixImpl
{

  SimpleTransformixImpl( void );
  ~SimpleTransformixImpl( void );

  typedef SimpleTransformixImpl Self;

  typedef elastix::ParameterObject                       ParameterObjectType;
  typedef ParameterObjectType::Pointer                   ParameterObjectPointer;
  typedef ParameterObjectType::ParameterMapType          ParameterMapType;
  typedef ParameterObjectType::ParameterMapVectorType    ParameterMapVectorType;
  typedef ParameterMapType::iterator                     ParameterMapIterator;
  typedef ParameterMapType::const_iterator               ParameterMapConstIterator;
  typedef itk::ParameterFileParser                       ParameterFileParserType;
  typedef ParameterFileParserType::Pointer               ParameterFileParserPointer;
  typedef ParameterObjectType::ParameterKeyType          ParameterKeyType;
  typedef ParameterObjectType::ParameterValueType        ParameterValueType;
  typedef ParameterObjectType::ParameterValueVectorType  ParameterValueVectorType;

  const std::string GetName( void );

  void SetMovingImage( const Image& movingImage );
  Image& GetMovingImage( void );
  void RemoveMovingImage( void );

  void SetFixedPointSetFileName( const std::string movingPointSetFileName );
  std::string GetFixedPointSetFileName( void );
  void RemoveFixedPointSetFileName( void );

  void SetComputeSpatialJacobian( const bool );
  bool GetComputeSpatialJacobian( void );
  void ComputeSpatialJacobianOn( void );
  void ComputeSpatialJacobianOff( void );

  void SetComputeDeterminantOfSpatialJacobian( const bool );
  bool GetComputeDeterminantOfSpatialJacobian( void );
  void ComputeDeterminantOfSpatialJacobianOn( void );
  void ComputeDeterminantOfSpatialJacobianOff( void );

  void SetComputeDeformationField( bool );
  bool GetComputeDeformationField( void );
  void ComputeDeformationFieldOn( void );
  void ComputeDeformationFieldOff( void );

  void SetOutputDirectory( const std::string outputDirectory );
  std::string GetOutputDirectory( void );
  void RemoveOutputDirectory( void );

  void SetLogFileName( const std::string logFileName );
  std::string GetLogFileName( void );
  void RemoveLogFileName( void );

  void SetLogToFile( const bool logToFile );
  bool GetLogToFile( void );
  void LogToFileOn( void );
  void LogToFileOff( void );

  void SetLogToConsole( const bool logToConsole );
  bool GetLogToConsole( void );
  void LogToConsoleOn();
  void LogToConsoleOff();

  void SetTransformParameterMap( const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapVector );
  void SetTransformParameterMap( const std::map< std::string, std::vector< std::string > > parameterMap );
  void AddTransformParameterMap( const std::map< std::string, std::vector< std::string > > parameterMap );
  std::vector< std::map< std::string, std::vector< std::string > > > GetTransformParameterMap( void );
  unsigned int GetNumberOfTransformParameterMaps( void );

  void SetTransformParameter( const std::string key, const std::string value );
  void SetTransformParameter( const std::string key, const std::vector< std::string > value );
  void SetTransformParameter( const unsigned int index, const std::string key, const std::string value );
  void SetTransformParameter( const unsigned int index, const std::string key, const std::vector< std::string > value );
  void AddTransformParameter( const std::string key, const std::string value );
  void AddTransformParameter( const unsigned int index, const std::string key, const std::string value );
  std::vector< std::string > GetTransformParameter( const std::string key );
  std::vector< std::string > GetTransformParameter( const unsigned int index, const std::string key );
  void RemoveTransformParameter( const std::string key );
  void RemoveTransformParameter( const unsigned int index, const std::string key );

  std::map< std::string, std::vector< std::string > > ReadParameterFile( const std::string filename );
  void WriteParameterFile( const std::map< std::string, std::vector< std::string > > parameterMap, const std::string parameterFileName );

  void PrintParameterMap( void );
  void PrintParameterMap( const std::map< std::string, std::vector< std::string > > parameterMap );
  void PrintParameterMap( const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapVector );

  Image Execute( void );

  Image GetResultImage( void );

  bool IsEmpty( const Image& image );

  // Definitions for SimpleITK member factory
  typedef Image ( Self::*MemberFunctionType )( void );
  template< class TMovingImage > Image ExecuteInternal( void );
  friend struct detail::MemberFunctionAddressor< MemberFunctionType >;
  nsstd::auto_ptr< detail::MemberFunctionFactory< MemberFunctionType > > m_MemberFactory;

  Image                   m_MovingImage;
  Image                   m_ResultImage;

  ParameterMapVectorType  m_TransformParameterMapVector;

  bool                    m_ComputeSpatialJacobian;
  bool                    m_ComputeDeterminantOfSpatialJacobian;
  bool                    m_ComputeDeformationField;
  std::string             m_MovingPointSetFileName;

  std::string             m_OutputDirectory;
  std::string             m_LogFileName;

  bool                    m_LogToConsole;
  bool                    m_LogToFile;
};

} // end namespace simple
} // end namespace itk

#endif // __sitksimpletransformiximpl_h_
