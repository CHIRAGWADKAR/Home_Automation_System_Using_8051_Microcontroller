#include<reg51.h>
sbit load1=P1^0;
sbit load2=P1^1;
sbit load3=P1^2;
sbit load4=P1^3;

void main() {
unsigned char x;
SCON=0X50;
TMOD=0X20; // Timer 1 Mode 2
TH1=-3; // baud rate 9600
TR1=1; // Timer 1
	
while (1) {
	while(RI==0);
	x=SBUF;
	SBUF=x;
	while(TI==0);
	// TI=0;
	// RI=0;
	if(x=='1')
	{
	load1=1; // load1 off
	}
	if(x=='2')
	{
	load1=0; // load1 on
	}
	if(x=='3')
	{
	load2=1; // load2 off
	}
	if(x=='4')
	{
	load2=0; // load2 on
	}
	if(x=='5') 
	{
	load3=1; // load3 off
	}
	if(x=='6')
	{
	load3=0; // load3 on
	}
	if(x=='7')
	{
	load4=1; // load4 off
	}
	if(x=='8'){
	load4=0; // load4 on
	}
	if(x=='9')
	{
	load1=load2=load3=load4=1; // all loads off
	}
	if(x=='0')
	{
	load1=load2=load3=load4=0; // all loads on
	}
}
}