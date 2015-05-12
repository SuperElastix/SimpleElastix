Affine Registration
===================

The affine transform allows for shearing and scaling in addition to rotation and translation. For example, if you are interested in registering bones from different patients, or want to initialize a non-rigid registration, the affine transform is usually a good choice. The affine transform is selected using :code:`(Transform "AdvancedAffineTransform")`. Consider the images in Figure 10. 

.. _fig10: 

    .. image::  _static/BrainProtonDensity.png
       :width: 45%
       :align: left
    .. image::  _static/BrainProtonDensityTranslatedR1013x17yS12.png
       :width: 45%
       :align: left

    .. class:  center
    
    Figure 10. The original image :code:`fixedImage.nii` (left) and translated and rotated image :code:`movingImage.nii` (right).

The image on right has been sheared, scaled 1.2x, rotated 10 degrees and translated 13 pixels in the x-direction and 17 pixels in the y-direction. Using the :code:`AdvancedAffineTransform` we may correct for this misaligned.

::

    import SimpleITK as sitk

    elastix = sitk.SimpleElastix()
    elastix.SetFixedImage(sitk.ReadImage("fixedImage.nii")
    elastix.SetMovingImage(sitk.ReadImage(""movingImage.nii")
    elastix.SetParameterMap(sitk.GetDefaultParameterMap("affine"))
    elastix.Execute()
    sitk.WriteImage(elastix.GetResultImage())

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

In the next example we will introduce non-rigid registration and initialize the moving image with an affine transform.