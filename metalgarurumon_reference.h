#ifndef portas_metal_H_
#define portas_metal_H_

//Definicao de parametros do codigo

//Pinos dos Leds
#define LED_0 PIN_D0
#define LED_1 PIN_D1
#define LED_2 PIN_D2
#define LED_3 PIN_D3
#define TRIGGER PIN_E1
#define ECHO PIN_E2

//Pinos dos sensores de linha
#define pin_sensor_linha_1 PIN_A5
#define pin_sensor_linha_2 PIN_A6

//Pinos dos sensores de dist√¢ncia
#define pin_sensor_distancia_direita PIN_A0
#define pin_sensor_distancia_frente_direita PIN_A1
#define pin_sensor_distancia_frente_esquerda PIN_A2
#define pin_sensor_distancia_esquerda PIN_A3
#define pin_sensor_distancia_5 PIN_A4

//Canais dos sensores de linha
#define canal_sensor_linha_1 5
#define canal_sensor_linha_2 6

//Canais dos sensores de dist√¢ncia
#define canal_sensor_distancia_direita 0
#define canal_sensor_distancia_frente_direita 1
#define canal_sensor_distancia_frente_esquerda 2
#define canal_sensor_distancia_esquerda 3
#define canal_sensor_distancia_5 4


//Habilitacao das pontes H
#define ENA_state 1
#define ENB_state 1
//Periodo do PWM
#define POWER_PWM_PERIOD 275 //Define o valor da constante per√≠odo do PWM
//Modo de HabilitaÁ„o por BlueTooth
#define SAFE_BT 0
#define ULTRASSONICO 0

#define TEMPO_ATACANDO 4500 //overflow a cada 13ms 
#define TEMPO_LINHA_TRAS_MS 175
#define TEMPO_GIRO_LINHA 100

#define VELOCIDADE_ATAQUE 100
#define VELOCIDADE_BUSCA_AGRESSIVA 30
#define VELOCIDADE_EVASAO 30
#define VELOCIDADE_LINHA 50
#define VELOCIDADE_GIRO_LINHA 60

//Declaracao de variaveis globais
int velocidade_teste=20; //Velocidade padrao para testes
int16 leitura = 0; //vari√°vel que realiza a leitura instantanea 
//int16 ultima_leitura = 0;//Vari√°vel usada para calcular a diferen√ßa entre uma leitura e sua √∫ltima leitura e apresentar uma nova apenas se necess√°rio
//signed int16 variacao = 0; //Vari·vel que indica o quanto o valor atual varia em relaÁ„o ao valor anterior
int8 resposta_sensores = 0b00000000;
/*Variavel que indica o estado atual dos sensores de lnha sem seus dois primeiros bits
podendo ter ent√£o os seguintes valores

00000000 - Nenhum sensor acionado
01000000 - Um sensor acionado
10000000 - Um sensor acionado
11000000 - Dois sensores acionados

Ela e inicializada em zero.
*/

//Inicializa contadores de overflow dos timers 0,1 e 5.
int16 overflow_timer1 = 0;
int16 overflow_timer0 = 0;
int16 cont_timer5 = 0;

//char input_robo[5];


int primeiro_inicio = 0;
//Variavel que indica se eh primeira vez que o robo entra na sua rotina normal

int estado_teste = 0; //Variavel que controla o estado do teste quando necess·rio

int LIGA = 0;
/*Variavel que indica se o robÙ esta ligado ou desligado.
0 - Desligado
1 - Ligado
*/
char leitura_bt[4]; //Variavel que armazena o char enviado pelo celular
int leitura_bt_int;

int1 primeira_busca = 1; //Indica se o robo est· na primeira tentativa de busca
int1 mover = 0; //Indica se o robo deve dar um pulso de movimento


int8 estado_sensores = 0; //Variavel que controla o estado em que o robo se
//encontra em relacao a encontrar o adversario

//Variaveis de controle da borda de subida e descida
int1 borda_subida = 0;
int1 borda_descida = 0;

//Variaveis usadas no sensor ultrassonico
int16 bs_t = 0; //momento em que houve borda de subida
int16 bd_t = 0; //momento em que houve borda de descida
int16 trigger_t = 0; //Tempo em alta no trigger
int1 enable_overflow_count = 0; //Controla a partir de quando conta overflows do timer5
int contador_overflows_timer5 = 0; //Conta quantos overflows houveram no timer 5


int busca_inicial;
int busca_padrao;
int pre_busca;

char lado;

//Declaracoes das funcoes do Firmware¥
void enable_motors();
void config();
int8 leitura_adc(int16 threshold, int canal, int8 resposta_leitura, int bit);
void motor_1(int duty_cycle, char sentido);
void motor_2(int duty_cycle, char sentido);
void bob();
void disables();
void trata_sensores_2();
void trata_sensores();
void sensores();
void leitura_hc04();
void evasao();

#endif
