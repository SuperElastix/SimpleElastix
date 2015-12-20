#ifndef __sitksimpletransformix_hxx_
#define __sitksimpletransformix_hxx_

#include "sitkSimpleElastix.h"
#include "sitkSimpleTransformix.h"
#include "elxElastixMain.h" // for xoutClose
 
namespace itk {
  namespace simple {

template<typename TResultImage >
Image
SimpleTransformix::ExecuteInternal( void )
{
  // Assert fixed and moving image is set
  if( IsEmpty( this->m_InputImage ) )
  {
    sitkExceptionMacro( << "Input image is not set. Use SetInputImage() or run Help() to get information on how to use this module." );
  }

  // Assert that at least one parameter map is set
  if( this->m_TransformParameterMaps.size() == 0 )
  {
    sitkExceptionMacro( << "Transform parameter map not set. Use SetTransformParameterMap() or run Help() to get information on how to use this module." );
  }

  for( unsigned int i = 0; i < this->m_TransformParameterMaps.size(); ++i )
  {
    // Parameter file must match input image dimensions and pixel type (InputImage == MovingImage)
    this->m_TransformParameterMaps[ i ][ "FixedInternalImagePixelType" ] = ParameterValuesType( 1, GetPixelIDValueAsElastixParameter( this->m_InputImage.GetPixelID() ) );
    this->m_TransformParameterMaps[ i ][ "FixedImageDimension" ] = ParameterValuesType( 1, to_string( this->m_InputImage.GetDimension() ) );
    this->m_TransformParameterMaps[ i ][ "MovingInternalImagePixelType" ] = ParameterValuesType( 1, GetPixelIDValueAsElastixParameter( this->m_InputImage.GetPixelID() ) );
    this->m_TransformParameterMaps[ i ][ "MovingImageDimension" ] = ParameterValuesType( 1, to_string( this->m_InputImage.GetDimension() ) );
    this->m_TransformParameterMaps[ i ][ "ResultImagePixelType" ] = ParameterValuesType( 1, GetPixelIDValueAsElastixParameter( this->m_InputImage.GetPixelID() ) );
  }

  // Do the tranformation
  int isError = 1;
  libtransformix transformix = libtransformix();
  try
  {
    isError = transformix.TransformImage(
      this->m_InputImage.GetITKBase(),
      this->m_TransformParameterMaps,
      this->m_OutputFolder,
      this->m_OutputFolder != "",
      this->m_LogToConsole
    );
  }
  catch( itk::ExceptionObject &e )
  {
    sitkExceptionMacro( << "Errors occured in transformix: " << e.what() );
  }

  if( isError == -2 )
  {
    sitkExceptionMacro( << "Errors occured in transformix: Output directory does not exist." );
  }

  if( isError != 0 )
  {
    sitkExceptionMacro( << "Errors occured in transformix. If you do not see any other error message, set LogToConsoleOn() or LogToFolder(\"path/to/folder\") to view transformix output." );
  }

  if( transformix.GetResultImage().IsNotNull() )
  {
    TResultImage* itkResultImage = static_cast< TResultImage* >( transformix.GetResultImage().GetPointer() );
    this->m_ResultImage = Image( itkResultImage );
  }
  else
  {
    sitkExceptionMacro( << "Error occured in transformix: If you do not see any other error message, Set LogToConsoleOn() or LogToFolder(\"path/to/folder\") to view transformix output." );
  }

  return this->m_ResultImage;
}


} // end namespace simple
} // end namespace itk

#endif // __sitksimpletransformix_hxx_