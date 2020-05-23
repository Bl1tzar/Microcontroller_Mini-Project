/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.80.0
        Device            :  PIC18F45K22
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.10 and above
        MPLAB 	          :  MPLAB X 5.30	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set channel_AN0 aliases
#define channel_AN0_TRIS                 TRISAbits.TRISA0
#define channel_AN0_LAT                  LATAbits.LATA0
#define channel_AN0_PORT                 PORTAbits.RA0
#define channel_AN0_ANS                  ANSELAbits.ANSA0
#define channel_AN0_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define channel_AN0_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define channel_AN0_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define channel_AN0_GetValue()           PORTAbits.RA0
#define channel_AN0_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define channel_AN0_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define channel_AN0_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define channel_AN0_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set led aliases
#define led_TRIS                 TRISAbits.TRISA1
#define led_LAT                  LATAbits.LATA1
#define led_PORT                 PORTAbits.RA1
#define led_ANS                  ANSELAbits.ANSA1
#define led_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define led_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define led_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define led_GetValue()           PORTAbits.RA1
#define led_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define led_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define led_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define led_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set RA2 procedures
#define RA2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define RA2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define RA2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define RA2_GetValue()              PORTAbits.RA2
#define RA2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define RA2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define RA2_SetAnalogMode()         do { ANSELAbits.ANSA2 = 1; } while(0)
#define RA2_SetDigitalMode()        do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set RA3 procedures
#define RA3_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define RA3_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define RA3_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define RA3_GetValue()              PORTAbits.RA3
#define RA3_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define RA3_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define RA3_SetAnalogMode()         do { ANSELAbits.ANSA3 = 1; } while(0)
#define RA3_SetDigitalMode()        do { ANSELAbits.ANSA3 = 0; } while(0)

// get/set tec_1 aliases
#define tec_1_TRIS                 TRISBbits.TRISB0
#define tec_1_LAT                  LATBbits.LATB0
#define tec_1_PORT                 PORTBbits.RB0
#define tec_1_WPU                  WPUBbits.WPUB0
#define tec_1_ANS                  ANSELBbits.ANSB0
#define tec_1_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define tec_1_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define tec_1_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define tec_1_GetValue()           PORTBbits.RB0
#define tec_1_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define tec_1_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define tec_1_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define tec_1_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define tec_1_SetAnalogMode()      do { ANSELBbits.ANSB0 = 1; } while(0)
#define tec_1_SetDigitalMode()     do { ANSELBbits.ANSB0 = 0; } while(0)

// get/set tec_2 aliases
#define tec_2_TRIS                 TRISBbits.TRISB1
#define tec_2_LAT                  LATBbits.LATB1
#define tec_2_PORT                 PORTBbits.RB1
#define tec_2_WPU                  WPUBbits.WPUB1
#define tec_2_ANS                  ANSELBbits.ANSB1
#define tec_2_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define tec_2_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define tec_2_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define tec_2_GetValue()           PORTBbits.RB1
#define tec_2_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define tec_2_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define tec_2_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define tec_2_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define tec_2_SetAnalogMode()      do { ANSELBbits.ANSB1 = 1; } while(0)
#define tec_2_SetDigitalMode()     do { ANSELBbits.ANSB1 = 0; } while(0)

// get/set tec_3 aliases
#define tec_3_TRIS                 TRISBbits.TRISB2
#define tec_3_LAT                  LATBbits.LATB2
#define tec_3_PORT                 PORTBbits.RB2
#define tec_3_WPU                  WPUBbits.WPUB2
#define tec_3_ANS                  ANSELBbits.ANSB2
#define tec_3_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define tec_3_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define tec_3_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define tec_3_GetValue()           PORTBbits.RB2
#define tec_3_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define tec_3_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define tec_3_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define tec_3_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define tec_3_SetAnalogMode()      do { ANSELBbits.ANSB2 = 1; } while(0)
#define tec_3_SetDigitalMode()     do { ANSELBbits.ANSB2 = 0; } while(0)

// get/set tec_A aliases
#define tec_A_TRIS                 TRISBbits.TRISB3
#define tec_A_LAT                  LATBbits.LATB3
#define tec_A_PORT                 PORTBbits.RB3
#define tec_A_WPU                  WPUBbits.WPUB3
#define tec_A_ANS                  ANSELBbits.ANSB3
#define tec_A_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define tec_A_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define tec_A_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define tec_A_GetValue()           PORTBbits.RB3
#define tec_A_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define tec_A_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define tec_A_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define tec_A_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define tec_A_SetAnalogMode()      do { ANSELBbits.ANSB3 = 1; } while(0)
#define tec_A_SetDigitalMode()     do { ANSELBbits.ANSB3 = 0; } while(0)

