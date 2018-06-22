#include <stdio.h>      // für printf
#include <wiringPi.h>   // für Pindefinition
#include <time.h>       /* für clock_gettime */
#include <stdint.h>     /* für uint64 definition */
#include <stdlib.h>     /* für exit() definition */
//https://www.electronicshub.org/raspberry-pi-color-sensor-tutorial/
// Pin Belegung in BCM Nummern
// Zeitmessungen / Pulsebreite: http://ondrej1024.github.io/emond/
#define S0        // direct auf Vcc
#define S1        // direct auf Vcc
#define S2 23
#define S3 24
#define sensorOut 25

/*
int setup(char x0, char y1)
{
wiringPiSetup () ;
if (wiringPiSetup() == -1)
    return 1;
//Pins als Outputs/Inputs initialiesieren
// pinMode (S0, Output);
// pinMode (S1, Output);
pinMode (S2, Output);
pinMode (S3, Output);
pinMode (sensorOut, Input);

//frequency scalling to 2%, 20%, 100% / mit x und y ausgewählen nach Tabelle:
// x = Low + y = High -> 2%
// x = High + y = Low -> 20%
// x = High + y = High -> 100%

//digitalWrite(S0,x);
//delay (500);
//digitalWrite(S1,y);
//delay (500);
}
*/

int main(void)
{
if (wiringPiSetup() == -1)
    return 1;
pinMode (S2, Output);
pinMode (S3, Output);
pinMode (sensorOut, Input);

int redloop = 0;
int blueloop = 0;
int greenloop = 0;
//setup (High,Low);		//Werte für x und y festlegen um scalling einzustellen
//Auslesen der Farben Tabelle
//S2 = Low + S3 = Low -> rot
//S2 = Low + S3 = High -> blau
//S2 = High + S3 = High -> grün

//rot lesen
digitalWrite(S2,LOW);
digitalWrite(S3,LOW);
// roter Sensor bleibt für mindestens 500ms aktiv
while (redloop < 50 || i=2)
{
    	uint64_t diff;
	struct timespec start, end;
	int i = 0;
    //Puls Messung risingedge bis fallingedge ms Messung
    if (digitalRead (sensorOut) == 1 && i == 0)
    {
    clock_gettime(CLOCK_MONOTONIC, &start);
    i = 1;
    }
    
    if (digitalRead (sensorOut) == 0 && i == 1)
    {
    clock_gettime(CLOCK_MONOTONIC, &end);
    i = 2;
    }
    redloop = redloop +1;
    // wartet 10 ms um mit 50 Durchläufen ca. 500ms nach rot zu prüfen
    delay(10);
}
    // Printing the value on the serial monitor
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	printf("Rot = %llu \n", (long long unsigned int) diff);
    exit(0);
    }
}
