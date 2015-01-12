import SimpleITK as sitk
import sys

# Instantiate SimpleElastix
selx = sitk.SimpleElastix()

# Read Input
selx.SetFixedImage(sitk.ReadImage(sys.argv[1]))
selx.SetMovingImage(sitk.ReadImage(sys.argv[2]))
selx.SetParameterMap(sitk.ReadParameterFile(sys.argv[3]))

# Perform registration
selx.Execute()

# Write result image
sitk.WriteImage(selx.GetResultImage(), sys.argv[4])