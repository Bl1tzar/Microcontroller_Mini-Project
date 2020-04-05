/* header file para as bibliotecas de XC8 */
#include <xc.h>

/* defini��o da velocidade de rel�gio para a fun��o delay */
#define _XTAL_FREQ 6000000

#include	"xlcd.h"


/********************************************************************
 *   For the XLCD, from the xlcd.h file, we must provide:
 *              - DelayFor18TCY() provides a 18 Tcy delay
 *              - DelayPORXLCD() provides at least 15ms delay
 *              - DelayXLCD() provides at least 5ms delay
 ********************************************************************/
//  My clock running at 4mhz - then devided by 4? to be ~ 1us/cycle ?

void DelayFor18TCY(void) {
    //Delay10TCYx(0x2);	//delays 20 cycles
    __delay_us(18);
    __delay_ms(1);
    return;
}

void DelayPORXLCD(void) // minimum 15ms
{
    //Delay100TCYx(0xA0);	  // 100TCY * 160
    __delay_ms(15);
    __delay_ms(15);
    return;
}

void DelayXLCD(void) // minimum 5ms
{
    //Delay100TCYx(0x36);      // 100TCY * 54
    __delay_ms(15);
    return;
}

/********************************************************************
 *       Function Name:  OpenXLCD                                    *
 *       Return Value:   void                                        *
 *       Parameters:     lcdtype: sets the type of LCD (lines)       *
 *       Description:    This routine configures the LCD. Based on   *
 *                       the Hitachi HD44780 LCD controller. The     *
 *                       routine will configure the I/O pins of the  *
 *                       microcontroller, setup the LCD for 4- or    *
 *                       8-bit mode and clear the display. The user  *
 *                       must provide three delay routines:          *
 *                       DelayFor18TCY() provides a 18 Tcy delay     *
 *                       DelayPORXLCD() provides at least 15ms delay *
 *                       DelayXLCD() provides at least 5ms delay     *
 *                                                                   *
 *    NOTE:  I think there may be some problems with the BIT8 mode   *
 ********************************************************************/
