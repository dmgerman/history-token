macro_line|#ifndef __ASM_SH64_PROCESSOR_H
DECL|macro|__ASM_SH64_PROCESSOR_H
mdefine_line|#define __ASM_SH64_PROCESSOR_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * include/asm-sh64/processor.h&n; *&n; * Copyright (C) 2000, 2001  Paolo Alberelli&n; * Copyright (C) 2003  Paul Mundt&n; * Copyright (C) 2004  Richard Curnow&n; *&n; */
macro_line|#include &lt;asm/page.h&gt;
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;asm/registers.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
multiline_comment|/*&n; * Default implementation of macro that returns current&n; * instruction pointer (&quot;program counter&quot;).&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() ({ &bslash;&n;void *pc; &bslash;&n;unsigned long long __dummy = 0; &bslash;&n;__asm__(&quot;gettr&t;tr0, %1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pta&t;4, tr0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;gettr&t;tr0, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;ptabs&t;%1, tr0&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;:&quot;=r&quot; (pc), &quot;=r&quot; (__dummy) &bslash;&n;&t;: &quot;1&quot; (__dummy)); &bslash;&n;pc; })
multiline_comment|/*&n; *  CPU type and hardware bug flags. Kept separately for each CPU.&n; */
DECL|enum|cpu_type
r_enum
id|cpu_type
(brace
DECL|enumerator|CPU_SH5_101
id|CPU_SH5_101
comma
DECL|enumerator|CPU_SH5_103
id|CPU_SH5_103
comma
DECL|enumerator|CPU_SH_NONE
id|CPU_SH_NONE
)brace
suffix:semicolon
multiline_comment|/*&n; * TLB information structure&n; *&n; * Defined for both I and D tlb, per-processor.&n; */
DECL|struct|tlb_info
r_struct
id|tlb_info
(brace
DECL|member|next
r_int
r_int
r_int
id|next
suffix:semicolon
DECL|member|first
r_int
r_int
r_int
id|first
suffix:semicolon
DECL|member|last
r_int
r_int
r_int
id|last
suffix:semicolon
DECL|member|entries
r_int
r_int
id|entries
suffix:semicolon
DECL|member|step
r_int
r_int
id|step
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sh_cpuinfo
r_struct
id|sh_cpuinfo
(brace
DECL|member|type
r_enum
id|cpu_type
id|type
suffix:semicolon
DECL|member|loops_per_jiffy
r_int
r_int
id|loops_per_jiffy
suffix:semicolon
DECL|member|hard_math
r_char
id|hard_math
suffix:semicolon
DECL|member|pgd_quick
r_int
r_int
op_star
id|pgd_quick
suffix:semicolon
DECL|member|pmd_quick
r_int
r_int
op_star
id|pmd_quick
suffix:semicolon
DECL|member|pte_quick
r_int
r_int
op_star
id|pte_quick
suffix:semicolon
DECL|member|pgtable_cache_sz
r_int
r_int
id|pgtable_cache_sz
suffix:semicolon
DECL|member|cpu_clock
DECL|member|master_clock
DECL|member|bus_clock
DECL|member|module_clock
r_int
r_int
id|cpu_clock
comma
id|master_clock
comma
id|bus_clock
comma
id|module_clock
suffix:semicolon
multiline_comment|/* Cache info */
DECL|member|icache
r_struct
id|cache_info
id|icache
suffix:semicolon
DECL|member|dcache
r_struct
id|cache_info
id|dcache
suffix:semicolon
multiline_comment|/* TLB info */
DECL|member|itlb
r_struct
id|tlb_info
id|itlb
suffix:semicolon
DECL|member|dtlb
r_struct
id|tlb_info
id|dtlb
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|sh_cpuinfo
id|boot_cpu_data
suffix:semicolon
DECL|macro|cpu_data
mdefine_line|#define cpu_data (&amp;boot_cpu_data)
DECL|macro|current_cpu_data
mdefine_line|#define current_cpu_data boot_cpu_data
macro_line|#endif
multiline_comment|/*&n; * User space process size: 2GB - 4k.&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;0x7ffff000UL
multiline_comment|/* This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;(TASK_SIZE / 3)
multiline_comment|/*&n; * Bit of SR register&n; *&n; * FD-bit:&n; *     When it&squot;s set, it means the processor doesn&squot;t have right to use FPU,&n; *     and it results exception when the floating operation is executed.&n; *&n; * IMASK-bit:&n; *     Interrupt level mask&n; *&n; * STEP-bit:&n; *     Single step bit&n; *&n; */
DECL|macro|SR_FD
mdefine_line|#define SR_FD    0x00008000
macro_line|#if defined(CONFIG_SH64_SR_WATCH)
DECL|macro|SR_MMU
mdefine_line|#define SR_MMU   0x84000000
macro_line|#else
DECL|macro|SR_MMU
mdefine_line|#define SR_MMU   0x80000000
macro_line|#endif
DECL|macro|SR_IMASK
mdefine_line|#define SR_IMASK 0x000000f0
DECL|macro|SR_SSTEP
mdefine_line|#define SR_SSTEP 0x08000000
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * FPU structure and data : require 8-byte alignment as we need to access it&n;   with fld.p, fst.p&n; */
DECL|struct|sh_fpu_hard_struct
r_struct
id|sh_fpu_hard_struct
(brace
DECL|member|fp_regs
r_int
r_int
id|fp_regs
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|fpscr
r_int
r_int
id|fpscr
suffix:semicolon
multiline_comment|/* long status; * software status information */
)brace
suffix:semicolon
macro_line|#if 0
multiline_comment|/* Dummy fpu emulator  */
r_struct
id|sh_fpu_soft_struct
(brace
r_int
r_int
r_int
id|fp_regs
(braket
l_int|32
)braket
suffix:semicolon
r_int
r_int
id|fpscr
suffix:semicolon
r_int
r_char
id|lookahead
suffix:semicolon
r_int
r_int
id|entry_pc
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
DECL|union|sh_fpu_union
r_union
id|sh_fpu_union
(brace
DECL|member|hard
r_struct
id|sh_fpu_hard_struct
id|hard
suffix:semicolon
multiline_comment|/* &squot;hard&squot; itself only produces 32 bit alignment, yet we need&n;&t;   to access it using 64 bit load/store as well. */
DECL|member|alignment_dummy
r_int
r_int
r_int
id|alignment_dummy
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
DECL|member|sp
r_int
r_int
id|sp
suffix:semicolon
DECL|member|pc
r_int
r_int
id|pc
suffix:semicolon
multiline_comment|/* This stores the address of the pt_regs built during a context&n;&t;   switch, or of the register save area built for a kernel mode&n;&t;   exception.  It is used for backtracing the stack of a sleeping task&n;&t;   or one that traps in kernel mode. */
DECL|member|kregs
r_struct
id|pt_regs
op_star
id|kregs
suffix:semicolon
multiline_comment|/* This stores the address of the pt_regs constructed on entry from&n;&t;   user mode.  It is a fixed value over the lifetime of a process, or&n;&t;   NULL for a kernel thread. */
DECL|member|uregs
r_struct
id|pt_regs
op_star
id|uregs
suffix:semicolon
DECL|member|trap_no
DECL|member|error_code
r_int
r_int
id|trap_no
comma
id|error_code
suffix:semicolon
DECL|member|address
r_int
r_int
id|address
suffix:semicolon
multiline_comment|/* Hardware debugging registers may come here */
multiline_comment|/* floating point info */
DECL|member|fpu
r_union
id|sh_fpu_union
id|fpu
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_MMAP
mdefine_line|#define INIT_MMAP &bslash;&n;{ &amp;init_mm, 0, 0, NULL, PAGE_SHARED, VM_READ | VM_WRITE | VM_EXEC, 1, NULL, NULL }
r_extern
r_struct
id|pt_regs
id|fake_swapper_regs
suffix:semicolon
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD  {&t;&t;&t;&t;&bslash;&n;&t;.sp&t;&t;= sizeof(init_stack) +&t;&bslash;&n;&t;&t;&t;  (long) &amp;init_stack,&t;&bslash;&n;&t;.pc&t;&t;= 0,&t;&t;&t;&bslash;&n;        .kregs&t;&t;= &amp;fake_swapper_regs,&t;&bslash;&n;&t;.uregs&t;        = NULL,&t;&t;&t;&bslash;&n;&t;.trap_no&t;= 0,&t;&t;&t;&bslash;&n;&t;.error_code&t;= 0,&t;&t;&t;&bslash;&n;&t;.address&t;= 0,&t;&t;&t;&bslash;&n;&t;.fpu&t;&t;= { { { 0, } }, }&t;&bslash;&n;}
multiline_comment|/*&n; * Do necessary setup to start up a newly executed thread.&n; */
DECL|macro|SR_USER
mdefine_line|#define SR_USER (SR_MMU | SR_FD)
DECL|macro|start_thread
mdefine_line|#define start_thread(regs, new_pc, new_sp) &t; &t;&t;&bslash;&n;&t;set_fs(USER_DS);&t;&t;&t; &t;&t;&bslash;&n;&t;regs-&gt;sr = SR_USER;&t;/* User mode. */ &t;&t;&bslash;&n;&t;regs-&gt;pc = new_pc - 4;&t;/* Compensate syscall exit */&t;&bslash;&n;&t;regs-&gt;pc |= 1;&t;&t;/* Set SHmedia ! */&t;&t;&bslash;&n;&t;regs-&gt;regs[18] = 0;   &t;&t; &t; &t;&t;&bslash;&n;&t;regs-&gt;regs[15] = new_sp
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
DECL|macro|copy_segments
mdefine_line|#define copy_segments(p, mm)&t;do { } while (0)
DECL|macro|release_segments
mdefine_line|#define release_segments(mm)&t;do { } while (0)
DECL|macro|forget_segments
mdefine_line|#define forget_segments()&t;do { } while (0)
DECL|macro|prepare_to_copy
mdefine_line|#define prepare_to_copy(tsk)&t;do { } while (0)
multiline_comment|/*&n; * FPU lazy state save handling.&n; */
DECL|function|release_fpu
r_extern
id|__inline__
r_void
id|release_fpu
c_func
(paren
r_void
)paren
(brace
r_int
r_int
r_int
id|__dummy
suffix:semicolon
multiline_comment|/* Set FD flag in SR */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;getcon&t;&quot;
id|__SR
l_string|&quot;, %0&bslash;n&bslash;t&quot;
l_string|&quot;or&t;%0, %1, %0&bslash;n&bslash;t&quot;
l_string|&quot;putcon&t;%0, &quot;
id|__SR
l_string|&quot;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|__dummy
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|SR_FD
)paren
)paren
suffix:semicolon
)brace
DECL|function|grab_fpu
r_extern
id|__inline__
r_void
id|grab_fpu
c_func
(paren
r_void
)paren
(brace
r_int
r_int
r_int
id|__dummy
suffix:semicolon
multiline_comment|/* Clear out FD flag in SR */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;getcon&t;&quot;
id|__SR
l_string|&quot;, %0&bslash;n&bslash;t&quot;
l_string|&quot;and&t;%0, %1, %0&bslash;n&bslash;t&quot;
l_string|&quot;putcon&t;%0, &quot;
id|__SR
l_string|&quot;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|__dummy
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_complement
id|SR_FD
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Round to nearest, no exceptions on inexact, overflow, underflow,&n;   zero-divide, invalid.  Configure option for whether to flush denorms to&n;   zero, or except if a denorm is encountered.  */
macro_line|#if defined(CONFIG_SH64_FPU_DENORM_FLUSH)
DECL|macro|FPSCR_INIT
mdefine_line|#define FPSCR_INIT  0x00040000
macro_line|#else
DECL|macro|FPSCR_INIT
mdefine_line|#define FPSCR_INIT  0x00000000
macro_line|#endif
multiline_comment|/* Save the current FP regs */
r_void
id|fpsave
c_func
(paren
r_struct
id|sh_fpu_hard_struct
op_star
id|fpregs
)paren
suffix:semicolon
multiline_comment|/* Initialise the FP state of a task */
r_void
id|fpinit
c_func
(paren
r_struct
id|sh_fpu_hard_struct
op_star
id|fpregs
)paren
suffix:semicolon
r_extern
r_struct
id|task_struct
op_star
id|last_task_used_math
suffix:semicolon
multiline_comment|/*&n; * Return saved PC of a blocked thread.&n; */
DECL|macro|thread_saved_pc
mdefine_line|#define thread_saved_pc(tsk)&t;(tsk-&gt;thread.pc)
r_extern
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
mdefine_line|#define KSTK_EIP(tsk)  ((tsk)-&gt;thread.pc)
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk)  ((tsk)-&gt;thread.sp)
DECL|macro|cpu_relax
mdefine_line|#define cpu_relax()&t;do { } while (0)
macro_line|#endif&t;/* __ASSEMBLY__ */
macro_line|#endif /* __ASM_SH64_PROCESSOR_H */
eof
