import org.itk.simple.*;

class SimpleElastix {
 
  public static void main(String argv[]) {

    if ( argv.length < 4 ) {
      System.out.println("Usage: java SimpleElastix <fixedImage> <movingImage> <parameterFile> <output>");
      return;
    }

    // Instantiate SimpleElastix
    org.itk.simple.SimpleElastix elastix = new org.itk.simple.SimpleElastix();

    // Read input
    org.itk.simple.ImageFileReader reader = new org.itk.simple.ImageFileReader();
    reader.setFileName(argv[0]);
    elastix.SetFixedImage(reader.execute());

    reader.setFileName(argv[1]);
    elastix.SetMovingImage(reader.execute());

    elastix.SetParameterMap(ReadParameterFile(argv[2]));

    // Perform registration
    elastix.execute();

    // Write result image
    ImageFileWriter writer = new ImageFileWriter();
    writer.setFileName(argv[3]);
    writer.execute(elastix.GetResultImage()); 

  }

}
