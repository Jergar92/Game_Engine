#pragma once
class UI_Windows
{
public:
	UI_Windows();
	~UI_Windows();


	virtual bool Draw();
	bool IsActive()const;
	void ChangeActive();

public:
	bool active_draw = true;
};
