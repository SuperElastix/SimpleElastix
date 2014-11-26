#ifndef __selxsimpleelastix_hxx_
#define __selxsimpleelastix_hxx_

#include "selxSimpleElastix.h"
#include "itkImageFileReader.h"
#include "itkImage.h"

namespace itk {
  namespace simple {
/*
template<typename TFixedImage, typename TMovingImage>
Image
SimpleElastix::ExecuteInternal( const Image* fixedImageDummy )
{
  itk::DataObject::Pointer fixedImage = 0;
  if( this->m_FixedImage->GetITKBase() )
  {
    typedef itk::ImageFileReader< TFixedImage > ReaderType;
   
    typename ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName("01001_t1_cma.hdr");

    fixedImage = static_cast< typename itk::DataObject::Pointer >( reader->GetOutput() );
    fixedImage->SetRequestedRegionToLargestPossibleRegion();
    fixedImage->Update();

    typename TMovingImage::Pointer itkImage = CastImageToITK< TFixedImage >( this->m_FixedImage );
  }
  else
  {
    sitkExceptionMacro( << "Fixed image is not set. Use SetFixedImage() or run Help() to get information on how to use this module." );
  }

  itk::DataObject::Pointer movingImage = 0;
  if( this->m_MovingImage->GetITKBase() )
  {
    typename TMovingImage::Pointer itkImage = CastImageToITK< TMovingImage >( this->m_MovingImage );
    movingImage = static_cast< typename itk::DataObject::Pointer >( itkImage );
    movingImage->SetRequestedRegionToLargestPossibleRegion();
    movingImage->Update();  }
  else
  {
    sitkExceptionMacro( << "Moving image is not set. Use SetMovingImage() or run Help() to get information on how to use this module." );
  }

  // TODO
  itk::DataObject::Pointer fixedMask = 0;
  itk::DataObject::Pointer movingMask = 0;

  ElastixLibType elastix;
  int isError = 1;
  try
  {
    isError = elastix.RegisterImages(
      fixedImage,
      movingImage,
      parameterMapList,
      "", // this->m_LogFileName,
      false, // this->m_LogFileName != "",
      true,//  this->m_LogToConsole,
      fixedMask,
      movingMask
    );
  }
  catch( itk::ExceptionObject &e )
  {
    sitkExceptionMacro( << e.what() );
  }

  if( isError != 0 )
  {
    sitkExceptionMacro( << "Errors occured during registration. Switch on logging to inspect." );
  }

  if( elastix.GetResultImage().IsNotNull() )
  {
    // Need to cast to ITK image first
    // this->m_ResultImage = Image( elastix.GetResultImage() );
    this->m_TransformParameters = elastix.GetTransformParameterMapList();
  }

  return this->m_ResultImage;
}
*/

} // end namespace simple
} // end namespace itk

#endif // __selxsimpleelastix_hxx_