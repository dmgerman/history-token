multiline_comment|/*&n; * include/asm-alpha/processor.h&n; *&n; * Copyright (C) 1994 Linus Torvalds&n; */
macro_line|#ifndef __ASM_ALPHA_PROCESSOR_H
DECL|macro|__ASM_ALPHA_PROCESSOR_H
mdefine_line|#define __ASM_ALPHA_PROCESSOR_H
macro_line|#include &lt;linux/personality.h&gt;&t;/* for ADDR_LIMIT_32BIT */
multiline_comment|/*&n; * Returns current instruction pointer (&quot;program counter&quot;).&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() &bslash;&n;  ({ void *__pc; __asm__ (&quot;br %0,.+4&quot; : &quot;=r&quot;(__pc)); __pc; })
multiline_comment|/*&n; * We have a 42-bit user address space: 4TB user VM...&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE (0x40000000000UL)
multiline_comment|/* This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE &bslash;&n;  ((current-&gt;personality &amp; ADDR_LIMIT_32BIT) ? 0x40000000 : TASK_SIZE / 2)
multiline_comment|/*&n; * Bus types&n; */
DECL|macro|EISA_bus
mdefine_line|#define EISA_bus 1
DECL|macro|EISA_bus__is_a_macro
mdefine_line|#define EISA_bus__is_a_macro /* for versions in ksyms.c */
DECL|macro|MCA_bus
mdefine_line|#define MCA_bus 0
DECL|macro|MCA_bus__is_a_macro
mdefine_line|#define MCA_bus__is_a_macro /* for versions in ksyms.c */
r_typedef
r_struct
(brace
DECL|member|seg
r_int
r_int
id|seg
suffix:semicolon
DECL|typedef|mm_segment_t
)brace
id|mm_segment_t
suffix:semicolon
multiline_comment|/* This is dead.  Everything has been moved to thread_info.  */
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
)brace
suffix:semicolon
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD  { }
multiline_comment|/* Return saved PC of a blocked thread.  */
r_struct
id|task_struct
suffix:semicolon
r_extern
r_int
r_int
id|thread_saved_pc
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
multiline_comment|/* Do necessary setup to start up a newly executed thread.  */
r_extern
r_void
id|start_thread
c_func
(paren
r_struct
id|pt_regs
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
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
multiline_comment|/* Create a kernel thread without removing it from tasklists.  */
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
multiline_comment|/* See arch/alpha/kernel/ptrace.c for details.  */
DECL|macro|PT_REG
mdefine_line|#define PT_REG(reg) &bslash;&n;  (PAGE_SIZE*2 - sizeof(struct pt_regs) + offsetof(struct pt_regs, reg))
DECL|macro|SW_REG
mdefine_line|#define SW_REG(reg) &bslash;&n; (PAGE_SIZE*2 - sizeof(struct pt_regs) - sizeof(struct switch_stack) &bslash;&n;  + offsetof(struct switch_stack, reg))
DECL|macro|KSTK_EIP
mdefine_line|#define KSTK_EIP(tsk) &bslash;&n;  (*(unsigned long *)(PT_REG(pc) + (unsigned long) ((tsk)-&gt;thread_info)))
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk) &bslash;&n;  ((tsk) == current ? rdusp() : (tsk)-&gt;thread_info-&gt;pcb.usp)
DECL|macro|cpu_relax
mdefine_line|#define cpu_relax()&t;do { } while (0)
DECL|macro|ARCH_HAS_PREFETCH
mdefine_line|#define ARCH_HAS_PREFETCH
DECL|macro|ARCH_HAS_PREFETCHW
mdefine_line|#define ARCH_HAS_PREFETCHW
DECL|macro|ARCH_HAS_SPINLOCK_PREFETCH
mdefine_line|#define ARCH_HAS_SPINLOCK_PREFETCH
macro_line|#if __GNUC__ &gt; 3 || (__GNUC__ == 3 &amp;&amp; __GNUC_MINOR__ &gt;= 1)
DECL|function|prefetch
r_extern
r_inline
r_void
id|prefetch
c_func
(paren
r_const
r_void
op_star
id|ptr
)paren
(brace
id|__builtin_prefetch
c_func
(paren
id|ptr
comma
l_int|0
comma
l_int|3
)paren
suffix:semicolon
)brace
DECL|function|prefetchw
r_extern
r_inline
r_void
id|prefetchw
c_func
(paren
r_const
r_void
op_star
id|ptr
)paren
(brace
id|__builtin_prefetch
c_func
(paren
id|ptr
comma
l_int|1
comma
l_int|3
)paren
suffix:semicolon
)brace
DECL|function|spin_lock_prefetch
r_extern
r_inline
r_void
id|spin_lock_prefetch
c_func
(paren
r_const
r_void
op_star
id|ptr
)paren
(brace
id|__builtin_prefetch
c_func
(paren
id|ptr
comma
l_int|1
comma
l_int|3
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|function|prefetch
r_extern
r_inline
r_void
id|prefetch
c_func
(paren
r_const
r_void
op_star
id|ptr
)paren
(brace
id|__asm__
(paren
l_string|&quot;ldl $31,%0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|ptr
)paren
)paren
suffix:semicolon
)brace
DECL|function|prefetchw
r_extern
r_inline
r_void
id|prefetchw
c_func
(paren
r_const
r_void
op_star
id|ptr
)paren
(brace
id|__asm__
(paren
l_string|&quot;ldq $31,%0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|ptr
)paren
)paren
suffix:semicolon
)brace
DECL|function|spin_lock_prefetch
r_extern
r_inline
r_void
id|spin_lock_prefetch
c_func
(paren
r_const
r_void
op_star
id|ptr
)paren
(brace
id|__asm__
(paren
l_string|&quot;ldq $31,%0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|ptr
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* GCC 3.1 */
macro_line|#endif /* __ASM_ALPHA_PROCESSOR_H */
eof
