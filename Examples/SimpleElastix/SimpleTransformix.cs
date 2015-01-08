using System;
using itk.simple;

namespace itk.simple.examples {
    class SimpleTransformix {
        static void Main(string[] args) {
            try {
                if (args.Length < 4) {
                    Console.WriteLine("Usage: SimpleElastix <fixedImage> <movingImage> <inputImage> <parameterFile> <output>");
                    return;
                }
                // Make transform parameter map
                SimpleElastix elastix;
                ImageFileReader reader = new ImageFileReader();
                reader.SetFileName(args[0]);
                elastix.SetFixedImage(reader.Execute());
                reader.SetFileName(args[1]);
                elastix.SetMovingImage(reader.Execute());
                elastix.SetParameterMap(ReadParameterFile(args[3]))
                elastix.Execute()

                // Instantiate transformix
                SimpleTransformix transformix

                // Read input
                reader.SetFileName(args[4])
                transformix.SetInputImage(reader.execute())
                transformix.SetParameterMapList(elastix.GetParameterMapList())

                // Perform warp
                transformix.Execute()

                // Write result image
                sitk.WriteImage(transformix.GetResultImage(), args[5])
                

            } catch (Exception ex) {
                Console.WriteLine(ex);
            }
        }
    }
}
