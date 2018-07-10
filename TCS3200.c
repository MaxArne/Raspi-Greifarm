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
#define S2 4
#define S3 5
#define sensorOut 6
#define BILLION  1000000000
// Kalibrierungswerte für rot, blau, grün
double Calred = 0;
double Calblue = 0;
double Calgreen = 0;

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
//uint_64 diff = 1000000;     //für Nanosec
//Zeitmessung für Pulsweite
struct timespec startred, endred, startblue, endblue,startgreen, endgreen;

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
    clock_gettime( CLOCK_MONOTONIC, &startred);
    i = 1;
    }
    
    if (digitalRead (sensorOut) == 0 && i == 1)
    {
    clock_gettime( CLOCK_MONOTONIC, &endred);
    i = 2;
    }
}

    // Impulselängen Berechnung in ns
    printf("Rot start_sec = %lld \n", (long long int) startred.tv_sec);
    printf("Rot start_nsec = %.9f \n", ((double) startred.tv_nsec/BILLION));
    printf("Rot end_sec = %lld \n",(long long int) endred.tv_sec);
    printf("Rot end_nsec = %.9f \n",((double) endred.tv_nsec/BILLION));
    Calred = ((endred.tv_sec + ((double)endred.tv_nsec/1000000000)) - (startred.tv_sec + ((double)startred.tv_nsec/1000000000))) ;
    //Zähler zurücksetzen für den nächsten Loop
    i = 0;

    
    
    
//blau lesen
digitalWrite(S2,LOW);
digitalWrite(S3,HIGH);
while (i == 2)
{
    	
    //Puls Messung risingedge bis fallingedge ms Messung
    //Puls Messung risingedge bis fallingedge ms Messung
    if (digitalRead (sensorOut) == 1 && i == 0)
    {
    clock_gettime( CLOCK_MONOTONIC, &startblue);
    i = 1;
    }
    
    if (digitalRead (sensorOut) == 0 && i == 1)
    {
    clock_gettime( CLOCK_MONOTONIC, &endblue);
    i = 2;
    }
}
    // Impulselängen Berechnung in ns
    printf("Blau start_sec = %lld \n", (long long int) startblue.tv_sec);
    printf("Blau start_nsec = %.9f \n", ((double) startblue.tv_nsec/BILLION));
    printf("Blau end_sec = %lld \n",(long long int) endblue.tv_sec);
    printf("Blau end_nsec = %.9f \n",((double) endblue.tv_nsec/BILLION));
    Calblue = ((endblue.tv_sec + ((double)endblue.tv_nsec/1000000000)) - (startblue.tv_sec + ((double)startblue.tv_nsec/1000000000))) ;
    //Zähler zurücksetzen für den nächsten Loop
    i = 0;

    
//grün lesen
digitalWrite(S2,HIGH);
digitalWrite(S3,HIGH);
while (i == 2)
{
    	
    //Puls Messung risingedge bis fallingedge ms Messung
    if (digitalRead (sensorOut) == 1 && i == 0)
    {
    clock_gettime( CLOCK_MONOTONIC, &startgreen);
    i = 1;
    }
    
    if (digitalRead (sensorOut) == 0 && i == 1)
    {
    clock_gettime( CLOCK_MONOTONIC, &endgreen);
    i = 2;
    }
}
    // Impulselängen Berechnung in ns
    printf("Blau start_sec = %lld \n", (long long int) startred.tv_sec);
    printf("Blau start_nsec = %.9f \n", ((double) startred.tv_nsec/BILLION));
    printf("Blau end_sec = %lld \n",(long long int) endred.tv_sec);
    printf("Blau end_nsec = %.9f \n",((double) endred.tv_nsec/BILLION));
    Calgreen = ((endgreen.tv_sec + ((double)endgreen.tv_nsec/1000000000)) - (startgreen.tv_sec + ((double)startgreen.tv_nsec/1000000000))) ;
    //Zähler zurücksetzen für den nächsten Loop
    i = 0;


printf("Kalibrierung abgeschlossen\n");
printf("Kal rot: %.9f \n Kal blau: %.9f \nKal gruen: %.9f \n",Calred,Calblue,Calgreen);
}
