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
    typedef SimpleElastixType::ParameterMapVectorType   ParameterMapVectorType;
    typedef SimpleElastixType::ParameterValueVectorType    ParameterValueVectorType;

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

    // Minimum viable parameter map
    ParameterMapType parameterMap;
    parameterMap[ "Interpolator"]         = ParameterValueVectorType( 1, "LinearInterpolator");
    parameterMap[ "Optimizer" ]           = ParameterValueVectorType( 1, "AdaptiveStochasticGradientDescent" );
    parameterMap[ "Resampler"]            = ParameterValueVectorType( 1, "DefaultResampler" );
    parameterMap[ "ResampleInterpolator"] = ParameterValueVectorType( 1, "FinalBSplineInterpolator" );
    parameterMap[ "ImageSampler" ]        = ParameterValueVectorType( 1, "RandomCoordinate" );
    parameterMap[ "Registration" ]        = ParameterValueVectorType( 1, "MultiResolutionRegistration" );
    parameterMap[ "Transform" ]           = ParameterValueVectorType( 1, "TranslationTransform" );
    parameterMap[ "Metric" ]              = ParameterValueVectorType( 1, "AdvancedMattesMutualInformation" );

    EXPECT_NO_THROW( elastix.LogToConsoleOn();  );
    EXPECT_NO_THROW( elastix.LogToFileOn();  );
    EXPECT_NO_THROW( elastix.SetParameterMap( parameterMap ) );
    EXPECT_NO_THROW( elastix.Execute() );
    EXPECT_FALSE( this->IsEmpty( elastix.GetResultImage() ) );

    EXPECT_NO_THROW( elastix.SetFixedMask( mask ) );
    EXPECT_NO_THROW( elastix.Execute() );
    EXPECT_FALSE( this->IsEmpty( elastix.GetResultImage() ) );

    EXPECT_NO_THROW( elastix.SetMovingMask( mask ) );
    EXPECT_NO_THROW( elastix.Execute() );
    EXPECT_FALSE( this->IsEmpty( elastix.GetResultImage() ) );

    EXPECT_NO_THROW( elastix.RemoveFixedMask() );
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
    EXPECT_NO_THROW( Elastix( fixedImage, movingImage, "translation", false ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );
    EXPECT_NO_THROW( Elastix( fixedImage, movingImage, "translation", true, true ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );
    EXPECT_NO_THROW( Elastix( fixedImage, movingImage, "translation", false, false ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );
    EXPECT_NO_THROW( Elastix( fixedImage, movingImage, "translation", true, false ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );
    EXPECT_NO_THROW( Elastix( fixedImage, movingImage, "translation", false, true ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );
    EXPECT_NO_THROW( Elastix( fixedImage, movingImage, "translation", true, true, outputFolder ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );
    EXPECT_NO_THROW( Elastix( fixedImage, movingImage, "translation", false, false, outputFolder ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );
    EXPECT_NO_THROW( Elastix( fixedImage, movingImage, "translation", true, false, outputFolder ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );
    EXPECT_NO_THROW( Elastix( fixedImage, movingImage, "translation", false, true, outputFolder ) );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );

// TODO: Add all combinations with new logToFile parameter
//    ParameterMapType parameterMap = sitk::GetDefaultParameterMap( "translation" );
//    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMap) );
//    EXPECT_FALSE( this->IsEmpty( resultImage ) );
//    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMap, true ) );
//    EXPECT_FALSE( this->IsEmpty( resultImage ) );
//    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMap, true, outputFolder ) );
//    EXPECT_FALSE( this->IsEmpty( resultImage ) );
//    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMap, false, outputFolder ) );
//    EXPECT_FALSE( this->IsEmpty( resultImage ) );
//
//    ParameterMapVectorType parameterMapVector;
//    parameterMapVector.push_back( sitk::GetDefaultParameterMap( "translation" ) );
//    parameterMapVector.push_back( sitk::GetDefaultParameterMap( "rigid" ) );
//
//    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMapVector) );
//    EXPECT_FALSE( this->IsEmpty( resultImage ) );
//    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMapVector, true ) );
//    EXPECT_FALSE( this->IsEmpty( resultImage ) );
//    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMapVector, true, outputFolder ) );
//    EXPECT_FALSE( this->IsEmpty( resultImage ) );
//    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMapVector, false, outputFolder ) );
//    EXPECT_FALSE( this->IsEmpty( resultImage ) );
//
//    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, "translation", mask, mask ) );
//    EXPECT_FALSE( this->IsEmpty( resultImage ) );
//    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, "translation", mask, mask, true ) );
//    EXPECT_FALSE( this->IsEmpty( resultImage ) );
//    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, "translation", true, outputFolder ) );
//    EXPECT_FALSE( this->IsEmpty( resultImage ) );
//    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, "translation", false, outputFolder ) );
//    EXPECT_FALSE( this->IsEmpty( resultImage ) );
//
//    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMap, mask, mask ) );
//    EXPECT_FALSE( this->IsEmpty( resultImage ) );
//    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMap, mask, mask, true ) );
//    EXPECT_FALSE( this->IsEmpty( resultImage ) );
//    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMap, mask, mask, true, outputFolder ) );
//    EXPECT_FALSE( this->IsEmpty( resultImage ) );
//    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMap, mask, mask, false, outputFolder ) );
//    EXPECT_FALSE( this->IsEmpty( resultImage ) );
//
//    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMapVector, mask, mask ) );
//    EXPECT_FALSE( this->IsEmpty( resultImage ) );
//    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMapVector, mask, mask, true ) );
//    EXPECT_FALSE( this->IsEmpty( resultImage ) );
//    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMapVector, mask, mask, true, outputFolder ) );
//    EXPECT_FALSE( this->IsEmpty( resultImage ) );
//    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMapVector, mask, mask, false, outputFolder ) );
//    EXPECT_FALSE( this->IsEmpty( resultImage ) );
//
//    parameterMap["WriteResultImage"] = ParameterValueVectorType( 1, "false" );
//    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMap ) );
//    EXPECT_FALSE( this->IsEmpty( resultImage ) );
//
//    parameterMapVector[1]["WriteResultImage"] = ParameterValueVectorType( 1, "false" );
//    EXPECT_NO_THROW( resultImage = Elastix( fixedImage, movingImage, parameterMapVector ) );
//    EXPECT_FALSE( this->IsEmpty( resultImage ) );
//
//    EXPECT_NO_THROW( sitk::PrettyPrint( parameterMapVector ) );
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

    EXPECT_NO_THROW( elastix.SetParameterMap( sitk::GetDefaultParameterMap( "rigid" ) ) );
    EXPECT_NO_THROW( elastix.Execute() );
    EXPECT_NO_THROW( resultImage = elastix.GetResultImage() );

    EXPECT_NO_THROW( elastix.SetParameterMap( sitk::GetDefaultParameterMap( "affine" ) ) );
    EXPECT_NO_THROW( elastix.Execute() );
    EXPECT_NO_THROW( resultImage = elastix.GetResultImage() );

    EXPECT_NO_THROW( elastix.SetParameterMap( sitk::GetDefaultParameterMap( "nonrigid" ) ) );
    EXPECT_NO_THROW( elastix.Execute() );
    EXPECT_NO_THROW( resultImage = elastix.GetResultImage() );

    EXPECT_NO_THROW( elastix.PrettyPrint( elastix.GetTransformParameterMap() ) );
}