void OpenXLCD(unsigned char lcdtype) {
    // For PICDEM 2 Plus, setup the A/D bits so they
    //  don't interfere with the XLCD control bits.

    DelayPORXLCD(); // delay 15ms

    // The data bits must be either a 8-bit port or the upper or
    // lower 4-bits of a port. These pins are made into inputs
#ifdef BIT8                             // 8-bit mode, use whole port
    DATA_PORT = 0;
    TRIS_DATA_PORT = 0xff;
#else                                   // 4-bit mode
#ifdef UPPER                            // Upper 4-bits of the port
    DATA_PORT &= 0x0f;
    TRIS_DATA_PORT |= 0xf0;
#else                                   // Lower 4-bits of the port
    DATA_PORT &= 0xf0;
    TRIS_DATA_PORT |= 0x0f;
#endif
#endif
    TRIS_RW = 0; // All control signals made outputs
    TRIS_RS = 0;
    TRIS_E = 0;
    RW_PIN = 0; // R/W pin made low
    RS_PIN = 0; // Register select pin made low
    E_PIN = 0; // Clock pin made low

    // Delay for 15ms to allow for LCD Power on reset
    DelayPORXLCD();


    // Setup interface to LCD - First Init Nibble
#ifdef BIT8                             // 8-bit mode interface
    TRIS_DATA_PORT = 0; // Data port output
    DATA_PORT = 0b00110000; // Function set cmd(8-bit interface)
#else                                   // 4-bit mode interface
#ifdef UPPER                            // Upper nibble interface
    TRIS_DATA_PORT &= 0x0f;
    DATA_PORT &= 0x0f;
    DATA_PORT |= 0b00110000; // Function set cmd(4-bit interface)
#else                                   // Lower nibble interface
    TRIS_DATA_PORT &= 0xf0;
    DATA_PORT &= 0xf0;
    DATA_PORT |= 0b00000011; // Function set cmd(4-bit interface)
#endif
#endif
    E_PIN = 1; // Clock the cmd in
    DelayFor18TCY();
    E_PIN = 0;

    // Delay for at least 4.1ms
    DelayXLCD();

    // Second Init Nibble
#ifdef BIT8                             // 8-bit mode interface

#else                                   // 4-bit mode interface
#ifdef UPPER                            // Upper nibble interface
    TRIS_DATA_PORT &= 0x0f;
    DATA_PORT &= 0x0f;
    DATA_PORT |= 0b00110000; // Function set cmd(4-bit interface)
#else                                   // Lower nibble interface
    TRIS_DATA_PORT &= 0xf0;
    DATA_PORT &= 0xf0;
    DATA_PORT |= 0b00000011; // Function set cmd(4-bit interface)
#endif
#endif
    E_PIN = 1; // Clock the cmd in
    DelayFor18TCY();
    E_PIN = 0;

    // Delay for at least 100us
    DelayXLCD();

    // Third Init Nibble
#ifdef BIT8                             // 8-bit interface
    DATA_PORT = 0b00110000; // Function set cmd(8-bit interface)
#else                                   // 4-bit interface
#ifdef UPPER                            // Upper nibble interface
    DATA_PORT &= 0x0f; // Function set cmd(4-bit interface)
    DATA_PORT |= 0b00110000;
#else                                   // Lower nibble interface
    DATA_PORT &= 0xf0; // Function set cmd(4-bit interface)
    DATA_PORT |= 0b00000011;
#endif
#endif
    E_PIN = 1; // Clock the cmd in
    DelayFor18TCY();
    E_PIN = 0;

    // Delay for at least 4.1ms
    DelayXLCD();

    // Fourth Init Nibble (Word for 8 bit)
#ifdef BIT8                             // 8-bit interface
    DATA_PORT = 0b00111100; // Function set cmd(8-bit interface)
    // Check lower Nibble for correct bits
    // This Init sequence has some issues!
#else                                   // 4-bit interface
#ifdef UPPER                            // Upper nibble interface
    DATA_PORT &= 0x0f; // Function set cmd(4-bit interface)
    DATA_PORT |= 0b00100000;
#else                                   // Lower nibble interface
    DATA_PORT &= 0xf0; // Function set cmd(4-bit interface)
    DATA_PORT |= 0b00000010;
#endif
#endif
    E_PIN = 1; // Clock cmd in
    DelayFor18TCY();
    E_PIN = 0;


#ifdef BIT8                             // 8-bit interface
    TRIS_DATA_PORT = 0xff; // Make data port input
#else                                   // 4-bit interface
#ifdef UPPER                            // Upper nibble interface
    TRIS_DATA_PORT |= 0xf0; // Make data nibble input
#else                                   // Lower nibble interface
    TRIS_DATA_PORT |= 0x0f; // Make data nibble input
#endif
#endif

    // From now on, send bytes - (2) nibbles for 4bit
    // Set data interface width, # lines, font
    while (BusyXLCD()); // Wait if LCD busy
    //        WriteCmdXLCD(lcdtype);          // Function set cmd
    WriteCmdXLCD(0x28); // Function set cmd


    // Turn the display on then off
    while (BusyXLCD()); // Wait if LCD busy
    //        WriteCmdXLCD(DOFF&CURSOR_OFF&BLINK_OFF);        // Display OFF/Blink OFF
    WriteCmdXLCD(0x0D);


    while (BusyXLCD()); // Wait if LCD busy
    //        WriteCmdXLCD(DON&CURSOR_ON&BLINK_ON);           // Display ON/Blink ON

    // Clear display
    while (BusyXLCD()); // Wait if LCD busy
    WriteCmdXLCD(0x01); // Clear display

    // Set entry mode inc, no shift
    while (BusyXLCD()); // Wait if LCD busy
    //        WriteCmdXLCD(SHIFT_CUR_LEFT);   // Entry Mode
    WriteCmdXLCD(0x06);


    // Set DD Ram address to 0
    while (BusyXLCD()); // Wait if LCD busy
    //        SetDDRamAddr(0);                // Set Display data ram address to 0
    WriteCmdXLCD(0x80); // Set Display data ram address to 0
    return;
}

/********************************************************************
 *       Function Name:  BusyXLCD                                    *
 *       Return Value:   char: busy status of LCD controller         *
 *       Parameters:     void                                        *
 *       Description:    This routine reads the busy status of the   *
 *                       Hitachi HD44780 LCD controller.             *
 ********************************************************************/
