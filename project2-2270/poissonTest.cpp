#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

int PoissonRandom( double expectedValue );
double randZeroToOne();

int main(int argc, char** argv) {
	
	srand(time(NULL));
	
	int numToGenerate = 30;
	double pVal = .25;

//	for(int j = 0; j < 30; j++)
//	{
		float sum = 0;
		
		for(int i = 0; i < numToGenerate; i++){
			
			double val = PoissonRandom(pVal);
					
			//cout << i << ":\t" << string(val,'*' ) << "\t" << val << endl;
			
			sum = sum + val;
		}
		cout << endl << (double)(sum/numToGenerate)<< endl;
//	}

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
