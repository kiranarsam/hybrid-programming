#include <iostream>
#include <vector>

// forward declaration
struct Creature;

// game
struct Game
{
  std::vector<Creature*> creatures;
};

// stat query
struct StatQuery
{
  enum Statistic { ATTACK, DEFENSE } statistic;
  int result;
};

// creature
struct Creature
{
protected:
  Game& game;
  int base_attack, base_defense;

public:
  Creature(Game &game, int base_attack, int base_defense)
    : game(game), base_attack(base_attack), base_defense(base_defense)
  {
  }

  virtual int getAttack() = 0;
  virtual int getDefense() = 0;
  virtual void query(void* source, StatQuery& sq) = 0;
};

class Goblin : public Creature
{
  int getStatistic(StatQuery::Statistic stat)
  {
    StatQuery q{stat,0};
    for (auto c : game.creatures) {
      c->query(this, q);
    }
    return q.result;
  }

public:
  Goblin(Game &game, int base_attack, int base_defense)
    : Creature(game, base_attack, base_defense)
  {
  }

  Goblin(Game &game) : Creature(game, 1, 1) {}

  int getAttack() override {
    return getStatistic(StatQuery::ATTACK);
  }

  int getDefense() override {
    return getStatistic(StatQuery::DEFENSE);
  }

  void query(void *source, StatQuery &sq) override {
    if (source == this)
    {
      switch (sq.statistic)
      {
        case StatQuery::ATTACK:
          sq.result += base_attack;
          break;
        case StatQuery::DEFENSE:
          sq.result += base_defense;
          break;
      }
    }
    else
    {
      if (sq.statistic == StatQuery::DEFENSE)
      {
        sq.result++;
      }
    }
  }
};

class GoblinKing : public Goblin
{
public:
  GoblinKing(Game &game) : Goblin(game, 3, 3) {}

  void query(void *source, StatQuery &sq) override {
    if (source != this && sq.statistic == StatQuery::ATTACK)
    {
      sq.result++;
    }
    else Goblin::query(source, sq);
  }
};

int main(int argc, char** argv)
{
  Game game;
  Goblin goblin{game};
  game.creatures.push_back(&goblin);

  std::cout << "Checking that a baseline goblin is a 1/1...\n";

  std::cout << "attack = " << goblin.getAttack() << "\n";
  std::cout << "defence = " << goblin.getDefense() << "\n";

  std::cout << "Adding a second goblin, now they should be 1/2...\n";
  Goblin goblin2{game};
  game.creatures.push_back(&goblin2);

  std::cout << "attack = " << goblin.getAttack() << "\n";
  std::cout << "defence = " << goblin.getDefense() << "\n";

  std::cout << "Adding a goblin king, now a goblin should be 2/3...\n";
  GoblinKing goblin3{game};
  game.creatures.push_back(&goblin3);

  std::cout << "attack = " << goblin.getAttack() << "\n";
  std::cout << "defence = " << goblin.getDefense() << "\n";
  return 0;
}