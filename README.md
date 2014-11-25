SimpleElastix
=============

[Elastix](elastix.isi.uu.nl/download/elastix_manual_v4.7.pdf "elastix manual") is a powerful, state-of-the-art medical image registration library. The goal of this project is to make elastix's robust medical image registration algorithms accessible to a wider audience by integrating [elastix](http://elastix.isi.uu.nl/ "Elastix website") with [SimpleITK](https://github.com/SimpleITK/SimpleITK "SimpleITK github repository"). This approach brings the robust language wrapping and automated build infrastructure of SimpleITK to elastix and transformix. SimpleElastix provides

- elastix and transformix bindings for Python, Java, R, Ruby, Octave, Lua, Tcl and C#.
- A user-friendly API that aligns with the design philosophy of SimpleITK, developed specifically for rapid prototyping and use in scripting languages. If you are interested, [The Design of SimpleITK](http://www.ncbi.nlm.nih.gov/pmc/articles/PMC3874546/ "PubMed") is a great read.
- Pre-configured parameter files that should serve as good starting points for new users.
- The complete set of SimpleITK image processing algorithms.
- SuperBuild that automatically compiles and installs SimpleElastix and any dependencies.

Previously, using elastix and transformix on large datasets would incur a significant overhead from scripting command line invocations and arguments to copying images and transform parameter files across folders. With SimpleElastix this complexity is easier to manage and more memory and disk I/O efficient. 

How does SimpleElastix accomplish this? Let's look at some code. Say you need to compare the volume, mean intensity and standard deviation of multiple anatomical structures across a population of images using an atlas segmentation. The following lines of python code does this:

```python
import SimpleITK as sitk

# The atlas and associated segmentation is loaded once and held in memory
movingImage = sitk.ReadImage('movingImage.hdr')
movingLabel = sitk.ReadImage('movingLabel.hdr')

# These images are loaded from disk one at a time
population = ['image1.hdr', 'image2.hdr', ... , 'imageN.hdr']

selx = sitk.SimpleElastix();
selx.SetMovingImage(movingImage)
selx.SetParameterMap('defaultNonrigidRegistration')

# Warp the segmentation to each image in the population
for fixedImage in population
  # Register images
  selx.SetFixedImage(sitk.ReadImage(fixedImage))
  selx.Run()

  # Transform label map using the deformation field from above and compute statistics
  resultLabel = sitk.SimpleTransformix(movingLabel, selx.GetTransformParameters())
  sitk.LabelStatisticsImageFilter(selx.GetResultImage(), resultLabel)
```

That was easy. The example demonstrates the efficiency of combining SimpleElastix's object oriented interface (the way we used elastix to register images) and procedural interface (the way we used transformix to warp labels) with SimpleITK (the way we computed statistics). For more examples, see below or the [Examples/SimpleElastix](https://github.com/kaspermarstal/SimpleElastix/tree/SimpleElastix/Examples/SimpleElastix "SimpleElastix examples") directory. 


### Procedural Interface

SimpleElastix provides a procedural inteface that aligns well with the design philosophy of SimpleITK and reduces registration to a one-liner. The procedural interface hides the elastix API's object oriented methods and directly invokes registration. 

```python
import SimpleElastix as sitk

resultImage = sitk.SimpleElastix(sitk.ReadImage(fixedImage), sitk.ReadImage(movingImage), sitk.ReadParameterFile('pf.txt'))
```

Loading images that already recide in memory does not count extra towards your RAM limit as only pointers are passed. In the next example, we first perform affine initialization and feed the resulting image to a non-rigid registration algorithm. The same fixed image is loaded once and used in both registrations. Notice the use of the default registration configurations that come with SimpleElastix.

```python
import SimpleElastix as sitk

fixedImage = sitk.ReadImage('fixedImage.hdr');
affineMovingImage = sitk.SimpleElastix(fixedImage, sitk.ReadImage('movingImage.hdr'), 'defaultAffineParameterMap')
registeredImage = sitk.SimpleElastix(fixedImage, affineMovingImage, 'defaultNonrigidParameterMap')
```


### Object Oriented Interface

While the procedural interface may be useful in rapid prototyping, it trades off code simplicity for flexibility. In the above example, the final deformation field cannot be retrived and applied to another image since portable language wrapping dictates only one return object per function call (in this case the image). This is a problem if you want to subsequently warp segmentations as we did in the first example. Further, image quality is reduced from resampling resulting image twice. To this end, SimpleElastix also comes with a powerful object oriented interface suitable for more advanced use cases and scripting purposes.

```python
import SimpleITK as sitk

# Here we instantiate an elastix object that will hold you data and configuration
selx = sitk.SimpleElastix()

selx.SetFixedImage(sitk.ReadImage('fixedImage.hdr'))
selx.SetMovingImage(sitk.ReadImage('movingImage.hdr')

# Get a preconfigured parameter map and customize e.g. number of iterations to suit your needs
p = selx.GetDefaultAffineParameters()
p['MaximumNumberOfIterations'] = '512'

# SetParameterMap() overrides existing parameter maps or create a new one if none exist
selx.SetParameterMap(p)

# You can also load your own parameter files. In this case, AppendParameterMap() will
# append nonrigid.txt to an internal list of parameter files
selx.AppendParameterMap(selx.ReadParameterFile('nonrigid.txt'))

# An affine registration will be run followed by non-rigid registration since the parameter
# files were added in this order. The moving image is resampled only after both registrations have run
selx.Run()
sitk.Show(selx.GetResultImage())
```

### Parameter Maps
In addition to loading your own parameter files from disk, you can construct parameter maps programmatically from SimpleElastix's parameter map interface. SimpleElastix maps the native language array types to an internal C++-map structure that you can call `keys(), size()`, `count()` on etc and even iterate over. 

```python
import SimpleITK as sitk

# In python, ParameterMap() returns a dictionary-like object that works as you expect
p = sitk.ParameterMap()
p['Registration'] = 'MultiMetricMultiResolutionRegistration'
p['Metric'] = ['NormalizedMutualInformation', 'TransformBendingEnergyPenalty']
p['Transform'] = 'AffineTransform'
p['FixedImagePyramidSchedule'] = ['8', '4', '2', '1']

# Lists of parameter maps can encapsulated in a C-style vector that works just like its
# std::vector counterpart. This will invod eMultiple consecutive registrations in one go. 
plist = ParameterMapList()
plist.push_back(p)

# In most cases yoy can treat the parameter list as a native dictionary type. 
# The following call will initialize a new parameter map at position two in the list
plist[1]['Transform'] = 'BSplineTransform'

# Passing the above list will cause elastix to run an affine initialization followed by a nonrigid registration
selx = sitk.SimpleElastix()
selx.SetParameterMap( plist ) 
selx.Run()  # ... set required parameters, images etc first of course
```

At the moment, the elastix library API does not support using multiple fixed and moving images so SimpleElastix doesn't either.

Building
--------

SimpleElastix integrates elastix and transformix with the SimpleITK SuperBuild. Simply clone this repository and invoke the SuperBuild (may take up to an hour on a quad-core machine).

```
git clone https://github.com/kaspermarstal/SimpleElastix
mkdir build
cd build
ccmake ../SimpleElastix/SuperBuild
make -j4
```

SimpleElastix will be compiled along with any dependencies (elastix, ITK, SimpleITK, SWIG and target language dependencies). These are downloaded on the fly.
