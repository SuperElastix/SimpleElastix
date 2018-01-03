Affine Registration
===================

The affine transform allows for shearing and scaling in addition to the rotation and translation. This is usually a good choice of transform for initialization of non-rigid transforms like the B-Spline transform. The affine transform is selected using :code:`sitk.GetDefaultParameterMap("affine")`.

Consider the images in Figure 10.

.. _fig10: 

    .. image::  _static/BrainProtonDensity.png
       :width: 45%
       :align: left
    .. image::  _static/BrainProtonDensityTranslatedR1013x17yS12.png
       :width: 45%
       :align: left

    .. class:  center
    
    Figure 10. The original image :code:`fixedImage.nii` (left) and translated and rotated image :code:`movingImage.nii` (right).

The image on the right has been sheared, scaled 1.2x, rotated 10 degrees and translated 13 pixels in the x-direction and 17 pixels in the y-direction. Using the :code:`AdvancedAffineTransform` we may correct for this misalignment.

::

    import SimpleITK as sitk

    elastixImageFilter = sitk.ElastixImageFilter()
    elastixImageFilter.SetFixedImage(sitk.ReadImage("fixedImage.nii")
    elastixImageFilter.SetMovingImage(sitk.ReadImage("movingImage.nii")
    elastixImageFilter.SetParameterMap(sitk.GetDefaultParameterMap("affine"))
    elastixImageFilter.Execute()
    sitk.WriteImage(elastixImageFilter.GetResultImage())

It is clear from the result mean image on right in Fig. 11 that registration was successful.

.. _fig11: 

    .. image::  _static/PreAffine.jpeg
       :width: 45%
       :align: left
    .. image::  _static/PostAffine.jpeg
       :width: 45%
       :align: left

    .. class:  center
    
    Figure 11. Mean image before registration (left) and mean image after registration (right).

Notice that the only difference from the previous example is the requested parameter map. In fact, only the `Transform` parameter seperates the two parameter maps. The following parameter map is equivalent to the one used above:

::

    import SimpleITK as sitk

    parameterMap = sitk.GetDefaultParameterMap("rigid")
    parameterMap["Transform"] = ["AffineTransform"]

You can inspect the default parameter maps in the `elastix repository <https://github.com/SuperElastix/elastix/blob/522843d90ff586be051c480514cd14a88db45dbf/src/Core/Main/elxParameterObject.cxx#L260-L362>`_ to convince yourself.

This demonstrates how easy it is to try out different registration components with SimpleElastix. In the next example we will introduce non-rigid registration and initialize the moving image with an affine transform.
