//////// Standard Header file for the PIC18F4431 device ////////////////
#device PIC18F4431
#nolist
//////// Program memory: 8192x16  Data RAM: 768  Stack: 31
//////// I/O: 36   Analog Pins: 9
//////// Data EEPROM: 256
//////// C Scratch area: 00   ID Location: 200000
//////// Fuses: LP,XT,HS,EC,EC_IO,H4,RC_IO,INTRC_IO,PROTECT,NOPROTECT,IESO
//////// Fuses: NOIESO,NOBROWNOUT,BROWNOUT,WDT1,WDT2,WDT4,WDT8,WDT16,WDT32
//////// Fuses: WDT64,WDT128,WDT,NOWDT,INTRC,BORV27,BORV42,BORV45,PUT,NOPUT
//////// Fuses: CPD,NOCPD,NOSTVREN,STVREN,NODEBUG,DEBUG,NOLVP,LVP,WRT,NOWRT
//////// Fuses: WRTD,NOWRTD,RC,FCMEN,NOFCMEN,WINEN,NOWINEN,T1LOWPOWER
//////// Fuses: T1STANDARD,HPOL_HIGH,WRTC,NOWRTC,WRTB,NOWRTB,EBTR,NOEBTR
//////// Fuses: EBTRB,NOEBTRB,CPB,NOCPB,HPOL_LOW,LPOL_HIGH,LPOL_LOW,PWMPIN
//////// Fuses: NOPWMPIN,MCLR,NOMCLR,WDT256,WDT512,WDT1024,WDT2048,WDT4096
//////// Fuses: WDT8192,WDT16384,WDT32768,FLTAC1,FLTAD4,SSP_RC,SSP_RD,PWM4B5
//////// Fuses: PWM4D5,EXCLKC3,EXCLKD0
//////// 
////////////////////////////////////////////////////////////////// I/O
// Discrete I/O Functions: SET_TRIS_x(), OUTPUT_x(), INPUT_x(),
//                         PORT_x_PULLUPS(), INPUT(),
//                         OUTPUT_LOW(), OUTPUT_HIGH(),
//                         OUTPUT_FLOAT(), OUTPUT_BIT()
// Constants used to identify pins in the above are:

#define PIN_A0  31744
#define PIN_A1  31745
#define PIN_A2  31746
#define PIN_A3  31747
#define PIN_A4  31748
#define PIN_A5  31749
#define PIN_A6  31750
#define PIN_A7  31751

#define PIN_B0  31752
#define PIN_B1  31753
#define PIN_B2  31754
#define PIN_B3  31755
#define PIN_B4  31756
#define PIN_B5  31757
#define PIN_B6  31758
#define PIN_B7  31759

#define PIN_C0  31760
#define PIN_C1  31761
#define PIN_C2  31762
#define PIN_C3  31763
#define PIN_C4  31764
#define PIN_C5  31765
#define PIN_C6  31766
#define PIN_C7  31767

#define PIN_D0  31768
#define PIN_D1  31769
#define PIN_D2  31770
#define PIN_D3  31771
#define PIN_D4  31772
#define PIN_D5  31773
#define PIN_D6  31774
#define PIN_D7  31775

#define PIN_E0  31776
#define PIN_E1  31777
#define PIN_E2  31778
#define PIN_E3  31779

////////////////////////////////////////////////////////////////// Useful defines
#define FALSE 0
#define TRUE 1

#define BYTE int8
#define BOOLEAN int1

#define getc getch
#define fgetc getch
#define getchar getch
#define putc putchar
#define fputc putchar
#define fgets gets
#define fputs puts

////////////////////////////////////////////////////////////////// Control
// Control Functions:  RESET_CPU(), SLEEP(), RESTART_CAUSE()
// Constants returned from RESTART_CAUSE() are:

#define WDT_TIMEOUT       7    
#define MCLR_FROM_SLEEP  11    
#define MCLR_FROM_RUN    15    
#define NORMAL_POWER_UP  12    
#define BROWNOUT_RESTART 14    
#define WDT_FROM_SLEEP   3     
#define RESET_INSTRUCTION 0    
////////////////////////////////////////////////////////////////// Timer 0
// Timer 0 (AKA RTCC)Functions: SETUP_COUNTERS() or SETUP_TIMER_0(),
//                              SET_TIMER0() or SET_RTCC(),
//                              GET_TIMER0() or GET_RTCC()
// Constants used for SETUP_TIMER_0() are:
#define RTCC_INTERNAL   0
#define RTCC_EXT_L_TO_H 32
#define RTCC_EXT_H_TO_L 48

