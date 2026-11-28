//++ BulliT

#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "player.h"
#include "weapons.h"
#include "gamerules.h"

#include "ag/rules.h"
#include "ag/global.h"
#include "ag/gamemodes/lms.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern int gmsgCountdown;

AgLMS::AgLMS()
{
	m_Round.m_fMatchStart = 0.0;
	m_Round.m_fNextCountdown = 0.0;
	m_Round.m_Status = AgRoundState::Waiting;
}

AgLMS::~AgLMS()
{
}

void AgLMS::Think()
{
	if (!g_pGameRules)
		return;

	if (AgRoundState::Playing == m_Round.m_Status)
	{
		if (m_Round.m_fNextCountdown > gpGlobals->time)
			return;
		m_Round.m_fNextCountdown = gpGlobals->time + 0.5;

		if (g_pGameRules->IsTeamplay())
		{
			// Teams.
			AgStringSet setTeams;
			for (int i = 1; i <= gpGlobals->maxClients; i++)
			{
				CBasePlayer *pPlayerLoop = AgPlayerByIndex(i);
				if (pPlayerLoop)
				{
					if (!pPlayerLoop->IsAlive())
					{
						pPlayerLoop->SetIngame(false); // Cant respawn
						if (!pPlayerLoop->IsSpectator())
						{
							// Quake1 teleport splash around him.
							MESSAGE_BEGIN(MSG_BROADCAST, SVC_TEMPENTITY);
							WRITE_BYTE(TE_TELEPORT);
							WRITE_COORD(pPlayerLoop->pev->origin.x);
							WRITE_COORD(pPlayerLoop->pev->origin.y);
							WRITE_COORD(pPlayerLoop->pev->origin.z);
							MESSAGE_END();

							pPlayerLoop->Spectate_Start(false);
							pPlayerLoop->Spectate_SetMode(OBS_IN_EYE);
						}
					}
					else
					{
						setTeams.insert(pPlayerLoop->m_szTeamName);
					}
				}
			}

			if (!(setTeams.size() > 1))
			{
				m_Round.m_sWinner = "";
				AgStringSet::iterator itrTeams = setTeams.begin();
				if (itrTeams != setTeams.end())
				{
					m_Round.m_sWinner = *itrTeams;
				}
				m_Round.m_Status = AgRoundState::Waiting;
			}
		}
		else
		{
			int iPlayersAlive = 0;
			CBasePlayer *pPlayer = NULL;

			for (int i = 1; i <= gpGlobals->maxClients; i++)
			{
				CBasePlayer *pPlayerLoop = AgPlayerByIndex(i);
				if (pPlayerLoop)
				{
					if (!pPlayerLoop->IsAlive())
					{
						pPlayerLoop->SetIngame(false); // Cant respawn
						if (!pPlayerLoop->IsSpectator())
						{
							// Quake1 teleport splash around him.
							MESSAGE_BEGIN(MSG_BROADCAST, SVC_TEMPENTITY);
							WRITE_BYTE(TE_TELEPORT);
							WRITE_COORD(pPlayerLoop->pev->origin.x);
							WRITE_COORD(pPlayerLoop->pev->origin.y);
							WRITE_COORD(pPlayerLoop->pev->origin.z);
							MESSAGE_END();

							pPlayerLoop->Spectate_Start(false);
							pPlayerLoop->Spectate_SetMode(OBS_IN_EYE);
						}
					}
					else
					{
						iPlayersAlive++;
						pPlayer = pPlayerLoop;
					}
				}
			}

			if (!(iPlayersAlive > 1))
			{
				m_Round.m_sWinner = "";
				if (pPlayer)
					m_Round.m_sWinner = pPlayer->GetName();
				m_Round.m_Status = AgRoundState::Waiting;
			}
		}
	}
	else
	{
		// We only update status once every second.
		if (m_Round.m_fNextCountdown > gpGlobals->time)
			return;
		m_Round.m_fNextCountdown = gpGlobals->time + 1.0;

		// Handle the status
		if (AgRoundState::Waiting == m_Round.m_Status)
		{
			if (g_pGameRules->IsTeamplay())
			{
				// Teams.
				AgStringSet setTeams;
				for (int i = 1; i <= gpGlobals->maxClients; i++)
				{
					CBasePlayer *pPlayerLoop = AgPlayerByIndex(i);
					if (pPlayerLoop && pPlayerLoop->m_bReady)
					{
						setTeams.insert(pPlayerLoop->m_szTeamName);
					}
				}

				if (setTeams.size() > 1)
				{
					m_Round.m_Status = AgRoundState::Countdown;
					m_Round.m_fMatchStart = gpGlobals->time + GetCountdownTimeOrDefault(8.0f);
					m_Round.m_fNextCountdown = gpGlobals->time + 3.0;
				}
			}
			else
			{
				int iPlayers = 0;
				for (int i = 1; i <= gpGlobals->maxClients; i++)
				{
					CBasePlayer *pPlayerLoop = AgPlayerByIndex(i);
					if (pPlayerLoop && pPlayerLoop->m_bReady)
					{
						iPlayers++;
					}
				}
				if (iPlayers > 1)
				{
					m_Round.m_Status = AgRoundState::Countdown;
					m_Round.m_fMatchStart = gpGlobals->time + GetCountdownTimeOrDefault(8.0f);
					m_Round.m_fNextCountdown = gpGlobals->time + 3.0;
				}
			}

			// Write waiting message
			m_Round.SendWaitingMessage();
		}
		else if (AgRoundState::Countdown == m_Round.m_Status)
		{
			if (m_Round.m_fMatchStart < gpGlobals->time)
			{
				// Clear out the map
				AgResetMap();

				int i = 1;

				for (i = 1; i <= gpGlobals->maxClients; i++)
				{
					CBasePlayer *pPlayerLoop = AgPlayerByIndex(i);
					if (pPlayerLoop && pPlayerLoop->m_bReady)
					{
						pPlayerLoop->SetIngame(true);
						g_pGameRules->m_ScoreCache.UpdateScore(pPlayerLoop);
					}
				}

				m_Round.m_Status = AgRoundState::Spawning;
				m_Round.m_sWinner = "";

				// Time to start playing.
				for (i = 1; i <= gpGlobals->maxClients; i++)
				{
					CBasePlayer *pPlayerLoop = AgPlayerByIndex(i);
					if (pPlayerLoop && pPlayerLoop->m_bReady)
					{
						if (pPlayerLoop->IsSpectator())
						{
							pPlayerLoop->Spectate_Stop();
						}
						else
							pPlayerLoop->RespawnMatch();
					}
				}

				m_Round.m_Status = AgRoundState::Playing;

				// Stop countdown
				m_Round.SendCountdownStop();
			}
			else
			{
				m_Round.SendCountdown((int)(m_Round.m_fMatchStart - gpGlobals->time));
			}
		}
	}
}

void AgLMS::ClientConnected(CBasePlayer *pPlayer)
{
	ASSERT(NULL != pPlayer);
	if (!pPlayer)
		return;
	ASSERT(NULL != pPlayer->pev);
	if (!pPlayer->pev)
		return;

	// Set status
	pPlayer->SetIngame(false);
}

void AgLMS::ClientDisconnected(CBasePlayer *pPlayer)
{
	ASSERT(NULL != pPlayer);
	if (!pPlayer)
		return;
	ASSERT(NULL != pPlayer->pev);
	if (!pPlayer->pev)
		return;

	// Set status
	pPlayer->SetIngame(false);
}

//-- Martin Webrant
