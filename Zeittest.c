#include <stdio.h>      // für printf
//#include <wiringPi.h>   // für Pindefinition
#include <time.h>       /* für clock_gettime */
#include <stdint.h>     /* für uint64 definition */
#include <stdlib.h>     /* für exit() definition */
#include <inttypes.h>

int main(void)
{
clock_t t1,t2;
int i = 0;
uint64_t diff = 1000000000;
struct timespec startred, endred, startblue, endblue,startgreen, endgreen;

clock_gettime(CLOCK_REALTIME, &startred);
while(i<1000)
{i= i+1;}

clock_gettime(CLOCK_REALTIME, &endred);

diff = diff * (endred.tv_sec - startred.tv_sec) + (endred.tv_nsec - startred.tv_nsec);  
printf("%llu\n",(long long unsigned int) diff);  
float ts = startred.tv_nsec;
float te = endred.tv_nsec;
printf("%llu\n"",""%llu\n",(long long unsigned int) ts,(long long unsigned int) te);

clock_gettime(CLOCK_REALTIME, &startred);
while(i<10)
{i= i+1;}

clock_gettime(CLOCK_REALTIME, &endred);

diff = diff * (endred.tv_sec - startred.tv_sec) + (endred.tv_nsec - startred.tv_nsec);
printf("%llu\n",(long long unsigned int) diff);   
ts = startred.tv_nsec;
te = endred.tv_nsec;
printf("%llu\n"",""%llu\n",(long long unsigned int) ts,(long long unsigned int) te);
return(0);
}
