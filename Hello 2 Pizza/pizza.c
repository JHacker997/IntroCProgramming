/*
John Hacker
9/4/2016
COP 3223, Section 203
Homework 1, Program B

Calculates the amount of money spent on pizza delivery
*/

#include <stdio.h>
#define SALES_TAX 0.065;

int main(void) {

//declare variables
int numberLargePizzas = 0;
int numberMediumPizzas = 0;
double totalCost = 0;

//ask for amount of large pizzas
printf("\nWelcome to Johnny's Pizzeria!\nHow many large pizzas would you like to order\n");

//read amount of large pizzas
scanf("%d", &numberLargePizzas);

//ask for amount of medium pizzas
printf("How many medium pizzas would you like to order?\n");

//read amount of medium pizzas
scanf("%d", &numberMediumPizzas);

//caluclate the total cost
totalCost += numberLargePizzas*10.0;
totalCost += numberMediumPizzas*7.5;
totalCost += totalCost*SALES_TAX;

//print the pizzas that were ordered
printf("You ordered %d large pizza(s) and %d medium pizza(s).\n", numberLargePizzas, numberMediumPizzas);

//print the total cost
printf("Your total cost is $%3.2lf\nThank you!\n\n", totalCost);

return 0;
}
