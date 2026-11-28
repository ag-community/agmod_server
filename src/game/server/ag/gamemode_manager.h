//++ BulliT

#if !defined(AG_GAMEMODE_MANAGER_H)
#define AG_GAMEMODE_MANAGER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ag/global.h"

#include <map>

struct AgGamemodeConfig
{
	AgString m_sCommandName;
	AgString m_sName;
	AgString m_sCfg;
	AgString m_sDescription;
	int m_iAsterisks = 0;
};

class AgGamemodeManager
{
	typedef std::map<AgString, AgGamemodeConfig *, std::less<AgString>> AgGamemodeConfigMap;
	AgGamemodeConfigMap m_mapGames;
	void LoadGames();
	AgGamemodeConfig *pCurrent;
	float m_fNextCheck;
	float m_fNextFpsLimitCheck;
	float m_fNextCvarCheck;

	static constexpr float MIN_FPS_LIMIT_CHECK_INTERVAL = 0.001;

	static constexpr float CVARS_CHECK_INTERVAL = 5.0;

public:
	AgGamemodeManager();
	virtual ~AgGamemodeManager();

	void Init();
	void Think();

	void ExecConfig();
	void Help(CBasePlayer *pPlayer = NULL);
	bool HandleCommand(CBasePlayer *pPlayer);

	void Gamemode(const AgString &sGamemode, CBasePlayer *pPlayer = NULL);
	bool IsGamemode(const AgString &sGamemode);
	bool IsAllowedGamemode(const AgString &sGamemode, CBasePlayer *pPlayer = NULL);

	void NextGamemode(const AgString &sGamemode, CBasePlayer *pPlayer = NULL);
};

extern DLL_GLOBAL AgGamemodeManager GameMode;
const char *AgGamenameChar();
AgString AgGamename();
AgString AgGamedescription();
AgString AgSanitizedShortGamename();

//++ muphicks
enum enumGameType
{
	STANDARD = 0,
	ARENA = 1,
	LMS = 2,
	CTF = 3,
	ARCADE = 4,
	SGBOW = 5,
	INSTAGIB = 6,
	DOM = 7,
	TOURNAMENT = 8
};
//-- muphicks
extern DLL_GLOBAL byte g_GameType;
inline byte AgGametype()
{
	return g_GameType;
};

#endif // !defined(AG_GAMEMODE_MANAGER_H)
//-- Martin Webrant
