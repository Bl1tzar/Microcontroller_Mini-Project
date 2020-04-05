#include "mcc_generated_files/mcc.h"
#include "xlcd.h"
/*header file para a biblioteca de Strings*/
//usado para o Teclado
#include <string.h>
#include <stdlib.h>

/*
                         Func�es
 */

//Inclui func�o LCD_inicio_teste 
//Inclui vari�veis globais LCD_linha_1 & LCD_linha_2
#include "LCD.h"


/* Inclui funcoes:
 * teclado_coluna_1 
 * teclado_coluna_2 
 * teclado_coluna_3
*/
#include "Teclado.h"


/*
                         Vari�veis Globais
 */

/*
         Teclado
 */
unsigned char tecla_premida; // Guarda a tecla que foi premida
int tecla_n; //Indica se alguma tecla foi premida
int tecla_limpar; // Indica que � para limpar o LCD
/*
         LCD
 */
// 192 = 2a linha 1a coluna (0b11000000) no LCD
int contador_colunas_LCD = 192; //contador 
int LCD_linha_1; //variavel externa - LCD.c
int LCD_linha_2; //variavel externa - LCD.c
/*
         PIN
 */
char pin [4]; // Guarda o valor do PIN introduzido para ter acesso
int pin_intr; // Valor do PIN introduzido
int pin_real = 0000; // Valor do PIN - o introduzido ter� que ser igual a este
/*
         Temperatura
 */
char temp_alar_int [2]; // Guarda o valor de temperatura de alarme introduzido 
int temp_alar; // Valor da temperatura de alarme 


/*
                         Func�es Temporarias
 */

//Testar LED com interrupc�o do Timer 0 & interrupc�es do telcado 
void acende_LED (void) {
    led_Toggle();
}


/*
                         Main application
 */

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();


    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:


    INTERRUPT_GlobalInterruptEnable();

    //INTERRUPT_GlobalInterruptDisable();

    INTERRUPT_PeripheralInterruptEnable();

    //INTERRUPT_PeripheralInterruptDisable();

    
    /*
                             Implementac�o de c�digo
     */
    
    int contador_caracteres = 4;
    
    //Escrever o inicio do LCD - "Mars Rocks_Teste Teclado" - LCD_inicio.h
    LCD_inicio_teste();
    
    //Interrupc�o do Timer para acender LED
    TMR0_SetInterruptHandler (acende_LED);
    
    //Interrupc�es dos bot�es das colunas do teclado para detetar uma tecla pressionada
    INT0_SetInterruptHandler (teclado_coluna_1);
    INT1_SetInterruptHandler (teclado_coluna_2);
    INT2_SetInterruptHandler (teclado_coluna_3);
    
    while (1)
    { 
        if (tecla_n){
            
            /*PIN*/
            //Adicionar o caracter da tecla premida � string PIN com a funcao strncat
            strncat(pin, &tecla_premida, 1);
            
            /*TESTAR A FUNCAO strncat*/
            
            WriteCmdXLCD(LCD_linha_2);
            while (BusyXLCD());

            /*
             * Escreve conte�do da string 'pin' para o LCD,
             * na posi��o anteriormente endere�ada
             */
            /*PIN*/
            putsXLCD(pin);
            while (BusyXLCD());
            
            /************************************************************/
            contador_caracteres++;
            contador_colunas_LCD++;
            tecla_n = 0;
        }
        else if (tecla_limpar){ //exclusivamente para limpar o ecr� com a tecla "#"
            WriteCmdXLCD(contador_colunas_LCD);
            while (BusyXLCD());
            
            putsXLCD("                    ");
            while (BusyXLCD());
            tecla_limpar = 0;
            
            
        }
    
        
        /*Loop para atribuir valores a todos os outputs para as linha do teclado*/
        //LATB = 0b11110111;
        /**/
        LATBbits.LATB3 = 0;
        LATBbits.LATB4 = 1;
        LATBbits.LATB5 = 1;
        LATBbits.LATB6 = 1;
        /**/
        __delay_ms (65); //Delay's porque se carregassemos numa tecla, ele escrevia um numero 3x seguidas
        //LATB = 0b11101111;
        /**/
        LATBbits.LATB3 = 1;
        LATBbits.LATB4 = 0;
        LATBbits.LATB5 = 1;
        LATBbits.LATB6 = 1;
        /**/
        __delay_ms (65);
        //LATB = 0b11011111;
        /**/
        LATBbits.LATB3 = 1;
        LATBbits.LATB4 = 1;
        LATBbits.LATB5 = 0;
        LATBbits.LATB6 = 1;
        /**/
        __delay_ms (65);
        //LATB = 0b10111111;
        /**/
        LATBbits.LATB3 = 1;
        LATBbits.LATB4 = 1;
        LATBbits.LATB5 = 1;
        LATBbits.LATB6 = 0;
        /**/
        __delay_ms (65);
        
    }
}
/**
 End of File
*/