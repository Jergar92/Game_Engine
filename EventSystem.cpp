#include "EventSystem.h"



EventSystem::EventSystem()
{
}


EventSystem::~EventSystem()
{
}

void EventSystem::AddEvent(Event new_event)
{
	event_list[new_event.name] = new_event;
}

void EventSystem::CallEvent(const char * name)
{
	std::map<std::string, Event> ::iterator it = event_list.find(name);

	if (it != event_list.end())
	{
		it->second.event_function();
	}
}

Event::Event(const char* name, void(*ptr_function)()) :name(name), event_function(ptr_function)
{
}
