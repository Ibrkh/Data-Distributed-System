#pragma once
#include<fstream>
#include<string>
#include<iostream>
using namespace std;

class File
{
public:

	string FilePath;
	int LineNo;

	File()
	{
		FilePath = "";
		LineNo = 0;
	}

	File(string filepath)
	{
		ofstream file;

		FilePath = filepath;
		LineNo = 0;

		file.open(FilePath, ios::out | ios::app);
		file.close();
	}
};
