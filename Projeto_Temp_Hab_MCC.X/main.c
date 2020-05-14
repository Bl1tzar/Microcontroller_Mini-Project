#include "mcc_generated_files/mcc.h"
#include "xlcd.h"
/*header file para a biblioteca de Strings*/
//usado para o Teclado
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*
                         Funcões
 */

//Inclui funcão LCD_inicio_teste 
//Inclui variáveis globais LCD_linha_1 & LCD_linha_2
#include "LCD.h"


/* Inclui funcoes:
 * teclado_coluna_1 
 * teclado_coluna_2 
 * teclado_coluna_3
*/
#include "Teclado.h"


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
// 192 = 2a linha 1a coluna (0b11000000) no LCD
int contador_colunas_LCD = 192; //contador 
int LCD_linha_1; //variavel externa - LCD.c - isto porque necessitei delas no LCD.c
int LCD_linha_2; //variavel externa - LCD.c
/*
         PIN
 */
char pin [4]; // Guarda o valor do PIN introduzido para ter acesso
int pin_intr; // Valor do PIN introduzido
int pin_real = 0000; // Valor do PIN - o introduzido terá que ser igual a este
/*
         Temperatura
 */
unsigned char temp_alarme_intro; // Guarda o valor de temperatura de alarme introduzido para passar para inteiro
char temp_alarme_string [4]; // Valor da temperatura de alarme 
int temp_alarme;
int temp_mudou;
/*
         ADC
 */

int codigo_digital; // 2 bits mais significativos do codigo digital de 10 bits
//char low [8] = ADRESL; // 8 bits menos significativos do codigo digital de 10 bits
int temp_ambiente;
int temp_ambiente_anterior; //Verificar se a temperatura varia - usada no ADC
char temp_ambiente_LCD [20];

/*
        Alarme
 */
int alarme_ativo;

/*
        Terminal
 */
int menu_estado; //Se menu_estado = 1, aparecera no terminal o menu principal.
                 //Se menu_estado = 0, aparecera no terminal o menu para mudar a temperatura.
int menu_entrada;
int limpar_terminal; //Dá scroll na página
int enter; //Verifica quando o enter é pressionado 
int temp_valida; //Verifica a temperatura de alarme introduzida
/*
                         Funcões Temporarias
 */

//Testar LED com interrupcão do Timer 0 & interrupcões do telcado 
void Timer_0 (void) { //LED + ADC
    if (alarme_ativo == 1){
        led_Toggle();
    }
    ADC_StartConversion();
}

void ADC_temperatura (void){
    
    codigo_digital = ADC_GetConversionResult(); //Obter codigo digital do conversor ADC
    
    //Calculo da Temperatura ambiente
    temp_ambiente = (int)(((((float) codigo_digital * (3.4/1024.0))-0.3)-0.400) / (0.0195));
    
    if (temp_ambiente != temp_ambiente_anterior){ //Verifica se a temperatura variou
    
        temp_mudou = 1;
        temp_ambiente_anterior = temp_ambiente;
    }
    else{
        temp_mudou = 0;
    }
    
}

/*
                         Main application
 */

