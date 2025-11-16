#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <math.h>

#define byte03 8 
#define byte02 9 
#define byte01 7
#define byte00 0

#define byte13 2
#define byte12 3
#define byte11 12
#define byte10 13

#define output0Middle 14
#define output0TopLeft 30
#define output0Top 21
#define output0TopRight 22
#define output0BottomLeft 23
#define output0Bottom 24
#define output0BottomRight 25
#define output0DecimalPoint 15

#define PI 3.14159

void DrawOne(int* array)
{
	digitalWrite(array[3], HIGH);
	digitalWrite(array[6], HIGH);
}

void DrawTwo(int* array)
{
	digitalWrite(array[0], HIGH);
	digitalWrite(array[2], HIGH);
	digitalWrite(array[3], HIGH);
	digitalWrite(array[4], HIGH);
	digitalWrite(array[5], HIGH);
}

void DrawThree(int* array)
{
	DrawOne(array);
	digitalWrite(array[0], HIGH);
	digitalWrite(array[2], HIGH);
	digitalWrite(array[5], HIGH);
}

void DrawFour(int* array)
{
	DrawOne(array);	
	digitalWrite(array[0], HIGH);
	digitalWrite(array[1], HIGH);
}

void DrawFive(int* array)
{
	digitalWrite(array[0], HIGH);
	digitalWrite(array[1], HIGH);
	digitalWrite(array[2], HIGH);
	digitalWrite(array[5], HIGH);
	digitalWrite(array[6], HIGH);
}

void Clear(int* array)
{
	for(int i = 0; i < 7; i++)
	{
		digitalWrite(array[i], LOW);
	}
}

void DrawNumber(int number, int* array)
{
	switch(number)
	{
	case 1:
		DrawOne(array);
		break;
	case 2:
		DrawTwo(array);
		break;
	case 3:
		DrawThree(array);
		break;
	case 4:
		DrawFour(array);
		break;
	case 5:
		DrawFive(array);
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	}
}

int main()
{
    if (wiringPiSetup () == -1)
    {
        fprintf (stderr, "[ERROR] Could not initialize wiringPi library!\n");
        exit (1);
    }

    pinMode(byte00, INPUT);
    pinMode(byte01, INPUT);
    pinMode(byte02, INPUT);
    pinMode(byte03, INPUT);
    pinMode(byte10, INPUT);
    pinMode(byte11, INPUT);
    pinMode(byte12, INPUT);
    pinMode(byte13, INPUT);
    pullUpDnControl(byte00, PUD_DOWN);
    pullUpDnControl(byte01, PUD_DOWN);
    pullUpDnControl(byte02, PUD_DOWN);
    pullUpDnControl(byte03, PUD_DOWN);
    pullUpDnControl(byte10, PUD_DOWN);
    pullUpDnControl(byte11, PUD_DOWN);
    pullUpDnControl(byte12, PUD_DOWN);
    pullUpDnControl(byte13, PUD_DOWN);
    pinMode(output0Middle, OUTPUT);
    pinMode(output0TopLeft, OUTPUT);
    pinMode(output0Top, OUTPUT);
    pinMode(output0TopRight, OUTPUT);
    pinMode(output0BottomLeft, OUTPUT);
    pinMode(output0Bottom, OUTPUT);
    pinMode(output0BottomRight, OUTPUT);
    pinMode(output0DecimalPoint, OUTPUT);
    
    int hi[8] =
    {
   	output0Middle,
	output0TopLeft,
	output0Top,
	output0TopRight,
	output0BottomLeft,
	output0Bottom,
	output0BottomRight,
	output0DecimalPoint	
    };
    
    while(1)
    {
	    for(int i = 0; i < 6; i++)
	    {
	    	Clear(&hi[0]);
	    	DrawNumber(i, &(hi[0]));
		delay(500);
	    }
    }

    return (0);
}
