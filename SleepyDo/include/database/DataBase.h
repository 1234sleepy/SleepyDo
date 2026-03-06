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
private:
	pqxx::connection _connectionString;

public:
	DataBase(const std::string& connectionString) :
		_connectionString(connectionString)
	{
		if (!_connectionString.is_open())
		{
			std::cout << "DataBase connection failed";
		}

		pqxx::work txn(getConnection());

		txn.exec(R"(
			CREATE TABLE IF NOT EXISTS tasks(
			id SERIAL PRIMARY KEY,
			title TEXT NOT NULL,
			createdAt TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
			expiredAt TIMESTAMP NOT NULL,
			isImportant BOOLEAN DEFAULT FALSE)
		)");

		txn.commit();
	}

	std::vector<Task> getTasks();

	bool removeTask(int id);
	bool setTaskImportantToggle(int id);

	Task addTask(const Task& task);

	pqxx::connection& getConnection()
	{
		return _connectionString;
	}

};