#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "player.h"
#include "weapons.h"

#include "ag/global.h"
#include "ag/rules.h"
#include "ag/gamemodes/ctf.h"
#include "ag/gamemodes/dom.h"
#include "ag/file_cache.h"

AgFileItem::AgFileItem()
{
	m_szName[0] = '\0';
	m_vOrigin = Vector(0, 0, 0);
	m_vAngles = Vector(0, 0, 0);
}

void AgFileItem::Show()
{
	CLaserSpot *pSpot = CLaserSpot::CreateSpot();
	UTIL_SetOrigin(pSpot->pev, m_vOrigin);
	pSpot->LiveForTime(5.0);
}

AgFileItemCache::~AgFileItemCache()
{
	for (AgFileItem *pItem : m_lstFileItems)
		delete pItem;
	m_lstFileItems.clear();
}

void AgFileItemCache::Add(const AgString &sFileItem, CBasePlayer *pPlayer)
{
	ASSERT(NULL != pPlayer);
	if (!pPlayer)
		return;
	ASSERT(NULL != pPlayer->pev);
	if (!pPlayer->pev)
		return;

	if (0 == sFileItem.size())
		return;

	AgFileItem *pFileItem = CreateItem();
	strcpy(pFileItem->m_szName, sFileItem.c_str());
	pFileItem->m_vOrigin = pPlayer->pev->origin;
	pFileItem->m_vAngles = pPlayer->pev->angles;

	m_lstFileItems.push_back(pFileItem);
	pFileItem->Show();

	Save(pPlayer);

	AgConsole(UTIL_VarArgs("Added item %s.", (const char *)sFileItem.c_str()), pPlayer);
}

void AgFileItemCache::Del(CBasePlayer *pPlayer)
{
	ASSERT(NULL != pPlayer);
	if (!pPlayer)
		return;
	ASSERT(NULL != pPlayer->pev);
	if (!pPlayer->pev)
		return;

	if (0 == m_lstFileItems.size())
		return;

	AgFileItem *pFileItem = m_lstFileItems.back();
	AgConsole(UTIL_VarArgs("Deleted last item - %s.", pFileItem->m_szName, pPlayer));
	m_lstFileItems.pop_back();
	delete pFileItem;
	Save(pPlayer);
}

void AgFileItemCache::List(CBasePlayer *pPlayer)
{
	ASSERT(NULL != pPlayer);
	if (!pPlayer)
		return;
	ASSERT(NULL != pPlayer->pev);
	if (!pPlayer->pev)
		return;

	for (AgFileItem *pFileItem : m_lstFileItems)
	{
		AgConsole(UTIL_VarArgs("%s", (const char *)pFileItem->m_szName), pPlayer);
		pFileItem->Show();
	}
}

void AgFileItemCache::Load(CBasePlayer *pPlayer)
{
	for (AgFileItem *pFileItem : m_lstFileItems)
		delete pFileItem;
	m_lstFileItems.clear();

	char szFile[MAX_PATH];
	char szData[20000];
	sprintf(szFile, "%s/%s/%s.%s", AgGetDirectory(), GetDirectory(), STRING(gpGlobals->mapname), GetExtension());
	FILE *pFile = fopen(szFile, "r");
	if (!pFile)
		return;

	int iRead = fread(szData, sizeof(char), sizeof(szData) - 2, pFile);
	fclose(pFile);
	if (0 >= iRead)
		return;
	szData[iRead] = '\0';

	char *pszLine = strtok(szData, "\n");
	while (pszLine != NULL)
	{
		AgFileItem *pItem = CreateItem();
		ParseItem(pItem, pszLine);
		m_lstFileItems.push_back(pItem);
		pszLine = strtok(NULL, "\n");
	}
}

void AgFileItemCache::Save(CBasePlayer *pPlayer)
{
	if (0 == m_lstFileItems.size())
		return;

	char szFile[MAX_PATH];
	sprintf(szFile, "%s/%s/%s.%s", AgGetDirectory(), GetDirectory(), STRING(gpGlobals->mapname), GetExtension());
	FILE *pFile = fopen(szFile, "wb");
	if (!pFile)
	{
		AgConsole(UTIL_VarArgs("Couldn't create/save FileItem file %s.", szFile), pPlayer);
		return;
	}

	for (AgFileItem *pFileItem : m_lstFileItems)
		WriteItem(pFile, pFileItem);

	fflush(pFile);
	fclose(pFile);
}

void AgFileItemCache::Init()
{
	if (m_bInitDone)
		return;
	m_bInitDone = true;

	for (AgFileItem *pFileItem : m_lstFileItems)
	{
		CBaseEntity *pEntity = nullptr;
		if (g_pGameRules->IsAllowedToSpawn(pFileItem->m_szName))
			pEntity = CBaseEntity::Create(pFileItem->m_szName, pFileItem->m_vOrigin, pFileItem->m_vAngles, INDEXENT(0));

		OnItemCreated(pFileItem, pEntity);
	}
}

AgFileItem *AgCTFFileItemCache::CreateItem()
{
	return new AgCTFFileItem;
}

bool AgCTFFileItemCache::ParseItem(AgFileItem *pItem, const char *pszLine)
{
	return 7 == sscanf(pszLine, "%s %f %f %f %f %f %f\n", pItem->m_szName, &pItem->m_vOrigin.x, &pItem->m_vOrigin.y, &pItem->m_vOrigin.z, &pItem->m_vAngles.x, &pItem->m_vAngles.y, &pItem->m_vAngles.z);
}

void AgCTFFileItemCache::WriteItem(FILE *pFile, AgFileItem *pItem)
{
	fprintf(pFile, "%s %f %f %f %f %f %f\n", pItem->m_szName, pItem->m_vOrigin.x, pItem->m_vOrigin.y, pItem->m_vOrigin.z,
	    pItem->m_vAngles.x, pItem->m_vAngles.y, pItem->m_vAngles.z);
}

AgFileItem *AgDOMFileItemCache::CreateItem()
{
	return new AgDOMFileItem;
}

bool AgDOMFileItemCache::ParseItem(AgFileItem *pItemBase, const char *pszLine)
{
	AgDOMFileItem *pItem = static_cast<AgDOMFileItem *>(pItemBase);
	return 8 == sscanf(pszLine, "%s %f %f %f %f %f %f %s\n", pItem->m_szName, &pItem->m_vOrigin.x, &pItem->m_vOrigin.y, &pItem->m_vOrigin.z, &pItem->m_vAngles.x, &pItem->m_vAngles.y, &pItem->m_vAngles.z, pItem->m_szData1);
}

void AgDOMFileItemCache::WriteItem(FILE *pFile, AgFileItem *pItemBase)
{
	AgDOMFileItem *pItem = static_cast<AgDOMFileItem *>(pItemBase);
	fprintf(pFile, "%s %f %f %f %f %f %f %s\n", pItem->m_szName, pItem->m_vOrigin.x, pItem->m_vOrigin.y, pItem->m_vOrigin.z,
	    pItem->m_vAngles.x, pItem->m_vAngles.y, pItem->m_vAngles.z, pItem->m_szData1);
}

void AgDOMFileItemCache::OnItemCreated(AgFileItem *pItemBase, CBaseEntity *pEntity)
{
	AgDOMFileItem *pItem = static_cast<AgDOMFileItem *>(pItemBase);
	if (FStrEq("item_dom_controlpoint", pItem->m_szName) && pEntity)
	{
		AgDOMControlPoint *pCP = (AgDOMControlPoint *)pEntity;
		strncpy(pCP->m_szLocation, pItem->m_szData1, sizeof(pCP->m_szLocation));
	}
}
