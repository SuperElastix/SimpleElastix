#ifndef __sitksimpletransformix_hxx_
#define __sitksimpletransformix_hxx_

#include "sitkSimpleTransformix.h"
 
namespace itk {
  namespace simple {

template< typename TInputImage >
Image
SimpleTransformix::ExecuteInternal( void )
{
  typedef elastix::TransformixFilter< TInputImage > TransformixFilterType;
  typedef typename TransformixFilterType::Pointer TransforimxFilterPointer;

  try
  {
    TransforimxFilterPointer transformixFilter = TransformixFilterType::New();

    if( !this->IsEmpty( this->m_InputImage ) ) {
      transformixFilter->SetInputImage( static_cast< TInputImage * >( this->GetInputImage().GetITKBase() ) );
    }

    transformixFilter->SetInputPointSetFileName( this->GetInputPointSetFileName() );
    transformixFilter->SetComputeSpatialJacobian( this->GetComputeSpatialJacobian() );
    transformixFilter->SetComputeDeterminantOfSpatialJacobian( this->GetComputeDeterminantOfSpatialJacobian() );
    transformixFilter->SetComputeDeformationField( this->GetComputeDeformationField() );

    transformixFilter->SetOutputDirectory( this->GetOutputDirectory() );
    transformixFilter->SetLogFileName( this->GetLogFileName() );
    transformixFilter->SetLogToFile( this->GetLogToFile() );
    transformixFilter->SetLogToConsole( this->GetLogToConsole() );

    ParameterObjectPointer parameterObject = ParameterObjectType::New();
    parameterObject->SetParameterMap( this->m_TransformParameterMapVector );
    transformixFilter->SetTransformParameterObject( parameterObject );

    transformixFilter->Update();

    if( !this->IsEmpty( this->m_InputImage) )
    {
      this->m_ResultImage = Image( transformixFilter->GetOutput() );
    }
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

#endif // __sitksimpletransformix_hxx_