unsigned char BusyXLCD(void) {
    RW_PIN = 1; // Set the control bits for read
    RS_PIN = 0;
    DelayFor18TCY();
    E_PIN = 1; // Clock in the command
    DelayFor18TCY();
#ifdef BIT8                             // 8-bit interface
    if (DATA_PORT & 0x80) // Read bit 7 (busy bit)
    { // If high
        E_PIN = 0; // Reset clock line
        RW_PIN = 0; // Reset control line
        return 1; // Return TRUE
    } else // Bit 7 low
    {
        E_PIN = 0; // Reset clock line
        RW_PIN = 0; // Reset control line
        return 0; // Return FALSE
    }
#else                                   // 4-bit interface
#ifdef UPPER                            // Upper nibble interface
    if (DATA_PORT & 0x80)
#else                                   // Lower nibble interface
    if (DATA_PORT & 0x08)
#endif
    {
        E_PIN = 0; // Reset clock line
        DelayFor18TCY();
        E_PIN = 1; // Clock out other nibble
        DelayFor18TCY();
        E_PIN = 0;
        RW_PIN = 0; // Reset control line
        return 1; // Return TRUE
    } else // Busy bit is low
    {
        E_PIN = 0; // Reset clock line
        DelayFor18TCY();
        E_PIN = 1; // Clock out other nibble
        DelayFor18TCY();
        E_PIN = 0;
        RW_PIN = 0; // Reset control line
        return 0; // Return FALSE
    }
#endif
}


/********************************************************************
 *       Function Name:  putrsXLCD
 *       Return Value:   void
 *       Parameters:     buffer: pointer to string
 *       Description:    This routine writes a string of bytes to the
 *                       Hitachi HD44780 LCD controller. The user
 *                       must check to see if the LCD controller is
 *                       busy before calling this routine. The data
 *                       is written to the character generator RAM or
 *                       the display data RAM depending on what the
 *                       previous SetxxRamAddr routine was called.
 ********************************************************************/
/*
void putrsXLCD(const rom char *buffer)
{
        while(*buffer)                  // Write data to LCD up to null
        {
                while(BusyXLCD());      // Wait while LCD is busy
                WriteDataXLCD(*buffer); // Write character to LCD
                buffer++;               // Increment buffer
        }
        return;
}

 */

/********************************************************************
 *       Function Name:  putsXLCD
 *       Return Value:   void
 *       Parameters:     buffer: pointer to string
 *       Description:    This routine writes a string of bytes to the
 *                       Hitachi HD44780 LCD controller. The user
 *                       must check to see if the LCD controller is
 *                       busy before calling this routine. The data
 *                       is written to the character generator RAM or
 *                       the display data RAM depending on what the
 *                       previous SetxxRamAddr routine was called.
 ********************************************************************/
void putsXLCD(char *buffer) {
    while (*buffer) // Write data to LCD up to null
    {
        while (BusyXLCD()); // Wait while LCD is busy
        WriteDataXLCD(*buffer); // Write character to LCD
        buffer++; // Increment buffer
    }
    return;
}

/*********************************************************************
 *       Function Name:  ReadAddrXLCD                                 *
 *       Return Value:   char: address from LCD controller            *
 *       Parameters:     void                                         *
 *       Description:    This routine reads an address byte from the  *
 *                       Hitachi HD44780 LCD controller. The user     *
 *                       must check to see if the LCD controller is   *
 *                       busy before calling this routine. The address*
 *                       is read from the character generator RAM or  *
 *                       the display data RAM depending on what the   *
 *                       previous SetxxRamAddr routine was called.    *
 *********************************************************************/