#define RTCC_DIV_1      8
#define RTCC_DIV_2      0
#define RTCC_DIV_4      1
#define RTCC_DIV_8      2
#define RTCC_DIV_16     3
#define RTCC_DIV_32     4
#define RTCC_DIV_64     5
#define RTCC_DIV_128    6
#define RTCC_DIV_256    7

#define RTCC_OFF        0x80  

#define RTCC_8_BIT      0x40  

// Constants used for SETUP_COUNTERS() are the above
// constants for the 1st param and the following for
// the 2nd param:

////////////////////////////////////////////////////////////////// WDT
// Watch Dog Timer Functions: SETUP_WDT() or SETUP_COUNTERS() (see above)
//                            RESTART_WDT()
// WDT base is 4ms
//
#define WDT_ON        0x100
#define WDT_OFF       0

////////////////////////////////////////////////////////////////// Timer 1
// Timer 1 Functions: SETUP_TIMER_1, GET_TIMER1, SET_TIMER1
// Constants used for SETUP_TIMER_1() are:
//      (or (via |) together constants from each group)
#define T1_DISABLED         0
#define T1_INTERNAL         0x85
#define T1_EXTERNAL         0x87
#define T1_EXTERNAL_SYNC    0x83

#define T1_CLK_OUT          8

#define T1_DIV_BY_1         0
#define T1_DIV_BY_2         0x10
#define T1_DIV_BY_4         0x20
#define T1_DIV_BY_8         0x30

////////////////////////////////////////////////////////////////// Timer 2
// Timer 2 Functions: SETUP_TIMER_2, GET_TIMER2, SET_TIMER2
// Constants used for SETUP_TIMER_2() are:
#define T2_DISABLED         0
#define T2_DIV_BY_1         4
#define T2_DIV_BY_4         5
#define T2_DIV_BY_16        6

////////////////////////////////////////////////////////////////// Timer 3
// Timer 5 Functions: SETUP_TIMER_5, GET_TIMER5, SET_TIMER5
// Constants used for SETUP_TIMER_5() are:
//      (or (via |) together constants from each group)
#define T5_DISABLED         0
#define T5_INTERNAL         0x01
#define T5_EXTERNAL         0x07
#define T5_EXTERNAL_SYNC    0x03

#define T5_DIV_BY_1         0
#define T5_DIV_BY_2         0x08
#define T5_DIV_BY_4         0x10
#define T5_DIV_BY_8         0x18

#define T5_ONE_SHOT         0x20

#define T5_DISABLE_SE_RESET 0x40

#define T5_ENABLE_DURING_SLEEP 0x80

////////////////////////////////////////////////////////////////// CCP
// CCP Functions: SETUP_CCPx, SET_PWMx_DUTY
// CCP Variables: CCP_x, CCP_x_LOW, CCP_x_HIGH
// Constants used for SETUP_CCPx() are:
#define CCP_OFF                         0
#define CCP_CAPTURE_FE                  4
#define CCP_CAPTURE_RE                  5
#define CCP_CAPTURE_DIV_4               6
#define CCP_CAPTURE_DIV_16              7
#define CCP_COMPARE_SET_ON_MATCH        8
#define CCP_COMPARE_CLR_ON_MATCH        9
#define CCP_COMPARE_INT                 0xA
#define CCP_COMPARE_INT_AND_TOGGLE      0x2       
#define CCP_COMPARE_RESET_TIMER         0xB
#define CCP_PWM                         0xC
#define CCP_PWM_PLUS_1                  0x1c
#define CCP_PWM_PLUS_2                  0x2c
#define CCP_PWM_PLUS_3                  0x3c
//#define CCP_USE_TIMER3                0x100  OBSOLETE, SEE TIMER-3     
#word   CCP_1    =                      getenv("SFR:CCPR1L")
#byte   CCP_1_LOW=                      getenv("SFR:CCPR1L")
#byte   CCP_1_HIGH=                     getenv("SFR:CCPR1H")
#word   CCP_2    =                      getenv("SFR:CCPR2L")
#byte   CCP_2_LOW=                      getenv("SFR:CCPR2L")
#byte   CCP_2_HIGH=                     getenv("SFR:CCPR2H")
////////////////////////////////////////////////////////////////// SPI
// SPI Functions: SETUP_SPI, SPI_WRITE, SPI_READ, SPI_DATA_IN
// Constants used in SETUP_SPI() are:
#define SPI_MASTER       0x20
#define SPI_SLAVE        0x24
#define SPI_L_TO_H       0
#define SPI_H_TO_L       0x10
#define SPI_CLK_DIV_4    0
#define SPI_CLK_DIV_16   1
#define SPI_CLK_DIV_64   2
#define SPI_CLK_T2       3
#define SPI_SS_DISABLED  1

