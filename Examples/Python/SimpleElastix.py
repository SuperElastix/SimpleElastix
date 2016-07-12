import SimpleITK as sitk
import sys

# Instantiate SimpleElastix
selx = sitk.SimpleElastix()

# Read Input
selx.SetFixedImage(sitk.ReadImage(str(sys.argv[1])))
selx.SetMovingImage(sitk.ReadImage(str(sys.argv[2])))
selx.SetParameterMap(sitk.ReadParameterFile(str(sys.argv[3])))

# Perform registration
selx.LogToConsoleOn()
selx.Execute()

# Write result image
sitk.WriteImage(selx.GetResultImage(), str(sys.argv[4]))
