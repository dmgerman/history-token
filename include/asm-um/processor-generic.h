multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __UM_PROCESSOR_GENERIC_H
DECL|macro|__UM_PROCESSOR_GENERIC_H
mdefine_line|#define __UM_PROCESSOR_GENERIC_H
r_struct
id|pt_regs
suffix:semicolon
r_struct
id|task_struct
suffix:semicolon
macro_line|#include &quot;linux/config.h&quot;
macro_line|#include &quot;linux/signal.h&quot;
macro_line|#include &quot;asm/segment.h&quot;
macro_line|#include &quot;asm/ptrace.h&quot;
macro_line|#include &quot;asm/siginfo.h&quot;
r_struct
id|mm_struct
suffix:semicolon
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() ((void *) 0)
DECL|macro|cpu_relax
mdefine_line|#define cpu_relax()&t;do ; while (0)
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
DECL|member|extern_pid
r_int
id|extern_pid
suffix:semicolon
DECL|member|tracing
r_int
id|tracing
suffix:semicolon
DECL|member|forking
r_int
id|forking
suffix:semicolon
DECL|member|kernel_stack
r_int
r_int
id|kernel_stack
suffix:semicolon
DECL|member|nsyscalls
r_int
id|nsyscalls
suffix:semicolon
DECL|member|regs
r_struct
id|pt_regs
id|regs
suffix:semicolon
DECL|member|cr2
r_int
r_int
id|cr2
suffix:semicolon
DECL|member|err
r_int
id|err
suffix:semicolon
DECL|member|fault_addr
r_void
op_star
id|fault_addr
suffix:semicolon
DECL|member|fault_catcher
r_void
op_star
id|fault_catcher
suffix:semicolon
DECL|member|vm_seq
r_int
id|vm_seq
suffix:semicolon
DECL|member|prev_sched
r_struct
id|task_struct
op_star
id|prev_sched
suffix:semicolon
DECL|member|temp_stack
r_int
r_int
id|temp_stack
suffix:semicolon
DECL|member|switch_pipe
r_int
id|switch_pipe
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|jmp
r_void
op_star
id|jmp
suffix:semicolon
DECL|member|arch
r_struct
id|arch_thread
id|arch
suffix:semicolon
DECL|member|singlestep_syscall
r_int
id|singlestep_syscall
suffix:semicolon
r_struct
(brace
DECL|member|op
r_int
id|op
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|pid
r_int
id|pid
suffix:semicolon
DECL|member|fork
DECL|member|exec
)brace
id|fork
comma
id|exec
suffix:semicolon
r_struct
(brace
DECL|member|proc
r_int
(paren
op_star
id|proc
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|member|arg
r_void
op_star
id|arg
suffix:semicolon
DECL|member|thread
)brace
id|thread
suffix:semicolon
r_struct
(brace
DECL|member|proc
r_void
(paren
op_star
id|proc
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|member|arg
r_void
op_star
id|arg
suffix:semicolon
DECL|member|cb
)brace
id|cb
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|request
)brace
id|request
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD &bslash;&n;{ &bslash;&n;&t;extern_pid:&t;&t;-1, &bslash;&n;&t;tracing:&t;&t;0, &bslash;&n;&t;forking:&t;&t;0, &bslash;&n;&t;kernel_stack:&t;&t;0, &bslash;&n;&t;nsyscalls:&t;&t;0, &bslash;&n;        regs:&t;&t;   &t;EMPTY_REGS, &bslash;&n;&t;cr2:&t;&t;&t;0, &bslash;&n;&t;err:&t;&t;&t;0, &bslash;&n;&t;fault_addr:&t;&t;NULL, &bslash;&n;&t;vm_seq:&t;&t;&t;0, &bslash;&n;&t;prev_sched:&t;&t;NULL, &bslash;&n;&t;temp_stack:&t;&t;0, &bslash;&n;&t;switch_pipe:&t;&t;{ -1, -1 }, &bslash;&n;&t;jmp:&t;&t;&t;NULL, &bslash;&n;&t;arch:&t;&t;&t;INIT_ARCH_THREAD, &bslash;&n;&t;singlestep_syscall:&t;0, &bslash;&n;&t;request:&t;&t;{ 0 } &bslash;&n;}
DECL|macro|INIT_THREAD_SIZE
mdefine_line|#define INIT_THREAD_SIZE (4 * PAGE_SIZE)
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
r_extern
r_struct
id|task_struct
op_star
id|alloc_task_struct
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|free_task_struct
c_func
(paren
r_struct
id|task_struct
op_star
id|task
)paren
suffix:semicolon
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
r_extern
r_void
id|dump_thread
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|user
op_star
id|u
)paren
suffix:semicolon
DECL|function|release_segments
r_static
r_inline
r_void
id|release_segments
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
)brace
DECL|function|copy_segments
r_static
r_inline
r_void
id|copy_segments
c_func
(paren
r_struct
id|task_struct
op_star
id|p
comma
r_struct
id|mm_struct
op_star
id|new_mm
)paren
(brace
)brace
DECL|macro|forget_segments
mdefine_line|#define forget_segments() do ; while(0)
r_extern
r_int
r_int
id|thread_saved_pc
c_func
(paren
r_struct
id|task_struct
op_star
id|t
)paren
suffix:semicolon
DECL|macro|init_stack
mdefine_line|#define init_stack&t;(init_thread_union.stack)
multiline_comment|/*&n; * User space process size: 3GB (default).&n; */
r_extern
r_int
r_int
id|task_size
suffix:semicolon
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(task_size)
multiline_comment|/* This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;(0x40000000)
r_extern
r_void
id|start_thread
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|entry
comma
r_int
r_int
id|stack
)paren
suffix:semicolon
DECL|struct|cpuinfo_um
r_struct
id|cpuinfo_um
(brace
DECL|member|loops_per_jiffy
r_int
r_int
id|loops_per_jiffy
suffix:semicolon
DECL|member|ipi_pipe
r_int
id|ipi_pipe
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|cpuinfo_um
id|boot_cpu_data
suffix:semicolon
DECL|macro|my_cpu_data
mdefine_line|#define my_cpu_data&t;&t;cpu_data[smp_processor_id()]
macro_line|#ifdef CONFIG_SMP
r_extern
r_struct
id|cpuinfo_um
id|cpu_data
(braket
)braket
suffix:semicolon
DECL|macro|current_cpu_data
mdefine_line|#define current_cpu_data cpu_data[smp_processor_id()]
macro_line|#else
DECL|macro|cpu_data
mdefine_line|#define cpu_data (&amp;boot_cpu_data)
DECL|macro|current_cpu_data
mdefine_line|#define current_cpu_data boot_cpu_data
macro_line|#endif
DECL|macro|KSTK_EIP
mdefine_line|#define KSTK_EIP(tsk) (PT_REGS_IP(&amp;tsk-&gt;thread.regs))
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk) (PT_REGS_SP(&amp;tsk-&gt;thread.regs))
DECL|macro|get_wchan
mdefine_line|#define get_wchan(p) (0)
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof