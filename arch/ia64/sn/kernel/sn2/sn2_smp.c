multiline_comment|/*&n; * SN2 Platform specific SMP Support&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000-2004 Silicon Graphics, Inc. All rights reserved.&n; */
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
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/nodemask.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/tlb.h&gt;
macro_line|#include &lt;asm/numa.h&gt;
macro_line|#include &lt;asm/hw_irq.h&gt;
macro_line|#include &lt;asm/current.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
macro_line|#include &lt;asm/sn/sn_sal.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/shub_mmr.h&gt;
macro_line|#include &lt;asm/sn/nodepda.h&gt;
macro_line|#include &lt;asm/sn/rw_mmr.h&gt;
r_void
id|sn2_ptc_deadlock_recovery
c_func
(paren
r_volatile
r_int
r_int
op_star
comma
r_int
r_int
id|data0
comma
r_volatile
r_int
r_int
op_star
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
DECL|function|wait_piowc
r_static
r_inline
r_int
r_int
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
comma
id|zeroval
suffix:semicolon
r_int
r_int
id|ws
suffix:semicolon
id|piows
op_assign
id|pda-&gt;pio_write_status_addr
suffix:semicolon
id|zeroval
op_assign
id|pda-&gt;pio_write_status_val
suffix:semicolon
r_do
(brace
id|cpu_relax
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
id|SH_PIO_WRITE_STATUS_PENDING_WRITE_COUNT_MASK
)paren
op_ne
id|zeroval
)paren
suffix:semicolon
r_return
id|ws
suffix:semicolon
)brace
DECL|function|sn_tlb_migrate_finish
r_void
id|sn_tlb_migrate_finish
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_if
c_cond
(paren
id|mm
op_eq
id|current-&gt;mm
)paren
id|flush_tlb_mm
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * sn2_global_tlb_purge - globally purge translation cache of virtual address range&n; * @start: start of virtual address range&n; * @end: end of virtual address range&n; * @nbits: specifies number of bytes to purge per instruction (num = 1&lt;&lt;(nbits &amp; 0xfc))&n; *&n; * Purges the translation caches of all processors of the given virtual address&n; * range.&n; *&n; * Note:&n; * &t;- cpu_vm_mask is a bit mask that indicates which cpus have loaded the context.&n; * &t;- cpu_vm_mask is converted into a nodemask of the nodes containing the&n; * &t;  cpus in cpu_vm_mask.&n; *&t;- if only one bit is set in cpu_vm_mask &amp; it is the current cpu,&n; *&t;  then only the local TLB needs to be flushed. This flushing can be done&n; *&t;  using ptc.l. This is the common case &amp; avoids the global spinlock.&n; *&t;- if multiple cpus have loaded the context, then flushing has to be&n; *&t;  done with ptc.g/MMRs under protection of the global ptc_lock.&n; */
r_void
DECL|function|sn2_global_tlb_purge
id|sn2_global_tlb_purge
c_func
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
id|i
comma
id|shub1
comma
id|cnode
comma
id|mynasid
comma
id|cpu
comma
id|lcpu
op_assign
l_int|0
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
op_assign
l_int|0
comma
id|data1
op_assign
l_int|0
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|current-&gt;active_mm
suffix:semicolon
r_int
id|nasids
(braket
id|MAX_NUMNODES
)braket
comma
id|nix
suffix:semicolon
id|nodemask_t
id|nodes_flushed
suffix:semicolon
id|nodes_clear
c_func
(paren
id|nodes_flushed
)paren
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
id|for_each_cpu_mask
c_func
(paren
id|cpu
comma
id|mm-&gt;cpu_vm_mask
)paren
(brace
id|cnode
op_assign
id|cpu_to_node
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|node_set
c_func
(paren
id|cnode
comma
id|nodes_flushed
)paren
suffix:semicolon
id|lcpu
op_assign
id|cpu
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|i
op_eq
l_int|1
op_logical_and
id|lcpu
op_eq
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
(brace
r_do
(brace
id|ia64_ptcl
c_func
(paren
id|start
comma
id|nbits
op_lshift
l_int|2
)paren
suffix:semicolon
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
id|ia64_srlz_i
c_func
(paren
)paren
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|mm-&gt;mm_users
)paren
op_eq
l_int|1
)paren
(brace
id|flush_tlb_mm
c_func
(paren
id|mm
)paren
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|nix
op_assign
l_int|0
suffix:semicolon
id|for_each_node_mask
c_func
(paren
id|cnode
comma
id|nodes_flushed
)paren
id|nasids
(braket
id|nix
op_increment
)braket
op_assign
id|cnodeid_to_nasid
c_func
(paren
id|cnode
)paren
suffix:semicolon
id|shub1
op_assign
id|is_shub1
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shub1
)paren
(brace
id|data0
op_assign
(paren
l_int|1UL
op_lshift
id|SH1_PTC_0_A_SHFT
)paren
op_or
(paren
id|nbits
op_lshift
id|SH1_PTC_0_PS_SHFT
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
id|SH1_PTC_0_RID_SHFT
)paren
op_or
(paren
l_int|1UL
op_lshift
id|SH1_PTC_0_START_SHFT
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
id|SH1_PTC_0
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
id|SH1_PTC_1
)paren
suffix:semicolon
)brace
r_else
(brace
id|data0
op_assign
(paren
l_int|1UL
op_lshift
id|SH2_PTC_A_SHFT
)paren
op_or
(paren
id|nbits
op_lshift
id|SH2_PTC_PS_SHFT
)paren
op_or
(paren
l_int|1UL
op_lshift
id|SH2_PTC_START_SHFT
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
id|SH2_PTC
op_plus
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
id|SH2_PTC_RID_SHFT
)paren
)paren
suffix:semicolon
id|ptc1
op_assign
l_int|NULL
suffix:semicolon
)brace
id|mynasid
op_assign
id|get_nasid
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
r_if
c_cond
(paren
id|shub1
)paren
id|data1
op_assign
id|start
op_or
(paren
l_int|1UL
op_lshift
id|SH1_PTC_1_START_SHFT
)paren
suffix:semicolon
r_else
id|data0
op_assign
(paren
id|data0
op_amp
op_complement
id|SH2_PTC_ADDR_MASK
)paren
op_or
(paren
id|start
op_amp
id|SH2_PTC_ADDR_MASK
)paren
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
id|nix
suffix:semicolon
id|i
op_increment
)paren
(brace
id|nasid
op_assign
id|nasids
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|nasid
op_eq
id|mynasid
)paren
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
r_if
c_cond
(paren
id|ptc1
)paren
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
id|SH_PIO_WRITE_STATUS_WRITE_DEADLOCK_MASK
)paren
)paren
(brace
id|sn2_ptc_deadlock_recovery
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
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * sn2_ptc_deadlock_recovery&n; *&n; * Recover from PTC deadlocks conditions. Recovery requires stepping thru each &n; * TLB flush transaction.  The recovery sequence is somewhat tricky &amp; is&n; * coded in assembly language.&n; */
DECL|function|sn2_ptc_deadlock_recovery
r_void
id|sn2_ptc_deadlock_recovery
c_func
(paren
r_volatile
r_int
r_int
op_star
id|ptc0
comma
r_int
r_int
id|data0
comma
r_volatile
r_int
r_int
op_star
id|ptc1
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
r_volatile
r_int
r_int
op_star
comma
r_int
r_int
comma
r_volatile
r_int
r_int
op_star
comma
r_int
r_int
comma
r_volatile
r_int
r_int
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|cnode
comma
id|mycnode
comma
id|nasid
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|piows
suffix:semicolon
r_volatile
r_int
r_int
id|zeroval
suffix:semicolon
id|sn2_ptc_deadlock_count
op_increment
suffix:semicolon
id|piows
op_assign
id|pda-&gt;pio_write_status_addr
suffix:semicolon
id|zeroval
op_assign
id|pda-&gt;pio_write_status_val
suffix:semicolon
id|mycnode
op_assign
id|numa_node_id
c_func
(paren
)paren
suffix:semicolon
id|for_each_online_node
c_func
(paren
id|cnode
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
r_if
c_cond
(paren
id|ptc1
)paren
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
comma
id|zeroval
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * sn_send_IPI_phys - send an IPI to a Nasid and slice&n; * @nasid: nasid to receive the interrupt (may be outside partition)&n; * @physid: physical cpuid to receive the interrupt.&n; * @vector: command to send&n; * @delivery_mode: delivery mechanism&n; *&n; * Sends an IPI (interprocessor interrupt) to the processor specified by&n; * @physid&n; *&n; * @delivery_mode can be one of the following&n; *&n; * %IA64_IPI_DM_INT - pend an interrupt&n; * %IA64_IPI_DM_PMI - pend a PMI&n; * %IA64_IPI_DM_NMI - pend an NMI&n; * %IA64_IPI_DM_INIT - pend an INIT interrupt&n; */
DECL|function|sn_send_IPI_phys
r_void
id|sn_send_IPI_phys
c_func
(paren
r_int
id|nasid
comma
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
DECL|function|sn2_send_IPI
r_void
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
r_int
id|nasid
suffix:semicolon
id|physid
op_assign
id|cpu_physical_id
c_func
(paren
id|cpuid
)paren
suffix:semicolon
id|nasid
op_assign
id|cpuid_to_nasid
c_func
(paren
id|cpuid
)paren
suffix:semicolon
multiline_comment|/* the following is used only when starting cpus at boot time */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|nasid
op_eq
op_minus
l_int|1
)paren
)paren
id|ia64_sn_get_sapic_info
c_func
(paren
id|physid
comma
op_amp
id|nasid
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|sn_send_IPI_phys
c_func
(paren
id|nasid
comma
id|physid
comma
id|vector
comma
id|delivery_mode
)paren
suffix:semicolon
)brace
eof
