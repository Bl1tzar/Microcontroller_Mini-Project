#ifndef LCD_H
#define	LCD_H


//Para as variáveis passarem de um ficheiro .c para outro .c (LCD.c -> main.c)

// 128 = 1a linha 1a coluna (0b10000000) no LCD
// 192 = 2a linha 1a coluna (0b11000000) no LCD
extern int LCD_linha_1; //1a linha 1a coluna no LCD
extern int LCD_linha_2; //2a linha 1a coluna no LCD

//Funcões
void LCD_inicio_teste(void);

void escrever_texto_LCD (int linha_LCD, char texto[21]){

    WriteCmdXLCD(linha_LCD);
    while (BusyXLCD());
    /*
    * Escreve conteúdo da string 'texto' para o LCD,
    * na posição anteriormente endereçada
    */
    putsXLCD(texto);
     while (BusyXLCD());
    
}

#endif	/* LCD_H */

