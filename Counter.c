/*
 READ ME!!
--Down counter program for 8051 in embedded C
--Using Seven Segment Display Multiplexing
--Theoretical Detailed Program.
--Enable pins of SSD's are connected to Pin 0 and 1 of Port 1
--Port 1 is control
--Port 2 is LSB
--Port 3 is MSB
**By Prathyush**

General Information:

BCD[7]= Hexadecimal
7 segment interfacing 

Format:
00000000
hgfedcba
     
	 a
     _ 
 f | _ | b
     g
 e | _ | c
     d      .h
   
Digit  --  Binary     --  Hexa
0          0100 0000 	  40H                     
1          1111 1001      F9H
2		   0010 0100      24H
3		   0011 0000 	  30H
4		   0001 1001	  19H
5		   0001 0010	  12H
6		   0000 0010	  02H
7		   1111 1000	  F8H
8		   0000 0000	  00H
9  		   0001 0000	  10H


Program flow:

main function
	--initialization function
	--calculation
		--delay function
*/

#include<reg51.h> 
#include<assert.h> // used for assert functions
#include<stdio.h>
#include<delay.h>
#include<time.h>
sbit ss1_ctrl=P1^0;// Seven Segment Display Control 1
sbit ss2_ctrl=P1^1;// Seven Segment Display Control 2
unsigned int i,temp,num1,num2,x,y;
unsigned int digits[10]={0x40,0xF9,0x24,0x30,0x19,0x12,0x02,0xF8,0x00,0x10}; //refer the above table
void delay_ms(int ms);//Declare function to override missing ANSI function prototype *Body missing, to be filled*

//initialization part
void init()
{
P1=0x00;
P2=0x00;
P3=0x00;
ss1_ctrl=0;
ss1_ctrl=0;
TMOD=0x01;
TH0=0xff;
TR0=1;
}


//Delay part 
/*Delay can be generated in three ways
1.Using built in timer method
2.Using builtin delay_ms(int sec) function (More efficient method)
3.Using looping technique and calculating machine cycles
*/


/*
//1.Using built in timer method
//Delay function using builtin timers generating 50ms delay
void delay(unsigned int del) 
{
unsigned int m;
	for(m=0;m<del;m++)
	{
	TMOD &=0xF0;//for more efficient use
	TMOD |=0x01;//for more efficient use
	//TMOD=0x01; //can be used
	ET0 =0;// Enables/disables Timer0
	TH0 =0x3C;
	TL0 =0xB0;
	TF0 =0;
	TR0 =1;
	while(TF0==0);
	TR0=0;
	}
}
*/

//2. Use delay_ms(int sec) or msdelay(int ms) as provided by libraries (More Efficient)

/*
//3.Using looping technique and calculating machine cycles
void delay(unsigned int del)
{
for(j=0;j<del;j++)
	{
	for(k=0;k<1000;k++)
		{
		for(k=0;k<1275;k++)
		}
	}
}
*/

//interfacing part
void inf( unsigned int* num1, unsigned int* num2) //pointers can be used for multiple return statements (if return needed)
{
//Check if pointer is pointing to null
assert(num1);
assert(num2);
//assign the pointers
x=*num1;
y=*num2;
//initialize all the digits and controls to 0
ss1_ctrl=0;
ss2_ctrl=0;
P2=0x00;
P3=0x00;
//condition
ss1_ctrl=1;
P2= digits[x];
ss2_ctrl=1;
P3=digits[y];
}

//Main part
void main()
{
init();// initialize parameters
for(i=70;i>=0;i--)//change the value of i for your requirements
	{
	temp=i;
	num1=temp%10;//to get LSB
	temp=temp/10;//to get MSB
	num2=temp;
	inf(&num1,&num2);//interfacing
	delay_ms(1000);// built in delay function
	//delay(1);//delay function using C/builtin timer! Be careful while removing comments!!
	}
}