// get/set tec_B aliases
#define tec_B_TRIS                 TRISBbits.TRISB4
#define tec_B_LAT                  LATBbits.LATB4
#define tec_B_PORT                 PORTBbits.RB4
#define tec_B_WPU                  WPUBbits.WPUB4
#define tec_B_ANS                  ANSELBbits.ANSB4
#define tec_B_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define tec_B_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define tec_B_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define tec_B_GetValue()           PORTBbits.RB4
#define tec_B_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define tec_B_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define tec_B_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define tec_B_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define tec_B_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define tec_B_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set tec_C aliases
#define tec_C_TRIS                 TRISBbits.TRISB5
#define tec_C_LAT                  LATBbits.LATB5
#define tec_C_PORT                 PORTBbits.RB5
#define tec_C_WPU                  WPUBbits.WPUB5
#define tec_C_ANS                  ANSELBbits.ANSB5
#define tec_C_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define tec_C_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define tec_C_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define tec_C_GetValue()           PORTBbits.RB5
#define tec_C_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define tec_C_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define tec_C_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define tec_C_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define tec_C_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define tec_C_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set tec_D aliases
#define tec_D_TRIS                 TRISBbits.TRISB6
#define tec_D_LAT                  LATBbits.LATB6
#define tec_D_PORT                 PORTBbits.RB6
#define tec_D_WPU                  WPUBbits.WPUB6
#define tec_D_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define tec_D_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define tec_D_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define tec_D_GetValue()           PORTBbits.RB6
#define tec_D_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define tec_D_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define tec_D_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define tec_D_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)

// get/set RC2 procedures
#define RC2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define RC2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define RC2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define RC2_GetValue()              PORTCbits.RC2
#define RC2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define RC2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define RC2_SetAnalogMode()         do { ANSELCbits.ANSC2 = 1; } while(0)
#define RC2_SetDigitalMode()        do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set Tx aliases
#define Tx_TRIS                 TRISCbits.TRISC6
#define Tx_LAT                  LATCbits.LATC6
#define Tx_PORT                 PORTCbits.RC6
#define Tx_ANS                  ANSELCbits.ANSC6
#define Tx_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define Tx_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define Tx_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define Tx_GetValue()           PORTCbits.RC6
#define Tx_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define Tx_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define Tx_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define Tx_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set Rx aliases
#define Rx_TRIS                 TRISCbits.TRISC7
#define Rx_LAT                  LATCbits.LATC7
#define Rx_PORT                 PORTCbits.RC7
#define Rx_ANS                  ANSELCbits.ANSC7
#define Rx_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define Rx_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define Rx_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define Rx_GetValue()           PORTCbits.RC7
#define Rx_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define Rx_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define Rx_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define Rx_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)

// get/set LCD_D4 aliases
#define LCD_D4_TRIS                 TRISDbits.TRISD0
#define LCD_D4_LAT                  LATDbits.LATD0
#define LCD_D4_PORT                 PORTDbits.RD0
#define LCD_D4_ANS                  ANSELDbits.ANSD0
#define LCD_D4_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define LCD_D4_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define LCD_D4_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define LCD_D4_GetValue()           PORTDbits.RD0
#define LCD_D4_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define LCD_D4_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define LCD_D4_SetAnalogMode()      do { ANSELDbits.ANSD0 = 1; } while(0)
#define LCD_D4_SetDigitalMode()     do { ANSELDbits.ANSD0 = 0; } while(0)

// get/set LCD_D5 aliases
#define LCD_D5_TRIS                 TRISDbits.TRISD1
#define LCD_D5_LAT                  LATDbits.LATD1
#define LCD_D5_PORT                 PORTDbits.RD1
#define LCD_D5_ANS                  ANSELDbits.ANSD1
#define LCD_D5_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define LCD_D5_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define LCD_D5_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define LCD_D5_GetValue()           PORTDbits.RD1
#define LCD_D5_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define LCD_D5_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define LCD_D5_SetAnalogMode()      do { ANSELDbits.ANSD1 = 1; } while(0)
#define LCD_D5_SetDigitalMode()     do { ANSELDbits.ANSD1 = 0; } while(0)

