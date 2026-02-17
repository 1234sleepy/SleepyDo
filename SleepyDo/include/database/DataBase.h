#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <pqxx/pqxx>

#include "../entities/Task.h"

class DbConfig
{
public:
	inline static const std::string connectionString{ "host=127.0.0.1 port=5432 dbname=postgres user=postgres password=postgrespw" };
};

class DataBase
{
public:
	DataBase(const std::string& connectionString) :
		_connectionString(connectionString)
	{
		if (!_connectionString.is_open())
		{
			std::cout << "DataBase connection failed";
		}

		pqxx::work txn(getConnectionString());

		txn.exec(R"(
			CREATE TABLE IF NOT EXISTS tasks(
			id SERIAL PRIMARY KEY,
			title TEXT NOT NULL,
			createdAt TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
			expiredAt TIMESTAMP NOT NULL)
		)");
		//Add important field as bool

		txn.commit();
	}

	std::vector<Task> getTasks();

	Task testRun()
	{
		pqxx::work txn(getConnectionString());
		
		pqxx::result r = txn.exec
		(R"(
			INSERT INTO tasks (title, expiredAt)
			VALUES ('Finish project', '2026-03-01 12:00:00')
			RETURNING *
		)");

		txn.commit();

		return Task{ 
			r[0]["id"].as<unsigned int>(),
			r[0]["title"].as<std::string>(),
			r[0]["createdAt"].as<std::string>(),
			r[0]["expiredAt"].as<std::string>()
		};
	}


	pqxx::connection& getConnectionString()
	{
		return _connectionString;
	}

	int getOffset() { return _offset; }

private:
	int _limit = 4;
	int _offset = 0;

	pqxx::connection _connectionString;
};