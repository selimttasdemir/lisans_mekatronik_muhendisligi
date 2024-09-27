$MOD51
PLLCON  EQU 0XD7;
T3FD    EQU 0X9D;
T3CON   EQU 0X9E;

CSEG

ORG 0000H

GO: 
; ------------------------------
; CLOCK ve P0 PORTU AYARLARI	 
MOV PLLCON, #00H   ; Sistem frekansini 16.78MHz olarak ayarla
MOV P0, #0FFH      ; P0 portunu giris olarak tanimla
ISIMAD EQU P0.0    ; P0 portunun 0. bitini temsil eder (P0.0)
NUMARANO EQU P0.1  ; P0 portunun 1. bitini temsil eder (P0.1)
; ------------------------------

; SERI HABERLESME MODU VE BAUD RATE HIZI AYARLARI...
MOV T3CON,#86H         ;Baud rate hizini 9600 ayarla
MOV T3FD ,#2DH         ;Baud rate hizini 9600 ayarla
MOV SCON ,#50H         ;Seri haberlesme mod1 8 bit uart olarak ayarla


ORG 1000H
AD: DB 12, 13, 'SELIM TASDEMIR', 0
ORG 2000H
NUM: DB 12, 13, '1810225103    ', 0

KONTROL:
    ; P0.0 ve P0.1'e bagli butonlarin logic durumu kontrol edilir
    ; LOJIK 0 ise kontrol 2 ye git
    CALL PORT_READ
    JMP KONTROL22

DEVAM:
    CALL PORT_READ
    CJNE R0, #00H, SAYAC_1
    JNB ACC.0, BUTON1

SAYAC_1:
    JB ACC.0, SAYAC_1_RESET
    JMP KONTROL

SAYAC_1_RESET:
    MOV R0, #00H
    JMP KONTROL

KONTROL22:
    CALL PORT_READ
    CJNE R1, #00H, SAYAC_2
    JNB ACC.1, BUTON2
    JMP DEVAM

SAYAC_2:
    JB ACC.1, SAYAC_2_RESET
    JMP DEVAM

SAYAC_2_RESET:
    MOV R1, #00H
    JMP DEVAM

PORT_READ:
    CLR A
    MOV C, ISIMAD
    MOV ACC.0, C
    MOV C, NUMARANO
    MOV ACC.1, C
    RETI

BUTON1:
    CLR A
    MOV DPTR, #AD

    ADD A, R0
    MOVC A, @A+DPTR
    CALL SERIALOKUMA
    JZ KONTROL22
    INC R0
    JMP BUTON1

BUTON2:
    CLR A
    MOV DPTR, #NUM

    ADD A, R1
    MOVC A, @A+DPTR
    CALL SERIALOKUMA
    JZ DEVAM
    INC R1
    JMP BUTON2

SERIALOKUMA:
    CLR TI
    MOV SBUF, A
    JNB TI, $
    RETI

END