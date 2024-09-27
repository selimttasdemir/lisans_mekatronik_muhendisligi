$MOD51
; Ozel adres tanimlamalari yapilir
PLLCON  EQU 0XD7;
T3FD    EQU 0X9D;
T3CON   EQU 0X9E;
CSEG

ORG 0000H
; Seri port dan PORT 0.0 a bagli butona(logic 0) basilinca 
; Adinizi PORT 0.1 a bagli butona(logic 0) basilinca 
; Numaranizi yazdiran program

; Program ilgili butonlara basilinca sadece bir kere serial
; Monitore yazdirma islemi yapar.Buton logic 1 yapilip tekrar
; Logic 0 yapilana kadar bir daha yazdirma yapmaz!

BASLA: 
;__________________________________________________________________________________________
     ;CLOCK VE P0 PORTU AYARLARI	 
MOV PLLCON,#00H        ; Sistem saat frekansini 16.78mhz olarak ayarlar
MOV P0, #0FFH          ; P0 portu giris olarak tanimlar
WR_NAME EQU P0.0       ; WR_NAME, P0 portunun 0. bitini temsil eder (P0.0)
WR_NUMBER EQU P0.1	   ; WR_NUMBER, P0 portunun 1. bitini temsil eder (P0.1)

;____________________________________________________________________________________
     ;SERI HABERLESME MODU VE BAUD RATE HIZI AYARLARI

; Bu degerler ADUC841_842_843 datasheet'inde Tablo 35 16.777216 MHz PLL Clock da
; Timer 3 icin yaygin kullanilan Baud Rates tablosundan alinmistir

MOV T3CON,#86H         ;Baud rate hizini 9600 ayarlar
MOV T3FD ,#2DH         ;Baud rate hizini 9600 ayarlar
MOV SCON ,#50H         ;Seri haberlesme mod1 8 bit uart olarak ayarlar
;__________________________________________________________________________________________


; P0.0 ve P0.1'e bagli butonlarin logic durumu kontrol edilir
; Eger logic 0 ise program gerekli fonksiyonlara yonlendirilir
CONTROL1:
	CALL PORT_READ 						; P0.0 ve P0.1 degerlerini gunceller
	JMP CONTROL2 						; P0.1 portu kontrol edilir 
	CONTUINE:
		CALL PORT_READ 					; P0.0 ve P0.1 degerlerini gunceller		
		CJNE R0,#00H,COUNTER_CHECK1 	; Eger R0 00H dan farkliysa COUNTER_CHECK1'e atlar
		JNB ACC.0,BUTTON1  				; Eger buton logic 0 ise BUTTON1'e atlar


; Buton1 logic 1 ve sayac(R0) 00H dan farkli ise sayac resetlenir
; Diger durumlarda port kontrol dongusunun devam etmesi icin
; CONTROL1'e islem yapilmadan atlanir
COUNTER_CHECK1:
	JB ACC.0,COUNTER1_RESET  	; Eger buton logic 1 ise R0'i resetler
	JMP CONTROL1 				; P0.0 portu kontrol edilir 
	COUNTER1_RESET:
		MOV R0,#00H        		; R0 sayacini sifirlar
		JMP CONTROL1
		
CONTROL2:
	CALL PORT_READ	
	
	CJNE R1,#00H,COUNTER_CHECK2 	; Eger R1 00H dan farkliysa farkliysa COUNTER_CHECK2'e atlar
	JNB ACC.1,BUTTON2  				; Eger buton logic 0 ise BUTTON2'ye atlar
	JMP CONTUINE

; Buton2 logic 1 ve sayac(R1) 00H dan farkli ise sayac resetlenir
; Diger durumlarda port kontrol dongusunun devam etmesi icin
; CONTUINE'e islem yapilmadan atlanir
COUNTER_CHECK2:
	JB ACC.1,COUNTER2_RESET     ; Eger buton logic 1 ise R1'i resetler
	JMP CONTUINE
	COUNTER2_RESET:
		MOV R1,#00H        		; R1 sayacini sifirlar
		JMP CONTUINE

PORT_READ:
	CLR A
    MOV C, WR_NAME     ; P0.0 portundan degeri A register'ina okur
	MOV ACC.0,C
	MOV C, WR_NUMBER   ; P0.1 portundan degeri B register'ina okur
	MOV ACC.1,C
	RETI


BUTTON1:
	CLR A              ; A register'i (Akumulator) sifirlanir (00H)
	MOV DPTR,#AD       ; Adin bulundugu belek adresi okunur
	
	; DPTR ile baslangic adresi alinan adin sonraki karakterlerine
	; gecmek icin R0 sayac olarak kullanilirlar
	
	ADD A,R0		   	  ; Akumulator'e sayac degeri ekler	
	
	MOVC A,@ A+DPTR    	  ; DPTR'nin gösterdigi bellek adresinden itibaren karakterleri
						  ; Akumulator'e atar	
	CALL  SERIAL_WRITE 	  ; Karakterlerin yazdirilmasi icin SERIAL_WRITE'i cagirir
	JZ  CONTROL2       	  ; Eger Akumulator 0 ise CONTUINE'ye atlar
	INC R0             	  ; R0'i 1 arttirir
	JMP BUTTON1        	  ; BUTTON1'e geri doner

BUTTON2:
	CLR A                 ; A register'i (Akumulator) sifirlanir (00H)
	MOV DPTR, #NUM        ; Numaranin bulundugu bellek adresi okunur
	
	; DPTR ile baslangiç adresi alinan numaranin sonraki karakterlerine
	; geçmek için R1 sayac olarak kullanilirlar
	
	ADD A, R1             ; Akumulator'e sayac degeri eklenir
	
	MOVC A,@ A+DPTR       ; DPTR'nin gösterdigi bellek adresinden itibaren karakterleri
	                      ; Akumulator'e atar
	CALL  SERIAL_WRITE    ; Karakterlerin yazdirilmasi için SERIAL_WRITE'i çagirir
	JZ  CONTUINE          ; Eger Akumulator 0 ise CONTROL'e atlar
	INC R1                ; R1'i 1 arttirir
	JMP BUTTON2           ; BUTTON2'ye geri doner
   
; 8051 entegresi bir karakterin yollanmasinin bittigini TI bitini "1" yaparak bildirir. 
; Dolayisiyla bu bitin degeri "1" ise karakterin yollanmasi bitmistir ve yeni bir karakter
; yollanabilir.

SERIAL_WRITE:
	CLR TI 			; Once TI bitini temizle. 
	MOV SBUF, A		; Serial'e Akumulator de tutulan karakter yazdirilir
	JNB TI,$ 		; Karakter yollamasinin bitmesini bekle.
	RETI

; Adi ve numarayi saklamak için bellek alanlari

; 12 ve 13 sayilari ASCII kontrol karakterleridir. 12, Form Feed (FF) karakterini temsil eder
; ve yazicida sayfanin basina geçmek için kullanilabilir.13 ise Carriage Return (CR) karakterini
; temsil eder ve yazicida veya terminalde bir satirin basina gitmek için kullanilir.

; Veriler ayni boyutta yapilarak onceki tum karakterlerin degistirlmesi saglanmis olur.
; Bu sayede her butona tiklandiginda en son yazdirilan metin goruntulenir.

ORG 1000H
AD:DB 12,13,'EMRECAN GULDOGAN',0
ORG 2000H
NUM:DB 12,13,'1910225051     ',0

END
