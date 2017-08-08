import org.itk.simple.*;

class SimpleTransformix {
 
  public static void main(String argv[]) {

    // If you get "no SimpleITKJava in java.library.path" point java.library.path to lib/libSimpeITKJava.jnilib

    if ( argv.length < 4 ) {
      System.out.println("Usage: java -cp SimpleTransformix.jar SimpleTransformix <fixedImage> <movingImage> <parameterFile> <inputImage> <output>");
      return;
    }

    // Make transform
    org.itk.simple.ImageFileReader reader = new org.itk.simple.ImageFileReader();
    reader.setFileName(argv[0]);
    org.itk.simple.ElastixImageFilter elastixImageFilter = new org.itk.simple.ElastixImageFilter();
    elastixImageFilter.setFixedImage(reader.execute());
    reader.setFileName(argv[1]);
    elastixImageFilter.setMovingImage(reader.execute());
    elastixImageFilter.setParameterMap(silx.readParameterFile(argv[2]));
    elastixImageFilter.logToConsoleOn();
    elastixImageFilter.execute();

    // Instantiate transformix
    org.itk.simple.TransformixImageFilter transformixImageFilter = new org.itk.simple.TransformixImageFilter();

    // Read input
    reader.setFileName(argv[3]);
    transformixImageFilter.setInputImage(reader.execute());
    transformixImageFilter.setTransformParameterMap(silx.getTransformParameterMap());

    // Perform warp
    transformixImageFilter.logToConsoleOn();
    transformixImageFilter.execute();

    // Write result image
    ImageFileWriter writer = new org.itk.simple.ImageFileWriter();
    writer.setFileName(argv[4]);
    writer.execute(transformixImageFilter.getResultImage()); 

  }

}
