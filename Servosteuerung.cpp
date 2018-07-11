#include <stdio.h>
//#include <ncurses.h>
//#include <thread>
#include <unistd.h>

using namespace std;
int main () {
    int c=0, i=0;
        printf ("Testing testing\n");
        //make sure you use the right address values.
        PCA9685 pwm;
        pwm.init(1,0x40);
        usleep(1000 * 100);
        printf ("Setting frequency..\n");
        pwm.setPWMFreq (60);
        usleep(1000 * 1000);

    while(true){
    int j=220;
    printf ("geben Sie 1 , 2, 3, 4 ein\n");
        scanf ("%d",&c);

    if(c==1){
pwm.setPWM(4,0,400); 
for(i=j; i<360;){
        i=i+10;
    pwm.setPWM(0,0,i);
    printf ("%d\n",i);
    usleep(1000 * 100);
    j=i;
}
        for(i=j;i<360;)
{
    i=i-10;
    pwm.setPWM(0,0,i);
    printf ("%d\n",i);
    usleep(1000 * 100);
    j=i;
}
pwm.setPWM(4,0,220); 

            }

            if (c==2){
pwm.setPWM(4,0,400); 
for(i=j; i<430;){
        i=i+10;
    pwm.setPWM(0,0,i);
    printf ("%d\n",i);
    usleep(1000 * 100);
    j=i;
}
       
for(i=j;i>430;)
{
    i=i-10;
    pwm.setPWM(0,0,i);
    printf ("%d\n",i);
    usleep(1000 * 100);
    j=i;
}     
pwm.setPWM(4,0,220); 
           }

        if (c==3){
pwm.setPWM(4,0,400); 
    for(i=j; i<500;){
        i=i+10;
    pwm.setPWM(0,0,i);
    printf ("%d\n",i);
    usleep(1000 * 100);
    j=i;
}
        for(i=j;i>500;)
{
    i=i-10;
    pwm.setPWM(0,0,i);
    printf ("%d\n",i);
    usleep(1000 * 100);
    j=i;
}
pwm.setPWM(4,0,220); 
            }
        if(c==4){

pwm.setPWM(4,0,250);   
           for(i=j; i<240;){
        i=i+10;
    pwm.setPWM(0,0,i);
    printf ("%d\n",i);
    usleep(1000 * 100);
    j=i;
}
        for(i=j;i>240;)
{
    i=i-10;
    pwm.setPWM(0,0,i);
    printf ("%d\n",i);
    usleep(1000 * 100);
    j=i;
}

        
}
        return 0;
}
}
