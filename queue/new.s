; An ASM File Containing sqrt() and a norm_squared() algorithm
;
; Mark Wickert, February 2015

    PRESERVE8 ; Preserve 8 byte stack alignment
    THUMB     ; indicate THUMB code is used
    AREA |.text|, CODE, READONLY ; Start of the CODE area

	EXPORT main
main 
	MOVW R1, #0x1
	MOVS R2, #0x2 	
	ADDS R3,R2,R1
	END   