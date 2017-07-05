#include <iostream>
#include <string>
#include <fstream>
#include <dirent.h>
#include <regex>
#include <vector>

using namespace std;

#define EQ_PATH "C:\\Users\\Public\\Daybreak Game Company\\Installed Games\\EverQuest"

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

bool isRaidDump(string filename)
{
	regex pattern("RaidRoster");
	return regex_search(filename.begin(), filename.end(), pattern);
}

int main()
{
	DIR *eqDir = NULL;
	struct dirent *ent = NULL;
	eqDir = opendir(EQ_PATH);
	if (!eqDir)
		cout << "Couldn't find EQ directory at: " << EQ_PATH << endl;

	vector<string> fileList;

	// prints a list of all files in the directory
	while (ent = readdir(eqDir))
	{
		if (!ent)
			cout << "Error initializing dirent structure!\n";
		else
			if (isRaidDump(ent->d_name))
				fileList.push_back(ent->d_name);
	}

	for (auto i = fileList.begin(); i != fileList.end(); ++i)
	{
		cout << *i << endl;
	}

	// next: search (regex?) for all files with a specific name scheme
	// push_back file names into a vector?
	// process each file and save in a local folder. :)

	closedir(eqDir);
	system("pause");
	return 0;
}