//TCS3200 Farbsensor 
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
long diff = 1000000000;     //für Nanosec
//Zeitmessung für Pulsweite
struct timespec startred, endred, startblue, endblue,startgreen, endgreen;

//Auslesen der Farben Tabelle
//S2 = Low + S3 = Low -> rot
//S2 = Low + S3 = High -> blau
//S2 = High + S3 = High -> grün

// Kalibrierung
printf("Weiß Kal. nach 5 sec\n");
delay(5000);
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
    clock_gettime(CLOCK_REALTIME, &startred);
    i = 1;
    }
    
    if (digitalRead (sensorOut) == 0 && i == 1)
    {
    clock_gettime(CLOCK_REALTIME, &endred);
    i = 2;
    }
}
    // Impulselängen Berechnung in ns
    printf("Rot start_sec = %ld \n",  startred.tv_sec);
    printf("Rot start_nsec = %ld \n", startred.tv_nsec);
    printf("Rot end_sec = %ld \n", endred.tv_sec);
    printf("Rot end_nsec = %ld \n", endred.tv_nsec);
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
    clock_gettime(CLOCK_REALTIME, &startblue);
    i = 1;
    }
    
    if (digitalRead (sensorOut) == 0 && i == 1)
    {
    clock_gettime(CLOCK_REALTIME, &endblue);
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
    clock_gettime(CLOCK_REALTIME, &startgreen);
    i = 1;
    }
    
    if (digitalRead (sensorOut) == 0 && i == 1)
    {
    clock_gettime(CLOCK_REALTIME, &endgreen);
    i = 2;
    }
}
    // Impulselängen Berechnung in ns
    Calgreen = diff * (endgreen.tv_sec - startgreen.tv_sec) + endgreen.tv_nsec - startgreen.tv_nsec;
    //Zähler zurücksetzen für den nächsten Loop
    i = 0;
    diff = 1000000000;

printf("Kalibrierung abgeschlossen\n");
printf("Kal rot: %ld \n Kal blau: %ld \nKal gruen: %ld \n",Calred,Calblue,Calgreen);

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
    clock_gettime(CLOCK_REALTIME, &startred);
    i = 1;
    }
    
    if (digitalRead (sensorOut) == 0 && i == 1)
    {
    clock_gettime(CLOCK_REALTIME, &endred);
    i = 2;
    }
}
    // Impulselängen Berechnung in ns
    diff = diff * (endred.tv_sec - startred.tv_sec) + endred.tv_nsec - startred.tv_nsec;
    diff = diff/Calred;
    printf("Rot start_sec = %ld \n", startred.tv_sec);
    printf("Rot start_nsec = %ld \n", startred.tv_nsec);
    printf("Rot end_sec = %ld \n", endred.tv_sec);
    printf("Rot end_nsec = %ld \n", endred.tv_nsec);
    printf("Rot = %llu \n", (long long unsigned int) diff);
    //Zähler zurücksetzen für den nächsten Loop
    i = 0;
    diff = 1000000000;
    delay(10000);
    
//blau lesen
digitalWrite(S2,LOW);
digitalWrite(S3,HIGH);
while (i == 2)
{
    	
    //Puls Messung risingedge bis fallingedge ms Messung
    if (digitalRead (sensorOut) == 1 && i == 0)
    {
    clock_gettime(CLOCK_REALTIME, &startblue);
    i = 1;
    }
    
    if (digitalRead (sensorOut) == 0 && i == 1)
    {
    clock_gettime(CLOCK_REALTIME, &endblue);
    i = 2;
    }
}
    // Impulselängen Berechnung in ns
    diff = diff * (endblue.tv_sec - startblue.tv_sec) + endblue.tv_nsec - startblue.tv_nsec;
    diff = diff/Calblue;
    printf("Blau = %ld \n", diff);
    //Zähler zurücksetzen für den nächsten Loop
    i = 0;
    diff = 1000000000;
    delay(10000);

//grün lesen
digitalWrite(S2,HIGH);
digitalWrite(S3,HIGH);
while (i == 2)
{
    	
    //Puls Messung risingedge bis fallingedge ms Messung
    if (digitalRead (sensorOut) == 1 && i == 0)
    {
    clock_gettime(CLOCK_REALTIME, &startgreen);
    i = 1;
    }
    
    if (digitalRead (sensorOut) == 0 && i == 1)
    {
    clock_gettime(CLOCK_REALTIME, &endgreen);
    i = 2;
    }
}
    // Impulselängen Berechnung in ns
    diff = diff * (endgreen.tv_sec - startgreen.tv_sec) + endgreen.tv_nsec - startgreen.tv_nsec;
    diff = diff/Calgreen;
    printf("Gruen = %ld \n", diff);
    //Zähler zurücksetzen für den nächsten Loop
    i = 0;
    diff = 1000000000;
    delay(10000);
}
    exit(0);
    
}
