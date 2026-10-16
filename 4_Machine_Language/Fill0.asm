// Let turn the whole screen black
// addr = SCREEN
// n = 8192
// i = 0
// for (i = 0; i < n; i++) {
// 	RAM[addr} = -1
// 	addr = addr + 1
// 	i = i + 1
// }

@SCREEN
D=A
@addr
M=D

@8192
D=A
@n
M=D

@i
M=0

(LOOP)
@i
D=M
@n
D=D-M
@END
D;JGT

@addr
A=M
M=-1

@addr
M=M+1

@i
M=M+1

@LOOP
0;JMP

(END)
@END
0;JMP
