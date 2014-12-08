#ifndef __selxsimpleelastix_hxx_
#define __selxsimpleelastix_hxx_

#include "selxSimpleElastix.h"
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
  if( this->m_ParameterMaps.size() == 0 )
  {
    sitkExceptionMacro( << "Parameter map not set. Use SetParameterMap() or run Help() to get information on how to use this module." );
  }

  for( unsigned int i = 0; i < this->m_ParameterMaps.size(); ++i )
  {
    // Parameter file must match fixed and moving image dimensions and pixel types
    this->m_ParameterMaps[ i ][ "FixedInternalImagePixelType" ] = ParameterValuesType( 1, GetPixelIDValueAsElastixParameter( this->m_FixedImage->GetPixelID() ) );
    this->m_ParameterMaps[ i ][ "MovingInternalImagePixelType" ] = ParameterValuesType( 1, GetPixelIDValueAsElastixParameter( this->m_MovingImage->GetPixelID() ) );
    this->m_ParameterMaps[ i ][ "FixedImageDimension" ] = ParameterValuesType( 1, std::to_string( this->m_FixedImage->GetDimension() ) );
    this->m_ParameterMaps[ i ][ "MovingImageDimension" ] = ParameterValuesType( 1, std::to_string( this->m_MovingImage->GetDimension() ) );

    // Elastix library always uses direction cosines
    this->m_ParameterMaps[ i ][ "UseDirectionCosines" ] = ParameterValuesType( 1, "true" );
  }

  // Get masks (optional)
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

  // Do the (possibly multiple) registrations
  int isError = 1;
  libelastix* elastix = new libelastix();
  try
  {
    isError = elastix->RegisterImages(
      this->m_FixedImage->GetITKBase(),
      this->m_MovingImage->GetITKBase(),
      this->m_ParameterMaps,
      this->m_OutputFolder,
      this->m_LogToDisk,
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

  if( isError == -2 )
  {
    sitkExceptionMacro( << "Errors occured during registration: Output directory does not exist." );
  }

  if( isError != 0 )
  {
    sitkExceptionMacro( << "Errors occured during registration." );
  }

  if( elastix->GetTransformParameterMapList().size() == 0 )
  {
    this->m_TransformParameterMaps = elastix->GetTransformParameterMapList();
  }
  else
  {
    // We continue execution in case the result image can be read
    std::cout << "Errors occured during registration: Could not read transform parameters." << std::endl;
  }

  if( elastix->GetResultImage().IsNotNull() )
  {
    TResultImage* itkResultImage = static_cast< TResultImage* >( elastix->GetResultImage().GetPointer() );
    this->m_ResultImage = Image( itkResultImage );
  }
  else
  {
    // We continue execution in case transform parameters was read
    std::cout << "Errors occured during registration: Could not read output image." << std::endl;;
  }

  delete elastix;
  elastix = NULL;

  return this->m_ResultImage;
}


} // end namespace simple
} // end namespace itk

#endif // __selxsimpleelastix_hxx_