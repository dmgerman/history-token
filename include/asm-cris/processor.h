multiline_comment|/*&n; * include/asm-cris/processor.h&n; *&n; * Copyright (C) 2000, 2001 Axis Communications AB&n; *&n; * Authors:         Bjorn Wesen        Initial version&n; *&n; */
macro_line|#ifndef __ASM_CRIS_PROCESSOR_H
DECL|macro|__ASM_CRIS_PROCESSOR_H
mdefine_line|#define __ASM_CRIS_PROCESSOR_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
multiline_comment|/*&n; * Default implementation of macro that returns current&n; * instruction pointer (&quot;program counter&quot;).&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() ({void *pc; __asm__ (&quot;move.d pc,%0&quot; : &quot;=rm&quot; (pc)); pc; })
multiline_comment|/* CRIS has no problems with write protection */
DECL|macro|wp_works_ok
mdefine_line|#define wp_works_ok 1
multiline_comment|/*&n; * User space process size. This is hardcoded into a few places,&n; * so don&squot;t change it unless you know what you are doing.&n; */
macro_line|#ifdef CONFIG_CRIS_LOW_MAP
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE       (0x50000000UL)   /* 1.25 GB */
macro_line|#else
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE       (0xB0000000UL)   /* 2.75 GB */
macro_line|#endif
multiline_comment|/* This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE      (TASK_SIZE / 3)
multiline_comment|/* THREAD_SIZE is the size of the task_struct/kernel_stack combo.&n; * normally, the stack is found by doing something like p + THREAD_SIZE&n; * in CRIS, a page is 8192 bytes, which seems like a sane size&n; */
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE       PAGE_SIZE
DECL|macro|KERNEL_STACK_SIZE
mdefine_line|#define KERNEL_STACK_SIZE PAGE_SIZE
multiline_comment|/* CRIS thread_struct. this really has nothing to do with the processor itself, since&n; * CRIS does not do any hardware task-switching, but it&squot;s here for legacy reasons.&n; * The thread_struct here is used when task-switching using _resume defined in entry.S.&n; * The offsets here are hardcoded into _resume - if you change this struct, you need to&n; * change them as well!!!&n;*/
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
DECL|member|ksp
r_int
r_int
id|ksp
suffix:semicolon
multiline_comment|/* kernel stack pointer */
DECL|member|usp
r_int
r_int
id|usp
suffix:semicolon
multiline_comment|/* user stack pointer */
DECL|member|dccr
r_int
r_int
id|dccr
suffix:semicolon
multiline_comment|/* saved flag register */
)brace
suffix:semicolon
multiline_comment|/*&n; * At user-&gt;kernel entry, the pt_regs struct is stacked on the top of the kernel-stack.&n; * This macro allows us to find those regs for a task.&n; * Notice that subsequent pt_regs stackings, like recursive interrupts occuring while&n; * we&squot;re in the kernel, won&squot;t affect this - only the first user-&gt;kernel transition&n; * registers are reached by this.&n; */
DECL|macro|user_regs
mdefine_line|#define user_regs(task) (((struct pt_regs *)((unsigned long)(task) + THREAD_SIZE)) - 1)
multiline_comment|/*&n; * Dito but for the currently running task&n; */
DECL|macro|current_regs
mdefine_line|#define current_regs() user_regs(current)
multiline_comment|/* INIT_MMAP is the kernels map of memory, between KSEG_C and KSEG_D */
macro_line|#ifdef CONFIG_CRIS_LOW_MAP
DECL|macro|INIT_MMAP
mdefine_line|#define INIT_MMAP { &amp;init_mm, KSEG_6, KSEG_7, NULL, PAGE_SHARED, &bslash;&n;&t;&t;&t;     VM_READ | VM_WRITE | VM_EXEC, 1, NULL, NULL }
macro_line|#else
DECL|macro|INIT_MMAP
mdefine_line|#define INIT_MMAP { &amp;init_mm, KSEG_C, KSEG_D, NULL, PAGE_SHARED, &bslash;&n;&t;&t;&t;     VM_READ | VM_WRITE | VM_EXEC, 1, NULL, NULL }
macro_line|#endif
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD  { &bslash;&n;   0, 0, 0x20 }  /* ccr = int enable, nothing else */
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
multiline_comment|/* give the thread a program location&n; * set user-mode (The &squot;U&squot; flag (User mode flag) is CCR/DCCR bit 8) &n; * switch user-stackpointer&n; */
DECL|macro|start_thread
mdefine_line|#define start_thread(regs, ip, usp) do { &bslash;&n;&t;set_fs(USER_DS);      &bslash;&n;&t;regs-&gt;irp = ip;       &bslash;&n;&t;regs-&gt;dccr |= 1 &lt;&lt; 8; &bslash;&n;&t;wrusp(usp);           &bslash;&n;} while(0)
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
DECL|macro|KSTK_EIP
mdefine_line|#define KSTK_EIP(tsk)   &bslash;&n;    ({                  &bslash;&n;        unsigned long eip = 0;   &bslash;&n;        unsigned long regs = (unsigned long)user_regs(tsk); &bslash;&n;        if (regs &gt; PAGE_SIZE &amp;&amp; &bslash;&n;            VALID_PAGE(virt_to_page(regs))) &bslash;&n;              eip = ((struct pt_regs *)regs)-&gt;irp; &bslash;&n;        eip; })
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk)   ((tsk) == current ? rdusp() : (tsk)-&gt;thread.usp)
DECL|macro|copy_segments
mdefine_line|#define copy_segments(tsk, mm)          do { } while (0)
DECL|macro|release_segments
mdefine_line|#define release_segments(mm)            do { } while (0)
DECL|macro|forget_segments
mdefine_line|#define forget_segments()               do { } while (0)
multiline_comment|/*&n; * Free current thread data structures etc..&n; */
DECL|function|exit_thread
r_static
r_inline
r_void
id|exit_thread
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Nothing needs to be done.  */
)brace
multiline_comment|/* Free all resources held by a thread. */
DECL|function|release_thread
r_static
r_inline
r_void
id|release_thread
c_func
(paren
r_struct
id|task_struct
op_star
id|dead_task
)paren
(brace
multiline_comment|/* Nothing needs to be done.  */
)brace
multiline_comment|/*&n; * Return saved PC of a blocked thread.&n; */
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
r_return
(paren
r_int
r_int
)paren
id|user_regs
c_func
(paren
id|t
)paren
op_member_access_from_pointer
id|irp
suffix:semicolon
)brace
DECL|macro|alloc_task_struct
mdefine_line|#define alloc_task_struct()  ((struct task_struct *) __get_free_pages(GFP_KERNEL,1))
DECL|macro|free_task_struct
mdefine_line|#define free_task_struct(p)  free_pages((unsigned long) (p), 1)
DECL|macro|get_task_struct
mdefine_line|#define get_task_struct(tsk) atomic_inc(&amp;virt_to_page(tsk)-&gt;count)
DECL|macro|init_task
mdefine_line|#define init_task       (init_task_union.task)
DECL|macro|init_stack
mdefine_line|#define init_stack      (init_task_union.stack)
macro_line|#endif /* __ASM_CRIS_PROCESSOR_H */
eof
