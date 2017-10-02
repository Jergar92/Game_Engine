#pragma once
#include <string>
#include "Parson\parson.h"
class Application;
struct PhysBody3D;

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

	virtual bool Awake(const JSON_Object* data)
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
	virtual bool LoadConfig(const JSON_Object* data)
	{
		return true;
	}

	virtual bool SaveConfig(const JSON_Object* data)
	{
		return true;
	}

	virtual bool CleanUp() 
	{ 
		return true; 
	}

	virtual void OnCollision(PhysBody3D* body1, PhysBody3D* body2)
	{}
public:
	std::string	name;
	
};