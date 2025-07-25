#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>

struct BankAccount
{
  int balance = 0;
  int overdraft_limit = -500;

  void deposit(int amount)
  {
    balance += amount;
    std::cout << "deposited " << amount << ", balance now " << balance << "\n";
  }

  bool withdraw(int amount)
  {
    if (balance - amount >= overdraft_limit)
    {
      balance -= amount;
      std::cout << "withdrew " << amount << ", balance now " << balance << "\n";
      return true;
    }
    return false;
  }
};

struct Command
{
  bool succeeded;
  virtual void call() = 0;
  virtual void undo() = 0;
};

// should really be BankAccountCommand
struct BankAccountCommand : Command
{
  BankAccount& account;
  enum Action { DEPOSIT, WITHDRAW } action;
  int amount;

  BankAccountCommand(BankAccount& account, const Action action, const int amount)
    : account(account), action(action), amount(amount)
  {
    succeeded = false;
  }

  void call() override
  {
    switch (action)
    {
    case DEPOSIT:
      account.deposit(amount);
      succeeded = true;
      break;
    case WITHDRAW:
      succeeded = account.withdraw(amount);
      break;
    }
  }

  void undo() override
  {
    if (!succeeded) return;

    switch (action)
    {
    case WITHDRAW:
      if (succeeded)
        account.deposit(amount);
      break;
    case DEPOSIT:
      account.withdraw(amount);
      break;
    }
  }
};

// vector doesn't have virtual dtor, but who cares?
struct CompositeBankAccountCommand : std::vector<BankAccountCommand>, Command
{
  CompositeBankAccountCommand(const std::initializer_list<value_type>& _Ilist)
    : std::vector<BankAccountCommand>(_Ilist)
  {
  }

  void call() override
  {
    for (auto& cmd : *this) {
      cmd.call();
    }
  }

  void undo() override
  {
    for (auto it = rbegin(); it != rend(); ++it) {
      it->undo();
    }
  }
};

struct DependentCompositeCommand : CompositeBankAccountCommand
{
  explicit DependentCompositeCommand(const std::initializer_list<value_type>& _Ilist)
    : CompositeBankAccountCommand{ _Ilist }
  {
  }

  void call() override
  {
    bool ok = true;
    for (auto& cmd : *this)
    {
      if (ok)
      {
        cmd.call();
        ok = cmd.succeeded;
      }
      else
      {
        cmd.succeeded = false;
      }
    }
  }
};

struct MoneyTransferCommand : DependentCompositeCommand
{
  MoneyTransferCommand(BankAccount& from, BankAccount& to, int amount)
    : DependentCompositeCommand
  {
    BankAccountCommand{from, BankAccountCommand::WITHDRAW, amount},
    BankAccountCommand{to, BankAccountCommand::DEPOSIT, amount}
  }
  {
  }
};


int main()
{
  BankAccount ba;
  std::vector<BankAccountCommand> commands1{
    BankAccountCommand{ ba, BankAccountCommand::DEPOSIT, 100 },
    BankAccountCommand{ ba, BankAccountCommand::WITHDRAW, 200 }
  };

  std::cout << ba.balance << std::endl;
  // apply all the commands
  for (auto& cmd : commands1)
  {
    cmd.call();
  }
  std::cout << ba.balance << std::endl;

  std::for_each(commands1.rbegin(), commands1.rend(), [](BankAccountCommand& cmd) { cmd.undo(); });
  std::cout << ba.balance << std::endl;

  // **************** //
  CompositeBankAccountCommand commands2{
    BankAccountCommand{ ba, BankAccountCommand::DEPOSIT, 100 },
    BankAccountCommand{ ba, BankAccountCommand::WITHDRAW, 200 }
  };

  std::cout << ba.balance << std::endl;
  // apply all the commands
  commands2.call();
  std::cout << ba.balance << std::endl;
  commands2.undo();
  std::cout << ba.balance << std::endl;

  return 0;
}
