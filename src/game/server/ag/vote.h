//++ BulliT

#pragma once

class AgVote
{
protected:
	AgString m_sVote;
	AgString m_sValue;
	AgString m_sValue2;
	AgString m_sFullValue;
	CBasePlayer *m_sTarget;
	AgString m_sCalled;
	AgString m_sCallerID;
	AgString m_sAuthID;

	double m_fMaxTime;
	double m_fNextCount;
	double m_fNextVote;

	enum VoteStatus
	{
		NotRunning = 0,
		Called = 1,
		Accepted = 2,
		Denied = 3,
	};

	bool m_bRunning;

public:
	AgVote();
	virtual ~AgVote();

	bool HandleCommand(CBasePlayer *pPlayer);

	bool CallVote(CBasePlayer *pPlayer);
	void Think();

	bool ResetVote();
};

//-- Martin Webrant
