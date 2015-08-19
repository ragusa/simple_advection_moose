#include "TimeStepCFL.h"

template<>
InputParameters validParams<TimeStepCFL>()
{
  InputParameters params = validParams<ElementPostprocessor>();

  params.addRequiredCoupledVar("u"  , "solution");
  params.addRequiredParam<Real>("cfl", "CFL number supplied by the user");
  params.addRequiredParam<Real>("viscosity", "viscosity");

  return params;
}

TimeStepCFL::TimeStepCFL(const InputParameters & parameters) :
  ElementPostprocessor(parameters),
  _u(coupledValue("u")),
  _cfl(getParam<Real>("cfl")),
  _viscosity(getParam<Real>("viscosity")),
  _value(0.)
{
}

TimeStepCFL::~TimeStepCFL()
{
}

void
TimeStepCFL::initialize()
{
  _value = std::numeric_limits<Real>::max();
}

void
TimeStepCFL::execute()
{
  // Compute cell size
  Real h_cell = std::pow(_current_elem->volume(), 1./_mesh.dimension());
  _value=1e10;
  
  // Loop over quadrature points
  for (unsigned qp = 0; qp < _qrule->n_points(); ++qp)
  {
    // Compute local max eigenvalue
    Real eigen = 1.;
    
    Real dt_hyperbolic = _cfl * h_cell / eigen;
    Real dt_diffusion  = 2. * _cfl * h_cell * h_cell / _viscosity;
    Real dt = std::min(dt_hyperbolic, dt_diffusion);

    // Compute the local time step
    _value = std::min(_value, dt);

//   Moose::out << "hyper " << dt_hyperbolic 
//              << " diff " << dt_diffusion 
//              << " dt " << dt 
//              << std::endl;
  }
  // debug
  //     _value = 1.e-4;
  
  Real my_rand = MooseRandom::rand();
//   Moose::out << "value = " << _value 
//              << " random = " << my_rand
//              << std::endl;
  _value = (1.-my_rand/10.)*_value;
}

Real
TimeStepCFL::getValue()
{
  _communicator.min(_value);
  return _value;
}

void
TimeStepCFL::threadJoin(const UserObject & uo)
{
  const TimeStepCFL & pps = dynamic_cast<const TimeStepCFL &>(uo);
  _value = std::min(_value, pps._value);
}