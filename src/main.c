#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <math.h>

#define clockOutput 8
#define load 7
#define RCLK 0 
#define input 9
#define SegOutput 2

#define CLOCK_DELAY 100

u_int8_t SevenSegmentEncoding[11] =
{
	0b01111110, //0
	0b00001000, //1
	0b11011010, //2
	0b11110010,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000
};

int main()
{
    if (wiringPiSetup () == -1)
    {
        fprintf (stderr, "[ERROR] Could not initialize wiringPi library!\n");
        exit (1);
    }

    pinMode(clockOutput, OUTPUT);
    pinMode(load, OUTPUT);
    pinMode(RCLK, OUTPUT);
    pinMode(SegOutput, OUTPUT);

    pinMode(input, INPUT);
    pullUpDnControl(input, PUD_DOWN);

    unsigned long lastHalfClock = millis();
    int clockState = LOW;
    int iterations = -1;
    int segmentIteration = 0;

    void OnHigh()
    {
	if(iterations == 0)
	{
		digitalWrite(load, HIGH);
		digitalWrite(RCLK, LOW);
		printf("\n");
	}
	
	int bit = digitalRead(input);
	printf("%d", bit);
	fflush(stdout);
    }

    void OnLow()
    {
	if(iterations == 7)
	{
		//DELAY NEEDS TO GO IN THE FUTURE
		delay(5);
		digitalWrite(load, LOW);
		digitalWrite(RCLK, HIGH);
	}
	digitalWrite(SegOutput, (SevenSegmentEncoding[1] >> segmentIteration) & 0x01);
	segmentIteration++;
	if(segmentIteration == 8) segmentIteration = 0;
    }

    while(1)
    {
	
	unsigned long now = millis();
	if(now - lastHalfClock >= CLOCK_DELAY / 2)
	{
		lastHalfClock = now;
		clockState = !clockState;
		digitalWrite(clockOutput, clockState);

		if(clockState == LOW)
		{
			OnLow();
		}

		if(clockState == HIGH)
		{

			if(iterations % 7 == 0 && iterations != 0)
			{
				iterations = 0;
			}
			else
			{
				if(iterations == -1)
				{
					iterations = 0;
				}
				else
				{
					iterations++;
				}
			}
			OnHigh();
		}
	}
    }
    return (0);
}
