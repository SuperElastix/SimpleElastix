#ifndef __sitksimpletransformix_cxx_
#define __sitksimpletransformix_cxx_

#include "sitkSimpleTransformix.h"
#include "sitkSimpleTransformixImpl.h"

namespace itk {
  namespace simple {

SimpleTransformix
::SimpleTransformix( void ) : m_Pimple( new SimpleTransformixImpl )
{
}

SimpleTransformix
::~SimpleTransformix( void )
{
}

const std::string 
SimpleTransformix
::GetName( void )
{ 
  return this->m_Pimple->GetName();
}

SimpleTransformix::Self&
SimpleTransformix
::SetMovingImage( const Image& movingImage )
{
  this->m_Pimple->SetMovingImage( movingImage );
  return *this;
}

Image&
SimpleTransformix
::GetMovingImage( void )
{
  return this->m_Pimple->GetMovingImage();
}

SimpleTransformix::Self&
SimpleTransformix
::RemoveMovingImage( void )
{
  this->m_Pimple->RemoveMovingImage();
  return *this;
}

SimpleTransformix::Self& 
SimpleTransformix
::SetFixedPointSetFileName( const std::string movingPointSetFileName )
{
  this->m_Pimple->SetFixedPointSetFileName( movingPointSetFileName );
  return *this;
}

std::string 
SimpleTransformix
::GetFixedPointSetFileName( void )
{
  return this->m_Pimple->GetFixedPointSetFileName();
}

SimpleTransformix::Self&
SimpleTransformix
::RemoveFixedPointSetFileName( void )
{
  this->m_Pimple->RemoveFixedPointSetFileName();
  return *this;
}

SimpleTransformix::Self&
SimpleTransformix
::SetComputeSpatialJacobian( const bool computeSpatialJacobian )
{
  this->m_Pimple->SetComputeSpatialJacobian( computeSpatialJacobian );
  return *this;
}

bool 
SimpleTransformix
::GetComputeSpatialJacobian( void )
{
  return this->m_Pimple->GetComputeSpatialJacobian();
}

SimpleTransformix::Self&
SimpleTransformix
::ComputeSpatialJacobianOn( void )
{
  this->m_Pimple->SetComputeSpatialJacobian( true );
  return *this;
}

SimpleTransformix::Self&
SimpleTransformix
::ComputeSpatialJacobianOff( void )
{
  this->m_Pimple->SetComputeSpatialJacobian( false );
  return *this;
}

SimpleTransformix::Self&
SimpleTransformix
::SetComputeDeterminantOfSpatialJacobian( const bool computeDeterminantOfSpatialJacobian )
{
  this->m_Pimple->SetComputeDeterminantOfSpatialJacobian( computeDeterminantOfSpatialJacobian );
  return *this;
}

bool 
SimpleTransformix
::GetComputeDeterminantOfSpatialJacobian( void )
{
  return this->m_Pimple->GetComputeDeterminantOfSpatialJacobian();
}

SimpleTransformix::Self&
SimpleTransformix
::ComputeDeterminantOfSpatialJacobianOn( void )
{
  this->m_Pimple->SetComputeDeterminantOfSpatialJacobian( true );
  return *this;
}

SimpleTransformix::Self&
SimpleTransformix
::ComputeDeterminantOfSpatialJacobianOff( void )
{
  this->m_Pimple->SetComputeDeterminantOfSpatialJacobian( false );
  return *this;
}

SimpleTransformix::Self&
SimpleTransformix
::SetComputeDeformationField( const bool computeDeformationField )
{
  this->m_Pimple->SetComputeDeformationField( computeDeformationField );
  return *this;
}

bool
SimpleTransformix
::GetComputeDeformationField( void )
{
  return this->m_Pimple->GetComputeDeformationField();
}

SimpleTransformix::Self&
SimpleTransformix
::ComputeDeformationFieldOn( void )
{
  this->m_Pimple->SetComputeDeformationField( true );
  return *this;
}

SimpleTransformix::Self&
SimpleTransformix
::ComputeDeformationFieldOff( void )
{
  this->m_Pimple->SetComputeDeformationField( false );
  return *this;
}

SimpleTransformix::Self& 
SimpleTransformix
::SetOutputDirectory( const std::string outputDirectory )
{
  this->m_Pimple->SetOutputDirectory( outputDirectory );
  return *this;
}

std::string
SimpleTransformix
::GetOutputDirectory( void )
{
  return this->m_Pimple->GetOutputDirectory();
}

SimpleTransformix::Self& 
SimpleTransformix
::RemoveOutputDirectory( void )
{
  this->m_Pimple->RemoveOutputDirectory();
  return *this;
}

SimpleTransformix::Self& 
SimpleTransformix
::SetLogFileName( std::string logFileName )
{
  this->m_Pimple->SetLogFileName( logFileName );
  return *this;
}

std::string
SimpleTransformix
::GetLogFileName( void )
{
  return this->m_Pimple->GetLogFileName();
}

SimpleTransformix::Self& 
SimpleTransformix
::RemoveLogFileName( void )
{
  this->m_Pimple->RemoveLogFileName();
  return *this;
}

SimpleTransformix::Self& 
SimpleTransformix
::SetLogToFile( bool logToFile )
{
  this->m_Pimple->SetLogToFile( logToFile );
  return *this;
}

bool
SimpleTransformix
::GetLogToFile( void )
{
  return this->m_Pimple->GetLogToFile();
}

SimpleTransformix::Self& 
SimpleTransformix
::LogToFileOn()
{
  this->m_Pimple->SetLogToFile( true );
  return *this;
}

SimpleTransformix::Self& 
SimpleTransformix
::LogToFileOff()
{
  this->m_Pimple->SetLogToFile( false );
  return *this;
}

SimpleTransformix::Self& 
SimpleTransformix
::SetLogToConsole( bool logToConsole )
{
  this->m_Pimple->SetLogToConsole( logToConsole );
  return *this;
}

bool
SimpleTransformix
::GetLogToConsole( void )
{
  return this->m_Pimple->GetLogToConsole();
}

SimpleTransformix::Self& 
SimpleTransformix
::LogToConsoleOn()
{
  this->m_Pimple->SetLogToConsole( true );
  return *this;
}

SimpleTransformix::Self& 
SimpleTransformix
::LogToConsoleOff()
{
  this->m_Pimple->SetLogToConsole( false );
  return *this;
}

SimpleTransformix::Self&
SimpleTransformix
::SetTransformParameterMap( const ParameterMapVectorType transformParameterMapVector )
{
  this->m_Pimple->SetTransformParameterMap( transformParameterMapVector );
  return *this;
}

SimpleTransformix::Self&
SimpleTransformix
::SetTransformParameterMap( const ParameterMapType transformParameterMap )
{
  this->m_Pimple->SetTransformParameterMap( transformParameterMap );
  return *this;
}

SimpleTransformix::Self&
SimpleTransformix
::AddTransformParameterMap( const ParameterMapType transformParameterMap )
{
  this->m_Pimple->AddTransformParameterMap( transformParameterMap );
  return *this;
}

SimpleTransformix::ParameterMapVectorType
SimpleTransformix
::GetTransformParameterMap( void )
{
  return this->m_Pimple->GetTransformParameterMap();
}

unsigned int
SimpleTransformix
::GetNumberOfTransformParameterMaps( void )
{
  return this->m_Pimple->GetNumberOfTransformParameterMaps();
}

SimpleTransformix::Self&
SimpleTransformix
::SetTransformParameter( const ParameterKeyType key, const ParameterValueType value )
{
  this->m_Pimple->SetTransformParameter( key, value );
  return *this;
}

SimpleTransformix::Self&
SimpleTransformix
::SetTransformParameter( const ParameterKeyType key, const ParameterValueVectorType value )
{
  this->m_Pimple->SetTransformParameter( key, value );
  return *this;
}

SimpleTransformix::Self&
SimpleTransformix
::SetTransformParameter( const unsigned int index, const ParameterKeyType key, const ParameterValueType value )
{
  this->m_Pimple->SetTransformParameter( index, key, value );
  return *this;
}

SimpleTransformix::Self&
SimpleTransformix
::SetTransformParameter( const unsigned int index, const ParameterKeyType key, const ParameterValueVectorType value )
{
  this->m_Pimple->SetTransformParameter( index, key, value );
  return *this;
}

SimpleTransformix::Self&
SimpleTransformix
::AddTransformParameter( const ParameterKeyType key, const ParameterValueType value )
{
  this->m_Pimple->AddTransformParameter( key, value );
  return *this;
}

SimpleTransformix::Self&
SimpleTransformix
::AddTransformParameter( const unsigned int index, const ParameterKeyType key, const ParameterValueType value )
{
  this->m_Pimple->AddTransformParameter( index, key, value );
  return *this;
}

SimpleTransformix::ParameterValueVectorType
SimpleTransformix
::GetTransformParameter( const ParameterKeyType key )
{
  return this->m_Pimple->GetTransformParameter( key );
}

SimpleTransformix::ParameterValueVectorType
SimpleTransformix
::GetTransformParameter( const unsigned int index, const ParameterKeyType key )
{
  return this->m_Pimple->GetTransformParameter( index, key );
}

SimpleTransformix::Self&
SimpleTransformix
::RemoveTransformParameter( const ParameterKeyType key )
{
  this->m_Pimple->RemoveTransformParameter( key );
  return *this;
}

SimpleTransformix::Self&
SimpleTransformix
::RemoveTransformParameter( const unsigned int index, const ParameterKeyType key )
{
  this->m_Pimple->RemoveTransformParameter( index, key );
  return *this;
}

SimpleTransformix::ParameterMapType 
SimpleTransformix
::ReadParameterFile( const std::string parameterFileName )
{
  return this->m_Pimple->ReadParameterFile( parameterFileName );
}

SimpleTransformix::Self&
SimpleTransformix
::WriteParameterFile( const ParameterMapType parameterMap, const std::string parameterFileName )
{
  this->m_Pimple->WriteParameterFile( parameterMap, parameterFileName );
  return *this;
}

SimpleTransformix::Self&
SimpleTransformix
::PrintParameterMap( void )
{
  this->m_Pimple->PrintParameterMap();
  return *this;
}

SimpleTransformix::Self& 
SimpleTransformix
::PrintParameterMap( const ParameterMapType parameterMap )
{
  this->m_Pimple->PrintParameterMap( parameterMap );
  return *this;
}

SimpleTransformix::Self& 
SimpleTransformix
::PrintParameterMap( const ParameterMapVectorType parameterMapVector )
{
  this->m_Pimple->PrintParameterMap( parameterMapVector );
  return *this;
}

Image
SimpleTransformix
::Execute( void )
{
  return this->m_Pimple->Execute();
}

Image
SimpleTransformix
::GetResultImage( void )
{
  return this->m_Pimple->GetResultImage();
}

/**
 * Procedural interface 
 */

Image
Transformix( const Image& movingImage, const SimpleTransformix::ParameterMapType parameterMap, const bool logToConsole, const std::string outputDirectory )
{
  SimpleTransformix::ParameterMapVectorType parameterMapVector;
  parameterMapVector.push_back( parameterMap );
  return Transformix( movingImage, parameterMapVector, logToConsole, outputDirectory );
}

Image
Transformix( const Image& movingImage, const SimpleTransformix::ParameterMapVectorType parameterMapVector, const bool logToConsole, const std::string outputDirectory )
{
  SimpleTransformix stfx;
  stfx.SetMovingImage( movingImage );
  stfx.SetTransformParameterMap( parameterMapVector );
  stfx.SetOutputDirectory( outputDirectory );
  stfx.LogToFileOn();
  stfx.SetLogToConsole( logToConsole );

  return stfx.Execute();
}

} // end namespace simple
} // end namespace itk

#endif // __sitksimpletransformix_cxx_