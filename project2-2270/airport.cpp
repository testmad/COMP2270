#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

struct plane
{
	int id;
	int fuel;
	int timeWaited;
	struct plane *next;
};

class AirportQueue
{
	private:
		plane *front;
		int qType;
		
	public:
		
		int inQueue;
		int totalSuccess;
		int totalFail;
		int totalRefused;
		int totalWaitTime;
		
		AirportQueue(int type)
		{
			qType = type;
			front = NULL;
			inQueue = 0;
			totalSuccess = 0;
			totalFail = 0;
			totalRefused = 0;
			totalWaitTime = 0;
		}
		
		void add(int id)
		{
			if(inQueue < 6)
			{
				plane *tmp, *que;
				tmp = new plane;
				
				tmp->id = id;
				tmp->timeWaited = 0;
				tmp->fuel = fuelRandom( 2 );
				
				
				if(qType)
				{
					cout<<"\t\tPlane " << id << " ready to land; " << tmp->fuel << " units of fuel remaining." << endl;
					
					if(front == NULL || tmp->fuel < front->fuel )
					{
						tmp -> next = front;
						front = tmp;
					}
					else
					{
						que = front;
						while (que->next != NULL && que->next->fuel <= tmp->fuel)
						{
							que = que->next;
						}
						
						tmp->next = que->next;
						que->next = tmp;
					}
					
				}
				else
				{
					cout<<"\t\tPlane " << id << " ready to take off." << endl;
					
					if(front == NULL )
					{
						tmp -> next = front;
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
			}
			else
			{	
				cout<<"\t\tPlane " << id << " told to try later." << endl;
				totalRefused++;
			}
		}
	
		int remove()
		{
			plane *tmp;
			
			if(front == NULL){
			
				//cout<<"No planes to remove.\n";
				return 0;
			}
				
			else
			{
				tmp = front;
				
				//cout<<"DEQUEUE"<<endl;
				
				if(qType){
					cout<<"Plane " << tmp->id << " landed; " << "in queue " << tmp->timeWaited << " time units." << endl;}
				else{
					cout<<"Plane " << tmp->id << " took off; " << "in queue " << tmp->timeWaited << " time units." << endl;}
				
				totalWaitTime += tmp->timeWaited;
				front = front->next;
				
				//I learned about this over the summer after continuing with classes and pointers from Programming 2.
				//May not be best thing to use since it doesn't throw exceptions, but since we aren't catching exceptions
				//for this project, I figure I can get away with using it.
				free(tmp);
				inQueue--;
				totalSuccess++;
				return 1;
			}
		}
		
		void cycle()
		{
			plane *tmp, *prev;
			
			if(front == NULL){
			
				//cout<<"No planes to remove.\n";
				
			}
				
			else
			{
				tmp = front;
				
				
				
				if(tmp->fuel == 0 && qType)
				{
					cout<<"\t\tPlane " << tmp->id << " has crashed!"<<endl;
					
					if(tmp == front)
					{
						front = tmp->next;
						free(tmp);
					}
					else
					{
						prev->next = tmp->next;
						free(tmp);
					}
					totalFail++;
					inQueue--;
				}
				else
				{
					tmp->fuel--;
					tmp->timeWaited++;
					
					prev = tmp;
					
					tmp = tmp->next;
				}
			}
		}
		
		int fuelRandom( double expectedValue)
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
	
};

int PoissonRandom( double expectedValue );
double randZeroToOne();

int main(int argc, char** argv)
{
	srand(time(NULL));
	
	int timeUnits = 10;
	double pVal = .75;
	
	int idleCount = 0;
	
	int useCount = 0;
	
	int planeId = 1;
	
	AirportQueue landingQ(1);
	AirportQueue takeoffQ(0);
	
	int needToLand(PoissonRandom(pVal));
	if(needToLand > 0)
	{
		for( int i = 0; i < needToLand; i++)
		{			
			landingQ.add(planeId);
			planeId++;
		}
	}
	
	int needToTakeoff(PoissonRandom(pVal));
	if(needToTakeoff > 0)
	{
		for( int i = 0; i < needToTakeoff; i++)
		{
			takeoffQ.add(planeId);
			planeId++;
		}
	}
	
	for( int i = 1; i < timeUnits+1; i++)
	{	
		cout << i << "\t";
		
		if (landingQ.remove())
		{
			useCount++;
		}
		else
		{
			
			if (takeoffQ.remove())
			{
				useCount++;
			}
			else
			{
				idleCount++;
				cout << "\tRunway is idle." << endl;
			}
		}

		landingQ.cycle();
		takeoffQ.cycle();
		
		
		
		
		int needToLand(PoissonRandom(pVal));
		if(needToLand > 0)
		{
			for( int j = 0; j < needToLand; j++)
			{
				landingQ.add(planeId);
				planeId++;
			}
		}
		
		int needToTakeoff(PoissonRandom(pVal));
		if(needToTakeoff > 0)
		{
			for( int j = 0; j < needToTakeoff; j++)
			{
				takeoffQ.add(planeId);
				planeId++;
			}
		}
		
		

	}
	
	cout << "SUMMARY:" << endl;
	cout << "\tSimulation has concluded after " << timeUnits << " time units.\n";
	cout << "\tTotal number of planes processed: \t\t" << (planeId - 1) << "\n";
	cout << "\t\tNumber of planes landed: \t\t" << landingQ.totalSuccess << endl;
	cout << "\t\tNumber of planes taken off: \t\t" << takeoffQ.totalSuccess << endl;
	cout << "\t\tNumber of planes refused use: \t\t" << (landingQ.totalRefused + takeoffQ.totalRefused) << endl;
	cout << "\t\tNumber left ready to land: \t\t" << landingQ.inQueue << endl;
	cout << "\t\tNumber left ready to take off: \t\t" << takeoffQ.inQueue << endl;
	cout << "\t\tNumber crashed: \t\t\t" << landingQ.totalFail << endl;
	cout << "\t\tPercentage of time runway was idle: \t" << (float)idleCount/(float)timeUnits << endl;
	cout << "\t\tAverage wait time to land: \t\t" << (float)landingQ.totalWaitTime/(float)timeUnits << endl;
	cout << "\t\tAverage wait time to take off: \t\t" << (float)takeoffQ.totalWaitTime/(float)timeUnits << endl;
	
	
	return 0;
}

int PoissonRandom( double expectedValue)
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
