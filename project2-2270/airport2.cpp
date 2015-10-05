/*
COMP-2270-01 Fall 2015
Title: Project 2 (Airport Traffic Simulator using priority queues)
Student: David Walker
Instructor: Randy Baker
Assigned: September 17, 2015
Due Date: October 8, 2015
*/

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

struct plane
{
	int id;
	int fuel;
	int type;
	int timeWaited;
	struct plane *next;
};

class Airstrip
{
	private:
		plane *front;
		
	public:
		int inQueue;
		int totalWait;
		
		Airstrip()
		{
			inQueue = 0;
			totalWait = 0;
			
			front = NULL;			
		}
		
		int insert(ofstream& outDataFile, int id, int fuel, int type)
		{
			//If there is space in the queue.
			if(inQueue < 6)
			{
				plane *tmp, *que;
			
				tmp = new plane;
			
				tmp->id = id;
				tmp->fuel = fuel;
				tmp->type = type;
				tmp->timeWaited = 0;
				
				//Different inserts for different plane types.
				if(tmp->type == 1)
				{
					outDataFile<<"\t\tPlane " << id << " ready to land; " << tmp->fuel << " units of fuel remaining." << endl;
					if (front == NULL || fuel < front->fuel)
					{
						tmp->next = front;
						front = tmp;
					}
					else
					{
						que = front;
						//This is only needed if the queue is for planes where the fuel matters.
						while(que->next != NULL && que->next->fuel <= fuel)
							que = que->next;
	
						tmp->next = que->next;
						que->next = tmp;
					}
				}
				else
				{
					outDataFile<<"\t\tPlane " << id << " ready to take off." << endl;
					if (front == NULL)
					{
						tmp->next = front;
						front = tmp;
					}
					else
					{
						que = front;
						tmp->next = que->next;
						que->next = tmp;
					}
				}
					
				inQueue++;
				
				return 1;
			}
			//Turn away planes if queue is full.
			else
			{
				plane *tmp, *que;
			
				tmp = new plane;
			
				tmp->id = id;
				tmp->fuel = fuel;
				tmp->type = type;
				
				if(tmp->type == 1)
				{
					outDataFile<<"\t\tPlane " << id << " ready to land; " << tmp->fuel << " units of fuel remaining." << endl;
					outDataFile<<"\t\tPlane " << id << " directed to another airport." << endl;
				}
				else
				{
					outDataFile<<"\t\tPlane " << id << " ready to take off." << endl;
					outDataFile<<"\t\tPlane " << id << " told to try later." << endl;
				}
				
				free(tmp);
					
				return 0;
			}
		}
		
		int remove(ofstream& outDataFile)
		{
			plane *tmp;
			
			if(front == NULL)
			{
				return 0;
			}
			else
			{
				//int tmpWaited = 0;
				tmp = front;
				
				//Different output based on type of plane removed.
				if(tmp->type == 1)
					outDataFile<<"Plane " << tmp->id << " landed; " << "in queue " << tmp->timeWaited << " time units."<< endl;
				else
					outDataFile<<"Plane " << tmp->id << " took off; " << "in queue " << tmp->timeWaited << " time units." << endl;
				
				totalWait += tmp->timeWaited;
				inQueue--;
				
				front = front->next;
				free(tmp);
				
				return 1;
			}
		}
		
		int purge(ofstream& outDataFile)
		{
			plane *tmp, *prev;
			tmp = front;
			
			int count = 0;
			
			//Not doing a proper delete from linked list.  Since only the front items are going to have negative fuel,
			//these are the only ones to check.  No need to handle deleting from middle of the list.
			while(tmp != NULL)
			{
				if(tmp->fuel < 0 )
				{
					outDataFile<<"\t\tPlane " << tmp->id << " has crashed!"<<endl;
					
					front = tmp->next;

					free(tmp);

					tmp = front;
					inQueue--;
					count++;
				}
				//No more front is no longer negative fuel.  Setting NULL to break from loop.
				else
				{
					tmp = NULL;
				}
			}
			return count;
		}
		
		void cycle()
		{
			plane *tmp;
			tmp = front;
			
			if(front == NULL)
			{
				//nothing todo
			}	
			else
			{
				while(tmp != NULL)
				{
					tmp->fuel--;
					tmp->timeWaited++;
					
					tmp = tmp->next;
				}
			}
		}
};

int pRandom( double expectedValue );
double randZeroToOne();

