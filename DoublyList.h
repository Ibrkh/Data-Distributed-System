#pragma once
#include"../DS-Project/DoublyNode.h"
#include"../DS-Project/SinglyCircular.h"
#include<iostream>
using namespace std;

class DoubleLinkedList
{
public:

	DoublyNode* head;

public:

	DoubleLinkedList() : head(nullptr) {
	}

	void insertFirst(SinglyCircularNode*& address);

	void insertAt(int index, SinglyCircularNode*& address);

	void insertLast(SinglyCircularNode* address);

	void removeNode(int index);

	void replaceNodeAt(int index, SinglyCircularNode*& address);

	void displayList();

	~DoubleLinkedList() {
		//delete head;
	}
};





