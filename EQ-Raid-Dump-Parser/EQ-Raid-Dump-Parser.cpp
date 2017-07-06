#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <regex>
#include <vector>
#include <unordered_map>

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
	vector<string> getFilenames();
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
	while (directory->ent = readdir(directory->dir))
	{
		if (!directory->ent)
			cout << "Error initializing dirent structure!\n";
		else
			if (isRaidDump(directory->ent->d_name))
			{
				string fpath = EQ_PATH;
				fpath += "\\";
				fpath += directory->ent->d_name;
				//cout << fpath << endl;
				filenames.push_back(fpath);
			}
	}

	for (auto i = filenames.begin(); i != filenames.end(); ++i)
	{
		cout << *i << endl;
	}
}

bool FileList::isRaidDump(string filename)
{
	regex pattern("RaidRoster-\\d{8}-\\d{6}\.txt");
	return regex_search(filename.begin(), filename.end(), pattern);
}

vector<string> FileList::getFilenames()
{
	return filenames;
}

class OutputData
{
public:
	int grp;
	string name;
	int level;
	string playerclass;
	friend ostream &operator<<(ostream &os, const OutputData &output);
};

ostream &operator<<(ostream &os, const OutputData &output)
{
	os << output.grp << " " << output.playerclass << " " << output.name << endl;
	return os;
}

class RaidDumpParser
{
private:
	string filename;
	string line;
	stringstream ss;
	ifstream inFile;
	vector<string> *fileList;
	unordered_map<string, string> classFormat;
	OutputData lineData;
	vector<OutputData> output;
public:
	RaidDumpParser(vector<string> *fList);
	void buildClassFormatMap();
	void parse();
	void printOutput();
};

RaidDumpParser::RaidDumpParser(vector<string> *fList)
{
	fileList = fList;
}

void RaidDumpParser::buildClassFormatMap()
{
	classFormat["Bard"] = "[COLOR=\"White\"]BRD[/COLOR]";
	classFormat["Beastlord"] = "[COLOR=\"Green\"]BST[/COLOR]";
	classFormat["Berserker"] = "[COLOR=\"Lime\"]BER[/COLOR]";
	classFormat["Cleric"] = "[COLOR=\"Cyan\"]CLR[/COLOR]";
	classFormat["Druid"] = "[COLOR=\"Teal\"]DRU[/COLOR]";
	classFormat["Enchanter"] = "[COLOR=\"DarkRed\"]ENC[/COLOR]";
	classFormat["Magician"] = "[COLOR=\"Red\"]MAG[/COLOR]";
	classFormat["Monk"] = "[COLOR=\"Lime\"]MNK[/COLOR]";
	classFormat["Necromancer"] = "[COLOR=\"Purple\"]NEC[/COLOR]";
	classFormat["Paladin"] = "[COLOR=\"Orange\"]PAL[/COLOR]";
	classFormat["Ranger"] = "[COLOR=\"Green\"]RNG[/COLOR]";
	classFormat["Rogue"] = "[COLOR=\"Lime\"]ROG[/COLOR]";
	classFormat["Shadow"] = "[COLOR=\"Orange\"]SHD[/COLOR]";
	classFormat["Shaman"] = "[COLOR=\"Teal\"]SHM[/COLOR]";
	classFormat["Warrior"] = "[COLOR=\"Yellow\"]WAR[/COLOR]";
	classFormat["Wizard"] = "[COLOR=\"Red\"]WIZ[/COLOR]";
}

void RaidDumpParser::parse()
{
	filename = fileList->at(0);
	string temp;
	inFile.open(filename);
	cout << "Opening " << fileList->at(0) << endl;
	while (getline(inFile, line))
	{
		ss << line;

		ss >> lineData.grp;
		ss >> lineData.name;
		ss >> lineData.level;
		ss >> lineData.playerclass;

		output.push_back(lineData);
		ss.str("");
		ss.clear();
	}
}

void RaidDumpParser::printOutput()
{
	for (auto i = output.begin(); i != output.end(); ++i)
		cout << *i;
}

int main()
{
	Directory eqDir(EQ_PATH);
	FileList raidDumps;
	raidDumps.setDirectory(&eqDir);
	raidDumps.buildFileList();
	vector<string> filenames = raidDumps.getFilenames();
	RaidDumpParser parser(&filenames);
	parser.parse();
	parser.printOutput();
	// process each file and save in a local folder.

	
	system("pause");
	return 0;
}