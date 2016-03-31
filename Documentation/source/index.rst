SimpleElastix Documentation
===========================

SimpleElastix is a medical image registration library that makes state-of-the-art image registration really easy to do in languages like Python, Java and R. For example, using the following line of code (Python),

::

    import SimpleITK as sitk
    resultImage = sitk.Elastix(sitk.ReadImage("fixedImage.nii"), sitk.ReadImage("movingImage.nii"))

we can register two human brain images:

.. _fig1: 

    .. image::  _static/PreNonrigid.jpg
       :width: 45%
       :align: left
    .. image::  _static/PostNonrigid.jpg
       :width: 45%
       :align: left

    Figure 1. Original mean image of two different subjects (left) and registered mean image (right) using the line of code above. Purple areas indicate good alignment and blue and red areas indicate misalignment.

The :ref:`Getting Started <GettingStarted>` section explains how to clone the `Github repository <https://github.com/kaspermarstal/SimpleElastix>`_ and compile SimpleElastix on :ref:`Linux <Linux>`, :ref:`Mac OS X <MacOSX>` and :ref:`Windows <Windows>`. The subsequent sections present how to use elastix, and gradually introduce more advanced features and use cases. If you have not used elastix or transformix before, we highly recommend that you familiarize yourself with the Introduction, Hello World example and Parameter Maps sections before working through the examples.

.. toctree::
    :maxdepth: 2

    GettingStarted
    Introduction
    HelloWorld
    ParameterMaps
    RigidRegistration
    AffineRegistration
    NonRigidRegistration
    GroupwiseRegistration
    Acknowledgements

The reader is refered to the `elastix manual <http://elastix.isi.uu.nl/download/elastix_manual_v4.7.pdf>`_ for a technical discussion of individual algorithms.

