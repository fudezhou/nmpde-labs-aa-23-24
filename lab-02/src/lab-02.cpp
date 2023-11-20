#include <iostream>
#include <deal.II/base/convergence_table.h>
#include <vector>

#include "Poisson1D.hpp"

// Main function.
int
main(int /*argc*/, char * /*argv*/[])
{
  const std::vector<unsigned int> N_values = { 9, 19, 39, 79, 159 };
  // const unsigned int N = 39; 
  const unsigned int r = 1;

  ConvergenceTable convergence_table;

  for (const auto &N : N_values)
  {
    Poisson1D problem(N, r);

    problem.setup();
    problem.assemble();
    problem.solve();
    problem.output();

    const double error_L2 = problem.compute_error_L2(VectorTools::L2_norm);
    const double h        = 1.0 / (N + 1.0);

    convergence_table.add_value("h", h);
    convergence_table.add_value("L2", error_L2);
  }
  
  convergence_table.evaluate_all_convergence_rates(
    "L2", ConvergenceTable::reduction_rate_log2);

  convergence_table.set_scientific("L2", true);
  convergence_table.write_text(std::cout);

  return 0;
}
