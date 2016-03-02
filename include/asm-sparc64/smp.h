multiline_comment|/* smp.h: Sparc64 specific SMP stuff.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC64_SMP_H
DECL|macro|_SPARC64_SMP_H
mdefine_line|#define _SPARC64_SMP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/asi.h&gt;
macro_line|#include &lt;asm/starfire.h&gt;
macro_line|#include &lt;asm/spitfire.h&gt;
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/cache.h&gt;
multiline_comment|/* PROM provided per-processor information we need&n; * to start them all up.&n; */
DECL|struct|prom_cpuinfo
r_struct
id|prom_cpuinfo
(brace
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
DECL|member|mid
r_int
id|mid
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|linux_num_cpus
suffix:semicolon
multiline_comment|/* number of CPUs probed  */
r_extern
r_struct
id|prom_cpuinfo
id|linux_cpus
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_int
r_int
id|prom_cpu_nodes
(braket
id|NR_CPUS
)braket
suffix:semicolon
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#ifdef CONFIG_SMP
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Per processor Sparc parameters we need. */
multiline_comment|/* Keep this a multiple of 64-bytes for cache reasons. */
r_typedef
r_struct
(brace
multiline_comment|/* Dcache line 1 */
DECL|member|__pad0
r_int
r_int
id|__pad0
suffix:semicolon
multiline_comment|/* bh_count moved to irq_stat for consistency. KAO */
DECL|member|multiplier
r_int
r_int
id|multiplier
suffix:semicolon
DECL|member|counter
r_int
r_int
id|counter
suffix:semicolon
DECL|member|idle_volume
r_int
r_int
id|idle_volume
suffix:semicolon
DECL|member|clock_tick
r_int
r_int
id|clock_tick
suffix:semicolon
multiline_comment|/* %tick&squot;s per second */
DECL|member|udelay_val
r_int
r_int
id|udelay_val
suffix:semicolon
multiline_comment|/* Dcache line 2 */
DECL|member|pgcache_size
r_int
r_int
id|pgcache_size
suffix:semicolon
DECL|member|pgdcache_size
r_int
r_int
id|pgdcache_size
suffix:semicolon
DECL|member|pte_cache
r_int
r_int
op_star
id|pte_cache
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|pgd_cache
r_int
r_int
op_star
id|pgd_cache
suffix:semicolon
multiline_comment|/* Dcache lines 3 and 4 */
DECL|member|irq_worklists
r_int
r_int
id|irq_worklists
(braket
l_int|16
)braket
suffix:semicolon
DECL|typedef|cpuinfo_sparc
)brace
id|____cacheline_aligned
id|cpuinfo_sparc
suffix:semicolon
r_extern
id|cpuinfo_sparc
id|cpu_data
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/*&n; *&t;Private routines/data&n; */
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
r_extern
r_int
r_char
id|boot_cpu_id
suffix:semicolon
r_extern
r_int
r_int
id|phys_cpu_present_map
suffix:semicolon
DECL|macro|cpu_possible
mdefine_line|#define cpu_possible(cpu)&t;(phys_cpu_present_map &amp; (1UL &lt;&lt; (cpu)))
r_extern
r_int
r_int
id|cpu_online_map
suffix:semicolon
DECL|macro|cpu_online
mdefine_line|#define cpu_online(cpu)&t;&t;(cpu_online_map &amp; (1UL &lt;&lt; (cpu)))
r_extern
id|atomic_t
id|sparc64_num_cpus_online
suffix:semicolon
DECL|macro|num_online_cpus
mdefine_line|#define num_online_cpus()&t;(atomic_read(&amp;sparc64_num_cpus_online))
r_extern
id|atomic_t
id|sparc64_num_cpus_possible
suffix:semicolon
DECL|macro|num_possible_cpus
mdefine_line|#define num_possible_cpus()&t;(atomic_read(&amp;sparc64_num_cpus_possible))
DECL|function|any_online_cpu
r_static
r_inline
r_int
r_int
id|any_online_cpu
c_func
(paren
r_int
r_int
id|mask
)paren
(brace
r_if
c_cond
(paren
(paren
id|mask
op_and_assign
id|cpu_online_map
)paren
op_ne
l_int|0UL
)paren
r_return
id|__ffs
c_func
(paren
id|mask
)paren
suffix:semicolon
r_return
id|NR_CPUS
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;General functions that each host system must provide.&n; */
DECL|function|hard_smp_processor_id
r_static
id|__inline__
r_int
id|hard_smp_processor_id
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|tlb_type
op_eq
id|cheetah
op_logical_or
id|tlb_type
op_eq
id|cheetah_plus
)paren
(brace
r_int
r_int
id|safari_config
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ldxa [%%g0] %1, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|safari_config
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|ASI_SAFARI_CONFIG
)paren
)paren
suffix:semicolon
r_return
(paren
(paren
id|safari_config
op_rshift
l_int|17
)paren
op_amp
l_int|0x3ff
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|this_is_starfire
op_ne
l_int|0
)paren
(brace
r_return
id|starfire_hard_smp_processor_id
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
id|upaconfig
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ldxa&t;[%%g0] %1, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|upaconfig
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|ASI_UPA_CONFIG
)paren
)paren
suffix:semicolon
r_return
(paren
(paren
id|upaconfig
op_rshift
l_int|17
)paren
op_amp
l_int|0x1f
)paren
suffix:semicolon
)brace
)brace
DECL|macro|smp_processor_id
mdefine_line|#define smp_processor_id() (current_thread_info()-&gt;cpu)
multiline_comment|/* This needn&squot;t do anything as we do not sleep the cpu&n; * inside of the idler task, so an interrupt is not needed&n; * to get a clean fast response.&n; *&n; * XXX Reverify this assumption... -DaveM&n; *&n; * Addendum: We do want it to do something for the signal&n; *           delivery case, we detect that by just seeing&n; *           if we are trying to send this to an idler or not.&n; */
DECL|function|smp_send_reschedule
r_static
id|__inline__
r_void
id|smp_send_reschedule
c_func
(paren
r_int
id|cpu
)paren
(brace
r_extern
r_void
id|smp_receive_signal
c_func
(paren
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_data
(braket
id|cpu
)braket
dot
id|idle_volume
op_eq
l_int|0
)paren
id|smp_receive_signal
c_func
(paren
id|cpu
)paren
suffix:semicolon
)brace
multiline_comment|/* This is a nop as well because we capture all other cpus&n; * anyways when making the PROM active.&n; */
DECL|function|smp_send_stop
r_static
id|__inline__
r_void
id|smp_send_stop
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* !(CONFIG_SMP) */
DECL|macro|NO_PROC_ID
mdefine_line|#define NO_PROC_ID&t;&t;0xFF
macro_line|#endif /* !(_SPARC64_SMP_H) */
eof
