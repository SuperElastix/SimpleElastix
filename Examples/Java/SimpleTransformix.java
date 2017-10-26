import org.itk.simple.*;

class SimpleTransformix {
 
  public static void main(String argv[]) {

    // If you get "no SimpleITKJava in java.library.path" point java.library.path to lib/libSimpeITKJava.jnilib

    if ( argv.length < 4 ) {
      System.out.println("Usage: java -cp SimpleTransformix.jar SimpleTransformix <fixedImage> <movingImage> <parameterFile> <inputImage> <output>");
      return;
    }

    // Make transform
    ImageFileReader reader = new ImageFileReader();
    reader.setFileName(argv[0]);
    ElastixImageFilter elastixImageFilter = new ElastixImageFilter();
    elastixImageFilter.setFixedImage(reader.execute());
    reader.setFileName(argv[1]);
    elastixImageFilter.setMovingImage(reader.execute());
    elastixImageFilter.setParameterMap(elastixImageFilter.readParameterFile(argv[2]));
    elastixImageFilter.logToConsoleOn();
    elastixImageFilter.execute();

    // Instantiate transformix
    TransformixImageFilter transformixImageFilter = new TransformixImageFilter();

    // Read input
    reader.setFileName(argv[3]);
    transformixImageFilter.setMovingImage(reader.execute());
    transformixImageFilter.setTransformParameterMap(elastixImageFilter.getTransformParameterMap());

    // Perform warp
    transformixImageFilter.logToConsoleOn();
    transformixImageFilter.execute();

    // Write result image
    ImageFileWriter writer = new ImageFileWriter();
    writer.setFileName(argv[4]);
    writer.execute(transformixImageFilter.getResultImage()); 

  }

}
