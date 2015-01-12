import org.itk.simple.*;

class SimpleElastix {
 
  public static void main(String argv[]) {

    // If you get "no SimpleITKJava in java.library.path" point java.library.path to lib/libSimpeITKJava.jnilib

    if ( argv.length < 4 ) {
      System.out.println("Usage: java -cp SimpleElastixJava.jar SimpleElastix <fixedImage> <movingImage> <parameterFile> <output>");
      return;
    }

    // Instantiate SimpleElastix
    org.itk.simple.SimpleElastix elastix = new org.itk.simple.SimpleElastix();

    // Read input
    org.itk.simple.ImageFileReader reader = new org.itk.simple.ImageFileReader();
    reader.setFileName(argv[0]);
    elastix.setFixedImage(reader.execute());
    reader.setFileName(argv[1]);
    elastix.setMovingImage(reader.execute());
    elastix.setParameterMap(elastix.readParameterFile(argv[2]));

    // Perform registration
    elastix.logToConsoleOn();
    elastix.execute();

    // Write result image
    ImageFileWriter writer = new ImageFileWriter();
    writer.setFileName(argv[3]);
    writer.execute(elastix.getResultImage()); 

    elastix.prettyPrint(elastix.getTransformParameterMapList());

  }

}
