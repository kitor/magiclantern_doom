//
// Copyright(C) 1993-1996 Id Software, Inc.
// Copyright(C) 2005-2014 Simon Howard
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//      Timer functions.
//

#ifdef ORIGCODE
#include "SDL.h"
#endif

#include "i_timer.h"
#include "doomtype.h"
#include "extfunctions.h"
#include "dryos.h"

#ifdef ORIGCODE

//
// I_GetTime
// returns time in 1/35th second tics
//

static Uint32 basetime = 0;

int  I_GetTime (void)
{
    Uint32 ticks;

    ticks = SDL_GetTicks();

    if (basetime == 0)
        basetime = ticks;

    ticks -= basetime;

    return (ticks * TICRATE) / 1000;    
}

//
// Same as I_GetTime, but returns time in milliseconds
//

int I_GetTimeMS(void)
{
    Uint32 ticks;

    ticks = SDL_GetTicks();

    if (basetime == 0)
        basetime = ticks;

    return ticks - basetime;
}

// Sleep for a specified number of ms

void I_Sleep(int ms)
{
    SDL_Delay(ms);
}

void I_WaitVBL(int count)
{
    I_Sleep((count * 1000) / 70);
}


void I_InitTimer(void)
{
    // initialize timer

    SDL_Init(SDL_INIT_TIMER);
}

#else

//
// I_GetTime
// returns time in 1/35th second tics
//

static uint32_t basetime = 0;

int  I_GetTime (void)
{
    uint32_t ticks;
    
    ticks = MEM(TIMER)/1000; //turtius: not for other models
    if (basetime == 0)
        basetime = ticks;

    ticks -= basetime;

    return (ticks * TICRATE) / 1000;
}

//
// Same as I_GetTime, but returns time in milliseconds
//

int I_GetTimeMS(void)
{
    uint32_t ticks;

    ticks = MEM(TIMER)/1000; //turtius: not for other models
    if (basetime == 0)
        basetime = ticks;

    return ticks - basetime;
}

// Sleep for a specified number of ms

void I_Sleep(int ms)
{
	msleep (ms);
}

void I_WaitVBL(int count)
{
    msleep((count * 1000) / 70);
}


void I_InitTimer(void)
{
    // initialize timer
}

#endif

