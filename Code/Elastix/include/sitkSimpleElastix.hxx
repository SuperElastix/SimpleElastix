#ifndef __sitksimpleelastix_hxx_
#define __sitksimpleelastix_hxx_

#include "sitkCastImageFilter.h"

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
      elastixFilter->AddFixedImage( itkDynamicCastInDebugMode< TFixedImage* >( Cast( this->GetFixedImage( i ), sitkFloat32 ).GetITKBase() ) );
    }

    for( unsigned int i = 0; i < this->GetNumberOfMovingImages(); ++i )
    {
      elastixFilter->AddMovingImage( itkDynamicCastInDebugMode< TMovingImage* >( Cast( this->GetMovingImage( i ), sitkFloat32 ).GetITKBase() ) );
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

    ParameterMapVectorType parameterMapVector = this->m_ParameterMapVector;
    for( unsigned int i = 0; i < parameterMapVector.size(); i++ )
    {
      parameterMapVector[ i ][ "FixedInternalImagePixelType" ] 
        = ParameterValueVectorType( 1, "float" );
      parameterMapVector[ i ][ "MovingInternalImagePixelType" ]
        = ParameterValueVectorType( 1, "float" );
      parameterMapVector[ i ][ "ResultImagePixelType" ]
        = ParameterValueVectorType( 1, "float" );
    }

    ParameterObjectPointer parameterObject = ParameterObjectType::New();
    parameterObject->SetParameterMap( parameterMapVector );
    elastixFilter->SetParameterObject( parameterObject );
    
    elastixFilter->Update();

    this->m_ResultImage = Image( itkDynamicCastInDebugMode< TFixedImage * >( elastixFilter->GetOutput() ) );
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
