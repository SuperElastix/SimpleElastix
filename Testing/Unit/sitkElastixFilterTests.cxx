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
  typedef ElastixFilter< ImageType, ImageType > ElastixFilterType;

  ImageFileReaderType::Pointer fixedImageReader = ImageFileReaderType::New();
  fixedImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20.png" ) );

  ImageFileReaderType::Pointer movingImageReader = ImageFileReaderType::New();
  movingImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceShifted13x17y.png" ) );

  ElastixFilterType::Pointer elastixFilter;
  EXPECT_NO_THROW( elastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( elastixFilter->SetFixedImage( fixedImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetMovingImage( movingImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->Update() );
}

TEST( ElastixFilterTest, UpdateOnOutputImageDownstreamUpdate )
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
  movingImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceShifted13x17y.png" ) );

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

/*
TEST( ElastixFilterTest, UpdateOnTransformParametersDownstreamUpdate )
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

  ImageFileReaderType::Pointer movingImageReader1 = ImageFileReaderType::New();
  movingImageReader1->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceShifted13x17y.png" ) );

  ImageFileReaderType::Pointer movingImageReader2 = ImageFileReaderType::New();
  movingImageReader2->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceShifted13x17y.png" ) );

  ElastixFilterType::Pointer elastixFilter;
  TransformixFilterType::Pointer transformixFilter;
  ParameterObject::Pointer transformParameterObject;

  EXPECT_NO_THROW( elastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( elastixFilter->SetFixedImage( fixedImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetMovingImage( movingImageReader1->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetParameterObject( parameterObject ) );

  // TODO: Fix getting transform parameter object resulting in "Illegal instruction: 4"
  EXPECT_NO_THROW( transformixFilter->SetTransformParameterObject( elastixFilter->GetTransformParameterObject() ) );
  EXPECT_NO_THROW( transformixFilter->SetInput( movingImageReader2->GetOutput() ));
  EXPECT_NO_THROW( transformixFilter->Update() );
}
*/

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
  parameterMap[ "MaximumNumberOfIterations" ] = ElastixFilterType::ParameterValueVectorType( 1, "1" );

  ParameterObject::Pointer parameterObject;
  EXPECT_NO_THROW( parameterObject = ParameterObject::New() );
  EXPECT_NO_THROW( parameterObject->SetParameterMap( parameterMap ) );

  std::string fixedPointSetFileName = dataFinder.GetOutputFile( "FixedPointSet.pts" );
  std::ofstream fixedPointSetFile;
  fixedPointSetFile.open( fixedPointSetFileName.c_str() );
  fixedPointSetFile << "point\n";
  fixedPointSetFile << "1\n";
  fixedPointSetFile << "128.0 128.0\n";
  fixedPointSetFile.close();

  std::string movingPointSetFileName = dataFinder.GetOutputFile( "MovingPointSet.pts" );
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
  EXPECT_NO_THROW( elastixFilter->SetFixedPointSetFileName( dataFinder.GetOutputFile( "FixedPointSet.pts" ) ) );
  EXPECT_NO_THROW( elastixFilter->SetMovingImage( movingImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetMovingPointSetFileName( dataFinder.GetOutputFile( "MovingPointSet.pts" ) ) );
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
  typedef itk::Image< unsigned char, 2 > MaskType;
  typedef typename MaskType::Pointer MaskPointer;
  typedef itk::ImageFileReader< ImageType > ImageFileReaderType;
  typedef itk::ImageFileWriter< ImageType > ImageFileWriterType;
  typedef ElastixFilter< ImageType, ImageType > ElastixFilterType;

  ImageFileReaderType::Pointer fixedImageReader = ImageFileReaderType::New();
  fixedImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20.png" ) );

  ImageFileReaderType::Pointer movingImageReader = ImageFileReaderType::New();
  movingImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceShifted13x17y.png" ) );

  ParameterObject::Pointer parameterObject = ParameterObject::New();
  ElastixFilterType::ParameterMapType parameterMap = parameterObject->GetDefaultParameterMap( "affine" );
  parameterMap[ "ImageSampler" ] = ElastixFilterType::ParameterValueVectorType( 1, "RandomSparseMask" );
  parameterMap[ "MaximumNumberOfIterations" ] = ElastixFilterType::ParameterValueVectorType( 1, "1" );
  parameterObject->SetParameterMap( parameterMap );

  fixedImageReader->Update();
  MaskPointer fixedMask = MaskType::New();
  fixedMask->CopyInformation(fixedImageReader->GetOutput());
  fixedMask->SetRegions(fixedImageReader->GetOutput()->GetLargestPossibleRegion());
  fixedMask->Allocate();
  fixedMask->FillBuffer(1);

  ElastixFilterType::Pointer elastixFilter;
  EXPECT_NO_THROW( elastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( elastixFilter->SetParameterObject( parameterObject ) );
  EXPECT_NO_THROW( elastixFilter->SetFixedImage( fixedImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetFixedMask( fixedMask ) );
  EXPECT_NO_THROW( elastixFilter->SetMovingImage( movingImageReader->GetOutput() ) );
  elastixFilter->LogToConsoleOn();

  ImageFileWriterType::Pointer writer = ImageFileWriterType::New();
  EXPECT_NO_THROW( writer->SetFileName( dataFinder.GetOutputFile( "BSplineWithFixedMask2DResultImage.nii" ) ) );
  EXPECT_NO_THROW( writer->SetInput( elastixFilter->GetOutput() ) ); writer->Update();
  EXPECT_NO_THROW( writer->Update() );

  ParameterObject::Pointer transformParameterObject;
  EXPECT_NO_THROW( transformParameterObject = elastixFilter->GetTransformParameterObject() );
}

TEST( ElastixFilterTest, InitialTransformTestEuler2D )
{
  ParameterObject::Pointer parameterObject;
  EXPECT_NO_THROW( parameterObject = ParameterObject::New() );
  EXPECT_NO_THROW( parameterObject->SetParameterMap( ParameterObject::GetDefaultParameterMap( "rigid" ) ) );
  parameterObject->SetParameter( "MaximumNumberOfIterations", "4" );

  typedef itk::Image< float, 2 > ImageType;
  typedef itk::ImageFileReader< ImageType > ImageFileReaderType;
  typedef itk::ImageFileWriter< ImageType > ImageFileWriterType;
  typedef ElastixFilter< ImageType, ImageType > ElastixFilterType;

  ImageFileReaderType::Pointer fixedImageReader = ImageFileReaderType::New();
  fixedImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20.png" ) );

  ImageFileReaderType::Pointer movingImageReader = ImageFileReaderType::New();
  movingImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceShifted13x17y.png" ) );

  ElastixFilterType::Pointer initialElastixFilter;
  EXPECT_NO_THROW( initialElastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( initialElastixFilter->SetFixedImage( fixedImageReader->GetOutput() ) );
  EXPECT_NO_THROW( initialElastixFilter->SetMovingImage( movingImageReader->GetOutput() ) );
  EXPECT_NO_THROW( initialElastixFilter->SetParameterObject( parameterObject ) );
  EXPECT_NO_THROW( initialElastixFilter->Update() );
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

TEST( ElastixFilterTest, SameFixedImageForMultipleRegistrations )
{ 
  typedef itk::Image< float, 2 > ImageType;
  typedef itk::ImageFileReader< ImageType > ImageFileReaderType;
  typedef ElastixFilter< ImageType, ImageType > ElastixFilterType;

  ImageFileReaderType::Pointer fixedImageReader = ImageFileReaderType::New();
  fixedImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20.png" ) );

  ImageFileReaderType::Pointer movingImageReader1 = ImageFileReaderType::New();
  movingImageReader1->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceShifted13x17y.png" ) );

  ImageFileReaderType::Pointer movingImageReader2 = ImageFileReaderType::New();
  movingImageReader2->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceShifted13x17y.png" ) );

  ElastixFilterType::Pointer elastixFilter = ElastixFilterType::New();
  elastixFilter->GetParameterObject()->SetParameter( "MaximumNumberOfIterations", "1" );

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
  parameterObject->SetParameter( "MaximumNumberOfIterations", "4" );

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
  parameterMap[ "MaximumNumberOfIterations" ] = ElastixFilterType::ParameterValueVectorType( 1, "1" );

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
