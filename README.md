SimpleElastix
=============

The goal of SimpleElastix is to bring the robust medical image registration algorithms of [elastix](http://elastix.isi.uu.nl/ "Elastix website") to a wider audience by integrating elastix with [SimpleITK](https://github.com/SimpleITK/SimpleITK "SimpleITK github repository"). This package provides

- elastix and transformix bindings for Python, Java, R, Ruby, Octave, Lua, Tcl and C# (see [elastix manual](elastix.isi.uu.nl/download/elastix_manual_v4.7.pdf "elastix manual" for a list of supported algorithms).
- A user-friendly API that aligns with the design philosophy of SimpleITK, developed specifically for rapid prototyping and use in scripting languages. If you are interested, [The Design of SimpleITK](http://www.ncbi.nlm.nih.gov/pmc/articles/PMC3874546/ "PubMed") is a great read.
- Pre-configured parameter files that should serve as good starting points for new users.
- The complete set of SimpleITK image processing algorithms.
- SuperBuild that automatically compiles and installs SimpleElastix and any dependencies.

Previously, using elastix and transformix on large datasets would incur a significant overhead from scripting command line invocations and arguments to copying images and transform parameter files across folders. With SimpleElastix this complexity is easier to manage and more memory and disk I/O efficient. 

Let's look at some code. Say you need to compare the volume, mean intensity and standard deviation of (possibly multiple) anatomical structures across a population of images using an atlas segmentation. This is accomplished using the following lines of Python code:

```python
import SimpleITK as sitk

# The atlas and associated segmentation is loaded once and held in memory
movingImage = sitk.ReadImage('movingImage.hdr')
movingLabel = sitk.ReadImage('movingLabel.hdr')

# Images are loaded from disk one at a time
population = ['image1.hdr', 'image2.hdr', ... , 'imageN.hdr']

selx = sitk.SimpleElastix();
selx.SetMovingImage(movingImage)
selx.SetParameterMap('defaultNonrigidRegistration')

# Do the processing
for fixedImage in population
  # Register images
  selx.SetFixedImage(sitk.ReadImage(fixedImage))
  selx.Execute()

  # Transform label map using the deformation field from above and compute statistics
  resultLabel = sitk.SimpleTransformix(movingLabel, selx.GetTransformParameters())
  sitk.LabelStatisticsImageFilter(selx.GetResultImage(), resultLabel)
```

That was easy. The example demonstrates the efficiency of combining SimpleElastix's object oriented interface (the way we used elastix to register images) and procedural interface (the way we used transformix to warp labels) with SimpleITK (the way we computed statistics). For more examples, see below or the [Examples/SimpleElastix](https://github.com/kaspermarstal/SimpleElastix/tree/SimpleElastix/Examples/SimpleElastix "SimpleElastix examples") directory. 


### Procedural Interface

SimpleElastix provides a procedural inteface that aligns well with the design philosophy of SimpleITK and reduces registration to a one-liner. The procedural interface hides the elastix API's object oriented methods and directly invokes registration. 

```python
import SimpleElastix as sitk

resultImage = sitk.SimpleElastix(sitk.ReadImage(fixedImage), 
                                 sitk.ReadImage(movingImage),
                                 sitk.ReadParameterFile('pf.txt'))
```

Loading images that already recide in memory does not count extra towards your RAM limit as only pointers are passed. In the next example, we first perform affine initialization and feed the resulting image to a non-rigid registration algorithm. The same fixed image is used in both registrations. 

```python
import SimpleElastix as sitk

fixedImage = sitk.ReadImage('fixedImage.hdr');

affineMovingImage = sitk.SimpleElastix(fixedImage, 
                                       sitk.ReadImage('movingImage.hdr'),
                                       'defaultAffineParameterMap')

registeredImage = sitk.SimpleElastix(fixedImage,
                                     affineMovingImage,
                                     'defaultNonrigidParameterMap')
```


### Object Oriented Interface

While the procedural interface may be useful in rapid prototyping, it trades off code simplicity for flexibility. In the above example, the final deformation field cannot be retrived and applied to another image since portable language wrapping dictates only one return object per function call (in this case the image). This is a problem if you want to subsequently warp segmentations as we did in the first example. Further, image quality is reduced from resampling resulting image twice. To this end, SimpleElastix also comes with a powerful object oriented interface suitable for more advanced use cases and scripting purposes. In the next example, we perform true groupwise registration as described in [Metz et al 2012](http://#).

```python
import SimpleITK as sitk

# First we concatenate the ND images into one (N+1)D image
population = ['image1.hdr', 'image2.hdr', ... , 'imageN.hdr']
vectorOfImages = sitk.VectorOfImages()
vectorOfImages = [vectorOfImages.push_back(sitk.ReadImage(image)) for image in population]
image4d = sitk.JoinSeriesFilter(vectorOfImages)

# We instantiate an elastix object that will hold data and configuration  
selx = sitk.SimpleElastix()

# The groupwise transform works only on the moving image. However, a 
# dummy fixed image is needed to prevent elastix from throwing errors
selx.SetFixedImage(image4d) 
selx.SetMovingImage(image4d)

# Customize the preconfigured groupwise parameter map and run the registration
p = selx.GetDefaultGroupwiseNonRigidParameters()
p['MaximumNumberOfIterations'] = '1024'
selx.SetParameterMap(p)
selx.Execute()
```

### Parameter Maps
In addition to loading your own parameter files from disk, you can construct parameter maps programmatically from SimpleElastix's parameter map interface that works seamlessly with target language native types. In python, a parameter map is a dictionary-like structure that you can call `keys(), clear()`, `has_key()` on etc and even iterate over. 

```python
import SimpleITK as sitk
selx = sitk.SimpleElastix()

# The dictionary-like object that works as you'd expect
p = sitk.ParameterMap()
p['Registration'] = 'MultiMetricMultiResolutionRegistration'
p['Metric'] = ['NormalizedMutualInformation', 'TransformBendingEnergyPenalty']
p['Transform'] = 'AffineTransform'
p['FixedImagePyramidSchedule'] = ['8', '4', '2', '1']

# Lists of parameter maps can be encapsulated in a C-style vector. Running SimpleElastix with a
# list of parameter maps will run multiple registrations consecutively in one go. 
plist = ParameterMapList()
plist.push_back(p)

# The following call will initialize a new parameter map at position two in the list
plist[1]['Transform'] = 'BSplineTransform'
# ... set rest of parameters, images etc

# Passing the above list will cause elastix to run an affine initialization followed by a nonrigid registration
selx.SetParameterMap( plist ) 
selx.Execute()  
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

SimpleElastix will be compiled along with any dependencies (elastix, ITK, SimpleITK, SWIG and target language dependencies, these are downloaded on the fly). Note that this project takes a long time to build. On a quad-core machine it takes around and hour and if your machine has less than 16 GB RAM you will have to compile with even fewer cores. Because of the extreme build time and memory consumption I prefer to build with clang.

About
-----

If you are interested in my work you are most welcome to visit [my website](https://kaspermarstal.github.io).
