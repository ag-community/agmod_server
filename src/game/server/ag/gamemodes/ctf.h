// AgCTF.h: interface for the AgCTF class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "ag/gamemode_base.h"
#include "ag/round_state.h"
#include "ag/file_cache.h"

#define CTF_TEAM1_NAME "blue"
#define CTF_TEAM2_NAME "red"

class AgCTFFileItem : public AgFileItem
{
};

class AgCTFFileItemCache : public AgFileItemCache
{
protected:
	const char *GetDirectory() const override { return "ctf"; }
	const char *GetExtension() const override { return "ctf"; }
	AgFileItem *CreateItem() override;
	bool ParseItem(AgFileItem *pItem, const char *pszLine) override;
	void WriteItem(FILE *pFile, AgFileItem *pItem) override;

public:
	AgCTFFileItemCache() = default;
};

class AgCTF : public AgGamemode
{
protected:
	AgRoundState m_Round;

	int m_iTeam1Captures;
	int m_iTeam2Captures;

	int m_iPlayerFlag1;
	int m_iPlayerFlag2;

public:
	AgCTF();
	virtual ~AgCTF();

	bool CaptureLimit();
	bool HasReachedScoreLimit() override { return CaptureLimit(); }
	void ResetCaptures();
	void ResetScore(bool bResetCaptures = true);
	void SendCaptures(CBasePlayer *pPlayer);
	void Think() override;
	void RoundBasedThink();

	void PlayerInitHud(CBasePlayer *pPlayer) override;
	void ClientDisconnected(CBasePlayer *pPlayer) override;
	void ClientConnected(CBasePlayer *pPlayer) override;
	void PlayerKilled(CBasePlayer *pPlayer, entvars_t *pKiller) override;
	void AddPointsForKill(CBasePlayer *pAttacker, CBasePlayer *pKilled);

	void PlayerDropFlag(CBasePlayer *pPlayer, bool bPlayerDrop = false);

	void RoundOver(const char *pszWinner);

	AgCTFFileItemCache m_FileItemCache;
};

class AgCTFFlag : public CBaseEntity
{
public:
	void Spawn(void);

	float m_fNextTouch;
	bool m_bDropped;
	char m_szTeamName[64];
	float m_fNextReset;

	static void ResetFlag(const char *pTeamName);

	void ResetFlag();

private:
	void Precache(void);
	void Capture(CBasePlayer *pPlayer, const char *pTeamName);
	void Materialize(void);
	void FlagTouch(CBaseEntity *pOther);
	bool MyTouch(CBasePlayer *pPlayer);
	void Think(void);
};

class AgCTFPlayerFlag : public CBaseEntity
{
public:
	void Spawn(void);
	virtual void UpdateOnRemove(void);

	CBasePlayer *m_pOwner;
	char m_szTeamName[64];

private:
	void Precache(void);
	void Think(void);
};
