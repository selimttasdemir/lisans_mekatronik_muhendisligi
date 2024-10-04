//------------------------------------------------------------------------------
// Copyright 2014 Silicon Laboratories, Inc.
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
//Supported Devices:
//  EFM8BB10F2G
//  EFM8BB10F4G
//  EFM8BB10F8G
//  EFM8BB10F8G
//  EFM8BB10F8G

#ifndef SI_EFM8BB1_DEFS_H
#define SI_EFM8BB1_DEFS_H

#include <si_toolchain.h>

//-----------------------------------------------------------------------------
// Register Definitions
//-----------------------------------------------------------------------------
SI_SFR (ACC,      0xE0); ///< Accumulator                            
SI_SFR (ADC0AC,   0xB3); ///< ADC0 Accumulator Configuration         
SI_SFR (ADC0CF,   0xBC); ///< ADC0 Configuration                     
SI_SFR (ADC0CN0,  0xE8); ///< ADC0 Control 0                         
SI_SFR (ADC0CN1,  0xB2); ///< ADC0 Control 1                         
SI_SFR (ADC0GTH,  0xC4); ///< ADC0 Greater-Than High Byte            
SI_SFR (ADC0GTL,  0xC3); ///< ADC0 Greater-Than Low Byte             
SI_SFR (ADC0H,    0xBE); ///< ADC0 Data Word High Byte               
SI_SFR (ADC0L,    0xBD); ///< ADC0 Data Word Low Byte                
SI_SFR (ADC0LTH,  0xC6); ///< ADC0 Less-Than High Byte               
SI_SFR (ADC0LTL,  0xC5); ///< ADC0 Less-Than Low Byte                
SI_SFR (ADC0MX,   0xBB); ///< ADC0 Multiplexer Selection             
SI_SFR (ADC0PWR,  0xDF); ///< ADC0 Power Control                     
SI_SFR (ADC0TK,   0xB9); ///< ADC0 Burst Mode Track Time             
SI_SFR (B,        0xF0); ///< B Register                             
SI_SFR (CKCON0,   0x8E); ///< Clock Control 0                        
SI_SFR (CLKSEL,   0xA9); ///< Clock Select                           
SI_SFR (CMP0CN0,  0x9B); ///< Comparator 0 Control 0                 
SI_SFR (CMP0MD,   0x9D); ///< Comparator 0 Mode                      
SI_SFR (CMP0MX,   0x9F); ///< Comparator 0 Multiplexer Selection     
SI_SFR (CMP1CN0,  0xBF); ///< Comparator 1 Control 0                 
SI_SFR (CMP1MD,   0xAB); ///< Comparator 1 Mode                      
SI_SFR (CMP1MX,   0xAA); ///< Comparator 1 Multiplexer Selection     
SI_SFR (CRC0AUTO, 0xD2); ///< CRC0 Automatic Control                 
SI_SFR (CRC0CN0,  0xCE); ///< CRC0 Control 0                         
SI_SFR (CRC0CNT,  0xD3); ///< CRC0 Automatic Flash Sector Count      
SI_SFR (CRC0DAT,  0xDE); ///< CRC0 Data Output                       
SI_SFR (CRC0FLIP, 0xCF); ///< CRC0 Bit Flip                          
SI_SFR (CRC0IN,   0xDD); ///< CRC0 Data Input                        
SI_SFR (DERIVID,  0xAD); ///< Derivative Identification              
SI_SFR (DEVICEID, 0xB5); ///< Device Identification                  
SI_SFR (DPH,      0x83); ///< Data Pointer High                      
SI_SFR (DPL,      0x82); ///< Data Pointer Low                       
SI_SFR (EIE1,     0xE6); ///< Extended Interrupt Enable 1            
SI_SFR (EIP1,     0xF3); ///< Extended Interrupt Priority 1          
SI_SFR (FLKEY,    0xB7); ///< Flash Lock and Key                     
SI_SFR (HFO0CAL,  0xC7); ///< High Frequency Oscillator 0 Calibration
SI_SFR (IE,       0xA8); ///< Interrupt Enable                       
SI_SFR (IP,       0xB8); ///< Interrupt Priority                     
SI_SFR (IT01CF,   0xE4); ///< INT0/INT1 Configuration                
SI_SFR (LFO0CN,   0xB1); ///< Low Frequency Oscillator Control       
SI_SFR (P0,       0x80); ///< Port 0 Pin Latch                       
SI_SFR (P0MASK,   0xFE); ///< Port 0 Mask                            
SI_SFR (P0MAT,    0xFD); ///< Port 0 Match                           
SI_SFR (P0MDIN,   0xF1); ///< Port 0 Input Mode                      
SI_SFR (P0MDOUT,  0xA4); ///< Port 0 Output Mode                     
SI_SFR (P0SKIP,   0xD4); ///< Port 0 Skip                            
SI_SFR (P1,       0x90); ///< Port 1 Pin Latch                       
SI_SFR (P1MASK,   0xEE); ///< Port 1 Mask                            
SI_SFR (P1MAT,    0xED); ///< Port 1 Match                           
SI_SFR (P1MDIN,   0xF2); ///< Port 1 Input Mode                      
SI_SFR (P1MDOUT,  0xA5); ///< Port 1 Output Mode                     
SI_SFR (P1SKIP,   0xD5); ///< Port 1 Skip                            
SI_SFR (P2,       0xA0); ///< Port 2 Pin Latch                       
SI_SFR (P2MDOUT,  0xA6); ///< Port 2 Output Mode                     
SI_SFR (PCA0CENT, 0x9E); ///< PCA Center Alignment Enable            
SI_SFR (PCA0CLR,  0x9C); ///< PCA Comparator Clear Control           
SI_SFR (PCA0CN0,  0xD8); ///< PCA Control                            
SI_SFR (PCA0CPH0, 0xFC); ///< PCA Channel 0 Capture Module High Byte 
SI_SFR (PCA0CPH1, 0xEA); ///< PCA Channel 1 Capture Module High Byte 
SI_SFR (PCA0CPH2, 0xEC); ///< PCA Channel 2 Capture Module High Byte 
SI_SFR (PCA0CPL0, 0xFB); ///< PCA Channel 0 Capture Module Low Byte  
SI_SFR (PCA0CPL1, 0xE9); ///< PCA Channel 1 Capture Module Low Byte  
SI_SFR (PCA0CPL2, 0xEB); ///< PCA Channel 2 Capture Module Low Byte  
SI_SFR (PCA0CPM0, 0xDA); ///< PCA Channel 0 Capture/Compare Mode     
SI_SFR (PCA0CPM1, 0xDB); ///< PCA Channel 1 Capture/Compare Mode     
SI_SFR (PCA0CPM2, 0xDC); ///< PCA Channel 2 Capture/Compare Mode     
SI_SFR (PCA0H,    0xFA); ///< PCA Counter/Timer High Byte            
SI_SFR (PCA0L,    0xF9); ///< PCA Counter/Timer Low Byte             
SI_SFR (PCA0MD,   0xD9); ///< PCA Mode                               
SI_SFR (PCA0POL,  0x96); ///< PCA Output Polarity                    
SI_SFR (PCA0PWM,  0xF7); ///< PCA PWM Configuration                  
SI_SFR (PCON0,    0x87); ///< Power Control                          
SI_SFR (PRTDRV,   0xF6); ///< Port Drive Strength                    
SI_SFR (PSCTL,    0x8F); ///< Program Store Control                  
SI_SFR (PSW,      0xD0); ///< Program Status Word                    
SI_SFR (REF0CN,   0xD1); ///< Voltage Reference Control              
SI_SFR (REG0CN,   0xC9); ///< Voltage Regulator 0 Control            
SI_SFR (REVID,    0xB6); ///< Revision Identifcation                 
SI_SFR (RSTSRC,   0xEF); ///< Reset Source                           
SI_SFR (SBUF0,    0x99); ///< UART0 Serial Port Data Buffer          
SI_SFR (SCON0,    0x98); ///< UART0 Serial Port Control              
SI_SFR (SMB0ADM,  0xD6); ///< SMBus 0 Slave Address Mask             
SI_SFR (SMB0ADR,  0xD7); ///< SMBus 0 Slave Address                  
SI_SFR (SMB0CF,   0xC1); ///< SMBus 0 Configuration                  
SI_SFR (SMB0CN0,  0xC0); ///< SMBus 0 Control                        
SI_SFR (SMB0DAT,  0xC2); ///< SMBus 0 Data                           
SI_SFR (SMB0TC,   0xAC); ///< SMBus 0 Timing and Pin Control         
SI_SFR (SP,       0x81); ///< Stack Pointer                          
SI_SFR (SPI0CFG,  0xA1); ///< SPI0 Configuration                     
SI_SFR (SPI0CKR,  0xA2); ///< SPI0 Clock Rate                        
SI_SFR (SPI0CN0,  0xF8); ///< SPI0 Control                           
SI_SFR (SPI0DAT,  0xA3); ///< SPI0 Data                              
SI_SFR (TCON,     0x88); ///< Timer 0/1 Control                      
SI_SFR (TH0,      0x8C); ///< Timer 0 High Byte                      
SI_SFR (TH1,      0x8D); ///< Timer 1 High Byte                      
SI_SFR (TL0,      0x8A); ///< Timer 0 Low Byte                       
SI_SFR (TL1,      0x8B); ///< Timer 1 Low Byte                       
SI_SFR (TMOD,     0x89); ///< Timer 0/1 Mode                         
SI_SFR (TMR2CN0,  0xC8); ///< Timer 2 Control 0                      
SI_SFR (TMR2H,    0xCD); ///< Timer 2 High Byte                      
SI_SFR (TMR2L,    0xCC); ///< Timer 2 Low Byte                       
SI_SFR (TMR2RLH,  0xCB); ///< Timer 2 Reload High Byte               
SI_SFR (TMR2RLL,  0xCA); ///< Timer 2 Reload Low Byte                
SI_SFR (TMR3CN0,  0x91); ///< Timer 3 Control 0                      
SI_SFR (TMR3H,    0x95); ///< Timer 3 High Byte                      
SI_SFR (TMR3L,    0x94); ///< Timer 3 Low Byte                       
SI_SFR (TMR3RLH,  0x93); ///< Timer 3 Reload High Byte               
SI_SFR (TMR3RLL,  0x92); ///< Timer 3 Reload Low Byte                
SI_SFR (VDM0CN,   0xFF); ///< Supply Monitor Control                 
SI_SFR (WDTCN,    0x97); ///< Watchdog Timer Control                 
SI_SFR (XBR0,     0xE1); ///< Port I/O Crossbar 0                    
SI_SFR (XBR1,     0xE2); ///< Port I/O Crossbar 1                    
SI_SFR (XBR2,     0xE3); ///< Port I/O Crossbar 2                    

