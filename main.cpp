/*  Serial IO Template
*   Operate an RGB LED using serial communications between a PC and the Nucleo L476RG Board.
*   
*   The program takes the users input from their PC keyboard to alter the state of each LED colour (Red, Green, Blue), 
*   The red LED is controlled to blink at different rates depending on the user input. The green and blue LEDs are off by default. 
*   This template is to be modified in accordance with the Serial Communications Activities
*
*   Author: Andrew Knowles & James Chandler 2021
*/

#include "mbed.h"

BufferedSerial pc(USBTX, USBRX);        //establish serial communications between PC and NUCLEO

PwmOut redled(PB_3);      //define PWM pins for RGB LED
PwmOut greenled(PB_5);
PwmOut blueled(PB_4);

//create a char array called instruct and store the message within it
char INSTRUCT[] = "Use the F, M and S keys to set the LED blink rate to Fast, Medium and Slow.\nPress G to switch the green LED ON and B to switch the blue LED ON. Press X to reset the LED.\n" ;

//create a new array that will continually be erased and updated
char *INPUT = new char[1];

//declare functions
void init_led();
void update_blink(float delay_val);

int main(){
    init_led(); //initialise led
    pc.write(INSTRUCT, sizeof(INSTRUCT));   //print instructions to terminal
       
    while(1){
        
        if(pc.readable()){          //Check if any data are available to be read
            pc.read(INPUT, sizeof(INPUT));  //read the users input and store it in char array called INPUT
            if(*INPUT == 's' || *INPUT == 'S'){ //Fast Mode: if input is equal to the char 's' or 'S' , change the blink rate to 1 Hz
                update_blink(1.0f);
            }
            else if(*INPUT == 'x' || *INPUT == 'X'){ //if input is equal to the char 'x' or 'X' , reset all states to 0
                init_led();
            }
            else{                          //default condition, maintain current states.
               
            }
        }
     thread_sleep_for(100); 

    }

}

void init_led(){
    //default states for RGB LED (red ON full at 50%, green OFF, blue OFF)
    redled.write(0.5);
    redled.period(1/1000.0f);

}

void update_blink(float delay_val){
    // Update the red LED with new frequency - print the new frequency to the console
    redled.write(0.5);
    redled.period(1/delay_val);
}

