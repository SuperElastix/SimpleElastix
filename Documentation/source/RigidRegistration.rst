Rigid Registration
==================

The rigid transform allows for rotation and translation. For example, if you are interested in registering bones from the same patient and two different time points, you can assume that there is no scaling or non-rigid deformation. The rigid transform is selected using :code:`(Transform "EulerTransform")`. Consider the images in Figure 8. 

.. _fig9: 

    .. image::  _static/BrainProtonDensity.png
       :width: 45%
       :align: left
    .. image::  _static/BrainProtonDensityTranslatedR1013x17y.png
       :width: 45%
       :align: left

    .. class:  center
    
    Figure 8. The original image :code:`fixedImage.nii` (left) and translated and rotated image :code:`movingImage.nii` (right).

The image on right has been rotated 10 degrees and translated 13 pixels in the x-direction and 17 pixels in the y-direction. Using the :code:`EulerTransform` we may correct for this misalignment.

::

    import SimpleITK as sitk

    elastix = sitk.SimpleElastix()
    elastix.SetFixedImage("fixedImage.nii")
    elastix.SetMovingImage("movingImage.nii")
    elastix.SetParameterMap(sitk.GetDefaultParameterMap("rigid"))
    elastix.Execute()
    sitk.WriteImage(elastix.GetResultImage())

It is clear from the result mean image on right in Fig. 9 that registration was successful.

.. _fig9: 

    .. image::  _static/PreRotated.jpeg
       :width: 45%
       :align: left
    .. image::  _static/PostRotated.jpeg
       :width: 45%
       :align: left

    .. class:  center
    
    Figure 9. Mean image before registration (left) and mean image after registration (right).

In the next example we will introduce scaling and shearing into the registration.