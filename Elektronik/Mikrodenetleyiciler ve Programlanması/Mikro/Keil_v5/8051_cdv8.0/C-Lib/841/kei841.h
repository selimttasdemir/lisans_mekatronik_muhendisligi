/*--------------------------------------------------------------------------
kei841.h

Header file for Keil C compiler for ADuC841 specific SFRs.
Copyright (c) 2002 Analog Devices Inc.
All rights reserved.
--------------------------------------------------------------------------*/
sfr P0   = 0x80;
sfr SP   = 0x81;
sfr DPL  = 0x82;
sfr DPH  = 0x83;
sfr DPP      =  0x84; //POINTER - PAGE BYTE
sfr PCON = 0x87;
sfr TCON = 0x88;
sfr TMOD = 0x89;
sfr TL0  = 0x8A;
sfr TL1  = 0x8B;
sfr TH0  = 0x8C;
sfr TH1  = 0x8D;
sfr P1   = 0x90;
sfr SCON = 0x98;
sfr SBUF = 0x99;
sfr T3FD     =  0x9D;	//Serial baudrate fraction
sfr T3CON    =  0x9E;	//Seral baudrate tap
sfr P2   = 0xA0;
sfr TIMECON  =  0xA1;	//TIME COUNTER CONTROL REGISTER
sfr HTHSEC   =  0xA2;	//1/128 OF A SECOND COUNTER
sfr SEC      =  0xA3;	//SECONDS COUNTER
sfr MIN      =  0xA4;	//MINUTES COUNTER
sfr HOUR     =  0xA5;	//HOURS COUNTER
sfr INTVAL   =  0xA6;	//TIMER INTERVAL
sfr DPCON    =  0xA7;	//Data Pointer control
sfr IE   = 0xA8;
sfr IEIP2    =  0xA9;	//INTERRUPT ENABLE 2
sfr PWMCON    =  0xAE;	//PWM control
sfr CFG841    =  0xAF;	//Extended memory modes
sfr P3   = 0xB0;
sfr PWM0L     =  0xB1;	//PWM width low
sfr PWM0H     =  0xB2;	//PWM width high
sfr PWM1L     =  0xB3;	//PWM cycle low
sfr PWM1H     =  0xB4;	//PWM cycle high
sfr SPH      =  0xB7;	//Stack pointer high
sfr IP   = 0xB8;
sfr ECON     =  0xB9;	//FLASH CONTROL
sfr EDATA1   =  0xBC;	//FLASH DATA1 
sfr EDATA2   =  0xBD;	//FLASH DATA2 
sfr EDATA3   =  0xBE;	//FLASH DATA3 
sfr EDATA4   =  0xBF;	//FLASH DATA4 
sfr WDCON    =  0xC0;	//WATCHDOG TIMER CONTROL
sfr CHIPID   =  0xC2;	//CHIP ID REGISTER
sfr EADRL    =  0xC6;	//EEPROM ADDRESS LOW
sfr EADRH    =  0xC7;	//EEPROM ADDRESS HIGH
sfr T2CON    =	0xc8;	//Timer 2 control.
sfr RCAP2L   =	0xca;	//Reload/capture 2 low.
sfr RCAP2H   =	0xcb;	//Reload/capture 2 high.
sfr TL2      =	0xcc;	//Timer 2 low byte.
sfr TH2      =	0xcd;	//Timer 2 high byte.
sfr PSW  = 0xD0;
sfr DMAL     =  0xD2;	//DMA low.
sfr DMAH     =  0xD3;	//DMA high.
sfr DMAP     =  0xD4;	//DMA page.
sfr PLLCON   =  0xD7;	//CRYSTAL PLL CONTROL REGISTER
sfr ADCCON2  =  0xD8;	//ADC CONTROL REGISTER
sfr ADCDATAL =  0xD9;	//ADC DATA REGISTERS
sfr ADCDATAH =  0xDA;
sfr PSMCON   =  0xDF;	//POWER SUPPLY MONITOR
sfr ACC  = 0xE0;
sfr GN0L     =  0xE9;	//MAIN ADC GAIN REGISTER
sfr GN0M     =  0xEA;	//MAIN ADC GAIN REGISTER
sfr GN0H     =  0xEB;	//MAIN ADC GAIN REGISTER
sfr GN1L     =  0xEC;	//AUX ADC GAIN REGISTER
sfr GN1H     =  0xED;	//AUX ADC GAIN REGISTER
sfr B    = 0xF0;
sfr ADCOFSL  =  0xf1;	//ADC OFFSET REGISTERS
sfr ADCOFSH  =  0xf2;
sfr ADCGAINL =  0xf3;	//ADC GAIN REGISTERS
sfr ADCGAINH =  0xf4;
sfr ADCCON3  =  0xED;	//ADC CONTROL REGISTER
sfr SPIDAT   =  0xF7;	//SPI = REGISTER
sfr SPICON   =  0xF8;	//SPI CONTROL REGISTER
sfr DAC0L    =  0xF9;	//DAC 0 DATA
sfr DAC0H    =  0xfa;
sfr DAC1L    =  0xFB;	//DAC 1 DATA
sfr DAC1H    =  0xFC;
sfr DACCON   =  0xFD;	//DAC CONTROL REGISTER
/* P0 */
sbit P00	=	0x80;	//Port0 bit0.
sbit P01	=	0x81;	//Port0 bit1.
sbit P02	=	0x82;	//Port0 bit2.
sbit P03	=	0x83;	//Port0 bit3.
sbit P04	=	0x84;	//Port0 bit4.
sbit P05	=	0x85;	//Port0 bit5.
sbit P06	=	0x86;	//Port0 bit6.
sbit P07	=	0x87;	//Port0 bit7.
/*  TCON  */
sbit TF1  = 0x8F;
sbit TR1  = 0x8E;
sbit TF0  = 0x8D;
sbit TR0  = 0x8C;
sbit IE1  = 0x8B;
sbit IT1  = 0x8A;
sbit IE0  = 0x89;
sbit IT0  = 0x88;
/* P1 */
sbit P10	=	0x90;	//Port1 bit0.
sbit P11	=	0x91;	//Port1 bit1.
sbit P12	=	0x92;	//Port1 bit2.
sbit P13	=	0x93;	//Port1 bit3.
sbit P14	=	0x94;	//Port1 bit4.
sbit P15	=	0x95;	//Port1 bit5.
sbit P16	=	0x96;	//Port1 bit6.
sbit P17	=	0x97;	//Port1 bit7.
/*  SCON  */
sbit SM0  = 0x9F;
sbit SM1  = 0x9E;
sbit SM2  = 0x9D;
sbit REN  = 0x9C;
sbit TB8  = 0x9B;
sbit RB8  = 0x9A;
sbit TI   = 0x99;
sbit RI   = 0x98;
/* P2 */
sbit P20	=	0xa0;	//Port2 bit0.
sbit P21	=	0xa1;	//Port2 bit1.
sbit P22	=	0xa2;	//Port2 bit2.
sbit P23	=	0xa3;	//Port2 bit3.
sbit P24	=	0xa4;	//Port2 bit4.
sbit P25	=	0xa5;	//Port2 bit5.
sbit P26	=	0xa6;	//Port2 bit6.
sbit P27	=	0xa7;	//Port2 bit7.
/*  IE   */
sbit EADC	=	0xae;	//IE.6 - ENABLE ADC INTURRUPT
sbit EA   = 0xAF;
sbit ES   = 0xAC;
sbit ET1  = 0xAB;
sbit EX1  = 0xAA;
sbit ET0  = 0xA9;
sbit EX0  = 0xA8;
/* P3 */
sbit P30	=	0xb0;	//Port3 bit0.
sbit P41	=	0xb1;	//Port3 bit1.
sbit P32	=	0xb2;	//Port3 bit2.
sbit P33	=	0xb3;	//Port3 bit3.
sbit P34	=	0xb4;	//Port3 bit4.
sbit P35	=	0xb5;	//Port3 bit5.
sbit P36	=	0xb6;	//Port3 bit6.
sbit P37	=	0xb7;	//Port3 bit7.
sbit RD   = 0xB7;
sbit WR   = 0xB6;
sbit T1   = 0xB5;
sbit T0   = 0xB4;
sbit INT1 = 0xB3;
sbit INT0 = 0xB2;
sbit TXD  = 0xB1;
sbit RXD  = 0xB0;
/*  IP   */ 
sbit PSI	=	0xbf;	//SERIAL INTERFACE PRIORITY
sbit PADC	=	0xbe;	//ADC INTERFACE PRIORITY
sbit PT2	=	0xbd;	//Timer2 INTERFACE PRIORITY
sbit PS   = 0xBC;
sbit PT1  = 0xBB;
sbit PX1  = 0xBA;
sbit PT0  = 0xB9;
sbit PX0  = 0xB8;
/* WDCON */
sbit WDWR    =  0xC0;	//WDCON.0 - WATCHDOG WRITE ENABLE BIT
sbit WDE     =  0xC1;	//WDCON.1 - WATCHDOG ENABLE
sbit WDS     =  0xC2;	//WDCON.2 - WATCHDOG STATUS
sbit WDIR    =  0xC3;	//WDCON.3 - WATCHDOG INTERRUPT RESPONSE BIT
sbit PRE0    =  0xC4;	//WDCON.4 - WATCHDOG TIMEOUT SELECTION BIT0
sbit PRE1    =  0xC5;	//WDCON.5 - WATCHDOG TIMEOUT SELECTION BIT1
sbit PRE2    =  0xC6;	//WDCON.6 - WATCHDOG TIMEOUT SELECTION BIT2
sbit PRE3    =  0xC7;	//WDCON.7 - WATCHDOG TIMEOUT SELECTION BIT3
/* T2CON */
sbit CAP2	=	0xc8;	//Capture/reload select.
sbit CNT2	=	0xc9;	//Timer/counter select.
sbit TR2	=	0xca;	//Run control.
sbit EXEN2	=	0xcb;	//External enable.
sbit TCLK	=	0xcc;	//Transmit clock enable.
sbit RCLK	=	0xcd;	//Receive clock enable.
sbit EXF2	=	0xce;	//External flag.
sbit TF2	=	0xcf;	//Overflow flag.
/*  PSW   */
sbit CY   = 0xD7;
sbit AC   = 0xD6;
sbit F0   = 0xD5;
sbit RS1  = 0xD4;
sbit RS0  = 0xD3;
sbit OV   = 0xD2;
sbit P    = 0xD0;
/* ACC */
sbit	ACC0	=	0xe0;	//ACC bit 0.
sbit	ACC1	=	0xe1;	//ACC bit 1.
sbit	ACC2	=	0xe2;	//ACC bit 2.
sbit	ACC3	=	0xe3;	//ACC bit 3.
sbit	ACC4	=	0xe4;	//ACC bit 4.
sbit	ACC5	=	0xe5;	//ACC bit 5.
sbit	ACC6	=	0xe6;	//ACC bit 6.
sbit	ACC7	=	0xe7;	//ACC bit 7.
/* B */
sbit	B0	=	0xf0;	//B bit 0.
sbit	B1	=	0xf1;	//B bit 1.
sbit	B2	=	0xf2;	//B bit 2.
sbit	B3	=	0xf3;	//B bit 3.
sbit	B4	=	0xf4;	//B bit 4.
sbit	B5	=	0xf5;	//B bit 5.
sbit	B6	=	0xf6;	//B bit 6.
sbit	B7	=	0xf7;	//B bit 7.
/* SPICON */
sbit SPR0    =  0xF8;	//SPICON.0 - SPI BITRATE SELECT BIT0
sbit SPR1    =  0xF9;	//SPICON.1 - SPI BITRATE SELECT BIT1
sbit CPHA    =  0xFA;	//SPICON.2 - SPI CLOCK PHASE SELECT
sbit CPOL    =  0xFB;	//SPICON.3 - SPI CLOCK POLARITY SELECT
sbit SPIM    =  0xFC;	//SPICON.4 - SPI MASTER/SLAVE MODE SELECT
sbit SPE     =  0xFD;	//SPICON.5 - SPI INTERFACE ENABLE
sbit WCOL    =  0xFE;	//SPICON.6 - SPI WRITE COLLISION ERROR FLAG
sbit ISPI    =  0xFF;	//SPICON.7 - SPI INTERRUPT BIT




