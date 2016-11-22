#ifndef __sitksimpleelastix_cxx_
#define __sitksimpleelastix_cxx_

#include "sitkSimpleElastix.h"
#include "sitkSimpleElastixImpl.h"

namespace itk {
  namespace simple {

SimpleElastix
::SimpleElastix( void ) : m_Pimple( new SimpleElastixImpl )
{
}

SimpleElastix
::~SimpleElastix( void )
{
  delete m_Pimple;
  m_Pimple = NULL;
}

const std::string 
SimpleElastix
::GetName( void )
{ 
  return this->m_Pimple->GetName();
}

SimpleElastix::Self& 
SimpleElastix
::SetFixedImage( const Image& fixedImage )
{
  this->m_Pimple->SetFixedImage( fixedImage );
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::SetFixedImage( const VectorOfImage& fixedImages )
{
  this->m_Pimple->SetFixedImage( fixedImages );
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::AddFixedImage( const Image& fixedImage )
{
  this->m_Pimple->AddFixedImage( fixedImage );
  return *this;
}

Image&
SimpleElastix
::GetFixedImage( const unsigned long index )
{
  return this->m_Pimple->GetFixedImage( index );
}

SimpleElastix::VectorOfImage&
SimpleElastix
::GetFixedImage( void )
{
  return this->m_Pimple->GetFixedImage();
}

SimpleElastix::Self& 
SimpleElastix
::RemoveFixedImage( const unsigned long index )
{
  this->m_Pimple->RemoveFixedImage( index );
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::RemoveFixedImage( void )
{
  this->m_Pimple->RemoveFixedImage();
  return *this;
}

unsigned int
SimpleElastix
::GetNumberOfFixedImages( void )
{
  return this->m_Pimple->GetNumberOfFixedImages();
}

SimpleElastix::Self& 
SimpleElastix
::SetMovingImage( const Image& movingImage )
{
  this->m_Pimple->SetMovingImage( movingImage );
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::SetMovingImage( const VectorOfImage& movingImages )
{
  this->m_Pimple->SetMovingImage( movingImages );
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::AddMovingImage( const Image& movingImage )
{
  this->m_Pimple->AddMovingImage( movingImage );
  return *this;
}

Image&
SimpleElastix
::GetMovingImage( const unsigned long index )
{
  return this->m_Pimple->GetMovingImage( index );
}

SimpleElastix::VectorOfImage&
SimpleElastix
::GetMovingImage( void )
{
  return this->m_Pimple->GetMovingImage();
}

SimpleElastix::Self& 
SimpleElastix
::RemoveMovingImage( const unsigned long index )
{
  this->m_Pimple->RemoveMovingImage( index );
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::RemoveMovingImage( void )
{
  this->m_Pimple->RemoveMovingImage();
  return *this;
}

unsigned int
SimpleElastix
::GetNumberOfMovingImages( void )
{
  return this->m_Pimple->GetNumberOfMovingImages();
}

SimpleElastix::Self& 
SimpleElastix
::SetFixedMask( const Image& fixedMask )
{
  this->m_Pimple->SetFixedMask( fixedMask );
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::SetFixedMask( const VectorOfImage& fixedMasks )
{
  this->m_Pimple->SetFixedMask( fixedMasks );
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::AddFixedMask( const Image& fixedMask )
{
  this->m_Pimple->AddFixedMask( fixedMask );
  return *this;
}

Image&
SimpleElastix
::GetFixedMask( const unsigned long index )
{
  return this->m_Pimple->GetFixedMask( index );
}

SimpleElastix::VectorOfImage&
SimpleElastix
::GetFixedMask( void )
{
  return this->m_Pimple->GetFixedMask();
}

SimpleElastix::Self& 
SimpleElastix
::RemoveFixedMask( const unsigned long index )
{
  this->m_Pimple->RemoveFixedMask( index );
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::RemoveFixedMask( void )
{
  this->m_Pimple->RemoveFixedMask();
  return *this;
}

unsigned int
SimpleElastix
::GetNumberOfFixedMasks( void )
{
  return this->m_Pimple->GetNumberOfFixedMasks();
}

SimpleElastix::Self& 
SimpleElastix
::SetMovingMask( const Image& movingMask )
{
  this->m_Pimple->SetMovingMask( movingMask );
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::SetMovingMask( const VectorOfImage& movingMasks )
{
  this->m_Pimple->SetMovingMask( movingMasks );
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::AddMovingMask( const Image& movingMask )
{
  this->m_Pimple->AddMovingMask( movingMask );
  return *this;
}

Image&
SimpleElastix
::GetMovingMask( const unsigned long index )
{
  return this->m_Pimple->GetMovingMask( index );
}

SimpleElastix::VectorOfImage&
SimpleElastix
::GetMovingMask( void )
{
  return this->m_Pimple->GetMovingMask();
}

SimpleElastix::Self& 
SimpleElastix
::RemoveMovingMask( const unsigned long index )
{
  this->m_Pimple->RemoveMovingMask( index );
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::RemoveMovingMask( void )
{
  this->m_Pimple->RemoveMovingMask();
  return *this;
}

unsigned int
SimpleElastix
::GetNumberOfMovingMasks( void )
{
  return this->m_Pimple->GetNumberOfMovingMasks();
}

SimpleElastix::Self& 
SimpleElastix
::SetFixedPointSetFileName( const std::string fixedPointSetFileName )
{
  this->m_Pimple->SetFixedPointSetFileName( fixedPointSetFileName );
  return *this;
}

std::string
SimpleElastix
::GetFixedPointSetFileName( void )
{
  return this->m_Pimple->GetFixedPointSetFileName();
}

SimpleElastix::Self& 
SimpleElastix
::RemoveFixedPointSetFileName( void )
{
  this->m_Pimple->RemoveFixedPointSetFileName();
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::SetMovingPointSetFileName( const std::string movingPointSetFileName )
{
  this->m_Pimple->SetMovingPointSetFileName( movingPointSetFileName );
  return *this;
}

std::string
SimpleElastix
::GetMovingPointSetFileName( void )
{
  return this->m_Pimple->GetMovingPointSetFileName();
}

SimpleElastix::Self& 
SimpleElastix
::RemoveMovingPointSetFileName( void )
{
  this->m_Pimple->RemoveMovingImage();
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::SetOutputDirectory( const std::string outputDirectory )
{
  this->m_Pimple->SetOutputDirectory( outputDirectory );
  return *this;
}

std::string
SimpleElastix
::GetOutputDirectory( void )
{
  return this->m_Pimple->GetOutputDirectory();
}

SimpleElastix::Self& 
SimpleElastix
::RemoveOutputDirectory( void )
{
  this->m_Pimple->RemoveOutputDirectory();
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::SetLogFileName( std::string logFileName )
{
  this->m_Pimple->SetLogFileName( logFileName );
  return *this;
}

std::string
SimpleElastix
::GetLogFileName( void )
{
  return this->m_Pimple->GetLogFileName();
}

SimpleElastix::Self& 
SimpleElastix
::RemoveLogFileName( void )
{
  this->m_Pimple->RemoveLogFileName();
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::SetLogToFile( bool logToFile )
{
  this->m_Pimple->SetLogToFile( logToFile );
  return *this;
}

bool
SimpleElastix
::GetLogToFile( void )
{
  return this->m_Pimple->GetLogToFile();
}

SimpleElastix::Self& 
SimpleElastix
::LogToFileOn()
{
  this->m_Pimple->LogToFileOn();
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::LogToFileOff()
{
  this->m_Pimple->LogToFileOff();
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::SetLogToConsole( bool logToConsole )
{
  this->m_Pimple->SetLogToConsole( logToConsole );
  return *this;
}

bool
SimpleElastix
::GetLogToConsole( void )
{
  return this->m_Pimple->GetLogToConsole();
}

SimpleElastix::Self& 
SimpleElastix
::LogToConsoleOn()
{
  this->m_Pimple->LogToConsoleOn();
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::LogToConsoleOff()
{
  this->m_Pimple->LogToConsoleOff();
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::SetParameterMap( const std::string transformName, const unsigned int numberOfResolutions, const double finalGridSpacingInPhysicalUnits )
{
  this->m_Pimple->SetParameterMap( transformName, numberOfResolutions, finalGridSpacingInPhysicalUnits );
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::SetParameterMap( const ParameterMapType parameterMap )
{
  this->m_Pimple->SetParameterMap( parameterMap );
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::SetParameterMap( const ParameterMapVectorType parameterMapVector )
{
  this->m_Pimple->SetParameterMap( parameterMapVector );
  return *this;
}

SimpleElastix::Self& 
SimpleElastix
::AddParameterMap( const ParameterMapType parameterMap )
{
  this->m_Pimple->AddParameterMap( parameterMap );
  return *this;
}

SimpleElastix::ParameterMapVectorType 
SimpleElastix
::GetParameterMap( void )
{
  return this->m_Pimple->GetParameterMap();
}

unsigned int 
SimpleElastix
::GetNumberOfParameterMaps( void )
{
  return this->m_Pimple->GetNumberOfParameterMaps();
}

SimpleElastix::Self&
SimpleElastix
::SetInitialTransformParameterFileName( const std::string initialTransformParameterFileName )
{
  this->m_Pimple->SetInitialTransformParameterFileName( initialTransformParameterFileName );
  return *this;
}

std::string
SimpleElastix
::GetInitialTransformParameterFileName( void )
{
  return this->m_Pimple->GetInitialTransformParameterFileName();
}

SimpleElastix::Self&
SimpleElastix
::RemoveInitialTransformParameterFileName( void )
{
  this->m_Pimple->RemoveInitialTransformParameterFileName();
  return *this;
}

SimpleElastix::Self&
SimpleElastix
::SetParameter( const ParameterKeyType key, const ParameterValueType value )
{
  this->m_Pimple->SetParameter( key, value );
  return *this;
}

SimpleElastix::Self&
SimpleElastix
::SetParameter( const ParameterKeyType key, const ParameterValueVectorType value )
{
  this->m_Pimple->SetParameter( key, value );
  return *this;
}

SimpleElastix::Self&
SimpleElastix
::SetParameter( const unsigned int index, const ParameterKeyType key, const ParameterValueType value )
{
  this->m_Pimple->SetParameter( index, key, value );
  return *this;
}

SimpleElastix::Self&
SimpleElastix
::SetParameter( const unsigned int index, const ParameterKeyType key, const ParameterValueVectorType value )
{
  this->m_Pimple->SetParameter( index, key, value );
  return *this;
}

SimpleElastix::Self&
SimpleElastix
::AddParameter( const ParameterKeyType key, const ParameterValueType value )
{
  this->m_Pimple->AddParameter( key, value );
  return *this;
}

SimpleElastix::Self&
SimpleElastix
::AddParameter( const ParameterKeyType key, const ParameterValueVectorType value )
{
  this->m_Pimple->AddParameter( key, value );
  return *this;
}

SimpleElastix::Self&
SimpleElastix
::AddParameter( const unsigned int index, const ParameterKeyType key, const ParameterValueType value )
{
  this->m_Pimple->AddParameter( index, key, value );
  return *this;
}

SimpleElastix::Self&
SimpleElastix
::AddParameter( const unsigned int index, const ParameterKeyType key, const ParameterValueVectorType value )
{
  this->m_Pimple->AddParameter( index, key, value );
  return *this;
}

SimpleElastix::ParameterValueVectorType
SimpleElastix
::GetParameter( const ParameterKeyType key )
{
  return this->m_Pimple->GetParameter( key );
}

SimpleElastix::ParameterValueVectorType
SimpleElastix
::GetParameter( const unsigned int index, const ParameterKeyType key )
{
  return this->m_Pimple->GetParameter( index, key );
}

SimpleElastix::Self&
SimpleElastix
::RemoveParameter( const ParameterKeyType key )
{
  this->m_Pimple->RemoveParameter( key );
  return *this;
}

SimpleElastix::Self&
SimpleElastix
::RemoveParameter( const unsigned int index, const ParameterKeyType key )
{
  this->m_Pimple->RemoveParameter( index, key );
  return *this;
}

SimpleElastix::ParameterMapType
SimpleElastix
::ReadParameterFile( const std::string fileName )
{
  return this->m_Pimple->ReadParameterFile( fileName );
}

SimpleElastix::Self&
SimpleElastix
::WriteParameterFile( ParameterMapType const parameterMap, const std::string parameterFileName )
{
  this->m_Pimple->WriteParameterFile( parameterMap, parameterFileName);
  return *this;
}

SimpleElastix::ParameterMapType
SimpleElastix
::GetDefaultParameterMap( const std::string transformName, const unsigned int numberOfResolutions, const double finalGridSpacingInPhysicalUnits )
{ 
  return this->m_Pimple->GetDefaultParameterMap( transformName, numberOfResolutions, finalGridSpacingInPhysicalUnits );
}

Image
SimpleElastix
::Execute( void )
{
  return this->m_Pimple->Execute();
}

SimpleElastix::ParameterMapVectorType 
SimpleElastix
::GetTransformParameterMap( void )
{
  return this->m_Pimple->GetTransformParameterMap();
}

SimpleElastix::ParameterMapType 
SimpleElastix
::GetTransformParameterMap( const unsigned int index )
{
  return this->m_Pimple->GetTransformParameterMap( index );
}

Image
SimpleElastix
::GetResultImage( void )
{
  return this->m_Pimple->GetResultImage();
}

SimpleElastix::ParameterMapVectorType
SimpleElastix
::ExecuteInverse( void )
{
  return this->m_Pimple->ExecuteInverse();
}

SimpleElastix::ParameterMapVectorType
SimpleElastix
::ExecuteInverse( std::map< std::string, std::vector< std::string > > inverseParameterMap )
{
  return this->m_Pimple->ExecuteInverse( ParameterMapVectorType( 1, inverseParameterMap ) );
}

SimpleElastix::ParameterMapVectorType
SimpleElastix
::ExecuteInverse( std::vector< std::map< std::string, std::vector< std::string > > > inverseParameterMapVector )
{
  return this->m_Pimple->ExecuteInverse( inverseParameterMapVector );
}

SimpleElastix::ParameterMapVectorType 
SimpleElastix
::GetInverseTransformParameterMap( void )
{
  return this->m_Pimple->GetInverseTransformParameterMap();
}

SimpleElastix::Self&
SimpleElastix
::PrintParameterMap( void )
{
  this->m_Pimple->PrintParameterMap();
  return *this;
}

SimpleElastix::Self&
SimpleElastix
::PrintParameterMap( const ParameterMapType parameterMap )
{
  this->m_Pimple->PrintParameterMap( parameterMap );
  return *this;
}

SimpleElastix::Self&
SimpleElastix
::PrintParameterMap( const ParameterMapVectorType parameterMapVector )
{
  this->m_Pimple->PrintParameterMap( parameterMapVector );
  return *this;
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
PrintParameterMap( const SimpleElastix::ParameterMapType parameterMap )
{
  SimpleElastix::ParameterMapVectorType parameterMapVector = SimpleElastix::ParameterMapVectorType( 1, parameterMap );
  PrintParameterMap( parameterMapVector );
}

void
PrintParameterMap( const SimpleElastix::ParameterMapVectorType parameterMapVector )
{
  SimpleElastix selx;
  selx.SetParameterMap( parameterMapVector );
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