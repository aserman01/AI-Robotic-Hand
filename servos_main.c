#include <MKL25Z4.H>
#include <stdio.h>
#include <math.h>
#include <string.h>


void servo_init(void);
void servo_angle(int angle, int servo_num);
uint8_t recive(void);
void uart_init(void);
int finger_detect(int recieved);
int turn_detect(int recieved);
void Delay(volatile unsigned int time_del);


int main(void){
    //int i;
    int rec_temp;
    int turn_det_v;
    int finger_det_v;
     int recieved = 0;
    uart_init();
    servo_init();
  servo_angle(45,0x0);
    servo_angle(45,0x1);
    servo_angle(45,0x2);
    servo_angle(45,0x3);
    servo_angle(45,0x4);
    while(1){
        recieved = recive();
        if(recieved == 0xFF){
        int i = 0;
         for( i = 0; i < 5; i++){
             recieved = 0;
             recieved = recive();

                if(finger_detect(recieved) == 0x0 & turn_detect(recieved) == 0x1){
                     servo_angle(30,0x0);}

                 if(finger_detect(recieved) == 0x0 & turn_detect(recieved) == 0x2){
                     servo_angle(65,0x0);}

                 if(finger_detect(recieved) == 0x0 & turn_detect(recieved) == 0x4){
                     servo_angle(180,0x0);}

                if(finger_detect(recieved) == 0x1 & turn_detect(recieved) == 0x1){
                     servo_angle(45,0x1);}

                 if(finger_detect(recieved) == 0x1 & turn_detect(recieved) == 0x2){
                     servo_angle(120,0x1);}

                 if(finger_detect(recieved) == 0x1 & turn_detect(recieved) == 0x4){
                     servo_angle(180,0x1);}

                if(finger_detect(recieved) == 0x2 & turn_detect(recieved) == 0x1){
                     servo_angle(30,0x2);}

                 if(finger_detect(recieved) == 0x2 & turn_detect(recieved) == 0x2){
                     servo_angle(90,0x2);}

                 if(finger_detect(recieved) == 0x2 & turn_detect(recieved) == 0x4){
                     servo_angle(180,0x2);}

                if(finger_detect(recieved) == 0x3 & turn_detect(recieved) == 0x1){
                     servo_angle(45,0x3);}

                 if(finger_detect(recieved) == 0x3 & turn_detect(recieved) == 0x2){
                     servo_angle(90,0x3);}

                 if(finger_detect(recieved) == 0x3 & turn_detect(recieved) == 0x4){
                     servo_angle(180,0x3);}

                if(finger_detect(recieved) == 0x4 & turn_detect(recieved) == 0x1){
                     servo_angle(45,0x4);}

                 if(finger_detect(recieved) == 0x4 & turn_detect(recieved) == 0x2){
                     servo_angle(100,0x4);}

                 if(finger_detect(recieved) == 0x4 & turn_detect(recieved) == 0x4){
                     servo_angle(180,0x4);}
                 recieved = 0;
                 }
             }
        }

    }



void servo_init(void){

SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;  //PORT D     enable

PORTD->PCR[0] = 0X0400;
PORTD->PCR[1] = 0X0400;
PORTD->PCR[2] = 0X0400;
PORTD->PCR[3] = 0X0400;
PORTD->PCR[4] = 0X0400;


SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;
SIM->SOPT2 |= 0x01000000; /* Counter clock for TPM */
TPM0->SC = 0; /* disable timer */

TPM0->CONTROLS[0].CnSC = 0x20 | 0x08; /* center-aligned, pulse high */
TPM0->CONTROLS[1].CnSC = 0x20 | 0x08; /* center-aligned, pulse high */
TPM0->CONTROLS[2].CnSC = 0x20 | 0x08; /* center-aligned, pulse high */
TPM0->CONTROLS[3].CnSC = 0x20 | 0x08; /* center-aligned, pulse high */
TPM0->CONTROLS[4].CnSC = 0x20 | 0x08; /* center-aligned, pulse high */

}

void servo_angle(int angle, int servo_num){

    int duty, mod, cnv;

    // servo 1
    if(servo_num == 0x0){
    mod = 20.97152*1000000/(2*16*50);
    duty = (13*angle - 2*angle + 360) / 180;
    cnv = duty*mod/100;


    TPM0->SC = 0; /* disable timer */
    TPM0->MOD = mod;
    TPM0->CONTROLS[0].CnV = cnv;
    TPM0->SC = 0x0C | 0x20;}


    // servo 2
    if(servo_num == 0x1){
    mod = 20.97152*1000000/(2*16*50);
    duty = (13*angle - 2*angle + 360) / 180;
    cnv = duty*mod/100;

    TPM0->MOD = mod;
    TPM0->CONTROLS[1].CnV = cnv;
  TPM0->SC = 0x0C | 0x20;}

    // servo 3
    if(servo_num == 0x2){
    mod = 20.97152*1000000/(2*16*50);
    duty = (13*angle - 2*angle + 360) / 180;
    cnv = duty*mod/100;

    TPM0->MOD = mod;
    TPM0->CONTROLS[2].CnV = cnv;
    TPM0->SC = 0x0C | 0x20;}

    // servo 4
    if(servo_num == 0x3){
    mod = 20.97152*1000000/(2*16*50);
    duty = (13*angle - 2*angle + 360) / 180;
    cnv = duty*mod/100;

    TPM0->MOD = mod;
    TPM0->CONTROLS[3].CnV = cnv;
  TPM0->SC = 0x0C | 0x20;}

    // servo 5
    if(servo_num == 0x4){
    mod = 20.97152*1000000/(2*16*50);
    duty = (13*angle - 2*angle + 360) / 180;
    cnv = duty*mod/100;

    TPM0->MOD = mod;
    TPM0->CONTROLS[4].CnV = cnv;
    TPM0->SC = 0xF;
    }
    //Delay(2000000);

}

int finger_detect(int recieved){
int servo_num;
servo_num = 0x7 & (recieved >> 5);
return servo_num;}

int turn_detect(int recieved){
int turn_angle;
turn_angle = 0x1F & recieved;
return turn_angle;}

void uart_init(void){

// Enable PORTA clock
SIM->SCGC5 |= SIM_SCGC5_PORTA(1);

PORTA_PCR1|=  PORT_PCR_MUX(2); /* PTA1 as ALT2 (UART0) */
PORTA_PCR2 |=  PORT_PCR_MUX(2); /* PTA2 as ALT2 (UART0) */

    // Select MCGFLLCLK as UART0 clock
SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);

// Enable UART0 Clock
SIM->SCGC4 |= SIM_SCGC4_UART0(1);

// Configure Baud Rate as 115200
UART0->BDL = 0x0B;
UART0->BDH = 0x0;

// Configure Serial Port as 8-N-1
// (8 data bits, No parity and 1 stop bit)
UART0->C1  = 0x00;

// Configure Tx/Rx Interrupts
UART0->C2  |= UART_C2_TIE(0);  // Tx Interrupt disabled
UART0->C2  |= UART_C2_TCIE(0); // Tx Complete Interrupt disabled
UART0->C2  |= UART_C2_RIE(1);    // Rx Interrupt enabled



// Configure Transmitter/Receiever
UART0->C2  |= UART_C2_TE(1);     // Tx Enabled
UART0->C2  |= UART_C2_RE(1);     // Rx Enabled
}
uint8_t recive(void){
     while(!(UART0->S1 & UART0_S1_RDRF_MASK));
    return UART0 -> D;
}

void Delay(volatile unsigned int time_del) {
    while (time_del--)
        {
    }
}
