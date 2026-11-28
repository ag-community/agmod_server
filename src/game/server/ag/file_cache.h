#ifndef AG_GAMEMODE_FILE_CACHE_H
#define AG_GAMEMODE_FILE_CACHE_H

#include <cstdio>
#include <list>

#include "mathlib/vector.h"
#include "ag/global.h"

class CBaseEntity;
class CBasePlayer;

class AgFileItem
{
public:
	char m_szName[32];
	Vector m_vOrigin;
	Vector m_vAngles;

	AgFileItem();
	virtual ~AgFileItem() = default;

	void Show();
};

class AgFileItemCache
{
protected:
	bool m_bInitDone = false;
	std::list<AgFileItem *> m_lstFileItems;

	virtual const char *GetDirectory() const = 0;
	virtual const char *GetExtension() const = 0;
	virtual AgFileItem *CreateItem() = 0;
	virtual bool ParseItem(AgFileItem *pItem, const char *pszLine) = 0;
	virtual void WriteItem(FILE *pFile, AgFileItem *pItem) = 0;
	virtual void OnItemCreated(AgFileItem *pItem, CBaseEntity *pEntity) { }

	void Load(CBasePlayer *pPlayer = nullptr);
	void Save(CBasePlayer *pPlayer = nullptr);

public:
	virtual ~AgFileItemCache();

	void Reload() { Load(); }
	void Init();

	void Add(const AgString &sItem, CBasePlayer *pPlayer);
	void Del(CBasePlayer *pPlayer);
	void List(CBasePlayer *pPlayer);
};

#endif
