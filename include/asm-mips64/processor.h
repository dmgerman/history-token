multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 Waldorf GMBH&n; * Copyright (C) 1995, 1996, 1997, 1998, 1999, 2001, 2002, 2003 Ralf Baechle&n; * Modified further for R[236]000 compatibility by Paul M. Antoine&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_PROCESSOR_H
DECL|macro|_ASM_PROCESSOR_H
mdefine_line|#define _ASM_PROCESSOR_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Return current * instruction pointer (&quot;program counter&quot;).&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr()&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;void *_a;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ (&quot;bal&bslash;t1f&bslash;t&bslash;t&bslash;t# current_text_addr&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&bslash;tmove&bslash;t%0, $31&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (_a)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;$31&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_a;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/cachectl.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/reg.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#if defined(CONFIG_SGI_IP27)
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/intr_public.h&gt;
macro_line|#endif
multiline_comment|/*&n; * Descriptor for a cache&n; */
DECL|struct|cache_desc
r_struct
id|cache_desc
(brace
DECL|member|linesz
r_int
r_int
id|linesz
suffix:semicolon
DECL|member|ways
r_int
r_int
id|ways
suffix:semicolon
DECL|member|sets
r_int
r_int
id|sets
suffix:semicolon
DECL|member|waybit
r_int
r_int
id|waybit
suffix:semicolon
multiline_comment|/* Bits to select in a cache set */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Flags describingcache properties */
)brace
suffix:semicolon
multiline_comment|/*&n; * Flag definitions&n; */
DECL|macro|MIPS_CACHE_NOT_PRESENT
mdefine_line|#define MIPS_CACHE_NOT_PRESENT&t;0x00000001
DECL|macro|MIPS_CACHE_VTAG
mdefine_line|#define MIPS_CACHE_VTAG&t;&t;0x00000002&t;/* Virtually tagged cache */
DECL|macro|MIPS_CACHE_ALIASES
mdefine_line|#define MIPS_CACHE_ALIASES&t;0x00000004&t;/* Cache could have aliases */
DECL|macro|MIPS_CACHE_IC_F_DC
mdefine_line|#define MIPS_CACHE_IC_F_DC&t;0x00000008&t;/* Ic can refill from D-cache */
DECL|struct|cpuinfo_mips
r_struct
id|cpuinfo_mips
(brace
DECL|member|udelay_val
r_int
r_int
id|udelay_val
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
macro_line|#if 0
r_int
r_int
id|loops_per_sec
suffix:semicolon
r_int
r_int
id|ipi_count
suffix:semicolon
r_int
r_int
id|irq_attempt
(braket
id|NR_IRQS
)braket
suffix:semicolon
r_int
r_int
id|smp_local_irq_count
suffix:semicolon
r_int
r_int
id|prof_multiplier
suffix:semicolon
r_int
r_int
id|prof_counter
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Capability and feature descriptor structure for MIPS CPU&n;&t; */
DECL|member|options
r_int
r_int
id|options
suffix:semicolon
DECL|member|processor_id
r_int
r_int
id|processor_id
suffix:semicolon
DECL|member|fpu_id
r_int
r_int
id|fpu_id
suffix:semicolon
DECL|member|cputype
r_int
r_int
id|cputype
suffix:semicolon
DECL|member|isa_level
r_int
id|isa_level
suffix:semicolon
DECL|member|tlbsize
r_int
id|tlbsize
suffix:semicolon
DECL|member|icache
r_struct
id|cache_desc
id|icache
suffix:semicolon
multiline_comment|/* Primary I-cache */
DECL|member|dcache
r_struct
id|cache_desc
id|dcache
suffix:semicolon
multiline_comment|/* Primary D or combined I/D cache */
DECL|member|scache
r_struct
id|cache_desc
id|scache
suffix:semicolon
multiline_comment|/* Secondary cache */
DECL|member|tcache
r_struct
id|cache_desc
id|tcache
suffix:semicolon
multiline_comment|/* Tertiary/split secondary cache */
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
id|SMP_CACHE_BYTES
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Assumption: Options of CPU 0 are a superset of all processors.&n; * This is true for all known MIPS systems.&n; */
DECL|macro|cpu_has_tlb
mdefine_line|#define cpu_has_tlb&t;&t;(cpu_data[0].options &amp; MIPS_CPU_TLB)
DECL|macro|cpu_has_4kex
mdefine_line|#define cpu_has_4kex&t;&t;(cpu_data[0].options &amp; MIPS_CPU_4KEX)
DECL|macro|cpu_has_4ktlb
mdefine_line|#define cpu_has_4ktlb&t;&t;(cpu_data[0].options &amp; MIPS_CPU_4KTLB)
DECL|macro|cpu_has_fpu
mdefine_line|#define cpu_has_fpu&t;&t;(cpu_data[0].options &amp; MIPS_CPU_FPU)
DECL|macro|cpu_has_32fpr
mdefine_line|#define cpu_has_32fpr&t;&t;(cpu_data[0].options &amp; MIPS_CPU_32FPR)
DECL|macro|cpu_has_counter
mdefine_line|#define cpu_has_counter&t;&t;(cpu_data[0].options &amp; MIPS_CPU_COUNTER)
DECL|macro|cpu_has_watch
mdefine_line|#define cpu_has_watch&t;&t;(cpu_data[0].options &amp; MIPS_CPU_WATCH)
DECL|macro|cpu_has_mips16
mdefine_line|#define cpu_has_mips16&t;&t;(cpu_data[0].options &amp; MIPS_CPU_MIPS16)
DECL|macro|cpu_has_divec
mdefine_line|#define cpu_has_divec&t;&t;(cpu_data[0].options &amp; MIPS_CPU_DIVEC)
DECL|macro|cpu_has_vce
mdefine_line|#define cpu_has_vce&t;&t;(cpu_data[0].options &amp; MIPS_CPU_VCE)
DECL|macro|cpu_has_cache_cdex
mdefine_line|#define cpu_has_cache_cdex&t;(cpu_data[0].options &amp; MIPS_CPU_CACHE_CDEX)
DECL|macro|cpu_has_mcheck
mdefine_line|#define cpu_has_mcheck&t;&t;(cpu_data[0].options &amp; MIPS_CPU_MCHECK)
DECL|macro|cpu_has_ejtag
mdefine_line|#define cpu_has_ejtag&t;&t;(cpu_data[0].options &amp; MIPS_CPU_EJTAG)
DECL|macro|cpu_has_nofpuex
mdefine_line|#define cpu_has_nofpuex&t;&t;(cpu_data[0].options &amp; MIPS_CPU_NOFPUEX)
DECL|macro|cpu_has_llsc
mdefine_line|#define cpu_has_llsc&t;&t;(cpu_data[0].options &amp; MIPS_CPU_LLSC)
DECL|macro|cpu_has_vtag_icache
mdefine_line|#define cpu_has_vtag_icache&t;(cpu_data[0].icache.flags &amp; MIPS_CACHE_VTAG)
DECL|macro|cpu_has_dc_aliases
mdefine_line|#define cpu_has_dc_aliases&t;(cpu_data[0].dcache.flags &amp; MIPS_CACHE_ALIASES)
DECL|macro|cpu_has_ic_fills_f_dc
mdefine_line|#define cpu_has_ic_fills_f_dc&t;(cpu_data[0].dcache.flags &amp; MIPS_CACHE_IC_F_DC)
DECL|macro|cpu_has_64bits
mdefine_line|#define cpu_has_64bits&t;&t;1
DECL|macro|cpu_has_subset_pcaches
mdefine_line|#define cpu_has_subset_pcaches&t;(cpu_data[0].options &amp; MIPS_CPU_SUBSET_CACHES)
r_extern
r_struct
id|cpuinfo_mips
id|cpu_data
(braket
)braket
suffix:semicolon
DECL|macro|current_cpu_data
mdefine_line|#define current_cpu_data cpu_data[smp_processor_id()]
r_extern
r_void
id|cpu_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cpu_report
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * System setup and hardware flags..&n; */
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
r_extern
r_int
r_int
id|vced_count
comma
id|vcei_count
suffix:semicolon
multiline_comment|/*&n; * Bus types (default is ISA, but people can check others with these..)&n; */
macro_line|#ifdef CONFIG_EISA
r_extern
r_int
id|EISA_bus
suffix:semicolon
macro_line|#else
DECL|macro|EISA_bus
mdefine_line|#define EISA_bus (0)
macro_line|#endif
DECL|macro|MCA_bus
mdefine_line|#define MCA_bus 0
DECL|macro|MCA_bus__is_a_macro
mdefine_line|#define MCA_bus__is_a_macro /* for versions in ksyms.c */
multiline_comment|/*&n; * User space process size: 1TB. This is hardcoded into a few places,&n; * so don&squot;t change it unless you know what you are doing.  TASK_SIZE&n; * is limited to 1TB by the R4000 architecture; R10000 and better can&n; * support 16TB.&n; */
DECL|macro|TASK_SIZE32
mdefine_line|#define TASK_SIZE32&t;   0x7fff8000UL
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;0x10000000000UL
multiline_comment|/* This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;((current-&gt;thread.mflags &amp; MF_32BIT_ADDR) ? &bslash;&n;&t;PAGE_ALIGN(TASK_SIZE32 / 3) : PAGE_ALIGN(TASK_SIZE / 3))
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
mdefine_line|#define MF_FIXADE&t;1&t;&t;/* Fix address errors in software */
DECL|macro|MF_LOGADE
mdefine_line|#define MF_LOGADE&t;2&t;&t;/* Log address errors to syslog */
DECL|macro|MF_32BIT_REGS
mdefine_line|#define MF_32BIT_REGS&t;4&t;&t;/* also implies 16/32 fprs */
DECL|macro|MF_32BIT_ADDR
mdefine_line|#define MF_32BIT_ADDR&t;8&t;&t;/* 32-bit address space (o32/n32) */
DECL|member|mflags
r_int
r_int
id|mflags
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
DECL|macro|MF_ABI_MASK
mdefine_line|#define MF_ABI_MASK&t;(MF_32BIT_REGS | MF_32BIT_ADDR)
DECL|macro|MF_O32
mdefine_line|#define MF_O32&t;&t;(MF_32BIT_REGS | MF_32BIT_ADDR)
DECL|macro|MF_N32
mdefine_line|#define MF_N32&t;&t;MF_32BIT_ADDR
DECL|macro|MF_N64
mdefine_line|#define MF_N64&t;&t;0
macro_line|#endif /* !__ASSEMBLY__ */
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD  { &bslash;&n;        /* &bslash;&n;         * saved main processor registers &bslash;&n;         */ &bslash;&n;&t;0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;&t;               0, 0, 0, &bslash;&n;&t;/* &bslash;&n;&t; * saved cp0 stuff &bslash;&n;&t; */ &bslash;&n;&t;0, &bslash;&n;&t;/* &bslash;&n;&t; * saved fpu/fpu emulator stuff &bslash;&n;&t; */ &bslash;&n;&t;INIT_FPU, &bslash;&n;&t;/* &bslash;&n;&t; * Other stuff associated with the process &bslash;&n;&t; */ &bslash;&n;&t;0, 0, 0, 0, &bslash;&n;&t;/* &bslash;&n;&t; * For now the default is to fix address errors &bslash;&n;&t; */ &bslash;&n;&t;MF_FIXADE, 0, 0 &bslash;&n;}
macro_line|#ifdef __KERNEL__
DECL|macro|KERNEL_STACK_SIZE
mdefine_line|#define KERNEL_STACK_SIZE 0x4000
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Free all resources held by a thread. */
DECL|macro|release_thread
mdefine_line|#define release_thread(thread) do { } while(0)
multiline_comment|/* Prepare to copy thread state - unlazy all lazy status */
DECL|macro|prepare_to_copy
mdefine_line|#define prepare_to_copy(tsk)&t;do { } while (0)
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
suffix:semicolon
DECL|macro|user_mode
mdefine_line|#define user_mode(regs)&t;(((regs)-&gt;cp0_status &amp; ST0_KSU) == KSU_USER)
multiline_comment|/*&n; * Do necessary setup to start up a newly executed thread.&n; */
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
id|pc
comma
r_int
r_int
id|sp
)paren
suffix:semicolon
r_struct
id|task_struct
suffix:semicolon
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
mdefine_line|#define __KSTK_TOS(tsk) ((unsigned long)(tsk-&gt;thread_info) + KERNEL_STACK_SIZE - 32)
DECL|macro|KSTK_EIP
mdefine_line|#define KSTK_EIP(tsk) (*(unsigned long *)(__KSTK_TOS(tsk) + __PT_REG(cp0_epc)))
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk) (*(unsigned long *)(__KSTK_TOS(tsk) + __PT_REG(regs[29])))
DECL|macro|KSTK_STATUS
mdefine_line|#define KSTK_STATUS(tsk) (*(unsigned long *)(__KSTK_TOS(tsk) + __PT_REG(cp0_status)))
DECL|macro|cpu_relax
mdefine_line|#define cpu_relax()&t;barrier()
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * Return_address is a replacement for __builtin_return_address(count)&n; * which on certain architectures cannot reasonably be implemented in GCC&n; * (MIPS, Alpha) or is unuseable with -fomit-frame-pointer (i386).&n; * Note that __builtin_return_address(x&gt;=1) is forbidden because GCC&n; * aborts compilation on some CPUs.  It&squot;s simply not possible to unwind&n; * some CPU&squot;s stackframes.&n; *&n; * In gcc 2.8 and newer  __builtin_return_address works only for non-leaf&n; * functions.  We avoid the overhead of a function call by forcing the&n; * compiler to save the return address register on the stack.&n; */
DECL|macro|return_address
mdefine_line|#define return_address() ({__asm__ __volatile__(&quot;&quot;:::&quot;$31&quot;);__builtin_return_address(0);})
macro_line|#endif /* _ASM_PROCESSOR_H */
eof
