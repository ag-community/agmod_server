/***
 *
 *	Copyright (c) 1996-2001, Valve LLC. All rights reserved.
 *
 *	This product contains software technology licensed from Id
 *	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
 *	All Rights Reserved.
 *
 *   Use, distribution, and modification of this source code and/or resulting
 *   object code is restricted to non-commercial enhancements to products from
 *   Valve LLC.  All other use, distribution, or modification is prohibited
 *   without written permission from Valve LLC.
 *
 ****/

#ifndef GAME_H
#define GAME_H

#include "cvar.h"

extern void GameDLLInit(void);

extern AgConVar displaysoundlist;
extern AgConVar fragsleft;
extern AgConVar timeleft;

// multiplayer server rules
extern AgConVar teamplay;
extern AgConVar fraglimit;
extern AgConVar timelimit;
extern AgConVar friendlyfire;
extern AgConVar falldamage;
extern AgConVar weaponstay;
extern AgConVar forcerespawn;
extern AgConVar flashlight;
extern AgConVar aimcrosshair;
extern AgConVar decalfrequency;
extern AgConVar teamlist;
extern AgConVar teamoverride;
extern AgConVar defaultteam;
extern AgConVar allowmonsters;
extern AgConVar mp_chattime;

extern AgConVar singleplayer;
extern cvar_t sploading;
extern cvar_t spgausscharging;

// Engine Cvars
extern cvar_t *g_psv_gravity;
extern cvar_t *g_psv_aim;
extern cvar_t *g_footsteps;
extern cvar_t *g_cheats;

#endif // GAME_H
