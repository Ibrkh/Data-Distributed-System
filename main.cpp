#pragma once
#include"../DS-Project/SinglyCircular.h"
#include "AVLTree.h"
#include <ctime>
#include<windows.h>
#include "SHA1.h"
#include <cstring>
#include <string>


int stringToInt(string hashValue)
{
	int decimal = 0;
	for (int i = 0; i < hashValue.length(); i++)
		decimal += hashValue[i];

	return decimal;
}

unsigned getDataID(const string key, unsigned bits)
{
	const string hash = sha1(key);
	int decimal = stringToInt(hash);
	int maxMachines = pow(2, bits);
	unsigned int DataId = decimal % maxMachines;
	return DataId;
}

string getRandomString()
{

	string temp = "";
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	srand((unsigned)time(NULL));

	temp.reserve(16);

	for (int i = 0; i < 16; ++i)
		temp += alphanum[rand() % (sizeof(alphanum) - 1)];

	return temp;
}


int getMachineId(int bits) {

	string ip_address = getRandomString();
	string hash = sha1(ip_address);
	int decimal = stringToInt(hash);
	int maxMachines = pow(2, bits);
	int MachineId = decimal % maxMachines;
	return MachineId;
}


void setMachindIDs(CircularLinkedList& DHT, unsigned& Bits, unsigned& numMachines)
{

	while (true)
	{
		cout << "\nEnter the number of Machines to activate in the DHT Ring \n";
		cin >> numMachines;

		if (numMachines > pow(2, Bits))
		{
			cout << "Machines cannot be Greater than " << pow(2, Bits) << " , Enter Again \n ";
			continue;
		}
		else
			break;
	}

label_again:

	unsigned choice;
	cout << "\nPress 1 to manually assign Machine Ids or 0 to set Automatically \n";
	cin >> choice;

	unsigned mID;
	vector<unsigned> dupID;
	bool flag = false;
	switch (choice)
	{

	case 1:
	{

		for (int loop = 0; loop < numMachines; loop++)
		{
			while (true)
			{
				cout << "\nEnter machineID of Machine " << (loop + 1) << "\n";
				cin >> mID;

				if (mID > (pow(2, Bits) - 1))
				{
					cout << "Limit exceeded  of space , Enter the machineID again of Machine: " << (loop + 1) << endl;
					continue;
				}
				else
				{
					if (mID < pow(2, Bits))
					{
						for (int checkdup = 0; checkdup < dupID.size(); checkdup++)
						{
							if (mID == dupID[checkdup])
								flag = true;
						}

						if (flag == true)
						{
							cout << "Duplicate Machine ID , Enter Again\n";
							flag = false;
							continue;
						}
						else
						{
							DHT.insertLast(mID, Bits);
							dupID.emplace_back(loop);
							break;
						}
					}
				}
			}
		}

		DHT.sortList();

		break;
	}

	case 0:
	{
		for (int loop = 0; loop < numMachines; loop++)
		{

			while (true)
			{
				mID = getMachineId(Bits);

				for (int checkdup = 0; checkdup < dupID.size(); checkdup++)
				{
					if (mID == dupID[checkdup])
						flag = true;
				}

				if (flag == true)
				{
					flag = false;
					continue;
				}
				else
				{
					dupID.emplace_back(mID);
					DHT.insertLast(mID, Bits);
					break;
				}
			}
		}

		DHT.sortList();
		break;
	}

	default:
	{
		cout << "Wrong Input! ,Enter Again\n";
		goto label_again;
	}

	}
}

void FileWriting(string Filename, string value)
{
	ofstream file;
	file.open(Filename, ios::out | ios::app);
	file << value << endl;
	file.close();
}

string FileReading(Data& Obj) {
	
	fstream file;
	file.open(Obj.Path, ios::out | ios::app | ios::in);

	char ch;
	int count = 1;	// we initialize count = 1; cause' the cursor is already on line 1

	string line;

	while (file.eof() != true) 
	{
		if (count == Obj.LineNo)
		{
			getline(file, line);
			return line;
		}
		
		file.get(ch);

		if(ch == '\n')
			count++;
	}

	file.close();
}

