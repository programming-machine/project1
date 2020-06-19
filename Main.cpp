#include <Arduino.h>

#define      t_LED 2
#define      t_RED 5
#define      t_EOL 255
#define      t_D13 13
#define       t_ON 1
#define      t_OFF 0
#define    t_BLINK 3
#define    t_GREEN 4
#define      t_SET 6
#define   t_STATUS 7
#define     t_LEDS 8
#define  t_VERSION 9
#define     t_HELP 10

using byte = unsigned char; 
using namespace std; 

char buffer [20];
byte newChar;
byte job = 0; 
byte index = 0 ; 
byte length = 0; 
byte tokenBuffer [10];
byte command_length;
byte first_char;
byte second_char;
byte count_letter = 0;


byte lookUp_array[13][4] = 
{{'l','e',3,t_LED},{'r','e',3,t_RED},{'e','o',3,t_EOL},{'d','1',3,t_D13},{'o','n',2,t_ON},
{'o','f',2,t_OFF},{'b','l',5,t_BLINK},{'g','r',5,t_GREEN},{'s','e',3,t_SET},{'s','t',6,t_STATUS},
{'l','e',4,t_LEDS},{'v','e',7,t_VERSION},{'h','e',4,t_HELP}};



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
                Serial.print( buffer[index]);
                if(newChar != 13){
                    index ++;
                }else{
                    buffer[index] = 0;
                    index = 0;
                    length = index;
                    job ++;
                    Serial.print('\n');
                    break;
                }
            }

                break; 
        case 2:
                for (byte i = 0 ; i < length ; i++){
                    if (buffer[i] != ' ' &&  buffer[i] != 0 ){
                        if (count_letter == 0){
                            first_char  = buffer[i];
                        }else if( count_letter == 1){
                            second_char = buffer[i]; 
                        }  
                        count_letter ++;
                            
                    }else{
                        // look up                            
                        for (byte i = 0; i < 13; i ++){
                                if (first_char == lookUp_array [i][0] && 
                                    second_char == lookUp_array[i][1] && count_letter == lookUp_array[i][2] ) {
                                } 
                        }
                        count_letter = 0;
                    }
                }
                job = 0;
                break;
        default:
                break;  
    }
}
