//++ BulliT

#include <map>

#pragma once

typedef std::map<AgString, int, std::less<AgString>> AgScoreLogMap;

class AgScoreLog
{
	float m_fNextLogUpdate;
	void EndScore();

public:
	AgScoreLog();
	virtual ~AgScoreLog();

	void Think();

	void Start();
	void End();
	void Score();

	void GetScores(AgScoreLogMap &mapScores);
};

//-- Martin Webrant
