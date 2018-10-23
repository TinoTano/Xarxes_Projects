#pragma once

#include "IDatabaseGateway.h"

class MySqlDatabaseGateway :
	public IDatabaseGateway
{
public:

	// Constructor and destructor

	MySqlDatabaseGateway();

	~MySqlDatabaseGateway();


	// Virtual methods from IDatabaseGateway

	void insertMessage(const Message &message) override;

	std::vector<Message> getAllMessagesReceivedByUser(const std::string &username) override;

	virtual void updateGUI() override;

private:

	// Text buffers for ImGUI
	char bufMySqlHost[64] = "sql2.freemysqlhosting.net";
	char bufMySqlPort[64] = "3306";
	char bufMySqlDatabase[64] = "sql2262471";
	char bufMySqlTable[64] = "messages";
	char bufMySqlUsername[64] = "sql2262471";
	char bufMySqlPassword[64] = "gY8!qZ8*";
};