void main(void)
{
        // Initialize the device
    SYSTEM_Initialize();
    
    uint8_t rxData; 
 

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

 

    // Enable high priority global interrupts
    INTERRUPT_GlobalInterruptHighEnable();

 

    // Enable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowEnable();

 

    // Disable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighDisable();

 

    // Disable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowDisable();

 

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

 

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    
    /*
                             Implementacão de código
     */
    
    int contador_caracteres = 4;
    
    //Escrever o inicio do LCD - "Mars Rocks_Teste Teclado" - LCD_inicio.h
    LCD_inicio_teste();
    
    //Interrupcão do Timer para acender LED
    TMR0_SetInterruptHandler (Timer_0);
    
    //Interrupcões dos botões das colunas do teclado para detetar uma tecla pressionada
    INT0_SetInterruptHandler (teclado_coluna_1);
    INT1_SetInterruptHandler (teclado_coluna_2);
    INT2_SetInterruptHandler (teclado_coluna_3);
    
    //Interrupcão do ADC - Quando ocorre, executa a funcao ADC_temperatura
    ADC_SetInterruptHandler(ADC_temperatura);
    
    CCP1CONbits.CCP1M = 0000; //desativa o PWM - desliga o sounder no inicio
    
    temp_alarme = 25; //Por default a temperatura de alarme esta a 20 C
    
    menu_estado = 1; //Por default o menu que aparece no terminal e o principal 
    
    menu_entrada = 1; //Por default tem autorizacao para entrar nos menus 
    
    enter = 1; //Por default o enter está = 1 porque o alarme só tem premissão quando ele está ativado
    
    while (1)
    {   
        
        if (temp_ambiente >= temp_alarme && enter == 1){
        
            CCP1CONbits.CCP1M = 1100; //ativa o PWM - liga o sounder
            alarme_ativo = 1; 
            
        }
        else if (temp_ambiente < temp_alarme && enter == 1){
        
            CCP1CONbits.CCP1M = 0000; //desativa o PWM - desliga o sounder
            alarme_ativo = 0;
            LATAbits.LATA1 = 0; //desliga o LED quando o alarme é desativado
            
        }
        
        if ((menu_estado == 1 && menu_entrada == 1) || (menu_estado == 1 && temp_mudou == 1 && temp_ambiente != 0)){ //Menu principal 
            printf("\r\n---------------Menu principal---------------");
            printf("\r\n\nTemperatura atual = %dºC", temp_ambiente);
            
            if (alarme_ativo == 1){
                printf("\r\nEstado do alarme: Ativo");
            }
            if (alarme_ativo == 0){
                printf("\r\nEstado do alarme: Desativo");
            }
            
            printf("\r\n\nTemperatura de alarme: %dºC", temp_alarme);
            
            printf ("\r\nAlterar temperatura de alarme? [Y]: ");
            
            menu_entrada = 0;
        }
        
        if (menu_estado == 0 && menu_entrada == 1){ //Sub-menu
            printf("\r\n-----------------Sub-menu-------------------");
            printf("\r\n\nTemperatura de alarme: %dºC", temp_alarme);
            printf("\r\nIntroduza a nova temperatura de alarme: ");
            
            
            
            menu_entrada = 0;
        }
        
//        if (limpar_terminal){ //Dar scroll na pagina do terminal
//            
//            
//            limpar_terminal = 0;
//        }
       
        /*Recebe caracter através do modulo EUSART1*/
        if (EUSART1_is_rx_ready()){
            
            enter = 0; 
            
            rxData = EUSART1_Read(); //Atribui o que foi escrito no terminal e que está guardado no EUSART a variavel rxData
            
            if (rxData == 13){ //Se carregar enter passa para o Menu principal 
                
                printf("%c", 12); //Limpa o terminal
                
                if (temp_alarme >=10 && temp_alarme <=50){
                
                    if (menu_estado == 0){ //Vai do menu secundário para o principal 
                        menu_estado = 1;
                        menu_entrada = 1; //Autorizacao para entrar no if dos menus
                    }
                    limpar_terminal = 1; //Quando se muda de menu, dá scroll na pagina do terminal

                    enter = 1; //Deteta quando a temperatura introduzida de alarme é confirmada com o enter

                    memset(temp_alarme_string, '\0', sizeof temp_alarme_string); //Limpar a string temp_alarme_string para não 
                                                                                 //haver sobreposicão de caracteres quando se quer introduzir mais do que 1 vez
                }
                else{ //Pede novamente a temperatura caso a anterior seja inválida
                    printf("\r\n\n------------TEMPERATURA INVÁLIDA------------");
                    printf("\r\n\nTemperatura de alarme: %dºC", temp_alarme);
                    printf("\r\nIntroduza a nova temperatura de alarme: ");
                    memset(temp_alarme_string, '\0', sizeof temp_alarme_string);
                }
            }
            if (rxData == 'Y' || rxData == 'y'){
                
                if (menu_estado == 1){ //Vai do menu principal para o secundário
                    printf("%c", 12); //Limpa o terminal
                    menu_estado = 0;
                    menu_entrada = 1; //Autorizacao para entrar no if dos menus
                }
                limpar_terminal = 1; //Quando se muda de menu, dá scroll na pagina do terminal
            }
            
            if ((rxData == '0' || rxData == '1' || rxData == '2' || rxData == '3' || rxData == '4' || rxData == '5' || rxData == '6' || rxData == '7' || rxData == '8' || rxData == '9') && menu_estado == 0){
                
                temp_alarme_intro = rxData;
                 EUSART1_Write(rxData); //Devolve para o terminal o que foi introduzido pelo utilizador para ele ver o que esta a escrever
                 //Adicionar o caracter introduzido no terminal à string temp_alarme_intro com a funcao strncat
                 strncat(temp_alarme_string, &temp_alarme_intro, 1);
                 //transforma o a temp_alarme_string de string para temp_alarme int
                 temp_alarme = atoi (temp_alarme_string);
            }
            

                
//                Printfs para teste
//                printf("\r\n temp_alarme_string: %s", temp_alarme_string);
//                printf("\r\n temp_alarme: %d", temp_alarme);
        }
        
        //Escrever no LCD a temperatura
        sprintf(temp_ambiente_LCD, "temp = %dC", temp_ambiente);
        
        WriteCmdXLCD(LCD_linha_1);
        while (BusyXLCD());
            /*
             * Escreve conteúdo da string 'temp_ambiente_LCD' para o LCD,
             * na posição anteriormente endereçada
             */
            /*temp_ambiente_LCD*/
        putsXLCD(temp_ambiente_LCD);
        while (BusyXLCD());
        
        
        
        
        if (tecla_n){
            
            /*PIN*/
            //Adicionar o caracter da tecla premida à string PIN com a funcao strncat
            strncat(pin, &tecla_premida, 1);
            
            /*TESTAR A FUNCAO strncat*/
            
            WriteCmdXLCD(LCD_linha_2);
            while (BusyXLCD());

            /*
             * Escreve conteúdo da string 'pin' para o LCD,
             * na posição anteriormente endereçada
             */
            /*PIN*/
            putsXLCD(pin);
            while (BusyXLCD());
            
            //escrever_texto_LCD (LCD_linha_2,pin);
            
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