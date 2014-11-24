set( proj ELASTIX )
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
  -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
  -DITK_DIR:PATH=${ITK_DIR}
  # Elastix components
  -DUSE_AdaptiveStochasticGradient:BOOL=          ON                                           
  -DUSE_AdvancedAffineTransform:BOOL=             ON
  -DUSE_AdvancedBSplineTransform:BOOL=            ON                                           
  -DUSE_AdvancedKappaStatisticMetric:BOOL=        ON                                           
  -DUSE_AdvancedMattesMutualInform:BOOL=          ON                                           
  -DUSE_AdvancedMeanSquaresMetric:BOOL=           ON                                           
  -DUSE_AdvancedNormalizedCorrelationMetric:BOOL= ON                                           
  -DUSE_AffineDTITransformElastix:BOOL=           ON                                           
  -DUSE_BSplineInterpolator:BOOL=                 ON                                           
  -DUSE_BSplineInterpolatorFloat:BOOL=            ON                                           
  -DUSE_BSplineResampleInterpolato:BOOL=          ON                                           
  -DUSE_BSplineResampleInterpolato:BOOL=          ON                                           
  -DUSE_BSplineStackTransform:BOOL=               ON                                           
  -DUSE_BSplineTransformWithDiffus:BOOL=          ON                                           
  -DUSE_CMAEvolutionStrategy:BOOL=                ON                                           
  -DUSE_CUDAResampler:BOOL=                       OFF                                          
  -DUSE_ConjugateGradient:BOOL=                   ON                                           
  -DUSE_ConjugateGradientFRPR:BOOL=               ON                                           
  -DUSE_CorrespondingPointsEuclide:BOOL=          ON
  -DUSE_DeformationFieldTransform:BOOL=           ON                                           
  -DUSE_DisplacementMagnitudePenalty:BOOL=        ON                                           
  -DUSE_DistancePreservingRigidity:BOOL=          ON                                           
  -DUSE_EulerTransformElastix:BOOL=               ON                                           
  -DUSE_FiniteDifferenceGradientDescent:BOOL=     ON                                           
  -DUSE_FixedGenericPyramid:BOOL=                 ON                                           
  -DUSE_FixedRecursivePyramid:BOOL=               ON                                           
  -DUSE_FixedShrinkingPyramid:BOOL=               ON                                           
  -DUSE_FixedSmoothingPyramid:BOOL=               ON                                           
  -DUSE_FullSampler:BOOL=                         ON                                           
  -DUSE_FullSearch:BOOL=                          ON                                           
  -DUSE_GradientDifferenceMetric:BOOL=            ON                                           
  -DUSE_GridSampler:BOOL=                         ON                                           
  -DUSE_KNNGraphAlphaMutualInformation:BOOL=      ON                                           
  -DUSE_LinearInterpolator:BOOL=                  ON                                           
  -DUSE_LinearResampleInterpolator:BOOL=          ON                                           
  -DUSE_MissingStructurePenalty:BOOL=             ON
  -DUSE_MovingRecursivePyramid:BOOL=              ON                                           
  -DUSE_MovingShrinkingPyramid:BOOL=              ON                                           
  -DUSE_MovingSmoothingPyramid:BOOL=              ON                                           
  -DUSE_MultiBSplineTransformWithNormals:BOOL=    ON                                           
  -DUSE_MultiInputRandomCoordinate:BOOL=          ON                                           
  -DUSE_MultiMetricMultiResolution:BOOL=          ON                                           
  -DUSE_MultiResolutionRegistration:BOOL=         ON                                           
  -DUSE_MultiResolutionRegistration:BOOL=         ON                                           
  -DUSE_MutualInformationHistogram:BOOL=          ON                                           
  -DUSE_MyStandardResampler:BOOL=                 ON                                           
  -DUSE_NearestNeighborInterpolato:BOOL=          ON                                           
  -DUSE_NearestNeighborResampleInt:BOOL=          ON                                           
  -DUSE_NormalizedGradientCorrelat:BOOL=          ON                                           
  -DUSE_NormalizedMutualInformatio:BOOL=          ON                                           
  -DUSE_PatternIntensityMetric:BOOL=              ON                                           
  -DUSE_PolydataDummyPenalty:BOOL=                ON                                           
  -DUSE_Powell:BOOL=                              ON
  -DUSE_QuasiNewtonLBFGS:BOOL=                    ON                                           
  -DUSE_RSGDEachParameterApart:BOOL=              ON                                           
  -DUSE_RandomCoordinateSampler:BOOL=             ON                                           
  -DUSE_RandomSampler:BOOL=                       ON                                           
  -DUSE_RandomSamplerSparseMask:BOOL=             ON                                           
  -DUSE_RayCastInterpolator:BOOL=                 ON                                           
  -DUSE_RayCastResampleInterpolato:BOOL=          ON                                           
  -DUSE_ReducedDimensionBSplineInt:BOOL=          ON                                           
  -DUSE_ReducedDimensionBSplineRes:BOOL=          ON                                           
  -DUSE_RegularStepGradientDescent:BOOL=          ON                                           
  -DUSE_SimilarityTransformElastix:BOOL=          ON                                           
  -DUSE_Simplex:BOOL=                             ON                                           
  -DUSE_SimultaneousPerturbation:BOOL=            ON                                           
  -DUSE_SplineKernelTransform:BOOL=               ON                                           
  -DUSE_StandardGradientDescent:BOOL=             ON                                           
  -DUSE_StatisticalShapePenalty:BOOL=             ON                                           
  -DUSE_TransformBendingEnergyPena:BOOL=          ON
  -DUSE_TransformRigidityPenalty:BOOL=            ON                                           
  -DUSE_TranslationTransformElasti:BOOL=          ON                                           
  -DUSE_VarianceOverLastDimensionM:BOOL=          ON                                           
  -DUSE_ViolaWellsMutualInformatio:BOOL=          ON                                           
  -DUSE_WeightedCombinationTransform:BOOL=        ON    
  DEPENDS
  ${ELASTIX_DEPENDENCIES}
)

ExternalProject_Get_Property(ELASTIX BINARY_DIR)
set( ELASTIX_USE_FILE "${BINARY_DIR}/src/UseElastix.cmake" )


