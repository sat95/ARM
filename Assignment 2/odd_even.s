     PRESERVE8
     THUMB
     AREA     appcode, CODE, READONLY
     EXPORT __main
	 ENTRY 
__main  FUNCTION		 
		mov r0,#8     				; Given Number 
		mov r1,#0x20000000			;At this addres 0E->Even Number
									;				0D->ODD Number
		mov r2,#13
		mov r3,#14
		tst r0,#1
		BEQ even
		BNE odd
even	str r3,[r1]
		B stop
		
odd		str r2,[r1]	
stop B stop ; stop program
     ENDFUNC
     END