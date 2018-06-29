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
// Kalibrierungswerte für rot, blau, grün
uint64_t Calred = 0;
uint64_t Calblue = 0;
uint64_t Calgreen = 0;

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
uint64_t diff = 1000000000;     //für Nanosec
//Zeitmessung für Pulsweite
struct timespec startred, endred, startblue, endblue,startgreen, endgreen;

//Auslesen der Farben Tabelle
//S2 = Low + S3 = Low -> rot
//S2 = Low + S3 = High -> blau
//S2 = High + S3 = High -> grün

// Kalibrierung
printf("Weiß Kal. nach 5 sec");
delay(5000);
printf("start");

//Start der Kalibrierung
//rot lesen
digitalWrite(S2,LOW);
digitalWrite(S3,LOW);

while (i == 2)
{
    	
    //Puls Messung risingedge bis fallingedge ms Messung
    if (digitalRead (sensorOut) == 1 && i == 0)
    {
    clock_gettime(CLOCK_MONOTONIC, &startred);
    i = 1;
    }
    
    if (digitalRead (sensorOut) == 0 && i == 1)
    {
    clock_gettime(CLOCK_MONOTONIC, &endred);
    i = 2;
    }
}
    // Impulselängen Berechnung in ns
    Calred = diff * (endred.tv_sec - startred.tv_sec) + endred.tv_nsec - startred.tv_nsec;
    //Zähler zurücksetzen für den nächsten Loop
    i = 0;
    diff = 1000000000;
    
//blau lesen
digitalWrite(S2,LOW);
digitalWrite(S3,HIGH);
while (i == 2)
{
    	
    //Puls Messung risingedge bis fallingedge ms Messung
    if (digitalRead (sensorOut) == 1 && i == 0)
    {
    clock_gettime(CLOCK_MONOTONIC, &startblue);
    i = 1;
    }
    
    if (digitalRead (sensorOut) == 0 && i == 1)
    {
    clock_gettime(CLOCK_MONOTONIC, &endblue);
    i = 2;
    }
}
    // Impulselängen Berechnung in ns
    Calblue = diff * (endblue.tv_sec - startblue.tv_sec) + endblue.tv_nsec - startblue.tv_nsec;
    //Zähler zurücksetzen für den nächsten Loop
    i = 0;
    diff = 1000000000;
    
//grün lesen
digitalWrite(S2,HIGH);
digitalWrite(S3,HIGH);
while (i == 2)
{
    	
    //Puls Messung risingedge bis fallingedge ms Messung
    if (digitalRead (sensorOut) == 1 && i == 0)
    {
    clock_gettime(CLOCK_MONOTONIC, &startgreen);
    i = 1;
    }
    
    if (digitalRead (sensorOut) == 0 && i == 1)
    {
    clock_gettime(CLOCK_MONOTONIC, &endgreen);
    i = 2;
    }
}
    // Impulselängen Berechnung in ns
    Calgreen = diff * (endgreen.tv_sec - startgreen.tv_sec) + endgreen.tv_nsec - startgreen.tv_nsec;
    //Zähler zurücksetzen für den nächsten Loop
    i = 0;
    diff = 1000000000;

printf("Kalibrierung abgeschlossen");
printf("Kal rot: %d \n Kal blau: %d \nKal gruen: %d \n",Calred,Calblue,Calgreen);

//Start der Messung
while (1)
{

//rot lesen
digitalWrite(S2,LOW);
digitalWrite(S3,LOW);

while (i == 2)
{
    	
    //Puls Messung risingedge bis fallingedge ms Messung
    if (digitalRead (sensorOut) == 1 && i == 0)
    {
    clock_gettime(CLOCK_MONOTONIC, &startred);
    i = 1;
    }
    
    if (digitalRead (sensorOut) == 0 && i == 1)
    {
    clock_gettime(CLOCK_MONOTONIC, &endred);
    i = 2;
    }
}
    // Impulselängen Berechnung in ns
    diff = diff * (endred.tv_sec - startred.tv_sec) + endred.tv_nsec - startred.tv_nsec;
    diff = diff/Calred;
    printf("Rot = %llu \n", (long long unsigned int) diff);
    //Zähler zurücksetzen für den nächsten Loop
    i = 0;
    diff = 1000000000;
    delay(100);
    
//blau lesen
digitalWrite(S2,LOW);
digitalWrite(S3,HIGH);
while (i == 2)
{
    	
    //Puls Messung risingedge bis fallingedge ms Messung
    if (digitalRead (sensorOut) == 1 && i == 0)
    {
    clock_gettime(CLOCK_MONOTONIC, &startblue);
    i = 1;
    }
    
    if (digitalRead (sensorOut) == 0 && i == 1)
    {
    clock_gettime(CLOCK_MONOTONIC, &endblue);
    i = 2;
    }
}
    // Impulselängen Berechnung in ns
    diff = diff * (endblue.tv_sec - startblue.tv_sec) + endblue.tv_nsec - startblue.tv_nsec;
    diff = diff/Calblue;
    printf("Blau = %llu \n", (long long unsigned int) diff);
    //Zähler zurücksetzen für den nächsten Loop
    i = 0;
    diff = 1000000000;
    delay(100);

//grün lesen
digitalWrite(S2,HIGH);
digitalWrite(S3,HIGH);
while (i == 2)
{
    	
    //Puls Messung risingedge bis fallingedge ms Messung
    if (digitalRead (sensorOut) == 1 && i == 0)
    {
    clock_gettime(CLOCK_MONOTONIC, &startgreen);
    i = 1;
    }
    
    if (digitalRead (sensorOut) == 0 && i == 1)
    {
    clock_gettime(CLOCK_MONOTONIC, &endgreen);
    i = 2;
    }
}
    // Impulselängen Berechnung in ns
    diff = diff * (endgreen.tv_sec - startgreen.tv_sec) + endgreen.tv_nsec - startgreen.tv_nsec;
    diff = diff/Calgreen;
    printf("Gruen = %llu \n", (long long unsigned int) diff);
    //Zähler zurücksetzen für den nächsten Loop
    i = 0;
    diff = 1000000000;
    delay(100);
}
    exit(0);
    
}
