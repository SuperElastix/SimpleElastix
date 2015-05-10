#include <SimpleITK.h>

namespace sitk = itk::simple;

int main ( void ) {

  /**
   * Prints translation parameter map to console for Hello World documentation.
   */

  sitk::PrettyPrint( sitk::GetDefaultParameterMap( "translation" ) );

  return 0;
}
