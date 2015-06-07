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

    typedef sitk::SimpleElastix SimpleElastixType;

    sitk::Image image4d;
};

TEST_F( SimpleElastix4DTest, GroupwiseRegistration )
{
    SimpleElastixType elastix;
    EXPECT_NO_THROW( elastix.SetFixedImage( image4d ) );
    EXPECT_NO_THROW( elastix.SetMovingImage( image4d ) );
    EXPECT_NO_THROW( elastix.SetParameterMap( sitk::GetDefaultParameterMap( "groupwise" ) ) );
    EXPECT_NO_THROW( elastix.LogToFolder( "." ) );
    EXPECT_NO_THROW( elastix.Execute() );
}