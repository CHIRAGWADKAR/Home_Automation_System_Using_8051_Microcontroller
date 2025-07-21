#include<reg51.h>

// Lamp Relays
sbit lamp1 = P1^0;
sbit lamp2 = P1^1;
sbit lamp3 = P1^2;
sbit lamp4 = P1^3;

// Stepper Motor
sbit coil1 = P2^1;
sbit coil2 = P2^2;
sbit coil3 = P2^3;
sbit coil4 = P2^4;

void delay(unsigned int time){
    unsigned int i,j;
    for(i=0;i<time;i++)
        for(j=0;j<1275;j++);
}

void stepper_cw(){
    unsigned int i;
    for(i=0; i<100; i++){
        coil1=1; coil2=0; coil3=0; coil4=0; delay(10);
        coil1=0; coil2=1; coil3=0; coil4=0; delay(10);
        coil1=0; coil2=0; coil3=1; coil4=0; delay(10);
        coil1=0; coil2=0; coil3=0; coil4=1; delay(10);
    }
}

void stepper_acw(){
    unsigned int i;
    for(i=0; i<100; i++){
        coil1=0; coil2=0; coil3=0; coil4=1; delay(10);
        coil1=0; coil2=0; coil3=1; coil4=0; delay(10);
        coil1=0; coil2=1; coil3=0; coil4=0; delay(10);
        coil1=1; coil2=0; coil3=0; coil4=0; delay(10);
    }
}

void main(){
    unsigned char x;
    SCON = 0x50; // UART Mode 1
    TMOD = 0x20;
    TH1 = -3;
    TR1 = 1;

    lamp1=lamp2=lamp3=lamp4=1;
    coil1=coil2=coil3=coil4=0;

    while(1){
        while(RI==0);
        x=SBUF;
        RI=0;
        SBUF=x;
        while(TI==0);
        TI=0;

        // Lamp control
        if(x=='1') lamp1=0;
        if(x=='2') lamp1=1;
        if(x=='3') lamp2=0;
        if(x=='4') lamp2=1;
        if(x=='5') lamp3=0;
        if(x=='6') lamp3=1;
        if(x=='7') lamp4=0;
        if(x=='8') lamp4=1;
        if(x=='9') {lamp1=lamp2=lamp3=lamp4=0;} // All ON
        if(x=='0') {lamp1=lamp2=lamp3=lamp4=1;} // All OFF

        // Stepper control
        if(x=='s' || x=='S') stepper_cw();
        if(x=='a' || x=='A') stepper_acw();
    }
}