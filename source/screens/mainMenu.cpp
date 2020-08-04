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

extern bool exiting;

void MainMenu::Draw(void) const {
	GFX::DrawTop();
	GFX::DrawSprite(sprites_betterDex_idx, 0, 25);
	Gui::DrawString(395-Gui::GetStringWidth(0.72f, V_STRING), 216, 0.72f, WHITE, V_STRING, 400);
	GFX::DrawBottom();
}

void MainMenu::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_START) {
		exiting = true;
	}
	
	if (hDown & KEY_A) {
		Gui::setScreen(std::make_unique<DexList>());
	}
}