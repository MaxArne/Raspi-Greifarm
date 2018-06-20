#include <stdio.h>
#include <wiringPi.h>
//https://www.electronicshub.org/raspberry-pi-color-sensor-tutorial/
// Pin Belegung in BCM Nummern
#define S0        // direct auf Vcc
#define S1        // direct auf Vcc
#define S2 23
#define S3 24
#define sensorOut 25

int frequency = 0;

int setup(char x0, char y1)
{
if (wiringPiSetup() == -1)
    return 1;
wiringPiSetup () ;
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

int main(void)
{

//setup (High,Low);		//Werte für x und y festlegen um scalling einzustellen
//Auslesen der Farben Tabelle
//S2 = Low + S3 = Low -> rot
//S2 = Low + S3 = High -> blau
//S2 = High + S3 = High -> grün
//rot lesen
digitalWrite(S2,LOW);
digitalWrite(S3,LOW);

// Reading the output frequency
frequency = pulseIn(sensorOut, LOW);
// Printing the value on the serial monitor
Serial.print("R= ");		//printing name
Serial.print(frequency);	//printing RED color frequency
Serial.print("  ");
delay(100);

}
