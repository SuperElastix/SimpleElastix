#include "elxElastixFilter.h"
#include "elxTransformixFilter.h"
#include "elxParameterObject.h"

#include "itkCastImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "SimpleITKTestHarness.h"
#include "gtest/gtest.h"

using namespace elastix;

TEST( TransformixFilterTest, Instantiation )
{
  typedef itk::Image< float, 2 > ImageType;
  typedef TransformixFilter< ImageType > TransformixFilterType;
  EXPECT_NO_THROW( TransformixFilterType::Pointer transformixFilter = TransformixFilterType::New() );
}

TEST( TransformixFilterTest, UpdateOnDownstreamUpdate )
{
  typedef itk::Image< float, 2 > ImageType;
  typedef itk::ImageFileReader< ImageType > ImageFileReaderType;
  typedef itk::ImageFileWriter< ImageType > ImageFileWriterType;
  typedef ElastixFilter< ImageType, ImageType > ElastixFilterType;
  typedef TransformixFilter< ImageType > TransformixFilterType;

  ImageFileReaderType::Pointer fixedImageReader = ImageFileReaderType::New();
  fixedImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20.png" ) );

  ImageFileReaderType::Pointer movingImageReader = ImageFileReaderType::New();
  movingImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceR10X13Y17.png" ) );

  ElastixFilterType::Pointer elastixFilter;
  EXPECT_NO_THROW( elastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( elastixFilter->SetFixedImage( fixedImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetMovingImage( movingImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->Update() );
  
  TransformixFilterType::Pointer transformixFilter;
  EXPECT_NO_THROW( transformixFilter = TransformixFilterType::New() );
  EXPECT_NO_THROW( transformixFilter->SetMovingImage( movingImageReader->GetOutput() ) );
  EXPECT_NO_THROW( transformixFilter->SetOutputDirectory( dataFinder.GetOutputDirectory() ) );
  EXPECT_NO_THROW( transformixFilter->SetTransformParameterObject( elastixFilter->GetTransformParameterObject() ) );

  ImageFileWriterType::Pointer writer = ImageFileWriterType::New();
  EXPECT_NO_THROW( writer->SetFileName( dataFinder.GetOutputFile( "Euler2DTransformixResultImage.nii" ) ) );
  EXPECT_NO_THROW( writer->SetInput( transformixFilter->GetOutput() ) );
  EXPECT_NO_THROW( writer->Update() );
}

TEST( TransformixFilterTest, GetInputImageFromElastixFilter )
{
  typedef itk::Image< float, 2 > ImageType;
  typedef itk::ImageFileReader< ImageType > ImageFileReaderType;
  typedef itk::ImageFileWriter< ImageType > ImageFileWriterType;
  typedef ElastixFilter< ImageType, ImageType > ElastixFilterType;
  typedef TransformixFilter< ImageType > TransformixFilterType;

  ImageFileReaderType::Pointer fixedImageReader = ImageFileReaderType::New();
  fixedImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20.png" ) );

  ImageFileReaderType::Pointer movingImageReader = ImageFileReaderType::New();
  movingImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceR10X13Y17.png" ) );

  ElastixFilterType::Pointer elastixFilter;
  EXPECT_NO_THROW( elastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( elastixFilter->SetFixedImage( fixedImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetMovingImage( movingImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->Update() );

  TransformixFilterType::Pointer transformixFilter;
  EXPECT_NO_THROW( transformixFilter = TransformixFilterType::New() );
  EXPECT_NO_THROW( transformixFilter->SetMovingImage( elastixFilter->GetOutput() ) );
  EXPECT_NO_THROW( transformixFilter->SetTransformParameterObject( elastixFilter->GetTransformParameterObject() ) );
  EXPECT_NO_THROW( transformixFilter->SetOutputDirectory( dataFinder.GetOutputDirectory() ) );

  ImageFileWriterType::Pointer writer = ImageFileWriterType::New();
  EXPECT_NO_THROW( writer->SetFileName( dataFinder.GetOutputFile( "Euler2DTransformixResultImage.nii" ) ) );
  EXPECT_NO_THROW( writer->SetInput( transformixFilter->GetOutput() ) );
  EXPECT_NO_THROW( writer->Update() );
}

TEST( TransformixFilterTest, ComputeSpatialJacobian )
{
  typedef itk::Image< float, 2 > ImageType;
  typedef itk::ImageFileReader< ImageType > ImageFileReaderType;
  typedef ElastixFilter< ImageType, ImageType > ElastixFilterType;
  typedef TransformixFilter< ImageType > TransformixFilterType;

  ImageFileReaderType::Pointer fixedImageReader = ImageFileReaderType::New();
  fixedImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20.png" ) );

  ImageFileReaderType::Pointer movingImageReader = ImageFileReaderType::New();
  movingImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceR10X13Y17.png" ) );


  ElastixFilterType::Pointer elastixFilter;
  EXPECT_NO_THROW( elastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( elastixFilter->SetFixedImage( fixedImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetMovingImage( movingImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->Update() );

  TransformixFilterType::Pointer transformixFilter;
  EXPECT_NO_THROW( transformixFilter = TransformixFilterType::New() );
  EXPECT_NO_THROW( transformixFilter->SetOutputDirectory( dataFinder.GetOutputDirectory() ) );
  EXPECT_NO_THROW( transformixFilter->SetTransformParameterObject( elastixFilter->GetTransformParameterObject() ) );
  EXPECT_NO_THROW( transformixFilter->ComputeSpatialJacobianOn() );
  EXPECT_NO_THROW( transformixFilter->Update() );
}

TEST( TransformixFilterTest, ComputeDeterminantOfSpatialJacobian )
{
  typedef itk::Image< float, 2 > ImageType;
  typedef itk::ImageFileReader< ImageType > ImageFileReaderType;
  typedef ElastixFilter< ImageType, ImageType > ElastixFilterType;
  typedef TransformixFilter< ImageType > TransformixFilterType;

  ImageFileReaderType::Pointer fixedImageReader = ImageFileReaderType::New();
  fixedImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20.png" ) );

  ImageFileReaderType::Pointer movingImageReader = ImageFileReaderType::New();
  movingImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceR10X13Y17.png" ) );

  ElastixFilterType::Pointer elastixFilter;
  EXPECT_NO_THROW( elastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( elastixFilter->SetFixedImage( fixedImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetMovingImage( movingImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->Update() );

  TransformixFilterType::Pointer transformixFilter;
  EXPECT_NO_THROW( transformixFilter = TransformixFilterType::New() );
  EXPECT_NO_THROW( transformixFilter->SetOutputDirectory( dataFinder.GetOutputDirectory() ) );
  EXPECT_NO_THROW( transformixFilter->SetTransformParameterObject( elastixFilter->GetTransformParameterObject() ) );
  EXPECT_NO_THROW( transformixFilter->ComputeDeterminantOfSpatialJacobianOn() );
  EXPECT_NO_THROW( transformixFilter->Update() );
}

TEST( TransformixFilterTest, ComputeDeformationField )
{
  typedef itk::Image< float, 2 > ImageType;
  typedef itk::ImageFileReader< ImageType > ImageFileReaderType;
  typedef ElastixFilter< ImageType, ImageType > ElastixFilterType;
  typedef TransformixFilter< ImageType > TransformixFilterType;
  typedef itk::ImageFileWriter< typename TransformixFilterType::OutputDeformationFieldType > ImageFileWriterType;

  ImageFileReaderType::Pointer fixedImageReader = ImageFileReaderType::New();
  fixedImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20.png" ) );

  ImageFileReaderType::Pointer movingImageReader = ImageFileReaderType::New();
  movingImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceR10X13Y17.png" ) );

  ParameterObject::Pointer parameterObject = ParameterObject::New();
  parameterObject->SetParameterMap( parameterObject->GetDefaultParameterMap( "affine" ) );

  ElastixFilterType::Pointer elastixFilter;
  EXPECT_NO_THROW( elastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( elastixFilter->SetFixedImage( fixedImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetMovingImage( movingImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetParameterObject( parameterObject ) );
  EXPECT_NO_THROW( elastixFilter->Update() );

  TransformixFilterType::Pointer transformixFilter;
  EXPECT_NO_THROW( transformixFilter = TransformixFilterType::New() );
  EXPECT_NO_THROW( transformixFilter->SetOutputDirectory( dataFinder.GetOutputDirectory() ) );
  EXPECT_NO_THROW( transformixFilter->SetTransformParameterObject( elastixFilter->GetTransformParameterObject() ) );
  EXPECT_NO_THROW( transformixFilter->ComputeDeformationFieldOn() );
  EXPECT_NO_THROW( transformixFilter->Update() );

  ImageFileWriterType::Pointer writer = ImageFileWriterType::New();
  EXPECT_NO_THROW( writer->SetFileName( dataFinder.GetOutputFile( "TransformixFilterTest.ComputeDeformationField.nii" ) ) );
  EXPECT_NO_THROW( writer->SetInput( transformixFilter->GetOutputDeformationField() ) );
  EXPECT_NO_THROW( writer->Update() );
}

TEST( TransformixFilterTest, TransformPointSet )
{
  typedef itk::Image< float, 2 > ImageType;
  typedef itk::ImageFileReader< ImageType > ImageFileReaderType;
  typedef ElastixFilter< ImageType, ImageType > ElastixFilterType;
  typedef TransformixFilter< ImageType > TransformixFilterType;

  ImageFileReaderType::Pointer fixedImageReader = ImageFileReaderType::New();
  fixedImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20.png" ) );

  ImageFileReaderType::Pointer movingImageReader = ImageFileReaderType::New();
  movingImageReader->SetFileName( dataFinder.GetFile( "Input/BrainProtonDensitySliceR10X13Y17.png" ) );
  
  const std::string fixedPointSetFileName = dataFinder.GetOutputFile( "InputPoints.pts" );
  std::ofstream fixedMeshFile;
  fixedMeshFile.open( fixedPointSetFileName.c_str() );
  fixedMeshFile << "point\n";
  fixedMeshFile << "1\n";
  fixedMeshFile << "128.0 128.0\n";
  fixedMeshFile.close();

  ElastixFilterType::Pointer elastixFilter;
  EXPECT_NO_THROW( elastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( elastixFilter->SetFixedImage( fixedImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetMovingImage( movingImageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->Update() );

  TransformixFilterType::Pointer transformixFilter;
  EXPECT_NO_THROW( transformixFilter = TransformixFilterType::New() );
  EXPECT_NO_THROW( transformixFilter->SetOutputDirectory( dataFinder.GetOutputDirectory() ) );
  EXPECT_NO_THROW( transformixFilter->SetTransformParameterObject( elastixFilter->GetTransformParameterObject() ) );
  EXPECT_NO_THROW( transformixFilter->SetFixedPointSetFileName( dataFinder.GetOutputFile( "InputPoints.pts" ) ) );
  EXPECT_NO_THROW( transformixFilter->Update() );
}

TEST( TransformixFilterTest, SameTransformParameterMapForMultipleTransformations )
{
  typedef itk::Image< float, 2 > ImageType;
  typedef itk::ImageFileReader< ImageType > ImageFileReaderType;
  typedef ElastixFilter< ImageType, ImageType > ElastixFilterType;
  typedef TransformixFilter< ImageType > TransformixFilterType;

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

  TransformixFilterType::Pointer transformixFilter;
  EXPECT_NO_THROW( transformixFilter = TransformixFilterType::New() );
  EXPECT_NO_THROW( transformixFilter->SetOutputDirectory( dataFinder.GetOutputDirectory() ) );
  EXPECT_NO_THROW( transformixFilter->SetTransformParameterObject( elastixFilter->GetTransformParameterObject() ) );
  EXPECT_NO_THROW( transformixFilter->SetMovingImage( movingImageReader1->GetOutput() ) );
  EXPECT_NO_THROW( transformixFilter->Update() );
  EXPECT_NO_THROW( transformixFilter->SetMovingImage( movingImageReader2->GetOutput() ) );
  EXPECT_NO_THROW( transformixFilter->Update() );
}

TEST( TransformixFilterTest, BSpline4D )
{
  typedef itk::Image< float, 4 > ImageType;
  typedef itk::ImageFileReader< ImageType > ImageFileReaderType;
  typedef itk::ImageFileWriter< ImageType > ImageFileWriterType;
  typedef ElastixFilter< ImageType, ImageType > ElastixFilterType;
  typedef TransformixFilter< ImageType > TransformixFilterType;

  ParameterObject::Pointer parameterObject = ParameterObject::New();
  ElastixFilterType::ParameterMapType parameterMap = ParameterObject::GetDefaultParameterMap( "groupwise" );
  parameterMap["MaximumNumberOfIterations"] = ElastixFilterType::ParameterValueVectorType( 1, "1" );
  parameterObject->SetParameterMap( parameterMap );

  ImageFileReaderType::Pointer imageReader = ImageFileReaderType::New();
  imageReader->SetFileName( dataFinder.GetFile( "Input/4D.nii.gz" ) );

  ElastixFilterType::Pointer elastixFilter;
  EXPECT_NO_THROW( elastixFilter = ElastixFilterType::New() );
  EXPECT_NO_THROW( elastixFilter->SetFixedImage( imageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetMovingImage( imageReader->GetOutput() ) );
  EXPECT_NO_THROW( elastixFilter->SetParameterObject( parameterObject ) );
  EXPECT_NO_THROW( elastixFilter->Update() );

  TransformixFilterType::Pointer transformixFilter;
  EXPECT_NO_THROW( transformixFilter = TransformixFilterType::New() );
  EXPECT_NO_THROW( transformixFilter->SetMovingImage( imageReader->GetOutput() ) );
  EXPECT_NO_THROW( transformixFilter->SetTransformParameterObject( elastixFilter->GetTransformParameterObject() ) );

  ImageFileWriterType::Pointer writer = ImageFileWriterType::New();
  EXPECT_NO_THROW( writer->SetFileName( dataFinder.GetOutputFile( "BSpline4DResultImage.nii" ) ) );
  EXPECT_NO_THROW( writer->SetInput( transformixFilter->GetOutput() ) );
  EXPECT_NO_THROW( writer->Update() );
}
