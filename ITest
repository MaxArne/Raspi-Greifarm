#include <stdio.h>      // für printf
#include <wiringPi.h>   // für Pindefinition
#include <time.h>       /* für clock_gettime */
#include <sys/time.h>   // für gettimeofday()
#include <stdint.h>     /* für uint64 definition */
#include <stdlib.h>     /* für exit() definition */
#include <unistd.h>

volatile int eventCounter = 0;
int i = 0;
double timer,starttime,endtime;
struct timespec start, end;
// myInterrupt:  called every time an event occurs
void myInterrupt(void) {
   eventCounter++;
}

int main(void) 
{
  
  // set Pin 17/0 generate an interrupt on high-to-low transitions
  // and attach myInterrupt() to the interrupt
   clock_gettime( CLOCK_MONOTONIC, &start);
   starttime = (start.tv_sec + ((double)start.tv_nsec/1000000000));
   while (timer<=50) 
   {
      wiringPiISR (i, INT_EDGE_FALLING, &myInterrupt);
      clock_gettime( CLOCK_MONOTONIC, &end);
      endtime = (end.tv_sec + ((double)end.tv_nsec/1000000000));
      timer = endtime-starttime;
      
      printf("Interruptcounter: %d\n",eventCounter);
      printf("timer: %f\n",timer);
      sleep(1);
      i=1;
      wiringPiISR (i, INT_EDGE_FALLING, &myInterrupt);
      clock_gettime( CLOCK_MONOTONIC, &end);
      end = (end.tv_sec + ((double)end.tv_nsec/1000000000));
      timer = endtime-starttime;
      
      printf("Interruptcounter: %d\n",eventCounter);
      printf("timer: %f\n",timer);
      sleep(1);
      i=0;
      return 0;
   }
}
