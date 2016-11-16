#include<reg51.h>

sbit atcl = P2^1;
sbit atct = P2^0;
sbit in = P0^0;
sbit landstat = P1^1;
sbit rqsterm = P0^2;
sbit clrterm = P1^0;
sbit t1 =P3^0;
sbit t2 =P3^1;
sbit t1s =P3^3;
sbit t2s =P3^4;
sbit toff =P3^6;
sbit trueland = P2^4;
sbit falseland = P2^5;

void delay350ms();
void main(){
  /*-----------------------------LANDING-------------------------------*/

  //po.o goes high when the plane is incoming and sends the status to p2.1
  //p2.1 is like a a person who checks the status of p1.1 which signals the airplane to land or not -----1__LAND----- otherwise 0
  //p0.2 senses the planes and sends the status to p2.1
  //p2.1 checks the stutus of p3.0,1 and send the status to p1.1 if 1 to terminal

  unsigned int i;
  in = 1;
  t1, t2 = 1;
  landstat =1;
  t1s, t2s =1;                                     //for takeoff signals from t1 and t2
  while(1){
    if(in == 1){                                   //check if plane is incoming when yes
      atcl = 1;                                    // send the incoming signal to atcl
      delay350ms();
      if((t1 & t2)== 0){                           //checking status of terminals, terminals go high when a plane is present
        landstat = 1;
      }
      else if((t1 & t2) ==1){
        landstat = 0;
      }
      delay350ms();
      if(landstat ==1){
        for(i=0;i<10;i++){
          trueland = ~trueland ;
          delay350ms();
        }
        trueland = 1;                                 // Keep the YES to land signal high after blinking GREEN LED
        P0^4 = t1;                                    // lights in the plane to direct to the free terminal
        P0^5 = t2;
        }
      else
      {
        for(i=0;i<10;i++){
          falseland= ~ falseland;
          delay350ms();
          }
          falseland = 1;                                // Keep the NO to land signal high after blinking BLUE LED
      }
    }

  /*-----------------------------TAKEOFF-------------------------------*/

  /* p3.0 and p3.1 are terminals
  terminal is 1 if plane is there (use IR sensors)
  if plane wants to leave signal 1 from terminal to p2.0
  if ok, p3.3 or p3.4 are 1 ( for t0 and t1 respectively) -> priority to p3.1
  if p0.0==1 or p2.1 == 1 or p0.1 == 0 -> wait (p3.6==0) else takeoff (p3.6==1) */
  toff = 0;
  while((t1 | t2)==1){                        // only if there is a plane in either of the terminals
      if((t1s| t2s)==1){
        atct = 1;
      }
      if(in==1){
        toff = 0;
        for(i =0;i <5; i++)                 // toff stays for minimum of 2 secs
        delay350ms();
      }
      else{
        for(i= 0;i<5;i++){                   // Blink and stay on for a few seconds
          toff = ~toff;
          delay350ms();
        }
        for(i=0;i<5;i++){
        toff = 1;
        }
      }
  }

  }

}
void delay350ms(){
  unsigned int i;
  TMOD = 0x01;
  for(i = 0;i< 5; i++){
    TLO = 0x00;
    TH0 = 0x00;
    TR0 = 1;
    while(TF0 == 0);
    TR0 = 0;
    TF0 = 0;
  }
}
