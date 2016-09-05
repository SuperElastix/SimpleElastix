#ifndef __sitksimpletransformix_hxx_
#define __sitksimpletransformix_hxx_

#include "sitkCastImageFilter.h"

namespace itk {
  namespace simple {

template< typename TMovingImage >
Image
SimpleTransformix::ExecuteInternal( void )
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
      transformParameterMapVector[ i ][ "ResultImagePixelType" ] = ParameterValueVectorType( 1, "float" );
    }

    ParameterObjectPointer parameterObject = ParameterObjectType::New();
    parameterObject->SetParameterMap( transformParameterMapVector );
    transformixFilter->SetTransformParameterObject( parameterObject );
    transformixFilter->Update();

    if( !this->IsEmpty( this->GetMovingImage() ) )
    {
      // Cast DataObject -> itk::Image< ResultImagePixelType, ImageDimension -> sitk::Image
      this->m_ResultImage = Cast( Image( itkDynamicCastInDebugMode< TMovingImage* >( transformixFilter->GetOutput() ) ), this->GetMovingImage().GetPixelID() );
      this->m_ResultImage.MakeUnique();
    }
  }
  catch( itk::ExceptionObject &e )
  {
    sitkExceptionMacro( << e );
  }

  return this->m_ResultImage;
}

} // end namespace simple
} // end namespace itk

#endif // __sitksimpletransformix_hxx_
