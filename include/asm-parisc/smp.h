macro_line|#ifndef __ASM_SMP_H
DECL|macro|__ASM_SMP_H
mdefine_line|#define __ASM_SMP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_SMP)
multiline_comment|/* Page Zero Location PDC will look for the address to branch to when we poke&n;** slave CPUs still in &quot;Icache loop&quot;.&n;*/
DECL|macro|PDC_OS_BOOT_RENDEZVOUS
mdefine_line|#define PDC_OS_BOOT_RENDEZVOUS     0x10
DECL|macro|PDC_OS_BOOT_RENDEZVOUS_HI
mdefine_line|#define PDC_OS_BOOT_RENDEZVOUS_HI  0x28
macro_line|#ifndef ASSEMBLY
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/threads.h&gt;&t;/* for NR_CPUS */
DECL|typedef|address_t
r_typedef
r_int
r_int
id|address_t
suffix:semicolon
r_extern
r_volatile
r_int
r_int
id|cpu_online_map
suffix:semicolon
multiline_comment|/*&n; *&t;Private routines/data&n; *&n; *&t;physical and logical are equivalent until we support CPU hotplug.&n; */
DECL|macro|cpu_number_map
mdefine_line|#define cpu_number_map(cpu)&t;(cpu)
DECL|macro|cpu_logical_map
mdefine_line|#define cpu_logical_map(cpu)&t;(cpu)
r_extern
r_void
id|smp_send_reschedule
c_func
(paren
r_int
id|cpu
)paren
suffix:semicolon
macro_line|#endif /* !ASSEMBLY */
multiline_comment|/*&n; *&t;This magic constant controls our willingness to transfer&n; *      a process across CPUs. Such a transfer incurs cache and tlb&n; *      misses. The current value is inherited from i386. Still needs&n; *      to be tuned for parisc.&n; */
DECL|macro|PROC_CHANGE_PENALTY
mdefine_line|#define PROC_CHANGE_PENALTY&t;15&t;&t;/* Schedule penalty */
DECL|macro|ENTRY_SYS_CPUS
macro_line|#undef ENTRY_SYS_CPUS
macro_line|#ifdef ENTRY_SYS_CPUS
DECL|macro|STATE_RENDEZVOUS
mdefine_line|#define STATE_RENDEZVOUS&t;&t;&t;0
DECL|macro|STATE_STOPPED
mdefine_line|#define STATE_STOPPED &t;&t;&t;&t;1 
DECL|macro|STATE_RUNNING
mdefine_line|#define STATE_RUNNING&t;&t;&t;&t;2
DECL|macro|STATE_HALTED
mdefine_line|#define STATE_HALTED&t;&t;&t;&t;3
macro_line|#endif
r_extern
r_int
r_int
id|cpu_present_mask
suffix:semicolon
DECL|macro|smp_processor_id
mdefine_line|#define smp_processor_id()&t;(current_thread_info()-&gt;cpu)
DECL|macro|cpu_online
mdefine_line|#define cpu_online(cpu) (cpu_online_map &amp; (1&lt;&lt;(cpu)))
DECL|macro|cpu_possible
mdefine_line|#define cpu_possible(cpu)       (cpu_present_mask &amp; (1&lt;&lt;(cpu)))
DECL|function|num_online_cpus
r_extern
r_inline
r_int
r_int
id|num_online_cpus
c_func
(paren
r_void
)paren
(brace
r_return
id|hweight32
c_func
(paren
id|cpu_online_map
)paren
suffix:semicolon
)brace
DECL|function|any_online_cpu
r_extern
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
id|mask
op_amp
id|cpu_online_map
)paren
r_return
id|__ffs
c_func
(paren
id|mask
op_amp
id|cpu_online_map
)paren
suffix:semicolon
r_return
id|NR_CPUS
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_SMP */
DECL|macro|NO_PROC_ID
mdefine_line|#define NO_PROC_ID&t;&t;0xFF&t;&t;/* No processor magic marker */
DECL|macro|ANY_PROC_ID
mdefine_line|#define ANY_PROC_ID&t;&t;0xFF&t;&t;/* Any processor magic marker */
macro_line|#endif /*  __ASM_SMP_H */
eof
