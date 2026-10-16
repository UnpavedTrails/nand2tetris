// Program: To turn the whole screen Black till the use presses key and revert back screen to white when key is released

(RESET)		// Resetting the value of ptr-addr
@SCREEN
D=A
@addr
M=D

@8192		// Total pixel memory map registers, each of 16bit
D=A
@n		// stored inside varialbe n
M=D

@i		// counter i
M=1

(LOOP)		// continous loop for reading KBD value then formatting SCREEN

@KBD
D=M
@BLACK_LOOP
D;JNE

@KBD
D=M
@WHITE_LOOP
D;JEQ

@LOOP
0;JMP

(BLACK_LOOP)	// Loop part to turn the SCREEN black
@i		// if i > n, reset the initial variables (addr to SCREEN, i = 1, n = 8192)
D=M
@n
D=D-M
@RESET
D;JGT

@addr		// else turn all the pixels black
A=M
M=-1

@addr		// addr = addr + 1
M=M+1

@i		// i = i + 1
M=M+1

@BLACK_LOOP
0;JMP

(WHITE_LOOP)	// Loop part to turn the SCREEN white
@i		// if i > n, reset the initial variables (addr to SCREEN, i = 1, n = 8192)
D=M
@n
D=D-M
@RESET
D;JGT

@addr		// else turn all the pixels white
A=M
M=0

@addr
M=M+1

@i
M=M+1

@WHITE_LOOP
0;JMP

(END)
@END
0;JMP
