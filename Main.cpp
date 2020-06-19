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
byte tokenBuffer [30];
byte command_length;
byte first_char;
byte second_char;
byte count_letter = 0;
byte token_buffer_count =0;



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
                
                // if (newChar != 127){
                //     buffer[index] = newChar;
                //     Serial.print( buffer[index]);
                // }else{
                //     //buffer[index] = buffer[ index + 1] ;
                //     buffer.remove(index)
                //     Serial.print( buffer[index]);
                //     index = index -1;
                
                // }

                if(newChar != 13){
                    index ++;
                }else{
                    buffer[index] = 0;
                    length = index;
                    job ++;
                    Serial.print('\n');
                    
                    //Serial.print((byte)buffer[length]); // works
                    index = 0;
                    //count_letter = 0;
                    break;
                }
            }

                break; 
        case 2:
                
                for (byte i = 0 ; i < length  ; i++){

                    if (buffer[i] != ' ' ){
                        if (count_letter == 0){
                                first_char  = (byte)buffer[i];
                                Serial.print((char)first_char);  // works
                        }else if( count_letter == 1){
                                second_char = (byte)buffer[i];
                                Serial.print((char)second_char); // works
                        }

                        if (buffer[i] != 0){
                            count_letter ++;

                        }  
                        //Serial.println(count_letter);
                        //Serial.println(count_letter); // works
                            
                    }else{
                        //Serial.println(count_letter);
                        count_letter = 0;
                    }
                    //Serial.print((char)first_char);
                    //Serial.print((char)second_char);
                    Serial.println(count_letter);

                }
                //Serial.print("hi");
                //for (byte i = 0; i < token_buffer_count ; i ++ ){
                //    Serial.print((int)tokenBuffer[i]);
                //}
                //Serial.print("hi");    
                //token_buffer_count = 0;
                job = 0;
                count_letter = 0;
                for (byte i = 0; i < length; i ++){
                        buffer[i] = 0;
                    }
                break;
        default:
                break;  
    }
}
