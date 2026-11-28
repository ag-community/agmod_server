//++ BulliT

#pragma once

class AgClient
{
public:
	AgClient();
	virtual ~AgClient();

	enum say_type
	{
		All,
		Team,
		Close
	};
	bool HandleCommand(CBasePlayer *pPlayer);
	void Say(CBasePlayer *pPlayer, say_type Type);
	void Play(CBasePlayer *pPlayer, say_type Type, const char *pszWave);
};

//-- Martin Webrant
