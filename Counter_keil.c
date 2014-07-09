/*
 READ ME!!
--Down counter program for 8051 in embedded C
--Using seven segment display multiplexing
-- Practical Program, Tested using Keil C5. 
-- Due to keil's limitation delay is generated using builtin timer. (Not very efficient).
--Enable pins of SSD's are connected to Pin 0 and 1 of Port 1
--Port 1 is control
--Port 2 is LSB
--Port 3 is MSB
**By Prathyush**
*/

#include<reg51.h>
#include<assert.h>
#include<stdio.h>
sbit ss1_ctrl=P1^0;
sbit ss2_ctrl=P1^1;
unsigned int i=70,temp,num1,num2,x,y,h;
unsigned int digits[10]={0x40,0xF9,0x24,0x30,0x19,0x12,0x02,0xF8,0x00,0x10}; //refer the above table


void delay (void) // Delay function using Timer 0 for 50ms.
{
TMOD &=0xF0;
TMOD |=0x01;
//TMOD=0x01; //can also be used
ET0 =0;
TH0 =0x3C;
TL0 =0xB0;
TF0 =0;
TR0 =1;
while(TF0==0);
TR0=0;
}


void inf( unsigned int num1, unsigned int num2)
{
P1=0x00;
ss1_ctrl=0;
ss2_ctrl=0;
P2=0x00;
P3=0x00;
ss1_ctrl=1;
P2= digits[num1];
ss2_ctrl=1;
P3=digits[num2];
}


void main()
{
while(i!=-1)
{
temp=i;
num1=temp%10;
temp=temp/10;
num2=temp;
inf(num1,num2);
for(h=0;h<20;h++)
delay();
i--;
}
}
