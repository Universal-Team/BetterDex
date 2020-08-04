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

#include "personal.hpp"
#include "statsScreen.hpp"

extern int pokedexNumber;
extern std::vector<std::string> g_speciesDatabase;
extern std::string speciesName;
extern std::string pokedex;

void StatsScreen::Draw(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 2, 0.7f, WHITE, "BetterDex -> Stats Screen.", 400);

	// Draw Pokémon inclusive name.
	GFX::DrawPKMSprite(pokedexNumber, 10, 40);
	Gui::Draw_Rect(10, 140, 100, 25, GRAY);
	Gui::DrawString((400-Gui::GetStringWidth(0.7f, speciesName))/2-190+50, 142, 0.7f, WHITE, speciesName, 100);

	// Draw Stats Text.
	Gui::DrawString(200, 40, 0.7f, WHITE, "HP", 400);
	Gui::DrawString(200, 70, 0.7f, WHITE, "Attack", 400);
	Gui::DrawString(200, 100, 0.7f, WHITE, "Defense", 400);
	Gui::DrawString(200, 130, 0.7f, WHITE, "Sp. Attack", 400);
	Gui::DrawString(200, 160, 0.7f, WHITE, "Sp. Defense", 400);
	Gui::DrawString(200, 190, 0.7f, WHITE, "Speed", 400);

	// Stats Boxes.
	Gui::Draw_Rect(320, 35, 50, 25, GRAY);
	Gui::Draw_Rect(320, 65, 50, 25, GRAY);
	Gui::Draw_Rect(320, 95, 50, 25, GRAY);
	Gui::Draw_Rect(320, 125, 50, 25, GRAY);
	Gui::Draw_Rect(320, 155, 50, 25, GRAY);
	Gui::Draw_Rect(320, 185, 50, 25, GRAY);

	// Get the base stats of the selected Pokémon and define it to a String.
	std::string HP = std::to_string(PersonalSMUSUM::baseHP(pokedexNumber));
	std::string Attack = std::to_string(PersonalSMUSUM::baseAtk(pokedexNumber));
	std::string Defense = std::to_string(PersonalSMUSUM::baseDef(pokedexNumber));
	std::string SpAttack = std::to_string(PersonalSMUSUM::baseSpa(pokedexNumber));
	std::string SpDefense = std::to_string(PersonalSMUSUM::baseSpd(pokedexNumber));
	std::string Speed = std::to_string(PersonalSMUSUM::baseSpe(pokedexNumber));

	// Draw the base stats.
	Gui::DrawString((400-Gui::GetStringWidth(0.5f, HP))/2+120+25, 40, 0.5f, WHITE, HP, 400);
	Gui::DrawString((400-Gui::GetStringWidth(0.5f, Attack))/2+120+25, 70, 0.5f, WHITE, Attack, 400);
	Gui::DrawString((400-Gui::GetStringWidth(0.5f, Defense))/2+120+25, 100, 0.5f, WHITE, Defense, 400);
	Gui::DrawString((400-Gui::GetStringWidth(0.5f, SpAttack))/2+120+25, 130, 0.5f, WHITE, SpAttack, 400);
	Gui::DrawString((400-Gui::GetStringWidth(0.5f, SpDefense))/2+120+25, 160, 0.5f, WHITE, SpDefense, 400);
	Gui::DrawString((400-Gui::GetStringWidth(0.5f, Speed))/2+120+25, 190, 0.5f, WHITE, Speed, 400);

	GFX::DrawBottom();
}

void StatsScreen::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_B) {
		Gui::screenBack();
		return;
	}
}