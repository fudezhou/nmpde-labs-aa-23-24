#include <deal.II/base/convergence_table.h>

#include <fstream>
#include <iostream>
<<<<<<< HEAD
#include <deal.II/base/convergence_table.h>
=======
>>>>>>> 75d41876821896addaf8378a6695d13b18b6d48d
#include <vector>

#include "Poisson1D.hpp"

// Main function.
int
main(int /*argc*/, char * /*argv*/[])
{
<<<<<<< HEAD
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
=======
  ConvergenceTable table;

  const std::vector<unsigned int> N_values = {9, 19, 39, 79, 159, 319};
  const unsigned int              degree   = 2;

  std::ofstream convergence_file("convergence.csv");
  convergence_file << "h,eL2,eH1" << std::endl;

  for (const unsigned int &N : N_values)
    {
      Poisson1D problem(N, degree);

      problem.setup();
      problem.assemble();
      problem.solve();
      problem.output();

      const double h        = 1.0 / (N + 1.0);
      const double error_L2 = problem.compute_error(VectorTools::L2_norm);
      const double error_H1 = problem.compute_error(VectorTools::H1_norm);

      table.add_value("h", h);
      table.add_value("L2", error_L2);
      table.add_value("H1", error_H1);

      convergence_file << h << "," << error_L2 << "," << error_H1 << std::endl;
    }

  table.evaluate_all_convergence_rates(ConvergenceTable::reduction_rate_log2);

  table.set_scientific("L2", true);
  table.set_scientific("H1", true);

  table.write_text(std::cout);
>>>>>>> 75d41876821896addaf8378a6695d13b18b6d48d

  return 0;
}