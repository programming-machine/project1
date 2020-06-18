#include <Arduino.h>

#define t_LED 2
#define t_RED 5
#define EOL t_EOL 255
using byte = unsigned char; 
using namespace std; 
//#include <string.h> 
//int incomingByte = 0; // for incoming serial data
//String a;

byte buffer [20];

byte newChar;
int job = 0; 

int index = 0 ; 


byte array [4];

void setup() {
    Serial.begin(9600);
    pinMode(13,OUTPUT);
}

void loop()
{
    //Serial.println("hello world");
    //Serial.readString();
    //delay(100000);
    //byte array [4];
    
    //digitalWrite(13,HIGH);delay(1000);
    //digitalWrite(13,LOW);delay(1000);

    switch (job){
        case 0: 
            Serial.println("Enter a commaand: ");
            job ++;
            break;
        case 1:
            while (Serial.available()){
                newChar = Serial.read(); // read the incoming data as string
                buffer[index] = newChar;
                index ++;
                    if (newChar == 13){
                        index = 0;
                        job ++;
                        break;
                    }
            }  
        break; 
        case 2:
                job = 0;
                break;
        default:
                break;  
    }
}