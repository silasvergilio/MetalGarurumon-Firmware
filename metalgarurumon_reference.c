#include "metalgarurumon_reference.h"
#include "metalgarurumon_estrategias.c"

void config()
{
   /*Definindo a deirecao de cada uma das portas, A, B, C, D, E.
1 indica input e 0 output e a ordem se d√° da seguinte maneira
e.g.

set_tris_a(a7,a6,a5,a4,a3,a2,a1,a0);

*/
   set_tris_a(0b11111111);
   set_tris_b(0b00000000);
   set_tris_c(0b10111111);
   set_tris_d(0b00000000);
   set_tris_e(0b1101);

//Configuracao dos modulos PWM do PIC18F2431
   setup_power_pwm_pins(PWM_BOTH_ON,PWM_BOTH_ON,PWM_BOTH_ON,PWM_BOTH_ON); // Configura os 4 m√≥dulos PWM.
   setup_power_pwm(PWM_FREE_RUN, 1, 0, POWER_PWM_PERIOD, 0, 1,30);
   
   /*
   FREE RUN eh o modo mais aconselhado para mover motores DC, outros modos podem controlar de maneiras espec√≠ficas, dividindo a frequ√™ncia
   o modo UP/DOWN aparentemente √© mais eficiente, √© preciso mais testes para garantir isso.
   
   1 indica o postscale usado na sa√≠da do PWM, o postscale divide a frequ√™ncia que recebe por um n√∫mero, no caso n√£o estamos dividindo por nada
   
   0 indica o valor inicial da contagem do Timer respons√°vel pela gera√ß√£o do pwm
   
   POWER_PWM_PERIOD √© o per√≠odo do PWM, isso pode controlar a frequ√™ncia do PWM de acordo com o per√≠odo
   
   0  o compare, ele compara esse valor com o valor do timer para verificar se algum evento especial deveria acontecer
   
   1 o postscale compare,ele afeta o compare utilizado no par√¢metro anterior.
   
   30 o dead time, ele altera a diferen√ßa de tempo entre o ON de um PWM e o OFF de seu complementar
   
   */
   setup_adc_ports(sAN0 | sAN1 | sAN2 | sAN3 | sAN4 | sAN5 | sAN6); //Define que todas as portas que possuem convers√£o A/D ser√£o usadas como convers√£o A/D
   setup_adc(ADC_CLOCK_INTERNAL); //Utiliza o mesmo clock do PIC para o conversor A/D
   enable_motors(); //Controla a habilita√ß√£o das duas ponte H, para desabilitar uma delas, basta mudar o valor das constantes ENA e ENB
   
   enable_interrupts(global); //Habilita interrupÁıes globais
   enable_interrupts(INT_TIMER1); //Habilita interrupÁ„o do Timer1
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8); //Configura Timer1 e uso o pre scaler para dividir por 8;
   
   disable_interrupts(INT_TIMER0);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_2|RTCC_8_BIT); //Configura Timer1 e uso o pre scaler para dividir por 8;
   
   enable_interrupts(INT_TIMER5); //Habilita interrupÁ„o do Timer1
   setup_timer_5(T5_INTERNAL|T5_DIV_BY_1);//Configura Timer5 e divide o seu clock por 1.
   
   enable_interrupts(INT_RDA);
   
 
}

//FunÁ„o que faz a leitura e tratameno de todos os sensores
void sensores()
{
          //faz a leitura do canal adc indicado e poe a resposta no bit indicado da palavra indicada (Sensores de linha)
         // resposta_sensores = leitura_adc(750,canal_sensor_linha_1, resposta_sensores, 0); //Sensor Direito
        //  resposta_sensores = leitura_adc(750,canal_sensor_linha_2, resposta_sensores, 1); //Sensor Esquerdo
         
         //(Sensores de distancia)
         
         resposta_sensores = leitura_adc(320,canal_sensor_distancia_direita, resposta_sensores, 2);
         resposta_sensores = leitura_adc(500,canal_sensor_distancia_frente_direita, resposta_sensores, 3);
         resposta_sensores = leitura_adc(500,canal_sensor_distancia_frente_esquerda, resposta_sensores, 4);
         resposta_sensores = leitura_adc(500,canal_sensor_distancia_esquerda, resposta_sensores, 5);
       
         trata_sensores_2(); //responde com o motor em relacao aos sensores usando uma maquina de estados
}

