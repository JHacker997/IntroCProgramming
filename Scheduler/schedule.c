/*
John Hacker
11/15/16
COP 3223, Section 203
Homework #6

Read in data on all TA office hour shifts, sort the data, then print out the information in a pre-specified format.
*/

//#include statements
#include <stdio.h>
#include <string.h>

//Declare structure
struct Shift
{
char name[100];
char day_of_week[100];
int start_hour;
int end_hour;
};

//Declare functions
/* Preconditions: array of structure "Shift" to store data
   Postconditions: number of shifts read in from data file
   Actions: Ask user for name of input file. Read the number
   of shifts, then read in the data for all
   of the shifts. Return the number of shifts. */
int read_data(struct Shift shift_data[]);

/* Preconditions: array of structure "Shift"
   integer value indicating number of shifts
   Postconditions: none - this function does not return anything.
   Actions: Sort the shifts by the TA's first name. */
void sort_data(struct Shift shift_data[], int num_shifts);

/* Preconditions: array of structure "Shift"
   integer value indicating number of shifts
   Postconditions: none - this function does not return anything.
   Actions: Print the sorted data in the format described below. */
void print_data(struct Shift shift[], int num_shifts);



int main(void){

//Declare all variables
struct Shift shifts[100];
int numShifts;

//Call function read_data() to read the data into the array of structures and find number of shifts
numShifts = read_data(shifts);

//Call function sort_data() to sort the data that you read in by the TA's first name
sort_data(shifts, numShifts);

//Call function print_data() to print out the sorted data in the format specified below
print_data(shifts, numShifts);

//Return zero just for giggles
return 0;
}



/* Preconditions: array of structure "Shift" to store data
   Postconditions: number of shifts read in from data file
   Actions: Ask user for name of input file. Read the number
   of shifts, then read in the data for all
   of the shifts. Return the number of shifts. */
int read_data(struct Shift shift_data[]){

//Declare all variables
FILE *ifp;
int numShifts;
int c;
char text[100];

//Ask for the name of the data file
printf("What is the name of your data file?\n");
scanf("%s", text);

//Open file
ifp = fopen(text, "r");

//Scan file for number of shifts
fscanf(ifp, "%d", &numShifts);

//Loop up to 100 times, for each TA
for (c = 0; c < numShifts; c++){

//save every aspect of the data file
fscanf(ifp, "%s %s %d %d", shift_data[c].name, shift_data[c].day_of_week, &shift_data[c].start_hour, &shift_data[c].end_hour);

}

//Close file
fclose(ifp);

//Return the number of shifts
return numShifts;
}



/* Preconditions: array of structure "Shift"
   integer value indicating number of shifts
   Postconditions: none - this function does not return anything.
   Actions: Sort the shifts by the TA's first name. */
void sort_data(struct Shift shift_data[], int num_shifts){ //do last

//Declare Variables
int c;
int i;
struct Shift temp;

//Bubble Sort: move the name that is last alphabetically to the end of the array--like a bubble rising from the water
for (c = 0; c < num_shifts - 1; c++){

for (i = 0; i < num_shifts - 1 - c; i++){

//Check if next name comes before the next name
if (strcmp(shift_data[i+1].name, shift_data[i].name) < 0){
//Swap the TAs
temp = shift_data[i+1];
shift_data[i+1] = shift_data[i];
shift_data[i] = temp;

}

}

} 

}



/* Preconditions: array of structure "Shift"
   integer value indicating number of shifts
   Postconditions: none - this function does not return anything.
   Actions: Print the sorted data in the format described below. */
void print_data(struct Shift shift[], int num_shifts){

//Declare counter
int c;

//Print title
printf("TA shifts\n==========================================\n");

//Print every TAs' shit data
for (c = 0; c < num_shifts; c++){

//Print name and shift day
printf("%7s  %9s  ", shift[c].name, shift[c].day_of_week);

//print start time
if (shift[c].start_hour > 12)
printf("%2d:00 pm  to ", shift[c].start_hour - 12);
else if (shift[c].start_hour == 12)
printf("12:00 pm  to ");
else if (shift[c].start_hour == 0)
printf("12:00 am  to ");
else
printf("%2d:00 am  to ", shift[c].start_hour);

//Print end time
if (shift[c].end_hour > 12)
printf("%2d:00 pm", shift[c].end_hour - 12);
else if (shift[c].end_hour == 12)
printf("12:00 pm");
else if (shift[c].end_hour == 0)
printf("12:00 am");
else
printf("%2d:00 am", shift[c].end_hour);

//New line
printf("\n");

}

}