multiline_comment|/*&n; * Copyright (c) 2004 Topspin Communications.  All rights reserved.&n; *&n; * This software is available to you under a choice of one of two&n; * licenses.  You may choose to be licensed under the terms of the GNU&n; * General Public License (GPL) Version 2, available from the file&n; * COPYING in the main directory of this source tree, or the&n; * OpenIB.org BSD license below:&n; *&n; *     Redistribution and use in source and binary forms, with or&n; *     without modification, are permitted provided that the following&n; *     conditions are met:&n; *&n; *      - Redistributions of source code must retain the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer.&n; *&n; *      - Redistributions in binary form must reproduce the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer in the documentation and/or other materials&n; *        provided with the distribution.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND,&n; * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF&n; * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND&n; * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS&n; * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN&n; * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN&n; * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE&n; * SOFTWARE.&n; *&n; * $Id: mthca_mr.c 1349 2004-12-16 21:09:43Z roland $&n; */
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &quot;mthca_dev.h&quot;
macro_line|#include &quot;mthca_cmd.h&quot;
multiline_comment|/*&n; * Must be packed because mtt_seg is 64 bits but only aligned to 32 bits.&n; */
DECL|struct|mthca_mpt_entry
r_struct
id|mthca_mpt_entry
(brace
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|page_size
id|u32
id|page_size
suffix:semicolon
DECL|member|key
id|u32
id|key
suffix:semicolon
DECL|member|pd
id|u32
id|pd
suffix:semicolon
DECL|member|start
id|u64
id|start
suffix:semicolon
DECL|member|length
id|u64
id|length
suffix:semicolon
DECL|member|lkey
id|u32
id|lkey
suffix:semicolon
DECL|member|window_count
id|u32
id|window_count
suffix:semicolon
DECL|member|window_count_limit
id|u32
id|window_count_limit
suffix:semicolon
DECL|member|mtt_seg
id|u64
id|mtt_seg
suffix:semicolon
DECL|member|mtt_sz
id|u32
id|mtt_sz
suffix:semicolon
multiline_comment|/* Arbel only */
DECL|member|reserved
id|u32
id|reserved
(braket
l_int|2
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|MTHCA_MPT_FLAG_SW_OWNS
mdefine_line|#define MTHCA_MPT_FLAG_SW_OWNS       (0xfUL &lt;&lt; 28)
DECL|macro|MTHCA_MPT_FLAG_MIO
mdefine_line|#define MTHCA_MPT_FLAG_MIO           (1 &lt;&lt; 17)
DECL|macro|MTHCA_MPT_FLAG_BIND_ENABLE
mdefine_line|#define MTHCA_MPT_FLAG_BIND_ENABLE   (1 &lt;&lt; 15)
DECL|macro|MTHCA_MPT_FLAG_PHYSICAL
mdefine_line|#define MTHCA_MPT_FLAG_PHYSICAL      (1 &lt;&lt;  9)
DECL|macro|MTHCA_MPT_FLAG_REGION
mdefine_line|#define MTHCA_MPT_FLAG_REGION        (1 &lt;&lt;  8)
DECL|macro|MTHCA_MTT_FLAG_PRESENT
mdefine_line|#define MTHCA_MTT_FLAG_PRESENT       1
multiline_comment|/*&n; * Buddy allocator for MTT segments (currently not very efficient&n; * since it doesn&squot;t keep a free list and just searches linearly&n; * through the bitmaps)&n; */
DECL|function|mthca_alloc_mtt
r_static
id|u32
id|mthca_alloc_mtt
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
comma
r_int
id|order
)paren
(brace
r_int
id|o
suffix:semicolon
r_int
id|m
suffix:semicolon
id|u32
id|seg
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dev-&gt;mr_table.mpt_alloc.lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|o
op_assign
id|order
suffix:semicolon
id|o
op_le
id|dev-&gt;mr_table.max_mtt_order
suffix:semicolon
op_increment
id|o
)paren
(brace
id|m
op_assign
l_int|1
op_lshift
(paren
id|dev-&gt;mr_table.max_mtt_order
op_minus
id|o
)paren
suffix:semicolon
id|seg
op_assign
id|find_first_bit
c_func
(paren
id|dev-&gt;mr_table.mtt_buddy
(braket
id|o
)braket
comma
id|m
)paren
suffix:semicolon
r_if
c_cond
(paren
id|seg
OL
id|m
)paren
r_goto
id|found
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;mr_table.mpt_alloc.lock
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
id|found
suffix:colon
id|clear_bit
c_func
(paren
id|seg
comma
id|dev-&gt;mr_table.mtt_buddy
(braket
id|o
)braket
)paren
suffix:semicolon
r_while
c_loop
(paren
id|o
OG
id|order
)paren
(brace
op_decrement
id|o
suffix:semicolon
id|seg
op_lshift_assign
l_int|1
suffix:semicolon
id|set_bit
c_func
(paren
id|seg
op_xor
l_int|1
comma
id|dev-&gt;mr_table.mtt_buddy
(braket
id|o
)braket
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;mr_table.mpt_alloc.lock
)paren
suffix:semicolon
id|seg
op_lshift_assign
id|order
suffix:semicolon
r_return
id|seg
suffix:semicolon
)brace
DECL|function|mthca_free_mtt
r_static
r_void
id|mthca_free_mtt
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
comma
id|u32
id|seg
comma
r_int
id|order
)paren
(brace
id|seg
op_rshift_assign
id|order
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dev-&gt;mr_table.mpt_alloc.lock
)paren
suffix:semicolon
r_while
c_loop
(paren
id|test_bit
c_func
(paren
id|seg
op_xor
l_int|1
comma
id|dev-&gt;mr_table.mtt_buddy
(braket
id|order
)braket
)paren
)paren
(brace
id|clear_bit
c_func
(paren
id|seg
op_xor
l_int|1
comma
id|dev-&gt;mr_table.mtt_buddy
(braket
id|order
)braket
)paren
suffix:semicolon
id|seg
op_rshift_assign
l_int|1
suffix:semicolon
op_increment
id|order
suffix:semicolon
)brace
id|set_bit
c_func
(paren
id|seg
comma
id|dev-&gt;mr_table.mtt_buddy
(braket
id|order
)braket
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;mr_table.mpt_alloc.lock
)paren
suffix:semicolon
)brace
DECL|function|hw_index_to_key
r_static
r_inline
id|u32
id|hw_index_to_key
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
comma
id|u32
id|ind
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;hca_type
op_eq
id|ARBEL_NATIVE
)paren
r_return
(paren
id|ind
op_rshift
l_int|24
)paren
op_or
(paren
id|ind
op_lshift
l_int|8
)paren
suffix:semicolon
r_else
r_return
id|ind
suffix:semicolon
)brace
DECL|function|key_to_hw_index
r_static
r_inline
id|u32
id|key_to_hw_index
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
comma
id|u32
id|key
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;hca_type
op_eq
id|ARBEL_NATIVE
)paren
r_return
(paren
id|key
op_lshift
l_int|24
)paren
op_or
(paren
id|key
op_rshift
l_int|8
)paren
suffix:semicolon
r_else
r_return
id|key
suffix:semicolon
)brace
DECL|function|mthca_mr_alloc_notrans
r_int
id|mthca_mr_alloc_notrans
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
comma
id|u32
id|pd
comma
id|u32
id|access
comma
r_struct
id|mthca_mr
op_star
id|mr
)paren
(brace
r_void
op_star
id|mailbox
suffix:semicolon
r_struct
id|mthca_mpt_entry
op_star
id|mpt_entry
suffix:semicolon
id|u32
id|key
suffix:semicolon
r_int
id|err
suffix:semicolon
id|u8
id|status
suffix:semicolon
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
id|mr-&gt;order
op_assign
op_minus
l_int|1
suffix:semicolon
id|key
op_assign
id|mthca_alloc
c_func
(paren
op_amp
id|dev-&gt;mr_table.mpt_alloc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|key
op_eq
op_minus
l_int|1
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|mr-&gt;ibmr.rkey
op_assign
id|mr-&gt;ibmr.lkey
op_assign
id|hw_index_to_key
c_func
(paren
id|dev
comma
id|key
)paren
suffix:semicolon
id|mailbox
op_assign
id|kmalloc
c_func
(paren
r_sizeof
op_star
id|mpt_entry
op_plus
id|MTHCA_CMD_MAILBOX_EXTRA
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mailbox
)paren
(brace
id|mthca_free
c_func
(paren
op_amp
id|dev-&gt;mr_table.mpt_alloc
comma
id|mr-&gt;ibmr.lkey
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|mpt_entry
op_assign
id|MAILBOX_ALIGN
c_func
(paren
id|mailbox
)paren
suffix:semicolon
id|mpt_entry-&gt;flags
op_assign
id|cpu_to_be32
c_func
(paren
id|MTHCA_MPT_FLAG_SW_OWNS
op_or
id|MTHCA_MPT_FLAG_MIO
op_or
id|MTHCA_MPT_FLAG_PHYSICAL
op_or
id|MTHCA_MPT_FLAG_REGION
op_or
id|access
)paren
suffix:semicolon
id|mpt_entry-&gt;page_size
op_assign
l_int|0
suffix:semicolon
id|mpt_entry-&gt;key
op_assign
id|cpu_to_be32
c_func
(paren
id|key
)paren
suffix:semicolon
id|mpt_entry-&gt;pd
op_assign
id|cpu_to_be32
c_func
(paren
id|pd
)paren
suffix:semicolon
id|mpt_entry-&gt;start
op_assign
l_int|0
suffix:semicolon
id|mpt_entry-&gt;length
op_assign
op_complement
l_int|0ULL
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|mpt_entry-&gt;lkey
comma
l_int|0
comma
r_sizeof
op_star
id|mpt_entry
op_minus
m_offsetof
(paren
r_struct
id|mthca_mpt_entry
comma
id|lkey
)paren
)paren
suffix:semicolon
id|err
op_assign
id|mthca_SW2HW_MPT
c_func
(paren
id|dev
comma
id|mpt_entry
comma
id|key
op_amp
(paren
id|dev-&gt;limits.num_mpts
op_minus
l_int|1
)paren
comma
op_amp
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|mthca_warn
c_func
(paren
id|dev
comma
l_string|&quot;SW2HW_MPT failed (%d)&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|status
)paren
(brace
id|mthca_warn
c_func
(paren
id|dev
comma
l_string|&quot;SW2HW_MPT returned status 0x%02x&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|mailbox
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|mthca_mr_alloc_phys
r_int
id|mthca_mr_alloc_phys
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
comma
id|u32
id|pd
comma
id|u64
op_star
id|buffer_list
comma
r_int
id|buffer_size_shift
comma
r_int
id|list_len
comma
id|u64
id|iova
comma
id|u64
id|total_size
comma
id|u32
id|access
comma
r_struct
id|mthca_mr
op_star
id|mr
)paren
(brace
r_void
op_star
id|mailbox
suffix:semicolon
id|u64
op_star
id|mtt_entry
suffix:semicolon
r_struct
id|mthca_mpt_entry
op_star
id|mpt_entry
suffix:semicolon
id|u32
id|key
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|u8
id|status
suffix:semicolon
r_int
id|i
suffix:semicolon
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
id|WARN_ON
c_func
(paren
id|buffer_size_shift
op_ge
l_int|32
)paren
suffix:semicolon
id|key
op_assign
id|mthca_alloc
c_func
(paren
op_amp
id|dev-&gt;mr_table.mpt_alloc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|key
op_eq
op_minus
l_int|1
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|mr-&gt;ibmr.rkey
op_assign
id|mr-&gt;ibmr.lkey
op_assign
id|hw_index_to_key
c_func
(paren
id|dev
comma
id|key
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|dev-&gt;limits.mtt_seg_size
op_div
l_int|8
comma
id|mr-&gt;order
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|list_len
suffix:semicolon
id|i
op_lshift_assign
l_int|1
comma
op_increment
id|mr-&gt;order
)paren
suffix:semicolon
multiline_comment|/* nothing */
id|mr-&gt;first_seg
op_assign
id|mthca_alloc_mtt
c_func
(paren
id|dev
comma
id|mr-&gt;order
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mr-&gt;first_seg
op_eq
op_minus
l_int|1
)paren
r_goto
id|err_out_mpt_free
suffix:semicolon
multiline_comment|/*&n;&t; * If list_len is odd, we add one more dummy entry for&n;&t; * firmware efficiency.&n;&t; */
id|mailbox
op_assign
id|kmalloc
c_func
(paren
id|max
c_func
(paren
r_sizeof
op_star
id|mpt_entry
comma
(paren
r_int
)paren
l_int|8
op_star
(paren
id|list_len
op_plus
(paren
id|list_len
op_amp
l_int|1
)paren
op_plus
l_int|2
)paren
)paren
op_plus
id|MTHCA_CMD_MAILBOX_EXTRA
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mailbox
)paren
r_goto
id|err_out_free_mtt
suffix:semicolon
id|mtt_entry
op_assign
id|MAILBOX_ALIGN
c_func
(paren
id|mailbox
)paren
suffix:semicolon
id|mtt_entry
(braket
l_int|0
)braket
op_assign
id|cpu_to_be64
c_func
(paren
id|dev-&gt;mr_table.mtt_base
op_plus
id|mr-&gt;first_seg
op_star
id|dev-&gt;limits.mtt_seg_size
)paren
suffix:semicolon
id|mtt_entry
(braket
l_int|1
)braket
op_assign
l_int|0
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
id|list_len
suffix:semicolon
op_increment
id|i
)paren
id|mtt_entry
(braket
id|i
op_plus
l_int|2
)braket
op_assign
id|cpu_to_be64
c_func
(paren
id|buffer_list
(braket
id|i
)braket
op_or
id|MTHCA_MTT_FLAG_PRESENT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_len
op_amp
l_int|1
)paren
(brace
id|mtt_entry
(braket
id|i
op_plus
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
op_increment
id|list_len
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
)paren
(brace
id|mthca_dbg
c_func
(paren
id|dev
comma
l_string|&quot;Dumping MPT entry&bslash;n&quot;
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
id|list_len
op_plus
l_int|2
suffix:semicolon
op_increment
id|i
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;[%2d] %016llx&bslash;n&quot;
comma
id|i
comma
(paren
r_int
r_int
r_int
)paren
id|be64_to_cpu
c_func
(paren
id|mtt_entry
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
)brace
id|err
op_assign
id|mthca_WRITE_MTT
c_func
(paren
id|dev
comma
id|mtt_entry
comma
id|list_len
comma
op_amp
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|mthca_warn
c_func
(paren
id|dev
comma
l_string|&quot;WRITE_MTT failed (%d)&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
r_goto
id|err_out_mailbox_free
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
)paren
(brace
id|mthca_warn
c_func
(paren
id|dev
comma
l_string|&quot;WRITE_MTT returned status 0x%02x&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|err_out_mailbox_free
suffix:semicolon
)brace
id|mpt_entry
op_assign
id|MAILBOX_ALIGN
c_func
(paren
id|mailbox
)paren
suffix:semicolon
id|mpt_entry-&gt;flags
op_assign
id|cpu_to_be32
c_func
(paren
id|MTHCA_MPT_FLAG_SW_OWNS
op_or
id|MTHCA_MPT_FLAG_MIO
op_or
id|MTHCA_MPT_FLAG_REGION
op_or
id|access
)paren
suffix:semicolon
id|mpt_entry-&gt;page_size
op_assign
id|cpu_to_be32
c_func
(paren
id|buffer_size_shift
op_minus
l_int|12
)paren
suffix:semicolon
id|mpt_entry-&gt;key
op_assign
id|cpu_to_be32
c_func
(paren
id|key
)paren
suffix:semicolon
id|mpt_entry-&gt;pd
op_assign
id|cpu_to_be32
c_func
(paren
id|pd
)paren
suffix:semicolon
id|mpt_entry-&gt;start
op_assign
id|cpu_to_be64
c_func
(paren
id|iova
)paren
suffix:semicolon
id|mpt_entry-&gt;length
op_assign
id|cpu_to_be64
c_func
(paren
id|total_size
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|mpt_entry-&gt;lkey
comma
l_int|0
comma
r_sizeof
op_star
id|mpt_entry
op_minus
m_offsetof
(paren
r_struct
id|mthca_mpt_entry
comma
id|lkey
)paren
)paren
suffix:semicolon
id|mpt_entry-&gt;mtt_seg
op_assign
id|cpu_to_be64
c_func
(paren
id|dev-&gt;mr_table.mtt_base
op_plus
id|mr-&gt;first_seg
op_star
id|dev-&gt;limits.mtt_seg_size
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
)paren
(brace
id|mthca_dbg
c_func
(paren
id|dev
comma
l_string|&quot;Dumping MPT entry %08x:&bslash;n&quot;
comma
id|mr-&gt;ibmr.lkey
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
r_sizeof
(paren
r_struct
id|mthca_mpt_entry
)paren
op_div
l_int|4
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|i
op_mod
l_int|4
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;[%02x] &quot;
comma
id|i
op_star
l_int|4
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; %08x&quot;
comma
id|be32_to_cpu
c_func
(paren
(paren
(paren
id|u32
op_star
)paren
id|mpt_entry
)paren
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i
op_plus
l_int|1
)paren
op_mod
l_int|4
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|err
op_assign
id|mthca_SW2HW_MPT
c_func
(paren
id|dev
comma
id|mpt_entry
comma
id|key
op_amp
(paren
id|dev-&gt;limits.num_mpts
op_minus
l_int|1
)paren
comma
op_amp
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|mthca_warn
c_func
(paren
id|dev
comma
l_string|&quot;SW2HW_MPT failed (%d)&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|status
)paren
(brace
id|mthca_warn
c_func
(paren
id|dev
comma
l_string|&quot;SW2HW_MPT returned status 0x%02x&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|mailbox
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
id|err_out_mailbox_free
suffix:colon
id|kfree
c_func
(paren
id|mailbox
)paren
suffix:semicolon
id|err_out_free_mtt
suffix:colon
id|mthca_free_mtt
c_func
(paren
id|dev
comma
id|mr-&gt;first_seg
comma
id|mr-&gt;order
)paren
suffix:semicolon
id|err_out_mpt_free
suffix:colon
id|mthca_free
c_func
(paren
op_amp
id|dev-&gt;mr_table.mpt_alloc
comma
id|mr-&gt;ibmr.lkey
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|mthca_free_mr
r_void
id|mthca_free_mr
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
comma
r_struct
id|mthca_mr
op_star
id|mr
)paren
(brace
r_int
id|err
suffix:semicolon
id|u8
id|status
suffix:semicolon
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
id|err
op_assign
id|mthca_HW2SW_MPT
c_func
(paren
id|dev
comma
l_int|NULL
comma
id|key_to_hw_index
c_func
(paren
id|dev
comma
id|mr-&gt;ibmr.lkey
)paren
op_amp
(paren
id|dev-&gt;limits.num_mpts
op_minus
l_int|1
)paren
comma
op_amp
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|mthca_warn
c_func
(paren
id|dev
comma
l_string|&quot;HW2SW_MPT failed (%d)&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|status
)paren
id|mthca_warn
c_func
(paren
id|dev
comma
l_string|&quot;HW2SW_MPT returned status 0x%02x&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mr-&gt;order
op_ge
l_int|0
)paren
id|mthca_free_mtt
c_func
(paren
id|dev
comma
id|mr-&gt;first_seg
comma
id|mr-&gt;order
)paren
suffix:semicolon
id|mthca_free
c_func
(paren
op_amp
id|dev-&gt;mr_table.mpt_alloc
comma
id|key_to_hw_index
c_func
(paren
id|dev
comma
id|mr-&gt;ibmr.lkey
)paren
)paren
suffix:semicolon
)brace
DECL|function|mthca_init_mr_table
r_int
id|__devinit
id|mthca_init_mr_table
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
)paren
(brace
r_int
id|err
suffix:semicolon
r_int
id|i
comma
id|s
suffix:semicolon
id|err
op_assign
id|mthca_alloc_init
c_func
(paren
op_amp
id|dev-&gt;mr_table.mpt_alloc
comma
id|dev-&gt;limits.num_mpts
comma
op_complement
l_int|0
comma
id|dev-&gt;limits.reserved_mrws
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
comma
id|dev-&gt;mr_table.max_mtt_order
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dev-&gt;limits.num_mtt_segs
suffix:semicolon
id|i
op_lshift_assign
l_int|1
comma
op_increment
id|dev-&gt;mr_table.max_mtt_order
)paren
suffix:semicolon
multiline_comment|/* nothing */
id|dev-&gt;mr_table.mtt_buddy
op_assign
id|kmalloc
c_func
(paren
(paren
id|dev-&gt;mr_table.max_mtt_order
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_int
op_star
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;mr_table.mtt_buddy
)paren
r_goto
id|err_out
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|dev-&gt;mr_table.max_mtt_order
suffix:semicolon
op_increment
id|i
)paren
id|dev-&gt;mr_table.mtt_buddy
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|dev-&gt;mr_table.max_mtt_order
suffix:semicolon
op_increment
id|i
)paren
(brace
id|s
op_assign
id|BITS_TO_LONGS
c_func
(paren
l_int|1
op_lshift
(paren
id|dev-&gt;mr_table.max_mtt_order
op_minus
id|i
)paren
)paren
suffix:semicolon
id|dev-&gt;mr_table.mtt_buddy
(braket
id|i
)braket
op_assign
id|kmalloc
c_func
(paren
id|s
op_star
r_sizeof
(paren
r_int
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;mr_table.mtt_buddy
(braket
id|i
)braket
)paren
r_goto
id|err_out_free
suffix:semicolon
id|bitmap_zero
c_func
(paren
id|dev-&gt;mr_table.mtt_buddy
(braket
id|i
)braket
comma
l_int|1
op_lshift
(paren
id|dev-&gt;mr_table.max_mtt_order
op_minus
id|i
)paren
)paren
suffix:semicolon
)brace
id|set_bit
c_func
(paren
l_int|0
comma
id|dev-&gt;mr_table.mtt_buddy
(braket
id|dev-&gt;mr_table.max_mtt_order
)braket
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
id|dev-&gt;mr_table.max_mtt_order
suffix:semicolon
op_increment
id|i
)paren
r_if
c_cond
(paren
l_int|1
op_lshift
id|i
op_ge
id|dev-&gt;limits.reserved_mtts
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|dev-&gt;mr_table.max_mtt_order
)paren
(brace
id|mthca_err
c_func
(paren
id|dev
comma
l_string|&quot;MTT table of order %d is &quot;
l_string|&quot;too small.&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
r_goto
id|err_out_free
suffix:semicolon
)brace
(paren
r_void
)paren
id|mthca_alloc_mtt
c_func
(paren
id|dev
comma
id|i
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_out_free
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|dev-&gt;mr_table.max_mtt_order
suffix:semicolon
op_increment
id|i
)paren
id|kfree
c_func
(paren
id|dev-&gt;mr_table.mtt_buddy
(braket
id|i
)braket
)paren
suffix:semicolon
id|err_out
suffix:colon
id|mthca_alloc_cleanup
c_func
(paren
op_amp
id|dev-&gt;mr_table.mpt_alloc
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|mthca_cleanup_mr_table
r_void
id|__devexit
id|mthca_cleanup_mr_table
c_func
(paren
r_struct
id|mthca_dev
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* XXX check if any MRs are still allocated? */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|dev-&gt;mr_table.max_mtt_order
suffix:semicolon
op_increment
id|i
)paren
id|kfree
c_func
(paren
id|dev-&gt;mr_table.mtt_buddy
(braket
id|i
)braket
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev-&gt;mr_table.mtt_buddy
)paren
suffix:semicolon
id|mthca_alloc_cleanup
c_func
(paren
op_amp
id|dev-&gt;mr_table.mpt_alloc
)paren
suffix:semicolon
)brace
eof
