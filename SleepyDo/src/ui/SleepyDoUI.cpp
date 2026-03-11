#define _CRT_SECURE_NO_WARNINGS

#include <ranges>
#include <filesystem>
#include <chrono>
#include <format>

#include "../../vendor/imguI/imgui.h"

#include "../../vendor/imguidatepicker/ImGuiDatePicker.hpp"

#include "../../vendor/imguI/misc/cpp/imgui_stdlib.h"

#include "../../include/extensions/SessionQuote.h"

#include "../../include/ui/SleepyDoUI.h"

SleepyDoUI::UIType SleepyDoUI::_currentUI{ UIType::HOMEUI };
std::string SleepyDoUI::_phraseOfTheSession{ SessionQuote::getRandomQuote()};
std::string SleepyDoUI::_toDoTaskText{ "" };

DataBase* SleepyDoUI::_dataBase = nullptr;
std::vector<Task> SleepyDoUI::_tasks;

int SleepyDoUI::_deleteTaskId{ -1 };

ImVec4 SleepyDoUI::_blueColor{ ImColor(164, 238, 255, 255) };
ImVec4 SleepyDoUI::_redColor{ ImColor(255, 0, 0, 255) };
ImVec4 SleepyDoUI::_blackColor{ ImColor(0, 0, 0, 255) };
bool SleepyDoUI::isDatePickerOpen{ false };

void SleepyDoUI::renderHomeUI()
{
    ImGui::SetWindowFontScale(1.5f);

    centerNextItem(ImGui::CalcTextSize(SleepyDoUI::_phraseOfTheSession.c_str()).x);
    ImGui::SetCursorPosY(60.0);

    ImGui::TextColored(SleepyDoUI::_blueColor, SleepyDoUI::_phraseOfTheSession.c_str());

    ImGui::SetWindowFontScale(1.0f);

    ImVec2 toDoChildSize = ImVec2(350, 250);
    ImGui::PushStyleColor(ImGuiCol_ChildBg, SleepyDoUI::_blueColor);

    centerNextItem(toDoChildSize.x);
    ImGui::SetCursorPosY(100.0);
    ImGui::BeginChild("ToDoMenuChild", toDoChildSize, true, ImGuiWindowFlags_None);
    
    if (_deleteTaskId == -1)
    {
        for (auto& t : _tasks)
        {
            SleepyDoUI::renderToDoTasks(t);
        }
    }
    else
    {
        eraseTask(_deleteTaskId);
        _deleteTaskId = -1;
        SleepyDoUI::sortTasks();
    }


    ImGui::EndChild();
    ImGui::PopStyleColor();

    SleepyDoUI::renderAddToDoTasks();

}

