     PRESERVE8
     THUMB
     AREA     appcode, CODE, READONLY
     EXPORT __main
	 ENTRY 
__main  FUNCTION		 
		MOV r1, #1		;First Fibonacci Element
		MOV r2, #1		;Second Fibonacci Element
		MOV r7, #9		;9th Fibonacci Element
		
		SUB r7, #2
loop	MOV r3, #0
		ADD r3, r1
		ADD r3, r2
		MOV r1, r2
		MOV r2, r3
		SUB r7, #1
		CMP r7, #0
		BGT loop
		
		
stop B stop ; stop program
     ENDFUNC
     END