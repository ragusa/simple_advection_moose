[GlobalParams]
  # don't change the domain size, this viscosity value is hardcoded and corresponds to 
  # the first-order viscosity for this domain size and this number of cells!
  viscosity =0.02
  implicit=false
[]

[Mesh]
  type = GeneratedMesh
  dim = 1
  nx =  100
  xmin =  0.
  xmax = 10.
[]

[Variables]
  [./u]
    order = FIRST
    family = LAGRANGE
    [./InitialCondition]
      type = FunctionIC
      function = ic_func
    [../]
  [../]
[]

[Functions]
  [./ic_func]
    axis = 0
    type = PiecewiseLinear
    x = ' 0.  5.   5.00001 10.'
    y = ' 3.  3.   1.       1.'
  [../]
[]

[Kernels]
  [./time]
    type = TimeDerivative
    variable = u
    implicit=true
  [../]

  [./advection]
    type = MyAdvection
    variable = u
    velocity ='1. 0. 0.'
  [../]

  [./diffusion]
    type = MyDiffusion
    variable = u
  [../]
[]

[BCs]
  [./left_u]
    type = DirichletBC
    variable = u
    boundary = left
    value = 3.
  [../]

  [./right_u]
    type = DirichletBC
    variable = u
    boundary = right
    value = 1.
  [../]
[]

[Postprocessors]
  [./dt]
    type = TimeStepCFL
    u = u
    cfl = 0.5
    outputs = none
  [../]
[]

# [Preconditioning]
#   [./smp]
#     type = SMP
#     full = true
#     solve_type = NEWTON               # Use "regular" Newton's method (Jacobian MUST be correct)
#     petsc_options_iname = '-pc_type'  # LU is essentially a "direct solve"
#     petsc_options_value = 'lu'
#     line_search = 'none'              # Don't allow line search to cut back the steps
#   [../]
# []

[Executioner]
  type = Transient
  scheme = 'explicit-euler'
  solve_type = 'LINEAR'
  l_tol =1.e-10
  
  [./TimeStepper]
    type = PostprocessorDT
    postprocessor = dt
    dt = 1.e-3
  [../]

  nl_rel_tol = 1e-12
  nl_abs_tol = 1e-6
  nl_max_its = 1
  
  end_time = 4.

[]

[Outputs]
  [./out]
    type = CSV
    file_base = cfl_explicit
  [../]
  output_initial = true
  file_base = out_explicit
  exodus = true
  print_linear_residuals = true
  print_perf_log = true
[]
