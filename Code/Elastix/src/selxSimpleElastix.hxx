#ifndef __selxsimpleelastix_hxx_
#define __selxsimpleelastix_hxx_

#include "selxSimpleElastix.h"
#include "itkImageFileReader.h"
#include "itkImage.h"
#include "sitkPixelIDValues.h"
 
namespace itk {
  namespace simple {

template<typename TFixedImage, typename TMovingImage>
Image
SimpleElastix::ExecuteInternal( const Image* fixedImageDummy )
{
  // Assert images are set
  if( this->m_FixedImage == 0 )
  {
    sitkExceptionMacro( << "Fixed image is not set. Use SetFixedImage() or run Help() to get information on how to use this module." );
  }

  if( this->m_MovingImage == 0 )
  {
    sitkExceptionMacro( << "Moving image is not set. Use SetMovingImage() or run Help() to get information on how to use this module." );
  }

  // Masks are optional
  itk::DataObject::Pointer fixedMask = 0;
  if( this->m_FixedMask != 0 )
  {
    fixedMask = this->m_FixedMask->GetITKBase();
  }

  itk::DataObject::Pointer movingMask = 0;
  if( this->m_MovingMask != 0 )
  {
    movingMask = this->m_MovingMask->GetITKBase();
  }

  // Ensure parameterfile matches image types and dimensions
  const std::string FixedImagePixelType = GetPixelIDValueAsElastixParameter( this->m_FixedImage->GetPixelID() );
  const std::string MovingImagePixelType = GetPixelIDValueAsElastixParameter( this->m_FixedImage->GetPixelID() );
  const std::string FixedImageDimension = std::to_string( this->m_FixedImage->GetDimension() );
  const std::string MovingImageDimension = std::to_string( this->m_MovingImage->GetDimension() );
  for( unsigned int i = 0; i < this->m_ParameterMapList.size(); ++i )
  {
    //Put( &this->m_ParameterMapList[ i ], "FixedInternalImagePixelType", FixedImagePixelType);
    //Put( &this->m_ParameterMapList[ i ], "MovingInternalImagePixelType", MovingImagePixelType);
    //Put( &this->m_ParameterMapList[ i ], "FixedImageDimension", FixedImageDimension);
    //Put( &this->m_ParameterMapList[ i ], "MovingImageDimension", FixedImageDimension);
  }

  // Do the (possibly multiple) registrations
  int isError = 1;
  ElastixLibType* elastix = new ElastixLibType();
  try
  {
    isError = elastix->RegisterImages(
      this->m_FixedImage->GetITKBase(),
      this->m_MovingImage->GetITKBase(),
      this->m_ParameterMapList,
      this->m_LogFileName,
      this->m_LogFileName != "",
      this->m_LogToConsole,
      fixedMask,
      movingMask
    );
  }
  catch( itk::ExceptionObject &e )
  {
    if( elastix )
    {
      delete elastix;
      elastix = NULL;
    }

    sitkExceptionMacro( << "Errors occured during registration: " << e.what() );
  }

  if( isError == 0 && elastix->GetResultImage().IsNotNull() )
  {
    // TODO: Cast and set this->m_ResultImage
    this->m_TransformParameters = elastix->GetTransformParameterMapList();
  }
  else
  {
    sitkExceptionMacro( << "Errors occured during registration. Set LogToConsoleOn() or LogToFile(\"path/to/file\") to inspect errors." );
  }

  if( elastix )
  {
    delete elastix;
    elastix = NULL;
  }

  return *fixedImageDummy;
}


} // end namespace simple
} // end namespace itk

#endif // __selxsimpleelastix_hxx_