multiline_comment|/*&n; * include/asm-sh/processor.h&n; *&n; * Copyright (C) 1999, 2000  Niibe Yutaka&n; * Copyright (C) 2002, 2003  Paul Mundt&n; */
macro_line|#ifndef __ASM_SH_PROCESSOR_H
DECL|macro|__ASM_SH_PROCESSOR_H
mdefine_line|#define __ASM_SH_PROCESSOR_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
multiline_comment|/*&n; * Default implementation of macro that returns current&n; * instruction pointer (&quot;program counter&quot;).&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() ({ void *pc; __asm__(&quot;mova&t;1f, %0&bslash;n1:&quot;:&quot;=z&quot; (pc)); pc; })
multiline_comment|/* Core Processor Version Register */
DECL|macro|CCN_PVR
mdefine_line|#define CCN_PVR&t;&t;0xff000030
DECL|macro|CCN_CVR
mdefine_line|#define CCN_CVR&t;&t;0xff000040
DECL|macro|CCN_PRR
mdefine_line|#define CCN_PRR&t;&t;0xff000044
multiline_comment|/*&n; *  CPU type and hardware bug flags. Kept separately for each CPU.&n; *&n; *  Each one of these also needs a CONFIG_CPU_SUBTYPE_xxx entry&n; *  in arch/sh/Kconfig, as well as an entry in arch/sh/kernel/setup.c&n; *  for parsing the subtype in get_cpu_subtype().&n; */
DECL|enum|cpu_type
r_enum
id|cpu_type
(brace
multiline_comment|/* SH-2 types */
DECL|enumerator|CPU_SH7604
id|CPU_SH7604
comma
multiline_comment|/* SH-3 types */
DECL|enumerator|CPU_SH7705
DECL|enumerator|CPU_SH7707
DECL|enumerator|CPU_SH7708
DECL|enumerator|CPU_SH7708S
DECL|enumerator|CPU_SH7708R
id|CPU_SH7705
comma
id|CPU_SH7707
comma
id|CPU_SH7708
comma
id|CPU_SH7708S
comma
id|CPU_SH7708R
comma
DECL|enumerator|CPU_SH7709
DECL|enumerator|CPU_SH7709A
DECL|enumerator|CPU_SH7729
DECL|enumerator|CPU_SH7300
id|CPU_SH7709
comma
id|CPU_SH7709A
comma
id|CPU_SH7729
comma
id|CPU_SH7300
comma
multiline_comment|/* SH-4 types */
DECL|enumerator|CPU_SH7750
DECL|enumerator|CPU_SH7750S
DECL|enumerator|CPU_SH7750R
DECL|enumerator|CPU_SH7751
DECL|enumerator|CPU_SH7751R
id|CPU_SH7750
comma
id|CPU_SH7750S
comma
id|CPU_SH7750R
comma
id|CPU_SH7751
comma
id|CPU_SH7751R
comma
DECL|enumerator|CPU_SH7760
DECL|enumerator|CPU_ST40RA
DECL|enumerator|CPU_ST40GX1
DECL|enumerator|CPU_SH4_202
DECL|enumerator|CPU_SH4_501
id|CPU_SH7760
comma
id|CPU_ST40RA
comma
id|CPU_ST40GX1
comma
id|CPU_SH4_202
comma
id|CPU_SH4_501
comma
DECL|enumerator|CPU_SH73180
id|CPU_SH73180
comma
multiline_comment|/* Unknown subtype */
DECL|enumerator|CPU_SH_NONE
id|CPU_SH_NONE
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
DECL|member|hard_math
r_char
id|hard_math
suffix:semicolon
DECL|member|loops_per_jiffy
r_int
r_int
id|loops_per_jiffy
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
macro_line|#ifdef CONFIG_CPU_SUBTYPE_ST40STB1
DECL|member|memory_clock
r_int
r_int
id|memory_clock
suffix:semicolon
macro_line|#endif
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
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|sh_cpuinfo
id|boot_cpu_data
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_extern
r_struct
id|sh_cpuinfo
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
multiline_comment|/*&n; * User space process size: 2GB.&n; *&n; * Since SH7709 and SH7750 have &quot;area 7&quot;, we can&squot;t use 0x7c000000--0x7fffffff&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;0x7c000000UL
multiline_comment|/* This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;(TASK_SIZE / 3)
multiline_comment|/*&n; * Bit of SR register&n; *&n; * FD-bit:&n; *     When it&squot;s set, it means the processor doesn&squot;t have right to use FPU,&n; *     and it results exception when the floating operation is executed.&n; *&n; * IMASK-bit:&n; *     Interrupt level mask&n; */
DECL|macro|SR_FD
mdefine_line|#define SR_FD&t;&t;0x00008000
DECL|macro|SR_DSP
mdefine_line|#define SR_DSP&t;&t;0x00001000
DECL|macro|SR_IMASK
mdefine_line|#define SR_IMASK&t;0x000000f0
multiline_comment|/*&n; * FPU structure and data&n; */
DECL|struct|sh_fpu_hard_struct
r_struct
id|sh_fpu_hard_struct
(brace
DECL|member|fp_regs
r_int
r_int
id|fp_regs
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|xfp_regs
r_int
r_int
id|xfp_regs
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|fpscr
r_int
r_int
id|fpscr
suffix:semicolon
DECL|member|fpul
r_int
r_int
id|fpul
suffix:semicolon
DECL|member|status
r_int
id|status
suffix:semicolon
multiline_comment|/* software status information */
)brace
suffix:semicolon
multiline_comment|/* Dummy fpu emulator  */
DECL|struct|sh_fpu_soft_struct
r_struct
id|sh_fpu_soft_struct
(brace
DECL|member|fp_regs
r_int
r_int
id|fp_regs
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|xfp_regs
r_int
r_int
id|xfp_regs
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|fpscr
r_int
r_int
id|fpscr
suffix:semicolon
DECL|member|fpul
r_int
r_int
id|fpul
suffix:semicolon
DECL|member|lookahead
r_int
r_char
id|lookahead
suffix:semicolon
DECL|member|entry_pc
r_int
r_int
id|entry_pc
suffix:semicolon
)brace
suffix:semicolon
DECL|union|sh_fpu_union
r_union
id|sh_fpu_union
(brace
DECL|member|hard
r_struct
id|sh_fpu_hard_struct
id|hard
suffix:semicolon
DECL|member|soft
r_struct
id|sh_fpu_soft_struct
id|soft
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* &n; * Processor flags&n; */
DECL|macro|CPU_HAS_FPU
mdefine_line|#define CPU_HAS_FPU&t;&t;0x0001&t;/* Hardware FPU support */
DECL|macro|CPU_HAS_P2_FLUSH_BUG
mdefine_line|#define CPU_HAS_P2_FLUSH_BUG&t;0x0002&t;/* Need to flush the cache in P2 area */
DECL|macro|CPU_HAS_MMU_PAGE_ASSOC
mdefine_line|#define CPU_HAS_MMU_PAGE_ASSOC&t;0x0004&t;/* SH3: TLB way selection bit support */
DECL|macro|CPU_HAS_DSP
mdefine_line|#define CPU_HAS_DSP&t;&t;0x0008&t;/* SH-DSP: DSP support */
DECL|macro|CPU_HAS_PERF_COUNTER
mdefine_line|#define CPU_HAS_PERF_COUNTER&t;0x0010&t;/* Hardware performance counters */
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
DECL|member|ubc_pc
r_int
r_int
id|ubc_pc
suffix:semicolon
multiline_comment|/* floating point info */
DECL|member|fpu
r_union
id|sh_fpu_union
id|fpu
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Count of active tasks with UBC settings */
r_extern
r_int
id|ubc_usercnt
suffix:semicolon
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD  {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;sizeof(init_stack) + (long) &amp;init_stack, /* sp */&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t; /* pc */&t;&bslash;&n;&t;0, 0, &t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;0, &t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;0, &t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{{{0,}},} &t;&t;&t;&t;/* fpu state */&t;&bslash;&n;}
multiline_comment|/*&n; * Do necessary setup to start up a newly executed thread.&n; */
DECL|macro|start_thread
mdefine_line|#define start_thread(regs, new_pc, new_sp)&t; &bslash;&n;&t;set_fs(USER_DS);&t;&t;&t; &bslash;&n;&t;regs-&gt;pr = 0;   &t;&t; &t; &bslash;&n;&t;regs-&gt;sr = SR_FD;&t;/* User mode. */ &bslash;&n;&t;regs-&gt;pc = new_pc;&t;&t;&t; &bslash;&n;&t;regs-&gt;regs[15] = new_sp
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
multiline_comment|/* Prepare to copy thread state - unlazy all lazy status */
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
DECL|macro|copy_segments
mdefine_line|#define copy_segments(p, mm)&t;do { } while(0)
DECL|macro|release_segments
mdefine_line|#define release_segments(mm)&t;do { } while(0)
multiline_comment|/*&n; * FPU lazy state save handling.&n; */
DECL|function|disable_fpu
r_static
id|__inline__
r_void
id|disable_fpu
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|__dummy
suffix:semicolon
multiline_comment|/* Set FD flag in SR */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stc&t;sr, %0&bslash;n&bslash;t&quot;
l_string|&quot;or&t;%1, %0&bslash;n&bslash;t&quot;
l_string|&quot;ldc&t;%0, sr&quot;
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
DECL|function|enable_fpu
r_static
id|__inline__
r_void
id|enable_fpu
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|__dummy
suffix:semicolon
multiline_comment|/* Clear out FD flag in SR */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stc&t;sr, %0&bslash;n&bslash;t&quot;
l_string|&quot;and&t;%1, %0&bslash;n&bslash;t&quot;
l_string|&quot;ldc&t;%0, sr&quot;
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
DECL|function|release_fpu
r_static
id|__inline__
r_void
id|release_fpu
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|regs-&gt;sr
op_or_assign
id|SR_FD
suffix:semicolon
)brace
DECL|function|grab_fpu
r_static
id|__inline__
r_void
id|grab_fpu
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|regs-&gt;sr
op_and_assign
op_complement
id|SR_FD
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_CPU_SH4
r_extern
r_void
id|save_fpu
c_func
(paren
r_struct
id|task_struct
op_star
id|__tsk
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#else
DECL|macro|save_fpu
mdefine_line|#define save_fpu(tsk)&t;do { } while (0)
macro_line|#endif
DECL|macro|unlazy_fpu
mdefine_line|#define unlazy_fpu(tsk, regs) do { &t;&t;&t;&t;&bslash;&n;&t;if (test_tsk_thread_flag(tsk, TIF_USEDFPU)) {&t;&bslash;&n;&t;&t;save_fpu(tsk, regs); &t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|clear_fpu
mdefine_line|#define clear_fpu(tsk, regs) do { &t;&t;&t;&t;&t;&bslash;&n;&t;if (test_tsk_thread_flag(tsk, TIF_USEDFPU)) { &t;&t;&bslash;&n;&t;&t;clear_tsk_thread_flag(tsk, TIF_USEDFPU); &t;&bslash;&n;&t;&t;release_fpu(regs);&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* Double presision, NANS as NANS, rounding to nearest, no exceptions */
DECL|macro|FPSCR_INIT
mdefine_line|#define FPSCR_INIT  0x00080000
DECL|macro|FPSCR_CAUSE_MASK
mdefine_line|#define&t;FPSCR_CAUSE_MASK&t;0x0001f000&t;/* Cause bits */
DECL|macro|FPSCR_FLAG_MASK
mdefine_line|#define&t;FPSCR_FLAG_MASK&t;&t;0x0000007c&t;/* Flag bits */
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
DECL|macro|cpu_sleep
mdefine_line|#define cpu_sleep()&t;__asm__ __volatile__ (&quot;sleep&quot; : : : &quot;memory&quot;)
DECL|macro|cpu_relax
mdefine_line|#define cpu_relax()&t;do { } while (0)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_SH_PROCESSOR_H */
eof
