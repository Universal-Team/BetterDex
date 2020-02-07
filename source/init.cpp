/*
*   This file is part of BetterDex
*   Copyright (C) 2019-2020 DeadPhoenix8091, Epicpkmn11, Flame, RocketRobz, StackZ, TotallyNotGuy
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

#include "common.hpp"
#include "init.hpp"
#include "mainMenu.hpp"

#include <3ds.h>
#include <dirent.h>
#include <fstream>

bool exiting = false;
touchPosition touch;

// Include all spritesheet's.
C2D_SpriteSheet sprites, spritesheet_pkm, spritesheet_types;


// If button Position pressed -> Do something.
bool touching(touchPosition touch, Structs::ButtonPos button) {
	if (touch.px >= button.x && touch.px <= (button.x + button.w) && touch.py >= button.y && touch.py <= (button.y + button.h))
		return true;
	else
		return false;
}

std::vector<std::string> g_speciesDatabase;
std::string languages[] = {"de", "en", "fr", "it", "jp"};

void Init::LoadSpeciesDatabase(int lang) {
	g_speciesDatabase.clear();

	std::string currentLine;
	std::ifstream speciesDatabase("romfs:/lang/" + languages[lang] + "/species.txt", std::ifstream::in);

	while (std::getline(speciesDatabase, currentLine)) {
		g_speciesDatabase.push_back(currentLine);
	}

	speciesDatabase.close();
}

Result Init::loadPkmnSheets() {
	sprites    			= C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
	spritesheet_pkm   	= C2D_SpriteSheetLoad("romfs:/gfx/pkm_spritesheet.t3x");
	spritesheet_types 	= C2D_SpriteSheetLoad("romfs:/gfx/types_spritesheet.t3x");
	return 0;
}

Result Init::unloadPkmnSheets() {
	C2D_SpriteSheetFree(sprites);
	C2D_SpriteSheetFree(spritesheet_pkm);
	C2D_SpriteSheetFree(spritesheet_types);
	return 0;
}

Result Init::Initialize() {
	gfxInitDefault();
	romfsInit();
	Gui::init();
	loadPkmnSheets();
	LoadSpeciesDatabase(1);
	sdmcInit();
	osSetSpeedupEnable(true);	// Enable speed-up for New 3DS users.

	// make folders if they don't exist
	mkdir("sdmc:/3ds", 0777);	// For DSP dump
	mkdir("sdmc:/BetterDex", 0777); // main Path.

	Gui::setScreen(std::make_unique<MainMenu>());
    return 0;
}

Result Init::MainLoop() {
    // Initialize everything.
    Initialize();

	// Loop as long as the status is not exiting.
	while (aptMainLoop() && !exiting)
	{
		// Scan all the Inputs.
		hidScanInput();
		u32 hDown = hidKeysDown();
		u32 hHeld = hidKeysHeld();
		hidTouchRead(&touch);
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(Top, BLACK);
		C2D_TargetClear(Bottom, BLACK);
		Gui::clearTextBufs();
		Gui::mainLoop(hDown, hHeld, touch);
		C3D_FrameEnd(0);
	}
    // Exit all services and exit the app.
    Exit();
    return 0;
}

Result Init::Exit() {
	cfguExit();
	sdmcExit();
	Gui::exit();
	unloadPkmnSheets();
	gfxExit();
	romfsExit();
	return 0;
}