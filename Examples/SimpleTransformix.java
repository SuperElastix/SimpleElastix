import org.itk.simple.*;

class SimpleTransformix {
 
  public static void main(String argv[]) {

    if ( argv.length < 4 ) {
      System.out.println("Usage: java SimpleElastix <fixedImage> <movingImage> <inputImage> <parameterFile> <output>");
      return;
    }

    // Make transform parameter map list
    org.itk.simple.SimpleElastix elastix = new org.itk.simple.SimpleElastix();
    org.itk.simple.ImageFileReader reader = new org.itk.simple.ImageFileReader();
    reader.setFileName(argv[0]);
    elastix.SetFixedImage(reader.execute());
    reader.setFileName(argv[1]);
    elastix.SetMovingImage(reader.execute());
    elastix.SetParameterMap(ReadParameterFile(argv[2]));
    elastix.execute();

    // Instantiate transformix
    org.itk.simple.SimpleTransformix transformix = new org.itk.simple.SimpleTransformix();

    // Read input
    reader.setFileName(argv[3]);
    transformix.SetInputImage(reader.execute());
    transformix.SetTransformParameterMapList(elastix.GetTransformParameterMapList())

    // Perform warp
    transformix.execute()

    // Write result image
    ImageFileWriter writer = new ImageFileWriter();
    writer.setFileName(argv[3]);
    writer.execute(transformix.GetResultImage()); 

  }

}
