#pragma once
#include "Globals.h"
#include "Application.h"
#include "ModuleEditorWindows.h"
void log(const char* format, ...)
{
	static char tmp_string[4096];
	static char tmp_string2[4096];
	static va_list  ap;

	// Construct the string from variable arguments
	va_start(ap, format);
	vsprintf_s(tmp_string, 4096, format, ap);
	va_end(ap);
	sprintf_s(tmp_string2, 4096, tmp_string);
	if(App != nullptr && App->editor_window != nullptr)
	App->editor_window->AddLog(tmp_string2);

	
	
}

