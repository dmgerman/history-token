multiline_comment|/*&n; * SMP Support&n; *&n; * Copyright (C) 1999 VA Linux Systems&n; * Copyright (C) 1999 Walt Drummond &lt;drummond@valinux.com&gt;&n; * Copyright (C) 2001-2003 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#ifndef _ASM_IA64_SMP_H
DECL|macro|_ASM_IA64_SMP_H
mdefine_line|#define _ASM_IA64_SMP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_SMP
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/param.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|macro|XTP_OFFSET
mdefine_line|#define XTP_OFFSET&t;&t;0x1e0008
DECL|macro|SMP_IRQ_REDIRECTION
mdefine_line|#define SMP_IRQ_REDIRECTION&t;(1 &lt;&lt; 0)
DECL|macro|SMP_IPI_REDIRECTION
mdefine_line|#define SMP_IPI_REDIRECTION&t;(1 &lt;&lt; 1)
DECL|macro|smp_processor_id
mdefine_line|#define smp_processor_id()&t;(current_thread_info()-&gt;cpu)
DECL|struct|smp_boot_data
r_extern
r_struct
id|smp_boot_data
(brace
DECL|member|cpu_count
r_int
id|cpu_count
suffix:semicolon
DECL|member|cpu_phys_id
r_int
id|cpu_phys_id
(braket
id|NR_CPUS
)braket
suffix:semicolon
)brace
id|smp_boot_data
id|__initdata
suffix:semicolon
r_extern
r_char
id|no_int_routing
id|__initdata
suffix:semicolon
r_extern
r_int
r_int
id|phys_cpu_present_map
suffix:semicolon
r_extern
r_volatile
r_int
r_int
id|cpu_online_map
suffix:semicolon
r_extern
r_int
r_int
id|ipi_base_addr
suffix:semicolon
r_extern
r_int
r_char
id|smp_int_redirect
suffix:semicolon
r_extern
r_volatile
r_int
id|ia64_cpu_to_sapicid
(braket
)braket
suffix:semicolon
DECL|macro|cpu_physical_id
mdefine_line|#define cpu_physical_id(i)&t;ia64_cpu_to_sapicid[i]
r_extern
r_int
r_int
id|ap_wakeup_vector
suffix:semicolon
DECL|macro|cpu_possible
mdefine_line|#define cpu_possible(cpu)&t;(phys_cpu_present_map &amp; (1UL &lt;&lt; (cpu)))
DECL|macro|cpu_online
mdefine_line|#define cpu_online(cpu)&t;&t;(cpu_online_map &amp; (1UL &lt;&lt; (cpu)))
r_static
r_inline
r_int
r_int
DECL|function|num_online_cpus
id|num_online_cpus
(paren
r_void
)paren
(brace
r_return
id|hweight64
c_func
(paren
id|cpu_online_map
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|any_online_cpu
id|any_online_cpu
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
multiline_comment|/*&n; * Function to map hard smp processor id to logical id.  Slow, so don&squot;t use this in&n; * performance-critical code.&n; */
r_static
r_inline
r_int
DECL|function|cpu_logical_id
id|cpu_logical_id
(paren
r_int
id|cpuid
)paren
(brace
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
id|NR_CPUS
suffix:semicolon
op_increment
id|i
)paren
r_if
c_cond
(paren
id|cpu_physical_id
c_func
(paren
id|i
)paren
op_eq
id|cpuid
)paren
r_break
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
multiline_comment|/*&n; * XTP control functions:&n; *&t;min_xtp   : route all interrupts to this CPU&n; *&t;normal_xtp: nominal XTP value&n; *&t;max_xtp   : never deliver interrupts to this CPU.&n; */
r_static
r_inline
r_void
DECL|function|min_xtp
id|min_xtp
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|smp_int_redirect
op_amp
id|SMP_IRQ_REDIRECTION
)paren
id|writeb
c_func
(paren
l_int|0x00
comma
id|ipi_base_addr
op_or
id|XTP_OFFSET
)paren
suffix:semicolon
multiline_comment|/* XTP to min */
)brace
r_static
r_inline
r_void
DECL|function|normal_xtp
id|normal_xtp
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|smp_int_redirect
op_amp
id|SMP_IRQ_REDIRECTION
)paren
id|writeb
c_func
(paren
l_int|0x08
comma
id|ipi_base_addr
op_or
id|XTP_OFFSET
)paren
suffix:semicolon
multiline_comment|/* XTP normal */
)brace
r_static
r_inline
r_void
DECL|function|max_xtp
id|max_xtp
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|smp_int_redirect
op_amp
id|SMP_IRQ_REDIRECTION
)paren
id|writeb
c_func
(paren
l_int|0x0f
comma
id|ipi_base_addr
op_or
id|XTP_OFFSET
)paren
suffix:semicolon
multiline_comment|/* Set XTP to max */
)brace
r_static
r_inline
r_int
r_int
DECL|function|hard_smp_processor_id
id|hard_smp_processor_id
(paren
r_void
)paren
(brace
r_union
(brace
r_struct
(brace
r_int
r_int
id|reserved
suffix:colon
l_int|16
suffix:semicolon
r_int
r_int
id|eid
suffix:colon
l_int|8
suffix:semicolon
r_int
r_int
id|id
suffix:colon
l_int|8
suffix:semicolon
r_int
r_int
id|ignored
suffix:colon
l_int|32
suffix:semicolon
)brace
id|f
suffix:semicolon
r_int
r_int
id|bits
suffix:semicolon
)brace
id|lid
suffix:semicolon
id|lid.bits
op_assign
id|ia64_get_lid
c_func
(paren
)paren
suffix:semicolon
r_return
id|lid.f.id
op_lshift
l_int|8
op_or
id|lid.f.eid
suffix:semicolon
)brace
multiline_comment|/* Upping and downing of CPUs */
r_extern
r_int
id|__cpu_disable
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__cpu_die
(paren
r_int
r_int
id|cpu
)paren
suffix:semicolon
r_extern
r_int
id|__cpu_up
(paren
r_int
r_int
id|cpu
)paren
suffix:semicolon
r_extern
r_void
id|__init
id|smp_build_cpu_map
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__init
id|init_smp_config
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|smp_do_timer
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
id|smp_call_function_single
(paren
r_int
id|cpuid
comma
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
)paren
suffix:semicolon
r_extern
r_void
id|smp_send_reschedule
(paren
r_int
id|cpu
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
macro_line|#endif /* _ASM_IA64_SMP_H */
eof
