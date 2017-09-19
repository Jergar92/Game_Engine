#include "Application.h"
#include "Globals.h"
#include"ModuleConsole.h"
#include"p2Defs.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_sdl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

ModuleConsole::ModuleConsole(Application * app, bool start_enabled) :Module(app, start_enabled)
{
	ClearLog();
	memset(inputBuf, 0, sizeof(inputBuf));
	HistoryPos = -1;
	Commands.push_back("HELP");
	Commands.push_back("HISTORY");
	Commands.push_back("CLEAR");
	Commands.push_back("CLASSIFY");  // "classify" is here to provide an example of "C"+[tab] completing to "CL" and displaying matches.
	AddLog("Welcome to ImGui!");
}


ModuleConsole::~ModuleConsole()
{		
}

bool ModuleConsole::Start()
{
	bool ret = true;


	return ret;
}

update_status ModuleConsole::PreUpdate(float dt)
{

	return UPDATE_CONTINUE;
}

update_status ModuleConsole::Update(float dt)
{
	
	return UPDATE_CONTINUE;
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

void ModuleConsole::Draw(const char * tittle, bool * p_open)
{

	ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin(tittle, p_open))
	{
		ImGui::End();
		return;
	}

	ImGui::TextWrapped("This example implements a console with basic coloring, completion and history. A more elaborate implementation may want to store entries along with extra data such as timestamp, emitter, etc.");
	ImGui::TextWrapped("Enter 'HELP' for help, press TAB to use text completion.");

	// TODO: display items starting from the bottom

	if (ImGui::SmallButton("Add Dummy Text")) { AddLog("%d some text", Items.Size); AddLog("some more text"); AddLog("display very important message here!"); } ImGui::SameLine();
	if (ImGui::SmallButton("Add Dummy Error")) { AddLog("[error] something went wrong"); } ImGui::SameLine();
	if (ImGui::SmallButton("Clear")) { ClearLog(); } ImGui::SameLine();
	bool copy_to_clipboard = ImGui::SmallButton("Copy"); ImGui::SameLine();
	if (ImGui::SmallButton("Scroll to bottom")) ScrollToBottom = true;
	//static float t = 0.0f; if (ImGui::GetTime() - t > 0.02f) { t = ImGui::GetTime(); AddLog("Spam %f", t); }

	ImGui::Separator();

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
	static ImGuiTextFilter filter;
	filter.Draw("Filter (\"incl,-excl\") (\"error\")", 180);
	ImGui::PopStyleVar();
	ImGui::Separator();

	ImGui::BeginChild("ScrollingRegion", ImVec2(0, -ImGui::GetItemsLineHeightWithSpacing()), false, ImGuiWindowFlags_HorizontalScrollbar);
	if (ImGui::BeginPopupContextWindow())
	{
		if (ImGui::Selectable("Clear")) ClearLog();
		ImGui::EndPopup();
	}
}

void ModuleConsole::InputText()
{
	if (ImGui::InputText("Input", inputBuf, IM_ARRAYSIZE(inputBuf), ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory, &TextEditCallbackStub, (void*)this))
	{
		char* input_end = inputBuf + strlen(inputBuf);
		while (input_end > inputBuf && input_end[-1] == ' ') { input_end--; } *input_end = 0;
		if (inputBuf[0])
			ExecCommand(inputBuf);
		strcpy(inputBuf, "");
	}
}

void ModuleConsole::ExecCommand(const char * command_line)
{
	HistoryPos = -1;
	for (int i = History.Size - 1; i >= 0; i--)
		if (stricmp(History[i], command_line) == 0)
		{
			free(History[i]);
			History.erase(History.begin() + i);
			break;
		}
	History.push_back(strdup(command_line));

	// Process command
	if (stricmp(command_line, "CLEAR") == 0)
	{
		ClearLog();
	}
	else if (stricmp(command_line, "HELP") == 0)
	{
		AddLog("Commands:");
		for (int i = 0; i < Commands.Size; i++)
			AddLog("- %s", Commands[i]);
	}
	else if (stricmp(command_line, "HISTORY") == 0)
	{
		int first = History.Size - 10;
		for (int i = first > 0 ? first : 0; i < History.Size; i++)
			AddLog("%3d: %s\n", i, History[i]);
	}
	else
	{
		AddLog("Unknown command: '%s'\n", command_line);
	}
}

