#pragma once

#include "EQ-Raid-Dump-Parser.h"
class InputFile
{
private:
	string filename;
public:
	ifstream inFile;
	InputFile(string filename);
	~InputFile();
	ifstream & getIfstream();
};

InputFile::InputFile(string filename)
{
	cout << "Opening input file: " << filename << "\n\n";
	inFile.open(filename);
}

ifstream & InputFile::getIfstream()
{
	return inFile;
}

InputFile::~InputFile()
{
	cout << "\nClosing " << filename << "\n";
	inFile.close();
}