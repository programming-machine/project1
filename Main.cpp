#include <Arduino.h>
#include <math.h>


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
byte final_length = 0 ; //just added
byte last_color = 0;
byte led = 13;;
word interval = 0;
byte count_digits = 0;
byte number_array [10];
byte done_counting = 0 ;



byte lookUp_array[13][4] = 
{{'l','e',3,t_LED},{'r','e',3,t_RED},{'e','o',3,t_EOL},{'d','1',3,t_D13},{'o','n',2,t_ON},
{'o','f',3,t_OFF},{'b','l',5,t_BLINK},{'g','r',5,t_GREEN},{'s','e',3,t_SET},{'s','t',6,t_STATUS},
{'l','e',4,t_LEDS},{'v','e',7,t_VERSION},{'h','e',4,t_HELP}};

void D13_turn_on (){
    digitalWrite(led, HIGH );
}

void D13_turn_off (){
    digitalWrite(led, LOW );
}


void D13_turn_blink (){

    for (byte i = 0; i < 10; i++){
        digitalWrite(led, HIGH );
        delay(500);
        digitalWrite(led, LOW );
        delay(500);
    }
}



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


void blink_led (byte last_color){
    //time = millis();
 
    if (last_color == 0 || last_color == t_RED ){
        for (int i = 0 ; i < 10; i ++){
            turn_red();
            delay(500);
            turn_off();
            delay(500);
        }    
    }else{

            for (int i = 0 ; i < 10; i ++){
            
            
            turn_green();
            delay(500);
            turn_off();
            delay(500);
            
        }    

    }
        
            
    

}



void setup() {
    Serial.begin(9600);
    pinMode(led, OUTPUT);
    pinMode(2,OUTPUT);
    pinMode(3,OUTPUT);

}



void loop()
{
    //time = millis();
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
                    if (tokenBuffer[0] == t_SET && tokenBuffer[1] == t_BLINK){
                            
                        if ( buffer[i] >= 48 && buffer[i] <= 57 && done_counting == 0){
                            number_array[count_digits] = buffer[i];
                            count_digits ++;
                            
                        }else{
                            done_counting = 1;
                        }
                                        
                    }

                }

                if (count_digits > 0){
                    for (byte i = count_digits - 1 ; i >= 0; i -- ){
                    interval += ( pow(10, i) * number_array [i] ) ;
                    }
                }
                
                Serial.print(interval);
                Serial.println();

                tokenBuffer[token_buffer_count] = t_EOL;

                switch (tokenBuffer[0])
                {
                case t_LED:
                    switch (tokenBuffer[1])
                    {
                    case t_RED:
                        turn_red();
                        last_color = t_RED;
                        break;
                    case t_GREEN:
                        turn_green();
                        last_color = t_GREEN;
                        break;
                    case t_BLINK:
                        blink_led(last_color);    
                        last_color = 0;
                        break;
                    case t_ON:
                        turn_on();
                        break;
                    case t_OFF:
                        turn_off();
                        break;
                    default:
                        break;
                    }
                break;
                case t_HELP:
                    Serial.println();
                    Serial.println();
                    Serial.println( "on: turns on" );
                    Serial.println( "off: turns off" );
                    Serial.println( "green: truns Green" );
                    Serial.println( "red: truns RED" );
                    Serial.println( "blink: led blinks" );
                    Serial.println();
                    Serial.println();
                break;

                case t_D13:

                    switch (tokenBuffer[1])
                    {
                    case t_ON:
                        D13_turn_on();
                        break;
                    case t_OFF:
                        D13_turn_off();
                        break;
                    case t_BLINK:
                        D13_turn_blink ();
                        break;
                        
                    default:
                        break;
                    }
                break;
                
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
                interval = 0;
                count_digits = 0;
                done_counting = 0;

                break;
        default:
                break;  
    }
}
