multiline_comment|/*&n; *  linux/fs/ufs/truncate.c&n; *&n; * Copyright (C) 1998&n; * Daniel Pirkl &lt;daniel.pirkl@email.cz&gt;&n; * Charles University, Faculty of Mathematics and Physics&n; *&n; *  from&n; *&n; *  linux/fs/ext2/truncate.c&n; *&n; * Copyright (C) 1992, 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  from&n; *&n; *  linux/fs/minix/truncate.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  Big-endian to little-endian byte-swapping/bitmaps by&n; *        David S. Miller (davem@caip.rutgers.edu), 1995&n; */
multiline_comment|/*&n; * Real random numbers for secure rm added 94/02/18&n; * Idea from Pierre del Perugia &lt;delperug@gla.ecoledoc.ibp.fr&gt;&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ufs_fs.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &quot;swab.h&quot;
macro_line|#include &quot;util.h&quot;
DECL|macro|UFS_TRUNCATE_DEBUG
macro_line|#undef UFS_TRUNCATE_DEBUG
macro_line|#ifdef UFS_TRUNCATE_DEBUG
DECL|macro|UFSD
mdefine_line|#define UFSD(x) printk(&quot;(%s, %d), %s: &quot;, __FILE__, __LINE__, __FUNCTION__); printk x;
macro_line|#else
DECL|macro|UFSD
mdefine_line|#define UFSD(x)
macro_line|#endif
multiline_comment|/*&n; * Secure deletion currently doesn&squot;t work. It interacts very badly&n; * with buffers shared with memory mappings, and for that reason&n; * can&squot;t be done in the truncate() routines. It should instead be&n; * done separately in &quot;release()&quot; before calling the truncate routines&n; * that will release the actual file blocks.&n; *&n; *&t;&t;Linus&n; */
DECL|macro|DIRECT_BLOCK
mdefine_line|#define DIRECT_BLOCK ((inode-&gt;i_size + uspi-&gt;s_bsize - 1) &gt;&gt; uspi-&gt;s_bshift)
DECL|macro|DIRECT_FRAGMENT
mdefine_line|#define DIRECT_FRAGMENT ((inode-&gt;i_size + uspi-&gt;s_fsize - 1) &gt;&gt; uspi-&gt;s_fshift)
DECL|macro|DATA_BUFFER_USED
mdefine_line|#define DATA_BUFFER_USED(bh) &bslash;&n;&t;(atomic_read(&amp;bh-&gt;b_count)&gt;1 || buffer_locked(bh))
DECL|function|ufs_trunc_direct
r_static
r_int
id|ufs_trunc_direct
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_struct
id|ufs_sb_private_info
op_star
id|uspi
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|u32
op_star
id|p
suffix:semicolon
r_int
id|frag1
comma
id|frag2
comma
id|frag3
comma
id|frag4
comma
id|block1
comma
id|block2
suffix:semicolon
r_int
id|frag_to_free
comma
id|free_count
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|tmp
suffix:semicolon
r_int
id|retry
suffix:semicolon
r_int
id|swab
suffix:semicolon
id|UFSD
c_func
(paren
(paren
l_string|&quot;ENTER&bslash;n&quot;
)paren
)paren
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
id|swab
op_assign
id|sb-&gt;u.ufs_sb.s_swab
suffix:semicolon
id|uspi
op_assign
id|sb-&gt;u.ufs_sb.s_uspi
suffix:semicolon
id|frag_to_free
op_assign
l_int|0
suffix:semicolon
id|free_count
op_assign
l_int|0
suffix:semicolon
id|retry
op_assign
l_int|0
suffix:semicolon
id|frag1
op_assign
id|DIRECT_FRAGMENT
suffix:semicolon
id|frag4
op_assign
id|min_t
c_func
(paren
id|u32
comma
id|UFS_NDIR_FRAGMENT
comma
id|inode-&gt;u.ufs_i.i_lastfrag
)paren
suffix:semicolon
id|frag2
op_assign
(paren
(paren
id|frag1
op_amp
id|uspi-&gt;s_fpbmask
)paren
ques
c_cond
(paren
(paren
id|frag1
op_or
id|uspi-&gt;s_fpbmask
)paren
op_plus
l_int|1
)paren
suffix:colon
id|frag1
)paren
suffix:semicolon
id|frag3
op_assign
id|frag4
op_amp
op_complement
id|uspi-&gt;s_fpbmask
suffix:semicolon
id|block1
op_assign
id|block2
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|frag2
OG
id|frag3
)paren
(brace
id|frag2
op_assign
id|frag4
suffix:semicolon
id|frag3
op_assign
id|frag4
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|frag2
OL
id|frag3
)paren
(brace
id|block1
op_assign
id|ufs_fragstoblks
(paren
id|frag2
)paren
suffix:semicolon
id|block2
op_assign
id|ufs_fragstoblks
(paren
id|frag3
)paren
suffix:semicolon
)brace
id|UFSD
c_func
(paren
(paren
l_string|&quot;frag1 %u, frag2 %u, block1 %u, block2 %u, frag3 %u, frag4 %u&bslash;n&quot;
comma
id|frag1
comma
id|frag2
comma
id|block1
comma
id|block2
comma
id|frag3
comma
id|frag4
)paren
)paren
r_if
c_cond
(paren
id|frag1
op_ge
id|frag2
)paren
r_goto
id|next1
suffix:semicolon
multiline_comment|/*&n;&t; * Free first free fragments&n;&t; */
id|p
op_assign
id|inode-&gt;u.ufs_i.i_u1.i_data
op_plus
id|ufs_fragstoblks
(paren
id|frag1
)paren
suffix:semicolon
id|tmp
op_assign
id|SWAB32
c_func
(paren
op_star
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
id|ufs_panic
(paren
id|sb
comma
l_string|&quot;ufs_trunc_direct&quot;
comma
l_string|&quot;internal error&quot;
)paren
suffix:semicolon
id|frag1
op_assign
id|ufs_fragnum
(paren
id|frag1
)paren
suffix:semicolon
id|frag2
op_assign
id|ufs_fragnum
(paren
id|frag2
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
id|frag1
suffix:semicolon
id|j
OL
id|frag2
suffix:semicolon
id|j
op_increment
)paren
(brace
id|bh
op_assign
id|get_hash_table
(paren
id|sb-&gt;s_dev
comma
id|tmp
op_plus
id|j
comma
id|uspi-&gt;s_fsize
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bh
op_logical_and
id|DATA_BUFFER_USED
c_func
(paren
id|bh
)paren
)paren
op_logical_or
id|tmp
op_ne
id|SWAB32
c_func
(paren
op_star
id|p
)paren
)paren
(brace
id|retry
op_assign
l_int|1
suffix:semicolon
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_goto
id|next1
suffix:semicolon
)brace
id|bforget
(paren
id|bh
)paren
suffix:semicolon
)brace
id|inode-&gt;i_blocks
op_sub_assign
(paren
id|frag2
op_minus
id|frag1
)paren
op_lshift
id|uspi-&gt;s_nspfshift
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|ufs_free_fragments
(paren
id|inode
comma
id|tmp
op_plus
id|frag1
comma
id|frag2
op_minus
id|frag1
)paren
suffix:semicolon
id|frag_to_free
op_assign
id|tmp
op_plus
id|frag1
suffix:semicolon
id|next1
suffix:colon
multiline_comment|/*&n;&t; * Free whole blocks&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
id|block1
suffix:semicolon
id|i
OL
id|block2
suffix:semicolon
id|i
op_increment
)paren
(brace
id|p
op_assign
id|inode-&gt;u.ufs_i.i_u1.i_data
op_plus
id|i
suffix:semicolon
id|tmp
op_assign
id|SWAB32
c_func
(paren
op_star
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|uspi-&gt;s_fpb
suffix:semicolon
id|j
op_increment
)paren
(brace
id|bh
op_assign
id|get_hash_table
(paren
id|sb-&gt;s_dev
comma
id|tmp
op_plus
id|j
comma
id|uspi-&gt;s_fsize
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bh
op_logical_and
id|DATA_BUFFER_USED
c_func
(paren
id|bh
)paren
)paren
op_logical_or
id|tmp
op_ne
id|SWAB32
c_func
(paren
op_star
id|p
)paren
)paren
(brace
id|retry
op_assign
l_int|1
suffix:semicolon
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_goto
id|next2
suffix:semicolon
)brace
id|bforget
(paren
id|bh
)paren
suffix:semicolon
)brace
op_star
id|p
op_assign
id|SWAB32
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|inode-&gt;i_blocks
op_sub_assign
id|uspi-&gt;s_nspb
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|free_count
op_eq
l_int|0
)paren
(brace
id|frag_to_free
op_assign
id|tmp
suffix:semicolon
id|free_count
op_assign
id|uspi-&gt;s_fpb
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|free_count
OG
l_int|0
op_logical_and
id|frag_to_free
op_eq
id|tmp
op_minus
id|free_count
)paren
id|free_count
op_add_assign
id|uspi-&gt;s_fpb
suffix:semicolon
r_else
(brace
id|ufs_free_blocks
(paren
id|inode
comma
id|frag_to_free
comma
id|free_count
)paren
suffix:semicolon
id|frag_to_free
op_assign
id|tmp
suffix:semicolon
id|free_count
op_assign
id|uspi-&gt;s_fpb
suffix:semicolon
)brace
id|next2
suffix:colon
suffix:semicolon
)brace
r_if
c_cond
(paren
id|free_count
OG
l_int|0
)paren
id|ufs_free_blocks
(paren
id|inode
comma
id|frag_to_free
comma
id|free_count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|frag3
op_ge
id|frag4
)paren
r_goto
id|next3
suffix:semicolon
multiline_comment|/*&n;&t; * Free last free fragments&n;&t; */
id|p
op_assign
id|inode-&gt;u.ufs_i.i_u1.i_data
op_plus
id|ufs_fragstoblks
(paren
id|frag3
)paren
suffix:semicolon
id|tmp
op_assign
id|SWAB32
c_func
(paren
op_star
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
id|ufs_panic
c_func
(paren
id|sb
comma
l_string|&quot;ufs_truncate_direct&quot;
comma
l_string|&quot;internal error&quot;
)paren
suffix:semicolon
id|frag4
op_assign
id|ufs_fragnum
(paren
id|frag4
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|frag4
suffix:semicolon
id|j
op_increment
)paren
(brace
id|bh
op_assign
id|get_hash_table
(paren
id|sb-&gt;s_dev
comma
id|tmp
op_plus
id|j
comma
id|uspi-&gt;s_fsize
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bh
op_logical_and
id|DATA_BUFFER_USED
c_func
(paren
id|bh
)paren
)paren
op_logical_or
id|tmp
op_ne
id|SWAB32
c_func
(paren
op_star
id|p
)paren
)paren
(brace
id|retry
op_assign
l_int|1
suffix:semicolon
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_goto
id|next1
suffix:semicolon
)brace
id|bforget
(paren
id|bh
)paren
suffix:semicolon
)brace
op_star
id|p
op_assign
id|SWAB32
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|inode-&gt;i_blocks
op_sub_assign
id|frag4
op_lshift
id|uspi-&gt;s_nspfshift
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|ufs_free_fragments
(paren
id|inode
comma
id|tmp
comma
id|frag4
)paren
suffix:semicolon
id|next3
suffix:colon
id|UFSD
c_func
(paren
(paren
l_string|&quot;EXIT&bslash;n&quot;
)paren
)paren
r_return
id|retry
suffix:semicolon
)brace
DECL|function|ufs_trunc_indirect
r_static
r_int
id|ufs_trunc_indirect
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|offset
comma
id|u32
op_star
id|p
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_struct
id|ufs_sb_private_info
op_star
id|uspi
suffix:semicolon
r_struct
id|ufs_buffer_head
op_star
id|ind_ubh
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|u32
op_star
id|ind
suffix:semicolon
r_int
id|indirect_block
comma
id|i
comma
id|j
comma
id|tmp
suffix:semicolon
r_int
id|frag_to_free
comma
id|free_count
suffix:semicolon
r_int
id|retry
suffix:semicolon
r_int
id|swab
suffix:semicolon
id|UFSD
c_func
(paren
(paren
l_string|&quot;ENTER&bslash;n&quot;
)paren
)paren
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
id|swab
op_assign
id|sb-&gt;u.ufs_sb.s_swab
suffix:semicolon
id|uspi
op_assign
id|sb-&gt;u.ufs_sb.s_uspi
suffix:semicolon
id|frag_to_free
op_assign
l_int|0
suffix:semicolon
id|free_count
op_assign
l_int|0
suffix:semicolon
id|retry
op_assign
l_int|0
suffix:semicolon
id|tmp
op_assign
id|SWAB32
c_func
(paren
op_star
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
r_return
l_int|0
suffix:semicolon
id|ind_ubh
op_assign
id|ubh_bread
(paren
id|sb-&gt;s_dev
comma
id|tmp
comma
id|uspi-&gt;s_bsize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ne
id|SWAB32
c_func
(paren
op_star
id|p
)paren
)paren
(brace
id|ubh_brelse
(paren
id|ind_ubh
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ind_ubh
)paren
(brace
op_star
id|p
op_assign
id|SWAB32
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|indirect_block
op_assign
(paren
id|DIRECT_BLOCK
OG
id|offset
)paren
ques
c_cond
(paren
id|DIRECT_BLOCK
op_minus
id|offset
)paren
suffix:colon
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|indirect_block
suffix:semicolon
id|i
OL
id|uspi-&gt;s_apb
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ind
op_assign
id|ubh_get_addr32
(paren
id|ind_ubh
comma
id|i
)paren
suffix:semicolon
id|tmp
op_assign
id|SWAB32
c_func
(paren
op_star
id|ind
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|uspi-&gt;s_fpb
suffix:semicolon
id|j
op_increment
)paren
(brace
id|bh
op_assign
id|get_hash_table
(paren
id|sb-&gt;s_dev
comma
id|tmp
op_plus
id|j
comma
id|uspi-&gt;s_fsize
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bh
op_logical_and
id|DATA_BUFFER_USED
c_func
(paren
id|bh
)paren
)paren
op_logical_or
id|tmp
op_ne
id|SWAB32
c_func
(paren
op_star
id|ind
)paren
)paren
(brace
id|retry
op_assign
l_int|1
suffix:semicolon
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_goto
id|next
suffix:semicolon
)brace
id|bforget
(paren
id|bh
)paren
suffix:semicolon
)brace
op_star
id|ind
op_assign
id|SWAB32
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|ubh_mark_buffer_dirty
c_func
(paren
id|ind_ubh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|free_count
op_eq
l_int|0
)paren
(brace
id|frag_to_free
op_assign
id|tmp
suffix:semicolon
id|free_count
op_assign
id|uspi-&gt;s_fpb
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|free_count
OG
l_int|0
op_logical_and
id|frag_to_free
op_eq
id|tmp
op_minus
id|free_count
)paren
id|free_count
op_add_assign
id|uspi-&gt;s_fpb
suffix:semicolon
r_else
(brace
id|ufs_free_blocks
(paren
id|inode
comma
id|frag_to_free
comma
id|free_count
)paren
suffix:semicolon
id|frag_to_free
op_assign
id|tmp
suffix:semicolon
id|free_count
op_assign
id|uspi-&gt;s_fpb
suffix:semicolon
)brace
id|inode-&gt;i_blocks
op_sub_assign
id|uspi-&gt;s_nspb
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|next
suffix:colon
suffix:semicolon
)brace
r_if
c_cond
(paren
id|free_count
OG
l_int|0
)paren
(brace
id|ufs_free_blocks
(paren
id|inode
comma
id|frag_to_free
comma
id|free_count
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|uspi-&gt;s_apb
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|SWAB32
c_func
(paren
op_star
id|ubh_get_addr32
c_func
(paren
id|ind_ubh
comma
id|i
)paren
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|uspi-&gt;s_apb
)paren
(brace
r_if
c_cond
(paren
id|ubh_max_bcount
c_func
(paren
id|ind_ubh
)paren
op_ne
l_int|1
)paren
(brace
id|retry
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|tmp
op_assign
id|SWAB32
c_func
(paren
op_star
id|p
)paren
suffix:semicolon
op_star
id|p
op_assign
id|SWAB32
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|inode-&gt;i_blocks
op_sub_assign
id|uspi-&gt;s_nspb
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|ufs_free_blocks
(paren
id|inode
comma
id|tmp
comma
id|uspi-&gt;s_fpb
)paren
suffix:semicolon
id|ubh_bforget
c_func
(paren
id|ind_ubh
)paren
suffix:semicolon
id|ind_ubh
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|IS_SYNC
c_func
(paren
id|inode
)paren
op_logical_and
id|ind_ubh
op_logical_and
id|ubh_buffer_dirty
c_func
(paren
id|ind_ubh
)paren
)paren
(brace
id|ubh_ll_rw_block
(paren
id|WRITE
comma
l_int|1
comma
op_amp
id|ind_ubh
)paren
suffix:semicolon
id|ubh_wait_on_buffer
(paren
id|ind_ubh
)paren
suffix:semicolon
)brace
id|ubh_brelse
(paren
id|ind_ubh
)paren
suffix:semicolon
id|UFSD
c_func
(paren
(paren
l_string|&quot;EXIT&bslash;n&quot;
)paren
)paren
r_return
id|retry
suffix:semicolon
)brace
DECL|function|ufs_trunc_dindirect
r_static
r_int
id|ufs_trunc_dindirect
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|offset
comma
id|u32
op_star
id|p
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_struct
id|ufs_sb_private_info
op_star
id|uspi
suffix:semicolon
r_struct
id|ufs_buffer_head
op_star
id|dind_bh
suffix:semicolon
r_int
id|i
comma
id|tmp
comma
id|dindirect_block
suffix:semicolon
id|u32
op_star
id|dind
suffix:semicolon
r_int
id|retry
op_assign
l_int|0
suffix:semicolon
r_int
id|swab
suffix:semicolon
id|UFSD
c_func
(paren
(paren
l_string|&quot;ENTER&bslash;n&quot;
)paren
)paren
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
id|swab
op_assign
id|sb-&gt;u.ufs_sb.s_swab
suffix:semicolon
id|uspi
op_assign
id|sb-&gt;u.ufs_sb.s_uspi
suffix:semicolon
id|dindirect_block
op_assign
(paren
id|DIRECT_BLOCK
OG
id|offset
)paren
ques
c_cond
(paren
(paren
id|DIRECT_BLOCK
op_minus
id|offset
)paren
op_rshift
id|uspi-&gt;s_apbshift
)paren
suffix:colon
l_int|0
suffix:semicolon
id|retry
op_assign
l_int|0
suffix:semicolon
id|tmp
op_assign
id|SWAB32
c_func
(paren
op_star
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
r_return
l_int|0
suffix:semicolon
id|dind_bh
op_assign
id|ubh_bread
(paren
id|inode-&gt;i_dev
comma
id|tmp
comma
id|uspi-&gt;s_bsize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ne
id|SWAB32
c_func
(paren
op_star
id|p
)paren
)paren
(brace
id|ubh_brelse
(paren
id|dind_bh
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dind_bh
)paren
(brace
op_star
id|p
op_assign
id|SWAB32
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
id|dindirect_block
suffix:semicolon
id|i
OL
id|uspi-&gt;s_apb
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dind
op_assign
id|ubh_get_addr32
(paren
id|dind_bh
comma
id|i
)paren
suffix:semicolon
id|tmp
op_assign
id|SWAB32
c_func
(paren
op_star
id|dind
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
r_continue
suffix:semicolon
id|retry
op_or_assign
id|ufs_trunc_indirect
(paren
id|inode
comma
id|offset
op_plus
(paren
id|i
op_lshift
id|uspi-&gt;s_apbshift
)paren
comma
id|dind
)paren
suffix:semicolon
id|ubh_mark_buffer_dirty
c_func
(paren
id|dind_bh
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|uspi-&gt;s_apb
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|SWAB32
c_func
(paren
op_star
id|ubh_get_addr32
(paren
id|dind_bh
comma
id|i
)paren
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|uspi-&gt;s_apb
)paren
(brace
r_if
c_cond
(paren
id|ubh_max_bcount
c_func
(paren
id|dind_bh
)paren
op_ne
l_int|1
)paren
id|retry
op_assign
l_int|1
suffix:semicolon
r_else
(brace
id|tmp
op_assign
id|SWAB32
c_func
(paren
op_star
id|p
)paren
suffix:semicolon
op_star
id|p
op_assign
id|SWAB32
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|inode-&gt;i_blocks
op_sub_assign
id|uspi-&gt;s_nspb
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|ufs_free_blocks
(paren
id|inode
comma
id|tmp
comma
id|uspi-&gt;s_fpb
)paren
suffix:semicolon
id|ubh_bforget
c_func
(paren
id|dind_bh
)paren
suffix:semicolon
id|dind_bh
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|IS_SYNC
c_func
(paren
id|inode
)paren
op_logical_and
id|dind_bh
op_logical_and
id|ubh_buffer_dirty
c_func
(paren
id|dind_bh
)paren
)paren
(brace
id|ubh_ll_rw_block
(paren
id|WRITE
comma
l_int|1
comma
op_amp
id|dind_bh
)paren
suffix:semicolon
id|ubh_wait_on_buffer
(paren
id|dind_bh
)paren
suffix:semicolon
)brace
id|ubh_brelse
(paren
id|dind_bh
)paren
suffix:semicolon
id|UFSD
c_func
(paren
(paren
l_string|&quot;EXIT&bslash;n&quot;
)paren
)paren
r_return
id|retry
suffix:semicolon
)brace
DECL|function|ufs_trunc_tindirect
r_static
r_int
id|ufs_trunc_tindirect
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_struct
id|ufs_sb_private_info
op_star
id|uspi
suffix:semicolon
r_struct
id|ufs_buffer_head
op_star
id|tind_bh
suffix:semicolon
r_int
id|tindirect_block
comma
id|tmp
comma
id|i
suffix:semicolon
id|u32
op_star
id|tind
comma
op_star
id|p
suffix:semicolon
r_int
id|retry
suffix:semicolon
r_int
id|swab
suffix:semicolon
id|UFSD
c_func
(paren
(paren
l_string|&quot;ENTER&bslash;n&quot;
)paren
)paren
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
id|swab
op_assign
id|sb-&gt;u.ufs_sb.s_swab
suffix:semicolon
id|uspi
op_assign
id|sb-&gt;u.ufs_sb.s_uspi
suffix:semicolon
id|retry
op_assign
l_int|0
suffix:semicolon
id|tindirect_block
op_assign
(paren
id|DIRECT_BLOCK
OG
(paren
id|UFS_NDADDR
op_plus
id|uspi-&gt;s_apb
op_plus
id|uspi-&gt;s_2apb
)paren
)paren
ques
c_cond
(paren
(paren
id|DIRECT_BLOCK
op_minus
id|UFS_NDADDR
op_minus
id|uspi-&gt;s_apb
op_minus
id|uspi-&gt;s_2apb
)paren
op_rshift
id|uspi-&gt;s_2apbshift
)paren
suffix:colon
l_int|0
suffix:semicolon
id|p
op_assign
id|inode-&gt;u.ufs_i.i_u1.i_data
op_plus
id|UFS_TIND_BLOCK
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|tmp
op_assign
id|SWAB32
c_func
(paren
op_star
id|p
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|tind_bh
op_assign
id|ubh_bread
(paren
id|sb-&gt;s_dev
comma
id|tmp
comma
id|uspi-&gt;s_bsize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ne
id|SWAB32
c_func
(paren
op_star
id|p
)paren
)paren
(brace
id|ubh_brelse
(paren
id|tind_bh
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|tind_bh
)paren
(brace
op_star
id|p
op_assign
id|SWAB32
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
id|tindirect_block
suffix:semicolon
id|i
OL
id|uspi-&gt;s_apb
suffix:semicolon
id|i
op_increment
)paren
(brace
id|tind
op_assign
id|ubh_get_addr32
(paren
id|tind_bh
comma
id|i
)paren
suffix:semicolon
id|retry
op_or_assign
id|ufs_trunc_dindirect
c_func
(paren
id|inode
comma
id|UFS_NDADDR
op_plus
id|uspi-&gt;s_apb
op_plus
(paren
(paren
id|i
op_plus
l_int|1
)paren
op_lshift
id|uspi-&gt;s_2apbshift
)paren
comma
id|tind
)paren
suffix:semicolon
id|ubh_mark_buffer_dirty
c_func
(paren
id|tind_bh
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|uspi-&gt;s_apb
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|SWAB32
c_func
(paren
op_star
id|ubh_get_addr32
(paren
id|tind_bh
comma
id|i
)paren
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|uspi-&gt;s_apb
)paren
(brace
r_if
c_cond
(paren
id|ubh_max_bcount
c_func
(paren
id|tind_bh
)paren
op_ne
l_int|1
)paren
id|retry
op_assign
l_int|1
suffix:semicolon
r_else
(brace
id|tmp
op_assign
id|SWAB32
c_func
(paren
op_star
id|p
)paren
suffix:semicolon
op_star
id|p
op_assign
id|SWAB32
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|inode-&gt;i_blocks
op_sub_assign
id|uspi-&gt;s_nspb
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|ufs_free_blocks
(paren
id|inode
comma
id|tmp
comma
id|uspi-&gt;s_fpb
)paren
suffix:semicolon
id|ubh_bforget
c_func
(paren
id|tind_bh
)paren
suffix:semicolon
id|tind_bh
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|IS_SYNC
c_func
(paren
id|inode
)paren
op_logical_and
id|tind_bh
op_logical_and
id|ubh_buffer_dirty
c_func
(paren
id|tind_bh
)paren
)paren
(brace
id|ubh_ll_rw_block
(paren
id|WRITE
comma
l_int|1
comma
op_amp
id|tind_bh
)paren
suffix:semicolon
id|ubh_wait_on_buffer
(paren
id|tind_bh
)paren
suffix:semicolon
)brace
id|ubh_brelse
(paren
id|tind_bh
)paren
suffix:semicolon
id|UFSD
c_func
(paren
(paren
l_string|&quot;EXIT&bslash;n&quot;
)paren
)paren
r_return
id|retry
suffix:semicolon
)brace
DECL|function|ufs_truncate
r_void
id|ufs_truncate
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_struct
id|ufs_sb_private_info
op_star
id|uspi
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|offset
suffix:semicolon
r_int
id|err
comma
id|retry
suffix:semicolon
id|UFSD
c_func
(paren
(paren
l_string|&quot;ENTER&bslash;n&quot;
)paren
)paren
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
id|uspi
op_assign
id|sb-&gt;u.ufs_sb.s_uspi
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_or
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_or
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|IS_APPEND
c_func
(paren
id|inode
)paren
op_logical_or
id|IS_IMMUTABLE
c_func
(paren
id|inode
)paren
)paren
r_return
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|retry
op_assign
id|ufs_trunc_direct
c_func
(paren
id|inode
)paren
suffix:semicolon
id|retry
op_or_assign
id|ufs_trunc_indirect
(paren
id|inode
comma
id|UFS_IND_BLOCK
comma
(paren
id|u32
op_star
)paren
op_amp
id|inode-&gt;u.ufs_i.i_u1.i_data
(braket
id|UFS_IND_BLOCK
)braket
)paren
suffix:semicolon
id|retry
op_or_assign
id|ufs_trunc_dindirect
(paren
id|inode
comma
id|UFS_IND_BLOCK
op_plus
id|uspi-&gt;s_apb
comma
(paren
id|u32
op_star
)paren
op_amp
id|inode-&gt;u.ufs_i.i_u1.i_data
(braket
id|UFS_DIND_BLOCK
)braket
)paren
suffix:semicolon
id|retry
op_or_assign
id|ufs_trunc_tindirect
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retry
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|IS_SYNC
c_func
(paren
id|inode
)paren
op_logical_and
(paren
id|inode-&gt;i_state
op_amp
id|I_DIRTY
)paren
)paren
id|ufs_sync_inode
(paren
id|inode
)paren
suffix:semicolon
id|run_task_queue
c_func
(paren
op_amp
id|tq_disk
)paren
suffix:semicolon
id|current-&gt;policy
op_or_assign
id|SCHED_YIELD
suffix:semicolon
id|schedule
(paren
)paren
suffix:semicolon
)brace
id|offset
op_assign
id|inode-&gt;i_size
op_amp
id|uspi-&gt;s_fshift
suffix:semicolon
r_if
c_cond
(paren
id|offset
)paren
(brace
id|bh
op_assign
id|ufs_bread
(paren
id|inode
comma
id|inode-&gt;i_size
op_rshift
id|uspi-&gt;s_fshift
comma
l_int|0
comma
op_amp
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
(brace
id|memset
(paren
id|bh-&gt;b_data
op_plus
id|offset
comma
l_int|0
comma
id|uspi-&gt;s_fsize
op_minus
id|offset
)paren
suffix:semicolon
id|mark_buffer_dirty
(paren
id|bh
)paren
suffix:semicolon
id|brelse
(paren
id|bh
)paren
suffix:semicolon
)brace
)brace
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;u.ufs_i.i_lastfrag
op_assign
id|DIRECT_FRAGMENT
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|UFSD
c_func
(paren
(paren
l_string|&quot;EXIT&bslash;n&quot;
)paren
)paren
)brace
eof
