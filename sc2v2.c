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



int main(void)
{
	double a1;
	double b1;
	double c1;
	double d1;
	double a2;
	double b2;
	double c2;
	double d2;
	double score;
	
	double a1Record=2;
	double b1Record=4;
	double c1Record=3;
	double d1Record=5;
	double a2Record=1.752;
	double b2Record=6.248;
	double c2Record=2;
	double d2Record=2;
	double scoreRecord = 99;
	
	
	int a;
	int b;
	int c;
	double d;
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
				// set the last gap
				for (d=2; d<17; d=d+0.04)
				{
					distance = a+b+c+d;
					if ((distance < 27.6) && (distance > 24.4))
					{
						// we have a valid configuration, start iterating
						// for the given gaps, determine the best setting
						for (a1=1;a1<a/2;a1=a1+0.04)
						{
							for (b1=1;b1<b/2;b1=b1+0.04)
							{
								for (c1=1;c1<c/2;c1=c1+0.04)
								{
									for (d1=1;d1<d/2;d1=d1+0.04)
									{
										// so we have gaps set, find our actual like gaps
										a2=a-a1;
										b2=b-b1;
										c2=c-c1;
										d2=d-d1;
										
										// find the reduction ratio
										reductionRatio = (a2*b2*c2*d2)/(a1*b1*c1*d1);
										
										// check for negatives and fail condition and interference
										if (!((reductionRatio < 11.88001) || (reductionRatio > 12.12) || (a2+c1+0.01 >= b) || (b2+d1+0.01 >= c)))
										{
											// win condition
											
											// find the score
											overshoot = fabs(26-distance);
											score = 0.2*(pow(a1,2) + pow(a2,2) + pow(b1,2) + pow(b2,2) + pow(c1,2) + pow(c2,2) + pow(d1,2) + pow(d2,2));
											score = score+4.5*overshoot*overshoot*overshoot;
											
											// check if you've beaten a record
											if (score < scoreRecord)
											{
												// new record
												a1Record = a1;
												a2Record = a2;
												b1Record = b1;
												b2Record = b2;
												c1Record = c1;
												c2Record = c2;
												d1Record = d1;
												d2Record = d2;
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
			}
		}
		printf("%d ", a);
	}
	
	scoreRecord=scoreRecord+ 25*(1/pow(0.9,4));
	
	// done the loop, print the score
	printf("\noh yeah\n");
	printf("score is %f\n", scoreRecord);
	printf("%f %f %f %f %f %f %f %f \n", a1Record, a2Record, b1Record, b2Record, c1Record, c2Record, d1Record, d2Record);
	printf("a b c d are %d, %d, %d, %f\n", aRecord, bRecord, cRecord, dRecord);
	printf("distance is %f\n", a+b+c+d);
	
	return 0;
}