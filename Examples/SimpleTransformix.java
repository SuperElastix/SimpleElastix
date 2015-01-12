import org.itk.simple.*;

class SimpleTransformix {
 
  public static void main(String argv[]) {

    if ( argv.length < 4 ) {
      System.out.println("Usage: java SimpleElastix <fixedImage> <movingImage> <inputImage> <parameterFile> <output>");
      return;
    }

    // Make transform parameter map list
    org.itk.simple.ImageFileReader reader = new org.itk.simple.ImageFileReader();
    reader.setFileName(argv[0]);
    org.itk.simple.SimpleElastix elastix = new org.itk.simple.SimpleElastix();
    elastix.setFixedImage(reader.execute());
    reader.setFileName(argv[1]);
    elastix.setMovingImage(reader.execute());
    elastix.setParameterMap(elastix.readParameterFile(argv[2]));
    elastix.execute();

    // Instantiate transformix
    org.itk.simple.SimpleTransformix transformix = new org.itk.simple.SimpleTransformix();

    // Read input
    reader.setFileName(argv[3]);
    transformix.setInputImage(reader.execute());
    transformix.setTransformParameterMapList(elastix.getTransformParameterMapList());

    // Perform warp
    transformix.execute();

    // Write result image
    ImageFileWriter writer = new ImageFileWriter();
    writer.setFileName(argv[3]);
    writer.execute(transformix.getResultImage()); 

  }

}
