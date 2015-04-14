SimpleElastix
=============
[![Build Status](https://travis-ci.org/kaspermarstal/SimpleElastix.svg?branch=SimpleElastix)](https://travis-ci.org/kaspermarstal/SimpleElastix)

Installation, examples, usage and introductory material is available at [simpleelastix.readthedocs.org](https://simpleelastix.readthedocs.org/). Tweet us [@SimpleElastix](https://twitter.com/SimpleElastix/)!

### What is SimpleElastix?
SimpleElastix is a medical image processing package that makes state-of-the-art medical image registration really easy to do. Image registration is the process of transforming images into a common coordinate system so corresponding pixels represent homologous biological points. This is a prerequisite for a wide range of medical image analysis tasks and a key algorithmic component for statistical analysis and machine learning in medical image processing. The goal of SimpleElastix is to bring the robust C++ medical image registration algorithms of the [elastix](http://elastix.isi.uu.nl/ "Elastix website") library to a wider audience by integrating elastix with [SimpleITK](https://github.com/SimpleITK/SimpleITK "SimpleITK github repository"). This package provides

- elastix and transformix bindings for Python, Java, R, Ruby, Octave, Lua, Tcl and C# (see [elastix manual](http://elastix.isi.uu.nl/download/elastix_manual_v4.7.pdf "elastix manual") for a list of supported registration algorithms).
- A user-friendly API that aligns with the design philosophy of SimpleITK, developed specifically for rapid prototyping and use in scripting languages. If you are interested, [The Design of SimpleITK](http://www.ncbi.nlm.nih.gov/pmc/articles/PMC3874546/ "PubMed") is a great read.
- Pre-configured parameter files that should serve as good starting points for new users.
- A SuperBuild that automatically compiles and installs SimpleElastix and any dependencies.
- The complete set of SimpleITK image processing algorithms.

Enough talk, time for some examples! Say you need to compare the volume, mean intensity and standard deviation of (possibly multiple) anatomical structures across a population of images using an atlas segmentation. This is accomplished using the following lines of Python code:

```python
import SimpleITK as sitk

# The atlas and associated segmentation is loaded once and held in memory
movingImage = sitk.ReadImage('atlasImage.hdr')
movingLabel = sitk.ReadImage('atlasLabel.hdr')

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

  # Transform label map using the deformation field from above
  resultLabel = sitk.Transformix(movingLabel, selx.GetTransformParameterMapList())

  # Compute statistics for label 1
  LabelStatistics = sitk.LabelStatisticsImageFilter()
  LabelStatistics.Execute(fixedImage, sitk.Cast(resultLabel, sitk.sitkInt8))
  LabelStatistics.GetCount(1)
  LabelStatistics.GetMean(1)
  LabelStatistics.GetVariance(1)
  # etc etc
```

That was easy. The example demonstrates the efficiency of combining SimpleElastix's object oriented interface (the way we used elastix to register images) and procedural interface (the way we used transformix to warp labels) with SimpleITK (the way we computed statistics). Previously, using elastix and transformix on large datasets would incur a significant overhead, from scripting command line invocations and arguments to copying images and transform parameter files across folders. With SimpleElastix this complexity is easier to manage and more memory and disk I/O efficient. For more examples see [the documentation](https://simpleelastix.readthedocs.org/) or the [Examples/SimpleElastix](Examples/SimpleElastix) directory. 

### Building with the SuperBuild
SimpleElastix integrates elastix and transformix with the SimpleITK SuperBuild. Simply clone this repository and invoke the SuperBuild.

```
git clone https://github.com/kaspermarstal/SimpleElastix
mkdir build
cd build
cmake ../SimpleElastix/SuperBuild
make -j4
```

The SuperBuild will download and install dependencies (elastix, ITK, SimpleITK and SWIG) and compile SimpleElastix. Target language dependencies need to be pre-installed, e.g. `sudo apt-get install cmake swig monodevelop r-base r-base-dev ruby python python-dev tcl tcl-dev tk tk-dev`. Note that this project takes around an hour to build on a quad-core machine.

The documentation explains how to [build SimpleElastix manually](http://simpleelastix.readthedocs.org/GettingStarted.html#building-manually-on-linux).

SimpleElastix has been tried and tested on Ubuntu 14.10 using GCC 4.9.2 and Clang 3.4.0, Mac OSX Yosemite using Apple Clang 600.0.56 and Windows 8.1 using Microsft Visual Studio 2012 C++ compiler.

### About
If you are interested in my work you are most welcome to visit [my website](https://kaspermarstal.github.io).
