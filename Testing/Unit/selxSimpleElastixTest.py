import SimpleITK as sitk
import numpy as np
import unittest

class TestSimpleElastix(unittest.TestCase):
    """This tests the SimpleElastix class. """

    def setUp(self):
        pass

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

        p1 = sitk.GetDefaultParameterMap('rigid')
        plist.push_back(p1)
        self.assertTrue(plist[0]['Transform'][0] == 'EulerTransform')

        p2 = sitk.GetDefaultParameterMap('affine')
        plist.push_back(p2)
        self.assertTrue(plist[1]['Transform'][0] == 'AffineTransform')

        p3 = sitk.GetDefaultParameterMap('nonrigid')
        plist.push_back(p3)
        self.assertTrue(plist[2]['Transform'][0] == 'BSplineTransform')
        self.assertTrue(plist[2]['Transform'][1] == 'TransformBendingEnergyPenalty')

        p4 = sitk.GetDefaultParameterMap('groupwise')
        plist.push_back(p4)
        self.assertTrue(plist[3]['Transform'] == 'VarianceOverLastDimensionMetric')

    def test_registration(self):
        array = np.linspace(0, 59, 60 ).reshape(3,4,5)
        fixedImage = sitk.GetImageFromArray(array, sitk.sitkInt16)

        array = np.linspace(0, 59, 60 ).reshape(3,4,5)
        movingImage = sitk.GetImageFromArray(array, sitk.sitkInt16)

        selx = sitk.SimpleElastix()
        selx.SetFixedImage(fixedImage)
        selx.SetMovingImage(movingImage)
        selx.SetParameterMap(sitk.GetDefaultParameterMap('affine'))
        selx.Execute()

        resultImage = selx.GetResultImage()
        self.assertTrue(sum(abs(resultImage-fixedImage)) < 1e-3)


if __name__ == '__main__':
    unittest.main()
