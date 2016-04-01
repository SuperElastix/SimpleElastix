#include "SimpleITKTestHarness.h"
#include "sitkCastImageFilter.h"
#include "sitkSimpleElastix.h"
#include "sitkSimpleTransformix.h"

namespace itk {
  namespace simple {

bool stfxIsEmpty( const Image image )
{
return ( image.GetWidth() == 0 && image.GetHeight() == 0 );
}


TEST( SimpleTransformix, ObjectOrientedInterface )
{
  Image fixedImage = Cast( ReadImage( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20.png" ) ), sitkFloat32 );
  Image movingImage = Cast( ReadImage( dataFinder.GetFile( "Input/BrainProtonDensitySliceShifted13x17y.png" ) ), sitkFloat32 );

  SimpleElastix silx;
  silx.SetFixedImage( fixedImage );
  silx.SetMovingImage( movingImage );
  silx.Execute();

  SimpleTransformix stfx;
  EXPECT_EQ( stfx.GetName(), "SimpleTransformix" );
  EXPECT_EQ( stfx.GetTransformParameterMap().size(), 0u );

  ASSERT_THROW( stfx.Execute(), GenericException );
  EXPECT_NO_THROW( stfx.SetInputImage( movingImage ) );
  ASSERT_THROW( stfx.Execute(), GenericException );

  EXPECT_NO_THROW( stfx.SetTransformParameterMap( silx.GetTransformParameterMap() ) );
  EXPECT_NO_THROW( stfx.Execute() );
  EXPECT_FALSE( stfxIsEmpty( stfx.GetResultImage() ) );

  EXPECT_NO_THROW( stfx.Execute() );
  EXPECT_FALSE( stfxIsEmpty( stfx.GetResultImage() ) );

  EXPECT_NO_THROW( stfx.Execute() );
  EXPECT_FALSE( stfxIsEmpty( stfx.GetResultImage() ) );
}


TEST( SimpleTransformix, ProceduralInterface )
{
  Image fixedImage = Cast( ReadImage( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20.png" ) ), sitkFloat32 );
  Image movingImage = Cast( ReadImage( dataFinder.GetFile( "Input/BrainProtonDensitySliceShifted13x17y.png" ) ), sitkFloat32 );
  Image resultImage;

  SimpleElastix silx;
  silx.SetFixedImage( fixedImage );
  silx.SetMovingImage( movingImage );
  silx.Execute();

  std::string outputDirectory = ".";

  EXPECT_NO_THROW( resultImage = Transformix( movingImage, silx.GetTransformParameterMap()[0] ) );
  EXPECT_FALSE( stfxIsEmpty( resultImage ) );
  EXPECT_NO_THROW( resultImage = Transformix( movingImage, silx.GetTransformParameterMap()[0], true ) );
  EXPECT_FALSE( stfxIsEmpty( resultImage ) );
  EXPECT_NO_THROW( resultImage = Transformix( movingImage, silx.GetTransformParameterMap()[0], true, outputDirectory ) );
  EXPECT_FALSE( stfxIsEmpty( resultImage ) );
  EXPECT_NO_THROW( resultImage = Transformix( movingImage, silx.GetTransformParameterMap()[0], false, outputDirectory ) );
  EXPECT_FALSE( stfxIsEmpty( resultImage ) );

  EXPECT_NO_THROW( resultImage = Transformix( movingImage, silx.GetTransformParameterMap() ) );
  EXPECT_FALSE( stfxIsEmpty( resultImage ) );
  EXPECT_NO_THROW( resultImage = Transformix( movingImage, silx.GetTransformParameterMap(), true ) );
  EXPECT_FALSE( stfxIsEmpty( resultImage ) );
  EXPECT_NO_THROW( resultImage = Transformix( movingImage, silx.GetTransformParameterMap(), true, outputDirectory ) );
  EXPECT_FALSE( stfxIsEmpty( resultImage ) );
  EXPECT_NO_THROW( resultImage = Transformix( movingImage, silx.GetTransformParameterMap(), false, outputDirectory ) );
  EXPECT_FALSE( stfxIsEmpty( resultImage ) );

  SimpleElastix::ParameterMapVectorType parameterMapVector = silx.GetTransformParameterMap();
  parameterMapVector[ parameterMapVector.size()-1 ][ "WriteResultImage" ] = SimpleElastix::ParameterValueVectorType( 1, "false" );
  EXPECT_NO_THROW( resultImage = Transformix( movingImage, silx.GetTransformParameterMap() ) );
  EXPECT_FALSE( stfxIsEmpty( resultImage ) );
}

#ifdef SITK_4D_IMAGES

TEST( SimpleTransformix, Transformation4D )
{
  Image fixedImage = ReadImage( dataFinder.GetFile( "Input/4D.nii.gz" ) );
  Image movingImage1 = ReadImage( dataFinder.GetFile( "Input/4D.nii.gz" ) );
  Image movingImage2 = ReadImage( dataFinder.GetFile( "Input/4D.nii.gz" ) );
  Image resultImage1;
  Image resultImage2;

  SimpleElastix silx; silx.LogToConsoleOn();
  silx.SetParameterMap( "groupwise" );
  silx.SetParameter("MaximumNumberOfIterations", "8.0");
  silx.SetParameter("FinalGridSpacingInPhysicalUnits", "32.0");
  silx.SetFixedImage( fixedImage );
  silx.SetMovingImage( movingImage1 );
  resultImage1 = silx.Execute();

  SimpleTransformix stfx; stfx.LogToConsoleOn();
  stfx.SetInputImage( movingImage2 );
  stfx.SetTransformParameterMap( silx.GetTransformParameterMap() );
  resultImage2 = stfx.Execute();
}

#endif // SITK_4D_IMAGES

} // namespace simple
} // namespace itk

