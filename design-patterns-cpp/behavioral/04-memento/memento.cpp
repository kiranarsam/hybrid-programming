#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Memento
{
  int m_balance;
public:
  Memento(int balance) : m_balance(balance)
  {
  }
  friend class BankAccount;
  friend class BankAccount2;
};

class BankAccount
{
  int m_balance = 0;
public:
  explicit BankAccount(const int balance) : m_balance(balance)
  {
  }

  Memento deposit(int amount)
  {
    m_balance += amount;
    return { m_balance };
  }

  void restore(const Memento& m)
  {
    m_balance = m.m_balance;
  }

  friend ostream& operator<<(ostream& os, const BankAccount& obj)
  {
    return os << "BA m_balance: " << obj.m_balance;
  }
};

class BankAccount2 // supports undo/redo
{
  int m_balance = 0;
  std::vector<std::shared_ptr<Memento>> m_changes;
  int m_current;
public:
  explicit BankAccount2(const int balance) : m_balance(balance)
  {
    m_changes.emplace_back(std::make_shared<Memento>(balance));
    m_current = 0;
  }

  std::shared_ptr<Memento> deposit(int amount)
  {
    m_balance += amount;
    auto m = std::make_shared<Memento>(m_balance);
    m_changes.push_back(m);
    ++m_current;
    return m;
  }

  void restore(const std::shared_ptr<Memento>& m)
  {
    if (m)
    {
      m_balance = m->m_balance;
      m_changes.push_back(m);
      m_current = m_changes.size() - 1;
    }
  }

  std::shared_ptr<Memento> undo()
  {
    if (m_current > 0)
    {
      --m_current;
      auto m = m_changes[m_current];
      m_balance = m->m_balance;
      return m;
    }
    return{};
  }

  shared_ptr<Memento> redo()
  {
    if (m_current + 1 < m_changes.size())
    {
      ++m_current;
      auto m = m_changes[m_current];
      m_balance = m->m_balance;
      return m;
    }
    return{};
  }

  friend ostream& operator<<(ostream& os, const BankAccount2& obj)
  {
    return os << "BA2 balance: " << obj.m_balance;
  }
};

void memento()
{
  BankAccount ba{ 100 };
  auto m1 = ba.deposit(50); // 150
  std::cout << ba << "\n";
  auto m2 = ba.deposit(25); // 175
  std::cout << ba << "\n";

  // undo to m1
  ba.restore(m1);
  std::cout << ba << "\n";

  // redo
  ba.restore(m2);
  std::cout << ba << "\n";
}

void undo_redo()
{
  BankAccount2 ba{ 100 };
  ba.deposit(50);
  ba.deposit(25); // 125
  std::cout << ba << "\n";

  ba.undo();
  std::cout << "Undo 1: " << ba << "\n";
  ba.undo();
  std::cout << "Undo 2: " << ba << "\n";
  ba.redo();
  std::cout << "Redo 2: " << ba << "\n";
  ba.undo();
  std::cout << "Undo 3: " << ba << "\n";
}

int main()
{
  memento();
  std::cout << " *************** \n";
  undo_redo();

  return 0;
}
