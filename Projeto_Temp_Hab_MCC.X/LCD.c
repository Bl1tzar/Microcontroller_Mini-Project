/*
 Funcão que inicializa o LCD
 */

#include "xlcd.h"
#include "mcc_generated_files/mcc.h" //Preciso por causa do delay 

#include "LCD.h"


/*
                         Funcoes
 */
void LCD_inicio (void){ 
    
    int i =0;
    int j = 0;
    
    OpenXLCD(FOUR_BIT & LINES_5X7);     //Modo de ligação do display a 4 bits e  caracteres no display com tamanho 5 colunas por 7 linhas
    while (BusyXLCD());
    WriteCmdXLCD(DON & CURSOR_OFF & BLINK_OFF);     //Liga display, desliga cursor e desliga modo blink (piscar)
    while (BusyXLCD());
    WriteCmdXLCD(SHIFT_CUR_RIGHT);      //Deslocamento do cursor para a direita
    while (BusyXLCD());
    WriteCmdXLCD(LCD_clear);        //Dá clear no LCD
    while (BusyXLCD());
    
    /*
	 * Endereçamento do display:
	 * 1a linha, 16a coluna
	*/
	WriteCmdXLCD(0b10000001);
	while (BusyXLCD());
    
    putsXLCD ("MICROPROCESSADORES");
    
    /*
	 * Endereçamento do display:
	 * 1a linha, 16a coluna
	*/
	WriteCmdXLCD(0b11000011);
	while (BusyXLCD());
    
    putsXLCD ("EAU - ESTG");
    
    __delay_ms (1000);
    
    WriteCmdXLCD(LCD_clear);        
    while (BusyXLCD());
    
    
       /*
	 * Endereçamento do display:
	 * 1a linha, 16a coluna
	*/
	WriteCmdXLCD(0b10000000);
	while (BusyXLCD());
    
    putsXLCD ("MIGUEL RIBEIRO 2191578");
    
    /*
     * Endereçamento do display:
     * 1a linha, 16a coluna
    */
    WriteCmdXLCD(0b11000000);
    while (BusyXLCD());
   
    putsXLCD ("JO O MEDEIROS 2172157");
   
    SetCGRamAddr(0b00000000); //Endereço da memória CGRAM
    while (BusyXLCD());
   
    WriteDataXLCD(0b00001110); // linha 0
    while (BusyXLCD());
    WriteDataXLCD(0b00000000); // linha 1
    while (BusyXLCD());
    WriteDataXLCD(0b00011111); // linha 2
    while (BusyXLCD());
    WriteDataXLCD(0b00010001); // linha 3
    while (BusyXLCD());
    WriteDataXLCD(0b00011111); // linha 4
    while (BusyXLCD());
    WriteDataXLCD(0b00010001); // linha 5
    while (BusyXLCD());
    WriteDataXLCD(0b00010001); // linha 6
    while (BusyXLCD());
    WriteDataXLCD(0b00010001); // linha 7
    while (BusyXLCD());
           
    WriteCmdXLCD(0b11000010); //Endereço do display, 2ºlinha 3ºcoluna
    while (BusyXLCD());
           
    putcXLCD(0b00000000); //Escrever o caracter personalizado na posição anteriormente endereçada
    while (BusyXLCD());
           
   
    __delay_ms(1000);
    
    for (i = 0; i < 2 ; i++ ) { //Quantos espacos anda para o lado
    /*
    * Comando interno para o LCD:
    * SHIFT_DISP_LEFT: Deslocamento do display do LCD para a
    * direita
    */
    WriteCmdXLCD(SHIFT_DISP_LEFT);
    while (BusyXLCD());
    for (j = 0; j < 100 ; j++ ) //Rapidez com que anda para o lado 
            __delay_ms(3); 
    }
    
    
    __delay_ms(1000);
    
    WriteCmdXLCD(LCD_clear);        
    while (BusyXLCD());
    
        
    SetCGRamAddr(0b00001000); //Endereço da memória CGRAM do caracter avisador do alarme
    while (BusyXLCD());
   
    WriteDataXLCD(0b00000000); // linha 0
    while (BusyXLCD());
    WriteDataXLCD(0b00001110); // linha 1
    while (BusyXLCD());
    WriteDataXLCD(0b00011111); // linha 2
    while (BusyXLCD());
    WriteDataXLCD(0b00011111); // linha 3
    while (BusyXLCD());
    WriteDataXLCD(0b00011111); // linha 4
    while (BusyXLCD());
    WriteDataXLCD(0b00001110); // linha 5
    while (BusyXLCD());
    WriteDataXLCD(0b00000000); // linha 6
    while (BusyXLCD());
    WriteDataXLCD(0b00000000); // linha 7
    while (BusyXLCD());
    
    SetCGRamAddr(0b00010000); //Endereço da memória CGRAM do caracter para apagar o avisador do alarme
    while (BusyXLCD());
   
    WriteDataXLCD(0b00000000); // linha 0
    while (BusyXLCD());
    WriteDataXLCD(0b00000000); // linha 1
    while (BusyXLCD());
    WriteDataXLCD(0b00000000); // linha 2
    while (BusyXLCD());
    WriteDataXLCD(0b00000000); // linha 3
    while (BusyXLCD());
    WriteDataXLCD(0b00000000); // linha 4
    while (BusyXLCD());
    WriteDataXLCD(0b00000000); // linha 5
    while (BusyXLCD());
    WriteDataXLCD(0b00000000); // linha 6
    while (BusyXLCD());
    WriteDataXLCD(0b00000000); // linha 7
    while (BusyXLCD());
}    



