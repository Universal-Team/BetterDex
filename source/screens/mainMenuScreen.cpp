	/*
*   This file is part of Universal-Manager
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

#include "screens/screenCommon.hpp"

struct ButtonPos {
    int x;
    int y;
    int w;
    int h;
	int link;
};

extern bool touching(touchPosition touch, ButtonPos button);

// Version numbers.
char betterdex_vertext[13];

void drawMainMenu(void) {
	// Initialize the Version Number.
	snprintf(betterdex_vertext, 13, "v%d.%d.%d", VERSION_MAJOR, VERSION_MINOR, VERSION_MICRO);

		set_screen(top);
		Draw_Rect(0, 0, 400, 240, BLUE);
		Draw_Rect(0, 0, 400, 25, GRAY);
		Draw_Rect(0, 215, 400, 25, GRAY);
		Gui::sprite(sprites_betterDex_idx, 0, 25);
		Draw_Text(340, 218, FONT_SIZE_18, WHITE, betterdex_vertext);

		set_screen(bottom);
		Draw_Rect(0, 0, 320, 240, BLUE);
		Draw_Rect(0, 0, 320, 25, GRAY);
		Draw_Rect(0, 215, 320, 25, GRAY);
}

void MainMenuLogic(u32 hDown, touchPosition touch) {
}