multiline_comment|/*&n; * SMP boot-related support&n; *&n; * Copyright (C) 1998-2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&n; * 01/05/16 Rohit Seth &lt;rohit.seth@intel.com&gt;&t;Moved SMP booting functions from smp.c to here.&n; * 01/04/27 David Mosberger &lt;davidm@hpl.hp.com&gt;&t;Added ITC synching code.&n; * 02/07/31 David Mosberger &lt;davidm@hpl.hp.com&gt;&t;Switch over to hotplug-CPU boot-sequence.&n; *&t;&t;&t;&t;&t;&t;smp_boot_cpus()/smp_commence() is replaced by&n; *&t;&t;&t;&t;&t;&t;smp_prepare_cpus()/__cpu_up()/smp_cpus_done().&n; */
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;asm/current.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/efi.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/mca.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/unistd.h&gt;
DECL|macro|SMP_DEBUG
mdefine_line|#define SMP_DEBUG 0
macro_line|#if SMP_DEBUG
DECL|macro|Dprintk
mdefine_line|#define Dprintk(x...)  printk(x)
macro_line|#else
DECL|macro|Dprintk
mdefine_line|#define Dprintk(x...)
macro_line|#endif
multiline_comment|/*&n; * ITC synchronization related stuff:&n; */
DECL|macro|MASTER
mdefine_line|#define MASTER&t;0
DECL|macro|SLAVE
mdefine_line|#define SLAVE&t;(SMP_CACHE_BYTES/8)
DECL|macro|NUM_ROUNDS
mdefine_line|#define NUM_ROUNDS&t;64&t;/* magic value */
DECL|macro|NUM_ITERS
mdefine_line|#define NUM_ITERS&t;5&t;/* likewise */
DECL|variable|itc_sync_lock
r_static
id|spinlock_t
id|itc_sync_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|go
r_static
r_volatile
r_int
r_int
id|go
(braket
id|SLAVE
op_plus
l_int|1
)braket
suffix:semicolon
DECL|macro|DEBUG_ITC_SYNC
mdefine_line|#define DEBUG_ITC_SYNC&t;0
r_extern
r_void
id|__init
id|calibrate_delay
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|start_ap
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ia64_iobase
suffix:semicolon
DECL|variable|cpucount
r_int
id|cpucount
suffix:semicolon
DECL|variable|task_for_booting_cpu
id|task_t
op_star
id|task_for_booting_cpu
suffix:semicolon
multiline_comment|/* Bitmask of currently online CPUs */
DECL|variable|cpu_online_map
r_volatile
r_int
r_int
id|cpu_online_map
suffix:semicolon
DECL|variable|phys_cpu_present_map
r_int
r_int
id|phys_cpu_present_map
suffix:semicolon
multiline_comment|/* which logical CPU number maps to which CPU (physical APIC ID) */
DECL|variable|ia64_cpu_to_sapicid
r_volatile
r_int
id|ia64_cpu_to_sapicid
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|cpu_callin_map
r_static
r_volatile
r_int
r_int
id|cpu_callin_map
suffix:semicolon
DECL|variable|__initdata
r_struct
id|smp_boot_data
id|smp_boot_data
id|__initdata
suffix:semicolon
DECL|variable|ap_wakeup_vector
r_int
r_int
id|ap_wakeup_vector
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* External Int use to wakeup APs */
DECL|variable|no_int_routing
r_char
id|__initdata
id|no_int_routing
suffix:semicolon
DECL|variable|smp_int_redirect
r_int
r_char
id|smp_int_redirect
suffix:semicolon
multiline_comment|/* are INT and IPI redirectable by the chipset? */
r_static
r_int
id|__init
DECL|function|nointroute
id|nointroute
(paren
r_char
op_star
id|str
)paren
(brace
id|no_int_routing
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;nointroute&quot;
comma
id|nointroute
)paren
suffix:semicolon
r_void
DECL|function|sync_master
id|sync_master
(paren
r_void
op_star
id|arg
)paren
(brace
r_int
r_int
id|flags
comma
id|i
suffix:semicolon
id|go
(braket
id|MASTER
)braket
op_assign
l_int|0
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_ROUNDS
op_star
id|NUM_ITERS
suffix:semicolon
op_increment
id|i
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
id|go
(braket
id|MASTER
)braket
)paren
suffix:semicolon
id|go
(braket
id|MASTER
)braket
op_assign
l_int|0
suffix:semicolon
id|go
(braket
id|SLAVE
)braket
op_assign
id|ia64_get_itc
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Return the number of cycles by which our itc differs from the itc on the master&n; * (time-keeper) CPU.  A positive number indicates our itc is ahead of the master,&n; * negative that it is behind.&n; */
r_static
r_inline
r_int
DECL|function|get_delta
id|get_delta
(paren
r_int
op_star
id|rt
comma
r_int
op_star
id|master
)paren
(brace
r_int
r_int
id|best_t0
op_assign
l_int|0
comma
id|best_t1
op_assign
op_complement
l_int|0UL
comma
id|best_tm
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|tcenter
comma
id|t0
comma
id|t1
comma
id|tm
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_ITERS
suffix:semicolon
op_increment
id|i
)paren
(brace
id|t0
op_assign
id|ia64_get_itc
c_func
(paren
)paren
suffix:semicolon
id|go
(braket
id|MASTER
)braket
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|tm
op_assign
id|go
(braket
id|SLAVE
)braket
)paren
)paren
suffix:semicolon
id|go
(braket
id|SLAVE
)braket
op_assign
l_int|0
suffix:semicolon
id|t1
op_assign
id|ia64_get_itc
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t1
op_minus
id|t0
OL
id|best_t1
op_minus
id|best_t0
)paren
id|best_t0
op_assign
id|t0
comma
id|best_t1
op_assign
id|t1
comma
id|best_tm
op_assign
id|tm
suffix:semicolon
)brace
op_star
id|rt
op_assign
id|best_t1
op_minus
id|best_t0
suffix:semicolon
op_star
id|master
op_assign
id|best_tm
op_minus
id|best_t0
suffix:semicolon
multiline_comment|/* average best_t0 and best_t1 without overflow: */
id|tcenter
op_assign
(paren
id|best_t0
op_div
l_int|2
op_plus
id|best_t1
op_div
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|best_t0
op_mod
l_int|2
op_plus
id|best_t1
op_mod
l_int|2
op_eq
l_int|2
)paren
op_increment
id|tcenter
suffix:semicolon
r_return
id|tcenter
op_minus
id|best_tm
suffix:semicolon
)brace
multiline_comment|/*&n; * Synchronize ar.itc of the current (slave) CPU with the ar.itc of the MASTER CPU&n; * (normally the time-keeper CPU).  We use a closed loop to eliminate the possibility of&n; * unaccounted-for errors (such as getting a machine check in the middle of a calibration&n; * step).  The basic idea is for the slave to ask the master what itc value it has and to&n; * read its own itc before and after the master responds.  Each iteration gives us three&n; * timestamps:&n; *&n; *&t;slave&t;&t;master&n; *&n; *&t;t0 ---&bslash;&n; *             ---&bslash;&n; *&t;&t;   ---&gt;&n; *&t;&t;&t;tm&n; *&t;&t;   /---&n; *&t;       /---&n; *&t;t1 &lt;---&n; *&n; *&n; * The goal is to adjust the slave&squot;s ar.itc such that tm falls exactly half-way between t0&n; * and t1.  If we achieve this, the clocks are synchronized provided the interconnect&n; * between the slave and the master is symmetric.  Even if the interconnect were&n; * asymmetric, we would still know that the synchronization error is smaller than the&n; * roundtrip latency (t0 - t1).&n; *&n; * When the interconnect is quiet and symmetric, this lets us synchronize the itc to&n; * within one or two cycles.  However, we can only *guarantee* that the synchronization is&n; * accurate to within a round-trip time, which is typically in the range of several&n; * hundred cycles (e.g., ~500 cycles).  In practice, this means that the itc&squot;s are usually&n; * almost perfectly synchronized, but we shouldn&squot;t assume that the accuracy is much better&n; * than half a micro second or so.&n; */
r_void
DECL|function|ia64_sync_itc
id|ia64_sync_itc
(paren
r_int
r_int
id|master
)paren
(brace
r_int
id|i
comma
id|delta
comma
id|adj
comma
id|adjust_latency
op_assign
l_int|0
comma
id|done
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
comma
id|rt
comma
id|master_time_stamp
comma
id|bound
suffix:semicolon
macro_line|#if DEBUG_ITC_SYNC
r_struct
(brace
r_int
id|rt
suffix:semicolon
multiline_comment|/* roundtrip time */
r_int
id|master
suffix:semicolon
multiline_comment|/* master&squot;s timestamp */
r_int
id|diff
suffix:semicolon
multiline_comment|/* difference between midpoint and master&squot;s timestamp */
r_int
id|lat
suffix:semicolon
multiline_comment|/* estimate of itc adjustment latency */
)brace
id|t
(braket
id|NUM_ROUNDS
)braket
suffix:semicolon
macro_line|#endif
id|go
(braket
id|MASTER
)braket
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|smp_call_function_single
c_func
(paren
id|master
comma
id|sync_master
comma
l_int|NULL
comma
l_int|1
comma
l_int|0
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sync_itc: failed to get attention of CPU %u!&bslash;n&quot;
comma
id|master
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_while
c_loop
(paren
id|go
(braket
id|MASTER
)braket
)paren
suffix:semicolon
multiline_comment|/* wait for master to be ready */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|itc_sync_lock
comma
id|flags
)paren
suffix:semicolon
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_ROUNDS
suffix:semicolon
op_increment
id|i
)paren
(brace
id|delta
op_assign
id|get_delta
c_func
(paren
op_amp
id|rt
comma
op_amp
id|master_time_stamp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|delta
op_eq
l_int|0
)paren
(brace
id|done
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* let&squot;s lock on to this... */
id|bound
op_assign
id|rt
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|done
)paren
(brace
r_if
c_cond
(paren
id|i
OG
l_int|0
)paren
(brace
id|adjust_latency
op_add_assign
op_minus
id|delta
suffix:semicolon
id|adj
op_assign
op_minus
id|delta
op_plus
id|adjust_latency
op_div
l_int|4
suffix:semicolon
)brace
r_else
id|adj
op_assign
op_minus
id|delta
suffix:semicolon
id|ia64_set_itc
c_func
(paren
id|ia64_get_itc
c_func
(paren
)paren
op_plus
id|adj
)paren
suffix:semicolon
)brace
macro_line|#if DEBUG_ITC_SYNC
id|t
(braket
id|i
)braket
dot
id|rt
op_assign
id|rt
suffix:semicolon
id|t
(braket
id|i
)braket
dot
id|master
op_assign
id|master_time_stamp
suffix:semicolon
id|t
(braket
id|i
)braket
dot
id|diff
op_assign
id|delta
suffix:semicolon
id|t
(braket
id|i
)braket
dot
id|lat
op_assign
id|adjust_latency
op_div
l_int|4
suffix:semicolon
macro_line|#endif
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|itc_sync_lock
comma
id|flags
)paren
suffix:semicolon
macro_line|#if DEBUG_ITC_SYNC
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_ROUNDS
suffix:semicolon
op_increment
id|i
)paren
id|printk
c_func
(paren
l_string|&quot;rt=%5ld master=%5ld diff=%5ld adjlat=%5ld&bslash;n&quot;
comma
id|t
(braket
id|i
)braket
dot
id|rt
comma
id|t
(braket
id|i
)braket
dot
id|master
comma
id|t
(braket
id|i
)braket
dot
id|diff
comma
id|t
(braket
id|i
)braket
dot
id|lat
)paren
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;CPU %d: synchronized ITC with CPU %u (last diff %ld cycles, maxerr %lu cycles)&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|master
comma
id|delta
comma
id|rt
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Ideally sets up per-cpu profiling hooks.  Doesn&squot;t do much now...&n; */
r_static
r_inline
r_void
id|__init
DECL|function|smp_setup_percpu_timer
id|smp_setup_percpu_timer
(paren
r_void
)paren
(brace
id|local_cpu_data-&gt;prof_counter
op_assign
l_int|1
suffix:semicolon
id|local_cpu_data-&gt;prof_multiplier
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Architecture specific routine called by the kernel just before init is&n; * fired off. This allows the BP to have everything in order [we hope].&n; * At the end of this all the APs will hit the system scheduling and off&n; * we go. Each AP will jump through the kernel&n; * init into idle(). At this point the scheduler will one day take over&n; * and give them jobs to do. smp_callin is a standard routine&n; * we use to track CPUs as they power up.&n; */
DECL|variable|smp_commenced
r_static
r_volatile
id|atomic_t
id|smp_commenced
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_static
r_void
id|__init
DECL|function|smp_commence
id|smp_commence
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Lets the callins below out of their loop.&n;&t; */
id|Dprintk
c_func
(paren
l_string|&quot;Setting commenced=1, go go go&bslash;n&quot;
)paren
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|smp_commenced
comma
l_int|1
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|smp_callin
id|smp_callin
(paren
r_void
)paren
(brace
r_int
id|cpuid
comma
id|phys_id
suffix:semicolon
r_extern
r_void
id|ia64_init_itm
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PERFMON
r_extern
r_void
id|perfmon_init_percpu
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
id|cpuid
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|phys_id
op_assign
id|hard_smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
id|cpuid
comma
op_amp
id|cpu_online_map
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;huh, phys CPU#0x%x, CPU#0x%x already present??&bslash;n&quot;
comma
id|phys_id
comma
id|cpuid
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|smp_setup_percpu_timer
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Synchronize the ITC with the BP&n;&t; */
id|Dprintk
c_func
(paren
l_string|&quot;Going to syncup ITC with BP.&bslash;n&quot;
)paren
suffix:semicolon
id|ia64_sync_itc
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Get our bogomips.&n;&t; */
id|ia64_init_itm
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set I/O port base per CPU&n;&t; */
id|ia64_set_kr
c_func
(paren
id|IA64_KR_IO_BASE
comma
id|__pa
c_func
(paren
id|ia64_iobase
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IA64_MCA
id|ia64_mca_cmc_vector_setup
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Setup vector on AP &amp; enable */
id|ia64_mca_check_errors
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* For post-failure MCA error logging */
macro_line|#endif
macro_line|#ifdef CONFIG_PERFMON
id|perfmon_init_percpu
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
id|calibrate_delay
c_func
(paren
)paren
suffix:semicolon
id|local_cpu_data-&gt;loops_per_jiffy
op_assign
id|loops_per_jiffy
suffix:semicolon
multiline_comment|/*&n;&t; * Allow the master to continue.&n;&t; */
id|set_bit
c_func
(paren
id|cpuid
comma
op_amp
id|cpu_callin_map
)paren
suffix:semicolon
id|Dprintk
c_func
(paren
l_string|&quot;Stack on CPU %d at about %p&bslash;n&quot;
comma
id|cpuid
comma
op_amp
id|cpuid
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Activate a secondary processor.  head.S calls this.&n; */
r_int
id|__init
DECL|function|start_secondary
id|start_secondary
(paren
r_void
op_star
id|unused
)paren
(brace
r_extern
r_int
id|cpu_idle
(paren
r_void
)paren
suffix:semicolon
id|Dprintk
c_func
(paren
l_string|&quot;start_secondary: starting CPU 0x%x&bslash;n&quot;
comma
id|hard_smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|efi_map_pal_code
c_func
(paren
)paren
suffix:semicolon
id|cpu_init
c_func
(paren
)paren
suffix:semicolon
id|smp_callin
c_func
(paren
)paren
suffix:semicolon
r_return
id|cpu_idle
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_struct
id|task_struct
op_star
id|__init
DECL|function|fork_by_hand
id|fork_by_hand
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * don&squot;t care about the eip and regs settings since we&squot;ll never reschedule the&n;&t; * forked task.&n;&t; */
r_return
id|do_fork
c_func
(paren
id|CLONE_VM
op_or
id|CLONE_IDLETASK
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|do_boot_cpu
id|do_boot_cpu
(paren
r_int
id|sapicid
comma
r_int
id|cpu
)paren
(brace
r_struct
id|task_struct
op_star
id|idle
suffix:semicolon
r_int
id|timeout
suffix:semicolon
multiline_comment|/*&n;&t; * We can&squot;t use kernel_thread since we must avoid to reschedule the child.&n;&t; */
id|idle
op_assign
id|fork_by_hand
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|idle
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;failed fork for CPU %d&quot;
comma
id|cpu
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We remove it from the pidhash and the runqueue&n;&t; * once we got the process:&n;&t; */
id|init_idle
c_func
(paren
id|idle
comma
id|cpu
)paren
suffix:semicolon
id|unhash_process
c_func
(paren
id|idle
)paren
suffix:semicolon
id|task_for_booting_cpu
op_assign
id|idle
suffix:semicolon
id|Dprintk
c_func
(paren
l_string|&quot;Sending wakeup vector %lu to AP 0x%x/0x%x.&bslash;n&quot;
comma
id|ap_wakeup_vector
comma
id|cpu
comma
id|sapicid
)paren
suffix:semicolon
id|platform_send_ipi
c_func
(paren
id|cpu
comma
id|ap_wakeup_vector
comma
id|IA64_IPI_DM_INT
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Wait 10s total for the AP to start&n;&t; */
id|Dprintk
c_func
(paren
l_string|&quot;Waiting on callin_map ...&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|timeout
op_assign
l_int|0
suffix:semicolon
id|timeout
OL
l_int|100000
suffix:semicolon
id|timeout
op_increment
)paren
(brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|cpu
comma
op_amp
id|cpu_callin_map
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* It has booted */
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
)brace
id|Dprintk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|cpu
comma
op_amp
id|cpu_callin_map
)paren
)paren
(brace
multiline_comment|/* number CPUs logically, starting from 1 (BSP is 0) */
id|printk
c_func
(paren
l_string|&quot;CPU%d: &quot;
comma
id|cpu
)paren
suffix:semicolon
multiline_comment|/*print_cpu_info(&amp;cpu_data[cpu]); */
id|printk
c_func
(paren
l_string|&quot;CPU has booted.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Processor 0x%x/0x%x is stuck.&bslash;n&quot;
comma
id|cpu
comma
id|sapicid
)paren
suffix:semicolon
id|ia64_cpu_to_sapicid
(braket
id|cpu
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
id|clear_bit
c_func
(paren
id|cpu
comma
op_amp
id|cpu_online_map
)paren
suffix:semicolon
multiline_comment|/* was set in smp_callin() */
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cache_decay_ticks
r_int
r_int
id|cache_decay_ticks
suffix:semicolon
multiline_comment|/* # of ticks an idle task is considered cache-hot */
r_static
r_void
DECL|function|smp_tune_scheduling
id|smp_tune_scheduling
(paren
r_void
)paren
(brace
id|cache_decay_ticks
op_assign
l_int|10
suffix:semicolon
multiline_comment|/* XXX base this on PAL info and cache-bandwidth estimate */
id|printk
c_func
(paren
l_string|&quot;task migration cache decay timeout: %ld msecs.&bslash;n&quot;
comma
(paren
id|cache_decay_ticks
op_plus
l_int|1
)paren
op_star
l_int|1000
op_div
id|HZ
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize the logical CPU number to SAPICID mapping&n; */
r_void
id|__init
DECL|function|smp_build_cpu_map
id|smp_build_cpu_map
(paren
r_void
)paren
(brace
r_int
id|sapicid
comma
id|cpu
comma
id|i
suffix:semicolon
r_int
id|boot_cpu_id
op_assign
id|hard_smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cpu
op_assign
l_int|0
suffix:semicolon
id|cpu
OL
id|NR_CPUS
suffix:semicolon
id|cpu
op_increment
)paren
id|ia64_cpu_to_sapicid
(braket
id|cpu
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
id|ia64_cpu_to_sapicid
(braket
l_int|0
)braket
op_assign
id|boot_cpu_id
suffix:semicolon
id|phys_cpu_present_map
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|cpu
op_assign
l_int|1
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|smp_boot_data.cpu_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sapicid
op_assign
id|smp_boot_data.cpu_phys_id
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|sapicid
op_eq
op_minus
l_int|1
op_logical_or
id|sapicid
op_eq
id|boot_cpu_id
)paren
r_continue
suffix:semicolon
id|phys_cpu_present_map
op_or_assign
(paren
l_int|1
op_lshift
id|cpu
)paren
suffix:semicolon
id|ia64_cpu_to_sapicid
(braket
id|cpu
)braket
op_assign
id|sapicid
suffix:semicolon
id|cpu
op_increment
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Cycle through the APs sending Wakeup IPIs to boot each.&n; */
r_void
id|__init
DECL|function|smp_prepare_cpus
id|smp_prepare_cpus
(paren
r_int
r_int
id|max_cpus
)paren
(brace
r_int
id|boot_cpu_id
op_assign
id|hard_smp_processor_id
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Initialize the per-CPU profiling counter/multiplier&n;&t; */
id|smp_setup_percpu_timer
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We have the boot CPU online for sure.&n;&t; */
id|set_bit
c_func
(paren
l_int|0
comma
op_amp
id|cpu_online_map
)paren
suffix:semicolon
id|set_bit
c_func
(paren
l_int|0
comma
op_amp
id|cpu_callin_map
)paren
suffix:semicolon
id|local_cpu_data-&gt;loops_per_jiffy
op_assign
id|loops_per_jiffy
suffix:semicolon
id|ia64_cpu_to_sapicid
(braket
l_int|0
)braket
op_assign
id|boot_cpu_id
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Boot processor id 0x%x/0x%x&bslash;n&quot;
comma
l_int|0
comma
id|boot_cpu_id
)paren
suffix:semicolon
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|cpu
op_assign
l_int|0
suffix:semicolon
id|smp_tune_scheduling
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If SMP should be disabled, then really disable it!&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|max_cpus
op_logical_or
(paren
id|max_cpus
OL
op_minus
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;SMP mode deactivated.&bslash;n&quot;
)paren
suffix:semicolon
id|cpu_online_map
op_assign
id|phys_cpu_present_map
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
r_void
DECL|function|smp_cpus_done
id|smp_cpus_done
(paren
r_int
r_int
id|dummy
)paren
(brace
r_int
id|cpu
suffix:semicolon
r_int
r_int
id|bogosum
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Allow the user to impress friends.&n;&t; */
r_for
c_loop
(paren
id|cpu
op_assign
l_int|0
suffix:semicolon
id|cpu
OL
id|NR_CPUS
suffix:semicolon
id|cpu
op_increment
)paren
r_if
c_cond
(paren
id|cpu_online
c_func
(paren
id|cpu
)paren
)paren
id|bogosum
op_add_assign
id|cpu_data
c_func
(paren
id|cpu
)paren
op_member_access_from_pointer
id|loops_per_jiffy
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Total of %d processors activated (%lu.%02lu BogoMIPS).&bslash;n&quot;
comma
id|num_online_cpus
c_func
(paren
)paren
comma
id|bogosum
op_div
(paren
l_int|500000
op_div
id|HZ
)paren
comma
(paren
id|bogosum
op_div
(paren
l_int|5000
op_div
id|HZ
)paren
)paren
op_mod
l_int|100
)paren
suffix:semicolon
)brace
r_int
id|__devinit
DECL|function|__cpu_up
id|__cpu_up
(paren
r_int
r_int
id|cpu
)paren
(brace
r_int
id|ret
suffix:semicolon
r_int
id|sapicid
suffix:semicolon
id|sapicid
op_assign
id|ia64_cpu_to_sapicid
(braket
id|cpu
)braket
suffix:semicolon
r_if
c_cond
(paren
id|sapicid
op_eq
op_minus
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Processor %d/%d is spinning up...&bslash;n&quot;
comma
id|sapicid
comma
id|cpu
)paren
suffix:semicolon
multiline_comment|/* Processor goes to start_secondary(), sets online flag */
id|ret
op_assign
id|do_boot_cpu
c_func
(paren
id|sapicid
comma
id|cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Processor %d has spun up...&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Assume that CPU&squot;s have been discovered by some platform-dependant interface.  For&n; * SoftSDV/Lion, that would be ACPI.&n; *&n; * Setup of the IPI irq handler is done in irq.c:init_IRQ_SMP().&n; */
r_void
id|__init
DECL|function|init_smp_config
id|init_smp_config
c_func
(paren
r_void
)paren
(brace
r_struct
id|fptr
(brace
r_int
r_int
id|fp
suffix:semicolon
r_int
r_int
id|gp
suffix:semicolon
)brace
op_star
id|ap_startup
suffix:semicolon
r_int
id|sal_ret
suffix:semicolon
multiline_comment|/* Tell SAL where to drop the AP&squot;s.  */
id|ap_startup
op_assign
(paren
r_struct
id|fptr
op_star
)paren
id|start_ap
suffix:semicolon
id|sal_ret
op_assign
id|ia64_sal_set_vectors
c_func
(paren
id|SAL_VECTOR_OS_BOOT_RENDEZ
comma
id|__pa
c_func
(paren
id|ap_startup-&gt;fp
)paren
comma
id|__pa
c_func
(paren
id|ap_startup-&gt;gp
)paren
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sal_ret
OL
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;SMP: Can&squot;t set SAL AP Boot Rendezvous: %s&bslash;n&quot;
comma
id|ia64_sal_strerror
c_func
(paren
id|sal_ret
)paren
)paren
suffix:semicolon
)brace
eof
