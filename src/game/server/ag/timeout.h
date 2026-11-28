//++ BulliT

#pragma once

class AgTimeout
{
	enum enumState
	{
		Inactive = 0,
		Called = 1,
		Pause = 2,
		Countdown = 3,
		DisablePause = 4
	};
	enumState m_State;
	double m_fDisablePause;
	double m_fTimeout;
	AgStringList m_lstStrings;

	bool CanTimeout(CBasePlayer *pPlayer);
	void AddTimeout(CBasePlayer *pPlayer);

public:
	AgTimeout();
	virtual ~AgTimeout();

	void Think();
	void Timeout(CBasePlayer *pPlayer);
	void Reset();
	void TogglePause(enumState State = DisablePause);
};

//-- Martin Webrant
