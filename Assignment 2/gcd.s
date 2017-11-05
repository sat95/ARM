     PRESERVE8
     THUMB
     AREA     appcode, CODE, READONLY
     EXPORT __main
	 ENTRY 
__main  FUNCTION		 
		MOV r1, #24		;First Element a
		MOV r2, #16		;Second Elemnt b
		MOV r3, #0   		;GCD of a and b
		CMP r1,r2
		BNE loop
		MOV r3, r2
		BEQ stop

loop	ITE GT
		SUBGT r1, r2
		SUBLE r2, r1
		
		CMP r1, r2
		BEQ check
		BNE loop

check 	MOV r3, r2
		
stop B stop ; stop program
     ENDFUNC
     END