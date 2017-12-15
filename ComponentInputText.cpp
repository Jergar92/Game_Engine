#include "ComponentInputText.h"
#include "ComponentText.h"
#include "GameObject.h"
#include "ComponentCanvas.h"



ComponentInputText::ComponentInputText(GameObject * my_go):ComponentInteractive(my_go)
{
	component_name = "Input Text";
	type = CANVAS_INPUT_TEXT;
	canvas = FindMyCanvas();
	canvas->interactive_array.push_back((ComponentInteractive*)this);
	my_text = (ComponentText*)my_go->FindComponent(ComponentType::CANVAS_TEXT);
	MoveToEnd();
	
}

ComponentInputText::~ComponentInputText()
{
}

void ComponentInputText::AddText(const char * str)
{
	AddText(str, cursor_pos);
}

void ComponentInputText::AddText(const char * str, uint position)
{
	my_text->text_str.insert(position, str);
}


bool ComponentInputText::EraseText(uint position)
{
	//check
	if (my_text->text_str.length() == 0) 
		return false;

	my_text->text_str.erase(position, 1);

	//check if still have text
	if (my_text->text_str.length() > 0)
		return true;
}

void ComponentInputText::MoveRight()
{
	if (cursor_pos < my_text->text_str.length())
	{
		cursor_pos++;
	}
}

void ComponentInputText::MoveLeft()
{
	if (cursor_pos >0)
	{
		cursor_pos--;
	}
}

void ComponentInputText::MoveToEnd()
{
	cursor_pos = my_text->text_str.length();
}

void ComponentInputText::MoveToStart()
{
	cursor_pos =0;

}

void ComponentInputText::CallUpdate()
{
	my_text->UpdateText();
}

void ComponentInputText::Idle()
{
}

void ComponentInputText::Hover()
{
}

void ComponentInputText::Down()
{
}

uint ComponentInputText::GetCurrentPos() const
{
	return cursor_pos;
}

void ComponentInputText::ReduceCursorPos()
{
	cursor_pos--;
}
