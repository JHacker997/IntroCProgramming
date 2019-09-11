/*
John Hacker
9/19/16
COP 3223, Section 203
Homework #3

When given an integer, this program can find all the integers that can be evenly divded by it to get another integer and displays them.
*/

#include <stdio.h>

int main(void){

//declare all variables
int divisor = 0;

//Ask and scan for the divisor until a valid one is given
do {
printf("Please enter a number between 1 and 100:\n");
scanf("%d", &divisor);
} while (divisor < 1 || divisor > 100);

//Find aand display all the numbers divisible by the divisor and print ... for all the rest
printf("Below are all numbers between 1 and 100 that are divisible by %d\n", divisor);
for(int c = 1; c <= 100; c++){

if (c % divisor == 0)
printf(" %3d ", c);
else
printf(" ... ");
//skip to next line every ten numbers checked
if (c % 10 == 0)
printf("\n");

}

return 0;
}