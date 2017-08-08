library(SimpleITK)

elastixImageFilter <- ElastixImageFilter()
elastixImageFilter$SetFixedImage(ReadImage("fixedImage.nii"))
elastixImageFilter$SetMovingImage(ReadImage("movingImage.nii"))
elastixImageFilter$Execute()
resultImage <- elastixImageFilter.GetResultImage()
