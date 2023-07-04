#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// v2 is four distances
// v3 is two distances (broken and bad)
// v4 is four distances and 7 gears: a1 a2, b1 b2, c1 c2 c3
// v5 is four distances and 7 gears: a1 a2, b1 b2 b3, c1 c2

// current best is 52.83


int main(void)
{
	double a1;
	double a2;
	double b1;
	double b2;
	double b3;
	double c1;
	double c2;
	double score;
	
	double a1Record=2;
	double a2Record=1.752;
	double b1Record=4;
	double b2Record=6.248;
	double b3Record=5;
	double c1Record=3;
	double c2Record=2;
	double scoreRecord = 99;
	
	
	int a;
	int b;
	int c;
	double d = 6.752;
	double distance;
	double overshoot;
	
	int aRecord=6;
	int bRecord=8;
	int cRecord=8;
	double dRecord=4;
	
	double reductionRatio;
	
	// ok here goes three nested for loops deciding what the gaps will be
	
	for (a=2; a<17; a=a+2)
	{
		for (b=2; b<17; b=b+2)
		{
			for (c=2; c<17; c=c+2)
			{
				// got our gaps
				for (a1=1;a1<a/2;a1=a1+0.05)
				{
					for (b1=1;b1<b/2;b1=b1+0.05)
					{
						for (c1=1;c1<c/2;c1=c1+0.05)
						{
							for (c2=1;c2<8;c2=c2+0.05)
							{
								// find the other gear dimensions
								a2=a-a1;
								b2=b-b1;
								b3=c-b2;
								d=c1+c2;
								distance = a+b+c+d;
								
								// find the reduction ratio
								reductionRatio = (a2*b3*c2)/(a1*b1*c1);
								
								// check for negatives and fail condition and interference
								if ((reductionRatio >= 11.88) && (reductionRatio <= 12.12) && (a2+c1+0.01 <= b+c) && (distance < 27) && (distance > 25))
								{
									// win condition
									
									// find the score
									overshoot = fabs(26-distance);
									score = 0.2*(pow(a1,2) + pow(a2,2) + pow(b1,2) + pow(b2,2) + pow(b3,2) + pow(c1,2) + pow(c2,2));
									score = score+4.5*overshoot*overshoot*overshoot;
									
									// check if you've beaten a record
									if (score < scoreRecord)
									{
										// new record
										a1Record = a1;
										a2Record = a2;
										b1Record = b1;
										b2Record = b2;
										b3Record = b3;
										c1Record = c1;
										c2Record = c2;
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
		}
		printf("%d ", a);
	}
	
	scoreRecord=scoreRecord+ 25*(1/pow(0.9,4));
	
	// done the loop, print the score
	printf("\noh yeah\n");
	printf("score is %f\n", scoreRecord);
	printf("%f %f %f %f %f %f %f \n", a1Record, a2Record, b1Record, b2Record, b3Record, c1Record, c2Record);
	printf("a b c d are %d, %d, %d, %f\n", aRecord, bRecord, cRecord, dRecord);
	printf("distance is %f\n", aRecord+bRecord+cRecord+dRecord);
	
	return 0;
}