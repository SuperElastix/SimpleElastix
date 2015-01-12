// This one header will include all SimpleITK filters and external
// objects.
#include <SimpleITK.h>
#include <selxSimpleElastix.h>
#include <iostream>
#include <stdlib.h>

namespace sitk = itk::simple;

int main ( int argc, char* argv[] ) {

  if ( argc < 4 ) {
    std::cerr << "Usage: " << argv[0] << " <fixedImage> <movingImage> <parameterFile> <outputImage>\n";
    return 1;
  }

  // Instantiate SimpleElastix
  sitk::SimpleElastix elastix;

  // Read input
  sitk::ImageFileReader reader;
  reader.SetFileName( std::string( argv[1] ) );
  elastix.SetFixedImage( reader.Execute() );
  reader.SetFileName( std::string( argv[2] ) );
  elastix.SetMovingImage( reader.Execute() );
  elastix.SetParameterMap( sitk::ReadParameterFile( std::string( argv[3] ) ) );
  elastix.LogToConsoleOn();

  // Perform registration
  elastix.Execute();
  elastix.Execute();

  // Write result image
  sitk::ImageFileWriter writer;
  writer.SetFileName( std::string( argv[4] ) );
  writer.Execute( elastix.GetResultImage() );

  elastix.PrettyPrint( elastix.GetTransformParameterMapList() );

  return 0;
}
