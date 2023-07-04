#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
ok so there are 14 dots
you will always have one in the first and last slot
so that leaves 12 dots that could be on or off
111 111 111 111 base 2 is 4095 different configuratons
can you guarantee that some will not be good?
like what if part of it is just adding a gear to extend it out w/o doing reduction ratio stuff

what do we control?
- which shafts
- which sides of the shafts
- how big the gears on the shafts are
- tolerances (ew)

at every shaft you have the choice to send it through to the other side or not
if you don't then the radius is set for the next gear
if you do send it through then you have to choose a diameter for the other side as well, which is very different


when I actually run it, I want it to start the first one at 0.5cm and then increase up to 20/8 = 2.5cm, and increasing in steps of 0.01
then you can do the maths to figure it out
if it ever goes over the next spot, drop that particular run and move on to the next one



*/


void turnNumberToBinary(int *numberIn, int *shaftArray)
{
	// so just set up an editing copy of numberIn
	int number = *numberIn;
	
	// set the first and last gears
	shaftArray[0]=1;
	shaftArray[13]=2;
	
	int spot = 12;
	// turn the number into binary
	// printf("the number under consideration is %d\n", number);*/
	while (number!=0)
	{
		shaftArray[spot] = number%2;
		number=number/2;
		spot=spot-1;
	}
	
	// print the array just to check it's correct
	/*int i;
	for (i=0; i<14; i++)
	{
		printf("%d ", shaftArray[i]);
	}
	printf("/n");*/
}

int checkValid(int *shaftArray)
{
	
	// check it's a valid number
	int sum=0;
	int i;
	for (i=1; i<13; i++)
	{
		sum=sum+shaftArray[i];
		//printf("%d", sum);
	}
	// printf("sum is %d\n\n", sum);
	
	// valid setups have an odd sum
	// so if the sum is even, this is invalid and we need to try again
	if (sum%2 == 0)
	{
		// this number sucks
		return 0;
	} else {
		return 1;
	}
}



int main(void)
{
	int number=0;	// 63 becomes 64
	int shaftArray[14]={0};

	double recordScore = 9999;
	double recordRadii[20]={0};
	int recordShaftArray[14]={0};
	int recordNumber=0;
	double recordFirstRadius=0;
	int recordNumberOfShafts=0;
	double recordCumulativeDistance=0;
	
	int i;
	
	
	while (number < 4095)						// 4095 is an invalid number
	{
		int isNumberGood = 0;	// false
		// the main loop:
		
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
		
		/* printf("we are going ahead with number = %d and also this is what the shaft array looks like\n", number);
		for (i=0; i<14; i++)
		{
			printf("%d ", shaftArray[i]);
		}
		printf("\n");
		*/
		
		// HENCE we have done this:
		// start by figuring out what your number is - 0 to 4095
		// turn it into binary
		// is it valid number? if no, go to next number and start again			0  2  4  6  8  10 12 14 16 18 20 22 24 26
		// write the relevant holes to an array for future use, something like [1  0  0  1  0  1  0  0  0  0  0  1  0  2]
		//																		1  2  3  4  5  6  7  8  9  10 11 12 13 14
		
		// now for the below!


		// set up some things for later
		int distanceOfShaft;
		double cumulativeDistance;
		double newRadius;
		int numberOfShafts;
		double radii[20] = {0};
		double score;

		// then set up a for loop to go through all the possible answers
			// so the thing that changes in the for loop is the radius of the starting gear
		double firstRadius;
		for (firstRadius=0.5; firstRadius<=2.5; firstRadius=firstRadius+0.000001)
		{
			// just real quick set the last gear radius
			double lastRadius=firstRadius*8;
		
			// we then figure out where the next gear is being placed (refer to the array of shafts we've made)
			// we need to figure out if the next gear is another middle one (a 1 in the array) or the last one (we'll tack on a two at the end of the array)
			
			//int shaftNumber = 1; //zero indexing, skipping the first one though
			numberOfShafts = 1;
			// radii[20] = {0};
			// index 13 is 2
			
			
			cumulativeDistance=firstRadius;
			radii[0]=firstRadius;
			
			
			int j;
			for (j=1; j<13; j++)
			{
				// we cycle through every shaft for a given starting radius
				if (shaftArray[j] != 0)
				{
					// we found one
					numberOfShafts++;
					// printf("j is %d, number of shafts found is now %d\n", j, numberOfShafts); prints "j is 4, numShafts is 2"
					
					// figure out how far in it is
					distanceOfShaft=j*2;
					
					// compare to existing frontier to see if covered
					if (distanceOfShaft <= cumulativeDistance)
					{
						// covered, fail condition
					} else {
						// a valid shaft
						// find the new radius
						newRadius = distanceOfShaft - cumulativeDistance;
						
						// update new cumulative distance
						cumulativeDistance = cumulativeDistance + 2*newRadius;
						
						// add radius to list
						radii[numberOfShafts-1] = newRadius;
						
						// that's all we need to do
					}
				}
			}
			
			// we've  gone through an entire shaft for one initial radius on one number.
			// now we handle the last gear
			radii[numberOfShafts] = lastRadius;
			cumulativeDistance = cumulativeDistance + lastRadius;
			numberOfShafts++;
			
			// that's all the gears in the shaft accounted for, now to just check we got every thing right
			
			// now we can calculate the score for this round
			// quickly find r^2
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
				for (i=0; i<14; i++)
				{
					recordShaftArray[i] = shaftArray[i];
				}
				recordFirstRadius = firstRadius;
				recordNumberOfShafts = numberOfShafts;
				recordCumulativeDistance = cumulativeDistance;
			}
		}
		printf("%d ", number);
		
		// every so often give a status update on how the record is going
		if (number%512 == 0)	// only hits sometimes lol
		{
			
				// this is where the record printing is going now
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
		}
		number++;
	}
	
	// at this point we have gone through all the possible variations
	printf("\n\nDONE\n\n");
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
	printf("\na list of the shafts:\n");
	for (i=0; i<14; i++)
	{
		printf("%d ", recordShaftArray[i]);
	}
	printf("\n\n\n");
}