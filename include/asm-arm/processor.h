multiline_comment|/*&n; *  linux/include/asm-arm/processor.h&n; *&n; *  Copyright (C) 1995-1999 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_ARM_PROCESSOR_H
DECL|macro|__ASM_ARM_PROCESSOR_H
mdefine_line|#define __ASM_ARM_PROCESSOR_H
multiline_comment|/*&n; * Default implementation of macro that returns current&n; * instruction pointer (&quot;program counter&quot;).&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() ({ __label__ _l; _l: &amp;&amp;_l;})
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/procinfo.h&gt;
macro_line|#include &lt;asm/types.h&gt;
DECL|macro|KERNEL_STACK_SIZE
mdefine_line|#define KERNEL_STACK_SIZE&t;PAGE_SIZE
DECL|union|debug_insn
r_union
id|debug_insn
(brace
DECL|member|arm
id|u32
id|arm
suffix:semicolon
DECL|member|thumb
id|u16
id|thumb
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|debug_entry
r_struct
id|debug_entry
(brace
DECL|member|address
id|u32
id|address
suffix:semicolon
DECL|member|insn
r_union
id|debug_insn
id|insn
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|debug_info
r_struct
id|debug_info
(brace
DECL|member|nsaved
r_int
id|nsaved
suffix:semicolon
DECL|member|bp
r_struct
id|debug_entry
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
DECL|macro|start_thread
mdefine_line|#define start_thread(regs,pc,sp)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long *stack = (unsigned long *)sp;&t;&t;&t;&bslash;&n;&t;set_fs(USER_DS);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;memzero(regs-&gt;uregs, sizeof(regs-&gt;uregs));&t;&t;&t;&bslash;&n;&t;if (current-&gt;personality &amp; ADDR_LIMIT_32BIT)&t;&t;&t;&bslash;&n;&t;&t;regs-&gt;ARM_cpsr = USR_MODE;&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;regs-&gt;ARM_cpsr = USR26_MODE;&t;&t;&t;&t;&bslash;&n;&t;if (elf_hwcap &amp; HWCAP_THUMB &amp;&amp; pc &amp; 1)&t;&t;&t;&t;&bslash;&n;&t;&t;regs-&gt;ARM_cpsr |= PSR_T_BIT;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;ARM_pc = pc &amp; ~1;&t;&t;/* pc */&t;&t;&t;&bslash;&n;&t;regs-&gt;ARM_sp = sp;&t;&t;/* sp */&t;&t;&t;&bslash;&n;&t;regs-&gt;ARM_r2 = stack[2];&t;/* r2 (envp) */&t;&t;&t;&bslash;&n;&t;regs-&gt;ARM_r1 = stack[1];&t;/* r1 (argv) */&t;&t;&t;&bslash;&n;&t;regs-&gt;ARM_r0 = stack[0];&t;/* r0 (argc) */&t;&t;&t;&bslash;&n;})
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
multiline_comment|/* Prepare to copy thread state - unlazy all lazy status */
DECL|macro|prepare_to_copy
mdefine_line|#define prepare_to_copy(tsk)&t;do { } while (0)
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
mdefine_line|#define cpu_relax()&t;&t;&t;barrier()
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
DECL|macro|KSTK_EIP
mdefine_line|#define KSTK_EIP(tsk)&t;(((unsigned long *)(4096+(unsigned long)(tsk)-&gt;thread_info))[1019])
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk)&t;(((unsigned long *)(4096+(unsigned long)(tsk)-&gt;thread_info))[1017])
multiline_comment|/*&n; * Prefetching support - only ARMv5.&n; */
macro_line|#if __LINUX_ARM_ARCH__ &gt;= 5
DECL|macro|ARCH_HAS_PREFETCH
mdefine_line|#define ARCH_HAS_PREFETCH
DECL|macro|prefetch
mdefine_line|#define prefetch(ptr)&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&bslash;&n;&t;&t;&quot;pld&bslash;t%0&quot;&t;&t;&t;&bslash;&n;&t;&t;:&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;o&quot; (*(char *)(ptr))&t;&t;&bslash;&n;&t;&t;: &quot;cc&quot;);&t;&t;&t;&bslash;&n;&t;})
DECL|macro|ARCH_HAS_PREFETCHW
mdefine_line|#define ARCH_HAS_PREFETCHW
DECL|macro|prefetchw
mdefine_line|#define prefetchw(ptr)&t;prefetch(ptr)
DECL|macro|ARCH_HAS_SPINLOCK_PREFETCH
mdefine_line|#define ARCH_HAS_SPINLOCK_PREFETCH
DECL|macro|spin_lock_prefetch
mdefine_line|#define spin_lock_prefetch(x) do { } while (0)
macro_line|#endif
macro_line|#endif
macro_line|#endif /* __ASM_ARM_PROCESSOR_H */
eof
