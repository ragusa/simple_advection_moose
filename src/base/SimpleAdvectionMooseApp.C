#include "SimpleAdvectionMooseApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"

// the include for simple_advection_mmose
#include "MyAdvection.h"
#include "MyDiffusion.h"
#include "TimeStepCFL.h"

template<>
InputParameters validParams<SimpleAdvectionMooseApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  return params;
}

SimpleAdvectionMooseApp::SimpleAdvectionMooseApp(InputParameters parameters) :
    MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  SimpleAdvectionMooseApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  SimpleAdvectionMooseApp::associateSyntax(_syntax, _action_factory);
}

SimpleAdvectionMooseApp::~SimpleAdvectionMooseApp()
{
}

// External entry point for dynamic application loading
extern "C" void SimpleAdvectionMooseApp__registerApps() { SimpleAdvectionMooseApp::registerApps(); }
void
SimpleAdvectionMooseApp::registerApps()
{
  registerApp(SimpleAdvectionMooseApp);
}

// External entry point for dynamic object registration
extern "C" void SimpleAdvectionMooseApp__registerObjects(Factory & factory) { SimpleAdvectionMooseApp::registerObjects(factory); }
void
SimpleAdvectionMooseApp::registerObjects(Factory & factory)
{
  registerTimeStepper(TimeStepCFL);
  registerKernel(MyAdvection);
  registerKernel(MyDiffusion);
}

// External entry point for dynamic syntax association
extern "C" void SimpleAdvectionMooseApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { SimpleAdvectionMooseApp::associateSyntax(syntax, action_factory); }
void
SimpleAdvectionMooseApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
