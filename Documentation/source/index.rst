SimpleElastix
=============

SimpleElastix is a medical image registration library that makes state-of-the-art image registration really easy to do. For example, you can perform state-of-the-art multi-resolution non-rigid groupwise registration with a single line of code:

.. _fig1: 

    .. image::  _static/PreGroupwise.jpg
       :width: 45%
       :align: left
    .. image::  _static/PostGroupwise.jpg
       :width: 45%
       :align: left

    Figure 1. Original mean image of five different subjects (left) and registered mean image (right). Each subject is displayed in a separate color. Grey areas indicate good alignment and colored areas indicate misalignment.

The :ref:`Getting Started <GettingStarted>` section explains how to clone the `Github repository <https://github.com/kaspermarstal/SimpleElastix>`_ and compile SimpleElastix on :ref:`Linux <Linux>`, :ref:`Mac OS X <MacOSX>` and :ref:`Windows <Windows>`. If you have not used elastix or transformix before, we highly recommend you familiarize yourself with the Introduction, Hello World example and Parameter Maps sections before working through the examples.

.. toctree:: 
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