void SleepyDoUI::renderAddToDoTasks()
{
    ImVec2 addToDoTasksChild{ ImVec2(350, 80) };
    centerNextItem(addToDoTasksChild.x);
    ImGui::SetCursorPosY(375);

    ImGui::BeginChild("AddToDoTasksChild", addToDoTasksChild, true, ImGuiWindowFlags_None);

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 9));
    ImGui::SetWindowFontScale(1.1f);
    ImGui::InputText("##ToDoTaskText", &SleepyDoUI::_toDoTaskText, ImGuiInputTextFlags_None);
    ImGui::SetWindowFontScale(1.0f);
    ImGui::PopStyleVar();

    

    static Task tmp;
    static std::string time = "";

    ImGui::SetCursorPosY(10);
    ImGui::SetCursorPosX(250);

    if (tmp.isImportant)
    {
        ImGui::PushStyleColor(ImGuiCol_Text, SleepyDoUI::_redColor);
    }
    else
    {
        ImGui::PushStyleColor(ImGuiCol_Text, SleepyDoUI::_blackColor);
    }

    if (ImGui::Button("!", ImVec2(20, 60)))
    {
        tmp.isImportant = !tmp.isImportant;
    }
    ImGui::PopStyleColor();
    ImGui::SetCursorPosY(10);
    ImGui::SetCursorPosX(280);


    if (ImGui::BeginPopupModal("errorPopUp", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
    {
        ImGui::Text("Your title is empty");
        if (ImGui::Button("Close"))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }



    if (ImGui::Button("+", ImVec2(60, 60)))
    {
        if (_toDoTaskText.size() == 0)
        {
            ImGui::OpenPopup("errorPopUp");
        }
        else
        {
            tmp.title = _toDoTaskText;
            tmp.expiredAt = time;

            Task task = _dataBase->addTask(tmp);

            if (task.id != -1)
            {
                addTask(task);
                SleepyDoUI::sortTasks();
            }

            SleepyDoUI::_toDoTaskText.clear();
            tmp = {};
        }
    }
    ImGui::SetCursorPosY(50);
    renderDatePicker(time);

    ImGui::EndChild();
}

void SleepyDoUI::renderToDoTasks(Task& t)
{
    std::string childId{ "ToDoChild-" + std::to_string(t.id) };
    ImGui::BeginChild(childId.c_str(), ImVec2(334, 50), true, ImGuiWindowFlags_None);

    ImGui::SetCursorPosY(16);
    ImGui::SetWindowFontScale(1.3f);
    ImGui::TextColored(SleepyDoUI::_blackColor, t.title.c_str());
    ImGui::SetWindowFontScale(1.0f);
    ImGui::SameLine();
    ImGui::SetCursorPosX(225);
    ImGui::SetCursorPosY(10);

    if (t.isImportant)
    {
        ImGui::PushStyleColor(ImGuiCol_Text, SleepyDoUI::_redColor);
    }
    else
    {
        ImGui::PushStyleColor(ImGuiCol_Text, SleepyDoUI::_blackColor);
    }

    if (ImGui::Button(("!##" + t.title + "imp").c_str(), ImVec2(40, 30)))
    {
       t.isImportant = _dataBase->setTaskImportantToggle(t.id);
       SleepyDoUI::sortTasks();
    }

    ImGui::PopStyleColor();

    ImGui::SetCursorPosX(270);
    ImGui::SetCursorPosY(10);
    ImGui::PushStyleColor(ImGuiCol_Text, SleepyDoUI::_blackColor);
    if (ImGui::Button(("X##" + t.title + "rem").c_str(), ImVec2(40, 30)))
    {
        if (_dataBase->removeTask(t.id))
        {
            _deleteTaskId = t.id;
        }
    }

    ImGui::PopStyleColor();
    ImGui::SetCursorPosY(30);
    ImGui::SetWindowFontScale(0.9f);
    ImGui::TextColored(SleepyDoUI::_blackColor, t.expiredAt.substr(0, t.expiredAt.find(' ')).c_str());
    ImGui::SetWindowFontScale(1.f);
    ImGui::EndChild();
}


void SleepyDoUI::renderAppUI()
{
    
    ImGui::SetNextWindowSize(ImVec2(SleepyDoUI::_kUIWidth, SleepyDoUI::_kUIHeight));
    ImGui::SetNextWindowPos(ImVec2(_kUIPosX, _kUIPosY), ImGuiCond_Once);

    ImGui::Begin("UI", nullptr, _kUIWindowsFlags);
        SleepyDoUI::renderHeaderUI();
        switch (SleepyDoUI::_currentUI)
        {
        default:
        case SleepyDoUI::UIType::HOMEUI:
            SleepyDoUI::renderHomeUI();
            break;
        case SleepyDoUI::UIType::LOADMOREUI:
            SleepyDoUI::renderLoadMoreUI();
            break;
        }
    ImGui::End();
}

void SleepyDoUI::renderDatePicker(std::string& time)
{
    static tm t{};

    static bool initialized = false;
    if (!initialized)
    {
        std::time_t now = std::time(nullptr);
        t = *std::localtime(&now);
        initialized = true;
    }
    ImGui::DatePicker("##Date", t);

    time = ImGui::TimePointToLongString(t);
    
}

void SleepyDoUI::renderHeaderUI()
{
    if (ImGui::BeginTable("MyTable", 2, ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_NoPadOuterX))
    {
        ImGui::TableSetupColumn("Title", ImGuiTableColumnFlags_WidthFixed, 185.0f);
        ImGui::TableSetupColumn("Time", ImGuiTableColumnFlags_WidthFixed, 185.0f);

        const float rowHeight{ 22.0f };

        ImGui::TableNextRow(ImGuiTableRowFlags_None, rowHeight);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.1f, 0.1f, 0.1f, 0.5f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.2f, 0.2f, 0.8f));
        ImGui::PushStyleColor(ImGuiCol_Text, SleepyDoUI::_blueColor);

        ImVec2 textSize{ -FLT_MIN, rowHeight };

        ImGui::TableNextColumn();
        ImGui::SetWindowFontScale(1.3f);
        ImGui::AlignTextToFramePadding();
        ImGui::Text("SleepyDo", textSize);
        ImGui::SetWindowFontScale(1.0f);

        ImGui::TableNextColumn();
        ImGui::AlignTextToFramePadding();
        auto local = std::chrono::zoned_time{ std::chrono::current_zone(), std::chrono::system_clock::now() };
        std::string timeStr = std::format("{:%Y-%m-%d}", local);
        ImGui::Text(timeStr.c_str(), textSize);

        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();

        ImGui::EndTable();
    }

    ImGui::Separator();
}

void SleepyDoUI::renderLoadMoreUI()
{

}

//DB SECTION

void SleepyDoUI::setDb(DataBase* db)
{
    SleepyDoUI::_dataBase = db;
    _tasks = _dataBase->getTasks();
    SleepyDoUI::sortTasks();
}

void SleepyDoUI::sortTasks()
{
    std::stable_sort(_tasks.begin(), _tasks.end(),
        [](const Task& a, const Task& b)
        {
            if (a.isImportant != b.isImportant)
            {
                return a.isImportant > b.isImportant;
            }
            return a.id > b.id;
        });
}

void SleepyDoUI::eraseTask(int id)
{
    for (auto it = _tasks.begin(); it != _tasks.end(); ++it)
    {
        if (it->id == id)
        {
            _tasks.erase(it);
            break;
        }
    }
}

void SleepyDoUI::addTask(const Task& task)
{
    _tasks.insert(_tasks.begin(), task);
}

