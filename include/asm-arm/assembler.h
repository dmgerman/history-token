multiline_comment|/*&n; * linux/asm/assembler.h&n; *&n; * This file contains arm architecture specific defines&n; * for the different processors.&n; *&n; * Do not include any C declarations in this file - it is included by&n; * assembler source.&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#error &quot;Only include this from assembly code&quot;
macro_line|#endif
macro_line|#include &lt;asm/proc/ptrace.h&gt;
macro_line|#include &lt;asm/proc/assembler.h&gt;
multiline_comment|/*&n; * Endian independent macros for shifting bytes within registers.&n; */
macro_line|#ifndef __ARMEB__
DECL|macro|pull
mdefine_line|#define pull            lsr
DECL|macro|push
mdefine_line|#define push            lsl
DECL|macro|byte
mdefine_line|#define byte(x)         (x*8)
macro_line|#else
DECL|macro|pull
mdefine_line|#define pull            lsl
DECL|macro|push
mdefine_line|#define push            lsr
DECL|macro|byte
mdefine_line|#define byte(x)         ((3-x)*8)
macro_line|#endif
eof
