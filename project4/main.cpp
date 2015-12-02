//David Walker
//Project 4
//All commented lines are either explaining what something does, or is left overs from debug.
//If you want to actually watch the program go through the steps, uncomment the couts and all methods.

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
	bool chosen;
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
			edge[edgeCount].chosen = false;
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
	
	//sort edges in ascending numerical order by weight and alphabetical order by first node.
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
			
			if(edge[i].weight == edge[j].weight)
			{
				if(edge[i].node1 > edge[j].node1)
				{
					Edge temp = edge[i];
					edge[i] = edge[j];
					edge[j] = temp;
				}
			}
		}
	}
	
	
	
	
//	//show all edges after sort
//	for(int i = 0; i< ((numNodes * numNodes + numNodes)/2) - numNodes;i++)
//		cout << "{ "<<edge[i].node1<<"  "<<edge[i].node2 <<" }"<<"\tweight = "<<edge[i].weight<<endl;
//	cout<<endl;


	//selecting edges
	string chosen[numNodes];
	for(int i = 0; i < numNodes; i++)
		chosen[i] = nodes[i];
	
	int weightTotal = 0;
		
	int nextIndex = 0;
	
	int chosenCount = 0;
	
	int i = 0;
	
	while(i < ((numNodes * numNodes + numNodes)/2) - numNodes  )
	{
		if(chosenCount == numNodes -1)
			break;
			
		bool free = true;
		
		//cout<< "Considering edge: "<<edge[i].node1<<"-"<<edge[i].node2<<endl;
		if(edge[i].weight > 0)
		{
			for(int j = 0; j < numNodes; j++)
			{
				//cout<<"Checking edge nodes: " << edge[i].node1 <<"-"<<edge[i].node2<<" against "<< chosen[j]<<endl; 
				
				if( chosen[j].find(edge[i].node1) != chosen[j].npos &&
					chosen[j].find(edge[i].node2) != chosen[j].npos)
				{
					//cout<<"\t-Rejecting edge: "<< edge[i].node1 <<"-"<<edge[i].node2<< "\tBoth nodes in one set."<<endl;
					edge[i].chosen = false;
					free = false;
				}
			}
				
			if(free)
			{
				edge[i].chosen = true;
				//cout<<"Nodes "<< edge[i].node1 <<"-"<<edge[i].node2 << " are independent.  Finding first node."<<endl;
				
				int firstNodeLocation;
				int secondNodeLocation;
				
				for( int j = 0; j < numNodes; j++ )
				{
					if(chosen[j].find(edge[i].node1) != chosen[j].npos)
					{
						//cout<<"Found "<< edge[i].node1 << " in " << chosen[j] << endl;
						
						firstNodeLocation = j;
					}
				}
				
				for( int j = firstNodeLocation + 1; j < numNodes; j++ )
				{
					if(chosen[j].find(edge[i].node2) != chosen[j].npos)
					{
						//cout<<"Found "<< edge[i].node2 << " in " << chosen[j] << endl;

						secondNodeLocation = j;
					}
				}
				
				chosen[firstNodeLocation] += chosen[secondNodeLocation];
				chosen[secondNodeLocation] = "";
				
//				cout<<"Sets after moving: "<<endl;
//				for( int j = 0; j < numNodes; j++ )
//				{
//					
//					cout<<chosen[j]<<endl;
//
//				}
				
				chosenCount++;
			}
		}
			
		else
		{
			//cout<<"\t-Edge not present."<<endl;
		}
		
		i++;
		
	}
	
//	//show chosen edges after kruskals.
//	for(int i = 0; i< ((numNodes * numNodes + numNodes)/2) - numNodes;i++)
//	{
//		if(edge[i].chosen)
//			cout << "{ "<<edge[i].node1<<"  "<<edge[i].node2 <<" }"<<"\tweight = "<<edge[i].weight<<endl;
//	}
		
	cout<<endl<<endl<<endl<<endl;
	cout<<center( "Edges included in the", 6+ 6*numNodes)<<endl;
	cout<<center( "minimal spanning tree", 6+ 6*numNodes)<<endl;
	cout<<center( "for this graph are:", 6+ 6*numNodes)<<endl;
	cout<<endl<<endl;
	
	//pretty print chosen edges after kruskals and add up weight.
	string str;
	int totalWeight = 0;
	
	for(int i = 0; i< ((numNodes * numNodes + numNodes)/2) - numNodes;i++)
	{
		if(edge[i].chosen)
		{
			str =  "{ ";
			str.append(edge[i].node1 );
			str.append("  " );
			str.append(edge[i].node2 );
			str.append(" }" );
			str.append("\tweight =" );
			
			cout <<center( str, 6+ 6*numNodes) << setw(3) << edge[i].weight << endl;
			
			totalWeight += edge[i].weight;
		}
			
	}
	
	cout<<endl<<endl;
	cout<<center( "Total weight of the ", 6+ 6*numNodes)<<endl;
	cout<<center( "minimal spanning tree", 6+ 6*numNodes)<<endl;
	cout<<center( "is: ", 2+ 6*numNodes) << setw(4) << totalWeight << endl;
}

string center(string input, int width)
{
	return string((width - input.length()) / 2, ' ') + input;
}
