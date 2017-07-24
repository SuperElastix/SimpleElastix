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
                ElastixImageFilter silx;

                // Read input 
                ImageFileReader reader = new ImageFileReader();
                reader.SetFileName(args[0]);
                silx.SetFixedImage(reader.Execute());
                reader.SetFileName(args[1]);
                silx.SetMovingImage(reader.Execute());
                silx.SetParameterMap(ReadParameterFile(args[2]));

                // Perform Registration
                silx.LogToConsoleOn();
                silx.Execute();

                // Write output image
                ImageFileWriter writer = new ImageFileWriter();
                writer.SetFileName(args[3]);
                writer.Execute(silx.GetResultImage());

            } catch (Exception e) {
                Console.WriteLine(e);
            }
        }
    }
}