// get/set LCD_D6 aliases
#define LCD_D6_TRIS                 TRISDbits.TRISD2
#define LCD_D6_LAT                  LATDbits.LATD2
#define LCD_D6_PORT                 PORTDbits.RD2
#define LCD_D6_ANS                  ANSELDbits.ANSD2
#define LCD_D6_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define LCD_D6_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define LCD_D6_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define LCD_D6_GetValue()           PORTDbits.RD2
#define LCD_D6_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define LCD_D6_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)
#define LCD_D6_SetAnalogMode()      do { ANSELDbits.ANSD2 = 1; } while(0)
#define LCD_D6_SetDigitalMode()     do { ANSELDbits.ANSD2 = 0; } while(0)

// get/set LCD_D7 aliases
#define LCD_D7_TRIS                 TRISDbits.TRISD3
#define LCD_D7_LAT                  LATDbits.LATD3
#define LCD_D7_PORT                 PORTDbits.RD3
#define LCD_D7_ANS                  ANSELDbits.ANSD3
#define LCD_D7_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define LCD_D7_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define LCD_D7_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define LCD_D7_GetValue()           PORTDbits.RD3
#define LCD_D7_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define LCD_D7_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)
#define LCD_D7_SetAnalogMode()      do { ANSELDbits.ANSD3 = 1; } while(0)
#define LCD_D7_SetDigitalMode()     do { ANSELDbits.ANSD3 = 0; } while(0)

// get/set LCD_RS aliases
#define LCD_RS_TRIS                 TRISDbits.TRISD4
#define LCD_RS_LAT                  LATDbits.LATD4
#define LCD_RS_PORT                 PORTDbits.RD4
#define LCD_RS_ANS                  ANSELDbits.ANSD4
#define LCD_RS_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define LCD_RS_SetLow()             do { LATDbits.LATD4 = 0; } while(0)
#define LCD_RS_Toggle()             do { LATDbits.LATD4 = ~LATDbits.LATD4; } while(0)
#define LCD_RS_GetValue()           PORTDbits.RD4
#define LCD_RS_SetDigitalInput()    do { TRISDbits.TRISD4 = 1; } while(0)
#define LCD_RS_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)
#define LCD_RS_SetAnalogMode()      do { ANSELDbits.ANSD4 = 1; } while(0)
#define LCD_RS_SetDigitalMode()     do { ANSELDbits.ANSD4 = 0; } while(0)

// get/set LCD_RW aliases
#define LCD_RW_TRIS                 TRISDbits.TRISD5
#define LCD_RW_LAT                  LATDbits.LATD5
#define LCD_RW_PORT                 PORTDbits.RD5
#define LCD_RW_ANS                  ANSELDbits.ANSD5
#define LCD_RW_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define LCD_RW_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define LCD_RW_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define LCD_RW_GetValue()           PORTDbits.RD5
#define LCD_RW_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define LCD_RW_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
#define LCD_RW_SetAnalogMode()      do { ANSELDbits.ANSD5 = 1; } while(0)
#define LCD_RW_SetDigitalMode()     do { ANSELDbits.ANSD5 = 0; } while(0)

// get/set LCD_E aliases
#define LCD_E_TRIS                 TRISDbits.TRISD6
#define LCD_E_LAT                  LATDbits.LATD6
#define LCD_E_PORT                 PORTDbits.RD6
#define LCD_E_ANS                  ANSELDbits.ANSD6
#define LCD_E_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define LCD_E_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define LCD_E_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define LCD_E_GetValue()           PORTDbits.RD6
#define LCD_E_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define LCD_E_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)
#define LCD_E_SetAnalogMode()      do { ANSELDbits.ANSD6 = 1; } while(0)
#define LCD_E_SetDigitalMode()     do { ANSELDbits.ANSD6 = 0; } while(0)

// get/set LCD_VDD aliases
#define LCD_VDD_TRIS                 TRISDbits.TRISD7
#define LCD_VDD_LAT                  LATDbits.LATD7
#define LCD_VDD_PORT                 PORTDbits.RD7
#define LCD_VDD_ANS                  ANSELDbits.ANSD7
#define LCD_VDD_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define LCD_VDD_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define LCD_VDD_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define LCD_VDD_GetValue()           PORTDbits.RD7
#define LCD_VDD_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define LCD_VDD_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)
#define LCD_VDD_SetAnalogMode()      do { ANSELDbits.ANSD7 = 1; } while(0)
#define LCD_VDD_SetDigitalMode()     do { ANSELDbits.ANSD7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/