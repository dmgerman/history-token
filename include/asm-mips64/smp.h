macro_line|#ifndef __ASM_SMP_H
DECL|macro|__ASM_SMP_H
mdefine_line|#define __ASM_SMP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_SMP
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#if 0
r_struct
id|cpuinfo_mips
(brace
multiline_comment|/* XXX  */
r_int
r_int
id|loops_per_sec
suffix:semicolon
r_int
r_int
id|last_asn
suffix:semicolon
r_int
r_int
op_star
id|pgd_cache
suffix:semicolon
r_int
r_int
op_star
id|pte_cache
suffix:semicolon
r_int
r_int
id|pgtable_cache_sz
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
id|cpuinfo_mips
id|cpu_data
(braket
id|NR_CPUS
)braket
suffix:semicolon
macro_line|#endif
DECL|macro|smp_processor_id
mdefine_line|#define smp_processor_id()&t;(current-&gt;processor)
DECL|macro|PROC_CHANGE_PENALTY
mdefine_line|#define PROC_CHANGE_PENALTY&t;20
multiline_comment|/* Map from cpu id to sequential logical cpu number.  This will only&n;   not be idempotent when cpus failed to come on-line.  */
r_extern
r_int
id|__cpu_number_map
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|macro|cpu_number_map
mdefine_line|#define cpu_number_map(cpu)  __cpu_number_map[cpu]
multiline_comment|/* The reverse map from sequential logical cpu number to cpu id.  */
r_extern
r_int
id|__cpu_logical_map
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|macro|cpu_logical_map
mdefine_line|#define cpu_logical_map(cpu)  __cpu_logical_map[cpu]
multiline_comment|/* Good enough for toy^Wupto 64 CPU Origins.  */
r_extern
r_int
r_int
id|cpu_present_mask
suffix:semicolon
macro_line|#endif
DECL|macro|NO_PROC_ID
mdefine_line|#define NO_PROC_ID&t;(-1)
macro_line|#endif __ASM_SMP_H
eof
