//++ BulliT

#pragma once

#include "ag/score.h"
#include <map>

class CBasePlayer;
class AgScoreCache
{
	typedef std::map<AgString, AgScore *, std::less<AgString>> AgScoreMap;
	AgScoreMap m_mapScores; // Holds the map score for each player.

public:
	AgScoreCache();
	virtual ~AgScoreCache();

	// Score cache.
	AgScore *FindScore(CBasePlayer *pPlayer); // Find a score for a player.
	void RestoreScore(CBasePlayer *pPlayer); // Restore his score from scorecache.
	void UpdateScore(CBasePlayer *pPlayer); // Update the cache with current score.
	void RestoreInGame(CBasePlayer *pPlayer); // Restore ingame flag from the scorecache.
	void Reset(); // Reset it.
};

//-- Martin Webrant
