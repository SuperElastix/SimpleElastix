SimpleElastix Documentation 
===========================

SimpleElastix is a medical image registration library that makes state-of-the-art image registration really easy to do. This is accomplished by native Python, Java, R, Ruby, Octave, Lua, Tcl and C# interfaces to the robust C++ algorithms of the elastix library and a modular architecture that allows you to quickly compare different registration methods.

The :ref:`Getting Started <GettingStarted>` section explains how to clone the `Github repository <https://github.com/kaspermarstal/SimpleElastix>`_ and compile SimpleElastix on :ref:`Linux <Linux>`, :ref:`Mac OS X <MacOSX>` and :ref:`Windows <Windows>`. If you know the basic syntax of any of the supported languages (like how to write a for loop), you are then ready to perform state-of-the-art medical image registration:

.. _fig1: 

    .. image::  _static/PreGroupwise.jpg
       :width: 45%
       :align: left
    .. image::  _static/PostGroupwise.jpg
       :width: 45%
       :align: left

    Figure 1. Original mean image of five different subjects (left) and registered mean image (right). Each subject is displayed in a separate color. Grey areas indicate good alignment and colored areas indicate misalignment.

The documentation consists of introductory material to image registration and examples of typical use cases in which SimpleElastix provides efficient workflows:
  
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

..    MultiMetricRegistration
..    AtlasBasedSegmentation
..    LabelBasedRegistration
..    PointBasedRegistration

The reader is refered to the `elastix manual <http://elastix.isi.uu.nl/download/elastix_manual_v4.7.pdf>`_ for a technical discussion of individual algorithms. If you have not used elastix or transformix before, we highly recommend you familiarize yourself with the Introduction, Hello World example, Parameter Maps and Registration Components sections before working through the examples.

.. note:: 
    Example code is written in Python. The commands map closely to other languages except for syntax differences. For examples in languages other than python, see `SimpleElastix/Examples <https://github.com/kaspermarstal/SimpleElastix/tree/SimpleElastix/Examples>`_.
