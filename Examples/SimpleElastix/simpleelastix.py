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

if __name__ == '__main__':
    unittest.main()
    