unsigned char ReadAddrXLCD(void) {
    char data; // Holds the data retrieved from the LCD

#ifdef BIT8                             // 8-bit interface
    RW_PIN = 1; // Set control bits for the read
    RS_PIN = 0;
    DelayFor18TCY();
    E_PIN = 1; // Clock data out of the LCD controller
    DelayFor18TCY();
    data = DATA_PORT; // Save the data in the register
    E_PIN = 0;
    RW_PIN = 0; // Reset the control bits
#else                                   // 4-bit interface
    RW_PIN = 1; // Set control bits for the read
    RS_PIN = 0;
    DelayFor18TCY();
    E_PIN = 1; // Clock data out of the LCD controller
    DelayFor18TCY();
#ifdef UPPER                            // Upper nibble interface
    data = DATA_PORT & 0xf0; // Read the nibble into the upper nibble of data
#else                                   // Lower nibble interface
    data = (DATA_PORT << 4)&0xf0; // Read the nibble into the upper nibble of data
#endif
    E_PIN = 0; // Reset the clock
    DelayFor18TCY();
    E_PIN = 1; // Clock out the lower nibble
    DelayFor18TCY();
#ifdef UPPER                            // Upper nibble interface
    data |= (DATA_PORT >> 4)&0x0f; // Read the nibble into the lower nibble of data
#else                                   // Lower nibble interface
    data |= DATA_PORT & 0x0f; // Read the nibble into the lower nibble of data
#endif
    E_PIN = 0;
    RW_PIN = 0; // Reset the control lines
#endif
    return (data & 0x7f); // Return the address, Mask off the busy bit
}

/********************************************************************
 *       Function Name:  ReadDataXLCD                                *
 *       Return Value:   char: data byte from LCD controller         *
 *       Parameters:     void                                        *
 *       Description:    This routine reads a data byte from the     *
 *                       Hitachi HD44780 LCD controller. The user    *
 *                       must check to see if the LCD controller is  *
 *                       busy before calling this routine. The data  *
 *                       is read from the character generator RAM or *
 *                       the display data RAM depending on what the  *
 *                       previous SetxxRamAddr routine was called.   *
 ********************************************************************/
char ReadDataXLCD(void) {
    char data;

#ifdef BIT8                             // 8-bit interface
    RS_PIN = 1; // Set the control bits
    RW_PIN = 1;
    DelayFor18TCY();
    E_PIN = 1; // Clock the data out of the LCD
    DelayFor18TCY();
    data = DATA_PORT; // Read the data
    E_PIN = 0;
    RS_PIN = 0; // Reset the control bits
    RW_PIN = 0;
#else                                   // 4-bit interface
    RW_PIN = 1;
    RS_PIN = 1;
    DelayFor18TCY();
    E_PIN = 1; // Clock the data out of the LCD
    DelayFor18TCY();
#ifdef UPPER                            // Upper nibble interface
    data = DATA_PORT & 0xf0; // Read the upper nibble of data
#else                                   // Lower nibble interface
    data = (DATA_PORT << 4)&0xf0; // read the upper nibble of data
#endif
    E_PIN = 0; // Reset the clock line
    DelayFor18TCY();
    E_PIN = 1; // Clock the next nibble out of the LCD
    DelayFor18TCY();
#ifdef UPPER                            // Upper nibble interface
    data |= (DATA_PORT >> 4)&0x0f; // Read the lower nibble of data
#else                                   // Lower nibble interface
    data |= DATA_PORT & 0x0f; // Read the lower nibble of data
#endif
    E_PIN = 0;
    RS_PIN = 0; // Reset the control bits
    RW_PIN = 0;
#endif
    return (data); // Return the data byte
}

/********************************************************************
 *       Function Name:  SetCGRamAddr                                *
 *       Return Value:   void                                        *
 *       Parameters:     CGaddr: character generator ram address     *
 *       Description:    This routine sets the character generator   *
 *                       address of the Hitachi HD44780 LCD          *
 *                       controller. The user must check to see if   *
 *                       the LCD controller is busy before calling   *
 *                       this routine.                               *
 ********************************************************************/
