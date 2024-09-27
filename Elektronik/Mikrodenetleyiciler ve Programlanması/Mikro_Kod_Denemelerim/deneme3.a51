$MOD51

CSEG

ORG 0000H
; PORT 0.0'dan okunan degeri PORT3.5'e atayan ve 
; butona tiklandiginda LED'i yakan program

MOV P0, #0FFH ; P0 PORTU GIRIS OLARAK TANIMLANIR

LED EQU P3.5
BUTTON EQU P0

CONTROL:
    MOV A, BUTTON     ; P0 portundan degeri A register'ina oku

    ; A register'indaki degerle 00000001B (hex #01H) degerini AND islemine tabi tut.
    ; Bu islem, sadece P0.0 bitini korur ve diger bitleri sifirlar.
    ANL A, #01H

    CJNE A, #01H, LED_CONTROL  ; Eger A 01H degilse, LED etiketine atla
    SETB LED    ; Eger A 01H ise, P3.5'i yuksek (LED'i yak) yap
    JMP CONTROL      ; CONTROL etiketine geri don

LED_CONTROL:
    CLR LED      ; P3.5'i dusuk (LED'i sondur) yap
    JMP CONTROL      ; CONTROL etiketine geri don

END
