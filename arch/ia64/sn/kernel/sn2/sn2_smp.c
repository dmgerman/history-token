multiline_comment|/*&n; * SN2 Platform specific SMP Support&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/hw_irq.h&gt;
macro_line|#include &lt;asm/current.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/sn2/shub_mmr.h&gt;
macro_line|#include &lt;asm/sn/nodepda.h&gt;
macro_line|#include &lt;asm/sn/rw_mmr.h&gt;
r_void
id|sn2_ptc_deadlock_recovery
c_func
(paren
r_int
r_int
id|data0
comma
r_int
r_int
id|data1
)paren
suffix:semicolon
DECL|variable|__cacheline_aligned
r_static
id|spinlock_t
id|sn2_global_ptc_lock
id|__cacheline_aligned
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|sn2_ptc_deadlock_count
r_static
r_int
r_int
id|sn2_ptc_deadlock_count
suffix:semicolon
r_static
r_inline
r_int
r_int
DECL|function|wait_piowc
id|wait_piowc
c_func
(paren
r_void
)paren
(brace
r_volatile
r_int
r_int
op_star
id|piows
suffix:semicolon
r_int
r_int
id|ws
suffix:semicolon
id|piows
op_assign
id|pda-&gt;pio_write_status_addr
suffix:semicolon
r_do
(brace
id|ia64_mfa
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
(paren
id|ws
op_assign
op_star
id|piows
)paren
op_amp
id|SH_PIO_WRITE_STATUS_0_PENDING_WRITE_COUNT_MASK
)paren
op_ne
id|SH_PIO_WRITE_STATUS_0_PENDING_WRITE_COUNT_MASK
)paren
suffix:semicolon
r_return
id|ws
suffix:semicolon
)brace
multiline_comment|/**&n; * sn2_global_tlb_purge - globally purge translation cache of virtual address range&n; * @start: start of virtual address range&n; * @end: end of virtual address range&n; * @nbits: specifies number of bytes to purge per instruction (num = 1&lt;&lt;(nbits &amp; 0xfc))&n; *&n; * Purges the translation caches of all processors of the given virtual address&n; * range.&n; */
r_void
DECL|function|sn2_global_tlb_purge
id|sn2_global_tlb_purge
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
r_int
r_int
id|nbits
)paren
(brace
r_int
id|cnode
comma
id|mycnode
comma
id|nasid
comma
id|flushed
op_assign
l_int|0
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|ptc0
comma
op_star
id|ptc1
suffix:semicolon
r_int
r_int
id|flags
op_assign
l_int|0
comma
id|data0
comma
id|data1
suffix:semicolon
id|data0
op_assign
(paren
l_int|1UL
op_lshift
id|SH_PTC_0_A_SHFT
)paren
op_or
(paren
id|nbits
op_lshift
id|SH_PTC_0_PS_SHFT
)paren
op_or
(paren
(paren
id|ia64_get_rr
c_func
(paren
id|start
)paren
op_rshift
l_int|8
)paren
op_lshift
id|SH_PTC_0_RID_SHFT
)paren
op_or
(paren
l_int|1UL
op_lshift
id|SH_PTC_0_START_SHFT
)paren
suffix:semicolon
id|ptc0
op_assign
(paren
r_int
op_star
)paren
id|GLOBAL_MMR_PHYS_ADDR
c_func
(paren
l_int|0
comma
id|SH_PTC_0
)paren
suffix:semicolon
id|ptc1
op_assign
(paren
r_int
op_star
)paren
id|GLOBAL_MMR_PHYS_ADDR
c_func
(paren
l_int|0
comma
id|SH_PTC_1
)paren
suffix:semicolon
id|mycnode
op_assign
id|numa_node_id
c_func
(paren
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|sn2_global_ptc_lock
comma
id|flags
)paren
suffix:semicolon
r_do
(brace
id|data1
op_assign
id|start
op_or
(paren
l_int|1UL
op_lshift
id|SH_PTC_1_START_SHFT
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cnode
op_assign
l_int|0
suffix:semicolon
id|cnode
OL
id|numnodes
suffix:semicolon
id|cnode
op_increment
)paren
(brace
r_if
c_cond
(paren
id|is_headless_node
c_func
(paren
id|cnode
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|cnode
op_eq
id|mycnode
)paren
(brace
id|ia64_ptcga
c_func
(paren
id|start
comma
id|nbits
op_lshift
l_int|2
)paren
suffix:semicolon
id|ia64_srlz_i
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|nasid
op_assign
id|cnodeid_to_nasid
c_func
(paren
id|cnode
)paren
suffix:semicolon
id|ptc0
op_assign
id|CHANGE_NASID
c_func
(paren
id|nasid
comma
id|ptc0
)paren
suffix:semicolon
id|ptc1
op_assign
id|CHANGE_NASID
c_func
(paren
id|nasid
comma
id|ptc1
)paren
suffix:semicolon
id|pio_atomic_phys_write_mmrs
c_func
(paren
id|ptc0
comma
id|data0
comma
id|ptc1
comma
id|data1
)paren
suffix:semicolon
id|flushed
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|flushed
op_logical_and
(paren
id|wait_piowc
c_func
(paren
)paren
op_amp
id|SH_PIO_WRITE_STATUS_0_WRITE_DEADLOCK_MASK
)paren
)paren
(brace
id|sn2_ptc_deadlock_recovery
c_func
(paren
id|data0
comma
id|data1
)paren
suffix:semicolon
)brace
id|start
op_add_assign
(paren
l_int|1UL
op_lshift
id|nbits
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|start
OL
id|end
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|sn2_global_ptc_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * sn2_ptc_deadlock_recovery&n; *&n; * Recover from PTC deadlocks conditions. Recovery requires stepping thru each &n; * TLB flush transaction.  The recovery sequence is somewhat tricky &amp; is&n; * coded in assembly language.&n; */
r_void
DECL|function|sn2_ptc_deadlock_recovery
id|sn2_ptc_deadlock_recovery
c_func
(paren
r_int
r_int
id|data0
comma
r_int
r_int
id|data1
)paren
(brace
r_extern
r_void
id|sn2_ptc_deadlock_recovery_core
c_func
(paren
r_int
op_star
comma
r_int
comma
r_int
op_star
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
r_int
id|cnode
comma
id|mycnode
comma
id|nasid
suffix:semicolon
r_int
op_star
id|ptc0
comma
op_star
id|ptc1
comma
op_star
id|piows
suffix:semicolon
id|sn2_ptc_deadlock_count
op_increment
suffix:semicolon
id|ptc0
op_assign
(paren
r_int
op_star
)paren
id|GLOBAL_MMR_PHYS_ADDR
c_func
(paren
l_int|0
comma
id|SH_PTC_0
)paren
suffix:semicolon
id|ptc1
op_assign
(paren
r_int
op_star
)paren
id|GLOBAL_MMR_PHYS_ADDR
c_func
(paren
l_int|0
comma
id|SH_PTC_1
)paren
suffix:semicolon
id|piows
op_assign
(paren
r_int
op_star
)paren
id|pda-&gt;pio_write_status_addr
suffix:semicolon
id|mycnode
op_assign
id|numa_node_id
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cnode
op_assign
l_int|0
suffix:semicolon
id|cnode
OL
id|numnodes
suffix:semicolon
id|cnode
op_increment
)paren
(brace
r_if
c_cond
(paren
id|is_headless_node
c_func
(paren
id|cnode
)paren
op_logical_or
id|cnode
op_eq
id|mycnode
)paren
r_continue
suffix:semicolon
id|nasid
op_assign
id|cnodeid_to_nasid
c_func
(paren
id|cnode
)paren
suffix:semicolon
id|ptc0
op_assign
id|CHANGE_NASID
c_func
(paren
id|nasid
comma
id|ptc0
)paren
suffix:semicolon
id|ptc1
op_assign
id|CHANGE_NASID
c_func
(paren
id|nasid
comma
id|ptc1
)paren
suffix:semicolon
id|sn2_ptc_deadlock_recovery_core
c_func
(paren
id|ptc0
comma
id|data0
comma
id|ptc1
comma
id|data1
comma
id|piows
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * sn_send_IPI_phys - send an IPI to a Nasid and slice&n; * @physid: physical cpuid to receive the interrupt.&n; * @vector: command to send&n; * @delivery_mode: delivery mechanism&n; *&n; * Sends an IPI (interprocessor interrupt) to the processor specified by&n; * @physid&n; *&n; * @delivery_mode can be one of the following&n; *&n; * %IA64_IPI_DM_INT - pend an interrupt&n; * %IA64_IPI_DM_PMI - pend a PMI&n; * %IA64_IPI_DM_NMI - pend an NMI&n; * %IA64_IPI_DM_INIT - pend an INIT interrupt&n; */
r_void
DECL|function|sn_send_IPI_phys
id|sn_send_IPI_phys
c_func
(paren
r_int
id|physid
comma
r_int
id|vector
comma
r_int
id|delivery_mode
)paren
(brace
r_int
id|nasid
comma
id|slice
comma
id|val
suffix:semicolon
r_int
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
r_volatile
r_int
op_star
id|p
suffix:semicolon
id|nasid
op_assign
id|cpu_physical_id_to_nasid
c_func
(paren
id|physid
)paren
suffix:semicolon
id|slice
op_assign
id|cpu_physical_id_to_slice
c_func
(paren
id|physid
)paren
suffix:semicolon
id|p
op_assign
(paren
r_int
op_star
)paren
id|GLOBAL_MMR_PHYS_ADDR
c_func
(paren
id|nasid
comma
id|SH_IPI_INT
)paren
suffix:semicolon
id|val
op_assign
(paren
l_int|1UL
op_lshift
id|SH_IPI_INT_SEND_SHFT
)paren
op_or
(paren
id|physid
op_lshift
id|SH_IPI_INT_PID_SHFT
)paren
op_or
(paren
(paren
r_int
)paren
id|delivery_mode
op_lshift
id|SH_IPI_INT_TYPE_SHFT
)paren
op_or
(paren
(paren
r_int
)paren
id|vector
op_lshift
id|SH_IPI_INT_IDX_SHFT
)paren
op_or
(paren
l_int|0x000feeUL
op_lshift
id|SH_IPI_INT_BASE_SHFT
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|enable_shub_wars_1_1
c_func
(paren
)paren
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|sn2_global_ptc_lock
comma
id|flags
)paren
suffix:semicolon
)brace
id|pio_phys_write_mmr
c_func
(paren
id|p
comma
id|val
)paren
suffix:semicolon
r_if
c_cond
(paren
id|enable_shub_wars_1_1
c_func
(paren
)paren
)paren
(brace
id|wait_piowc
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|sn2_global_ptc_lock
comma
id|flags
)paren
suffix:semicolon
)brace
)brace
DECL|variable|sn_send_IPI_phys
id|EXPORT_SYMBOL
c_func
(paren
id|sn_send_IPI_phys
)paren
suffix:semicolon
multiline_comment|/**&n; * sn2_send_IPI - send an IPI to a processor&n; * @cpuid: target of the IPI&n; * @vector: command to send&n; * @delivery_mode: delivery mechanism&n; * @redirect: redirect the IPI?&n; *&n; * Sends an IPI (InterProcessor Interrupt) to the processor specified by&n; * @cpuid.  @vector specifies the command to send, while @delivery_mode can &n; * be one of the following&n; *&n; * %IA64_IPI_DM_INT - pend an interrupt&n; * %IA64_IPI_DM_PMI - pend a PMI&n; * %IA64_IPI_DM_NMI - pend an NMI&n; * %IA64_IPI_DM_INIT - pend an INIT interrupt&n; */
r_void
DECL|function|sn2_send_IPI
id|sn2_send_IPI
c_func
(paren
r_int
id|cpuid
comma
r_int
id|vector
comma
r_int
id|delivery_mode
comma
r_int
id|redirect
)paren
(brace
r_int
id|physid
suffix:semicolon
id|physid
op_assign
id|cpu_physical_id
c_func
(paren
id|cpuid
)paren
suffix:semicolon
id|sn_send_IPI_phys
c_func
(paren
id|physid
comma
id|vector
comma
id|delivery_mode
)paren
suffix:semicolon
)brace
eof
