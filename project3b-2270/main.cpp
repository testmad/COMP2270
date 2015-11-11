#include <iostream>

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
		
		node* L_Rotation(node* tmp_node)
		{
			node* p = tmp_node->parent;
			
			p->leftChild = tmp_node->rightChild;
			
			if(p->leftChild)
				p->leftChild->parent = p;
				
			tmp_node->rightChild = p;
			tmp_node->parent = p->parent;
			p->parent = tmp_node;
			
			return tmp_node;
		}
		
		node* R_Rotation(node* tmp_node)
		{
			node* p = tmp_node->parent;
			
			p->rightChild = tmp_node->leftChild;
			
			if(p->rightChild)
				p->rightChild->parent = p;
				
			tmp_node->leftChild = p;
			tmp_node->parent = p->parent;
			p->parent = tmp_node;
			
			return tmp_node;
		}
		
		node* LL_Rotation(node* tmp_node)
		{
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
				return tmp_node;
			}
		}
		
		void LR_Rotation()
		{
			
		}
		
		void RL_Rotation()
		{
			
		}
		
		node* RR_Rotation(node* tmp_node)
		{
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
					break;
				}
				else
				{
					cout<<"Splaying node."<<endl;
					cout<<"Parent assignment"<<endl;
					p = tmp_node->parent;

					cout<<"GrandParent assignment"<<endl;
					gp = p->parent;

					if(gp == NULL)
					{
						cout<<"1 begin."<<endl;
						
						if(tmp_node == p->leftChild)
						{
							cout<<"1a."<<endl;
							//Zig rotation
							root = L_Rotation(tmp_node);
							
						}
						else
						{
							cout<<"1b."<<endl;
							//Zag rotation
							root = R_Rotation(tmp_node);
							
						}
						cout<<"1 end."<<endl;
					}
					else
					{
						cout<<"2 begin."<<endl;
						if (p == gp->leftChild)
						{
							cout<<"2a."<<endl;
							if(tmp_node == p->leftChild)
							{
								cout<<"2a1."<<endl;
								//Zig-Zig rotation
								root = LL_Rotation(tmp_node);
							}
							else
							{
								cout<<"2a2."<<endl;
								//Zig-Zag rotation
								root = L_Rotation(tmp_node);
								root = R_Rotation(tmp_node);
							}
						}
						else
						{
							cout<<"2b."<<endl;
							if(tmp_node == p->leftChild)
							{
								cout<<"2b1."<<endl;
								//Zag-Zig rotation
								root = R_Rotation(tmp_node);
								root = L_Rotation(tmp_node);
							}
							else
							{
								cout<<"2b2."<<endl;
								//Zag-Zag rotation
								root = RR_Rotation(tmp_node);
							}
						}
						cout<<"2 end."<<endl;
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
				cout<<"Placing node."<<endl;
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
						cout<<"Going deeper and left."<<endl;
					}
					else
					{
						cout<<"Placing node."<<endl;
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
						cout<<"Going deeper and right."<<endl;
					}
					else
					{
						cout<<"Placing node."<<endl;
						tmp_root->rightChild = tmp_node;
						tmp_node->parent = tmp_root;
						tmp_root = NULL;
						break;
					}
				}
				
				if(tmp_node->key == tmp_root->key)
				{
					cout<<"Node is a duplicate."<<endl;
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
		
		void clear()
		{
			
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
				//
				//
				// crashing on getheight after inserting h
				//
				//
				
				cout<<"TRYING: "<<getHeight(root)<<endl;
				
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
			}
			else
			{
				cout<<"PROBLEM!!!!"<<endl;
			}
		}
		
		
};

int main()
{
	SplayTree splayTree;
		
	node* root;
	
	root = NULL;

	cout<<"Inserting m."<<endl;
	root = splayTree.insertNode("m", root);
	system("pause");
	splayTree.display(root);
	
	system("pause");
	
	cout<<"Inserting o."<<endl;
	//cout<<"Root: "<<root->key<<endl;
	root = splayTree.insertNode("o", root);
	system("pause");
	splayTree.display(root);
	
	system("pause");
	
	cout<<"Inserting e."<<endl;
	//cout<<"Root: "<<root->key<<endl;
	root = splayTree.insertNode("e", root);
	system("pause");
	splayTree.display(root);
	
	system("pause");
	
	cout<<"Inserting a."<<endl;
	//cout<<"Root: "<<root->key<<endl;
	root = splayTree.insertNode("a", root);
	system("pause");
	splayTree.display(root);
	
	system("pause");
	
	cout<<"Inserting z."<<endl;
	//cout<<"Root: "<<root->key<<endl;
	root = splayTree.insertNode("z", root);
	system("pause");
	splayTree.display(root);
	
	system("pause");

	cout<<"Inserting h."<<endl;
	root = splayTree.insertNode("h", root);
	system("pause");
	splayTree.display(root);///////////////////////CRASHING HERE!!!??????
	
	system("pause");
	
	cout<<"Inserting k."<<endl;
	root = splayTree.insertNode("k", root);
	system("pause");
	splayTree.display(root);
	
	system("pause");
	
	cout<<"Inserting j."<<endl;
	root = splayTree.insertNode("g", root);
	system("pause");
	
	cout<<"Inserting k again."<<endl;
	root = splayTree.insertNode("k", root);
	system("pause");
	
	cout<<"Inserting m again."<<endl;
	root = splayTree.insertNode("m", root);
	system("pause");
	
	cout<<endl<< splayTree.getHeight(root)<<endl;
	
	
	splayTree.display(root);
	
	system("pause");
	
	return 0;
}
