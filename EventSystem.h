#pragma once
#include <string>
#include <functional>
#include <map>
#include "ModuleScene.h"
// Function Pointers http://www.learncpp.com/cpp-tutorial/78-function-pointers/
struct EventVoid
{

	void Create(std::string ptr, void(*ptr_function)())
	{
		name = ptr;
		event_function = ptr_function;
	}
	
	template<typename C>
	void Create(std::string ptr, C* class_obj, void(C::*ptr_function)())
	{
		Create(ptr, [object = class_obj, memFunc = ptr_function]()
		{
			name = ptr;
			(object->*(memFunc))(arg);
		});

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
	
	void AddEvent(EventVoid new_event);
	void CallEvent(const char* name);

private:
	
	std::map<std::string, EventVoid> event_list;
	
};

extern EventSystem* EventS;


