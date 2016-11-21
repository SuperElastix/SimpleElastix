#ifndef __sitksimpletransformiximpl_cxx_
#define __sitksimpletransformiximpl_cxx_

#include "sitkSimpleTransformix.h"
#include "sitkSimpleTransformixImpl.h"
#include "sitkCastImageFilter.h"

namespace itk {
  namespace simple {

SimpleTransformix::SimpleTransformixImpl
::SimpleTransformixImpl( void )
{
  // Register this class with SimpleITK
  this->m_MemberFactory.reset( new detail::MemberFunctionFactory< MemberFunctionType >( this ) );
  this->m_MemberFactory->RegisterMemberFunctions< FloatPixelIDTypeList, 2 >();
  this->m_MemberFactory->RegisterMemberFunctions< FloatPixelIDTypeList, 3 >();

#ifdef SITK_4D_IMAGES
  m_MemberFactory->RegisterMemberFunctions< FloatPixelIDTypeList, 4 >();
#endif

  this->m_MovingImage = Image();
  this->m_ResultImage = Image();

  this->m_TransformParameterMapVector = ParameterMapVectorType();

  this->m_ComputeSpatialJacobian = false;
  this->m_ComputeDeterminantOfSpatialJacobian = false;
  this->m_ComputeDeformationField = false;
  this->m_MovingPointSetFileName = "";

  this->m_OutputDirectory = "";
  this->m_LogFileName = "";
  
  this->m_LogToFile = "";
  this->m_LogToConsole = "";
}

SimpleTransformix::SimpleTransformixImpl
::~SimpleTransformixImpl( void )
{
}

Image
SimpleTransformix::SimpleTransformixImpl
::Execute( void )
{
  const PixelIDValueEnum MovingImagePixelEnum = this->m_MovingImage.GetPixelID();
  const unsigned int MovingImageDimension = this->m_MovingImage.GetDimension();

  if( this->m_MemberFactory->HasMemberFunction( sitkFloat32, MovingImageDimension ) )
  {
    return this->m_MemberFactory->GetMemberFunction( sitkFloat32, MovingImageDimension )();
  }

  sitkExceptionMacro( << "SimpleTransformix does not support the combination of image type "
                      << GetPixelIDValueAsElastixParameter( MovingImagePixelEnum ) << " and dimension "
                      << MovingImageDimension << ". This a serious error. "
                      << "Contact developers at https://github.com/kaspermarstal/SimpleElastix/issues." );
}

template< typename TMovingImage >
Image
SimpleTransformix::SimpleTransformixImpl
::ExecuteInternal( void )
{
  typedef elastix::TransformixFilter< TMovingImage > TransformixFilterType;
  typedef typename TransformixFilterType::Pointer TransforimxFilterPointer;

  try
  {
    TransforimxFilterPointer transformixFilter = TransformixFilterType::New();

    if( !this->IsEmpty( this->m_MovingImage ) ) {
      transformixFilter->SetMovingImage( itkDynamicCastInDebugMode< TMovingImage* >( Cast( this->GetMovingImage(), static_cast< PixelIDValueEnum >( GetPixelIDValueFromElastixString( "float" ) ) ).GetITKBase() ) );
    }

    transformixFilter->SetFixedPointSetFileName( this->GetFixedPointSetFileName() );
    transformixFilter->SetComputeSpatialJacobian( this->GetComputeSpatialJacobian() );
    transformixFilter->SetComputeDeterminantOfSpatialJacobian( this->GetComputeDeterminantOfSpatialJacobian() );
    transformixFilter->SetComputeDeformationField( this->GetComputeDeformationField() );

    transformixFilter->SetOutputDirectory( this->GetOutputDirectory() );
    transformixFilter->SetLogFileName( this->GetLogFileName() );
    transformixFilter->SetLogToFile( this->GetLogToFile() );
    transformixFilter->SetLogToConsole( this->GetLogToConsole() );

    ParameterMapVectorType transformParameterMapVector = this->m_TransformParameterMapVector;
    for( unsigned int i = 0; i < transformParameterMapVector.size(); i++ )
    {
      transformParameterMapVector[ i ][ "FixedInternalImagePixelType" ] = ParameterValueVectorType( 1, "float" );
      transformParameterMapVector[ i ][ "MovingInternalImagePixelType" ] = ParameterValueVectorType( 1, "float" );
    }

    ParameterObjectPointer parameterObject = ParameterObjectType::New();
    parameterObject->SetParameterMap( transformParameterMapVector );
    transformixFilter->SetTransformParameterObject( parameterObject );
    transformixFilter->Update();

    if( !this->IsEmpty( this->GetMovingImage() ) )
    {
      this->m_ResultImage = Image( itkDynamicCastInDebugMode< TMovingImage * >( transformixFilter->GetOutput() ) );
      this->m_ResultImage.MakeUnique();
    }
  }
  catch( itk::ExceptionObject &e )
  {
    sitkExceptionMacro( << e );
  }

  return this->m_ResultImage;
}

const std::string 
SimpleTransformix::SimpleTransformixImpl
::GetName( void )
{ 
  const std::string name = std::string( "SimpleTransformix" );
  return name;
}

void
SimpleTransformix::SimpleTransformixImpl
::SetMovingImage( const Image& movingImage )
{
  this->m_MovingImage = movingImage;
}

Image&
SimpleTransformix::SimpleTransformixImpl
::GetMovingImage( void )
{
  return this->m_MovingImage;
}

void
SimpleTransformix::SimpleTransformixImpl
::RemoveMovingImage( void )
{
  this->SetMovingImage( Image() );
}

void 
SimpleTransformix::SimpleTransformixImpl
::SetFixedPointSetFileName( const std::string movingPointSetFileName )
{
  this->m_MovingPointSetFileName = movingPointSetFileName;
}

std::string 
SimpleTransformix::SimpleTransformixImpl
::GetFixedPointSetFileName( void )
{
  return this->m_MovingPointSetFileName;
}

void
SimpleTransformix::SimpleTransformixImpl
::RemoveFixedPointSetFileName( void )
{
  this->m_MovingPointSetFileName = std::string();
}

void
SimpleTransformix::SimpleTransformixImpl
::SetComputeSpatialJacobian( const bool computeSpatialJacobian )
{
  this->m_ComputeSpatialJacobian = computeSpatialJacobian;
}

bool 
SimpleTransformix::SimpleTransformixImpl
::GetComputeSpatialJacobian( void )
{
  return this->m_ComputeSpatialJacobian;
}

void
SimpleTransformix::SimpleTransformixImpl
::ComputeSpatialJacobianOn( void )
{
  this->SetComputeSpatialJacobian( true );
  
}

void
SimpleTransformix::SimpleTransformixImpl
::ComputeSpatialJacobianOff( void )
{
  this->SetComputeSpatialJacobian( false );
}

void
SimpleTransformix::SimpleTransformixImpl
::SetComputeDeterminantOfSpatialJacobian( const bool computeDeterminantOfSpatialJacobian )
{
  this->m_ComputeDeterminantOfSpatialJacobian = computeDeterminantOfSpatialJacobian;
}

bool 
SimpleTransformix::SimpleTransformixImpl
::GetComputeDeterminantOfSpatialJacobian( void )
{
  return this->m_ComputeDeterminantOfSpatialJacobian;
}

void
SimpleTransformix::SimpleTransformixImpl
::ComputeDeterminantOfSpatialJacobianOn( void )
{
  this->SetComputeDeterminantOfSpatialJacobian( true );
}

void
SimpleTransformix::SimpleTransformixImpl
::ComputeDeterminantOfSpatialJacobianOff( void )
{
  this->SetComputeDeterminantOfSpatialJacobian( false );
  
}

void
SimpleTransformix::SimpleTransformixImpl
::SetComputeDeformationField( const bool computeDeformationField )
{
  this->m_ComputeDeformationField = computeDeformationField;
}

bool
SimpleTransformix::SimpleTransformixImpl
::GetComputeDeformationField( void )
{
  return this->m_ComputeDeformationField;
}

void
SimpleTransformix::SimpleTransformixImpl
::ComputeDeformationFieldOn( void )
{
  this->SetComputeDeformationField( true );
}

void
SimpleTransformix::SimpleTransformixImpl
::ComputeDeformationFieldOff( void )
{
  this->SetComputeDeformationField( false );
  
}

void 
SimpleTransformix::SimpleTransformixImpl
::SetOutputDirectory( const std::string outputDirectory )
{
  this->m_OutputDirectory = outputDirectory;
}

std::string
SimpleTransformix::SimpleTransformixImpl
::GetOutputDirectory( void )
{
  return this->m_OutputDirectory;
}

void 
SimpleTransformix::SimpleTransformixImpl
::RemoveOutputDirectory( void )
{
  this->m_OutputDirectory = std::string();
}

void 
SimpleTransformix::SimpleTransformixImpl
::SetLogFileName( std::string logFileName )
{
  this->m_LogFileName = logFileName;
}

std::string
SimpleTransformix::SimpleTransformixImpl
::GetLogFileName( void )
{
  return this->m_LogFileName;
}

void 
SimpleTransformix::SimpleTransformixImpl
::RemoveLogFileName( void )
{
  this->m_LogFileName = std::string();
}

void 
SimpleTransformix::SimpleTransformixImpl
::SetLogToFile( bool logToFile )
{
  this->m_LogToFile = logToFile;
  
}

bool
SimpleTransformix::SimpleTransformixImpl
::GetLogToFile( void )
{
  return this->m_LogToFile;
}

void 
SimpleTransformix::SimpleTransformixImpl
::LogToFileOn()
{
  this->SetLogToFile( true );
}

void 
SimpleTransformix::SimpleTransformixImpl
::LogToFileOff()
{
  this->SetLogToFile( false );
}

void 
SimpleTransformix::SimpleTransformixImpl
::SetLogToConsole( bool logToConsole )
{
  this->m_LogToConsole = logToConsole;
}

bool
SimpleTransformix::SimpleTransformixImpl
::GetLogToConsole( void )
{
  return this->m_LogToConsole;
}

void 
SimpleTransformix::SimpleTransformixImpl
::LogToConsoleOn()
{
  this->SetLogToConsole( true );
}

void 
SimpleTransformix::SimpleTransformixImpl
::LogToConsoleOff()
{
  this->SetLogToConsole( false );
}

void
SimpleTransformix::SimpleTransformixImpl
::SetTransformParameterMap( const ParameterMapVectorType parameterMapVector )
{
  this->m_TransformParameterMapVector = parameterMapVector;
}

void
SimpleTransformix::SimpleTransformixImpl
::SetTransformParameterMap( const ParameterMapType parameterMap )
{
  ParameterMapVectorType parameterMapVector;
  parameterMapVector.push_back( parameterMap );
  this->SetTransformParameterMap( parameterMapVector );
  
}

void
SimpleTransformix::SimpleTransformixImpl
::AddTransformParameterMap( const ParameterMapType parameterMap )
{
  this->m_TransformParameterMapVector.push_back( parameterMap );
}

SimpleTransformix::SimpleTransformixImpl::ParameterMapVectorType
SimpleTransformix::SimpleTransformixImpl
::GetTransformParameterMap( void )
{
  return this->m_TransformParameterMapVector;
}

unsigned int
SimpleTransformix::SimpleTransformixImpl
::GetNumberOfTransformParameterMaps( void )
{
  return this->m_TransformParameterMapVector.size();
}

void
SimpleTransformix::SimpleTransformixImpl
::SetTransformParameter( const ParameterKeyType key, const ParameterValueType value )
{
  for( unsigned int i = 0; i < this->m_TransformParameterMapVector.size(); i++ )
  {
    this->SetTransformParameter( i, key, value );
  }
}

void
SimpleTransformix::SimpleTransformixImpl
::SetTransformParameter( const ParameterKeyType key, const ParameterValueVectorType value )
{
  for( unsigned int i = 0; i < this->m_TransformParameterMapVector.size(); i++ )
  {
    this->SetTransformParameter( i, key, value );
  }
}

void
SimpleTransformix::SimpleTransformixImpl
::SetTransformParameter( const unsigned int index, const ParameterKeyType key, const ParameterValueType value )
{
  if( index >= this->m_TransformParameterMapVector.size() )
  {
    sitkExceptionMacro( "Parameter map index is out of range (index: " << index << "; number of transform parameters maps: " << this->m_TransformParameterMapVector.size() << "). Note that indexes are zero-based." );
  }

  this->m_TransformParameterMapVector[ index ][ key ] = ParameterValueVectorType( 1, value );
}

void
SimpleTransformix::SimpleTransformixImpl
::SetTransformParameter( const unsigned int index, const ParameterKeyType key, const ParameterValueVectorType value )
{
  if( index >= this->m_TransformParameterMapVector.size() )
  {
    sitkExceptionMacro( "Parameter map index is out of range (index: " << index << ", number of transform parameters maps: " << this->m_TransformParameterMapVector.size() << "). Note that indexes are zero-based." );
  }

  this->m_TransformParameterMapVector[ index ][ key ] = value;
}

void
SimpleTransformix::SimpleTransformixImpl
::AddTransformParameter( const ParameterKeyType key, const ParameterValueType value )
{
  for( unsigned int i = 0; i < this->m_TransformParameterMapVector.size(); i++ )
  {
    this->AddTransformParameter( i, key, value );
  }
}

void
SimpleTransformix::SimpleTransformixImpl
::AddTransformParameter( const unsigned int index, const ParameterKeyType key, const ParameterValueType value )
{
  if( index >= this->m_TransformParameterMapVector.size() )
  {
    sitkExceptionMacro( "Parameter map index is out of range (index: " << index << ", number of transform parameters maps: " << this->m_TransformParameterMapVector.size() << "). Note that indexes are zero-based." );
  }

  if( this->m_TransformParameterMapVector[ index ].find( key ) == this->m_TransformParameterMapVector[ index ].end() )
  {
    this->SetTransformParameter( index, key, value );
  }
  else
  {
    this->m_TransformParameterMapVector[ index ][ key ].push_back( value );
  }
}

SimpleTransformix::SimpleTransformixImpl::ParameterValueVectorType
SimpleTransformix::SimpleTransformixImpl
::GetTransformParameter( const ParameterKeyType key )
{
  if( this->m_TransformParameterMapVector.size() > 0 )
  {
    sitkExceptionMacro( "An index is needed when more than one transform parameter map is present. Please specify the parameter map number as the first argument." );
  }

  return this->GetTransformParameter( 0, key );
}

SimpleTransformix::SimpleTransformixImpl::ParameterValueVectorType
SimpleTransformix::SimpleTransformixImpl
::GetTransformParameter( const unsigned int index, const ParameterKeyType key )
{
  if( index >= this->m_TransformParameterMapVector.size() )
  {
    sitkExceptionMacro( "Parameter map index is out of range (index: " << index << ", number of transform parameters maps: " << this->m_TransformParameterMapVector.size() << "). Note that indexes are zero-based." );
  }

  return this->m_TransformParameterMapVector[ index ][ key ];
}

void
SimpleTransformix::SimpleTransformixImpl
::RemoveTransformParameter( const ParameterKeyType key )
{
  for( unsigned int i = 0; i < this->m_TransformParameterMapVector.size(); i++ )
  {
    this->RemoveTransformParameter( i, key );
  } 
}

void
SimpleTransformix::SimpleTransformixImpl
::RemoveTransformParameter( const unsigned int index, const ParameterKeyType key )
{
  if( index >= this->m_TransformParameterMapVector.size() )
  {
    sitkExceptionMacro( "Parameter map index is out of range (index: " << index << ", number of transform parameters maps: " << this->m_TransformParameterMapVector.size() << "). Note that indexes are zero-based." );
  }

  this->m_TransformParameterMapVector[ index ].erase( key );
}

SimpleTransformix::SimpleTransformixImpl::ParameterMapType 
SimpleTransformix::SimpleTransformixImpl
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

void
SimpleTransformix::SimpleTransformixImpl
::WriteParameterFile( const ParameterMapType parameterMap, const std::string parameterFileName )
{
  ParameterObjectPointer parameterObject = ParameterObjectType::New();
  parameterObject->WriteParameterFile( parameterMap, parameterFileName );
}

void
SimpleTransformix::SimpleTransformixImpl
::PrintParameterMap( void )
{
  this->PrintParameterMap( this->GetTransformParameterMap() );
}

void 
SimpleTransformix::SimpleTransformixImpl
::PrintParameterMap( const ParameterMapType parameterMap )
{
  ParameterMapVectorType parameterMapVector = ParameterMapVectorType( 1 );
  parameterMapVector[ 0 ] = parameterMap;
  this->PrintParameterMap( parameterMapVector );
}

void 
SimpleTransformix::SimpleTransformixImpl
::PrintParameterMap( const ParameterMapVectorType parameterMapVector )
{
  ParameterObjectPointer parameterObject = ParameterObjectType::New();
  parameterObject->SetParameterMap( parameterMapVector );
  parameterObject->Print( std::cout );
  
}

Image
SimpleTransformix::SimpleTransformixImpl
::GetResultImage( void )
{
  if( this->IsEmpty( this->m_ResultImage ) )
  {
    sitkExceptionMacro( "No result image was found. Has transformix run yet?" )
  }

  return this->m_ResultImage;
}


bool
SimpleTransformix::SimpleTransformixImpl
::IsEmpty( const Image& image )
{
  bool isEmpty = image.GetWidth() == 0 && image.GetHeight() == 0;
  return isEmpty;
}

} // end namespace simple
} // end namespace itk

#endif // __sitksimpletransformiximpl_cxx_