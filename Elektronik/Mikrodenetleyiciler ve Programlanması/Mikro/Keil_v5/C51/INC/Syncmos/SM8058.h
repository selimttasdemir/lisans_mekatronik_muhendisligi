/*--------------------------------------------------------------------------
SM8058.H
Registers definition for SyncMOS SM8058

Copyright (c) 2004 Keil Elektronik GmbH and Keil Software, Inc.
All rights reserved.
-------------------------------------------------------------------------- */

/* Byte Addresses */
sfr   P0   	 = 0x80;
sfr   SP   	 = 0x81;
sfr   DPL   	 = 0x82;
sfr   DPH   	 = 0x83;
sfr   PCON   	 = 0x87;
sfr   TCON   	 = 0x88;
sfr   TMOD   	 = 0x89;
sfr   TL0   	 = 0x8A;
sfr   TL1   	 = 0x8B;
sfr   TH0   	 = 0x8C;
sfr   TH1   	 = 0x8D;
sfr   P1   	 = 0x90;
sfr   SCON   	 = 0x98;
sfr   SBUF   	 = 0x99;
sfr   P2   	 = 0xA0;
sfr   IE   	 = 0xA8;
sfr   P3   	 = 0xB0;
sfr   IP   	 = 0xB8;
sfr   PSW   	 = 0xD0;
sfr   ACC   	 = 0xE0;
sfr   B   	 = 0xF0;

/* Bit Addresses */

/* TCON */
sbit   IT0   	 = TCON^0;
sbit   IE0   	 = TCON^1;
sbit   IT1   	 = TCON^2;
sbit   IE1   	 = TCON^3;
sbit   TR0   	 = TCON^4;
sbit   TF0   	 = TCON^5;
sbit   TR1   	 = TCON^6;
sbit   TF1   	 = TCON^7;

/* SCON */
sbit   RI   	 = SCON^0;
sbit   TI   	 = SCON^1;
sbit   RB8   	 = SCON^2;
sbit   TB8   	 = SCON^3;
sbit   REN   	 = SCON^4;
sbit   SM3   	 = SCON^5;
sbit   SM1   	 = SCON^6;
sbit   SM0   	 = SCON^7;

/* IE */
sbit   EX0   	 = IE^0;
sbit   ET0   	 = IE^1;
sbit   EX1   	 = IE^2;
sbit   ET1   	 = IE^3;
sbit   ES   	 = IE^4;
sbit   EA   	 = IE^7;

/* IP */
sbit   PX0   	 = IP^0;
sbit   PT0   	 = IP^1;
sbit   PX1   	 = IP^2;
sbit   PT1   	 = IP^3;
sbit   PS   	 = IP^4;

/* PSW */
sbit   P   	 = PSW^0;
sbit   OV   	 = PSW^2;
sbit   RS0   	 = PSW^3;
sbit   RS1   	 = PSW^4;
sbit   F0   	 = PSW^5;
sbit   AC   	 = PSW^6;
sbit   CY   	 = PSW^7;
