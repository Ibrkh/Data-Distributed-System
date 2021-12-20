#pragma once

#include"../DS_Project/DoublyCircularNode.h"
#include<iostream>
using namespace std;

template<typename datatype>
class DoubleLinkedList
{
private:
	DoublyCircularNode<datatype>* head;

public:
	DoubleLinkedList()
	{
		head = NULL;
	}

	void insertFirst(datatype initial_value)
	{
		DoublyCircularNode<datatype>* newNode = new DoublyCircularNode<datatype>(initial_value);

		if (head == NULL)
		{
			head = newNode;
			newNode->previous = head;
			head->previous = newNode;
			newNode->next = head;
		}
		else if (head != NULL)
		{
			DoublyCircularNode<datatype>* ptr = head;

			while (ptr->next != head)
				ptr = ptr->next;

			ptr->next = newNode;
			newNode->previous = ptr;
			head->previous = newNode;
			newNode->next = head;

			head = newNode;
		}
	}

	void insertAt(int index, datatype initial_value)
	{
		DoublyCircularNode <datatype>* newNode = new DoublyCircularNode<datatype>(initial_value);
		DoublyCircularNode <datatype>* ptr = head;
		int counter = 1;

		if (index <= 0)
		{
			cout << "\nInvalid index.. cannot insert node\n" << endl;

			return;
		}
		else if (index == 1)
		{
			insertFirst(initial_value);
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

	void insertLast(datatype initial_value)
	{
		DoublyCircularNode<datatype>* newNode = new DoublyCircularNode<datatype>(initial_value);

		if (head == NULL)
		{
			head = newNode;
			newNode->previous = head;
			head->previous = newNode;
			newNode->next = head;
		}
		else if (head != NULL)
		{
			DoublyCircularNode<datatype>* ptr = head;

			while (ptr->next != head)
				ptr = ptr->next;

			ptr->next = newNode;
			newNode->previous = ptr;
			head->previous = newNode;
			newNode->next = head;
		}
	}

	void removeNode(int index)
	{
		DoublyCircularNode<datatype>* ptr = head;
		DoublyCircularNode<datatype>* temp = NULL;
		int counter = 1;

		if (index <= 0)
		{
			cout << "\nInvalid index.. cannot remove node\n" << endl;
		}
		else if (index == 1)
		{
			while (ptr->next != head)
				ptr = ptr->next;

			temp = head->next;
			ptr->next = temp;
			temp->previous = ptr;

			head = temp;
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

	void replaceNodeAt(int index, datatype initial_value)
	{
		DoublyCircularNode <datatype>* ptr = head;
		int counter = 1;

		if (index <= 0)
		{
			cout << "\nInvalid index.. cannot replace node\n" << endl;
		}
		else if (index == 1)
		{
			head->data = initial_value;
		}
		else
		{
			while (counter < index - 1)
			{
				ptr = ptr->next;
				counter++;
			}

			ptr->next->data = initial_value;
		}
	}

	DoublyCircularNode<datatype>* NodeIndex(int index)
	{
		DoublyCircularNode <datatype>* ptr = head;
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
		DoublyCircularNode <datatype>* ptr = head;
		datatype temp = NULL;
		int counter = 1;

		while (ptr->next != head)
		{
			ptr = ptr->next;
			counter++;
		}

		for (int i = 0; i < counter; i++)
		{
			for (int j = i + 1; j < counter; j++)
			{
				if (NodeIndex(i)->data > NodeIndex(j)->data)
				{
					temp = NodeIndex(i)->data;
					NodeIndex(i)->data = NodeIndex(j)->data;
					NodeIndex(j)->data = temp;
				}
			}
		}
	}

	void ReverseList()
	{
		DoublyCircularNode <datatype>* ptr = head;
		DoublyCircularNode <datatype>* prev = NULL;
		DoublyCircular <datatype>* next = NULL;


		do {
			next = ptr->next;
			ptr->next = prev;

			prev = ptr;
			ptr = next;
		} while (ptr != head);

		// adjutsing the links so as to make the 
		// last node point to the first node 
		head->next = prev;
		head = prev;
	}

	void displayList()
	{
		if (head == NULL)
		{
			cout << "Linked List is empty.." << endl;
		}
		else if (head != NULL)
		{
			DoublyCircularNode <datatype>* ptr = head;
			int counter = 1;

			cout << "\n**Linked List Elements**\n" << endl;

			do {
				cout << "List Element[" << counter << "]: " << ptr->data << endl;

				ptr = ptr->next;
				counter++;

			} while (ptr != head);

			cout << endl;
		}
	}

	~DoubleLinkedList()
	{
		delete head;
	}
};