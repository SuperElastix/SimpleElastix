#ifndef __selxsimpleelastix_hxx_
#define __selxsimpleelastix_hxx_

#include "selxSimpleElastix.h"
#include "itkImageFileReader.h"
#include "itkImage.h"
#include "sitkPixelIDValues.h"
 
namespace itk {
  namespace simple {

template<typename TResultImage >
Image
SimpleElastix::ExecuteInternal( void )
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

  // Get masks if set (masks are optional)
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

  // Parameter file configurations
  for( unsigned int i = 0; i < this->m_ParameterMapList.size(); ++i )
  {
    // Parameter file must match fixed and moving image dimensions and pixel types
    this->Put( &this->m_ParameterMapList[ i ], "FixedInternalImagePixelType", GetPixelIDValueAsElastixParameter( this->m_FixedImage->GetPixelID() ) );
    this->Put( &this->m_ParameterMapList[ i ], "MovingInternalImagePixelType", GetPixelIDValueAsElastixParameter( this->m_MovingImage->GetPixelID() ) );
    this->Put( &this->m_ParameterMapList[ i ], "FixedImageDimension", std::to_string( this->m_FixedImage->GetDimension() ) );
    this->Put( &this->m_ParameterMapList[ i ], "MovingImageDimension", std::to_string( this->m_MovingImage->GetDimension() ) );

    // Elastix library always uses direction cosines
    this->Put( &this->m_ParameterMapList[ i ], "UseDirectionCosines", "true" );
  }

  // Do the (possibly multiple) registrations
  int isError = 1;
  libelastix* elastix = new libelastix();
  try
  {
    isError = elastix->RegisterImages(
      this->m_FixedImage->GetITKBase(),
      this->m_MovingImage->GetITKBase(),
      this->m_ParameterMapList,
      this->m_LogFileName,
      this->m_LogFileName != "output_path_not_set",
      this->m_LogToConsole,
      fixedMask,
      movingMask
    );
  }
  catch( itk::ExceptionObject &e )
  {
    delete elastix;
    elastix = NULL;
    sitkExceptionMacro( << "Errors occured during registration: " << e.what() );
  }

  if( isError == 0 && elastix->GetResultImage().IsNotNull() )
  {
    TResultImage* itkResultImage = static_cast< TResultImage* >( elastix->GetResultImage().GetPointer() );
    this->m_ResultImage = Image( itkResultImage );
    this->m_TransformParameters = elastix->GetTransformParameterMapList();
  }

  delete elastix;
  elastix = NULL;

  if( isError != 0 )
  {
    sitkExceptionMacro( << "Errors occured during registration. Set LogToConsoleOn() or LogToFile(\"path/to/file\") to inspect errors." );
  }

  return this->m_ResultImage;
}


} // end namespace simple
} // end namespace itk

#endif // __selxsimpleelastix_hxx_