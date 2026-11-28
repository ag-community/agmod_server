// agarena.h: interface for the AgArena class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AGARENA_H__1929C55A_3034_4C89_8398_1F8243B83499__INCLUDED_)
#define AFX_AGARENA_H__1929C55A_3034_4C89_8398_1F8243B83499__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ag/gamemode_base.h"
#include "ag/round_state.h"

class AgArena : public AgGamemode
{
protected:
	AgRoundState m_Round;

	typedef std::list<int> AgWaitList;
	AgWaitList m_lstWaitList;
	EHANDLE m_Player1;
	EHANDLE m_Player2;

	CBasePlayer *GetPlayer1();
	CBasePlayer *GetPlayer2();

	void Add(CBasePlayer *pPlayer);
	void Remove(CBasePlayer *pPlayer);

public:
	AgArena();
	virtual ~AgArena();

	void Think() override;

	void Ready(CBasePlayer *pPlayer);
	void NotReady(CBasePlayer *pPlayer);

	void ClientDisconnected(CBasePlayer *pPlayer) override;
	void ClientConnected(CBasePlayer *pPlayer) override;

	bool CanTakeDamage() override;
	bool CanHaveItem() override;
};

inline CBasePlayer *AgArena::GetPlayer1()
{
	if (m_Player1)
		return (CBasePlayer *)(CBaseEntity *)m_Player1;
	else
		return NULL;
};

inline CBasePlayer *AgArena::GetPlayer2()
{
	if (m_Player2)
		return (CBasePlayer *)(CBaseEntity *)m_Player2;
	else
		return NULL;
};

inline bool AgArena::CanTakeDamage()
{
	return AgRoundState::Playing == m_Round.m_Status || AgRoundState::PlayerDied == m_Round.m_Status;
}

inline bool AgArena::CanHaveItem()
{
	return AgRoundState::Spawning == m_Round.m_Status;
}

#endif // !defined(AFX_AGARENA_H__1929C55A_3034_4C89_8398_1F8243B83499__INCLUDED_)
