#pragma once
#include"SinglyCircular.h"
#include<iostream>
using namespace std;

class SinglyCircularNode;

class DoublyNode {
public:
	DoublyNode* next;
	DoublyNode* previous;
	SinglyCircularNode* MachineAddress;
public:


	DoublyNode() : next(nullptr), previous(nullptr), MachineAddress(nullptr) {
	}

	DoublyNode(SinglyCircularNode* address) : next(nullptr), previous(nullptr) {
		MachineAddress = address;
		//cout << "address id : " << MachineAddress->machineId << endl;
	}

	~DoublyNode() {

	}
};
