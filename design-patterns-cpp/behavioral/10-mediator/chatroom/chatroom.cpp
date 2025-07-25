#include "chatroom.hpp"

void ChatRoom::broadcast(const std::string &origin, const std::string &message)
{
  for (auto p : people) {
    if (p->name != origin)
      p->receive(origin, message);
  }
}

void ChatRoom::join(Person *p)
{
  std::string join_msg = p->name + " joins the chat";
  broadcast("room", join_msg);
  p->room = this;
  people.push_back(p);
}