//------------------------------------------------------------------------------
// 16-bit Register Definitions (may not work on all compilers)
//------------------------------------------------------------------------------
SI_SFR16 (ADC0GT,  0xC3); ///< ADC0 Greater-Than            
SI_SFR16 (ADC0,    0xBD); ///< ADC0 Data Word               
SI_SFR16 (ADC0LT,  0xC5); ///< ADC0 Less-Than               
SI_SFR16 (DP,      0x82); ///< Data Pointer                 
SI_SFR16 (PCA0CP0, 0xFB); ///< PCA Channel 0 Capture Module 
SI_SFR16 (PCA0CP1, 0xE9); ///< PCA Channel 1 Capture Module 
SI_SFR16 (PCA0CP2, 0xEB); ///< PCA Channel 2 Capture Module 
SI_SFR16 (PCA0,    0xF9); ///< PCA Counter/Timer            
SI_SFR16 (TMR2,    0xCC); ///< Timer 2                      
SI_SFR16 (TMR2RL,  0xCA); ///< Timer 2 Reload               
SI_SFR16 (TMR3,    0x94); ///< Timer 3                      
SI_SFR16 (TMR3RL,  0x92); ///< Timer 3 Reload               

//------------------------------------------------------------------------------
// Indirect Register Definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Bit Definitions
//------------------------------------------------------------------------------

