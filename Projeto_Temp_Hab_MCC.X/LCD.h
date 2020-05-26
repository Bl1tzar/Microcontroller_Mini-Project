#ifndef LCD_H
#define	LCD_H


//Para as variáveis passarem de um ficheiro .c para outro .c (LCD.c -> main.c)

// 128 = 1a linha 1a coluna (0b10000000) no LCD
// 192 = 2a linha 1a coluna (0b11000000) no LCD
#define LCD_linha_1 128 //1a linha 1a coluna no LCD
#define LCD_linha_2 192 //2a linha 1a coluna no LCD
#define LCD_clear 0b00000001 //define que corresponde a um clear numa funcao do xlcd

//Funcões
void LCD_inicio(void);


#endif	/* LCD_H */

