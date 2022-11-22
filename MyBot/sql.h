#pragma once

#include <sqlapi/SQLAPI.h>
#include <spdlog/spdlog.h>

void SQLCon() {
	SAConnection con;

	try {
		con.Connect(_TSA("my_db"), _TSA("my_user"), _TSA("my_password"), SA_MariaDB_Client);
		printf("We are connected!\n");


		con.Disconnect();
		printf("We are disconnected!\n");
	}
	catch (SAException& x) {
		con.Rollback();
		printf("%s\n", x.ErrText().GetMultiByteChars());
	}
}