string updateFile(Data& Obj)
{
	fstream inputFile;
	fstream outputFile;
	string tempStr;
	int count = 1;

	inputFile.open(Obj.Path, ios::in);

	if (!inputFile)
	{
		cout << "Error in Opening Source File...!!!";
		return 0;
	}

	string textFile = "temp.txt";

	std::ofstream::trunc;

	outputFile.open(textFile, ios::out | ios:: app);

	if (!outputFile)
	{
		cout << "Error in Opening Destination File...!!!";
		inputFile.close();
		return 0;
	}

	string returnValue = "";


		while (inputFile.eof() != true)
		{
			getline(inputFile, tempStr);

			if (Obj.LineNo != count)
				outputFile << tempStr << "\n";
			else if (Obj.LineNo == count)
			{
				outputFile << endl;
				returnValue = tempStr;
			}
				
			count++;
		}


		inputFile.close();
		outputFile.close();

		count = 0;

		outputFile.open(textFile, ios::in );
		inputFile.open(Obj.Path, ios::out | ios::trunc);


		while (outputFile.eof() != true)
		{
			getline(outputFile, tempStr);

			inputFile << tempStr;

		}

	///////////////////////////////////

	int n1 = Obj.Path.length();
	char  *destinationfile = new char [n1];
	int i;
	for(i=0;i<n1;i++)
	{
		destinationfile[i] = Obj.Path[i];
	}
	destinationfile[i] = '\0';

	//rename("temp.txt", Obj.Path);
	int n2 = textFile.length();
	char  *sourcefile = new char [n2+1];
	

	int j;
	for(j=0;j<n2;j++)
	{
		sourcefile[j] = textFile[j];
	}
	sourcefile[j] = '\0';

	inputFile.close();
	outputFile.close();

	return returnValue;
}

void DHTIterator(CircularLinkedList& DHT, unsigned int DataID, Data& obj)
{
	unsigned int tempID = DataID;
	SinglyCircularNode* temp = DHT.head;
	AVLNode* tempAVlNode = nullptr;

	do {
		if (tempID > temp->machineId)
			temp = temp->next;
		else if (tempID == temp->machineId)
		{
			obj.Path = temp->fileobj.FilePath;
			temp->fileobj.LineNo++;
			obj.LineNo = temp->fileobj.LineNo;

			FileWriting(obj.Path, obj.value);

			cout << "**MachineID: " << temp->machineId << "**" << endl;
			tempAVlNode = temp->Machine.root;
			tempAVlNode = temp->Machine.insert(tempAVlNode, obj);
			return;
		}
		else if (tempID < temp->machineId)
			tempID++;
	} while (temp != DHT.head);


	obj.Path = temp->fileobj.FilePath;
	temp->fileobj.LineNo++;
	obj.LineNo = temp->fileobj.LineNo;

	FileWriting(obj.Path, obj.value);

	cout << "**MachineID: " << temp->machineId << "**" << endl;
	tempAVlNode = temp->Machine.root;
	tempAVlNode = temp->Machine.insert(tempAVlNode, obj);
	return;

}

void insertDHT(CircularLinkedList& DHT, unsigned& Bits)
{
	unsigned choice;
	Data tempData;
	unsigned DataID;
	int input;

	//cout << "Enter the MachineID from which you want to Insert Data... " << endl; cin >> input;

	cout << "Enter the data in (key, value) pairs...\n";
	cout << "Press 1 to continue.. Press 0 to exit..." << endl;
	cin >> choice;

	while (choice != 0)
	{
		cout << "Enter Data Key: "; cin >> tempData.key;
		cout << "Enter Data Value: "; cin >> tempData.value;

		DataID = getDataID(tempData.key, Bits);
		DHTIterator(DHT, DataID, tempData);

		cout << "Press 1 to continue.. Press 0 to exit..." << endl;
		cin >> choice;
	}
}

void PrintData(const CircularLinkedList& DHT, int machineID)
{
	SinglyCircularNode* temp = DHT.head;

	do
	{
		AVLNode* ptr = temp->Machine.root;

		if (temp->machineId == machineID)
		{
			cout << endl << "MachineID: " << temp->machineId << endl;
			temp->Machine.printPreorder(ptr);
			cout << endl; cout << endl;
		}
		temp = temp->next;
	} while (temp != DHT.head);
}

