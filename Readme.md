SimpleElastix
=============

SimpleElastix integrates [SimpleITK](https://github.com/SimpleITK/SimpleITK) with the [elastix medical image registration library](http://elastix.isi.uu.nl/ "Elastix website") intended to make elastix's robust registration algorithms accessible to a wider audience. In addition to the standard SimpleITK image processing algorithms, this package provides

- elastix and transformix bindings for Python, Java, R, Octave, Lua, Tcl and C#
- Preconfigured parameter files for affine, non-rigid, groupwise and labelmap registration that should serve as good starting points for new users

The goal of SimpleElastix is to bring the robust langauge wrapping of SimpleITK to elastix. SimpleElastix has been designed specifically for rapid prototyping and use in scripting languages. Using elastix and transformix on large datasets typically incurs a significant amount of overhead from scripting command line arguments to copying images and transform parameter files across folders. With SimpleElastix this complexity is easier to manage and much more memory and disk I/O efficient.

Examples
--------

### Procedural Interface
This interface aligns with the SimpleITK procedural paradigm and reduces registration to a one-liner. The procedural interface directly invokes registration and hiding the elastix API's object oriented methods.

```python
import SimpleITK as sitk

# Register images using a preset parameter file.
resultImage = sitk.elastix('fixedImage.hdr', 'movingImage.hdr', 'defaultNonrigidParameters')
```

However, consecutive registrations sacrifice some image quality for code simplicity (the moving image is warped and resampled following each registeration). 

```python
# Affine initialization followed by non-rigid registration. This time we pass 
# elastix images from memory and load a parameter file from disk.
f = sitk.ReadImage('fixedImage');
m = sitk.ReadImage('movingImage');
initializedImage = elastix.SimpleElastix(fixedImage, movingImage, 'affineParameterFile.txt')
resultImage = elastix.SimpleElastix(fixedImage, movingImage.hdr, 'nonrigidParameterFile.txt')
```

### Object Oriented interface 

SimpleElastix also comes with a powerful object oriented suited for scripting purposes
elastix = sitk.SimpleElastix()

```python
# Images can loaded from memory or disk
elastix.SetFixedImage('fixedImage.hdr')
elastix.SetMovingImage(inMemoryImage)

# Get a preconfigured parameter map and customize e.g. number of iterations to suit your needs
p = selx.GetDefaultAffineParameters()
p.SetParameter("MaximumNumberOfIterations", 512)

# SetParameterMap() overrides existing parameter maps or add a new one if none exist
selx.SetParameterMap(p)

# You can also load your own parameter files. In this case, AddParameterFile() will
# append nonrigid.txt to an internal list of parameter files
selx.AddParameterFile('nonrigid.txt')

# This will run an affine registration followed by non-rigid registration since the parameter
# files were added in this order. The transforms are composed and the moving image is only
# resampled when both registrations have run
elastix.Run()
sitk.Show(selx.GetResultImage())
```

### What you get from SimpleITK integration
Together, elastix and SimpleITK becomes an efficient, scriptable registration toolkit. For exmaple, say you want to compute mean intensities and standard deviation of segmented structures.

```python
# Transform label map and compute some statistics
transformix = sitk.SimpleTransformix()
in = transformix.ReadImage('labels.hdr')
transformix.SetImage(in)
transformix.SetParameterMap(elastix.GetTransformParameters())
transformix.Run()
sitk.ComputeLabelStatisticsImageFilter(elastix.GetResultImage(), transformix.GetResultImage())
```

### Parameter file interface 
You can also construct your parameter file from SimpleElastix's parameter file interface.

```python
import SimpleITK as sitk

p = sitk.SimpleElastix().ParameterMap()

# SetParameter() overrides existing parameters or creates them if none exist
p.SetParameter("Registration", "MultiResolutionRegistration")     

# AddParameter() does not override existing parameters but throws warnings if a parameter exists
p.AddParameter("Metric", ["AdvancedMattesMutualInformationMetric", "TransformBendingEnergyPenalty"])

# Multi-valued parameters can also be set using AppendParameter()
p.SetParameter("Metric", "NormalizedCorrelationCoefficient") # this overrides the previous declaration
p.AppendParameter("Metric", "TransformBendingEnergyPenalty")

# SimpleElastix maps naturally the target language types
p.AddParameter("FixedImagePyramidSchedule", [8, 4, 2, 1])
```

Wrapping is accomplished through SWIG thanks to the elastix library interface. In principle, any language wrapped by SWIG should be applicable to this project. SimpleElastix is licensed under the Apache 2.0 License in the same way as ITK, SimpleITK and elastix.

Building
--------

SimpleElastix integrates elastix and transformix with the SimpleITK superbuild. Simply clone this repository invoke the superbuild.

```
git clone https://github.com/kaspermarstal/SimpleITK
mkdir build
cd build
ccmake ../SimpleElastix/SuperBuild
make -j4
```

This will download and install ITK, SimpleITK, SWIG and elastix to your computer, compile and install the binaries.

Notes
-----
- At the moment, the elastix library API does not support using multiple fixed and moving images so SimpleElastix doesn't either. 