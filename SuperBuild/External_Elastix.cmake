CMAKE_MINIMUM_REQUIRED( VERSION 2.8.11 )

set( proj elastix )
set( ELASTIX_DEPENDENCIES "ITK")
set( ELASTIX_REPOSITORY git://github.com/kaspermarstal/elastix.git )

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${proj}-build/CMakeCacheInit.txt" "${ep_common_cache}" )

ExternalProject_Add( ${proj} 
  GIT_REPOSITORY ${ELASTIX_REPOSITORY}
  UPDATE_COMMAND ""
  SOURCE_DIR ${proj}
  BINARY_DIR ${proj}-build
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
  --no-warn-unused-cli
  -C "${CMAKE_CURRENT_BINARY_DIR}/${proj}-build/CMakeCacheInit.txt"
  -DELASTIX_BUILD_TESTING:BOOL=OFF
  -DELASTIX_BUILD_EXECUTABLE:BOOL=OFF
  -DELASTIX_BUILD_SHARED_LIBS:BOOL=OFF
  -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
  -DITK_DIR:PATH=${ITK_DIR}
  # Elastix components configuration
  -DUSE_AdaptiveStochasticGradientDescent:BOOL=ON                                           
  -DUSE_AdvancedAffineTransformElastix:BOOL=ON
  -DUSE_AdvancedBSplineTransform:BOOL=ON                                           
  -DUSE_AdvancedKappaStatisticMetric:BOOL=ON                                           
  -DUSE_AdvancedMattesMutualInformationMetric:BOOL=ON                                           
  -DUSE_AdvancedMeanSquaresMetric:BOOL=ON                                           
  -DUSE_AdvancedNormalizedCorrelationMetric:BOOL=ON                                           
  -DUSE_AffineDTITransformElastix:BOOL=ON                                           
  -DUSE_BSplineInterpolator:BOOL=ON                                           
  -DUSE_BSplineInterpolatorFloat:BOOL=ON                                           
  -DUSE_BSplineResampleInterpolator:BOOL=ON                                           
  -DUSE_BSplineResampleInterpolatoFloat:BOOL=ON                                           
  -DUSE_BSplineStackTransform:BOOL=ON                                           
  -DUSE_BSplineTransformWithDiffusion:BOOL=ON                                           
  -DUSE_CMAEvolutionStrategy:BOOL=ON                                           
  -DUSE_CUDAResampler:BOOL=OFF                                          
  -DUSE_ConjugateGradient:BOOL=ON                                           
  -DUSE_ConjugateGradientFRPR:BOOL=ON                                           
  -DUSE_CorrespondingPointsEuclideanDistanceMetric:BOOL=ON
  -DUSE_DeformationFieldTransform:BOOL=ON                                           
  -DUSE_DisplacementMagnitudePenalty:BOOL=ON                                           
  -DUSE_DistancePreservingRigidityPenalty:BOOL=ON                                           
  -DUSE_EulerTransformElastix:BOOL= ON                                           
  -DUSE_FiniteDifferenceGradientDescent:BOOL=ON                                           
  -DUSE_FixedGenericPyramid:BOOL=ON                                           
  -DUSE_FixedRecursivePyramid:BOOL=ON                                           
  -DUSE_FixedShrinkingPyramid:BOOL=ON                                           
  -DUSE_FixedSmoothingPyramid:BOOL=ON                                           
  -DUSE_FullSampler:BOOL=ON                                           
  -DUSE_FullSearch:BOOL=ON                                           
  -DUSE_GradientDifferenceMetric:BOOL=ON                                           
  -DUSE_GridSampler:BOOL=ON                                           
  -DUSE_KNNGraphAlphaMutualInformationMetric:BOOL=OFF                                         
  -DUSE_LinearInterpolator:BOOL=ON                                           
  -DUSE_LinearResampleInterpolator:BOOL=ON                                           
  -DUSE_MissingStructurePenalty:BOOL=ON
  -DUSE_MovingRecursivePyramid:BOOL=ON                                           
  -DUSE_MovingShrinkingPyramid:BOOL=ON                                           
  -DUSE_MovingSmoothingPyramid:BOOL=ON                                           
  -DUSE_MultiBSplineTransformWithNormal:BOOL=ON                                           
  -DUSE_MultiInputRandomCoordinateSampler:BOOL=ON                                           
  -DUSE_MultiMetricMultiResolutionRegistration:BOOL=ON                                           
  -DUSE_MultiResolutionRegistration:BOOL=ON                                           
  -DUSE_MultiResolutionRegistrationWithFeatures:BOOL=ON                                           
  -DUSE_MutualInformationHistogramMetric:BOOL=ON                                           
  -DUSE_MyStandardResampler:BOOL=ON                                           
  -DUSE_NearestNeighborInterpolator:BOOL=ON                                           
  -DUSE_NearestNeighborResampleInterpolator:BOOL=ON                                           
  -DUSE_NormalizedGradientCorrelationMetric:BOOL=ON                                           
  -DUSE_NormalizedMutualInformationMetric:BOOL=ON                                           
  -DUSE_PatternIntensityMetric:BOOL=ON                                           
  -DUSE_PolydataDummyPenalty:BOOL=ON                                           
  -DUSE_Powell:BOOL=ON
  -DUSE_QuasiNewtonLBFGS:BOOL=ON                                           
  -DUSE_RSGDEachParameterApart:BOOL=ON                                           
  -DUSE_RandomCoordinateSampler:BOOL=ON                                           
  -DUSE_RandomSampler:BOOL=ON                                           
  -DUSE_RandomSamplerSparseMask:BOOL=ON                                           
  -DUSE_RayCastInterpolator:BOOL=ON                                           
  -DUSE_RayCastResampleInterpolator:BOOL=ON                                           
  -DUSE_ReducedDimensionBSplineInterpolator:BOOL=ON                                           
  -DUSE_ReducedDimensionBSplineResampleInterpolator:BOOL=ON                                           
  -DUSE_RegularStepGradientDescent:BOOL=ON                                           
  -DUSE_SimilarityTransformElastix:BOOL=ON                                           
  -DUSE_Simplex:BOOL=ON                                           
  -DUSE_SimultaneousPerturbation:BOOL=ON                                           
  -DUSE_SplineKernelTransform:BOOL=ON                                           
  -DUSE_StandardGradientDescent:BOOL=ON                                           
  -DUSE_StatisticalShapePenalty:BOOL=ON                                           
  -DUSE_TransformBendingEnergyPenanalty:BOOL=ON
  -DUSE_TransformRigidityPenalty:BOOL=ON                                           
  -DUSE_TranslationTransformElastix:BOOL=ON                                           
  -DUSE_VarianceOverLastDimensionMetric:BOOL=ON                                           
  -DUSE_ViolaWellsMutualInformationMetric:BOOL=ON                                           
  -DUSE_WeightedCombinationTransformElastix:BOOL=ON    
  DEPENDS
  ${ELASTIX_DEPENDENCIES}
)

ExternalProject_Get_Property(elastix BINARY_DIR)
set( ELASTIX_USE_FILE "${BINARY_DIR}/src/UseElastix.cmake" )


