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

#ifndef GFX_HPP
#define GFX_HPP

#include "spriteIDs.h"

#include <3ds.h>
#include <citro2d.h>

// Colors.
#define WHITE C2D_Color32(255, 255, 255, 255)
#define BLACK C2D_Color32(0, 0, 0, 255)
#define GRAY C2D_Color32(127, 127, 127, 255)
#define BLUE C2D_Color32(0, 0, 128, 255)
#define TRANSPARENT C2D_Color32(0, 0, 0, 0)
#define RED C2D_Color32(255, 0, 0, 255)
#define GREEN RGBA8(0, 255, 0, 255)

typedef u32 Color;

namespace GFX
{
	// Basic GUI.
	void DrawTop(void);
	void DrawBottom(void);
	// Draw Sprites.
	void DrawPKMSprite(int img, int x, int y, float ScaleX = 2.5, float ScaleY = 2.5);
	void DrawSprite(int img, int x, int y, float ScaleX = 1.0, float ScaleY = 1.0);
	void DrawOther(int img, int x, int y, float ScaleX = 1.0, float ScaleY = 1.0);
}

#endif