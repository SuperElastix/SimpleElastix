Parameter Maps
==============

In the previous section we saw how to configure an entire multi-resolution registration process with a single parameter. Here, we will examine how SimpleElastix configures registration components internally. Knowing the internal mechanisms is not strictly necessary to register simple anatomical structures but will help you solve complex problems that most likely require modifications to default parameters to obtain good results. 


Elastix introduces the concept of a "parameter map" to configure the registration procedure. A parameter map is a collection of key-value pairs that completely defines the components of the registration and any settings they might require. Only input images and output options need to be specified seperately. Elastix will read a given parameter map and load the specified components at runtime. 


The original elastix and transformix command line programs read text files from disk in which parameters are specified according to the following format:

::

(ParameterName ParameterValue)

The parameter may be either single- or vector-valued. If the value is of type :code:`string` then the value will be quoted:

::

      (ParameterName "value1" ... "valueN")

If the value is of numerical type it will be unquoted:

::

      (ParameterName 123)

SimpleElastix can read these types of files as well but further introduces native data objects for parameter files in all target languages. This means that instead of editing text files you can programmatically configure registration components. For example, we could initialize a parameter object and start populating it with values that defines a desired registration method:

::

      import SimpleITK as sitk

      p = sitk.ParameterMap()
      p["Registration"] = ["MultiResolutionRegistration"]
      p["Transform"] = ["TranslationTransform"]
      ...

We can also load one of the default parameter maps and tweak its settings to get started more quickly, however, as shown in the following section.

The Default Parameter Maps
--------------------------
In the Hello World example we obtained a registered image by running 

::

  resultImage = sitk.Elastix(sitk.ReadImage("fixedImage.nii"),  \
                             sitk.ReadImage("movingImage.nii"), \
                             "translation")

Internally, SimpleElastix passes images along with a parameter map to elastix and invokes registration. The parameter map is returned by a call to :code:`sitk.GetDefaultParameterFile('translation')`. This function further provides parameter maps for rigid, affine, non-rigid and groupwise registration methods (in order of increasing complexity). The returned parameter object can be reconfigured and passed back to SimpleElastix allowing you to quickly optimize the registration method to your particular type of problem:

::

  parameterMap = sitk.GetDefaultParameterMap('translation')

  # Use a non-rigid transform instead of a translation transform
  parameterMap["Transform"] = ["BSplineTransform"]

  # Because of the increased complexity of the b-sbpline transform,
  # it is a good idea to run the registration a little longer to 
  # ensure convergence  
  parameterMap["MaximumNumberOfIterations"] = ["512"]

  resultImage = sitk.Elastix(sitk.ReadImage("fixedImage.nii"),  \
                             sitk.ReadImage("movingImage.nii"), \
                             parameterMap)

We will study other parameter maps more closely in later examples. For now, we simply print the translation parameter map to console and examine its contents: 

::

    >>> sitk.PrettyPrint(sitk.GetDefaultParameterMap("translation"))
    ParameterMap 0: 
      (AutomaticParameterEstimation "true")
      (CheckNumberOfSamples "true")
      (DefaultPixelValue 0)
      (FinalBSplineInterpolationOrder 2)
      (FixedImagePyramid "FixedSmoothingImagePyramid")
      (FixedImagePyramidSchedule 8 8 8 4 4 4 2 2 2 1 1 1)
      (ImageSampler "RandomCoordinate")
      (Interpolator "LinearInterpolator")
      (MaximumNumberOfIterations 32)
      (MaximumNumberOfSamplingAttempts 8)
      (Metric "AdvancedMattesMutualInformation")
      (MovingImagePyramid "MovingSmoothingImagePyramid")
      (MovingImagePyramidSchedule 8 8 8 4 4 4 2 2 2 1 1 1)
      (NewSamplesEveryIteration "true")
      (NumberOfResolutions 4)
      (NumberOfSamplesForExactGradient 4096)
      (NumberOfSpatialSamples 4096)
      (Optimizer "AdaptiveStochasticGradientDescent")
      (Registration "MultiResolutionRegistration")
      (ResampleInterpolator "FinalBSplineInterpolator")
      (Resampler "DefaultResampler")
      (Transform "TranslationTransform")
      (WriteResultImage "true")

The first thing to note is that the parameter map is enumerated. SimpleElastix can take a vector of parameter maps and apply the corresponding registrations sequentially. The resulting transform is is called a composite transform since the final transformation is a composition of sequentially applied deformation fields. For example, a non-rigid registration is often initialized with an affine transformation (translation, scale, rotation, shearing) to bring the objects into rough alignment. This will make your registration more robust to local minima. You can also ask SimpleElastix to add the individual deformation fields and apply them in one go, but make sure you know what you are doing before opting for this apprach. 

:code:`Registration` is the top-level parameter which in this case has been set to :code:`MultiResolutionRegistration`. A multi-resolution pyramid strategy improves the capture range and robustness of the registration and you will almost always want to use multiple resolutions unless your problem is particularly simple. The basic idea is to first estimate :code:`T(x)` on a low resolution version of the images and then propagate the estimated deformation to higher resolutions. This makes the registration initially focus on larger structures (the skull and brain hemispheres etc), before focusing on high-frequency information (brain subregions etc) which contain more local minima that may stall convergence in without propor initialization. :code:`FixedImagePyramid`, :code:`FixedImagePyramidSchedule`, :code:`MovingImagePyramid`, :code:`MovingImagePyramidSchedule`, and :code:`NumberOfResolutions` controls the pyramid strategy.

The :code:`Transform` parameter is set to :code:`TranslationTransform` which it is optimized with an :code:`AdaptiveStochasticGradientDescent` optimizer (Klein et al. 2009). SimpleElastix will always use this optimizer together with the :code:`AdvancedMattesMutualInformation` metric by default since this combination work well for a broad range of problems whether mono-modal or multi-modal. 

Image intensities are sampled using algorithms specified by :code:`ImageSampler`, :code:`Interpolator`, :code:`ResampleInterpolator`. The :code:`RandomCoordinate` sampler selects random positions in the fixed and moving images (as opposed to random indexes which are always centered on a single pixel) and off-grid posititions are interpolated using a :code:`LinearInterpolator` during optimization which is very fast.

A :code:`BSplineInterpolator` of order 2 is used to resample the result image from the moving image once the final transformation has been found. This is a one-time step so the additional computational complexity is worth the trade-off for higher image quality.

Another important parameter is :code:`AutomaticParameterEstimation` which controls whether the :code:`AdaptiveStochasticGradientDescent` optimizer should estimate its own convergence parameters or allow you to set them. Automatically obtained parameters work well almost always and facilitates a complete hands-off approach which is highly recommended. Optimizers can be tricky to tune by hand. 

:code:`DefaultPixelValue` sets value of pixels outside the moving image grid. The rest of the key-value pairs are component specific parameters. There are multiple choices available for each type of component. For example, you can construct an image pyramid with recursive sampling or via Gaussian Smoothing. Each choice has its own pros and cons. Consult the registration components secton for a description of all types of available components. 