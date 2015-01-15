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
#ifndef __sitkDisplacementFieldTransform_h
#define __sitkDisplacementFieldTransform_h

#include "sitkCommon.h"
#include "sitkTransform.h"
#include "sitkInterpolator.h"

namespace itk
{
namespace simple
{

class SITKCommon_EXPORT DisplacementFieldTransform
  : public Transform
{
public:
  typedef DisplacementFieldTransform Self;
  typedef Transform Superclass;
  DisplacementFieldTransform(unsigned int dimensions);
  DisplacementFieldTransform( Image &);

  DisplacementFieldTransform( const DisplacementFieldTransform & );

  DisplacementFieldTransform &operator=( const DisplacementFieldTransform & );

  /** parameters */
  // set displacement methods take ownership for the image and remove it
  Self &SetDisplacementField(Image &);
  /** \todo The returned image is should not directly modify the
   * internal displacement field.
   */
  Image GetDisplacementField() const;

  /** fixed parameter */

  /* additional methods */
  Self &SetInverseDisplacementField(Image &);
  /** \todo The returned image is should not directly modify the
   * internal displacement field.
   */
  Image GetInverseDisplacementField() const;

  Self &SetInterpolator(InterpolatorEnum interp);
  // InterpolatorEnum GetInterpolator() const; How to do this?

  Self &SetSmoothingOff();
  Self &SetSmoothingGaussianOnUpdate( double varianceForUpdateField=1.75, double varianceForTotalField=0.5 );
  Self &SetSmoothingBSplineOnUpdate( const std::vector<unsigned int> &numberOfControlPointsForUpdateField = std::vector<unsigned int>(3,4),
                                     const std::vector<unsigned int> &numberOfControlPointsForTotalField = std::vector<unsigned int>(3,4),
                                     bool enforceStationaryBoundary=true,
                                     unsigned int order=3 );


protected:

  virtual void SetPimpleTransform( PimpleTransformBase *pimpleTransform );

private:

  using Superclass::AddTransform;

  struct MyVisitor
  {
    itk::TransformBase *transform;
    DisplacementFieldTransform *that;
    template< typename TransformType >
    void operator() ( void ) const
      {
        TransformType *t = dynamic_cast<TransformType*>(transform);
        if (t)
          {
          that->InternalInitialization<TransformType>(t);
          }
      }
  };

  void InternalInitialization(itk::TransformBase *transform);

  template <typename TransformType>
    void InternalInitialization(TransformType *transform);

  template< typename TDisplacementFieldTransform >
    static Image InternalGetDisplacementField( const TDisplacementFieldTransform *itkDisplacementTx );
  template< typename TDisplacementFieldTransform >
    static Image InternalGetInverseDisplacementField( const TDisplacementFieldTransform *itkDisplacementTx );

  template< typename TDisplacementFieldTransform >
    void InternalSetSmoothingOff(TDisplacementFieldTransform *itkDisplacement);
  template< typename TDisplacementFieldTransform >
    void InternalSetSmoothingGaussianOnUpdate( TDisplacementFieldTransform *itkDisplacement,
                                               double varianceForUpdateField,
                                               double varianceForTotalField );
  template< typename TDisplacementFieldTransform >
    void InternalSetSmoothingBSplineOnUpdate( TDisplacementFieldTransform *itkDisplacement,
                                              const std::vector<unsigned int> &numberOfControlPointsForUpdateField,
                                              const std::vector<unsigned int> &numberOfControlPointsForTotalField,
                                              bool enforceStationaryBoundary,
                                              unsigned int order );


  static PimpleTransformBase *CreateDisplacementFieldPimpleTransform(unsigned int dimension);

  nsstd::function<void (Image &)> m_pfSetDisplacementField;
  nsstd::function<Image ()> m_pfGetDisplacementField;

  nsstd::function<void (Image &)> m_pfSetInverseDisplacementField;
  nsstd::function<Image ()> m_pfGetInverseDisplacementField;

  nsstd::function<void (InterpolatorEnum &)> m_pfSetInterpolator;
  nsstd::function<InterpolatorEnum ()> m_pfGetInterpolator;

  nsstd::function<void ()> m_pfSetSmoothingOff;
  nsstd::function<void (double, double)> m_pfSetSmoothingGaussianOnUpdate;
  nsstd::function<void (const std::vector<unsigned int> &,const std::vector<unsigned int>&, bool, unsigned int)> m_pfSetSmoothingBSplineOnUpdate;

};

}
}

#endif // __sitkDisplacementFieldTransform_h
