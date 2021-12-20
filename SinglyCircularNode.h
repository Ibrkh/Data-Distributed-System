#pragma once
#include<iostream>
#include "../DS-Project/File.h"
#include "../DS-Project/DoublyNode.h"
#include "../DS-Project/DoublyList.h"
#include "../DS-Project/AVLTree.h"

class DoubleLinkedList;

class SinglyCircularNode
{
public:

	SinglyCircularNode* next;
	AVLTree Machine;
	int IdentifierBits;
	int machineId;
	File fileobj;
	DoubleLinkedList FingerTable;

public:

	SinglyCircularNode() : next(nullptr), IdentifierBits(-1), machineId(-1) {
	}


	SinglyCircularNode(int mID, int bits) : next(nullptr), machineId(mID), IdentifierBits(bits) {

		string filepath = "MachineID";
		filepath += to_string(machineId);
		filepath += ".txt";

		File temp(filepath);
		fileobj = temp;
	}


	void SearchFingerTable(SinglyCircularNode* node, bool& found, Data& toSearch) {
		DoublyNode* temp = node->FingerTable.head;
		while (temp->next != nullptr) {
			temp->MachineAddress->Machine.Search(node->Machine.root, toSearch, found);
			temp = temp->next;
		}

	}

	~SinglyCircularNode()
	{
		//delete next;
	}
};


void DoubleLinkedList::insertFirst(SinglyCircularNode*& address)
{
	DoublyNode* newNode = new DoublyNode(address);

	if (head == NULL)
	{
		head = newNode;
		newNode->previous = head;
	}
	else if (head != NULL)
	{
		newNode->next = head;
		head->previous = newNode;
		head = newNode;
	}
}

void DoubleLinkedList::insertAt(int index, SinglyCircularNode*& address)
{
	DoublyNode* newNode = new DoublyNode(address);
	DoublyNode* ptr = head;
	int counter = 1;

	if (index <= 0)
	{
		cout << "\nInvalid index.. cannot insert node\n" << endl;

		return;
	}
	else if (index == 1)
	{
		insertFirst(address);
	}
	else
	{
		while (counter < index - 1)
		{
			ptr = ptr->next;
			counter++;
		}

		newNode->next = ptr->next;
		ptr->next->previous = newNode;
		ptr->next = newNode;
		newNode->previous = ptr;
	}
}

void DoubleLinkedList::insertLast(SinglyCircularNode* address) {

	DoublyNode* newNode = new DoublyNode(address);
	//cout << "address id : " << newNode->MachineAddress->machineId << endl;
	DoublyNode* last = head;
	newNode->next = NULL;


	if (head == NULL) {
		newNode->previous = NULL;

		head = newNode;
		return;
	}
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = newNode;
		newNode->previous = last;
		return;
	}

}

void DoubleLinkedList::removeNode(int index)
{
	DoublyNode* ptr = head;
	DoublyNode* temp = NULL;
	int counter = 1;

	if (index <= 0)
	{
		cout << "\nInvalid index.. cannot remove node\n" << endl;

	}
	else if (index == 1)
	{
		temp = head->next;
		head = temp;
		head->previous = head;
	}
	else
	{
		while (counter < index - 1)
		{
			ptr = ptr->next;
			counter++;
		}

		temp = ptr->next->next;
		ptr->next->next->previous = temp;
		ptr->next = temp;
		temp->previous = ptr;
	}
}

void DoubleLinkedList::replaceNodeAt(int index, SinglyCircularNode*& address)
{
	DoublyNode* ptr = head;
	int counter = 1;

	if (index < 0)
	{
		cout << "\nInvalid index.. cannot replace node\n" << endl;
	}
	else if (index == 1)
	{
		head->MachineAddress = address;
	}
	else
	{
		while (counter < index - 1)
		{
			ptr = ptr->next;
			counter++;
		}

		ptr->next->MachineAddress = address;
	}
}

void DoubleLinkedList::displayList()
{

	DoublyNode* ptr = head;
	int count = 1;

	while (ptr != NULL)
	{
		cout << "\tList Element[" << count << "]: " << ptr->MachineAddress->machineId << endl;
		ptr = ptr->next;
		count++;
	}
	cout << endl;
}
