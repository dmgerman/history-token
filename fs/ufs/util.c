multiline_comment|/*&n; *  linux/fs/ufs/util.c&n; *&n; * Copyright (C) 1998&n; * Daniel Pirkl &lt;daniel.pirkl@email.cz&gt;&n; * Charles University, Faculty of Mathematics and Physics&n; */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/ufs_fs.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &quot;swab.h&quot;
macro_line|#include &quot;util.h&quot;
DECL|macro|UFS_UTILS_DEBUG
macro_line|#undef UFS_UTILS_DEBUG
macro_line|#ifdef UFS_UTILS_DEBUG
DECL|macro|UFSD
mdefine_line|#define UFSD(x) printk(&quot;(%s, %d), %s: &quot;, __FILE__, __LINE__, __FUNCTION__); printk x;
macro_line|#else
DECL|macro|UFSD
mdefine_line|#define UFSD(x)
macro_line|#endif
DECL|function|_ubh_bread_
r_struct
id|ufs_buffer_head
op_star
id|_ubh_bread_
(paren
r_struct
id|ufs_sb_private_info
op_star
id|uspi
comma
r_struct
id|super_block
op_star
id|sb
comma
id|u64
id|fragment
comma
id|u64
id|size
)paren
(brace
r_struct
id|ufs_buffer_head
op_star
id|ubh
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
id|u64
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|size
op_amp
op_complement
id|uspi-&gt;s_fmask
)paren
r_return
l_int|NULL
suffix:semicolon
id|count
op_assign
id|size
op_rshift
id|uspi-&gt;s_fshift
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|UFS_MAXFRAG
)paren
r_return
l_int|NULL
suffix:semicolon
id|ubh
op_assign
(paren
r_struct
id|ufs_buffer_head
op_star
)paren
id|kmalloc
(paren
r_sizeof
(paren
r_struct
id|ufs_buffer_head
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ubh
)paren
r_return
l_int|NULL
suffix:semicolon
id|ubh-&gt;fragment
op_assign
id|fragment
suffix:semicolon
id|ubh-&gt;count
op_assign
id|count
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
id|count
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|ubh-&gt;bh
(braket
id|i
)braket
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
id|fragment
op_plus
id|i
)paren
)paren
)paren
r_goto
id|failed
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
id|UFS_MAXFRAG
suffix:semicolon
id|i
op_increment
)paren
id|ubh-&gt;bh
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
id|ubh
suffix:semicolon
id|failed
suffix:colon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|i
suffix:semicolon
id|j
op_increment
)paren
id|brelse
(paren
id|ubh-&gt;bh
(braket
id|j
)braket
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ubh
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|ubh_bread_uspi
r_struct
id|ufs_buffer_head
op_star
id|ubh_bread_uspi
(paren
r_struct
id|ufs_sb_private_info
op_star
id|uspi
comma
r_struct
id|super_block
op_star
id|sb
comma
id|u64
id|fragment
comma
id|u64
id|size
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
id|u64
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|size
op_amp
op_complement
id|uspi-&gt;s_fmask
)paren
r_return
l_int|NULL
suffix:semicolon
id|count
op_assign
id|size
op_rshift
id|uspi-&gt;s_fshift
suffix:semicolon
r_if
c_cond
(paren
id|count
op_le
l_int|0
op_logical_or
id|count
OG
id|UFS_MAXFRAG
)paren
r_return
l_int|NULL
suffix:semicolon
id|USPI_UBH-&gt;fragment
op_assign
id|fragment
suffix:semicolon
id|USPI_UBH-&gt;count
op_assign
id|count
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
id|count
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|USPI_UBH-&gt;bh
(braket
id|i
)braket
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
id|fragment
op_plus
id|i
)paren
)paren
)paren
r_goto
id|failed
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
id|UFS_MAXFRAG
suffix:semicolon
id|i
op_increment
)paren
id|USPI_UBH-&gt;bh
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
id|USPI_UBH
suffix:semicolon
id|failed
suffix:colon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|i
suffix:semicolon
id|j
op_increment
)paren
id|brelse
(paren
id|USPI_UBH-&gt;bh
(braket
id|j
)braket
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|ubh_brelse
r_void
id|ubh_brelse
(paren
r_struct
id|ufs_buffer_head
op_star
id|ubh
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ubh
)paren
r_return
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
id|ubh-&gt;count
suffix:semicolon
id|i
op_increment
)paren
id|brelse
(paren
id|ubh-&gt;bh
(braket
id|i
)braket
)paren
suffix:semicolon
id|kfree
(paren
id|ubh
)paren
suffix:semicolon
)brace
DECL|function|ubh_brelse_uspi
r_void
id|ubh_brelse_uspi
(paren
r_struct
id|ufs_sb_private_info
op_star
id|uspi
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|USPI_UBH
)paren
r_return
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
id|USPI_UBH-&gt;count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|brelse
(paren
id|USPI_UBH-&gt;bh
(braket
id|i
)braket
)paren
suffix:semicolon
id|USPI_UBH-&gt;bh
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|function|ubh_mark_buffer_dirty
r_void
id|ubh_mark_buffer_dirty
(paren
r_struct
id|ufs_buffer_head
op_star
id|ubh
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ubh
)paren
r_return
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
id|ubh-&gt;count
suffix:semicolon
id|i
op_increment
)paren
id|mark_buffer_dirty
(paren
id|ubh-&gt;bh
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
DECL|function|ubh_mark_buffer_uptodate
r_void
id|ubh_mark_buffer_uptodate
(paren
r_struct
id|ufs_buffer_head
op_star
id|ubh
comma
r_int
id|flag
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ubh
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|flag
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ubh-&gt;count
suffix:semicolon
id|i
op_increment
)paren
id|set_buffer_uptodate
(paren
id|ubh-&gt;bh
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ubh-&gt;count
suffix:semicolon
id|i
op_increment
)paren
id|clear_buffer_uptodate
(paren
id|ubh-&gt;bh
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
DECL|function|ubh_ll_rw_block
r_void
id|ubh_ll_rw_block
(paren
r_int
id|rw
comma
r_int
id|nr
comma
r_struct
id|ufs_buffer_head
op_star
id|ubh
(braket
)braket
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ubh
)paren
r_return
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
id|nr
suffix:semicolon
id|i
op_increment
)paren
id|ll_rw_block
(paren
id|rw
comma
id|ubh
(braket
id|i
)braket
op_member_access_from_pointer
id|count
comma
id|ubh
(braket
id|i
)braket
op_member_access_from_pointer
id|bh
)paren
suffix:semicolon
)brace
DECL|function|ubh_wait_on_buffer
r_void
id|ubh_wait_on_buffer
(paren
r_struct
id|ufs_buffer_head
op_star
id|ubh
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ubh
)paren
r_return
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
id|ubh-&gt;count
suffix:semicolon
id|i
op_increment
)paren
id|wait_on_buffer
(paren
id|ubh-&gt;bh
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
DECL|function|ubh_max_bcount
r_int
id|ubh_max_bcount
(paren
r_struct
id|ufs_buffer_head
op_star
id|ubh
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|max
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ubh
)paren
r_return
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
id|ubh-&gt;count
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|ubh-&gt;bh
(braket
id|i
)braket
op_member_access_from_pointer
id|b_count
)paren
OG
id|max
)paren
id|max
op_assign
id|atomic_read
c_func
(paren
op_amp
id|ubh-&gt;bh
(braket
id|i
)braket
op_member_access_from_pointer
id|b_count
)paren
suffix:semicolon
r_return
id|max
suffix:semicolon
)brace
DECL|function|ubh_bforget
r_void
id|ubh_bforget
(paren
r_struct
id|ufs_buffer_head
op_star
id|ubh
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ubh
)paren
r_return
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
id|ubh-&gt;count
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|ubh-&gt;bh
(braket
id|i
)braket
)paren
id|bforget
(paren
id|ubh-&gt;bh
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
DECL|function|ubh_buffer_dirty
r_int
id|ubh_buffer_dirty
(paren
r_struct
id|ufs_buffer_head
op_star
id|ubh
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ubh
)paren
r_return
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
id|ubh-&gt;count
suffix:semicolon
id|i
op_increment
)paren
id|result
op_or_assign
id|buffer_dirty
c_func
(paren
id|ubh-&gt;bh
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|_ubh_ubhcpymem_
r_void
id|_ubh_ubhcpymem_
c_func
(paren
r_struct
id|ufs_sb_private_info
op_star
id|uspi
comma
r_int
r_char
op_star
id|mem
comma
r_struct
id|ufs_buffer_head
op_star
id|ubh
comma
r_int
id|size
)paren
(brace
r_int
id|len
comma
id|bhno
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
(paren
id|ubh-&gt;count
op_lshift
id|uspi-&gt;s_fshift
)paren
)paren
id|size
op_assign
id|ubh-&gt;count
op_lshift
id|uspi-&gt;s_fshift
suffix:semicolon
id|bhno
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|size
)paren
(brace
id|len
op_assign
id|min_t
c_func
(paren
r_int
r_int
comma
id|size
comma
id|uspi-&gt;s_fsize
)paren
suffix:semicolon
id|memcpy
(paren
id|mem
comma
id|ubh-&gt;bh
(braket
id|bhno
)braket
op_member_access_from_pointer
id|b_data
comma
id|len
)paren
suffix:semicolon
id|mem
op_add_assign
id|uspi-&gt;s_fsize
suffix:semicolon
id|size
op_sub_assign
id|len
suffix:semicolon
id|bhno
op_increment
suffix:semicolon
)brace
)brace
DECL|function|_ubh_memcpyubh_
r_void
id|_ubh_memcpyubh_
c_func
(paren
r_struct
id|ufs_sb_private_info
op_star
id|uspi
comma
r_struct
id|ufs_buffer_head
op_star
id|ubh
comma
r_int
r_char
op_star
id|mem
comma
r_int
id|size
)paren
(brace
r_int
id|len
comma
id|bhno
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
(paren
id|ubh-&gt;count
op_lshift
id|uspi-&gt;s_fshift
)paren
)paren
id|size
op_assign
id|ubh-&gt;count
op_lshift
id|uspi-&gt;s_fshift
suffix:semicolon
id|bhno
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|size
)paren
(brace
id|len
op_assign
id|min_t
c_func
(paren
r_int
r_int
comma
id|size
comma
id|uspi-&gt;s_fsize
)paren
suffix:semicolon
id|memcpy
(paren
id|ubh-&gt;bh
(braket
id|bhno
)braket
op_member_access_from_pointer
id|b_data
comma
id|mem
comma
id|len
)paren
suffix:semicolon
id|mem
op_add_assign
id|uspi-&gt;s_fsize
suffix:semicolon
id|size
op_sub_assign
id|len
suffix:semicolon
id|bhno
op_increment
suffix:semicolon
)brace
)brace
id|dev_t
DECL|function|ufs_get_inode_dev
id|ufs_get_inode_dev
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ufs_inode_info
op_star
id|ufsi
)paren
(brace
id|__fs32
id|fs32
suffix:semicolon
id|dev_t
id|dev
suffix:semicolon
r_if
c_cond
(paren
(paren
id|UFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_flags
op_amp
id|UFS_ST_MASK
)paren
op_eq
id|UFS_ST_SUNx86
)paren
id|fs32
op_assign
id|ufsi-&gt;i_u1.i_data
(braket
l_int|1
)braket
suffix:semicolon
r_else
id|fs32
op_assign
id|ufsi-&gt;i_u1.i_data
(braket
l_int|0
)braket
suffix:semicolon
id|fs32
op_assign
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|fs32
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|UFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_flags
op_amp
id|UFS_ST_MASK
)paren
(brace
r_case
id|UFS_ST_SUNx86
suffix:colon
r_case
id|UFS_ST_SUN
suffix:colon
r_if
c_cond
(paren
(paren
id|fs32
op_amp
l_int|0xffff0000
)paren
op_eq
l_int|0
op_logical_or
(paren
id|fs32
op_amp
l_int|0xffff0000
)paren
op_eq
l_int|0xffff0000
)paren
id|dev
op_assign
id|old_decode_dev
c_func
(paren
id|fs32
op_amp
l_int|0x7fff
)paren
suffix:semicolon
r_else
id|dev
op_assign
id|MKDEV
c_func
(paren
id|sysv_major
c_func
(paren
id|fs32
)paren
comma
id|sysv_minor
c_func
(paren
id|fs32
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|dev
op_assign
id|old_decode_dev
c_func
(paren
id|fs32
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|dev
suffix:semicolon
)brace
r_void
DECL|function|ufs_set_inode_dev
id|ufs_set_inode_dev
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ufs_inode_info
op_star
id|ufsi
comma
id|dev_t
id|dev
)paren
(brace
id|__fs32
id|fs32
suffix:semicolon
r_switch
c_cond
(paren
id|UFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_flags
op_amp
id|UFS_ST_MASK
)paren
(brace
r_case
id|UFS_ST_SUNx86
suffix:colon
r_case
id|UFS_ST_SUN
suffix:colon
id|fs32
op_assign
id|sysv_encode_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|fs32
op_amp
l_int|0xffff8000
)paren
op_eq
l_int|0
)paren
(brace
id|fs32
op_assign
id|old_encode_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|fs32
op_assign
id|old_encode_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|fs32
op_assign
id|cpu_to_fs32
c_func
(paren
id|sb
comma
id|fs32
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|UFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_flags
op_amp
id|UFS_ST_MASK
)paren
op_eq
id|UFS_ST_SUNx86
)paren
id|ufsi-&gt;i_u1.i_data
(braket
l_int|1
)braket
op_assign
id|fs32
suffix:semicolon
r_else
id|ufsi-&gt;i_u1.i_data
(braket
l_int|0
)braket
op_assign
id|fs32
suffix:semicolon
)brace
eof
