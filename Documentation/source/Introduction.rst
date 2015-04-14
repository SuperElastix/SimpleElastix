Introduction
============

Medical image registration is the process of transforming images into a common coordinate system so corresponding pixels represent homologous biological points. This is a prerequisite for a wide range of medical image analysis tasks and a key algorithmic component for statistical analysis and machine learning in medical image processing. For example, registration can be used to obtain point correspondences for construction of statistical shape models, or brain regions can be segmented using atlas-based segmentation where regions of interest are warped from one image to another.


SimpleElastix is a multi-lingual wrapper around the elastix library C++ API that exposes elastix algorithms in a wide variatety of programming languages. Elastix is a framework of pluggable registration components that can easily be interchanged. This flexibility means that a combinatorial variety of registration methods can be created allowing you to pick and choose the right tool for the right job. For example, to register two MRI scans you could use a Sum of Squared Differences (SSD) metric which is optimal under Gaussian distributed noise found in MR images. If instead you wanted to register a CT image with a MR image, you would use a mutual information-based metric which is invariant to differences in the underlying intensity scales. Choosing a metric is as simple as initializing a variable.

::

    parameters["Metric"] = ["NormalizedMutualInformation"]

Transforms, optimizers, interpolators, resamplers, penalty terms and image pyramids can be swapped out in a similar fashion. 

Image Registration
------------------

The registration concept is schematically depicted in Figure 1. A standard image registration procedure involves two input images: One is defined as the fixed image :math:`I_F(x)` and the other as moving image :math:`I_M(x)` which will be deformed to match the fixed. The :math:`x` denotes the :math:`d`-dimensional position in the image. If you are registering images taken with your iPhone, :math:`d = 2` and :math:`x` will have two components, one for each dimension of the 2D plane. If you are registering body parts taken with a CT scanner, :math:`d = 3` and :math:`x` will have three components, one for each of the spatial dimensions. You may also encounter time series which is four-dimensional (3D+t).

The transform component :math:`T(x)` represents the spatial mapping of points from the fixed image :math:`p` to points in the moving image :math:`q`. This establishes a correspondence for every pixel in the fixed image to a position in the moving image. It may seem counter-intuitive that the transform is defined in this direction, since it is the moving image we want to transform. Would it not be more logical to map each pixel in the moving image to its new position in fixed image? Perhaps, but then two pixels from the moving image might be mapped to the same pixel on the fixed grid, or some pixels in the fixed image might not be mapped to at all. The chosen convention allows us to iterate over the fixed image and pick a pixel from the moving image for every pixel in the fixed image. 

ITKv4 introduces an even more flexible registration framework in which the computations can happen in a "virtual" physical domain different from both the fixed image and moving image domains. We will ignore this distinction for the remainder of this discussion however, and present registration examples in the special case of the virtual domain being the same as the fixed image domain. This is also what happens in most real life applications.

.. figure:: _static/ImageRegistrationConcept.png
    :align: right
    :figwidth: 50%
    :width: 90% 

    Figure 2: Image registration is the act of deforming moving image points :math:`p` to biologically corresponding points :math:`q` in the fixed image domain.

A similarity metric provides a measure of how well the fixed image is matched by the transformed moving image. This measure forms a quantitative criterion to be optimized by the optimizer over the search space defined by the parameters of the transform. In general, the registration procedure is formulated as an optimization problem in which a cost function :math:`C` is minimized with respect to :math:`T`. This simply means that the optimizer adjusts the parameters of the transform in a way that minimizes the difference between the two images. Mathematically, :math:`I_M(x)` is deformed to match :math:`I_F(x)` by finding a coordinate transformation :math:`T(x)` that makes :math:`I_M(T(x))` spatially aligned with :math:`I_F(x)`.  

The metric is a key component in the registration process. It uses intensity values from the fixed and transformed moving image to evaluate the fitness value and derivatives, which are passed to the optimizer that asks transform to update its parameters. This process is repeated until a convergence criteria is met.

Sometimes a regularisation term is added to the cost function to penalize unwanted transformations. For example, if you expect your transform to be reasonably smooth, you can penalize sharp deformations. Further, a multi-resolution approach is typically adopted where you start from coarse images and gradually sharpen images. This makes registration much less prone to local minima. 

In theory, the combinatorial number of choices of registration components can be daunting. In practice, you will develop an intuition about which algorithms are better suited to what types of problems. Choosing the right method for a particualr problem will always be a trial-and-error process even for experts, but with the right tools you focus more on underlying problem and less on implementation.

Elastix And Transformix
-----------------------
The `original elastix registration library <http://elastix.isi.uu.nl/>`_ consists of two command line programs. Elastix is the main program that performs registration as outlined above, taking input images and generating output images and transform parameter files. Transform parameter files contains all the information found by elastix to reproduce the final transformation from the moving to the fixed image. 

Transformix takes a transform parameter file and can apply the transformation to other images, indexes, point sets or write the deformation field and transform Jacobian to disk. You can use transformix to apply the transformation to an original (larger) image to gain resolution orapply the transformation to a label image to do atlas-based segmentations.

Previously, performing these kinds of operations on large datasets would incur a significant workflow overhead from scripting command line invocations and arguments to copying images and transform parameter files across folders. With SimpleElastix and SimpleTransformix this complexity is easier to manage and much more memory and disk I/O efficient.

Below is listed some of the key features that hopefully make your time with SimpleElastix as productive as possible. SimpleElastix is

* Flexible: SimpleElastix is configured using a simple parameter interface and loads the specified components at runtime.
* Fast: Stochastic sampling (Klein et al. 2007), multi-threading and code optimizations (Shamonin et al 2014) makes registration run very fast. Some components are based on CUDA and OpenCL and can take advantage of heterogeneous execution platforms. 
* Robust: The core image processing algorithms are based on ITK which is thoroughly tested and developed according to some highest standards you will find in open source software. An estimated 400 man years has gone into developing ITK.
* Easy to use: New users can get started quickly and the native interface makes processing large data sets significantly easier than scripting command line invocations.
* Multi-lingual: Available in C++, Python, Java, R, Ruby, Octave, Lua, Tcl and C#.
* Shipped with the complete set of SimpleITK image processing algorithms.
* Open Source and freely available from `Github.com <https://github.com/kaspermarstal/SimpleElastix>`_.
* Multi-platform: Compiles and runs on Windows, Mac OS X and Linux using Visual Studio, Clang and GCC compilers.

Enough talk! Time for some examples. In the next section we introduce the SimpleElastix Hello World example.
