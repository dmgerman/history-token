multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file &quot;COPYING&quot; in the main directory of this&n; * archive for more details.&n; *&n; * Copyright (C) 2000 - 2001 by Kanoj Sarcar (kanoj@sgi.com)&n; * Copyright (C) 2000 - 2001 by Silicon Graphics, Inc.&n; * Copyright (C) 2000, 2001, 2002 Ralf Baechle&n; * Copyright (C) 2000, 2001 Broadcom Corporation&n; */
macro_line|#ifndef __ASM_SMP_H
DECL|macro|__ASM_SMP_H
mdefine_line|#define __ASM_SMP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_SMP
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/cpumask.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
DECL|macro|smp_processor_id
mdefine_line|#define smp_processor_id()&t;(current_thread_info()-&gt;cpu)
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
DECL|macro|NO_PROC_ID
mdefine_line|#define NO_PROC_ID&t;(-1)
DECL|struct|call_data_struct
r_struct
id|call_data_struct
(brace
DECL|member|func
r_void
(paren
op_star
id|func
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|member|info
r_void
op_star
id|info
suffix:semicolon
DECL|member|started
id|atomic_t
id|started
suffix:semicolon
DECL|member|finished
id|atomic_t
id|finished
suffix:semicolon
DECL|member|wait
r_int
id|wait
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|call_data_struct
op_star
id|call_data
suffix:semicolon
DECL|macro|SMP_RESCHEDULE_YOURSELF
mdefine_line|#define SMP_RESCHEDULE_YOURSELF&t;0x1&t;/* XXX braindead */
DECL|macro|SMP_CALL_FUNCTION
mdefine_line|#define SMP_CALL_FUNCTION&t;0x2
r_extern
id|cpumask_t
id|phys_cpu_present_map
suffix:semicolon
r_extern
id|cpumask_t
id|cpu_online_map
suffix:semicolon
DECL|macro|cpu_possible
mdefine_line|#define cpu_possible(cpu)&t;cpu_isset(cpu, phys_cpu_present_map)
DECL|macro|cpu_online
mdefine_line|#define cpu_online(cpu)&t;&t;cpu_isset(cpu, cpu_online_map)
DECL|function|num_online_cpus
r_static
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
id|cpus_weight
c_func
(paren
id|cpu_online_map
)paren
suffix:semicolon
)brace
r_extern
id|cpumask_t
id|cpu_callout_map
suffix:semicolon
multiline_comment|/* We don&squot;t mark CPUs online until __cpu_up(), so we need another measure */
DECL|function|num_booting_cpus
r_static
r_inline
r_int
id|num_booting_cpus
c_func
(paren
r_void
)paren
(brace
r_return
id|cpus_weight
c_func
(paren
id|cpu_callout_map
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_SMP */
macro_line|#endif /* __ASM_SMP_H */
eof