// ACC (Accumulator)
#define SFR_ACC 0xE0
SI_SBIT (ACC_ACC0, SFR_ACC, 0); ///< Accumulator Bit 0
SI_SBIT (ACC_ACC1, SFR_ACC, 1); ///< Accumulator Bit 1
SI_SBIT (ACC_ACC2, SFR_ACC, 2); ///< Accumulator Bit 2
SI_SBIT (ACC_ACC3, SFR_ACC, 3); ///< Accumulator Bit 3
SI_SBIT (ACC_ACC4, SFR_ACC, 4); ///< Accumulator Bit 4
SI_SBIT (ACC_ACC5, SFR_ACC, 5); ///< Accumulator Bit 5
SI_SBIT (ACC_ACC6, SFR_ACC, 6); ///< Accumulator Bit 6
SI_SBIT (ACC_ACC7, SFR_ACC, 7); ///< Accumulator Bit 7

// ADC0CN0 (ADC0 Control 0)
#define SFR_ADC0CN0 0xE8
SI_SBIT (ADC0CN0_ADCM0,  SFR_ADC0CN0, 0); ///< Start of Conversion Mode Select Bit 0
SI_SBIT (ADC0CN0_ADCM1,  SFR_ADC0CN0, 1); ///< Start of Conversion Mode Select Bit 1
SI_SBIT (ADC0CN0_ADCM2,  SFR_ADC0CN0, 2); ///< Start of Conversion Mode Select Bit 2
SI_SBIT (ADC0CN0_ADWINT, SFR_ADC0CN0, 3); ///< Window Compare Interrupt Flag        
SI_SBIT (ADC0CN0_ADBUSY, SFR_ADC0CN0, 4); ///< ADC Busy                             
SI_SBIT (ADC0CN0_ADINT,  SFR_ADC0CN0, 5); ///< Conversion Complete Interrupt Flag   
SI_SBIT (ADC0CN0_ADBMEN, SFR_ADC0CN0, 6); ///< Burst Mode Enable                    
SI_SBIT (ADC0CN0_ADEN,   SFR_ADC0CN0, 7); ///< ADC Enable                           

