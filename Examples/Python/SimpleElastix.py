import SimpleITK as sitk
import sys

# Instantiate SimpleElastix
elastixImageFilter = sitk.ElastixImageFilter()

# Read Input
elastixImageFilter.SetFixedImage(sitk.ReadImage(str(sys.argv[1])))
elastixImageFilter.SetMovingImage(sitk.ReadImage(str(sys.argv[2])))
elastixImageFilter.SetParameterMap(sitk.ReadParameterFile(str(sys.argv[3])))

# Perform registration
elastixImageFilter.LogToConsoleOn()
elastixImageFilter.Execute()

# Write result image
elastixImageFilter.WriteImage(elastixImageFilter.GetResultImage(), str(sys.argv[4]))
