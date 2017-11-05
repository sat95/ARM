     PRESERVE8
     THUMB
     AREA     appcode, CODE, READONLY
     EXPORT __main
	 ENTRY 
__main  FUNCTION		 
		MOV r1, #8				;First Element
		MOV r2, #20			;Second Element
		MOV r3, #50			;Third Element
		
		CMP r1, r2
		;ITE GT
		BGT first
		BLE second
			
first	CMP r1, r3
		ITE GT
		MOVGT r4, r1
		MOVLE r4, r3             ;Largest of 3 is in r4
		B stop
		
second	CMP r2, r3
		ITE GT
		MOVGT r4, r2
		MOVLE r4, r3			;Largest of 3 is in r4
		B stop
		
stop B stop ; stop program
     ENDFUNC
     END