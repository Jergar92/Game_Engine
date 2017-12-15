#include "ComponentInputText.h"
#include "ComponentText.h"




ComponentInputText::ComponentInputText(GameObject * my_go):ComponentInteractive(my_go)
{
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
