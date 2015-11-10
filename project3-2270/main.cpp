#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>

using namespace std;

struct node
{
	string key;
	node* leftChild;
	node* rightChild;
};

class SplayTree
{
	public:
		SplayTree()
		{
			
		}
		
		//rotate to right.
		node* RR_Rotation(node* tempNode2)
		{
			node* tempNode1 = tempNode2->leftChild;
			tempNode2->leftChild = tempNode1->rightChild;
			tempNode1->rightChild = tempNode2;
			
			return tempNode1;
		}
		
		//rotate to left.
		node* LL_Rotation(node* tempNode2)
		{
			node* tempNode1 = tempNode2->rightChild;
			tempNode2->rightChild = tempNode1->leftChild;
			tempNode1->leftChild = tempNode2;
			
			return tempNode1;
		}
		
		node* Splay(string key, node* root)
		{
			if(!root)
			{
				return NULL;
			}
			
			node headNode;
			
			headNode.leftChild = NULL;
			headNode.rightChild = NULL;
			
			node* LeftSubtreeMax = &headNode;
			node* RightSubtreeMin = &headNode;
			
			while(1)
			{
				if(key < root->key)
				{
					if(!root->leftChild)
					{
						break;
					}
					
					if(key < root->leftChild->key)
					{
						root = RR_Rotation(root);
						
						if(!root->leftChild)
						{
							break;
						}
					}
					
					RightSubtreeMin->leftChild = root;
					RightSubtreeMin = RightSubtreeMin->leftChild;
					root = root->leftChild;
					RightSubtreeMin->leftChild = NULL;
				}
				else if(key > root->key)
				{
					if(!root->rightChild)
					{
						break;
					}
					
					if(key > root->rightChild->key)
					{
						root = LL_Rotation(root);
						
						if(!root->rightChild)
						{
							break;
						}
					}
					
					LeftSubtreeMax->rightChild = root;
					LeftSubtreeMax = LeftSubtreeMax->rightChild;
					root = root->rightChild;
					LeftSubtreeMax->rightChild = NULL;
				}
				else
				{
					break;
				}
			}
			
			LeftSubtreeMax->rightChild = root->leftChild;
			RightSubtreeMin->leftChild = root->rightChild;
			
			root->leftChild = headNode.rightChild;
			root->rightChild = headNode.leftChild;
			
			return root;
		}
		
		node* New_Node(string key)
		{
			node* tmp_node = new node;
			
			if(!tmp_node)
			{
				cout<<"Error allocating node."<<endl;
				exit(1);
			}
			
			tmp_node->key = key;
			tmp_node->leftChild = NULL;
			tmp_node->rightChild = NULL;
			
			return tmp_node;
		}
		
		node* InsertKey(string key, node* root)
		{
			node* tmp_node = NULL;
			
			if(!tmp_node)
			{
				tmp_node = New_Node(key);
			}
			else
			{
				tmp_node->key = key;
			}
			
			if(!root)
			{
				root = tmp_node;
				tmp_node = NULL;
				
				return root;
			}
			
			root = Splay(key, root);
			
			if(key < root->key)
			{
				tmp_node->leftChild = root->leftChild;
				tmp_node->rightChild = root;
				root->leftChild = NULL;
				root = tmp_node;
			}
			else if(key > root->key)
			{
				tmp_node->rightChild = root->rightChild;
				tmp_node->leftChild = root;
				root->leftChild = NULL;
				root = tmp_node;
			}
			else
			{
				return root;
			}
			
			tmp_node = NULL;
			return root;
		}
		
		node* DeleteKey(string key, node* root)
		{
			node* tmp_node;
			
			if(!root)
			{
				return NULL;
			}
			
			root = Splay(key, root);
			
			if(key != root->key)
			{
				return root;
			}
			else
			{
				if(!root->leftChild)
				{
					tmp_node = root;
					root = root->rightChild;
				}
				else
				{
					tmp_node = root;
					root = Splay(key, root->leftChild);
					root->rightChild = tmp_node->rightChild;
				}
				
				free(tmp_node);
				
				return root;
			}
		}
		
		node* SearchKey(string key, node* root)
		{
			return Splay(key, root);
		}
		
		node* Clear(node* root)
		{
			if(!root)
			{
				return NULL;
			}
			
			if(!root->leftChild && !root->rightChild)
			{
				free(root);
				return NULL;
			}
			
			Clear(root->leftChild);
			Clear(root->rightChild);
			
			free(root);
			return NULL;
			
			cout<<"Tree cleared."<<endl;
		}
		
		int getHeight(node* root)
		{
			if(!root)
				return -1;
				
			return 1 + max(getHeight(root->leftChild), getHeight(root->rightChild));
		}
		
