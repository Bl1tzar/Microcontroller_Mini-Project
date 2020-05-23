/*
 Funcões que detetam o pressionamento de uma tecla
 */

#include "mcc_generated_files/mcc.h"

#include "Teclado.h"

/*
                         Declaracão de variáveis globais 
 */
//Para as variáveis passarem de um ficheiro .c para outro .c (teclado.c -> main.c)
unsigned char tecla_premida; // Guarda a tecla que foi premida
int tecla_n; //Indica se alguma tecla foi premida
int tecla_limpar; // Indica que é para limpar o LCD

int contador_colunas_LCD = 192; // 192 = 2a linha 1a coluna (0b10000000) no LCD


void teclado_coluna_1 (void) {

    if (PORTBbits.RB3 == 0){
            tecla_premida = '1';
        }
        else if (PORTBbits.RB4 == 0){
            tecla_premida = '4';
        }
        else if (PORTBbits.RB5 == 0){
            tecla_premida = '7';
        }
        else if (PORTBbits.RB6 == 0){
            tecla_premida = '*';
        }
        tecla_n = 1;   
}

void teclado_coluna_2 (void) {

    if (PORTBbits.RB3 == 0){
            tecla_premida = '2';
        }
        else if (PORTBbits.RB4 == 0){
            tecla_premida = '5';
        }
        else if (PORTBbits.RB5 == 0){
            tecla_premida = '8';
        }
        else if (PORTBbits.RB6 == 0){
            tecla_premida = '0';
        }
        tecla_n = 1;   
}

void teclado_coluna_3 (void) {
    tecla_n = 1;
    if (PORTBbits.RB3 == 0){
            tecla_premida = '3';
        }
        else if (PORTBbits.RB4 == 0){
            tecla_premida = '6';
        }
        else if (PORTBbits.RB5 == 0){
            tecla_premida = '9';
        }
        else if (PORTBbits.RB6 == 0){
            tecla_premida = '#';
        }
}