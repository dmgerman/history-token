multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file &quot;COPYING&quot; in the main directory of this&n; * archive for more details.&n; *&n; * Copyright (C) 2000 - 2001 by Kanoj Sarcar (kanoj@sgi.com)&n; * Copyright (C) 2000 - 2001 by Silicon Graphics, Inc.&n; * Copyright (C) 2000, 2001, 2002 Ralf Baechle&n; * Copyright (C) 2000, 2001 Broadcom Corporation&n; */
macro_line|#ifndef __ASM_SMP_H
DECL|macro|__ASM_SMP_H
mdefine_line|#define __ASM_SMP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_SMP
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
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
DECL|macro|cpu_possible_map
mdefine_line|#define cpu_possible_map&t;phys_cpu_present_map
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
multiline_comment|/* These are defined by the board-specific code. */
multiline_comment|/*&n; * Cause the function described by call_data to be executed on the passed&n; * cpu.  When the function has finished, increment the finished field of&n; * call_data.&n; */
r_extern
r_void
id|core_send_ipi
c_func
(paren
r_int
id|cpu
comma
r_int
r_int
id|action
)paren
suffix:semicolon
multiline_comment|/*&n; * Firmware CPU startup hook&n; */
r_extern
r_void
id|prom_boot_secondary
c_func
(paren
r_int
id|cpu
comma
r_struct
id|task_struct
op_star
id|idle
)paren
suffix:semicolon
multiline_comment|/*&n; *  After we&squot;ve done initial boot, this function is called to allow the&n; *  board code to clean up state, if needed&n; */
r_extern
r_void
id|prom_init_secondary
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Detect available CPUs, populate phys_cpu_present_map before smp_init&n; */
r_extern
r_void
id|prom_prepare_cpus
c_func
(paren
r_int
r_int
id|max_cpus
)paren
suffix:semicolon
multiline_comment|/*&n; * Last chance for the board code to finish SMP initialization before&n; * the CPU is &quot;online&quot;.&n; */
r_extern
r_void
id|prom_smp_finish
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Hook for after all CPUs are online */
r_extern
r_void
id|prom_cpus_done
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|asmlinkage
id|smp_bootstrap
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * this function sends a &squot;reschedule&squot; IPI to another CPU.&n; * it goes straight through and wastes no time serializing&n; * anything. Worst case is that we lose a reschedule ...&n; */
DECL|function|smp_send_reschedule
r_static
r_inline
r_void
id|smp_send_reschedule
c_func
(paren
r_int
id|cpu
)paren
(brace
id|core_send_ipi
c_func
(paren
id|cpu
comma
id|SMP_RESCHEDULE_YOURSELF
)paren
suffix:semicolon
)brace
r_extern
id|asmlinkage
r_void
id|smp_call_function_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
macro_line|#endif /* __ASM_SMP_H */
eof
