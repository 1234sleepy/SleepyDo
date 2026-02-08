#pragma once

#include <iostream>
#include <string>
#include <pqxx/pqxx>


class DbConfig
{
public:
	inline static const std::string connectionString{ "Host=postgres;Port=5432;Database=shop-db;Username=postgres;Password=postgrespw" };
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
	}

	pqxx::connection& getConnectionString()
	{
		return _connectionString;
	}
private:
	pqxx::connection _connectionString;
};