#ifndef __sitksimpletransformix_h_
#define __sitksimpletransformix_h_

// SimpleITK
#include "sitkCommon.h"
#include "sitkMemberFunctionFactory.h"
#include "sitkImage.h"

// Transformix
#include "elxTransformixFilter.h"
#include "elxParameterObject.h"

namespace itk { 
  namespace simple {

class SITKCommon_EXPORT SimpleTransformix
{
  public:

    SimpleTransformix( void );
    ~SimpleTransformix( void );

    typedef SimpleTransformix Self;                                

    typedef elastix::ParameterObject                       ParameterObjectType;
    typedef ParameterObjectType::Pointer                   ParameterObjectPointer;
    typedef ParameterObjectType::ParameterMapType          ParameterMapType;
    typedef ParameterObjectType::ParameterMapVectorType    ParameterMapVectorType;
    typedef ParameterMapType::iterator                     ParameterMapIterator;
    typedef ParameterMapType::const_iterator               ParameterMapConstIterator;
    typedef itk::ParameterFileParser                       ParameterFileParserType;
    typedef ParameterFileParserType::Pointer               ParameterFileParserPointer;
    typedef ParameterObjectType::ParameterKeyType          ParameterKeyType;
    typedef ParameterObjectType::ParameterValueVectorType  ParameterValueVectorType;

    /** To be wrapped by SWIG */ 

    const std::string GetName( void );

    // Images
    Self& SetInputImage( const Image& inputImage );
    Image& GetInputImage( void );

    Self& SetInputPointSetFileName( const std::string inputPointSetFileName );
    std::string GetInputPointSetFileName( void );
    Self& RemoveInputPointSetFileName( void );

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

    Self& SetTransformParameterMap( const ParameterMapVectorType parameterMapVector );
    Self& SetTransformParameterMap( const ParameterMapType parameterMap );

    ParameterMapType ReadParameterFile( const std::string filename );
    Self& WriteParameterFile( const ParameterMapType parameterMap, const std::string parameterFileName );

    Self& PrettyPrint( void );
    Self& PrettyPrint( const ParameterMapType parameterMap );
    Self& PrettyPrint( const ParameterMapVectorType parameterMapVector );

    Image Execute( void );

    Image GetResultImage( void );
    ParameterMapVectorType GetTransformParameterMap( void );

  private:

    bool IsEmpty( const Image& image );

    // Definitions for SimpleITK member factory
    typedef Image (Self::*MemberFunctionType)( void );
    template< class TInputImage > Image ExecuteInternal ( void );
    friend struct detail::MemberFunctionAddressor< MemberFunctionType >;
    std::auto_ptr< detail::MemberFunctionFactory< MemberFunctionType > > m_MemberFactory;

    Image                   m_InputImage;

    bool                    m_ComputeSpatialJacobian;
    bool                    m_ComputeDeterminantOfSpatialJacobian;
    bool                    m_ComputeDeformationField;
    std::string             m_InputPointSetFileName;

    ParameterMapVectorType  m_TransformParameterMapVector;

    std::string             m_OutputDirectory;
    std::string             m_LogFileName;

    bool                    m_LogToConsole;
    bool                    m_LogToFile;

    Image                   m_ResultImage;

};

// Procedural Interface 
SITKCommon_EXPORT Image Transformix( const Image& inputImage, const SimpleTransformix::ParameterMapType parameterMap, const bool logToConsole = false, const std::string outputDirectory = "." );
SITKCommon_EXPORT Image Transformix( const Image& inputImage, const SimpleTransformix::ParameterMapVectorType parameterMapVector, const bool logToConsole = false, const std::string outputDirectory = "." );

} // end namespace simple
} // end namespace itk

#endif // __sitksimpletransformix_h_