multiline_comment|/*&n; * Copyright (C) 2001 Broadcom Corporation&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_regs.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_int.h&gt;
r_extern
id|irqreturn_t
id|smp_call_function_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|smp_tune_scheduling
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * These are routines for dealing with the sb1250 smp capabilities&n; * independent of board/firmware&n; */
DECL|variable|mailbox_set_regs
r_static
id|u64
id|mailbox_set_regs
(braket
)braket
op_assign
(brace
id|KSEG1
op_plus
id|A_IMR_CPU0_BASE
op_plus
id|R_IMR_MAILBOX_SET_CPU
comma
id|KSEG1
op_plus
id|A_IMR_CPU1_BASE
op_plus
id|R_IMR_MAILBOX_SET_CPU
)brace
suffix:semicolon
DECL|variable|mailbox_clear_regs
r_static
id|u64
id|mailbox_clear_regs
(braket
)braket
op_assign
(brace
id|KSEG1
op_plus
id|A_IMR_CPU0_BASE
op_plus
id|R_IMR_MAILBOX_CLR_CPU
comma
id|KSEG1
op_plus
id|A_IMR_CPU1_BASE
op_plus
id|R_IMR_MAILBOX_CLR_CPU
)brace
suffix:semicolon
DECL|variable|mailbox_regs
r_static
id|u64
id|mailbox_regs
(braket
)braket
op_assign
(brace
id|KSEG1
op_plus
id|A_IMR_CPU0_BASE
op_plus
id|R_IMR_MAILBOX_CPU
comma
id|KSEG1
op_plus
id|A_IMR_CPU1_BASE
op_plus
id|R_IMR_MAILBOX_CPU
)brace
suffix:semicolon
multiline_comment|/*&n; * Simple enough; everything is set up, so just poke the appropriate mailbox&n; * register, and we should be set&n; */
DECL|function|core_send_ipi
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
(brace
id|__raw_writeq
c_func
(paren
(paren
(paren
(paren
id|u64
)paren
id|action
)paren
op_lshift
l_int|48
)paren
comma
id|mailbox_set_regs
(braket
id|cpu
)braket
)paren
suffix:semicolon
)brace
DECL|function|sb1250_smp_finish
r_void
id|sb1250_smp_finish
c_func
(paren
r_void
)paren
(brace
r_extern
r_void
id|sb1_sanitize_tlb
c_func
(paren
r_void
)paren
suffix:semicolon
id|sb1_sanitize_tlb
c_func
(paren
)paren
suffix:semicolon
id|sb1250_time_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|sb1250_mailbox_interrupt
r_void
id|sb1250_mailbox_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_int
r_int
id|action
suffix:semicolon
id|kstat_this_cpu.irqs
(braket
id|K_INT_MBOX_0
)braket
op_increment
suffix:semicolon
multiline_comment|/* Load the mailbox register to figure out what we&squot;re supposed to do */
id|action
op_assign
(paren
id|__raw_readq
c_func
(paren
id|mailbox_regs
(braket
id|cpu
)braket
)paren
op_rshift
l_int|48
)paren
op_amp
l_int|0xffff
suffix:semicolon
multiline_comment|/* Clear the mailbox to clear the interrupt */
id|__raw_writeq
c_func
(paren
(paren
(paren
id|u64
)paren
id|action
)paren
op_lshift
l_int|48
comma
id|mailbox_clear_regs
(braket
id|cpu
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Nothing to do for SMP_RESCHEDULE_YOURSELF; returning from the&n;&t; * interrupt will do the reschedule for us&n;&t; */
r_if
c_cond
(paren
id|action
op_amp
id|SMP_CALL_FUNCTION
)paren
(brace
id|smp_call_function_interrupt
c_func
(paren
l_int|0
comma
l_int|NULL
comma
id|regs
)paren
suffix:semicolon
)brace
)brace
r_extern
id|atomic_t
id|cpus_booted
suffix:semicolon
r_extern
r_void
id|prom_setup_smp
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|prom_boot_secondary
c_func
(paren
r_int
id|cpu
comma
r_int
r_int
id|sp
comma
r_int
r_int
id|gp
)paren
suffix:semicolon
DECL|function|smp_boot_cpus
r_void
id|__init
id|smp_boot_cpus
c_func
(paren
r_void
)paren
(brace
r_int
id|cur_cpu
op_assign
l_int|0
suffix:semicolon
r_int
id|cpu
suffix:semicolon
id|prom_setup_smp
c_func
(paren
)paren
suffix:semicolon
id|init_new_context
c_func
(paren
id|current
comma
op_amp
id|init_mm
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
id|cpu_data
(braket
l_int|0
)braket
dot
id|udelay_val
op_assign
id|loops_per_jiffy
suffix:semicolon
id|cpu_data
(braket
l_int|0
)braket
dot
id|asid_cache
op_assign
id|ASID_FIRST_VERSION
suffix:semicolon
id|cpus_clear
c_func
(paren
id|cpu_online_map
)paren
suffix:semicolon
id|cpu_set
c_func
(paren
l_int|0
comma
id|cpu_online_map
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|cpus_booted
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Master CPU is already booted... */
id|smp_tune_scheduling
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This loop attempts to compensate for &quot;holes&quot; in the CPU&n;&t; * numbering.  It&squot;s overkill, but general.&n;&t; */
r_for
c_loop
(paren
id|cpu
op_assign
l_int|1
suffix:semicolon
id|cpu
OL
id|num_online_cpus
c_func
(paren
)paren
suffix:semicolon
)paren
(brace
r_struct
id|task_struct
op_star
id|idle
suffix:semicolon
r_struct
id|pt_regs
id|regs
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Starting CPU %d... &quot;
comma
id|cpu
)paren
suffix:semicolon
multiline_comment|/* Spawn a new process normally.  Grab a pointer to&n;&t;&t;   its task struct so we can mess with it */
id|idle
op_assign
id|copy_process
c_func
(paren
id|CLONE_VM
op_or
id|CLONE_IDLETASK
comma
l_int|0
comma
op_amp
id|regs
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
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
multiline_comment|/*&n;&t;&t; * We remove it from the pidhash and the runqueue&n;&t;&t; * once we got the process:&n;&t;&t; */
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
r_do
(brace
multiline_comment|/* Iterate until we find a CPU that comes up */
id|cur_cpu
op_increment
suffix:semicolon
id|retval
op_assign
id|prom_boot_secondary
c_func
(paren
id|cur_cpu
comma
(paren
r_int
r_int
)paren
id|idle
op_plus
id|THREAD_SIZE
op_minus
l_int|32
comma
(paren
r_int
r_int
)paren
id|idle
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|retval
op_logical_and
(paren
id|cur_cpu
OL
id|NR_CPUS
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|cpu
op_increment
suffix:semicolon
)brace
r_else
(brace
id|panic
c_func
(paren
l_string|&quot;CPU discovery disaster&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Wait for everyone to come up */
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|cpus_booted
)paren
op_ne
id|num_online_cpus
c_func
(paren
)paren
)paren
suffix:semicolon
id|smp_threads_ready
op_assign
l_int|1
suffix:semicolon
)brace
eof
