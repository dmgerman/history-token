macro_line|#ifndef __ASM_SMP_H
DECL|macro|__ASM_SMP_H
mdefine_line|#define __ASM_SMP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/cpumask.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/pal.h&gt;
multiline_comment|/* HACK: Cabrio WHAMI return value is bogus if more than 8 bits used.. :-( */
r_static
id|__inline__
r_int
r_char
DECL|function|__hard_smp_processor_id
id|__hard_smp_processor_id
c_func
(paren
r_void
)paren
(brace
r_register
r_int
r_char
id|__r0
id|__asm__
c_func
(paren
l_string|&quot;$0&quot;
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;call_pal %1 #whami&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__r0
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|PAL_whami
)paren
suffix:colon
l_string|&quot;$1&quot;
comma
l_string|&quot;$22&quot;
comma
l_string|&quot;$23&quot;
comma
l_string|&quot;$24&quot;
comma
l_string|&quot;$25&quot;
)paren
suffix:semicolon
r_return
id|__r0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
macro_line|#include &lt;asm/irq.h&gt;
DECL|struct|cpuinfo_alpha
r_struct
id|cpuinfo_alpha
(brace
DECL|member|loops_per_jiffy
r_int
r_int
id|loops_per_jiffy
suffix:semicolon
DECL|member|last_asn
r_int
r_int
id|last_asn
suffix:semicolon
DECL|member|need_new_asn
r_int
id|need_new_asn
suffix:semicolon
DECL|member|asn_lock
r_int
id|asn_lock
suffix:semicolon
DECL|member|ipi_count
r_int
r_int
id|ipi_count
suffix:semicolon
DECL|member|prof_multiplier
r_int
r_int
id|prof_multiplier
suffix:semicolon
DECL|member|prof_counter
r_int
r_int
id|prof_counter
suffix:semicolon
DECL|member|mcheck_expected
r_int
r_char
id|mcheck_expected
suffix:semicolon
DECL|member|mcheck_taken
r_int
r_char
id|mcheck_taken
suffix:semicolon
DECL|member|mcheck_extra
r_int
r_char
id|mcheck_extra
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|64
)paren
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|cpuinfo_alpha
id|cpu_data
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|macro|PROC_CHANGE_PENALTY
mdefine_line|#define PROC_CHANGE_PENALTY     20
DECL|macro|hard_smp_processor_id
mdefine_line|#define hard_smp_processor_id()&t;__hard_smp_processor_id()
DECL|macro|smp_processor_id
mdefine_line|#define smp_processor_id()&t;(current_thread_info()-&gt;cpu)
r_extern
id|cpumask_t
id|cpu_present_mask
suffix:semicolon
r_extern
id|cpumask_t
id|cpu_online_map
suffix:semicolon
r_extern
r_int
id|smp_num_cpus
suffix:semicolon
DECL|macro|cpu_possible_map
mdefine_line|#define cpu_possible_map&t;cpu_present_mask
r_int
id|smp_call_function_on_cpu
c_func
(paren
r_void
(paren
op_star
id|func
)paren
(paren
r_void
op_star
id|info
)paren
comma
r_void
op_star
id|info
comma
r_int
id|retry
comma
r_int
id|wait
comma
id|cpumask_t
id|cpu
)paren
suffix:semicolon
macro_line|#else /* CONFIG_SMP */
DECL|macro|smp_call_function_on_cpu
mdefine_line|#define smp_call_function_on_cpu(func,info,retry,wait,cpu)    ({ 0; })
macro_line|#endif /* CONFIG_SMP */
DECL|macro|NO_PROC_ID
mdefine_line|#define NO_PROC_ID&t;(-1)
macro_line|#endif
eof