// B (B Register)
#define SFR_B 0xF0
SI_SBIT (B_B0, SFR_B, 0); ///< B Register Bit 0
SI_SBIT (B_B1, SFR_B, 1); ///< B Register Bit 1
SI_SBIT (B_B2, SFR_B, 2); ///< B Register Bit 2
SI_SBIT (B_B3, SFR_B, 3); ///< B Register Bit 3
SI_SBIT (B_B4, SFR_B, 4); ///< B Register Bit 4
SI_SBIT (B_B5, SFR_B, 5); ///< B Register Bit 5
SI_SBIT (B_B6, SFR_B, 6); ///< B Register Bit 6
SI_SBIT (B_B7, SFR_B, 7); ///< B Register Bit 7

// IE (Interrupt Enable)
#define SFR_IE 0xA8
SI_SBIT (IE_EX0,   SFR_IE, 0); ///< External Interrupt 0 Enable
SI_SBIT (IE_ET0,   SFR_IE, 1); ///< Timer 0 Interrupt Enable   
SI_SBIT (IE_EX1,   SFR_IE, 2); ///< External Interrupt 1 Enable
SI_SBIT (IE_ET1,   SFR_IE, 3); ///< Timer 1 Interrupt Enable   
SI_SBIT (IE_ES0,   SFR_IE, 4); ///< UART0 Interrupt Enable     
SI_SBIT (IE_ET2,   SFR_IE, 5); ///< Timer 2 Interrupt Enable   
SI_SBIT (IE_ESPI0, SFR_IE, 6); ///< SPI0 Interrupt Enable      
SI_SBIT (IE_EA,    SFR_IE, 7); ///< All Interrupts Enable      

