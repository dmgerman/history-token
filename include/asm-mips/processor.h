multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 Waldorf GMBH&n; * Copyright (C) 1995, 1996, 1997, 1998, 1999, 2001 Ralf Baechle&n; * Copyright (C) 1996 Paul M. Antoine&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_PROCESSOR_H
DECL|macro|_ASM_PROCESSOR_H
mdefine_line|#define _ASM_PROCESSOR_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/isadep.h&gt;
multiline_comment|/*&n; * Default implementation of macro that returns current&n; * instruction pointer (&quot;program counter&quot;).&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() ({ __label__ _l; _l: &amp;&amp;_l;})
macro_line|#if !defined (_LANGUAGE_ASSEMBLY)
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/cachectl.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/reg.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|struct|mips_cpuinfo
r_struct
id|mips_cpuinfo
(brace
DECL|member|udelay_val
r_int
r_int
id|udelay_val
suffix:semicolon
DECL|member|pgd_quick
r_int
r_int
op_star
id|pgd_quick
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
)brace
suffix:semicolon
multiline_comment|/*&n; * System setup and hardware flags..&n; * XXX: Should go into mips_cpuinfo.&n; */
r_extern
r_void
(paren
op_star
id|cpu_wait
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* only available on R4[26]00 and R3081 */
r_extern
r_void
id|r3081_wait
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|r4k_wait
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_char
id|cyclecounter_available
suffix:semicolon
multiline_comment|/* only available from R4000 upwards. */
r_extern
r_char
id|dedicated_iv_available
suffix:semicolon
multiline_comment|/* some embedded MIPS like Nevada */
r_extern
r_struct
id|mips_cpuinfo
id|boot_cpu_data
suffix:semicolon
r_extern
r_int
r_int
id|vced_count
comma
id|vcei_count
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_extern
r_struct
id|mips_cpuinfo
id|cpu_data
(braket
)braket
suffix:semicolon
DECL|macro|current_cpu_data
mdefine_line|#define current_cpu_data cpu_data[smp_processor_id()]
macro_line|#else
DECL|macro|cpu_data
mdefine_line|#define cpu_data &amp;boot_cpu_data
DECL|macro|current_cpu_data
mdefine_line|#define current_cpu_data boot_cpu_data
macro_line|#endif
multiline_comment|/*&n; * Bus types (default is ISA, but people can check others with these..)&n; * MCA_bus hardcoded to 0 for now.&n; *&n; * This needs to be extended since MIPS systems are being delivered with&n; * numerous different types of bus systems.&n; */
r_extern
r_int
id|EISA_bus
suffix:semicolon
DECL|macro|MCA_bus
mdefine_line|#define MCA_bus 0
DECL|macro|MCA_bus__is_a_macro
mdefine_line|#define MCA_bus__is_a_macro /* for versions in ksyms.c */
multiline_comment|/*&n; * MIPS has no problems with write protection&n; */
DECL|macro|wp_works_ok
mdefine_line|#define wp_works_ok 1
DECL|macro|wp_works_ok__is_a_macro
mdefine_line|#define wp_works_ok__is_a_macro /* for versions in ksyms.c */
multiline_comment|/* Lazy FPU handling on uni-processor */
r_extern
r_struct
id|task_struct
op_star
id|last_task_used_math
suffix:semicolon
multiline_comment|/*&n; * User space process size: 2GB. This is hardcoded into a few places,&n; * so don&squot;t change it unless you know what you are doing.  TASK_SIZE&n; * for a 64 bit kernel expandable to 8192EB, of which the current MIPS&n; * implementations will &quot;only&quot; be able to use 1TB ...&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(0x7fff8000UL)
multiline_comment|/* This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;(TASK_SIZE / 3)
multiline_comment|/*&n; * Size of io_bitmap in longwords: 32 is ports 0-0x3ff.&n; */
DECL|macro|IO_BITMAP_SIZE
mdefine_line|#define IO_BITMAP_SIZE&t;32
DECL|macro|NUM_FPU_REGS
mdefine_line|#define NUM_FPU_REGS&t;32
DECL|struct|mips_fpu_hard_struct
r_struct
id|mips_fpu_hard_struct
(brace
DECL|member|fp_regs
r_float
id|fp_regs
(braket
id|NUM_FPU_REGS
)braket
suffix:semicolon
DECL|member|control
r_int
r_int
id|control
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * It would be nice to add some more fields for emulator statistics, but there&n; * are a number of fixed offsets in offset.h and elsewhere that would have to&n; * be recalculated by hand.  So the additional information will be private to&n; * the FPU emulator for now.  See asm-mips/fpu_emulator.h.&n; */
DECL|typedef|fpureg_t
r_typedef
id|u64
id|fpureg_t
suffix:semicolon
DECL|struct|mips_fpu_soft_struct
r_struct
id|mips_fpu_soft_struct
(brace
DECL|member|regs
id|fpureg_t
id|regs
(braket
id|NUM_FPU_REGS
)braket
suffix:semicolon
DECL|member|sr
r_int
r_int
id|sr
suffix:semicolon
)brace
suffix:semicolon
DECL|union|mips_fpu_union
r_union
id|mips_fpu_union
(brace
DECL|member|hard
r_struct
id|mips_fpu_hard_struct
id|hard
suffix:semicolon
DECL|member|soft
r_struct
id|mips_fpu_soft_struct
id|soft
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_FPU
mdefine_line|#define INIT_FPU { &bslash;&n;&t;{{0,},} &bslash;&n;}
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
multiline_comment|/*&n; * If you change thread_struct remember to change the #defines below too!&n; */
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
multiline_comment|/* Saved main processor registers. */
DECL|member|reg16
r_int
r_int
id|reg16
suffix:semicolon
DECL|member|reg17
DECL|member|reg18
DECL|member|reg19
DECL|member|reg20
DECL|member|reg21
DECL|member|reg22
DECL|member|reg23
r_int
r_int
id|reg17
comma
id|reg18
comma
id|reg19
comma
id|reg20
comma
id|reg21
comma
id|reg22
comma
id|reg23
suffix:semicolon
DECL|member|reg29
DECL|member|reg30
DECL|member|reg31
r_int
r_int
id|reg29
comma
id|reg30
comma
id|reg31
suffix:semicolon
multiline_comment|/* Saved cp0 stuff. */
DECL|member|cp0_status
r_int
r_int
id|cp0_status
suffix:semicolon
multiline_comment|/* Saved fpu/fpu emulator stuff. */
DECL|member|fpu
r_union
id|mips_fpu_union
id|fpu
suffix:semicolon
multiline_comment|/* Other stuff associated with the thread. */
DECL|member|cp0_badvaddr
r_int
r_int
id|cp0_badvaddr
suffix:semicolon
multiline_comment|/* Last user fault */
DECL|member|cp0_baduaddr
r_int
r_int
id|cp0_baduaddr
suffix:semicolon
multiline_comment|/* Last kernel fault accessing USEG */
DECL|member|error_code
r_int
r_int
id|error_code
suffix:semicolon
DECL|member|trap_no
r_int
r_int
id|trap_no
suffix:semicolon
DECL|macro|MF_FIXADE
mdefine_line|#define MF_FIXADE 1&t;&t;&t;/* Fix address errors in software */
DECL|macro|MF_LOGADE
mdefine_line|#define MF_LOGADE 2&t;&t;&t;/* Log address errors to syslog */
DECL|member|mflags
r_int
r_int
id|mflags
suffix:semicolon
DECL|member|current_ds
id|mm_segment_t
id|current_ds
suffix:semicolon
DECL|member|irix_trampoline
r_int
r_int
id|irix_trampoline
suffix:semicolon
multiline_comment|/* Wheee... */
DECL|member|irix_oldctx
r_int
r_int
id|irix_oldctx
suffix:semicolon
multiline_comment|/*&n;&t; * These are really only needed if the full FPU emulator is configured.&n;&t; * Would be made conditional on MIPS_FPU_EMULATOR if it weren&squot;t for the&n;&t; * fact that having offset.h rebuilt differently for different config&n;&t; * options would be asking for trouble.&n;&t; *&n;&t; * Saved EPC during delay-slot emulation (see math-emu/cp1emu.c)&n;&t; */
DECL|member|dsemul_epc
r_int
r_int
id|dsemul_epc
suffix:semicolon
multiline_comment|/*&n;&t; * Pointer to instruction used to induce address error&n;&t; */
DECL|member|dsemul_aerpc
r_int
r_int
id|dsemul_aerpc
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* !defined (_LANGUAGE_ASSEMBLY) */
DECL|macro|INIT_MMAP
mdefine_line|#define INIT_MMAP { &amp;init_mm, KSEG0, KSEG1, NULL, PAGE_SHARED, &bslash;&n;                    VM_READ | VM_WRITE | VM_EXEC, 1, NULL, NULL }
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD  { &bslash;&n;        /* &bslash;&n;         * saved main processor registers &bslash;&n;         */ &bslash;&n;&t;0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;&t;               0, 0, 0, &bslash;&n;&t;/* &bslash;&n;&t; * saved cp0 stuff &bslash;&n;&t; */ &bslash;&n;&t;0, &bslash;&n;&t;/* &bslash;&n;&t; * saved fpu/fpu emulator stuff &bslash;&n;&t; */ &bslash;&n;&t;INIT_FPU, &bslash;&n;&t;/* &bslash;&n;&t; * Other stuff associated with the process &bslash;&n;&t; */ &bslash;&n;&t;0, 0, 0, 0, &bslash;&n;&t;/* &bslash;&n;&t; * For now the default is to fix address errors &bslash;&n;&t; */ &bslash;&n;&t;MF_FIXADE, { 0 }, 0, 0, &bslash;&n;&t;/* &bslash;&n;&t; * dsemul_epc and dsemul_aerpc should never be used uninitialized, &bslash;&n;&t; * but... &bslash;&n;&t; */ &bslash;&n;&t;0 ,0 &bslash;&n;}
macro_line|#ifdef __KERNEL__
DECL|macro|KERNEL_STACK_SIZE
mdefine_line|#define KERNEL_STACK_SIZE 8192
macro_line|#if !defined (_LANGUAGE_ASSEMBLY)
multiline_comment|/* Free all resources held by a thread. */
DECL|macro|release_thread
mdefine_line|#define release_thread(thread) do { } while(0)
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
mdefine_line|#define copy_segments(p, mm) do { } while(0)
DECL|macro|release_segments
mdefine_line|#define release_segments(mm) do { } while(0)
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
r_extern
r_void
id|ret_from_fork
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* New born processes are a special case */
r_if
c_cond
(paren
id|t-&gt;reg31
op_eq
(paren
r_int
r_int
)paren
id|ret_from_fork
)paren
r_return
id|t-&gt;reg31
suffix:semicolon
r_return
(paren
(paren
r_int
r_int
op_star
)paren
id|t-&gt;reg29
)paren
(braket
l_int|10
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; * Do necessary setup to start up a newly executed thread.&n; */
DECL|macro|start_thread
mdefine_line|#define start_thread(regs, new_pc, new_sp) do {&t;&t;&t;&t;&bslash;&n;&t;/* New thread looses kernel privileges. */&t;&t;&t;&bslash;&n;&t;regs-&gt;cp0_status = (regs-&gt;cp0_status &amp; ~(ST0_CU0|ST0_KSU)) | KU_USER;&bslash;&n;&t;regs-&gt;cp0_epc = new_pc;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;regs[29] = new_sp;&t;&t;&t;&t;&t;&bslash;&n;&t;current-&gt;thread.current_ds = USER_DS;&t;&t;&t;&t;&bslash;&n;} while (0)
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
DECL|macro|__PT_REG
mdefine_line|#define __PT_REG(reg) ((long)&amp;((struct pt_regs *)0)-&gt;reg - sizeof(struct pt_regs))
DECL|macro|__KSTK_TOS
mdefine_line|#define __KSTK_TOS(tsk) ((unsigned long)(tsk) + KERNEL_STACK_SIZE - 32)
DECL|macro|KSTK_EIP
mdefine_line|#define KSTK_EIP(tsk) (*(unsigned long *)(__KSTK_TOS(tsk) + __PT_REG(cp0_epc)))
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk) (*(unsigned long *)(__KSTK_TOS(tsk) + __PT_REG(regs[29])))
multiline_comment|/* Allocation and freeing of basic task resources. */
multiline_comment|/*&n; * NOTE! The task struct and the stack go together&n; */
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE (2*PAGE_SIZE)
DECL|macro|alloc_task_struct
mdefine_line|#define alloc_task_struct() &bslash;&n;&t;((struct task_struct *) __get_free_pages(GFP_KERNEL,1))
DECL|macro|free_task_struct
mdefine_line|#define free_task_struct(p)&t;free_pages((unsigned long)(p),1)
DECL|macro|get_task_struct
mdefine_line|#define get_task_struct(tsk)      atomic_inc(&amp;virt_to_page(tsk)-&gt;count)
DECL|macro|init_task
mdefine_line|#define init_task&t;(init_task_union.task)
DECL|macro|init_stack
mdefine_line|#define init_stack&t;(init_task_union.stack)
macro_line|#endif /* !defined (_LANGUAGE_ASSEMBLY) */
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * Return_address is a replacement for __builtin_return_address(count)&n; * which on certain architectures cannot reasonably be implemented in GCC&n; * (MIPS, Alpha) or is unuseable with -fomit-frame-pointer (i386).&n; * Note that __builtin_return_address(x&gt;=1) is forbidden because GCC&n; * aborts compilation on some CPUs.  It&squot;s simply not possible to unwind&n; * some CPU&squot;s stackframes.&n; *&n; * __builtin_return_address works only for non-leaf functions.  We avoid the&n; * overhead of a function call by forcing the compiler to save the return&n; * address register on the stack.&n; */
DECL|macro|return_address
mdefine_line|#define return_address() ({__asm__ __volatile__(&quot;&quot;:::&quot;$31&quot;);__builtin_return_address(0);})
macro_line|#endif /* _ASM_PROCESSOR_H */
eof
