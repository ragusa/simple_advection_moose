#ifndef SIMPLE_ADVECTION_MOOSEAPP_H
#define SIMPLE_ADVECTION_MOOSEAPP_H

#include "MooseApp.h"

class SimpleAdvectionMooseApp;

template<>
InputParameters validParams<SimpleAdvectionMooseApp>();

class SimpleAdvectionMooseApp : public MooseApp
{
public:
  SimpleAdvectionMooseApp(InputParameters parameters);
  virtual ~SimpleAdvectionMooseApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* SIMPLE_ADVECTION_MOOSEAPP_H */
