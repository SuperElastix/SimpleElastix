import SimpleITK as sitk
import sys

# Make transform 
elastix = sitk.SimpleElastix()
elastix.SetFixedImage(sitk.ReadImage(str(sys.argv[1])))
elastix.SetMovingImage(sitk.ReadImage(str(sys.argv[2])))
elastix.SetParameterMap(sitk.ReadParameterFile(str(sys.argv[3])))
elastix.LogToConsoleOn()
elastix.Execute()

# Instantiate SimpleTransformix
transformix = sitk.SimpleTransformix()

# Read Input
transformix.SetInputImage(sitk.ReadImage(str(sys.argv[4])))
transformix.SetParameterMapList(elastix.GetTransformParameterMapList())

# Perform warp
transformix.Execute()

# Write result image
sitk.WriteImage(transformix.GetResultImage(), str(sys.argv[5]))