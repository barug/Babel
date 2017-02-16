#include "../QtNet.h"
#include <iostream>

int main()
{
  QtNet qtNet;
  std::queue<Event *> events;
  
  qtNet.connectTcp("127.0.0.1", 4242);
  events.emplace(new Event(Event::GUI_REGISTER));
  events.back()->addData("messageData", "this is the data");
  events.emplace(new Event(Event::GUI_AUTHENTIFICATION));
  events.back()->addData("messageData", "this is the second data");
  events.emplace(new Event(Event::GUI_CALL));
  events.back()->addData("messageData", "this is the third data");
  std::cout << events.size();
  qtNet.sendEvents(&events);
  while(1);
  
}