int8 leitura_adc(int16 threshold, int canal, int8 resposta_leitura, int bit)
{
  
   switch(canal) //switch para preparar o canal desejado para a convers√£o A/D
   {
      case 0: set_adc_channel(0); break;
      case 1: set_adc_channel(1); break;
      case 2: set_adc_channel(2); break;
      case 3: set_adc_channel(3); break;
      case 4: set_adc_channel(4); break;
      case 5: set_adc_channel(5); break;
      case 6: set_adc_channel(6); break;
   }
  
   delay_us(10);            //delay de 10 us (valor suscet√≠vel a erro devido ao uso da interrup√ß√£o do Timer1), importante ser um valor pequeno                          
   leitura = read_adc();    //Realiza a leitura do canal anal√≥gico-digital
  /* 
   if(canal == canal_sensor_linha_1)  printf("*G%Lu*",leitura);
   else if(canal == canal_sensor_linha_2) printf("*P%Lu*",leitura); */
  
   if (leitura > threshold) bit_clear(resposta_leitura,bit); //Caso o sensor retorne 0, a palavra recebe 0 em seu primeiro bit
   else bit_set(resposta_leitura,bit); //Caso sensor retorne 1 , a palavra recebe 1 em seu primeiro bit
   
   
   return resposta_leitura; //devolve a variavel com seus bits alterados

}


  
  void trata_sensores_2() //Trata a resposta aos sensores usando uma espÈcie de maquina de estados
{

 /*
     DiagramaÁ„o dos bits da palavra resposta_sensores
     
     bit 0 - Sensor Linha Direita
     bit 1 - Sensor Linha Esquerda
     bit 2 - Sensor Lateral Direita
     bit 3 - Sensor Frente Direita
     bit 4 - Sensor Frente Esquerda
     bit 5 - Sensor Lateral Esquerda
     
     */
      if ( bit_test(resposta_sensores,0) ) //Verifica isoladamente os sensores de linha
   {
      
      motor_1(0,'b');
      motor_2(0,'b');
      delay_ms(200);
      
      //Anda para tr·s
      motor_1(VELOCIDADE_LINHA,'b');
      motor_2(VELOCIDADE_LINHA,'b');
      delay_ms(TEMPO_LINHA_TRAS_MS);
      
      //Para o motor rapidamen
      
      
      //Gira o robÙ
      motor_1(VELOCIDADE_GIRO_LINHA,'b');
      motor_2(VELOCIDADE_GIRO_LINHA,'f');
      delay_ms(TEMPO_GIRO_LINHA);
      
      estado_sensores = 0;
      mover = 0;
      
      bit_clear(resposta_sensores,0);
     
   }
   
   if ( bit_test(resposta_sensores,1) ) //Verifica isoladamente os sensores de linha
   {
   
       motor_1(0,'b');
       motor_2(0,'b');
       delay_ms(200);
    
      //Anda para tr·s
      motor_1(VELOCIDADE_LINHA,'b');
      motor_2(VELOCIDADE_LINHA,'b');
      delay_ms(TEMPO_LINHA_TRAS_MS);
     
      
      //Gira o robÙ
      motor_1(VELOCIDADE_GIRO_LINHA,'f');
      motor_2(VELOCIDADE_GIRO_LINHA,'b');
      delay_ms(TEMPO_GIRO_LINHA);
      
      estado_sensores = 0;
      mover = 0;
      
      bit_clear(resposta_sensores,0);
   }
   
   if(estado_sensores == 0) //Estado em que nenhum sensor foi visto, estado inicial do robo
   {
   disable_interrupts(INT_TIMER5);
   disable_interrupts(INT_TIMER0);
      if(!primeira_busca)
      {
      //Executa estrategia padrao para localizacao do adversario em qualquer ponto da partida depois de ter achado uma vez
      
        switch(busca_padrao)
      {
         case 1: busca_passiva(); break;
         case 2: busca_twister(lado); break;
         case 3: busca_agressiva(); break;
      }
      
      }
      else{
      
        switch(busca_inicial)
      {
         case 0: busca_passiva(); break;
         case 1: busca_twister(lado); break;
         case 2: busca_arco(lado); break;
         case 3: busca_agressiva(); break;
         case 4: busca_pulso(); break;
      }
      
      }
      
      if(mover) //Executa um pequeno movimento caso tenha dado overflows o suficiente
      {
         motor_1(50,'f');
         motor_2(50,'f');
         delay_ms(50);
      //  printf("Moveu\n");
         mover = 0;
      }
      
      
      switch(resposta_sensores)
      {
      case 0b00000000: estado_sensores = 0; break;
      case 0b00000100: estado_sensores = 1; break;
      case 0b00001100: estado_sensores = 2; break;
      case 0b00011000: estado_sensores = 2; break;
      case 0b00001000: estado_sensores = 2; break;
      case 0b00100000: estado_sensores = 3; break;
      case 0b00110000: estado_sensores = 2; break;
      case 0b00010000: estado_sensores = 2; break;
      
      default: estado_sensores = 0; break;
      }
   }
   
   if(estado_sensores == 1)
   {
      motor_1(50,'f');
      motor_2(50,'b');
      primeira_busca = 0;
      disable_interrupts(INT_TIMER5);
      disable_interrupts(INT_TIMER1); //Timer para estratÈgia inicial de busca
      enable_interrupts(INT_TIMER0); //Timer para fazer volta em torno do proprio eixo
     // printf("Estado Atual: %d \r",estado_sensores);
     
      if(overflow_timer0 >= 1000)  estado_sensores = 0b000000000; goto fim1;
    
      
      switch(resposta_sensores)
      {
      case 0b00011000: estado_sensores = 2; break;
      default: estado_sensores = 1;  break;
      }
      fim1:
      estado_sensores = estado_sensores;
   }
   
   if(estado_sensores == 2)
   {
      disable_interrupts(INT_TIMER5); //Aciona Timer para ataque cronometrado
      //Move ambos motores para o araque
      motor_1(VELOCIDADE_ATAQUE,'f');
      motor_2(VELOCIDADE_ATAQUE,'f');
      //Indica que o robo ja achou um adversario uma vez pelo menos
      primeira_busca = 0;
      //Desabilita interrupÁıes de giro do motor e de pulso de movimento
      disable_interrupts(INT_TIMER1);
      disable_interrupts(INT_TIMER0);
      //Zera contagem de overflows do timer0
      overflow_timer0 = 0; 
      
      switch(resposta_sensores)
      {
      case 0b00011000: estado_sensores = 2; break;
      case 0b00010000: estado_sensores = 2; break;
      case 0b00001000: estado_sensores = 2; break;
      case 0b11111110: evasao(); estado_sensores = 0; resposta_sensores = 0b00000000; break; 
      
      default: estado_sensores = 0; break;
      
      }
      
   }
   
   
   if(estado_sensores == 3)
   {
      
      motor_1(50,'b');
      motor_2(50,'f');
      primeira_busca = 0;
      disable_interrupts(INT_TIMER1);
      disable_interrupts(INT_TIMER5);
      enable_interrupts(INT_TIMER0);
      
      if(overflow_timer0 >= 1000) estado_sensores = 0b00000000; goto fim3;
 
      
      switch(resposta_sensores)
      {
      case 0b00011000: estado_sensores = 2; break;
      
      default: estado_sensores = 3;  break;
      }
      fim3:
      estado_sensores = estado_sensores;
   }
   
}

