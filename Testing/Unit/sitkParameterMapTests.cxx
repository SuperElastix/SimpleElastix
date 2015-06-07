#include "SimpleITKTestHarness.h"
#include "sitkCastImageFilter.h"
#include "sitkSimpleElastix.h"

namespace sitk = itk::simple;

TEST(ParameterMapTest,ParameterMap)
{
    sitk::SimpleElastix::ParameterMapType parameterMap;

    EXPECT_EQ( parameterMap.size(), 0u );
    EXPECT_NO_THROW( parameterMap["key"] = sitk::SimpleElastix::ParameterValuesType( 1, "value" ) );
    EXPECT_EQ( parameterMap["key"], sitk::SimpleElastix::ParameterValuesType( 1, "value" ) );
    EXPECT_EQ( parameterMap["key"].size(), 1u );
    EXPECT_EQ( parameterMap.size(), 1u );

    EXPECT_NO_THROW( parameterMap["key"] = sitk::SimpleElastix::ParameterValuesType( 2, "values" ) );
    EXPECT_EQ( parameterMap["key"], sitk::SimpleElastix::ParameterValuesType( 2, "values" ) );
    EXPECT_EQ( parameterMap["key"].size(), 2u );
    EXPECT_EQ( parameterMap.size(), 1u );
}

TEST(ParameteMapTest,ParameterMapList)
{
    sitk::SimpleElastix::ParameterMapType parameterMap;
    parameterMap["key1"] = sitk::SimpleElastix::ParameterValuesType( 1, "value1" );
    parameterMap["key2"] = sitk::SimpleElastix::ParameterValuesType( 2, "value2" );
    parameterMap["key3"] = sitk::SimpleElastix::ParameterValuesType( 3, "value3" );
    EXPECT_EQ( parameterMap.size(), 3u );

    sitk::SimpleElastix::ParameterMapListType parameterMapList0;
    EXPECT_EQ( parameterMapList0.size(), 0u );
    parameterMapList0.push_back( parameterMap );
    EXPECT_EQ( parameterMapList0.size(), 1u );
    EXPECT_EQ( parameterMapList0[0].size(), 3u );
    EXPECT_EQ( parameterMapList0[0]["key3"], sitk::SimpleElastix::ParameterValuesType( 3, "value3" ) );

    EXPECT_NO_THROW( parameterMapList0[0]["key3"] = sitk::SimpleElastix::ParameterValuesType( 4, "newValue3" ) );
    EXPECT_EQ( parameterMapList0[0]["key3"], sitk::SimpleElastix::ParameterValuesType( 4, "newValue3" ) );

    sitk::SimpleElastix::ParameterMapListType parameterMapList1 = sitk::SimpleElastix::ParameterMapListType( 2, parameterMap );
    EXPECT_EQ( parameterMapList1.size(), 2u );
}

TEST(ParameterMapTest,ProceduralInterface)
{
    sitk::SimpleElastix::ParameterMapType parameterMap;
    EXPECT_NO_THROW( parameterMap = sitk::GetDefaultParameterMap( "translation" ) );
    EXPECT_NO_THROW( sitk::WriteParameterFile( parameterMap, "ParameterMapTestProceduralInterface.txt" ) );

    sitk::SimpleElastix::ParameterMapType parameterMapRead;
    EXPECT_NO_THROW( parameterMapRead = sitk::ReadParameterFile( "ParameterMapTestProceduralInterface.txt" ) );
    EXPECT_EQ( parameterMap, parameterMapRead );

    EXPECT_NO_THROW( sitk::PrettyPrint( parameterMap ) );

    sitk::SimpleElastix::ParameterMapListType parameterMapList;
    parameterMapList.push_back( parameterMap );
    parameterMapList.push_back( parameterMap );
    EXPECT_NO_THROW( sitk::PrettyPrint( parameterMapList ) );
}
