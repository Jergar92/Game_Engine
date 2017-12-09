#pragma once
#include <string>
#include <functional>
#include <map>
// Function Pointers http://www.learncpp.com/cpp-tutorial/78-function-pointers/

struct EventVoid
{
	EventVoid();
	//EventVoid(const EventVoid& copy);
	EventVoid(std::string name);

	EventVoid(std::string name, std::function<void()>);


	~EventVoid();

	std::string name;

	std::function<void()> event_function;

};

//TODO add events with argurments
class EventSystem
{
public:
	
	EventSystem();
	~EventSystem();
	void AddEvent(EventVoid new_event);
	void CallEvent(const char* name);
private:
	std::map<std::string, EventVoid> event_list;
};

extern EventSystem* EventS;
