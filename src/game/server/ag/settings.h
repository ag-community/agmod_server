//++ BulliT

#pragma once

class AgSettings
{
	bool m_bChangeNextLevel;
	bool m_bCheckNextMap;
	bool m_bCalcNextMap;
	float m_fNextCheck;
	void CalcNextMap();

public:
	AgSettings();
	virtual ~AgSettings();

	bool Think();

	void SetNextLevel(const AgString &sMap);
	AgString GetNextLevel();
	void ChangeNextLevel();

	void Changelevel(const AgString &sMap);
	bool AdminSetting(const AgString &sSetting, const AgString &sValue); // Not all settings is allowed.
};

//-- Martin Webrant
