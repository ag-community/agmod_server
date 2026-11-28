#include "extdll.h"
#include "util.h"

#include "ag/global.h"
#include "ag/round_state.h"

extern int gmsgCountdown;

void AgRoundState::SendWaitingMessage()
{
	MESSAGE_BEGIN(MSG_ALL, gmsgCountdown);
	WRITE_BYTE(50);
	WRITE_BYTE(1);
	WRITE_STRING(m_sWinner.c_str());
	WRITE_STRING("");
	MESSAGE_END();
}

void AgRoundState::SendCountdown(int iSeconds, const char *pszPlayer1, const char *pszPlayer2)
{
	MESSAGE_BEGIN(MSG_ALL, gmsgCountdown);
	WRITE_BYTE(iSeconds);
	WRITE_BYTE(1);
	WRITE_STRING(pszPlayer1);
	WRITE_STRING(pszPlayer2);
	MESSAGE_END();
}

void AgRoundState::SendCountdownStop()
{
	MESSAGE_BEGIN(MSG_ALL, gmsgCountdown);
	WRITE_BYTE(-1);
	WRITE_BYTE(0);
	WRITE_STRING("");
	WRITE_STRING("");
	MESSAGE_END();
}
