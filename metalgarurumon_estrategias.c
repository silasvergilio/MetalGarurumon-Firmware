#include "metalgarurumon_reference.h"

void busca_passiva()
{
         //Para os dois motores
         motor_1(0,'b'); 
         motor_2(0,'f');
         //Forca o motor a nao dar um pulso de movimento
         mover = 0;
         //desabilita o timer responsavel por impedir que o robo fique num mesmo estado muito tempo 
         disable_interrupts(INT_TIMER0);
         disable_interrupts(INT_TIMER5);
         //reseta o contador do timer0
         overflow_timer0 = 0;
}

void busca_twister(char lado)
{
      //Gira de acordo com o lado mais proximo do robo adversario
        if(lado == 'e')
        {
        motor_1(50,'b');
        motor_2(50,'f');
        }
        else if(lado == 'd')  
        {
        motor_1(50,'f'); 
        motor_2(50,'b');
        }
        
         //Forca o motor a nao dar um pulso de movimento
         mover = 0;
         //desabilita o timer responsavel por impedir que o robo fique num mesmo estado muito tempo 
         disable_interrupts(INT_TIMER0);
         disable_interrupts(INT_TIMER5);
         //reseta o contador do timer0
         overflow_timer0 = 0;
}

void busca_arco(char lado)
{
      //Gira de acordo com o lado mais proximo do adversario
      if(lado == 'e')
      {
      motor_1(30,'f'); 
      motor_2(60,'f');
      }
      else if (lado == 'd')
      {
      motor_1(60,'f'); 
      motor_2(30,'f');
      }
        
         //Forca o motor a nao dar um pulso de movimento
         mover = 0;
         //desabilita o timer responsavel por impedir que o robo fique num mesmo estado muito tempo 
         disable_interrupts(INT_TIMER0);
         disable_interrupts(INT_TIMER5);
         //reseta o contador do timer0
         overflow_timer0 = 0;
}

void busca_agressiva()
{
      //Para os dois motores
         motor_1(VELOCIDADE_BUSCA_AGRESSIVA,'f'); 
         motor_2(VELOCIDADE_BUSCA_AGRESSIVA,'f');
         //Forca o motor a nao dar um pulso de movimento
         mover = 0;
         //desabilita o timer responsavel por impedir que o robo fique num mesmo estado muito tempo 
         disable_interrupts(INT_TIMER0);
         disable_interrupts(INT_TIMER5);
         //reseta o contador do timer0
         overflow_timer0 = 0;  
}

void busca_pulso()
{

      enable_interrupts(INT_TIMER1); //Habilita Timer1 para dar o pulso de movimento
      disable_interrupts(INT_TIMER5);
      //Para os motores quando não tiver enviado o pulso
      motor_1(0,'f'); 
      motor_2(0,'f');
}






