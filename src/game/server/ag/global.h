//++ BulliT

#pragma once

#pragma warning(disable : 4786)
#pragma warning(disable : 4530)

#include "hltv.h"
#include "ag/random.h"
#include "cvar.h"

#define _bool_h 1

#include <string>
#include <list>
#include <set>
#include <vector>
#include <algorithm>

typedef std::string AgString;
typedef std::list<AgString> AgStringList;
typedef std::set<AgString, std::less<AgString>> AgStringSet;

#define ADD_SERVER_COMMAND (*g_engfuncs.pfnAddServerCommand)
extern DLL_GLOBAL bool g_fGameOver;

extern AgConVar ag_version;
extern AgConVar ag_gametype;
extern AgConVar ag_oldphysics;

extern AgConVar fraglimit;
extern AgConVar timelimit;

extern AgConVar ag_gamemode;
extern AgConVar ag_gamemode_auto;
extern AgConVar ag_allowed_gamemodes;

extern AgConVar ag_spectalk;
extern AgConVar ag_max_spectators;
extern AgConVar ag_spec_enable_disable;

extern AgConVar ag_pure;
extern AgConVar ag_allow_vote;
extern AgConVar ag_match_running;
extern AgConVar ag_player_id;
extern AgConVar ag_lj_timer;
extern AgConVar ag_auto_admin;
extern AgConVar mm_agsay;

extern AgConVar ag_wallgauss;
extern AgConVar ag_headshot;
extern AgConVar ag_blastradius;

extern AgConVar ag_ban_crowbar;
extern AgConVar ag_ban_glock;
extern AgConVar ag_ban_357;
extern AgConVar ag_ban_mp5;
extern AgConVar ag_ban_shotgun;
extern AgConVar ag_ban_crossbow;
extern AgConVar ag_ban_rpg;
extern AgConVar ag_ban_gauss;
extern AgConVar ag_ban_egon;
extern AgConVar ag_ban_hornet;

extern AgConVar ag_ban_hgrenade;
extern AgConVar ag_ban_satchel;
extern AgConVar ag_ban_tripmine;
extern AgConVar ag_ban_snark;
extern AgConVar ag_ban_m203;
extern AgConVar ag_ban_longjump;
extern AgConVar ag_ban_9mmar;
extern AgConVar ag_ban_bockshot;
extern AgConVar ag_ban_uranium;
extern AgConVar ag_ban_bolts;
extern AgConVar ag_ban_rockets;
extern AgConVar ag_ban_357ammo;

extern AgConVar ag_ban_armour;
extern AgConVar ag_ban_health;

extern AgConVar ag_ban_recharg;

extern AgConVar ag_start_crowbar;
extern AgConVar ag_start_glock;
extern AgConVar ag_start_357;
extern AgConVar ag_start_mp5;
extern AgConVar ag_start_shotgun;
extern AgConVar ag_start_crossbow;
extern AgConVar ag_start_rpg;
extern AgConVar ag_start_gauss;
extern AgConVar ag_start_egon;
extern AgConVar ag_start_hornet;

extern AgConVar ag_start_hgrenade;
extern AgConVar ag_start_satchel;
extern AgConVar ag_start_tripmine;
extern AgConVar ag_start_snark;
extern AgConVar ag_start_m203;
extern AgConVar ag_start_longjump;
extern AgConVar ag_start_9mmar;
extern AgConVar ag_start_bockshot;
extern AgConVar ag_start_uranium;
extern AgConVar ag_start_bolts;
extern AgConVar ag_start_rockets;
extern AgConVar ag_start_357ammo;

extern AgConVar ag_start_armour;
extern AgConVar ag_start_health;

