#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define Z 10000
unsigned int takt = 0;
unsigned int sek = 0;
unsigned int min=0;
unsigned int hour=0;
unsigned int razn1=0;
unsigned int razn2=0;
unsigned int razn3=0;
unsigned int razn4=0;
unsigned int newtime=0;

int go [10] = {
         0b00111111, //0
         0b00000110, //1
         0b01011011, //2
         0b01001111, //3
         0b01100110, //4
         0b01101101, //5
         0b01111101, //6
         0b00000111, //7
         0b01111111, //8
         0b01101111 //9
};

ISR(TIMER2_OVF_vect){
        takt++;
        if (takt>=488){sek++; takt=0x00;}
        if (sek>=60) {min++; sek=0x00;}
        if (min>=60) {hour++; min=0x00;}
        if (hour>=24) {hour=0;}
        razn1 = hour%100/10;
        razn2 = hour%10;
        razn3 = min%100/10;
        razn4 = min%10;
}


int main(void)
{
    DDRD = 0b11111111;
    DDRC = 0b00001111;
    DDRB = 0b00000000;
    PORTB = 0b00001111;

    TIMSK |= (1<<TOIE2);
    TCCR2 |= (1<<CS22)|(1<<CS20); // деление частоты на 1024 = 16000000/128 т.к. асин-хронный = 125000/256 = 488
    sei();

    while (1)
    {
        if(PINB == 0b00001110){
            hour++;
            if (hour>=24) {hour=0;}
            _delay_ms(100);
        }
        if(PINB == 0b00001101){
            hour--;
            if (hour<0) {hour=24;}
            _delay_ms(100);
        }
        if(PINB == 0b00001011){
            min++;
            if (min>=60) {min=0;}
            _delay_ms(100);
        }
        if(PINB == 0b00000111){
            min--;
            if (min<0) {min=59;}
            _delay_ms(100);
        }

        if(newtime==1){PORTC = 0b00000001; PORTD = go[razn1];}
        if(newtime==2){PORTC = 0b00000010; PORTD = go[razn2];}
        if(newtime==3){PORTC = 0b00000100; PORTD = go[razn3];}
        if(newtime==4){PORTC = 0b00001000; PORTD = go[razn4];}
        newtime++;
        if (newtime>=5){newtime=0;}
        _delay_ms(10);
    }
}
