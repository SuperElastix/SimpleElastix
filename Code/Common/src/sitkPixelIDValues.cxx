/*=========================================================================
*
*  Copyright Insight Software Consortium
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*         http://www.apache.org/licenses/LICENSE-2.0.txt
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*=========================================================================*/
#include "sitkPixelIDValues.h"

namespace itk
{
namespace simple
{

const std::string GetPixelIDValueAsString( PixelIDValueEnum type )
{
  return GetPixelIDValueAsString( static_cast<PixelIDValueType>(type) );
}

const std::string GetPixelIDValueAsString( PixelIDValueType type )
{

  if ( type == sitkUnknown )
    {
    // Unknow must be first because other enums may be -1 if they are
    // not instantiated
    return "Unknown pixel id";
    }
  else if ( type == sitkUInt8 )
    {
    return "8-bit unsigned integer";
    }
  else if ( type == sitkInt8 )
    {
    return "8-bit signed integer";
    }
  else if ( type ==  sitkUInt16 )
    {
    return "16-bit unsigned integer";
    }
  else if ( type == sitkInt16 )
    {
    return "16-bit signed integer";
    }
  else if ( type == sitkUInt32 )
    {
    return "32-bit unsigned integer";
    }
  else if ( type == sitkInt32 )
    {
    return "32-bit signed integer";
    }
  else if ( type == sitkUInt64 )
    {
    return "64-bit unsigned integer";
    }
  else if ( type == sitkInt64 )
    {
    return "64-bit signed integer";
    }
  else if ( type == sitkFloat32 )
    {
    return "32-bit float";
    }
  else if ( type == sitkFloat64 )
    {
    return "64-bit float";
    }
  else if ( type == sitkComplexFloat32 )
    {
    return "complex of 32-bit float";
    }
  else if ( type == sitkComplexFloat64 )
    {
    return "complex of 64-bit float";
    }
  else if ( type == sitkVectorUInt8 )
    {
    return "vector of 8-bit unsigned integer";
    }
  else if ( type == sitkVectorInt8 )
    {
    return "vector of 8-bit signed integer";
    }
  else if ( type ==  sitkVectorUInt16 )
    {
    return "vector of 16-bit unsigned integer";
    }
  else if ( type == sitkVectorInt16 )
    {
    return "vector of 16-bit signed integer";
    }
  else if ( type == sitkVectorUInt32 )
    {
    return "vector of 32-bit unsigned integer";
    }
  else if ( type == sitkVectorInt32 )
    {
    return "vector of 32-bit signed integer";
    }
  else if ( type == sitkVectorUInt64 )
    {
    return "vector of 64-bit unsigned integer";
    }
  else if ( type == sitkVectorInt64 )
    {
    return "vector of 64-bit signed integer";
    }
  else if ( type == sitkVectorFloat32 )
    {
    return "vector of 32-bit float";
    }
  else if ( type == sitkVectorFloat64 )
    {
    return "vector of 64-bit float";
    }
  else if ( type == sitkLabelUInt8 )
    {
    return "label of 8-bit unsigned integer";
    }
  else if ( sitkLabelUInt16 )
    {
    return "label of 16-bit unsigned integer";
    }
  else if ( sitkLabelUInt32 )
    {
    return "label of 32-bit unsigned integer";
    }
  else if ( sitkLabelUInt64 )
    {
    return "label of 64-bit unsigned integer";
    }
  else
    {
    return "ERRONEOUS PIXEL ID!";
    }
}

const std::string GetPixelIDValueAsElastixParameter( PixelIDValueType type )
{

  if ( type == sitkUnknown )
    {
    // Unknow must be first because other enums may be -1 if they are
    // not instantiated
    return "Unknown pixel id";
    }
  else if ( type == sitkUInt8 )
    {
    return "unsigned char";
    }
  else if ( type == sitkInt8 )
    {
    return "char";
    }
  else if ( type ==  sitkUInt16 )
    {
    return "unsigned short";
    }
  else if ( type == sitkInt16 )
    {
    return "short";
    }
  else if ( type == sitkUInt32 )
    {
    return "unsigned int";
    }
  else if ( type == sitkInt32 )
    {
    return "int";
    }
  else if ( type == sitkUInt64 )
    {
    return "unsigned long";
    }
  else if ( type == sitkInt64 )
    {
    return "long";
    }
  else if ( type == sitkFloat32 )
    {
    return "float";
    }
  else if ( type == sitkFloat64 )
    {
    return "double";
    }
  else
    {
    return "Unsupported pixel type.";
    }
}

std::ostream& operator<<(std::ostream& os, const PixelIDValueEnum id)
{
  return (os << GetPixelIDValueAsString(id));
}


}
}
