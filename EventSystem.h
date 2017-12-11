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
template<typename TYPE>
struct EventType
{

	void Create(std::function<void(TYPE)>ptr_function)
	{

		event_function = ptr_function;
	}

	template<typename C>
	void Create(std::string name, C* class_obj, void(C::*ptr_function)(TYPE))
	{
		SetName(name);
		Create([object = class_obj, memFunc = ptr_function](TYPE arg)
		{
			(object->*(memFunc))(arg);//<--send this to Create(void(*ptr_function)());
		});

	}

	void SetName(std::string ptr)
	{
		name = ptr;

	}

	std::string name;

	std::function<void(TYPE)> event_function;

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

/*	template<typename TYPE>
	void AddEvent(EventType<TYPE> new_event)
	{
		event_type_list[new_event.name]= new_event;
	}*/

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
/*	template<typename TYPE>
	void CallEvent(std::string name, TYPE arg)
	{
		std::map<std::string, EventType<TYPE>>::const_iterator it = event_type_list.begin();
		for (; it != event_type_list.end(); it++)
		{
			if (strcmp(name.c_str(), it->first.c_str()) == 0)
			{
				it->second.event_function(arg);
			}
		}
	}*/
private:
	//TODO make one big list of events??¿¿
	std::map<std::string, EventVoid > event_list;

//	template<typename TYPE>
//	std::map<std::string, EventType<TYPE> event_type_list;

};

extern EventSystem* EventS;


