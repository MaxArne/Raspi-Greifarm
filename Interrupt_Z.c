#include <string.h>
#include <errno.h>
#include <stdio.h>      // für printf
#include <wiringPi.h>   // für Pindefinition
#include <time.h>       /* für clock_gettime */
#include <sys/time.h>   // für gettimeofday()
#include <stdint.h>     /* für uint64 definition */
#include <stdlib.h>     /* für exit() definition */
#include <unistd.h>

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


// Use GPIO Pin 17, which is Pin 0 for wiringPi library


//Interrupt Bsp.: http://www.science.smith.edu/dftwiki/index.php/Tutorial:_Interrupt-Driven_Event-Counter_on_the_Raspberry_Pi
// the event counter 
volatile int eventCounter = 0;
struct timespec tim, tim2;
   tim.tv_sec = 0;
   tim.tv_nsec = 1000000;
// myInterrupt:  called every time an event occurs
void myInterrupt(void) {
   eventCounter++;
}

int main(void) {
  // sets up the wiringPi library
  if (wiringPiSetup () < 0) {
      fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno));
      return 1;
  }
pinMode (S2, OUTPUT);
pinMode (S3, OUTPUT);
pinMode (sensorOut, INPUT);

  // set Pin 17/0 generate an interrupt on high-to-low transitions
  // and attach myInterrupt() to the interrupt
  
   if ( wiringPiISR (sensorOut, INT_EDGE_FALLING, &myInterrupt) && i <=500 ) 
  {
      
      return 1;
  }
   
  // display counter value every second.
  //clock_gettime(clk_id, &start);
  //starttime = (start.tv_sec + ((double)start.tv_nsec/1000000000));
  //500ms essung
   while ( i <= 500 ) 
  {
    printf( "%d\n", eventCounter );
    nanosleep(&tim,&tim2);
    i++;
  }
  Calred = ((eventCounter/500)/2);
  printf ("Calred:%.9f\n",Calred)
  eventCounter = 0;
  return 0;
}
