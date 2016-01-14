#include "SimpleITKTestHarness.h"
#include "sitkCastImageFilter.h"
#include "sitkSimpleElastix.h"

namespace sitk = itk::simple;

class SimpleElastix4DTest : public ::testing::Test
{
protected:

    virtual void SetUp()
    {
        image4d = sitk::ReadImage( dataFinder.GetFile( "Input/4D.nii.gz" ) );
    }

    typedef sitk::SimpleElastix                      SimpleElastixType;
    typedef SimpleElastixType::ParameterMapType      ParameterMapType;
    typedef SimpleElastixType::ParameterValueVectorType   ParameterValueVectorType;

    sitk::Image image4d;

    bool IsEmpty( const sitk::Image image )
    {
      return ( image.GetWidth() == 0 && image.GetHeight() == 0 );
    }
};

TEST_F( SimpleElastix4DTest, GroupwiseRegistration )
{
    ParameterMapType parameterMap = sitk::GetDefaultParameterMap( "groupwise", 1, 32 );

    // otherwise unreasonable testing time
    parameterMap["MaximumNumberOfIterations"] = ParameterValueVectorType( 1, "16" ); 

    SimpleElastixType elastix;
    sitk::Image resultImage;

    EXPECT_NO_THROW( elastix.SetFixedImage( image4d ) );
    EXPECT_NO_THROW( elastix.SetMovingImage( image4d ) );
    EXPECT_NO_THROW( elastix.SetParameterMap( parameterMap ) );
    EXPECT_NO_THROW( elastix.SetOutputDirectory( "." ) );
    EXPECT_NO_THROW( elastix.LogToFileOn() );
    EXPECT_NO_THROW( elastix.Execute() );
    EXPECT_NO_THROW( resultImage = elastix.GetResultImage() );
    EXPECT_FALSE( this->IsEmpty( resultImage ) );
}