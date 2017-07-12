//#define F_CPU 16000000L

#include "main.h"
#define A0 -5.057972711832
#define X0 adc/1000
#define C0 165.817620190823

#define A1 -5.05797271
#define X1 adc/1000
#define C1 164.80602565

//-5.05797271*x+164.80602565
char* SUB = "NO2";
#define MOLAR 46.0055
unsigned int x=0;
char* fromparse = "";
char* SN = "";
char* PPB = "";
char* TEMP = "";
char* HYDR = "";
char* ADCppb = "";
char* ADCtemp = "";
char* ADChydr = "";
char* HOUR = "";
char* MIN = "";
char* SEC = "";
//char MG0[8] ;
//char MG1[8] ;
char* Trash = "";
unsigned int trigger = 0;
double mgStok = 0;
double mgPrivat0 = 0;
double mgPrivat1 = 0;
unsigned int ppb = 0;
unsigned int tmp = 0;
unsigned int adc = 0;
//-----------------------------------------------------------------------//

void DataPackageFormation(char data[]);
void TakeConcentration(void);
int my_getnbr(char *str)
{
	int           result;
	int           puiss;

	result = 0;
	puiss = 1;
	while (('-' == (*str)) || ((*str) == '+'))
	{
		if (*str == '-')
		puiss = puiss * -1;
		str++;
	}
	while ((*str >= '0') && (*str <= '9'))
	{
		result = (result * 10) + ((*str) - '0');
		str++;
	}
	return (result * puiss);
}

//-----------------------------------------------------------------------//

int main(void)
{
	
	USARTinit(); //207 -> 9600 для 16Mhz
	SOFT_UART_init();
	sei();
	//printf("TIME\tMg\\m3\tPPB\tMg1\\m3\tMg2\\m3\tTEMP\tHYDR\tADCppb\n\r");
	
	while(1)
	{
		//USART_Transmit_str("OK!");
		
		TakeConcentration();
		_delay_ms(1000);
		
		
	}
	return 0;
}

//-----------------------------------------------------------------------//

void DataPackageFormation(char data[])
{
	//USART_Transmit_str(data);
	//USART_Transmit('\r');
	char *pch = strtok (data," ,"); //во втором параметре указаны разделители (пробел, запятая, точка)
	while (pch != NULL) //пока есть лексемы pch !== NULL а сейчас проверяем первые 4
	{	//		0		1	2	3	4		5		6	7	 8	 9	 10
		//111116010250, 13, 25, 51, 13143, 27064, 30330, 00, 03, 43, 30
		switch ( trigger )
		{
			//----------------------------//
			
			case 0:
			SN = pch;
			pch = strtok (NULL, " ,");
			trigger++;
			break;
			
			//----------------------------//
			
			case 1:
			PPB = pch;
			pch = strtok (NULL, " ,");
			trigger++;
			break;
			
			//----------------------------//
			
			case 2:
			TEMP = pch;
			pch = strtok (NULL, " ,");
			trigger++;
			break;
			
			//----------------------------//
			
			case 3:
			HYDR = pch;
			pch = strtok (NULL, " ,");
			trigger++;
			break;
			
			//----------------------------//
			
			case 4:
			ADCppb = pch;
			pch = strtok (NULL, " ,");
			trigger++;
			break;
			
			//----------------------------//
			
			case 5:
			ADCtemp = pch;
			pch = strtok (NULL, " ,");
			trigger++;
			break;
			
			//----------------------------//
			
			case 6:
			ADChydr = pch;
			pch = strtok (NULL, " ,");
			trigger++;
			break;
			
			//----------------------------//
			
			case 8:
			HOUR = pch;
			pch = strtok (NULL, " ,");
			trigger++;
			break;
			
			//----------------------------//
			
			case 9:
			MIN = pch;
			pch = strtok (NULL, " ,");
			trigger++;
			break;
			
			//----------------------------//
			
			case 10:
			SEC = pch;
			SEC[2]= '\0';
			//SEC[3]= '\0';
			pch = strtok (NULL, " ,");
			trigger++;
			break;
			
			//----------------------------//
			
			
			default:
			Trash = pch;
			pch = strtok (NULL, " ,");
			trigger++;
			break;
		}
		
	}
	trigger = 0;
	
	
}

//-----------------------------------------------------------------------//
//-----------------------------------------------------------------------//

void TakeConcentration(void)
{
	SOFT_UART_byte(' ');
	
	fromparse = OperationResponse();
	
	DataPackageFormation(fromparse);
	
	if (PPB[0]=='-')
	{
		ppb = 0;
		
	}
	else
	{
		ppb = my_getnbr(PPB);
		
	}
	if (ADCppb[0]=='\0')
	{
		adc = 0;
		
	}
	else
	{
		//ADCppb[5] = '\0';
		//adc = atoi(ADCppb);
		adc = my_getnbr(ADCppb);
		//sscanf(ADCppb, "%d", &adc);
		//adc  = 32783;
		//adc  = 32768;
		//printf("%c%c%c%c%c \t %d\n",ADCppb[0],ADCppb[1],ADCppb[2],ADCppb[3],ADCppb[4],adc);
	}
	
	tmp = atoi(TEMP);
	
	mgStok = MOLAR*0.000001*(ppb)/(8.314472*(tmp+273.15)/101325);
	mgPrivat0 = A0*X0+C0;					//Линейное уравнение
	mgPrivat1 = A1*X1+C1;
	if (HOUR[0]!='\0')
	{
		printf("%s:%s:%s \t %.4f \t %s \t %.4f \t %.4f \t %s \t %s \t %s \n",HOUR,MIN,SEC,mgStok,PPB,mgPrivat0,mgPrivat1,TEMP,HYDR,ADCppb);
		
	}
	
	
}

//-----------------------------------------------------------------------//