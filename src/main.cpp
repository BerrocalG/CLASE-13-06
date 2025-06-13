#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
/*
//ejercicio 4: controlar intensidad de corriente
void config_intext(void){
  EIMSK|=(1<<INT0);
  EICRA|=(1<<ISC01);
  DDRD&=~(1<<PD2);
}

void config_ADC(void){
  ADCSRA|=(1<<ADEN)|(1<<ADIE)|(1<<ADPS2);
  ADMUX|=(1<<REFS0);
}

unsigned char porcentaje=0;

ISR(ADC_vect){
  porcentaje=ADC*(100.0/1023.0);
  OCR0A=porcentaje*(1.2)+5;
  ADCSRA|=(1<<ADSC);
}

void config_timer(void){
  TCCR0A|=(1<<WGM01);
}

ISR(INT0_vect){
  PORTB|=0x01;
  TCNT0=0;
  TCCR0B|=(1<<CS02)|(1<<CS00);
  while(!(TIFR0&(1<<OCF0A)));
  TIFR0|=(1<<OCF0A);
  PORTB&=~0x01;
  TCCR0B&=~((1<<CS02)|(1<<CS00));
}

int main(void){
  config_ADC();
  config_timer();
  config_intext();
  sei();
  ADCSRA|=(1<<ADSC);
  DDRB|=0x01;
  while(1){
  }
}
  */

  //ejercicio 5 fast pwm
void config_ADC(void){
  ADCSRA|=(1<<ADEN)|(1<<ADIE)|(1<<ADPS2);
  ADMUX|=(1<<REFS0);
}

unsigned char porcentaje=0;

ISR(ADC_vect){
  porcentaje=ADC*(255.0/1023.0);
  OCR0A=(unsigned char)(porcentaje);
  ADCSRA|=(1<<ADSC);
}

void config_timer(void){
  TCCR0A|=(1<<WGM01)|(1<<WGM00)|(1<<COM0A1);
  TCCR0B|=(1<<CS02)|(1<<CS00);
  OCR0A=0;
  DDRD|=(1<<PD6);
}

int main(void){
  config_ADC();
  config_timer();
  DDRB|=0x01;
  sei();
  ADCSRA|=(1<<ADSC);
  while(1){
  }
}