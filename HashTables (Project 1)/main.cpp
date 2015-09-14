/*
COMP-2270-01 Fall 2015
Title: Project 1 (Hash Table using Double Hashing)
Student: David Walker
Instructor: Randy Baker
Assigned: August 27, 2015
Due Date: September 15, 2015
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int TABLE_SIZE = 19;

//Hash Item Class
class HashItem
{
	public:
		string key;
		int value;

		HashItem(string key, int value)
		{
			this->key = key;
			this->value = value;
		}
};

//Hash Table Class
class HashTable
{
	private:

		HashItem **htable;
		int openSlots;

	public:

		//Hash Table constructor.
		HashTable()
		{
			htable = new HashItem* [TABLE_SIZE];

			for( int i = 0; i < TABLE_SIZE; i++ )
			{
				htable[i] = NULL;
			}

			this->openSlots = TABLE_SIZE;
		}

		//Hash Table deconstructor.
		~HashTable()
		{
			for( int i = 0; i < TABLE_SIZE; i++ )
			{
				if (htable[i] != NULL )
					delete htable[i];
			}

			delete[] htable;
		}

		//Helper function to check if table is empty.
		bool IsEmpty()
		{
			if(this->openSlots == TABLE_SIZE)
				return true;
			else
				return false;
		}

		//Helper function to check if table is full.
		bool IsFull()
		{
			if(this->openSlots == 0)
				return true;
			else
				return false;
		}

		//Helper function to get sum of string
		int KeySum(string key)
		{
			int sum = 0;

			for( int i = 0; i < key.length(); i++ )
			{
				sum = sum + (int)key[i];
			}

			return sum;
		}

		//Hash function.
		int HashFunction(string key)
		{
			int sum = KeySum(key);

			return 11 * sum % TABLE_SIZE;
		}

		//Insert function using double hashing.
		void InsertItem(string key)
		{

			int sum = KeySum(key);
			int increment = 11 * sum / TABLE_SIZE;
			int hash_value = HashFunction(key);
			bool isInsertable = true;

			if(!IsFull())
			{
				while(htable[hash_value] != NULL && isInsertable)
				{
					if( htable[hash_value]->key.compare(key) != 0)
					{
						hash_value = (hash_value + increment) % TABLE_SIZE;
					}
					else
					{
						cout << "\n ERROR: This table entry already exists.\n" << endl;
						system("pause");
						isInsertable = false;
					}
				}
				if(isInsertable)
				{
					htable[hash_value] = new HashItem(key, hash_value);
					this->openSlots--;
				}
			}
			else
			{

			}
		}

		void SearchItem(string key)
		{
			int sum = KeySum(key);
			int increment = 11 * sum / TABLE_SIZE;
			int hash_value = HashFunction(key);
			bool isFound = false;
			int counter = 0;

			if(!IsEmpty())
			{
				while(htable[hash_value] != NULL && !isFound && counter<TABLE_SIZE )
				{
					if( htable[hash_value]->key.compare(key) != 0)
					{
						hash_value = (hash_value + increment) % TABLE_SIZE;
						counter++;
					}
					else
					{
						isFound = true;
					}
				}

				if(isFound)
				{
					cout << "\n SUCCESS: Match found at index: " << htable[hash_value]->value << " with key: " << htable[hash_value]->key << ".\n" << endl;
					system("pause");
				}
				else
				{
					cout << "\n FAILED: No match found.\n" << endl;
					system("pause");
				}
			}
			else
			{

			}
		}

		void DeleteItem(string key)
		{
			int sum = KeySum(key);
			int increment = 11 * sum / TABLE_SIZE;
			int hash_value = HashFunction(key);
			bool isFound = false;
			int counter = 0;

			if(!IsEmpty())
			{
				while(htable[hash_value] != NULL && !isFound && counter<TABLE_SIZE )
				{
					if( htable[hash_value]->key.compare(key) != 0)
					{
						hash_value = (hash_value + increment) % TABLE_SIZE;
						counter++;
					}
					else
					{
						isFound = true;
					}
				}

				if(isFound)
				{
					cout << "\n SUCCESS: Deleting key at index: " << htable[hash_value]->value << ".\n" << endl;
					htable[hash_value] = NULL;
					this->openSlots++;
					system("pause");
				}
				else
				{
					cout << "\n FAILED: Unable to delete. No matching word found.\n" << endl;
					system("pause");
				}
			}
			else
			{

			}
		}

		void displayTable()
		{
			for( int i = 0; i < TABLE_SIZE; i++)
			{
				if(htable[i] != NULL)
				{
					cout << i+1 << ".  " << htable[i]->key << endl;
				}
				else
					cout << i+1 << ".  " << "" << endl;
			}

		}
};

int main(void)
{
	HashTable hash;
	string key;

	ifstream inDataFile;
	string filename;
	int truncatedEntries = 0;

	int choice;

	cout << "Enter a filename to process: ";
	getline(cin, filename);

	//This bit here is annoying. Converting str to c_str.
	//I can't be sure if this will be compiled against C++11 which supports str in ifstream.open.
	//Planning for worst case.
	inDataFile.open(filename.c_str());
	//cout << "opened"<<endl;

	if(inDataFile.fail()){
		cout << "Error opening data file." << endl;
		system("pause");
		exit(1);
	}

	cin.clear();
	cin.sync();
	cout << endl;

	while( getline(inDataFile, key) )
	{
		if(hash.IsFull())
		{
			truncatedEntries++;
		}
		else
		{
			hash.InsertItem(key);
		}
	}

	if(truncatedEntries)
	{
		cout << "There were " << truncatedEntries << " entries not placed in the table.\n" << endl;
		system("pause");
	}

	while(1)
	{
		system("cls");
		cout << "\n ----------------------\n" << endl;
		cout << " 1. Add item." << endl;
		cout << " 2. Search for item." << endl;
		cout << " 3. Delete item." << endl;
		cout << " 4. Display table." << endl;
		cout << " 5. Exit." << endl;
		cout << "\n ----------------------\n" << endl;
		cout << " Enter a selection: ";

		cin>>choice;

		switch(choice)
		{
			case 1:
				cin.clear();
				cin.sync();
				cout << endl;

				if(hash.IsFull())
				{
					cout << " ERROR: The table is full.\n" << endl;
					system("pause");

				}
				else
				{
					cout << " Enter word(s) to add: ";
					getline(cin, key);
					hash.InsertItem(key);
				}

				break;

			case 2:
				cin.clear();
				cin.sync();
				cout << endl;

				if(hash.IsEmpty())
				{
					cout << " ERROR: There is nothing to search.\n" << endl;
					system("pause");
				}
				else
				{
					cout << " Enter word(s) to search for: ";
					getline(cin, key);
					hash.SearchItem(key);
				}

				break;

			case 3:
				cin.clear();
				cin.sync();
				cout << endl;

				if(hash.IsEmpty())
				{
					cout << " ERROR: There is nothing to delete.\n" << endl;
					system("pause");
				}
				else
				{
					cout << " Enter word(s) to delete: ";
					getline(cin, key);
					hash.DeleteItem(key);
				}

				break;

			case 4:
				cin.clear();
				cin.sync();
				system("cls");
				hash.displayTable();
				cout << endl;
				system("pause");

				break;

			case 5:
				exit(1);

			default:
				cin.clear();
				cin.sync();
				cout << endl;
				cout << " Enter a correct selection.\n\n";
				system("pause");
		}
	}
	return 0;
}
