multiline_comment|/*&n; * SN2 Platform specific SMP Support&n; *&n; * Copyright (C) 2000-2002 Silicon Graphics, Inc. All rights reserved.&n; * &n; * This program is free software; you can redistribute it and/or modify it &n; * under the terms of version 2 of the GNU General Public License &n; * as published by the Free Software Foundation.&n; * &n; * This program is distributed in the hope that it would be useful, but &n; * WITHOUT ANY WARRANTY; without even the implied warranty of &n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. &n; * &n; * Further, this software is distributed without any warranty that it is &n; * free of the rightful claim of any third person regarding infringement &n; * or the like.  Any license provided herein, whether implied or &n; * otherwise, applies only to this software file.  Patent licenses, if &n; * any, provided herein do not apply to combinations of this program with &n; * other software, or any other product whatsoever.&n; * &n; * You should have received a copy of the GNU General Public &n; * License along with this program; if not, write the Free Software &n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; * &n; * Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pkwy, &n; * Mountain View, CA  94043, or:&n; * &n; * http://www.sgi.com &n; * &n; * For further information regarding this notice, see: &n; * &n; * http://oss.sgi.com/projects/GenInfo/NoticeExplan&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
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
id|__asm__
id|__volatile__
(paren
l_string|&quot;mf.a&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
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
macro_line|#ifdef PTCG_WAR
multiline_comment|/*&n; * The following structure is used to pass params thru smp_call_function&n; * to other cpus for flushing TLB ranges.&n; */
r_typedef
r_struct
(brace
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
DECL|member|end
r_int
r_int
id|end
suffix:semicolon
DECL|member|nbits
r_int
r_int
id|nbits
suffix:semicolon
DECL|member|rid
r_int
r_int
id|rid
suffix:semicolon
DECL|member|unfinished_count
id|atomic_t
id|unfinished_count
suffix:semicolon
DECL|member|fill
r_char
id|fill
(braket
l_int|96
)braket
suffix:semicolon
DECL|typedef|ptc_params_t
)brace
id|ptc_params_t
suffix:semicolon
DECL|macro|NUMPTC
mdefine_line|#define NUMPTC&t;512
DECL|variable|ptcParamArray
r_static
id|ptc_params_t
id|ptcParamArray
(braket
id|NUMPTC
)braket
id|__attribute__
c_func
(paren
(paren
id|__aligned__
c_func
(paren
l_int|128
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* use separate cache lines on ptcParamsNextByCpu to avoid false sharing */
DECL|variable|ptcParamsNextByCpu
r_static
id|ptc_params_t
op_star
id|ptcParamsNextByCpu
(braket
id|NR_CPUS
op_star
l_int|16
)braket
id|__attribute__
c_func
(paren
(paren
id|__aligned__
c_func
(paren
l_int|128
)paren
)paren
)paren
suffix:semicolon
DECL|variable|__cacheline_aligned
r_static
r_volatile
id|ptc_params_t
op_star
id|ptcParamsEmpty
id|__cacheline_aligned
suffix:semicolon
multiline_comment|/*REFERENCED*/
DECL|variable|__cacheline_aligned
r_static
id|spinlock_t
id|ptcParamsLock
id|__cacheline_aligned
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|ptcInit
r_static
r_int
id|ptcInit
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef PTCDEBUG
DECL|variable|ptcParamsAllBusy
r_static
r_int
id|ptcParamsAllBusy
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* debugging/statistics */
DECL|variable|ptcCountBacklog
r_static
r_int
id|ptcCountBacklog
op_assign
l_int|0
suffix:semicolon
DECL|variable|ptcBacklog
r_static
r_int
id|ptcBacklog
(braket
id|NUMPTC
op_plus
l_int|1
)braket
suffix:semicolon
DECL|variable|ptcParamsCounts
r_static
r_char
id|ptcParamsCounts
(braket
id|NR_CPUS
)braket
(braket
id|NUMPTC
)braket
id|__attribute__
c_func
(paren
(paren
id|__aligned__
c_func
(paren
l_int|128
)paren
)paren
)paren
suffix:semicolon
DECL|variable|ptcParamsResults
r_static
r_char
id|ptcParamsResults
(braket
id|NR_CPUS
)braket
(braket
id|NUMPTC
)braket
id|__attribute__
c_func
(paren
(paren
id|__aligned__
c_func
(paren
l_int|128
)paren
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Make smp_send_flush_tlbsmp_send_flush_tlb() a weak reference,&n; * so that we get a clean compile with the ia64 patch without the&n; * actual SN1 specific code in arch/ia64/kernel/smp.c.&n; */
r_extern
r_void
id|smp_send_flush_tlb
(paren
r_void
)paren
id|__attribute
c_func
(paren
(paren
id|weak
)paren
)paren
suffix:semicolon
multiline_comment|/**&n; * sn1_ptc_l_range - purge local translation cache&n; * @start: start of virtual address range&n; * @end: end of virtual address range&n; * @nbits: specifies number of bytes to purge per instruction (num = 1&lt;&lt;(nbits &amp; 0xfc))&n; *&n; * Purges the range specified from the local processor&squot;s translation cache&n; * (as opposed to the translation registers).  Note that more than the specified&n; * range *may* be cleared from the cache by some processors.&n; *&n; * This is probably not good enough, but I don&squot;t want to try to make it better &n; * until I get some statistics on a running system. At a minimum, we should only &n; * send IPIs to 1 processor in each TLB domain &amp; have it issue a ptc.g on it&squot;s &n; * own FSB. Also, we only have to serialize per FSB, not globally.&n; *&n; * More likely, we will have to do some work to reduce the frequency of calls to&n; * this routine.&n; */
r_static
r_inline
r_void
DECL|function|sn1_ptc_l_range
id|sn1_ptc_l_range
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
r_do
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;ptc.l %0,%1&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|start
)paren
comma
l_string|&quot;r&quot;
(paren
id|nbits
op_lshift
l_int|2
)paren
suffix:colon
l_string|&quot;memory&quot;
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
id|ia64_srlz_d
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * sn1_received_flush_tlb - cpu tlb flush routine&n; *&n; * Flushes the TLB of a given processor.&n; */
r_void
DECL|function|sn1_received_flush_tlb
id|sn1_received_flush_tlb
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|start
comma
id|end
comma
id|nbits
suffix:semicolon
r_int
r_int
id|rid
comma
id|saved_rid
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_int
id|result
suffix:semicolon
id|ptc_params_t
op_star
id|ptcParams
suffix:semicolon
id|ptcParams
op_assign
id|ptcParamsNextByCpu
(braket
id|cpu
op_star
l_int|16
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ptcParams
op_eq
id|ptcParamsEmpty
)paren
r_return
suffix:semicolon
r_do
(brace
id|start
op_assign
id|ptcParams-&gt;start
suffix:semicolon
id|saved_rid
op_assign
(paren
r_int
r_int
)paren
id|ia64_get_rr
c_func
(paren
id|start
)paren
suffix:semicolon
id|end
op_assign
id|ptcParams-&gt;end
suffix:semicolon
id|nbits
op_assign
id|ptcParams-&gt;nbits
suffix:semicolon
id|rid
op_assign
id|ptcParams-&gt;rid
suffix:semicolon
r_if
c_cond
(paren
id|saved_rid
op_ne
id|rid
)paren
(brace
id|ia64_set_rr
c_func
(paren
id|start
comma
(paren
r_int
r_int
)paren
id|rid
)paren
suffix:semicolon
id|ia64_srlz_d
c_func
(paren
)paren
suffix:semicolon
)brace
id|sn1_ptc_l_range
c_func
(paren
id|start
comma
id|end
comma
id|nbits
)paren
suffix:semicolon
r_if
c_cond
(paren
id|saved_rid
op_ne
id|rid
)paren
id|ia64_set_rr
c_func
(paren
id|start
comma
(paren
r_int
r_int
)paren
id|saved_rid
)paren
suffix:semicolon
id|ia64_srlz_i
c_func
(paren
)paren
suffix:semicolon
id|result
op_assign
id|atomic_dec
c_func
(paren
op_amp
id|ptcParams-&gt;unfinished_count
)paren
suffix:semicolon
macro_line|#ifdef PTCDEBUG
(brace
r_int
id|i
op_assign
id|ptcParams
op_minus
op_amp
id|ptcParamArray
(braket
l_int|0
)braket
suffix:semicolon
id|ptcParamsResults
(braket
id|cpu
)braket
(braket
id|i
)braket
op_assign
(paren
r_char
)paren
id|result
suffix:semicolon
id|ptcParamsCounts
(braket
id|cpu
)braket
(braket
id|i
)braket
op_increment
suffix:semicolon
)brace
macro_line|#endif /* PTCDEBUG */
r_if
c_cond
(paren
op_increment
id|ptcParams
op_eq
op_amp
id|ptcParamArray
(braket
id|NUMPTC
)braket
)paren
id|ptcParams
op_assign
op_amp
id|ptcParamArray
(braket
l_int|0
)braket
suffix:semicolon
)brace
r_while
c_loop
(paren
id|ptcParams
op_ne
id|ptcParamsEmpty
)paren
suffix:semicolon
id|ptcParamsNextByCpu
(braket
id|cpu
op_star
l_int|16
)braket
op_assign
id|ptcParams
suffix:semicolon
)brace
multiline_comment|/**&n; * sn1_global_tlb_purge - flush a translation cache range on all processors&n; * @start: start of virtual address range to flush&n; * @end: end of virtual address range&n; * @nbits: specifies number of bytes to purge per instruction (num = 1&lt;&lt;(nbits &amp; 0xfc))&n; *&n; * Flushes the translation cache of all processors from @start to @end.&n; */
r_void
DECL|function|sn1_global_tlb_purge
id|sn1_global_tlb_purge
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
id|ptc_params_t
op_star
id|params
suffix:semicolon
id|ptc_params_t
op_star
id|next
suffix:semicolon
r_int
r_int
id|irqflags
suffix:semicolon
macro_line|#ifdef PTCDEBUG
id|ptc_params_t
op_star
id|nextnext
suffix:semicolon
r_int
id|backlog
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|smp_num_cpus
op_eq
l_int|1
)paren
(brace
id|sn1_ptc_l_range
c_func
(paren
id|start
comma
id|end
comma
id|nbits
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; *  If at interrupt level and cannot get spinlock, &n;&t;&t; *  then do something useful by flushing own tlbflush queue&n;&t;&t; *  so as to avoid a possible deadlock.&n;&t;&t; */
r_while
c_loop
(paren
op_logical_neg
id|spin_trylock
c_func
(paren
op_amp
id|ptcParamsLock
)paren
)paren
(brace
id|local_irq_save
c_func
(paren
id|irqflags
)paren
suffix:semicolon
id|sn1_received_flush_tlb
c_func
(paren
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|irqflags
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
multiline_comment|/* take it easier on the bus */
)brace
)brace
r_else
(brace
id|spin_lock
c_func
(paren
op_amp
id|ptcParamsLock
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ptcInit
)paren
(brace
r_int
id|cpu
suffix:semicolon
id|ptcInit
op_assign
l_int|1
suffix:semicolon
id|memset
c_func
(paren
id|ptcParamArray
comma
l_int|0
comma
r_sizeof
(paren
id|ptcParamArray
)paren
)paren
suffix:semicolon
id|ptcParamsEmpty
op_assign
op_amp
id|ptcParamArray
(braket
l_int|0
)braket
suffix:semicolon
r_for
c_loop
(paren
id|cpu
op_assign
l_int|0
suffix:semicolon
id|cpu
OL
id|NR_CPUS
suffix:semicolon
id|cpu
op_increment
)paren
id|ptcParamsNextByCpu
(braket
id|cpu
op_star
l_int|16
)braket
op_assign
op_amp
id|ptcParamArray
(braket
l_int|0
)braket
suffix:semicolon
macro_line|#ifdef PTCDEBUG
id|memset
c_func
(paren
id|ptcBacklog
comma
l_int|0
comma
r_sizeof
(paren
id|ptcBacklog
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|ptcParamsCounts
comma
l_int|0
comma
r_sizeof
(paren
id|ptcParamsCounts
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|ptcParamsResults
comma
l_int|0
comma
r_sizeof
(paren
id|ptcParamsResults
)paren
)paren
suffix:semicolon
macro_line|#endif&t;/* PTCDEBUG */
)brace
id|params
op_assign
(paren
id|ptc_params_t
op_star
)paren
id|ptcParamsEmpty
suffix:semicolon
id|next
op_assign
(paren
id|ptc_params_t
op_star
)paren
id|ptcParamsEmpty
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|next
op_eq
op_amp
id|ptcParamArray
(braket
id|NUMPTC
)braket
)paren
id|next
op_assign
op_amp
id|ptcParamArray
(braket
l_int|0
)braket
suffix:semicolon
macro_line|#ifdef PTCDEBUG
id|nextnext
op_assign
id|next
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|nextnext
op_eq
op_amp
id|ptcParamArray
(braket
id|NUMPTC
)braket
)paren
id|nextnext
op_assign
op_amp
id|ptcParamArray
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ptcCountBacklog
)paren
(brace
multiline_comment|/* quick count of backlog */
id|ptc_params_t
op_star
id|ptr
suffix:semicolon
multiline_comment|/* check the current pointer to the beginning */
id|ptr
op_assign
id|params
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|ptr
op_ge
op_amp
id|ptcParamArray
(braket
l_int|0
)braket
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|ptr-&gt;unfinished_count
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
op_increment
id|backlog
suffix:semicolon
)brace
r_if
c_cond
(paren
id|backlog
)paren
(brace
multiline_comment|/* check the end of the array */
id|ptr
op_assign
op_amp
id|ptcParamArray
(braket
id|NUMPTC
)braket
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|ptr
OG
id|params
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|ptr-&gt;unfinished_count
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
op_increment
id|backlog
suffix:semicolon
)brace
)brace
id|ptcBacklog
(braket
id|backlog
)braket
op_increment
suffix:semicolon
)brace
macro_line|#endif&t;/* PTCDEBUG */
multiline_comment|/* wait for the next entry to clear...should be rare */
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|next-&gt;unfinished_count
)paren
OG
l_int|0
)paren
(brace
macro_line|#ifdef PTCDEBUG
id|ptcParamsAllBusy
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|nextnext-&gt;unfinished_count
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|next-&gt;unfinished_count
)paren
OG
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;&bslash;nnonzero next zero nextnext %lx %lx&bslash;n&quot;
comma
(paren
r_int
)paren
id|next
comma
(paren
r_int
)paren
id|nextnext
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
multiline_comment|/* it could be this cpu that is behind */
id|local_irq_save
c_func
(paren
id|irqflags
)paren
suffix:semicolon
id|sn1_received_flush_tlb
c_func
(paren
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|irqflags
)paren
suffix:semicolon
multiline_comment|/* now we know it&squot;s not this cpu, so just wait */
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|next-&gt;unfinished_count
)paren
OG
l_int|0
)paren
(brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
id|params-&gt;start
op_assign
id|start
suffix:semicolon
id|params-&gt;end
op_assign
id|end
suffix:semicolon
id|params-&gt;nbits
op_assign
id|nbits
suffix:semicolon
id|params-&gt;rid
op_assign
(paren
r_int
r_int
)paren
id|ia64_get_rr
c_func
(paren
id|start
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|params-&gt;unfinished_count
comma
id|smp_num_cpus
)paren
suffix:semicolon
multiline_comment|/* The atomic_set above can hit memory *after* the update&n;&t; * to ptcParamsEmpty below, which opens a timing window&n;&t; * that other cpus can squeeze into!&n;&t; */
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* everything is ready to process:&n;&t; *&t;-- global lock is held&n;&t; *&t;-- new entry + 1 is free&n;&t; *&t;-- new entry is set up&n;&t; * so now:&n;&t; *&t;-- update the global next pointer&n;&t; *&t;-- unlock the global lock&n;&t; *&t;-- send IPI to notify other cpus&n;&t; *&t;-- process the data ourselves&n;&t; */
id|ptcParamsEmpty
op_assign
id|next
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|ptcParamsLock
)paren
suffix:semicolon
id|smp_send_flush_tlb
c_func
(paren
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|irqflags
)paren
suffix:semicolon
id|sn1_received_flush_tlb
c_func
(paren
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|irqflags
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * Since IPIs are polled event (for now), we need to wait til the&n;&t; * TLB flush has started.&n;&t; * wait for the flush to complete &n;&t; */
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|params-&gt;unfinished_count
)paren
OG
l_int|0
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* PTCG_WAR */
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
multiline_comment|/*&n;&t; * Special case 1 cpu &amp; 1 node. Use local purges.&n;&t; */
macro_line|#ifdef PTCG_WAR
id|sn1_global_tlb_purge
c_func
(paren
id|start
comma
id|end
comma
id|nbits
)paren
suffix:semicolon
r_return
suffix:semicolon
macro_line|#endif /* PTCG_WAR */
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
id|local_nodeid
suffix:semicolon
multiline_comment|/* &n;&t; * For now, we dont want to spin uninterruptibly waiting&n;&t; * for the lock. Makes hangs hard to debug.&n;&t; */
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|spin_trylock
c_func
(paren
op_amp
id|sn2_global_ptc_lock
)paren
)paren
(brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
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
id|asm
r_volatile
(paren
l_string|&quot;ptc.ga %0,%1;;srlz.i;;&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|start
)paren
comma
l_string|&quot;r&quot;
(paren
id|nbits
op_lshift
l_int|2
)paren
suffix:colon
l_string|&quot;memory&quot;
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
)brace
)brace
r_if
c_cond
(paren
id|wait_piowc
c_func
(paren
)paren
op_amp
id|SH_PIO_WRITE_STATUS_0_WRITE_DEADLOCK_MASK
)paren
id|sn2_ptc_deadlock_recovery
c_func
(paren
id|data0
comma
id|data1
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
id|local_nodeid
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
suffix:semicolon
r_int
id|val
suffix:semicolon
r_volatile
r_int
op_star
id|p
suffix:semicolon
macro_line|#ifdef BUS_INT_WAR
r_if
c_cond
(paren
id|vector
op_ne
id|ap_wakeup_vector
op_logical_and
id|delivery_mode
op_eq
id|IA64_IPI_DM_INT
)paren
(brace
r_return
suffix:semicolon
)brace
macro_line|#endif
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
id|pio_phys_write_mmr
c_func
(paren
id|p
comma
id|val
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SHUB_1_0_SPECIFIC
multiline_comment|/* doesnt work on shub 1.0 */
id|wait_piowc
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
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
