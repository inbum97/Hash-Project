#ifndef Hash_H
#define Hash_H
#include <iostream>
#include "List.h"
//#include <list>
using namespace std;

class Hash {
private:
	//number of buckets
	int numBucket;
	List *table;
	int collision;
	double LF;
public:
	//constructor
	Hash();
	//overloaded constructor
	Hash(int);
	//basic hash functions
	bool insertItem(armor *A);
	bool deleteItem(string target);
	int hashFunction(string unikey);
	void displayHash();
	bool searchByP(string uniKey);
	void stat();
	//setter
	void setCol(int a) { collision = a; }
	void setLF(double a) { LF = a; }
	//getter
	int getCol() { return collision; }
	double getLF() { return LF; }
};

void Hash::stat() {
	int collision=0;
	double loadFactor = 0.0;
	for (int i = 0; i < numBucket; i++) {
		if (table[i].getCount() > 1) {
			collision += table[i].getCount()-1;
		}
	}
	setCol(collision);
	cout << "Collision: " << collision<<endl;
	loadFactor = ((numBucket - collision)/ numBucket)*100;
	setLF(loadFactor);
	cout <<"Load Facotr " << loadFactor;

}

bool Hash::searchByP(string uniKey) {
	bool found = false;
	int index = hashFunction(uniKey);
	armor *a= new armor;
	cout << "printing search result ";

	if (table[index].searchListP(uniKey, a)) {
		found = true;
		cout << a->getUnikey() << endl;

	}
	return found;
}
//void Hash::displayHash() {
//	for (int i = 0; i < numBucket; i++) {
//		cout << i;
//		for (auto x : table[i])
//			cout << "--> " << x;
//		cout << endl;
//	}
//}

/****************************************************
 hashFunction: This reads each characters from string
  and add up each of ascii value and modulo the size 
  of the hash and return that value
  **************************************************/
int Hash::hashFunction(string uniKey) {
	int sum = 0;
	int len = uniKey.size();
	for (int i = 0; i <len ; i++) {
		sum += uniKey[i];
	}
	int key = sum % numBucket;
	cout << "Key: " << sum<<endl;
	cout<<"Bucket number: " <<key<<endl;
	return key;
}

//Overloaded Constructor
Hash::Hash(int b) {
	this->numBucket = b;
	table = new List[numBucket];
	cout << "Hash array of " << b << " number of index created\n";
}

//Inserting an item into the hash table
bool Hash::insertItem(armor *A) {
	bool found = false;
	int index = hashFunction(A->getUnikey());
	if (table[index].insertNode(A)) {
		found = true;
		cout << A->getName() << " has been inserted\n";
	}
	return found;
}

//what should be the parameter
bool Hash::deleteItem(string target) {
	bool found = false;
	int index = hashFunction(target);
	if (table[index].deleteNode(target)) {
		found = true;
	}
	return found;
}





#endif Hash-H
