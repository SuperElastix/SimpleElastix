#ifndef __sitksimpleelastix_cxx_
#define __sitksimpleelastix_cxx_

#include "sitkSimpleElastix.h"
#include "sitkSimpleElastix.hxx"

namespace itk {
  namespace simple {

SimpleElastix
::SimpleElastix( void )
{
  // Register this class with SimpleITK
  this->m_DualMemberFactory.reset( new detail::DualMemberFunctionFactory< MemberFunctionType >( this ) );
  this->m_DualMemberFactory->RegisterMemberFunctions< BasicPixelIDTypeList, BasicPixelIDTypeList, 2 >();
  this->m_DualMemberFactory->RegisterMemberFunctions< BasicPixelIDTypeList, BasicPixelIDTypeList, 3 >();

  #ifdef SITK_4D_IMAGES
    this->m_DualMemberFactory->RegisterMemberFunctions< BasicPixelIDTypeList, BasicPixelIDTypeList, 4 >();
  #endif
 
  m_FixedImages                 = VectorOfImage();
  m_MovingImages                = VectorOfImage();
  m_FixedMasks                  = VectorOfImage();
  m_MovingMasks                 = VectorOfImage();

  m_ParameterMapVector          = ParameterMapVectorType();
  m_TransformParameterMapVector = ParameterMapVectorType();

  m_FixedPointSetFileName       = std::string();
  m_MovingPointSetFileName      = std::string();

  m_OutputDirectory             = ".";
  m_LogFileName                 = std::string();

  this->LogToFileOff();
  this->LogToConsoleOff();

  m_ResultImage                 = Image();

  ParameterObjectPointer defaultParameterObject = ParameterObjectType::New();
  defaultParameterObject->AddParameterMap( "translation" );
  defaultParameterObject->AddParameterMap( "affine" );
  defaultParameterObject->AddParameterMap( "bspline" );
  this->SetParameterMap( defaultParameterObject->GetParameterMap() );
}

SimpleElastix
::~SimpleElastix( void )
{
}

const std::string 
SimpleElastix
::GetName( void )
{ 
  const std::string name = "SimpleElastix";
  return name;
}

SimpleElastix::Self& 
SimpleElastix
::SetFixedImage( const Image& fixedImage )
{
  if( this->IsEmpty( fixedImage ) )
  {
    sitkExceptionMacro( "Image is empty." )
  }

  this->RemoveFixedImage();
  this->m_FixedImages.push_back( fixedImage );
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::SetFixedImage( const VectorOfImage& fixedImages )
{
  if( fixedImages.size() == 0u )
  {
    sitkExceptionMacro( "Cannot set fixed images from empty vector" );
  }

  this->RemoveFixedImage();
  this->m_FixedImages = fixedImages;

  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::AddFixedImage( const Image& fixedImage )
{
  if( this->IsEmpty( fixedImage ) )
  {
    sitkExceptionMacro( "Image is empty." )
  }

  this->m_FixedImages.push_back( fixedImage );
  return *this;
}

Image&
SimpleElastix
::GetFixedImage( const unsigned long index )
{
  if( index < this->m_FixedImages.size() )
  {
    return this->m_FixedImages[ index ];
  }

  sitkExceptionMacro( "Index out of range (index: " << index << ", number of fixed images: " << this->m_FixedImages.size() << ")" );
}

SimpleElastix::VectorOfImage&
SimpleElastix
::GetFixedImage( void )
{
  return this->m_FixedImages;
}

SimpleElastix::Self& 
SimpleElastix
::RemoveFixedImage( const unsigned long index )
{
  if( index < this->m_FixedImages.size() )
  {
    this->m_FixedImages.erase( this->m_FixedImages.begin() + index );
    return *this;
  }

  sitkExceptionMacro( "Index out of range (index: " << index << ", number of fixed images: " << this->m_FixedImages.size() << ")" );
}

SimpleElastix::Self& 
SimpleElastix
::RemoveFixedImage( void )
{
  this->m_FixedImages.clear();
  return *this;
}

unsigned int
SimpleElastix
::GetNumberOfFixedImages( void )
{
  return this->m_FixedImages.size();
}

SimpleElastix::Self& 
SimpleElastix
::SetMovingImage( const Image& movingImage )
{
  if( this->IsEmpty( movingImage ) )
  {
    sitkExceptionMacro( "Image is empty." )
  }

  this->RemoveMovingImage();
  this->m_MovingImages.push_back( movingImage );
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::SetMovingImage( const VectorOfImage& movingImages )
{
  if( movingImages.size() == 0u )
  {
    sitkExceptionMacro( "Cannot set moving images from empty vector" );
  }

  this->RemoveFixedImage();
  this->m_MovingImages = movingImages;

  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::AddMovingImage( const Image& movingImage )
{
  if( this->IsEmpty( movingImage ) )
  {
    sitkExceptionMacro( "Image is empty." )
  }

  this->m_MovingImages.push_back( movingImage );
  return *this;
}

Image&
SimpleElastix
::GetMovingImage( const unsigned long index )
{
  if( index < this->m_MovingImages.size() )
  {
    return this->m_MovingImages[ index ];
  }
  
  sitkExceptionMacro( "Index out of range (index: " << index << ", number of moving images: " << this->m_MovingImages.size() << ")" );
}

SimpleElastix::VectorOfImage&
SimpleElastix
::GetMovingImage( void )
{
  return this->m_MovingImages;
}

SimpleElastix::Self& 
SimpleElastix
::RemoveMovingImage( const unsigned long index )
{
  if( index < this->m_MovingImages.size() )
  {
    this->m_MovingImages.erase( this->m_MovingImages.begin() + index );
    return *this;
  }

  sitkExceptionMacro( "Index out of range (index: " << index << ", number of moving images: " << this->m_MovingImages.size() << ")" );
}

SimpleElastix::Self& 
SimpleElastix
::RemoveMovingImage( void )
{
  this->m_MovingImages.clear();
  return *this;
}

unsigned int
SimpleElastix
::GetNumberOfMovingImages( void )
{
  return this->m_MovingImages.size();
}

SimpleElastix::Self& 
SimpleElastix
::SetFixedMask( const Image& fixedMask )
{
  if( this->IsEmpty( fixedMask ) )
  {
    sitkExceptionMacro( "Image is empty." )
  }

  this->RemoveFixedMask();
  this->m_FixedMasks.push_back( fixedMask );
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::SetFixedMask( const VectorOfImage& fixedMasks )
{
  if( fixedMasks.size() == 0u )
  {
    sitkExceptionMacro( "Cannot set fixed images from empty vector" );
  }

  this->RemoveFixedMask();
  this->m_FixedMasks = fixedMasks;

  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::AddFixedMask( const Image& fixedMask )
{
  if( this->IsEmpty( fixedMask ) )
  {
    sitkExceptionMacro( "Image is empty." )
  }

  this->m_FixedMasks.push_back( fixedMask );
  return *this;
}

Image&
SimpleElastix
::GetFixedMask( const unsigned long index )
{
  if( index < this->m_FixedMasks.size() )
  {
    return this->m_FixedMasks[ index ];
  }

  sitkExceptionMacro( "Index out of range (index: " << index << ", number of fixed masks: " << this->m_FixedMasks.size() << ")" );
}

SimpleElastix::VectorOfImage&
SimpleElastix
::GetFixedMask( void )
{
  return this->m_FixedMasks;
}

SimpleElastix::Self& 
SimpleElastix
::RemoveFixedMask( const unsigned long index )
{
  if( index < this->m_FixedMasks.size()  )
  {
    this->m_FixedMasks.erase( this->m_FixedMasks.begin() + index );
    return *this;
  }

  sitkExceptionMacro( "Index out of range (index: " << index << ", number of fixed masks: " << this->m_FixedMasks.size() << ")" );
}

SimpleElastix::Self& 
SimpleElastix
::RemoveFixedMask( void )
{
  this->m_FixedMasks.clear();
  return *this;
}

unsigned int
SimpleElastix
::GetNumberOfFixedMasks( void )
{
  return this->m_FixedMasks.size();
}

SimpleElastix::Self& 
SimpleElastix
::SetMovingMask( const Image& movingMask )
{
  if( this->IsEmpty( movingMask ) )
  {
    sitkExceptionMacro( "Image is empty." )
  }

  this->RemoveMovingMask();
  this->m_MovingMasks.push_back( movingMask );
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::SetMovingMask( const VectorOfImage& movingMasks )
{
  if( movingMasks.size() == 0u )
  {
    sitkExceptionMacro( "Cannot set moving masks from empty vector" );
  }

  this->RemoveMovingMask();
  this->m_MovingMasks = movingMasks;

  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::AddMovingMask( const Image& movingMask )
{
  if( this->IsEmpty( movingMask ) )
  {
    sitkExceptionMacro( "Image is empty." )
  }

  this->m_MovingMasks.push_back( movingMask );
  return *this;
}

Image&
SimpleElastix
::GetMovingMask( const unsigned long index )
{
  if( index < this->m_MovingMasks.size()  )
  {
    return this->m_MovingMasks[ index ];
  }

  sitkExceptionMacro( "Index out of range (index: " << index << ", number of moving masks: " << this->m_MovingMasks.size() << ")" );
}

SimpleElastix::VectorOfImage&
SimpleElastix
::GetMovingMask( void )
{
  return this->m_MovingMasks;
}

SimpleElastix::Self& 
SimpleElastix
::RemoveMovingMask( const unsigned long index )
{
  if( index < this->m_MovingMasks.size()  )
  {
    this->m_MovingMasks.erase( this->m_MovingMasks.begin() + index );
    return *this;
  }

  sitkExceptionMacro( "Index out of range (index: " << index << ", number of moving masks: " << this->m_MovingMasks.size() << ")" );
}

SimpleElastix::Self& 
SimpleElastix
::RemoveMovingMask( void )
{
  this->m_MovingMasks.clear();
  return *this;
}

unsigned int
SimpleElastix
::GetNumberOfMovingMasks( void )
{
  return this->m_MovingMasks.size();
}

SimpleElastix::Self& 
SimpleElastix
::SetFixedPointSetFileName( const std::string fixedPointSetFileName )
{
  this->m_FixedPointSetFileName = fixedPointSetFileName;
  return *this;
}

std::string
SimpleElastix
::GetFixedPointSetFileName( void )
{
  return this->m_FixedPointSetFileName;
}

SimpleElastix::Self& 
SimpleElastix
::RemoveFixedPointSetFileName( void )
{
  this->m_FixedPointSetFileName = std::string();
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::SetMovingPointSetFileName( const std::string movingPointSetFileName )
{
  this->m_MovingPointSetFileName = movingPointSetFileName;
  return *this;
}

std::string
SimpleElastix
::GetMovingPointSetFileName( void )
{
  return this->m_MovingPointSetFileName;
}

SimpleElastix::Self& 
SimpleElastix
::RemoveMovingPointSetFileName( void )
{
  this->m_MovingPointSetFileName = std::string();
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::SetOutputDirectory( const std::string outputDirectory )
{
  this->m_OutputDirectory = outputDirectory;
  return *this;
}

std::string
SimpleElastix
::GetOutputDirectory( void )
{
  return this->m_OutputDirectory;
}

SimpleElastix::Self& 
SimpleElastix
::RemoveOutputDirectory( void )
{
  this->m_OutputDirectory = std::string();
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::SetLogFileName( std::string logFileName )
{
  this->m_LogFileName = logFileName;
  return *this;
}

std::string
SimpleElastix
::GetLogFileName( void )
{
  return this->m_LogFileName;
}

SimpleElastix::Self& 
SimpleElastix
::RemoveLogFileName( void )
{
  this->m_LogFileName = std::string();
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::SetLogToFile( bool logToFile )
{
  this->m_LogToFile = logToFile;
  return *this;
}

bool
SimpleElastix
::GetLogToFile( void )
{
  return this->m_LogToFile;
}

SimpleElastix::Self& 
SimpleElastix
::LogToFileOn()
{
  this->SetLogToFile( true );
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::LogToFileOff()
{
  this->SetLogToFile( false );
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::SetLogToConsole( bool logToConsole )
{
  this->m_LogToConsole = logToConsole;
  return *this;
}

bool
SimpleElastix
::GetLogToConsole( void )
{
  return this->m_LogToConsole;
}

SimpleElastix::Self& 
SimpleElastix
::LogToConsoleOn()
{
  this->SetLogToConsole( true );
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::LogToConsoleOff()
{
  this->SetLogToConsole( false );
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::SetParameterMap( const std::string transformName, const unsigned int numberOfResolutions, const double finalGridSpacingInPhysicalUnits )
{
  ParameterObjectPointer parameterObject = ParameterObjectType::New();
  ParameterMapType parameterMap = parameterObject->GetParameterMap( transformName, numberOfResolutions, finalGridSpacingInPhysicalUnits );
  this->SetParameterMap( parameterMap );
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::SetParameterMap( const ParameterMapType parameterMap )
{
  ParameterMapVectorType parameterMapVector = ParameterMapVectorType( 1 );
  parameterMapVector[ 0 ] = parameterMap;
  this->SetParameterMap( parameterMapVector );
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::SetParameterMap( const ParameterMapVectorType parameterMapVector )
{
  this->m_ParameterMapVector = parameterMapVector;
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::AddParameterMap( const ParameterMapType parameterMap )
{
  this->m_ParameterMapVector.push_back( parameterMap );
  return *this;
}

SimpleElastix::ParameterMapVectorType 
SimpleElastix
::GetParameterMap( void )
{
  return this->m_ParameterMapVector;
}

unsigned int 
SimpleElastix
::GetNumberOfParameterMaps( void )
{
  return this->m_ParameterMapVector.size();
}

SimpleElastix::Self&
SimpleElastix
::SetInitialTransformParameterFileName( const std::string initialTransformParameterFileName )
{
  this->m_InitialTransformParameterMapFileName = initialTransformParameterFileName;
  return *this;
}

std::string
SimpleElastix
::GetInitialTransformParameterFileName( void )
{
  return m_InitialTransformParameterMapFileName ;
}

SimpleElastix::Self&
SimpleElastix
::RemoveInitialTransformParameterFileName( void )
{
  this->m_InitialTransformParameterMapFileName = "";
  return *this;
}

SimpleElastix::Self&
SimpleElastix
::SetParameter( const ParameterKeyType key, const ParameterValueType value )
{
  for( unsigned int i = 0; i < this->m_ParameterMapVector.size(); i++ )
  {
    this->SetParameter( i, key, value );
  }

  return *this;
}

SimpleElastix::Self&
SimpleElastix
::SetParameter( const ParameterKeyType key, const ParameterValueVectorType value )
{
  for( unsigned int i = 0; i < this->m_ParameterMapVector.size(); i++ )
  {
    this->SetParameter( i, key, value );
  }

  return *this;
}

SimpleElastix::Self&
SimpleElastix
::SetParameter( const unsigned int index, const ParameterKeyType key, const ParameterValueType value )
{
  if( index >= this->m_ParameterMapVector.size() )
  {
    sitkExceptionMacro( "Parameter map index is out of range (index: " << index << "; number of parameters maps: " << this->m_ParameterMapVector.size() << "). Note that indexes are zero-based." );
  }

  this->m_ParameterMapVector[ index ][ key ] = ParameterValueVectorType( 1, value );

  return *this;
}

SimpleElastix::Self&
SimpleElastix
::SetParameter( const unsigned int index, const ParameterKeyType key, const ParameterValueVectorType value )
{
  if( index >= this->m_ParameterMapVector.size() )
  {
    sitkExceptionMacro( "Parameter map index is out of range (index: " << index << ", number of parameters maps: " << this->m_ParameterMapVector.size() << "). Note that indexes are zero-based." );
  }

  this->m_ParameterMapVector[ index ][ key ] = value;

  return *this;
}

SimpleElastix::Self&
SimpleElastix
::AddParameter( const ParameterKeyType key, const ParameterValueType value )
{
  for( unsigned int i = 0; i < this->m_ParameterMapVector.size(); i++ )
  {
    this->AddParameter( i, key, value );
  }

  return *this;
}

SimpleElastix::Self&
SimpleElastix
::AddParameter( const ParameterKeyType key, const ParameterValueVectorType value )
{
  for( unsigned int i = 0; i < this->m_ParameterMapVector.size(); i++ )
  {
    this->AddParameter( i, key, value );
  }

  return *this;
}

SimpleElastix::Self&
SimpleElastix
::AddParameter( const unsigned int index, const ParameterKeyType key, const ParameterValueType value )
{
  if( index >= this->m_ParameterMapVector.size() )
  {
    sitkExceptionMacro( "Parameter map index is out of range (index: " << index << ", number of parameters maps: " << this->m_ParameterMapVector.size() << "). Note that indexes are zero-based." );
  }

  if( this->m_ParameterMapVector[ index ].find( key ) == this->m_ParameterMapVector[ index ].end() )
  {
    this->SetParameter( index, key, value );
  }
  else
  {
    this->m_ParameterMapVector[ index ][ key ].push_back( value );
  }

  return *this;
}

SimpleElastix::Self&
SimpleElastix
::AddParameter( const unsigned int index, const ParameterKeyType key, const ParameterValueVectorType value )
{
  if( index >= this->m_ParameterMapVector.size() )
  {
    sitkExceptionMacro( "Parameter map index is out of range (index: " << index << ", number of parameters maps: " << this->m_ParameterMapVector.size() << "). Note that indexes are zero-based." );
  }

  if( this->m_ParameterMapVector[ index ].find( key ) == this->m_ParameterMapVector[ index ].end() )
  {
    this->SetParameter( index, key, value );
  }
  else
  {
    for( unsigned int i = 0; i < value.size(); i++ )
    {
      this->m_ParameterMapVector[ index ][ key ].push_back( value[ i ] );
    }
  }

  return *this;
}

SimpleElastix::ParameterValueVectorType
SimpleElastix
::GetParameter( const ParameterKeyType key )
{
  if( this->m_ParameterMapVector.size() > 0 )
  {
    sitkExceptionMacro( "An index is needed when more than one parameter map is present. Please specify the parameter map number as the first argument." );
  }

  return this->GetParameter( 0, key );
}

SimpleElastix::ParameterValueVectorType
SimpleElastix
::GetParameter( const unsigned int index, const ParameterKeyType key )
{
  if( index >= this->m_ParameterMapVector.size() )
  {
    sitkExceptionMacro( "Parameter map index is out of range (index: " << index << ", number of parameters maps: " << this->m_ParameterMapVector.size() << "). Note that indexes are zero-based." );
  }

  return this->m_ParameterMapVector[ index ][ key ];
}

SimpleElastix::Self&
SimpleElastix
::RemoveParameter( const ParameterKeyType key )
{
  for( unsigned int i = 0; i < this->m_ParameterMapVector.size(); i++ )
  {
    this->RemoveParameter( i, key );
  }

  return *this;
}

SimpleElastix::Self&
SimpleElastix
::RemoveParameter( const unsigned int index, const ParameterKeyType key )
{
  if( index >= this->m_ParameterMapVector.size() )
  {
    sitkExceptionMacro( "Parameter map index is out of range (index: " << index << ", number of parameters maps: " << this->m_ParameterMapVector.size() << "). Note that indexes are zero-based." );
  }

  this->m_ParameterMapVector[ index ].erase( key );

  return *this;
}

SimpleElastix::ParameterMapType
SimpleElastix
::ReadParameterFile( const std::string fileName )
{
  ParameterObjectPointer parameterObject = ParameterObjectType::New();
  parameterObject->ReadParameterFile( fileName );
  return parameterObject->GetParameterMap( 0 );
}

SimpleElastix::Self&
SimpleElastix
::WriteParameterFile( ParameterMapType const parameterMap, const std::string parameterFileName )
{
  ParameterObjectPointer parameterObject = ParameterObjectType::New();
  parameterObject->WriteParameterFile( parameterMap, parameterFileName );
  return *this;
}

SimpleElastix::ParameterMapType
SimpleElastix
::GetDefaultParameterMap( const std::string transformName, const unsigned int numberOfResolutions, const double finalGridSpacingInPhysicalUnits )
{ 
  SimpleElastix::ParameterObjectPointer parameterObject = SimpleElastix::ParameterObjectType::New();
  return parameterObject->GetParameterMap( transformName, numberOfResolutions, finalGridSpacingInPhysicalUnits );
}

SimpleElastix::Self&
SimpleElastix
::PrettyPrint( void )
{
  this->PrettyPrint( this->GetParameterMap() );
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::PrettyPrint( const ParameterMapType parameterMap )
{
  ParameterMapVectorType parameterMapVector = ParameterMapVectorType( 1 );
  parameterMapVector[ 0 ] = parameterMap;
  this->PrettyPrint( parameterMapVector );
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
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
SimpleElastix
::Execute( void )
{
  if( this->GetNumberOfFixedImages() == 0 )
  {
    sitkExceptionMacro( "Fixed image not set." );
  }

  if( this->GetNumberOfMovingImages() == 0 )
  {
    sitkExceptionMacro( "Moving image not set." );
  }

  for( unsigned int i = 0; i < this->GetNumberOfFixedMasks(); ++i )
  {
    const PixelIDValueEnum FixedMaskPixelID = this->GetFixedMask( i ).GetPixelID();
    if( FixedMaskPixelID != sitkUInt8 )
    {
      sitkExceptionMacro( "Fixed mask must be of pixel type unsigned char (fixed mask at index " << i << " is of type " << GetPixelIDValueAsElastixParameter( FixedMaskPixelID ) << ")." );
    }
  }

  for( unsigned int i = 0; i < this->GetNumberOfMovingMasks(); ++i )
  {
    const PixelIDValueEnum MovingMaskPixelID = this->GetMovingMask( i ).GetPixelID();
    if( MovingMaskPixelID != sitkUInt8 )
    {
      sitkExceptionMacro( "Moving mask must be of pixel type unsigned char (moving mask at index " << i << " is of type " << GetPixelIDValueAsElastixParameter( MovingMaskPixelID ) << ")." );
    }
  }

  const PixelIDValueEnum FixedImagePixelID = this->GetFixedImage( 0 ).GetPixelID();
  const unsigned int FixedImageDimension = this->GetFixedImage( 0 ).GetDimension();
  const PixelIDValueEnum MovingImagePixelID = this->GetMovingImage( 0 ).GetPixelID();
  const unsigned int MovingImageDimension = this->GetMovingImage( 0 ).GetDimension();
  if( this->m_DualMemberFactory->HasMemberFunction( FixedImagePixelID, MovingImagePixelID, FixedImageDimension ) )
  {
    return this->m_DualMemberFactory->GetMemberFunction( FixedImagePixelID, MovingImagePixelID, FixedImageDimension )();
  }

  sitkExceptionMacro( << "SimpleElastix does not support the combination of "
                      << FixedImageDimension << "-dimensional "
                      << GetPixelIDValueAsElastixParameter( FixedImagePixelID ) << " fixed image and a "
                      << MovingImageDimension << "-dimensional " 
                      << GetPixelIDValueAsElastixParameter( FixedImagePixelID ) << " moving image." )
}

SimpleElastix::ParameterMapVectorType 
SimpleElastix
::GetTransformParameterMap( void )
{
  if( this->m_TransformParameterMapVector.size() == 0 )
  {
    sitkExceptionMacro( "Number of transform parameter maps: 0. Run registration with Execute()." );
  }

  return this->m_TransformParameterMapVector;
}

Image
SimpleElastix
::GetResultImage( void )
{
  if( this->IsEmpty( this->m_ResultImage ) )
  {
    sitkExceptionMacro( "No result image found. Run registration with Execute()." )
  }

  return this->m_ResultImage;
}

// SimpleElastix::ParameterMapVectorType
// SimpleElastix
// ::ExecuteInverse( void )
// {
//   if( this->GetFixedImage().size() == 0 )
//   {
//     sitkExceptionMacro( "No fixed images found. Elastix needs the fixed image of the forward transformation to compute the inverse transform.")
//   }

//   if( this->m_TransformParameterMapVector.size() == 0 )
//   {
//     sitkExceptionMacro( "No forward transform parameter map found. Run forward registration before computing the inverse.")
//   }

//   // Write forward transform parameter file to disk
//   ParameterMapVectorType forwardTransformParameterMaps = this->m_TransformParameterMapVector;
//   std::vector< std::string > forwardTransformParameterFileNames;
//   for( unsigned int i = 0; i < forwardTransformParameterMaps.size(); i++ )
//   {
//     ParameterObjectPointer forwardTransformParameterMapObject = ParameterObjectType::New();

//     if( i > 0 )
//     {
//       // Chain transform parameter file
//       forwardTransformParameterFileNames.push_back( this->GetOutputDirectory() + "/forwardTransformParameterFile." + forwardTransformParameterMapObject->ToString( i-1 ) + ".txt" );
//       forwardTransformParameterMaps[ i ][ "InitialTransformParametersFileName" ] = ParameterValueVectorType( 1, forwardTransformParameterFileNames[ forwardTransformParameterFileNames.size()-1 ] );
//     }
//     else
//     { 
//       // Head of chain
//       forwardTransformParameterFileNames.push_back( this->GetOutputDirectory() + "/forwardTransformParameterFile." + forwardTransformParameterMapObject->ToString( i ) + ".txt" );
//       forwardTransformParameterMaps[ i ][ "InitialTransformParametersFileName" ] = ParameterValueVectorType( 1, "NoInitialTransform" );
//     }

//     forwardTransformParameterMapObject->SetParameterMap( forwardTransformParameterMaps[ i ] );
//     forwardTransformParameterMapObject->WriteParameterFile( forwardTransformParameterFileNames[ i ] );
//   }

//   // Setup inverse transform parameter map
//   ParameterMapVectorType inverseParameterMap = this->m_ParameterMapVector;
//   for( unsigned int i = 0; i < inverseParameterMap.size(); i++ )
//   {
//     inverseParameterMap[ i ][ "Registration" ] = ParameterValueVectorType( 1, "MultiResolutionRegistration" );
//     inverseParameterMap[ i ][ "Metric" ] = ParameterValueVectorType( 1, "DisplacementMagnitudePenalty" );
//   }

//   // Setup inverse registration
//   SimpleElastix selx;
//   selx.SetInitialTransformParameterFileName( forwardTransformParameterFileNames[ 0 ] );
//   selx.SetParameterMap( inverseParameterMap );  

//   // Pass options from this SimpleElastix
//   selx.SetFixedImage( this->GetFixedImage( 0 ) ); 
//   selx.SetMovingImage( this->GetFixedImage( 0 ) ); // <-- The fixed image is also used as the moving image. This is not a bug.
//   selx.SetOutputDirectory( this->GetOutputDirectory() );
//   selx.SetLogFileName( this->GetLogFileName() );
//   selx.SetLogToFile( this->GetLogToFile() );
//   selx.SetLogToConsole( this->GetLogToConsole() );
//   selx.Execute();

//   for( unsigned int i = 0; i < forwardTransformParameterFileNames.size(); i++ )
//   {
//     // TODO: Delete forward transform parameter files on disk
//   }

//   // Unlink the first transform parameter map
//   ParameterMapVectorType inverseTransformParameterMap = selx.GetTransformParameterMap();
//   inverseTransformParameterMap[ 0 ][ "InitialTransformParametersFileName" ] = ParameterValueVectorType( 1, "NoInitialTransform" );
//   this->m_InverseTransformParameterMapVector = inverseTransformParameterMap;
//   return this->m_InverseTransformParameterMapVector;
// }

// SimpleElastix::ParameterMapVectorType 
// SimpleElastix
// ::GetInverseTransformParameterMap( void )
// {
//   if( this->m_InverseTransformParameterMapVector.size() == 0 )
//   {
//     sitkExceptionMacro( "Number of inverse transform parameter maps: 0. Run inverse registration with ExecuteInverse()." );
//   }

//   return this->m_InverseTransformParameterMapVector;
// }

bool
SimpleElastix
::IsEmpty( const Image& image )
{
  const bool isEmpty = image.GetWidth() == 0 && image.GetHeight() == 0;
  return isEmpty;
}

/**
 * Procedural interface 
 */

SimpleElastix::ParameterMapType
GetDefaultParameterMap( std::string transform, const unsigned int numberOfResolutions, const double finalGridSpacingInPhysicalUnits )
{
  SimpleElastix selx;
  SimpleElastix::ParameterMapType parameterMap = selx.GetDefaultParameterMap( transform, numberOfResolutions, finalGridSpacingInPhysicalUnits );
  return parameterMap;
}

SimpleElastix::ParameterMapType
ReadParameterFile( const std::string fileName )
{
  SimpleElastix selx;
  SimpleElastix::ParameterMapType parameterMap = selx.ReadParameterFile( fileName );
  return parameterMap;
}

void
WriteParameterFile( const SimpleElastix::ParameterMapType parameterMap, const std::string filename )
{
  SimpleElastix selx;
  selx.WriteParameterFile( parameterMap, filename );
}

void 
PrettyPrint( const SimpleElastix::ParameterMapType parameterMap )
{
  SimpleElastix::ParameterMapVectorType parameterMapVector = SimpleElastix::ParameterMapVectorType( 1, parameterMap );
  PrettyPrint( parameterMapVector );
}

void
PrettyPrint( const SimpleElastix::ParameterMapVectorType parameterMapVector )
{
  SimpleElastix selx;
  selx.PrettyPrint( parameterMapVector );
}

Image
Elastix( const Image& fixedImage, const Image& movingImage, const bool logToConsole, const bool logToFile, const std::string outputDirectory )
{
  SimpleElastix selx;
  selx.SetFixedImage( fixedImage );
  selx.SetMovingImage( movingImage );
  selx.SetLogToFile( logToFile );
  selx.SetLogToConsole( logToConsole );
  selx.SetOutputDirectory( outputDirectory );

  return selx.Execute();
}

Image
Elastix( const Image& fixedImage, const Image& movingImage, const Image& fixedMask, const Image& movingMask, const bool logToConsole, const bool logToFile, const std::string outputDirectory )
{
  SimpleElastix selx;
  selx.SetFixedImage( fixedImage );
  selx.SetMovingImage( movingImage );
  selx.SetFixedMask( fixedMask );
  selx.SetMovingMask( movingMask );
  selx.SetLogToFile( logToFile );
  selx.SetLogToConsole( logToConsole );
  selx.SetOutputDirectory( outputDirectory );

  return selx.Execute();
}

Image
Elastix( const Image& fixedImage, const Image& movingImage, const std::string defaultParameterMapName, const bool logToConsole, const bool logToFile, const std::string outputDirectory )
{
  return Elastix( fixedImage, movingImage, GetDefaultParameterMap( defaultParameterMapName ), logToConsole, logToFile, outputDirectory );
}

Image
Elastix( const Image& fixedImage, const Image& movingImage, const SimpleElastix::ParameterMapType parameterMap, const bool logToConsole, const bool logToFile, const std::string outputDirectory )
{
  SimpleElastix::ParameterMapVectorType parameterMapVector = SimpleElastix::ParameterMapVectorType( 1, parameterMap );
  return Elastix( fixedImage, movingImage, parameterMapVector, logToConsole, logToFile, outputDirectory );
}

Image
Elastix( const Image& fixedImage, const Image& movingImage, const SimpleElastix::ParameterMapVectorType parameterMapVector, const bool logToConsole, const bool logToFile, const std::string outputDirectory )
{
  SimpleElastix selx;
  selx.SetFixedImage( fixedImage );
  selx.SetMovingImage( movingImage );
  selx.SetParameterMap( parameterMapVector );
  selx.SetLogToFile( logToFile );
  selx.SetLogToConsole( logToConsole );
  selx.SetOutputDirectory( outputDirectory );

  return selx.Execute();
}

Image
Elastix( const Image& fixedImage, const Image& movingImage, const std::string defaultParameterMapName, const Image& fixedMask, const Image& movingMask, const bool logToConsole, const bool logToFile, const std::string outputDirectory )
{
  return Elastix( fixedImage, movingImage, GetDefaultParameterMap( defaultParameterMapName ), fixedMask, movingMask, logToConsole, logToFile, outputDirectory );
}

Image
Elastix( const Image& fixedImage, const Image& movingImage, const SimpleElastix::ParameterMapType parameterMap, const Image& fixedMask, const Image& movingMask, bool logToConsole, const bool logToFile, std::string outputDirectory )
{
  SimpleElastix::ParameterMapVectorType parameterMapVector = SimpleElastix::ParameterMapVectorType( 1, parameterMap );
  return Elastix( fixedImage, movingImage, parameterMapVector, fixedMask, movingMask, logToConsole, logToFile, outputDirectory );
}

Image
Elastix( const Image& fixedImage, const Image& movingImage, SimpleElastix::ParameterMapVectorType parameterMapVector, const Image& fixedMask, const Image& movingMask, bool logToConsole, const bool logToFile, std::string outputDirectory )
{
  SimpleElastix selx;
  selx.SetFixedImage( fixedImage );
  selx.SetMovingImage( movingImage );
  selx.SetParameterMap( parameterMapVector );
  selx.SetFixedMask( fixedMask );
  selx.SetMovingMask( movingMask );
  selx.SetLogToFile( logToFile );
  selx.SetLogToConsole( logToConsole );
  selx.SetOutputDirectory( outputDirectory );

  return selx.Execute();
}

} // end namespace simple
} // end namespace itk

#endif // __sitksimpleelastix_cxx_