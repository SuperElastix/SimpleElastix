import SimpleITK as sitk
import sys

# Make transform parameter map
elastix = sitk.SimpleElastix()
elastix.SetFixedImage(sitk.ReadImage(sys.argv[1]))
elastix.SetMovingImage(sitk.ReadImage(sys.argv[2]))
elastix.SetParameterMap(sitk.ReadParameterFile(sys.argv[3]))
elastix.Execute()

# Instantiate SimpleTransformix
transformix = sitk.SimpleTransformix()

# Read Input
transformix.SetInputImage(sitk.ReadImage(sys.argv[4]))
transformix.SetParameterMapList(elastix.GetTransformParameterMapList())

# Perform warp
transformix.Execute()

# Write result image
sitk.WriteImage(transformix.GetResultImage(), sys.argv[5])