// IP (Interrupt Priority)
#define SFR_IP 0xB8
SI_SBIT (IP_PX0,   SFR_IP, 0); ///< External Interrupt 0 Priority Control                        
SI_SBIT (IP_PT0,   SFR_IP, 1); ///< Timer 0 Interrupt Priority Control                           
SI_SBIT (IP_PX1,   SFR_IP, 2); ///< External Interrupt 1 Priority Control                        
SI_SBIT (IP_PT1,   SFR_IP, 3); ///< Timer 1 Interrupt Priority Control                           
SI_SBIT (IP_PS0,   SFR_IP, 4); ///< UART0 Interrupt Priority Control                             
SI_SBIT (IP_PT2,   SFR_IP, 5); ///< Timer 2 Interrupt Priority Control                           
SI_SBIT (IP_PSPI0, SFR_IP, 6); ///< Serial Peripheral Interface (SPI0) Interrupt Priority Control

// P0 (Port 0 Pin Latch)
#define SFR_P0 0x80
SI_SBIT (P0_B0, SFR_P0, 0); ///< Port 0 Bit 0 Latch
SI_SBIT (P0_B1, SFR_P0, 1); ///< Port 0 Bit 1 Latch
SI_SBIT (P0_B2, SFR_P0, 2); ///< Port 0 Bit 2 Latch
SI_SBIT (P0_B3, SFR_P0, 3); ///< Port 0 Bit 3 Latch
SI_SBIT (P0_B4, SFR_P0, 4); ///< Port 0 Bit 4 Latch
SI_SBIT (P0_B5, SFR_P0, 5); ///< Port 0 Bit 5 Latch
SI_SBIT (P0_B6, SFR_P0, 6); ///< Port 0 Bit 6 Latch
SI_SBIT (P0_B7, SFR_P0, 7); ///< Port 0 Bit 7 Latch

// P1 (Port 1 Pin Latch)
#define SFR_P1 0x90
SI_SBIT (P1_B0, SFR_P1, 0); ///< Port 1 Bit 0 Latch
SI_SBIT (P1_B1, SFR_P1, 1); ///< Port 1 Bit 1 Latch
SI_SBIT (P1_B2, SFR_P1, 2); ///< Port 1 Bit 2 Latch
SI_SBIT (P1_B3, SFR_P1, 3); ///< Port 1 Bit 3 Latch
SI_SBIT (P1_B4, SFR_P1, 4); ///< Port 1 Bit 4 Latch
SI_SBIT (P1_B5, SFR_P1, 5); ///< Port 1 Bit 5 Latch
SI_SBIT (P1_B6, SFR_P1, 6); ///< Port 1 Bit 6 Latch
SI_SBIT (P1_B7, SFR_P1, 7); ///< Port 1 Bit 7 Latch

// P2 (Port 2 Pin Latch)
#define SFR_P2 0xA0
SI_SBIT (P2_B0, SFR_P2, 0); ///< Port 2 Bit 0 Latch
SI_SBIT (P2_B1, SFR_P2, 1); ///< Port 2 Bit 1 Latch

// PCA0CN0 (PCA Control)
#define SFR_PCA0CN0 0xD8
SI_SBIT (PCA0CN0_CCF0, SFR_PCA0CN0, 0); ///< PCA Module 0 Capture/Compare Flag
SI_SBIT (PCA0CN0_CCF1, SFR_PCA0CN0, 1); ///< PCA Module 1 Capture/Compare Flag
SI_SBIT (PCA0CN0_CCF2, SFR_PCA0CN0, 2); ///< PCA Module 2 Capture/Compare Flag
SI_SBIT (PCA0CN0_CR,   SFR_PCA0CN0, 6); ///< PCA Counter/Timer Run Control    
SI_SBIT (PCA0CN0_CF,   SFR_PCA0CN0, 7); ///< PCA Counter/Timer Overflow Flag  

