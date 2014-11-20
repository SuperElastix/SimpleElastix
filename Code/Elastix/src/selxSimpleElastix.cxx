#ifndef __selxsimpleelastix_cxx_
#define __selxsimpleelastix_cxx_

#include "selxSimpleElastix.h"

namespace itk {
  namespace simple {

SimpleElastix::SimpleElastix( void )
{

}

SimpleElastix::~SimpleElastix( void )
{

}

const std::string SimpleElastix::GetName( void )
{ 
  const std::string name = std::string("SimpleElastix");
  return name;
}

/** Procedural interface */

const std::string HelloWorld( void )
{
  SimpleElastix elastix;
  return elastix.GetName();
}

} // end namespace simple
} // end namespace itk

#endif // __selxsimpleelastix_cxx_