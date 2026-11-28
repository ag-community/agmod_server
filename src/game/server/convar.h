#pragma once

#include <algorithm>

#include "cvardef.h"

enum class ConItemType
{
	ConVar
};

/**
 * ConItemBase - the base class for ConVar and ConCommand.
 */
class ConItemBase
{
public:
	ConItemBase(const char *name);
	ConItemBase(const char *name, const char *desc);
	ConItemBase(const ConItemBase &) = delete;
	virtual ~ConItemBase();

	virtual ConItemType GetType() = 0;

	const char *GetName();
	const char *GetDescription();

	ConItemBase &operator=(const ConItemBase &) = delete;

private:
	const char *m_pName;
	const char *m_pDesc;

	ConItemBase *m_pNextItem = nullptr;
	static ConItemBase *m_pFirstItem;

	friend class CvarSystem;
};

/**
 * ConVar - a Source-like way to register cvars.
 */
class ConVar : public ConItemBase
{
public:
	ConVar(const char *name, const char *def_val, int flags = 0);
	ConVar(const char *name, const char *def_val, int flags, const char *desc);

	virtual ConItemType GetType();

	const char *GetDefaultValue();
	int GetFlags();

	float GetFloat() { return GetCvar()->value; }
	int GetInt() { return (int)GetCvar()->value; }
	bool GetBool() { return !!GetInt(); }
	const char *GetString() { return GetCvar()->string; }

	template <typename T>
	T GetEnumClamped()
	{
		const int minValue = static_cast<int>(T::_Min);
		const int maxValue = static_cast<int>(T::_Max);
		return static_cast<T>(std::clamp(GetInt(), minValue, maxValue));
	}

	void SetValue(float val);
	void SetValue(int val);
	void SetValue(const char *val);

	cvar_t *GetCvar();

private:
	const char *m_pDefVal;
	int m_iFlags;

	cvar_t m_Cvar = {};

	friend class CvarSystem;
};

inline cvar_t *ConVar::GetCvar()
{
	return &m_Cvar;
}

/**
 * ConVarRef - a reference to an existing cvar.
 */
class ConVarRef
{
public:
	ConVarRef(const char *name);
	ConVarRef(cvar_t *cvar);
	ConVarRef(ConVar &cvar);
	ConVarRef(ConVar *cvar);

	const char *GetName();

	bool IsValid();

	float GetFloat();
	int GetInt();
	bool GetBool();
	const char *GetString();

	void SetValue(float val);
	void SetValue(int val);
	void SetValue(const char *val);

	cvar_t *GetCvar();

private:
	const char *m_pName = nullptr;
	cvar_t *m_pCvar = nullptr;
};

/**
 * CvarSystem - cvar manager
 */
class CvarSystem
{
public:
	static void RegisterCvars();
	static ConItemBase *FindItem(const char *name);
	static ConVar *FindCvar(const char *name);
	static ConVar *FindCvar(cvar_t *cvar);
};
