//++ BulliT

#include "extdll.h"
#include "util.h"
#include "ag/global.h"
#include "ag/score.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AgScore::AgScore()
{
	m_iFrags = 0;
	m_iDeaths = 0;
	m_bIngame = false;
}

AgScore::~AgScore()
{
}

//-- Martin Webrant
