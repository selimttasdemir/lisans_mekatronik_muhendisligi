NAME	DELAY

PR_delay_DELAY     SEGMENT CODE
DT_delay_DELAY     SEGMENT DATA OVERLAYABLE
	PUBLIC	_delay

	RSEG  DT_delay_DELAY

delay_BYTE:
					;Define variable to be used
     length_040:   DS   1		;Paramater passed into function
     var0:	   DS	1               ;Variables for delay loop
     var1:	   DS   1
; #pragma SRC                           ;Code from original c file
;
; void delay(int length);
; void delay(int length)

	RSEG  PR_delay_DELAY
_delay:
					; SOURCE LINE # 4
	MOV  	length_040,R7           ; Paramater passed in as R6/R7
					; Since length is always <11 we only use R7
; {
LOOP:   MOV     var1,#200       	; 200 * 500us = 100ms
DLY1:   MOV     var0,#229       	; 229 * 2.17us = 500us
        DJNZ    var0,$          	; sit here for 500us
        DJNZ    var1,DLY1       	; repeat 200 times (100ms delay)
	DJNZ	length_040,LOOP
;	 }			; SOURCE LINE # 6
	RET
; END OF _delay

	END






