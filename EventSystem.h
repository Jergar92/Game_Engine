#ifndef _EVENT_SYSTEM_H
#define _EVENT_SYSTEM_H
#include <string>
#include <functional>
#include <map>
// Function Pointers http://www.learncpp.com/cpp-tutorial/78-function-pointers/

struct Event
{
	Event(const char* name, void(*ptr_function)());
	std::string name;
	std::function<void()> event_function;

};
//TODO add events with argurments
class EventSystem
{
public:
	EventSystem();
	~EventSystem();
	void AddEvent(Event new_event);
	void CallEvent(const char* name);
private:
	std::map<std::string, Event> event_list;
};

#endif //_EVENT_SYSTEM_H
