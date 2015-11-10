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
		
		void L_Rotation()
		{
			
		}
		
		void R_Rotation()
		{
			
		}
		
		void LL_Rotation()
		{
			
		}
		
		void LR_Rotation()
		{
			
		}
		
		void RL_Rotation()
		{
			
		}
		
		void RR_Rotation()
		{
			
		}
		
		void splay()
		{
		
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
			
			//We are inserting into empty tree.
			if(!root)
			{
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
						tmp_root = tmp_root->leftChild;
					else
					{
						tmp_root->leftChild = tmp_node;
						tmp_node->parent = tmp_root;
						break;
					}
				}
				
				if(tmp_node->key > tmp_root->key)
				{
					if(tmp_root->rightChild)
						tmp_root = tmp_root->rightChild;
					else
					{
						tmp_root->rightChild = tmp_node;
						tmp_node->parent = tmp_root;
						break;
					}
				}
			}
			
			//Should be in place.
			//Now splay.
//			while(1)
//			{
//				
//			}
			
				
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
			if(!root)
				return -1;
				
			return 1 + max(getHeight(root->leftChild), getHeight(root->rightChild));
		}
		
		void display()
		{
			
		}
		
		
};

int main()
{
	SplayTree splayTree;
		
	node* root;
	
	root = NULL;

	cout<<"Inserting m."<<endl;
	root = splayTree.insertNode("m", root);
	
	cout<<"Inserting o."<<endl;
	root = splayTree.insertNode("o", root);
	
	cout<<"Inserting e."<<endl;
	root = splayTree.insertNode("e", root);
	
	cout<<"Inserting a."<<endl;
	root = splayTree.insertNode("a", root);
	
	cout<<"Inserting z."<<endl;
	root = splayTree.insertNode("z", root);

	cout<<"Inserting h."<<endl;
	root = splayTree.insertNode("h", root);
	
	cout<<"Inserting k."<<endl;
	root = splayTree.insertNode("k", root);
	
	cout<<"Inserting j."<<endl;
	root = splayTree.insertNode("j", root);
	
	cout<<endl<< splayTree.getHeight(root)<<endl;
	
	cout<<root->key<<endl;
	cout<<root->leftChild->leftChild->key<<endl;
	cout<<root->leftChild->rightChild->key<<endl;
	cout<<root->leftChild->rightChild->leftChild->key<<endl;
	cout<<root->leftChild->rightChild->rightChild->key;
	
	system("pause");
	
	return 0;
}
