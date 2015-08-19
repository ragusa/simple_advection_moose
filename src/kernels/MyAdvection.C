/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "MyAdvection.h"

template<>
InputParameters validParams<MyAdvection>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredParam<RealVectorValue>("velocity", "Velocity Vector");
  return params;
}

MyAdvection::MyAdvection(const InputParameters & parameters) :
    Kernel(parameters),
   _velocity(getParam<RealVectorValue>("velocity"))
{}

Real MyAdvection::computeQpResidual()
{
  return _test[_i][_qp]*(_velocity * _grad_u[_qp]);
}

Real MyAdvection::computeQpJacobian()
{
  return _test[_i][_qp]*(_velocity * _grad_phi[_j][_qp]);
}
