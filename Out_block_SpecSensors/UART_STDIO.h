/*
 * UART_STDIO.h
 *
 * Created: 07.07.2017 14:51:55
 *  Author: N
 */ 


#ifndef UART_STDIO_H_
#define UART_STDIO_H_


#include "main.h"


#define LEN 32
char buffer[LEN];

register unsigned char IT asm("r16");
volatile unsigned char done;
volatile unsigned char IDX;

void USARTinit(void);
int uart_putchar(char c, FILE *stream);
void clearStr(char* str);
void blink13(uint8_t count);



#endif /* UART_STDIO_H_ */