multiline_comment|/*&n; *  linux/include/asm-arm/processor.h&n; *&n; *  Copyright (C) 1995 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_ARM_PROCESSOR_H
DECL|macro|__ASM_ARM_PROCESSOR_H
mdefine_line|#define __ASM_ARM_PROCESSOR_H
multiline_comment|/*&n; * Default implementation of macro that returns current&n; * instruction pointer (&quot;program counter&quot;).&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() ({ __label__ _l; _l: &amp;&amp;_l;})
macro_line|#ifdef __KERNEL__
DECL|macro|EISA_bus
mdefine_line|#define EISA_bus 0
DECL|macro|MCA_bus
mdefine_line|#define MCA_bus 0
DECL|macro|MCA_bus__is_a_macro
mdefine_line|#define MCA_bus__is_a_macro
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/arch/memory.h&gt;
macro_line|#include &lt;asm/proc/processor.h&gt;
DECL|struct|debug_info
r_struct
id|debug_info
(brace
DECL|member|nsaved
r_int
id|nsaved
suffix:semicolon
r_struct
(brace
DECL|member|address
r_int
r_int
id|address
suffix:semicolon
DECL|member|insn
r_int
r_int
id|insn
suffix:semicolon
DECL|member|bp
)brace
id|bp
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
multiline_comment|/* fault info&t;  */
DECL|member|address
r_int
r_int
id|address
suffix:semicolon
DECL|member|trap_no
r_int
r_int
id|trap_no
suffix:semicolon
DECL|member|error_code
r_int
r_int
id|error_code
suffix:semicolon
multiline_comment|/* debugging&t;  */
DECL|member|debug
r_struct
id|debug_info
id|debug
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD  {&t;}
multiline_comment|/* Forward declaration, a strange C thing */
r_struct
id|task_struct
suffix:semicolon
multiline_comment|/* Free all resources held by a thread. */
r_extern
r_void
id|release_thread
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
multiline_comment|/* Copy and release all segment info associated with a VM */
DECL|macro|copy_segments
mdefine_line|#define copy_segments(tsk, mm)&t;&t;do { } while (0)
DECL|macro|release_segments
mdefine_line|#define release_segments(mm)&t;&t;do { } while (0)
r_int
r_int
id|get_wchan
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
suffix:semicolon
DECL|macro|cpu_relax
mdefine_line|#define cpu_relax()&t;&t;&t;do { } while (0)
multiline_comment|/*&n; * Create a new kernel thread&n; */
r_extern
r_int
id|kernel_thread
c_func
(paren
r_int
(paren
op_star
id|fn
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|arg
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __ASM_ARM_PROCESSOR_H */
eof
