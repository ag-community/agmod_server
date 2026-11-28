// aglms.h: interface for the AgLMS class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "ag/gamemode_base.h"
#include "ag/round_state.h"

class AgLMS : public AgGamemode
{
protected:
	AgRoundState m_Round;

public:
	AgLMS();
	virtual ~AgLMS();

	void Think() override;

	void ClientDisconnected(CBasePlayer *pPlayer) override;
	void ClientConnected(CBasePlayer *pPlayer) override;

	bool CanTakeDamage() override;
};

inline bool AgLMS::CanTakeDamage()
{
	return AgRoundState::Playing == m_Round.m_Status;
}
