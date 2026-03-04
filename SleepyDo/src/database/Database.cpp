#include "../../include/database/DataBase.h"

std::vector<Task> DataBase::getTasks()
{
	pqxx::work txn(getConnection());

	void sortTasks();

	std::string query = R"(
		SELECT id, title, createdAt, expiredAt, isImportant
		FROM tasks
		ORDER BY id DESC
	)";
	pqxx::params p;

	auto r = txn.exec(query, p);

	std::vector<Task> tasks;

	for (const auto& row : r)
	{
		tasks.emplace_back
		(
			row["id"].as<unsigned int>(),
			row["title"].as<std::string>(),
			row["createdAt"].as<std::string>(),
			row["expiredAt"].as<std::string>(),
			row["isImportant"].as<bool>()
		);
	}

	return tasks;
}

bool DataBase::removeTask(int id)
{
	pqxx::work txn(getConnection());

	std::string query = R"(
		DELETE FROM tasks
		WHERE id = $1
	)";

	pqxx::params p;

	p.append(id);

	auto r = txn.exec(query, p);

	txn.commit();

	return r.affected_rows() > 0;
}

int DataBase::addTask(const Task& task)
{
	pqxx::work txn(getConnection());

	std::string query = R"(
		INSERT INTO tasks (title, expiredAt, isImportant)
		VALUES ($1, $2, $3)
		RETURNING  id;
	)";

	pqxx::params p;

	p.append(task.title);
	p.append(task.expiredAt);
	p.append(task.isImportant);

	auto r = txn.exec(query, p);

	txn.commit();

	return r[0]["id"].as<unsigned int>();
}

bool DataBase::setTaskImportantToggle(int id)
{
	pqxx::work txn(getConnection());

	std::string query = R"(
		UPDATE tasks
		SET isImportant = NOT isImportant
		WHERE id = $1
		RETURNING isImportant
	)";

	pqxx::params p;

	p.append(id);

	auto r = txn.exec(query, p);

	txn.commit();

	return r[0][0].as<bool>();
}
