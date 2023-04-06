	.global hash
	.p2align 2
	.type hash,%function
		
		
	.global factorial
	.p2align 2
	.type factorial,%function
		
	 
 
 
hash:
	 .fnstart

	 
	 MOV 		 R5, 0x00 // int hashResult = 0
	 MOV 		 R6, 0x00 // int i = 0
	 
loop:
	 LDRB R7, [R0, R6] // R7 = s[i]
	 CMP 	     R7, #0x00   // compare s[i] with '\0'
	 BEQ		 endOfWhile  // if s[i] == '\0' go to endOfWhile
	 CMP		 R7, #0x61   // compare s[i] with 97
	 BLT		 elseIfLabel // go to elseLabel if s[i] < 97
	 CMP		 R7, #0x7A   // compare s[i] with 122
	 BGT		 label   	 // if s[i] > 122 go to i++
	 
	 // if the code reach here we are inside if(s[i] >= 97 && s[i] <= 122)
	 
	 SUB 	     R8, R7, #0x61 // s[i] - 97
	 LDRB 	     R9, [R1, R8]  // t[s[i] - 97]
	 ADD 	     R5, R5, R9    // hashResult += t[s[i] - 97]
	 b	         label         // go to i++
	 
elseIfLabel:
	 CMP         R7, #0x30 // compare R7 to 48
	 BLT	     label 	   // if s[i] < 48 go to i++
	 CMP         R7, #0x39 // compare R7 to 57
	 BGT         label     // if s[i] > 57 go to i++
	 SUB	     R10, R7, #0x30  // s[i] - 48;
	 SUB         R5, R5, R10   // hashResult -= s[i] - 48;
label:   
	 ADD 		 R6, R6, #0x01 // i = i + 1
	 b 			 loop  		   // go to loop 
endOfWhile:
	 MOV         R0, R5
	 bx 		 lr
	 
	 
	 .fnend
	  
 
 
 
 
factorial:
	 .fnstart
	 MOV 	     R1, #0 // s[i] = 0
	 MOV		 R2, #0 // sum = 0
	 MOV 	     R3, #0 // sd = 0
	 MOV		 R4, #0 // i = 0
	 MOV 	     R5, #1 // factorial = 1
	 
loop_f:

	 LDRB       R1,[R0,R4]       // Load to R1 the value on the address R0+R4 // 
	 CMP        R1, #0
	 BEQ	    factorial_calculation
	 SUB	    R1, #48      
	 ADD	    R2, R2, R1   	// sum += s[i] - 48 ; 
	 CMP	    R2, #10
	 BLT		label_f
	 SUB 	    R3, R2, #10     // 	sd = sum - 10;
	 ADD	    R2, R3, #1 		// sum = 1 + sd;  // calculate the sum
	 
label_f:
	 ADD        R4, R4, #1
	 B		    loop_f
	 
factorial_calculation:
	 CMP		R2, #0     // compare sum with 0
	 BGE		label_greater_or_equal_than_zero
	 // if(sum < 0) // 
	 MOV        R5, #0
	 B			return_label
	 
label_greater_or_equal_than_zero:
	 CMP		R2, #0     // compare sum with 0
	 BNE		loop_is_greater_than_zero
	 // if(sum = 0) //
	 MOV	    R5, #1
	 B			return_label
	
loop_is_greater_than_zero: 
	 CMP		R2, #1
	 BEQ	    return_label
	 MUL        R5, R5, R2
	 SUB 		R2, R2, #1
	 B			loop_is_greater_than_zero
	 
return_label:
	 MOV		R0, R5
	 BX 		LR


     .fnend

