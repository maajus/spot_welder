/* 
 * File:   definition.h
 * Author: justas
 *
 * Created on December 15, 2014, 7:12 PM
 */
#ifndef MAIN_H
#define MAIN_H

#define  _BV(bit)   (1 << (bit))

#define LED_PIN 4 //PC4
#define WELD_PIN 3
#define PEDAL_PIN 3
#define BUTTON_PIN 2 //PD2
#define BUTTON1_PIN 5 //PD5
#define DIGIT0_PIN 1
#define DIGIT1_PIN 2
#define DIGIT2_PIN 0
#define zeroCrossPin 1

#define SEGMENT1 (PORTB |= (1<<4))
#define SEGMENT1_OFF (PORTB &= ~(1<<4))
#define SEGMENT2 (PORTD |= (1<<7))
#define SEGMENT2_OFF (PORTD &= ~(1<<7))
#define SEGMENT3 (PORTC |= (1<<2))
#define SEGMENT3_OFF (PORTC &= ~(1<<2))
#define SEGMENT4 (PORTC |= (1<<1))
#define SEGMENT4_OFF (PORTC &= ~(1<<1))
#define SEGMENT5 (PORTC |= (1<<0))
#define SEGMENT5_OFF (PORTC &= ~(1<<0))
#define SEGMENT6 (PORTD |= (1<<6))
#define SEGMENT6_OFF (PORTD &= ~(1<<6))
#define SEGMENT7 (PORTC |= (1<<3))
#define SEGMENT7_OFF (PORTC &= ~(1<<3))

#define DIGIT0 (PORTB |= (1<<DIGIT0_PIN))
#define DIGIT1 (PORTB |= (1<<DIGIT1_PIN))
#define DIGIT2 (PORTB |= (1<<DIGIT2_PIN))

#define DIGIT0_OFF (PORTB &= ~(1<<DIGIT0_PIN))
#define DIGIT1_OFF (PORTB &= ~(1<<DIGIT1_PIN))
#define DIGIT2_OFF (PORTB &= ~(1<<DIGIT2_PIN))


#define WELD_ON (PORTB |= (1<<WELD_PIN))
#define WELD_OFF (PORTB &= ~(1<<WELD_PIN))

#define LED_ON (PORTC |= (1<<LED_PIN))
#define LED_OFF (PORTC &= ~(1<<LED_PIN))



void init_pins(){
    
    DDRB |= ((1<<DIGIT0_PIN) | (1<<DIGIT1_PIN)| (1<<DIGIT2_PIN) | (1<<WELD_PIN)); //outputs
    PORTB &= ~((1<<DIGIT0_PIN) | (1<<DIGIT1_PIN)| (1<<DIGIT2_PIN));//write 0
    //PORTB |= ((1<<BUTTON1) | (1<<BUTTON2));
    DDRB |= (1<<4);
    DDRC |= ((1<<0) | (1<<1)| (1<<2)| (1<<3) | (1<<LED_PIN)); //outputs
    DDRD |= ((1<<6) | (1<<7)); //outputs
    
    DDRD &= ~((1<<PEDAL_PIN) | (1<<BUTTON_PIN) | (1<<BUTTON1_PIN));// inputs
    PORTD |=((1<<PEDAL_PIN) | (1<<BUTTON_PIN) | (1<<BUTTON1_PIN));// pull-ups
    //PORTC |= (1<<3);
}

