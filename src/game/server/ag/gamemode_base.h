#ifndef AG_GAMEMODE_MODE_H
#define AG_GAMEMODE_MODE_H

#include "extdll.h"

class CBasePlayer;

class AgGamemode
{
public:
	virtual ~AgGamemode() = default;

	// Called for every active mode.
	virtual void Think() = 0;
	virtual void ClientConnected(CBasePlayer *pPlayer) { }
	virtual void ClientDisconnected(CBasePlayer *pPlayer) { }

	// Only some modes use these.
	virtual void PlayerInitHud(CBasePlayer *pPlayer) { }
	virtual void PlayerKilled(CBasePlayer *pPlayer, entvars_t *pKiller) { }
	virtual bool CanTakeDamage() { return true; }
	virtual bool CanHaveItem() { return false; }
	virtual bool HasReachedScoreLimit() { return false; }
};

#endif
