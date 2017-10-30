#pragma once
#include <string>
#include "JSONConfig.h"
class Application;

class Module
{
private :
	bool enabled;

public:
	/*Application* App;*/

	Module(bool start_enabled = true)
	{}

	virtual ~Module()
	{}

	virtual bool Awake(const JSONConfig& data)
	{
		return true;
	}
	
	virtual bool Start()
	{
		return true;
	}

	virtual update_status PreUpdate(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status Update(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate(float dt)
	{
		return UPDATE_CONTINUE;
	}
	virtual update_status GuiUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual void GuiConfigUpdate()
	{
		return;
	}
	virtual bool LoadConfig(const JSONConfig& data)
	{
		return true;
	}

	virtual bool SaveConfig(JSONConfig& data)
	{
		return true;
	}

	virtual bool CleanUp() 
	{ 
		return true; 
	}


public:
	std::string	name;
	
};