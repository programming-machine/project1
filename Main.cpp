#include <Arduino.h>

#define t_LED 2
#define t_RED 5
#define EOL t_EOL 255
using byte = unsigned char; 
using namespace std; 

byte buffer [20];
byte newChar;
int job = 0; 
int index = 0 ; 
int length = 0; 
byte array [4];

void setup() {
    Serial.begin(9600);
    pinMode(13,OUTPUT);
}

void loop()
{
    switch (job){
        case 0: 
            Serial.print("Enter a commaand: ");
            job ++;
            break;
        case 1:
            while (Serial.available()){
                newChar = Serial.read(); // read the incoming data as string
                buffer[index] = newChar;
                Serial.print((char)buffer[index]);
                if(newChar != 13){
                    index ++;
                }else{
                    buffer[index] = 0;
                    index = 0;
                    job ++;
                    Serial.print('\n');
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