void SetCGRamAddr(unsigned char CGaddr) {
#ifdef BIT8                                     // 8-bit interface
    TRIS_DATA_PORT = 0; // Make data port ouput
    DATA_PORT = CGaddr | 0b01000000; // Write cmd and address to port
    RW_PIN = 0; // Set control signals
    RS_PIN = 0;
    DelayFor18TCY();
    E_PIN = 1; // Clock cmd and address in
    DelayFor18TCY();
    E_PIN = 0;
    DelayFor18TCY();
    TRIS_DATA_PORT = 0xff; // Make data port inputs
#else                                           // 4-bit interface
#ifdef UPPER                                    // Upper nibble interface
    TRIS_DATA_PORT &= 0x0f; // Make nibble input
    DATA_PORT &= 0x0f; // and write upper nibble
    DATA_PORT |= ((CGaddr | 0b01000000) & 0xf0);
#else                                           // Lower nibble interface
    TRIS_DATA_PORT &= 0xf0; // Make nibble input
    DATA_PORT &= 0xf0; // and write upper nibble
    DATA_PORT |= (((CGaddr | 0b01000000) >> 4) & 0x0f);
#endif
    RW_PIN = 0; // Set control signals
    RS_PIN = 0;
    DelayFor18TCY();
    E_PIN = 1; // Clock cmd and address in
    DelayFor18TCY();
    E_PIN = 0;
#ifdef UPPER                                    // Upper nibble interface
    DATA_PORT &= 0x0f; // Write lower nibble
    DATA_PORT |= ((CGaddr << 4)&0xf0);
#else                                           // Lower nibble interface
    DATA_PORT &= 0xf0; // Write lower nibble
    DATA_PORT |= (CGaddr & 0x0f);
#endif
    DelayFor18TCY();
    E_PIN = 1; // Clock cmd and address in
    DelayFor18TCY();
    E_PIN = 0;
#ifdef UPPER                                    // Upper nibble interface
    TRIS_DATA_PORT |= 0xf0; // Make inputs
#else                                           // Lower nibble interface
    TRIS_DATA_PORT |= 0x0f; // Make inputs
#endif
#endif
    return;
}

/********************************************************************
 *       Function Name:  SetDDRamAddr                                *
 *       Return Value:   void                                        *
 *       Parameters:     CGaddr: display data address                *
 *       Description:    This routine sets the display data address  *
 *                       of the Hitachi HD44780 LCD controller. The  *
 *                       user must check to see if the LCD controller*
 *                       is busy before calling this routine.        *
 ********************************************************************/
void SetDDRamAddr(unsigned char DDaddr) {
#ifdef BIT8                                     // 8-bit interface
    TRIS_DATA_PORT = 0; // Make port output
    DATA_PORT = DDaddr | 0b10000000; // Write cmd and address to port
    RW_PIN = 0; // Set the control bits
    RS_PIN = 0;
    DelayFor18TCY();
    E_PIN = 1; // Clock the cmd and address in
    DelayFor18TCY();
    E_PIN = 0;
    DelayFor18TCY();
    TRIS_DATA_PORT = 0xff; // Make port input
#else                                           // 4-bit interface
#ifdef UPPER                                    // Upper nibble  interface
    TRIS_DATA_PORT &= 0x0f; // Make port output
    DATA_PORT &= 0x0f; // and write upper nibble
    DATA_PORT |= ((DDaddr | 0b10000000) & 0xf0);
#else                                           // Lower nibble interface
    TRIS_DATA_PORT &= 0xf0; // Make port output
    DATA_PORT &= 0xf0; // and write upper nibble
    DATA_PORT |= (((DDaddr | 0b10000000) >> 4) & 0x0f);
#endif
    RW_PIN = 0; // Set control bits
    RS_PIN = 0;
    DelayFor18TCY();
    E_PIN = 1; // Clock the cmd and address in
    DelayFor18TCY();
    E_PIN = 0;
#ifdef UPPER                                    // Upper nibble interface
    DATA_PORT &= 0x0f; // Write lower nibble
    DATA_PORT |= ((DDaddr << 4)&0xf0);
#else                                           // Lower nibble interface
    DATA_PORT &= 0xf0; // Write lower nibble
    DATA_PORT |= (DDaddr & 0x0f);
#endif
    DelayFor18TCY();
    E_PIN = 1; // Clock the cmd and address in
    DelayFor18TCY();
    E_PIN = 0;
#ifdef UPPER                                    // Upper nibble interface
    TRIS_DATA_PORT |= 0xf0; // Make port input
#else                                           // Lower nibble interface
    TRIS_DATA_PORT |= 0x0f; // Make port input
#endif
#endif
    return;
}

/********************************************************************
 *       Function Name:  WriteCmdXLCD                                *
 *       Return Value:   void                                        *
 *       Parameters:     cmd: command to send to LCD                 *
 *       Description:    This routine writes a command to the Hitachi*
 *                       HD44780 LCD controller. The user must check *
 *                       to see if the LCD controller is busy before *
 *                       calling this routine.                       *
 ********************************************************************/
