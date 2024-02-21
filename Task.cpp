#include "Task.h"
#include "Date.h"
#include <string>
#include <fstream>

using namespace std;

Task::Task()
{
	name = "";
	description = "";
	completed = false;
	priority = 0;
}
Task::Task(string name, string description, DateAndTime deadline, int priority)
{
	this->name = name;
	this->description = description;

	Date d;
	if (deadline.getYear() == d.getYear())
	{
		if (deadline.getMonth() == d.getMonth())
		{
			if (deadline.getDay() < d.getDay())
			{
				this->deadline = d;
			}
		}
		else if (deadline.getMonth() < d.getMonth())
		{
			this->deadline = d;
		}
	}
	else if (deadline.getYear() < d.getYear())
	{
		this->deadline = d;
	}
	this->deadline = deadline;

	if (priority < 0 && priority > 5)
	{
		this->priority = 0;
	}
	this->priority = priority;
	completed = false;
}
string Task::getPriority()
{
	switch (priority) {
	case 0:
		return "Not set";
	case 1:
		return "Low";
	case 2:
		return "Moderate";
	case 3:
		return "Medium";
	case 4:
		return "High";
	case 5:
		return "Critical";
	default:
		return "Invalid priority";
	}
}
void Task::markCompleted()
{
	completed = true;
}
void Task::changeName(string newName)
{
	if (newName.length() > 2)
	{
		name = newName;
	}
	else
	{
		throw exception("Invalid name!");
	}
}
void Task::changeDescription(string newDescription)
{
	description = newDescription;
}
void Task::changePriority(int newPriority)
{
	if (priority > 0 && priority < 6)
	{
		priority = newPriority;
	}
	else
	{
		throw exception("Invalid priority!");
	}
}
bool Task::isCompleted()
{
	return completed;
}
bool Task::operator!=(Task t)
{
	if (this->name != t.name)
	{
		return true;
	}
	if (this->description != t.description)
	{
		return true;
	}
	if (this->priority != t.priority)
	{
		return true;
	}
	if (this->completed != t.completed)
	{
		return true;
	}
	if (this->deadline.getDate() != t.deadline.getDate())
	{
		return true;
	}
	if (this->dateAdded.getDate() != t.dateAdded.getDate())
	{
		return true;
	}
	return false;
}

ostream& operator<<(ostream& out, Task t)
{
	out << t.name << endl;
	out << t.description << endl;
	out << "Deadline: " << t.deadline << endl;
	out << "Priority: " << t.getPriority() << endl;
	if (t.completed == 1)
	{
		out << "Task done.";
	}
	else
	{
		out << "Task not done.";
	}
	cout << "\n";
	return out;
}
istream& operator>>(istream& in, Task& t)
{
	string name;
	cout << "Task name: ";
	in >> ws;
	getline(in, name);
	if (name.length() > 2)
	{
		t.changeName(name);
	}
	cout << "Task description: ";
	getline(in, t.description);
	cout << "Deadline" << endl;
	try 
	{
		in >> t.deadline;
	}
	catch (exception e)
	{
		cerr << e.what();
	}
	cout << "On a scale from 1 to 5, how important is it?\n";
	int priority;
	in >> priority;
	if (priority > 0 && priority < 6)
	{
		t.priority = priority;
	}
	else
	{
		t.priority = 0;
	}
	cout << "Is it completed yet? (Y/N)\n";
	char completed;
	in >> completed;
	if (completed == 'y' || completed == 'Y')
	{
		t.completed = 1;
	}
	else if (completed == 'n' || completed == 'N')
	{
		t.completed = 0;
	}
	return in;
}
void Task::operator=(const Task& t)
{
	this->name = t.name;
	this->description = t.description;
	this->deadline = t.deadline;
	this->completed = t.completed;
	this->priority = t.priority;
}
void Task::changeIt()
{
	char resp;
	cout << "Change task name? (Y/N) ";
	cin >> resp;
	if (resp == 'y' || resp == 'Y')
	{
		cout << "New name: ";
		string newName = "";
		getline(cin, newName);
		while (newName.length() < 2)
		{
			cout << "More than 2 characters, please!" << endl;
			getline(cin, newName);
		}
		name = newName;
	}
	cout << "Change description? (Y/N) ";
	cin >> resp;
	if (resp == 'y' || resp == 'Y')
	{
		cout << "New description:" << endl;
		getline(cin, description);
	}
	cout << "Change deadline? (Y/N) ";
	cin >> resp;
	if(resp == 'Y' || resp == 'y')
	{
		cout << "New deadline:" << endl;
		try
		{
			cin >> deadline;
		}
		catch (exception e)
		{
			cerr << e.what();
		}
	}
	string comp;
	isCompleted() ? comp = "completed" : comp = "not completed";
	cout << "Task is currently marked as " << comp << ". Change it?(Y/N) ";
	cin >> resp;
	if (resp == 'y' || resp == 'Y')
	{
		completed = !completed;
	}
	cout << "Change priority? (Y/N) ";
	cin >> resp;
	if (resp == 'y' || resp == 'Y')
	{
		cout << "New priority: ";
		int newPriority;
		cin >> newPriority;
		try
		{
			changePriority(newPriority);
		}
		catch (exception e)
		{
			cerr << e.what();
		}
	}
}
bool Task::deserialize(ifstream& f)
{
	int length = 0;
	f.read((char*)&length, sizeof(length));
	if (f.eof())
	{
		return false;
	}
	char* buffer = new char[length];
	f.read(buffer, length);
	name.assign(buffer, length);
	delete[] buffer;

	length = 0;
	f.read((char*)&length, sizeof(length));
	char* buffer2 = new char[length];
	f.read(buffer2, length);
	description.assign(buffer2, length);
	delete[] buffer2;

	dateAdded.deserialize(f);
	deadline.deserialize(f);
	f.read((char*)&completed, sizeof(char));
	f.read((char*)&priority, sizeof(priority));
	return true;
}
void Task::serialize(ofstream& f)
{
	int length;
	length = name.length();
	f.write((char*)&length, sizeof(length));
	f.write(name.c_str(), length);

	length = description.length();
	f.write((char*)&length, sizeof(length));
	f.write(description.c_str(), length);

	dateAdded.serialize(f);
	deadline.serialize(f);
	f.write((char*)&completed, sizeof(char));
	f.write((char*)&priority, sizeof(priority));
}
