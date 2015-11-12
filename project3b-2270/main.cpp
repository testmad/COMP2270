#include <iostream>
#include <fstream>
//#include <stdlib.h>

using namespace std;

struct node
{
	string key;
	node* leftChild;
	node* rightChild;
	node* parent;
};

class SplayTree
{
	public:
		SplayTree()
		{
			
		}
		
		//ZIG
		node* L_Rotation(node* tmp_node)
		{
			cout<<"L_Rotation"<<endl;
			
			node* p = tmp_node->parent;
			
			p->leftChild = tmp_node->rightChild;
			
			if(p->leftChild)
				p->leftChild->parent = p;
				
			tmp_node->rightChild = p;
			tmp_node->parent = p->parent;
			p->parent = tmp_node;
			
			display(tmp_node);
			
			return tmp_node;
		}
		
		//ZAG
		node* R_Rotation(node* tmp_node)
		{
			cout<<"R_Rotation"<<endl;
			
			node* p = tmp_node->parent;
			
			p->rightChild = tmp_node->leftChild;

			if(p->rightChild)
				p->rightChild->parent = p;
				
			tmp_node->leftChild = p;
			tmp_node->parent = p->parent;
			p->parent = tmp_node;

			display(tmp_node);
			
			return tmp_node;
		}
		
		node* LL_Rotation(node* tmp_node)
		{
			cout<<"LL_Rotation"<<endl;
			
			node* p = tmp_node->parent;
			node* gp = p->parent;
			node* ggp = gp->parent;
			
			///
			
			gp->leftChild = p->rightChild;
			
			if(gp->leftChild)
				gp->leftChild->parent = gp;
				
			p->rightChild = gp;
			gp->parent = p;
			
			///
			
			p->leftChild = tmp_node->rightChild;
			
			if(p->leftChild)
				p->leftChild->parent = p;
				
			tmp_node->rightChild = p;
			p->parent = tmp_node;
			
			///
			
			tmp_node->parent = ggp;
			
			if(ggp)
			{
				if(gp == ggp->leftChild)
					ggp->leftChild = tmp_node;
				else
					ggp->rightChild = tmp_node;
			}
			else
			{
				display(tmp_node);
				
				return tmp_node;
			}
		}
		
		node* RR_Rotation(node* tmp_node)
		{
			cout<<"RR_Rotation"<<endl;
			
			node* p = tmp_node->parent;
			node* gp = p->parent;
			node* ggp = gp->parent;
			
			///
			
			gp->rightChild = p->leftChild;
			
			if(gp->rightChild)
				gp->rightChild->parent = gp;
				
			p->leftChild = gp;
			gp->parent = p;
			
			///
			
			p->rightChild = tmp_node->leftChild;
			
			if(p->rightChild)
				p->rightChild->parent = p;
				
			tmp_node->leftChild = p;
			p->parent = tmp_node;
			
			///
			
			tmp_node->parent = ggp;
			
			if(ggp)
			{
				if(gp == ggp->rightChild)
					ggp->rightChild = tmp_node;
				else
					ggp->leftChild = tmp_node;
			}
			else
			{
				display(tmp_node);
				
				return tmp_node;
			}
		}
		
		node* splay(node* tmp_node, node* root)
		{
			
			node* p = NULL;
			node* gp = NULL;
				
			while(1)
			{
				if(tmp_node == NULL || tmp_node == root)
				{
					cout<<"Splay not needed. Already root."<<endl;
					//return tmp_node;
					break;
				}
				else
				{
					cout<<"Splaying node."<<endl;
						
					p = tmp_node->parent;

					gp = p->parent;

					if(gp == NULL)
					{
						if(tmp_node == p->leftChild)
						{
							//Zig rotation
							//cout<<"L_ROT"<<endl;
							tmp_node = L_Rotation(tmp_node);
							//display(root);
						}
						else
						{
							//Zag rotation
							//cout<<"R_ROT"<<endl;
							tmp_node = R_Rotation(tmp_node);
							//display(root);
						}
					}
					else
					{
						if (p == gp->leftChild)
						{
							if(tmp_node == p->leftChild)
							{
								//Zig-Zig rotation
								//cout<<"LL_ROT"<<endl;
								tmp_node = LL_Rotation(tmp_node);
								//display(root);
							}
							else
							{
								//Zag-Zig rotation
								//cout<<"rl_ROT"<<endl;
								//tmp_node = R_Rotation(tmp_node);
								//cout<<"rl_ROT 11111111"<<endl;
								tmp_node = L_Rotation(R_Rotation(tmp_node));
								//cout<<"rl_ROT 22222222"<<endl;
								//cout<<tmp_node->key<<" <tmp : root> "<< root->key<<endl;
								//display(root);
							}
						}
						else
						{
							if(tmp_node == p->leftChild)
							{
							
								
								//Zig-Zag rotation
								
								//tmp_node = L_Rotation(tmp_node);
								tmp_node = R_Rotation(L_Rotation(tmp_node));
								
								
								
								//display(root);
							}
							else
							{
								//Zag-Zag rotation
								//cout<<"RR_ROT"<<endl;
								tmp_node = RR_Rotation(tmp_node);
								//display(root);
							}
						}
					}
				}
			}
			return root;
		}
		
