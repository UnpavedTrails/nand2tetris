// compute 1 + 2 + . . + n and store value of the result in RAM[1]
// n = RAM[0]

// Pseudo code 
// n = R0
// i = 1
// sum = 0
// LOOP:
//	if i > n
//		goto STOP
//	else
//		sum = sum + i
// 		i = i + 1
//		goto LOOP
// STOP:
// R1 = sum
// END

//Setting variables
@R0
D=M
@n
M=D
@i
M=1
@sum
M=0

(LOOP)
@i	
D=M
@n
D=D-M
@STOP	// if i > n goto STOP
D;JGT

@sum
D=M
@i
D=D+M
@sum
M=D	// sum = sum + i
@i
M=M+1	// i = i + 1
@LOOP
0;JMP

(STOP)
@sum
D=M
@R1
M=D

(END)
@END
0;JMP
