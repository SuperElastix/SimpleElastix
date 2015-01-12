using System;
using itk.simple;

namespace itk.simple.examples {
    class SimpleElastix {
        static void Main(string[] args) {
            try {
                if (args.Length < 4) {
                    Console.WriteLine("Usage: SimpleElastix <fixedImage> <movingImage> <parameterFile> <output>");
                    return;
                }
                // Instantiate SimpleElastix
                SimpleElastix elastix;

                // Read input 
                ImageFileReader reader = new ImageFileReader();
                reader.SetFileName(args[0]);
                elastix.SetFixedImage(reader.Execute());
                reader.SetFileName(args[1]);
                elastix.SetMovingImage(reader.Execute());
                elastix.SetParameterMap(ReadParameterFile(args[2]))

                // Perform Registration
                elastix.Execute()

                // Write output image
                ImageFileWriter writer = new ImageFileWriter();
                writer.SetFileName(args[3]);
                writer.Execute(elastix.GetResultImage());

            } catch (Exception ex) {
                Console.WriteLine(ex);
            }
        }
    }
}