int ModuleConsole::TextEditCallback(ImGuiTextEditCallbackData * data)
{
	switch (data->EventFlag)
	{
	case ImGuiInputTextFlags_CallbackCompletion:
	{
		// Example of TEXT COMPLETION

		// Locate beginning of current word
		const char* word_end = data->Buf + data->CursorPos;
		const char* word_start = word_end;
		while (word_start > data->Buf)
		{
			const char c = word_start[-1];
			if (c == ' ' || c == '\t' || c == ',' || c == ';')
				break;
			word_start--;
		}

		// Build a list of candidates
		ImVector<const char*> candidates;
		for (int i = 0; i < Commands.Size; i++)
			if (strnicmp(Commands[i], word_start, (int)(word_end - word_start)) == 0)
				candidates.push_back(Commands[i]);

		if (candidates.Size == 0)
		{
			// No match
			AddLog("No match for \"%.*s\"!\n", (int)(word_end - word_start), word_start);
		}
		else if (candidates.Size == 1)
		{
			// Single match. Delete the beginning of the word and replace it entirely so we've got nice casing
			data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
			data->InsertChars(data->CursorPos, candidates[0]);
			data->InsertChars(data->CursorPos, " ");
		}
		else
		{
			// Multiple matches. Complete as much as we can, so inputing "C" will complete to "CL" and display "CLEAR" and "CLASSIFY"
			int match_len = (int)(word_end - word_start);
			for (;;)
			{
				int c = 0;
				bool all_candidates_matches = true;
				for (int i = 0; i < candidates.Size && all_candidates_matches; i++)
					if (i == 0)
						c = toupper(candidates[i][match_len]);
					else if (c == 0 || c != toupper(candidates[i][match_len]))
						all_candidates_matches = false;
				if (!all_candidates_matches)
					break;
				match_len++;
			}

			if (match_len > 0)
			{
				data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
				data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
			}

			// List matches
			AddLog("Possible matches:\n");
			for (int i = 0; i < candidates.Size; i++)
				AddLog("- %s\n", candidates[i]);
		}

		break;
	}
	case ImGuiInputTextFlags_CallbackHistory:
	{
		// Example of HISTORY
		const int prev_history_pos = HistoryPos;
		if (data->EventKey == ImGuiKey_UpArrow)
		{
			if (HistoryPos == -1)
				HistoryPos = History.Size - 1;
			else if (HistoryPos > 0)
				HistoryPos--;
		}
		else if (data->EventKey == ImGuiKey_DownArrow)
		{
			if (HistoryPos != -1)
				if (++HistoryPos >= History.Size)
					HistoryPos = -1;
		}

		// A better implementation would preserve the data on the current input line along with cursor position.
		if (prev_history_pos != HistoryPos)
		{
			data->CursorPos = data->SelectionStart = data->SelectionEnd = data->BufTextLen = (int)snprintf(data->Buf, (size_t)data->BufSize, "%s", (HistoryPos >= 0) ? History[HistoryPos] : "");
			data->BufDirty = true;
		}
	}
	}
	return 0;
}



int ModuleConsole::TextEditCallbackStub(ImGuiTextEditCallbackData * data)
{
	ModuleConsole* console = (ModuleConsole*)data->UserData;
	return console->TextEditCallbackStub(data);
}

void ModuleConsole::ClearLog()
{
	for (int i = 0; i < Items.Size; i++)
		free(Items[i]);

	Items.clear();
	ScrollToBottom = true;

}




