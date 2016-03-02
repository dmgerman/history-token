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
macro_line|#include &lt;linux/cpumask.h&gt;
DECL|typedef|address_t
r_typedef
r_int
r_int
id|address_t
suffix:semicolon
r_extern
id|cpumask_t
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
macro_line|#endif /* CONFIG_SMP */
DECL|macro|NO_PROC_ID
mdefine_line|#define NO_PROC_ID&t;&t;0xFF&t;&t;/* No processor magic marker */
DECL|macro|ANY_PROC_ID
mdefine_line|#define ANY_PROC_ID&t;&t;0xFF&t;&t;/* Any processor magic marker */
DECL|function|__cpu_disable
r_static
r_inline
r_int
id|__cpu_disable
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|__cpu_die
r_static
r_inline
r_void
id|__cpu_die
(paren
r_int
r_int
id|cpu
)paren
(brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
)brace
r_extern
r_int
id|__cpu_up
(paren
r_int
r_int
id|cpu
)paren
suffix:semicolon
macro_line|#endif /*  __ASM_SMP_H */
eof
