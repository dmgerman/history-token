multiline_comment|/*&n; * SN1 Platform specific synergy Support&n; *&n; * Copyright (C) 2000-2002 Silicon Graphics, Inc. All rights reserved.&n; * &n; * This program is free software; you can redistribute it and/or modify it &n; * under the terms of version 2 of the GNU General Public License &n; * as published by the Free Software Foundation.&n; * &n; * This program is distributed in the hope that it would be useful, but &n; * WITHOUT ANY WARRANTY; without even the implied warranty of &n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. &n; * &n; * Further, this software is distributed without any warranty that it is &n; * free of the rightful claim of any third person regarding infringement &n; * or the like.  Any license provided herein, whether implied or &n; * otherwise, applies only to this software file.  Patent licenses, if &n; * any, provided herein do not apply to combinations of this program with &n; * other software, or any other product whatsoever.&n; * &n; * You should have received a copy of the GNU General Public &n; * License along with this program; if not, write the Free Software &n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; * &n; * Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pkwy, &n; * Mountain View, CA  94043, or:&n; * &n; * http://www.sgi.com &n; * &n; * For further information regarding this notice, see: &n; * &n; * http://oss.sgi.com/projects/GenInfo/NoticeExplan&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
macro_line|#include &lt;asm/sn/sn1/bedrock.h&gt;
macro_line|#include &lt;asm/sn/intr.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/nodepda.h&gt;
macro_line|#include &lt;asm/sn/sn1/synergy.h&gt;
macro_line|#include &lt;asm/sn/sndrv.h&gt;
r_int
id|bit_pos_to_irq
c_func
(paren
r_int
id|bit
)paren
suffix:semicolon
r_void
id|setclear_mask_b
c_func
(paren
r_int
id|irq
comma
r_int
id|cpuid
comma
r_int
id|set
)paren
suffix:semicolon
r_void
id|setclear_mask_a
c_func
(paren
r_int
id|irq
comma
r_int
id|cpuid
comma
r_int
id|set
)paren
suffix:semicolon
r_void
op_star
id|kmalloc
c_func
(paren
r_int
id|size
comma
r_int
id|flags
)paren
suffix:semicolon
DECL|variable|synergy_perf_initialized
r_static
r_int
id|synergy_perf_initialized
op_assign
l_int|0
suffix:semicolon
r_void
DECL|function|synergy_intr_alloc
id|synergy_intr_alloc
c_func
(paren
r_int
id|bit
comma
r_int
id|cpuid
)paren
(brace
r_return
suffix:semicolon
)brace
r_int
DECL|function|synergy_intr_connect
id|synergy_intr_connect
c_func
(paren
r_int
id|bit
comma
r_int
id|cpuid
)paren
(brace
r_int
id|irq
suffix:semicolon
r_int
id|is_b
suffix:semicolon
id|irq
op_assign
id|bit_pos_to_irq
c_func
(paren
id|bit
)paren
suffix:semicolon
id|is_b
op_assign
(paren
id|cpuid_to_slice
c_func
(paren
id|cpuid
)paren
)paren
op_amp
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|is_b
)paren
(brace
id|setclear_mask_b
c_func
(paren
id|irq
comma
id|cpuid
comma
l_int|1
)paren
suffix:semicolon
id|setclear_mask_a
c_func
(paren
id|irq
comma
id|cpuid
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|setclear_mask_a
c_func
(paren
id|irq
comma
id|cpuid
comma
l_int|1
)paren
suffix:semicolon
id|setclear_mask_b
c_func
(paren
id|irq
comma
id|cpuid
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|setclear_mask_a
id|setclear_mask_a
c_func
(paren
r_int
id|irq
comma
r_int
id|cpuid
comma
r_int
id|set
)paren
(brace
r_int
id|synergy
suffix:semicolon
r_int
id|nasid
suffix:semicolon
r_int
id|reg_num
suffix:semicolon
r_int
r_int
id|mask
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_int
r_int
id|reg
suffix:semicolon
r_int
r_int
id|val
suffix:semicolon
r_int
id|my_cnode
comma
id|my_synergy
suffix:semicolon
r_int
id|target_cnode
comma
id|target_synergy
suffix:semicolon
multiline_comment|/*&n;         * Perform some idiot checks ..&n;         */
r_if
c_cond
(paren
(paren
id|irq
OL
l_int|0
)paren
op_logical_or
(paren
id|irq
OG
l_int|255
)paren
op_logical_or
(paren
id|cpuid
OL
l_int|0
)paren
op_logical_or
(paren
id|cpuid
OG
l_int|512
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;clear_mask_a: Invalid parameter irq %d cpuid %d&bslash;n&quot;
comma
id|irq
comma
id|cpuid
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|target_cnode
op_assign
id|cpuid_to_cnodeid
c_func
(paren
id|cpuid
)paren
suffix:semicolon
id|target_synergy
op_assign
id|cpuid_to_synergy
c_func
(paren
id|cpuid
)paren
suffix:semicolon
id|my_cnode
op_assign
id|cpuid_to_cnodeid
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|my_synergy
op_assign
id|cpuid_to_synergy
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|reg_num
op_assign
id|irq
op_div
l_int|64
suffix:semicolon
id|mask
op_assign
l_int|1
suffix:semicolon
id|mask
op_lshift_assign
(paren
id|irq
op_mod
l_int|64
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|reg_num
)paren
(brace
r_case
l_int|0
suffix:colon
id|reg
op_assign
id|VEC_MASK0A
suffix:semicolon
id|addr
op_assign
id|VEC_MASK0A_ADDR
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|reg
op_assign
id|VEC_MASK1A
suffix:semicolon
id|addr
op_assign
id|VEC_MASK1A_ADDR
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|reg
op_assign
id|VEC_MASK2A
suffix:semicolon
id|addr
op_assign
id|VEC_MASK2A_ADDR
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|reg
op_assign
id|VEC_MASK3A
suffix:semicolon
id|addr
op_assign
id|VEC_MASK3A_ADDR
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|reg
op_assign
id|addr
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|my_cnode
op_eq
id|target_cnode
op_logical_and
id|my_synergy
op_eq
id|target_synergy
)paren
(brace
singleline_comment|// local synergy
id|val
op_assign
id|READ_LOCAL_SYNERGY_REG
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|set
)paren
(brace
id|val
op_or_assign
id|mask
suffix:semicolon
)brace
r_else
(brace
id|val
op_and_assign
op_complement
id|mask
suffix:semicolon
)brace
id|WRITE_LOCAL_SYNERGY_REG
c_func
(paren
id|addr
comma
id|val
)paren
suffix:semicolon
id|val
op_assign
id|READ_LOCAL_SYNERGY_REG
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* remote synergy */
id|synergy
op_assign
id|cpuid_to_synergy
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
id|val
op_assign
id|REMOTE_SYNERGY_LOAD
c_func
(paren
id|nasid
comma
id|synergy
comma
id|reg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|set
)paren
(brace
id|val
op_or_assign
id|mask
suffix:semicolon
)brace
r_else
(brace
id|val
op_and_assign
op_complement
id|mask
suffix:semicolon
)brace
id|REMOTE_SYNERGY_STORE
c_func
(paren
id|nasid
comma
id|synergy
comma
id|reg
comma
id|val
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|setclear_mask_b
id|setclear_mask_b
c_func
(paren
r_int
id|irq
comma
r_int
id|cpuid
comma
r_int
id|set
)paren
(brace
r_int
id|synergy
suffix:semicolon
r_int
id|nasid
suffix:semicolon
r_int
id|reg_num
suffix:semicolon
r_int
r_int
id|mask
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_int
r_int
id|reg
suffix:semicolon
r_int
r_int
id|val
suffix:semicolon
r_int
id|my_cnode
comma
id|my_synergy
suffix:semicolon
r_int
id|target_cnode
comma
id|target_synergy
suffix:semicolon
multiline_comment|/*&n;&t; * Perform some idiot checks ..&n;&t; */
r_if
c_cond
(paren
(paren
id|irq
OL
l_int|0
)paren
op_logical_or
(paren
id|irq
OG
l_int|255
)paren
op_logical_or
(paren
id|cpuid
OL
l_int|0
)paren
op_logical_or
(paren
id|cpuid
OG
l_int|512
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;clear_mask_b: Invalid parameter irq %d cpuid %d&bslash;n&quot;
comma
id|irq
comma
id|cpuid
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|target_cnode
op_assign
id|cpuid_to_cnodeid
c_func
(paren
id|cpuid
)paren
suffix:semicolon
id|target_synergy
op_assign
id|cpuid_to_synergy
c_func
(paren
id|cpuid
)paren
suffix:semicolon
id|my_cnode
op_assign
id|cpuid_to_cnodeid
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|my_synergy
op_assign
id|cpuid_to_synergy
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|reg_num
op_assign
id|irq
op_div
l_int|64
suffix:semicolon
id|mask
op_assign
l_int|1
suffix:semicolon
id|mask
op_lshift_assign
(paren
id|irq
op_mod
l_int|64
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|reg_num
)paren
(brace
r_case
l_int|0
suffix:colon
id|reg
op_assign
id|VEC_MASK0B
suffix:semicolon
id|addr
op_assign
id|VEC_MASK0B_ADDR
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|reg
op_assign
id|VEC_MASK1B
suffix:semicolon
id|addr
op_assign
id|VEC_MASK1B_ADDR
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|reg
op_assign
id|VEC_MASK2B
suffix:semicolon
id|addr
op_assign
id|VEC_MASK2B_ADDR
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|reg
op_assign
id|VEC_MASK3B
suffix:semicolon
id|addr
op_assign
id|VEC_MASK3B_ADDR
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|reg
op_assign
id|addr
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|my_cnode
op_eq
id|target_cnode
op_logical_and
id|my_synergy
op_eq
id|target_synergy
)paren
(brace
singleline_comment|// local synergy
id|val
op_assign
id|READ_LOCAL_SYNERGY_REG
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|set
)paren
(brace
id|val
op_or_assign
id|mask
suffix:semicolon
)brace
r_else
(brace
id|val
op_and_assign
op_complement
id|mask
suffix:semicolon
)brace
id|WRITE_LOCAL_SYNERGY_REG
c_func
(paren
id|addr
comma
id|val
)paren
suffix:semicolon
id|val
op_assign
id|READ_LOCAL_SYNERGY_REG
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* remote synergy */
id|synergy
op_assign
id|cpuid_to_synergy
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
id|val
op_assign
id|REMOTE_SYNERGY_LOAD
c_func
(paren
id|nasid
comma
id|synergy
comma
id|reg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|set
)paren
(brace
id|val
op_or_assign
id|mask
suffix:semicolon
)brace
r_else
(brace
id|val
op_and_assign
op_complement
id|mask
suffix:semicolon
)brace
id|REMOTE_SYNERGY_STORE
c_func
(paren
id|nasid
comma
id|synergy
comma
id|reg
comma
id|val
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Synergy perf stats. Multiplexed via timer_interrupt.&n; */
r_static
r_int
DECL|function|synergy_perf_append
id|synergy_perf_append
c_func
(paren
r_uint64
id|modesel
)paren
(brace
r_int
id|cnode
suffix:semicolon
id|nodepda_t
op_star
id|npdap
suffix:semicolon
id|synergy_perf_t
op_star
id|p
suffix:semicolon
r_int
id|checked
op_assign
l_int|0
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* bit 45 is enable */
id|modesel
op_or_assign
(paren
l_int|1UL
op_lshift
l_int|45
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
multiline_comment|/* for each node, insert a new synergy_perf entry */
r_if
c_cond
(paren
(paren
id|npdap
op_assign
id|NODEPDA
c_func
(paren
id|cnode
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;synergy_perf_append: cnode=%d NODEPDA(cnode)==NULL, nodepda=%p&bslash;n&quot;
comma
id|cnode
comma
(paren
r_void
op_star
)paren
id|nodepda
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|npdap-&gt;synergy_perf_enabled
)paren
(brace
multiline_comment|/* user must disable counting to append new events */
id|err
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|checked
op_logical_and
id|npdap-&gt;synergy_perf_data
op_ne
l_int|NULL
)paren
(brace
id|checked
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|npdap-&gt;synergy_perf_first
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;modesel
op_eq
id|modesel
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* event already registered */
r_if
c_cond
(paren
(paren
id|p
op_assign
id|p-&gt;next
)paren
op_eq
id|npdap-&gt;synergy_perf_first
)paren
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* XX use kmem_alloc_node() when it is implemented */
id|p
op_assign
(paren
id|synergy_perf_t
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|synergy_perf_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
(paren
r_uint64
)paren
id|p
)paren
op_amp
l_int|7UL
)paren
op_ne
l_int|0
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* bad alignment */
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
(brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
(brace
id|memset
c_func
(paren
id|p
comma
l_int|0
comma
r_sizeof
(paren
id|synergy_perf_t
)paren
)paren
suffix:semicolon
id|p-&gt;modesel
op_assign
id|modesel
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|npdap-&gt;synergy_perf_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|npdap-&gt;synergy_perf_data
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* circular list */
id|p-&gt;next
op_assign
id|p
suffix:semicolon
id|npdap-&gt;synergy_perf_first
op_assign
id|p
suffix:semicolon
id|npdap-&gt;synergy_perf_data
op_assign
id|p
suffix:semicolon
)brace
r_else
(brace
id|p-&gt;next
op_assign
id|npdap-&gt;synergy_perf_data-&gt;next
suffix:semicolon
id|npdap-&gt;synergy_perf_data-&gt;next
op_assign
id|p
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|npdap-&gt;synergy_perf_lock
comma
id|flags
)paren
suffix:semicolon
)brace
)brace
r_return
id|err
suffix:semicolon
)brace
r_static
r_void
DECL|function|synergy_perf_set_freq
id|synergy_perf_set_freq
c_func
(paren
r_int
id|freq
)paren
(brace
r_int
id|cnode
suffix:semicolon
id|nodepda_t
op_star
id|npdap
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
(paren
id|npdap
op_assign
id|NODEPDA
c_func
(paren
id|cnode
)paren
)paren
op_ne
l_int|NULL
)paren
id|npdap-&gt;synergy_perf_freq
op_assign
id|freq
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|synergy_perf_set_enable
id|synergy_perf_set_enable
c_func
(paren
r_int
id|enable
)paren
(brace
r_int
id|cnode
suffix:semicolon
id|nodepda_t
op_star
id|npdap
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
(paren
id|npdap
op_assign
id|NODEPDA
c_func
(paren
id|cnode
)paren
)paren
op_ne
l_int|NULL
)paren
id|npdap-&gt;synergy_perf_enabled
op_assign
id|enable
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;NOTICE: synergy perf counting %sabled on all nodes&bslash;n&quot;
comma
id|enable
ques
c_cond
l_string|&quot;en&quot;
suffix:colon
l_string|&quot;dis&quot;
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|synergy_perf_size
id|synergy_perf_size
c_func
(paren
id|nodepda_t
op_star
id|npdap
)paren
(brace
id|synergy_perf_t
op_star
id|p
suffix:semicolon
r_int
id|n
suffix:semicolon
r_if
c_cond
(paren
id|npdap-&gt;synergy_perf_enabled
op_eq
l_int|0
)paren
(brace
multiline_comment|/* no stats to return */
r_return
l_int|0
suffix:semicolon
)brace
id|spin_lock_irq
c_func
(paren
op_amp
id|npdap-&gt;synergy_perf_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
comma
id|p
op_assign
id|npdap-&gt;synergy_perf_first
suffix:semicolon
id|p
suffix:semicolon
)paren
(brace
id|n
op_increment
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
id|npdap-&gt;synergy_perf_first
)paren
r_break
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|npdap-&gt;synergy_perf_lock
)paren
suffix:semicolon
multiline_comment|/* bytes == n pairs of {event,counter} */
r_return
id|n
op_star
l_int|2
op_star
r_sizeof
(paren
r_uint64
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|synergy_perf_ioctl
id|synergy_perf_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|cnode
suffix:semicolon
id|nodepda_t
op_star
id|npdap
suffix:semicolon
id|synergy_perf_t
op_star
id|p
suffix:semicolon
r_int
id|intarg
suffix:semicolon
r_int
id|fsb
suffix:semicolon
r_uint64
id|longarg
suffix:semicolon
r_uint64
op_star
id|stats
suffix:semicolon
r_int
id|n
suffix:semicolon
id|devfs_handle_t
id|d
suffix:semicolon
id|arbitrary_info_t
id|info
suffix:semicolon
r_if
c_cond
(paren
(paren
id|d
op_assign
id|devfs_get_handle_from_inode
c_func
(paren
id|inode
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|info
op_assign
id|hwgraph_fastinfo_get
c_func
(paren
id|d
)paren
suffix:semicolon
id|cnode
op_assign
id|SYNERGY_PERF_INFO_CNODE
c_func
(paren
id|info
)paren
suffix:semicolon
id|fsb
op_assign
id|SYNERGY_PERF_INFO_FSB
c_func
(paren
id|info
)paren
suffix:semicolon
id|npdap
op_assign
id|NODEPDA
c_func
(paren
id|cnode
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SNDRV_GET_SYNERGY_VERSION
suffix:colon
multiline_comment|/* return int, version of data structure for SNDRV_GET_SYNERGYINFO */
id|intarg
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* version 1 */
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|intarg
comma
r_sizeof
(paren
id|intarg
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_GET_INFOSIZE
suffix:colon
multiline_comment|/* return int, sizeof buf needed for SYNERGY_PERF_GET_STATS */
id|intarg
op_assign
id|synergy_perf_size
c_func
(paren
id|npdap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|intarg
comma
r_sizeof
(paren
id|intarg
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_GET_SYNERGYINFO
suffix:colon
multiline_comment|/* return array of event/value pairs, this node only */
r_if
c_cond
(paren
(paren
id|intarg
op_assign
id|synergy_perf_size
c_func
(paren
id|npdap
)paren
)paren
op_le
l_int|0
)paren
r_return
op_minus
id|ENODATA
suffix:semicolon
r_if
c_cond
(paren
(paren
id|stats
op_assign
(paren
r_uint64
op_star
)paren
id|kmalloc
c_func
(paren
id|intarg
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|npdap-&gt;synergy_perf_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
comma
id|p
op_assign
id|npdap-&gt;synergy_perf_first
suffix:semicolon
id|p
suffix:semicolon
)paren
(brace
id|stats
(braket
id|n
op_increment
)braket
op_assign
id|p-&gt;modesel
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;intervals
OG
l_int|0
)paren
id|stats
(braket
id|n
op_increment
)braket
op_assign
id|p-&gt;counts
(braket
id|fsb
)braket
op_star
id|p-&gt;total_intervals
op_div
id|p-&gt;intervals
suffix:semicolon
r_else
id|stats
(braket
id|n
op_increment
)braket
op_assign
l_int|0
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
id|npdap-&gt;synergy_perf_first
)paren
r_break
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|npdap-&gt;synergy_perf_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
id|stats
comma
id|intarg
)paren
)paren
(brace
id|kfree
c_func
(paren
id|stats
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|stats
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_SYNERGY_APPEND
suffix:colon
multiline_comment|/* reads 64bit event, append synergy perf event to all nodes  */
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|longarg
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|longarg
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|synergy_perf_append
c_func
(paren
id|longarg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_GET_SYNERGY_STATUS
suffix:colon
multiline_comment|/* return int, 1 if enabled else 0 */
id|intarg
op_assign
id|npdap-&gt;synergy_perf_enabled
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|intarg
comma
r_sizeof
(paren
id|intarg
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_SYNERGY_ENABLE
suffix:colon
multiline_comment|/* read int, if true enable counting else disable */
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|intarg
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|intarg
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|synergy_perf_set_enable
c_func
(paren
id|intarg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_SYNERGY_FREQ
suffix:colon
multiline_comment|/* read int, set jiffies per update */
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|intarg
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|intarg
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|intarg
OL
l_int|0
op_logical_or
id|intarg
op_ge
id|HZ
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|synergy_perf_set_freq
c_func
(paren
id|intarg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Warning: invalid ioctl %d on synergy mon for cnode=%d fsb=%d&bslash;n&quot;
comma
id|cmd
comma
id|cnode
comma
id|fsb
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|synergy_mon_fops
r_struct
id|file_operations
id|synergy_mon_fops
op_assign
(brace
dot
id|ioctl
op_assign
id|synergy_perf_ioctl
comma
)brace
suffix:semicolon
r_void
DECL|function|synergy_perf_update
id|synergy_perf_update
c_func
(paren
r_int
id|cpu
)paren
(brace
id|nasid_t
id|nasid
suffix:semicolon
id|cnodeid_t
id|cnode
suffix:semicolon
r_struct
id|nodepda_s
op_star
id|npdap
suffix:semicolon
multiline_comment|/*&n;&t; * synergy_perf_initialized is set by synergy_perf_init()&n;&t; * which is called last thing by sn_mp_setup(), i.e. well&n;&t; * after nodepda has been initialized.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|synergy_perf_initialized
)paren
r_return
suffix:semicolon
id|cnode
op_assign
id|cpuid_to_cnodeid
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|npdap
op_assign
id|NODEPDA
c_func
(paren
id|cnode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|npdap
op_eq
l_int|NULL
op_logical_or
id|cnode
OL
l_int|0
op_logical_or
id|cnode
op_ge
id|numnodes
)paren
multiline_comment|/* this should not happen: still in early io init */
r_return
suffix:semicolon
macro_line|#if 0
multiline_comment|/* use this to check nodepda initialization */
r_if
c_cond
(paren
(paren
(paren
r_uint64
)paren
id|npdap
)paren
op_amp
l_int|0x7
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;nERROR on cpu %d : cnode=%d, npdap == %p, not aligned&bslash;n&quot;
comma
id|cpu
comma
id|cnode
comma
id|npdap
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|npdap-&gt;synergy_perf_enabled
op_eq
l_int|0
op_logical_or
id|npdap-&gt;synergy_perf_data
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* Not enabled, or no events to monitor */
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|npdap-&gt;synergy_inactive_intervals
op_increment
op_mod
id|npdap-&gt;synergy_perf_freq
op_ne
l_int|0
)paren
(brace
multiline_comment|/* don&squot;t multiplex on every timer interrupt */
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Read registers for last interval and increment counters.&n;&t; * Hold the per-node synergy_perf_lock so concurrent readers get&n;&t; * consistent values.&n;&t; */
id|spin_lock_irq
c_func
(paren
op_amp
id|npdap-&gt;synergy_perf_lock
)paren
suffix:semicolon
id|nasid
op_assign
id|cpuid_to_nasid
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|npdap-&gt;synergy_active_intervals
op_increment
suffix:semicolon
id|npdap-&gt;synergy_perf_data-&gt;intervals
op_increment
suffix:semicolon
id|npdap-&gt;synergy_perf_data-&gt;total_intervals
op_assign
id|npdap-&gt;synergy_active_intervals
suffix:semicolon
id|npdap-&gt;synergy_perf_data-&gt;counts
(braket
l_int|0
)braket
op_add_assign
l_int|0xffffffffffUL
op_amp
id|REMOTE_SYNERGY_LOAD
c_func
(paren
id|nasid
comma
l_int|0
comma
id|PERF_CNTR0_A
)paren
suffix:semicolon
id|npdap-&gt;synergy_perf_data-&gt;counts
(braket
l_int|1
)braket
op_add_assign
l_int|0xffffffffffUL
op_amp
id|REMOTE_SYNERGY_LOAD
c_func
(paren
id|nasid
comma
l_int|1
comma
id|PERF_CNTR0_B
)paren
suffix:semicolon
multiline_comment|/* skip to next in circular list */
id|npdap-&gt;synergy_perf_data
op_assign
id|npdap-&gt;synergy_perf_data-&gt;next
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|npdap-&gt;synergy_perf_lock
)paren
suffix:semicolon
multiline_comment|/* set the counter 0 selection modes for both A and B */
id|REMOTE_SYNERGY_STORE
c_func
(paren
id|nasid
comma
l_int|0
comma
id|PERF_CNTL0_A
comma
id|npdap-&gt;synergy_perf_data-&gt;modesel
)paren
suffix:semicolon
id|REMOTE_SYNERGY_STORE
c_func
(paren
id|nasid
comma
l_int|1
comma
id|PERF_CNTL0_B
comma
id|npdap-&gt;synergy_perf_data-&gt;modesel
)paren
suffix:semicolon
multiline_comment|/* and reset the counter registers to zero */
id|REMOTE_SYNERGY_STORE
c_func
(paren
id|nasid
comma
l_int|0
comma
id|PERF_CNTR0_A
comma
l_int|0UL
)paren
suffix:semicolon
id|REMOTE_SYNERGY_STORE
c_func
(paren
id|nasid
comma
l_int|1
comma
id|PERF_CNTR0_B
comma
l_int|0UL
)paren
suffix:semicolon
)brace
r_void
DECL|function|synergy_perf_init
id|synergy_perf_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;synergy_perf_init(), counting is initially disabled&bslash;n&quot;
)paren
suffix:semicolon
id|synergy_perf_initialized
op_increment
suffix:semicolon
)brace
eof
