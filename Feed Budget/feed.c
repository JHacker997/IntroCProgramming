/*
John Hacker
10/29/16
COP 3223, Section 203
Homework #5

Read a txt file to find out how much food each horse of the Mounted Unit needs to eat each week and calculates the amount of bags needed to buy every week for food.
*/

//inclusion statements
#include <stdio.h>
#include <string.h>
#include <math.h>

//Define constant for number of HORSES
#define HORSES 12
//Define constant for LONGEST_NAME of any horse
#define LONGEST_NAME 8
//Define constant for amount of days in WEEK
#define WEEK 7

//Declare function
void readPlan(FILE *ifp);

int main(void){

//Declare variables
FILE *ifp;
char name[HORSES][LONGEST_NAME];
double breakfast[HORSES];
double dinner[HORSES];
int c;
char horse[LONGEST_NAME];
double weight;
double totalWeight = 0;
double bags1;
int bags;

//print intro-sentence
printf("Amount of grain per horse each week:\n");

//Open a link to  an input file called input.txt which contains the feed plans for each horse
ifp = fopen("input.txt", "r");

//Loop through to read each feeding plan separately
for (c = 0; c < HORSES; c++){

//put an end-character at end of each Stringin array
name[c][LONGEST_NAME] = '\0';

//scan file for name of horse
fscanf(ifp, "%s", horse);

//copy string in name array
strcpy(name[c], horse);

//scan from file the amount of scoops needed for breakfast and dinner
fscanf(ifp, "%lf %lf", &breakfast[c], &dinner[c]);

//calculate the amount of pounds the horse needs to eat
weight = (breakfast[c] + dinner[c]) * 3.5 * WEEK;

//print the name and pounds of food planned to eat for this horse
printf("%8s %7.2lf pounds\n", name[c], weight);

//add to total weight of food needed
totalWeight += weight;

}

//calculate the amount of bags required to buy for the week, rounding up everytime
bags = totalWeight / 50;
bags1 = totalWeight / 50;
if (bags1 != bags)
bags++;

//print the amout of pounds of food tobe eaten total
printf("Total grain required each week: %6.2lf pounds\n", totalWeight);

//print amount of bags of grain required to buy
printf("Total grain to purchase each week: %d bags\n", bags);

//Close the link tothe input file
fclose(ifp);

return 0;
}