void trata_sensores() //FunÁ„o que cuida de todo o tratamento dos sensores.
{
/*
   if ( bit_test(resposta_sensores,0) || bit_test(resposta_sensores,1) ) //Verifica isoladamente os sensores de linha
   {
      motor_1(70,'b');
      motor_2(70,'b');
      
      motor_1(0,'b');
      motor_2(0,'b');
      
      motor_1(70,'b');
      motor_2(70,'f');
      
      bit_clear(resposta_sensores,0);
      bit_clear(resposta_sensores,1);
      printf("cheguei aqui");
   }
*/
   switch(resposta_sensores)
   {
     
     /*
     DiagramaÁ„o dos bits da palavra resposta_sensores
     
     bit 0 - Sensor Linha Direita
     bit 1 - Sensor Linha Esquerda
     bit 2 - Sensor Lateral Direita
     bit 3 - Sensor Frente Esquerda
     bit 4 - Sensor Frente Direita
     bit 5 - Sensor Lateral Esquerda
     
     */
    
     
      case 0b00000000:
      
      if(!primeira_busca)
      {
      //Caso ele j· tenha achado pelo menos uma vez o advers·rio, ele gira em torno do prÛprio eixo
         motor_1(0,'b'); 
         motor_2(0,'f');
         mover = 0;
         
      }
      else{
      
      enable_interrupts(INT_TIMER1);
      motor_1(0,'f');
      motor_2(0,'f');
      
      }
      
      
      break;
      
      case 0b00000100: 
      motor_1(50,'f'); 
      motor_2(50,'b');
  
      primeira_busca = 0;
      disable_interrupts(INT_TIMER1);
      break;
      
      case 0b00001000: 
      motor_1(50,'f'); 
      motor_2(50,'f'); 
      primeira_busca = 0;
      disable_interrupts(INT_TIMER1);
      break;
      
      case 0b00010000: 
      motor_1(50,'f'); 
      motor_2(50,'f'); 
      primeira_busca = 0;
      disable_interrupts(INT_TIMER1);
      break;
      
      case 0b00100000: 
      motor_1(50,'b'); 
      motor_2(50,'f'); 
      primeira_busca = 0;
      disable_interrupts(INT_TIMER1);
      break;
      
      case 0b00011000: 
      motor_1(50,'f');
      motor_2(50,'f'); 
      primeira_busca = 0;
      disable_interrupts(INT_TIMER1);
      break;
      
      case 0b00001100: 
      motor_1(50,'f'); 
      motor_2(50,'b');

      primeira_busca = 0;
      disable_interrupts(INT_TIMER1);
      break;
      
      case 0b00110000: 
      motor_1(50,'b'); 
      motor_2(50,'f');
      primeira_busca = 0;
      disable_interrupts(INT_TIMER1);
      break;
      
      default:  motor_1(0,'b'); motor_2(0,'f'); break;
   }
   
   delay_us(10); //Delay para uma nova leitura
   resposta_sensores = 0b00000000; //Zera a vari·vel de resposta para garantir que um resultado passado n„o fique gravado
}

