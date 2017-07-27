#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <vector>
#include <unordered_map>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio>

using namespace std;

#define EQ_PATH "C:\\Users\\Public\\Daybreak Game Company\\Installed Games\\EverQuest"
#define MAX_GROUPS 12

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
	string delimiter;
public:
	FileList();
	vector<string> filenames;
	vector<string> shortnames;
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
				shortnames.push_back(directory->ent->d_name);
			}
	}

	for (auto i = shortnames.begin(); i != shortnames.end(); ++i)
	{
		cout << *i << endl;
	}
}

bool FileList::isRaidDump(string filename)
{
	regex pattern("RaidRoster-\\d{8}-\\d{6}\.txt");
	return regex_search(filename.begin(), filename.end(), pattern);
}

class OutputData
{
public:
	int grp;
	string name;
	int level;
	int weightedGrp;
	string playerclass;
	string pcformatted;
	friend bool operator<(const OutputData &data1, const OutputData &data2);
	friend bool operator>(const OutputData &data1, const OutputData &data2);
	friend bool operator==(const OutputData &data1, const OutputData &data2);
	friend ostream &operator<<(ostream &os, const OutputData &output);
};

bool operator<(const OutputData &data1, const OutputData &data2)
{
	if (data1.weightedGrp == data2.weightedGrp) // if they're in the same group
	{
		if (data1.playerclass == data2.playerclass) // and they're the same class
		{
			if (data1.name < data2.name) // sort alpha by name
				return true;
			else
				return false;
		}			
		else
		{
			if (data1.playerclass < data2.playerclass) // if they're in the same group, sort alpha by class
				return true;
			else
				return false;
		}			
	}
	else if (data1.weightedGrp < data2.weightedGrp) // if different groups, sort by group
		return true;
	else
		return false;
}

bool operator>(const OutputData &data1, const OutputData &data2)
{
	if (data1.weightedGrp == data2.weightedGrp) // if they're in the same group
	{
		if (data1.playerclass == data2.playerclass) // and they're the same class
		{
			if (data1.name > data2.name) // sort alpha by name
				return true;
			else
				return false;
		}
		else
		{
			if (data1.playerclass > data2.playerclass) // if they're in the same group, sort alpha by class
				return true;
			else
				return false;
		}
	}
	else if (data1.weightedGrp > data2.weightedGrp) // if different groups, sort by group
		return true;
	else
		return false;
}

bool operator==(const OutputData &data1, const OutputData &data2)
{
	if (data1.grp == data2.grp && data1.name == data2.name &&
		data1.level == data2.level && data1.playerclass == data2.playerclass)
		return true;
	else
		return false;
}

ostream &operator<<(ostream &os, const OutputData &output)
{
	os << output.grp << " " << output.pcformatted << " " << output.name;
	return os;
}

class RaidDumpParser
{
private:
	FileList *fileList;
	string filename;
	string line;
	stringstream ss;
	ifstream inFile;
	//vector<string> *fileList;
	unordered_map<string, string> classFormat;
	OutputData lineData;
	vector<OutputData> output;
	int nBenched;
public:
	RaidDumpParser(FileList *fList);
	void buildClassFormatMap();
	void parse();
	vector<OutputData> *getData();
	void printOutput();
	void writeOutputFile();
};

RaidDumpParser::RaidDumpParser(FileList *fList)
{
	nBenched = 0;
	fileList = fList;
	buildClassFormatMap();
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
	filename = fileList->filenames[0];
	inFile.open(filename);
	cout << "Opening " << fileList->filenames[0] << endl;
	while (getline(inFile, line))
	{
		ss << line;

		ss >> lineData.grp;
		ss >> lineData.name;
		ss >> lineData.level;
		ss >> lineData.playerclass;

		lineData.pcformatted = classFormat[lineData.playerclass];
		if (lineData.grp == 0)
		{
			lineData.weightedGrp = MAX_GROUPS + 1;
			nBenched++;
		}			
		else
			lineData.weightedGrp = lineData.grp;

		output.push_back(lineData);
		ss.str("");
		ss.clear();
	}
	inFile.close();
	sort(output.begin(), output.end());
}

void RaidDumpParser::printOutput()
{
	for (auto i = output.begin(); i != output.end(); ++i)
		cout << *i << endl;
}

void RaidDumpParser::writeOutputFile()
{
	cout << "Writing to output file...\n";
	ofstream outFile;
	string fpath;
	fpath = "Raid Dumps\\Processed\\Processed";
	int currGrp = output[0].grp;
	outFile.open((fpath + fileList->shortnames[0]).c_str());
	outFile << "[b][u]Event[/b][/u] (" << output.size() - nBenched << ") + " << nBenched << "\n";
	for (int i = 0; i < output.size(); i++)
	{
		if (output[i].grp != currGrp)
		{
			outFile << "\n";
			currGrp = output[i].grp;
		}
		outFile << output[i] << "\n";
	}
	outFile.close();
}

vector<OutputData> *RaidDumpParser::getData()
{
	return &output;
}

class FileHandler
{
private:
	vector<OutputData> *output;
public:
	FileHandler(vector<OutputData> *data);
	void buildDir();
	void printData();
	void copyFile(string f1, string f2);
	string getPrePath();
};

FileHandler::FileHandler(vector<OutputData> *data)
{
	output = data;
}

void FileHandler::printData()
{
	for (auto i = output->begin(); i != output->end(); ++i)
		cout << *i << endl;
}

void FileHandler::buildDir()
{
	system("mkdir \"Raid Dumps\"");
	system("mkdir \"Raid Dumps\"\\Processed");
	system("mkdir \"Raid Dumps\"\\Pre-Processed");
}

void FileHandler::copyFile(string f1, string f2)
{
	const static int BUF_SIZE = 4096;
	ifstream sourceFile(f1, ios_base::in | ios_base::binary);
	ofstream destinationFile(f2, ios_base::out | ios_base::binary);
	char buf[BUF_SIZE];

	do
	{
		sourceFile.read(&buf[0], BUF_SIZE);
		destinationFile.write(&buf[0], sourceFile.gcount()); // gcount = char count in the stream
	} while (sourceFile.gcount() > 0);

	sourceFile.close();
	destinationFile.close();
}

string FileHandler::getPrePath()
{
	// temp just do 1st file...
	string outpath = "";
//	outpath = "Raid Dumps\\Pre-Processed\\" + fileList->shortnames[0]).c_str();
	return outpath;
}

int main()
{
	Directory eqDir(EQ_PATH);
	FileList raidDumps;
	raidDumps.setDirectory(&eqDir);
	raidDumps.buildFileList();
	RaidDumpParser parser(&raidDumps);
	parser.parse();
	FileHandler filehandler(parser.getData());
	filehandler.buildDir();
	filehandler.printData();
	parser.writeOutputFile();
	// process each file and save in a local folder.
	// next; move old file to /Raid Dumps/Pre-Processed
	// finally: loop for all existing raid dump files.
	filehandler.copyFile(raidDumps.filenames[0], "Raid Dumps\\Pre-Processed");
	
	system("pause");
	return 0;
}