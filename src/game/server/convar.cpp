#include <cstdlib>
#include <map>
#include <string>

#include "extdll.h"
#include "enginecallback.h"
#include "convar.h"

ConItemBase *ConItemBase::m_pFirstItem = nullptr;

ConItemBase::ConItemBase(const char *name)
    : ConItemBase(name, "")
{
}

ConItemBase::ConItemBase(const char *name, const char *desc)
{
	m_pName = name;
	m_pDesc = desc;
	m_pNextItem = m_pFirstItem;
	m_pFirstItem = this;
}

ConItemBase::~ConItemBase()
{
}

const char *ConItemBase::GetName()
{
	return m_pName;
}

const char *ConItemBase::GetDescription()
{
	return m_pDesc;
}

ConVar::ConVar(const char *name, const char *def_val, int flags)
    : ConVar(name, def_val, flags, "")
{
}

ConVar::ConVar(const char *name, const char *def_val, int flags, const char *desc)
    : ConItemBase(name, desc)
{
	m_pDefVal = def_val;
	m_iFlags = flags;

	GetCvar()->name = const_cast<char *>(GetName());
	GetCvar()->string = const_cast<char *>(GetDefaultValue());
	GetCvar()->flags = GetFlags();
	GetCvar()->value = std::atof(GetDefaultValue());
}

ConItemType ConVar::GetType()
{
	return ConItemType::ConVar;
}

const char *ConVar::GetDefaultValue()
{
	return m_pDefVal;
}

int ConVar::GetFlags()
{
	return m_iFlags;
}

void ConVar::SetValue(float val)
{
	CVAR_SET_FLOAT(GetName(), val);
}

void ConVar::SetValue(int val)
{
	SetValue(static_cast<float>(val));
}

void ConVar::SetValue(const char *val)
{
	CVAR_SET_STRING(GetName(), val);
}

ConVarRef::ConVarRef(const char *name)
{
	m_pCvar = CVAR_GET_POINTER(name);
	m_pName = name;
}

ConVarRef::ConVarRef(cvar_t *cvar)
{
	if (cvar)
	{
		m_pCvar = cvar;
		m_pName = cvar->name;
	}
}

ConVarRef::ConVarRef(ConVar &cvar)
    : ConVarRef(cvar.GetCvar())
{
}

ConVarRef::ConVarRef(ConVar *cvar)
    : ConVarRef(*cvar)
{
}

const char *ConVarRef::GetName()
{
	return m_pName;
}

bool ConVarRef::IsValid()
{
	return m_pCvar != nullptr;
}

float ConVarRef::GetFloat()
{
	if (m_pCvar)
		return m_pCvar->value;

	return 0.0f;
}

int ConVarRef::GetInt()
{
	return static_cast<int>(GetFloat());
}

bool ConVarRef::GetBool()
{
	return !!GetInt();
}

const char *ConVarRef::GetString()
{
	if (m_pCvar)
		return m_pCvar->string;

	return "";
}

void ConVarRef::SetValue(float val)
{
	if (m_pCvar)
		CVAR_SET_FLOAT(m_pCvar->name, val);
}

void ConVarRef::SetValue(int val)
{
	SetValue(static_cast<float>(val));
}

void ConVarRef::SetValue(const char *val)
{
	if (m_pCvar)
		CVAR_SET_STRING(m_pCvar->name, val);
}

cvar_t *ConVarRef::GetCvar()
{
	return m_pCvar;
}

static std::map<std::string, ConItemBase *> s_ItemNameMap;
static std::map<cvar_t *, ConVar *> s_CvarMap;

void CvarSystem::RegisterCvars()
{
	for (ConItemBase *item = ConItemBase::m_pFirstItem; item; item = item->m_pNextItem)
	{
		s_ItemNameMap[item->GetName()] = item;

		if (item->GetType() == ConItemType::ConVar)
		{
			ConVar *cvar = static_cast<ConVar *>(item);
			CVAR_REGISTER(cvar->GetCvar());
			s_CvarMap[cvar->GetCvar()] = cvar;
		}
	}
}

ConItemBase *CvarSystem::FindItem(const char *name)
{
	auto it = s_ItemNameMap.find(name);
	if (it == s_ItemNameMap.end())
		return nullptr;

	return it->second;
}

ConVar *CvarSystem::FindCvar(const char *name)
{
	ConItemBase *item = FindItem(name);
	if (item && item->GetType() == ConItemType::ConVar)
		return static_cast<ConVar *>(item);

	return nullptr;
}

ConVar *CvarSystem::FindCvar(cvar_t *cvar)
{
	auto it = s_CvarMap.find(cvar);
	if (it == s_CvarMap.end())
		return nullptr;

	return it->second;
}
