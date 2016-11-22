#ifndef __sitksimpleelastiximpl_h_
#define __sitksimpleelastiximpl_h_

// SimpleITK
#include "sitkSimpleElastix.h"
#include "sitkMemberFunctionFactory.h"
#include "sitkDualMemberFunctionFactory.h"

// Elastix
#include "elxElastixFilter.h"
#include "elxParameterObject.h"

namespace itk { 
  namespace simple {

struct SimpleElastix::SimpleElastixImpl
{

  SimpleElastixImpl( void );
  ~SimpleElastixImpl( void );

  typedef SimpleElastixImpl Self;                                

  typedef SimpleElastix::VectorOfImage                VectorOfImage;

  typedef SimpleElastix::ParameterKeyType             ParameterKeyType;
  typedef SimpleElastix::ParameterValueType           ParameterValueType;
  typedef SimpleElastix::ParameterValueVectorType     ParameterValueVectorType;
  typedef SimpleElastix::ParameterValueVectorIterator ParameterValueVectorIterator;
  typedef SimpleElastix::ParameterMapType             ParameterMapType;
  typedef SimpleElastix::ParameterMapVectorType       ParameterMapVectorType;
  typedef SimpleElastix::ParameterMapIterator         ParameterMapIterator;
  typedef SimpleElastix::ParameterMapConstIterator    ParameterMapConstIterator;

  typedef elastix::ParameterObject                    ParameterObjectType;
  typedef elastix::ParameterObject::Pointer           ParameterObjectPointer;           

  const std::string GetName( void );

  void SetFixedImage( const Image& fixedImage );
  void SetFixedImage( const VectorOfImage& fixedImages );
  void AddFixedImage( const Image& fixedImage );
  Image& GetFixedImage( const unsigned long index );
  VectorOfImage& GetFixedImage( void );
  void RemoveFixedImage( const unsigned long index );
  void RemoveFixedImage( void );
  unsigned int GetNumberOfFixedImages();

  void SetMovingImage( const Image& movingImages );
  void SetMovingImage( const VectorOfImage& movingImage );
  void AddMovingImage( const Image& movingImage );
  Image& GetMovingImage( const unsigned long index );
  VectorOfImage& GetMovingImage( void );
  void RemoveMovingImage( const unsigned long index );
  void RemoveMovingImage( void );
  unsigned int GetNumberOfMovingImages();

  void SetFixedMask( const Image& fixedMask );
  void SetFixedMask( const VectorOfImage& fixedMasks );
  void AddFixedMask( const Image& fixedMask );
  Image& GetFixedMask( const unsigned long index );
  VectorOfImage& GetFixedMask( void );
  void RemoveFixedMask( const unsigned long index );
  void RemoveFixedMask( void );
  unsigned int GetNumberOfFixedMasks();

  void SetMovingMask( const Image& movingMask );
  void SetMovingMask( const VectorOfImage& movingMasks );
  void AddMovingMask( const Image& movingMask );
  Image& GetMovingMask( const unsigned long index );
  VectorOfImage& GetMovingMask( void );
  void RemoveMovingMask( const unsigned long index );
  void RemoveMovingMask( void );
  unsigned int GetNumberOfMovingMasks();

  void SetFixedPointSetFileName( const std::string movingPointSetFileName );
  std::string GetFixedPointSetFileName( void );
  void RemoveFixedPointSetFileName( void );

  void SetMovingPointSetFileName( const std::string movingPointSetFileName );
  std::string GetMovingPointSetFileName( void );
  void RemoveMovingPointSetFileName( void );

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

  void SetLogToConsole( bool );
  bool GetLogToConsole( void );
  void LogToConsoleOn();
  void LogToConsoleOff();

  void SetParameterMap( const std::string transformName, const unsigned int numberOfResolutions = 4u, const double finalGridSpacingInPhysicalUnits = 10.0 );
  void SetParameterMap( const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapVector );
  void SetParameterMap( const std::map< std::string, std::vector< std::string > > parameterMap );
  void AddParameterMap( const std::map< std::string, std::vector< std::string > > parameterMap );
  std::vector< std::map< std::string, std::vector< std::string > > > GetParameterMap( void );
  std::map< std::string, std::vector< std::string > > GetDefaultParameterMap( const std::string transformName, const unsigned int numberOfResolutions = 4, const double finalGridSpacingInPhysicalUnits = 10.0 );
  unsigned int GetNumberOfParameterMaps( void );

  void SetParameter( const std::string key, const std::string value );
  void SetParameter( const std::string key, const std::vector< std::string > value );
  void SetParameter( const unsigned int index, const std::string key, const std::string value );
  void SetParameter( const unsigned int index, const std::string key, const std::vector< std::string > value );
  void AddParameter( const std::string key, const std::string value );
  void AddParameter( const unsigned int index, const std::string key, const std::string value );
  void AddParameter( const std::string key, const std::vector< std::string > value );
  void AddParameter( const unsigned int index, const std::string key, const std::vector< std::string > value );
  std::vector< std::string > GetParameter( const std::string key );
  std::vector< std::string > GetParameter( const unsigned int index, const std::string key );
  void RemoveParameter( const std::string key );
  void RemoveParameter( const unsigned int index, const std::string key );

  void SetInitialTransformParameterFileName( const std::string initialTransformParmaterFileName );
  std::string GetInitialTransformParameterFileName( void );
  void RemoveInitialTransformParameterFileName( void );

  std::map< std::string, std::vector< std::string > > ReadParameterFile( const std::string filename );
  void WriteParameterFile( const std::map< std::string, std::vector< std::string > > parameterMap, const std::string filename );

  Image Execute( void );
  std::vector< std::map< std::string, std::vector< std::string > > > GetTransformParameterMap( void );
  std::map< std::string, std::vector< std::string > > GetTransformParameterMap( const unsigned int index );
  Image GetResultImage( void );

  std::vector< std::map< std::string, std::vector< std::string > > > ExecuteInverse( void );
  std::vector< std::map< std::string, std::vector< std::string > > > ExecuteInverse( std::map< std::string, std::vector< std::string > > inverseParameterMap );
  std::vector< std::map< std::string, std::vector< std::string > > > ExecuteInverse( std::vector< std::map< std::string, std::vector< std::string > > > inverseParameterMapVector );
  std::vector< std::map< std::string, std::vector< std::string > > > GetInverseTransformParameterMap( void );

  void PrintParameterMap( void );
  void PrintParameterMap( const ParameterMapType parameterMapVector );
  void PrintParameterMap( const ParameterMapVectorType parameterMapVector );

  bool IsEmpty( const Image& image );

  // Definitions for SimpleITK member factory
  typedef Image ( Self::*MemberFunctionType )( void );
  template< class TFixedImage, class TMovingImage > Image DualExecuteInternal( void );
  friend struct detail::DualExecuteInternalAddressor< MemberFunctionType >;
  nsstd::auto_ptr< detail::DualMemberFunctionFactory< MemberFunctionType > > m_DualMemberFactory;

  VectorOfImage           m_FixedImages;
  VectorOfImage           m_MovingImages;
  VectorOfImage           m_FixedMasks;
  VectorOfImage           m_MovingMasks;
  Image                   m_ResultImage;

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

};

} // end namespace simple
} // end namespace itk

#endif // __sitksimpleelastiximpl_h_