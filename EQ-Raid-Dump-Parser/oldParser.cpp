#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void cleanFile(string infilename);

int main()
{
	string infilename, outfilename, group, name, eqclass;
	ifstream inFile2;
	ofstream outFile2;
	infilename = "RaidRoster-20170604-165648";
	cleanFile(infilename);
	inFile2.open((infilename + "cleaned1.txt").c_str());
	outFile2.open((infilename + "cleaned2.txt").c_str());
	string text;
	int i = 0;
	while (inFile2)
	{
		getline(inFile2, text);
		inFile2 >> group >> name >> eqclass;
		//cout << text << endl;
		//inFile >> group >> name >> eqclass;
		//
		outFile2 << group << " " << eqclass << " " << name << endl;
		if (group != "0")
			i++;
	}
	cout << " " << i << endl;
	outFile2 << "(" << i << ")" << endl;
	inFile2.close();
	outFile2.close();

	return 0;
}

void cleanFile(string infilename)
{
	ifstream inFile;
	ofstream outFile;
	string text;
	inFile.open((infilename + ".txt").c_str());
	//"RaidRoster-20160821-160829.txt"
	if (!inFile)
	{
		cout << "ERROR opening the input file!\n";
	}

	outFile.open((infilename + "cleaned1.txt").c_str());

	while (inFile >> text)
	{
		//getline (inFile, text);
		//cout << text << endl;
		//inFile >> group >> name >> level >> eqclass >> grplead >> grplead2 >> flag;
		//cout << group << " " << name << " " << level << " " << eqclass << " " << flag << " ";
		if (text == "1" || text == "2" || text == "3" || text == "4"
			|| text == "5" || text == "6" || text == "7" || text == "8"
			|| text == "9" || text == "11" || text == "12")
			outFile << text << " ";
		else if (text == "0")
			outFile << "0" << " ";
		else if (text != "Group" && text != "Leader" && text != "Raid" &&
			text != "Yes" && text != "No" && text != "Knight" && text != "105")
		{
			if (text == "Bard")
				outFile << "[COLOR=\"White\"]" << "BRD" << "[/COLOR]";
			else if (text == "Beastlord")
				outFile << "[COLOR=\"Green\"]" << "BST" << "[/COLOR]";
			else if (text == "Berserker")
				outFile << "[COLOR=\"Lime\"]" << "BER" << "[/COLOR]";
			else if (text == "Cleric")
				outFile << "[COLOR=\"Cyan\"]" << "CLR" << "[/COLOR]";
			else if (text == "Druid")
				outFile << "[COLOR=\"Teal\"]" << "DRU" << "[/COLOR]";
			else if (text == "Enchanter")
				outFile << "[COLOR=\"DarkRed\"]" << "ENC" << "[/COLOR]";
			else if (text == "Magician")
				outFile << "[COLOR=\"Red\"]" << "MAG" << "[/COLOR]";
			else if (text == "Monk")
				outFile << "[COLOR=\"Lime\"]" << "MNK" << "[/COLOR]";
			else if (text == "Necromancer")
				outFile << "[COLOR=\"Purple\"]" << "NEC" << "[/COLOR]";
			else if (text == "Paladin")
				outFile << "[COLOR=\"Orange\"]" << "PAL" << "[/COLOR]";
			else if (text == "Ranger")
				outFile << "[COLOR=\"Green\"]" << "RNG" << "[/COLOR]";
			else if (text == "Rogue")
				outFile << "[COLOR=\"Lime\"]" << "ROG" << "[/COLOR]";
			else if (text == "Shadow")
				outFile << "[COLOR=\"Orange\"]" << "SHD" << "[/COLOR]";
			else if (text == "Shaman")
				outFile << "[COLOR=\"Teal\"]" << "SHM" << "[/COLOR]";
			else if (text == "Warrior")
				outFile << "[COLOR=\"Yellow\"]" << "WAR" << "[/COLOR]";
			else if (text == "Wizard")
				outFile << "[COLOR=\"Red\"]" << "WIZ" << "[/COLOR]";
			else
				outFile << text << " ";
		}
		if (text == "Yes" || text == "No")
		{
			outFile << "\n";
		}
	}
	inFile.close();
	outFile.close();
}
