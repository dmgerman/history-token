multiline_comment|/*&n; * include/asm-alpha/processor.h&n; *&n; * Copyright (C) 1994 Linus Torvalds&n; */
macro_line|#ifndef __ASM_ALPHA_PROCESSOR_H
DECL|macro|__ASM_ALPHA_PROCESSOR_H
mdefine_line|#define __ASM_ALPHA_PROCESSOR_H
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
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
multiline_comment|/* the fields below are used by PALcode and must match struct pcb: */
DECL|member|ksp
r_int
r_int
id|ksp
suffix:semicolon
DECL|member|usp
r_int
r_int
id|usp
suffix:semicolon
DECL|member|ptbr
r_int
r_int
id|ptbr
suffix:semicolon
DECL|member|pcc
r_int
r_int
id|pcc
suffix:semicolon
DECL|member|asn
r_int
r_int
id|asn
suffix:semicolon
DECL|member|unique
r_int
r_int
id|unique
suffix:semicolon
multiline_comment|/*&n;&t; * bit  0: floating point enable&n;&t; * bit 62: performance monitor enable&n;&t; */
DECL|member|pal_flags
r_int
r_int
id|pal_flags
suffix:semicolon
DECL|member|res1
DECL|member|res2
r_int
r_int
id|res1
comma
id|res2
suffix:semicolon
multiline_comment|/*&n;&t; * The fields below are Linux-specific:&n;&t; *&n;&t; * bit 1..5: IEEE_TRAP_ENABLE bits (see fpu.h)&n;&t; * bit 6..8: UAC bits (see sysinfo.h)&n;&t; * bit 17..21: IEEE_STATUS_MASK bits (see fpu.h)&n;&t; * bit 63: die_if_kernel recursion lock&n;&t; */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Perform syscall argument validation (get/set_fs). */
DECL|member|fs
id|mm_segment_t
id|fs
suffix:semicolon
multiline_comment|/* Breakpoint handling for ptrace.  */
DECL|member|bpt_addr
r_int
r_int
id|bpt_addr
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|bpt_insn
r_int
r_int
id|bpt_insn
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|bpt_nsaved
r_int
id|bpt_nsaved
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_MMAP
mdefine_line|#define INIT_MMAP { &amp;init_mm, PAGE_OFFSET,  PAGE_OFFSET+0x10000000, &bslash;&n;&t;NULL, PAGE_SHARED, VM_READ | VM_WRITE | VM_EXEC, 1, NULL, NULL }
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD  { &bslash;&n;&t;0, 0, 0, &bslash;&n;&t;0, 0, 0, &bslash;&n;&t;0, 0, 0, &bslash;&n;&t;0, &bslash;&n;&t;KERNEL_DS &bslash;&n;}
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE (2*PAGE_SIZE)
macro_line|#include &lt;asm/ptrace.h&gt;
multiline_comment|/*&n; * Return saved PC of a blocked thread.  This assumes the frame&n; * pointer is the 6th saved long on the kernel stack and that the&n; * saved return address is the first long in the frame.  This all&n; * holds provided the thread blocked through a call to schedule() ($15&n; * is the frame pointer in schedule() and $15 is saved at offset 48 by&n; * entry.S:do_switch_stack).&n; *&n; * Under heavy swap load I&squot;ve seen this lose in an ugly way.  So do&n; * some extra sanity checking on the ranges we expect these pointers&n; * to be in so that we can fail gracefully.  This is just for ps after&n; * all.  -- r~&n; */
DECL|function|thread_saved_pc
r_extern
r_inline
r_int
r_int
id|thread_saved_pc
c_func
(paren
r_struct
id|thread_struct
op_star
id|t
)paren
(brace
r_int
r_int
id|fp
comma
id|sp
op_assign
id|t-&gt;ksp
comma
id|base
op_assign
(paren
r_int
r_int
)paren
id|t
suffix:semicolon
r_if
c_cond
(paren
id|sp
OG
id|base
op_logical_and
id|sp
op_plus
l_int|6
op_star
l_int|8
OL
id|base
op_plus
l_int|16
op_star
l_int|1024
)paren
(brace
id|fp
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|sp
)paren
(braket
l_int|6
)braket
suffix:semicolon
r_if
c_cond
(paren
id|fp
OG
id|sp
op_logical_and
id|fp
OL
id|base
op_plus
l_int|16
op_star
l_int|1024
)paren
r_return
op_star
(paren
r_int
r_int
op_star
)paren
id|fp
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
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
mdefine_line|#define PT_REG(reg)&t;(PAGE_SIZE*2 - sizeof(struct pt_regs)&t;&t;&bslash;&n;&t;&t;&t; + (long)&amp;((struct pt_regs *)0)-&gt;reg)
DECL|macro|SW_REG
mdefine_line|#define SW_REG(reg)&t;(PAGE_SIZE*2 - sizeof(struct pt_regs)&t;&t;&bslash;&n;&t;&t;&t; - sizeof(struct switch_stack)&t;&t;&t;&bslash;&n;&t;&t;&t; + (long)&amp;((struct switch_stack *)0)-&gt;reg)
DECL|macro|KSTK_EIP
mdefine_line|#define KSTK_EIP(tsk) &bslash;&n;    (*(unsigned long *)(PT_REG(pc) + (unsigned long)(tsk)))
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk)&t;((tsk) == current ? rdusp() : (tsk)-&gt;thread.usp)
multiline_comment|/* NOTE: The task struct and the stack go together!  */
DECL|macro|alloc_task_struct
mdefine_line|#define alloc_task_struct() &bslash;&n;        ((struct task_struct *) __get_free_pages(GFP_KERNEL,1))
DECL|macro|free_task_struct
mdefine_line|#define free_task_struct(p)     free_pages((unsigned long)(p),1)
DECL|macro|get_task_struct
mdefine_line|#define get_task_struct(tsk)      atomic_inc(&amp;virt_to_page(tsk)-&gt;count)
DECL|macro|init_task
mdefine_line|#define init_task&t;(init_task_union.task)
DECL|macro|init_stack
mdefine_line|#define init_stack&t;(init_task_union.stack)
macro_line|#endif /* __ASM_ALPHA_PROCESSOR_H */
eof
