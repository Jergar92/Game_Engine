#pragma once
#include <string>

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

	virtual bool Init() 
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
	virtual bool GuiUpdate()
	{
		return true;
	}

	virtual bool Load()
	{
		return true;
	}

	virtual bool Save()
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