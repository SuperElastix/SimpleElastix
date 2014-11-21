SimpleElastix
=============

The goal of this project is to make elastix's robust registration algorithms accessible to a wider audience by integrating the [elastix medical image registration library](http://elastix.isi.uu.nl/ "Elastix website") with [SimpleITK](https://github.com/SimpleITK/SimpleITK "SimpleITK github repository"). This approach brings the robust language wrapping features and automated build infrastructure of SimpleITK to elastix and transformix. This package provides

- elastix and transformix bindings for Python, Java, R, Ruby, Octave, Lua, Tcl and C#
- Preconfigured parameter files for affine, non-rigid, groupwise and label map registration that should serve as good starting points for new users
- SuperBuild that automatically compiles and installs SimpleElastix and its dependencies (elastix, ITK, SimpleITK, SWIG and target language dependencies)
- The usual SimpleITK image processing algorithms. If you are interested in the design philosophy behind SimpleITK, [The Design of SimpleITK](http://www.ncbi.nlm.nih.gov/pmc/articles/PMC3874546/ "PubMed article") is a great read.

SimpleElastix has been designed specifically for rapid prototyping and use in scripting languages. Previously, using elastix and transformix on large datasets would incur a significant overhead from scripting command line invocations and arguments to copying images and transform parameter files across folders. With SimpleElastix this complexity is easier to manage and more memory and disk I/O efficient. 

Enough talk. Let's see some code. Say you need to compare the volume, mean intensity and standard deviation of multiple segmented structures across a population of images but only have one segmentation. Then, for each image in the population, you run the following python code:

```python
import SimpleElastix as sitk

referenceImage = sitk.ReadImage('referenceImage.hdr')
referenceLabel = sitk.ReadImage('referenceLabel.hdr')
population = ['image1.hdr', 'image2.hdr', ... , 'imageN.hdr']

elastix = sitk.SimpleElastix();
elastix.SetMovingImage(referenceImage)
elastix.SetParameterMap('defaultNonrigidRegistration')

# We warp the segmentation to each image in the population
for fixedImage in population
  # Register images
  elastix.SetFixedImage(fixedImage)
  elastix.Run()

  # Transform label map using the deformation field from above and compute statistics
  resultLabel = sitk.SimpleTransformix(referenceLabel, elastix.GetTransformParameters())
  sitk.LabelStatisticsImageFilter(elastix.GetResultImage(), resultLabel)
  
```

We could also have warped the images to the reference image domain and computed statistics here, registered images groupwise or registered all images to the reference and segmented the mean image. This example merely demonstrates efficiency of combining the the object oriented interface (the way we used elastix) and the procedural interface (the way we warped the reference labels) with SimpleITK (the way we computed statistics). There are more examples below and in the [Examples/SimpleElastix](https://github.com/kaspermarstal/SimpleElastix/tree/SimpleElastix/Examples/SimpleElastix "SimpleElastix examples") directory. 

Wrapping is accomplished through SWIG thanks to the elastix library interface. In principle, any language wrapped by SWIG should be applicable to this project. SimpleElastix is licensed under the Apache 2.0 License in the same way as ITK, SimpleITK and elastix.

More Examples
--------

SimpleElastix provides a procedural inteface that aligns well with the SimpleITK design philosophy and reduces registration to a one-liner. The procedural interface hides the elastix API's object oriented methods, templated types and directly invokes registration. 

```python
import SimpleITK as sitk

# The images and parameter file is loaded from disk
registeredImage = sitk.SimpleElastix('fixedImage.hdr', 'movingImage.hdr', 'parameterfile.txt')
```

In-memory images can also be passed to elastix. Loading an image from memory does not count extra towards your RAM limit as only a pointer is passed. Here, we first perform affine initialization and feed the resulting image to a non-rigid registration algorithm. Notice the use of the default registration configurations that come with SimpleElastix.

```python
import SimpleITK as sitk

fixedImage = sitk.ReadImage('fixedImage');
movingImage = sitk.ReadImage('movingImage');
affineInitializationImage = sitk.SimpleElastix(fixedImage, movingImage, 'defaultAffineParameterMap')
registeredImage = sitk.SimpleElastix(fixedImage, affineInitializationImage, 'defaultNonrigidParameterMap')
```

That was easy. However, the procedural interface trades off code simplicity for flexibility. The final deformation field cannot be retrived and applied to another image since portable language wrapping dictates only one return object per function call (in this case the image). This is a problem if, for example, you want to subsequently warp segmentations of the moving image as we did in the first example. Further, in the case above image quality is reduced from resampling resulting image twice.

Therefore, SimpleElastix also comes with a powerful object oriented interface suitable for more advanced use cases and scripting purposes.

```python
import SimpleITK as sitk

# Here we instantiate an elastix object that will hold you data and configuration
elastix = sitk.SimpleElastix()

# As with the procedural interface, images can loaded both from disk and memory.
elastix.SetFixedImage('fixedImage.hdr')
elastix.SetMovingImage(inMemoryMovingImage)

# Get a preconfigured parameter map and customize e.g. number of iterations to suit your needs
p = elastix.GetDefaultAffineParameters()
p.SetParameter("MaximumNumberOfIterations", 512)

# SetParameterMap() overrides existing parameter maps or create a new one if none exist
elastix.SetParameterMap(p)

# You can also load your own parameter files. In this case, AddParameterFile() will
# append nonrigid.txt to an internal list of parameter files
selx.AddParameterFile('nonrigid.txt')

# In this case, an affine registration will be run followed by non-rigid registration since the parameter
# files were added in this order. The moving image is only resampled after both registrations have run
elastix.Run()
sitk.Show(elastix.GetResultImage())
```

You can also construct your parameter file from SimpleElastix's parameter file interface.

```python
import SimpleITK as sitk

p = sitk.SimpleElastix().ParameterMap()

# SetParameter() overrides existing parameters or creates them if none exist
p.SetParameter("Metric", "NormalizedCorrelationCoefficient")    # this overrides any previous declaration
p.AppendParameter("Metric", "TransformBendingEnergyPenalty")    # the registration now uses two metrics

# The above can also be achieved using native arrays of your target language. AddParameter() does not 
# override existing parameters but will throw a warning instead (yes, this would throw a warning)
p.AddParameter("Metric", ["AdvancedMattesMutualInformationMetric", "TransformBendingEnergyPenalty"])

# SimpleElastix maps naturally the target language types
p.AddParameter("FixedImagePyramidSchedule", [8, 4, 2, 1])
```

Building
--------

SimpleElastix integrates elastix and transformix with the SimpleITK superbuild. Simply clone this repository invoke the superbuild (may take up to an hour on a quad-core machine).

```
git clone https://github.com/kaspermarstal/SimpleITK
mkdir build
cd build
ccmake ../SimpleElastix/SuperBuild
make -j4
```

This will download and compile SimpleElastix along with any dependencies (elastix, ITK, SimpleITK, SWIG and target language dependencies).

Notes
-----
- At the moment, the elastix library API does not support using multiple fixed and moving images so SimpleElastix doesn't either. 
