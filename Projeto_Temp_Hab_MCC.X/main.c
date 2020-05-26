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
char temp_alarme_LCD [40]; //String para fazer print da temperatura de alarme no LCD
char temp_ambiente_LCD [40]; ////String para fazer print da temperatura do sensor no LCD
int digitos_introduzidos_alarme; //Conta os caracteres introduzidos no teclado
int menu_estado_LCD; //Variavel binaria -Troca entre menus
                //Se menu_estado_LCD = 1, aparecera no LCD o menu para mudar a temperatura.
                //Se menu_estado_LCD = 0, aparecera no LCD o menu principal.
/*
         PIN
 */
int menu_pin; //Variavel binaria -So quando carrego no '*' do teclado é que vai para o menu
int introduzir_pin; //Variavel binaria -No inicio, terá que introduzir sempre o PIN quando pretende mudar a temperatura
int pin_introduzido; // Guarda o valor do PIN introduzido para ter acesso
char pin_intr_string [5]; // Valor do PIN introduzido
int pin_real = 0000; // Valor do PIN - o introduzido terá que ser igual a este
int digitos_introduzidos_pin; //Contador de digitos introduzidos para quando se esta a introduzir um pin - max 4 digitos
int mudar_pin; //Variavel binaria -Se mudar_pin = 1, muda o PIN. Se = 0, permite o resto das funcionalidades do LCD
int pin_mudado; //Variavel que compara com o pin_real quando se esta a mudar o PIN - confirmacao
int estado_pin_alterado; //Variavel binaria -Saber quando o pin foi alterado
int menu_mudar_pin; //Variavel binaria -Usada dentro da funcionalidade de mudar o PIN - Se = 1 pede para confirmar o atual; Se = 0 para alterar o atual
char pin_mudado_string [5]; //String intermediaria para quando se esta a alterar o PIN
/*
         Temperatura
 */
unsigned char temp_alarme_intro; // Guarda o valor de temperatura de alarme introduzido para passar para inteiro
char temp_alarme_string [4]; // Valor da temperatura de alarme 
int temp_alarme_provisoria; //EUSART - Serve de intermediario para comparacao - desta maneira, o alarme nao e ativado enquanto se muda a temperatura 
int temp_alarme; //Temperatura de alarme 
int temp_mudou; //Variavel binaria -Indica quando a temperatura mudou na funcao do ADC - Para dar refresh no menu do LCD para mostrar a temperatura alterada 
int temp_alarme_mudou; //Variavel binaria -quando a temperatura de alarme e atualizada no terminal, atualizar tambem no LCD
int update_temp_alarme; //Variavel binaria -quando a temperatura de alarme e atualizada no LCD, atualizar tambem no terminal
int EUSART_mudar_temp_alarme; //Variavel binaria -Para nao ser possivel mudar a temperatura ao mesmo tempo no terminal e no LCD
int LCD_mudar_temp_alarme; //Variavel binaria -Para nao ser possivel mudar a temperatura ao mesmo tempo no terminal e no LCD
/*
         ADC
 */
float tensao; //Calculo da tensao do sensor analogico 
int codigo_digital; // 2 bits mais significativos do codigo digital de 10 bits
//char low [8] = ADRESL; // 8 bits menos significativos do codigo digital de 10 bits
int temp_ambiente; //Temperatura do sensor
int temp_ambiente_anterior; //Verificar se a temperatura varia - usada no ADC
/*
        Alarme
 */
int alarme_ativo; //Variavel binaria - Se o alarme esta ativc
int buzzer_intermitencia; //Variavel binaria -Se = 1, ativa, se = 0, desliga com intermitência de 2 segundos
/*
        Terminal
 */
int menu_estado; //Variavel binaria -Se menu_estado = 1, aparecera no terminal o menu principal.
                 //Variavel binaria -Se menu_estado = 0, aparecera no terminal o menu para mudar a temperatura.
int menu_entrada;
int limpar_terminal; //Dá scroll na página
int enter; //Variavel binaria -Verifica quando o enter é pressionado 
int temp_valida; //Variavel binaria -Verifica a temperatura de alarme introduzida
uint8_t rxData; 


