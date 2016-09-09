Hello World
===========

This example illustrates how to use SimpleElastix. With a single function call we can specify the fixed image, the moving image and the type of registration you want to perform. SimpleElastix will then register our images using sensible default parameters that work well in most cases. In later examples we shall see how to tweak the default parameters, but for now we keep it simple.

Registration With Translation Transform
---------------------------------------

Say we want to register the following two brain MRIs.

.. _fig: 

    .. image::  _static/BrainProtonDensity.png
       :width: 45%
       :align: left
    .. image::  _static/BrainProtonDensityTranslated13x17y.png
       :width: 45%
       :align: left

    .. class:  center
    
    Figure 2. The original image :code:`fixedImage.nii` (left) and translated image :code:`movingImage.nii` (right).


We identify that the objects are related by a simple spatial shift and that a translation transform should be sufficient to align the objects. To correct the misalignment, we run the following lines of python code:

::

  import SimpleITK as sitk

  resultImage = sitk.Elastix(sitk.ReadImage("fixedImage.nii"), \ 
                             sitk.ReadImage("movingImage.nii"), \
                             "translation")


That's it! We have effectively registered two images using a rsingle line of code. Compare this to the `ITK Hello World example <https://github.com/InsightSoftwareConsortium/ITK/blob/master/Examples/RegistrationITKv4/DeformableRegistration1.cxx>`_. We refer to this short-hand notation as the procedural interface (some people also refer to it as the functional interface) because it consists of functions that accomplish a specific task. The procedural interface is less flexible than the object-oriented interface introduced below, but it is very simple to use. Let's break down what goes on under the hood of this single function call.

First of all, :code:`import SimpleITK as sitk` loads the SimpleITK module from which SimpleElastix is accessed. This assumes that SimpleElastix has been compiled and installed on your machine.

:code:`sitk.ReadImage()` is the generic image file reader of SimpleITK which loads an image from disk and pass a SimpleITK image object to SimpleElastix. You can also apply a SimpleITK filter to an image before passing them to SimpleElastix. For example, you could use the :code:`ResampleImageFilter()` to downsample images that would otherwise consume too much memory during registration.

The final parameter :code:`"translation"` specifies the desired type of registration. In the Parameter Maps section we will take a close look at parameter maps and examine what happens when you specify this parameter. It is obvious from the figure below that a translation transform is sufficient to align these images.

.. _fig2: 

    .. image::  _static/PreTranslated.jpeg
       :width: 45%
       :align: left
    .. image::  _static/PostTranslated.jpeg
       :width: 45%
       :align: left

    .. class:  center
    
    Figure 3. Mean image before registration (left) and mean image after registration (right). The fixed image is shown the red color channel and the moving image is shown in the blue color channel.

Object-Oriented Interface
-------------------------

The example above used procedural interface. While the procedural interface may be useful for rapid prototyping, it trades off flexibility for code simplicity. For example, the final deformation field cannot be retrived and applied to another image. This is a problem if we want to subsequently warp other images, e.g. a label image, using the same transformation. Further, image quality is reduced from resampling the resulting image twice. To this end, SimpleElastix comes with a more flexible object-oriented interface suitable for more advanced use cases and scripting purposes. In the next example, we perform the same registration as above, but this time using the object oriented interface:

::

    import SimpleITK as sitk

    fixedImage = sitk.ReadImage('fixedImage.nii')
    movingImage = sitk.ReadImage('movingImage.nii')
    parameterMap = sitk.GetDefaultParameterMap('translation')

    SimpleElastix = sitk.SimpleElastix()
    SimpleElastix.SetFixedImage(fixedImage)
    SimpleElastix.SetMovingImage(movingImage)
    SimpleElastix.SetParameterMap(parameterMap)
    SimpleElastix.Execute()

    resultImage = SimpleElastix.GetResultImage()
    transformParameterMap = SimpleElastix.GetTransformParameterMap()

This is more verbose but also a lot more powerful. We can now warp an entire population of images (e.g. binary label images for segmentation of different brain regions) using the same parameter map and a single instance of transformix:

::
    
    SimpleTransformix = sitk.SimpleTransformix()
    SimpleTransformix.SetTransformParameterMap(transformParameterMap)

    population = ['image1.hdr', 'image2.hdr', ... , 'imageN.hdr']

    for filename in population:
        SimpleTransformix.SetMovingImage(sitk.ReadImage(filename))
        SimpleTransformix.Execute()
        sitk.WriteImage(SimpleTransformix.GetResultImage(), "result_"+filename)

The object-oriented interface facilitates reuse of components and dramatically simplifies book-keeping and boilerplate code. We will use the object-oriented interface from this point forward.

In the next section, we will take a closer look at the parameter map interface that configures the registration components.







