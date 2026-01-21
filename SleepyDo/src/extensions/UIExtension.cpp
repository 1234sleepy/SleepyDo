#include "../../include/extensions/UIExtension.hpp"

void centerNextItem(float itemWidth)
{
    float availSize = ImGui::GetContentRegionAvail().x;
    float cursorX = ImGui::GetCursorPosX();
    ImGui::SetCursorPosX(cursorX + (availSize - itemWidth) * 0.5f);
}