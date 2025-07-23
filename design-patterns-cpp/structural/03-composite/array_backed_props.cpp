#include <iostream>
#include <array>
#include <algorithm>
#include <numeric> // std::accumulate()

// old style
class CreatureCustom
{
 int strength, agility, intelligence;
 // new property
 int charisma;
public:
 int getStrength() const
 {
   return strength;
 }

 void setStrength(int strength)
 {
   Creature::strength=strength;
 }

 int getAgility() const
 {
   return agility;
 }

 void setAgility(int agility)
 {
   Creature::agility=agility;
 }

 int getIntelligence() const
 {
   return intelligence;
 }

 void setIntelligence(int intelligence)
 {
   Creature::intelligence=intelligence;
 }

 // sum, average, max.

 double sum() const {
   return strength + agility + intelligence;
 }

 double average() const {
   return sum() / 3.0;
 }

 int max() const {
   return ::max(::max(strength, agility), intelligence);
 }
};

// New way, composite form
class Creature
{
  enum Abilities{ STRENGTH = 0, AGILITY, INTELLIGENCE, COUNT };

  std::array<int, Abilities::COUNT> abilities;

public:
  int getStrength() const { return abilities[Abilities::STRENGTH]; }
  void setStrength(int value) { abilities[Abilities::STRENGTH] = value; }

  int getAgility() const { return abilities[Abilities::AGILITY]; }
  void setAgility(int value) { abilities[Abilities::AGILITY] = value; }

  int getIntelligence() const { return abilities[Abilities::INTELLIGENCE]; }
  void setIntelligence(int value) { abilities[Abilities::INTELLIGENCE] = value; }

  int sum() const {
    return std::accumulate(abilities.begin(), abilities.end(), 0);
  }

  double average() const {
    return sum() / (double)Abilities::COUNT;
  }

  int max() const {
    return *std::max_element(abilities.begin(), abilities.end());
  }
};

int main(int argc, char* argv[])
{
  Creature orc;
  orc.setStrength(16);
  orc.setAgility(11);
  orc.setIntelligence(9);

  std::cout << "The orc has an average stat of "
       << orc.average()
       << " and a maximum stat of "
       << orc.max()
       << "\n";

  return 0;
}