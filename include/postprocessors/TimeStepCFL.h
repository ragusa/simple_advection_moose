#ifndef TIMESTEPCFL_H
#define TIMESTEPCFL_H

#include "ElementPostprocessor.h"
#include "MooseRandom.h"

class TimeStepCFL;

template<>
InputParameters validParams<TimeStepCFL>();

class TimeStepCFL : public ElementPostprocessor
{
public:
  TimeStepCFL(const InputParameters & parameters);
  virtual ~TimeStepCFL();

  virtual void initialize();
  virtual void execute();
  virtual Real getValue();
  virtual void threadJoin(const UserObject & uo);

  static void initRandom()
  {

    unsigned int randinit = 2000;
    MooseRandom::seed(randinit);

  }
protected:

  // Coupled variables
  VariableValue & _u;

  // Parameter
  Real _cfl;
  Real _viscosity;
  Real _value;
};


#endif // TIMESTEPCFL_H
