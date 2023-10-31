#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include"SeatAssigned.h"
#define Totalflight 4
#define Totalseats 12
//refactor4 
//program to creat a menu for the passengers 
// Lux- pro71985 
//Professor Steve

void InitSeatTable()
{
	FILE* fp;
	fp = fopen(FILE_NAME, "r");//open file
	if (fp == NULL) //if fp == NULL，open is faile
	{
		char* seatNum[] =
		{
		"A1","A2","A3","B1","B2","B3",
		"C1","C2","C3","D1","D2","D3"
		};
		//initial
		for (int j = 0; j < Totalflight; j++)
		{
			for (int i = 0; i < Totalseats; i++)
			{
				strcpy(seats[j][i].seatID, seatNum[i]);
				seats[j][i].isAssigned = 0;
				strcpy(seats[j][i].firstName, "0");
				strcpy(seats[j][i].lastName, "0");
			}
		}
	}
	else
	{
		for (int j = 0; j < Totalflight; j++)
		{
			for (int i = 0; i < Totalseats; i++)
			{
				fscanf(fp, "%s %d %s %s\n",
					seats[j][i].seatID,
					&seats[j][i].isAssigned,
					seats[j][i].firstName,
					seats[j][i].lastName);
			}
		}
		fclose(fp);//close file
	}
}
//print top menu
void ChoiceAnAirLine()
{
	printf("1) Flights 102\n");
	printf("2) Flights 311\n");
	printf("3) Flights 444\n");
	printf("4) Flights 519\n");
	printf("5) Quit\n");
	printf("Please choose a Flights: ");
}
//print the sencond 
void PrintMenu()
{
	printf("a) Show number of empty seats\n");
	printf("b) Show list of empty seats\n");
	printf("c) Show alphabetical list of seats \n");
	printf("d) Assign a customer to a seat assignment\n");
	printf("e) Delete a seat assignment\n");
	printf("f) Confirming a seat assignment\n");
	printf("g) Back to top menu\n");
	printf("Please choose a operator: ");
}
//Get the number of empty seats on a flight
int GetNumOfEmptySeats(int plane)
{
	int empty = 0;
	for (int i = 0; i < Totalseats; i++)
	{
		if (!seats[plane][i].isAssigned)
		{
			empty++;
		}
	}
	return empty;
}
//Print the number of the empty seat
void PrintEmptySeat(int plane)
{
	if (!GetNumOfEmptySeats(plane))
	{
		printf("All the seat have assignged!\n");
		return;
	}
	printf("Empty Seats:");
	for (int i = 0; i < Totalseats; i++)
	{
		if (!seats[plane][i].isAssigned)
		{
			printf("%s, ", seats[plane][i].seatID);
		}
	}
	printf("\n");
}

/* Determines if a seat is unassigned.
* Return value.
* 0: means it has been assigned.
* 1: means not assigned
* 2: this seat number does not exist */
int SeatIsEmpty(int plane, char* id)
{
	for (int i = 0; i < Totalseats; i++)
	{
		if (strcmp(seats[plane][i].seatID, id) == 0) //if the seat ID entered by the user exists in the file.
		{
			if (seats[plane][i].isAssigned == 0)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	return 2;
}

/* assigning a seat to a passenger.
* Parameters.
* id: ID of the seat to be assigned
* firstName: the last name of the booker
* lastName: the first name of the booker
* Return value.
* 1: The seat was allocated successfully.
* -1: The seat has been assigned
* -2: allocation failed, seat number not found
* lastName
* Note: First, whether this seat is not assigned, if it is assigned, -1 is returned, then if the seat number entered does not exist, * then -2 is returned.

Translated with www.DeepL.com/Translator (free version)
*/
int AssignOneSeat(int plane, char* id, char* firstName, char* lastName)
{
	for (int i = 0; i < Totalseats; i++)
	{
		if (strcmp(seats[plane][i].seatID, id) == 0)
		{
			strcpy(seats[plane][i].firstName, firstName);
			strcpy(seats[plane][i].lastName, lastName);
			seats[plane][i].isAssigned = 1;
			return 1;
		}
	}
	return 0;
}

/*Deletes a seat assignment, i.e., makes the position empty
* Return value.
* 0: Deletion failed, seat number not found
* 1: Deleted successfully */
int DelOneSeat(int plane, char* id)
{
	for (int i = 0; i < Totalseats; i++)
	{
		if (strcmp(seats[plane][i].seatID, id) == 0)
		{
			strcpy(seats[plane][i].firstName, "0");
			strcpy(seats[plane][i].lastName, "0");
			seats[plane][i].isAssigned = 0;
			return 1;
		}
	}
	return 0;
}

/* Gets a list of assigned seats.
* Return value.
* 0: Failed to get, no seats have been assigned
* >0: the acquisition succeeds and returns the list length */
int GetSeatTable(int plane, SeatInfo arr[4][12])
{
	int j = 0;
	for (int i = 0; i < Totalseats; i++)
	{
		if (seats[plane][i].isAssigned)
		{
			arr[plane][j++] = seats[plane][i];
		}
	}
	
	for (int k = j; k > 0; k--)
	{
		for (int i = 0; i < k; i++)
		{
			if (strcmp(arr[plane][i].firstName, arr[plane][i + 1].firstName) > 0)
			{
				SeatInfo temp = arr[plane][i];
				arr[plane][i] = arr[plane][i + 1];
				arr[plane][i + 1] = temp;
			}
		}
	}
	return j;
}

//Create the date.txt file and store the data inside the structure into the file
void WriteToFile()
{
	FILE* fp;
	fp = fopen(FILE_NAME, "wt");
	for (int j = 0; j < Totalflight; j++)
	{
		for (int i = 0; i < Totalseats; i++)
		{
			fprintf(fp, "%s %d %s %s\n",
				seats[j][i].seatID,
				seats[j][i].isAssigned,
				seats[j][i].firstName,
				seats[j][i].lastName);
		}
	}
	fclose(fp);
}
void find(char* firstName, char* lastName)
{
	int index = 0;
	for (int plane = 0; plane < Totalflight; plane++)
	{
		for (int i = 0; i < Totalseats; i++)
		{
			if ((strcmp(seats[plane][i].firstName, firstName) == 0) && (strcmp(seats[plane][i].lastName, lastName) == 0))
			{
				if (plane == 0) { printf("You has reserved a seat: flight 102, seat：%s\n", seats[plane][i].seatID); }
				else if (plane == 1) { printf("You has reserved a seat: flight 311, seat：%s\n", seats[plane][i].seatID); }
				else if (plane == 2) { printf("You has reserved a seat: flight 444, seat：%s\n", seats[plane][i].seatID); }
				else if (plane == 3) { printf("You has reserved a seat: flight 519, seat：%s\n", seats[plane][i].seatID); }
				index = 1;
			}

		}
	}
	if (index == 0) {
		printf("没有找到相对应的乘客\n");
	}
}
