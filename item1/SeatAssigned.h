#pragma once
#define FILE_NAME "data.txt"
#define IDlength 15
#define FirstNamelength 25
#define LastNamelength 25
#define Totalflight 5
#define Totalseats 15
//refactor4 
//program to creat a menu for the passengers 
// Lux- pro71985 
//Professor Steve

typedef struct
{
	char seatID[IDlength];
	int isAssigned; 
	char firstName[FirstNamelength];
	char lastName[LastNamelength];
} SeatInfo;

SeatInfo seats[Totalflight][Totalseats];//Request an array of structs of size 48

void ChoiceAnAirLine();
void InitSeatTable();
void PrintMenu();
int GetNumOfEmptySeats(int plane);
void PrintEmptySeat(int plane);
int SeatIsEmpty(int plane, char* id);
int AssignOneSeat(int plane, char* id, char* firstName, char* lastName);
int DelOneSeat(int plane, char* id);
int GetSeatTable(int plane, SeatInfo** arr);
void WriteToFile();
void find(char* firstName, char* lastName);