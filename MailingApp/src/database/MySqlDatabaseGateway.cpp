#include "MySqlDatabaseGateway.h"
#include "DBConnection.h"
#include "../imgui/imgui.h"
#include <cstdarg>

#include <time.h>

// You can use this function to create the SQL statements easily, works like the printf function
std::string stringFormat(const char *fmt, ...)
{
	// Find out the final string length
	va_list ap;
	va_start(ap, fmt);
	int size = vsnprintf(nullptr, 0, fmt, ap);
	va_end(ap);

	// Format the actual resulting string
	std::string resultString;
	resultString.resize(size + 1, '\0');
	va_start(ap, fmt);
	vsnprintf(&resultString[0], resultString.size(), fmt, ap);
	va_end(ap);

	return resultString;
}


MySqlDatabaseGateway::MySqlDatabaseGateway()
{
}


MySqlDatabaseGateway::~MySqlDatabaseGateway()
{
}

void MySqlDatabaseGateway::insertMessage(const Message & message)
{
	DBConnection db(bufMySqlHost, bufMySqlPort, bufMySqlDatabase, bufMySqlUsername, bufMySqlPassword);

	if (db.isConnected())
	{
		DBResultSet res;
		
		// Get time
		char str[26];

#ifdef __STDC_LIB_EXT1__
		struct tm buf;
		asctime_s(str, sizeof str, gmtime_s(&t, &buf));
		printf("UTC:   %s", str);
		asctime_s(str, sizeof str, localtime_s(&t, &buf));
		printf("local: %s", str);
#endif
		// ----

		std::string sqlStatement;
		// TODO: Create the SQL statement to insert the passed message into the DB (INSERT)
		sqlStatement = "INSERT INTO messages (sender, receiver, subject, message) VALUES ( (SELECT userid FROM user WHERE name = '" + message.senderUsername + "'), (SELECT userid FROM user WHERE name = '" + message.receiverUsername + "'), '" + message.subject + "', '" + message.body + "');";

		// insert some messages
		db.sql(sqlStatement.c_str());
	}
}

std::vector<Message> MySqlDatabaseGateway::getAllMessagesReceivedByUser(const std::string & username)
{
	std::vector<Message> messages;

	DBConnection db(bufMySqlHost, bufMySqlPort, bufMySqlDatabase, bufMySqlUsername, bufMySqlPassword);

	if (db.isConnected())
	{
		std::string sqlStatement;
		// TODO: Create the SQL statement to query all messages from the given user (SELECT)
		sqlStatement = "SELECT (SELECT name FROM user WHERE userid = (SELECT sender FROM messages WHERE receiver = (SELECT userid FROM user WHERE name = '" + username + "'))), (SELECT name FROM user WHERE userid = (SELECT receiver FROM messages WHERE receiver = (SELECT userid FROM user WHERE name = '" + username + "'))), subject, message, date  FROM messages WHERE receiver = (SELECT userid FROM user WHERE name = '" + username + "');";

		// consult all messages
		DBResultSet res = db.sql(sqlStatement.c_str());

		// fill the array of messages
		for (auto & messageRow : res.rows)
		{
			Message message;
			message.senderUsername = messageRow.columns[0];
			message.receiverUsername = messageRow.columns[1];
			message.subject = messageRow.columns[2];
			message.body = messageRow.columns[3];
			message.date = messageRow.columns[4];
			messages.push_back(message);
		}
	}


	return messages;
}

void MySqlDatabaseGateway::updateGUI()
{
	ImGui::Separator();

	ImGui::Text("MySQL Server info");
	ImGui::InputText("Host", bufMySqlHost, sizeof(bufMySqlHost));
	ImGui::InputText("Port", bufMySqlPort, sizeof(bufMySqlPort));
	ImGui::InputText("Database", bufMySqlDatabase, sizeof(bufMySqlDatabase));
	ImGui::InputText("Username", bufMySqlUsername, sizeof(bufMySqlUsername));
	ImGui::InputText("Password", bufMySqlPassword, sizeof(bufMySqlUsername), ImGuiInputTextFlags_Password);
}