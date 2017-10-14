#include "Application.h"
#include "Globals.h"
#include"ModuleConsole.h"
#include"p2Defs.h"




ModuleConsole::ModuleConsole(bool start_enabled) 
{
	name = "Console";
	ClearLog();
	memset(inputBuf, 0, sizeof(inputBuf));
	HistoryPos = -1;
}


ModuleConsole::~ModuleConsole()
{
}

bool ModuleConsole::Start()
{
	bool ret = true;
	LOG("Engine Console Ready");
	return ret;
}


bool ModuleConsole::CleanUp()
{
	bool ret = true;
	ClearLog();

	for (int i = 0; i < History.Size; i++)
		free(History[i]);

	return ret;
}


void ModuleConsole::AddLog(const char * fmt, ...)
{
	char buffer[1024];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buffer, IM_ARRAYSIZE(buffer), fmt, args);
	buffer[IM_ARRAYSIZE(buffer) - 1] = 0;
	va_end(args);
	Items.push_back(strdup(buffer));
	ScrollToBottom = true;

}

void ModuleConsole::ClearLog()
{
	for (int i = 0; i < Items.Size; i++)
		free(Items[i]);

	Items.clear();
	ScrollToBottom = true;

}
void ModuleConsole::Draw(const char * tittle)
{
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_ShowBorders;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	ImGui::SetNextWindowSize(ImVec2(550, 600), ImGuiCond_Once);

	ImGui::Begin(tittle, &show_app_console,window_flags);
	ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);


	ImGui::TextWrapped("Game Engine Console, in this console you can display all information do it for LOG");

	if (ImGui::SmallButton("Clear")) { ClearLog(); } ImGui::SameLine();
	if (ImGui::SmallButton("Scroll to bottom")) ScrollToBottom = true;
	ImGui::Separator();

	ImGui::BeginChild("ScrollingRegion", ImVec2(0, -ImGui::GetItemsLineHeightWithSpacing()), false, ImGuiWindowFlags_HorizontalScrollbar);
	if (ImGui::BeginPopupContextWindow())
	{
		if (ImGui::Selectable("Clear")) ClearLog();
		ImGui::EndPopup();
	}

	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
	for (int i = 0; i < Items.Size; i++)
	{
		const char* item = Items[i];

		ImVec4 col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // A better implementation may store a type per-item. For the sample let's just parse the text.
		if (strstr(item, "[error]")) col = ImColor(1.0f, 0.4f, 0.4f, 1.0f);
		else if (strncmp(item, "# ", 2) == 0) col = ImColor(1.0f, 0.78f, 0.58f, 1.0f);
		ImGui::PushStyleColor(ImGuiCol_Text, col);
		ImGui::TextUnformatted(item);
		ImGui::PopStyleColor();
	}
	if (ScrollToBottom)
		ImGui::SetScrollHere();
	ScrollToBottom = false;
	ImGui::PopStyleVar();
	ImGui::EndChild();
	ImGui::Separator();

	ImGui::End();
}


void ModuleConsole::ActiveConsole()
{
   show_app_console = !show_app_console;
}

bool ModuleConsole::GetShowConsole()
{
	return show_app_console;
}


