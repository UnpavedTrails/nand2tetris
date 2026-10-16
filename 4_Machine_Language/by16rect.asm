// for (i=0; i<n; i++) {
//	draw 16 black pixels at
//	the beginning of row i
// }

// addr = SCREEN
// n = RAM[0]
// i = 0

// LOOP:
//	if i > n goto END
//	RAM[addr] = -1 (i.e. 1111111111111111)
//	// advancesd to the next row
//	addr = addr + 32
//	i = i + 1
//	goto LOOP

// END:
//	goto END

@SCREEN 	// addr = SCREEN
D=A
@addr
M=D
@R0 		// n = RAM[0]
D=M
@n
M=D
@i 		// i = 0
M=0

(LOOP)
@i 		// if i > n goto END
D=M
@n
D=D-M
@END
D;JGT

@addr
A=M
M=-1

@32
D=A
@addr
M=D+M 		// addr = addr + 32

@i
M=M+1

@LOOP
0;JMP

(END)
@END
0;JMP