void SearchDHT1(CircularLinkedList& DHT , unsigned mSearch)	// For reading the data
{
	Data Obj;
	string tempStr;
	bool found = false;
	bool status = false;

	cout << "\nEnter Key to search data in DHT\n";
	cin >> Obj.key;

	int DataId = getDataID(Obj.key, DHT.head->IdentifierBits);

	//cout << "**DataID: " << DataId << "**" << endl;

	SinglyCircularNode* MachinePtr = DHT.getMachine(mSearch);
	//loop -> NoOfEntriesinfingerTable     
	cout << "Search path followed  : " <<MachinePtr->machineId << " -> ";
	do
	{
		DoublyNode* NodePtr = MachinePtr->FingerTable.head;
		
		if (MachinePtr->machineId == DataId) // p = e
		{
			MachinePtr->Machine.searchData(Obj, found);

			if (found) {
				cout << endl << "Value inside MachineID" << MachinePtr->machineId << " : " << FileReading(Obj) << endl;
				break;
			}
			else if (!found) {
				cout << "\nValue not found in MachineID" << MachinePtr->machineId << endl;
				MachinePtr = MachinePtr->next;
			}

		}
		else if (MachinePtr->machineId < DataId && DataId <= NodePtr->MachineAddress->machineId)  //p < e and e ≤ FTp [1].
		{
			NodePtr->MachineAddress->Machine.searchData(Obj, found);

			if (found) {
				cout << "Value found in FingerTable[1] of MachineID " << MachinePtr->machineId << " : " << FileReading(Obj) << endl;
				cout << "FingerTable[1] of MachineID: " << MachinePtr->machineId << ", which corresponds to MachineID: " << NodePtr->MachineAddress->machineId << endl;
				break;
			}
			else if (!found) {
				cout << "\nValue not found in MachineID" << MachinePtr->machineId << endl;
				MachinePtr = MachinePtr->next;
				}
		}
		else
		{
			while (NodePtr->next != nullptr)
			{
				if (NodePtr->MachineAddress->machineId < DataId && DataId <= NodePtr->next->MachineAddress->machineId)	// FTp[j] < e ≤ FTp[ j+1].
				{
					//NodePtr->MachineAddress->Machine.searchData( Obj, found);
					//if (found)
					//	cout << "Value found in FingerTable : " << Obj.value << endl;
					//else if (!found)
					cout << "MachineID: " << MachinePtr->machineId << " -> ";
					MachinePtr = NodePtr->MachineAddress;
					//cout << "-> " << MachinePtr->machineId << " -> ";
					status = true;

					if (DataId <= MachinePtr->machineId) {
						while (true) {

							if (DataId == MachinePtr->machineId) {
								MachinePtr->Machine.searchData(Obj, found);

								if (found) {
									cout << endl << "Value inside MachineID " << MachinePtr->machineId << " : " << FileReading(Obj) << endl;
									break;
								}
								else if (!found) {
									cout << "\nValue not found in MachineID" << MachinePtr->machineId << endl;
									MachinePtr = MachinePtr->next;
								}
							}
							else
								DataId++;

						}

					}

					break;
				}
				else
					NodePtr = NodePtr->next;
			}
		}
		if (status == false)
			MachinePtr = MachinePtr->next;
	} while (found != true);

	cout << "Search END !" << endl;
}

