multiline_comment|/*&n; *   Generic Instrument routines for ALSA sequencer&n; *   Copyright (c) 1999 by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &quot;seq_clientmgr.h&quot;
macro_line|#include &lt;sound/seq_instr.h&gt;
macro_line|#include &lt;sound/initval.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jaroslav Kysela &lt;perex@suse.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Advanced Linux Sound Architecture sequencer instrument library.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_CLASSES
c_func
(paren
l_string|&quot;{sound}&quot;
)paren
suffix:semicolon
id|MODULE_SUPPORTED_DEVICE
c_func
(paren
l_string|&quot;sound&quot;
)paren
suffix:semicolon
DECL|function|snd_instr_lock_ops
r_static
r_void
id|snd_instr_lock_ops
c_func
(paren
id|snd_seq_kinstr_list_t
op_star
id|list
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|list-&gt;flags
op_amp
id|SNDRV_SEQ_INSTR_FLG_DIRECT
)paren
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|list-&gt;ops_lock
comma
id|list-&gt;ops_flags
)paren
suffix:semicolon
)brace
r_else
(brace
id|down
c_func
(paren
op_amp
id|list-&gt;ops_mutex
)paren
suffix:semicolon
)brace
)brace
DECL|function|snd_instr_unlock_ops
r_static
r_void
id|snd_instr_unlock_ops
c_func
(paren
id|snd_seq_kinstr_list_t
op_star
id|list
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|list-&gt;flags
op_amp
id|SNDRV_SEQ_INSTR_FLG_DIRECT
)paren
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|list-&gt;ops_lock
comma
id|list-&gt;ops_flags
)paren
suffix:semicolon
)brace
r_else
(brace
id|up
c_func
(paren
op_amp
id|list-&gt;ops_mutex
)paren
suffix:semicolon
)brace
)brace
DECL|function|snd_seq_cluster_new
id|snd_seq_kcluster_t
op_star
id|snd_seq_cluster_new
c_func
(paren
r_int
id|atomic
)paren
(brace
id|snd_seq_kcluster_t
op_star
id|cluster
suffix:semicolon
id|cluster
op_assign
(paren
id|snd_seq_kcluster_t
op_star
)paren
id|snd_kcalloc
c_func
(paren
r_sizeof
(paren
id|snd_seq_kcluster_t
)paren
comma
id|atomic
ques
c_cond
id|GFP_ATOMIC
suffix:colon
id|GFP_KERNEL
)paren
suffix:semicolon
r_return
id|cluster
suffix:semicolon
)brace
DECL|function|snd_seq_cluster_free
r_void
id|snd_seq_cluster_free
c_func
(paren
id|snd_seq_kcluster_t
op_star
id|cluster
comma
r_int
id|atomic
)paren
(brace
r_if
c_cond
(paren
id|cluster
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|kfree
c_func
(paren
id|cluster
)paren
suffix:semicolon
)brace
DECL|function|snd_seq_instr_new
id|snd_seq_kinstr_t
op_star
id|snd_seq_instr_new
c_func
(paren
r_int
id|add_len
comma
r_int
id|atomic
)paren
(brace
id|snd_seq_kinstr_t
op_star
id|instr
suffix:semicolon
id|instr
op_assign
(paren
id|snd_seq_kinstr_t
op_star
)paren
id|snd_kcalloc
c_func
(paren
r_sizeof
(paren
id|snd_seq_kinstr_t
)paren
op_plus
id|add_len
comma
id|atomic
ques
c_cond
id|GFP_ATOMIC
suffix:colon
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|instr
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|instr-&gt;add_len
op_assign
id|add_len
suffix:semicolon
r_return
id|instr
suffix:semicolon
)brace
DECL|function|snd_seq_instr_free
r_int
id|snd_seq_instr_free
c_func
(paren
id|snd_seq_kinstr_t
op_star
id|instr
comma
r_int
id|atomic
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|instr
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|instr-&gt;ops
op_logical_and
id|instr-&gt;ops-&gt;remove
)paren
id|result
op_assign
id|instr-&gt;ops
op_member_access_from_pointer
id|remove
c_func
(paren
id|instr-&gt;ops-&gt;private_data
comma
id|instr
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|result
)paren
id|kfree
c_func
(paren
id|instr
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|snd_seq_instr_list_new
id|snd_seq_kinstr_list_t
op_star
id|snd_seq_instr_list_new
c_func
(paren
r_void
)paren
(brace
id|snd_seq_kinstr_list_t
op_star
id|list
suffix:semicolon
id|list
op_assign
(paren
id|snd_seq_kinstr_list_t
op_star
)paren
id|snd_kcalloc
c_func
(paren
r_sizeof
(paren
id|snd_seq_kinstr_list_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|list-&gt;lock
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|list-&gt;ops_lock
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|list-&gt;ops_mutex
)paren
suffix:semicolon
id|list-&gt;owner
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
id|list
suffix:semicolon
)brace
DECL|function|snd_seq_instr_list_free
r_void
id|snd_seq_instr_list_free
c_func
(paren
id|snd_seq_kinstr_list_t
op_star
op_star
id|list_ptr
)paren
(brace
id|snd_seq_kinstr_list_t
op_star
id|list
suffix:semicolon
id|snd_seq_kinstr_t
op_star
id|instr
suffix:semicolon
id|snd_seq_kcluster_t
op_star
id|cluster
suffix:semicolon
r_int
id|idx
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|list_ptr
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|list
op_assign
op_star
id|list_ptr
suffix:semicolon
op_star
id|list_ptr
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|list
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|SNDRV_SEQ_INSTR_HASH_SIZE
suffix:semicolon
id|idx
op_increment
)paren
(brace
r_while
c_loop
(paren
(paren
id|instr
op_assign
id|list-&gt;hash
(braket
id|idx
)braket
)paren
op_ne
l_int|NULL
)paren
(brace
id|list-&gt;hash
(braket
id|idx
)braket
op_assign
id|instr-&gt;next
suffix:semicolon
id|list-&gt;count
op_decrement
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_while
c_loop
(paren
id|instr-&gt;use
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snd_seq_instr_free
c_func
(paren
id|instr
comma
l_int|0
)paren
OL
l_int|0
)paren
id|snd_printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;instrument free problem&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|cluster
op_assign
id|list-&gt;chash
(braket
id|idx
)braket
)paren
op_ne
l_int|NULL
)paren
(brace
id|list-&gt;chash
(braket
id|idx
)braket
op_assign
id|cluster-&gt;next
suffix:semicolon
id|list-&gt;ccount
op_decrement
suffix:semicolon
id|snd_seq_cluster_free
c_func
(paren
id|cluster
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
id|kfree
c_func
(paren
id|list
)paren
suffix:semicolon
)brace
DECL|function|instr_free_compare
r_static
r_int
id|instr_free_compare
c_func
(paren
id|snd_seq_kinstr_t
op_star
id|instr
comma
id|snd_seq_instr_header_t
op_star
id|ifree
comma
r_int
r_int
id|client
)paren
(brace
r_switch
c_cond
(paren
id|ifree-&gt;cmd
)paren
(brace
r_case
id|SNDRV_SEQ_INSTR_FREE_CMD_ALL
suffix:colon
multiline_comment|/* all, except private for other clients */
r_if
c_cond
(paren
(paren
id|instr-&gt;instr.std
op_amp
l_int|0xff000000
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|instr-&gt;instr.std
op_rshift
l_int|24
)paren
op_amp
l_int|0xff
)paren
op_eq
id|client
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
r_case
id|SNDRV_SEQ_INSTR_FREE_CMD_PRIVATE
suffix:colon
multiline_comment|/* all my private instruments */
r_if
c_cond
(paren
(paren
id|instr-&gt;instr.std
op_amp
l_int|0xff000000
)paren
op_eq
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|instr-&gt;instr.std
op_rshift
l_int|24
)paren
op_amp
l_int|0xff
)paren
op_eq
id|client
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
r_case
id|SNDRV_SEQ_INSTR_FREE_CMD_CLUSTER
suffix:colon
multiline_comment|/* all my private instruments */
r_if
c_cond
(paren
(paren
id|instr-&gt;instr.std
op_amp
l_int|0xff000000
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|instr-&gt;instr.cluster
op_eq
id|ifree-&gt;id.cluster
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
(paren
id|instr-&gt;instr.std
op_rshift
l_int|24
)paren
op_amp
l_int|0xff
)paren
op_eq
id|client
)paren
(brace
r_if
c_cond
(paren
id|instr-&gt;instr.cluster
op_eq
id|ifree-&gt;id.cluster
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|snd_seq_instr_list_free_cond
r_int
id|snd_seq_instr_list_free_cond
c_func
(paren
id|snd_seq_kinstr_list_t
op_star
id|list
comma
id|snd_seq_instr_header_t
op_star
id|ifree
comma
r_int
id|client
comma
r_int
id|atomic
)paren
(brace
id|snd_seq_kinstr_t
op_star
id|instr
comma
op_star
id|prev
comma
op_star
id|next
comma
op_star
id|flist
suffix:semicolon
r_int
id|idx
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|snd_instr_lock_ops
c_func
(paren
id|list
)paren
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|SNDRV_SEQ_INSTR_HASH_SIZE
suffix:semicolon
id|idx
op_increment
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|instr
op_assign
id|list-&gt;hash
(braket
id|idx
)braket
suffix:semicolon
id|prev
op_assign
id|flist
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|instr
)paren
(brace
r_while
c_loop
(paren
id|instr
op_logical_and
id|instr_free_compare
c_func
(paren
id|instr
comma
id|ifree
comma
(paren
r_int
r_int
)paren
id|client
)paren
)paren
(brace
id|prev
op_assign
id|instr
suffix:semicolon
id|instr
op_assign
id|instr-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|instr
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|instr-&gt;ops
op_logical_and
id|instr-&gt;ops-&gt;notify
)paren
id|instr-&gt;ops
op_member_access_from_pointer
id|notify
c_func
(paren
id|instr-&gt;ops-&gt;private_data
comma
id|instr
comma
id|SNDRV_SEQ_INSTR_NOTIFY_REMOVE
)paren
suffix:semicolon
id|next
op_assign
id|instr-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|prev
op_eq
l_int|NULL
)paren
(brace
id|list-&gt;hash
(braket
id|idx
)braket
op_assign
id|next
suffix:semicolon
)brace
r_else
(brace
id|prev-&gt;next
op_assign
id|next
suffix:semicolon
)brace
id|list-&gt;count
op_decrement
suffix:semicolon
id|instr-&gt;next
op_assign
id|flist
suffix:semicolon
id|flist
op_assign
id|instr
suffix:semicolon
id|instr
op_assign
id|next
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_while
c_loop
(paren
id|flist
)paren
(brace
id|instr
op_assign
id|flist
suffix:semicolon
id|flist
op_assign
id|instr-&gt;next
suffix:semicolon
r_while
c_loop
(paren
id|instr-&gt;use
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|snd_seq_instr_free
c_func
(paren
id|instr
comma
id|atomic
)paren
OL
l_int|0
)paren
id|snd_printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;instrument free problem&bslash;n&quot;
)paren
suffix:semicolon
id|instr
op_assign
id|next
suffix:semicolon
)brace
)brace
id|snd_instr_unlock_ops
c_func
(paren
id|list
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|compute_hash_instr_key
r_static
r_int
id|compute_hash_instr_key
c_func
(paren
id|snd_seq_instr_t
op_star
id|instr
)paren
(brace
r_int
id|result
suffix:semicolon
id|result
op_assign
id|instr-&gt;bank
op_or
(paren
id|instr-&gt;prg
op_lshift
l_int|16
)paren
suffix:semicolon
id|result
op_add_assign
id|result
op_rshift
l_int|24
suffix:semicolon
id|result
op_add_assign
id|result
op_rshift
l_int|16
suffix:semicolon
id|result
op_add_assign
id|result
op_rshift
l_int|8
suffix:semicolon
r_return
id|result
op_amp
(paren
id|SNDRV_SEQ_INSTR_HASH_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#if 0
r_static
r_int
id|compute_hash_cluster_key
c_func
(paren
id|snd_seq_instr_cluster_t
id|cluster
)paren
(brace
r_int
id|result
suffix:semicolon
id|result
op_assign
id|cluster
suffix:semicolon
id|result
op_add_assign
id|result
op_rshift
l_int|24
suffix:semicolon
id|result
op_add_assign
id|result
op_rshift
l_int|16
suffix:semicolon
id|result
op_add_assign
id|result
op_rshift
l_int|8
suffix:semicolon
r_return
id|result
op_amp
(paren
id|SNDRV_SEQ_INSTR_HASH_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|compare_instr
r_static
r_int
id|compare_instr
c_func
(paren
id|snd_seq_instr_t
op_star
id|i1
comma
id|snd_seq_instr_t
op_star
id|i2
comma
r_int
id|exact
)paren
(brace
r_if
c_cond
(paren
id|exact
)paren
(brace
r_if
c_cond
(paren
id|i1-&gt;cluster
op_ne
id|i2-&gt;cluster
op_logical_or
id|i1-&gt;bank
op_ne
id|i2-&gt;bank
op_logical_or
id|i1-&gt;prg
op_ne
id|i2-&gt;prg
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i1-&gt;std
op_amp
l_int|0xff000000
)paren
op_ne
(paren
id|i2-&gt;std
op_amp
l_int|0xff000000
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|i1-&gt;std
op_amp
id|i2-&gt;std
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
id|client_check
suffix:semicolon
r_if
c_cond
(paren
id|i2-&gt;cluster
op_logical_and
id|i1-&gt;cluster
op_ne
id|i2-&gt;cluster
)paren
r_return
l_int|1
suffix:semicolon
id|client_check
op_assign
id|i2-&gt;std
op_amp
l_int|0xff000000
suffix:semicolon
r_if
c_cond
(paren
id|client_check
)paren
(brace
r_if
c_cond
(paren
(paren
id|i1-&gt;std
op_amp
l_int|0xff000000
)paren
op_ne
id|client_check
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|i1-&gt;std
op_amp
id|i2-&gt;std
)paren
op_ne
id|i2-&gt;std
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
id|i1-&gt;bank
op_ne
id|i2-&gt;bank
op_logical_or
id|i1-&gt;prg
op_ne
id|i2-&gt;prg
suffix:semicolon
)brace
)brace
DECL|function|snd_seq_instr_find
id|snd_seq_kinstr_t
op_star
id|snd_seq_instr_find
c_func
(paren
id|snd_seq_kinstr_list_t
op_star
id|list
comma
id|snd_seq_instr_t
op_star
id|instr
comma
r_int
id|exact
comma
r_int
id|follow_alias
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|depth
op_assign
l_int|0
suffix:semicolon
id|snd_seq_kinstr_t
op_star
id|result
suffix:semicolon
r_if
c_cond
(paren
id|list
op_eq
l_int|NULL
op_logical_or
id|instr
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|__again
suffix:colon
id|result
op_assign
id|list-&gt;hash
(braket
id|compute_hash_instr_key
c_func
(paren
id|instr
)paren
)braket
suffix:semicolon
r_while
c_loop
(paren
id|result
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|compare_instr
c_func
(paren
op_amp
id|result-&gt;instr
comma
id|instr
comma
id|exact
)paren
)paren
(brace
r_if
c_cond
(paren
id|follow_alias
op_logical_and
(paren
id|result-&gt;type
op_eq
id|SNDRV_SEQ_INSTR_ATYPE_ALIAS
)paren
)paren
(brace
id|instr
op_assign
(paren
id|snd_seq_instr_t
op_star
)paren
id|KINSTR_DATA
c_func
(paren
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|depth
OG
l_int|10
)paren
r_goto
id|__not_found
suffix:semicolon
r_goto
id|__again
suffix:semicolon
)brace
id|result-&gt;use
op_increment
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
id|result
op_assign
id|result-&gt;next
suffix:semicolon
)brace
id|__not_found
suffix:colon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|snd_seq_instr_free_use
r_void
id|snd_seq_instr_free_use
c_func
(paren
id|snd_seq_kinstr_list_t
op_star
id|list
comma
id|snd_seq_kinstr_t
op_star
id|instr
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|list
op_eq
l_int|NULL
op_logical_or
id|instr
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|instr-&gt;use
op_le
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;free_use: fatal!!! use = %i, name = &squot;%s&squot;&bslash;n&quot;
comma
id|instr-&gt;use
comma
id|instr-&gt;name
)paren
suffix:semicolon
)brace
r_else
(brace
id|instr-&gt;use
op_decrement
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|instr_ops
r_static
id|snd_seq_kinstr_ops_t
op_star
id|instr_ops
c_func
(paren
id|snd_seq_kinstr_ops_t
op_star
id|ops
comma
r_char
op_star
id|instr_type
)paren
(brace
r_while
c_loop
(paren
id|ops
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|ops-&gt;instr_type
comma
id|instr_type
)paren
)paren
r_return
id|ops
suffix:semicolon
id|ops
op_assign
id|ops-&gt;next
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|instr_result
r_static
r_int
id|instr_result
c_func
(paren
id|snd_seq_event_t
op_star
id|ev
comma
r_int
id|type
comma
r_int
id|result
comma
r_int
id|atomic
)paren
(brace
id|snd_seq_event_t
id|sev
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|sev
comma
l_int|0
comma
r_sizeof
(paren
id|sev
)paren
)paren
suffix:semicolon
id|sev.type
op_assign
id|SNDRV_SEQ_EVENT_RESULT
suffix:semicolon
id|sev.flags
op_assign
id|SNDRV_SEQ_TIME_STAMP_REAL
op_or
id|SNDRV_SEQ_EVENT_LENGTH_FIXED
op_or
id|SNDRV_SEQ_PRIORITY_NORMAL
suffix:semicolon
id|sev.source
op_assign
id|ev-&gt;dest
suffix:semicolon
id|sev.dest
op_assign
id|ev-&gt;source
suffix:semicolon
id|sev.data.result.event
op_assign
id|type
suffix:semicolon
id|sev.data.result.result
op_assign
id|result
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;instr result - type = %i, result = %i, queue = %i, source.client:port = %i:%i, dest.client:port = %i:%i&bslash;n&quot;
comma
id|type
comma
id|result
comma
id|sev.queue
comma
id|sev.source.client
comma
id|sev.source.port
comma
id|sev.dest.client
comma
id|sev.dest.port
)paren
suffix:semicolon
macro_line|#endif
r_return
id|snd_seq_kernel_client_dispatch
c_func
(paren
id|sev.source.client
comma
op_amp
id|sev
comma
id|atomic
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|instr_begin
r_static
r_int
id|instr_begin
c_func
(paren
id|snd_seq_kinstr_ops_t
op_star
id|ops
comma
id|snd_seq_kinstr_list_t
op_star
id|list
comma
id|snd_seq_event_t
op_star
id|ev
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list-&gt;owner
op_ge
l_int|0
op_logical_and
id|list-&gt;owner
op_ne
id|ev-&gt;source.client
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|instr_result
c_func
(paren
id|ev
comma
id|SNDRV_SEQ_EVENT_INSTR_BEGIN
comma
op_minus
id|EBUSY
comma
id|atomic
)paren
suffix:semicolon
)brace
id|list-&gt;owner
op_assign
id|ev-&gt;source.client
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|instr_result
c_func
(paren
id|ev
comma
id|SNDRV_SEQ_EVENT_INSTR_BEGIN
comma
l_int|0
comma
id|atomic
)paren
suffix:semicolon
)brace
DECL|function|instr_end
r_static
r_int
id|instr_end
c_func
(paren
id|snd_seq_kinstr_ops_t
op_star
id|ops
comma
id|snd_seq_kinstr_list_t
op_star
id|list
comma
id|snd_seq_event_t
op_star
id|ev
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* TODO: timeout handling */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list-&gt;owner
op_eq
id|ev-&gt;source.client
)paren
(brace
id|list-&gt;owner
op_assign
op_minus
l_int|1
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|instr_result
c_func
(paren
id|ev
comma
id|SNDRV_SEQ_EVENT_INSTR_END
comma
l_int|0
comma
id|atomic
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|instr_result
c_func
(paren
id|ev
comma
id|SNDRV_SEQ_EVENT_INSTR_END
comma
op_minus
id|EINVAL
comma
id|atomic
)paren
suffix:semicolon
)brace
DECL|function|instr_info
r_static
r_int
id|instr_info
c_func
(paren
id|snd_seq_kinstr_ops_t
op_star
id|ops
comma
id|snd_seq_kinstr_list_t
op_star
id|list
comma
id|snd_seq_event_t
op_star
id|ev
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
(brace
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|function|instr_format_info
r_static
r_int
id|instr_format_info
c_func
(paren
id|snd_seq_kinstr_ops_t
op_star
id|ops
comma
id|snd_seq_kinstr_list_t
op_star
id|list
comma
id|snd_seq_event_t
op_star
id|ev
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
(brace
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|function|instr_reset
r_static
r_int
id|instr_reset
c_func
(paren
id|snd_seq_kinstr_ops_t
op_star
id|ops
comma
id|snd_seq_kinstr_list_t
op_star
id|list
comma
id|snd_seq_event_t
op_star
id|ev
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
(brace
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|function|instr_status
r_static
r_int
id|instr_status
c_func
(paren
id|snd_seq_kinstr_ops_t
op_star
id|ops
comma
id|snd_seq_kinstr_list_t
op_star
id|list
comma
id|snd_seq_event_t
op_star
id|ev
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
(brace
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|function|instr_put
r_static
r_int
id|instr_put
c_func
(paren
id|snd_seq_kinstr_ops_t
op_star
id|ops
comma
id|snd_seq_kinstr_list_t
op_star
id|list
comma
id|snd_seq_event_t
op_star
id|ev
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|snd_seq_instr_header_t
id|put
suffix:semicolon
id|snd_seq_kinstr_t
op_star
id|instr
suffix:semicolon
r_int
id|result
op_assign
op_minus
id|EINVAL
comma
id|len
comma
id|key
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ev-&gt;flags
op_amp
id|SNDRV_SEQ_EVENT_LENGTH_MASK
)paren
op_ne
id|SNDRV_SEQ_EVENT_LENGTH_VARUSR
)paren
r_goto
id|__return
suffix:semicolon
r_if
c_cond
(paren
id|ev-&gt;data.ext.len
OL
r_sizeof
(paren
id|snd_seq_instr_header_t
)paren
)paren
r_goto
id|__return
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|put
comma
id|ev-&gt;data.ext.ptr
comma
r_sizeof
(paren
id|snd_seq_instr_header_t
)paren
)paren
)paren
(brace
id|result
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|__return
suffix:semicolon
)brace
id|snd_instr_lock_ops
c_func
(paren
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|put.id.instr.std
op_amp
l_int|0xff000000
)paren
(brace
multiline_comment|/* private instrument */
id|put.id.instr.std
op_and_assign
l_int|0x00ffffff
suffix:semicolon
id|put.id.instr.std
op_or_assign
(paren
r_int
r_int
)paren
id|ev-&gt;source.client
op_lshift
l_int|24
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|instr
op_assign
id|snd_seq_instr_find
c_func
(paren
id|list
comma
op_amp
id|put.id.instr
comma
l_int|1
comma
l_int|0
)paren
)paren
)paren
(brace
id|snd_seq_instr_free_use
c_func
(paren
id|list
comma
id|instr
)paren
suffix:semicolon
id|snd_instr_unlock_ops
c_func
(paren
id|list
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|__return
suffix:semicolon
)brace
id|ops
op_assign
id|instr_ops
c_func
(paren
id|ops
comma
id|put.data.data.format
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ops
op_eq
l_int|NULL
)paren
(brace
id|snd_instr_unlock_ops
c_func
(paren
id|list
)paren
suffix:semicolon
r_goto
id|__return
suffix:semicolon
)brace
id|len
op_assign
id|ops-&gt;add_len
suffix:semicolon
r_if
c_cond
(paren
id|put.data.type
op_eq
id|SNDRV_SEQ_INSTR_ATYPE_ALIAS
)paren
id|len
op_assign
r_sizeof
(paren
id|snd_seq_instr_t
)paren
suffix:semicolon
id|instr
op_assign
id|snd_seq_instr_new
c_func
(paren
id|len
comma
id|atomic
)paren
suffix:semicolon
r_if
c_cond
(paren
id|instr
op_eq
l_int|NULL
)paren
(brace
id|snd_instr_unlock_ops
c_func
(paren
id|list
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|__return
suffix:semicolon
)brace
id|instr-&gt;ops
op_assign
id|ops
suffix:semicolon
id|instr-&gt;instr
op_assign
id|put.id.instr
suffix:semicolon
id|strlcpy
c_func
(paren
id|instr-&gt;name
comma
id|put.data.name
comma
r_sizeof
(paren
id|instr-&gt;name
)paren
)paren
suffix:semicolon
id|instr-&gt;type
op_assign
id|put.data.type
suffix:semicolon
r_if
c_cond
(paren
id|instr-&gt;type
op_eq
id|SNDRV_SEQ_INSTR_ATYPE_DATA
)paren
(brace
id|result
op_assign
id|ops
op_member_access_from_pointer
id|put
c_func
(paren
id|ops-&gt;private_data
comma
id|instr
comma
id|ev-&gt;data.ext.ptr
op_plus
r_sizeof
(paren
id|snd_seq_instr_header_t
)paren
comma
id|ev-&gt;data.ext.len
op_minus
r_sizeof
(paren
id|snd_seq_instr_header_t
)paren
comma
id|atomic
comma
id|put.cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|snd_seq_instr_free
c_func
(paren
id|instr
comma
id|atomic
)paren
suffix:semicolon
id|snd_instr_unlock_ops
c_func
(paren
id|list
)paren
suffix:semicolon
r_goto
id|__return
suffix:semicolon
)brace
)brace
id|key
op_assign
id|compute_hash_instr_key
c_func
(paren
op_amp
id|instr-&gt;instr
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|instr-&gt;next
op_assign
id|list-&gt;hash
(braket
id|key
)braket
suffix:semicolon
id|list-&gt;hash
(braket
id|key
)braket
op_assign
id|instr
suffix:semicolon
id|list-&gt;count
op_increment
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|snd_instr_unlock_ops
c_func
(paren
id|list
)paren
suffix:semicolon
id|result
op_assign
l_int|0
suffix:semicolon
id|__return
suffix:colon
id|instr_result
c_func
(paren
id|ev
comma
id|SNDRV_SEQ_EVENT_INSTR_PUT
comma
id|result
comma
id|atomic
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|instr_get
r_static
r_int
id|instr_get
c_func
(paren
id|snd_seq_kinstr_ops_t
op_star
id|ops
comma
id|snd_seq_kinstr_list_t
op_star
id|list
comma
id|snd_seq_event_t
op_star
id|ev
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
(brace
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|function|instr_free
r_static
r_int
id|instr_free
c_func
(paren
id|snd_seq_kinstr_ops_t
op_star
id|ops
comma
id|snd_seq_kinstr_list_t
op_star
id|list
comma
id|snd_seq_event_t
op_star
id|ev
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
(brace
id|snd_seq_instr_header_t
id|ifree
suffix:semicolon
id|snd_seq_kinstr_t
op_star
id|instr
comma
op_star
id|prev
suffix:semicolon
r_int
id|result
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|hash
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ev-&gt;flags
op_amp
id|SNDRV_SEQ_EVENT_LENGTH_MASK
)paren
op_ne
id|SNDRV_SEQ_EVENT_LENGTH_VARUSR
)paren
r_goto
id|__return
suffix:semicolon
r_if
c_cond
(paren
id|ev-&gt;data.ext.len
OL
r_sizeof
(paren
id|snd_seq_instr_header_t
)paren
)paren
r_goto
id|__return
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ifree
comma
id|ev-&gt;data.ext.ptr
comma
r_sizeof
(paren
id|snd_seq_instr_header_t
)paren
)paren
)paren
(brace
id|result
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|__return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ifree.cmd
op_eq
id|SNDRV_SEQ_INSTR_FREE_CMD_ALL
op_logical_or
id|ifree.cmd
op_eq
id|SNDRV_SEQ_INSTR_FREE_CMD_PRIVATE
op_logical_or
id|ifree.cmd
op_eq
id|SNDRV_SEQ_INSTR_FREE_CMD_CLUSTER
)paren
(brace
id|result
op_assign
id|snd_seq_instr_list_free_cond
c_func
(paren
id|list
comma
op_amp
id|ifree
comma
id|ev-&gt;dest.client
comma
id|atomic
)paren
suffix:semicolon
r_goto
id|__return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ifree.cmd
op_eq
id|SNDRV_SEQ_INSTR_FREE_CMD_SINGLE
)paren
(brace
r_if
c_cond
(paren
id|ifree.id.instr.std
op_amp
l_int|0xff000000
)paren
(brace
id|ifree.id.instr.std
op_and_assign
l_int|0x00ffffff
suffix:semicolon
id|ifree.id.instr.std
op_or_assign
(paren
r_int
r_int
)paren
id|ev-&gt;source.client
op_lshift
l_int|24
suffix:semicolon
)brace
id|hash
op_assign
id|compute_hash_instr_key
c_func
(paren
op_amp
id|ifree.id.instr
)paren
suffix:semicolon
id|snd_instr_lock_ops
c_func
(paren
id|list
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|instr
op_assign
id|list-&gt;hash
(braket
id|hash
)braket
suffix:semicolon
id|prev
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|instr
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|compare_instr
c_func
(paren
op_amp
id|instr-&gt;instr
comma
op_amp
id|ifree.id.instr
comma
l_int|1
)paren
)paren
r_goto
id|__free_single
suffix:semicolon
id|prev
op_assign
id|instr
suffix:semicolon
id|instr
op_assign
id|instr-&gt;next
suffix:semicolon
)brace
id|result
op_assign
op_minus
id|ENOENT
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|snd_instr_unlock_ops
c_func
(paren
id|list
)paren
suffix:semicolon
r_goto
id|__return
suffix:semicolon
id|__free_single
suffix:colon
r_if
c_cond
(paren
id|prev
)paren
(brace
id|prev-&gt;next
op_assign
id|instr-&gt;next
suffix:semicolon
)brace
r_else
(brace
id|list-&gt;hash
(braket
id|hash
)braket
op_assign
id|instr-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|instr-&gt;ops
op_logical_and
id|instr-&gt;ops-&gt;notify
)paren
id|instr-&gt;ops
op_member_access_from_pointer
id|notify
c_func
(paren
id|instr-&gt;ops-&gt;private_data
comma
id|instr
comma
id|SNDRV_SEQ_INSTR_NOTIFY_REMOVE
)paren
suffix:semicolon
r_while
c_loop
(paren
id|instr-&gt;use
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|result
op_assign
id|snd_seq_instr_free
c_func
(paren
id|instr
comma
id|atomic
)paren
suffix:semicolon
id|snd_instr_unlock_ops
c_func
(paren
id|list
)paren
suffix:semicolon
r_goto
id|__return
suffix:semicolon
)brace
id|__return
suffix:colon
id|instr_result
c_func
(paren
id|ev
comma
id|SNDRV_SEQ_EVENT_INSTR_FREE
comma
id|result
comma
id|atomic
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|instr_list
r_static
r_int
id|instr_list
c_func
(paren
id|snd_seq_kinstr_ops_t
op_star
id|ops
comma
id|snd_seq_kinstr_list_t
op_star
id|list
comma
id|snd_seq_event_t
op_star
id|ev
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
(brace
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|function|instr_cluster
r_static
r_int
id|instr_cluster
c_func
(paren
id|snd_seq_kinstr_ops_t
op_star
id|ops
comma
id|snd_seq_kinstr_list_t
op_star
id|list
comma
id|snd_seq_event_t
op_star
id|ev
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
(brace
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|function|snd_seq_instr_event
r_int
id|snd_seq_instr_event
c_func
(paren
id|snd_seq_kinstr_ops_t
op_star
id|ops
comma
id|snd_seq_kinstr_list_t
op_star
id|list
comma
id|snd_seq_event_t
op_star
id|ev
comma
r_int
id|client
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
(brace
r_int
id|direct
op_assign
l_int|0
suffix:semicolon
id|snd_assert
c_func
(paren
id|ops
op_ne
l_int|NULL
op_logical_and
id|list
op_ne
l_int|NULL
op_logical_and
id|ev
op_ne
l_int|NULL
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snd_seq_ev_is_direct
c_func
(paren
id|ev
)paren
)paren
(brace
id|direct
op_assign
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|ev-&gt;type
)paren
(brace
r_case
id|SNDRV_SEQ_EVENT_INSTR_BEGIN
suffix:colon
r_return
id|instr_begin
c_func
(paren
id|ops
comma
id|list
comma
id|ev
comma
id|atomic
comma
id|hop
)paren
suffix:semicolon
r_case
id|SNDRV_SEQ_EVENT_INSTR_END
suffix:colon
r_return
id|instr_end
c_func
(paren
id|ops
comma
id|list
comma
id|ev
comma
id|atomic
comma
id|hop
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|list-&gt;flags
op_amp
id|SNDRV_SEQ_INSTR_FLG_DIRECT
)paren
op_logical_and
op_logical_neg
id|direct
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
id|ev-&gt;type
)paren
(brace
r_case
id|SNDRV_SEQ_EVENT_INSTR_INFO
suffix:colon
r_return
id|instr_info
c_func
(paren
id|ops
comma
id|list
comma
id|ev
comma
id|atomic
comma
id|hop
)paren
suffix:semicolon
r_case
id|SNDRV_SEQ_EVENT_INSTR_FINFO
suffix:colon
r_return
id|instr_format_info
c_func
(paren
id|ops
comma
id|list
comma
id|ev
comma
id|atomic
comma
id|hop
)paren
suffix:semicolon
r_case
id|SNDRV_SEQ_EVENT_INSTR_RESET
suffix:colon
r_return
id|instr_reset
c_func
(paren
id|ops
comma
id|list
comma
id|ev
comma
id|atomic
comma
id|hop
)paren
suffix:semicolon
r_case
id|SNDRV_SEQ_EVENT_INSTR_STATUS
suffix:colon
r_return
id|instr_status
c_func
(paren
id|ops
comma
id|list
comma
id|ev
comma
id|atomic
comma
id|hop
)paren
suffix:semicolon
r_case
id|SNDRV_SEQ_EVENT_INSTR_PUT
suffix:colon
r_return
id|instr_put
c_func
(paren
id|ops
comma
id|list
comma
id|ev
comma
id|atomic
comma
id|hop
)paren
suffix:semicolon
r_case
id|SNDRV_SEQ_EVENT_INSTR_GET
suffix:colon
r_return
id|instr_get
c_func
(paren
id|ops
comma
id|list
comma
id|ev
comma
id|atomic
comma
id|hop
)paren
suffix:semicolon
r_case
id|SNDRV_SEQ_EVENT_INSTR_FREE
suffix:colon
r_return
id|instr_free
c_func
(paren
id|ops
comma
id|list
comma
id|ev
comma
id|atomic
comma
id|hop
)paren
suffix:semicolon
r_case
id|SNDRV_SEQ_EVENT_INSTR_LIST
suffix:colon
r_return
id|instr_list
c_func
(paren
id|ops
comma
id|list
comma
id|ev
comma
id|atomic
comma
id|hop
)paren
suffix:semicolon
r_case
id|SNDRV_SEQ_EVENT_INSTR_CLUSTER
suffix:colon
r_return
id|instr_cluster
c_func
(paren
id|ops
comma
id|list
comma
id|ev
comma
id|atomic
comma
id|hop
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n; *  Init part&n; */
DECL|function|alsa_seq_instr_init
r_static
r_int
id|__init
id|alsa_seq_instr_init
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alsa_seq_instr_exit
r_static
r_void
id|__exit
id|alsa_seq_instr_exit
c_func
(paren
r_void
)paren
(brace
)brace
id|module_init
c_func
(paren
id|alsa_seq_instr_init
)paren
id|module_exit
c_func
(paren
id|alsa_seq_instr_exit
)paren
id|EXPORT_SYMBOL
c_func
(paren
id|snd_seq_instr_list_new
)paren
suffix:semicolon
DECL|variable|EXPORT_SYMBOL
id|EXPORT_SYMBOL
c_func
(paren
id|snd_seq_instr_list_free
)paren
suffix:semicolon
DECL|variable|snd_seq_instr_list_free_cond
id|EXPORT_SYMBOL
c_func
(paren
id|snd_seq_instr_list_free_cond
)paren
suffix:semicolon
DECL|variable|snd_seq_instr_find
id|EXPORT_SYMBOL
c_func
(paren
id|snd_seq_instr_find
)paren
suffix:semicolon
DECL|variable|snd_seq_instr_free_use
id|EXPORT_SYMBOL
c_func
(paren
id|snd_seq_instr_free_use
)paren
suffix:semicolon
DECL|variable|snd_seq_instr_event
id|EXPORT_SYMBOL
c_func
(paren
id|snd_seq_instr_event
)paren
suffix:semicolon
eof
