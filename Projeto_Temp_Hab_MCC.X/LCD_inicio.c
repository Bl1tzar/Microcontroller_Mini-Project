/*
 Func�o que inicializa o LCD
 */

#include <xc.h>
#include "xlcd.h"
#include "mcc_generated_files/mcc.h" //Preciso por causa do delay 

#include "LCD_inicio.h"

void LCD_inicio_teste (void){ 

    /*
                    Inicializac�o do LCD
     */
    
    /*
	 * Inicializa��o do LCD:
	 * FOUR_BIT: Modo de liga��o do display a 4 bits
	 * LINES_5X7: Caracteres no display com tamanho 5 colunas por
	 * 7 linhas
	 *
	 * OpenXLCD(FOUR_BIT & LINES_5X7);
	 */
	OpenXLCD(0b00101011);
	while (BusyXLCD());
	/*
	 * Comando interno para o LCD:
	 * D_ON: Liga display
	 * CURSOR_OFF: Desliga cursor
	 * BLINK_OFF: Desliga modo blink (piscar)
	 *
	 * WriteCmdXLCD(DON & CURSOR_OFF & BLINK_OFF);
	 */
	WriteCmdXLCD(0b00001100);
	while (BusyXLCD()); 
	/*
	 * Comando interno para o LCD:
	 * SHIFT_CUR_RIGHT: Deslocamento do cursor para a direita
	 *
	 * WriteCmdXLCD(SHIFT_CUR_RIGHT);
	 */
	WriteCmdXLCD(0b00010111);
	while (BusyXLCD());
	/*
	 * Comando interno para o LCD:
	 * CLEAR_LCD: Limpa conte�do do display
	 */
	WriteCmdXLCD(0b00000001);
	while (BusyXLCD());
    
    
    
    
    
    /*
                        Escrever no LCD
     */
    
  
    /*
	 * Endere�amento do display:
	 * 1a linha, 1a coluna
	 */
	WriteCmdXLCD(0b10000000);
	while (BusyXLCD());

	/*
	 * Escreve conte�do da string 'mybuff1' para o LCD,
	 * na posi��o anteriormente endere�ada
	 */
    putsXLCD("Mars ROCK'S!");
	while (BusyXLCD());
    
    __delay_ms(1000);
    
    	WriteCmdXLCD(0b00010111);
	while (BusyXLCD());
	/*
	 * Comando interno para o LCD:
	 * CLEAR_LCD: Limpa conte�do do display
	 */
	WriteCmdXLCD(0b00000001);
	while (BusyXLCD());

	/*
	 * Endere�amento do display:
	 * 1a linha, 1a coluna
	 */
	WriteCmdXLCD(0b10000000);
	while (BusyXLCD());

	/*
	 * Escreve conte�do da string 'mybuff1' para o LCD,
	 * na posi��o anteriormente endere�ada
	 */
    putsXLCD("Teste - Teclado");
	while (BusyXLCD());
    
}    

