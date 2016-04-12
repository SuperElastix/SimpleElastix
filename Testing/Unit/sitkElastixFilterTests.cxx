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
  EXPECT_NO_THROW( elastixFilter->LogToConsoleOn() );
  EXPECT_NO_THROW( elastixFilter->SetFixedImage( fixedImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetMovingImage( movingImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->Update() );
}

TEST( ElastixFilterTest, UpdateOnDownstreamUpdate )
{
  ParameterObject::Pointer parameterObject;
  EXPECT_NO_THROW( parameterObject = ParameterObject::New() );
  EXPECT_NO_THROW( parameterObject->SetParameterMap( "rigid" ) );

  typedef itk::Image< float, 2 > ImageType;
  typedef itk::ImageFileReader< ImageType > ImageFileReaderType;
  typedef itk::ImageFileWriter< ImageType > ImageFileWriterType;
  typedef ElastixFilter< ImageType, ImageType > ElastixFilterType;

  ImageFileReaderType::Pointer fixedImageReader = ImageFileReaderType::New();
  fixedImageReader->SetFileName( "/Users/kasper/Development/build/SimpleElastixDebug/SimpleITK-build/ExternalData/Testing/Data/Input/BrainProtonDensitySliceBorder20.png" );

  ImageFileReaderType::Pointer movingImageReader = ImageFileReaderType::New();
  movingImageReader->SetFileName( "/Users/kasper/Development/build/SimpleElastixDebug/SimpleITK-build/ExternalData/Testing/Data/Input/BrainProtonDensitySliceR10X13Y17.png" );

  ElastixFilterType::Pointer elastixFilter;
  EXPECT_NO_THROW( elastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( elastixFilter->LogToConsoleOn() );
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
  EXPECT_NO_THROW( parameterObject->SetParameterMap( "rigid" ) );

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
  EXPECT_NO_THROW( elastixFilter->LogToConsoleOn() );
  EXPECT_NO_THROW( elastixFilter->SetFixedImage( fixedImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetMovingImage( movingImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetParameterObject( parameterObject ) );
  EXPECT_NO_THROW( transformParameters = elastixFilter->GetTransformParameterObject() );
  EXPECT_TRUE( transformParameters->GetParameterMap()[ 0 ].size() > 0 );
}

TEST( ElastixFilterTest, AffineWithDataObjectContainerInterface2D )
{
  typedef itk::Image< float, 2 > ImageType;
  typedef itk::ImageFileReader< ImageType > ImageFileReaderType;
  typedef itk::ImageFileWriter< ImageType > ImageFileWriterType;
  typedef ElastixFilter< ImageType, ImageType > ElastixFilterType;
  typedef ElastixFilterType::DataObjectContainerType  DataObjectContainerType;
  typedef ElastixFilterType::DataObjectContainerPointer DataObjectContainerPointer;

  ParameterObject::Pointer parameterObject;
  EXPECT_NO_THROW( parameterObject = ParameterObject::New() );
  EXPECT_NO_THROW( parameterObject->SetParameterMap( "affine" ) );
  EXPECT_NO_THROW( parameterObject->GetParameterMap( 0 )[ "Registration" ] = ElastixFilterType::ParameterValueVectorType( 1, "MultiMetricMultiResolutionRegistration" ) );
  EXPECT_NO_THROW( parameterObject->GetParameterMap( 0 )[ "Metric" ] = ElastixFilterType::ParameterValueVectorType( 2, parameterObject->GetParameterMap( 0 )[ "Metric" ][ 0 ] ) );
  EXPECT_NO_THROW( parameterObject->GetParameterMap( 0 )[ "ImageSampler" ] = ElastixFilterType::ParameterValueVectorType( 2, parameterObject->GetParameterMap( 0 )[ "ImageSampler" ][ 0 ] ) );
  EXPECT_NO_THROW( parameterObject->GetParameterMap( 0 )[ "Interpolator" ] = ElastixFilterType::ParameterValueVectorType( 2, parameterObject->GetParameterMap( 0 )[ "Interpolator" ][ 0 ] ) );
  EXPECT_NO_THROW( parameterObject->GetParameterMap( 0 )[ "FixedImagePyramid" ] = ElastixFilterType::ParameterValueVectorType( 2, parameterObject->GetParameterMap( 0 )[ "FixedImagePyramid" ][ 0 ] ) );
  EXPECT_NO_THROW( parameterObject->GetParameterMap( 0 )[ "MovingImagePyramid" ] = ElastixFilterType::ParameterValueVectorType( 2, parameterObject->GetParameterMap( 0 )[ "MovingImagePyramid" ][ 0 ] ) );

  ImageFileReaderType::Pointer fixedImageReader0 = ImageFileReaderType::New();
  fixedImageReader0->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20.png" ) );

  ImageFileReaderType::Pointer fixedImageReader1 = ImageFileReaderType::New();
  fixedImageReader1->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20.png" ) );

  ImageFileReaderType::Pointer movingImageReader0 = ImageFileReaderType::New();
  movingImageReader0->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceR10X13Y17S12.png" ) );

  ImageFileReaderType::Pointer movingImageReader1 = ImageFileReaderType::New();
  movingImageReader1->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceR10X13Y17S12.png" ) );

  // We fill the first pair of fixed and moving images with zeros to be able 
  // to inspect if the subsequent pair is able to drive the registration
  ImageType::Pointer fixedImage0 = fixedImageReader0->GetOutput();
  fixedImage0->Update();
  fixedImage0->DisconnectPipeline();
  fixedImage0->FillBuffer( 0.0 );
  ImageType::Pointer movingImage0 = movingImageReader0->GetOutput();
  movingImage0->Update();
  movingImage0->DisconnectPipeline();
  movingImage0->FillBuffer( 0.0 );

  DataObjectContainerPointer fixedImages;
  EXPECT_NO_THROW( fixedImages = DataObjectContainerType::New() );
  EXPECT_NO_THROW( fixedImages->CreateElementAt( 0 ) = static_cast< itk::DataObject* >( fixedImage0 ) );
  EXPECT_NO_THROW( fixedImages->CreateElementAt( 1 ) = static_cast< itk::DataObject* >( fixedImageReader1->GetOutput() ) );

  DataObjectContainerPointer movingImages;
  EXPECT_NO_THROW( movingImages = DataObjectContainerType::New() );
  EXPECT_NO_THROW( movingImages->CreateElementAt( 0 ) = static_cast< itk::DataObject* >( movingImage0 ) );
  EXPECT_NO_THROW( movingImages->CreateElementAt( 1 ) = static_cast< itk::DataObject* >( movingImageReader1->GetOutput() ) );

  ElastixFilterType::Pointer elastixFilter;
  EXPECT_NO_THROW( elastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( elastixFilter->LogToConsoleOn() );
  EXPECT_NO_THROW( elastixFilter->SetFixedImage( fixedImages ) );
  EXPECT_NO_THROW( elastixFilter->SetMovingImage( movingImages ) );
  EXPECT_NO_THROW( elastixFilter->SetParameterObject( parameterObject ) );

  ImageFileWriterType::Pointer writer = ImageFileWriterType::New();
  EXPECT_NO_THROW( writer->SetFileName( dataFinder.GetOutputFile( "AffineWithDataObjectContainerInterface2D.nii" ) ) );
  EXPECT_NO_THROW( writer->SetInput( elastixFilter->GetOutput() ) );
  EXPECT_NO_THROW( writer->Update() );

  ParameterObject::Pointer transformParameterObject;
  EXPECT_NO_THROW( transformParameterObject = elastixFilter->GetTransformParameterObject() );
}

TEST( ElastixFilterTest, AffineWithAddImagesInterface2D )
{
  typedef itk::Image< float, 2 > ImageType;
  typedef itk::ImageFileReader< ImageType > ImageFileReaderType;
  typedef itk::ImageFileWriter< ImageType > ImageFileWriterType;
  typedef ElastixFilter< ImageType, ImageType > ElastixFilterType;
  typedef ElastixFilterType::DataObjectContainerType  DataObjectContainerType;
  typedef ElastixFilterType::DataObjectContainerPointer DataObjectContainerPointer;

  ParameterObject::Pointer parameterObject;
  EXPECT_NO_THROW( parameterObject = ParameterObject::New() );
  EXPECT_NO_THROW( parameterObject->SetParameterMap( "affine" ) );
  EXPECT_NO_THROW( parameterObject->GetParameterMap( 0 )[ "Registration" ] = ElastixFilterType::ParameterValueVectorType( 1, "MultiMetricMultiResolutionRegistration" ) );
  EXPECT_NO_THROW( parameterObject->GetParameterMap( 0 )[ "Metric" ] = ElastixFilterType::ParameterValueVectorType( 2, parameterObject->GetParameterMap( 0 )[ "Metric" ][ 0 ] ) );
  EXPECT_NO_THROW( parameterObject->GetParameterMap( 0 )[ "ImageSampler" ] = ElastixFilterType::ParameterValueVectorType( 2, parameterObject->GetParameterMap( 0 )[ "ImageSampler" ][ 0 ] ) );
  EXPECT_NO_THROW( parameterObject->GetParameterMap( 0 )[ "Interpolator" ] = ElastixFilterType::ParameterValueVectorType( 2, parameterObject->GetParameterMap( 0 )[ "Interpolator" ][ 0 ] ) );
  EXPECT_NO_THROW( parameterObject->GetParameterMap( 0 )[ "FixedImagePyramid" ] = ElastixFilterType::ParameterValueVectorType( 2, parameterObject->GetParameterMap( 0 )[ "FixedImagePyramid" ][ 0 ] ) );
  EXPECT_NO_THROW( parameterObject->GetParameterMap( 0 )[ "MovingImagePyramid" ] = ElastixFilterType::ParameterValueVectorType( 2, parameterObject->GetParameterMap( 0 )[ "MovingImagePyramid" ][ 0 ] ) );

  ImageFileReaderType::Pointer fixedImageReader0 = ImageFileReaderType::New();
  fixedImageReader0->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20.png" ) );

  ImageFileReaderType::Pointer fixedImageReader1 = ImageFileReaderType::New();
  fixedImageReader1->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20.png" ) );

  ImageFileReaderType::Pointer movingImageReader0 = ImageFileReaderType::New();
  movingImageReader0->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceR10X13Y17S12.png" ) );

  ImageFileReaderType::Pointer movingImageReader1 = ImageFileReaderType::New();
  movingImageReader1->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceR10X13Y17S12.png" ) );

  // We fill the first pair of fixed and moving images with zeros to be able 
  // to inspect that the subsequent pair is really driving the registration
  ImageType::Pointer fixedImage0 = fixedImageReader0->GetOutput();
  fixedImage0->Update();
  fixedImage0->DisconnectPipeline();
  fixedImage0->FillBuffer( 0.0 );
  ImageType::Pointer movingImage0 = movingImageReader0->GetOutput();
  movingImage0->Update();
  movingImage0->DisconnectPipeline();
  movingImage0->FillBuffer( 0.0 );

  ElastixFilterType::Pointer elastixFilter;
  EXPECT_NO_THROW( elastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( elastixFilter->LogToConsoleOn() );
  EXPECT_NO_THROW( elastixFilter->AddFixedImage( fixedImage0 ) );
  EXPECT_NO_THROW( elastixFilter->AddFixedImage( fixedImageReader1->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->AddMovingImage( movingImage0 ) );
  EXPECT_NO_THROW( elastixFilter->AddMovingImage( movingImageReader1->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetParameterObject( parameterObject ) );

  ImageFileWriterType::Pointer writer = ImageFileWriterType::New();
  EXPECT_NO_THROW( writer->SetFileName( dataFinder.GetOutputFile( "AffineWithAddImagesInterface2D.nii" ) ) );
  EXPECT_NO_THROW( writer->SetInput( elastixFilter->GetOutput() ) );
  EXPECT_NO_THROW( writer->Update() );

  ParameterObject::Pointer transformParameterObject;
  EXPECT_NO_THROW( transformParameterObject = elastixFilter->GetTransformParameterObject() );
}

TEST( ElastixFilterTest, TranslationWithPointSets2D )
{
  typedef itk::Image< float, 2 > ImageType;
  typedef itk::ImageFileReader< ImageType > ImageFileReaderType;
  typedef itk::ImageFileWriter< ImageType > ImageFileWriterType;
  typedef ElastixFilter< ImageType, ImageType > ElastixFilterType;

  ParameterObject::Pointer parameterObject;
  EXPECT_NO_THROW( parameterObject = ParameterObject::New() );
  EXPECT_NO_THROW( parameterObject->SetParameterMap( "translation" ) );
  EXPECT_NO_THROW( parameterObject->GetParameterMap( 0 )[ "Registration" ] = ElastixFilterType::ParameterValueVectorType( 1, "MultiMetricMultiResolutionRegistration" ) );
  EXPECT_NO_THROW( parameterObject->GetParameterMap( 0 )[ "Transform" ] = ElastixFilterType::ParameterValueVectorType( 1, "TranslationTransform" ) );
  EXPECT_NO_THROW( parameterObject->GetParameterMap( 0 )[ "Metric" ].push_back( "CorrespondingPointsEuclideanDistanceMetric" ) );
  EXPECT_NO_THROW( parameterObject->GetParameterMap( 0 )[ "Metric0Weight"] = ElastixFilterType::ParameterValueVectorType( 1, "0.0" ) );

  // We generate the point sets manually
  std::ofstream fixedPointSetFile;
  fixedPointSetFile.open( dataFinder.GetFile( "Input/FixedPointSet.pts" ) );
  fixedPointSetFile << "point\n";
  fixedPointSetFile << "1\n";
  fixedPointSetFile << "128.0 128.0\n";
  fixedPointSetFile.close();

  std::ofstream movingPointSetFile;
  movingPointSetFile.open( dataFinder.GetFile( "Input/MovingPointSet.pts" ) );
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
  EXPECT_NO_THROW( elastixFilter->LogToConsoleOn() );
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
  ElastixFilterType::ParameterMapType parameterMap = parameterObject->GetParameterMap( "affine" );
  parameterMap[ "ImageSampler" ] = ElastixFilterType::ParameterValueVectorType( 1, "RandomSparseMask" );
  parameterObject->SetParameterMap( parameterMap );

  ElastixFilterType::Pointer elastixFilter;
  EXPECT_NO_THROW( elastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( elastixFilter->LogToConsoleOn() );
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
  EXPECT_NO_THROW( parameterObject->SetParameterMap( "rigid" ) );

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
  EXPECT_NO_THROW( initialElastixFilter->LogToConsoleOn() );
  EXPECT_NO_THROW( initialElastixFilter->SetFixedImage( fixedImageReader->GetOutput() ) );
  EXPECT_NO_THROW( initialElastixFilter->SetMovingImage( movingImageReader->GetOutput() ) );
  EXPECT_NO_THROW( initialElastixFilter->SetParameterObject( parameterObject ) );
  EXPECT_NO_THROW( initialElastixFilter->GetTransformParameterObject()->WriteParameterFile( "initialTransformTestEuler2D.txt" ) );

  ElastixFilterType::Pointer elastixFilter;
  EXPECT_NO_THROW( elastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( elastixFilter->LogToConsoleOn() );
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
  EXPECT_NO_THROW( parameterObject->SetParameterMap( "rigid" ) );

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
  EXPECT_NO_THROW( forwardElastixFilter->LogToConsoleOn() );
  EXPECT_NO_THROW( forwardElastixFilter->SetFixedImage( fixedImageReader->GetOutput() ) );
  EXPECT_NO_THROW( forwardElastixFilter->SetMovingImage( movingImageReader->GetOutput() ) );
  EXPECT_NO_THROW( forwardElastixFilter->SetParameterObject( parameterObject ) );
  EXPECT_NO_THROW( forwardElastixFilter->GetTransformParameterObject()->WriteParameterFile( dataFinder.GetOutputFile( "inverseTransformTestEuler2D.txt" ) ) );

  // Inverse registration
  ParameterObject::Pointer inverseParameterObject;
  EXPECT_NO_THROW( inverseParameterObject = ParameterObject::New() );
  EXPECT_NO_THROW( inverseParameterObject->SetParameterMap( "rigid" ) );
  EXPECT_NO_THROW( inverseParameterObject->GetParameterMap( 0 )[ "Metric" ] = ElastixFilterType::ParameterValueVectorType( 1, "DisplacementMagnitudePenalty" ) );

  ElastixFilterType::Pointer inverseElastixFilter;
  EXPECT_NO_THROW( inverseElastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( inverseElastixFilter->LogToConsoleOn() );
  EXPECT_NO_THROW( inverseElastixFilter->SetFixedImage( fixedImageReader->GetOutput() ) );
  EXPECT_NO_THROW( inverseElastixFilter->SetMovingImage( fixedImageReader->GetOutput() ) );
  EXPECT_NO_THROW( inverseElastixFilter->SetParameterObject( inverseParameterObject ) );
  EXPECT_NO_THROW( inverseElastixFilter->SetInitialTransformParameterFileName( dataFinder.GetOutputFile( "inverseTransformTestEuler2D.txt" ) ) );
  EXPECT_NO_THROW( inverseElastixFilter->Update() );
  EXPECT_NO_THROW( inverseElastixFilter->GetTransformParameterObject()->GetParameterMap( 0 )[ "InitialTransformParametersFileName" ] = ElastixFilterType::ParameterValueVectorType( 1, "NoInitialTransform" ) );

  // TODO: Fix segmentation fault
  // Warp fixed image to moving image with the inverse transform
  // TransformixFilterType::Pointer transformixFilter;
  // transformixFilter->SetInputImage( inputImageReader->GetOutput() );
  // transformixFilter->SetTransformParameterObject( inverseElastixFilter->GetTransformParameterObject() );

  // ImageFileWriterType::Pointer writer = ImageFileWriterType::New();
  // EXPECT_NO_THROW( writer->SetFileName( dataFinder.GetOutputFile( "InverseTransformTestEuler2DResultImage.nii" ) ) );
  // EXPECT_NO_THROW( writer->SetInput( fixedImageReader->GetOutput() ) );
  // EXPECT_NO_THROW( writer->Update() );
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
  EXPECT_NO_THROW( elastixFilter->LogToConsoleOn() );
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
  EXPECT_NO_THROW( parameterObject->SetParameterMap( "nonrigid" ) );
  EXPECT_NO_THROW( parameterObject->GetParameterMap( 0 )[ "MaximumNumberOfIterations" ] = ElastixFilterType::ParameterValueVectorType( 1, "8" ) );

  ImageFileReaderType::Pointer fixedImageReader = ImageFileReaderType::New();
  fixedImageReader->SetFileName( dataFinder.GetFile( "Input/OAS1_0001_MR1_mpr-1_anon.nrrd" ) );

  ImageFileReaderType::Pointer movingImageReader = ImageFileReaderType::New();
  movingImageReader->SetFileName( dataFinder.GetFile( "Input/OAS1_0002_MR1_mpr-1_anon.nrrd" ) );

  ElastixFilterType::Pointer elastixFilter;
  EXPECT_NO_THROW( elastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( elastixFilter->LogToConsoleOn() );
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

  ParameterObject::Pointer parameterObject = ParameterObject::New();
  parameterObject->SetParameterMap( "groupwise" );
  parameterObject->GetParameterMap( 0 )[ "MaximumNumberOfIterations" ] = ElastixFilterType::ParameterValueVectorType( 1, "4" );

  ImageFileReaderType::Pointer imageReader1 = ImageFileReaderType::New();
  imageReader1->SetFileName( dataFinder.GetFile( "Input/4D.nii.gz" ) );

  ImageFileReaderType::Pointer imageReader2 = ImageFileReaderType::New();
  imageReader2->SetFileName( dataFinder.GetFile( "Input/4D.nii.gz" ) );

  ElastixFilterType::Pointer elastixFilter;
  EXPECT_NO_THROW( elastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( elastixFilter->LogToConsoleOn() );
  EXPECT_NO_THROW( elastixFilter->SetFixedImage( imageReader1->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetMovingImage( imageReader2->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetParameterObject( parameterObject ) );
  EXPECT_NO_THROW( elastixFilter->Update() );

  ImageFileWriterType::Pointer writer = ImageFileWriterType::New();
  EXPECT_NO_THROW( writer->SetFileName( dataFinder.GetOutputFile( "Input/BSpline4DResultImage.nii" ) ) );
  EXPECT_NO_THROW( writer->SetInput( elastixFilter->GetOutput() ) );
  EXPECT_NO_THROW( writer->Update() );

  ParameterObject::Pointer transformParameterObject;
  EXPECT_NO_THROW( transformParameterObject = elastixFilter->GetTransformParameterObject() );
}
