#include <stdio.h>
#include <time.h>
#include<stdlib.h>

int main(int argc, char **argv)
{

  double result;
  struct timespec tp,tz;
  clockid_t clk_id;
  double i=1.123456789;
  printf("i: %.9f\n", i);
//  clk_id = CLOCK_REALTIME;
  clk_id = CLOCK_MONOTONIC;
//  clk_id = CLOCK_BOOTTIME;
//  clk_id = CLOCK_PROCESS_CPUTIME_ID;

  // int clock_gettime(clockid_t clk_id, struct timespec *tp);
  result = clock_gettime(clk_id, &tp);
  printf("result: %f\n", result);
  printf("tp.tv_sec: %lld\n", (long long int)tp.tv_sec);
  printf("tp.tv_nsec: %ld\n", tp.tv_nsec);

  result = clock_getres(clk_id, &tp);
  printf("result: %f\n", result);
  printf("tp.tv_sec: %lld\n",(long long int) tp.tv_sec);
  printf("tp.tv_nsec: %ld\n", tp.tv_nsec);
  //500 ns sleep
  result = clock_gettime(clk_id, &tz);
  struct timespec tim, tim2;
   tim.tv_sec = 0;
   tim.tv_nsec = 500;

   nanosleep(&tim , &tim2);


  result = clock_gettime(clk_id, &tp);
  printf("result: %f\n", result);
  printf("tp.tv_sec: %lld\n", (long long int)tp.tv_sec);
  printf("tp.tv_nsec: %f\n", (double) tp.tv_nsec/1000000000);
  printf("tz.tv_sec: %lld\n", (long long int)tz.tv_sec);
  printf("tz.tv_nsec: %f\n", (double) tz.tv_nsec/1000000000);
  result = ((tp.tv_sec + ((double)tp.tv_nsec/1000000000)) -
(tz.tv_sec + ((double)tz.tv_nsec/1000000000)));
printf("result: %.9f\n", result);
return 0;
}
