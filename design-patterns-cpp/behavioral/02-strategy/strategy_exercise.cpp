#include <iostream>
#include <vector>
#include <complex>
#include <tuple>
using namespace std;

struct DiscriminantStrategy
{
    virtual double calculate_discriminant(double a, double b, double c) = 0;
};

struct OrdinaryDiscriminantStrategy : DiscriminantStrategy
{
    double calculate_discriminant(double a, double b, double c) override {
      return b*b - 4*a*c;
    }
};

struct RealDiscriminantStrategy : DiscriminantStrategy
{
    double calculate_discriminant(double a, double b, double c) override {
      double result = b*b - 4*a*c;
      return result >= 0 ? result : numeric_limits<double>::quiet_NaN();
    }
};

class QuadraticEquationSolver
{
    DiscriminantStrategy& strategy;
public:
    QuadraticEquationSolver(DiscriminantStrategy &strategy) : strategy(strategy) {}

    tuple<complex<double>, complex<double>> solve(double a, double b, double c)
    {
      complex<double> disc{strategy.calculate_discriminant(a,b,c), 0};
      auto root_disc = sqrt(disc);
      return {
          (-b+root_disc) / (2*a),
          (-b-root_disc) / (2*a) };
    };
};

int main(int argc, char* argv[])
{
  OrdinaryDiscriminantStrategy ostr1;
  QuadraticEquationSolver solver1{ostr1};
  auto results1 = solver1.solve(1,10,16);
  std::cout << "solver1; get<0> = " << get<0>(results1) << "\n";
  std::cout << "solver1; get<1> = " << get<1>(results1) << "\n";

  RealDiscriminantStrategy rstr1;
  QuadraticEquationSolver solver2{rstr1};
  auto results2 = solver2.solve(1,10,16);
  std::cout << "solver2; get<0> = " << get<0>(results2) << "\n";
  std::cout << "solver2; get<1> = " << get<1>(results2) << "\n";

  RealDiscriminantStrategy rstr2;
  QuadraticEquationSolver solver3{rstr2};
  auto results3 = solver3.solve(1,4,5);
  auto x1 = get<0>(results3);
  auto x2 = get<1>(results3);
  std::cout << "solver3; x1.real = " << x1.real() << "\n";
  std::cout << "solver3; x2.real = " << x2.real() << "\n";
  std::cout << "solver3; x1.imag = " << x1.imag() << "\n";
  std::cout << "solver3; x2.imag = " << x2.imag() << "\n";
  std::cout << "solver3; x1 = " << x1 << "\n";
  std::cout << "solver3; x2 = " << x2 << "\n";

  OrdinaryDiscriminantStrategy ostr2;
  QuadraticEquationSolver solver4{ostr2};
  auto results4 = solver4.solve(1,4,5);
  std::cout << "solver4; get<0> = " << get<0>(results4) << "\n";
  std::cout << "solver4; get<1> = " << get<1>(results4) << "\n";

  return 0;
}