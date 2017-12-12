#include "ComponentButton.h"
#include "Application.h"
#include "ModuleInput.h"
#include "GameObject.h"
#include <gl/GLU.h>
#include "imgui/imgui.h"
#include "ComponentImage.h"

ComponentButton::ComponentButton(GameObject* my_go) : Component(my_go)
{
	component_name = "Button";
	type = CANVAS_BUTTON;

	texture = (ComponentImage*)my_go->FindComponent(ComponentType::CANVAS_IMAGE);
	
	//Setting uv0 &uv1
	idle.SetCoords({ 0, 220 }, { 890, 0});
	over.SetCoords ({ 895,220 }, {1786, 0 });
	pressed.SetCoords({ 1793, 220 }, {2684, 0});
	SetState(IDLE);
};



ComponentButton::~ComponentButton()
{

}

void ComponentButton::Update(float dt)
{
	//Needs improvement to not be constantly called every frame (only when moving mouse)
	
	if ( (App->input->GetMouseX() > (texture->GetImageRect().pos_x && App->input->GetMouseX()<texture->GetImageRect().width))) //check if the mouse in inside button in the X axis
	{
		if ((App->input->GetMouseY() > (texture->GetImageRect().pos_y && App->input->GetMouseY() < texture->GetImageRect().height)))//now with Y axis
		{
			SetState(OVER);
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
	{
		SetState(OVER);
	}
}

void ComponentButton::InspectorUpdate()
{

}

void ComponentButton::SetState(ButtonState status)
{
	if(texture != nullptr)
	{
		switch (status)
		{
		case IDLE:
			texture->Set_uv(idle.uv0, idle.uv1);
			break;
		case OVER:
			texture->Set_uv(over.uv0, over.uv1);
			break;
		case CLICKED:
			texture->Set_uv(pressed.uv0, pressed.uv1);
			break;
		default:
			texture->Set_uv(idle.uv0, idle.uv1);
		}
	}
	}


void State::SetCoords(float2 uv0, float2 uv1)
{
	this->uv0.x = uv0.x;
	this->uv0.y = uv0.y;
	this->uv1.x = uv1.x;
	this->uv1.y = uv1.y;
}


