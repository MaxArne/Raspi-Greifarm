//TCS3200 Farbsensor 
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

//frequency scalling to 2%, 20%, 100%
// S0 = Low + S1 = High -> 2%
// S0 = High + S1 = Low -> 20%
// S0 = High + S1 = High -> 100%

int main(void)
{
// OUTPUT / INPUT Definition
if (wiringPiSetup() == -1)
    return 1;
pinMode (S2, OUTPUT);
pinMode (S3, OUTPUT);
pinMode (sensorOut, INPUT);
// loop Variablen initialisieren
int redloop = 0;
int blueloop = 0;
int greenloop = 0;
int i = 0;
uint64_t diff = 1000000000;     //für Nanosec
struct timespec start, end;
//Auslesen der Farben Tabelle
//S2 = Low + S3 = Low -> rot
//S2 = Low + S3 = High -> blau
//S2 = High + S3 = High -> grün
    
while (1)
{

//rot lesen
digitalWrite(S2,LOW);
digitalWrite(S3,LOW);

while (/*redloop < 50 ||*/ i == 2)
{
    	
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
    //redloop = redloop +1;
    // wartet 1 ms
    delay(1);
}
    // Printing the value on the serial monitor
    diff = diff * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    printf("Rot = %llu \n", (long long unsigned int) diff);
    //Zähler zurücksetzen für den nächsten Loop
    i = 0;
    //redloop = 0;
    diff = 1000000000;
    
//blau lesen
digitalWrite(S2,LOW);
digitalWrite(S3,HIGH);
while (/*blueloop < 50 ||*/ i == 2)
{
    	
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
    //blueloop = blueloop +1;
    // wartet 1 ms
    delay(1);
}
    // Printing the value on the serial monitor
    diff = diff * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    printf("Blau = %llu \n", (long long unsigned int) diff);
    //Zähler zurücksetzen für den nächsten Loop
    i = 0;
    //blueloop = 0;
    diff = 1000000000;

//grün lesen
digitalWrite(S2,HIGH);
digitalWrite(S3,HIGH);
while (/*greenloop < 50 ||*/ i == 2)
{
    	
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
    //greenloop = greenloop +1;
    // wartet 1ms //um mit 50 Durchläufen ca. 500ms nach rot zu prüfen
    delay(1);
}
    // Printing the value on the serial monitor
    diff = diff * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    printf("Gruen = %llu \n", (long long unsigned int) diff);
    //Zähler zurücksetzen für den nächsten Loop
    i = 0;
    //greenloop = 0;
    diff = 1000000000;
}
    exit(0);
    
}
