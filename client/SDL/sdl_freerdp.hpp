/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * SDL Client
 *
 * Copyright 2022 Armin Novak <armin.novak@thincast.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <memory>
#include <thread>

#include <freerdp/freerdp.h>
#include <freerdp/client/rdpei.h>
#include <freerdp/client/rail.h>
#include <freerdp/client/cliprdr.h>
#include <freerdp/client/rdpgfx.h>

#include <SDL.h>
#include <SDL_video.h>

#include "sdl_types.hpp"
#include "sdl_disp.hpp"
#include "sdl_kbd.hpp"
#include "sdl_utils.hpp"

typedef struct
{
	SDL_Window* window;
	int offset_x;
	int offset_y;
} sdl_window_t;

using SDLSurfacePtr = std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>;
using SDLPixelFormatPtr = std::unique_ptr<SDL_PixelFormat, decltype(&SDL_FreeFormat)>;

struct sdl_context
{
	rdpClientContext common;

	/* SDL */
	BOOL fullscreen;
	BOOL resizeable;
	BOOL grab_mouse;
	BOOL grab_kbd;
	BOOL highDpi;

	size_t windowCount;
	sdl_window_t windows[16];

	std::unique_ptr<CriticalSection> critical;
	std::thread thread;
	std::unique_ptr<WinPREvent> initialize;
	std::unique_ptr<WinPREvent> initialized;
	std::unique_ptr<WinPREvent> update_complete;
	std::unique_ptr<WinPREvent> windows_created;
	int exit_code;

	SDLSurfacePtr primary;
	SDLPixelFormatPtr primary_format;

	std::unique_ptr<sdlDispContext> disp;
	std::unique_ptr<sdlInput> input;

	Uint32 sdl_pixel_format;

	wLog* log;

	BOOL update_resizeable(BOOL enable);
	BOOL update_fullscreen(BOOL enter);
};
