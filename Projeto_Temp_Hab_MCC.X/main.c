

#include "mcc_generated_files/mcc.h"
#include "xlcd.h"
/*header file para a biblioteca de Strings*/
//usado para o Teclado
#include <string.h>
#include <stdlib.h>

#include "LCD_inicio.h"

/*
                         Variáveis Globais
 */

/*
         Teclado
 */

unsigned char tecla_premida; // Guarda a tecla que foi premida
int tecla_n; //Indica se alguma tecla foi premida
int tecla_limpar; // Indica que é para limpar o LCD

/*
         LCD
 */

int contador_colunas_LCD = 192; // 192 = 2a linha 1a coluna (0b10000000) no LCD

/*
         PIN
 */

char pin [4]; // Guarda o valor do PIN introduzido para ter acesso
int pin_intr; // Valor do PIN introduzido
int pin_real = 0000; // Valor do PIN - o introduzido terá que ser igual a este

/*
         Temperatura
 */

char temp_alar_int [2]; // Guarda o valor de temperatura de alarme introduzido 
int temp_alar; // Valor da temperatura de alarme 




/*
                         Funcões Temporarias
 */

//Testar LED com interrupcão do Timer 0 & interrupcões do telcado 

void acende_LED (void) {
    led_Toggle();
}

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
            contador_colunas_LCD = 192;
            tecla_n = 0;
            tecla_limpar = 1;
        }
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
                             Implementacão de código
     */
    
    int contador_caracteres = 4;
    
    //Escrever o inicio do LCD - "Mars Rocks_Teste Teclado" - LCD_inicio.h
    LCD_inicio_teste();
    
    
    TMR0_SetInterruptHandler (acende_LED);
    
    INT0_SetInterruptHandler (teclado_coluna_1);
    INT1_SetInterruptHandler (teclado_coluna_2);
    INT2_SetInterruptHandler (teclado_coluna_3);
    
    while (1)
    { 
        if (tecla_n){
            
            /*PIN*/
            //Adicionar o caracter da tecla premida à string PIN com a funcao strncat
            strncat(pin, &tecla_premida, 1);
            
            /*TESTAR A FUNCAO strncat*/
            
            WriteCmdXLCD(0b11000000);
            while (BusyXLCD());

            /*
             * Escreve conteúdo da string 'pin' para o LCD,
             * na posição anteriormente endereçada
             */
            /*PIN*/
            putsXLCD(pin);
            while (BusyXLCD());
            
            /************************************************************/
            contador_caracteres++;
            contador_colunas_LCD++;
            tecla_n = 0;
        }
        else if (tecla_limpar){ //exclusivamente para limpar o ecrã com a tecla "#"
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