void SearchDHT2(CircularLinkedList& DHT)	// For removal of data
{
	Data Obj;
	string tempStr;
	bool found = false;
	bool status = false;

	cout << "\nEnter Key to Remove data from DHT\n";
	cin >> Obj.key;

	int DataId = getDataID(Obj.key, DHT.head->IdentifierBits);

	//cout << "**DataID: " << DataId << "**" << endl;

	SinglyCircularNode* MachinePtr = DHT.head;
	//loop -> NoOfEntriesinfingerTable     
	cout << "Search path followed  : " << MachinePtr->machineId << " -> ";
	do
	{
		DoublyNode* NodePtr = MachinePtr->FingerTable.head;

		if (MachinePtr->machineId == DataId) // p = e
		{
			MachinePtr->Machine.searchData(Obj, found);

			if (found) {
				cout << endl << "Value inside MachineID" << MachinePtr->machineId << " : " << updateFile(Obj) << endl;
				break;
			}
			else if (!found) {
				cout << "\nValue not found in MachineID" << MachinePtr->machineId << endl;
				MachinePtr = MachinePtr->next;
			}
		}
		else if (MachinePtr->machineId < DataId && DataId <= NodePtr->MachineAddress->machineId)  //p < e and e ≤ FTp [1].
		{
			NodePtr->MachineAddress->Machine.searchData(Obj, found);

			if (found) {
				cout << "Value found in FingerTable[1] of MachineID " << MachinePtr->machineId << " : " << updateFile(Obj) << endl;
				cout << "FingerTable[1] of MachineID: " << MachinePtr->machineId << ", which corresponds to MachineID: " << NodePtr->MachineAddress->machineId << endl;
				break;
			}
			else if (!found) {
				cout << "\nValue not found in MachineID" << MachinePtr->machineId << endl;
				MachinePtr = MachinePtr->next;
			}
		}
		else
		{
			while (NodePtr->next != nullptr)
			{
				if (NodePtr->MachineAddress->machineId < DataId && DataId <= NodePtr->next->MachineAddress->machineId)	// FTp[j] < e ≤ FTp[ j+1].
				{
					//NodePtr->MachineAddress->Machine.searchData( Obj, found);
					//if (found)
					//	cout << "Value found in FingerTable : " << Obj.value << endl;
					//else if (!found)
					cout << "MachineID: " << MachinePtr->machineId << " -> ";
					MachinePtr = NodePtr->MachineAddress;
					//cout << "-> " << MachinePtr->machineId << " -> ";
					status = true;

					if (DataId <= MachinePtr->machineId) {
						while (true) {

							if (DataId == MachinePtr->machineId) {
								MachinePtr->Machine.searchData(Obj, found);

								if (found) {
									cout << endl << "Value inside MachineID " << MachinePtr->machineId << " : " << updateFile(Obj) << endl;
									break;
								}
								else if (!found) {
									cout << "\nValue not found in MachineID" << MachinePtr->machineId << endl;
									MachinePtr = MachinePtr->next;
								}
							}
							else
								DataId++;

						}

					}

					break;
				}
				else
					NodePtr = NodePtr->next;
			}
		}
		if (status == false)
			MachinePtr = MachinePtr->next;
	} while (found != true);

	cout << "Removal Complete !" << endl;
}

void PrintFingerTable(const CircularLinkedList& DHT, int machineID) {

	SinglyCircularNode* temp = DHT.head;

	do
	{
		if (temp->machineId == machineID)
		{
			cout << "\t**Finger Table [" << temp->machineId << "]**\n" << endl;
			temp->FingerTable.displayList();
			cout << endl;
		}
		temp = temp->next;
	} while (temp != DHT.head);
}

void AddMachine(CircularLinkedList& DHT, unsigned bits) {
	unsigned mID;
	while (true) {
		cout << "Enter New Machine ID\n";
		cin >> mID;
		if(mID > pow(2 , bits) - 1 ){
			cout<<"Machine Id out of range\n";
	    continue;	
		}
		else
			break;
	}
	DHT.insertLast(mID, bits);
	DHT.sortList();
}

void RemoveMachine(CircularLinkedList & DHT) {

}

void DisplayMenu()
{
	cout << "\t\t\t\t\t\t\t\t\t******************** CS218: Data Structures (Fall 2020) ********************" << endl;
	cout << "\t\t\t\t\t\t\t\t\t***************************** Semester Project ******************************\n\n" << endl;

	cout << "1. Set Machine IDs in the Ring \n";
	cout << "2. Insert Data in DHT \n";
	cout << "3. Check Machines \n";
	cout << "4. Search Data in DHT\n";
	cout << "5. Print Machine Data \n";
	cout << "6. Print FingerTable \n";
	cout << "7. Remove Data from DHT \n";
	cout << "8. Add New Machine in  DHT \n";
	cout << "9. Clear Screen \n";
	cout << "0. Exit Program \n";

}

void checkMachines(const CircularLinkedList & DHT ) {
	SinglyCircularNode* ptr = DHT.head;
	cout << "\nChecking the empty machines" << endl;
	ptr = DHT.head;
	do {
		cout << ptr->Machine.isEmpty();
		ptr = ptr->next;
	} while (ptr != DHT.head);
}

