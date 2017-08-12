/*
Firmware para PIC18F4431 do Robô METALGARURUMON da equipe FEG-Robótica
Data da última atualização 04/08/2017
Responsável atual: Silas Vergilio
Versão: 5.0
*/
#include<18f4431.h> //Adiciona biblioteca referente ao microcontrolador adequado(PIC15F4431)
#device adc=10 //Define a resolução do conversor A/D do microcontrolador
#fuses HS, NOWDT, NOPROTECT, NOBROWNOUT, NOPUT, NOLVP //Define algumas Configurações do PIC
#use delay(clock=20000000) //definição do cristal externo usado(na linha superior foi definido usar um cristal rápido HS), em Hz, no caso 20Mhz

/*
HS - Significa que estamos usando um cristal de alta velocidade (no caso 20Mhz)
NOWDTH - Não desejamos nos usar do WatchDog Timer, que impede que o programa "trave" dentro de loops infinitos ou algo assim. Nosso robô depende de um loop infinitos
NOPROTECT - O código não é protegido,portanto é possível acessar ele a partir do microcontrolador
NOLVP - Desabilita programação em baixa tensão.
*/ 

//Configuração da comunicação rs232 usada para comunicar com o módulo Bluetooth
#use rs232(BAUD=9600,UART1, XMIT=PIN_C6, RCV=PIN_C7, PARITY= N, BITS = 8, STREAM = BT) 
/*
Baud Rate é a taxa de transferência de bits da comunicação, é importante que quem recebe e quem envia os faça a mesma taxa.
XMIT define o pino que irá transmitir informações
RCV define o pino que irá receber informações
PARITY é o tipo de paridade que será usada na comunicação
STREAM define a id usada nas funções da comunicação serial
Bits = define o tamanho máximo da cada palavra da comunicação
*/
#include "metalgarurumon_reference.c" //Inclui bibliotea de funcoes para o metalgarurumon
#include<stdlib.h>
#PRIORITY INT_TIMER0,INT_RDA,INT_TIMER1,INT_TIMER5 //Define as prioridades do das interrupcoes

#INT_RDA
void RDA_isr(void)
{
  
  if(LIGA == 0)
  {
     gets(leitura_bt); //Obtem string da serial (bluetooth no caso)
     leitura_bt_int = atoi(leitura_bt);
     LIGA = 1; 
     primeiro_inicio = 1;
     set_estrategia(leitura_bt_int);
     imprime_estrategia(busca_inicial, busca_padrao, pre_busca);
     printf("\rEscolha o lado do oponente:\r");
     lado = getc();
  }
  else
  {
   gets(leitura_bt);
   leitura_bt_int = atoi(leitura_bt);
   if(leitura_bt_int == 0)
   {
      LIGA = 0;
   }
   
  }
  

}

#int_TIMER1 //deritiva de programacao que indica que o  codigo abaixo eh acionado cada vez que o contador Timer1 da uma a flag de overflow
void TIMER1_isr (void)
{

    overflow_timer1++; //Variável que conta quantas vezes o timer1 deu overflow
   
    set_timer1(0); //Reseta o Timer para que ele faça uma nova contagem
    
    if(overflow_timer1 == 20) //O contador dá overflow aproximadamente 612 vezes em 2 segundos (valor hipotético) 
    {
  //  printf("Interrupt \n");
    overflow_timer1 = 0;
    mover = 1;
   }

}
#int_TIMER5 //Timer usado tanto para o Trigger quanto o Echo do Sensor Ultrassonica HC-04
void TIMER5_isr(void)
{
   #if ULTRASSONICO
   if(enable_overflow_count) 
   {
      contador_overflows_timer5++;  
   }
   #endif
   
   cont_timer5++; 
   if(cont_timer5 == TEMPO_ATACANDO)
   {
      resposta_sensores = 0b11111110;
      cont_timer5 = 0;
   }
   
   
}
//Timer responsavel por impedir que o robo fique muito tempo no mesmo estado
#int_TIMER0 //Diretiva de programacoa que indica que o codigo abaixo eh acionado cada vez que o contador Timer0 da uma flag de overflow
void TIMER0_isr (void)
{
   overflow_timer0++; 
   set_timer0(0); //Reseta o Timer para que ele faça uma nova contagem
}
void main()
{

   config(); //Executa rotina de configurações 
   
   disable_interrupts(INT_TIMER0);
   disable_interrupts(INT_TIMER1);
   disable_interrupts(INT_TIMER5);


   
   while(true) //Ciclo principal do software
   {
    while(LIGA == 0)
    {
    //Desliga os motores quando o robô é desligado via celular
    motor_1(0,'f');
    motor_2(0,'f');
    if(primeiro_inicio == 0)
    {
      printf("\rDigite a string responsavel pela estrategia\r");
      primeiro_inicio = 1;
    }
    //Liga dois leds para indicar que o robô está ligado
    output_high(LED_0); 
    output_low(LED_1);
    //Desabilita interrupções quando o robô não foi acionado
    disable_interrupts(INT_TIMER1);
    disable_interrupts(INT_TIMER0);
    disable_interrupts(INT_TIMER5);
    enable_interrupts(INT_RDA);
    enable_interrupts(global);
    
    //Reseta as variáveis de controle do overflow dos Timers
    overflow_timer1 = 0;
    overflow_timer0 = 0;
    cont_timer5 = 0;
    primeira_busca = 1;
    }
   
   while(LIGA == 1)
   {  
      if(primeiro_inicio == 1)
         {
         if(primeiro_inicio == 1) primeiro_inicio = 2;
         }
         LIGA = 2;
   }
   
   while(LIGA == 2)
   {     
         disable_interrupts(INT_TIMER0);
         disable_interrupts(INT_TIMER1);
         disable_interrupts(INT_TIMER5);
         
         if(primeiro_inicio == 2)
         {
         printf("\rBem vindo ao software do MetalGarurumon\r");
         set_timer0(0); //Inicializa o timer0
         set_timer1(0); //Inicializa o timer1
         set_timer5(0); //Inicializa o timer5
         primeiro_inicio = 0;
         printf("\r Lado: %c \r",lado);
        // delay_ms(4700);
         }
         //Liga o Led que indica que o robô está ligado
         output_high(LED_1);
         output_low(LED_0);
         
         sensores();     

            
} //While LIGA
    

   }
}

