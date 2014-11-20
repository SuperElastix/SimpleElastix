#ifndef __selxsimpleelastix_h_
#define __selxsimpleelastix_h_

#include "sitkSimpleElastix.h"
#include "elastixlib.h"

namespace itk {
 namespace simple {

class SELX_EXPORT SimpleElastix
{
  public:

    // Instantiate an Elastix API object 
    SimpleElastix( void );

    // Delete Elastix API object
    ~SimpleElastix( void );

    const std::string GetName( void );

  protected:

  private:

};

SELX_EXPORT const std::string HelloWorld( void );

/** Procedural Interface 

// Invoke registration with no masks
SELX_EXPORT Image elastix( Image fixedImage, Image movingImage, str::string parameterFileName, bool outputToConsole = false, std::string out = "" );
SELX_EXPORT Image elastix( Image fixedImage, Image movingImage, ParameterMapType parameterMap, bool outputToConsole = false, std::string out = "" );

// Invoke registration with masks
SELX_EXPORT Image elastix( Image fixedImage, Image movingImage, str::string parameterFileName, Image fixedMask, Image movingMask, bool outputToConsole = false, std::string out = "" );
SELX_EXPORT Image elastix( Image fixedImage, Image movingImage, ParameterMapType parameterMap, Image fixedMask, Image movingMask, bool outputToConsole = false, std::string out = "" );

*/

} // end namespace simple
} // end namespace itk

#endif // __selxsimpleelastix_h_