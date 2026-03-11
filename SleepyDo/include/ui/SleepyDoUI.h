#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define IMGUI_DATEPICKER_YEAR_MIN 1970
#define IMGUI_DATEPICKER_YEAR_MAX 3000


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

	static DataBase* _dataBase;

	static std::vector<Task> _tasks;

	static UIType _currentUI;

	static ImVec4 _blueColor;
	static ImVec4 _blackColor;
	static ImVec4 _redColor;

	static int _deleteTaskId;

	static const int _kUIWidth{ 400 };
	static const int _kUIHeight{ 600 };

	static const int _kUIPosX{ 0 };
	static const int _kUIPosY{ 0 };

	static bool isDatePickerOpen;

	static std::string _phraseOfTheSession;
	static std::string _toDoTaskText;
	
	static const ImGuiWindowFlags _kUIWindowsFlags{ ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar };

	static void renderHeaderUI();
	static void renderDatePicker(std::string& time);
	static void eraseTask(int id);
	static void addTask(const Task& task);
	static void renderHomeUI();
	static void renderLoadMoreUI();
	static void renderToDoTasks(Task& t);
	static void renderAddToDoTasks();
	static void sortTasks();

};