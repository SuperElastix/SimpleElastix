from __future__ import print_function
import sys
import unittest
import tempfile
import numpy as np
import os
from itertools import cycle

import SimpleITK as sitk


class ActiveRegistrationModelShapeMetricTest(unittest.TestCase):
    def makeGridShapes(self, center, grid_width, grid_height, grid_num):
        return [[i, j]
                for i in np.linspace(center - grid_width // 2, center + grid_width // 2, grid_num)
                for j in np.linspace(center - grid_height // 2, center + grid_height // 2, grid_num)]

    # Makes grids translated along the diagonal
    def makeGridShapesTranslation(self, center_lower, center_upper, shape_num, grid_width, grid_height, grid_num):
        return [self.makeGridShapes(c, grid_width, grid_height, grid_num)
                for c in np.linspace(center_lower, center_upper, shape_num)]

    def makeSquareImageShapeModel(self, image_size, center, square_size):
        array = np.zeros(image_size, np.float)
        for i in range(center[0] - square_size[0] // 2, center[0] + square_size[0] // 2):
            for j in range(center[1] - square_size[1] // 2, center[1] + square_size[1] // 2):
                array[i, j] = 1

        return sitk.GetImageFromArray(array)

    def makeSquareImageIntensityModel(self, image_size, center, square_size, foreground, background):
        array = np.full(image_size, background, dtype=np.float)
        for i in range(center[0] - square_size[0] // 2, center[0] + square_size[0] // 2):
            for j in range(center[1] - square_size[1] // 2, center[1] + square_size[1] // 2):
                array[i, j] = foreground

        return sitk.GetImageFromArray(array)

    def makeSquareImagesIntensityModel(self, image_size, center, square_size, foreground_range, background_range):
        return [self.makeSquareImageIntensityModel(image_size, center, square_size, foreground, background)
                for foreground in np.linspace(foreground_range[0], foreground_range[1], 10)
                for background in np.linspace(background_range[0], background_range[1], 10)]

    def makeVtkFile(self, shape, dir):
        array = np.array(shape)

        with tempfile.NamedTemporaryFile(mode='w+', dir=dir, suffix='.vtk', delete=False) as f:
            filename = f.name

            f.write("# vtk DataFile Version 2.0\n")
            f.write("Active Registration Model Shape\n")
            f.write("ASCII\n")
            f.write("DATASET POLYDATA\n")
            f.write("POINTS %i float\n" % array.shape[0])

            for point in array:
                for p in point:
                    f.write("%f " % p)

                f.write("\n")

        return filename

    def makeGridImage(self, image_size, center, square_size):
        x = cycle(np.linspace(0, 1, image_size[0] // 10))
        y = cycle(np.linspace(0, 1, image_size[1] // 10))
        array = np.zeros(image_size, np.float)
        for i in range(center[0] - square_size[0] // 2, center[0] + square_size[0] // 2):
            m = round(next(x))
            for j in range(center[1] - square_size[1] // 2, center[1] + square_size[1] // 2):
                array[i,j] = m + round(next(y)) + 1

        return sitk.GetImageFromArray(array)

    def makeCheckerBoardImage(self, image_size):
        return sitk.CheckerBoard(sitk.GetImageFromArray(np.zeros(image_size, np.float)),
                                 sitk.GetImageFromArray(np.ones(image_size, np.float)), (10, 10))


    def setUp(self):
        center_lower = 40
        center_upper = 60
        shape_num = 10
        self.width = self.height = 40
        grid_num = 10

        self.center = (50, 50)
        self.size = (100, 100)
        self.movingGridImage = self.makeGridImage(self.size, (60, 60), (self.width, self.height))  # offset from the mean shape
        self.checkerBoardImage = self.makeCheckerBoardImage(self.size)

        # Shape model
        self.gridShapesTranslation = self.makeGridShapesTranslation(center_lower, center_upper, shape_num, self.width, self.height, grid_num)

        # Intensity model
        self.squareImagesIntensityModel = self.makeSquareImagesIntensityModel(self.size, self.center, (self.width, self.height), (10, 20), (0, 10))

    def register(self, fixedImage, movingImage, dir, testName, parameterMap):
        # Write files to disk in a non-temporary directory for registering with command-line elastix
        # in an external IDE for debugging
        if True:
            sitk.WriteImage(fixedImage, os.path.join("/tmp", testName + "_fixedImage.nii"))
            sitk.WriteImage(movingImage, os.path.join("/tmp", testName + "_movingImage.nii"))
            sitk.WriteImage(self.checkerBoardImage, os.path.join("/tmp", testName + "_checkerBoardImage.nii"))
            parameterMapFileName = os.path.join("/tmp", testName + "_parameterMap.txt")
            sitk.WriteParameterFile(parameterMap, parameterMapFileName)

        silx = sitk.ElastixImageFilter()
        silx.SetFixedImage(fixedImage)
        silx.SetMovingImage(movingImage)
        silx.SetParameterMap(parameterMap)
        silx.Execute()
        sitk.WriteImage(silx.GetResultImage(), os.path.join(dir, testName + "_resultImageWithActiveRegistrationModel.nii"))

        sitx = sitk.TransformixImageFilter()
        sitx.ComputeDeformationFieldOff()

        sitk.WriteImage(fixedImage, os.path.join(dir, testName + "_fixedImage.nii"))
        sitk.WriteImage(movingImage, os.path.join(dir, testName + "_movingImage.nii"))

        transformParameterMap = silx.GetTransformParameterMap()

        sitx.SetTransformParameterMap(silx.GetTransformParameterMap())
        sitx.ComputeDeformationFieldOn()
        sitx.Execute()
        sitk.WriteImage(sitx.GetDeformationField(), os.path.join(dir, testName + "_deformationFieldWithActiveRegistrationModel.nii"))

        sitk.WriteImage(self.movingGridImage, os.path.join(dir, testName + "_gridImage.nii"))
        sitx.ComputeDeformationFieldOff()
        sitx.SetMovingImage(self.movingGridImage)
        sitx.Execute()
        sitk.WriteImage(sitx.GetResultImage(), os.path.join(dir, testName + "_gridImageTransformedWithActiveRegistrationModel.nii"))

        sitk.WriteImage(self.checkerBoardImage, os.path.join(dir, testName + "_checkerBoardImage.nii"))
        sitx.SetMovingImage(self.checkerBoardImage)
        sitx.Execute()
        sitk.WriteImage(sitx.GetResultImage(), os.path.join(dir, testName + "_checkerBoardImageTransformedWithActiveRegistrationModel.nii"))

        # Now the whole thing again without shape metric
        parameterMap["Metric"] = ["AdvancedMeanSquares"]

        silx.SetFixedImage(fixedImage)
        silx.SetMovingImage(movingImage)
        silx.SetParameterMap(parameterMap)
        silx.Execute()
        sitk.WriteImage(silx.GetResultImage(), os.path.join(dir, testName + "_resultImage.nii"))

        sitx.ComputeDeformationFieldOn()
        sitx.Execute()
        sitk.WriteImage(sitx.GetDeformationField(), os.path.join(dir, testName + "_deformationField.nii"))

        sitx.SetTransformParameterMap(silx.GetTransformParameterMap())
        sitx.ComputeDeformationFieldOff()
        sitx.SetMovingImage(self.movingGridImage)
        sitx.Execute()
        sitk.WriteImage(sitx.GetResultImage(), os.path.join(dir, testName + "_gridImageTransformed.nii"))

        sitx.SetMovingImage(self.checkerBoardImage)
        sitx.Execute()
        sitk.WriteImage(sitx.GetResultImage(), os.path.join(dir, testName + "_checkerBoardImageTransformed.nii"))

        return transformParameterMap

    def test_ActiveRegistrationModelShapeMetric(self):
        fixedImage = self.makeSquareImageShapeModel(self.size, self.center, (self.width, self.height)) # centered on the mean shape
        movingImage = self.makeSquareImageShapeModel(self.size, (60, 60), (self.width, self.height)) # offset from the mean shape

        parameterMap = sitk.GetDefaultParameterMap("bspline", 1)
        parameterMap["Metric"] = ["AdvancedMeanSquares", "ActiveRegistrationModelShapeMetric"]
        parameterMap["FinalGridSpacingInPhysicalUnits"] = ["10", "10", "10"]
        parameterMap["FinalBSplineInterpolationOrder"] = ["0"]
        parameterMap["Metric1Weight"] = ["0.01"]

        with tempfile.TemporaryDirectory(dir="/tmp") as d:
            gridShapesTranslationFileNames = [self.makeVtkFile(gridShapeTranslation, d)
                                              for gridShapeTranslation in self.gridShapesTranslation]

            parameterMap["Registration"] = ["MultiMetricMultiResolutionRegistration"]
            parameterMap["BuildShapeModel1"] = [d]
            parameterMap["ReferenceShape1"] = [gridShapesTranslationFileNames[0]]
            parameterMap["SaveShapeModel1"] = [os.path.join(d, "test_ActiveRegistrationModelShapeMetric_shapeModel.hdf5")]
            parameterMap["WriteShapeModelMeanShapeAfterRegistration"] = ["true"]
            parameterMap["WriteShapeModelFinalReconstructionAfterRegistration"] = ["true"]
            parameterMap["WriteShapeModelFinalReconstructionProbabilityAfterRegistration"] = ["false"]
            parameterMap["WriteShapeModelPrincipalComponentsAfterRegistration"] = ["true"]
            parameterMap["WriteShapeModelReconstructionAfterEachResolution"] = ["false"]
            parameterMap["WriteShapeModelReconstructionAfterEachIteration"] = ["false"] # Writes a lot of shapes to disk

            sitk.PrintParameterMap(parameterMap)
            parameterMapFileName = os.path.join(d, "test_ActiveRegistrationModelShapeMetric_parameterMap.txt")
            sitk.WriteParameterFile(parameterMap, parameterMapFileName)
            print("\nWrote paramter file %s" % parameterMapFileName)

            transformParameterMap = self.register(fixedImage, movingImage, d, "test_ActiveRegistrationModelShapeMetric", parameterMap)
            a = 1
            # TODO: Add regression test

    def test_ActiveRegistrationModelIntensityMetric(self):
        # With these foreground and background values the movingImage square tend to move towards the background
        # and away from the fixedImage square - unless you take into account the variation in the training set :)
        fixedImage = self.makeSquareImageIntensityModel(self.size, self.center, (self.width, self.height), 15, 5) # Mean image has 15 as foreground and 5 as background
        movingImage = self.makeSquareImageIntensityModel(self.size, (60, 60), (self.width, self.height), 5, 15)

        parameterMap = sitk.GetDefaultParameterMap("bspline", 1)
        parameterMap["Metric"] = ["ActiveRegistrationModelIntensityMetric"]
        parameterMap["FinalGridSpacingInPhysicalUnits"] = ["10", "10", "10"]
        parameterMap["FinalBSplineInterpolationOrder"] = ["0"]

        with tempfile.TemporaryDirectory(dir="/tmp") as d:
            [sitk.WriteImage(image, os.path.join(d, str(i) + ".nii")) for i, image in enumerate(self.squareImagesIntensityModel)]

            parameterMap["Registration"] = ["MultiMetricMultiResolutionRegistration"]
            parameterMap["BuildIntensityModel0"] = [d]
            parameterMap["ReferenceImage0"] = [os.path.join(d, "1.nii")]
            parameterMap["SaveIntensityModel0"] = [os.path.join(d, "test_ActiveRegistrationModelIntensityMetric_intensityModel.hdf5")]
            parameterMap["WriteIntensityModelMeanImageAfterRegistration"] = ["true"]
            parameterMap["WriteIntensityModelFinalReconstructionAfterRegistration"] = ["true"]
            parameterMap["WriteIntensityModelFinalReconstructionProbabilityAfterRegistration"] = ["false"]
            parameterMap["WriteIntensityModelPrincipalComponentsAfterRegistration"] = ["true"]
            parameterMap["WriteIntensityModelReconstructionAfterEachResolution"] = ["false"]
            parameterMap["WriteIntensityModelReconstructionAfterEachIteration"] = ["false"] # Writes a lot of images to disk

            sitk.PrintParameterMap(parameterMap)
            parameterMapFileName = os.path.join(d, "test_ActiveRegistrationModelIntensityMetric_parameterMap.txt")
            sitk.WriteParameterFile(parameterMap, parameterMapFileName)
            print("\nWrote paramter file %s" % parameterMapFileName)

            transformParameterMap = self.register(fixedImage, movingImage, d, "test_ActiveRegistrationModelIntensityMetric", parameterMap)
            a = 1
            # TODO: Add regression test


    # TODO: Intensity+Shape model and inverted intensities
    # Overleaf: Add these experiments to document



if __name__ == '__main__':
    unittest.main()
