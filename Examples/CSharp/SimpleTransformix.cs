using System;
using itk.simple;

namespace itk.simple.examples {
    class SimpleTransformix {
        static void Main(string[] args) {
            try {
                if (args.Length < 4) {
                    Console.WriteLine("Usage: SimpleTransformix <fixedImage> <movingImage> <inputImage> <parameterFile> <output>");
                    return;
                }
                // Make transform
                ElastixImageFilter silx;
                ImageFileReader reader = new ImageFileReader();
                reader.SetFileName(args[0]);
                silx.SetFixedImage(reader.Execute());
                reader.SetFileName(args[1]);
                silx.SetMovingImage(reader.Execute());
                silx.SetParameterMap(ReadParameterFile(args[3]));
                silx.Execute();

                // Instantiate transformix
                TransformixImageFilter stfx;

                // Read input
                reader.SetFileName(args[4]);
                stfx.SetInputImage(reader.execute());
                stfx.SetTransformParameterMap(silx.GetTransformParameterMap());

                // Perform warp
                stfx.LogToConsoleOn();
                stfx.Execute();

                // Write result image
                sitk.WriteImage(stfx.GetResultImage(), args[5]);
                

            } catch (Exception e) {
                Console.WriteLine(e);
            }
        }
    }
}
