try:
    import SimpleITK as sitk
except ImportError:
    print('Could not find SimpleITK.py. Compile SimpleElastix and execute \'sudo python PythonPackage/setup.py intall \' in the SimpleElastix\\SimpleITk-build\\Wrapping\' directory.')
    raise

import unittest

class TestSimpleElastix(unittest.TestCase):

    def test_exists(self):
        # Make sure SimpleElastix is available from this SimpleITK module
        self.assertTrue("SimpleElastix" in dir(sitk))

    def test_parametermap(self):
        p = sitk.ParameterMap()
        p['key'] = 'value'
        self.assertTrue(p.has_key('key')
        self.assertTrue(p['key'] == 'value')

    def test_parametermaplist(self):
        plist = sitk.ParameterMapList()
        p = sitk.ParameterMap()

        plist.push_back(p)
        plist.push_back(p)
        self.assertTrue(plist.size() == 2)

        plist.pop()
        self.assertTrue(plist.size() == 1)

    def test_defaultparametermaps(self):
        plist = sitk.ParameterMapList()

        a = sitk.GetDefaultParameterMap('rigid')
        plist.push_back(a)
        self.assertTrue(plist[0]['Metric'] == 'EulerTransform')

        b = sitk.GetDefaultParameterMap('affine')
        plist.push_back(b)
        self.assertTrue(plist[1]['Metric'] == 'AffineTransform')

        c = sitk.GetDefaultParameterMap('nonrigid')
        plist.push_back(c)
        self.assertTrue(plist[2]['Metric'][0] == 'BSplineTransform')
        self.assertTrue(plist[2]['Metric'][1] == 'TransformBendingEnergyPenalty')

        d = sitk.GetDefaultParameterMap('groupwise')
        plist.push_back(d)
        self.assertTrue(plist[3]['Metric'] == 'VarianceOverLastDimensionMetric')


if __name__ == '__main__':
    unittest.main()
    
