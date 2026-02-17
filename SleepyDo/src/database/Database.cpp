#include "../../include/database/DataBase.h"

std::vector<Task> DataBase::getTasks()
{
	pqxx::work txn(getConnectionString());

	std::string query = R"(
		SELECT id, title, createdAt, expiredAt
		FROM tasks
		ORDER BY id DESC
		LIMIT $1 OFFSET $2
	)";

	pqxx::params p;

	p.append(_limit);
	p.append(_offset);

	auto r = txn.exec(query, p);

	std::vector<Task> tasks;

	for (const auto& row : r)
	{
		tasks.emplace_back
		(
			row["id"].as<unsigned int>(),
			row["title"].as<std::string>(),
			row["createdAt"].as<std::string>(),
			row["expiredAt"].as<std::string>()
		);
	}

	_offset+=4;

	return tasks;
}