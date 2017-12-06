	PRESERVE8
	THUMB
	AREA	appcode,	CODE,	READONLY
	EXPORT __main
	ENTRY
__main  FUNCTION
	MOV r0, #0x20000000 	;r0--> start address of stack in memory
	SUB r1, r0, #4 		;r1--> stack top in the memory	

	;Push Data On to stack
	ADD r1, #4     ;r1=20000000
	VLDR.F32 s0, =32.870000
	VSTR.F32 s0, [r1]

	;Push Data On to stack
	ADD r1, #4     ;r1=20000004
	VLDR.F32 s0, =0.000000
	VSTR.F32 s0, [r1]

	;Push Data On to stack
	ADD r1, #4     ;r1=20000008
	VLDR.F32 s0, =23.000000
	VSTR.F32 s0, [r1]

	;arithmetic Operation
	VLDR.F32 s0, [r1]
	SUB r1, #4
	VLDR.F32 s1, [r1]
	VSUB.F32 s1, s0
	VSTR.F32 s1, [r1]

	;arithmetic Operation
	VLDR.F32 s0, [r1]
	SUB r1, #4
	VLDR.F32 s1, [r1]
	VMUL.F32 s1, s0
	VSTR.F32 s1, [r1]

	;Push Data On to stack
	ADD r1, #4     ;r1=2000000c
	VLDR.F32 s0, =54.000000
	VSTR.F32 s0, [r1]

	;Push Data On to stack
	ADD r1, #4     ;r1=20000010
	VLDR.F32 s0, =2.000000
	VSTR.F32 s0, [r1]

	;arithmetic Operation
	VLDR.F32 s0, [r1]
	SUB r1, #4
	VLDR.F32 s1, [r1]
	;Div by 0 Check
	VMOV r4, s0
	CMP r4, #0
	MOVEQ r3, #1
	BEQ stop
	VDIV.F32 s1, s0
	VSTR.F32 s1, [r1]

	;Push Data On to stack
	ADD r1, #4     ;r1=20000014
	VLDR.F32 s0, =5.300000
	VSTR.F32 s0, [r1]

	;Push Data On to stack
	ADD r1, #4     ;r1=20000018
	VLDR.F32 s0, =6.500000
	VSTR.F32 s0, [r1]

	;arithmetic Operation
	VLDR.F32 s0, [r1]
	SUB r1, #4
	VLDR.F32 s1, [r1]
	;Div by 0 Check
	VMOV r4, s0
	CMP r4, #0
	MOVEQ r3, #1
	BEQ stop
	VDIV.F32 s1, s0
	VSTR.F32 s1, [r1]

	;arithmetic Operation
	VLDR.F32 s0, [r1]
	SUB r1, #4
	VLDR.F32 s1, [r1]
	VMUL.F32 s1, s0
	VSTR.F32 s1, [r1]

	;arithmetic Operation
	VLDR.F32 s0, [r1]
	SUB r1, #4
	VLDR.F32 s1, [r1]
	VADD.F32 s1, s0
	VSTR.F32 s1, [r1]

	;Push Data On to stack
	ADD r1, #4     ;r1=2000001c
	VLDR.F32 s0, =96.990000
	VSTR.F32 s0, [r1]

	;arithmetic Operation
	VLDR.F32 s0, [r1]
	SUB r1, #4
	VLDR.F32 s1, [r1]
	VADD.F32 s1, s0
	VSTR.F32 s1, [r1]

stop B stop		; Infinite Loop at the end
	ENDFUNC
	END
