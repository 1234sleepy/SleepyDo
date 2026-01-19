#include "../../include/ui/SleepyDoUI.hpp"



void SleepyDoUI::renderAppUI()
{
    ImGui::SetNextWindowSize(ImVec2(SleepyDoUI::kUIWidth, SleepyDoUI::kUIHeight));
    ImGui::SetNextWindowPos(ImVec2(kUIPosX, kUIPosY), ImGuiCond_Once);

    ImGui::Begin("UI", nullptr, kUIWindowsFlags);
    {
        SleepyDoUI::renderHeaderUI();
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

        const float rowHeight = 22.0f;

        ImGui::TableNextRow(ImGuiTableRowFlags_None, rowHeight);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.1f, 0.1f, 0.1f, 0.5f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.2f, 0.2f, 0.8f));
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(164, 238, 255, 255)));

        ImGui::TableNextColumn();
        ImGui::SetWindowFontScale(1.3f);
        ImGui::AlignTextToFramePadding();
        if (ImGui::Button("SleepyDo", ImVec2{ -FLT_MIN, rowHeight }))
        {

        }
        ImGui::SetWindowFontScale(1.0f);

        ImGui::TableNextColumn();
        ImGui::AlignTextToFramePadding();
        if (ImGui::Button("Data/Time", ImVec2{ -FLT_MIN, rowHeight }))
        {

        }

        ImGui::TableNextColumn();
        ImGui::AlignTextToFramePadding();
        if (ImGui::Button("Imp", ImVec2{ -FLT_MIN, rowHeight }))
        {

        }

        ImGui::TableNextColumn();
        ImGui::AlignTextToFramePadding();
        if (ImGui::Button("Exp", ImVec2{ -FLT_MIN, rowHeight }))
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


