#pragma once

#include "../../include/extensions/UIExtension.h"
#include "../../include/database/DataBase.h"

#include <iostream>
#include <string>

class SleepyDoUI
{
public:
	SleepyDoUI() = delete;
	~SleepyDoUI() = delete;

	static void renderAppUI();

	static void setDb(DataBase* db);
private:
	enum class UIType
	{
		HOMEUI = 0,
		LOADMOREUI = 1,
	};

	static DataBase* dataBase;

	static UIType _currentUI;

	static ImVec4 _blueColor;
	static ImVec4 _blackColor;

	static const int _kUIWidth{ 400 };
	static const int _kUIHeight{ 600 };

	static const int _kUIPosX{ 0 };
	static const int _kUIPosY{ 0 };

	static std::string _phraseOfTheDay;

	static std::string _toDoTaskText;
	
	static const ImGuiWindowFlags _kUIWindowsFlags{ ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar };

	static void renderHeaderUI();

	static void renderHomeUI();
	static void renderLoadMoreUI();

	static void renderToDoTasks(const std::string& title);

	static void renderAddToDoTasks();

};