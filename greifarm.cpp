#include "servo.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>   // für Pindefinition
#include <time.h>       // nanosleep()

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
// myInterrupt:  Wird nach jedem Interrupt aufgerufen
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
    //Address values.
    PCA9685 pwm;
    pwm.init(1,0x40);
    usleep(1000 * 100);
    printf ("Setting frequency..\n");
    pwm.setPWMFreq (60);
    usleep(1000 * 1000);
    
    int j=220;
    
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
    
    pwm.setPWM(4,0,400);
    for(p=j; p<290;){
        p=p+10;
        pwm.setPWM(0,0,p);
        printf ("%d\n",p);
        usleep(1000 * 100);
        j=p;
    }
    
    pwm.setPWM(4,0,250);
    for(p=j;p>240;)
     {
     p=p-10;
     pwm.setPWM(0,0,p);
     printf ("%d\n",p);
     usleep(1000 * 100);
     j=p;
     }
    double rot, blau, gruen;
    bool x=true;
    bool red, blue, green,black,yellow,white;
    
    while(1){
        
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
        x = true;
        red= false;
        blue= false;
        green= false;
        black=false;
        yellow=false;
        white=false;
                      
        while (x==true)
        {
        //Initialisierung
        red= false;
        blue= false;
        green= false;
        black=false;
        yellow=false;
        white=false;
            
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
            
            //500ms Messung Gruen
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
            
            if (rot => 45 && rot > blau && rot > gruen)
            {
                red = true;
            }
            
            if (blue => 50 && blau > rot && blau > gruen)
            {
                blue = true;
            }
            
            if (gruen => 25 && gruen > blau && gruen > rot)
            {
                green = true;
            }
            if (gruen < 15 && rot < 15 && blue < 15)
            {
                black = true;
            }
            if (gruen => 60 && rot => 50 && blau => 40)
            {
                yellow = true;
            }
             if (gruen => 65 && rot => 65 && blau => 65)
            {
                white = true;
                yellow = false;
            }
            
        }
        //Auswahl der Bewegungroutine für rot
        if(red==true && blue==false && green == false && black==false && yellow==false && white==false){
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
        //Auswahl der Bewegungroutine für blau
        elseif(red==false && blue==true && green == false && black==false && yellow==false && white==false){
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
        //Auswahl der Bewegungroutine für grün
        elseif(red==false && blue==false && green == true && black==false && yellow==false && white==false){
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
        //Auswahl der Bewegungroutine für black
        elseif(red==false && blue==false && green == false && black==true && yellow==false && white==false){
        
        }
        //Auswahl der Bewegungroutine für yellow
        elseif(red==false && blue==false && green == false && black==false && yellow==true && white==false){
        
        }
        //Auswahl der Bewegungroutine für white
        elseif(red==false && blue==false && green == false && black==false && yellow==false && white==true){
        
        }
        
    }
    return 0;
}
