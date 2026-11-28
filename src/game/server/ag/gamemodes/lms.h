// aglms.h: interface for the AgLMS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__AG_LMS_H__)
#define __AG_LMS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#endif // !defined(__AG_LMS_H__)
