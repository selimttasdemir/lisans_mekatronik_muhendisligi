$MOD51
	
CSEG
		
ORG 0000H 
;PORT 0 DAN OKUNAN DEGERI PORT1 E ATAYAN PROGRAM

MOV P0,#0FFH ;P0 PORTU GIRIS OLARAK TANIMLANIR

READ:
	MOV C,P0.0
	JC LED
	CLR P3.5
	JMP READ
	
LED:
	SETB P3.5
	JMP READ

END