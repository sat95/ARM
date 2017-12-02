     PRESERVE8
     THUMB
     AREA     appcode, CODE, READONLY
     EXPORT __main
	 ENTRY 
__main  FUNCTION	
	
	VMOV.F32 s0, #9		;x in exp(x)
	MOV r0, #0				;Precision i.e. value of y   when term (X^y)/(y!) = 0
	VMOV.F32 s2, #1			;Denominator i.e. y!
	VMOV.F32 s3, #1			;Numerator i.e (X^y)/(y!)
	VMOV.F32 s5, #1
	;VMOV.F32 s4, #0			;Final result
	
loop	VADD.F32 s4, s3
		VMUL.F32 s3, s0
		VDIV.F32 s3, s2
		VADD.F32 s2, s2, s5
		VMOV.F32 r1, s3
		ADD r0, #1
		CMP r1, #0
		BEQ stop			;Stop when the s3 (X^y)/(y!) = 0 
		BNE loop			;Continue Untill F32 can handle the precision
		
			
stop B stop 				; Infinte Loop at the end
     ENDFUNC
     END