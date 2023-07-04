#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
ok all right lesh go
uh
ohh ok i get it now
base three
0 is a pass
1 is a one side
2 is a two side
oh that makes so much sense

you need an odd number of shafts

so once you have the shape of your thing
you need to figure out things

so 










1  0  0  0  2  0  0  0  2  0  1  0  0  3
1  0  0  2  0  0  0  2  0  0  0  2  0  3

   1  2  3  4  5  6  7  8  9  10 11 12
1  x  x  x  x  x  x  x  x  x  x  x  x  1
0  2  4  6  8  10 12 14 16 18 20 22 24 26

12 digits in base 3. um that means 222 222 222 222 in base 3 is 531440 in base 10

*/


// v2 is four distances
// v3 is two distances (broken and bad)


int main(void)
{
	double a1;
	double b1;
	double a2;
	double b2;
	double score;
	
	double a1Record=2;
	double b1Record=4;
	double a2Record=1.752;
	double b2Record=6.248;
	double scoreRecord = 99;
	
	
	int a;
	double b;
	double distance;
	double overshoot;
	
	int aRecord=6;
	double bRecord=8;
	
	double reductionRatio;
	
	// ok here goes nested for loops deciding what the gaps will be
	
	for (a=2; a<17; a=a+2)
	{
		for (b=2; b<17; b=b+0.05)
		{
			distance = a+b;
			if (distance > 24.2)
			{
				// we have a valid configuration, start iterating
				// for the given gaps, determine the best setting
				for (a1=1;a1<a/2;a1=a1+0.05)
				{
					for (b1=1;b1<b/2;b1=b1+0.05)
					{
						// so we have gaps set, find our actual like gaps
						a2=a-a1;
						b2=b-b1;
			
						
						// find the reduction ratio
						reductionRatio = (a2*b2)/(a1*b1);
						
						// check for negatives and fail condition and interference
						if ((reductionRatio > 11.88001) && (reductionRatio < 11.95) && (a2<=8) && (b2<=8))
						{
							// win condition
							
							// find the score
							overshoot = fabs(26-distance);
							score = 0.2*(pow(a1,2) + pow(a2,2) + pow(b1,2) + pow(b2,2));
							score = score+4.5*overshoot*overshoot*overshoot;
							
							// check if you've beaten a record
							if (score < scoreRecord)
							{
								// new record
								a1Record = a1;
								a2Record = a2;
								b1Record = b1;
								b2Record = b2;
								scoreRecord = score;
								
								aRecord=a;
								bRecord=b;
							}
						}
					}
				}
			}
		}
		printf("%d ", a);
	}
	
	scoreRecord=scoreRecord+ 25*(1/pow(0.9,2));
	
	// done the loop, print the score
	printf("\noh yeah\n");
	printf("score is %f\n", scoreRecord);
	printf("%f %f %f %f\n", a1Record, a2Record, b1Record, b2Record);
	printf("a b are %d, %f", aRecord, bRecord);
	
	
	return 0;
}