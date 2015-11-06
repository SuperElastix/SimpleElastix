#include "SimpleITKTestHarness.h"
#include "sitkCastImageFilter.h"
#include "sitkSimpleElastix.h"

namespace sitk = itk::simple;

class SimpleElastixTest : public ::testing::Test
{
protected:

    virtual void SetUp()
    {
        fixedImage = sitk::Cast( sitk::ReadImage( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20.png" ) ), sitk::sitkFloat32 );
        movingImage = sitk::Cast( sitk::ReadImage( dataFinder.GetFile( "Input/BrainProtonDensitySliceShifted13x17y.png" ) ), sitk::sitkFloat32 );
        mask = sitk::Cast( sitk::ReadImage( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20Mask.png" ) ), sitk::sitkFloat32 );
        outputFolder = std::string( "." );
    }

    typedef sitk::SimpleElastix                       SimpleElastixType;
    typedef SimpleElastixType::ParameterMapType       ParameterMapType;
    typedef SimpleElastixType::ParameterMapListType   ParameterMapListType;
    typedef SimpleElastixType::ParameterValuesType    ParameterValuesType;

    sitk::Image fixedImage;
    sitk::Image movingImage;
    sitk::Image mask;
    std::string outputFolder;

    bool IsEmpty( const sitk::Image image )
    {
      return ( image.GetWidth() == 0 && image.GetHeight() == 0 );
    }
};

TEST_F( SimpleElastixTest, ObjectOrientedInterface )
{
    SimpleElastixType elastix;

    EXPECT_EQ( elastix.GetName(), "SimpleElastix" );
    EXPECT_EQ( elastix.GetParameterMap().size(), 0u );
    EXPECT_EQ( elastix.GetTransformParameterMap().size(), 0u );

    EXPECT_THROW( elastix.Execute(), sitk::GenericException );
    EXPECT_NO_THROW( elastix.SetFixedImage( fixedImage ) );
    EXPECT_THROW( elastix.Execute(), sitk::GenericException );
    EXPECT_NO_THROW( elastix.SetMovingImage( movingImage ) );
    EXPECT_THROW( elastix.Execute(), sitk::GenericException );

    // Minimum viable parameter map
    ParameterMapType parameterMap;
    parameterMap[ "Interpolator"]         = ParameterValuesType( 1, "LinearInterpolator");
    parameterMap[ "Optimizer" ]           = ParameterValuesType( 1, "AdaptiveStochasticGradientDescent" );
    parameterMap[ "Resampler"]            = ParameterValuesType( 1, "DefaultResampler" );
    parameterMap[ "ResampleInterpolator"] = ParameterValuesType( 1, "FinalBSplineInterpolator" );
    parameterMap[ "ImageSampler" ]        = ParameterValuesType( 1, "RandomCoordinate" );
    parameterMap[ "Registration" ]        = ParameterValuesType( 1, "MultiResolutionRegistration" );
    parameterMap[ "Transform" ]           = ParameterValuesType( 1, "TranslationTransform" );
    parameterMap[ "Metric" ]              = ParameterValuesType( 1, "AdvancedMattesMutualInformation" );

    EXPECT_NO_THROW( elastix.LogToConsoleOn();  );
    EXPECT_NO_THROW( elastix.LogToFolder(".");  );
    EXPECT_NO_THROW( elastix.SetParameterMap( parameterMap ) );
    EXPECT_NO_THROW( elastix.Execute() );
    EXPECT_FALSE( this->IsEmpty( elastix.GetResultImage() ) );

    EXPECT_NO_THROW( elastix.SetFixedMask( mask ) );
    EXPECT_NO_THROW( elastix.Execute() );
    EXPECT_FALSE( this->IsEmpty( elastix.GetResultImage() ) );

    EXPECT_NO_THROW( elastix.SetMovingMask( mask ) );
    EXPECT_NO_THROW( elastix.Execute() );
    EXPECT_FALSE( this->IsEmpty( elastix.GetResultImage() ) );

    EXPECT_NO_THROW( elastix.SetFixedMask( sitk::Image() ) ); // set mask to zero
    EXPECT_NO_THROW( elastix.Execute() );
    EXPECT_FALSE( this->IsEmpty( elastix.GetResultImage() ) );
}

TEST_F( SimpleElastixTest, ProceduralInterface )
{
    sitk::Image resultImage;

    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, "translation") );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );
    EXPECT_NO_THROW( Elastix( fixedImage, movingImage, "translation", true ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );
    EXPECT_NO_THROW( Elastix( fixedImage, movingImage, "translation", true, outputFolder ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );
    EXPECT_NO_THROW( Elastix( fixedImage, movingImage, "translation", false, outputFolder ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );

    ParameterMapType parameterMap = sitk::GetDefaultParameterMap( "translation" );
    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMap) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );
    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMap, true ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );
    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMap, true, outputFolder ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );
    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMap, false, outputFolder ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );

    ParameterMapListType parameterMapList;
    parameterMapList.push_back( sitk::GetDefaultParameterMap( "translation" ) );
    parameterMapList.push_back( sitk::GetDefaultParameterMap( "rigid" ) );

    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMapList) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );
    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMapList, true ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );
    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMapList, true, outputFolder ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );
    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMapList, false, outputFolder ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );

    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, "translation", mask, mask ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );
    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, "translation", mask, mask, true ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );
    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, "translation", true, outputFolder ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );
    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, "translation", false, outputFolder ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );

    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMap, mask, mask ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );
    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMap, mask, mask, true ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );
    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMap, mask, mask, true, outputFolder ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );
    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMap, mask, mask, false, outputFolder ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );

    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMapList, mask, mask ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );
    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMapList, mask, mask, true ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );
    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMapList, mask, mask, true, outputFolder ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );
    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMapList, mask, mask, false, outputFolder ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );

    parameterMap["WriteResultImage"] = ParameterValuesType( 1, "false" );
    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMap ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );

    parameterMapList[1]["WriteResultImage"] = ParameterValuesType( 1, "false" );
    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMapList ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );

    EXPECT_NO_THROW( sitk::PrettyPrint( parameterMapList ) );
}

TEST_F( SimpleElastixTest, DefaultPairwiseParameterMaps )
{
    sitk::Image resultImage;

    SimpleElastixType elastix;
    elastix.SetFixedImage( fixedImage );
    elastix.SetMovingImage( movingImage );

    EXPECT_NO_THROW( elastix.SetParameterMap( sitk::GetDefaultParameterMap( "translation" ) ) );
    EXPECT_NO_THROW( elastix.Execute() );
    EXPECT_NO_THROW( resultImage = elastix.GetResultImage() );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );

    EXPECT_NO_THROW( elastix.SetParameterMap( sitk::GetDefaultParameterMap( "rigid" ) ) );
    EXPECT_NO_THROW( elastix.Execute() );
    EXPECT_NO_THROW( resultImage = elastix.GetResultImage() );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );

    EXPECT_NO_THROW( elastix.SetParameterMap( sitk::GetDefaultParameterMap( "affine" ) ) );
    EXPECT_NO_THROW( elastix.Execute() );
    EXPECT_NO_THROW( resultImage = elastix.GetResultImage() );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );

    EXPECT_NO_THROW( elastix.SetParameterMap( sitk::GetDefaultParameterMap( "nonrigid" ) ) );
    EXPECT_NO_THROW( elastix.Execute() );
    EXPECT_NO_THROW( resultImage = elastix.GetResultImage() );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );

    EXPECT_NO_THROW( elastix.PrettyPrint( elastix.GetTransformParameterMap() ) );
}
