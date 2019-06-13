// Specification file for the CollegeList class
// Written By:
// IDE: 

#ifndef List_H
#define List_H
#include "armor.h"
#include <fstream> 
#include <iomanip>

using namespace std;
using std::string;

class List
{
private:
	struct ListNode {
		armor *A;
		ListNode *next;
	};
	ListNode *head;
	int count;

public:
	//Constructor
	List();

	// Linked list operations
	bool insertNode(armor *);
	bool deleteNode(string);
	bool searchListP(string, armor *);
	bool searchListS(string, armor *);
	void displayList() const;
	int getCount() { return count; }

	//Destructor
	~List();
};





//**************************************************
// Constructor
// This function allocates and initializes a sentinel node
//      A sentinel (or dummy) node is an extra node added before the first data record.
//      This convention simplifies and accelerates some list-manipulation algorithms,
//      by making sure that all links can be safely dereferenced and that every list
//      (even one that contains no data elements) always has a "first" node.
//**************************************************
List::List()
{
	head = new ListNode; // head points to the sentinel node
	head->next = NULL;
	count = 0;
}

//**************************************************
// The insertNode function inserts a node with
// stu copied to its value member.
//**************************************************
bool List::insertNode(armor * dataIn)
{
	ListNode *newNode;  // A new node
	ListNode *pCur;     // To traverse the list
	ListNode *pPre;     // The previous node
	bool inserted = false;

	// Allocate a new node and store num there.
	newNode = new ListNode;
	newNode->A = dataIn;
	// Initialize pointers
	pPre = head;
	pCur = head->next;
	// Find location: skip all nodes whose name is less than dataIn's name.
	while (pCur != NULL )
	{
		pPre = pCur;
		pCur = pCur->next;
	}

	// Insert the new node between pPre and pCur
	pPre->next = newNode;
	newNode->next = pCur;
	inserted = true;
	//Update the counter
	count++;
	return inserted;
}

//**************************************************
// The deleteNode function searches for a node
// with num as its value. The node, if found, is
// deleted from the list and from memory.
//**************************************************
bool List::deleteNode(string target)
{
	ListNode *pCur;       // To traverse the list
	ListNode *pPre;        // To point to the previous node
	bool deleted = false;

	// Initialize pointers
	pPre = head;
	pCur = head->next;

	// Find node containing the target: Skip all nodes whose name is less than the target
	while (pCur != NULL &&pCur->A->getUnikey()!=target)
	{
		pPre = pCur;
		pCur = pCur->next;
	}

	// If found, delete the node
	if (pCur != NULL && pCur->A->getUnikey() == target)
	{
		cout << "deleting " << pCur->A->getUnikey() << endl;
		pPre->next = pCur->next;
		delete pCur;
		deleted = true;
		//Update counter
		count--;
	}
	else
		cout << "I can't find it\n";
	return deleted;

}

//******************************************************************************
// Search function shows if the college name is match with what the user enters
//******************************************************************************
bool List::searchListP(string target, armor *dataOut)
{
	ListNode *pCur;
	pCur = head->next;
	bool found = false;

	while (pCur != NULL && pCur->A->getUnikey() < target)
		pCur = pCur->next;

	if (pCur != NULL && pCur->A->getUnikey() == target) {
		found = true;
		dataOut = pCur->A;
	}
	return found;

}

//**************************************************
// Display function shows every college name with their rank and cost.
//**************************************************

//void List::displayList() const
//{
//	ListNode *pCur;  // To move through the list
//
//					 // print header
//	cout << endl
//		<< "==== ============================= ========= ==========" << endl
//		<< "Rank          Name                    Cost      NoStu  " << endl
//		<< "==== ============================= ========= ==========" << endl;
//
//	pCur = head->next;          // Position pCur: skip the head of the list.
//	while (pCur != NULL)
//	{
//		pCur->col.display();  //Display the value in the node.
//		pCur = pCur->next;    //Move to the next node.
//
//	}
//	cout
//		<< "==== ============================= ========= ==========" << endl;
//}

//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
//**************************************************
List::~List()
{
	ListNode *pCur;   // To traverse the list
	ListNode *pNext;  // To point to the next node

					  // Position nodePtr at the head of the list.
	pCur = head->next;

	// While pCur is not at the end of the list...
	while (pCur != NULL)
	{
		// Save a pointer to the next node.
		pNext = pCur->next;

		// Delete the current node.
		cout << "DEBUG - Destructor: Now deleting " << pCur->A->getName() << endl;
		delete pCur;

		// Position pCur at the next node.
		pCur = pNext;
	}
	//cout << "DEBUG - Destructor: Now deleting the sentinel node rank " << head->A->getRank() << endl;
	delete head; // delete the sentinel node
}

#endif 