#define SPI_SAMPLE_AT_END 0x8000
#define SPI_XMIT_L_TO_H  0x4000

////////////////////////////////////////////////////////////////// UART
// Constants used in setup_uart() are:
// FALSE - Turn UART off
// TRUE  - Turn UART on
#define UART_ADDRESS           2
#define UART_DATA              4
#define UART_AUTODETECT        8
#define UART_AUTODETECT_NOWAIT 9
#define UART_WAKEUP_ON_RDA     10
#define UART_SEND_BREAK        13
////////////////////////////////////////////////////////////////// VREF
// Constants used in setup_low_volt_detect() are:
//
#define LVD_LVDIN   0x1F
#define LVD_42 0x1E
#define LVD_39 0x1D
#define LVD_38 0x1C
#define LVD_36 0x1B
#define LVD_34 0x1A
#define LVD_33 0x19
#define LVD_31 0x18
#define LVD_28 0x17
#define LVD_27 0x16
#define LVD_26 0x15
#define LVD_24 0x14
#define LVD_23 0x13
#define LVD_21 0x12


////////////////////////////////////////////////////////////////// INTERNAL RC
// Constants used in setup_oscillator() are:
#define OSC_31KHZ   0
#define OSC_125KHZ  0x10
#define OSC_250KHZ  0x20
#define OSC_500KHZ  0x30
#define OSC_1MHZ    0x40
#define OSC_2MHZ    0x50
#define OSC_4MHZ    0x60
#define OSC_8MHZ    0x70
// The following may be OR'ed in with the above using |
#define OSC_TIMER1  1
#define OSC_INTRC   2
#define OSC_NORMAL  0
// The following may be OR'ed in with the above using |
#define OSC_IDLE_MODE  0x80
// A second optional parameter may be used with this part to fine
// tune the speed (signed int,0-63)
// Result may be (ignore all other bits)
#define OSC_STATE_STABLE 4
#define OSC_STATE_EXT_RUNNING 8

////////////////////////////////////////////////////////////////// POWER PWM
// CCP Functions: SETUP_POWER_PWM()
// Constants used for SETUP_POWER_PWM() are:
#define PWM_CLOCK_DIV_4   0x00
#define PWM_CLOCK_DIV_16  0x04
#define PWM_CLOCK_DIV_64  0x08
#define PWM_CLOCK_DIV_128 0x0C

#define PWM_OFF           0x0000
#define PWM_FREE_RUN      0x8000
#define PWM_SINGLE_SHOT   0x8001
#define PWM_UP_DOWN       0x8002
#define PWM_UP_DOWN_INT   0x8003

#define PWM_OVERRIDE_SYNC  0x10000

#define PWM_UP_TRIGGER     0x00000
#define PWM_DOWN_TRIGGER   0x80000

#define PWM_DEAD_CLOCK_DIV_2  0x000000
#define PWM_DEAD_CLOCK_DIV_4  0x100000
#define PWM_DEAD_CLOCK_DIV_8  0x200000
#define PWM_DEAD_CLOCK_DIV_16 0x300000

// Constants used for SET_POWER_PWMx_DUTY() are:
#define PWM_UPDATE_DISABLE 0x20000
#define PWM_UPDATE_ENABLE  0x00000

// Constants used for SETUP_POWER_PWM_PINS() are:
//#define PWM_OFF         0
#define PWM_ODD_ON        1
#define PWM_BOTH_ON       2
#define PWM_COMPLEMENTARY 3


////////////////////////////////////////////////////////////////// ADC
// ADC Functions: SETUP_ADC(), SETUP_ADC_PORTS() (aka SETUP_PORT_A),
//                SET_ADC_CHANNEL(), READ_ADC()
// Constants used for SETUP_ADC() are:
#define ADC_OFF               0           // ADC Off
#define ADC_CLOCK_DIV_2 0x1000000
#define ADC_CLOCK_DIV_4    0x0400
#define ADC_CLOCK_DIV_8    0x0100
#define ADC_CLOCK_DIV_16   0x0500
#define ADC_CLOCK_DIV_32   0x0200
#define ADC_CLOCK_DIV_64   0x0600
#define ADC_CLOCK_INTERNAL 0x0700           // Internal 2-6us

