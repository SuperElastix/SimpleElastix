import SimpleITK as sitk
import numpy as np
import unittest

class TestSimpleElastix(unittest.TestCase):
    """This tests the SimpleElastix class. """

    def setUp(self):
        pass

    def assertImageNDArrayEquals(self, img, nda, msg=""):
        for p,n in zip(img, nda.flat):
            self.assertEqual( p, n, msg )

    def test_exists(self):
        # Make sure SimpleElastix is available from this SimpleITK module
        self.assertTrue("SimpleElastix" in dir(sitk))

    def test_parametermap(self):
        p = sitk.ParameterMap()

        p['key'] = ['value']
        self.assertTrue(p.has_key('key'))
        self.assertTrue(p['key'] == ('value',))
        self.assertTrue(p['key'][0] == 'value')

        p['vector'] = ['0', '1']
        self.assertTrue(p['vector'] == ('0', '1'))
        self.assertTrue(p['vector'][0] == '0')
        self.assertTrue(p['vector'][1] == '1')

    def test_parametermaplist(self):
        plist = sitk.ParameterMapList()

        p1 = sitk.ParameterMap()
        p1['key'] = ['value']
        plist.push_back(p1)
        self.assertTrue(plist[0].has_key('key'))
        self.assertTrue(plist[0]['key'] == ('value',))
        self.assertTrue(plist[0]['key'][0] == 'value')

        p2 = sitk.ParameterMap()
        p2['vector'] = ['0', '1']
        plist.push_back(p2)
        self.assertTrue(plist[1]['vector'] == ('0', '1'))
        self.assertTrue(plist[1]['vector'][0] == '0')
        self.assertTrue(plist[1]['vector'][1] == '1')

        self.assertTrue(plist.size() == 2)
        plist.pop()
        self.assertTrue(plist.size() == 1)

        # TODO: Report to SWIG dev that plist[1]['key'] = ['value'] does not work

    def test_defaultparametermaps(self):
        plist = sitk.ParameterMapList()

        p1 = sitk.GetDefaultParameterMap('translation')
        self.assertTrue(p1['Registration'][0] == 'MultiResolutionRegistration')
        self.assertTrue(p1['Transform'][0] == 'TranslationTransform')
        self.assertTrue(p1['Metric'][0] == 'AdvancedMattesMutualInformation')
        self.assertTrue(p1['MaximumNumberOfIterations'][0] == '32')

        p2 = sitk.GetDefaultParameterMap('rigid')
        self.assertTrue(p2['Registration'][0] == 'MultiResolutionRegistration')
        self.assertTrue(p2['Transform'][0] == 'EulerTransform')
        self.assertTrue(p2['Metric'][0] == 'AdvancedMattesMutualInformation')
        self.assertTrue(p2['MaximumNumberOfIterations'][0] == '64')

        p3 = sitk.GetDefaultParameterMap('affine')
        self.assertTrue(p3['Registration'][0] == 'MultiResolutionRegistration')
        self.assertTrue(p3['Transform'][0] == 'AffineTransform')
        self.assertTrue(p3['Metric'][0] == 'AdvancedMattesMutualInformation')
        self.assertTrue(p3['MaximumNumberOfIterations'][0] == '128')

        p4 = sitk.GetDefaultParameterMap('nonrigid')
        self.assertTrue(p4['Registration'][0] == 'MultiMetricMultiResolutionRegistration')
        self.assertTrue(p4['Transform'][0] == 'BSplineTransform')
        self.assertTrue(p4['Transform'][1] == 'TransformBendingEnergyPenalty')
        self.assertTrue(p4['Metric'][0] == 'AdvancedMattesMutualInformation')
        self.assertTrue(p4['Metric0Weight'][0] == '0.001')
        self.assertTrue(p4['Metric1Weight'][0] == '0.999')
        self.assertTrue(p4['MaximumNumberOfIterations'][0] == '256')

        p5 = sitk.GetDefaultParameterMap('groupwise')
        self.assertTrue(p5['Registration'][0] == 'MultiResolutionRegistration')
        self.assertTrue(p5['Transform'][0] == 'BSplineStackTransform')
        self.assertTrue(p5['Metric'][0] == 'VarianceOverLastDimensionMetric')
        self.assertTrue(p5['MaximumNumberOfIterations'][0] == '512')

    def test_proc_interface(self):
        array = np.linspace(0, 119, 120).reshape(4,5,6).astype(np.int16)
        fixedImage = sitk.GetImageFromArray(array)
        movingImage = sitk.GetImageFromArray(array)
        
        resultImage = sitk.elastix(fixedImage,movingImage,'affine')
        a = np.ndarray.flatten(sitk.GetArrayFromImage(resultImage))
        b = np.ndarray.flatten(array)

         # Last pixel of each row is round to floor due to linear interpolator edgecase
        self.assertTrue(sum(abs(a-b)) < 100.01)
        self.assertTrue(sum(abs(a-b)) > 99.99)

        # Running twice should produce the same result
        resultImage2 = sitk.elastix(fixedImage,movingImage,'affine')
        self.assertTrue(sum(abs(resultImage-resultImage2)) < 1e-16)

    def test_oo_interface(self):
        array = np.linspace(0, 119, 120).reshape(4,5,6).astype(np.int16)
        fixedImage = sitk.GetImageFromArray(array)
        movingImage = sitk.GetImageFromArray(array)

        selx = sitk.SimpleElastix()
        selx.SetFixedImage(fixedImage)
        selx.SetMovingImage(movingImage)
        selx.SetParameterMap(sitk.GetDefaultParameterMap('affine'))
        selx.LogToConsoleOff()
        selx.Execute()

        resultImage = selx.GetResultImage()
        a = np.ndarray.flatten(sitk.GetArrayFromImage(resultImage))
        b = np.ndarray.flatten(array)

        # Last pixel of each row is round to floor due to linear interpolator edgecase
        self.assertTrue(sum(abs(a-b)) < 100.01)
        self.assertTrue(sum(abs(a-b)) > 99.99)

        # Fixed image buffered region is emptied when running registration so can't run twice
        # fixedImage-resultImage


if __name__ == '__main__':
    unittest.main()
