#pragma once

#include "../../include/extensions/UIExtension.hpp"

#include "../../vendor/imguI/imgui.h"

#include "../../vendor/imguI/misc/cpp/imgui_stdlib.h"


#include <iostream>
#include <filesystem>




class SleepyDoUI
{
public:
	SleepyDoUI() = delete;
	~SleepyDoUI() = delete;

	static void renderAppUI();
private:
	enum class UIType
	{
		HOMEUI = 0,
		LOADMOREUI = 1,
	};

	static UIType currentUI;

	static ImVec4 blueColor;
	static ImVec4 blackColor;

	static const int kUIWidth{ 400 };
	static const int kUIHeight{ 600 };

	static const int kUIPosX{ 0 };
	static const int kUIPosY{ 0 };

	static std::string phraseOfTheDay;

	static std::string toDoTaskText;

	static void renderHeaderUI();

	static void renderHomeUI();
	static void renderLoadMoreUI();

	static void renderToDoTasks(std::string id);

	static void renderAddToDoTasks();

	static const ImGuiWindowFlags kUIWindowsFlags{ ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar };
};