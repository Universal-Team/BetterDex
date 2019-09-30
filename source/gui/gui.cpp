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

#include "gui.hpp"
#include <assert.h>
#include <stdarg.h>


C3D_RenderTarget* top;
C3D_RenderTarget* bottom;

C2D_SpriteSheet sprites, spritesheet_pkm, spritesheet_types;
C2D_TextBuf sizeBuf;
C2D_Font defaultFont;
std::stack<std::unique_ptr<SCREEN>> screens;
bool currentScreen = false;

void Gui::clearTextBufs(void)
{
    C2D_TextBufClear(sizeBuf);
}

Result Gui::init(void)
{
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
    top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

    sizeBuf = C2D_TextBufNew(4096);
    sprites    = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
    spritesheet_pkm   = C2D_SpriteSheetLoad("romfs:/gfx/pkm_spritesheet.t3x");
    spritesheet_types = C2D_SpriteSheetLoad("romfs:/gfx/types_spritesheet.t3x");
    defaultFont = C2D_FontLoadSystem(CFG_REGION_USA);
    return 0;
}

void Gui::exit(void)
{
    C2D_SpriteSheetFree(sprites);
    C2D_SpriteSheetFree(spritesheet_pkm);
    C2D_SpriteSheetFree(spritesheet_types);
    C2D_TextBufDelete(sizeBuf);
    C2D_Fini();
    C3D_Fini();
}

void Gui::sprite(int sheet, int key, int x, int y)
{
    if (sheet == 0) {
        C2D_DrawImageAt(C2D_SpriteSheetGetImage(sprites, key), x, y, 0.5f);
    } else if (sheet == 1) {
        C2D_DrawImageAt(C2D_SpriteSheetGetImage(spritesheet_pkm, key), x, y, 0.5f);
    } else if (sheet == 2) {
        C2D_DrawImageAt(C2D_SpriteSheetGetImage(spritesheet_types, key), x, y, 0.5f);
    }
}

void findAndReplaceAll(std::string & data, std::string toSearch, std::string replaceStr)
{
	// Get the first occurrence
	size_t pos = data.find(toSearch);
 
	// Repeat till end is reached
	while( pos != std::string::npos)
	{
		// Replace this occurrence of Sub String
		data.replace(pos, toSearch.size(), replaceStr);
		// Get the next occurrence from the current position
		pos =data.find(toSearch, pos + replaceStr.size());
	}
}

void Gui::DrawStringCentered(float x, float y, float size, u32 color, std::string Text, int maxWidth) {
    Gui::DrawString((currentScreen ? 400 : 320)+x-(std::min(maxWidth, (int)Gui::GetStringWidth(size, Text)/2)), y, size, color, Text, maxWidth);
}

// Draw String or Text.
void Gui::DrawString(float x, float y, float size, u32 color, std::string Text, int maxWidth) {
	float width = 1, height = 1;

	findAndReplaceAll(Text, "\\n", "\n");
	C2D_Text c2d_text;
	C2D_TextFontParse(&c2d_text, defaultFont, sizeBuf, Text.c_str());

	if(maxWidth > 0) {
		C2D_TextGetDimensions(&c2d_text, size, size, &width, &height);
	}

	C2D_TextOptimize(&c2d_text);
	C2D_DrawText(&c2d_text, C2D_WithColor, x, y, 0.5f, std::min(size, size*(maxWidth/width)), size, color);
}


// Get String or Text Width.
float Gui::GetStringWidth(float size, std::string Text) {
	findAndReplaceAll(Text, "\\n", "\n");
	float width = 0;
	GetStringSize(size, &width, NULL, Text);
	return width;
}

// Get String or Text Size.
void Gui::GetStringSize(float size, float *width, float *height, std::string Text) {
	findAndReplaceAll(Text, "\\n", "\n");
	C2D_Text c2d_text;
	C2D_TextFontParse(&c2d_text, defaultFont, sizeBuf, Text.c_str());
	C2D_TextGetDimensions(&c2d_text, size, size, width, height);
}


// Get String or Text Height.
float Gui::GetStringHeight(float size, std::string Text) {
	findAndReplaceAll(Text, "\\n", "\n");
	float height = 0;
	GetStringSize(size, NULL, &height, Text.c_str());
	return height;
}

bool Gui::Draw_Rect(float x, float y, float w, float h, u32 color) {
	return C2D_DrawRectSolid(x, y, 0.5f, w, h, color);
}


// Mainloop the GUI.
void Gui::mainLoop(u32 hDown, u32 hHeld, touchPosition touch) {
	screens.top()->Draw();
	screens.top()->Logic(hDown, hHeld, touch);
}

// Set the current Screen.
void Gui::setScreen(std::unique_ptr<SCREEN> screen)
{
	screens.push(std::move(screen));
}

// Go a Screen back.
void Gui::screenBack()
{
	screens.pop();
}

// Select, on which Screen should be drawn.
void Gui::ScreenDraw(C3D_RenderTarget * screen)
{
	C2D_SceneBegin(screen);
	currentScreen = screen == top ? 1 : 0;
}