macro_line|#ifndef __ASM_FPU_H
DECL|macro|__ASM_FPU_H
mdefine_line|#define __ASM_FPU_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * MAX floating point unit state size (FSAVE/FRESTORE)&n; */
DECL|macro|kernel_fpu_end
mdefine_line|#define kernel_fpu_end() do { asm volatile(&quot;bar&quot;:::&quot;memory&quot;); preempt_enable(); } while(0)
macro_line|#endif /* __ASM_FPU_H */
eof
