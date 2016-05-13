#ifndef __sitksimpleelastix_hxx_
#define __sitksimpleelastix_hxx_

#include "sitkSimpleElastix.h"

namespace itk {
  namespace simple {

template< typename TFixedImage, typename TMovingImage >
Image
SimpleElastix::DualExecuteInternal( void )
{
  typedef elastix::ElastixFilter< TFixedImage, TMovingImage >   ElastixFilterType;
  typedef typename ElastixFilterType::Pointer                   ElastixFilterPointer;
  typedef typename ElastixFilterType::FixedMaskType             FixedMaskType;
  typedef typename ElastixFilterType::MovingMaskType            MovingMaskType;

  try
  {
    ElastixFilterPointer elastixFilter = ElastixFilterType::New();

    for( unsigned int i = 0; i < this->GetNumberOfFixedImages(); ++i )
    {
      elastixFilter->AddFixedImage( itkDynamicCastInDebugMode< TFixedImage* >( this->GetFixedImage( i ).GetITKBase() ) );
    }

    for( unsigned int i = 0; i < this->GetNumberOfMovingImages(); ++i )
    {
      elastixFilter->AddMovingImage( itkDynamicCastInDebugMode< TMovingImage* >( this->GetMovingImage( i ).GetITKBase() ) );
    }

    for( unsigned int i = 0; i < this->GetNumberOfFixedMasks(); ++i )
    {
      elastixFilter->AddFixedMask( itkDynamicCastInDebugMode< FixedMaskType* >( this->GetFixedMask( i ).GetITKBase() ) );
    }

    for( unsigned int i = 0; i < this->GetNumberOfMovingMasks(); ++i )
    {
      elastixFilter->AddMovingMask( itkDynamicCastInDebugMode< MovingMaskType* >( this->GetMovingMask( i ).GetITKBase() ) );
    }

    elastixFilter->SetInitialTransformParameterFileName( this->GetInitialTransformParameterFileName() );

    elastixFilter->SetFixedPointSetFileName( this->GetFixedPointSetFileName() );
    elastixFilter->SetMovingPointSetFileName( this->GetMovingPointSetFileName() );

    elastixFilter->SetOutputDirectory( this->GetOutputDirectory() );
    elastixFilter->SetLogFileName( this->GetLogFileName() );
    elastixFilter->SetLogToFile( this->GetLogToFile() );
    elastixFilter->SetLogToConsole( this->GetLogToConsole() );

    ParameterObjectPointer parameterObject = ParameterObjectType::New();
    parameterObject->SetParameterMap( this->m_ParameterMapVector );
    elastixFilter->SetParameterObject( parameterObject );
    
    elastixFilter->Update();

    this->m_ResultImage = Image( elastixFilter->GetOutput() );
    this->m_ResultImage.MakeUnique();
    this->m_TransformParameterMapVector = elastixFilter->GetTransformParameterObject()->GetParameterMap();
  }
  catch( itk::ExceptionObject &e )
  {
    sitkExceptionMacro( << e );
  }

  return this->m_ResultImage;
}


} // end namespace simple
} // end namespace itk

#endif // __sitksimpleelastix_hxx_
