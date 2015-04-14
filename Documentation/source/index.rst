SimpleElastix Documentation
===========================

SimpleElastix is a medical image processing package that makes state-of-the-art medical image registration really easy to do. This is accomplished by exposing native interfaces to the robust C++ registration algorithms of the elastix library in Python, Java, R, Ruby, Octave, Lua, Tcl and C#, and by a modular architecture that allows you to quickly compare different registration methods. With this approach you can focus on applying the right algorithm to the right problem using your language of choice. If you know the basic syntax of any of the supported languages (like how to write a for loop), you are ready to perform state-of-the-art medical image registration:

.. _fig1: 

    .. image::  _static/PreGroupwise.jpg
       :width: 45%
       :align: left
    .. image::  _static/PostGroupwise.jpg
       :width: 45%
       :align: left

    Figure 1. Original mean image (left) and registered mean image (right).

The documentation consists of introductory material to image registration and examples of typical use cases in which SimpleElastix provides efficient workflows. The reader is refered to the `elastix manual <http://elastix.isi.uu.nl/download/elastix_manual_v4.7.pdf>`_ for a technical discussion of individual algorithms. If you have not used elastix or transformix before, we highly recommend you familiarize yourself with the Introduction, Hello World example, Parameter Maps and Registration Components sections before working through the examples.

.. note::

    Got questions? Suggestions for improvements? Tweet us `@SimpleElastix <https://twitter.com/SimpleElastix>`_!


Contents:
  
.. toctree:: 
    Introduction
    GettingStarted
    HelloWorld
    ParameterMaps
    RegistrationComponents
    ObjectOrientedInterface
    RigidRegistration
    AffineRegistration
    NonRigidRegistration
    GroupwiseRegistration
    Acknowledgements

..    MultiMetricRegularisation
..    AtlasBasedSegmentation
..    LabelBasedRegistration
..    PointBasedRegistration


.. note:: 
    Example code is written in Python. The commands map closely to other languages except for syntax differences. For examples in languages other than python, see `SimpleElastix/Examples <https://github.com/kaspermarstal/SimpleElastix/tree/SimpleElastix/Examples>`_.
