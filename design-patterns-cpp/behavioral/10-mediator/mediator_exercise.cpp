#include <iostream>
#include <vector>

struct IParticipant
{
    virtual void notify(IParticipant* sender, int value) = 0;
};

struct Mediator
{
    std::vector<IParticipant*> participants;
    void say(IParticipant* sender, int value)
    {
      for (auto p : participants) {
        p->notify(sender, value);
      }
    }
};

struct Participant : IParticipant
{
    int value{0};
    Mediator& mediator;

    Participant(Mediator &mediator) : mediator(mediator)
    {
      mediator.participants.push_back(this);
    }

    void notify(IParticipant *sender, int value) override {
      if (sender != this) {
        this->value += value;
      }
    }

    void say(int value)
    {
      mediator.say(this, value);
    }
};

int main(int argc, char **argv)
{
  Mediator m;
  Participant p1{m}, p2{m};

  std::cout << "p1 value = " << p1.value << "\n";
  std::cout << "p2 value = " << p2.value << "\n";

  p1.say(2);

  std::cout << "p1 value = " << p1.value << "\n";
  std::cout << "p2 value = " << p2.value << "\n";

  p2.say(4);

  std::cout << "p1 value = " << p1.value << "\n";
  std::cout << "p2 value = " << p2.value << "\n";

  return 0;
}
