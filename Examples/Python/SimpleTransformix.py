import SimpleITK as sitk
import sys

# Make transform 
elastixImageFilter = sitk.ElastixImageFilter()
elastixImageFilter.SetFixedImage(sitk.ReadImage(str(sys.argv[1])))
elastixImageFilter.SetMovingImage(sitk.ReadImage(str(sys.argv[2])))
elastixImageFilter.SetParameterMap(sitk.ReadParameterFile(str(sys.argv[3])))
elastixImageFilter.LogToConsoleOn()
elastixImageFilter.Execute()

# Instantiate SimpleTransformix
transformixImageFilter = sitk.TransformixImageFilter()

# Read Input
transformixImageFilter.SetInputImage(sitk.ReadImage(str(sys.argv[4])))
transformixImageFilter.SetParameterMap(elastixImageFilter.GetTransformParameterMap())

# Perform warp
transformixImageFilter.LogToConsoleOn()
transformixImageFilter.Execute()

# Write result image
sitk.WriteImage(transformixImageFilter.GetResultImage(), str(sys.argv[5]))
