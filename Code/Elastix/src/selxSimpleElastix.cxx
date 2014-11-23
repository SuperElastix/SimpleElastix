#ifndef __selxsimpleelastix_cxx_
#define __selxsimpleelastix_cxx_

#include "SimpleITK.h"

namespace itk {
  namespace simple {

SimpleElastix
::SimpleElastix( void )
{
  this->m_Elastix = new ElastixLibType();
}

SimpleElastix
::~SimpleElastix( void )
{
  delete this->m_Elastix;
}

const std::string 
SimpleElastix
::GetName( void )
{ 
  const std::string name = std::string("SimpleElastix");
  return name;
}

void 
SimpleElastix
::SetFixedImage( Image fixedImage )
{
  this->m_FixedImage = fixedImage;
}

void 
SimpleElastix
::SetMovingImage( Image movingImage )
{
  this->m_MovingImage = movingImage;
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