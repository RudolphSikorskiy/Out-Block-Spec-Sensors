#include "UART_STDIO.h"

static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

 void USARTinit(void)
 {	 
	 UBRRL=103;
	 UCSRB=(1<<TXEN)|(1<<RXEN)|(1<<RXCIE);
	 UCSRC=(1<<URSEL)|(3<<UCSZ0);

	 DDRB |= (1<<PB5); //  pinMode(13,OUTPUT);

	 blink13(3); //ready indication
	 IDX=0;
	 done=0;
	 sei();

	 stdout = &mystdout;
}
 

int uart_putchar(char c, FILE *stream)
{
   if (c == '\n')
   uart_putchar('\r', stream);
   loop_until_bit_is_set(UCSRA, UDRE);
   UDR = c;
   return 0;
}

void clearStr(char* str)
{
        for(IT=0;IT<LEN;IT++)
                str[IT]=0;
}
/*
void writeSerial(char* str)
{
        IT=0; while (str[IT] != 0 && IT < LEN)
        {
                while(!(UCSRA&(1<<UDRE))){};
                UDR = str[IT];
                IT++;
        }
}
*/
ISR(USART_RXC_vect)
{
        char bf= UDR;
        buffer[IDX]=bf;
        IDX++;

        if (bf == '*' || IDX >= LEN)
        {
                IDX=0;
                done=1;
				printf("%s",buffer);
				
        }
		//printf("%c",buffer[IDX]);

}

void blink13(uint8_t count)
{
        PORTB |= (1<<PB5);
        count =(count <<1);count--; //count=(count*2)-1;
        for (IT=0;IT<count;IT++)
        {
                //_delay_ms(500);
                PORTB ^= (1<<PB5);
        };
};

