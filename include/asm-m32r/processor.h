macro_line|#ifndef _ASM_M32R_PROCESSOR_H
DECL|macro|_ASM_M32R_PROCESSOR_H
mdefine_line|#define _ASM_M32R_PROCESSOR_H
multiline_comment|/*&n; * include/asm-m32r/processor.h&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994  Linus Torvalds&n; * Copyright (C) 2001  Hiroyuki Kondo, Hirokazu Takata, and Hitoshi Yamamoto&n; * Copyright (C) 2004  Hirokazu Takata &lt;takata at linux-m32r.org&gt;&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;  /* pt_regs */
multiline_comment|/*&n; * Default implementation of macro that returns current&n; * instruction pointer (&quot;program counter&quot;).&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() ({ __label__ _l; _l: &amp;&amp;_l; })
multiline_comment|/*&n; *  CPU type and hardware bug flags. Kept separately for each CPU.&n; *  Members of this structure are referenced in head.S, so think twice&n; *  before touching them. [mj]&n; */
DECL|struct|cpuinfo_m32r
r_struct
id|cpuinfo_m32r
(brace
DECL|member|pgtable_cache_sz
r_int
r_int
id|pgtable_cache_sz
suffix:semicolon
DECL|member|cpu_clock
r_int
r_int
id|cpu_clock
suffix:semicolon
DECL|member|bus_clock
r_int
r_int
id|bus_clock
suffix:semicolon
DECL|member|timer_divide
r_int
r_int
id|timer_divide
suffix:semicolon
DECL|member|loops_per_jiffy
r_int
r_int
id|loops_per_jiffy
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * capabilities of CPUs&n; */
r_extern
r_struct
id|cpuinfo_m32r
id|boot_cpu_data
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_extern
r_struct
id|cpuinfo_m32r
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
multiline_comment|/*&n; * User space process size: 2GB (default).&n; */
macro_line|#ifdef CONFIG_MMU
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE  (0x80000000UL)
macro_line|#else
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE  (0x00400000UL)
macro_line|#endif
multiline_comment|/* This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;PAGE_ALIGN(TASK_SIZE / 3)
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
DECL|struct|debug_trap
r_struct
id|debug_trap
(brace
DECL|member|nr_trap
r_int
id|nr_trap
suffix:semicolon
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
DECL|member|insn
r_int
r_int
id|insn
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
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
multiline_comment|/* Trap number  */
DECL|member|error_code
r_int
r_int
id|error_code
suffix:semicolon
multiline_comment|/* Error code of trap */
DECL|member|lr
r_int
r_int
id|lr
suffix:semicolon
multiline_comment|/* saved pc */
DECL|member|sp
r_int
r_int
id|sp
suffix:semicolon
multiline_comment|/* user stack pointer */
DECL|member|debug_trap
r_struct
id|debug_trap
id|debug_trap
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_SP
mdefine_line|#define INIT_SP&t;(sizeof(init_stack) + (unsigned long) &amp;init_stack)
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD&t;{&t;&bslash;&n;&t;.sp = INIT_SP,&t;&t;&bslash;&n;}
multiline_comment|/*&n; * Do necessary setup to start up a newly executed thread.&n; */
multiline_comment|/* User process Backup PSW */
DECL|macro|USERPS_BPSW
mdefine_line|#define USERPS_BPSW (M32R_PSW_BSM|M32R_PSW_BIE|M32R_PSW_BPM)
DECL|macro|start_thread
mdefine_line|#define start_thread(regs, new_pc, new_spu) &t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;set_fs(USER_DS); &t;&t;&t;&t;&t;&bslash;&n;&t;&t;regs-&gt;psw = (regs-&gt;psw | USERPS_BPSW) &amp; 0x0000FFFFUL;&t;&bslash;&n;&t;&t;regs-&gt;bpc = new_pc;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;regs-&gt;spu = new_spu;&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
multiline_comment|/* Forward declaration, a strange C thing */
r_struct
id|task_struct
suffix:semicolon
r_struct
id|mm_struct
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
DECL|macro|prepare_to_copy
mdefine_line|#define prepare_to_copy(tsk)&t;do { } while (0)
multiline_comment|/*&n; * create a kernel thread without removing it from tasklists&n; */
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
multiline_comment|/* Copy and release all segment info associated with a VM */
r_extern
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
id|mm
)paren
suffix:semicolon
r_extern
r_void
id|release_segments
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
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
multiline_comment|/* Copy and release all segment info associated with a VM */
DECL|macro|copy_segments
mdefine_line|#define copy_segments(p, mm)  do { } while (0)
DECL|macro|release_segments
mdefine_line|#define release_segments(mm)  do { } while (0)
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
mdefine_line|#define KSTK_EIP(tsk)  ((tsk)-&gt;thread.lr)
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk)  ((tsk)-&gt;thread.sp)
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE (2*PAGE_SIZE)
DECL|macro|cpu_relax
mdefine_line|#define cpu_relax()&t;barrier()
macro_line|#endif /* _ASM_M32R_PROCESSOR_H */
eof
