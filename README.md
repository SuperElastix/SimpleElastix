What is SimpleElastix?
======================
Image registration is the process of transforming images into a common coordinate system so corresponding pixels represent homologous biological points. SimpleElastix is an extension of [SimpleITK](https://github.com/SimpleITK/SimpleITK "SimpleITK github repository") that offers a user-friendly API to the popular image registration algorithms of the [elastix](http://elastix.isi.uu.nl/ "Elastix website") C++ library. This makes state-of-the-art medical image registration really easy to do in languages like Python, Java, C# and R. This package provides

- elastix and transformix bindings for C++, Python, Java, R, Ruby, Octave, Lua, Tcl and C# (see [elastix manual](http://elastix.isi.uu.nl/download/elastix_manual_v4.7.pdf "elastix manual") for a list of supported registration algorithms).
- Pre-configured registration methods that work well in many cases and serve as starting points for tuning elastix to domain-specific applications.
- Installation guides, examples, and introductory material at [simpleelastix.readthedocs.org](https://simpleelastix.readthedocs.org/).
- A user-friendly API that aligns with the design philosophy of SimpleITK developed specifically for rapid prototyping. If you are interested, [The Design of SimpleITK](http://www.ncbi.nlm.nih.gov/pmc/articles/PMC3874546/ "PubMed") is a great read.
- The complete set of SimpleITK image processing algorithms.

Enough talk, time for some examples! We will use Python for the following code. Say you need to register two images. This can be accomplished with a single line of code:

```python
resultImage = SimpleITK.Elastix(sitk.ReadImage("fixedImage.dcm"), sitk.ReadImage("movingImage.dcm"))
```

Under the hood, Elastix will use stochastic optimization for maximum speed, a multi-resolution strategy and several different transforms of increasing complexity for maximum robustness. All aspects of the registration procedure can be customized via [parameter maps](https://simpleelastix.readthedocs.io/ParameterMaps.html). 

SimpleElastix can also be used for more complex image processing pipelines. Say you want to compare the volume, mean intensity and standard deviation of the intensity of anatomical structures across a population of images using an atlas segmentation. We can accomplish this task with the following lines of Python code:

```python
import SimpleITK as sitk

# The atlas and associated segmentation is loaded once and held in memory
movingImage = sitk.ReadImage('atlasImage.hdr')
movingLabel = sitk.ReadImage('atlasLabel.hdr')

# Images are loaded from disk one at a time. Here we specify an array of 
# paths to images which we will loop over. 
population = ['image1.dcm', 'image2.dcm', ... , 'imageN.dcm']

selx = sitk.ElastixImageFilter()
selx.SetMovingImage(movingImage)
selx.SetParameterMap(selx.GetDefaultParameterMap('nonrigid'))

for filename in population
  # Register images
  fixedImage = sitk.ReadImage(filename)
  selx.SetFixedImage(fixedImage)
  selx.Execute()

  # Transform label map using the deformation field from above
  resultLabel = sitk.Transformix(movingLabel, selx.GetTransformParameterMap())

  # Compute statistics for label 1
  LabelStatistics = sitk.LabelStatisticsImageFilter()
  LabelStatistics.Execute(fixedImage, sitk.Cast(resultLabel, sitk.sitkInt8))
  LabelStatistics.GetCount(1)
  LabelStatistics.GetMean(1)
  LabelStatistics.GetVariance(1)
  # etc etc
```

This example demonstrates the efficiency of combining SimpleElastix's object oriented interface (the way we used elastix to register images) and procedural interface (the way we used transformix to warp labels) with SimpleITK (the way we computed statistics). Previously, using elastix and transformix on large datasets would incur a significant overhead, from scripting command line invocations and arguments to copying images and transform parameter files across folders. With SimpleElastix this complexity is easier to manage and more memory and disk I/O efficient. For more examples see [the documentation](https://simpleelastix.readthedocs.org/). 

### Building with the SuperBuild
SimpleElastix integrates elastix and transformix with the SimpleITK SuperBuild. Simply clone this repository and invoke the SuperBuild as outlined in [the documentation](http://simpleelastix.readthedocs.org/GettingStarted.html). The SuperBuild will download and install dependencies (elastix, ITK, SimpleITK and SWIG) and compile SimpleElastix. Target language dependencies need to be pre-installed, e.g. `sudo apt-get install cmake swig monodevelop r-base r-base-dev ruby ruby-dev python python-dev tcl tcl-dev tk tk-dev`. Note that this project takes around an hour to build on a quad-core machine.

The documentation further describes how to [build SimpleElastix on Windows](http://simpleelastix.readthedocs.org/GettingStarted.html#Windows) and how to [build SimpleElastix manually](http://simpleelastix.readthedocs.org/GettingStarted.html#building-manually-on-linux) without the SuperBuild.

SimpleElastix has been tried and tested on Ubuntu 14.10 using GCC 4.9.2 and Clang 3.4.0, Mac OSX Yosemite using Apple Clang 600.0.56 and Windows 8.1 using Microsft Visual Studio 2012 C++ compiler.

### About
If you are interested in my work you are most welcome to visit [my website](https://kaspermarstal.github.io).