int main() {

	cout << "\t\t\t\t\t\t\t\t\t******************** CS218: Data Structures (Fall 2020) ********************" << endl;
	cout << "\t\t\t\t\t\t\t\t\t***************************** Semester Project ******************************\n\n" << endl;

	cout << "\t\t\t\t\t\t\t\t\t************************** Distributed Hash Table ***************************\n\n" << endl;

	cout << "*Project Description\n" << endl;

	cout << "We are considering a scenario where the data is not located on a single machine but rather stored on multiple machines go - distributed across the Internet.\nIn such a scenario, searching or retrieval of data ";
	cout << "is very challenging, as it is hard to determine on which machine the required data is stored.\nThe data structures used for efficiently search data stored on a single machine such as hash tables cannot be directly";
	cout << "employed in a distributed environment.\n\n";
	cout << "Typically, data is stored as a key, value pair. For example, key might be the name of the student or the student ID and value is the complete information \n";
	cout << "about the student. Likewise, the key can be the name of the patient and value can be the medical record. Similarly, the key can be the name of an image file\n";
	cout << "and value represents the file itself.\n\n";
	cout << "A distributed hash table (DHT) provides a lookup (or search) service similar to a hash table: (key,value) pairs are stored in a DHTand any participating machine\n";
	cout << "can efficiently retrieve the value	associated with a given key.Responsibility for maintaining the mapping from keys to values is distributed among the machines.\n\n\n";

	cout << "\t\t\t\t\t\t\t\t\t\t\tGroup Members:  Section: BS(CS19)-G\n" << endl; 
	cout << "\t\t\t\t\t\t\t\t\t\t     1. Syed Iftikhar Mehdi ~ Rollno: i19-0657" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t     2. Talha Khan ~ Rollno: i19-0657" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t     3. Ahmed Ibrahim Khan ~ Rollno: k19-0312" << endl;


	int input;

	cout << "Press 1 to continue.. " << endl;
	cin >> input;

	if (input == 1)
		system("cls");

	system("cls");

	unsigned choice;
	CircularLinkedList DHT;
	unsigned Bits = 0;
	unsigned mSeacrh = 0;
	
	cout << "\t\t\t\t\t\t\t\t\t******************** CS218: Data Structures (Fall 2020) ********************" << endl;
	cout << "\t\t\t\t\t\t\t\t\t***************************** Semester Project ******************************\n\n" << endl;


			Bits = 0;
			cout << "Enter Bits in Identifier space: \n";
			cin >> Bits;

			system("cls");

	do {
		DisplayMenu();
		cin >> choice;

		switch (choice) {
		case 1: {
			unsigned numMachines = 0;
			setMachindIDs(DHT, Bits, numMachines);

			// generating FT Tables for machines in DHT
			SinglyCircularNode* ptr = DHT.head;
			int FT = 0;
			do {
				DHT.GenerateFTable(ptr->machineId, ptr);
				cout << endl;
				FT++;
				ptr = ptr->next;
			} while (FT < numMachines && ptr != DHT.head);

			cout << "Press 1 to continue.. " << endl;
			cin >> input;
			
			if(input == 1)
			system("cls");
			break;
		}

		case 2: {

			insertDHT(DHT, Bits);

				system("cls");
				break;
		}

		case 3: {

			checkMachines(DHT);

			cout << "Press 1 to continue.. " << endl;
			cin >> input;

			if (input == 1)
				system("cls");
				break;
		}

		case 4: {
			cout << "\nEnter the MachineID from which you want to start the Search Process :  "; cin >> mSeacrh;
			SearchDHT1(DHT, mSeacrh);

			cout << "Press 1 to continue.. " << endl;
			cin >> input;

			if (input == 1)
				system("cls");
			break;
		}

		case 5: {

			int mID;

			cout << "\nEnter the MachineID for which you want to print the Machine AVLTree Data :"; cin >> mID;
			PrintData(DHT, mID);

			cout << "Press 1 to continue.. " << endl;
			cin >> input;

			if (input == 1)
				system("cls");
			break;

		}

		case 6: {

			int mID;

			cout << "\nEnter the MachineID for which you want to print the FingerTable : "; cin >> mID;

			PrintFingerTable(DHT, mID);
			cout << "Press 1 to continue.. " << endl;
			cin >> input;

			if (input == 1)
				system("cls");
			break;
		}

		case 7: {
			int data;

			SearchDHT2(DHT);
			cout << "Press 1 to continue.. " << endl;
			cin >> input;

			if (input == 1)
			system("cls");
			break;
		}

		case 8: {
			cout << "New Machine Added in DHT\n";
			break;
		}

		case 9: {
			system("cls");
			break;
		}


		case 0: {
			exit(1);
			break;
		}

		default:
			cout << "Invalid Choice.";
		}
	} while (choice != 0);


	cout << "\nControl returned to System. \n";
	return 0;
}