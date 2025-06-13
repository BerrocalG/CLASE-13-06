#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL

void config_timer(void){
  TCCR0A|=(1<<WGM01);
  TCCR0B|=(1<<CS01);
}
void delay_10us(void){
  OCR0A=20;
  TCNT0=0;
  while(!(TIFR0&(1<<OCF0A)));
  TIFR0|=(1<<OCF0A);
}
unsigned char b=50;
void pwm(void){
  DDRB|=0x01;
  PORTB&=~0x01;
  config_timer();
}
void pwm(unsigned char b){
  PORTB|=0x01;
  for(int i=0; i<100+b;i++){
    delay_10us();
  }
  PORTB&=~0x01;
  for(int i=0;i<1900-b;i++){
    delay_10us();
  }
}

void config(void){
  EICRA|=(1<<ISC00)|(1<<ISC01); //Se activa con el flanco de bajada
  EIMSK|=(1<<INT0);
  DDRD &=~(0X04);
}
int a=0;
ISR(INT0_vect){
  if (a>60){
    a=0;
    PORTB^=0x01;
   }
 a++;
}
int main(void){
  DDRB|=0x01;
  config();
  sei();
  while(1){
  }
}