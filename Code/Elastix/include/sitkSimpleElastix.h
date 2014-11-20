#ifndef __sitkSimpleElastix_h
#define __sitkSimpleElastix_h

#include "sitkMacro.h"

#if defined( SITKDLL )
  #ifdef SELX_EXPORTS
    #define SELX_EXPORT SITK_ABI_EXPORT
  #else
    #define SELX_EXPORT SITK_ABI_IMPORT
  #endif  /* SimpleEalstix_EXPORTS */
#else
  // Don't hide symbols in the static SimpleITKRegistration library in case
  // -fvisibility=hidden is used
  #define SELX_EXPORT
#endif

#define SELX_HIDDEN SITK_ABI_HIDDEN

#endif // __sitkSimpleElastix_h