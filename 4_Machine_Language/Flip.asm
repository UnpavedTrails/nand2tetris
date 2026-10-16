// flip values of RAM[0] and RAM[1] 

// temp = R1 
// R1 = R0
// R0 = R1

@R0
D=M
@temp
M=D

@R1
D=M
@R0
M=D

@temp
D=M
@R1
M=D

(END)
@END
0;JMP
