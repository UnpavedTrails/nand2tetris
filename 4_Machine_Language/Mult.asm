// Mult.asm: R2 = R0 * R1 (R0, R1 >= 0), R0 and R1 left unchanged
//
// pseudo-code:
// R2 = 0
// i = 0
// while (i < R1) { R2 = R2 + R0; i = i + 1 }

@R2
M=0          // result accumulates directly in R2
@i
M=0          // i counts up from 0

(LOOP)
@i
D=M
@R1
D=D-M        // D = i - R1
@END
D;JGE        // if i >= R1, we're done

@R0
D=M
@R2
M=D+M        // R2 = R2 + R0
@i
M=M+1        // i++
@LOOP
0;JMP

(END)
@END
0;JMP
