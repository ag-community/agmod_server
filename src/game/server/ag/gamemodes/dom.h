//++ muphicks
// AGDomination mode header file

#pragma once

#include "ag/gamemode_base.h"
#include "ag/file_cache.h"

#define DOM_TEAM1_NAME   "blue"
#define DOM_TEAM2_NAME   "red"
#define DOM_NEUTRAL_NAME "neutral"

class AgDOMFileItem : public AgFileItem
{
public:
	char m_szData1[64] = {};

	AgDOMFileItem() = default;
};

class AgDOMFileItemCache : public AgFileItemCache
{
protected:
	const char *GetDirectory() const override { return "dom"; }
	const char *GetExtension() const override { return "dom"; }
	AgFileItem *CreateItem() override;
	bool ParseItem(AgFileItem *pItem, const char *pszLine) override;
	void WriteItem(FILE *pFile, AgFileItem *pItem) override;
	void OnItemCreated(AgFileItem *pItem, CBaseEntity *pEntity) override;

public:
	AgDOMFileItemCache() = default;
};

class AgDOMControlPoint : public CBaseEntity
{
public:
	void Spawn(void); // spawn a control point in the map
	void Reset(void); // reset control point to neutral state
	void ClientDisconnected(CBasePlayer *pPlayer);

	char m_szTeamName[64]; // who controls this point?
	char m_szLocation[64];

	float m_fCaptureTime;
	float m_fNextTouch;
	int m_iConsecutiveScores; // how many times in a row has same team scored
	CBasePlayer *pCapturingPlayer;

private:
	void Precache(void);
	void Think(void);
	void ChangeControllingTeam(const char *szTeamName);
	void Touch(CBaseEntity *pOther);
	void Capture(CBasePlayer *pPlayer, const char *szTeamName);
};

class AgDOM : public AgGamemode
{
private:
	int m_iTeam1Score;
	int m_iTeam2Score;

public:
	AgDOM();
	virtual ~AgDOM();

	void Think() override;
	void ResetControlPoints();
	bool ScoreLimit(void);
	bool HasReachedScoreLimit() override { return ScoreLimit(); }

	void ClientDisconnected(CBasePlayer *pPlayer) override;
	void ClientConnected(CBasePlayer *pPlayer) override;

	void PlayerInitHud(CBasePlayer *pPlayer) override;
	void SendControlScores(CBasePlayer *pPlayer);

	AgDOMFileItemCache m_FileItemCache;
};
