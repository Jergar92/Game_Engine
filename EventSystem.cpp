#include "EventSystem.h"



EventSystem::EventSystem()
{
}


EventSystem::~EventSystem()
{
}

void EventSystem::AddEvent(EventVoid new_event)
{
	event_list[new_event.name] = new_event;
}

void EventSystem::CallEvent(const char * name)
{
	std::map<std::string, EventVoid> ::iterator it = event_list.find(name);

	if (it != event_list.end())
	{
		it->second.event_function();
	}
}

EventVoid::EventVoid()
{
}
EventVoid::EventVoid(std::string name):name(name)
{
}
/*
EventVoid::EventVoid(const EventVoid & copy)
{
	name = copy.name;
	event_function = copy.event_function;
}
*/
EventVoid::EventVoid(std::string  name, std::function<void()> ptr_function) :name(name), event_function(ptr_function)
{
}

EventVoid::~EventVoid()
{
}
