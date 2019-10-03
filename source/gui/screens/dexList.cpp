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

#include "gui/screens/dexList.hpp"

#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

extern C2D_SpriteSheet spritesheet_pkm;
extern std::vector<std::string> g_speciesDatabase;
std::string speciesName;
std::string pokedex;

extern bool touching(touchPosition touch, Structs::ButtonPos button);

void DexList::DrawSprite(size_t imgindex, int x, int y) const
{
	C2D_Image img = C2D_SpriteSheetGetImage(spritesheet_pkm, imgindex);
	C2D_DrawImageAt(img, x, y, 0.5f, NULL, 2.5, 2.5);
}

void DexList::DisplayList(void) const {
	Gui::ScreenDraw(top);
	Gui::Draw_Rect(0, 0, 400, 240, BLUE);
	Gui::Draw_Rect(0, 0, 400, 25, GRAY);
	Gui::Draw_Rect(0, 215, 400, 25, GRAY);

	for (int i = 1; i < 808; i++) {
		if (pokedexNumber == i) {
			DrawSprite(i, 160, 80);
			speciesName = g_speciesDatabase[i];
			pokedex = std::to_string(i);
		}
	}


		std::string pokedexString = "Pokedex Number: ";
		std::string name = "Species: ";
		name += speciesName;
		pokedexString += pokedex;
		Gui::DrawString(100, 0, 0.7f, WHITE, pokedexString, 400);
		Gui::DrawString(100, 160, 0.7f, WHITE, name, 400);
		Gui::DrawString(40, 215, 0.7f, WHITE, "BetterDex - Made by Universal-Team.", 400);

		Gui::ScreenDraw(bottom);
		Gui::Draw_Rect(0, 0, 320, 240, BLUE);
		Gui::Draw_Rect(0, 0, 320, 25, GRAY);
		Gui::Draw_Rect(0, 215, 320, 25, GRAY);
		Gui::sprite(0, sprites_search_idx, 290, 3);
}


void DexList::Draw(void) const
{
	DisplayList();
}

int getNumber(uint maxLength, int maxNum)
{
	int dex;
	C3D_FrameEnd(0);
	static SwkbdState state;
	static bool first = true;
	if (first)
	{
		swkbdInit(&state, SWKBD_TYPE_NUMPAD, 2, maxLength);
		first = false;
	}
	swkbdSetFeatures(&state, SWKBD_FIXED_WIDTH);
	swkbdSetValidation(&state, SWKBD_NOTBLANK_NOTEMPTY, 0, 0);
	char input[maxLength + 1]	= {0};
	SwkbdButton ret = swkbdInputText(&state, input, sizeof(input));
	input[maxLength]		= '\0';
	if (ret == SWKBD_BUTTON_CONFIRM)
	{
		dex = (int)std::min(std::stoi(input), maxNum);
		first = true;
		return dex;
	} else {
		first = true;
		return 0;
	}
}

void DexList::Search(void) {
	pokedexNumber = getNumber(3, 807);
}


void DexList::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	gspWaitForVBlank();
	if (hDown & KEY_DOWN) {
		scrollIndex++;
		gspWaitForVBlank();
		pokedexNumber++;
		if (pokedexNumber > 807)	pokedexNumber = 1;
	} else if (hDown & KEY_UP) {
		pokedexNumber--;
		if (pokedexNumber < 1)	pokedexNumber = 807;

	} else if (hDown & KEY_RIGHT) {
		pokedexNumber += 10;
		if (pokedexNumber > 796)	pokedexNumber = 1;

	} else if (hDown & KEY_LEFT) {
		pokedexNumber -= 10;
		if (pokedexNumber < 12)	pokedexNumber = 807;


	} else if (hDown & KEY_B) {
		Gui::screenBack();
		return;
	} else if (hDown & KEY_START) {
		Search();
	}

	if (hDown & KEY_TOUCH && touching(touch, search[0])) {
		Search();
	}
}