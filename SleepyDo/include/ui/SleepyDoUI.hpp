#pragma once

#include <iostream>
#include <filesystem>

#include "../../vendor/imguI/imgui.h"



class SleepyDoUI
{
public:
	SleepyDoUI() = delete;
	~SleepyDoUI() = delete;

	static void renderAppUI();
private:
	static const int kUIWidth{ 400 };
	static const int kUIHeight{ 600 };

	static const int kUIPosX{ 0 };
	static const int kUIPosY{ 0 };

	static void renderHeaderUI();

	static const ImGuiWindowFlags kUIWindowsFlags{ ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar };
};