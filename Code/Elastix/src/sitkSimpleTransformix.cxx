#ifndef __sitksimpletransformix_cxx_
#define __sitksimpletransformix_cxx_

#include "sitkSimpleTransformix.h"
#include "sitkSimpleTransformix.hxx"

namespace itk {
  namespace simple {



SimpleTransformix
::SimpleTransformix( void )
{
  // Register this class with SimpleITK
  this->m_MemberFactory.reset( new detail::MemberFunctionFactory< MemberFunctionType >( this ) );
  this->m_MemberFactory->RegisterMemberFunctions< BasicPixelIDTypeList, 2 >();
  this->m_MemberFactory->RegisterMemberFunctions< BasicPixelIDTypeList, 3 >();

  #ifdef SITK_4D_IMAGES
    m_MemberFactory->RegisterMemberFunctions< BasicPixelIDTypeList, 4 >();
  #endif

  this->SetInputImage( Image() );

  this->ComputeSpatialJacobianOff();
  this->ComputeDeterminantOfSpatialJacobianOff();
  this->ComputeDeformationFieldOff();

  this->SetOutputDirectory( "" );
  this->SetLogFileName( "" );
  
  this->LogToFileOff();
  this->LogToConsoleOff();

  this->m_ResultImage = Image();
}

SimpleTransformix
::~SimpleTransformix( void )
{
}

const std::string 
SimpleTransformix
::GetName( void )
{ 
  const std::string name = std::string( "SimpleTransformix" );
  return name;
}

SimpleTransformix::Self&
SimpleTransformix
::SetInputImage( const Image& inputImage )
{
  this->m_InputImage = inputImage;
  return *this;
}

Image&
SimpleTransformix
::GetInputImage( void )
{
  return this->m_InputImage;
}

SimpleTransformix::Self& 
SimpleTransformix
::SetInputPointSetFileName( const std::string inputPointSetFileName )
{
  this->m_InputPointSetFileName = inputPointSetFileName;
  return *this;
}

std::string 
SimpleTransformix
::GetInputPointSetFileName( void )
{
  return this->m_InputPointSetFileName;
}

SimpleTransformix::Self&
SimpleTransformix
::RemoveInputPointSetFileName( void )
{
  this->m_InputPointSetFileName = std::string();
  return *this;
}

SimpleTransformix::Self&
SimpleTransformix
::SetComputeSpatialJacobian( const bool computeSpatialJacobian )
{
  this->m_ComputeSpatialJacobian = computeSpatialJacobian;
  return *this;
}

bool 
SimpleTransformix
::GetComputeSpatialJacobian( void )
{
  return this->m_ComputeSpatialJacobian;
}

SimpleTransformix::Self&
SimpleTransformix
::ComputeSpatialJacobianOn( void )
{
  this->SetComputeSpatialJacobian( true );
  return *this;
}

SimpleTransformix::Self&
SimpleTransformix
::ComputeSpatialJacobianOff( void )
{
  this->SetComputeSpatialJacobian( false );
  return *this;
}

SimpleTransformix::Self&
SimpleTransformix
::SetComputeDeterminantOfSpatialJacobian( const bool computeDeterminantOfSpatialJacobian )
{
  this->m_ComputeDeterminantOfSpatialJacobian = computeDeterminantOfSpatialJacobian;
  return *this;
}

bool 
SimpleTransformix
::GetComputeDeterminantOfSpatialJacobian( void )
{
  return this->m_ComputeDeterminantOfSpatialJacobian;
}

SimpleTransformix::Self&
SimpleTransformix
::ComputeDeterminantOfSpatialJacobianOn( void )
{
  this->SetComputeDeterminantOfSpatialJacobian( true );
  return *this;
}

SimpleTransformix::Self&
SimpleTransformix
::ComputeDeterminantOfSpatialJacobianOff( void )
{
  this->SetComputeDeterminantOfSpatialJacobian( false );
  return *this;
}

SimpleTransformix::Self&
SimpleTransformix
::SetComputeDeformationField( const bool computeDeformationField )
{
  this->m_ComputeDeformationField = computeDeformationField;
  return *this;
}

bool
SimpleTransformix
::GetComputeDeformationField( void )
{
  return this->m_ComputeDeformationField;
}

SimpleTransformix::Self&
SimpleTransformix
::ComputeDeformationFieldOn( void )
{
  this->SetComputeDeformationField( true );
  return *this;
}

SimpleTransformix::Self&
SimpleTransformix
::ComputeDeformationFieldOff( void )
{
  this->SetComputeDeformationField( false );
  return *this;
}

SimpleTransformix::Self& 
SimpleTransformix
::SetOutputDirectory( const std::string outputDirectory )
{
  this->m_OutputDirectory = outputDirectory;
  return *this;
}

std::string
SimpleTransformix
::GetOutputDirectory( void )
{
  return this->m_OutputDirectory;
}

SimpleTransformix::Self& 
SimpleTransformix
::RemoveOutputDirectory( void )
{
  this->m_OutputDirectory = std::string();
  return *this;
}

SimpleTransformix::Self& 
SimpleTransformix
::SetLogFileName( std::string logFileName )
{
  this->m_LogFileName = logFileName;
  return *this;
}

std::string
SimpleTransformix
::GetLogFileName( void )
{
  return this->m_LogFileName;
}

SimpleTransformix::Self& 
SimpleTransformix
::RemoveLogFileName( void )
{
  this->m_LogFileName = std::string();
  return *this;
}

SimpleTransformix::Self& 
SimpleTransformix
::SetLogToFile( bool logToFile )
{
  this->m_LogToFile = logToFile;
  return *this;
}

bool
SimpleTransformix
::GetLogToFile( void )
{
  return this->m_LogToFile;
}

SimpleTransformix::Self& 
SimpleTransformix
::LogToFileOn()
{
  this->SetLogToFile( true );
  return *this;
}

SimpleTransformix::Self& 
SimpleTransformix
::LogToFileOff()
{
  this->SetLogToFile( false );
  return *this;
}

SimpleTransformix::Self& 
SimpleTransformix
::SetLogToConsole( bool logToConsole )
{
  this->m_LogToConsole = logToConsole;
  return *this;
}

bool
SimpleTransformix
::GetLogToConsole( void )
{
  return this->m_LogToConsole;
}

SimpleTransformix::Self& 
SimpleTransformix
::LogToConsoleOn()
{
  this->SetLogToConsole( true );
  return *this;
}

SimpleTransformix::Self& 
SimpleTransformix
::LogToConsoleOff()
{
  this->SetLogToConsole( false );
  return *this;
}

SimpleTransformix::Self&
SimpleTransformix
::SetTransformParameterMap( const ParameterMapVectorType parameterMapVector )
{
  this->m_TransformParameterMapVector = parameterMapVector;
  return *this;
}

SimpleTransformix::Self&
SimpleTransformix
::SetTransformParameterMap( const ParameterMapType parameterMap )
{
  ParameterMapVectorType parameterMapVector;
  parameterMapVector.push_back( parameterMap );
  this->SetTransformParameterMap( parameterMapVector );
  return *this;
}

SimpleTransformix::Self&
SimpleTransformix
::AddTransformParameterMap( const ParameterMapType parameterMap )
{
  this->m_TransformParameterMapVector.push_back( parameterMap );
  return *this;
}

SimpleTransformix::ParameterMapVectorType
SimpleTransformix
::GetTransformParameterMap( void )
{
  return this->m_TransformParameterMapVector;
}

unsigned int
SimpleTransformix
::GetNumberOfTransformParameterMaps( void )
{
  return this->m_TransformParameterMapVector.size();
}


SimpleTransformix::ParameterMapType 
SimpleTransformix
::ReadParameterFile( const std::string filename )
{
  ParameterFileParserPointer parser = ParameterFileParserType::New();
  parser->SetParameterFileName( filename );
  try
  {
    parser->ReadParameterFile();
  }
  catch( itk::ExceptionObject &e )
  {
    std::cout << e.what() << std::endl;
  }

  return parser->GetParameterMap();
}

SimpleTransformix::Self&
SimpleTransformix
::WriteParameterFile( const ParameterMapType parameterMap, const std::string parameterFileName )
{
  ParameterObjectPointer parameterObject = ParameterObjectType::New();
  parameterObject->WriteParameterFile( parameterMap, parameterFileName );
  return *this;
}

SimpleTransformix::Self&
SimpleTransformix
::PrettyPrint( void )
{
  this->PrettyPrint( this->GetTransformParameterMap() );
  return *this;
}

SimpleTransformix::Self& 
SimpleTransformix
::PrettyPrint( const ParameterMapType parameterMap )
{
  ParameterMapVectorType parameterMapVector = ParameterMapVectorType( 1 );
  parameterMapVector[ 0 ] = parameterMap;
  this->PrettyPrint( parameterMapVector );
  return *this;
}

SimpleTransformix::Self& 
SimpleTransformix
::PrettyPrint( const ParameterMapVectorType parameterMapList )
{
  for( unsigned int i = 0; i < parameterMapList.size(); ++i )
  {
    std::cout << "ParameterMap " << i << ": " << std::endl;
    ParameterMapConstIterator parameterMapIterator = parameterMapList[ i ].begin();
    ParameterMapConstIterator parameterMapIteratorEnd = parameterMapList[ i ].end();
    while( parameterMapIterator != parameterMapIteratorEnd )
    {
      std::cout << "  (" << parameterMapIterator->first;
      ParameterValueVectorType parameterMapValueVector = parameterMapIterator->second;
      
      for(unsigned int j = 0; j < parameterMapValueVector.size(); ++j)
      {
        std::stringstream stream( parameterMapValueVector[ j ] );
        float number;
        stream >> number;
        if( stream.fail() ) {
           std::cout << " \"" << parameterMapValueVector[ j ] << "\"";
        }
        else
        {
          std::cout << " " << number;
        }      
      }
      
      std::cout << ")" << std::endl;
      parameterMapIterator++;
    }
  }

  return *this;
}

Image
SimpleTransformix
::Execute( void )
{
  const PixelIDValueEnum InputImagePixelEnum = this->m_InputImage.GetPixelID();
  const unsigned int InputImageDimension = this->m_InputImage.GetDimension();

  if( this->m_MemberFactory->HasMemberFunction( InputImagePixelEnum, InputImageDimension ) )
  {
    try {
      return this->m_MemberFactory->GetMemberFunction( InputImagePixelEnum, InputImageDimension )();
    } catch( itk::ExceptionObject &e ) {
      sitkExceptionMacro( << e );
    }
  }

  sitkExceptionMacro( << "SimpleTransformix does not support the combination of image type \""
                      << GetPixelIDValueAsString( InputImagePixelEnum ) << "\" ("
                      << GetPixelIDValueAsElastixParameter( InputImagePixelEnum ) << ") and dimension "
                      << InputImageDimension << "." );
}

Image
SimpleTransformix
::GetResultImage( void )
{
  if( this->IsEmpty( this->m_ResultImage ) )
  {
    sitkExceptionMacro( "No result image was found. Has transformix run yet?" )
  }

  return this->m_ResultImage;
}


bool
SimpleTransformix
::IsEmpty( const Image& image )
{
  bool isEmpty = image.GetWidth() == 0 && image.GetHeight() == 0;
  return isEmpty;
}

/**
 * Procedural interface 
 */

Image
Transformix( const Image& inputImage, const SimpleTransformix::ParameterMapType parameterMap, const bool logToConsole, const std::string outputDirectory )
{
  SimpleTransformix::ParameterMapVectorType parameterMapVector;
  parameterMapVector.push_back( parameterMap );
  return Transformix( inputImage, parameterMapVector, logToConsole, outputDirectory );
}

Image
Transformix( const Image& inputImage, const SimpleTransformix::ParameterMapVectorType parameterMapVector, const bool logToConsole, const std::string outputDirectory )
{
  SimpleTransformix stfx;
  stfx.SetInputImage( inputImage );
  stfx.SetTransformParameterMap( parameterMapVector );
  stfx.SetOutputDirectory( outputDirectory );
  stfx.LogToFileOn();
  stfx.SetLogToConsole( logToConsole );

  return stfx.Execute();
}

} // end namespace simple
} // end namespace itk

#endif // __sitksimpletransformix_cxx_