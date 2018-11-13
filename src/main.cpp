//ebike by J.Mazeika 2014

#include <Arduino.h>
#include <avr/interrupt.h>
#include <EEPROM.h>
#include <avr/delay.h>
#include <avr/wdt.h>
#include "main.h"

const int sinusMax_us = 4583;
volatile unsigned int digit_on = 0;
volatile int d0 = 8;
volatile int d1 = 8;
volatile int d2 = 8;


void sinusMax();
void EEPROMWriteInt(int p_address, int p_value);
unsigned int EEPROMReadInt(int p_address);

int main() {

    unsigned int pulses = 0;
    bool cont_pulse = false;
    unsigned int display = 0;
    unsigned int prepulse = 10;
    unsigned int pulse = 150;
    const int pin_A = A5; // pin 12
    const int pin_B = 5; // pin 11
    unsigned char encoder_A;
    unsigned char encoder_B;
    unsigned char encoder_A_prev = 0;
    volatile int update_eeprom = 0;


    //---------------start init---------------//
    init();
    init_pins();

    pinMode(pin_A, INPUT);
    pinMode(pin_B, INPUT);
    pinMode(zeroCrossPin, INPUT);
    //analogReference(2); //set analog reference to internal 1.1V

    //wdt_enable(WDTO_2S);
    // enable interrupts
    cli();
    TCCR1B = (1 << WGM12) | (1 << CS10) | (1 << CS11);
    TCCR1A = 0;
    OCR1A = 1500; //interrupt freq
    TIMSK |= (1 << OCIE1A); //enable interrupt for display
    sei();

    LED_ON;
    _delay_ms(800);
    LED_OFF;
    d0 = 12;
    d1 = 12;
    d2 = 12;
    _delay_ms(500);
    d0 = 0;
    d1 = 0;
    d2 = 0;

    pulse = EEPROMReadInt(0x10);
    prepulse = EEPROMReadInt(0x20);
    
    //---------------start main loop---------------//
    
    while (1) {

        
        
        encoder_A = digitalRead(pin_A); // Read encoder pins
        encoder_B = digitalRead(pin_B);


        switch (display) {
            case 2:
                d0 = 0;
                d1 = 11;
                d2 = 11;
                cont_pulse = true;
                break;

            case 1:
                if ((!encoder_A) && (encoder_A_prev)) {
                    // A has gone from high to low 
                    if (encoder_B) {
                        // B is high so clockwise  
                        if (prepulse++ >= 100) prepulse = 0;
                        update_eeprom = 1;
                    } else {
                        // B is low so counter-clockwise      
                        if (prepulse-- <= 0) prepulse = 99;
                        update_eeprom = 1;
                    }

                }
                d0 = 10;
                d1 = prepulse / 10;
                d2 = (prepulse % 10);
                cont_pulse = false;
                break;

            case 0:
                if ((!encoder_A) && (encoder_A_prev)) {
                    // A has gone from high to low 
                    if (encoder_B) {
                        // B is high so clockwise  
                        if (pulse++ >= 999) pulse = 0;
                        update_eeprom = 1;
                    } else {
                        // B is low so counter-clockwise      
                        if (pulse-- <= 0) pulse = 999;
                        update_eeprom = 1;
                    }

                }
                d0 = pulse / 100;
                d1 = (pulse % 100) / 10;
                d2 = (pulse % 10);
                cont_pulse = false;
                break;
        }

        //_delay_ms(15);


        if (!(PIND & (1 << BUTTON_PIN))) {
            display++;
            if (display >= 3) display = 0;
            if(update_eeprom){
                EEPROMWriteInt(0x10, pulse);
                EEPROMWriteInt(0x20, prepulse);
                update_eeprom = 0;
            }
            while (!(PIND & (1 << BUTTON_PIN)));
            //_delay_ms(100);
        }



        if (!(PIND & (1 << PEDAL_PIN))) {
            if (cont_pulse) {
                sinusMax();
                LED_ON;
                WELD_ON;
                while (!(PIND & (1 << PEDAL_PIN)));
                
                WELD_OFF;
                LED_OFF;
            } else {
                sinusMax();
                LED_ON;
                WELD_ON;
                my_delay_ms(prepulse);
                WELD_OFF;
                my_delay_ms(10);
                sinusMax();
                WELD_ON;
                my_delay_ms(pulse);
                WELD_OFF;
                //sei();
                LED_OFF;
                my_delay_ms(200);
            }
        }

        encoder_A_prev = encoder_A; // Store value of A for next time 

    }
    return 0;
}





//timer1 overflow

ISR(TIMER1_COMPA_vect) {
    TIMSK &= ~(1 << OCIE1A); //disable this interrupt
    sei(); //enable global interrupts

    switch (digit_on) {
        case 0: //mux first digit
            select_digit(0);
            number(d0);
            break;
        case 1: //mux second digit
            select_digit(1);
            number(d1);
            break;
        case 2: //mux second digit
            select_digit(2);
            number(d2);
            break;
    }

    digit_on++;
    if (digit_on == 3) digit_on = 0;
    TIMSK |= (1 << OCIE1A); //enable tis interrupt
}





//This function will write a 2 byte integer to the eeprom at the specified address and address + 1
void EEPROMWriteInt(int p_address, int p_value) {
    byte lowByte = ((p_value >> 0) & 0xFF);
    byte highByte = ((p_value >> 8) & 0xFF);

    EEPROM.write(p_address, lowByte);
    EEPROM.write(p_address + 1, highByte);
}


//This function will read a 2 byte integer from the eeprom at the specified address and address + 1
unsigned int EEPROMReadInt(int p_address) {
    byte lowByte = EEPROM.read(p_address);
    byte highByte = EEPROM.read(p_address + 1);

    return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
}


void sinusMax()
{ 
  while(digitalRead(zeroCrossPin));
  while(!digitalRead(zeroCrossPin));
  delayMicroseconds(sinusMax_us); // to prevent inrush current, turn-on at the sinus max
}