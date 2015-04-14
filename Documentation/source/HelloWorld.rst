Hello World
===========

This example illustrates the simplest way to use SimpleElastix. With *one* line of code you can specify two images and the type of registration you want to perform, and SimpleElastix will register your images using sensible default parameters that works in most cases. In a later example we shall see how to tweak the default parameters if you are not happy with the initial results.

Registration With Translation Transform
---------------------------------------

Say you want to register the following two images. We identify that the objects are related by a simple spatial shift and that a translation transform should be sufficient to align the objects.

.. _fig: 

    .. image::  _static/BrainProtonDensity.png
       :width: 45%
       :align: left
    .. image::  _static/BrainProtonDensityTranslated13x17y.png
       :width: 45%
       :align: left

    .. class:  center
    
    Figure 2. The original image :code:`fixedImage.nii` (left) and translated image :code:`movingImage.nii` (right).


To correct the misalignment, we run the following lines of python code:

::

  import SimpleITK as sitk

  resultImage = sitk.Elastix(sitk.ReadImage('fixedImage.nii'),  \
                             sitk.ReadImage('movingImage.nii'), \
                             'translation')


Congratulations! You have effectively registered two images using a robust multi-resolution approach with single line of code. Compare this to the `ITK Hello World example <https://github.com/InsightSoftwareConsortium/ITK/blob/master/Examples/RegistrationITKv4/DeformableRegistration1.cxx>`_. We call this short-hand notation the procedural interface. Now, let us break down what actually goes on. 

:code:`import SimpleITK as sitk` loads the SimpleITK module from which SimpleElastix is accessed in your python session. This assumes that SimpleElastix has been compiled and installed on your machine. :code:`sitk.ReadImage()` is the generic image file reader of SimpleITK which loads an image from disk and pass a SimpleITK image object to SimpleElastix. The final parameter :code:`'translation'` specifies the desired type of registration. It is obvious from the figure below that registration was successful.

.. _fig2: 

    .. image::  _static/PreTranslated.jpeg
       :width: 45%
       :align: left
    .. image::  _static/PostTranslated.jpeg
       :width: 45%
       :align: left

    .. class:  center
    
    Figure 3. Mean image before registration (left) and mean image after registration (right).


In the next section we will take a look at parameter maps and examine what actually happens when you specify the :code:`'translation'` parameter.