void motor_1(int duty_cycle, char sentido)
{
   if(sentido == 'f')
   {
   //gira o motor para frente com duty_cycle% de sua pot√™ncia total
      set_power_pwm0_duty((int16)((POWER_PWM_PERIOD *4) * (duty_cycle*0.01))); 
      set_power_pwm2_duty((int16)(0));
      
       /*Aqui multiplica-se por 4 pois o maior valor do per√≠odo do PWM √© 4095 e o valor m√°ximo do par√¢metro da fun√ß√£o,
      que daria 100% de duty cycle √© 16383, portanto cria-se assim uma propo√ß√£o entre o per√≠odo e a velocidade multiplicando por um n√∫mero entre 0 e 1
      que seria a porcentagem desejada. 
      */  
   }
   
   if(sentido == 'b')
   {
     //gira o motor para tr√°s com duty_cyle% de sua pot√™ncia total
      set_power_pwm0_duty((int16)(0)); 
      set_power_pwm2_duty((int16)((POWER_PWM_PERIOD *4) * (duty_cycle*0.01))); 
     /*Aqui multiplica-se por 4 pois o maior valor do per√≠odo do PWM √© 4095 e o valor m√°ximo do par√¢metro da fun√ß√£o,
      que daria 100% de duty cycle √© 16383, portanto cria-se assim uma propo√ß√£o entre o per√≠odo e a velocidade multiplicando por um n√∫mero entre 0 e 1
      que seria a porcentagem desejada. 
      */
   }
}

