macro_line|#ifndef _ASM_IA64_SYSTEM_H
DECL|macro|_ASM_IA64_SYSTEM_H
mdefine_line|#define _ASM_IA64_SYSTEM_H
multiline_comment|/*&n; * System defines. Note that this is included both from .c and .S&n; * files, so it does only defines, not any C code.  This is based&n; * on information published in the Processor Abstraction Layer&n; * and the System Abstraction Layer manual.&n; *&n; * Copyright (C) 1998-2003 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; * Copyright (C) 1999 Asit Mallick &lt;asit.k.mallick@intel.com&gt;&n; * Copyright (C) 1999 Don Dugger &lt;don.dugger@intel.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/kregs.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pal.h&gt;
macro_line|#include &lt;asm/percpu.h&gt;
DECL|macro|GATE_ADDR
mdefine_line|#define GATE_ADDR&t;&t;__IA64_UL_CONST(0xa000000000000000)
multiline_comment|/*&n; * 0xa000000000000000+2*PERCPU_PAGE_SIZE&n; * - 0xa000000000000000+3*PERCPU_PAGE_SIZE remain unmapped (guard page)&n; */
DECL|macro|KERNEL_START
mdefine_line|#define KERNEL_START&t;&t; __IA64_UL_CONST(0xa000000100000000)
DECL|macro|PERCPU_ADDR
mdefine_line|#define PERCPU_ADDR&t;&t;(-PERCPU_PAGE_SIZE)
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
DECL|struct|pci_vector_struct
r_struct
id|pci_vector_struct
(brace
DECL|member|segment
id|__u16
id|segment
suffix:semicolon
multiline_comment|/* PCI Segment number */
DECL|member|bus
id|__u16
id|bus
suffix:semicolon
multiline_comment|/* PCI Bus number */
DECL|member|pci_id
id|__u32
id|pci_id
suffix:semicolon
multiline_comment|/* ACPI split 16 bits device, 16 bits function (see section 6.1.1) */
DECL|member|pin
id|__u8
id|pin
suffix:semicolon
multiline_comment|/* PCI PIN (0 = A, 1 = B, 2 = C, 3 = D) */
DECL|member|irq
id|__u32
id|irq
suffix:semicolon
multiline_comment|/* IRQ assigned */
)brace
suffix:semicolon
DECL|struct|ia64_boot_param
r_extern
r_struct
id|ia64_boot_param
(brace
DECL|member|command_line
id|__u64
id|command_line
suffix:semicolon
multiline_comment|/* physical address of command line arguments */
DECL|member|efi_systab
id|__u64
id|efi_systab
suffix:semicolon
multiline_comment|/* physical address of EFI system table */
DECL|member|efi_memmap
id|__u64
id|efi_memmap
suffix:semicolon
multiline_comment|/* physical address of EFI memory map */
DECL|member|efi_memmap_size
id|__u64
id|efi_memmap_size
suffix:semicolon
multiline_comment|/* size of EFI memory map */
DECL|member|efi_memdesc_size
id|__u64
id|efi_memdesc_size
suffix:semicolon
multiline_comment|/* size of an EFI memory map descriptor */
DECL|member|efi_memdesc_version
id|__u32
id|efi_memdesc_version
suffix:semicolon
multiline_comment|/* memory descriptor version */
r_struct
(brace
DECL|member|num_cols
id|__u16
id|num_cols
suffix:semicolon
multiline_comment|/* number of columns on console output device */
DECL|member|num_rows
id|__u16
id|num_rows
suffix:semicolon
multiline_comment|/* number of rows on console output device */
DECL|member|orig_x
id|__u16
id|orig_x
suffix:semicolon
multiline_comment|/* cursor&squot;s x position */
DECL|member|orig_y
id|__u16
id|orig_y
suffix:semicolon
multiline_comment|/* cursor&squot;s y position */
DECL|member|console_info
)brace
id|console_info
suffix:semicolon
DECL|member|fpswa
id|__u64
id|fpswa
suffix:semicolon
multiline_comment|/* physical address of the fpswa interface */
DECL|member|initrd_start
id|__u64
id|initrd_start
suffix:semicolon
DECL|member|initrd_size
id|__u64
id|initrd_size
suffix:semicolon
)brace
op_star
id|ia64_boot_param
suffix:semicolon
multiline_comment|/*&n; * Macros to force memory ordering.  In these descriptions, &quot;previous&quot;&n; * and &quot;subsequent&quot; refer to program order; &quot;visible&quot; means that all&n; * architecturally visible effects of a memory access have occurred&n; * (at a minimum, this means the memory has been read or written).&n; *&n; *   wmb():&t;Guarantees that all preceding stores to memory-&n; *&t;&t;like regions are visible before any subsequent&n; *&t;&t;stores and that all following stores will be&n; *&t;&t;visible only after all previous stores.&n; *   rmb():&t;Like wmb(), but for reads.&n; *   mb():&t;wmb()/rmb() combo, i.e., all previous memory&n; *&t;&t;accesses are visible before all subsequent&n; *&t;&t;accesses and vice versa.  This is also known as&n; *&t;&t;a &quot;fence.&quot;&n; *&n; * Note: &quot;mb()&quot; and its variants cannot be used as a fence to order&n; * accesses to memory mapped I/O registers.  For that, mf.a needs to&n; * be used.  However, we don&squot;t want to always use mf.a because (a)&n; * it&squot;s (presumably) much slower than mf and (b) mf.a is supported for&n; * sequential memory pages only.&n; */
DECL|macro|mb
mdefine_line|#define mb()&t;ia64_mf()
DECL|macro|rmb
mdefine_line|#define rmb()&t;mb()
DECL|macro|wmb
mdefine_line|#define wmb()&t;mb()
DECL|macro|read_barrier_depends
mdefine_line|#define read_barrier_depends()&t;do { } while(0)
macro_line|#ifdef CONFIG_SMP
DECL|macro|smp_mb
macro_line|# define smp_mb()&t;mb()
DECL|macro|smp_rmb
macro_line|# define smp_rmb()&t;rmb()
DECL|macro|smp_wmb
macro_line|# define smp_wmb()&t;wmb()
DECL|macro|smp_read_barrier_depends
macro_line|# define smp_read_barrier_depends()&t;read_barrier_depends()
macro_line|#else
DECL|macro|smp_mb
macro_line|# define smp_mb()&t;barrier()
DECL|macro|smp_rmb
macro_line|# define smp_rmb()&t;barrier()
DECL|macro|smp_wmb
macro_line|# define smp_wmb()&t;barrier()
DECL|macro|smp_read_barrier_depends
macro_line|# define smp_read_barrier_depends()&t;do { } while(0)
macro_line|#endif
multiline_comment|/*&n; * XXX check on these---I suspect what Linus really wants here is&n; * acquire vs release semantics but we can&squot;t discuss this stuff with&n; * Linus just yet.  Grrr...&n; */
DECL|macro|set_mb
mdefine_line|#define set_mb(var, value)&t;do { (var) = (value); mb(); } while (0)
DECL|macro|set_wmb
mdefine_line|#define set_wmb(var, value)&t;do { (var) = (value); mb(); } while (0)
DECL|macro|safe_halt
mdefine_line|#define safe_halt()         ia64_pal_halt_light()    /* PAL_HALT_LIGHT */
multiline_comment|/*&n; * The group barrier in front of the rsm &amp; ssm are necessary to ensure&n; * that none of the previous instructions in the same group are&n; * affected by the rsm/ssm.&n; */
multiline_comment|/* For spinlocks etc */
multiline_comment|/*&n; * - clearing psr.i is implicitly serialized (visible by next insn)&n; * - setting psr.i requires data serialization&n; * - we need a stop-bit before reading PSR because we sometimes&n; *   write a floating-point register right before reading the PSR&n; *   and that writes to PSR.mfl&n; */
DECL|macro|__local_irq_save
mdefine_line|#define __local_irq_save(x)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ia64_stop();&t;&t;&t;&t;&bslash;&n;&t;(x) = ia64_getreg(_IA64_REG_PSR);&t;&bslash;&n;&t;ia64_stop();&t;&t;&t;&t;&bslash;&n;&t;ia64_rsm(IA64_PSR_I);&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|__local_irq_disable
mdefine_line|#define __local_irq_disable()&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ia64_stop();&t;&t;&t;&t;&bslash;&n;&t;ia64_rsm(IA64_PSR_I);&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|__local_irq_restore
mdefine_line|#define __local_irq_restore(x)&t;ia64_intrin_local_irq_restore((x) &amp; IA64_PSR_I)
macro_line|#ifdef CONFIG_IA64_DEBUG_IRQ
r_extern
r_int
r_int
id|last_cli_ip
suffix:semicolon
DECL|macro|__save_ip
macro_line|# define __save_ip()&t;&t;last_cli_ip = ia64_getreg(_IA64_REG_IP)
DECL|macro|local_irq_save
macro_line|# define local_irq_save(x)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long psr;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__local_irq_save(psr);&t;&t;&t;&t;&t;&bslash;&n;&t;if (psr &amp; IA64_PSR_I)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__save_ip();&t;&t;&t;&t;&t;&bslash;&n;&t;(x) = psr;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|local_irq_disable
macro_line|# define local_irq_disable()&t;do { unsigned long x; local_irq_save(x); } while (0)
DECL|macro|local_irq_restore
macro_line|# define local_irq_restore(x)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long old_psr, psr = (x);&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;local_save_flags(old_psr);&t;&t;&t;&t;&bslash;&n;&t;__local_irq_restore(psr);&t;&t;&t;&t;&bslash;&n;&t;if ((old_psr &amp; IA64_PSR_I) &amp;&amp; !(psr &amp; IA64_PSR_I))&t;&bslash;&n;&t;&t;__save_ip();&t;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#else /* !CONFIG_IA64_DEBUG_IRQ */
DECL|macro|local_irq_save
macro_line|# define local_irq_save(x)&t;__local_irq_save(x)
DECL|macro|local_irq_disable
macro_line|# define local_irq_disable()&t;__local_irq_disable()
DECL|macro|local_irq_restore
macro_line|# define local_irq_restore(x)&t;__local_irq_restore(x)
macro_line|#endif /* !CONFIG_IA64_DEBUG_IRQ */
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable()&t;({ ia64_stop(); ia64_ssm(IA64_PSR_I); ia64_srlz_d(); })
DECL|macro|local_save_flags
mdefine_line|#define local_save_flags(flags)&t;({ ia64_stop(); (flags) = ia64_getreg(_IA64_REG_PSR); })
DECL|macro|irqs_disabled
mdefine_line|#define irqs_disabled()&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __ia64_id_flags;&t;&t;&bslash;&n;&t;local_save_flags(__ia64_id_flags);&t;&bslash;&n;&t;(__ia64_id_flags &amp; IA64_PSR_I) == 0;&t;&bslash;&n;})
macro_line|#ifdef __KERNEL__
DECL|macro|prepare_to_switch
mdefine_line|#define prepare_to_switch()    do { } while(0)
macro_line|#ifdef CONFIG_IA32_SUPPORT
DECL|macro|IS_IA32_PROCESS
macro_line|# define IS_IA32_PROCESS(regs)&t;(ia64_psr(regs)-&gt;is != 0)
macro_line|#else
DECL|macro|IS_IA32_PROCESS
macro_line|# define IS_IA32_PROCESS(regs)&t;&t;0
r_struct
id|task_struct
suffix:semicolon
DECL|function|ia32_save_state
r_static
r_inline
r_void
DECL|function|ia32_load_state
r_static
r_inline
r_void
macro_line|#endif
multiline_comment|/*&n; * Context switch from one thread to another.  If the two threads have&n; * different address spaces, schedule() has already taken care of&n; * switching to the new address space by calling switch_mm().&n; *&n; * Disabling access to the fph partition and the debug-register&n; * context switch MUST be done before calling ia64_switch_to() since a&n; * newly created thread returns directly to&n; * ia64_ret_from_syscall_clear_r8.&n; */
r_extern
r_struct
id|task_struct
op_star
id|ia64_switch_to
(paren
r_void
op_star
id|next_task
)paren
suffix:semicolon
r_struct
id|task_struct
suffix:semicolon
r_extern
r_void
id|ia64_save_extra
(paren
r_struct
id|task_struct
op_star
id|task
)paren
suffix:semicolon
r_extern
r_void
id|ia64_load_extra
(paren
r_struct
id|task_struct
op_star
id|task
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PERFMON
id|DECLARE_PER_CPU
c_func
(paren
r_int
r_int
comma
id|pfm_syst_info
)paren
suffix:semicolon
DECL|macro|PERFMON_IS_SYSWIDE
macro_line|# define PERFMON_IS_SYSWIDE() (__get_cpu_var(pfm_syst_info) &amp; 0x1)
macro_line|#else
DECL|macro|PERFMON_IS_SYSWIDE
macro_line|# define PERFMON_IS_SYSWIDE() (0)
macro_line|#endif
DECL|macro|IA64_HAS_EXTRA_STATE
mdefine_line|#define IA64_HAS_EXTRA_STATE(t)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;((t)-&gt;thread.flags &amp; (IA64_THREAD_DBG_VALID|IA64_THREAD_PM_VALID)&t;&bslash;&n;&t; || IS_IA32_PROCESS(ia64_task_regs(t)) || PERFMON_IS_SYSWIDE())
DECL|macro|__switch_to
mdefine_line|#define __switch_to(prev,next,last) do {&t;&t;&t;&t;&t;&t;&t; &bslash;&n;&t;if (IA64_HAS_EXTRA_STATE(prev))&t;&t;&t;&t;&t;&t;&t;&t; &bslash;&n;&t;&t;ia64_save_extra(prev);&t;&t;&t;&t;&t;&t;&t;&t; &bslash;&n;&t;if (IA64_HAS_EXTRA_STATE(next))&t;&t;&t;&t;&t;&t;&t;&t; &bslash;&n;&t;&t;ia64_load_extra(next);&t;&t;&t;&t;&t;&t;&t;&t; &bslash;&n;&t;ia64_psr(ia64_task_regs(next))-&gt;dfh = !ia64_is_local_fpu_owner(next);&t;&t;&t; &bslash;&n;&t;(last) = ia64_switch_to((next));&t;&t;&t;&t;&t;&t;&t; &bslash;&n;} while (0)
macro_line|#ifdef CONFIG_SMP
multiline_comment|/*&n; * In the SMP case, we save the fph state when context-switching away from a thread that&n; * modified fph.  This way, when the thread gets scheduled on another CPU, the CPU can&n; * pick up the state from task-&gt;thread.fph, avoiding the complication of having to fetch&n; * the latest fph state from another CPU.  In other words: eager save, lazy restore.&n; */
DECL|macro|switch_to
macro_line|# define switch_to(prev,next,last) do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (ia64_psr(ia64_task_regs(prev))-&gt;mfh &amp;&amp; ia64_is_local_fpu_owner(prev)) {&t;&t;&t;&t;&bslash;&n;&t;&t;ia64_psr(ia64_task_regs(prev))-&gt;mfh = 0;&t;&t;&t;&bslash;&n;&t;&t;(prev)-&gt;thread.flags |= IA64_THREAD_FPH_VALID;&t;&t;&t;&bslash;&n;&t;&t;__ia64_save_fpu((prev)-&gt;thread.fph);&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__switch_to(prev, next, last);&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#else
DECL|macro|switch_to
macro_line|# define switch_to(prev,next,last)&t;__switch_to(prev, next, last)
macro_line|#endif
multiline_comment|/*&n; * On IA-64, we don&squot;t want to hold the runqueue&squot;s lock during the low-level context-switch,&n; * because that could cause a deadlock.  Here is an example by Erich Focht:&n; *&n; * Example:&n; * CPU#0:&n; * schedule()&n; *    -&gt; spin_lock_irq(&amp;rq-&gt;lock)&n; *    -&gt; context_switch()&n; *       -&gt; wrap_mmu_context()&n; *          -&gt; read_lock(&amp;tasklist_lock)&n; *&n; * CPU#1:&n; * sys_wait4() or release_task() or forget_original_parent()&n; *    -&gt; write_lock(&amp;tasklist_lock)&n; *    -&gt; do_notify_parent()&n; *       -&gt; wake_up_parent()&n; *          -&gt; try_to_wake_up()&n; *             -&gt; spin_lock_irq(&amp;parent_rq-&gt;lock)&n; *&n; * If the parent&squot;s rq happens to be on CPU#0, we&squot;ll wait for the rq-&gt;lock&n; * of that CPU which will not be released, because there we wait for the&n; * tasklist_lock to become available.&n; */
DECL|macro|prepare_arch_switch
mdefine_line|#define prepare_arch_switch(rq, next)&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;spin_lock(&amp;(next)-&gt;switch_lock);&t;&bslash;&n;&t;spin_unlock(&amp;(rq)-&gt;lock);&t;&t;&bslash;&n;} while (0)
DECL|macro|finish_arch_switch
mdefine_line|#define finish_arch_switch(rq, prev)&t;spin_unlock_irq(&amp;(prev)-&gt;switch_lock)
DECL|macro|task_running
mdefine_line|#define task_running(rq, p) &t;&t;((rq)-&gt;curr == (p) || spin_is_locked(&amp;(p)-&gt;switch_lock))
DECL|macro|ia64_platform_is
mdefine_line|#define ia64_platform_is(x) (strcmp(x, platform_name) == 0)
r_void
id|cpu_idle_wait
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _ASM_IA64_SYSTEM_H */
eof