// PSW (Program Status Word)
#define SFR_PSW 0xD0
SI_SBIT (PSW_PARITY, SFR_PSW, 0); ///< Parity Flag               
SI_SBIT (PSW_F1,     SFR_PSW, 1); ///< User Flag 1               
SI_SBIT (PSW_OV,     SFR_PSW, 2); ///< Overflow Flag             
SI_SBIT (PSW_RS0,    SFR_PSW, 3); ///< Register Bank Select Bit 0
SI_SBIT (PSW_RS1,    SFR_PSW, 4); ///< Register Bank Select Bit 1
SI_SBIT (PSW_F0,     SFR_PSW, 5); ///< User Flag 0               
SI_SBIT (PSW_AC,     SFR_PSW, 6); ///< Auxiliary Carry Flag      
SI_SBIT (PSW_CY,     SFR_PSW, 7); ///< Carry Flag                

// SCON0 (UART0 Serial Port Control)
#define SFR_SCON0 0x98
SI_SBIT (SCON0_RI,    SFR_SCON0, 0); ///< Receive Interrupt Flag             
SI_SBIT (SCON0_TI,    SFR_SCON0, 1); ///< Transmit Interrupt Flag            
SI_SBIT (SCON0_RB8,   SFR_SCON0, 2); ///< Ninth Receive Bit                  
SI_SBIT (SCON0_TB8,   SFR_SCON0, 3); ///< Ninth Transmission Bit             
SI_SBIT (SCON0_REN,   SFR_SCON0, 4); ///< Receive Enable                     
SI_SBIT (SCON0_MCE,   SFR_SCON0, 5); ///< Multiprocessor Communication Enable
SI_SBIT (SCON0_SMODE, SFR_SCON0, 7); ///< Serial Port 0 Operation Mode       

// SMB0CN0 (SMBus 0 Control)
#define SFR_SMB0CN0 0xC0
SI_SBIT (SMB0CN0_SI,      SFR_SMB0CN0, 0); ///< SMBus Interrupt Flag            
SI_SBIT (SMB0CN0_ACK,     SFR_SMB0CN0, 1); ///< SMBus Acknowledge               
SI_SBIT (SMB0CN0_ARBLOST, SFR_SMB0CN0, 2); ///< SMBus Arbitration Lost Indicator
SI_SBIT (SMB0CN0_ACKRQ,   SFR_SMB0CN0, 3); ///< SMBus Acknowledge Request       
SI_SBIT (SMB0CN0_STO,     SFR_SMB0CN0, 4); ///< SMBus Stop Flag                 
SI_SBIT (SMB0CN0_STA,     SFR_SMB0CN0, 5); ///< SMBus Start Flag                
SI_SBIT (SMB0CN0_TXMODE,  SFR_SMB0CN0, 6); ///< SMBus Transmit Mode Indicator   
SI_SBIT (SMB0CN0_MASTER,  SFR_SMB0CN0, 7); ///< SMBus Master/Slave Indicator    

// SPI0CN0 (SPI0 Control)
#define SFR_SPI0CN0 0xF8
SI_SBIT (SPI0CN0_SPIEN,  SFR_SPI0CN0, 0); ///< SPI0 Enable            
SI_SBIT (SPI0CN0_TXBMT,  SFR_SPI0CN0, 1); ///< Transmit Buffer Empty  
SI_SBIT (SPI0CN0_NSSMD0, SFR_SPI0CN0, 2); ///< Slave Select Mode Bit 0
SI_SBIT (SPI0CN0_NSSMD1, SFR_SPI0CN0, 3); ///< Slave Select Mode Bit 1
SI_SBIT (SPI0CN0_RXOVRN, SFR_SPI0CN0, 4); ///< Receive Overrun Flag   
SI_SBIT (SPI0CN0_MODF,   SFR_SPI0CN0, 5); ///< Mode Fault Flag        
SI_SBIT (SPI0CN0_WCOL,   SFR_SPI0CN0, 6); ///< Write Collision Flag   
SI_SBIT (SPI0CN0_SPIF,   SFR_SPI0CN0, 7); ///< SPI0 Interrupt Flag    

