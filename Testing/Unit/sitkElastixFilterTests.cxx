#include "elxElastixFilter.h"
#include "elxTransformixFilter.h"
#include "elxParameterObject.h"

#include "itkCastImageFilter.h" 
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "SimpleITKTestHarness.h"

// TODO: Check that desired results are actually obtained, e.g. by comparing result
// images against a baseline. Right now we only check that no errors are thrown.

using namespace elastix;

TEST( ElastixFilterTest, Instantiation )
{
  typedef itk::Image< float, 2 > ImageType;
  typedef ElastixFilter< ImageType, ImageType > ElastixFilterType;
  EXPECT_NO_THROW( ElastixFilterType::Pointer elastixFilter = ElastixFilterType::New() );
}


TEST( ElastixFilterTest, DefaultParameterObject2D )
{
  typedef itk::Image< float, 2 > ImageType;
  typedef itk::ImageFileReader< ImageType > ImageFileReaderType;
  typedef itk::ImageFileWriter< ImageType > ImageFileWriterType;
  typedef ElastixFilter< ImageType, ImageType > ElastixFilterType;

  ImageFileReaderType::Pointer fixedImageReader = ImageFileReaderType::New();
  fixedImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20.png" ) );

  ImageFileReaderType::Pointer movingImageReader = ImageFileReaderType::New();
  movingImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceR10X13Y17.png" ) );

  ElastixFilterType::Pointer elastixFilter;
  EXPECT_NO_THROW( elastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( elastixFilter->SetFixedImage( fixedImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetMovingImage( movingImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->Update() );
}

TEST( ElastixFilterTest, UpdateOnDownstreamUpdate )
{
  ParameterObject::Pointer parameterObject;
  EXPECT_NO_THROW( parameterObject = ParameterObject::New() );
  EXPECT_NO_THROW( parameterObject->SetParameterMap( ParameterObject::GetDefaultParameterMap( "rigid" ) ) );

  typedef itk::Image< float, 2 > ImageType;
  typedef itk::ImageFileReader< ImageType > ImageFileReaderType;
  typedef itk::ImageFileWriter< ImageType > ImageFileWriterType;
  typedef ElastixFilter< ImageType, ImageType > ElastixFilterType;

  ImageFileReaderType::Pointer fixedImageReader = ImageFileReaderType::New();
  fixedImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20.png" ) );

  ImageFileReaderType::Pointer movingImageReader = ImageFileReaderType::New();
  movingImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceR10X13Y17.png" ) );

  ElastixFilterType::Pointer elastixFilter;
  EXPECT_NO_THROW( elastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( elastixFilter->SetFixedImage( fixedImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetMovingImage( movingImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetParameterObject( parameterObject ) );

  ImageFileWriterType::Pointer writer = ImageFileWriterType::New();
  EXPECT_NO_THROW( writer->SetFileName( dataFinder.GetOutputFile( "UpdateOnGetOutputEuler2DResultImage.nii" ) ) );
  EXPECT_NO_THROW( writer->SetInput( elastixFilter->GetOutput() ) );
  EXPECT_NO_THROW( writer->Update() );
}

TEST( ElastixFilterTest, UpdateOnGetTransformParametersEuler2D )
{
  ParameterObject::Pointer parameterObject;
  EXPECT_NO_THROW( parameterObject = ParameterObject::New() );
  EXPECT_NO_THROW( parameterObject->SetParameterMap( ParameterObject::GetDefaultParameterMap( "rigid" ) ) );

  typedef itk::Image< float, 2 > ImageType;
  typedef itk::ImageFileReader< ImageType > ImageFileReaderType;
  typedef itk::ImageFileWriter< ImageType > ImageFileWriterType;
  typedef ElastixFilter< ImageType, ImageType > ElastixFilterType;

  ImageFileReaderType::Pointer fixedImageReader = ImageFileReaderType::New();
  fixedImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20.png" ) );

  ImageFileReaderType::Pointer movingImageReader = ImageFileReaderType::New();
  movingImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceR10X13Y17.png" ) );

  ElastixFilterType::Pointer elastixFilter;
  ParameterObject::Pointer transformParameters;

  EXPECT_NO_THROW( elastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( elastixFilter->SetFixedImage( fixedImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetMovingImage( movingImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetParameterObject( parameterObject ) );
  EXPECT_NO_THROW( transformParameters = elastixFilter->GetTransformParameterObject() );
  EXPECT_TRUE( transformParameters->GetParameterMap()[ 0 ].size() > 0 );
}

TEST( ElastixFilterTest, TranslationWithPointSets2D )
{
  typedef itk::Image< float, 2 > ImageType;
  typedef itk::ImageFileReader< ImageType > ImageFileReaderType;
  typedef itk::ImageFileWriter< ImageType > ImageFileWriterType;
  typedef ElastixFilter< ImageType, ImageType > ElastixFilterType;

  ElastixFilterType::ParameterMapType parameterMap = ParameterObject::GetDefaultParameterMap( "translation" );
  parameterMap[ "Registration" ] = ElastixFilterType::ParameterValueVectorType( 1, "MultiMetricMultiResolutionRegistration" );
  parameterMap[ "Transform" ] = ElastixFilterType::ParameterValueVectorType( 1, "TranslationTransform" );
  parameterMap[ "Metric" ].push_back( "CorrespondingPointsEuclideanDistanceMetric" );
  parameterMap[ "Metric0Weight"] = ElastixFilterType::ParameterValueVectorType( 1, "0.0" );

  ParameterObject::Pointer parameterObject;
  EXPECT_NO_THROW( parameterObject = ParameterObject::New() );
  EXPECT_NO_THROW( parameterObject->SetParameterMap( parameterMap ) );

  std::string fixedPointSetFileName = dataFinder.GetFile( "Input/FixedPointSet.pts" );
  std::ofstream fixedPointSetFile;
  fixedPointSetFile.open( fixedPointSetFileName.c_str() );
  fixedPointSetFile << "point\n";
  fixedPointSetFile << "1\n";
  fixedPointSetFile << "128.0 128.0\n";
  fixedPointSetFile.close();

  std::string movingPointSetFileName = dataFinder.GetFile( "Input/MovingPointSet.pts" );
  std::ofstream movingPointSetFile;
  movingPointSetFile.open( movingPointSetFileName.c_str() );
  movingPointSetFile << "point\n";
  movingPointSetFile << "1\n";
  movingPointSetFile << "115.0 111.0\n";
  movingPointSetFile.close();

  ImageFileReaderType::Pointer fixedImageReader = ImageFileReaderType::New();
  fixedImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20.png" ) );

  ImageFileReaderType::Pointer movingImageReader = ImageFileReaderType::New();
  movingImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceShifted13x17y.png" ) );

  ElastixFilterType::Pointer elastixFilter;
  EXPECT_NO_THROW( elastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( elastixFilter->SetFixedImage( fixedImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetFixedPointSetFileName( dataFinder.GetFile( "Input/FixedPointSet.pts" )  ) );
  EXPECT_NO_THROW( elastixFilter->SetMovingImage( movingImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetMovingPointSetFileName( dataFinder.GetFile( "Input/MovingPointSet.pts" ) ) );
  EXPECT_NO_THROW( elastixFilter->SetParameterObject( parameterObject ) );

  ImageFileWriterType::Pointer writer = ImageFileWriterType::New();
  EXPECT_NO_THROW( writer->SetFileName( dataFinder.GetOutputFile( "TranslationWithPointSets2DResultImage.nii" ) ) );
  EXPECT_NO_THROW( writer->SetInput( elastixFilter->GetOutput() ) );
  EXPECT_NO_THROW( writer->Update() );

  ParameterObject::Pointer transformParameterObject;
  EXPECT_NO_THROW( transformParameterObject = elastixFilter->GetTransformParameterObject() );
 }

TEST( ElastixFilterTest, BSplineWithFixedMask2D )
{
  typedef itk::Image< float, 2 > ImageType;
  typedef itk::ImageFileReader< ImageType > ImageFileReaderType;
  typedef itk::ImageFileWriter< ImageType > ImageFileWriterType;
  typedef ElastixFilter< ImageType, ImageType > ElastixFilterType;

  ImageFileReaderType::Pointer fixedImageReader = ImageFileReaderType::New();
  fixedImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20.png" ) );

  ImageFileReaderType::Pointer fixedMaskReader = ImageFileReaderType::New();
  fixedMaskReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20Mask.png" ) );

  ImageFileReaderType::Pointer movingImageReader = ImageFileReaderType::New();
  movingImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceR10X13Y17.png" ) );

  typedef itk::CastImageFilter< ImageType, ElastixFilterType::FixedMaskType > CastMaskFilterType;
  CastMaskFilterType::Pointer castImageFilter = CastMaskFilterType::New();
  castImageFilter->SetInput( fixedMaskReader->GetOutput() );
  EXPECT_NO_THROW( castImageFilter->Update() );

  ParameterObject::Pointer parameterObject = ParameterObject::New();
  ElastixFilterType::ParameterMapType parameterMap = parameterObject->GetDefaultParameterMap( "affine" );
  parameterMap[ "ImageSampler" ] = ElastixFilterType::ParameterValueVectorType( 1, "RandomSparseMask" );
  parameterObject->SetParameterMap( parameterMap );

  ElastixFilterType::Pointer elastixFilter;
  EXPECT_NO_THROW( elastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( elastixFilter->SetParameterObject( parameterObject ) );
  EXPECT_NO_THROW( elastixFilter->SetFixedImage( fixedImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetFixedMask( castImageFilter->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetMovingImage( movingImageReader->GetOutput() ) );

  ImageFileWriterType::Pointer writer = ImageFileWriterType::New();
  EXPECT_NO_THROW( writer->SetFileName( dataFinder.GetOutputFile( "BSplineWithFixedMask2DResultImage.nii" ) ) );
  EXPECT_NO_THROW( writer->SetInput( elastixFilter->GetOutput() ) );
  EXPECT_NO_THROW( writer->Update() );

  ParameterObject::Pointer transformParameterObject;
  EXPECT_NO_THROW( transformParameterObject = elastixFilter->GetTransformParameterObject() );
}

TEST( ElastixFilterTest, InitialTransformTestEuler2D )
{
  ParameterObject::Pointer parameterObject;
  EXPECT_NO_THROW( parameterObject = ParameterObject::New() );
  EXPECT_NO_THROW( parameterObject->SetParameterMap( ParameterObject::GetDefaultParameterMap( "rigid" ) ) );

  typedef itk::Image< float, 2 > ImageType;
  typedef itk::ImageFileReader< ImageType > ImageFileReaderType;
  typedef itk::ImageFileWriter< ImageType > ImageFileWriterType;
  typedef ElastixFilter< ImageType, ImageType > ElastixFilterType;

  ImageFileReaderType::Pointer fixedImageReader = ImageFileReaderType::New();
  fixedImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20.png" ) );

  ImageFileReaderType::Pointer movingImageReader = ImageFileReaderType::New();
  movingImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceR10X13Y17.png" ) );

  ElastixFilterType::Pointer initialElastixFilter;
  EXPECT_NO_THROW( initialElastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( initialElastixFilter->SetFixedImage( fixedImageReader->GetOutput() ) );
  EXPECT_NO_THROW( initialElastixFilter->SetMovingImage( movingImageReader->GetOutput() ) );
  EXPECT_NO_THROW( initialElastixFilter->SetParameterObject( parameterObject ) );
  EXPECT_NO_THROW( initialElastixFilter->GetTransformParameterObject()->WriteParameterFile( "initialTransformTestEuler2D.txt" ) );

  ElastixFilterType::Pointer elastixFilter;
  EXPECT_NO_THROW( elastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( elastixFilter->SetFixedImage( fixedImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetMovingImage( movingImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetParameterObject( parameterObject ) );
  EXPECT_NO_THROW( elastixFilter->SetInitialTransformParameterFileName( "initialTransformTestEuler2D.txt" ) );

  ImageFileWriterType::Pointer writer = ImageFileWriterType::New();
  EXPECT_NO_THROW( writer->SetFileName( dataFinder.GetOutputFile( "InitialTransformTestEuler2DResultImage.nii" ) ) );
  EXPECT_NO_THROW( writer->SetInput( elastixFilter->GetOutput() ) );
  EXPECT_NO_THROW( writer->Update() );
}

TEST( ElastixFilterTest, InverseTransformTestEuler2D )
{
  ParameterObject::Pointer parameterObject;
  EXPECT_NO_THROW( parameterObject = ParameterObject::New() );
  EXPECT_NO_THROW( parameterObject->SetParameterMap( ParameterObject::GetDefaultParameterMap( "rigid" ) ) );

  typedef itk::Image< float, 2 > ImageType;
  typedef itk::ImageFileReader< ImageType > ImageFileReaderType;
  typedef itk::ImageFileWriter< ImageType > ImageFileWriterType;
  typedef ElastixFilter< ImageType, ImageType > ElastixFilterType;
  typedef TransformixFilter< ImageType > TransformixFilterType;

  ImageFileReaderType::Pointer fixedImageReader = ImageFileReaderType::New();
  fixedImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20.png" ) );

  ImageFileReaderType::Pointer inputImageReader = ImageFileReaderType::New();
  inputImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20.png" ) );

  ImageFileReaderType::Pointer movingImageReader = ImageFileReaderType::New();
  movingImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceR10X13Y17.png" ) );

  // Forward registration
  ElastixFilterType::Pointer forwardElastixFilter;
  EXPECT_NO_THROW( forwardElastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( forwardElastixFilter->SetFixedImage( fixedImageReader->GetOutput() ) );
  EXPECT_NO_THROW( forwardElastixFilter->SetMovingImage( movingImageReader->GetOutput() ) );
  EXPECT_NO_THROW( forwardElastixFilter->SetParameterObject( parameterObject ) );
  EXPECT_NO_THROW( forwardElastixFilter->GetTransformParameterObject()->WriteParameterFile( dataFinder.GetOutputFile( "inverseTransformTestEuler2D.txt" ) ) );

  // Inverse registration
  ElastixFilterType::ParameterMapType parameterMap = ParameterObject::GetDefaultParameterMap( "rigid" );
  parameterMap[ "Metric" ] = ElastixFilterType::ParameterValueVectorType( 1, "DisplacementMagnitudePenalty" );
  ParameterObject::Pointer inverseParameterObject;
  EXPECT_NO_THROW( inverseParameterObject = ParameterObject::New() );
  EXPECT_NO_THROW( inverseParameterObject->SetParameterMap( parameterMap ) );

  ElastixFilterType::Pointer inverseElastixFilter;
  EXPECT_NO_THROW( inverseElastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( inverseElastixFilter->SetFixedImage( fixedImageReader->GetOutput() ) );
  EXPECT_NO_THROW( inverseElastixFilter->SetMovingImage( fixedImageReader->GetOutput() ) );
  EXPECT_NO_THROW( inverseElastixFilter->SetParameterObject( inverseParameterObject ) );
  EXPECT_NO_THROW( inverseElastixFilter->SetInitialTransformParameterFileName( dataFinder.GetOutputFile( "inverseTransformTestEuler2D.txt" ) ) );
  EXPECT_NO_THROW( inverseElastixFilter->Update() );

  ElastixFilterType::ParameterMapVectorType inverseParameterMap;
  EXPECT_NO_THROW( inverseParameterMap = inverseElastixFilter->GetTransformParameterObject()->GetParameterMap() );
  EXPECT_NO_THROW( inverseParameterMap[ 0 ][ "InitialTransformParametersFileName" ] = ElastixFilterType::ParameterValueVectorType( 1, "NoInitialTransform" ) );

  ParameterObject::Pointer inverseTransformParameterObject = ParameterObject::New();
  inverseTransformParameterObject->SetParameterMap( inverseParameterMap );

  // Warp fixed image to moving image with the inverse transform
  TransformixFilterType::Pointer transformixFilter = TransformixFilterType::New();
  EXPECT_NO_THROW( transformixFilter->SetInput( inputImageReader->GetOutput() ) );
  EXPECT_NO_THROW( transformixFilter->SetTransformParameterObject( inverseTransformParameterObject ) );

  ImageFileWriterType::Pointer writer = ImageFileWriterType::New();
  EXPECT_NO_THROW( writer->SetFileName( dataFinder.GetOutputFile( "InverseTransformTestEuler2DResultImage.nii" ) ) );
  EXPECT_NO_THROW( writer->SetInput( transformixFilter->GetOutput() ) );
  EXPECT_NO_THROW( writer->Update() );
}

TEST( ElastixFilterTest, SameFixedImageForMultipleRegistrations )
{ 
  typedef itk::Image< float, 2 > ImageType;
  typedef itk::ImageFileReader< ImageType > ImageFileReaderType;
  typedef itk::ImageFileWriter< ImageType > ImageFileWriterType;
  typedef ElastixFilter< ImageType, ImageType > ElastixFilterType;

  ImageFileReaderType::Pointer fixedImageReader = ImageFileReaderType::New();
  fixedImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20.png" ) );

  ImageFileReaderType::Pointer movingImageReader1 = ImageFileReaderType::New();
  movingImageReader1->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceR10X13Y17.png" ) );

  ImageFileReaderType::Pointer movingImageReader2 = ImageFileReaderType::New();
  movingImageReader2->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceR10X13Y17.png" ) );

  ElastixFilterType::Pointer elastixFilter;

  EXPECT_NO_THROW( elastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( elastixFilter->SetFixedImage( fixedImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetMovingImage( movingImageReader1->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->Update() );

  EXPECT_NO_THROW( elastixFilter->SetMovingImage( movingImageReader2->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->Update() );
}

TEST( ElastixFilterTest, BSpline3D )
{
  typedef itk::Image< float, 3 > ImageType;
  typedef itk::ImageFileReader< ImageType > ImageFileReaderType;
  typedef itk::ImageFileWriter< ImageType > ImageFileWriterType;
  typedef ElastixFilter< ImageType, ImageType > ElastixFilterType;

  ParameterObject::Pointer parameterObject;
  EXPECT_NO_THROW( parameterObject = ParameterObject::New() );
  EXPECT_NO_THROW( parameterObject->SetParameterMap( parameterObject->GetDefaultParameterMap( "nonrigid" ) ) );

  ImageFileReaderType::Pointer fixedImageReader = ImageFileReaderType::New();
  fixedImageReader->SetFileName( dataFinder.GetFile( "Input/OAS1_0001_MR1_mpr-1_anon.nrrd" ) );

  ImageFileReaderType::Pointer movingImageReader = ImageFileReaderType::New();
  movingImageReader->SetFileName( dataFinder.GetFile( "Input/OAS1_0002_MR1_mpr-1_anon.nrrd" ) );

  ElastixFilterType::Pointer elastixFilter;
  EXPECT_NO_THROW( elastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( elastixFilter->SetFixedImage( fixedImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetMovingImage( movingImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetParameterObject( parameterObject ) );

  ImageFileWriterType::Pointer writer = ImageFileWriterType::New();
  EXPECT_NO_THROW( writer->SetFileName( dataFinder.GetOutputFile( "BSpline3DResultImage.nii" ) ) );
  EXPECT_NO_THROW( writer->SetInput( elastixFilter->GetOutput() ) );
  EXPECT_NO_THROW( writer->Update() );

  ParameterObject::Pointer transformParameterObject;
  EXPECT_NO_THROW( transformParameterObject = elastixFilter->GetTransformParameterObject() );
}

TEST( ElastixFilterTest, BSpline4D )
{
  typedef itk::Image< float, 4 > ImageType;
  typedef itk::ImageFileReader< ImageType > ImageFileReaderType;
  typedef itk::ImageFileWriter< ImageType > ImageFileWriterType;
  typedef ElastixFilter< ImageType, ImageType > ElastixFilterType;

  ElastixFilterType::ParameterMapType parameterMap = ParameterObject::GetDefaultParameterMap( "groupwise" );
  parameterMap[ "MaximumNumberOfIterations" ] = ElastixFilterType::ParameterValueVectorType( 1, "4" );

  ParameterObject::Pointer parameterObject;
  EXPECT_NO_THROW( parameterObject = ParameterObject::New() );
  EXPECT_NO_THROW( parameterObject->SetParameterMap( parameterMap ) );
  
  ImageFileReaderType::Pointer imageReader1 = ImageFileReaderType::New();
  imageReader1->SetFileName( dataFinder.GetFile( "Input/4D.nii.gz" ) );

  ImageFileReaderType::Pointer imageReader2 = ImageFileReaderType::New();
  imageReader2->SetFileName( dataFinder.GetFile( "Input/4D.nii.gz" ) );

  ElastixFilterType::Pointer elastixFilter;
  EXPECT_NO_THROW( elastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( elastixFilter->SetFixedImage( imageReader1->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetMovingImage( imageReader2->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetParameterObject( parameterObject ) );
  EXPECT_NO_THROW( elastixFilter->Update() );

  ImageFileWriterType::Pointer writer = ImageFileWriterType::New();
  EXPECT_NO_THROW( writer->SetFileName( dataFinder.GetOutputFile( "BSpline4DResultImage.nii" ) ) );
  EXPECT_NO_THROW( writer->SetInput( elastixFilter->GetOutput() ) );
  EXPECT_NO_THROW( writer->Update() );

  ParameterObject::Pointer transformParameterObject;
  EXPECT_NO_THROW( transformParameterObject = elastixFilter->GetTransformParameterObject() );
}
