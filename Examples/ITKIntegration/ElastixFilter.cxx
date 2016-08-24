#include <iostream>
#include <stdlib.h>

#include "elxElastixFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

int main( int argc, char* argv[] ) {

  if ( argc < 4 ) {
    std::cerr << "Usage: " << argv[0] << " <fixedImage> <movingImage> <parameterFile> <outputImage>\n";
    return 1;
  }

  typedef itk::Image< float, 2u > ImageType;

  typedef elastix::ElastixFilter< ImageType, ImageType > ElastixFilterType;
  typedef ElastixFilterType::Pointer ElastixPointer;

  typedef elastix::ParameterObject ParameterObjectType;
  typedef ParameterObjectType::Pointer ParameterObjectPointer;

  typedef itk::ImageFileReader< ImageType > FixedImageReaderType;
  typedef FixedImageReaderType::Pointer FixedImageReaderPointer;

  typedef itk::ImageFileReader< ImageType > MovingImageReaderType;
  typedef MovingImageReaderType::Pointer MovingImageReaderPointer;

  typedef itk::ImageFileWriter< ImageType > ResultImageWriterType;
  typedef ResultImageWriterType::Pointer ResultImageWriterPointer;

  try 
  {
    FixedImageReaderPointer fixedImageReader = FixedImageReaderType::New();
    fixedImageReader->SetFileName( argv[1] );

    MovingImageReaderPointer movingImageReader = MovingImageReaderType::New();
    movingImageReader->SetFileName( argv[2] );

    ParameterObjectPointer parameterObject = ParameterObjectType::New();
    parameterObject->ReadParameterFile( argv[3] );

    ElastixPointer elastixFilter = ElastixFilterType::New();
    elastixFilter->SetFixedImage( fixedImageReader->GetOutput() );
    elastixFilter->SetMovingImage( movingImageReader->GetOutput() );
    elastixFilter->SetParameterObject( parameterObject );
    elastixFilter->LogToConsoleOn();
    
    ResultImageWriterPointer resultImageWriter = ResultImageWriterType::New();
    resultImageWriter->SetFileName( argv[4] );
    resultImageWriter->SetInput( elastixFilter->GetOutput() );
    resultImageWriter->Update();
  } 
  catch( itk::ExceptionObject &e )
  {
    std::cerr << "Errors occured during registration: ";
    std::cerr << e << std::endl;
    return EXIT_FAILURE;
  }

  return 0;

}
