#include <iostream>
#include <vector>

struct Command
{
  enum Action { DEPOSIT, WITHDRAW } action;
  int amount{0};
  bool success{false};
};

struct Account
{
  int balance{0};

  void process(Command& cmd)
  {
    switch (cmd.action)
    {
      case Command::DEPOSIT:
        balance += cmd.amount;
        cmd.success = true;
        break;
      case Command::WITHDRAW:
        cmd.success = (balance >= cmd.amount);
        if (cmd.success) balance -= cmd.amount;
        break;
    }
  }
};

int main(int ac, char* av[])
{
  Account a;
  Command command{Command::DEPOSIT, 100};
  a.process(command);

  std::cout << "Balance = " << a.balance << "\n";
  std::cout << "Success = " << command.success << "\n";

  command = Command{Command::WITHDRAW, 50};
  a.process(command);

  std::cout << "Balance = " << a.balance << "\n";
  std::cout << "Success = " << command.success << "\n";

  command = Command{Command::WITHDRAW, 150};
  a.process(command);

  std::cout << "Balance = " << a.balance << "\n";
  std::cout << "Success = " << command.success << "\n";

  return 0;
}