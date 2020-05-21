/*
 Funcão que inicializa o LCD
 */

#include "xlcd.h"
#include "mcc_generated_files/mcc.h" //Preciso por causa do delay 

#include "LCD.h"

/*
                         Variaveis
 */

// 128 = 1a linha 1a coluna (0b10000000) no LCD
// 192 = 2a linha 1a coluna (0b11000000) no LCD




/*
                         Funcoes
 */
void LCD_inicio_teste (void){ 
    
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
    
    putsXLCD ("JOAO MEDEIROS 2172157");
    
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
}    

//void escrever_texto_LCD (int linha_LCD, char texto[21]){
//
//    WriteCmdXLCD(linha_LCD);
//    while (BusyXLCD());
//    /*
//    * Escreve conteúdo da string 'texto' para o LCD,
//    * na posição anteriormente endereçada
//    */
//    putsXLCD(texto);
//     while (BusyXLCD());
//    
//}

//void escrever_variaveis_LCD (coluna,variavel){

//}

