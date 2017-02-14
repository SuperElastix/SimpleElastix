library(SimpleITK)

SimpleElastixObj <- SimpleElastix()
SimpleElastixObj$SetFixedImage(ReadImage("fixedImage.nii"))
SimpleElastixObj$SetMovingImage(ReadImage("movingImage.nii"))
SimpleElastixObj$Execute()
resultImage <- SimpleElastixObj.GetResultImage()
