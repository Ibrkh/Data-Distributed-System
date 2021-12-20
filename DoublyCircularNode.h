#pragma once
#include<iostream>
using namespace std;

template<typename datatype>
class DoublyCircularNode
{
public:
	DoublyCircularNode* next;
	DoublyCircularNode* previous;

	datatype data;

	DoublyCircularNode()
	{
		next = NULL;
		previous = NULL;

		data = NULL;
	}

	DoublyCircularNode(datatype initial_value)
	{
		next = NULL;
		previous = NULL;

		data = initial_value;
	}

	~DoublyCircularNode()
	{
		//delete next;
		//delete previous;
	}
};
