#pragma once

#include "ag/global.h"

class AgRoundState
{
public:
	enum Status
	{
		Waiting,
		Countdown,
		Spawning,
		Playing,
		PlayerDied
	};

	Status m_Status = Waiting;
	float m_fNextCountdown = 0.0f;
	float m_fMatchStart = 0.0f;
	AgString m_sWinner;

	void SendWaitingMessage();
	void SendCountdown(int iSeconds, const char *pszPlayer1 = "", const char *pszPlayer2 = "");
	void SendCountdownStop();
};
