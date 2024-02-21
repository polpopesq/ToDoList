#pragma once
#include "Node.h"

class NoAccountException : public exception
{
public:
	NoAccountException() : exception() {}
	NoAccountException(const char* message) : exception(message) {}
};

class TaskList
{
private:
	Node* head;

public:
	TaskList();
	void append(const Task& task);
	void clear();
	void deleteTask(Task& toDelete);
	void deleteTask(int number);
	void showAll();
	void update(int number);
	void deserializeAll(const string& file);
	void serializeAll(const string& file);
};