/*
                         Funcões 
 */

//Testar LED com interrupcão do Timer 0 & interrupcões do telcado 
void Timer_0 (void) { //LED + ADC
    if (alarme_ativo == 1){
        led_Toggle();
    }
    ADC_StartConversion();
}

void enable_pin(void){ //A cada 60 segundos, mete a variavel introduzir_pin = 1 - desta forma, cada vez que introduz o PIN, nao ha filhos a gozar com o Pai

    if (introduzir_pin == 0 && menu_pin == 0 ){
    
        introduzir_pin = 1;
    
    }

}

void intermitencia_buzzer(void){

    if (alarme_ativo == 1){
        if (buzzer_intermitencia == 1){
            buzzer_intermitencia = 0;
        }
        else{
            buzzer_intermitencia = 1;
        }
    }
    
}



void ADC_temperatura (void){
    
    codigo_digital = ADC_GetConversionResult(); //Obter codigo digital do conversor ADC
    
    //Calculo da Temperatura ambiente
    //temp_ambiente = (int)(((((float) codigo_digital * (3.4/1024.0))-0.3)-0.400) / (0.0195));
    
    //Na formula anterior nao tinha arredondamentos e trabalhava com varios digitos, por exemplo, o codigo_digital quando lia 15,555555 lia o valor errado
    tensao = ((3.4)*(float)(codigo_digital/1024.0)) - 0.3; 
    tensao = (int) ((tensao * 100) + 0.5);
    tensao = (float) tensao/100;
    
    temp_ambiente = (int) ((tensao - 0.400)/0.0195); //Valor inteiro da temperatura ambiente 
    
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

    // Enable high priority global interrupts
    INTERRUPT_GlobalInterruptHighEnable();
 
    /*
                             Implementacão de código
     */
       

    
    CCP1CONbits.CCP1M = 0000; //desativa o PWM - desliga o sounder no inicio
    T1CONbits.TMR1ON = 0; //Comeca com o Timer 0 desativado - e apenas ativado quando se introduz o PIN para alterar a temperatura
    //Escrever o inicio do LCD - LCD.c
    LCD_inicio();
    
    //Interrupcão do Timer para acender LED
    TMR0_SetInterruptHandler (Timer_0);
    
    //Interrupcões dos botões das colunas do teclado para detetar uma tecla pressionada
    INT0_SetInterruptHandler (teclado_coluna_1);
    INT1_SetInterruptHandler (teclado_coluna_2);
    INT2_SetInterruptHandler (teclado_coluna_3);
    
    TMR1_SetInterruptHandler (enable_pin); //De 1 em 1 minuto, da enable para introduzir pin cada vez que se quer introduzir nova temp alarme
    
    TMR3_SetInterruptHandler (intermitencia_buzzer); //Intermitencia do buzzer 
    
    
    //Interrupcão do ADC - Quando ocorre, executa a funcao ADC_temperatura
    ADC_SetInterruptHandler(ADC_temperatura);
    
    temp_alarme = 25; //Por default a temperatura de alarme esta a 20 C 
    
    menu_estado = 1; //Por default o menu que aparece no terminal e o principal 
    
    menu_entrada = 0; //Por default tem autorizacao para entrar nos menus 
    
    enter = 1; //Por default o enter está = 1 porque o alarme só tem premissão quando ele está ativado  
    
    menu_estado_LCD = 0; //Por default no LCD não pede para mudar a temperatura de alarme
    
    digitos_introduzidos_alarme = 0; //Por default, nao ha digitos introduzidos
    
    digitos_introduzidos_pin = 0; 
    
    update_temp_alarme = 0; //Por default, o alarme nao foi atualizado
    
    temp_alarme_mudou = 0; //Por default, a temperatura de alarme nao mudou
    
    EUSART_mudar_temp_alarme = 0; //Desativa a variavel de que se esta a mudar a temp. de alarme
    
    LCD_mudar_temp_alarme = 0; //Disable do Timer 1
    
    introduzir_pin = 1; //Por default, tera que introduzir o PIN
    
    menu_pin = 0; //So quando se carrega no '*' é que ativa o menu, logo por default está desativado
    
    mudar_pin = 0; //Por default, nao se pretende mudar o PIN
    
    menu_mudar_pin = 1; //Por default para mudar de PIN, pede primeiro o atual
    
    estado_pin_alterado = 0; //Por default, o pin nao foi alterado
    
    buzzer_intermitencia = 1; //Por default, quando o alarme e ativado o buzzer comeca a apitar instantaneamente

    while (1)
    {   
        
        if (introduzir_pin == 0){ //Cada vez que e introduzido o pin, ele ira contar 1 minuto para depois ter que se introduzir outra vez
        
            T1CONbits.TMR1ON = 1; //Enable do Timer 1
        
        }
        
        
        if (temp_ambiente >= temp_alarme){ //Ativar o alarme 
            
            alarme_ativo = 1; 
            //Intermitencia do buzzer - Timer3
            if (buzzer_intermitencia == 1){
                CCP1CONbits.CCP1M = 1100; //ativa o PWM - liga o sounder 
                
                WriteCmdXLCD(0b11010011); //Endereço do display, 2ºlinha 20ºcoluna
                while (BusyXLCD());
           
                putcXLCD(0b00000001); //Escrever o caracter personalizado na posição anteriormente endereçada
                while (BusyXLCD());
            }
            else if (buzzer_intermitencia == 0){
                CCP1CONbits.CCP1M = 0000; //desativa o PWM - desliga o sounder
                
                WriteCmdXLCD(0b11010011); //Endereço do display, 2ºlinha 20ºcoluna
                while (BusyXLCD());
           
                putcXLCD(0b00000010); //Escrever o caracter personalizado na posição anteriormente endereçada
                while (BusyXLCD());
            }
        }   
        else if (temp_ambiente < temp_alarme){ //Desativar o alarme
            
            CCP1CONbits.CCP1M = 0000; //desativa o PWM - desliga o sounder
            alarme_ativo = 0;
            LATAbits.LATA1 = 0; //desliga o LED quando o alarme é desativado
            buzzer_intermitencia = 1; //Ativa a variavel de maneira de na proxima vez que o alarme ser ativo comecar instantaneamente/no momento
        }
        
        /*
                     Terminal
         */
        
        
        /*Menu Principal*/ 
        if ((menu_estado == 1 && menu_entrada == 1 && update_temp_alarme == 1) || (menu_estado == 1 && temp_mudou == 1)){ 
            
            
            
            printf("%c" , 12); //Limpa o terminal
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
            
            update_temp_alarme = 0;
        }
        /*Submenu*/ 
        if (menu_estado == 0 && menu_entrada == 1 && EUSART_mudar_temp_alarme == 1 && LCD_mudar_temp_alarme == 0){ 
            printf("\r\n-----------------Sub-menu-------------------");
            printf("\r\n\nTemperatura de alarme: %dºC", temp_alarme);
            printf("\r\nIntroduza a nova temperatura de alarme: ");
            menu_entrada = 0;
        }
        
        /*Recebe caracter através do modulo EUSART1*/
        if (EUSART1_is_rx_ready()){ //Apenas le alguma coisa do eusart quando e possivel mudar de temperatura
            
            enter = 0; 
            
            rxData = EUSART1_Read(); //Atribui o que foi escrito no terminal e que está guardado no EUSART a variavel rxData
            
            if (rxData == 13 && EUSART_mudar_temp_alarme == 1){ //Se carregar enter passa para o Menu principal e apenas deixa aceitar o enter no menu secundario
                
                tecla_n = 0; //Isto porque enquanto eu estou a mudar a temperatura de alarme e carregar no * do keypad, ela fica guardada e depois quando carrego enter abre o menu do LCD
                
                printf("%c", 12); //Limpa o terminal
                
                if (temp_alarme_provisoria >=10 && temp_alarme_provisoria <=50){
                    
                    temp_alarme = temp_alarme_provisoria;
                    
                    EUSART_mudar_temp_alarme = 0;
                    
                    if (menu_estado == 0){ //Vai do menu secundário para o principal 
                        menu_estado = 1;
                        menu_entrada = 1; //Autorizacao para entrar no if dos menus
                    }
                    limpar_terminal = 1; //Quando se muda de menu, dá scroll na pagina do terminal
                    
                    enter = 1; //Deteta quando a temperatura introduzida de alarme é confirmada com o enter
                    
                    update_temp_alarme = 1;
                    
                    temp_alarme_mudou = 1; 
                    
                    memset(temp_alarme_string, '\0', sizeof temp_alarme_string); //Limpar a string temp_alarme_string para não 
                                                                                 //haver sobreposicão de caracteres quando se quer introduzir mais do que 1 vez
                }
                else{ //Pede novamente a temperatura caso a anterior seja inválida
                    printf("\r\n\n------------TEMPERATURA INVÁLIDA------------");
                    printf("\r\n\nTemperatura de alarme inválida: %dºC", temp_alarme);
                    printf("\r\nIntroduza a nova temperatura de alarme: ");
                    memset(temp_alarme_string, '\0', sizeof temp_alarme_string);
                }
            }
            if ((rxData == 'Y' || rxData == 'y') && (LCD_mudar_temp_alarme == 0)){
                
                EUSART_mudar_temp_alarme = 1;
                
                if (menu_estado == 1){ //Vai do menu principal para o secundário
                    printf("%c", 12); //Limpa o terminal
                    menu_estado = 0;
                    menu_entrada = 1; //Autorizacao para entrar no if dos menus
                }
                limpar_terminal = 1; //Quando se muda de menu, dá scroll na pagina do terminal
            }
            
            if ((EUSART_mudar_temp_alarme == 1) && (menu_estado == 0) && (rxData == '0' || rxData == '1' || rxData == '2' || rxData == '3' || rxData == '4' || rxData == '5' || rxData == '6' || rxData == '7' || rxData == '8' || rxData == '9')){
                
                temp_alarme_intro = rxData;
                 EUSART1_Write(rxData); //Devolve para o terminal o que foi introduzido pelo utilizador para ele ver o que esta a escrever
                 //Adicionar o caracter introduzido no terminal por temp_alarme_intro à string temp_alarme_string com a funcao strncat
                 strncat(temp_alarme_string, &temp_alarme_intro, 1);
                 //transforma o a temp_alarme_string de string para temp_alarme int
                 temp_alarme_provisoria = atoi (temp_alarme_string);
            }
            
        }
        
        /*
                     LCD
         */
        
        /*
             MENUS e ACESSOS
         */

        /*Leitura de teclas*/
        
        //Carregar na tecla '#' para mudar o PIN
        if (tecla_n == 1 && tecla_premida == '#' && menu_estado_LCD == 0 && EUSART_mudar_temp_alarme == 0 && mudar_pin == 0){
        
            mudar_pin = 1;
            tecla_n = 0;
            WriteCmdXLCD(LCD_clear);        
            while (BusyXLCD());
            menu_mudar_pin = 1;
        }
        //Se quer sair enquanto esta a mudar o PIN
        if (tecla_n == 1 && tecla_premida == '#' && mudar_pin == 1){ 
        
            mudar_pin = 0;
            tecla_n = 0;
            WriteCmdXLCD(LCD_clear);        
            while (BusyXLCD());
            digitos_introduzidos_pin = 0;
            memset(pin_mudado_string, '\0', sizeof pin_mudado_string); //Limpar a string
            estado_pin_alterado = 1;
        }
        
        /*
         * Permite quando se esta a mudar o PIN
         *
         */
        if (mudar_pin == 1){
             /*Menu mudar PIN - PIN atual*/ 
            if (menu_mudar_pin == 1){ 
                //Escrever no LCD
                WriteCmdXLCD(133);
                while (BusyXLCD());
                putsXLCD("PIN Atual");
                while (BusyXLCD());

                WriteCmdXLCD(LCD_linha_2);
                while (BusyXLCD());
                putsXLCD ("PIN:");
                while (BusyXLCD());
                
                if ((tecla_n == 1) && (tecla_premida == '1' || tecla_premida == '2' || tecla_premida == '3' || tecla_premida == '4' || tecla_premida == '5' || tecla_premida == '6' || tecla_premida == '7' || tecla_premida == '8' || tecla_premida == '9' || tecla_premida == '0')){
                    
                    
                    
                    strncat(pin_mudado_string, &tecla_premida, 1);
                    
                    WriteCmdXLCD(196);
                    while (BusyXLCD());
                    putsXLCD(pin_mudado_string);
                    while (BusyXLCD());
                    
                    digitos_introduzidos_pin++;
                    tecla_n = 0;
                    
                    if (digitos_introduzidos_pin == 4){
                        digitos_introduzidos_pin = 0;
                        pin_mudado = atoi (pin_mudado_string); //Passa de string para numero inteiro 
                        
                        if (pin_mudado == pin_real){
                            menu_mudar_pin = 0;
                            memset(pin_mudado_string, '\0', sizeof pin_mudado_string); //Limpar a string
                            
                            WriteCmdXLCD(LCD_clear);        
                            while (BusyXLCD());
                        }
                        else if (pin_mudado > pin_real || pin_mudado < pin_real){
                           
                            WriteCmdXLCD(LCD_clear);        
                            while (BusyXLCD());
                            
                            WriteCmdXLCD(201);
                            while (BusyXLCD());
                            putsXLCD("INCORRETO");
                            while (BusyXLCD());
                            //__delay_ms (1000);
                            memset(pin_mudado_string, '\0', sizeof pin_mudado_string); //Limpar a string
                        }
                    }
                } 
            }
            /*Menu mudar PIN - PIN novo*/ 
            if (menu_mudar_pin == 0){ 
                WriteCmdXLCD(131);
                while (BusyXLCD());
                putsXLCD("Atualizar PIN");
                while (BusyXLCD());

                WriteCmdXLCD(LCD_linha_2);
                while (BusyXLCD());
                putsXLCD ("PIN:");
                while (BusyXLCD());
                
                if ((tecla_n == 1) && (tecla_premida == '1' || tecla_premida == '2' || tecla_premida == '3' || tecla_premida == '4' || tecla_premida == '5' || tecla_premida == '6' || tecla_premida == '7' || tecla_premida == '8' || tecla_premida == '9' || tecla_premida == '0')){
                    
                    
                    
                    strncat(pin_mudado_string, &tecla_premida, 1);
                    
                    WriteCmdXLCD(196);
                    while (BusyXLCD());
                    putsXLCD(pin_mudado_string);
                    while (BusyXLCD());
                    
                    digitos_introduzidos_pin++;
                    tecla_n = 0;
                    
                    if (digitos_introduzidos_pin == 4){
                        
                        digitos_introduzidos_pin = 0;
                        mudar_pin = 0;
                        
                        pin_real = atoi (pin_mudado_string); //Passa de string para numero inteiro 
                        
                        
                        __delay_ms (500);
                        
                        WriteCmdXLCD(LCD_clear);        
                        while (BusyXLCD());
                        
                         WriteCmdXLCD(130);
                        while (BusyXLCD());
                        putsXLCD("Atualizado com");
                        while (BusyXLCD());

                        WriteCmdXLCD(196);
                        while (BusyXLCD());
                        putsXLCD ("Sucesso");
                        while (BusyXLCD());
                        
                        __delay_ms (500);
                        
                        WriteCmdXLCD(LCD_clear);        
                        while (BusyXLCD());
                        
                        estado_pin_alterado = 1;
                        
                        memset(pin_mudado_string, '\0', sizeof pin_mudado_string); //Limpar a string
                    }
                    
                }
            }   
        }
    
       
        /*
         * Permite quando nao esta a mudar o PIN
         *
         */
        if (mudar_pin == 0){
            
            /*Leitura de teclas*/
            
            //Carregar na tecla '*' para mudar a temperatura de alarme e trocar entre menus
            //Passar do menu principal para o submenu para mudar a temp
            if (tecla_n == 1 && tecla_premida == '*' && menu_estado_LCD == 0 && EUSART_mudar_temp_alarme == 0 && introduzir_pin == 0){ 
                menu_estado_LCD = 1;
                WriteCmdXLCD(LCD_clear);        
                while (BusyXLCD());
                tecla_n =0;
                LCD_mudar_temp_alarme = 1;
            }
            
            //Carregar no '*' quando se esta no menu principal e se quer alterar a temp mas tem que se introduzir o PIN
            if (tecla_n == 1 && tecla_premida == '*' && menu_estado_LCD == 0 && EUSART_mudar_temp_alarme == 0 && introduzir_pin == 1 && menu_pin == 0){
                LCD_mudar_temp_alarme = 1;
                menu_pin = 1;
                WriteCmdXLCD(LCD_clear);        
                while (BusyXLCD());
                tecla_n = 0;
            }
            
            //Passar do submenu de mudar a temp para o menu principal
            if (tecla_n == 1 && tecla_premida == '*' && menu_estado_LCD == 1){ 
                digitos_introduzidos_alarme = 0;  
                menu_estado_LCD = 0; 
                temp_alarme_mudou = 1; 
                WriteCmdXLCD(LCD_clear);         
                while (BusyXLCD()); 
                tecla_n =0;  
            }

            /*Menu principal*/ 
            
            if ((((menu_estado_LCD == 0 && temp_mudou == 1) || (menu_estado_LCD == 0 && temp_alarme_mudou == 1)) && menu_pin == 0) || estado_pin_alterado == 1){ 

                memset(temp_alarme_string, '\0', sizeof temp_alarme_string); //Limpar a string temp_alarme_string para não 
                                                                                     //haver sobreposicão de caracteres quando se quer introduzir mais do que 1 vez
                
                estado_pin_alterado = 0;
                temp_alarme_mudou = 0;

                LCD_mudar_temp_alarme = 0;

                //Escrever no LCD a temperatura atual
                sprintf(temp_ambiente_LCD, "Temp. atual = %.0d C            ", temp_ambiente);
                WriteCmdXLCD(LCD_linha_1);
                while (BusyXLCD()); 
                    /*
                     * Escreve conteúdo da string 'temp_ambiente_LCD' para o LCD,
                     * na posição anteriormente endereçada
                     */
                    /*temp_ambiente_LCD*/
                putsXLCD(temp_ambiente_LCD);
                while (BusyXLCD());

                //Escrever no LCD a temperatura de alarme
                sprintf(temp_alarme_LCD, "Temp. alarme = %.0d C", temp_alarme);
                WriteCmdXLCD(LCD_linha_2);
                while (BusyXLCD());
                    /*
                     * Escreve conteúdo da string 'temp_ambiente_LCD' para o LCD,
                     * na posição anteriormente endereçada
                     */
                    /*temp_ambiente_LCD*/
                putsXLCD(temp_alarme_LCD);
                while (BusyXLCD());
            }

            /*Submenu para mudar a temperatura*/
            if (menu_estado_LCD == 1 && menu_pin == 0){ 


                //Escrever no LCD a temperatura de alarme
                sprintf(temp_alarme_LCD, "Temp. alarme = %.0d C            ", temp_alarme);
                WriteCmdXLCD(LCD_linha_1);
                while (BusyXLCD());
                    /*
                     * Escreve conteúdo da string 'temp_ambiente_LCD' para o LCD,
                     * na posição anteriormente endereçada
                     */
                    /*temp_ambiente_LCD*/
                putsXLCD(temp_alarme_LCD);
                while (BusyXLCD());

                WriteCmdXLCD(LCD_linha_2);
                while (BusyXLCD());
                    /*
                     * Escreve conteúdo da string 'temp_ambiente_LCD' para o LCD,
                     * na posição anteriormente endereçada
                     */
                    /*temp_ambiente_LCD*/
                putsXLCD("Nova temp.:");
                while (BusyXLCD());

            }

            



            /*Menu do PIN*/
            if (menu_pin == 1){

                memset(temp_alarme_string, '\0', sizeof temp_alarme_string); //Limpar a string temp_alarme_string para não 
                                                                                         //haver sobreposicão de caracteres quando se quer introduzir mais do que 1 vez

                //Escrever no LCD a mensagem 
                sprintf(temp_alarme_LCD, "Introduza o PIN", temp_alarme);
                WriteCmdXLCD(LCD_linha_1);
                while (BusyXLCD());
                    /*
                     * Escreve conteúdo da string 'temp_ambiente_LCD' para o LCD,
                     * na posição anteriormente endereçada
                     */
                    /*temp_ambiente_LCD*/
                putsXLCD(temp_alarme_LCD);
                while (BusyXLCD());

                WriteCmdXLCD(LCD_linha_2);
                while (BusyXLCD());

                putsXLCD("PIN:");
                while (BusyXLCD());

            }
            //Quando se esta dentro do menu do PIN e se quer sair para o menu principal 
            if (tecla_n == 1 && tecla_premida == '*' && menu_pin == 1){

                LCD_mudar_temp_alarme = 0;
                menu_pin = 0;
                WriteCmdXLCD(LCD_clear);        
                while (BusyXLCD());
                tecla_n = 0;
                temp_alarme_mudou = 1; //Assim, consegue regressar ao menu
            }


            //CONDICOES

            if (menu_pin == 0){ 

                if ((menu_estado_LCD == 1 && tecla_n == 1) && (tecla_premida == '1' || tecla_premida == '2' || tecla_premida == '3' || tecla_premida == '4' || tecla_premida == '5' || tecla_premida == '6' || tecla_premida == '7' || tecla_premida == '8' || tecla_premida == '9' || tecla_premida == '0')){ //Mudar temperatura de alarme no LCD
                        //Adicionar o caracter introduzido no teclado por tecla_premida à string temp_alarme_string com a funcao strncat
                        strncat(temp_alarme_string, &tecla_premida, 1);
                        WriteCmdXLCD(203);
                        while (BusyXLCD());
                        
                        
                        putsXLCD(temp_alarme_string);
                        while (BusyXLCD());

                        digitos_introduzidos_alarme++;



                    if (digitos_introduzidos_alarme == 2){ //Quando se introduz dois digitos, é como se desse automaticamente "enter"

                        __delay_ms (500); //Para o segundo caracter introduzido se ver

                        WriteCmdXLCD(LCD_clear);        
                        while (BusyXLCD());

                        //transforma o a temp_alarme_string de string para temp_alarme int
                        temp_alarme_provisoria = atoi (temp_alarme_string);

                        digitos_introduzidos_alarme = 0;

                        if (temp_alarme_provisoria >= 10 && temp_alarme_provisoria <= 50){

                            temp_alarme = temp_alarme_provisoria;

                            menu_estado_LCD = 0;

                            temp_alarme_mudou = 1;

                            menu_entrada = 1; //Autorizacao para entrar no if dos menus

                            update_temp_alarme = 1;
                            memset(temp_alarme_string, '\0', sizeof temp_alarme_string); //Limpar a string temp_alarme_string para não 
                                                                                         //haver sobreposicão de caracteres quando se quer introduzir mais do que 1 vez
                        }
                        else {

                            memset(temp_alarme_string, '\0', sizeof temp_alarme_string); //Limpar a string temp_alarme_string para não 
                                                                                         //haver sobreposicão de caracteres quando se quer introduzir mais do que 1 vez

                            WriteCmdXLCD(132);
                            while (BusyXLCD());
                                /*
                                 * Escreve conteúdo da string 'temp_ambiente_LCD' para o LCD,
                                 * na posição anteriormente endereçada
                                 */
                                /*temp_ambiente_LCD*/
                            putsXLCD("TEMPERATURA");
                            while (BusyXLCD());

                            WriteCmdXLCD(197);
                            while (BusyXLCD());
                                /*
                                 * Escreve conteúdo da string 'temp_ambiente_LCD' para o LCD,
                                 * na posição anteriormente endereçada
                                 */
                                /*temp_ambiente_LCD*/
                            putsXLCD("INVALIDA !");
                            while (BusyXLCD());

                            __delay_ms (2000);

                            WriteCmdXLCD(LCD_clear);        
                            while (BusyXLCD());
                        }

                    }
                    tecla_n = 0;
                }
            }

            else if (menu_pin == 1){

                if (tecla_n == 1 && (tecla_premida == '1' || tecla_premida == '2' || tecla_premida == '3' || tecla_premida == '4' || tecla_premida == '5' || tecla_premida == '6' || tecla_premida == '7' || tecla_premida == '8' || tecla_premida == '9' || tecla_premida == '0')){ //Introduzir PIN

                    //Adicionar o caracter introduzido no teclado por tecla_premida à string temp_alarme_string com a funcao strncat
                        strncat(pin_intr_string, &tecla_premida, 1);
                        WriteCmdXLCD(196);
                        while (BusyXLCD());

                        /*
                         * Escreve conteúdo da string 'pin' para o LCD,
                         * na posição anteriormente endereçada
                         */
                        putsXLCD(pin_intr_string);
                        while (BusyXLCD());

                        digitos_introduzidos_pin++; //Contador de digitos introduzidos 

                        tecla_n = 0;

                        if (digitos_introduzidos_pin == 4){

                            pin_introduzido = atoi (pin_intr_string);

                            if (pin_introduzido == pin_real) {

                                strncat(pin_intr_string, &tecla_premida, 1);

                                WriteCmdXLCD(LCD_clear);        
                                while (BusyXLCD());

                                memset(pin_intr_string, '\0', sizeof temp_alarme_string); //Limpar a string 
                                digitos_introduzidos_pin = 0;  
                                menu_pin = 0;
                                introduzir_pin = 0;
                                menu_estado_LCD = 1;



                            }
                            else if (pin_introduzido > pin_real || pin_introduzido < pin_real){
                                
                                
                                WriteCmdXLCD(LCD_clear);        
                                while (BusyXLCD());
                                
                                strncat(pin_intr_string, &tecla_premida, 1);
                                WriteCmdXLCD(201);
                                while (BusyXLCD());
                                putsXLCD("INCORRETO");
                                while (BusyXLCD());

                                //__delay_ms (1000);


                                memset(pin_intr_string, '\0', sizeof temp_alarme_string); //Limpar a string 
                                digitos_introduzidos_pin = 0;
                            }

                        }
                }
            }     
        }
    
            /*Loop para atribuir valores a todos os outputs para as linha do teclado*/

            //LATB = 0b11110111;
            /**/
            LATBbits.LATB3 = 0;
            LATBbits.LATB4 = 1;
            LATBbits.LATB5 = 1;
            LATBbits.LATB6 = 1;
            /**/
            __delay_ms (60); //Delay's porque se carregassemos numa tecla, ele escrevia um numero 3x seguidas
            //LATB = 0b11101111;
            /**/
            LATBbits.LATB3 = 1;
            LATBbits.LATB4 = 0;
            LATBbits.LATB5 = 1;
            LATBbits.LATB6 = 1;
            /**/
            __delay_ms (60);
            //LATB = 0b11011111;
            /**/
            LATBbits.LATB3 = 1;
            LATBbits.LATB4 = 1;
            LATBbits.LATB5 = 0;
            LATBbits.LATB6 = 1;
            /**/
            __delay_ms (60);
            //LATB = 0b10111111;
            /**/
            LATBbits.LATB3 = 1;
            LATBbits.LATB4 = 1;
            LATBbits.LATB5 = 1;
            LATBbits.LATB6 = 0;
            /**/
            __delay_ms (50);    
    }
}
/**
 End of File
*/