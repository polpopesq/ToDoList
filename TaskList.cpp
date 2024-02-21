#include "TaskList.h"
#include <string>
#include <fstream>

TaskList::TaskList() : head(nullptr) {}

void TaskList::append(const Task& task)
{
	Node* newNode = new Node(task);
	if (head == nullptr)
	{
		head = newNode;
	}
	else
	{
		Node* current = head;
		while (current->next != nullptr)
		{
			current = current->next;
		}
		current->next = newNode;
	}
}

void TaskList::clear()
{
	Node* current = head;
	while (current != nullptr)
	{
		Node* next = current->next;
		delete current;
		current = next;
	}
	head = nullptr;
}

void TaskList::deleteTask(Task& toDelete)
{
		Node* current = head;
		if (!(current->data != toDelete))
		{
			head = current->next;
			delete current;
		}
		else
		{
			while (current->next->data != toDelete && current->next != nullptr)
			{
				current = current->next;
			}
			if (current->next == nullptr)
			{
				throw exception("Task to delete does not exist!");
			}
			else
			{
				Node* toBeDeleted = current->next;
				current->next = toBeDeleted->next;
				delete toBeDeleted;
			}
		}
		
}

void TaskList::deleteTask(int number)
{
	int counter = 1;
	Node* current = head;
	while (counter < number && current != nullptr)
	{
		current = current->next;
		counter++;
	}
	if (current == nullptr)
	{
		throw exception("Selected task does not exist!");
	}
	else
	{
		deleteTask(current->data);
	}
}

void TaskList::showAll()
{
	cout << "Task list:" << endl;
	int counter = 0;
	Node* current = head;
	while (current != nullptr)
	{
		counter++;
		cout << counter << ". " << current->data << endl;
		current = current->next;
	}
	if (counter == 0)
	{
		cout << "You have no tasks. ";
	}
	else if (counter == 1)
	{
		cout << "This is your task. ";
	}
	else
	{
		cout << "These are all your " << counter << " tasks. ";
	}
}

void TaskList::update(int number)
{
	int counter = 1;
	Node* current = head;
	while (counter < number && current != nullptr)
	{
		current = current->next;
		counter++;
	}
	if (current == nullptr)
	{
		throw exception("Selected node does not exist!");
	}
	else
	{
		current->data.changeIt();
	}
}

void TaskList::deserializeAll(const string& file)
{
	ifstream f(file, ios::binary);
	if (!f.is_open())
	{
		f.close();
		throw NoAccountException("You haven't logged in with this name before. Creating new file.\n");
	}

	Task t;
	while (t.deserialize(f))
	{
		append(t); 
	}

	f.close();
}

void TaskList::serializeAll(const string& file)
{
	ofstream f(file, ios::binary);
	if (!f.is_open())
	{
		cerr << "Error opening file." << endl;
	}

	Node* current = head;
	while (current != nullptr)
	{
		current->data.serialize(f);
		current = current->next;
	}
	if (f.fail())
	{
		cerr << "Error!!!!" << endl;
	}

	f.close();
}