#include "person.hpp"
#include "chatroom.hpp"

int main(int argc, char **argv)
{
  ChatRoom room;

  Person john{"John"};
  Person jane{"Jane"};
  room.join(&john);
  room.join(&jane);
  john.say("hi room");
  jane.say("oh, hey john");

  Person simon{"Simon"};
  room.join(&simon);
  simon.say("hi everyone!");

  jane.pm("Simon", "glad you found us, simon!");

  return 0;
}