extern AgConVar ag_dmg_crowbar;
extern AgConVar ag_dmg_glock;
extern AgConVar ag_dmg_357;
extern AgConVar ag_dmg_mp5;
extern AgConVar ag_dmg_shotgun;
extern AgConVar ag_dmg_crossbow;
extern AgConVar ag_dmg_bolts;
extern AgConVar ag_dmg_rpg;
extern AgConVar ag_dmg_gauss;
extern AgConVar ag_dmg_egon_wide;
extern AgConVar ag_dmg_egon_narrow;
extern AgConVar ag_dmg_hornet;
extern AgConVar ag_dmg_hgrenade;
extern AgConVar ag_dmg_satchel;
extern AgConVar ag_dmg_tripmine;
extern AgConVar ag_dmg_m203;

extern AgConVar ag_spawn_volume;
extern AgConVar ag_show_gibs;

extern AgConVar ag_allow_timeout;

extern AgConVar ag_vote_start;
extern AgConVar ag_vote_setting;
extern AgConVar ag_vote_gamemode;
extern AgConVar ag_vote_kick;
extern AgConVar ag_vote_admin;
extern AgConVar ag_vote_allow;
extern AgConVar ag_vote_map;
extern AgConVar ag_vote_failed_time;

extern AgConVar ag_start_minplayers;

extern AgConVar ag_vote_mp_timelimit_low;
extern AgConVar ag_vote_mp_timelimit_high;
extern AgConVar ag_vote_mp_fraglimit_low;
extern AgConVar ag_vote_mp_fraglimit_high;
extern AgConVar ag_vote_extra_timelimit;

extern AgConVar ag_vote_bot;
extern AgConVar ag_vote_team;
extern AgConVar ag_vote_spectator;

extern AgConVar ag_floodmsgs;
extern AgConVar ag_floodpersecond;
extern AgConVar ag_floodwaitdelay;

extern AgConVar ag_ctf_flag_resettime;
extern AgConVar ag_ctf_capturepoints;
extern AgConVar ag_ctf_teamcapturepoints;
extern AgConVar ag_ctf_capture_limit;
extern AgConVar ag_ctf_returnpoints;
extern AgConVar ag_ctf_carrierkillpoints;
extern AgConVar ag_ctf_stealpoints;
extern AgConVar ag_ctf_defendpoints;
extern AgConVar ag_ctf_roundbased;

//++ muphicks
extern AgConVar ag_dom_mincontroltime;
extern AgConVar ag_dom_controlpoints;
extern AgConVar ag_dom_resetscorelimit;
extern AgConVar ag_dom_scorelimit;
//-- muphicks

extern AgConVar ag_gauss_fix;
extern AgConVar ag_rpg_fix;

extern AgConVar ag_spawn_system;
extern AgConVar ag_spawn_history_entries;
extern AgConVar ag_spawn_avoid_last_spots;
extern AgConVar ag_spawn_far_spots;
extern AgConVar ag_spawn_pa_visible_chance;
extern AgConVar ag_spawn_pa_audible_chance;
extern AgConVar ag_spawn_pa_safe_chance;
extern AgConVar ag_spawn_seed;

extern AgConVar ag_fps_limit;
extern AgConVar ag_fps_limit_auto;
extern AgConVar ag_fps_limit_check_interval;
extern AgConVar ag_fps_limit_match_only;
extern AgConVar ag_fps_limit_steampipe;
extern AgConVar ag_fps_limit_warnings;
extern AgConVar ag_fps_limit_warnings_interval;
extern AgConVar ag_fps_limit_punishment;
extern AgConVar ag_fps_limit_punishment_slap_intensity;
extern AgConVar ag_fps_limit_punishment_slap_interval;
extern AgConVar ag_fps_limit_punishment_ban_time;

extern AgConVar ag_satchel_destroyable;
extern AgConVar ag_satchel_health;
extern AgConVar ag_satchel_solid;

extern AgConVar ag_bot_allow_vote;
extern AgConVar ag_bot_limit;

extern AgConVar ag_flood_name_cooldown;
extern AgConVar ag_flood_name_spec_cooldown;
extern AgConVar ag_flood_model_cooldown;
extern AgConVar ag_flood_model_spec_cooldown;

extern AgConVar ag_enforcement_cooldown;

extern AgConVar ag_force_match_recording;
extern AgConVar ag_force_take_end_screenshot;
extern AgConVar ag_force_take_death_screenshot;
extern AgConVar ag_force_take_death_screenshot_chance;

