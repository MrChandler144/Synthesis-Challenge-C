#include <stdio.h>

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


void turnNumberToBinary(int *numberIn, int *shaftArray)
{
	// so just set up an editing copy of numberIn
	int number = *numberIn;
	
	// set the first and last gears
	shaftArray[0]=1;
	shaftArray[13]=2;
	
	int spot = 12;
	// turn the number into binary
	printf("%d\n", number);
	while (number!=0)
	{
		shaftArray[spot] = number%2;
		number=number/2;
		spot=spot-1;
	}
	
	// print the array just to check it's correct
	int i;
	for (i=0; i<14; i++)
	{
		printf("%d ", shaftArray[i]);
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
		//printf("%d", sum);
	}
	printf("sum is %d\n\n", sum);
	
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
	int number=255;	// 63 becomes 64
	int shaftArray[14]={0};
	
	
	//while (number < 4095)						// 4095 is an invalid number
	//{
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
		
		printf("we are going ahead with number = %d and also\n", number);
		int i;
		for (i=0; i<14; i++)
		{
			printf("%d ", shaftArray[i]);
		}
		printf("\n");
		
		// HENCE we have done this:
		// start by figuring out what your number is - 0 to 4095
		// turn it into binary
		// is it valid number? if no, go to next number and start again			0  2  4  6  8  10 12 14 16 18 20 22 24 26
		// write the relevant holes to an array for future use, something like [1  0  0  1  0  1  0  0  0  0  0  1  0  2]
		//																		1  2  3  4  5  6  7  8  9  10 11 12 13 14
		
		// now for the below!




		// then set up a for loop to go through all the possible answers
			// so the thing that changes in the for loop is the radius of the starting gear
		double firstRadius;
		for (firstRadius=0.5; firstRadius<2.5; firstRadius=firstRadius+0.01)
		{
			// just real quick set the last gear radius
			double lastRadius=firstRadius*8;
		
			// we then figure out where the next gear is being placed (refer to the array of shafts we've made)
			// we need to figure out if the next gear is another middle one (a 1 in the array) or the last one (we'll tack on a two at the end of the array)
			
			int shaftNumber = 1; //zero indexing, skipping the first one though
			int distanceOfShaft;
			int numberOfShafts = 1;
			double cumulativeDistance = firstRadius;
			double newRadius;
			
			printf("made it to line 141\n");
			
			// so go through and add gears until we hit that 2
			while(shaftNumber < 13)
			{
				// so go through and fund the next shaft
				while (shaftArray[shaftNumber]==0)
				{
					shaftNumber++;
				}
				// shaftNumber now points to a non-zero array
				// now we know the index of the next shaft, figure out how far along it is and add one to the shaft counter
				distanceOfShaft=shaftNumber*2;
				numberOfShafts++;
				
				// if it is a middle one:
					// if it is covered by an existing gear we quit this model and move onto the next radius of first gear
					// otherwise we figure out the radius of the next gear to make it work
				// if it is the end one:
					// add the final radius, and figure out where the final gear ends up relative to 26cm
					// at this point we have a fully fleshed out concept
					// figure out its score, add one to the tally of valid concepts, and move onto the next one
				
				printf("line 164\n");
				
				if (shaftNumber != 13)
				{
					// it's a middle/normal one
					if (cumulativeDistance > distanceOfShaft)
					{
						// this is an immediate fail condition for the entire for loop
					} else {
						// this is a valid gear
						// figure out how wide it has to be
						newRadius = distanceOfShaft - cumulativeDistance;
						// the radius has to be within certain limits, otherwise an immediate fail condition
						if ((newRadius <0.5) || (newRadius > 2.5))
						{
							// immediate fail condition
						}
						
						cumulativeDistance=cumulativeDistance+2*newRadius;
					}
					
				} else {
					// we've hit the end
					printf("we've hot the end, the array number is %d", shaftArray[shaftNumber]);
					cumulativeDistance=cumulativeDistance+lastRadius;
				}
				
				printf("line 191, shaftNumber is %d\n", shaftNumber);
			}
			printf("\n and there were %d shafts", numberOfShafts);
		}
		
		
		
		
		
		
		
			
			
			// when we have gone through the entire for loop, uh, add one to the number, recalculate the shafts and do it all again

			// nice
			
		number++;
		
		
	//}
}