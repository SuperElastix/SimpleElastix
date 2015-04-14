import org.itk.simple.*;

class SimpleTransformix {
 
  public static void main(String argv[]) {

    // If you get "no SimpleITKJava in java.library.path" point java.library.path to lib/libSimpeITKJava.jnilib

    if ( argv.length < 4 ) {
      System.out.println("Usage: java -cp SimpleTransformixJava.jar SimpleTransformix <fixedImage> <movingImage> <parameterFile> <inputImage> <output>");
      return;
    }

    // Make transform
    org.itk.simple.ImageFileReader reader = new org.itk.simple.ImageFileReader();
    reader.setFileName(argv[0]);
    org.itk.simple.SimpleElastix elastix = new org.itk.simple.SimpleElastix();
    elastix.setFixedImage(reader.execute());
    reader.setFileName(argv[1]);
    elastix.setMovingImage(reader.execute());
    elastix.setParameterMap(elastix.readParameterFile(argv[2]));
    elastix.logToConsoleOn();
    elastix.execute();

    // Instantiate transformix
    org.itk.simple.SimpleTransformix transformix = new org.itk.simple.SimpleTransformix();

    // Read input
    reader.setFileName(argv[3]);
    transformix.setInputImage(reader.execute());
    transformix.setTransformParameterMapList(elastix.getTransformParameterMapList());

    // Perform warp
    transformix.logToConsoleOn();
    transformix.execute();

    // Write result image
    ImageFileWriter writer = new org.itk.simple.ImageFileWriter();
    writer.setFileName(argv[4]);
    writer.execute(transformix.getResultImage()); 

  }

}