extern AgConVar ag_match_mute;

extern AgConVar ag_min_respawn_time;
extern AgConVar ag_forcerespawn_time;

extern AgConVar ag_restrict_vote;

extern AgConVar ag_allow_nuke;
extern AgConVar ag_nuke_grenade;
extern AgConVar ag_nuke_crossbow;
extern AgConVar ag_nuke_rpg;
extern AgConVar ag_nuke_gauss;
extern AgConVar ag_nuke_egon;
extern AgConVar ag_nuke_tripmine;
extern AgConVar ag_nuke_satchel;
extern AgConVar ag_nuke_snark;
extern AgConVar ag_nuke_other; // maybe for a new weapon, added via plugin, that does radius damage or sth

extern AgConVar ag_explosion_fix;

extern AgConVar ag_match_teamchange_suicide_penalty;

extern AgConVar ag_speedrun;
extern AgConVar ag_countdown;
extern AgConVar ag_log_cvars;
extern AgConVar ag_say_on_changelevel_delay;

extern AgConVar ag_unlimited_uranium;
extern AgConVar ag_selfdamage;
extern AgConVar ag_selfdamage_boost;

extern AgConVar ag_unstuck_on_changelevel;
extern AgConVar ag_unstuck_max_attempts;

extern AgConVar ag_hl25_satchel_controls;
extern AgConVar ag_hl25_handgrenade_throw;
extern AgConVar ag_hl25_mp5_max_initial_ammo;
extern AgConVar ag_hl25_mp5_spread;

extern bool g_bLangame;
extern bool g_bUseTeamColors;

extern std::vector<CBaseEntity *> g_spawnPoints;
extern std::vector<CBaseEntity *> g_spawnHistory;

extern float g_flSpeedrunStartTime;

extern AgRandom g_spawnRNG;

constexpr float MIN_COUNTDOWN_TIME = 0.1f;

void AgInitGame();
CBasePlayer *AgPlayerByIndex(int iPlayerIndex);
CBasePlayer *AgPlayerByName(const AgString &sNameOrPlayerNumber, CBasePlayer *pPlayer);
CBasePlayer *AgPlayerByAuthID(const AgString &authID);

void RemoveColorCodes(AgString &input);

void AgChangelevel(const AgString &sLevelname);

void AgSay(CBasePlayer *pPlayer, const AgString &sText, float *pfFloodProtected = NULL, float fHoldTime = 3.5, float x = -1, float y = -1, int iChannel = 5, int r = 180, int g = 180, int b = 180);
void AgConsole(const AgString &sText, CBasePlayer *pPlayer = NULL);

void AgResetMap();

char *AgStringToLower(char *pszString);
void AgToLower(AgString &strLower);
void AgTrim(AgString &sTrim);

void AgLogError(const char *pszLog);

double AgTime();

void AgDirList(const AgString &sDir, AgStringSet &setFiles);

void AgSendDirectorMessage(CBaseEntity *ent1, CBaseEntity *ent2, int priority);

void AgStripColors(char *pszString);

void AgGetDetails(char *pszDetails, int iMaxSize, int *piSize);
void AgGetPlayerInfo(char *pszPlayerInfo, int iMaxSize, int *piSize);

char *AgOSVersion();

AgString AgReadFile(const char *pszFile);

void AgDisplayGreetingMessage(const char *pszAuthID);

bool AgIsCTFMap(const char *pszMap);
//++ muphicks
bool AgIsDOMMap(const char *pszMap);
//-- muphicks

void AgSound(CBasePlayer *pPlayer, const char *pszWave);
void AgPlayCountdown(CBasePlayer *pPlayer, int iSeconds);

bool AgIsLocalServer();

const char *AgGetGame();
const char *AgGetDirectory();
const char *AgGetDirectoryValve();
bool IsNukeAllowed(entvars_t *pevInflictor);

void ReseedSpawnSystem();

float GetCountdownTimeOrDefault(float defaultValue);

//-- Martin Webrant
