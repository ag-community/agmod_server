//++ BulliT

#pragma once

#include "ag/admin.h"
#include "ag/global.h"
#include <list>

class CBasePlayer;

// Contains list of all admins and ability to save/load/restore and admin.
class AgAdminCache
{
	typedef std::list<AgAdmin *> AgAdminList;
	AgAdminList m_lstAdmins;

public:
	AgAdminCache();
	virtual ~AgAdminCache();

	void RestoreAdmin(CBasePlayer *pPlayer);
	void Load();
	void Save(CBasePlayer *pPlayer = NULL);

	void AddAdmin(const AgString &sAdmin, const AgString &sPassword, CBasePlayer *pPlayer = NULL);
	void ListAdmins(CBasePlayer *pPlayer = NULL);
	void DelAdmin(const AgString &sAdmin, CBasePlayer *pPlayer = NULL);

	void Auth(const AgString &sAdmin, const AgString &sPassword, CBasePlayer *pPlayer);
	void Newpass(const AgString &sOldpassword, const AgString &sPassword, CBasePlayer *pPlayer);
};

extern DLL_GLOBAL AgAdminCache AdminCache;

//-- Martin Webrant
