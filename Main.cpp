#include <Arduino.h>

#define      t_LED 2
#define      t_RED 5
#define      t_EOL 255
#define      t_D13 13
#define       t_ON 1
#define      t_OFF 100
#define    t_BLINK 3
#define    t_GREEN 4
#define      t_SET 6
#define   t_STATUS 7
#define     t_LEDS 8
#define  t_VERSION 9
#define     t_HELP 10

using byte = unsigned char; 
using namespace std; 

char buffer [40];
byte newChar;
byte job = 0; 
byte index = 0 ; 
byte length = 0; 
byte tokenBuffer [30];
byte first_char;
byte second_char;
byte count_letter = 0;
byte token_buffer_count =0;
byte command_length =0;
byte count_space = 0;
byte final_length;



byte lookUp_array[13][4] = 
{{'l','e',3,t_LED},{'r','e',3,t_RED},{'e','o',3,t_EOL},{'d','1',3,t_D13},{'o','n',2,t_ON},
{'o','f',3,t_OFF},{'b','l',5,t_BLINK},{'g','r',5,t_GREEN},{'s','e',3,t_SET},{'s','t',6,t_STATUS},
{'l','e',4,t_LEDS},{'v','e',7,t_VERSION},{'h','e',4,t_HELP}};

void turn_red (){
    digitalWrite(3, LOW);
    digitalWrite(2, HIGH );


}

void turn_green (){
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH );

}


void turn_on (){
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH );

}


void turn_off (){
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH );

}



void setup() {
    Serial.begin(9600);
    pinMode(2,OUTPUT);
    pinMode(3,OUTPUT);
    //digitalWrite(3, LOW);
    //digitalWrite(2, HIGH );
    //turn_green();

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
                        count_space = 0;
                        if (count_letter == 0){
                                first_char  = (byte)buffer[i];
                                //Serial.print((char)first_char);  // works
                        }else if( count_letter == 1){
                                second_char = (byte)buffer[i];
                                //Serial.print((char)second_char); // works
                        }

                        if (buffer[i] != 0){
                            count_letter ++;
                        }

                        if ( i == length -1 )
                        {
                        command_length = count_letter;    
                        }
                              
                    }else{
                        count_space ++;
                        command_length = count_letter;    
                        // }
                        count_letter = 0;
                    }

                   if ( (count_space == 1|| i == length -1) &&  command_length !=0  ) {
                      final_length = command_length; 
                      //Serial.println( final_length );

                            // look up
                    for (byte i = 0; i < 13 ; i ++){
                        if (lookUp_array[i][0] == first_char && lookUp_array[i][1] == second_char && 
                        lookUp_array[i][2] == final_length ){
                          //Serial.println("hi");
                          tokenBuffer[token_buffer_count] = lookUp_array[i][3];
                          token_buffer_count ++; 
                        }
                    }
                    }

                }

                tokenBuffer[token_buffer_count] = t_EOL;

                switch (tokenBuffer[0])
                {
                case t_LED:
                    switch (tokenBuffer[1])
                    {
                    case t_RED:
                        turn_red();
                        break;
                    case t_GREEN:
                        turn_green();
                        break;
                    default:
                        break;
                    }
                    case t_ON:
                        //turn_on();
                        break;

                    case t_OFF:
                        turn_off();
                        break;
                    break;
                
                // case t_ON:
                //     turn_on();
                //     break;

                // case t_OFF:
                //     turn_off();
                //     break;
                
                default:
                    break;
                }
                    
                    for (byte i = 0; i <= token_buffer_count ; i ++){
                        Serial.print((byte)tokenBuffer[i]);
                        Serial.print( ' ' );
                    }



                     Serial.println(  );
                job = 0;
                count_letter = 0;
                command_length = 0;
                for (byte i = 0; i < length; i ++){
                        buffer[i] = 0;
                    }
                token_buffer_count = 0;

                for (byte i = 0; i < token_buffer_count; i ++){
                        tokenBuffer[i] = 0;
                    }


                break;
        default:
                break;  
    }
}
