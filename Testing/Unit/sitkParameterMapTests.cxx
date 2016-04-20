#include "SimpleITKTestHarness.h"
#include "sitkCastImageFilter.h"
#include "sitkHashImageFilter.h"
#include "sitkSimpleElastix.h"

namespace sitk = itk::simple;

TEST(ParameterMapTest,ParameterMap)
{
    sitk::SimpleElastix::ParameterMapType parameterMap;

    EXPECT_EQ( parameterMap.size(), 0u );
    EXPECT_NO_THROW( parameterMap["key"] = sitk::SimpleElastix::ParameterValueVectorType( 1, "value" ) );
    EXPECT_EQ( parameterMap["key"], sitk::SimpleElastix::ParameterValueVectorType( 1, "value" ) );
    EXPECT_EQ( parameterMap["key"].size(), 1u );
    EXPECT_EQ( parameterMap.size(), 1u );

    EXPECT_NO_THROW( parameterMap["key"] = sitk::SimpleElastix::ParameterValueVectorType( 2, "values" ) );
    EXPECT_EQ( parameterMap["key"], sitk::SimpleElastix::ParameterValueVectorType( 2, "values" ) );
    EXPECT_EQ( parameterMap["key"].size(), 2u );
    EXPECT_EQ( parameterMap.size(), 1u );
}

TEST(ParameteMapTest,ParameterMapVector)
{
    sitk::SimpleElastix::ParameterMapType parameterMap;
    parameterMap["key1"] = sitk::SimpleElastix::ParameterValueVectorType( 1, "value1" );
    parameterMap["key2"] = sitk::SimpleElastix::ParameterValueVectorType( 2, "value2" );
    parameterMap["key3"] = sitk::SimpleElastix::ParameterValueVectorType( 3, "value3" );
    EXPECT_EQ( parameterMap.size(), 3u );

    sitk::SimpleElastix::ParameterMapVectorType parameterMapVector0;
    EXPECT_EQ( parameterMapVector0.size(), 0u );
    parameterMapVector0.push_back( parameterMap );
    EXPECT_EQ( parameterMapVector0.size(), 1u );
    EXPECT_EQ( parameterMapVector0[0].size(), 3u );
    EXPECT_EQ( parameterMapVector0[0]["key3"], sitk::SimpleElastix::ParameterValueVectorType( 3, "value3" ) );

    EXPECT_NO_THROW( parameterMapVector0[0]["key3"] = sitk::SimpleElastix::ParameterValueVectorType( 4, "newValue3" ) );
    EXPECT_EQ( parameterMapVector0[0]["key3"], sitk::SimpleElastix::ParameterValueVectorType( 4, "newValue3" ) );

    sitk::SimpleElastix::ParameterMapVectorType parameterMapVector1 = sitk::SimpleElastix::ParameterMapVectorType( 2, parameterMap );
    EXPECT_EQ( parameterMapVector1.size(), 2u );
}

TEST( ParameterMapTest, ProceduralInterface )
{
    sitk::SimpleElastix::ParameterMapType parameterMap;
    EXPECT_NO_THROW( parameterMap = sitk::GetDefaultParameterMap( "translation" ) );
    EXPECT_NO_THROW( sitk::PrettyPrint( parameterMap ) );

    sitk::SimpleElastix::ParameterMapVectorType parameterMapVector;
    parameterMapVector.push_back( parameterMap );
    parameterMapVector.push_back( parameterMap );
    EXPECT_NO_THROW( sitk::PrettyPrint( parameterMapVector ) );
}

TEST( ParameterMapTest, ReadWrite )
{
    sitk::SimpleElastix::ParameterMapType parameterMap;
    EXPECT_NO_THROW( parameterMap = sitk::GetDefaultParameterMap( "translation" ) );

    sitk::Image fixedImage = sitk::ReadImage( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20.png" ) );
    sitk::Image movingImage = sitk::ReadImage( dataFinder.GetFile( "Input/BrainProtonDensitySliceShifted13x17y.png" ) );

    sitk::Image resultImage0;
    EXPECT_NO_THROW( resultImage0 = Elastix( fixedImage, movingImage, parameterMap ) );

    sitk::Image resultImage1;
    EXPECT_NO_THROW( sitk::WriteParameterFile( parameterMap, dataFinder.GetOutputFile( "ParameterMapTestReadWrite.txt" ) ) );
    sitk::SimpleElastix::ParameterMapType parameterMapRead;
    EXPECT_NO_THROW( parameterMapRead = sitk::ReadParameterFile( dataFinder.GetOutputFile( "ParameterMapTestReadWrite.txt" ) ) );
    EXPECT_NO_THROW( resultImage1 = Elastix( fixedImage, movingImage, parameterMapRead ) );
}
