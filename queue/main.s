 PRESERVE8 ; Preserve 8 byte stack alignment
 THUMB ; indicate THUMB code is used
AREA |.text|, CODE, READONLY;Start of the CODE area
EXPORT norm_sq_asm
norm_sq_asm FUNCTION
	; Input array address: R0
	; Number of elements: R1
	MOVS R2, R0 ; move the address in R0 to R2
	MOVS R0, #0 ; initialize the result
sum_loop
	LDRSH R3, [R2],#0x2; load int16_t value pointed to
	; by R2 into R3, then increment
	MLA R0, R3, R3, R0; sq & accum in one step (faster)
	SUBS R1, R1, #1; R1 = R1 - 1, decrement the count
	CMP R1, #0 ; compare to 0 and set Z register
	BNE sum_loop; branch if compare not zero
	BX LR ; return R0
	ENDFUNC
	END ; End of file