int main(int argc, char** argv)
{
	srand(time(NULL));
	
	ofstream outDataFile;
	string filename;
	
	//TODO: User input values.
	int tUnits = 0; //40;
	double lVal = 0; //.47;
	double tVal = 0; //.47;
	double fVal = 0; //5;
	
	int planeId = 1;
	int count = 0;
	
	int totalLanded = 0;
	int totalTakeoff = 0;
	int totalIdle = 0;
	int totalRefuse = 0;
	int totalCrash = 0;
	
	Airstrip landingQ;
	Airstrip takeoffQ;
	
	cout << "Enter a filename to save output to (existing file will be overwritten): ";
	getline(cin, filename);
	
	outDataFile.open(filename.c_str());
	
	if(outDataFile.fail()){
		cout << "Error creating data file." << endl;
		system("pause");
		exit(1);
	}
	
	cin.clear();
	cin.sync();
	
	cout << "Enter total time units (int): ";
	cin>>tUnits;
	while(cin.fail() || tUnits == '\0')
	{
		cout<<endl<<"Input invalid."<<endl;
		cin.clear();
		cin.sync();
		cout << "Enter total time units (int): ";
		cin>>tUnits;
	}
	cin.clear();
	cin.sync();
	
	cout << "Enter expected value for planes landing (double): ";
	cin>>lVal;
	while(cin.fail() || lVal == '\0')
	{
		cout<<endl<<"Input invalid."<<endl;
		cin.clear();
		cin.sync();
		cout << "Enter expected value for planes landing (double): ";
		cin>>lVal;
	}
	cin.clear();
	cin.sync();
	
	cout << "Enter expected value for planes taking off (double): ";
	cin>>tVal;
	while(cin.fail() || tVal == '\0')
	{
		cout<<endl<<"Input invalid."<<endl;
		cin.clear();
		cin.sync();
		cout << "Enter expected value for planes taking off (double): ";
		cin>>tVal;
	}
	cin.clear();
	cin.sync();
	
	cout << "Enter expected value for fuel in planes (double): ";
	cin>>fVal;
	while(cin.fail() || fVal == '\0')
	{
		cout<<endl<<"Input invalid."<<endl;
		cin.clear();
		cin.sync();
		cout << "Enter expected value for planes taking off (double): ";
		cin>>fVal;
	}
	cin.clear();
	cin.sync();
		
	outDataFile << "Total time units: " << tUnits << endl <<"Landing expected: " << lVal << endl << "Takeoff expected: " << tVal << endl << "Fuel expected: " << fVal << endl;
	outDataFile << endl << "ACTIVITY LOG:" << endl << endl;
	while(tUnits > count)
	{
		int tmp;

		tmp = pRandom(lVal);
		if(tmp > 0)
		{
			for(int i = 0; i < tmp; i++)
			{
				if(landingQ.insert(outDataFile, planeId, pRandom(fVal), 1))
					planeId++;
				else
				{
					planeId++;
					totalRefuse++;
				}
			}
		}

		tmp = pRandom(tVal);
		if(tmp > 0)
		{
			for(int i = 0; i < tmp; i++)
			{
				if(takeoffQ.insert(outDataFile, planeId, pRandom(fVal), 0))
					planeId++;
				else
				{
					planeId++;
					totalRefuse++;
				}
			}
		}

		totalCrash += landingQ.purge(outDataFile);

		outDataFile << count+1 << ":\t";
		
		if(landingQ.remove(outDataFile))
			totalLanded++;
		else
		{
			if(takeoffQ.remove(outDataFile))
				totalTakeoff++;
			else
			{
				outDataFile << "Runway is idle." << endl;
				totalIdle++;
			}
		}	

		landingQ.cycle();
		takeoffQ.cycle();

		count++;
	}
	
	//Summary
	outDataFile << endl << "SUMMARY:" << endl << endl;
	outDataFile << "\tSimulation has concluded after " << tUnits << " time units." << endl << endl;
	outDataFile << "\tTotal number of planes processed: \t\t\t" << (planeId - 1) << endl;
	outDataFile << "\t\tNumber of planes landed: \t\t\t\t" << totalLanded << endl;
	outDataFile << "\t\tNumber of planes taken off: \t\t\t" << totalTakeoff << endl;
	outDataFile << "\t\tNumber of planes refused use: \t\t\t" << totalRefuse << endl;
	outDataFile << "\t\tNumber left ready to land: \t\t\t\t" << landingQ.inQueue << endl;
	outDataFile << "\t\tNumber left ready to take off: \t\t\t" << takeoffQ.inQueue << endl;
	outDataFile << "\t\tNumber crashed: \t\t\t\t\t\t" << totalCrash << endl;
	outDataFile << "\t\tPercentage of time runway was idle: \t" << ((float)totalIdle/(float)tUnits)*100 << endl;
	if(totalLanded == 0)
	{
		outDataFile << "\t\tAverage wait time to land: \t\t\t\t0" << endl;
	}
	else
	{
		outDataFile << "\t\tAverage wait time to land: \t\t\t\t" << (float)landingQ.totalWait/(float)totalLanded << endl;
	}
	if(totalTakeoff == 0)
	{
		outDataFile << "\t\tAverage wait time to take off: \t\t\t0" << endl;
	}
	else
	{
		outDataFile << "\t\tAverage wait time to take off: \t\t\t" << (float)takeoffQ.totalWait/(float)totalTakeoff << endl;
	}
	return 0;
}

int pRandom( double expectedValue)
{
	int count = 0;
	double limit = exp(-expectedValue);
	double product = randZeroToOne();
	
	while( product > limit)
	{
		product *= randZeroToOne();
		count += 1;
	}
	
	return count;
}

double randZeroToOne()
{
    return (double)rand() / (double)(RAND_MAX);
}
