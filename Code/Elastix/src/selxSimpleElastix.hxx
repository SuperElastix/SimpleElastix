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
  // Assert fixed and moving image is set
  if( this->m_FixedImage == 0 )
  {
    sitkExceptionMacro( << "Fixed image is not set. Use SetFixedImage() or run Help() to get information on how to use this module." );
  }

  if( this->m_MovingImage == 0 )
  {
    sitkExceptionMacro( << "Moving image is not set. Use SetMovingImage() or run Help() to get information on how to use this module." );
  }

  // Assert that at least one parameter map is set
  if( !(this->ReadParameterMapList().size() > 0) )
  {
    sitkExceptionMacro( << "Parameter map not set. Use SetParameterMap() or run Help() to get information on how to use this module." );
  }

  // Get masks if set (optional)
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

  // Parameter file must match fixed and moving image dimensions and pixel types
  this->Put( "FixedInternalImagePixelType", GetPixelIDValueAsElastixParameter( this->m_FixedImage->GetPixelID() ) );
  this->Put( "MovingInternalImagePixelType", GetPixelIDValueAsElastixParameter( this->m_MovingImage->GetPixelID() ) );
  this->Put( "FixedImageDimension", std::to_string( this->m_FixedImage->GetDimension() ) );
  this->Put( "MovingImageDimension", std::to_string( this->m_MovingImage->GetDimension() ) ); 

  // Elastix library always uses direction cosines
  this->Put( "UseDirectionCosines", "true" );

  // Do the (possibly multiple) registrations
  int isError = 1;
  libelastix* elastix = new libelastix();
  try
  {
    isError = elastix->RegisterImages(
      this->m_FixedImage->GetITKBase(),
      this->m_MovingImage->GetITKBase(),
      this->ReadParameterMapList(),
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
    this->SetTransformParameterMapList( elastix->GetTransformParameterMapList() );
  }

  delete elastix;
  elastix = NULL;

  if( isError == -1 )
  {
    sitkExceptionMacro( << "Errors occured during registration: Output directory does not exist." );
  }

  if( isError != 0 )
  {
    sitkExceptionMacro( << "Errors occured during registration. Set LogToConsoleOn() or LogToFile(\"path/to/file\") for detailed error messages." );
  }

  return this->m_ResultImage;
}


} // end namespace simple
} // end namespace itk

#endif // __selxsimpleelastix_hxx_