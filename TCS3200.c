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
struct timespec startred, endred, startblue, endblue,startgreen, endgreen;
//Auslesen der Farben Tabelle
//S2 = Low + S3 = Low -> rot
//S2 = Low + S3 = High -> blau
//S2 = High + S3 = High -> grün

// Kalibrierung
printf("Weiß Kal. nach 5 sec");
delay(5000);
printf("start");
// Cal = 1 Kalibirierung abgeschlossen
int Cal = 0;
// Startwerte für rot, blau, grün
uint64_t Calred = 0;
uint64_t Calblue = 0;
uint64_t Calgreen = 0;

while (Cal == 0)
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
    //redloop = redloop +1;
    // wartet 10 ms
    delay(10);
}
    // Impulselängen Berechnung in ns
    Calred = diff * (endred.tv_sec - startred.tv_sec) + endred.tv_nsec - startred.tv_nsec;
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
    clock_gettime(CLOCK_MONOTONIC, &startblue);
    i = 1;
    }
    
    if (digitalRead (sensorOut) == 0 && i == 1)
    {
    clock_gettime(CLOCK_MONOTONIC, &endblue);
    i = 2;
    }
    //blueloop = blueloop +1;
    // wartet 10ms
    delay(10);
}
    // Impulselängen Berechnung in ns
    Calblue = diff * (endblue.tv_sec - startblue.tv_sec) + endblue.tv_nsec - startblue.tv_nsec;
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
    clock_gettime(CLOCK_MONOTONIC, &startgreen);
    i = 1;
    }
    
    if (digitalRead (sensorOut) == 0 && i == 1)
    {
    clock_gettime(CLOCK_MONOTONIC, &endgreen);
    i = 2;
    }
    //greenloop = greenloop +1;
    // wartet 10s 
    delay(10);
}
    // Impulselängen Berechnung in ns
    Calgreen = diff * (endgreen.tv_sec - startgreen.tv_sec) + endgreen.tv_nsec - startgreen.tv_nsec;
    //Zähler zurücksetzen für den nächsten Loop
    i = 0;
    //greenloop = 0;
    diff = 1000000000;
    Cal = 1;
}
printf("Kalibrierung abgeschlossen");
printf("Kal rot: %d\n Kal blau: %d\nKal gruen: %d\n",Calred,Calblue,Calgreen);

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
    clock_gettime(CLOCK_MONOTONIC, &startred);
    i = 1;
    }
    
    if (digitalRead (sensorOut) == 0 && i == 1)
    {
    clock_gettime(CLOCK_MONOTONIC, &endred);
    i = 2;
    }
    //redloop = redloop +1;
    // wartet 10 ms
    delay(10);
}
    // Impulselängen Berechnung in ns
    diff = diff * (endred.tv_sec - startred.tv_sec) + endred.tv_nsec - startred.tv_nsec;
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
    clock_gettime(CLOCK_MONOTONIC, &startblue);
    i = 1;
    }
    
    if (digitalRead (sensorOut) == 0 && i == 1)
    {
    clock_gettime(CLOCK_MONOTONIC, &endblue);
    i = 2;
    }
    //blueloop = blueloop +1;
    // wartet 10ms
    delay(10);
}
    // Impulselängen Berechnung in ns
    diff = diff * (endblue.tv_sec - startblue.tv_sec) + endblue.tv_nsec - startblue.tv_nsec;
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
    clock_gettime(CLOCK_MONOTONIC, &startgreen);
    i = 1;
    }
    
    if (digitalRead (sensorOut) == 0 && i == 1)
    {
    clock_gettime(CLOCK_MONOTONIC, &endgreen);
    i = 2;
    }
    //greenloop = greenloop +1;
    // wartet 10s 
    delay(10);
}
    // Impulselängen Berechnung in ns
    diff = diff * (endgreen.tv_sec - startgreen.tv_sec) + endgreen.tv_nsec - startgreen.tv_nsec;
    printf("Gruen = %llu \n", (long long unsigned int) diff);
    //Zähler zurücksetzen für den nächsten Loop
    i = 0;
    //greenloop = 0;
    diff = 1000000000;
}
    exit(0);
    
}
