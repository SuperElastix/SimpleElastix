Point-based Registation
=======================

Point-based registration allows us to help the registration via pre-defined sets of corresponding points. The :code:`CorrespondingPointsEuclideanDistanceMetric` minimises the distance of between a points on the fixed image and corresponding points on the moving image. The metric can be used to help in a difficult registration task by taking into account positions are known to correspond. Think of it as a way of embedding expert knowledge in the registration procedure. We can manually select points or automatically them via centroids of segmentations for example. Anything is possible.

To use :code:`CorrespondingPointsEuclideanDistanceMetric` we append it to the list of metrics in the parameter map. 

::

    import SimpleITK as sitk

    parameterMap = sitk.GetDefaultParameterMap("bspline")
    parameterMap["Metric"].append("CorrespondingPointsEuclideanDistanceMetric")

.. note::

	The :code:`CorrespondingPointsEuclideanDistanceMetric` metric must be specified as the last metric due to technical constraints in elastix.

The metric can also be added to all metrics in the ElastixImageFilter object with a single call.

::

    import SimpleITK as sitk

    elastixImageFilter = sitk.ElastixImageFilter()
    elastixImageFilter.AddParameter( "Metric", "CorrespondingPointsEuclideanDistanceMetric" )

Or to a single parameter map (here we assume that SimpleElastix contains at least two parameter maps)

::

    elastixImageFilter.AddParameter( 1, "Metric", "CorrespondingPointsEuclideanDistanceMetric" )


The point set are specified as text files. They can either be in `VTK pointdata legacy format <http://dunne.uni-hd.de/VisuSimple/documents/vtkfileformat.html#pointdata>`_ or elastix' own format that usually has the :code:`pts` extension.

::

	<index, point>
	<number of points>
	point1 x point1 y [point1 z]
	point2 x point2 y [point2 z]

:code:`index` is used when points are specified in pixel coordinates. :code:`point` is used when the points are specified in world coordinates. For example, this is a valid point file:

::

	point
	3
	102.8 -33.4 57.0
	178.1 -10.9 14.5
	180.4 -18.1 78.9

Transforming Point Sets
-----------------------

We can apply a transformation computed with SimpleElastix to a point set with SimpleTransformix.

:: 

    import SimpleITK as sitk

    fixedImage = sitk.ReadImage("fixedImage.nii")
    movingImage = sitk.ReadImage("movingImage.nii")

    # Compute the transformation
    elastixImageFilter = sitk.ElastixImageFilter()
    elastixImageFilter.SetFixedImage(fixedImage)
    elastixImageFilter.SetMovingImage(movingImage)
    elastixImageFilter.Execute()

    # Warp point set. The transformed points will be written to a file named 
    # outputpoints.txt in the output directory determined by SetOutputDirectory()
    # (defaults to working directory). The moving image is needed for transformix
    # to correctly infer the dimensionality of the point set.
    transformixImageFilter = sitk.TransformixImageFilter()
    transformixImageFilter.SetTransformParameterMap(elastixImageFilter.GetTransformParameterMap())
    transformixImageFilter.SetFixedPointSetFileName("fixedPointSet.pts")
    transformixImageFilter.Execute()

.. warning::
	
	The input points are specified in the fixed image domain (!) and warped from the fixed image to moving image since the transformation direction is from fixed to moving image. If we want to warp points from the moving image to fixed image, we need the inverse transform. This can be computed manually (see section 6.1.6 in the `elastix manual <http://elastix.isi.uu.nl/download/elastix_manual_v4.8.pdf>`_) or via :code:`elastixImageFilter.ExecuteInverse()`.


    
