#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // for_each

struct BankAccount
{
  int balance = 0;
  int overdraft_limit = -500;

  void deposit(int amount)
  {
    balance += amount;
    std::cout << "deposited " << amount << ", balance now " << balance << "\n";
  }

  void withdraw(int amount)
  {
    if (balance - amount >= overdraft_limit)
    {
      balance -= amount;
      std::cout << "withdrew " << amount << ", balance now " << balance << "\n";
    }
  }
};

struct Command
{
  virtual ~Command() = default;
  virtual void call() const = 0;
  virtual void undo() const = 0;
};

// should really be BankAccountCommand
struct BankAccountCommand : Command
{
  BankAccount& account;
  enum Action { DEPOSIT, WITHDRAW } action;
  int amount;

  BankAccountCommand(BankAccount& account, const Action action, const int amount)
    : account(account), action(action), amount(amount) {}

  void call() const override
  {
    switch (action)
    {
    case DEPOSIT:
      account.deposit(amount);
      break;
    case WITHDRAW:
      account.withdraw(amount);
      break;
    default: break;
    }
  }

  void undo() const override
  {
    switch (action)
    {
    case WITHDRAW:
      account.deposit(amount);
      break;
    case DEPOSIT:
      account.withdraw(amount);
      break;
    default: break;
    }
  }
};

// vector doesn't have virtual dtor, but who cares?
struct CompositeBankAccountCommand
  : std::vector<BankAccountCommand>, Command
{
  CompositeBankAccountCommand(const std::initializer_list<value_type>& items)
    : std::vector<BankAccountCommand>(items) {}

  void call() const override
  {
    for (auto& cmd : *this) {
      cmd.call();
    }
  }

  void undo() const override
  {
    for (auto& cmd : *this) {
      cmd.undo();
    }
  }
};

int main(int argc, char **argv)
{
  BankAccount ba;
  std::vector<BankAccountCommand> commands1{
    BankAccountCommand{ba, BankAccountCommand::DEPOSIT, 100},
    BankAccountCommand{ba, BankAccountCommand::WITHDRAW, 200}
  };

  CompositeBankAccountCommand commands2 {
    BankAccountCommand{ba, BankAccountCommand::DEPOSIT, 100},
    BankAccountCommand{ba, BankAccountCommand::WITHDRAW, 200}
  };

  std::cout << ba.balance << std::endl;

  // apply all the commands
  for (auto& cmd : commands1)
  {
    cmd.call();
  }
  std::cout << ba.balance << std::endl;

  std::for_each(commands1.rbegin(), commands1.rend(),[](const BankAccountCommand& cmd) {
      cmd.undo();
    });

  std::cout << ba.balance << std::endl;
  commands2.call();
  std::cout << ba.balance << std::endl;
  commands2.undo();
  std::cout << ba.balance << std::endl;

  return 0;
}
