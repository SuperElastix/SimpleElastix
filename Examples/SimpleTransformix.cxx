// This one header will include all SimpleITK filters and external
// objects.
#include <SimpleITK.h>
#include <iostream>
#include <stdlib.h>

namespace sitk = itk::simple;

int main ( int argc, char* argv[] ) {

  if ( argc < 4 ) {
    std::cerr << "Usage: " << argv[0] << " <fixedImage> <movingImage> <inputImage> <parameterFile> <outputImage>\n";
    return 1;
  }

  // Make transform
  sitk::SimpleElastix elastix;
  sitk::ImageFileReader reader;
  reader.SetFileName( std::string( argv[1] ) );
  elastix.SetFixedImage( reader.Execute() );
  reader.SetFileName( std::string( argv[2] ) );
  elastix.SetMovingImage( reader.Execute() );
  elastix.SetParameterMap( sitk::ReadParameterFile( std::string( argv[3] ) ) );
  elastix.LogToConsoleOn();
  elastix.Execute();

  // Instantiate transformix
  sitk::SimpleTransformix transformix;

  // Read input
  reader.SetFileName( std::string( argv[4] ) );
  transformix.SetInputImage( reader.Execute() );
  transformix.SetTransformParameterMap( elastix.GetTransformParameterMap() );

  // Perform warp
  transformix.LogToConsoleOn();
  transformix.Execute();

  // Write result image
  sitk::ImageFileWriter writer;
  writer.SetFileName( std::string( argv[5] ) );
  writer.Execute( transformix.GetResultImage() );

  return 0;
}

