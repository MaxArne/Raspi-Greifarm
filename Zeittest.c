#include <stdio.h>      // für printf
#include <wiringPi.h>   // für Pindefinition
#include <time.h>       /* für clock_gettime */
#include <sys/time.h>   // für gettimeofday()
#include <stdint.h>     /* für uint64 definition */
#include <stdlib.h>     /* für exit() definition */
#include <unistd.h>
//https://www.electronicshub.org/raspberry-pi-color-sensor-tutorial/
// Pin Belegung in BCM Nummern
// Zeitmessungen / Pulsebreite: http://ondrej1024.github.io/emond/
#define S0        // direct auf Vcc
#define S1        // direct auf Vcc
#define S2 23
#define S3 24
#define sensorOut 25
// Kalibrierungswerte für rot, blau, grün
long Calred = 0;
long Calblue = 0;
long Calgreen = 0;
long red = 0;

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
int i = 0;
long diff;     //für Nanosec
//Zeitmessung für Pulsweite
struct timespec startred, endred;

//Auslesen der Farben Tabelle
//S2 = Low + S3 = Low -> rot
//S2 = Low + S3 = High -> blau
//S2 = High + S3 = High -> grün

// Kalibrierung
printf("Weiß Kal. nach 5 sec\n");
delay(500);
printf("start\n");
fflush(stdout);
//Start der Kalibrierung
//rot lesen
digitalWrite(S2,LOW);
digitalWrite(S3,LOW);
    
while (i == 2)
{
    	
    //Puls Messung risingedge bis fallingedge ms Messung
    if (digitalRead (sensorOut) == 1 && i == 0)
    {
    clock_gettime( CLOCK_REALTIME, &startred);
    i = 1;
    }
    
    if (digitalRead (sensorOut) == 0 && i == 1)
    {
    clock_gettime( CLOCK_REALTIME, &endred);
    i = 2;
    }
}
Calred = (endred.tv_sec - startred.tv_sec) + (endred.tv_nsec - startred.tv_nsec);
printf("Rot = %lu \n", Calred);
    //Zähler zurücksetzen für den nächsten Loop
    i = 0;

digitalWrite(S2,LOW);
digitalWrite(S3,LOW);
    
while (i == 2)
{
    	
    //Puls Messung risingedge bis fallingedge ms Messung
    if (digitalRead (sensorOut) == 1 && i == 0)
    {
    clock_gettime( CLOCK_REALTIME, &startred);
    i = 1;
    }
    
    if (digitalRead (sensorOut) == 0 && i == 1)
    {
    clock_gettime( CLOCK_REALTIME, &endred);
    i = 2;
    }
}
red = (endred.tv_sec - startred.tv_sec) + (endred.tv_nsec - startred.tv_nsec);
printf("Rot = %lu \n", red);
red= red/Calred;
printf("Rot = %lu \n", red);
}
