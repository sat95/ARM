     PRESERVE8
     THUMB
     AREA     appcode, CODE, READONLY
     EXPORT __main
	 ENTRY 
__main  FUNCTION		 
		MOV r1, #0x20000000
		MOV r2, #10 ;size of the queue
		MOV r3, #0x20000000;Front pointer
		MOV r4, #0x20000000;Rear pointer
		MOV r5,#1

;fill all the positions of the queue 
loop1 STR r5,[r4]	;enqueue
	  ADD r4,#4;	increment rear pointe
	  ADD r5,#1
	  SUBGT r2,r2,#1
	  CMP r2,#0
	  BGT loop1

;deque from 1-5 position

      MOV r2, #5
loop2 LDR r6,[r3]	;dequeue 
	  ADD r3,#4		;increment front pointer
	  SUBGT r2,r2,#1
	  CMP r2,#1
	  BGT loop2

;fill 1-5 positions of the queue	  
	  MOV r2,#5
	  MOV r4,#0x20000000
loop3 STR r5,[r4]	;enqueue
	  ADD r4,#4		;increment rear pointer
	  SUBGT r2,r2,#1
	  CMP r2,#1
	  BGT loop3

;deque from 6-10 position	  
	  MOV r2,#10
loop4 LDR r6,[r3];dequeue
	  ADD r3,#4		;increment front pointer
	  SUBGT r2,r2,#1
	  CMP r2,#6
	  BGT loop4	

;remove all the elements from the queue
	  MOV r2,#10
	  MOV r3,#0x20000000

loop5 LDR r6,[r3];dequeue
	  ADD r3,#4		;increment rear pointer
	  SUBGT r2,r2,#1
	  CMP r2,#1
	  BGT loop5
	  
stop B stop ; stop program
     ENDFUNC
     END