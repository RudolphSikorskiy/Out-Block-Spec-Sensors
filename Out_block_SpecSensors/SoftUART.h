/*
 * SoftUART.h
 *
 * Created: 22.06.2017 9:13:39
 *  Author: N
 */ 


#ifndef SOFTUART_H_
#define SOFTUART_H_

#include "main.h"

#define CheckBit(reg,bit) (reg&(1<<bit)) //n=PIND&(1<<RX_PIN);

#define TX_PIN 3
#define RX_PIN 2
#define BTREIT 9600 //������� � 9600, ��� ������� ����� �������
#define MLN 1000000L //�������

void SOFT_UART_init();				// ������������� ����������� UART
void SOFT_UART_bit( char b);		// �������� ����
void SOFT_UART_byte( char a);		// �������� �����
void SOFT_UART_send( char *str);	// �������� ������
unsigned char SOFT_UART_read(void);		// ����� ������
char *OperationResponse(void);				// ������� �������� ������ �������



#endif /* SOFTUART_H_ */