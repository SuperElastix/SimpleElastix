#ifndef __sitksimpleelastix_hxx_
#define __sitksimpleelastix_hxx_

#include "sitkSimpleElastix.h"
#include "itkImage.h"
 
namespace itk {
  namespace simple {

template< typename TResultImage >
Image
SimpleElastix::ExecuteInternal( void )
{
  // Assert fixed and moving image is set
  if( IsEmpty( this->m_FixedImage ) )
  {
    sitkExceptionMacro( << "Fixed image is not set. Set with method SetFixedImage()." );
  }

  if( IsEmpty( this->m_MovingImage ) )
  {
    sitkExceptionMacro( << "Moving image is not set. Set with method SetMovingImage()." );
  }

  // Assert at least one parameter map is set
  if( this->m_ParameterMaps.size() == 0 )
  {
    sitkExceptionMacro( << "Parameter map not set. Set with method SetParameterMap()." );
  }

  for( unsigned int i = 0; i < this->m_ParameterMaps.size(); ++i )
  {
    // Parameter file must match fixed and moving image dimensions and pixel types
    this->m_ParameterMaps[ i ][ "FixedInternalImagePixelType" ] = ParameterValuesType( 1, GetPixelIDValueAsElastixParameter( this->m_FixedImage.GetPixelID() ) );
    this->m_ParameterMaps[ i ][ "FixedImageDimension" ] = ParameterValuesType( 1, to_string( this->m_FixedImage.GetDimension() ) );
    this->m_ParameterMaps[ i ][ "MovingInternalImagePixelType" ] = ParameterValuesType( 1, GetPixelIDValueAsElastixParameter( this->m_MovingImage.GetPixelID() ) );    
    this->m_ParameterMaps[ i ][ "MovingImageDimension" ] = ParameterValuesType( 1, to_string( this->m_MovingImage.GetDimension() ) );
    this->m_ParameterMaps[ i ][ "ResultImagePixelType" ] = ParameterValuesType( 1, GetPixelIDValueAsElastixParameter( this->m_FixedImage.GetPixelID() ) );
  }

  // Get masks (optional)
  itk::DataObject::Pointer fixedMask = 0;
  if( !this->IsEmpty( this->m_FixedMask ) )
  {
    fixedMask = this->m_FixedMask.GetITKBase();
  }

  itk::DataObject::Pointer movingMask = 0;
  if( !this->IsEmpty( this->m_MovingMask ) )
  {
    movingMask = this->m_MovingMask.GetITKBase();
  }

  /**
   * BUG: Fixed image buffer is empty after elastix has run.
   * We pass a copy as a temporary workaround until the issue is fixed
   */
  Image fixedImage = this->m_FixedImage;
  fixedImage.SetDirection( fixedImage.GetDirection() );

  // Do the (possibly multiple) registrations
  int isError = 1;
  libelastix elastix = libelastix();
  try
  {
    isError = elastix.RegisterImages(
      fixedImage.GetITKBase(),
      this->m_MovingImage.GetITKBase(),
      this->m_ParameterMaps,
      this->m_OutputFolder,
      this->m_OutputFolder != "",
      this->m_LogToConsole,
      fixedMask,
      movingMask
    );
  }
  catch( itk::ExceptionObject &e )
  {
    sitkExceptionMacro( << "Errors occured during registration: " << e.what() );
  }

  if( isError == -2 )
  {
    sitkExceptionMacro( << "Errors occured during registration: Output directory does not exist." );
  }

  if( isError != 0 )
  {
    sitkExceptionMacro( << "Errors occured during registration. If you do not see any error message, set LogToConsoleOn() or LogToFolder(\"path/to/folder\") to view elastix output." );
  }

  if( elastix.GetTransformParameterMapList().size() > 0 )
  {
    this->m_TransformParameterMaps = elastix.GetTransformParameterMapList();
  }
  else
  {
    sitkExceptionMacro( "Errors occured during registration: Could not read final transform parameters." );
  }

  // Some day this will save someone a LOT of time ...
  if( this->m_LogToConsole && this->m_TransformParameterMaps[ this->m_ParameterMaps.size()-1 ].count( "WriteResultImage" ) > 0 )
  {
    if( this->m_TransformParameterMaps[ this->m_ParameterMaps.size()-1 ][ "WriteResultImage" ][ 0 ] == "false" )
    {
      std::cout << "WARNING: Result image cannot be read because WriteResultImage is set to \"false\". " << std::endl; 
    }
  }

  // We let the program continue even if result image can't be read, because user might 
  // have supplied (WriteResultImage "false") and plans to warp image with transformix
  if( elastix.GetResultImage().IsNotNull() )
  {
    TResultImage* itkResultImage = static_cast< TResultImage* >( elastix.GetResultImage().GetPointer() );
    this->m_ResultImage = Image( itkResultImage );
  }

  return this->m_ResultImage;
}


} // end namespace simple
} // end namespace itk

#endif // __sitksimpleelastix_hxx_