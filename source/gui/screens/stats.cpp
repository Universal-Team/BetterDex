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

#include "gui/screens/screenCommon.hpp"
#include "gui/screens/stats.hpp"

extern int pokedexNumber;
extern std::vector<std::string> g_speciesDatabase;
extern std::string speciesName;
extern std::string pokedex;

void StatsScreen::Draw(void) const
{
		Gui::ScreenDraw(top);
		Gui::Draw_Rect(0, 0, 400, 240, BLUE);
		Gui::Draw_Rect(0, 0, 400, 25, GRAY);
		Gui::Draw_Rect(0, 215, 400, 25, GRAY);

		Gui::DrawString(100, 0, 0.7f, WHITE, "BetterDex -> Stats Screen.", 400);

		// Draw Pokémon inclusive name.
		DrawPKMSprite(6, 10, 40);
		Gui::Draw_Rect(10, 140, 100, 25, GRAY);
		Gui::DrawString(20, 142, 0.7f, WHITE, "Charizard", 400);

		// Draw Stats Text.
		Gui::DrawString(200, 40, 0.7f, WHITE, "HP", 400);
		Gui::DrawString(200, 70, 0.7f, WHITE, "Attack", 400);
		Gui::DrawString(200, 100, 0.7f, WHITE, "Defense", 400);
		Gui::DrawString(200, 130, 0.7f, WHITE, "Sp. Attack", 400);
		Gui::DrawString(200, 160, 0.7f, WHITE, "Sp. Defense", 400);
		Gui::DrawString(200, 190, 0.7f, WHITE, "Initiative", 400);

		// Stats Boxes.
		Gui::Draw_Rect(320, 35, 50, 25, GRAY);
		Gui::Draw_Rect(320, 65, 50, 25, GRAY);
		Gui::Draw_Rect(320, 95, 50, 25, GRAY);
		Gui::Draw_Rect(320, 125, 50, 25, GRAY);
		Gui::Draw_Rect(320, 155, 50, 25, GRAY);
		Gui::Draw_Rect(320, 185, 50, 25, GRAY);

		// Draw Stats.
		Gui::DrawString(330, 40, 0.5f, WHITE, "78", 400);
		Gui::DrawString(330, 70, 0.5f, WHITE, "84", 400);
		Gui::DrawString(330, 100, 0.5f, WHITE, "78", 400);
		Gui::DrawString(330, 130, 0.5f, WHITE, "109", 400);
		Gui::DrawString(330, 160, 0.5f, WHITE, "85", 400);
		Gui::DrawString(330, 190, 0.5f, WHITE, "100", 400);


		Gui::ScreenDraw(bottom);
		Gui::Draw_Rect(0, 0, 320, 240, BLUE);
		Gui::Draw_Rect(0, 0, 320, 25, GRAY);
		Gui::Draw_Rect(0, 215, 320, 25, GRAY);
}

void StatsScreen::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_B) {
		Gui::screenBack();
		return;
	}
}