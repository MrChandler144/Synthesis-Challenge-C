#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
ok so there are 14 dots
you will always have one in the first and last slot
so that leaves 12 dots that could be on or off
111 111 111 111 base 2 is 4095 different configuratons
I can reuse some code probably from the cellular automata to convert a number to binary
and then I can immediately throw it out if it has an even number of ones, because it will rotate the wrong way
uh

"the one at the end is eight times bigger than the one at the start"
when I actually run it, I want it to start the first one at 0.5cm and then increase up to 20/8 = 2.5cm, and increasing in steps of 0.01
then you can do the maths to figure it out
if it ever goes over the next spot, drop that particular run and move on to the next one

I know what the last one will be, (eight times the starting one) so I can add that on at the end
and then I can run the calculation to get the score.

I want it to print out the best result every 500 runs, and again at the end (like a progress bar)

*/

// v1 was the intial attempt
// v2 happened when i got stuck so I made v2 with a new apporach to the actual maths
// v3 is scaling up for the final answer ahh!
// v4 is me being impatient and breaking 
// v5 is me cleaning it up so it looks presentable



void turnNumberToBinary(int *numberIn, int *shaftArray)
{
	// so just set up an editing copy of numberIn
	int number = *numberIn;
	
	// set the first and last gears
	shaftArray[0]=1;
	shaftArray[13]=2;
	
	int spot = 12;
	// turn the number into binary
	while (number!=0)
	{
		shaftArray[spot] = number%2;
		number=number/2;
		spot=spot-1;
	}
}

int checkValid(int *shaftArray)
{
	
	// check it's a valid number
	int sum=0;
	int i;
	for (i=1; i<13; i++)
	{
		sum=sum+shaftArray[i];
	}
	
	// valid setups have an odd sum
	// so if the sum is even, this is invalid and we need to try again
	if (sum%2 == 0)
	{
		// the final gear will turn the wrong way with the current configuration
		return 0;
	} else {
		return 1;
	}
}



int main(void)
{
	int number=0;
	int shaftArray[14]={0};

	double recordScore = 9999;
	double recordRadii[20]={0};
	int recordNumber=0;
	int recordNumberOfShafts=0;
	double recordFirstRadius=0;
	double recordCumulativeDistance=0;
	int distanceOfShaft, numberOfShafts;
	double cumulativeDistance, newRadius, score, firstRadius, lastRadius;
	
	int i, j;
		
	while (number < 4095)						// 4095 is an invalid number
	{
		int isNumberGood = 0;	// false
		
		// we can't go past this until it's a good number (the out wheel spins the same way as the in wheel)
		while (isNumberGood == 0)
		{
			//turn the number into binary
			turnNumberToBinary(&number, shaftArray);
			// check it's a valid number
			isNumberGood = checkValid(shaftArray);
			// check there's a right amount of gears for spinning the same way
			if (isNumberGood == 0)
			{
				// this failed the check, make it try again
				number=number+1;
			}
		}
		
		// reset the radii matrix
		double radii[20] = {0};
		
		// then set up a for loop to go through all the possible first radii
		for (firstRadius=0.5; firstRadius<=2.5; firstRadius=firstRadius+0.0001)
		{
			// we know the radius of the last gear
			lastRadius=firstRadius*8;
			
			cumulativeDistance=firstRadius;
			radii[0]=firstRadius;
			numberOfShafts = 1;
			
			
			// we cycle through every shaft for a given starting radius, looking for shafts with gears
			for (j=1; j<13; j++)
			{
				if (shaftArray[j] != 0)
				{
					// we found one
					numberOfShafts++;
					
					// figure out how far in it is
					distanceOfShaft=j*2;
					
					// compare to existing frontier to see if covered
					if (distanceOfShaft <= cumulativeDistance)
					{
						// covered, fail condition
						radii[0]=999;
						// while not technically a fail condition, this will make the score so large it is never considered.
					} else {
						// a valid shaft
						// find the new radius
						newRadius = distanceOfShaft - cumulativeDistance;
						
						// update new cumulative distance
						cumulativeDistance = cumulativeDistance + 2*newRadius;
						
						// add radius to list
						radii[numberOfShafts-1] = newRadius;
					}
				}
			}
			
			// we've  gone through an entire shaft for one initial radius on one number.
			// now we handle the last gear
			radii[numberOfShafts] = lastRadius;
			cumulativeDistance = cumulativeDistance + lastRadius;
			numberOfShafts++;
			
			
			// now we can calculate the score for this round
			
			// find the r^2 component
			double rSquared = 0;
			for (i=0; i<17; i++)
			{
				rSquared = rSquared + radii[i]*radii[i];
			}
			double distance = 26-cumulativeDistance;
			double distance3 = distance*distance*distance;
			score = 7*numberOfShafts + 0.3*rSquared + 9 * fabs(distance3);
			
			// and finally, compare the score to the record
			if (score < recordScore)
			{
				// a new record
				// update the records
				recordScore = score;
				recordNumber=number;
				for (i=0; i<20; i++)
				{
					recordRadii[i] = radii[i];
				}
				recordFirstRadius = firstRadius;
				recordNumberOfShafts = numberOfShafts;
				recordCumulativeDistance = cumulativeDistance;
			}
		}
		
		printf("%d ", number);
		
		/* every so often give a status update on how the record is going
		if (number%512 == 0)	// only hits sometimes
		{
				printf("current record:\n");
				printf("\nthe score is %f\n", recordScore);
				printf("the number is %d\n", recordNumber);
				printf("firstRadius is %f\n", recordFirstRadius);
				printf("the number of shafts is %d\n", recordNumberOfShafts);
				printf("the cumulative distance is %f\n", recordCumulativeDistance);
				printf("a list of the radii:\n");
				for (i=0; i<17; i++)
				{
					printf("%f ", recordRadii[i]);
				}
				printf("\n\n\n");
		}*/
		
		number++;
	}
	
	// at this point we have gone through all the possible variations
	printf("\n\nDONE\n\n");
	printf("for the best configuration:\n");
	printf("the score is %f\n", recordScore);
	printf("the number is %d\n", recordNumber);
	printf("firstRadius is %f\n", recordFirstRadius);
	printf("the number of shafts is %d\n", recordNumberOfShafts);
	printf("the cumulative distance is %f\n", recordCumulativeDistance);
	printf("a list of the radii:\n");
	for (i=0; i<14; i++)
	{
		printf("%f ", recordRadii[i]);
	}
	printf("\n\n\n");
}