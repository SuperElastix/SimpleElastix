#ifndef __selxsimpletransformix_hxx_
#define __selxsimpletransformix_hxx_

#include "selxSimpleTransformix.h"
#include "itkImage.h"
#include "sitkPixelIDValues.h"
 
namespace itk {
  namespace simple {

template<typename TResultImage >
Image
SimpleTransformix::ExecuteInternal( void )
{
  // Assert fixed and moving image is set
  if( this->m_InputImage == 0 )
  {
    sitkExceptionMacro( << "Input image is not set. Use SetInputImage() or run Help() to get information on how to use this module." );
  }

  // Assert that at least one parameter map is set
  if( this->m_TransformParameterMaps.size() == 0 )
  {
    sitkExceptionMacro( << "Transform parameter map not set. Use SetTransformParameterMap() or run Help() to get information on how to use this module." );
  }

  // Do the tranformation
  int isError = 1;
  libtransformix* transformix = new libtransformix();
  try
  {
    isError = transformix->TransformImage(
      this->m_InputImage->GetITKBase(),
      this->m_TransformParameterMaps,
      this->m_OutputFolder,
      this->m_LogToDisk,
      this->m_LogToConsole
    );
  }
  catch( itk::ExceptionObject &e )
  {
    delete transformix;
    transformix = NULL;
    sitkExceptionMacro( << "Errors occured during transformation: " << e.what() );
  }

  if( isError == -2 )
  {
    sitkExceptionMacro( << "Errors occured during transformation: Output directory does not exist." );
  }

  if( isError != 0 )
  {
    sitkExceptionMacro( << "Errors occured during transformation." );
  }

  if( transformix->GetResultImage().IsNotNull() )
  {
    TResultImage* itkResultImage = static_cast< TResultImage* >( transformix->GetResultImage().GetPointer() );
    this->m_ResultImage = Image( itkResultImage );
  }
  else
  {
    sitkExceptionMacro( << "Errors occured during registration: Could not read output image." );
  }

  delete transformix;
  transformix = NULL;

  return this->m_ResultImage;
}


} // end namespace simple
} // end namespace itk

#endif // __selxsimpletransformix_hxx_