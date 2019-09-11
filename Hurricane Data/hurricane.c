/*
John Hacker
10/15/16
COP 3223, Section 203
Homework #4

Input a text file with hurricane data points for the purpose of summarizing the tracking data for hurricanes that happened in 2016.
Finds the start and final date, average and maximum wind speed, and maximum category of the hurricane.
*/

#include <stdio.h>

//Declare constant YEAR
#define YEAR 2016

//Declare functions
void read_data(FILE *ifp);
int get_category(double windSpeed);
void print_month(int month);
void print_summary(int sMonth, int sDay, int fMonth, int fDay, double avgWind, int maxWind, int category);

int main(void){

//Declare variables
FILE *ifp;

//Open a link to  an input file called input.txt which contains the tracking data for a single storm
ifp = fopen("input.txt", "r");

//Call the function read_data() that reads the data from the input.txt and prints out a summary of the storm data
read_data(ifp);

//Close the link tothe input file
fclose(ifp);

return 0;
}


//Function that takes in a file pointer and returns nothing
/*
Reads input.txt and saves start and final month and day
Calculates the average wind speed
Calls functions to save the max category and print the summary data
*/
void read_data(FILE *ifp){

//Declare variables
int totalPoints;
int month;
int sMonth;
int fMonth;
int day;
int sDay;
int fDay;
double avgSpeed;
int maxSpeed = 0;
double currentSpeed;
double totalSpeed = 0;
int maxCategory;
int c;

//Read data from the input file, saving the maximum wind speed and the start and final month and day

//Find the total amount of data points collected
fscanf(ifp, "%d", &totalPoints);

//Loop through to read each data point separately
for (c = 1; c <= totalPoints; c++){

//Read in month, day, and speed of a data point
fscanf(ifp, "%d %d %lf", &month, &day, &currentSpeed);

//Save start month and day
if (c == 1){
sMonth = month;
sDay = day;
}

//Save final month and day
if (c == totalPoints){
fMonth = month;
fDay = day;
}

//Save maximum wind speed
if (currentSpeed >= maxSpeed)
maxSpeed = currentSpeed;

//Add up all the speeds together fo use of calculating average wind speed
totalSpeed += currentSpeed;
}

//Calculate the average wind speed over all data points
avgSpeed = totalSpeed/totalPoints;

//Call function get_category() to get the maximum category achieved by the storm
maxCategory = get_category(maxSpeed);

//Call function print_summary() to print out the summary data
print_summary(sMonth, sDay, fMonth, fDay, avgSpeed, maxSpeed, maxCategory);
}


//Function that takes in floating point wind speed and returns an integer maximum category
//Finds the appropriate hurricane category based on the wind speed
int get_category(double windSpeed){

//Declare variable
int category = 0;

//Find what hurricane category the wind speed correlates with
if (windSpeed > 135)
category = 5;
else if (windSpeed >= 113)
category = 4;
else if (windSpeed >= 96)
category = 3;
else if (windSpeed >= 83)
category = 2;
else if (windSpeed >= 64)
category = 1;
else
category = 0;

//Return the maximum category of the given storm
return category;
}


//Function that takes in an integer month and returns nothing
//Print the name of the month the hurricane took place in
void print_month(int month){

//If statements to find the name of the month based on the given integer
if (month == 1)
printf("January");
if (month == 2)
printf("February");
if (month == 3)
printf("March");
if (month == 4)
printf("April");
if (month == 5)
printf("May");
if (month == 6)
printf("June");
if (month == 7)
printf("July");
if (month == 8)
printf("August");
if (month == 9)
printf("September");
if (month == 10)
printf("October");
if (month == 11)
printf("November");
if (month == 12)
printf("December");
}


//Function that takes in six important integer--and one floating point--aspects of a hurricane and returns nothing
//Prints the start and final date, average and maximum wind speed, and maximum category of the hurricane
void print_summary(int sMonth, int sDay, int fMonth, int fDay, double avgWind, int maxWind, int category){

//Print statements and print_month() functions that execute the purpose of function
printf("Start day: ");
print_month(sMonth);
printf(" %d, %d\nFinal day: ", sDay, YEAR);
print_month(fMonth);
printf(" %d, %d\n", fDay, YEAR);
printf("Average wind speed: %6.2lf knots\n", avgWind);
printf("Maximum wind speed: %3d knots\n", maxWind);
printf("Maximum category: %d\n", category);
}