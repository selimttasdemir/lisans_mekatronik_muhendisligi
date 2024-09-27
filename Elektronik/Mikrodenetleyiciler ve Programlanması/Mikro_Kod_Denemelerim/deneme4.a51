$MOD51

; PORT 3.4'dan bagli LED'i 100 ms 'lik araliklarla yakip sonduren program
;MOV P0, #0FFH ; P0 PORTU GIRIS OLARAK TANIMLANIR

LED EQU P3.4
PLLCON EQU 0xD7 ;SFR adres tanimlamasi yapilmasi gerekmektedir	

CSEG
ORG 0000H
MOV PLLCON,#00H ;Islemci freakansi 16.777 MHz olarak ayarlanir 2.097 E GÖRE DEGERLER AYARLI
MOV A,#0FAH
BLINK:
	CPL LED ;Bitleri ters cevirir "0" i "1" , "1" i "0" yapar
	CALL DELAY
	JMP BLINK

DELAY:
	MOV R1,A

DLY0: MOV R2,#0C8H ;Loop1 bekleme degeri
DLY1: MOV R3,#004H ;Loop2 bekleme degeri
		DJNZ R3,$ ; 1 azalt ve 0 olana kadar bekle
		DJNZ R2,DLY1 ;
		DJNZ R1,DLY0
		RET
END