//++ BulliT

#pragma once

class AgTimer
{
	float m_fNextTimerUpdate;
	float m_fLastTimeCheck;
	float m_fEffectiveTime;
	cvar_t *m_pmp_timelimit;

public:
	AgTimer();
	virtual ~AgTimer();

	void Think();

	float GetEffectiveTime();
	void Reset();
	bool TimeRemaining(int &iTimeRemaining); // Calculate time remaining.
};

inline bool AgTimer::TimeRemaining(int &iTimeRemaining)
{
	float fTimeLimit = m_pmp_timelimit->value * 60;
	iTimeRemaining = (int)(fTimeLimit ? (fTimeLimit - m_fEffectiveTime) : 0);
	if (fTimeLimit != 0 && m_fEffectiveTime >= fTimeLimit)
		return false;

	return true;
}

inline void AgTimer::Reset()
{
	m_fNextTimerUpdate = 0;
	m_fLastTimeCheck = gpGlobals->time;
	m_fEffectiveTime = 0;
}

inline float AgTimer::GetEffectiveTime()
{
	return m_fEffectiveTime;
}
extern bool g_bPaused;

//-- Martin Webrant
