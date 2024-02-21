#pragma once
#include "Task.h"
class Node
{
public:
	Task data;
	Node* next;

	Node(const Task& newData) : data(newData), next(nullptr) {}
};

