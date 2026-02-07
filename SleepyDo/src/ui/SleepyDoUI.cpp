#include "../../include/ui/SleepyDoUI.h"

#include "../../vendor/imguI/imgui.h"

#include "../../vendor/imguI/misc/cpp/imgui_stdlib.h"

#include <iostream>
#include <filesystem>

SleepyDoUI::UIType SleepyDoUI::_currentUI{ UIType::HOMEUI };
std::string SleepyDoUI::_phraseOfTheDay{ "Loading..." };
std::string SleepyDoUI::_toDoTaskText{ "" };

ImVec4 SleepyDoUI::_blueColor{ ImColor(164, 238, 255, 255) };
ImVec4 SleepyDoUI::_blackColor{ ImColor(0, 0, 0, 255) };

void SleepyDoUI::renderHomeUI()
{
    ImGui::SetWindowFontScale(1.5f);

    centerNextItem(ImGui::CalcTextSize(SleepyDoUI::_phraseOfTheDay.c_str()).x);
    ImGui::SetCursorPosY(60.0);

    ImGui::TextColored(SleepyDoUI::_blueColor, SleepyDoUI::_phraseOfTheDay.c_str());

    ImGui::SetWindowFontScale(1.0f);

    ImVec2 toDoChildSize = ImVec2(350, 250);
    ImGui::PushStyleColor(ImGuiCol_ChildBg, SleepyDoUI::_blueColor);

    centerNextItem(toDoChildSize.x);
    ImGui::SetCursorPosY(100.0);
    ImGui::BeginChild("ToDoMenuChild", toDoChildSize, true, ImGuiWindowFlags_None);
    
    int childPosY{ 10 };

    for (int i{ 0 }; i < 4; i++) 
    {
        ImGui::SetCursorPosY(childPosY);
        SleepyDoUI::renderToDoTasks(std::to_string(i));
        childPosY += 60;
    }

    ImGui::EndChild();
    ImGui::PopStyleColor();

    SleepyDoUI::renderAddToDoTasks();

}

void SleepyDoUI::renderAddToDoTasks()
{
    ImVec2 addToDoTasksChild{ ImVec2(350, 50) };
    centerNextItem(addToDoTasksChild.x);
    ImGui::SetCursorPosY(375);


    ImGui::BeginChild("AddToDoTasksChild", addToDoTasksChild, true, ImGuiWindowFlags_None);


    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 9));
    ImGui::SetWindowFontScale(1.1f);
    ImGui::InputText("##ToDoTaskText", &SleepyDoUI::_toDoTaskText, ImGuiInputTextFlags_None);
    ImGui::SetWindowFontScale(1.0f);
    ImGui::PopStyleVar();

    ImGui::SetCursorPosX(310);
    ImGui::SetCursorPosY(10);
    if (ImGui::Button("+", ImVec2(30, 30)))
    {
        //Do something

        SleepyDoUI::_toDoTaskText.clear();
    }


    ImGui::EndChild();
}


void SleepyDoUI::renderLoadMoreUI()
{

}

void SleepyDoUI::renderToDoTasks(std::string id)
{
    std::string childId{ "ToDoChild-" + id };
    ImGui::BeginChild(childId.c_str(), ImVec2(334, 50), true, ImGuiWindowFlags_None);

    ImGui::SetCursorPosY(16);
    ImGui::SetWindowFontScale(1.3f);
    ImGui::TextColored(SleepyDoUI::_blackColor, "dsafdsafdassf");
    ImGui::SetWindowFontScale(1.0f);
    ImGui::SameLine();
    ImGui::SetCursorPosX(290);
    ImGui::SetCursorPosY(10);

    ImGui::PushStyleColor(ImGuiCol_Text, SleepyDoUI::_blackColor);
    std::string buttonId{ "V-" + id };
    if (ImGui::Button(buttonId.c_str(), ImVec2(40, 30)))
    {

    }

    ImGui::PopStyleColor();
    ImGui::EndChild();
}


void SleepyDoUI::renderAppUI()
{
    ImGui::SetNextWindowSize(ImVec2(SleepyDoUI::_kUIWidth, SleepyDoUI::_kUIHeight));
    ImGui::SetNextWindowPos(ImVec2(_kUIPosX, _kUIPosY), ImGuiCond_Once);

    ImGui::Begin("UI", nullptr, _kUIWindowsFlags);
    {
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

    }
    ImGui::End();
}


void SleepyDoUI::renderHeaderUI()
{
    if (ImGui::BeginTable("MyTable", 4, ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_NoPadOuterX))
    {
        ImGui::TableSetupColumn("Title", ImGuiTableColumnFlags_WidthFixed, 100.0f);
        ImGui::TableSetupColumn("Time", ImGuiTableColumnFlags_WidthFixed, 140.0f);
        ImGui::TableSetupColumn("Imp", ImGuiTableColumnFlags_WidthFixed, 65.0f);
        ImGui::TableSetupColumn("Exp", ImGuiTableColumnFlags_WidthFixed, 65.0f);

        const float rowHeight{ 22.0f };

        ImGui::TableNextRow(ImGuiTableRowFlags_None, rowHeight);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.1f, 0.1f, 0.1f, 0.5f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.2f, 0.2f, 0.8f));
        ImGui::PushStyleColor(ImGuiCol_Text, SleepyDoUI::_blueColor);

        ImVec2 btnSize{ -FLT_MIN, rowHeight };

        ImGui::TableNextColumn();
        ImGui::SetWindowFontScale(1.3f);
        ImGui::AlignTextToFramePadding();
        if (ImGui::Button("SleepyDo", btnSize))
        {

        }
        ImGui::SetWindowFontScale(1.0f);

        ImGui::TableNextColumn();
        ImGui::AlignTextToFramePadding();
        if (ImGui::Button("Data/Time", btnSize))
        {

        }

        ImGui::TableNextColumn();
        ImGui::AlignTextToFramePadding();
        if (ImGui::Button("Imp", btnSize))
        {

        }

        ImGui::TableNextColumn();
        ImGui::AlignTextToFramePadding();
        if (ImGui::Button("Exp", btnSize))
        {

        }

        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();

        ImGui::EndTable();
    }

    ImGui::Separator();
}

