SimpleElastix
=============
[![Build Status](https://travis-ci.org/kaspermarstal/SimpleElastix.svg?branch=SimpleElastix)](https://travis-ci.org/kaspermarstal/SimpleElastix)

Medical image registration is the process of transforming images into a common coordinate system so corresponding pixels represent homologous biological points. This is a prerequisite for a wide range of medical image analysis tasks and a key algorithmic component for statistical analysis and machine learning in medical image processing. The goal of SimpleElastix is to bring the robust medical image registration algorithms of the [elastix](http://elastix.isi.uu.nl/ "Elastix website") library to a wider audience by integrating elastix with [SimpleITK](https://github.com/SimpleITK/SimpleITK "SimpleITK github repository"). This package provides

- elastix and transformix bindings for Python, Java, R, Ruby, Octave, Lua, Tcl and C# (see [elastix manual](http://elastix.isi.uu.nl/download/elastix_manual_v4.7.pdf "elastix manual") for a list of supported registration algorithms).
- A user-friendly API that aligns with the design philosophy of SimpleITK, developed specifically for rapid prototyping and use in scripting languages. If you are interested, [The Design of SimpleITK](http://www.ncbi.nlm.nih.gov/pmc/articles/PMC3874546/ "PubMed") is a great read.
- Pre-configured parameter files that should serve as good starting points for new users.
- A SuperBuild that automatically compiles and installs SimpleElastix and any dependencies.
- The complete set of SimpleITK image processing algorithms.

Say you need to compare the volume, mean intensity and standard deviation of (possibly multiple) anatomical structures across a population of images using an atlas segmentation. This is accomplished using the following lines of Python code:

```python
import SimpleITK as sitk

# The atlas and associated segmentation is loaded once and held in memory
movingImage = sitk.ReadImage('movingImage.hdr')
movingLabel = sitk.ReadImage('movingLabel.hdr')

# Images are loaded from disk one at a time
population = ['image1.hdr', 'image2.hdr', ... , 'imageN.hdr']

selx = sitk.SimpleElastix()
selx.SetMovingImage(movingImage)
selx.SetParameterMap(selx.GetDefaultParameterMap('nonrigid'))

for filename in population
  # Register images
  fixedImage = sitk.ReadImage(filename)
  selx.SetFixedImage(fixedImage)
  selx.Execute()

  # Transform label map using the deformation field from above and compute statistics
  resultLabel = sitk.SimpleTransformix(movingLabel, selx.GetTransformParameters())
  sitk.LabelStatisticsImageFilter(fixedImage, resultLabel)
```

That was easy. The example demonstrates the efficiency of combining SimpleElastix's object oriented interface (the way we used elastix to register images) and procedural interface (the way we used transformix to warp labels) with SimpleITK (the way we computed statistics). Previously, using elastix and transformix on large datasets would incur a significant overhead, from scripting command line invocations and arguments to copying images and transform parameter files across folders. With SimpleElastix this complexity is easier to manage and more memory and disk I/O efficient. For more examples see below or the [Examples/SimpleElastix](Examples/SimpleElastix) directory.

### Procedural Interface
SimpleElastix provides a procedural inteface that aligns well with the design philosophy of SimpleITK. This directly invokes registration much like the elastix command line interface. 

```python
import SimpleElastix as sitk

resultImage = sitk.SimpleElastix(sitk.ReadImage(fixedImage), sitk.ReadImage(movingImage), sitk.ReadParameterFile('pf.txt'))
```

Loading images that already recide in memory does not count extra towards your RAM limit as only pointers are passed. In the next example, we first perform affine initialization and feed the resulting image to a non-rigid registration algorithm. The same fixed image is used in both registrations. 

```python
import SimpleElastix as sitk

fixedImage = sitk.ReadImage('fixedImage.hdr');
affineMovingImage = sitk.SimpleElastix(fixedImage, sitk.ReadImage('movingImage.hdr'), 'affine')
registeredImage = sitk.SimpleElastix(fixedImage, affineMovingImage, 'nonrigid')
```


### Object Oriented Interface
While the procedural interface may be useful in rapid prototyping, it trades off flexibility for code simplicity. In the example above, the final deformation field cannot be retrived and applied to another image. This is a problem if you want to subsequently warp segmentations as we did in the first example. Further, image quality is reduced from resampling the resulting image twice. To this end, SimpleElastix also comes with a powerful object oriented interface suitable for more advanced use cases and scripting purposes. In the next example, we perform groupwise registration.

```python
import SimpleITK as sitk

# First we concatenate the ND images into one (N+1)D image
population = ['image1.hdr', 'image2.hdr', ... , 'imageN.hdr']
vectorOfImages = sitk.VectorOfImage()
vectorOfImages = [vectorOfImages.push_back(sitk.ReadImage(image)) for image in population]
image4d = sitk.JoinSeriesFilter(vectorOfImages)

# Instantiate an elastix object 
selx = sitk.SimpleElastix()

# The groupwise transform works only on the moving image. However, a 
# dummy fixed image is needed to prevent elastix from throwing errors
selx.SetFixedImage(image4d) 
selx.SetMovingImage(image4d)

# Add preconfigured groupwise parameter map and run the registration
p = selx.GetDefaultParameterMap('groupwise')
selx.SetParameterMap(p)
selx.Execute()
```

### Parameter Maps
In addition to loading your own parameter files from disk, you can construct parameter maps programmatically from SimpleElastix's parameter map interface. This interface works seamlessly with native types of your target language. In python, a parameter map is a dictionary-like structure that you can call `keys(), clear()`, `has_key()` on etc and even iterate over. 

```python
import SimpleITK as sitk
selx = sitk.SimpleElastix()

# The dictionary-like object works as you'd expect
p = sitk.ParameterMap()
p['Registration'] = ['MultiMetricMultiResolutionRegistration']
p['Metric'] = ['NormalizedMutualInformation', 'TransformBendingEnergyPenalty']
p['Transform'] = ['AffineTransform']
p['FixedImagePyramidSchedule'] = ['8', '4', '2', '1']

# Lists of parameter maps can be encapsulated in a C-style vector. Running 
# SimpleElastix with a list of parameter maps will run multiple registrations 
# consecutively in one go. 
plist = ParameterMapList()
plist.push_back(p)

# The following calls will initialize a new parameter map with a nonrigid 
# transform at position two in the list
plist.push_back(sitk.GetDefaultParameterMap('nonrigid'))

# Passing the above list will cause elastix to run an affine initialization
# followed by a nonrigid registration 
selx.SetParameterMapList(plist) 
selx.Execute()  
```

At the moment, the elastix library API does not support using multiple fixed and moving images so SimpleElastix doesn't either.

### Building with the SuperBuild
SimpleElastix integrates elastix and transformix with the SimpleITK SuperBuild. Simply clone this repository and invoke the SuperBuild.

```
git clone https://github.com/kaspermarstal/SimpleElastix
mkdir build
cd build
ccmake ../SimpleElastix/SuperBuild
make -j4
```

The SuperBuild will download and install dependencies (elastix, ITK, SimpleITK and SWIG) and compile SimpleElastix. Target language dependencies need to be pre-installed, e.g. `sudo apt-get install cmake swig monodevelop r-base r-base-dev ruby python python-dev tcl tcl-dev tk tk-dev` if you are running Linux. Note that this project takes around an hour to build on a quad-core machine.

### Building Manually
This is not the recommended way of building SimpleElastix but it can be useful if you want to use a system version of ITK, SWIG or your own version of elastix. 

1. Setup the prerequisites
 - `sudo apt-get install cmake swig monodevelop r-base r-base-dev ruby python python-dev tcl tcl-dev tk tk-dev`.
2. Install the matching version of SWIG >= 2.0.12
3. Download elastix
4. Configure elastix using CMake
 - BUILD_TESTING=OFF, BUILD_EXECUTABLE=OFF, BUILD_SHARED_LIBRARIES=ON, USE_KNNGraphAlphaMutualInformationMetric=OFF 
 - Set appropriate ELASTIX_IMAGE_2/3/4D_PIXELTYPES and any components that you might require
5. Build elastix
6. Download the SimpleITK source code from the SourceForge page
7. Download the matching version of ITK
 - e.g. SimpleITK 0.9 uses ITK 4.6.1 (tag v4.6.1)
8. Configure ITK using CMake
 - BUILD_EXAMPLES=OFF, BUILD_TESTING=OFF, BUILD_SHARED_LIBS=OFF, ITK_USE_REVIEW=ON, ITK_WRAP_*=OFF
9. Build ITK
 - Be sure to note the build settings e.g. Release x64
10. Configure SimpleITK using CMake
 - Set ITK_DIR to the location of the ITK build location from the previous steps
 - SET ELASTIX_DIR to the location of the elastix build location from the previous steps
Build SimpleITK
 - Be sure to configure the build settings exactly the same as ITK e.g. Release x64

### Testing
Only Python wrappers has been tested extensively. To run these tests,

1. Install the built python package into the system Python by running `python setup.py install` in the `SimpleITK-build/Wrapping/PythonPackage` directory.
2. Invoke the `selxSimpleElastixTest.py` and `selxSimpleTrasnformixTest.py` in the [Testing/Unit](Testing/Unit) directory.

Pull requests are welcome if you want to contribute with tests for other languages. 

### Known Issues
- Assigning a parameter in a parameter map list silently fails (e.g. `plist[1]['Transform'] = ['BSplineTrasnform']`). A workaround is to assign the value directly to the parameter map before adding the map to the list.

### About
If you are interested in my work you are most welcome to visit [my website](https://kaspermarstal.github.io).
