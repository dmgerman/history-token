multiline_comment|/*&n; * include/asm-parisc/processor.h&n; *&n; * Copyright (C) 1994 Linus Torvalds&n; * Copyright (C) 2001 Grant Grundler&n; */
macro_line|#ifndef __ASM_PARISC_PROCESSOR_H
DECL|macro|__ASM_PARISC_PROCESSOR_H
mdefine_line|#define __ASM_PARISC_PROCESSOR_H
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pdc.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#endif /* __ASSEMBLY__ */
DECL|macro|KERNEL_STACK_SIZE
mdefine_line|#define KERNEL_STACK_SIZE &t;(4*PAGE_SIZE)
multiline_comment|/*&n; * Default implementation of macro that returns current&n; * instruction pointer (&quot;program counter&quot;).&n; */
multiline_comment|/* We cannot use MFIA as it was added for PA2.0 - prumpf&n;&n;   At one point there were no &quot;0f/0b&quot; type local symbols in gas for&n;   PA-RISC.  This is no longer true, but this still seems like the&n;   nicest way to implement this. */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() ({ void *pc; __asm__(&quot;&bslash;n&bslash;tblr 0,%0&bslash;n&bslash;tnop&quot;:&quot;=r&quot; (pc)); pc; })
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE               (current-&gt;thread.task_size)
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE      (current-&gt;thread.map_base)
DECL|macro|DEFAULT_TASK_SIZE32
mdefine_line|#define DEFAULT_TASK_SIZE32&t;(0xFFF00000UL)
DECL|macro|DEFAULT_MAP_BASE32
mdefine_line|#define DEFAULT_MAP_BASE32&t;(0x40000000UL)
macro_line|#ifdef __LP64__
DECL|macro|DEFAULT_TASK_SIZE
mdefine_line|#define DEFAULT_TASK_SIZE       (MAX_ADDRESS-0xf000000)
DECL|macro|DEFAULT_MAP_BASE
mdefine_line|#define DEFAULT_MAP_BASE        (0x200000000UL)
macro_line|#else
DECL|macro|DEFAULT_TASK_SIZE
mdefine_line|#define DEFAULT_TASK_SIZE&t;DEFAULT_TASK_SIZE32
DECL|macro|DEFAULT_MAP_BASE
mdefine_line|#define DEFAULT_MAP_BASE&t;DEFAULT_MAP_BASE32
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Data detected about CPUs at boot time which is the same for all CPU&squot;s.&n; * HP boxes are SMP - ie identical processors.&n; *&n; * FIXME: some CPU rev info may be processor specific...&n; */
DECL|struct|system_cpuinfo_parisc
r_struct
id|system_cpuinfo_parisc
(brace
DECL|member|cpu_count
r_int
r_int
id|cpu_count
suffix:semicolon
DECL|member|cpu_hz
r_int
r_int
id|cpu_hz
suffix:semicolon
DECL|member|hversion
r_int
r_int
id|hversion
suffix:semicolon
DECL|member|sversion
r_int
r_int
id|sversion
suffix:semicolon
DECL|member|cpu_type
r_enum
id|cpu_type
id|cpu_type
suffix:semicolon
r_struct
(brace
DECL|member|model
r_struct
id|pdc_model
id|model
suffix:semicolon
DECL|member|versions
r_int
r_int
id|versions
suffix:semicolon
DECL|member|cpuid
r_int
r_int
id|cpuid
suffix:semicolon
DECL|member|capabilities
r_int
r_int
id|capabilities
suffix:semicolon
DECL|member|sys_model_name
r_char
id|sys_model_name
(braket
l_int|81
)braket
suffix:semicolon
multiline_comment|/* PDC-ROM returnes this model name */
DECL|member|pdc
)brace
id|pdc
suffix:semicolon
DECL|member|cpu_name
r_char
op_star
id|cpu_name
suffix:semicolon
multiline_comment|/* e.g. &quot;PA7300LC (PCX-L2)&quot; */
DECL|member|family_name
r_char
op_star
id|family_name
suffix:semicolon
multiline_comment|/* e.g. &quot;1.1e&quot; */
)brace
suffix:semicolon
multiline_comment|/* Per CPU data structure - ie varies per CPU.  */
DECL|struct|cpuinfo_parisc
r_struct
id|cpuinfo_parisc
(brace
DECL|member|it_value
r_int
r_int
id|it_value
suffix:semicolon
multiline_comment|/* Interval Timer at last timer Intr */
DECL|member|it_delta
r_int
r_int
id|it_delta
suffix:semicolon
multiline_comment|/* Interval delta (tic_10ms / HZ * 100) */
DECL|member|irq_count
r_int
r_int
id|irq_count
suffix:semicolon
multiline_comment|/* number of IRQ&squot;s since boot */
DECL|member|irq_max_cr16
r_int
r_int
id|irq_max_cr16
suffix:semicolon
multiline_comment|/* longest time to handle a single IRQ */
DECL|member|cpuid
r_int
r_int
id|cpuid
suffix:semicolon
multiline_comment|/* aka slot_number or set to NO_PROC_ID */
DECL|member|hpa
r_int
r_int
id|hpa
suffix:semicolon
multiline_comment|/* Host Physical address */
DECL|member|txn_addr
r_int
r_int
id|txn_addr
suffix:semicolon
multiline_comment|/* MMIO addr of EIR or id_eid */
macro_line|#ifdef CONFIG_SMP
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* synchronization for ipi&squot;s */
DECL|member|pending_ipi
r_int
r_int
id|pending_ipi
suffix:semicolon
multiline_comment|/* bitmap of type ipi_message_type */
DECL|member|ipi_count
r_int
r_int
id|ipi_count
suffix:semicolon
multiline_comment|/* number ipi Interrupts */
macro_line|#endif
DECL|member|bh_count
r_int
r_int
id|bh_count
suffix:semicolon
multiline_comment|/* number of times bh was invoked */
DECL|member|prof_counter
r_int
r_int
id|prof_counter
suffix:semicolon
multiline_comment|/* per CPU profiling support */
DECL|member|prof_multiplier
r_int
r_int
id|prof_multiplier
suffix:semicolon
multiline_comment|/* per CPU profiling support */
DECL|member|fp_rev
r_int
r_int
id|fp_rev
suffix:semicolon
DECL|member|fp_model
r_int
r_int
id|fp_model
suffix:semicolon
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
DECL|member|dev
r_struct
id|parisc_device
op_star
id|dev
suffix:semicolon
DECL|member|loops_per_jiffy
r_int
r_int
id|loops_per_jiffy
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|system_cpuinfo_parisc
id|boot_cpu_data
suffix:semicolon
r_extern
r_struct
id|cpuinfo_parisc
id|cpu_data
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|macro|current_cpu_data
mdefine_line|#define current_cpu_data cpu_data[smp_processor_id()]
DECL|macro|CPU_HVERSION
mdefine_line|#define CPU_HVERSION ((boot_cpu_data.hversion &gt;&gt; 4) &amp; 0x0FFF)
r_typedef
r_struct
(brace
DECL|member|seg
r_int
id|seg
suffix:semicolon
DECL|typedef|mm_segment_t
)brace
id|mm_segment_t
suffix:semicolon
DECL|macro|ARCH_MIN_TASKALIGN
mdefine_line|#define ARCH_MIN_TASKALIGN&t;8
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
DECL|member|regs
r_struct
id|pt_regs
id|regs
suffix:semicolon
DECL|member|task_size
r_int
r_int
id|task_size
suffix:semicolon
DECL|member|map_base
r_int
r_int
id|map_base
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Thread struct flags. */
DECL|macro|PARISC_KERNEL_DEATH
mdefine_line|#define PARISC_KERNEL_DEATH&t;(1UL &lt;&lt; 31)&t;/* see die_if_kernel()... */
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD { &bslash;&n;&t;regs:&t;{&t;gr: { 0, }, &bslash;&n;&t;&t;&t;fr: { 0, }, &bslash;&n;&t;&t;&t;sr: { 0, }, &bslash;&n;&t;&t;&t;iasq: { 0, }, &bslash;&n;&t;&t;&t;iaoq: { 0, }, &bslash;&n;&t;&t;&t;cr27: 0, &bslash;&n;&t;&t;}, &bslash;&n;&t;task_size:      DEFAULT_TASK_SIZE, &bslash;&n;&t;map_base:       DEFAULT_MAP_BASE, &bslash;&n;&t;flags:          0 &bslash;&n;&t;}
multiline_comment|/*&n; * Return saved PC of a blocked thread.  This is used by ps mostly.&n; */
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
r_void
id|show_trace
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
r_int
op_star
id|stack
)paren
suffix:semicolon
multiline_comment|/*&n; * Start user thread in another space.&n; *&n; * Note that we set both the iaoq and r31 to the new pc. When&n; * the kernel initially calls execve it will return through an&n; * rfi path that will use the values in the iaoq. The execve&n; * syscall path will return through the gateway page, and&n; * that uses r31 to branch to.&n; *&n; * For ELF we clear r23, because the dynamic linker uses it to pass&n; * the address of the finalizer function.&n; *&n; * We also initialize sr3 to an illegal value (illegal for our&n; * implementation, not for the architecture).&n; */
DECL|typedef|elf_caddr_t
r_typedef
r_int
r_int
id|elf_caddr_t
suffix:semicolon
DECL|macro|start_thread_som
mdefine_line|#define start_thread_som(regs, new_pc, new_sp) do {&t;&bslash;&n;&t;unsigned long *sp = (unsigned long *)new_sp;&t;&bslash;&n;&t;__u32 spaceid = (__u32)current-&gt;mm-&gt;context;&t;&bslash;&n;&t;unsigned long pc = (unsigned long)new_pc;&t;&bslash;&n;&t;/* offset pc for priv. level */&t;&t;&t;&bslash;&n;&t;pc |= 3;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;set_fs(USER_DS);&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;iasq[0] = spaceid;&t;&t;&t;&bslash;&n;&t;regs-&gt;iasq[1] = spaceid;&t;&t;&t;&bslash;&n;&t;regs-&gt;iaoq[0] = pc;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;iaoq[1] = pc + 4;                         &bslash;&n;&t;regs-&gt;sr[2] = LINUX_GATEWAY_SPACE;              &bslash;&n;&t;regs-&gt;sr[3] = 0xffff;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;sr[4] = spaceid;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;sr[5] = spaceid;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;sr[6] = spaceid;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;sr[7] = spaceid;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;gr[ 0] = USER_PSW;                        &bslash;&n;&t;regs-&gt;gr[30] = ((new_sp)+63)&amp;~63;&t;&t;&bslash;&n;&t;regs-&gt;gr[31] = pc;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;get_user(regs-&gt;gr[26],&amp;sp[0]);&t;&t;&t;&bslash;&n;&t;get_user(regs-&gt;gr[25],&amp;sp[-1]); &t;&t;&bslash;&n;&t;get_user(regs-&gt;gr[24],&amp;sp[-2]); &t;&t;&bslash;&n;&t;get_user(regs-&gt;gr[23],&amp;sp[-3]); &t;&t;&bslash;&n;} while(0)
multiline_comment|/* The ELF abi wants things done a &quot;wee bit&quot; differently than&n; * som does.  Supporting this behavior here avoids&n; * having our own version of create_elf_tables.&n; *&n; * Oh, and yes, that is not a typo, we are really passing argc in r25&n; * and argv in r24 (rather than r26 and r25).  This is because that&squot;s&n; * where __libc_start_main wants them.&n; *&n; * Duplicated from dl-machine.h for the benefit of readers:&n; *&n; *  Our initial stack layout is rather different from everyone else&squot;s&n; *  due to the unique PA-RISC ABI.  As far as I know it looks like&n; *  this:&n;&n;   -----------------------------------  (user startup code creates this frame)&n;   |         32 bytes of magic       |&n;   |---------------------------------|&n;   | 32 bytes argument/sp save area  |&n;   |---------------------------------| (bprm-&gt;p)&n;   |&t;    ELF auxiliary info&t;     |&n;   |         (up to 28 words)        |&n;   |---------------------------------|&n;   |&t;&t;   NULL&t;&t;     |&n;   |---------------------------------|&n;   |&t;   Environment pointers&t;     |&n;   |---------------------------------|&n;   |&t;&t;   NULL&t;&t;     |&n;   |---------------------------------|&n;   |        Argument pointers        |&n;   |---------------------------------| &lt;- argv&n;   |          argc (1 word)          |&n;   |---------------------------------| &lt;- bprm-&gt;exec (HACK!)&n;   |         N bytes of slack        |&n;   |---------------------------------|&n;   |&t;filename passed to execve    |&n;   |---------------------------------| (mm-&gt;env_end)&n;   |           env strings           |&n;   |---------------------------------| (mm-&gt;env_start, mm-&gt;arg_end)&n;   |           arg strings           |&n;   |---------------------------------|&n;   | additional faked arg strings if |&n;   | we&squot;re invoked via binfmt_script |&n;   |---------------------------------| (mm-&gt;arg_start)&n;   stack base is at TASK_SIZE - rlim_max.&n;&n;on downward growing arches, it looks like this:&n;   stack base at TASK_SIZE&n;   | filename passed to execve&n;   | env strings&n;   | arg strings&n;   | faked arg strings&n;   | slack&n;   | ELF&n;   | envps&n;   | argvs&n;   | argc&n;&n; *  The pleasant part of this is that if we need to skip arguments we&n; *  can just decrement argc and move argv, because the stack pointer&n; *  is utterly unrelated to the location of the environment and&n; *  argument vectors.&n; *&n; * Note that the S/390 people took the easy way out and hacked their&n; * GCC to make the stack grow downwards.&n; *&n; * Final Note: For entry from syscall, the W (wide) bit of the PSW&n; * is stuffed into the lowest bit of the user sp (%r30), so we fill&n; * it in here from the current-&gt;personality&n; */
macro_line|#ifdef __LP64__
DECL|macro|USER_WIDE_MODE
mdefine_line|#define USER_WIDE_MODE&t;(personality(current-&gt;personality) == PER_LINUX)
macro_line|#else
DECL|macro|USER_WIDE_MODE
mdefine_line|#define USER_WIDE_MODE&t;0
macro_line|#endif
DECL|macro|start_thread
mdefine_line|#define start_thread(regs, new_pc, new_sp) do {&t;&t;&bslash;&n;&t;elf_addr_t *sp = (elf_addr_t *)new_sp;&t;&t;&bslash;&n;&t;__u32 spaceid = (__u32)current-&gt;mm-&gt;context;&t;&bslash;&n;&t;elf_addr_t pc = (elf_addr_t)new_pc | 3;&t;&t;&bslash;&n;&t;elf_caddr_t *argv = (elf_caddr_t *)bprm-&gt;exec + 1;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;set_fs(USER_DS);&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;iasq[0] = spaceid;&t;&t;&t;&bslash;&n;&t;regs-&gt;iasq[1] = spaceid;&t;&t;&t;&bslash;&n;&t;regs-&gt;iaoq[0] = pc;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;iaoq[1] = pc + 4;                         &bslash;&n;&t;regs-&gt;sr[2] = LINUX_GATEWAY_SPACE;              &bslash;&n;&t;regs-&gt;sr[3] = 0xffff;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;sr[4] = spaceid;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;sr[5] = spaceid;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;sr[6] = spaceid;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;sr[7] = spaceid;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;gr[ 0] = USER_PSW | (USER_WIDE_MODE ? PSW_W : 0); &bslash;&n;&t;regs-&gt;fr[ 0] = 0LL;                            &t;&bslash;&n;&t;regs-&gt;fr[ 1] = 0LL;                            &t;&bslash;&n;&t;regs-&gt;fr[ 2] = 0LL;                            &t;&bslash;&n;&t;regs-&gt;fr[ 3] = 0LL;                            &t;&bslash;&n;&t;regs-&gt;gr[30] = (((unsigned long)sp + 63) &amp;~ 63) | (USER_WIDE_MODE ? 1 : 0); &bslash;&n;&t;regs-&gt;gr[31] = pc;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;get_user(regs-&gt;gr[25], (argv - 1));&t;&t;&bslash;&n;&t;regs-&gt;gr[24] = (long) argv;&t;&t;&t;&bslash;&n;&t;regs-&gt;gr[23] = 0;&t;&t;&t;&t;&bslash;&n;} while(0)
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
multiline_comment|/* Prepare to copy thread state - unlazy all lazy status */
DECL|macro|prepare_to_copy
mdefine_line|#define prepare_to_copy(tsk)&t;do { } while (0)
r_extern
r_void
id|map_hpux_gateway_page
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
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
mdefine_line|#define KSTK_EIP(tsk)&t;((tsk)-&gt;thread.regs.iaoq[0])
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk)&t;((tsk)-&gt;thread.regs.gr[30])
multiline_comment|/*&n; * PA 2.0 defines data prefetch instructions on page 6-11 of the Kane book.&n; * In addition, many implementations do hardware prefetching of both&n; * instructions and data.&n; *&n; * PA7300LC (page 14-4 of the ERS) also implements prefetching by a load&n; * to gr0 but not in a way that Linux can use.  If the load would cause an&n; * interruption (eg due to prefetching 0), it is suppressed on PA2.0&n; * processors, but not on 7300LC.&n; */
macro_line|#ifdef  CONFIG_PREFETCH
DECL|macro|ARCH_HAS_PREFETCH
mdefine_line|#define ARCH_HAS_PREFETCH
DECL|macro|ARCH_HAS_PREFETCHW
mdefine_line|#define ARCH_HAS_PREFETCHW
DECL|function|prefetch
r_extern
r_inline
r_void
id|prefetch
c_func
(paren
r_const
r_void
op_star
id|addr
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;ldw 0(%0), %%r0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|prefetchw
r_extern
r_inline
r_void
id|prefetchw
c_func
(paren
r_const
r_void
op_star
id|addr
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;ldd 0(%0), %%r0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|macro|cpu_relax
mdefine_line|#define cpu_relax()&t;barrier()
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* __ASM_PARISC_PROCESSOR_H */
eof