void WriteCmdXLCD(unsigned char cmd) {
#ifdef BIT8                             // 8-bit interface
    TRIS_DATA_PORT = 0; // Data port output
    DATA_PORT = cmd; // Write command to data port
    RW_PIN = 0; // Set the control signals
    RS_PIN = 0; // for sending a command
    DelayFor18TCY();
    E_PIN = 1; // Clock the command in
    DelayFor18TCY();
    E_PIN = 0;
    DelayFor18TCY();
    TRIS_DATA_PORT = 0xff; // Data port input
#else                                   // 4-bit interface
#ifdef UPPER                            // Upper nibble interface
    TRIS_DATA_PORT &= 0x0f;
    DATA_PORT &= 0x0f;
    DATA_PORT |= cmd & 0xf0;
#else                                   // Lower nibble interface
    TRIS_DATA_PORT &= 0xf0;
    DATA_PORT &= 0xf0;
    DATA_PORT |= (cmd >> 4)&0x0f;
#endif
    RW_PIN = 0; // Set control signals for command
    RS_PIN = 0;
    DelayFor18TCY();
    E_PIN = 1; // Clock command in
    DelayFor18TCY();
    E_PIN = 0;
#ifdef UPPER                            // Upper nibble interface
    DATA_PORT &= 0x0f;
    DATA_PORT |= (cmd << 4)&0xf0;
#else                                   // Lower nibble interface
    DATA_PORT &= 0xf0;
    DATA_PORT |= cmd & 0x0f;
#endif
    DelayFor18TCY();
    E_PIN = 1; // Clock command in
    DelayFor18TCY();
    E_PIN = 0;
#ifdef UPPER                            // Make data nibble input
    TRIS_DATA_PORT |= 0xf0;
#else
    TRIS_DATA_PORT |= 0x0f;
#endif
#endif
    return;
}

/********************************************************************
 *       Function Name:  WriteDataXLCD                               *
 *       Return Value:   void                                        *
 *       Parameters:     data: data byte to be written to LCD        *
 *       Description:    This routine writes a data byte to the      *
 *                       Hitachi HD44780 LCD controller. The user    *
 *                       must check to see if the LCD controller is  *
 *                       busy before calling this routine. The data  *
 *                       is written to the character generator RAM or*
 *                       the display data RAM depending on what the  *
 *                       previous SetxxRamAddr routine was called.   *
 ********************************************************************/
void WriteDataXLCD(char data) {
#ifdef BIT8                             // 8-bit interface
    TRIS_DATA_PORT = 0; // Make port output
    DATA_PORT = data; // Write data to port
    RS_PIN = 1; // Set control bits
    RW_PIN = 0;
    DelayFor18TCY();
    E_PIN = 1; // Clock data into LCD
    DelayFor18TCY();
    E_PIN = 0;
    RS_PIN = 0; // Reset control bits
    TRIS_DATA_PORT = 0xff; // Make port input
#else                                   // 4-bit interface
#ifdef UPPER                            // Upper nibble interface
    TRIS_DATA_PORT &= 0x0f;
    DATA_PORT &= 0x0f;
    DATA_PORT |= data & 0xf0;
#else                                   // Lower nibble interface
    TRIS_DATA_PORT &= 0xf0;
    DATA_PORT &= 0xf0;
    DATA_PORT |= ((data >> 4)&0x0f);
#endif
    RS_PIN = 1; // Set control bits
    RW_PIN = 0;
    DelayFor18TCY();
    E_PIN = 1; // Clock nibble into LCD
    DelayFor18TCY();
    E_PIN = 0;
#ifdef UPPER                            // Upper nibble interface
    DATA_PORT &= 0x0f;
    DATA_PORT |= ((data << 4)&0xf0);
#else                                   // Lower nibble interface
    DATA_PORT &= 0xf0;
    DATA_PORT |= (data & 0x0f);
#endif
    DelayFor18TCY();
    E_PIN = 1; // Clock nibble into LCD
    DelayFor18TCY();
    E_PIN = 0;
#ifdef UPPER                            // Upper nibble interface
    TRIS_DATA_PORT |= 0xf0;
#else                                   // Lower nibble interface
    TRIS_DATA_PORT |= 0x0f;
#endif
#endif
    return;
}

