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

#include "MyDiffusion.h"

template<>
InputParameters validParams<MyDiffusion>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredParam<Real>("viscosity", "Viscosity to stabilize FEM");
  return params;
}

MyDiffusion::MyDiffusion(const InputParameters & parameters) :
    Kernel(parameters),
   _viscosity(getParam<Real>("viscosity"))
{}

Real MyDiffusion::computeQpResidual()
{
  return _viscosity * _grad_test[_i][_qp] * _grad_u[_qp];
}

Real MyDiffusion::computeQpJacobian()
{
  return _viscosity * _grad_test[_i][_qp] * _grad_phi[_j][_qp];
}
