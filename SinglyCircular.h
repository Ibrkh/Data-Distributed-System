#pragma once
#include "../DS-Project/SinglyCircularNode.h"
#include <cmath>
#include<iostream>
using namespace std;


class CircularLinkedList
{
public:

	SinglyCircularNode* head;

	CircularLinkedList() : head(nullptr)
	{
	}

	SinglyCircularNode* successor(int parameter, int NoOfpossibleMachine)
	{
		int temp = parameter;

		if (temp > (NoOfpossibleMachine - 1))
			temp = temp - NoOfpossibleMachine;

		SinglyCircularNode* ptr = head;

		do
		{
			if (temp > ptr->machineId)
				ptr = ptr->next;
			else if (temp < ptr->machineId)
			{
				if (temp < NoOfpossibleMachine)
					temp++;
			}
			else if (temp == ptr->machineId)
			{
				cout << endl;
				//cout << "Internal" << endl;
				//cout << "MachineID: " << ptr->machineId;
				return ptr;
			}

		} while (ptr != head);

		cout << endl;
		//cout << "External" << endl;
		//cout << "MachineID: " << ptr->machineId;
		return ptr;
	}

	void GenerateFTable(int currMachineId, SinglyCircularNode* ptr)
	{
		for (int i = 1, j = 0; j < ptr->IdentifierBits; i++, j++)
		{
			int p = currMachineId;
			int secondParameter = pow(2, (i - 1));
			int parameter = p + secondParameter;

			SinglyCircularNode* address = successor(parameter,
				pow(2, ptr->IdentifierBits));
			ptr->FingerTable.insertLast(address);
		}

	}

	void SearchFingerTable(SinglyCircularNode* MachinePtr, bool& found, Data& Obj)
	{
		DoublyNode* NodePtr = MachinePtr->FingerTable.head;

		while (NodePtr != nullptr)
		{
			NodePtr->MachineAddress->Machine.searchData(Obj, found);
			if (found == true)
				return;

			NodePtr = NodePtr->next;
		}
	}


	SinglyCircularNode* getMachine(int temp)
	{
		SinglyCircularNode* ptr = head;

		do
		{
			if (temp > ptr->machineId)
				ptr = ptr->next;
			else if (temp < ptr->machineId)
				temp++;
			else if (temp == ptr->machineId)
			{
				cout << endl;
				//cout << "Internal" << endl;
				//cout << "MachineID: " << ptr->machineId;
				return ptr;
			}

		} while (ptr != head);

		cout << endl;
		//cout << "External" << endl;
		//cout << "MachineID: " << ptr->machineId;
		return ptr;
	}

	void insertFirst(int mID, int Bits)
	{
		SinglyCircularNode* newNode = new SinglyCircularNode(mID, Bits);
		SinglyCircularNode* ptr = head;

		if (head == NULL)
		{
			head = newNode;
			newNode->next = head;
		}
		else if (head != NULL)
		{
			while (ptr->next != head)
				ptr = ptr->next;

			ptr->next = newNode;

			newNode->next = head;
			head = newNode;
		}
	}

	void insertAt(int index, int mID, int Bits)
	{
		SinglyCircularNode* newNode = new SinglyCircularNode(mID, Bits);
		SinglyCircularNode* ptr = head;

		if (index < 0)
		{
			cout << "\nInvalid index.. cannot insert node\n" << endl;
		}
		else if (index == 1)
		{
			insertFirst(mID, Bits);
		}
		else
		{
			int counter = 1;

			while (counter < index - 1)
			{
				ptr = ptr->next;
				counter++;
			}

			newNode->next = ptr->next;
			ptr->next = newNode;
		}
	}

	void insertLast(int machineId, int Bits)
	{
		SinglyCircularNode* newNode = new SinglyCircularNode(machineId, Bits);
		SinglyCircularNode* ptr = head;

		if (head == NULL)
		{
			head = newNode;
			newNode->next = head;
		}
		else
		{
			while (ptr->next != head)
			{
				ptr = ptr->next;
			}

			ptr->next = newNode;
			newNode->next = head;
		}
	}

	void replaceNodeAt(int index, int mID, int Bits)
	{
		SinglyCircularNode* ptr = head;
		int counter = 1;

		if (index < 0)
		{
			cout << "\nInvalid index.. cannot replace node\n" << endl;
		}
		else if (index == 1)
		{
			head->machineId = mID;
		}
		else
		{
			while (counter < index - 1)
			{
				ptr = ptr->next;
				counter++;
			}

			ptr->next->machineId = mID;
		}
	}

	void removeNodeAt(int index)
	{
		SinglyCircularNode* ptr = head;
		SinglyCircularNode* temp = nullptr;


		if (index <= 0)
		{
			cout << "\nInvalid index.. cannot remove node\n" << endl;
		}
		else if (index == 1)
		{
			// head = head->next;

			temp = head->next;
			head = temp;
		}
		else
		{
			int counter = 1;

			while (counter < index - 1)
			{
				ptr = ptr->next;
				counter++;
			}

			//ptr->next = ptr->next->next;

			temp = ptr->next->next;
			ptr->next = temp;
		}
	}

	void DisplayList()
	{
		if (head == nullptr)
		{
			cout << "Linked List is empty.." << endl;
		}
		else
		{
			SinglyCircularNode* ptr = head;
			AVLNode* tempAVL = ptr->Machine.root;

			int counter = 0;

			cout << "\n**Linked List Elements**\n" << endl;

			do
			{
				tempAVL = ptr->Machine.root;
				counter = ptr->machineId;

				cout << "Machine ID[" << counter << "]" << endl;
				ptr->Machine.printPreorder(tempAVL);
				cout << endl << endl;

				ptr = ptr->next;

			} while (ptr != head);
		}
	}

	SinglyCircularNode* NodeIndex(int index)
	{
		SinglyCircularNode* ptr = head;
		int counter = 0;

		while (1)
		{
			if (counter == index)
			{
				return ptr;
			}

			ptr = ptr->next;
			counter++;
		}

		return ptr;
	}

	void sortList()
	{
		SinglyCircularNode* ptr = head;
		int counter = 1;
		int temp;

		while (ptr->next != head)
		{
			ptr = ptr->next;
			counter++;
		}

		for (int i = 0; i < counter; i++)
		{
			for (int j = i + 1; j < counter; j++)
			{
				if (NodeIndex(i)->machineId > NodeIndex(j)->machineId)
				{
					temp = NodeIndex(i)->machineId;
					NodeIndex(i)->machineId = NodeIndex(j)->machineId;
					NodeIndex(j)->machineId = temp;
				}
			}
		}
	}

	//void clearList()
	//{
	//	SinglyCircularNode * ptr = head;
	//	ptr->machineId = NULL;
	//	ptr->IdentifierBits = NULL;
	//	delete ptr->fileobj;
	//	
	//	while (ptr->next != head)
	//	{
	//		ptr = ptr->next;
	//		ptr->data = NULL;
	//	}
	//}

	~CircularLinkedList()
	{

	}
};


