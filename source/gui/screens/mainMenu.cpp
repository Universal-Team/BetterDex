	/*
*   This file is part of BetterDex
*   Copyright (C) 2019 VoltZ, Epicpkmn11, Flame, RocketRobz, TotallyNotGuy
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
*       * Requiring preservation of specified reasonable legal notices or
*         author attributions in that material or in the Appropriate Legal
*         Notices displayed by works containing it.
*       * Prohibiting misrepresentation of the origin of that material,
*         or requiring that modified versions of such material be marked in
*         reasonable ways as different from the original version.
*/

#include "gui/screens/mainMenu.hpp"
#include "gui/screens/screenCommon.hpp"

extern bool exiting;
extern int fadealpha;
extern bool fadein;

void MainMenu::Draw(void) const
{
		Gui::ScreenDraw(top);
		Gui::Draw_Rect(0, 0, 400, 240, BLUE);
		Gui::Draw_Rect(0, 0, 400, 25, GRAY);
		Gui::Draw_Rect(0, 215, 400, 25, GRAY);
		Gui::sprite(0, sprites_betterDex_idx, 0, 25);
		Gui::DrawString(395-Gui::GetStringWidth(FONT_SIZE_18, V_STRING), 216, FONT_SIZE_18, WHITE, V_STRING, 400);
		if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(0, 0, 0, fadealpha)); // Fade in/out effect

		Gui::ScreenDraw(bottom);
		Gui::Draw_Rect(0, 0, 320, 240, BLUE);
		Gui::Draw_Rect(0, 0, 320, 25, GRAY);
		Gui::Draw_Rect(0, 215, 320, 25, GRAY);
		if (fadealpha > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(0, 0, 0, fadealpha)); // Fade in/out effect
}

void MainMenu::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_START) {
		exiting = true;
	}
}