		//TODO: display function here.
		void InOrder(node* root, int height)
//		{
//			if(root)
//			{
//			InOrder(root->leftChild);
//			std::cout<< "key: " <<root->key;
//			if(root->leftChild)
//				std::cout<< " | left child: "<< root->leftChild->key;
//			if(root->rightChild)
//				std::cout << " | right child: " << root->rightChild->key;
//			std::cout<< "\n------------------------------------------------\n";
//			InOrder(root->rightChild);
//			}
//		}

		{
			if(root != NULL)
			{
				string left;
				string right;
				
				if(getHeight(root) >= 0)
				{
					cout<<"                               "<<root->key<<endl;
				}
				
				if(getHeight(root) >= 1)
				{
					if(root->leftChild == NULL )
						left = "***";
					else
						left = root->leftChild->key;
					
					if(root->rightChild == NULL)
						right = "***";
					else
						right = root->rightChild->key;
						
					cout<<"               "<<left<<"                             "<<right<<endl;
				}
				
				if(getHeight(root) >= 2)
				{
					if(root->leftChild == NULL || root->leftChild->leftChild == NULL )
						left = "***";
					else
						left = root->leftChild->leftChild->key;
					
					if(root->leftChild == NULL || root->leftChild->rightChild == NULL)
						right = "***";
					else
						right = root->leftChild->rightChild->key;
					
					cout << "       "<<left << "             " << right;

					if(root->rightChild == NULL || root->rightChild->leftChild == NULL )
						left = "***";
					else
						left = root->rightChild->leftChild->key;
					
					if(root->rightChild == NULL || root->rightChild->rightChild == NULL)
						right = "***";
					else
						right = root->rightChild->rightChild->key;

					cout << "             "<<left <<"             " << right << endl;
				}
				
				if(getHeight(root) >= 3)
				{
					if(root->leftChild == NULL || root->leftChild->leftChild == NULL || root->leftChild->leftChild->leftChild == NULL)
						left = "***";
					else
						left = root->leftChild->leftChild->leftChild->key;
					
					if(root->leftChild == NULL || root->leftChild->leftChild == NULL || root->leftChild->leftChild->rightChild == NULL)
						right = "***";
					else
						right = root->leftChild->leftChild->rightChild->key;
					
					cout << "   "<<left << "     " << right;
					
					
					
					if(root->leftChild == NULL || root->leftChild->rightChild == NULL || root->leftChild->rightChild->leftChild == NULL)
						left = "***";
					else
						left = root->leftChild->rightChild->leftChild->key;
					
					if(root->leftChild == NULL || root->leftChild->rightChild == NULL || root->leftChild->rightChild->rightChild == NULL)
						right = "***";
					else
						right = root->leftChild->rightChild->rightChild->key;
					
					cout << "     "<<left << "     " << right;
					

					if(root->rightChild == NULL || root->rightChild->leftChild == NULL || root->rightChild->leftChild->leftChild == NULL)
						left = "***";
					else
						left = root->rightChild->leftChild->leftChild->key;
					
					if(root->rightChild == NULL || root->rightChild->leftChild == NULL || root->rightChild->leftChild->rightChild == NULL)
						right = "***";
					else
						right = root->rightChild->leftChild->rightChild->key;

					cout << "     "<<left <<"     " << right;
					
					
					if(root->rightChild == NULL || root->rightChild->rightChild == NULL || root->rightChild->rightChild->leftChild == NULL)
						left = "***";
					else
						left = root->rightChild->rightChild->leftChild->key;
					
					if(root->rightChild == NULL || root->rightChild->rightChild == NULL || root->rightChild->rightChild->rightChild == NULL)
						right = "***";
					else
						right = root->rightChild->rightChild->rightChild->key;
					
					cout << "     "<<left << "     " << right<<endl;
				}

				if(getHeight(root) >= 4)
				{
					if(root->leftChild == NULL || root->leftChild->leftChild == NULL || root->leftChild->leftChild->leftChild == NULL || root->leftChild->leftChild->leftChild->leftChild == NULL)
						left = "***";
					else
						left = root->leftChild->leftChild->leftChild->leftChild->key;
					
					if(root->leftChild == NULL || root->leftChild->leftChild == NULL || root->leftChild->leftChild->leftChild == NULL || root->leftChild->leftChild->leftChild->rightChild == NULL)
						right = "***";
					else
						right = root->leftChild->leftChild->leftChild->rightChild->key;
					
					cout << " "<<left << " " << right;
					
////				cout<<"                               ---                               "<<endl;
////				cout<<"               ---                             ---               "<<endl;
////				cout<<"       ---             ---             ---             ---       "<<endl;
////				cout<<"   ---     ---     ---     ---     ---     ---     ---     ---   "<<endl;
////        		cout<<" --- --- *** *** *** *** *** *** *** *** *** *** *** *** *** *** "<<endl;
//					
//					if(root->leftChild == NULL || root->leftChild->rightChild == NULL || root->leftChild->rightChild->leftChild == NULL)
//						left = "***";
//					else
//						left = root->leftChild->rightChild->leftChild->key;
//					
//					if(root->leftChild == NULL || root->leftChild->rightChild == NULL || root->leftChild->rightChild->rightChild == NULL)
//						right = "***";
//					else
//						right = root->leftChild->rightChild->rightChild->key;
//					
//					cout << "     "<<left << "     " << right;
//
////				cout<<"                               ---                               "<<endl;
////				cout<<"               ---                             ---               "<<endl;
////				cout<<"       ---             ---             ---             ---       "<<endl;
////				cout<<"   ---     ---     ---     ---     ---     ---     ---     ---   "<<endl;
////        		cout<<" *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** "<<endl;
//
//					if(root->rightChild == NULL || root->rightChild->leftChild == NULL || root->rightChild->leftChild->leftChild == NULL)
//						left = "***";
//					else
//						left = root->rightChild->leftChild->leftChild->key;
//					
//					if(root->rightChild == NULL || root->rightChild->leftChild == NULL || root->rightChild->leftChild->rightChild == NULL)
//						right = "***";
//					else
//						right = root->rightChild->leftChild->rightChild->key;
//
//					cout << "     "<<left <<"     " << right;
//					
////				cout<<"                               ---                               "<<endl;
////				cout<<"               ---                             ---               "<<endl;
////				cout<<"       ---             ---             ---             ---       "<<endl;
////				cout<<"   ---     ---     ---     ---     ---     ---     ---     ---   "<<endl;
////        		cout<<" *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** "<<endl;
//					
//					if(root->rightChild == NULL || root->rightChild->rightChild == NULL || root->rightChild->rightChild->leftChild == NULL)
//						left = "***";
//					else
//						left = root->rightChild->rightChild->leftChild->key;
//					
//					if(root->rightChild == NULL || root->rightChild->rightChild == NULL || root->rightChild->rightChild->rightChild == NULL)
//						right = "***";
//					else
//						right = root->rightChild->rightChild->rightChild->key;
//					
//					cout << "     "<<left << "     " << right<<endl;
				}
//
////				cout<<"                               ---                               "<<endl;
////				cout<<"               ---                             ---               "<<endl;
////				cout<<"       ---             ---             ---             ---       "<<endl;
////				cout<<"   ---     ---     ---     ---     ---     ---     ---     ---   "<<endl;
////        		cout<<" *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** "<<endl;
    		}
    		
    		system("pause");
			
		}
		
		
		
		
};