void motor_2(int duty_cycle, char sentido)
{
   if(sentido == 'f')
   {
    //gira o motor para frente com duty_cycle% de sua potencia total
      set_power_pwm4_duty((int16)((POWER_PWM_PERIOD *4) * (duty_cycle*0.01))); 
      set_power_pwm6_duty((int16)(0));
      /*Aqui multiplica-se por 4 pois o maior valor do per√≠odo do PWM √© 4095 e o valor m√°ximo do par√¢metro da fun√ß√£o,
      que daria 100% de duty cycle √© 16383, portanto cria-se assim uma propo√ß√£o entre o per√≠odo e a velocidade multiplicando por um n√∫mero entre 0 e 1
      que seria a porcentagem desejada. 
      */
   }
   
   if(sentido == 'b')
   {
    //gira o motor para tras com duty_cyle% de sua potencia total
      set_power_pwm4_duty((int16)(0)); 
      set_power_pwm6_duty((int16)((POWER_PWM_PERIOD *4) * (duty_cycle*0.01)));
      /*Aqui multiplica-se por 4 pois o maior valor do per√≠odo do PWM √© 4095 e o valor m√°ximo do par√¢metro da fun√ß√£o,
      que daria 100% de duty cycle √© 16383, portanto cria-se assim uma propo√ß√£o entre o per√≠odo e a velocidade multiplicando por um n√∫mero entre 0 e 1
      que seria a porcentagem desejada. 
      */
   }
}

void leitura_hc04() //Funcao para fazer a leitura do sensor ultrassonico
{
   enable_interrupts(INT_TIMER5); //Habilita interrupÁıes do TIMER5
   
 
   if(cont_timer5 < 8)
   {
      output_low(TRIGGER);
   }
   else if(cont_timer5 >= 8 && cont_timer5 < 10)
   {
      output_high(TRIGGER);
   }
   else if(cont_timer5 == 10)
   {
      cont_timer5 = 0;
   }
   
   if( (input(ECHO)) && (!borda_subida) )
   {
      bs_t = get_timer5();
      borda_subida = 1;
      enable_overflow_count = 1;
   }
   
   else if( (!input(ECHO)) && (!borda_descida) && (borda_subida) )
   {
      bd_t = get_timer5();
      borda_descida = 1;
   }
   
   if( (borda_descida)  )
   {
      if(bd_t>bs_t)
      {
         if(contador_overflows_timer5==0){ trigger_t = bd_t - bs_t; }
         if(contador_overflows_timer5>0) { trigger_t = (bd_t - bs_t) + (65535*(contador_overflows_timer5));  }
      }
      else
      {
      trigger_t = (65535*contador_overflows_timer5) + (bd_t - bs_t);
     // printf(" %Lu \r",trigger_t);
      }
      if(trigger_t <= 30000)  output_high(LED_3); // bit_set(resposta_sensores,3); bit_set(resposta_sensores,4); 
      else output_low(LED_3);
      
      //Reset das variaveis para uma proxima leitura
      borda_descida = 0;
      borda_subida = 0;
      enable_overflow_count = 0;
      contador_overflows_timer5 = 0;
      
   }
   
}
 void bob() //FunÁ„o para teste completo do robÙ
{
  
  
   if(estado_teste == 0) //CondiÁ„o para que a mensagem apareÁa apenas uma vez
   {
      printf("\nTeste: Funcionamento do Motor Esquerdo - Frente\n"); //Mensagem indicando qual parte do teste o usu·rio est·
      estado_teste = 1; //Atualiza estado
      motor_2(0,'f'); // Para motor por seguranÁa.
      motor_1(0,'f'); //Para motor por seguranÁa.
   }
  
  if(estado_teste == 1)
  {
      motor_1(velocidade_teste,'f'); //Testa motor 1 girando em um sentido
       
  }
   if(estado_teste == 2) //CondiÁ„o para que a mensagem apareÁa apenas uma vez
   {
      printf("\nTeste: Funcionamento do Motor Esquerdo - Tras\n"); //Mensagem indicando qual parte do teste o usu·rio est·
      estado_teste = 3; //Atualiza estado
      motor_2(0,'f'); // Para motor por seguranÁa.
      motor_1(0,'f'); //Para motor por seguranÁa.
   }   
   
   if(estado_teste == 3)
   {
      motor_1(velocidade_teste,'b'); //Testa motor 1 girando em um sentido
   
   }
   
    if(estado_teste == 4) //CondiÁ„o para que a mensagem apareÁa apenas uma vez
   {
      printf("\nTeste: Funcionamento do Motor Direito - Frente\n"); //Mensagem indicando qual parte do teste o usu·rio est·
      estado_teste = 5; //Atualiza estado
      motor_2(0,'f'); // Para motor por seguranÁa.
      motor_1(0,'f'); //Para motor por seguranÁa.
   }   
   
   if(estado_teste == 5)
   {
      motor_2(velocidade_teste,'f'); //Testa motor 1 girando em um sentido
      
   }
   
    if(estado_teste == 6) //CondiÁ„o para que a mensagem apareÁa apenas uma vez
   {
      printf("\nTeste: Funcionamento do Motor Direito - Tras\n"); //Mensagem indicando qual parte do teste o usu·rio est·
      estado_teste = 7; //Atualiza estado
      motor_2(0,'f'); // Para motor por seguranÁa.
      motor_1(0,'f'); //Para motor por seguranÁa.
   }   
   
   if(estado_teste == 7)
   {
      motor_2(velocidade_teste,'b'); //Testa motor 1 girando em um sentido
  
   }
   if(estado_teste == 8) //CondiÁ„o para que a mensagem apareÁa apenas uma vez
   {
      printf("\nTeste: Motores Desligados\n"); //Mensagem indicando qual parte do teste o usu·rio est·
      estado_teste = 9; //Atualiza estado
      motor_2(0,'f'); // Para motor por seguranÁa.
      motor_1(0,'f'); //Para motor por seguranÁa.
   }  
      if(estado_teste == 9)
   {
      motor_1(0,'b'); //Testa motor 1 girando em um sentido
      motor_2(0,'b');
    
   }
  }  
   
