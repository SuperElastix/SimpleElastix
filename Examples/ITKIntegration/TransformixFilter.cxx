#include <iostream>
#include <stdlib.h>

#include "elxTransformixFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

int main( int argc, char* argv[] ) {

  if ( argc < 3 ) {
    std::cerr << "Usage: " << argv[0] << " <movingImage> <parameterFile> <outputImage>\n";
    return 1;
  }

  typedef itk::Image< float, 2u > ImageType;

  typedef elastix::TransformixFilter< ImageType > TransformixFilterType;
  typedef TransformixFilterType::Pointer TransformixPointer;

  typedef elastix::ParameterObject ParameterObjectType;
  typedef ParameterObjectType::Pointer ParameterObjectPointer;

  typedef itk::ImageFileReader< ImageType > InputImageReaderType;
  typedef InputImageReaderType::Pointer InputImageReaderPointer;

  typedef itk::ImageFileWriter< ImageType > OutputImageWriterType;
  typedef OutputImageWriterType::Pointer OutputImageWriterPointer;

  try 
  {
    InputImageReaderPointer imageReader = InputImageReaderType::New();
    imageReader->SetFileName( argv[1] );

    ParameterObjectPointer parameterObject = ParameterObjectType::New();
    parameterObject->ReadParameterFile( argv[2] );

    TransformixPointer transformixFilter = TransformixFilterType::New();
    transformixFilter->SetMovingImage( imageReader->GetOutput() );
    transformixFilter->SetTransformParameterObject( parameterObject );
    transformixFilter->LogToConsoleOn();
    
    OutputImageWriterPointer outputImageWriter = OutputImageWriterType::New();
    outputImageWriter->SetFileName( argv[3] );
    outputImageWriter->SetInput( transformixFilter->GetOutput() );
    outputImageWriter->Update();
  } 
  catch( itk::ExceptionObject &e )
  {
    std::cerr << "Errors occured during transformation: ";
    std::cerr << e << std::endl;
    return EXIT_FAILURE;
  }

  return 0;

}
