//++ BulliT

#pragma once

// The admin user
class AgAdmin
{
public:
	AgAdmin();
	virtual ~AgAdmin();

	AgString m_sAdmin;
	AgString m_sPassword;
	AgString m_sAuthID;
};

//-- Martin Webrant