		node* newNode(string key)
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
			tmp_node->parent = NULL;
			
			return tmp_node;
		}
		
		node* insertNode(string key, node* root)
		{
			node* tmp_node = newNode(key);
			
			//Inserting into empty tree.
			if(!root)
			{
				//cout<<"Placing node."<<endl;
				root = tmp_node;
				tmp_node = NULL;
				
				return root;
			}
			
			//Moving new node to proper position.
			node* tmp_root = root;
			
			while(1)
			{
				if(tmp_node->key < tmp_root->key)
				{
					if(tmp_root->leftChild)
					{
						tmp_root = tmp_root->leftChild;
						//cout<<"Going deeper and left."<<endl;
					}
					else
					{
						//cout<<"Placing node."<<endl;
						tmp_root->leftChild = tmp_node;
						tmp_node->parent = tmp_root;
						tmp_root = NULL;
						break;
					}
				}
				
				if(tmp_node->key > tmp_root->key)
				{
					if(tmp_root->rightChild)
					{
						tmp_root = tmp_root->rightChild;
						//cout<<"Going deeper and right."<<endl;
					}
					else
					{
						//cout<<"Placing node."<<endl;
						tmp_root->rightChild = tmp_node;
						tmp_node->parent = tmp_root;
						tmp_root = NULL;
						break;
					}
				}
				
				if(tmp_node->key == tmp_root->key)
				{
					//cout<<"Node is a duplicate."<<endl;
					tmp_node = tmp_root;
					tmp_root = NULL;
					break;
				}
			}
			
			//Should be in place.
			//Now splay.
			
			root = splay(tmp_node, root);

			tmp_node = NULL;
			
			return root;
		}
		
		void search()
		{
			
		}
		
		void deleteNode()
		{
			
		}
		
		node* clear(node* root)
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
			
			clear(root->leftChild);
			clear(root->rightChild);
			
			free(root);
			return NULL;
			
			cout<<"Tree cleared."<<endl;
		}
				
		int getHeight(node* root)
		{
			if(root == NULL)
				return 0;
			else
				return 1 + max(getHeight(root->leftChild), getHeight(root->rightChild));
		}
		
		
		void display(node* root)
		{
			if(root)
			{
				string left;
				string right;

				int height = getHeight(root);
				
				if(height >= 0)
				{
					cout<<"                               "<<root->key<<endl;
				}
				
				if(height >= 1)
				{
					if(root->leftChild == NULL )
						left = "...";
					else
						left = root->leftChild->key;
					
					if(root->rightChild == NULL)
						right = "...";
					else
						right = root->rightChild->key;
						
					cout<<"               "<<left<<"                             "<<right<<endl;
				}
				
				if(height >= 2)
				{
					if(root->leftChild == NULL || root->leftChild->leftChild == NULL )
						left = "...";
					else
						left = root->leftChild->leftChild->key;
					
					if(root->leftChild == NULL || root->leftChild->rightChild == NULL)
						right = "...";
					else
						right = root->leftChild->rightChild->key;
					
					cout << "       "<<left << "             " << right;

					if(root->rightChild == NULL || root->rightChild->leftChild == NULL )
						left = "...";
					else
						left = root->rightChild->leftChild->key;
					
					if(root->rightChild == NULL || root->rightChild->rightChild == NULL)
						right = "...";
					else
						right = root->rightChild->rightChild->key;

					cout << "             "<<left <<"             " << right << endl;
				}
				
				if(height >= 3)
				{
					if(root->leftChild == NULL || root->leftChild->leftChild == NULL || root->leftChild->leftChild->leftChild == NULL)
						left = "...";
					else
						left = root->leftChild->leftChild->leftChild->key;
					
					if(root->leftChild == NULL || root->leftChild->leftChild == NULL || root->leftChild->leftChild->rightChild == NULL)
						right = "...";
					else
						right = root->leftChild->leftChild->rightChild->key;
					
					cout << "   "<<left << "     " << right;
					
					
					
					if(root->leftChild == NULL || root->leftChild->rightChild == NULL || root->leftChild->rightChild->leftChild == NULL)
						left = "...";
					else
						left = root->leftChild->rightChild->leftChild->key;
					
					if(root->leftChild == NULL || root->leftChild->rightChild == NULL || root->leftChild->rightChild->rightChild == NULL)
						right = "...";
					else
						right = root->leftChild->rightChild->rightChild->key;
					
					cout << "     "<<left << "     " << right;
					

					if(root->rightChild == NULL || root->rightChild->leftChild == NULL || root->rightChild->leftChild->leftChild == NULL)
						left = "...";
					else
						left = root->rightChild->leftChild->leftChild->key;
					
					if(root->rightChild == NULL || root->rightChild->leftChild == NULL || root->rightChild->leftChild->rightChild == NULL)
						right = "...";
					else
						right = root->rightChild->leftChild->rightChild->key;

					cout << "     "<<left <<"     " << right;
					
					
					if(root->rightChild == NULL || root->rightChild->rightChild == NULL || root->rightChild->rightChild->leftChild == NULL)
						left = "...";
					else
						left = root->rightChild->rightChild->leftChild->key;
					
					if(root->rightChild == NULL || root->rightChild->rightChild == NULL || root->rightChild->rightChild->rightChild == NULL)
						right = "...";
					else
						right = root->rightChild->rightChild->rightChild->key;
					
					cout << "     "<<left << "     " << right<<endl;
				}
				
				if(height >= 4)
				{
					if(root->leftChild == NULL || root->leftChild->leftChild == NULL || root->leftChild->leftChild->leftChild == NULL || root->leftChild->leftChild->leftChild->leftChild == NULL) 
						left = "...";
					else
						left = root->leftChild->leftChild->leftChild->leftChild->key;
					
					if(root->leftChild == NULL || root->leftChild->leftChild == NULL || root->leftChild->leftChild->leftChild == NULL || root->leftChild->leftChild->leftChild->rightChild == NULL) 
						right = "...";
					else
						right = root->leftChild->leftChild->leftChild->rightChild->key;
					
					cout << " "<<left << " " << right;
					
					
					
					
					if(root->leftChild == NULL || root->leftChild->leftChild == NULL || root->leftChild->leftChild->rightChild == NULL || root->leftChild->leftChild->rightChild->leftChild == NULL) 
						left = "...";
					else
						left = root->leftChild->leftChild->rightChild->leftChild->key;
					
					if(root->leftChild == NULL || root->leftChild->leftChild == NULL || root->leftChild->leftChild->rightChild == NULL || root->leftChild->leftChild->rightChild->rightChild == NULL) 
						right = "...";
					else
						right = root->leftChild->leftChild->rightChild->rightChild->key;
					
					cout << " "<<left << " " << right;
					
					
					
					
					if(root->leftChild == NULL || root->leftChild->rightChild == NULL || root->leftChild->rightChild->leftChild == NULL || root->leftChild->rightChild->leftChild->leftChild == NULL) 
						left = "...";
					else
						left = root->leftChild->rightChild->leftChild->leftChild->key;
					
					if(root->leftChild == NULL || root->leftChild->rightChild == NULL || root->leftChild->rightChild->leftChild == NULL || root->leftChild->rightChild->leftChild->rightChild == NULL) 
						right = "...";
					else
						right = root->leftChild->rightChild->leftChild->rightChild->key;
					
					cout << " "<<left << " " << right;
					
					
					
					if(root->leftChild == NULL || root->leftChild->rightChild == NULL || root->leftChild->rightChild->rightChild == NULL || root->leftChild->rightChild->rightChild->leftChild == NULL) 
						left = "...";
					else
						left = root->leftChild->rightChild->rightChild->leftChild->key;
					
					if(root->leftChild == NULL || root->leftChild->rightChild == NULL || root->leftChild->rightChild->rightChild == NULL || root->leftChild->rightChild->rightChild->rightChild == NULL) 
						right = "...";
					else
						right = root->leftChild->rightChild->rightChild->rightChild->key;
					
					cout << " "<<left << " " << right;
					
					
					
					if(root->rightChild == NULL || root->rightChild->leftChild == NULL || root->rightChild->leftChild->leftChild == NULL || root->rightChild->leftChild->leftChild->leftChild == NULL) 
						left = "...";
					else
						left = root->rightChild->leftChild->leftChild->leftChild->key;
					
					if(root->rightChild == NULL || root->rightChild->leftChild == NULL || root->rightChild->leftChild->leftChild == NULL || root->rightChild->leftChild->leftChild->rightChild == NULL) 
						right = "...";
					else
						right = root->rightChild->leftChild->leftChild->rightChild->key;
					
					cout << " "<<left << " " << right;
					
					
					
					if(root->rightChild == NULL || root->rightChild->leftChild == NULL || root->rightChild->leftChild->rightChild == NULL || root->rightChild->leftChild->rightChild->leftChild == NULL) 
						left = "...";
					else
						left = root->rightChild->leftChild->rightChild->leftChild->key;
					
					if(root->rightChild == NULL || root->rightChild->leftChild == NULL || root->rightChild->leftChild->rightChild == NULL || root->rightChild->leftChild->rightChild->rightChild == NULL) 
						right = "...";
					else
						right = root->rightChild->leftChild->rightChild->rightChild->key;
					
					cout << " "<<left << " " << right;
					
					
					
					if(root->rightChild == NULL || root->rightChild->rightChild == NULL || root->rightChild->rightChild->leftChild == NULL || root->rightChild->rightChild->leftChild->leftChild == NULL) 
						left = "...";
					else
						left = root->rightChild->rightChild->leftChild->leftChild->key;
					
					if(root->rightChild == NULL || root->rightChild->rightChild == NULL || root->rightChild->rightChild->leftChild == NULL || root->rightChild->rightChild->leftChild->rightChild == NULL) 
						right = "...";
					else
						right = root->rightChild->rightChild->leftChild->rightChild->key;
					
					cout << " "<<left << " " << right;
					
					
					
					if(root->rightChild == NULL || root->rightChild->rightChild == NULL || root->rightChild->rightChild->rightChild == NULL || root->rightChild->rightChild->rightChild->leftChild == NULL) 
						left = "...";
					else
						left = root->rightChild->rightChild->rightChild->leftChild->key;
					
					if(root->rightChild == NULL || root->rightChild->rightChild == NULL || root->rightChild->rightChild->rightChild == NULL || root->rightChild->rightChild->rightChild->rightChild == NULL) 
						right = "...";
					else
						right = root->rightChild->rightChild->rightChild->rightChild->key;
					
					cout << " "<<left << " " << right<<endl;
	
					
				}
				
				if(height >= 5)
				{
					cout<<"****************************************************************"<<endl;
					cout<<"          Tree levels greater than 4 are not displyed.          "<<endl;
					cout<<"****************************************************************"<<endl;
				}
			}
			else
			{
				//Should never see this, but just incase.
				cout<<"****************************************************************"<<endl;
				cout<<"                  There is no tree to display.                  "<<endl;
				cout<<"****************************************************************"<<endl;
			}
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
					root = splayTree.insertNode(key, root);
					
					//call display function here to show after every insert.
					splayTree.display(root);
				}

				break;
				
			case 2:
				cin.clear();
				cin.sync();
				cout << endl;
				
				cout << " Enter key to add: ";
				cin>>key;
				
				root = splayTree.insertNode(key, root);
				
				//call display function here to show after every insert.
				//splayTree.display(root);
				
				break;
				
			case 3:
//				cin.clear();
//				cin.sync();
//				cout << endl;
//				
//				cout << " Enter key to delete: ";
//				cin>>key;
//				
//				root = splayTree.DeleteKey(key, root);
//				
//				//call display function here to show after every insert.
//				splayTree.InOrder(root, splayTree.getHeight(root));
				
				break;
				
			case 4:
//				cin.clear();
//				cin.sync();
//				cout << endl;
//				
//				cout << " Enter key to search for: ";
//				cin>>key;
//				
//				root = splayTree.searchKey(key, root);
//				
//				//call display function here to show after every insert.
//				splayTree.InOrder(root, splayTree.getHeight(root));
				
				break;
				
			case 5:
				cin.clear();
				cin.sync();
				cout << endl;
							
				root = splayTree.clear(root);
				splayTree.display(root);
				
				//call display function here to show after every insert.
				
				
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
