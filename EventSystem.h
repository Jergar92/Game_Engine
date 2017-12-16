#pragma once
#include "Globals.h"
#include <string>
#include <functional>
#include <map>
#include <list>
// Function Pointers http://www.learncpp.com/cpp-tutorial/78-function-pointers/

struct EventVoid
{

	void Create(std::function<void()>ptr_function)
	{
	
		event_function = ptr_function;
	}

	template<typename C>
	void Create(std::string name, C* class_obj, void(C::*ptr_function)(), uint UID = 0)
	{
		SetUID(UID);
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

	void SetUID(uint value)
	{
		UID = value;

	}
	bool Compare(uint value)
	{
		return UID == value;
	}
	bool operator==(const EventVoid& other)
	{
		return UID == other.UID;
	}
		uint UID;


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
	void Create( std::string name, C* class_obj, void(C::*ptr_function)(float, float), uint UID = 0)
	{
		SetUID(UID);

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

	void SetUID(uint value)
	{
		UID = value;

	}
	bool Compare(uint value)
	{
		return UID == value;
	}
	bool operator==(const EventFloat& other)
	{
		return UID == other.UID;
	}
	uint UID;

	std::string name;

	std::function<void(float, float)> event_function;

};


struct EventChar
{

	void Create(std::function<void(const char*)>ptr_function)
	{

		event_function = ptr_function;
	}

	template<typename C>
	void Create( std::string name, C* class_obj, void(C::*ptr_function)(const char*), uint UID = 0)
	{
		SetUID(UID);

		SetName(name);
		Create([object = class_obj, memFunc = ptr_function](const char* arg)
		{
			(object->*(memFunc))(arg);//<--send this to Create(void(*ptr_function)());
		});

	}

	void SetUID(uint value)
	{
		UID = value;

	}

	void SetName(std::string ptr)
	{
		name = ptr;

	}
	bool Compare(uint value)
	{
		return UID == value;
	}
	bool operator==(const EventChar& other)
	{
		return UID == other.UID;
	}
	uint UID;

	std::string name;

	std::function<void(const char*)> event_function;
};


struct EventBool
{

	void Create(std::function<void(bool)>ptr_function)
	{

		event_function = ptr_function;
	}

	template<typename C>
	void Create(std::string name, C* class_obj, void(C::*ptr_function)(bool), uint UID = 0)
	{
		SetUID(UID);

		SetName(name);
		Create([object = class_obj, memFunc = ptr_function](bool arg)
		{
			(object->*(memFunc))(arg);//<--send this to Create(void(*ptr_function)());
		});

	}

	void SetUID(uint value)
	{
		UID = value;

	}

	void SetName(std::string ptr)
	{
		name = ptr;

	}
	bool Compare(uint value)
	{
		return UID == value;
	}
	bool operator==(const EventBool& other)
	{
		return UID == other.UID;
	}
	uint UID;

	std::string name;

	std::function<void(bool)> event_function;
};
//TODO add events with argurments
class EventSystem
{
public:
	
	EventSystem();
	~EventSystem();
	void AddEvent(EventVoid new_event)
	{
		event_list[new_event.name].push_back(new_event);
	}

	void AddEvent(EventFloat new_event)
	{
		event_float_list[new_event.name].push_back( new_event);
	}
	void AddEvent(EventChar new_event)
	{
		event_char_list[new_event.name].push_back(new_event);
	}
	void AddEvent(EventBool new_event)
	{
		event_bool_list[new_event.name].push_back(new_event);
	}
	
	void CallEvent(std::string name)
	{		
		std::map<std::string, std::list<EventVoid> >::const_iterator it = event_list.begin();
		for (; it != event_list.end(); it++)
		{
			if (strcmp(name.c_str(), it->first.c_str()) == 0)
			{
				for (std::list<EventVoid>::const_iterator iterator = it->second.begin(); iterator != it->second.end(); iterator++)
				{
					iterator->event_function();
				}
			}
		}
	}
	void CallEvent(std::string name, float arg1, float arg2)
	{
		std::map<std::string, std::list<EventFloat>>::const_iterator it = event_float_list.begin();
		for (; it != event_float_list.end(); it++)
		{
			if (strcmp(name.c_str(), it->first.c_str()) == 0)
			{
				for (std::list<EventFloat>::const_iterator iterator = it->second.begin(); iterator != it->second.end(); iterator++)
				{
					iterator->event_function(arg1, arg2);
				}
			}
		}
	}
	void CallEvent(std::string name, const char* arg)
	{
		std::map<std::string, std::list<EventChar>>::const_iterator it = event_char_list.begin();
		for (; it != event_char_list.end(); it++)
		{
			if (strcmp(name.c_str(), it->first.c_str()) == 0)
			{
				for (std::list<EventChar>::const_iterator iterator = it->second.begin(); iterator != it->second.end(); iterator++)
				{
					iterator->event_function(arg);
				}
			}
		}
	}

	void CallEvent(std::string name, bool arg)
	{
		std::map<std::string, std::list<EventBool>>::const_iterator it = event_bool_list.begin();
		for (; it != event_bool_list.end(); it++)
		{
			if (strcmp(name.c_str(), it->first.c_str()) == 0)
			{
				for (std::list<EventBool>::const_iterator iterator = it->second.begin(); iterator != it->second.end(); iterator++)
				{
					iterator->event_function(arg);
				}
			}
		}
	}
//Removals
	
	void EraseEventVoid(std::string name, uint UID)
	{
		std::map<std::string, std::list<EventVoid>>::iterator it = event_list.begin();
		for (; it != event_list.end(); it++)
		{
			if (strcmp(name.c_str(), it->first.c_str()) == 0)
			{
				for (std::list<EventVoid>::iterator iterator = it->second.begin(); iterator != it->second.end(); iterator++)
				{
					
					if ((*iterator).Compare(UID))
					{
						it->second.remove((*iterator));
						return;
					}
					
				}
			}
		}
	}


	
	void EraseEventFloat(std::string name, uint UID)
	{
		std::map<std::string, std::list<EventFloat>>::iterator it = event_float_list.begin();
		for (; it != event_float_list.end(); it++)
		{
			if (strcmp(name.c_str(), it->first.c_str()) == 0)
			{
				for (std::list<EventFloat>::iterator iterator = it->second.begin(); iterator != it->second.end(); iterator++)
				{
					if ((*iterator).Compare(UID))
					{
						it->second.remove((*iterator));
						return;
					}
				}
			}
		}
	}
	void EraseEventChar(std::string name, uint UID)
	{
		std::map<std::string, std::list<EventChar>>::iterator it = event_char_list.begin();
		for (; it != event_char_list.end(); it++)
		{
			if (strcmp(name.c_str(), it->first.c_str()) == 0)
			{
				for (std::list<EventChar>::iterator iterator = it->second.begin(); iterator != it->second.end(); iterator++)
				{
					if ((*iterator).Compare(UID))
					{
						it->second.remove((*iterator));
						return;
					}
				}
			}
		}
	}
	void EraseEventBool(std::string name, uint UID)
	{
		std::map<std::string, std::list<EventBool>>::iterator it = event_bool_list.begin();
		for (; it != event_bool_list.end(); it++)
		{
			if (strcmp(name.c_str(), it->first.c_str()) == 0)
			{
				for (std::list<EventBool>::iterator iterator = it->second.begin(); iterator != it->second.end(); iterator++)
				{
					if ((*iterator).Compare(UID))
					{
						it->second.remove((*iterator));
						return;
					}
				}
			}
		}
	}
private:
	//TODO make one big list of events??¿¿
	std::map<std::string, std::list<EventVoid> > event_list;
	std::map<std::string, std::list<EventFloat>> event_float_list;
	std::map<std::string, std::list<EventChar>> event_char_list;
	std::map<std::string, std::list<EventBool>> event_bool_list;

};

extern EventSystem* EventS;


