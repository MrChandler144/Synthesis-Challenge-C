#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// v2 is four distances
// v3 is two distances (broken and bad)
// v4 is four distances and 7 gears: a1 a2, b1 b2, c1 c2 c3
// v5 is four distances and 7 gears: a1 a2, b1 b2 b3, c1 c2
// v6 is four distances and 7 gears: a1 a2 a3, b1 b2, c1 c2		52.83
// v7 is a general case for 5 gears: a1 a2 a3, b1 b2			53.21
// v8 is a general case for 5 gears: a1 a2, b1 b2 b3			53.11
// v9 is a general case for 6 gears: a1 a2 a3, b1 b2 b3			51.55 yo

// current best is 52.83


int main(void)
{
	int a,b,c;
	double d;
	double a1Record=0;
	double a2Record=0;
	double a3Record=0;
	double b1Record=0;
	double b2Record=0;
	double b3Record=0;
	int aRecord=0;
	int bRecord=0;
	int cRecord=0;
	double dRecord=0;
	double score=99;
	double scoreRecord = 52.84;
	double a1,a2,a3,b1,b2,b3;
	double distance, reductionRatio, overshoot;
	
	
	for (a=2; a<17; a=a+2)
	{
		for (b=2; b<17; b=b+2)
		{
			for (c=2; c<17; c=c+2)
			{
				for (a1=1; a1<8; a1=a1+0.02)
				{
					for (b1=1; b1<8; b1=b1+0.02)
					{
						for (b3=1; b3<8; b3=b3+0.02)
						{
							a2=a-a1;
							a3=b-a2;
							b2=c-b1;
							d=b2+b3;
							distance=a+b+c+d;
							reductionRatio = (a3*b3)/(a1*b1);
							
							if ((distance > 25) && (distance < 27) && (reductionRatio >= 11.88) && (reductionRatio <= 12.12))
							{
								// win condition
								
								// find the score
								overshoot = fabs(26-distance);
								score = 0.2*(pow(a1,2) + pow(a2,2) + pow(a3,2) + pow(b1,2) + pow(b2,2) + pow(b3,2));
								score = score+4.5*overshoot*overshoot*overshoot;
								
								// check if you've beaten a record
								if (score < scoreRecord)
								{
									// new record
									a1Record = a1;
									a2Record = a2;
									a3Record = a3;
									b1Record = b1;
									b2Record = b2;
									b3Record = b3;
									scoreRecord = score;
									
									aRecord=a;
									bRecord=b;
									cRecord=c;
									dRecord=d;
								}
							}
						}
					}
				}
			}
		}
		printf("%d ", a);
	}
	
	scoreRecord=scoreRecord+ 25*(1/pow(0.9,4));
	
	// done the loop, print the score
	printf("\noh yeah\n");
	printf("score is %f\n", scoreRecord);
	printf("%f %f %f %f %f %f \n", a1Record, a2Record, a3Record, b1Record, b2Record, b3Record);
	printf("a b c d are %d, %d, %d, %f\n", aRecord, bRecord, cRecord, dRecord);
	printf("distance is %f\n", aRecord+bRecord+cRecord+dRecord);
	
	return 0;
}