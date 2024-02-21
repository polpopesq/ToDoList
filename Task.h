#pragma once
#include "Date.h"

class Task
{
private:
	string name;
	string description;
	Date dateAdded;
	DateAndTime deadline;
	bool completed;
	int priority;
public:
	string getPriority();
	Task();
	Task(string name, string description, DateAndTime deadline, int priority);
	void markCompleted();
	void changeName(string newName);
	void changeDescription(string newDescription);
	void changePriority(int newPriority);
	bool isCompleted();
	bool operator!=(Task t);
	friend ostream& operator<<(ostream& out, Task t);
	friend istream& operator>>(istream& in, Task& t);
	void operator=(const Task& t);
	void changeIt();
	bool deserialize(ifstream& f);
	void serialize(ofstream& f);
};

