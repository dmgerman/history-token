macro_line|#ifndef _ASM_IA64_PROCESSOR_H
DECL|macro|_ASM_IA64_PROCESSOR_H
mdefine_line|#define _ASM_IA64_PROCESSOR_H
multiline_comment|/*&n; * Copyright (C) 1998-2003 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&t;Stephane Eranian &lt;eranian@hpl.hp.com&gt;&n; * Copyright (C) 1999 Asit Mallick &lt;asit.k.mallick@intel.com&gt;&n; * Copyright (C) 1999 Don Dugger &lt;don.dugger@intel.com&gt;&n; *&n; * 11/24/98&t;S.Eranian&t;added ia64_set_iva()&n; * 12/03/99&t;D. Mosberger&t;implement thread_saved_pc() via kernel unwind API&n; * 06/16/00&t;A. Mallick&t;added csd/ssd/tssd for ia32 support&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/intrinsics.h&gt;
macro_line|#include &lt;asm/kregs.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/ustack.h&gt;
DECL|macro|IA64_NUM_DBG_REGS
mdefine_line|#define IA64_NUM_DBG_REGS&t;8
multiline_comment|/*&n; * Limits for PMC and PMD are set to less than maximum architected values&n; * but should be sufficient for a while&n; */
DECL|macro|IA64_NUM_PMC_REGS
mdefine_line|#define IA64_NUM_PMC_REGS&t;32
DECL|macro|IA64_NUM_PMD_REGS
mdefine_line|#define IA64_NUM_PMD_REGS&t;32
DECL|macro|DEFAULT_MAP_BASE
mdefine_line|#define DEFAULT_MAP_BASE&t;0x2000000000000000
DECL|macro|DEFAULT_TASK_SIZE
mdefine_line|#define DEFAULT_TASK_SIZE&t;0xa000000000000000
multiline_comment|/*&n; * TASK_SIZE really is a mis-named.  It really is the maximum user&n; * space address (plus one).  On IA-64, there are five regions of 2TB&n; * each (assuming 8KB page size), for a total of 8TB of user virtual&n; * address space.&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;&t;(current-&gt;thread.task_size)
multiline_comment|/*&n; * MM_VM_SIZE(mm) gives the maximum address (plus 1) which may contain a mapping for&n; * address-space MM.  Note that with 32-bit tasks, this is still DEFAULT_TASK_SIZE,&n; * because the kernel may have installed helper-mappings above TASK_SIZE.  For example,&n; * for x86 emulation, the LDT and GDT are mapped above TASK_SIZE.&n; */
DECL|macro|MM_VM_SIZE
mdefine_line|#define MM_VM_SIZE(mm)&t;&t;DEFAULT_TASK_SIZE
multiline_comment|/*&n; * This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;(current-&gt;thread.map_base)
multiline_comment|/*&n; * Bus types&n; */
DECL|macro|MCA_bus
mdefine_line|#define MCA_bus 0
DECL|macro|MCA_bus__is_a_macro
mdefine_line|#define MCA_bus__is_a_macro /* for versions in ksyms.c */
DECL|macro|IA64_THREAD_FPH_VALID
mdefine_line|#define IA64_THREAD_FPH_VALID&t;(__IA64_UL(1) &lt;&lt; 0)&t;/* floating-point high state valid? */
DECL|macro|IA64_THREAD_DBG_VALID
mdefine_line|#define IA64_THREAD_DBG_VALID&t;(__IA64_UL(1) &lt;&lt; 1)&t;/* debug registers valid? */
DECL|macro|IA64_THREAD_PM_VALID
mdefine_line|#define IA64_THREAD_PM_VALID&t;(__IA64_UL(1) &lt;&lt; 2)&t;/* performance registers valid? */
DECL|macro|IA64_THREAD_UAC_NOPRINT
mdefine_line|#define IA64_THREAD_UAC_NOPRINT&t;(__IA64_UL(1) &lt;&lt; 3)&t;/* don&squot;t log unaligned accesses */
DECL|macro|IA64_THREAD_UAC_SIGBUS
mdefine_line|#define IA64_THREAD_UAC_SIGBUS&t;(__IA64_UL(1) &lt;&lt; 4)&t;/* generate SIGBUS on unaligned acc. */
DECL|macro|IA64_THREAD_KRBS_SYNCED
mdefine_line|#define IA64_THREAD_KRBS_SYNCED&t;(__IA64_UL(1) &lt;&lt; 5)&t;/* krbs synced with process vm? */
DECL|macro|IA64_THREAD_FPEMU_NOPRINT
mdefine_line|#define IA64_THREAD_FPEMU_NOPRINT (__IA64_UL(1) &lt;&lt; 6)&t;/* don&squot;t log any fpswa faults */
DECL|macro|IA64_THREAD_FPEMU_SIGFPE
mdefine_line|#define IA64_THREAD_FPEMU_SIGFPE  (__IA64_UL(1) &lt;&lt; 7)&t;/* send a SIGFPE for fpswa faults */
DECL|macro|IA64_THREAD_XSTACK
mdefine_line|#define IA64_THREAD_XSTACK&t;(__IA64_UL(1) &lt;&lt; 8)&t;/* stack executable by default? */
DECL|macro|IA64_THREAD_UAC_SHIFT
mdefine_line|#define IA64_THREAD_UAC_SHIFT&t;3
DECL|macro|IA64_THREAD_UAC_MASK
mdefine_line|#define IA64_THREAD_UAC_MASK&t;(IA64_THREAD_UAC_NOPRINT | IA64_THREAD_UAC_SIGBUS)
DECL|macro|IA64_THREAD_FPEMU_SHIFT
mdefine_line|#define IA64_THREAD_FPEMU_SHIFT&t;6
DECL|macro|IA64_THREAD_FPEMU_MASK
mdefine_line|#define IA64_THREAD_FPEMU_MASK&t;(IA64_THREAD_FPEMU_NOPRINT | IA64_THREAD_FPEMU_SIGFPE)
multiline_comment|/*&n; * This shift should be large enough to be able to represent 1000000000/itc_freq with good&n; * accuracy while being small enough to fit 10*1000000000&lt;&lt;IA64_NSEC_PER_CYC_SHIFT in 64 bits&n; * (this will give enough slack to represent 10 seconds worth of time as a scaled number).&n; */
DECL|macro|IA64_NSEC_PER_CYC_SHIFT
mdefine_line|#define IA64_NSEC_PER_CYC_SHIFT&t;30
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/fpu.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/percpu.h&gt;
macro_line|#include &lt;asm/rse.h&gt;
macro_line|#include &lt;asm/unwind.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#ifdef CONFIG_NUMA
macro_line|#include &lt;asm/nodedata.h&gt;
macro_line|#endif
multiline_comment|/* like above but expressed as bitfields for more efficient access: */
DECL|struct|ia64_psr
r_struct
id|ia64_psr
(brace
DECL|member|reserved0
id|__u64
id|reserved0
suffix:colon
l_int|1
suffix:semicolon
DECL|member|be
id|__u64
id|be
suffix:colon
l_int|1
suffix:semicolon
DECL|member|up
id|__u64
id|up
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ac
id|__u64
id|ac
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mfl
id|__u64
id|mfl
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mfh
id|__u64
id|mfh
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved1
id|__u64
id|reserved1
suffix:colon
l_int|7
suffix:semicolon
DECL|member|ic
id|__u64
id|ic
suffix:colon
l_int|1
suffix:semicolon
DECL|member|i
id|__u64
id|i
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pk
id|__u64
id|pk
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved2
id|__u64
id|reserved2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dt
id|__u64
id|dt
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dfl
id|__u64
id|dfl
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dfh
id|__u64
id|dfh
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sp
id|__u64
id|sp
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pp
id|__u64
id|pp
suffix:colon
l_int|1
suffix:semicolon
DECL|member|di
id|__u64
id|di
suffix:colon
l_int|1
suffix:semicolon
DECL|member|si
id|__u64
id|si
suffix:colon
l_int|1
suffix:semicolon
DECL|member|db
id|__u64
id|db
suffix:colon
l_int|1
suffix:semicolon
DECL|member|lp
id|__u64
id|lp
suffix:colon
l_int|1
suffix:semicolon
DECL|member|tb
id|__u64
id|tb
suffix:colon
l_int|1
suffix:semicolon
DECL|member|rt
id|__u64
id|rt
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved3
id|__u64
id|reserved3
suffix:colon
l_int|4
suffix:semicolon
DECL|member|cpl
id|__u64
id|cpl
suffix:colon
l_int|2
suffix:semicolon
DECL|member|is
id|__u64
id|is
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mc
id|__u64
id|mc
suffix:colon
l_int|1
suffix:semicolon
DECL|member|it
id|__u64
id|it
suffix:colon
l_int|1
suffix:semicolon
DECL|member|id
id|__u64
id|id
suffix:colon
l_int|1
suffix:semicolon
DECL|member|da
id|__u64
id|da
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dd
id|__u64
id|dd
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ss
id|__u64
id|ss
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ri
id|__u64
id|ri
suffix:colon
l_int|2
suffix:semicolon
DECL|member|ed
id|__u64
id|ed
suffix:colon
l_int|1
suffix:semicolon
DECL|member|bn
id|__u64
id|bn
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved4
id|__u64
id|reserved4
suffix:colon
l_int|19
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * CPU type, hardware bug flags, and per-CPU state.  Frequently used&n; * state comes earlier:&n; */
DECL|struct|cpuinfo_ia64
r_struct
id|cpuinfo_ia64
(brace
multiline_comment|/* irq_stat must be 64-bit aligned */
r_union
(brace
r_struct
(brace
DECL|member|irq_count
id|__u32
id|irq_count
suffix:semicolon
DECL|member|bh_count
id|__u32
id|bh_count
suffix:semicolon
DECL|member|f
)brace
id|f
suffix:semicolon
DECL|member|irq_and_bh_counts
id|__u64
id|irq_and_bh_counts
suffix:semicolon
DECL|member|irq_stat
)brace
id|irq_stat
suffix:semicolon
DECL|member|softirq_pending
id|__u32
id|softirq_pending
suffix:semicolon
DECL|member|itm_delta
id|__u64
id|itm_delta
suffix:semicolon
multiline_comment|/* # of clock cycles between clock ticks */
DECL|member|itm_next
id|__u64
id|itm_next
suffix:semicolon
multiline_comment|/* interval timer mask value to use for next clock tick */
DECL|member|pgd_quick
id|__u64
op_star
id|pgd_quick
suffix:semicolon
DECL|member|pmd_quick
id|__u64
op_star
id|pmd_quick
suffix:semicolon
DECL|member|pgtable_cache_sz
id|__u64
id|pgtable_cache_sz
suffix:semicolon
multiline_comment|/* CPUID-derived information: */
DECL|member|ppn
id|__u64
id|ppn
suffix:semicolon
DECL|member|features
id|__u64
id|features
suffix:semicolon
DECL|member|number
id|__u8
id|number
suffix:semicolon
DECL|member|revision
id|__u8
id|revision
suffix:semicolon
DECL|member|model
id|__u8
id|model
suffix:semicolon
DECL|member|family
id|__u8
id|family
suffix:semicolon
DECL|member|archrev
id|__u8
id|archrev
suffix:semicolon
DECL|member|vendor
r_char
id|vendor
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|itc_freq
id|__u64
id|itc_freq
suffix:semicolon
multiline_comment|/* frequency of ITC counter */
DECL|member|proc_freq
id|__u64
id|proc_freq
suffix:semicolon
multiline_comment|/* frequency of processor */
DECL|member|cyc_per_usec
id|__u64
id|cyc_per_usec
suffix:semicolon
multiline_comment|/* itc_freq/1000000 */
DECL|member|nsec_per_cyc
id|__u64
id|nsec_per_cyc
suffix:semicolon
multiline_comment|/* (1000000000&lt;&lt;IA64_NSEC_PER_CYC_SHIFT)/itc_freq */
DECL|member|unimpl_va_mask
id|__u64
id|unimpl_va_mask
suffix:semicolon
multiline_comment|/* mask of unimplemented virtual address bits (from PAL) */
DECL|member|unimpl_pa_mask
id|__u64
id|unimpl_pa_mask
suffix:semicolon
multiline_comment|/* mask of unimplemented physical address bits (from PAL) */
DECL|member|ptce_base
id|__u64
id|ptce_base
suffix:semicolon
DECL|member|ptce_count
id|__u32
id|ptce_count
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|ptce_stride
id|__u32
id|ptce_stride
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|ksoftirqd
r_struct
id|task_struct
op_star
id|ksoftirqd
suffix:semicolon
multiline_comment|/* kernel softirq daemon for this CPU */
macro_line|#ifdef CONFIG_SMP
DECL|member|cpu
r_int
id|cpu
suffix:semicolon
DECL|member|loops_per_jiffy
id|__u64
id|loops_per_jiffy
suffix:semicolon
DECL|member|ipi_count
id|__u64
id|ipi_count
suffix:semicolon
DECL|member|prof_counter
id|__u64
id|prof_counter
suffix:semicolon
DECL|member|prof_multiplier
id|__u64
id|prof_multiplier
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_NUMA
DECL|member|node_data
r_struct
id|ia64_node_data
op_star
id|node_data
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
id|DECLARE_PER_CPU
c_func
(paren
r_struct
id|cpuinfo_ia64
comma
id|cpu_info
)paren
suffix:semicolon
multiline_comment|/*&n; * The &quot;local&quot; data variable.  It refers to the per-CPU data of the currently executing&n; * CPU, much like &quot;current&quot; points to the per-task data of the currently executing task.&n; * Do not use the address of local_cpu_data, since it will be different from&n; * cpu_data(smp_processor_id())!&n; */
DECL|macro|local_cpu_data
mdefine_line|#define local_cpu_data&t;&t;(&amp;__ia64_per_cpu_var(cpu_info))
DECL|macro|cpu_data
mdefine_line|#define cpu_data(cpu)&t;&t;(&amp;per_cpu(cpu_info, cpu))
r_extern
r_void
id|identify_cpu
(paren
r_struct
id|cpuinfo_ia64
op_star
)paren
suffix:semicolon
r_extern
r_void
id|print_cpu_info
(paren
r_struct
id|cpuinfo_ia64
op_star
)paren
suffix:semicolon
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
DECL|macro|SET_UNALIGN_CTL
mdefine_line|#define SET_UNALIGN_CTL(task,value)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(task)-&gt;thread.flags = (((task)-&gt;thread.flags &amp; ~IA64_THREAD_UAC_MASK)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;| (((value) &lt;&lt; IA64_THREAD_UAC_SHIFT) &amp; IA64_THREAD_UAC_MASK));&t;&bslash;&n;&t;0;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|GET_UNALIGN_CTL
mdefine_line|#define GET_UNALIGN_CTL(task,addr)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;put_user(((task)-&gt;thread.flags &amp; IA64_THREAD_UAC_MASK) &gt;&gt; IA64_THREAD_UAC_SHIFT,&t;&bslash;&n;&t;&t; (int *) (addr));&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|SET_FPEMU_CTL
mdefine_line|#define SET_FPEMU_CTL(task,value)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(task)-&gt;thread.flags = (((task)-&gt;thread.flags &amp; ~IA64_THREAD_FPEMU_MASK)&t;&t;&bslash;&n;&t;&t;&t;  | (((value) &lt;&lt; IA64_THREAD_FPEMU_SHIFT) &amp; IA64_THREAD_FPEMU_MASK));&t;&bslash;&n;&t;0;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|GET_FPEMU_CTL
mdefine_line|#define GET_FPEMU_CTL(task,addr)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;put_user(((task)-&gt;thread.flags &amp; IA64_THREAD_FPEMU_MASK) &gt;&gt; IA64_THREAD_FPEMU_SHIFT,&t;&bslash;&n;&t;&t; (int *) (addr));&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
multiline_comment|/* various thread flags (see IA64_THREAD_*) */
multiline_comment|/* writing on_ustack is performance-critical, so it&squot;s worth spending 8 bits on it... */
DECL|member|on_ustack
id|__u8
id|on_ustack
suffix:semicolon
multiline_comment|/* executing on user-stacks? */
DECL|member|pad
id|__u8
id|pad
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ksp
id|__u64
id|ksp
suffix:semicolon
multiline_comment|/* kernel stack pointer */
DECL|member|map_base
id|__u64
id|map_base
suffix:semicolon
multiline_comment|/* base address for get_unmapped_area() */
DECL|member|task_size
id|__u64
id|task_size
suffix:semicolon
multiline_comment|/* limit for task size */
DECL|member|rbs_bot
id|__u64
id|rbs_bot
suffix:semicolon
multiline_comment|/* the base address for the RBS */
DECL|member|last_fph_cpu
r_int
id|last_fph_cpu
suffix:semicolon
multiline_comment|/* CPU that may hold the contents of f32-f127 */
macro_line|#ifdef CONFIG_IA32_SUPPORT
DECL|member|eflag
id|__u64
id|eflag
suffix:semicolon
multiline_comment|/* IA32 EFLAGS reg */
DECL|member|fsr
id|__u64
id|fsr
suffix:semicolon
multiline_comment|/* IA32 floating pt status reg */
DECL|member|fcr
id|__u64
id|fcr
suffix:semicolon
multiline_comment|/* IA32 floating pt control reg */
DECL|member|fir
id|__u64
id|fir
suffix:semicolon
multiline_comment|/* IA32 fp except. instr. reg */
DECL|member|fdr
id|__u64
id|fdr
suffix:semicolon
multiline_comment|/* IA32 fp except. data reg */
DECL|member|old_k1
id|__u64
id|old_k1
suffix:semicolon
multiline_comment|/* old value of ar.k1 */
DECL|member|old_iob
id|__u64
id|old_iob
suffix:semicolon
multiline_comment|/* old IOBase value */
DECL|macro|INIT_THREAD_IA32
macro_line|# define INIT_THREAD_IA32&t;.eflag =&t;0,&t;&t;&t;&bslash;&n;&t;&t;&t;&t;.fsr =&t;&t;0,&t;&t;&t;&bslash;&n;&t;&t;&t;&t;.fcr =&t;&t;0x17800000037fULL,&t;&bslash;&n;&t;&t;&t;&t;.fir =&t;&t;0,&t;&t;&t;&bslash;&n;&t;&t;&t;&t;.fdr =&t;&t;0,&t;&t;&t;&bslash;&n;&t;&t;&t;&t;.old_k1 =&t;0,&t;&t;&t;&bslash;&n;&t;&t;&t;&t;.old_iob =&t;0,
macro_line|#else
DECL|macro|INIT_THREAD_IA32
macro_line|# define INIT_THREAD_IA32
macro_line|#endif /* CONFIG_IA32_SUPPORT */
macro_line|#ifdef CONFIG_PERFMON
DECL|member|pmcs
id|__u64
id|pmcs
(braket
id|IA64_NUM_PMC_REGS
)braket
suffix:semicolon
DECL|member|pmds
id|__u64
id|pmds
(braket
id|IA64_NUM_PMD_REGS
)braket
suffix:semicolon
DECL|member|pfm_context
r_void
op_star
id|pfm_context
suffix:semicolon
multiline_comment|/* pointer to detailed PMU context */
DECL|member|pfm_needs_checking
r_int
r_int
id|pfm_needs_checking
suffix:semicolon
multiline_comment|/* when &gt;0, pending perfmon work on kernel exit */
DECL|macro|INIT_THREAD_PM
macro_line|# define INIT_THREAD_PM&t;&t;.pmcs =&t;&t;&t;{0UL, },  &bslash;&n;&t;&t;&t;&t;.pmds =&t;&t;&t;{0UL, },  &bslash;&n;&t;&t;&t;&t;.pfm_context =&t;&t;NULL,     &bslash;&n;&t;&t;&t;&t;.pfm_needs_checking =&t;0UL,
macro_line|#else
DECL|macro|INIT_THREAD_PM
macro_line|# define INIT_THREAD_PM
macro_line|#endif
DECL|member|dbr
id|__u64
id|dbr
(braket
id|IA64_NUM_DBG_REGS
)braket
suffix:semicolon
DECL|member|ibr
id|__u64
id|ibr
(braket
id|IA64_NUM_DBG_REGS
)braket
suffix:semicolon
DECL|member|fph
r_struct
id|ia64_fpreg
id|fph
(braket
l_int|96
)braket
suffix:semicolon
multiline_comment|/* saved/loaded on demand */
)brace
suffix:semicolon
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD {&t;&t;&t;&t;&bslash;&n;&t;.flags =&t;0,&t;&t;&t;&bslash;&n;&t;.on_ustack =&t;0,&t;&t;&t;&bslash;&n;&t;.ksp =&t;&t;0,&t;&t;&t;&bslash;&n;&t;.map_base =&t;DEFAULT_MAP_BASE,&t;&bslash;&n;&t;.rbs_bot =&t;DEFAULT_USER_STACK_SIZE,&t;&bslash;&n;&t;.task_size =&t;DEFAULT_TASK_SIZE,&t;&bslash;&n;&t;.last_fph_cpu =  -1,&t;&t;&t;&bslash;&n;&t;INIT_THREAD_IA32&t;&t;&t;&bslash;&n;&t;INIT_THREAD_PM&t;&t;&t;&t;&bslash;&n;&t;.dbr =&t;&t;{0, },&t;&t;&t;&bslash;&n;&t;.ibr =&t;&t;{0, },&t;&t;&t;&bslash;&n;&t;.fph =&t;&t;{{{{0}}}, }&t;&t;&bslash;&n;}
DECL|macro|start_thread
mdefine_line|#define start_thread(regs,new_ip,new_sp) do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;set_fs(USER_DS);&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;cr_ipsr = ((regs-&gt;cr_ipsr | (IA64_PSR_BITS_TO_SET | IA64_PSR_CPL))&t;&t;&bslash;&n;&t;&t;&t; &amp; ~(IA64_PSR_BITS_TO_CLEAR | IA64_PSR_RI | IA64_PSR_IS));&t;&t;&bslash;&n;&t;regs-&gt;cr_iip = new_ip;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;ar_rsc = 0xf;&t;&t;/* eager mode, privilege level 3 */&t;&t;&t;&bslash;&n;&t;regs-&gt;ar_rnat = 0;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;ar_bspstore = current-&gt;thread.rbs_bot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;ar_fpsr = FPSR_DEFAULT;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;loadrs = 0;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;r8 = current-&gt;mm-&gt;dumpable;&t;/* set &quot;don&squot;t zap registers&quot; flag */&t;&t;&bslash;&n;&t;regs-&gt;r12 = new_sp - 16;&t;/* allocate 16 byte scratch area */&t;&t;&t;&bslash;&n;&t;if (unlikely(!current-&gt;mm-&gt;dumpable)) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;/*&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t; * Zap scratch regs to avoid leaking bits between processes with different&t;&bslash;&n;&t;&t; * uid/privileges.&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t; */&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;regs-&gt;ar_pfs = 0; regs-&gt;b0 = 0; regs-&gt;pr = 0;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;regs-&gt;r1 = 0; regs-&gt;r9  = 0; regs-&gt;r11 = 0; regs-&gt;r13 = 0; regs-&gt;r15 = 0;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* Forward declarations, a strange C thing... */
r_struct
id|mm_struct
suffix:semicolon
r_struct
id|task_struct
suffix:semicolon
multiline_comment|/*&n; * Free all resources held by a thread. This is called after the&n; * parent of DEAD_TASK has collected the exit status of the task via&n; * wait().&n; */
DECL|macro|release_thread
mdefine_line|#define release_thread(dead_task)
multiline_comment|/* Prepare to copy thread state - unlazy all lazy status */
DECL|macro|prepare_to_copy
mdefine_line|#define prepare_to_copy(tsk)&t;do { } while (0)
multiline_comment|/*&n; * This is the mechanism for creating a new kernel thread.&n; *&n; * NOTE 1: Only a kernel-only process (ie the swapper or direct&n; * descendants who haven&squot;t done an &quot;execve()&quot;) should use this: it&n; * will work within a system call from a &quot;real&quot; process, but the&n; * process memory space will not be free&squot;d until both the parent and&n; * the child have exited.&n; *&n; * NOTE 2: This MUST NOT be an inlined function.  Otherwise, we get&n; * into trouble in init/main.c when the child thread returns to&n; * do_basic_setup() and the timing is such that free_initmem() has&n; * been called already.&n; */
r_extern
id|pid_t
id|kernel_thread
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
multiline_comment|/* Get wait channel for task P.  */
r_extern
r_int
r_int
id|get_wchan
(paren
r_struct
id|task_struct
op_star
id|p
)paren
suffix:semicolon
multiline_comment|/* Return instruction pointer of blocked task TSK.  */
DECL|macro|KSTK_EIP
mdefine_line|#define KSTK_EIP(tsk)&t;&t;&t;&t;&t;&bslash;&n;  ({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct pt_regs *_regs = ia64_task_regs(tsk);&t;&bslash;&n;&t;_regs-&gt;cr_iip + ia64_psr(_regs)-&gt;ri;&t;&t;&bslash;&n;  })
multiline_comment|/* Return stack pointer of blocked task TSK.  */
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk)  ((tsk)-&gt;thread.ksp)
r_extern
r_void
id|ia64_getreg_unknown_kr
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ia64_setreg_unknown_kr
(paren
r_void
)paren
suffix:semicolon
DECL|macro|ia64_get_kr
mdefine_line|#define ia64_get_kr(regnum)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long r = 0;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (regnum) {&t;&t;&t;&t;&t;&bslash;&n;&t;    case 0: r = ia64_getreg(_IA64_REG_AR_KR0); break;&t;&bslash;&n;&t;    case 1: r = ia64_getreg(_IA64_REG_AR_KR1); break;&t;&bslash;&n;&t;    case 2: r = ia64_getreg(_IA64_REG_AR_KR2); break;&t;&bslash;&n;&t;    case 3: r = ia64_getreg(_IA64_REG_AR_KR3); break;&t;&bslash;&n;&t;    case 4: r = ia64_getreg(_IA64_REG_AR_KR4); break;&t;&bslash;&n;&t;    case 5: r = ia64_getreg(_IA64_REG_AR_KR5); break;&t;&bslash;&n;&t;    case 6: r = ia64_getreg(_IA64_REG_AR_KR6); break;&t;&bslash;&n;&t;    case 7: r = ia64_getreg(_IA64_REG_AR_KR7); break;&t;&bslash;&n;&t;    default: ia64_getreg_unknown_kr(); break;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;r;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_set_kr
mdefine_line|#define ia64_set_kr(regnum, r) &t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (regnum) {&t;&t;&t;&t;&t;&bslash;&n;&t;    case 0: ia64_setreg(_IA64_REG_AR_KR0, r); break;&t;&bslash;&n;&t;    case 1: ia64_setreg(_IA64_REG_AR_KR1, r); break;&t;&bslash;&n;&t;    case 2: ia64_setreg(_IA64_REG_AR_KR2, r); break;&t;&bslash;&n;&t;    case 3: ia64_setreg(_IA64_REG_AR_KR3, r); break;&t;&bslash;&n;&t;    case 4: ia64_setreg(_IA64_REG_AR_KR4, r); break;&t;&bslash;&n;&t;    case 5: ia64_setreg(_IA64_REG_AR_KR5, r); break;&t;&bslash;&n;&t;    case 6: ia64_setreg(_IA64_REG_AR_KR6, r); break;&t;&bslash;&n;&t;    case 7: ia64_setreg(_IA64_REG_AR_KR7, r); break;&t;&bslash;&n;&t;    default: ia64_setreg_unknown_kr(); break;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/*&n; * The following three macros can&squot;t be inline functions because we don&squot;t have struct&n; * task_struct at this point.&n; */
multiline_comment|/* Return TRUE if task T owns the fph partition of the CPU we&squot;re running on. */
DECL|macro|ia64_is_local_fpu_owner
mdefine_line|#define ia64_is_local_fpu_owner(t)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct task_struct *__ia64_islfo_task = (t);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(__ia64_islfo_task-&gt;thread.last_fph_cpu == smp_processor_id()&t;&t;&t;&t;&bslash;&n;&t; &amp;&amp; __ia64_islfo_task == (struct task_struct *) ia64_get_kr(IA64_KR_FPU_OWNER));&t;&bslash;&n;})
multiline_comment|/* Mark task T as owning the fph partition of the CPU we&squot;re running on. */
DECL|macro|ia64_set_local_fpu_owner
mdefine_line|#define ia64_set_local_fpu_owner(t) do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct task_struct *__ia64_slfo_task = (t);&t;&t;&t;&t;&t;&bslash;&n;&t;__ia64_slfo_task-&gt;thread.last_fph_cpu = smp_processor_id();&t;&t;&t;&bslash;&n;&t;ia64_set_kr(IA64_KR_FPU_OWNER, (unsigned long) __ia64_slfo_task);&t;&t;&bslash;&n;} while (0)
multiline_comment|/* Mark the fph partition of task T as being invalid on all CPUs.  */
DECL|macro|ia64_drop_fpu
mdefine_line|#define ia64_drop_fpu(t)&t;((t)-&gt;thread.last_fph_cpu = -1)
r_extern
r_void
id|__ia64_init_fpu
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__ia64_save_fpu
(paren
r_struct
id|ia64_fpreg
op_star
id|fph
)paren
suffix:semicolon
r_extern
r_void
id|__ia64_load_fpu
(paren
r_struct
id|ia64_fpreg
op_star
id|fph
)paren
suffix:semicolon
r_extern
r_void
id|ia64_save_debug_regs
(paren
r_int
r_int
op_star
id|save_area
)paren
suffix:semicolon
r_extern
r_void
id|ia64_load_debug_regs
(paren
r_int
r_int
op_star
id|save_area
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IA32_SUPPORT
r_extern
r_void
id|ia32_save_state
(paren
r_struct
id|task_struct
op_star
id|task
)paren
suffix:semicolon
r_extern
r_void
id|ia32_load_state
(paren
r_struct
id|task_struct
op_star
id|task
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|ia64_fph_enable
mdefine_line|#define ia64_fph_enable()&t;do { ia64_rsm(IA64_PSR_DFH); ia64_srlz_d(); } while (0)
DECL|macro|ia64_fph_disable
mdefine_line|#define ia64_fph_disable()&t;do { ia64_ssm(IA64_PSR_DFH); ia64_srlz_d(); } while (0)
multiline_comment|/* load fp 0.0 into fph */
r_static
r_inline
r_void
DECL|function|ia64_init_fpu
id|ia64_init_fpu
(paren
r_void
)paren
(brace
id|ia64_fph_enable
c_func
(paren
)paren
suffix:semicolon
id|__ia64_init_fpu
c_func
(paren
)paren
suffix:semicolon
id|ia64_fph_disable
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* save f32-f127 at FPH */
r_static
r_inline
r_void
DECL|function|ia64_save_fpu
id|ia64_save_fpu
(paren
r_struct
id|ia64_fpreg
op_star
id|fph
)paren
(brace
id|ia64_fph_enable
c_func
(paren
)paren
suffix:semicolon
id|__ia64_save_fpu
c_func
(paren
id|fph
)paren
suffix:semicolon
id|ia64_fph_disable
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* load f32-f127 from FPH */
r_static
r_inline
r_void
DECL|function|ia64_load_fpu
id|ia64_load_fpu
(paren
r_struct
id|ia64_fpreg
op_star
id|fph
)paren
(brace
id|ia64_fph_enable
c_func
(paren
)paren
suffix:semicolon
id|__ia64_load_fpu
c_func
(paren
id|fph
)paren
suffix:semicolon
id|ia64_fph_disable
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_inline
id|__u64
DECL|function|ia64_clear_ic
id|ia64_clear_ic
(paren
r_void
)paren
(brace
id|__u64
id|psr
suffix:semicolon
id|psr
op_assign
id|ia64_getreg
c_func
(paren
id|_IA64_REG_PSR
)paren
suffix:semicolon
id|ia64_stop
c_func
(paren
)paren
suffix:semicolon
id|ia64_rsm
c_func
(paren
id|IA64_PSR_I
op_or
id|IA64_PSR_IC
)paren
suffix:semicolon
id|ia64_srlz_i
c_func
(paren
)paren
suffix:semicolon
r_return
id|psr
suffix:semicolon
)brace
multiline_comment|/*&n; * Restore the psr.&n; */
r_static
r_inline
r_void
DECL|function|ia64_set_psr
id|ia64_set_psr
(paren
id|__u64
id|psr
)paren
(brace
id|ia64_stop
c_func
(paren
)paren
suffix:semicolon
id|ia64_setreg
c_func
(paren
id|_IA64_REG_PSR_L
comma
id|psr
)paren
suffix:semicolon
id|ia64_srlz_d
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Insert a translation into an instruction and/or data translation&n; * register.&n; */
r_static
r_inline
r_void
DECL|function|ia64_itr
id|ia64_itr
(paren
id|__u64
id|target_mask
comma
id|__u64
id|tr_num
comma
id|__u64
id|vmaddr
comma
id|__u64
id|pte
comma
id|__u64
id|log_page_size
)paren
(brace
id|ia64_setreg
c_func
(paren
id|_IA64_REG_CR_ITIR
comma
(paren
id|log_page_size
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
id|ia64_setreg
c_func
(paren
id|_IA64_REG_CR_IFA
comma
id|vmaddr
)paren
suffix:semicolon
id|ia64_stop
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|target_mask
op_amp
l_int|0x1
)paren
id|ia64_itri
c_func
(paren
id|tr_num
comma
id|pte
)paren
suffix:semicolon
r_if
c_cond
(paren
id|target_mask
op_amp
l_int|0x2
)paren
id|ia64_itrd
c_func
(paren
id|tr_num
comma
id|pte
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Insert a translation into the instruction and/or data translation&n; * cache.&n; */
r_static
r_inline
r_void
DECL|function|ia64_itc
id|ia64_itc
(paren
id|__u64
id|target_mask
comma
id|__u64
id|vmaddr
comma
id|__u64
id|pte
comma
id|__u64
id|log_page_size
)paren
(brace
id|ia64_setreg
c_func
(paren
id|_IA64_REG_CR_ITIR
comma
(paren
id|log_page_size
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
id|ia64_setreg
c_func
(paren
id|_IA64_REG_CR_IFA
comma
id|vmaddr
)paren
suffix:semicolon
id|ia64_stop
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* as per EAS2.6, itc must be the last instruction in an instruction group */
r_if
c_cond
(paren
id|target_mask
op_amp
l_int|0x1
)paren
id|ia64_itci
c_func
(paren
id|pte
)paren
suffix:semicolon
r_if
c_cond
(paren
id|target_mask
op_amp
l_int|0x2
)paren
id|ia64_itcd
c_func
(paren
id|pte
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Purge a range of addresses from instruction and/or data translation&n; * register(s).&n; */
r_static
r_inline
r_void
DECL|function|ia64_ptr
id|ia64_ptr
(paren
id|__u64
id|target_mask
comma
id|__u64
id|vmaddr
comma
id|__u64
id|log_size
)paren
(brace
r_if
c_cond
(paren
id|target_mask
op_amp
l_int|0x1
)paren
id|ia64_ptri
c_func
(paren
id|vmaddr
comma
(paren
id|log_size
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|target_mask
op_amp
l_int|0x2
)paren
id|ia64_ptrd
c_func
(paren
id|vmaddr
comma
(paren
id|log_size
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Set the interrupt vector address.  The address must be suitably aligned (32KB).  */
r_static
r_inline
r_void
DECL|function|ia64_set_iva
id|ia64_set_iva
(paren
r_void
op_star
id|ivt_addr
)paren
(brace
id|ia64_setreg
c_func
(paren
id|_IA64_REG_CR_IVA
comma
(paren
id|__u64
)paren
id|ivt_addr
)paren
suffix:semicolon
id|ia64_srlz_i
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Set the page table address and control bits.  */
r_static
r_inline
r_void
DECL|function|ia64_set_pta
id|ia64_set_pta
(paren
id|__u64
id|pta
)paren
(brace
multiline_comment|/* Note: srlz.i implies srlz.d */
id|ia64_setreg
c_func
(paren
id|_IA64_REG_CR_PTA
comma
id|pta
)paren
suffix:semicolon
id|ia64_srlz_i
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ia64_eoi
id|ia64_eoi
(paren
r_void
)paren
(brace
id|ia64_setreg
c_func
(paren
id|_IA64_REG_CR_EOI
comma
l_int|0
)paren
suffix:semicolon
id|ia64_srlz_d
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|macro|cpu_relax
mdefine_line|#define cpu_relax()&t;ia64_hint(ia64_hint_pause)
r_static
r_inline
r_void
DECL|function|ia64_set_lrr0
id|ia64_set_lrr0
(paren
r_int
r_int
id|val
)paren
(brace
id|ia64_setreg
c_func
(paren
id|_IA64_REG_CR_LRR0
comma
id|val
)paren
suffix:semicolon
id|ia64_srlz_d
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ia64_set_lrr1
id|ia64_set_lrr1
(paren
r_int
r_int
id|val
)paren
(brace
id|ia64_setreg
c_func
(paren
id|_IA64_REG_CR_LRR1
comma
id|val
)paren
suffix:semicolon
id|ia64_srlz_d
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Given the address to which a spill occurred, return the unat bit&n; * number that corresponds to this address.&n; */
r_static
r_inline
id|__u64
DECL|function|ia64_unat_pos
id|ia64_unat_pos
(paren
r_void
op_star
id|spill_addr
)paren
(brace
r_return
(paren
(paren
id|__u64
)paren
id|spill_addr
op_rshift
l_int|3
)paren
op_amp
l_int|0x3f
suffix:semicolon
)brace
multiline_comment|/*&n; * Set the NaT bit of an integer register which was spilled at address&n; * SPILL_ADDR.  UNAT is the mask to be updated.&n; */
r_static
r_inline
r_void
DECL|function|ia64_set_unat
id|ia64_set_unat
(paren
id|__u64
op_star
id|unat
comma
r_void
op_star
id|spill_addr
comma
r_int
r_int
id|nat
)paren
(brace
id|__u64
id|bit
op_assign
id|ia64_unat_pos
c_func
(paren
id|spill_addr
)paren
suffix:semicolon
id|__u64
id|mask
op_assign
l_int|1UL
op_lshift
id|bit
suffix:semicolon
op_star
id|unat
op_assign
(paren
op_star
id|unat
op_amp
op_complement
id|mask
)paren
op_or
(paren
id|nat
op_lshift
id|bit
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Return saved PC of a blocked thread.&n; * Note that the only way T can block is through a call to schedule() -&gt; switch_to().&n; */
r_static
r_inline
r_int
r_int
DECL|function|thread_saved_pc
id|thread_saved_pc
(paren
r_struct
id|task_struct
op_star
id|t
)paren
(brace
r_struct
id|unw_frame_info
id|info
suffix:semicolon
r_int
r_int
id|ip
suffix:semicolon
id|unw_init_from_blocked_task
c_func
(paren
op_amp
id|info
comma
id|t
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unw_unwind
c_func
(paren
op_amp
id|info
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|unw_get_ip
c_func
(paren
op_amp
id|info
comma
op_amp
id|ip
)paren
suffix:semicolon
r_return
id|ip
suffix:semicolon
)brace
multiline_comment|/*&n; * Get the current instruction/program counter value.&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() &bslash;&n;&t;({ void *_pc; _pc = (void *)ia64_getreg(_IA64_REG_IP); _pc; })
r_static
r_inline
id|__u64
DECL|function|ia64_get_ivr
id|ia64_get_ivr
(paren
r_void
)paren
(brace
id|__u64
id|r
suffix:semicolon
id|ia64_srlz_d
c_func
(paren
)paren
suffix:semicolon
id|r
op_assign
id|ia64_getreg
c_func
(paren
id|_IA64_REG_CR_IVR
)paren
suffix:semicolon
id|ia64_srlz_d
c_func
(paren
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ia64_set_dbr
id|ia64_set_dbr
(paren
id|__u64
id|regnum
comma
id|__u64
id|value
)paren
(brace
id|__ia64_set_dbr
c_func
(paren
id|regnum
comma
id|value
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ITANIUM
id|ia64_srlz_d
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
r_static
r_inline
id|__u64
DECL|function|ia64_get_dbr
id|ia64_get_dbr
(paren
id|__u64
id|regnum
)paren
(brace
id|__u64
id|retval
suffix:semicolon
id|retval
op_assign
id|__ia64_get_dbr
c_func
(paren
id|regnum
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ITANIUM
id|ia64_srlz_d
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* XXX remove the handcoded version once we have a sufficiently clever compiler... */
macro_line|#ifdef SMART_COMPILER
DECL|macro|ia64_rotr
macro_line|# define ia64_rotr(w,n)&t;&t;&t;&t;&t;&t;&bslash;&n;  ({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 __ia64_rotr_w = (w), _n = (n);&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(__ia64_rotr_w &gt;&gt; _n) | (__ia64_rotr_w &lt;&lt; (64 - _n));&t;&bslash;&n;  })
macro_line|#else
DECL|macro|ia64_rotr
macro_line|# define ia64_rotr(w,n)&t;&t;&t;&t;&t;&bslash;&n;  ({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 __ia64_rotr_w;&t;&t;&t;&t;&bslash;&n;&t;__ia64_rotr_w = ia64_shrp((w), (w), (n));&t;&bslash;&n;&t;__ia64_rotr_w;&t;&t;&t;&t;&t;&bslash;&n;  })
macro_line|#endif
DECL|macro|ia64_rotl
mdefine_line|#define ia64_rotl(w,n)&t;ia64_rotr((w),(64)-(n))
multiline_comment|/*&n; * Take a mapped kernel address and return the equivalent address&n; * in the region 7 identity mapped virtual area.&n; */
r_static
r_inline
r_void
op_star
DECL|function|ia64_imva
id|ia64_imva
(paren
r_void
op_star
id|addr
)paren
(brace
r_void
op_star
id|result
suffix:semicolon
id|result
op_assign
(paren
r_void
op_star
)paren
id|ia64_tpa
c_func
(paren
id|addr
)paren
suffix:semicolon
r_return
id|__va
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
DECL|macro|ARCH_HAS_PREFETCH
mdefine_line|#define ARCH_HAS_PREFETCH
DECL|macro|ARCH_HAS_PREFETCHW
mdefine_line|#define ARCH_HAS_PREFETCHW
DECL|macro|ARCH_HAS_SPINLOCK_PREFETCH
mdefine_line|#define ARCH_HAS_SPINLOCK_PREFETCH
DECL|macro|PREFETCH_STRIDE
mdefine_line|#define PREFETCH_STRIDE 256
r_static
r_inline
r_void
DECL|function|prefetch
id|prefetch
(paren
r_const
r_void
op_star
id|x
)paren
(brace
id|ia64_lfetch
c_func
(paren
id|ia64_lfhint_none
comma
id|x
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|prefetchw
id|prefetchw
(paren
r_const
r_void
op_star
id|x
)paren
(brace
id|ia64_lfetch_excl
c_func
(paren
id|ia64_lfhint_none
comma
id|x
)paren
suffix:semicolon
)brace
DECL|macro|spin_lock_prefetch
mdefine_line|#define spin_lock_prefetch(x)&t;prefetchw(x)
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASM_IA64_PROCESSOR_H */
eof
