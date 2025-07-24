#include <iostream>
#include <vector>
#include <complex>
#include <tuple>
using namespace std;

struct Creature
{
    int attack, health;

    Creature(int attack, int health) : attack(attack), health(health) {}
};

struct CardGame
{
    vector<Creature> creatures;

    CardGame(const vector<Creature> &creatures) : creatures(creatures) {}

    // return -1 if there is no clear winner
    int combat(int creature1, int creature2)
    {
      Creature& first = creatures[creature1];
      Creature& second = creatures[creature2];
      hit(first, second);
      hit(second, first);
      bool first_alive = first.health > 0;
      bool second_alive = second.health > 0;
      if (first_alive == second_alive) return -1;
      return first_alive ? creature1 : creature2;
    }

    virtual void hit(Creature& attacker, Creature& other) = 0;
};

struct TemporaryCardDamageGame : CardGame
{
    TemporaryCardDamageGame(const vector<Creature> &creatures) : CardGame(creatures) {}

    void hit(Creature &attacker, Creature &other) override {
      auto old_health = other.health;
      other.health -= attacker.attack;
      if (other.health > 0) other.health = old_health;
    }
};

struct PermanentCardDamageGame : CardGame
{
    PermanentCardDamageGame(const vector<Creature> &creatures) : CardGame(creatures) {}

    void hit(Creature &attacker, Creature &other) override
    {
      other.health -= attacker.attack;
    }
};

int main(int argc, char* argv[])
{
  Creature c1{1,2};
  Creature c2{1,2};
  TemporaryCardDamageGame game({c1,c2});
  std::cout << "CASE1 = " << game.combat(0,1) << "\n";
  std::cout << "CASE1 = " << game.combat(0,1) << "\n";

  Creature c1_1{1,1};
  Creature c2_1{2,2};
  TemporaryCardDamageGame game_1({c1_1, c2_1});
  std::cout << "CASE2 = " << game_1.combat(0,1) << "\n";

  Creature c1_2{2,2};
  Creature c2_2{2,2};
  TemporaryCardDamageGame game_2({c1_2, c2_2});
  std::cout << "CASE3 = " << game_2.combat(0,1) << "\n";

  Creature c1_3{1,2};
  Creature c2_3{1,3};
  PermanentCardDamageGame game_3({c1_3, c2_3});
  std::cout << "CASE4 = " << game.combat(0,1) << "\n";
  std::cout << "CASE4 = " << game.combat(1,0) << "\n";

  return 0;
}