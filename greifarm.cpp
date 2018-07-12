#include "servo.h"
#include <iostream>
#include <stdio.h>
//#include <ncurses.h>
//#include <thread>
#include <unistd.h>

#include <stdio.h>
#include <string.h>
//#include <ncurses.h>
//#include <thread>
#include <unistd.h>
#include <wiringPi.h>   // f  r Pindefinition
#include <time.h>

#define S2 4
#define S3 5
#define sensorOut 0

double Calred = 0;
double Calblue = 0;
double Calgreen = 0;

//frequency scalling to 2%, 20%, 100%
// S0 = Low + S1 = High -> 2%
// S0 = High + S1 = Low -> 20%
// S0 = High + S1 = High -> 100%

using namespace std;
// event counter Variable
volatile int eventCounter = 0;
int p = 0;
// myInterrupt:  Wir nach jedem Interrupt aufgerufen
void myInterrupt(void) {
    eventCounter++;
}


int main () {
    if (wiringPiSetup () < 0) {
        fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno));
        return 1;
    }
    
    
    //Motor und Hat Initiallizierung
    
    int c=0, p=0, i;
    printf ("Testing testing\n");
    //make sure you use the right address values.
    PCA9685 pwm;
    pwm.init(1,0x40);
    usleep(1000 * 100);
    printf ("Setting frequency..\n");
    pwm.setPWMFreq (60);
    usleep(1000 * 1000);
    
    int j=220;
   // printf ("geben Sie 1 , 2, 3, 4 ein\n");
    //scanf ("%d",&c);
    
    //Motor auf Ausgang Position
    pwm.setPWM(4,0,250);
    for(p=j; p<240;){
        p=p+10;
        pwm.setPWM(0,0,p);
        printf ("%d\n",p);
        usleep(1000 * 100);
        j=p;
    }
    for(p=j;p>240;)
    {
        p=p-10;
        pwm.setPWM(0,0,p);
        printf ("%d\n",p);
        usleep(1000 * 100);
        j=p;
    }
    
    printf ("Kalibrierung des Sensors\n");
    sleep(3);
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
    
    //500ms Messung Gr  n
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
    
    //Wei ^=er Stein in Box
    //
    
    pwm.setPWM(4,0,400);
    for(p=j; p<290;){
        p=p+10;
        pwm.setPWM(0,0,p);
        printf ("%d\n",p);
        usleep(1000 * 100);
        j=p;
    }
    
    pwm.setPWM(4,0,250);
    /* for(p=j;p>240;)
     {
     p=p-10;
     pwm.setPWM(0,0,p);
     printf ("%d\n",p);
     usleep(1000 * 100);
     j=p;
     }*/
    while(true){
        
        //Motor auf Ausgang Position
        pwm.setPWM(4,0,250);
        for(p=j; p<240;){
            p=p+10;
            pwm.setPWM(0,0,p);
            printf ("%d\n",p);
            usleep(1000 * 100);
            j=p;
        }
        for(p=j;p>240;)
        {
            p=p-10;
            pwm.setPWM(0,0,p);
            printf ("%d\n",p);
            usleep(1000 * 100);
            j=p;
        }
        
        double rot, blau, gruen;
        bool red, blue, green;
        red= false;
        blue= false;
        green= false;
        
        while (red == true || blue == true || green == true )
        {
            //500ms Messung Rot
            digitalWrite(S2,LOW);
            digitalWrite(S3,LOW);
            while ( i <= 500 )
            {
                // printf( "%d\n", eventCounter );
                nanosleep(&tim,&tim2);
                i++;
            }
            rot = (eventCounter/500);
            printf ("Calred:%.9f\n",rot);
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
            blau = (eventCounter/500);
            printf ("Calblue:%.9f\n",blau);
            eventCounter = 0;
            i = 0;
            
            //500ms Messung Gr  n
            digitalWrite(S2,HIGH);
            digitalWrite(S3,HIGH);
            while ( i <= 500 )
            {
                // printf( "%d\n", eventCounter );
                nanosleep(&tim,&tim2);
                i++;
            }
            gruen = (eventCounter/500);
            printf ("Calgreen:%.9f\n",gruen);
            eventCounter = 0;
            i = 0;
            
            if (rot > Calred*2/3 && blau < Calblue/3 && gruen < Calgreen/3)
            {
                red = true;
            }
            
            if (rot < Calred/3 && blau > Calblue*2/3 && gruen < Calgreen/3)
            {
                blue = true;
            }
            
            if (rot < Calred/3 && blau < Calblue/3 && gruen  > Calgreen*2/3)
            {
                green = true;
            }
            
            
        }
        
        if(red==true && blue==false && green == false){
            pwm.setPWM(4,0,400);
            for(p=j; p<360;){
                p=p+10;
                pwm.setPWM(0,0,p);
                printf ("%d\n",p);
                usleep(1000 * 100);
                j=p;
            }
            for(p=j;p<360;)
            {
                p=p-10;
                pwm.setPWM(0,0,p);
                printf ("%d\n",p);
                usleep(1000 * 100);
                j=p;
            }
            pwm.setPWM(4,0,220);
            
        }
        
        if(red==false && blue==true && green == false){
            pwm.setPWM(4,0,400);
            for(p=j; p<430;){
                p=p+10;
                pwm.setPWM(0,0,p);
                printf ("%d\n",p);
                usleep(1000 * 100);
                j=p;
            }
            
            for(p=j;p>430;)
            {
                p=p-10;
                pwm.setPWM(0,0,p);
                printf ("%d\n",p);
                usleep(1000 * 100);
                j=p;
            }
            pwm.setPWM(4,0,220);
        }
        
        if(red==false && blue==false && green == true){
            pwm.setPWM(4,0,400);
            for(p=j; p<500;){
                p=p+10;
                pwm.setPWM(0,0,p);
                printf ("%d\n",p);
                usleep(1000 * 100);
                j=p;
            }
            for(p=j;p>500;)
            {
                p=p-10;
                pwm.setPWM(0,0,p);
                printf ("%d\n",p);
                usleep(1000 * 100);
                j=p;
            }
            pwm.setPWM(4,0,220);
        }
        
        return 0;
    }
}
