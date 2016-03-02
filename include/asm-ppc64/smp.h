multiline_comment|/* &n; * smp.h: PPC64 specific SMP code.&n; *&n; * Original was a copy of sparc smp.h.  Now heavily modified&n; * for PPC.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1996-2001 Cort Dougan &lt;cort@fsmlabs.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC64_SMP_H
DECL|macro|_PPC64_SMP_H
mdefine_line|#define _PPC64_SMP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/cpumask.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/paca.h&gt;
macro_line|#ifdef CONFIG_SMP
r_extern
r_void
id|smp_send_debugger_break
c_func
(paren
r_int
id|cpu
)paren
suffix:semicolon
r_struct
id|pt_regs
suffix:semicolon
r_extern
r_void
id|smp_message_recv
c_func
(paren
r_int
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|macro|smp_processor_id
mdefine_line|#define smp_processor_id() (get_paca()-&gt;paca_index)
DECL|macro|hard_smp_processor_id
mdefine_line|#define hard_smp_processor_id() (get_paca()-&gt;hw_cpu_id)
multiline_comment|/*&n; * Retrieve the state of a CPU:&n; * online:          CPU is in a normal run state&n; * possible:        CPU is a candidate to be made online&n; * available:       CPU is candidate for the &squot;possible&squot; pool&n; *                  Used to get SMT threads started at boot time.&n; * present_at_boot: CPU was available at boot time.  Used in DLPAR&n; *                  code to handle special cases for processor start up.&n; */
r_extern
id|cpumask_t
id|cpu_present_at_boot
suffix:semicolon
r_extern
id|cpumask_t
id|cpu_online_map
suffix:semicolon
r_extern
id|cpumask_t
id|cpu_possible_map
suffix:semicolon
r_extern
id|cpumask_t
id|cpu_available_map
suffix:semicolon
DECL|macro|cpu_present_at_boot
mdefine_line|#define cpu_present_at_boot(cpu) cpu_isset(cpu, cpu_present_at_boot)
DECL|macro|cpu_available
mdefine_line|#define cpu_available(cpu)       cpu_isset(cpu, cpu_available_map) 
multiline_comment|/* Since OpenPIC has only 4 IPIs, we use slightly different message numbers.&n; *&n; * Make sure this matches openpic_request_IPIs in open_pic.c, or what shows up&n; * in /proc/interrupts will be wrong!!! --Troy */
DECL|macro|PPC_MSG_CALL_FUNCTION
mdefine_line|#define PPC_MSG_CALL_FUNCTION   0
DECL|macro|PPC_MSG_RESCHEDULE
mdefine_line|#define PPC_MSG_RESCHEDULE      1
multiline_comment|/* This is unused now */
macro_line|#if 0
mdefine_line|#define PPC_MSG_MIGRATE_TASK    2
macro_line|#endif
DECL|macro|PPC_MSG_DEBUGGER_BREAK
mdefine_line|#define PPC_MSG_DEBUGGER_BREAK  3
r_extern
id|cpumask_t
id|irq_affinity
(braket
)braket
suffix:semicolon
r_void
id|smp_init_iSeries
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|smp_init_pSeries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|__cpu_disable
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__cpu_die
c_func
(paren
r_int
r_int
id|cpu
)paren
suffix:semicolon
r_extern
r_void
id|cpu_die
c_func
(paren
r_void
)paren
id|__attribute__
c_func
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
macro_line|#endif /* !(CONFIG_SMP) */
DECL|macro|get_hard_smp_processor_id
mdefine_line|#define get_hard_smp_processor_id(CPU) (paca[(CPU)].hw_cpu_id)
DECL|macro|set_hard_smp_processor_id
mdefine_line|#define set_hard_smp_processor_id(CPU, VAL) &bslash;&n;&t;do { (paca[(CPU)].hw_proc_num = (VAL)); } while (0)
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* !(_PPC64_SMP_H) */
macro_line|#endif /* __KERNEL__ */
eof
