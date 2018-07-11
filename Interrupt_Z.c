#include <string.h>
#include <errno.h>
#include <stdio.h>      // für printf
#include <wiringPi.h>   // für Pindefinition
#include <time.h>       // für nanosleep
//#include <stdint.h>     /* für uint64 definition */
//#include <stdlib.h>     /* für exit() definition */
#include <unistd.h>

//Pindefinition mit wiringPi
//S0       direct auf Vcc
//S1       direct auf Vcc
#define S2 4
#define S3 5
#define sensorOut 0

// Kalibrierungswerte für rot, blau, grün
double Calred = 0;
double Calblue = 0;
double Calgreen = 0;

//frequency scalling to 2%, 20%, 100%
// S0 = Low + S1 = High -> 2%
// S0 = High + S1 = Low -> 20%
// S0 = High + S1 = High -> 100%

// event counter Variable
volatile int eventCounter = 0;
int i = 0;
// myInterrupt:  Wir nach jedem Interrupt aufgerufen
void myInterrupt(void) {
   eventCounter++;
}

int main(void) {
  // sets up wiringPi library
  if (wiringPiSetup () < 0) {
      fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno));
      return 1;
  }
//Steuerpins S2/S3 als Output
pinMode (S2, OUTPUT);
pinMode (S3, OUTPUT);
pinMode (sensorOut, INPUT);

//Definition des nanosleeps
struct timespec tim, tim2;
   tim.tv_sec = 0;
   tim.tv_nsec = 1000000;
   
//Start der Interruptroutine
   if ( wiringPiISR (sensorOut, INT_EDGE_FALLING, &myInterrupt) < 0 ) 
  {
      
      return 1;
  }

  //500ms Messung Rot
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  while ( i <= 500 ) 
  {
   // printf( "%d\n", eventCounter );
    nanosleep(&tim,&tim2);
    i++;
  }
  Calred = (eventCounter/500);
  printf ("Calred:%.9f\n",Calred);
  eventCounter = 0;
  i = 0;
  
  //500ms Messung Blau
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  while ( i <= 500 ) 
  {
   // printf( "%d\n", eventCounter );
    nanosleep(&tim,&tim2);
    i++;
  }
  Calblue = (eventCounter/500);
  printf ("Calblue:%.9f\n",Calblue);
  eventCounter = 0;
  i = 0;
   
   //500ms Messung Grün
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  while ( i <= 500 ) 
  {
   // printf( "%d\n", eventCounter );
    nanosleep(&tim,&tim2);
    i++;
  }
  Calgreen = (eventCounter/500);
  printf ("Calgreen:%.9f\n",Calgreen);
  eventCounter = 0;
  i = 0;
  return 0;
}
