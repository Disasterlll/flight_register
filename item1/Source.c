#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "SeatAssigned.h"


void choose2(int plane) {
	int result = 1;
	char firstName[FirstNamelength];
	char lastName[LastNamelength];
	for (;;)
	{
		PrintMenu();
		char choose2;

		choose2 = getchar();
		getchar();
		switch (choose2)
		{
		case 'a':
			printf("Number of empty seats: %d\n", GetNumOfEmptySeats(plane));
			printf("\n");
			break;
		case 'b':
			PrintEmptySeat(plane);
			printf("\n");
			break;
		case 'c':
		{
			SeatInfo arr[Totalflight][Totalseats];
			int count = GetSeatTable(plane, arr);
			for (int i = 0; i < count; i++)
			{
				char str[100];
				sprintf(str, "Name:%s %s   SeatID:%s",
					arr[plane][i].firstName,
					arr[plane][i].lastName,
					arr[plane][i].seatID);
				printf("%s\n", str);
			}
			printf("\n");
			break;
		}
		case 'd':
			if (GetNumOfEmptySeats(plane) != 0)
			{
				PrintEmptySeat(plane);//Print the number of the empty position of the flight
				printf("Please choose a seat from empty seats(enter q to abandon):");
				char id[50];
				while (1)
				{
					scanf("%s", id);
					getchar();
					if (strcmp(id, "q") == 0)
					{
						printf("\n");
						break;
					}
					int ret = SeatIsEmpty(plane, id);
					if (ret == 1)
					{
						char firstName[FirstNamelength];
						char lastName[LastNamelength];
						printf("Please enter FirstName:");
						scanf("%s", firstName);
						getchar();
						printf("Please enter LastName:");
						scanf("%s", lastName);
						getchar();
						if (AssignOneSeat(plane, id, firstName, lastName) == 1)
						{
							printf("Assign success!\n\n");
							break;
						}
					}
					else if (ret == 0)
					{
						printf("The seat you entered has already been assigned, please select a new seat (enter q to abandon):");
					}
					else
					{
						printf("The seat you entered does not exist, please re-enter a seat (enter q to abandon):");
					}
				}
			}
			else
			{
				printf("All the seat have assigned,there are no seat to be assigned!");
			}
			break;
		case 'e':
		{
			printf("Please input a seat ID(enter q to abandon):");
			char id[IDlength];
			scanf("%s", id);
			getchar();
			if (strcmp(id, "q") == 0)
			{
				printf("/n");
			}
			int ret = DelOneSeat(plane, id);
			if (ret == 1)
			{
				char str[100];
				sprintf(str, "Seat %s have been Delete", id);
				printf("%s\n\n", str);
			}
			else
			{
				char str[100];
				sprintf(str, "Seat %s is no exist", id);
				printf("%s\n\n", str);
			}
			break;
		}
		case 'f':
			printf("Please enter FirstName:");
			scanf("%s", firstName);
			getchar();
			printf("Please enter LastName:");
			scanf("%s", lastName);
			getchar();
			find(firstName, lastName);
			break;
		case 'g':
			result = 0;
			break;
		default:
			printf("no this option\n\n");
			break;
		}
		if (result == 0) { break; }
	}
}
void main(void)
{
	char choose1;
	int result = 1;
	InitSeatTable();//initial 

	for (;;)
	{
		ChoiceAnAirLine();
		choose1 = getchar();
		getchar();
		switch (choose1)
		{
		case '1':
			printf("thanks your pick  Flights 102\n\n Flights 102:\n");
			choose2(0);//102 Flight Information
			break;
		case '2':
			printf("thanks your pick  Flights 311\n\n Flights 311:\n");
			choose2(1);//311 Flight Information
			break;
		case '3':
			printf("thanks your pick  Flights 444\n\n Flights 444:\n");
			choose2(2);//444 Flight Information
			break;
		case '4':
			printf("thanks your pick  Flights 519\n\n Flights 519:\n");
			choose2(3);//519 Flight Information
			break;
		case '5':
			printf("You exiting!\n");
			WriteToFile();
			result = 0;
			break;
		default:
			printf("No this Flights, try again\n");
			break;
		}
		if (result == 0) { break; }
	}
}