#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <string.h>

using namespace std;

struct Edge
{
	string node1;
	string node2;
	int weight;
};

string center(string input, int width);

int main()
{
	
	ifstream inDataFile;
	string filename;
	
	int numLines = 0;
	string dummy;
	
	int numNodes = 0;
	
	cout << "Enter a filename to process: ";
	getline(cin, filename);
	
	
	inDataFile.open(filename.c_str());
	
	if(inDataFile.fail())
	{
		cout << "Error opening data file." << endl;
		system("pause");
		exit(1);
	}
	
	while( getline(inDataFile,dummy))
		++numLines;
		
	numNodes = ceil(numLines/2.0);
	
	if(numNodes <= 1)
	{
		cout << "Unable to generate data." << endl;
		system("pause");
		exit(1);
	}
	
	inDataFile.clear();
	inDataFile.seekg(0, inDataFile.beg);
	
	//allocate node names
	string nodes[numNodes];
	
	//pupolate with node labels
	for(int i = 0; i< numNodes; i++)
		getline(inDataFile,nodes[i]);
	
	//allocate matrix
	int matrix[numNodes][numNodes];
	
	//init matrix with 0's
	for(int j = 0; j< numNodes; j++)
	{
		for(int k = 0; k< numNodes; k++)
		{
			matrix[j][k]  = 0;
		}
	}

	//populate upper portion and create edges for later sorting.
	int counter = 1;
	
	Edge* edge = new Edge[((numNodes * numNodes + numNodes)/2) - numNodes];
	int edgeCount = 0;
	
	for(int j = 0; j< numNodes - 1; j++)
	{
		for(int k = 0 + counter; k< numNodes; k++)
		{
			inDataFile>>matrix[j][k];
			edge[edgeCount].node1 = nodes[j];
			edge[edgeCount].node2 = nodes[k];
			edge[edgeCount].weight = matrix[j][k];
			edgeCount++;
		}
		counter++;
	}
	cout<<endl;
		
	//populate lower portion
	for(int j = 0; j< numNodes; j++)
	{
		for(int k = 0; k< numNodes; k++)
		{
			matrix[k][j]  = matrix[j][k];
		}
	}
	
	//Pretty printed matrix	
	cout << center("Adjacency Matrix", 6+ 6*numNodes) << endl<< endl;
	cout<<center(" ", 5);
	for(int i = 0; i<numNodes; i++)
		cout<<center(nodes[i], 11);
	cout<<endl;
	cout<<"     ";
	for(int i = 0; i<numNodes; i++)
		cout<<center("------", 6);
	cout<<"-"<<endl;
	
	for(int j = 0; j< numNodes; j++)
	{
		cout<<center(nodes[j], 5)<<"  |";
		
		for(int k = 0; k< numNodes; k++)
		{
			cout<<setw(5)<< matrix[j][k]<<"|";
		}
		cout<<endl;
		cout<<"     ";
		for(int i = 0; i<numNodes; i++)
			cout<<center("------", 6);
		cout<<"-"<<endl;
	}
	
	//sort edges in ascending order.
	for(int i = 0; i < ((numNodes * numNodes + numNodes)/2) - numNodes; i++)
	{
		for(int j = i+1; j<((numNodes * numNodes + numNodes)/2) - numNodes;j++)
		{
			if(edge[i].weight > edge[j].weight)
			{
				Edge temp = edge[i];
				edge[i] = edge[j];
				edge[j] = temp;
			}
		}
	}
	
	//show all edges after sort
	for(int i = 0; i< ((numNodes * numNodes + numNodes)/2) - numNodes;i++)
		cout << "{ "<<edge[i].node1<<"  "<<edge[i].node2 <<" }"<<"\tweight = "<<edge[i].weight<<endl;
	cout<<endl;


	//selecting edges ?
	string chosen[numNodes];
	for(int i = 0; i < numNodes; i++)
		chosen[i] = nodes[i];
	
	
	int weightTotal = 0;
		
	int nextIndex = 0;
	bool pass1 = false;
	bool pass2 = false;
	
	for(int i = 0; i < ((numNodes * numNodes + numNodes)/2) - numNodes;i++)
	{
		
		if(edge[i].weight > 0)
		{
//			if( (chosen.find(edge[i].node1) == chosen.npos) && (chosen.find(edge[i].node2) == chosen.npos) )
				//cout<<"NOTHING"<<endl;
			
			for(int j = 0; j < numNodes; j++)
			{
				if(chosen[j].find(edge[i].node1) == chosen[j].npos)
				{
					
					pass1 = false;
				}
				else
					pass1 = true;
				
				if(chosen[j].find(edge[i].node2) == chosen[j].npos)
				{
						
					pass2 = false;
				}
				else
					pass2 = true;
					
					
				
				 
				
				
			}
			
			if(pass1 && pass2)
			{
				cout<<"both nodes in one set"<<endl;
			}

			else
			{
				cout<<"both nodes are in different sets"<<endl;
				
				for(int j = 0; j < numNodes; j++)
				{
					if(chosen[j].find(edge[i].node1) != chosen[j].npos)
					{
						
						chosen[j] += edge[i].node2;
						
						for(int k = 0; k < numNodes; k++)
						{
							if(chosen[k].find(edge[i].node2) != chosen[j].npos)
								chosen[k] = "";
						}
						
//						edge[i].node1 = "";
//						edge[i].node2 = "";
//						edge[i].weight = 0;
						
					}
				
				
					
				}
				
			}
			
			
			pass1,pass2 = false;
			
			
			
			for(int i = 0; i < numNodes; i++)
				cout << chosen[i]<<endl ;

			
			//if( (chosen.find(edge[i].node1) == chosen.npos) && (chosen.find(edge[i].node2) == chosen.npos) )

					
//			if( (chosen.find(edge[i].node1) == chosen.npos) && (chosen.find(edge[i].node2) == chosen.npos) )
//			{
//				cout << "{ "<<edge[i].node1<<"  "<<edge[i].node2 <<" }"<<"\tweight = "<<edge[i].weight<<endl;
//				chosen += edge[i].node1;
//				chosen += edge[i].node2;
//				weightTotal += edge[i].weight;
//			}
				
		}
		else
		{
			edge[i].node1 = "";
			edge[i].node2 = "";
			edge[i].weight = 0;
			
		}

		
		
		
		
	}
		
	return 0;
}

string center(string input, int width)
{
	return string((width - input.length()) / 2, ' ') + input;
}
