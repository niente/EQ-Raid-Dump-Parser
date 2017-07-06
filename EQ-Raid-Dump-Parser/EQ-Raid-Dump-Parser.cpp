#include <iostream>
#include <string>
#include <fstream>
#include <dirent.h>
#include <regex>
#include <vector>

using namespace std;

#define EQ_PATH "C:\\Users\\Public\\Daybreak Game Company\\Installed Games\\EverQuest"

class Directory
{
public:
	DIR *dir;
	struct dirent *ent;
	Directory();
	~Directory();
	Directory(string path);
};

Directory::Directory()
{
	dir = nullptr;
	ent = nullptr;
}



Directory::Directory(string path)
{
	dir = opendir(path.c_str());
	if (!dir)
		cout << "Couldn't find target directory at: " << path << endl;
	ent = nullptr;
}

Directory::~Directory()
{
	closedir(dir);
}

class FileList
{
private:
	Directory *directory;
	vector<string> filenames;
	string delimiter;
public:
	FileList();
	void setDelimiter(string d);
	void setDirectory(Directory *d);
	void buildFileList();
	bool isRaidDump(string s);
};

FileList::FileList()
{
	delimiter = "";
}

void FileList::setDelimiter(string d)
{
	delimiter = d;
}

void FileList::setDirectory(Directory *d)
{
	directory = d;
}

void FileList::buildFileList()
{
	// prints a list of all files in the directory
	while (directory->ent = readdir(directory->dir))
	{
		if (!directory->ent)
			cout << "Error initializing dirent structure!\n";
		else
			if (isRaidDump(directory->ent->d_name))
				filenames.push_back(directory->ent->d_name);
	}

	for (auto i = filenames.begin(); i != filenames.end(); ++i)
	{
		cout << *i << endl;
	}
}

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

ifstream &InputFile::getIfstream()
{
	return inFile;
}

InputFile::~InputFile()
{
	cout << "\nClosing " << filename << "\n";
	inFile.close();
}

bool FileList::isRaidDump(string filename)
{
	regex pattern("RaidRoster-\\d{8}-\\d{6}\.txt");
	return regex_search(filename.begin(), filename.end(), pattern);
}

int main()
{
	Directory eqDir(EQ_PATH);
	FileList raidDumps;
	raidDumps.setDirectory(&eqDir);
	raidDumps.buildFileList();

	// process each file and save in a local folder.

	
	system("pause");
	return 0;
}