// The following may be OR'ed in with the above using |
#define ADC_TAD_MUL_0      0x0000
#define ADC_TAD_MUL_2      0x0800
#define ADC_TAD_MUL_4      0x1000
#define ADC_TAD_MUL_6      0x1800
#define ADC_TAD_MUL_8      0x2000
#define ADC_TAD_MUL_10     0x2800
#define ADC_TAD_MUL_12     0x3000
#define ADC_TAD_MUL_16     0x3800
#define ADC_TAD_MUL_20     0x4000
#define ADC_TAD_MUL_24     0x4800
#define ADC_TAD_MUL_28     0x5000
#define ADC_TAD_MUL_32     0x5800
#define ADC_TAD_MUL_36     0x6000
#define ADC_TAD_MUL_40     0x6800
#define ADC_TAD_MUL_48     0x7000
#define ADC_TAD_MUL_64     0x7800

// One of the following may be OR'ed in with the above using |
#define ADC_CONT_A         0x20  // These options select
#define ADC_CONT_B         0x24  // continuous sampling, the channels
#define ADC_CONT_C         0x28  // A,B,C,D are each mapped to a pin
#define ADC_CONT_D         0x2C  // in set_adc_channel

#define ADC_CONT_A_B       0x30  // These do continuous sampling
#define ADC_CONT_A_B_C_D   0x34  // on alternating channels
#define ADC_CONT_AB        0x38
#define ADC_CONT_AB_CD     0x3C

// One of the following may be OR'ed in with the above using |
#define ADC_WHEN_INT0      0x010000
#define ADC_WHEN_TIMER5    0x020000
#define ADC_WHEN_IC1       0x040000
#define ADC_WHEN_CCP2      0x080000
#define ADC_WHEN_PPWM      0x100000

// One of the following may be OR'ed in with the above using |
#define ADC_INT_EVERY_OTHER 0x400000
#define ADC_INT_EVERY_FOUR  0x800000

// This device allows 4 params to set_adc_channel to set the channel
// for each group A,B,C,D

// Constants used in SETUP_ADC_PORTS() are:
#define sAN0            1       //| A0
#define sAN1            2       //| A1
#define sAN2            4       //| A2
#define sAN3            8       //| A3
#define sAN4            16      //| A4
#define sAN5            32      //| A5      
#define sAN6            64      //| E0      
#define sAN7            128     //| E1      
#define sAN8        0x10000     //| E2      
#define NO_ANALOGS      0       // None
#define ALL_ANALOG  0x100FF     // A0 A1 A2 A3 A4 A5 E0 E1 E2 

// One of the following may be OR'ed in with the above using |
#define VSS_VDD               0x0000          // Range 0-Vdd
#define VREF_VREF             0xC000          // Range VrefL-VrefH
#define VSS_VREF              0x4000          // Range 0-VrefH
#define VREF_VDD              0x8000          // Range VrefL-Vdd


// Constants used in READ_ADC() are:
#define ADC_START_AND_READ     7   // This is the default if nothing is specified
#define ADC_START_ONLY         1
#define ADC_READ_ONLY          6




////////////////////////////////////////////////////////////////// INT
// Interrupt Functions: ENABLE_INTERRUPTS(), DISABLE_INTERRUPTS(),
//                      CLEAR_INTERRUPT(), INTERRUPT_ACTIVE(),
//                      EXT_INT_EDGE()
//
// Constants used in EXT_INT_EDGE() are:
#define L_TO_H              0x40
#define H_TO_L                 0
// Constants used in ENABLE/DISABLE_INTERRUPTS() are:
#define GLOBAL                    0xF2C0
#define INT_RTCC                  0xF220
#define INT_TIMER0                0xF220
#define INT_TIMER1                0x9D01
#define INT_TIMER2                0x9D02
#define INT_EXT                   0xF210
#define INT_EXT1                  0xF008
#define INT_EXT2                  0xF010
#define INT_RB                    0xFFF208
#define INT_AD                    0x9D40
#define INT_RDA                   0x9D20
#define INT_TBE                   0x9D10
#define INT_SSP                   0x9D08
#define INT_CCP1                  0x9D04
#define INT_CCP2                  0xA001
#define INT_LOWVOLT               0xA004
#define INT_EEPROM                0xA010
#define INT_OSCF                  0xA080
#define INT_PWMTB                 0xA310
#define INT_IC3DR                 0xA308
#define INT_IC2QEI                0xA304
#define INT_IC1                   0xA302
#define INT_TIMER5                0xA301

#list
