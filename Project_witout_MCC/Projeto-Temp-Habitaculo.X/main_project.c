 /* 
 * Engenharia Autom�vel - 19/20 
 * Mars Rock's
 * _________________________________________
 * MINIPROJ: Projeto Final
 * TURMA:PL2
 * GRUPO:6
 *
 * NOME:JO�O MEDEIROS
 * NUMERO: 2172157
 * 
 * NOME: MIGUEL RIBEIRO
 * NUMERO: 2191578
 * ________________________________________
 *
 */
/* header file para as bibliotecas de XC8 */
#include <xc.h>

/* defini��o da velocidade de rel�gio para a fun��o delay */
#define _XTAL_FREQ 6000000 

/* header file para a biblioteca XLCD */
#include "xlcd.h"

/*header file para a biblioteca de Strings*/
//usado para o Teclado
#include <string.h>
#include <stdlib.h>

/* configura��o do oscilador externo */
#pragma config FOSC = ECMP
/* desactiva��o do modo de programa��o em baixa tens�o */
#pragma config LVP = ON 
/* desactiva��o do temporizador Watch Dog Timer */
#pragma config WDTEN = OFF 

/**************************Programac�o das interrupc�es************************/

/* Rotina de servico � interrupc�o (ISR) de alta prioridade 
 * RB0 -> sempre de alta prioridade 
 */

int contador_colunas_LCD = 192; // 192 = 2a linha 1a coluna (0b10000000) no LCD
unsigned char tecla_premida; // Guarda a tecla que foi premida

char pin [4]; // Guarda o valor do PIN introduzido para ter acesso
int pin_intr; // Valor do PIN introduzido
int pin_real = 0000; // Valor do PIN - o introduzido ter� que ser igual a este

char temp_alar_int [2]; // Guarda o valor de temperatura de alarme introduzido 
int temp_alar; // Valor da temperatura de alarme 

int tecla_n; // Indica se alguma tecla foi premida
int tecla_limpar; // Indica que � para limpar o LCD

void __interrupt(high_priority) highISR(void){
    
    /*TECLADO*/
    // Coluna 1; Linhas A,B,C,D
    if ((INTCONbits.INT0IE)&&(INTCONbits.INT0IF)){
        
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
        INTCONbits.INT0IF = 0;
    }
    // Coluna 2; Linhas A,B,C,D
    if ((INTCON3bits.INT1IE)&&(INTCON3bits.INT1IF)){
        
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
        INTCON3bits.INT1IF = 0;
    }
        // Coluna 3; Linhas A,B,C,D
    if ((INTCON3bits.INT2IE)&&(INTCON3bits.INT2IF)){
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
        else if (PORTBbits.RB6 == 0){ //limpar LCD com tecla "#"
            contador_colunas_LCD = 192;
            tecla_n = 0;
            tecla_limpar = 1;
        }
        INTCON3bits.INT2IF = 0;
    }
    
    /*LED & TIMER*/
    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF){
        
            //Contagem Inicial
            TMR0H = 0x48;
            TMR0L = 0xE5;
        
        if (LATAbits.LATA1){
            LATAbits.LATA1 = 0;
        }
        else{
            LATAbits.LATA1 = 1;
        }
        
        INTCONbits.TMR0IF = 0;
    }
    
    
}


/******************************************************************************/    
    
/**
 * Ponto de entrada da aplica��o.
 */
void main(void)
{
    
    int contador_caracteres = 4; //conta a quantidade de caracteres adicionados
    
    
	/*
	 * configura��o das linhas associadas aos canais anal�gicos
	 * do m�dulo ADC do Porto D como linhas digitais
 	 */
    ANSELA=0;
	ANSELB=0;
    ANSELC=0;
    ANSELD=0;
    ANSELE=0;
	/*
	 * Defini��o da direc��o das linhas
	 */

    /*LCD*/
    // linhas do porto D definidas como sa�das digitais 
	TRISD = 0;

    /*Variadade*/
    //RA0 - Sensor de temperatura: Input
    //RA1 - LED: Output
    //RA2 - RA7: N�o usadas, logo, configuradas como saidas
	TRISA = 0b00000001;
    
    /*Teclado*/
    //RB0 - RB2: Input
    //RB3 - RB7: Output (apenas RB3-RB6 s�o usadas)
	TRISB = 0b00000111;
    
    /*
    //Atribuir aos outputs que v�o para o teclado '0'
    // NOTA: Ver linha 233
    LATBbits.LATB3 = 0;
    LATBbits.LATB4 = 0;
    LATBbits.LATB5 = 0;
    LATBbits.LATB6 = 0;
    */
    
    /*RS232*/
    //RC6 - Tx (transmit) - output
    //RC7 - Rx (receive) - input
	TRISC = 0b10000000;
    
    /*Bot�o Reset*/
	TRISE = 0b10000000;
	
    /*******Configurac�o das interrupc�es*******/
    
    /* limpeza dos registos */
	INTCON = 0;
	INTCON2 = 0;
	INTCON3 = 0;
    
    /*Ativar as resistencias pull up*/ 
    INTCON2bits.RBPU = 0;
    //Apenas ativar a do pino RB0,RB1,RB2
    WPUB = 0b00000111;
    
    
    /*Registo RCON que ativa/desativa as prioridades*/
    //desativac�o das prioridades
    RCONbits.IPEN = 0;
   
    /*
	 * configura��o da interrup��o INT0:
	 *  flanco descendente
	 *  activa��o da interrup��o
	 */
	INTCON2bits.INTEDG0 = 0;
	INTCONbits.INT0IE = 1;
	/*
	 * configura��o da interrup��o INT1:
	 *  flanco descendente
	 *  activa��o da interrup��o
	 */
	INTCON2bits.INTEDG1 = 0;
	INTCON3bits.INT1IE = 1;

	/*
	 * configura��o da interrup��o INT2:
	 *  flanco descendente
	 *  activa��o da interrup��o
	 */
	INTCON2bits.INTEDG2 = 0;
	INTCON3bits.INT2IE = 1;
    
    /*Timers e interrupc�es*/
    //Configurac�o do Timer0
    T0CON = 0b10000011; 
    

    
    //Configurac�o das interrupc�es do Timer0
    INTCONbits.TMR0IE = 1;
	INTCONbits.TMR0IF = 0;
	INTCON2bits.TMR0IP = 0;
    
    
    /*********************LCD***********************/
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
            /********************Programac�o do LCD*********************/	
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
    
    
    
    /*Ativac�o das interrupc�es*/
    INTCONbits.GIE = 1;
    /*********************Teclado Matricial**************/
    
    /*Ideia geral:
     *Sendo que vamos usar pull-ups internas, o RB0, RB1 e RB2, quando n�o se
     * carrega num bot�o est�o a '1'. Quando se carrega num bot�o, um deles ir� 
     * ficar a zero.
     * Para isso, os outputs (RB3 - RB6) ter�o que dar um output de '0' quando
     * se carrega no bot�o
     * Ou seja, teremos que fazer um ciclo de 1110, 1101, 1011 e 0111 para ver
     * onde sai o 0!
     */
    
    while (1){
        /*Display no LCD da tecla pressionada e detetada na func�o de interrupc�es*/
        if (tecla_n){
            
            /*PIN*/
            //Adicionar o caracter da tecla premida � string PIN com a funcao strncat
            strncat(pin, &tecla_premida, 1);
            
            /*TESTAR A FUNCAO strncat*/
            
            WriteCmdXLCD(0b11000000);
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
