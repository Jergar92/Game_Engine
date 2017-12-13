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
struct EventFloat
{

	void Create(std::function<void(float,float)>ptr_function)
	{

		event_function = ptr_function;
	}

	template<typename C>
	void Create(std::string name, C* class_obj, void(C::*ptr_function)(float, float))
	{
		SetName(name);
		Create([object = class_obj, memFunc = ptr_function](float arg1, float arg2)
		{
			(object->*(memFunc))(arg1, arg2);//<--send this to Create(void(*ptr_function)());
		});

	}

	void SetName(std::string ptr)
	{
		name = ptr;

	}

	std::string name;

	std::function<void(float, float)> event_function;

};
//TODO add events with argurments
class EventSystem
{
public:
	
	EventSystem();
	~EventSystem();
	void AddEvent(EventVoid new_event)
	{
		event_list[new_event.name]=new_event;
	}

	void AddEvent(EventFloat new_event)
	{
		event_float_list[new_event.name]= new_event;
	}

	void CallEvent(std::string name)
	{		
		std::map<std::string, EventVoid>::const_iterator it = event_list.begin();
		for (; it != event_list.end(); it++)
		{
			if (strcmp(name.c_str(), it->first.c_str()) == 0)
			{
				it->second.event_function();
			}
		}
	}
	void CallEvent(std::string name, float arg1, float arg2)
	{
		std::map<std::string, EventFloat>::const_iterator it = event_float_list.begin();
		for (; it != event_float_list.end(); it++)
		{
			if (strcmp(name.c_str(), it->first.c_str()) == 0)
			{
				it->second.event_function(arg1, arg2);
			}
		}
	}
private:
	//TODO make one big list of events??¿¿
	std::map<std::string, EventVoid > event_list;

	std::map<std::string, EventFloat> event_float_list;

};

extern EventSystem* EventS;


