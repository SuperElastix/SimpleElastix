Introduction
============

Image Registration
------------------

Medical image registration is the process of transforming images into a common coordinate system so corresponding pixels represent homologous biological points. This is a prerequisite for a wide range of medical image analysis tasks and a key algorithmic component for statistical analysis and machine learning in medical image processing. 

.. figure:: _static/ImageRegistrationConcept.png
    :align: right
    :figwidth: 50%
    :width: 90% 

    Figure 1: Image registration is the act of deforming moving image points :math:`p` to biologically corresponding points :math:`q` in the fixed image domain.

Mathematically, a moving image :math:`I_M(x)` is deformed to match a fixed image :math:`I_F(x)` by finding a coordinate transformation :math:`T(x)` that makes :math:`I_M(x)` spatially aligned with :math:`I_F(x)`. The registration procedure is generally formulated as an optimization problem in which the cost function :math:`C` is minimized with respect to :math:`T`. The optimizer aligns the moving image with the fixed adjusting the parameters of the transform in a way that minimizes the difference between them. The cost function (commonly refered to as a metric in the literature) defines how this difference is measured.


Many metrics are available each with its own pros and cons and SimpleElastix makes it dead simple to swap out the different components of the registration procedure. For example, to register two CT scans you would pass the :code:`parameter["Metric"] = ["NormalizedCorrelationMetric"]` option to SimpleElastix. If instead you wanted to register a CT image with a MR image you would change this option to or :code:`parameter["Metric"] = ["NormalizedMutualInformation"]` to use a similarity measure that is invariant to intensity scales. Different transforms, optimizers, interpolators, resamplers and image pyramids can be swapped out in a similar fashion. 


In truth, image registration is not about using the most recent and fancy algorithm, but to apply the right algorithm to the right problem. This will take you some time to master, but with the right tools you focus on the underlying principles and not the implementation. Below is listed some of the key features that hopefully make your time with SimpleElastix as productive as possible.

Key Features
------------
SimpleElastix is

* Open Source and freely available from `Github.com <https://github.com/kaspermarstal/SimpleElastix>`_.
* Multi-platform: Compiles and runs on Windows, Mac OS X and Linux using GCC, Clang and Visual Studio compilers.
* Multi-lingual: Available in C++, Python, Java, R, Ruby, Octave, Lua, Tcl and C#.
* Fast: Stochastic sampling [Klain et al. 2007], multi-threading and code optimizations [Shamonin et al 2014] makes registration run very fast. Some components also use CUDA and OpenCL. 
* Robust: The core image processing algorithims are based on ITK which thoroughly tested and developed according to the highest standards. An estimated 400 man years has gone into developing ITK.
* Easy to use: New users can get started quickly and the native interface makes processing of large data sets significantly easier than scripting command line invocations.
* Shipped with the complete set of SimpleITK image processing algorithms.