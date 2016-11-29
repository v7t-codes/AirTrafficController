#include<reg51.h>

sbit atcl = P2^1;
sbit atct = P2^0;
sbit in = P0^0;
//sbit landstat = P0^7;
//sbit rqsterm = P1^0;
//sbit clrterm = P1^7;
sbit t1 =P3^0;
sbit t2 =P3^1;
sbit t1s =P0^3;
sbit t2s =P0^4;
sbit toff =P2^7;
sbit trueland = P2^4;
sbit falseland = P2^5;

//sbit yes=P3^5;

unsigned char x;

//sbit a = P0^4;
//sbit b=P0^5;

void landing();
void takeoff1();
void takeoff12();
void takeoff2();
void blink();
void delay();

void landing() 
{
	
atcl=1;
atct=0;
	if((t1 & t2)==1)	   	
	{
//	blink(falseland) ;
for(x=0;x<10;x++)
	{
		falseland=~falseland;
		delay();
	}   	
	 
	
}
else 
	{
		toff=0;
	
//	blink(trueland);
		for(x=0;x<10;x++)
	{
		trueland=~trueland;
		delay();
	}
	delay();
	toff=1;
	//rqsterm=1;
	if((t1==0)|((t1==0)&(t2==0)))
	{
//	blink(t1);
		for(x=0;x<10;x++)
	{
		t1=~t1;
		delay();
	}
	delay();
	t1=1;
	}
	else
	{
//	blink(t2);
		for(x=0;x<10;x++)
	{
		t2=~t2;
		delay();
	}
	delay();
	
	t2=1;
	}
}
	atcl=0;
	in=0; 

}
void takeoff1()
{
if(t1)
{
atct=1;
//if((t1s==1) & (t2s==0))
{
//blink(t1);
	for(x=0;x<10;x++)
	{
		t1=~t1;
		delay();
	}
	toff=1;
delay();
	toff=0;
	t1=0;
		atct=0;
	t1s=0;
	
}
}
}
void takeoff2()
{
	if(t2)
	{
	atct=1;
//else if((t2s==1) & (t1s==0))
//blink(t2);
	for(x=0;x<10;x++)
	{
		t2=~t2;
		delay();
	}
t2=0;
toff=1;
delay();
toff=0;
atct=0;
t2s=0;
}
}
void takeoff12()
{
	if(t1)
	takeoff1();
	delay();
	delay();
	if(t2)
	takeoff2();
	}
void main()
{
AGAIN:	
	t1s=0;
t2s=0;
  
in=0; 
atct =0;
atcl=0;	
while(1)
{	
	if(in)
	{
	landing();
    goto AGAIN;
	}
if(t1s)
{	
 takeoff1();
 delay();
 if(!in)
 {
 toff=1;
 }
 else
 {
 landing();
delay();
 }
	 goto AGAIN;
 }
 else if(t2s)
{	
 takeoff2();
 delay();
 if(!in)
 {
 toff=1;
 }
 else
 {
 landing();
 delay();
 }
  goto AGAIN;
 }
 else if((t1s)&&(t2s))
{	
 takeoff12();
 delay();
 if(!in)
 {
 toff=1;
 }
 else
 {
 landing();
 delay();
 }
  goto AGAIN;
 }
 else
	 goto AGAIN;
 }
}
void delay()
{
  unsigned int i;
  TMOD = 0x01;
   for(i=0;i<5;i++)
	{
    TL0 = 0x00;
    TH0 = 0x00;
    TR0 = 1;
    while(TF0 == 0);
    TR0 = 0;
    TF0 = 0;
}
}
