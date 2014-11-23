SimpleElastix
=============

The goal of this project is to make elastix's robust registration algorithms accessible to a wider audience by integrating the [elastix medical image registration library](http://elastix.isi.uu.nl/ "Elastix website") with [SimpleITK](https://github.com/SimpleITK/SimpleITK "SimpleITK github repository"). This approach brings the robust language wrapping and automated build infrastructure of SimpleITK to elastix and transformix. This package provides

- elastix and transformix bindings for Python, Java, R, Ruby, Octave, Lua, Tcl and C#
- An user-friendly API that aligns with the design philosophy of SimpleITK. If you are interested, [The Design of SimpleITK](http://www.ncbi.nlm.nih.gov/pmc/articles/PMC3874546/ "PubMed article") is a great read.
- Pre-configured parameter files that should serve as good starting points for new users
- SuperBuild that automatically compiles and installs SimpleElastix and its dependencies (elastix, ITK, SimpleITK, SWIG and target language dependencies)
- The usual SimpleITK image processing algorithms. 

Like SimpleITK, SimpleElastix has been designed specifically for rapid prototyping and use in scripting languages. Previously, using elastix and transformix on large datasets would incur a significant overhead from scripting command line invocations and arguments to copying images and transform parameter files across folders. With SimpleElastix this complexity is easier to manage and more memory and disk I/O efficient. 

Let's see some code. Say you need to compare the volume, mean intensity and standard deviation of multiple segmented structures across a population of images but only have one segmentation. This accomplished with the following python code:

```python
import SimpleElastix as selx

# These images are loaded once and held in memory
movingImage = selx.ReadImage('movingImage.hdr')
movingLabel = selx.ReadImage('movingLabel.hdr')

# These images are loaded from disk one at a time
population = ['image1.hdr', 'image2.hdr', ... , 'imageN.hdr']

elastix = selx.SimpleElastix();
elastix.SetMovingImage(movingImage)
elastix.SetParameterMap('defaultNonrigidRegistration')

# Warp the segmentation to each image in the population
for fixedImage in population
  # Register images
  elastix.SetFixedImage(selx.ReadImage(fixedImage))
  elastix.Run()

  # Transform label map using the deformation field from above and compute statistics
  resultLabel = selx.SimpleTransformix(movingLabel, elastix.GetTransformParameters())
  selx.LabelStatisticsImageFilter(elastix.GetResultImage(), resultLabel)
  
```

This example demonstrates the efficiency of combining SimpleElastix's object oriented interface (the way we used elastix to register images) and procedural interface (the way we used transformix to warp labels) with SimpleITK (the way we computed statistics). For more such examples, see below or the [Examples/SimpleElastix](https://github.com/kaspermarstal/SimpleElastix/tree/SimpleElastix/Examples/SimpleElastix "SimpleElastix examples") directory. 

Wrapping is accomplished through SWIG thanks to the elastix library interface. In principle, any language wrapped by SWIG should be applicable to this project. SimpleElastix is licensed under the Apache 2.0 License in the same way as ITK, SimpleITK and elastix.

More Examples
-------------

SimpleElastix provides a procedural inteface that aligns well with the design philosophy of SimpleITK that reduces registration to a one-liner. The procedural interface hides the elastix API's object oriented methods, templated types and directly invokes registration. 

```python
import SimpleElastix as selx

resultImage = selx.SimpleElastix(selx.ReadImage(fixedImage), selx.ReadImage(movingImage), selx.ReadParameterFile('pf.txt'))
```

Loading images that already recide in memory does not count extra towards your RAM limit as only pointers are passed. In the next example, we first perform affine initialization and feed the resulting image to a non-rigid registration algorithm. The same fixed image is loaded once and used in both registrations. Notice the use of the default registration configurations that come with SimpleElastix.

```python
import SimpleElastix as selx

fixedImage = selx.ReadImage('fixedImage.hdr');
affineMovingImage = selx.SimpleElastix(fixedImage, selx.ReadImage('movingImage.hdr'), 'defaultAffineParameterMap')
registeredImage = selx.SimpleElastix(fixedImage, affineMovingImage, 'defaultNonrigidParameterMap')
```

That was easy. However, the procedural interface trades off code simplicity for flexibility. In the above examples, the final deformation field cannot be retrived and applied to another image since portable language wrapping dictates only one return object per function call (in this case the image). That is a problem if, for example, you want to subsequently warp segmentations of the moving image as we did in the first example. Further, in the case above image quality is reduced from resampling resulting image twice.

Therefore SimpleElastix also comes with a powerful object oriented interface suitable for more advanced use cases and scripting purposes.

```python
import SimpleElastix as selx

# Here we instantiate an elastix object that will hold you data and configuration
elastix = selx.SimpleElastix()

elastix.SetFixedImage(selx.ReadImage('fixedImage.hdr'))
elastix.SetMovingImage(selx.ReadImage('movingImage.hdr')

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
selx.Show(elastix.GetResultImage())
```

You can also construct your parameter file from SimpleElastix's parameter file interface.

```python
import SimpleElastix as selx

p = selx.SimpleElastix().ParameterMap()

# SetParameter() overrides existing parameters or creates them if none exist
p.SetParameter("Metric", "NormalizedCorrelationCoefficient")    # this overrides any previous declaration
p.AppendParameter("Metric", "TransformBendingEnergyPenalty")    # the registration now uses two metrics

# The above can also be achieved using native arrays of your target language. AddParameter() does not 
# override existing parameters but will throw a warning instead (yes, this would throw a warning)
p.AddParameter("Metric", ["AdvancedMattesMutualInformationMetric", "TransformBendingEnergyPenalty"])

# SimpleElastix maps naturally the target language types
p.AddParameter("FixedImagePyramidSchedule", [8, 4, 2, 1])
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

This will download and compile SimpleElastix along with any dependencies (elastix, ITK, SimpleITK, SWIG and target language dependencies). If you do not use the superbuild and install ITK manually, make sure you have install version 4.6.1 or higher.
