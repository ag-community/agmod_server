//++ BulliT

#pragma once

class AgMatch
{
	float m_fMatchStart;
	float m_fNextSay;
	float m_fNextHLTV;
	AgString m_sSpawnFlag;
	bool m_bCountdownStarted;
	void MatchStart();

public:
	AgMatch();
	virtual ~AgMatch();

	void Think();

	void Start(const AgString &sSpawn);
	void Abort();
	void Allow(CBasePlayer *pPlayer);
	void CountdownStart();
};

//-- Martin Webrant