void enable_motors()
{
   if(ENA_state) output_high(PIN_B6); //Manda sinal para habilitar a ponteH do motor 1.
   else output_low(PIN_B6); //Manda sinal para desabilitar a ponteH do motor 1.
   
   if(ENB_state) output_high(PIN_B7); //Manda sinal para habilitar a ponteH do motor 2.
   else output_low(PIN_B7); //Manda sinal para desabilitar a ponteH do motor 2.

}

void evasao()
{
  disable_interrupts(INT_TIMER5);
 
    motor_1(0,'b');
   motor_2(0,'b');
   delay_ms(500);
  //Da um 'passo' para tras do robo adversario
   motor_1(VELOCIDADE_EVASAO,'b');
   motor_2(VELOCIDADE_EVASAO,'b');
   delay_ms(200);
   
   //Pare novamente
   motor_1(0,'b');
   motor_2(0,'b');
   delay_ms(500);
   
   motor_1(35,'b');
   motor_2(35,'f');
   delay_ms(150);
   
}

void imprime_estrategia(int busca_inicial, int busca_padrao, int pre_busca)
{
         printf("Pre Estrategia:  \r");
         switch(pre_busca)
         {
            case 0: printf("Null\r"); break;
            case 1: printf("Arco Tras Esquerda\r"); break;
            case 2: printf("Arco Tras Direita\r"); break;
            case 3: printf("Tras Reto\r"); break;
            case 4: printf("3-Point-Death-Punch \r"); break;
            default: printf("Estrategia Invalida\r"); LIGA = 0; primeiro_inicio = 0; break;
         }
         printf("Estrategia Inicial:  \r");
         switch(busca_inicial)
         {
            case 0: printf("Busca Passiva\r"); break;
            case 1: printf("Busca Twister\r"); break;
            case 2: printf("Busca Arco\r"); break;
            case 3: printf("Busca Agressiva\r"); break;
            case 4: printf("Busca Pulso Movimento \r"); break;
            default: printf("Estrategia Invalida\r"); LIGA = 0; primeiro_inicio = 0; break;
         }
         
         printf("Estrategia Padrao:  \r");
         switch(busca_padrao)
         {
            case 1: printf("Busca Passiva\r"); break;
            case 2: printf("Busca Twister\r"); break;
            case 3: printf("Busca Agressiva\r"); break; 
            default: printf("Estrategia Invalida!\r"); LIGA = 0; primeiro_inicio = 0; break;
         }
         
}

void set_estrategia(int codigo_estrategia)
{
   pre_busca = (codigo_estrategia/15);
   busca_inicial = (codigo_estrategia/3) - ( (codigo_estrategia/15)*5 );
   busca_padrao = (codigo_estrategia - ((codigo_estrategia/15)*15)) - (((codigo_estrategia - ((codigo_estrategia/15)*15))/3)*3);
}


   
   
