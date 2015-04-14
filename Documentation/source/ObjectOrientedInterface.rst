Object-Oriented Interface
=========================

In the Hello World example we obtained a registered image using a procedural-style function call:

::

  resultImage = sitk.Elastix(sitk.ReadImage('fixedImage.nii'),  \
                             sitk.ReadImage('movingImage.nii'), \
                             'translation')

While the procedural interface may be useful in rapid prototyping, it trades off flexibility for code simplicity. In the example above, the final deformation field cannot be retrived and applied to another image. This is a problem if you want to subsequently warp other images, e.g. a label image, using the same transformation. Further, image quality is reduced from resampling the resulting image twice. To this end, SimpleElastix also comes with a powerful object-oriented interface suitable for more advanced use cases and scripting purposes. In the next example, we perform the same Hello World example, but this time using the object oriented interface:

::

    import SimpleITK as sitk

    fixedImage = sitk.ReadImage('fixedImage.nii')
    movingImage = sitk.ReadImage('movingImage.nii')
    parameterMap = sitk.GetDefaultParameterMap('translation')

    elastix = sitk.SimpleElastix()
    elastix.SetFixedImage(fixedImage)
    elastix.SetMovingImage(movingImage)
    elastix.SetParameterMap(parameterMap)

    elastix.Execute()

    resultImage = elastix.GetResultImage()
    transformParameterMap = elastix.GetTransformParameters()

This is more verbose but also a lot more powerful. For example, we can now warp an entire population of images using the same parameter map and a single instance of transformix:

::
    
    transformix = sitk.SimpleTransformix()
    transformix.SetParameterMap(transformParameterMap)

    population = ['image1.hdr', 'image2.hdr', ... , 'imageN.hdr']

    for filename in population:
        transformix.SetInputImage(sitk.ReadImage(filename))
        transformix.Execute()
        sitk.WriteImage(transformix.GetResultImage(), "result_"+filename)

This concludes the introductory material. In the next section, we start with a simple registration problem. In the following sections we gradually introduce more advanced registration problems and their solutions. We will use the object-oriented interface from this point forward.



