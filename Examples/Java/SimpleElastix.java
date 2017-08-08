import org.itk.simple.*;

class SimpleElastix {
 
  public static void main(String[] argv) {

    // If you get "no SimpleITKJava in java.library.path" point java.library.path to lib/libSimpeITKJava.jnilib

    if ( argv.length < 4 ) {
      System.out.println("Usage: java -cp SimpleElastix.jar SimpleElastix <fixedImage> <movingImage> <parameterFile> <outputDirectory>");
      return;
    }

    // Instantiate SimpleElastix
    org.itk.simple.ElastixImageFilter elastixImageFilter = new org.itk.simple.ElastixImageFilter();

    // Read input
    org.itk.simple.ImageFileReader reader = new org.itk.simple.ImageFileReader();
    reader.setFileName(argv[0]);
    elastixImageFilter.setFixedImage(reader.execute());
    reader.setFileName(argv[1]);
    elastixImageFilter.setMovingImage(reader.execute());
    elastixImageFilter.setParameterMap(silx.readParameterFile(argv[2]));

    // Perform registration
    elastixImageFilter.logToConsoleOn();
    elastixImageFilter.execute();

    // Write result image
    ImageFileWriter writer = new org.itk.simple.ImageFileWriter();
    writer.setFileName(argv[3]);
    writer.execute(elastixImageFilter.getResultImage(), "."); 

    elastixImageFilter.prettyPrint(elastixImageFilter.getTransformParameterMap());

  }

}
