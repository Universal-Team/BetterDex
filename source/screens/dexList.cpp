/*
*   This file is part of BetterDex
*   Copyright (C) 2019-2020 Universal-Team
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

#include "dexList.hpp"
#include "mainMenu.hpp"
#include "statsScreen.hpp"

#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

extern std::vector<std::string> g_speciesDatabase;
std::string speciesName;
std::string pokedex;
int pokedexNumber = 1;

extern bool touching(touchPosition touch, Structs::ButtonPos button);

void DexList::DisplayList(void) const {
	GFX::DrawTop();

	// Draw the Pokémon Sprite and get the name of it inclusive Pokédex Number.
	for (int i = 1; i < 808; i++) {
		if (pokedexNumber == i) {
			GFX::DrawPKMSprite(i, 160, 80);
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
	Gui::DrawStringCentered(0, 215, 0.7f, WHITE, "BetterDex - Made by Universal-Team.", 400);

	GFX::DrawBottom();
	GFX::DrawSprite(sprites_search_idx, 290, 3);
}


void DexList::Draw(void) const {
	DisplayList();
}

int getNumber(uint maxLength, int maxNum) {
	int dex;
	C3D_FrameEnd(0);
	static SwkbdState state;
	static bool first = true;

	if (first) {
		swkbdInit(&state, SWKBD_TYPE_NUMPAD, 2, maxLength);
		first = false;
	}

	swkbdSetFeatures(&state, SWKBD_FIXED_WIDTH);
	swkbdSetValidation(&state, SWKBD_NOTBLANK_NOTEMPTY, 0, 0);
	char input[maxLength + 1]	= {0};
	SwkbdButton ret = swkbdInputText(&state, input, sizeof(input));
	input[maxLength]		= '\0';

	if (ret == SWKBD_BUTTON_CONFIRM) {
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
	if (hDown & KEY_DOWN) {
		this->scrollIndex++;
		pokedexNumber++;
		if (pokedexNumber > 807) pokedexNumber = 1;
	}
	
	if (hDown & KEY_UP) {
		pokedexNumber--;
		if (pokedexNumber < 1) pokedexNumber = 807;
	}
	
	if (hDown & KEY_RIGHT) {
		pokedexNumber += 10;
		if (pokedexNumber > 796)	pokedexNumber = 1;
	}
	
	if (hDown & KEY_LEFT) {
		pokedexNumber -= 10;
		if (pokedexNumber < 12)	pokedexNumber = 807;
	}
	
	if (hDown & KEY_B) {
		Gui::screenBack();
		return;
	}
	
	if (hDown & KEY_A) {
		Gui::setScreen(std::make_unique<StatsScreen>());
	}

	if (hDown & KEY_TOUCH && touching(touch, search[0])) {
		Search();
	}
}