void number(uint8_t nr) {
    switch (nr) {
        case 0:
            SEGMENT1_OFF;
            SEGMENT2;
            SEGMENT3;
            SEGMENT4;
            SEGMENT5;
            SEGMENT6;
            SEGMENT7;
            break;

        case 1:
            SEGMENT1_OFF;
            SEGMENT2_OFF;
            SEGMENT3_OFF;
            SEGMENT4_OFF;
            SEGMENT5;
            SEGMENT6_OFF;
            SEGMENT7;
            break;

        case 2:
            SEGMENT1;
            SEGMENT2;
            SEGMENT3;
            SEGMENT4_OFF;
            SEGMENT5_OFF;
            SEGMENT6;
            SEGMENT7;
            break;

        case 3:
            SEGMENT1;
            SEGMENT2_OFF;
            SEGMENT3;
            SEGMENT4_OFF;
            SEGMENT5;
            SEGMENT6;
            SEGMENT7;
            break;

        case 4:
            SEGMENT1;
            SEGMENT2_OFF;
            SEGMENT3_OFF;
            SEGMENT4;
            SEGMENT5;
            SEGMENT6_OFF;
            SEGMENT7;
            break;

        case 5:
            SEGMENT1;
            SEGMENT2_OFF;
            SEGMENT3;
            SEGMENT4;
            SEGMENT5;
            SEGMENT6;
            SEGMENT7_OFF;
            break;

        case 6:
            SEGMENT1;
            SEGMENT2;
            SEGMENT3;
            SEGMENT4;
            SEGMENT5;
            SEGMENT6;
            SEGMENT7_OFF;
            break;

        case 7:
            SEGMENT1_OFF;
            SEGMENT2_OFF;
            SEGMENT3_OFF;
            SEGMENT4_OFF;
            SEGMENT5;
            SEGMENT6;
            SEGMENT7;
            break;

        case 8:
            SEGMENT1;
            SEGMENT2;
            SEGMENT3;
            SEGMENT4;
            SEGMENT5;
            SEGMENT6;
            SEGMENT7;
            break;

        case 9:
            SEGMENT1;
            SEGMENT2_OFF;
            SEGMENT3;
            SEGMENT4;
            SEGMENT5;
            SEGMENT6;
            SEGMENT7;
            break;
        case 10:
            SEGMENT1;
            SEGMENT2;
            SEGMENT3_OFF;
            SEGMENT4;
            SEGMENT5_OFF;
            SEGMENT6;
            SEGMENT7;
            break;
        case 11:
            SEGMENT1;
            SEGMENT2;
            SEGMENT3_OFF;
            SEGMENT4;
            SEGMENT5_OFF;
            SEGMENT6;
            SEGMENT7_OFF;
            break;
            
        case 12:
            SEGMENT1_OFF;
            SEGMENT2_OFF;
            SEGMENT3_OFF;
            SEGMENT4_OFF;
            SEGMENT5_OFF;
            SEGMENT6_OFF;
            SEGMENT7_OFF;
            break;
    }

}

void select_digit(uint8_t digit){
    
    switch(digit){
        case 0:
            DIGIT0;
            DIGIT1_OFF;
            DIGIT2_OFF;
            break;
        case 1:
            DIGIT0_OFF;
            DIGIT1;
            DIGIT2_OFF;
            break;
        case 2:
            DIGIT0_OFF;
            DIGIT1_OFF;
            DIGIT2;
            break;
    }
}



/*
   1 - PB4
 * 2 - PD7
 * 3 - PC2
 * 4 - PC1
 * 5 - PC0
 * 6 - PD6
 * 7 - PC3


 *      ____6___
 *      |      |
 *     4|      |7
 *      |___1__|
 *      |      |
 *     2|      |5
 *      |______|
 *          3
 * 
 * 
 * 
 */


static unsigned int digits[14] ={
    ~0b11111101, //0
    ~0b10100001, //1
    ~0b11001111, //2
    ~0b11101011, //3
    ~0b10110011, //4
    ~0b01111011, //5
    ~0b01111111, //6
    ~0b11100001, //7
    ~0b11111111, //8
    ~0b11111011, //9
    0b11111100, //- 
    ~0b01011101, //C
    ~0b10110111, //H
    0b11111111 //blank
};

void my_delay_ms(int n) {
 while(n--) {
  _delay_ms(1);
 }
}



void select_digit(uint8_t digit);
void display_numbers(uint8_t digit2, uint8_t digit1);
void beep(uint8_t duration);
void init_pins();

#endif /* DEFINITION_H */