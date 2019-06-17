#include<iostream>
#include <string>
#include "armor.h"
#include "Hash.h"
#include "List.h"
#include <fstream>
using namespace std;

void insertHashManager(Hash &H);
void deleteHashManager(Hash &H);
void searchHashManager(Hash &H, void visit(Armors *));
void inputValid(string &returnItem);
void display(Armors *a);
void fileInput(string filename, Hash &H);

//
void display(Armors *a) {
	cout << "I am in display func\n";
	cout << a->getCodeName() << " " << a->getYear() << endl;
	cout << "--------------------------------------------------------------------------" << endl;
	cout << a->getCodeName() << ":" << a->getArmorType() << "\nMade by: " << a->getCreator() << " in " << a->getYear()
		<< "\nUsers: " << a->getUser() << ", appeared in: " << a->getMovie() << "\nCurrent Status: " << a->getStatus()
		<< "\nArmor Capabilities: " << a->getCap() << "\nWeapons: " << a->getWeapon()
		<< "\nPrecede: " << a->getPre() << "\tSucceed: " << a->getSuc();
	cout << "\n--------------------------------------------------------------------------" << endl;
}


int main() {
	/*armor *A= new armor;
	Hash H(1);
	H.insertItem(A);
	armor* A1 = new armor;
	H.searchByP("Sneaky", A1);
	string del = "Sneaky";
	H.deleteItem(del);
	H.stat();*/
	string fileName = "armors.txt";
	Hash H(20);
	fileInput(fileName, H);
	H.stat();
	insertHashManager(H);
	searchHashManager(H,display);
	deleteHashManager(H);
	return 0;
}

void insertHashManager(Hash &H) {
	string targetName = "";
	Armors *A = new Armors;
	Armors *A2 = new Armors;
	A2->setCodeName("");

	cout << "\n Insert\n";
	cout << "=======\n";

	while (A2->getCodeName() != "Q")
	{
		cout << endl << "Enter an armor name to insert (or Q for stop inserting):";
		getline(cin, targetName);
		A2->setCodeName(targetName);
		cout << endl;
		if (A2->getCodeName() != "Q")
		{
			if (H.searchHash(A2, A))
				cout << "Armor " << targetName << " is already in this Hash Table.";
			else {
				cout << "Enter the information of the Armor" << endl;
				getline(cin, A);
				if (H.insertItem(A))
					cout << "\nInserted" << endl;
			}
		}
	}
	cout << endl;
	cout << "___________________END INSERT SECTION _____\n";
}

void deleteHashManager(Hash &H) {
	string targetName = "";
	int n = 0;

	cout << "\n Delete\n";
	cout << "=======\n";

	while (targetName != "Q")
	{
		cout << endl << "Enter an armor name for delete (or Q for stop searching): ";
		getline(cin, targetName);

		if (targetName != "Q")
		{
			if (H.deleteItem(targetName))
				cout << "Deleted\n";
			else
				cout << "Armor " << targetName << " was not found in this Hash Table." << endl;
		}
	}
	cout << "___________________END DELETE SECTION_____\n";
}

void searchHashManager(Hash &H, void visit(Armors *) ){
	string key = "";
	string sKey = "";
	Armors *A;
	Armors *A2;
	A = new Armors;
	A2 = new Armors;
	cout << "\n Search\n";
	cout << "=======\n";
		do
		{
			cout << "\nEnter a primary key for search (or Q for stop searching): ";
			getline(cin, key);
			if (!cin.good())
				inputValid(key);
			A2->setCodeName(key);
			cout << endl;
			if (A2->getCodeName() != "Q") {
				if (!H.searchHash(A2, A))
					cout << "Armor " << key << " was not found in this Hash Table.\n";
				else
					visit(A);
			}
		} while (key != "Q");
	
	cout << endl;
	cout << "___________________END SEARCH SECTION _____\n";

}

void inputValid(string &returnItem) {
	string val;
	do {
		cout << "Your input is invalid\n" << "Please input integer to search\n";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		getline(cin, val);
	} while (!cin.good());
	returnItem = val;
}


void fileInput(string filename, Hash &H)
{
	ifstream infile(filename);

	string codename, type, creator, movie, curstat, precede, succeed, users, capbl, weap,space;
	int year = 0;

	if (!infile) {
		cout << "Error happened to open the input file!" << endl;
		exit(EXIT_FAILURE);
	}

	// READING THE FILE AND DECLARE TO RESPECTICE VARIABLE 
	//======================================================

	while (getline(infile, codename, ';'))
	{
		getline(infile, type, ';');
		getline(infile, creator, ';');
		infile >> year;
		infile.ignore();
		getline(infile, users, ';');
		getline(infile, movie, ';');
		getline(infile, curstat, ';');
		getline(infile, capbl, ';');
		getline(infile, weap, ';');
		getline(infile, precede, ';');
		getline(infile, succeed, ';');


		Armors *armors;
		armors = new Armors(codename, type, creator, year, users, movie, curstat, capbl, weap, precede, succeed);
		H.insertItem(armors);
		cout << "Inserted\n";
		getline(infile, space);



		
	}
	infile.close();

}