int main()
{
	SplayTree splayTree;
	
	ifstream inDataFile;
	string filename;
	
	node* root;
	
	root = NULL;
	
	string key;
	int choice;
	
	while(1)
	{
		//system("cls");
		cout << "\n ----------------------\n" << endl;
		cout << " 1. Build tree from file." << endl;
		cout << " 2. Insert a key." << endl;
		cout << " 3. Delete a key." << endl;
		cout << " 4. Search for key." << endl;
		cout << " 5. Clear the tree." << endl;
		cout << " 6. Exit." << endl;
		cout << "\n ----------------------\n" << endl;
		cout << " Enter a selection: ";
		
		cin>>choice;
		
		switch(choice)
		{
			case 1:
				cin.clear();
				cin.sync();
				cout << endl;
				
				cout << "Enter a filename to process: ";
				getline(cin, filename);
				
				inDataFile.open(filename.c_str());
				
				if(inDataFile.fail())
				{
					cout << "Error opening data file." << endl;
					system("pause");
					exit(1);
				}
	
				cin.clear();
				cin.sync();
				cout << endl;
				
				while( inDataFile>>key )
				{
					root = splayTree.InsertKey(key, root);
					
					//call display function here to show after every insert.
					splayTree.InOrder(root, splayTree.getHeight(root));
				}

				break;
				
			case 2:
				cin.clear();
				cin.sync();
				cout << endl;
				
				cout << " Enter key to add: ";
				cin>>key;
				
				root = splayTree.InsertKey(key, root);
				
				//call display function here to show after every insert.
				splayTree.InOrder(root, splayTree.getHeight(root));
				
				break;
				
			case 3:
				cin.clear();
				cin.sync();
				cout << endl;
				
				cout << " Enter key to delete: ";
				cin>>key;
				
				root = splayTree.DeleteKey(key, root);
				
				//call display function here to show after every insert.
				splayTree.InOrder(root, splayTree.getHeight(root));
				
				break;
				
			case 4:
				cin.clear();
				cin.sync();
				cout << endl;
				
				cout << " Enter key to search for: ";
				cin>>key;
				
				root = splayTree.SearchKey(key, root);
				
				//call display function here to show after every insert.
				splayTree.InOrder(root, splayTree.getHeight(root));
				
				break;
				
			case 5:
				cin.clear();
				cin.sync();
				cout << endl;
							
				root = splayTree.Clear(root);
				
				//call display function here to show after every insert.
				//InOrder(root);
				
				break;
				
			case 6:
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
























