#ifndef __selxsimpleelastix_hxx_
#define __selxsimpleelastix_hxx_

#include "selxSimpleElastix.h"
#include "itkImageFileReader.h"
#include "itkImage.h"
 
namespace itk {
  namespace simple {

template<typename TFixedImage, typename TMovingImage>
Image
SimpleElastix::ExecuteInternal( const Image* fixedImageDummy )
{
  // TODO
  if( 0 )
  {
    sitkExceptionMacro( << "Fixed image is not set. Use SetFixedImage() or run Help() to get information on how to use this module." );
  }

  // TODO
  if( 0 )
  {
    sitkExceptionMacro( << "Moving image is not set. Use SetMovingImage() or run Help() to get information on how to use this module." );
  }

  // TODO
  itk::DataObject::Pointer fixedMask = 0;
  itk::DataObject::Pointer movingMask = 0;

  ElastixLibType* elastix = new ElastixLibType();
  int isError = 1;
  try
  {
    isError = elastix->RegisterImages(
      this->m_FixedImage->GetITKBase(),
      this->m_MovingImage->GetITKBase(),
      this->m_ParameterMapList,
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

  if( isError == 0 )
  {
    if( elastix->GetResultImage().IsNotNull() )
    {
      // TODO: Cast and set this->m_ResultImage
    }
    else
    {
      sitkExceptionMacro( "Error occured getting result image." )
    }

    this->m_TransformParameters = elastix->GetTransformParameterMapList();
  }
  else
  {
    sitkExceptionMacro( << "Errors occured during registration. Switch on logging to inspect." );
  }

  delete elastix;

  return *fixedImageDummy;
}


} // end namespace simple
} // end namespace itk

#endif // __selxsimpleelastix_hxx_