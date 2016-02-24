#ifndef __sitksimpleelastix_hxx_
#define __sitksimpleelastix_hxx_

#include "sitkSimpleElastix.h"

namespace itk {
  namespace simple {

template< typename TFixedImage, typename TMovingImage >
Image
SimpleElastix::DualExecuteInternal( void )
{
  typedef elastix::ElastixFilter< TFixedImage, TMovingImage > ElastixFilterType;
  typedef typename ElastixFilterType::Pointer ElastixFilterPointer;

  try
  {
    ElastixFilterPointer elastixFilter = ElastixFilterType::New();

    for( unsigned int i = 0; i < this->GetNumberOfFixedImages(); ++i )
    {
      elastixFilter->AddFixedImage( static_cast< TFixedImage* >( this->GetFixedImage( i ).GetITKBase() ) );
    }

    for( unsigned int i = 0; i < this->GetNumberOfMovingImages(); ++i )
    {
      elastixFilter->AddMovingImage( static_cast< TMovingImage* >( this->GetMovingImage( i ).GetITKBase() ) );
    }

    for( unsigned int i = 0; i < this->GetNumberOfFixedMasks(); ++i )
    {
      elastixFilter->AddFixedMask( static_cast< typename ElastixFilterType::FixedMaskType* >( this->GetFixedMask( i ).GetITKBase() ) );
    }

    for( unsigned int i = 0; i < this->GetNumberOfMovingMasks(); ++i )
    {
      elastixFilter->AddMovingMask( static_cast< typename ElastixFilterType::MovingMaskType* >( this->GetMovingMask( i ).GetITKBase() ) );
    }

    elastixFilter->SetInitialTransformParameterFileName( this->GetInitialTransformParameterFileName() );
    elastixFilter->SetFixedPointSetFileName( this->GetFixedPointSetFileName() );
    elastixFilter->SetMovingPointSetFileName( this->GetMovingPointSetFileName() );

    elastixFilter->SetOutputDirectory( this->GetOutputDirectory() );
    elastixFilter->SetLogFileName( this->GetLogFileName() );
    elastixFilter->SetLogToFile( this->GetLogToFile() );
    elastixFilter->SetLogToConsole( this->GetLogToConsole() );

    if( this->GetNumberOfParameterMaps() > 0 )
    {
      ParameterObjectPointer parameterObject = ParameterObjectType::New();
      parameterObject->SetParameterMap( this->m_ParameterMapVector );
      elastixFilter->SetParameterObject( parameterObject );
    }

    this->m_ResultImage = Image( elastixFilter->GetOutput() );
    this->m_TransformParameterMapVector = elastixFilter->GetTransformParameterObject()->GetParameterMap();
  }
  catch( itk::ExceptionObject &e )
  {
    sitkExceptionMacro( << e );
  }

  // Make a deep copy. This is important to prevent the internal data object trying to update its
  // source (this elastixFilter) outside this function (where it has gone out of scope and been destroyed).
  // TODO: We should be able to simply call DisconnectPipeline() on the ITK output image but this does not seem to work
  this->m_ResultImage.MakeUnique();

  return this->m_ResultImage;
}


} // end namespace simple
} // end namespace itk

#endif // __sitksimpleelastix_hxx_
