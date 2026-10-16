// if R0 > 0
// 	R1 = 1
// else
// 	R1 = 0

@R0
D=M

@POSI
D;JGT

@R1
M=0
@END
0;JMP

(POSI)
@R1
M=1

(END)
@END
0;JMP