// TCON (Timer 0/1 Control)
#define SFR_TCON 0x88
SI_SBIT (TCON_IT0, SFR_TCON, 0); ///< Interrupt 0 Type Select
SI_SBIT (TCON_IE0, SFR_TCON, 1); ///< External Interrupt 0   
SI_SBIT (TCON_IT1, SFR_TCON, 2); ///< Interrupt 1 Type Select
SI_SBIT (TCON_IE1, SFR_TCON, 3); ///< External Interrupt 1   
SI_SBIT (TCON_TR0, SFR_TCON, 4); ///< Timer 0 Run Control    
SI_SBIT (TCON_TF0, SFR_TCON, 5); ///< Timer 0 Overflow Flag  
SI_SBIT (TCON_TR1, SFR_TCON, 6); ///< Timer 1 Run Control    
SI_SBIT (TCON_TF1, SFR_TCON, 7); ///< Timer 1 Overflow Flag  

// TMR2CN0 (Timer 2 Control 0)
#define SFR_TMR2CN0 0xC8
SI_SBIT (TMR2CN0_T2XCLK,  SFR_TMR2CN0, 0); ///< Timer 2 External Clock Select    
SI_SBIT (TMR2CN0_TR2,     SFR_TMR2CN0, 2); ///< Timer 2 Run Control              
SI_SBIT (TMR2CN0_T2SPLIT, SFR_TMR2CN0, 3); ///< Timer 2 Split Mode Enable        
SI_SBIT (TMR2CN0_TF2CEN,  SFR_TMR2CN0, 4); ///< Timer 2 Capture Enable           
SI_SBIT (TMR2CN0_TF2LEN,  SFR_TMR2CN0, 5); ///< Timer 2 Low Byte Interrupt Enable
SI_SBIT (TMR2CN0_TF2L,    SFR_TMR2CN0, 6); ///< Timer 2 Low Byte Overflow Flag   
SI_SBIT (TMR2CN0_TF2H,    SFR_TMR2CN0, 7); ///< Timer 2 High Byte Overflow Flag  

//------------------------------------------------------------------------------
// Interrupt Definitions
//------------------------------------------------------------------------------
#define INT0_IRQn    0  ///< External Interrupt 0      
#define TIMER0_IRQn  1  ///< Timer 0 Overflow          
#define INT1_IRQn    2  ///< External Interrupt 1      
#define TIMER1_IRQn  3  ///< Timer 1 Overflow          
#define UART0_IRQn   4  ///< UART0                     
#define TIMER2_IRQn  5  ///< Timer 2 Overflow / Capture
#define SPI0_IRQn    6  ///< SPI0                      
#define SMBUS0_IRQn  7  ///< SMBus0                    
#define PMATCH_IRQn  8  ///< Port Match                
#define ADC0WC_IRQn  9  ///< ADC0 Window Compare       
#define ADC0EOC_IRQn 10 ///< ADC0 End of Conversion    
#define PCA0_IRQn    11 ///< PCA0                      
#define CMP0_IRQn    12 ///< Comparator 0              
#define CMP1_IRQn    13 ///< Comparator 1              
#define TIMER3_IRQn  14 ///< Timer 3 Overflow / Capture

//-----------------------------------------------------------------------------
// SDCC PDATA External Memory Paging Support
//-----------------------------------------------------------------------------

#if defined SDCC

SI_SFR(_XPAGE, 0xAA); // Point to the EMI0CN register

#endif

#endif // SI_EFM8BB1_DEFS_H
//-eof--------------------------------------------------------------------------

