#include "../../include/extensions/UIExtension.h"

#include "../../vendor/imguI/imgui.h"

void centerNextItem(float itemWidth)
{
    float availSize = ImGui::GetContentRegionAvail().x;
    float cursorX = ImGui::GetCursorPosX();
    ImGui::SetCursorPosX(cursorX + (availSize - itemWidth) * 0.5f);
}