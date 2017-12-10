#pragma once
#include <string>
#include <functional>
#include <map>
// Function Pointers http://www.learncpp.com/cpp-tutorial/78-function-pointers/

struct EventVoid
{

	void Create(std::function<void()>ptr_function)
	{
	
		event_function = ptr_function;
	}

	template<typename C>
	void Create(std::string name, C* class_obj, void(C::*ptr_function)())
	{
		SetName(name);
		Create([object = class_obj, memFunc = ptr_function]()
		{
			//std::bind( memFunc, object);

			(object->*(memFunc))();//<--send this to Create(void(*ptr_function)());
		});

	}

	void SetName(std::string ptr)
	{
		name = ptr;

	}

	std::string name;

	std::function<void()> event_function;

};

//TODO add events with argurments
class EventSystem
{
public:
	
	EventSystem();
	~EventSystem();
	void AddEvent(EventVoid new_event)
	{
		event_list[new_event.name] = new_event;
	}

	void CallEvent(std::string name)
	{
		
		std::map<std::string, EventVoid> ::iterator it = event_list.find(name);

		if (it != event_list.end())
		{
			it->second.event_function();
		}
	}

private:
	std::map<std::string, EventVoid> event_list;
	
};

extern EventSystem* EventS;


