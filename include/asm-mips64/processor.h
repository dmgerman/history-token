multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 Waldorf GMBH&n; * Copyright (C) 1995, 1996, 1997, 1998, 1999, 2000 Ralf Baechle&n; * Modified further for R[236]000 compatibility by Paul M. Antoine&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_PROCESSOR_H
DECL|macro|_ASM_PROCESSOR_H
mdefine_line|#define _ASM_PROCESSOR_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Return current * instruction pointer (&quot;program counter&quot;).&n; *&n; * Two implementations.  The ``la&squot;&squot; version results in shorter code for&n; * the kernel which we assume to reside in the 32-bit compat address space.&n; * The  ``jal&squot;&squot; version is for use by modules which live in outer space.&n; * This is just a single instruction unlike the long dla macro expansion.&n; */
macro_line|#ifdef MODULE
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr()&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;void *_a;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ (&quot;jal&bslash;t1f, 1f&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (_a));&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_a;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#else
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr()&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;void *_a;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ (&quot;dla&bslash;t%0, 1f&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (_a));&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_a;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
macro_line|#if !defined (_LANGUAGE_ASSEMBLY)
macro_line|#include &lt;asm/cachectl.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/reg.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#if (defined(CONFIG_SGI_IP27))
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/intr_public.h&gt;
macro_line|#endif
DECL|struct|cpuinfo_mips
r_struct
id|cpuinfo_mips
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
DECL|member|last_asn
r_int
r_int
id|last_asn
suffix:semicolon
DECL|member|asid_cache
r_int
r_int
id|asid_cache
suffix:semicolon
macro_line|#if defined(CONFIG_SGI_IP27)
DECL|member|p_cpuid
id|cpuid_t
id|p_cpuid
suffix:semicolon
multiline_comment|/* PROM assigned cpuid */
DECL|member|p_nodeid
id|cnodeid_t
id|p_nodeid
suffix:semicolon
multiline_comment|/* my node ID in compact-id-space */
DECL|member|p_nasid
id|nasid_t
id|p_nasid
suffix:semicolon
multiline_comment|/* my node ID in numa-as-id-space */
DECL|member|p_slice
r_int
r_char
id|p_slice
suffix:semicolon
multiline_comment|/* Physical position on node board */
DECL|member|p_intmasks
id|hub_intmasks_t
id|p_intmasks
suffix:semicolon
multiline_comment|/* SN0 per-CPU interrupt masks */
macro_line|#endif
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|128
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * System setup and hardware flags..&n; * XXX: Should go into mips_cpuinfo.&n; */
r_extern
r_char
id|wait_available
suffix:semicolon
multiline_comment|/* only available on R4[26]00 */
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
r_char
id|vce_available
suffix:semicolon
multiline_comment|/* Supports VCED / VCEI exceptions */
r_extern
r_char
id|mips4_available
suffix:semicolon
multiline_comment|/* CPU has MIPS IV ISA or better */
r_extern
r_int
r_int
id|vced_count
comma
id|vcei_count
suffix:semicolon
r_extern
r_struct
id|cpuinfo_mips
id|cpu_data
(braket
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|macro|current_cpu_data
mdefine_line|#define current_cpu_data cpu_data[smp_processor_id()]
macro_line|#else
DECL|macro|current_cpu_data
mdefine_line|#define current_cpu_data cpu_data[0]
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
macro_line|#ifndef CONFIG_SMP
DECL|macro|IS_FPU_OWNER
mdefine_line|#define IS_FPU_OWNER()&t;&t;(last_task_used_math == current)
DECL|macro|CLEAR_FPU_OWNER
mdefine_line|#define CLEAR_FPU_OWNER()&t;last_task_used_math = NULL;
macro_line|#else
DECL|macro|IS_FPU_OWNER
mdefine_line|#define IS_FPU_OWNER()&t;&t;(current-&gt;flags &amp; PF_USEDFPU)
DECL|macro|CLEAR_FPU_OWNER
mdefine_line|#define CLEAR_FPU_OWNER()&t;current-&gt;flags &amp;= ~PF_USEDFPU;
macro_line|#endif
multiline_comment|/*&n; * User space process size: 1TB. This is hardcoded into a few places,&n; * so don&squot;t change it unless you know what you are doing.  TASK_SIZE&n; * is limited to 1TB by the R4000 architecture; R10000 and better can&n; * support 16TB.&n; */
DECL|macro|TASK_SIZE32
mdefine_line|#define TASK_SIZE32&t;   0x80000000UL
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;0x10000000000UL
multiline_comment|/* This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;((current-&gt;thread.mflags &amp; MF_32BIT) ? &bslash;&n;&t;(TASK_SIZE32 / 3) : (TASK_SIZE / 3))
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
r_int
r_int
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
multiline_comment|/*&n; * FIXME: no fpu emulator yet (but who cares anyway?)&n; */
DECL|struct|mips_fpu_soft_struct
r_struct
id|mips_fpu_soft_struct
(brace
DECL|member|dummy
r_int
id|dummy
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
DECL|macro|MF_32BIT
mdefine_line|#define MF_32BIT  4&t;&t;&t;/* Process is in 32-bit compat mode */
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
)brace
suffix:semicolon
macro_line|#endif /* !defined (_LANGUAGE_ASSEMBLY) */
DECL|macro|INIT_MMAP
mdefine_line|#define INIT_MMAP { &amp;init_mm, KSEG0, KSEG1, NULL, PAGE_SHARED, &bslash;&n;                    VM_READ | VM_WRITE | VM_EXEC, 1, NULL, NULL }
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD  { &bslash;&n;        /* &bslash;&n;         * saved main processor registers &bslash;&n;         */ &bslash;&n;&t;0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;&t;               0, 0, 0, &bslash;&n;&t;/* &bslash;&n;&t; * saved cp0 stuff &bslash;&n;&t; */ &bslash;&n;&t;0, &bslash;&n;&t;/* &bslash;&n;&t; * saved fpu/fpu emulator stuff &bslash;&n;&t; */ &bslash;&n;&t;INIT_FPU, &bslash;&n;&t;/* &bslash;&n;&t; * Other stuff associated with the process &bslash;&n;&t; */ &bslash;&n;&t;0, 0, 0, 0, &bslash;&n;&t;/* &bslash;&n;&t; * For now the default is to fix address errors &bslash;&n;&t; */ &bslash;&n;&t;MF_FIXADE, { 0 }, 0, 0 &bslash;&n;}
macro_line|#ifdef __KERNEL__
DECL|macro|KERNEL_STACK_SIZE
mdefine_line|#define KERNEL_STACK_SIZE 0x4000
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
id|ret_from_sys_call
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
id|ret_from_sys_call
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
l_int|11
)braket
suffix:semicolon
)brace
DECL|macro|user_mode
mdefine_line|#define user_mode(regs)&t;(((regs)-&gt;cp0_status &amp; ST0_KSU) == KSU_USER)
multiline_comment|/*&n; * Do necessary setup to start up a newly executed thread.&n; */
DECL|macro|start_thread
mdefine_line|#define start_thread(regs, pc, sp) &t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __status;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;/* New thread looses kernel privileges. */&t;&t;&t;&bslash;&n;&t;__status = regs-&gt;cp0_status &amp; ~(ST0_CU0|ST0_FR|ST0_KSU);&t;&bslash;&n;&t;__status |= KSU_USER;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__status |= (current-&gt;thread.mflags &amp; MF_32BIT) ? 0 : ST0_FR;&t;&bslash;&n;&t;regs-&gt;cp0_status = __status;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;cp0_epc = pc;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;regs[29] = sp;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;current-&gt;thread.current_ds = USER_DS;&t;&t;&t;&t;&bslash;&n;} while(0)
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
mdefine_line|#define alloc_task_struct() &bslash;&n;&t;((struct task_struct *) __get_free_pages(GFP_KERNEL, 2))
DECL|macro|free_task_struct
mdefine_line|#define free_task_struct(p)&t;free_pages((unsigned long)(p), 2)
DECL|macro|get_task_struct
mdefine_line|#define get_task_struct(tsk)&t;atomic_inc(&amp;virt_to_page(tsk)-&gt;count)
DECL|macro|init_task
mdefine_line|#define init_task&t;(init_task_union.task)
DECL|macro|init_stack
mdefine_line|#define init_stack&t;(init_task_union.stack)
macro_line|#endif /* !defined (_LANGUAGE_ASSEMBLY) */
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * Return_address is a replacement for __builtin_return_address(count)&n; * which on certain architectures cannot reasonably be implemented in GCC&n; * (MIPS, Alpha) or is unuseable with -fomit-frame-pointer (i386).&n; * Note that __builtin_return_address(x&gt;=1) is forbidden because GCC&n; * aborts compilation on some CPUs.  It&squot;s simply not possible to unwind&n; * some CPU&squot;s stackframes.&n; *&n; * In gcc 2.8 and newer  __builtin_return_address works only for non-leaf&n; * functions.  We avoid the overhead of a function call by forcing the&n; * compiler to save the return address register on the stack.&n; */
DECL|macro|return_address
mdefine_line|#define return_address() ({__asm__ __volatile__(&quot;&quot;:::&quot;$31&quot;);__builtin_return_address(0);})
macro_line|#endif /* _ASM_PROCESSOR_H */
eof
