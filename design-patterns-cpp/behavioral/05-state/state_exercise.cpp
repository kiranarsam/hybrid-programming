#include <iostream>
#include <vector>
#include <string>

class CombinationLock
{
private:
    std::vector<int> combination;
    int digits_entered{0};
    bool failed{false};

    void reset()
    {
      status = "LOCKED";
      digits_entered = 0;
      failed = false;
    }
public:
    std::string status;

    CombinationLock(const std::vector<int> &combination) : combination(combination)
    {
      reset();
    }

    void enter_digit(int digit)
    {
      if (status == "LOCKED") {
        status = "";
      }

      status +=  std::to_string(digit);

      if (combination[digits_entered] != digit)
      {
        failed = true;
      }

      digits_entered++;

      if (digits_entered == combination.size()) {
        status = failed ? "ERROR" : "OPEN";
      }
    }
};

int main(int argc, char** argv)
{
  CombinationLock c1({1,2,3});
  std::cout << "Status = " << c1.status << "\n";
  c1.enter_digit(1);
  std::cout << "Status = " << c1.status << "\n";
  c1.enter_digit(2);
  std::cout << "Status = " << c1.status << "\n";
  c1.enter_digit(3);
  std::cout << "Status = " << c1.status << "\n";

  CombinationLock c2({1,2,3});
  std::cout << "Status = " << c2.status << "\n";
  c2.enter_digit(1);
  std::cout << "Status = " << c2.status << "\n";
  c2.enter_digit(2);
  std::cout << "Status = " << c2.status << "\n";
  c2.enter_digit(5);
  std::cout << "Status = " << c2.status << "\n";

  return 0;
}