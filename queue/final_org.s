	PRESERVE8
	THUMB
	;AREA	|.text|, CODE, READONLY
	AREA	appcode, CODE, READONLY
	EXPORT __main
	ENTRY
__main  FUNCTION
		MOV R0,#5
		MOV R0,#11
		MOV R1,R0
		ADD R1,R0
		ADD R1,R1
		ADD R1,R0
		MOV R1, #1
		MOV R2, #2
		MOV R3, #3
		MOV R4, #4
		MOV R5, #5
		MOV R6, #6
loop 	B loop
	ENDFUNC
		END