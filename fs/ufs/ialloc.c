multiline_comment|/*&n; *  linux/fs/ufs/ialloc.c&n; *&n; * Copyright (c) 1998&n; * Daniel Pirkl &lt;daniel.pirkl@email.cz&gt;&n; * Charles University, Faculty of Mathematics and Physics&n; *&n; *  from&n; *&n; *  linux/fs/ext2/ialloc.c&n; *&n; * Copyright (C) 1992, 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  BSD ufs-inspired inode and directory allocation by &n; *  Stephen Tweedie (sct@dcs.ed.ac.uk), 1993&n; *  Big-endian to little-endian byte-swapping/bitmaps by&n; *        David S. Miller (davem@caip.rutgers.edu), 1995&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ufs_fs.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/quotaops.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &quot;swab.h&quot;
macro_line|#include &quot;util.h&quot;
DECL|macro|UFS_IALLOC_DEBUG
macro_line|#undef UFS_IALLOC_DEBUG
macro_line|#ifdef UFS_IALLOC_DEBUG
DECL|macro|UFSD
mdefine_line|#define UFSD(x) printk(&quot;(%s, %d), %s: &quot;, __FILE__, __LINE__, __FUNCTION__); printk x;
macro_line|#else
DECL|macro|UFSD
mdefine_line|#define UFSD(x)
macro_line|#endif
multiline_comment|/*&n; * NOTE! When we get the inode, we&squot;re the only people&n; * that have access to it, and as such there are no&n; * race conditions we have to worry about. The inode&n; * is not on the hash-lists, and it cannot be reached&n; * through the filesystem because the directory entry&n; * has been deleted earlier.&n; *&n; * HOWEVER: we must make sure that we get no aliases,&n; * which means that we have to call &quot;clear_inode()&quot;&n; * _before_ we mark the inode not in use in the inode&n; * bitmaps. Otherwise a newly created file might use&n; * the same inode number (not actually the same pointer&n; * though), and then we&squot;d have two inodes sharing the&n; * same inode number and space on the harddisk.&n; */
DECL|function|ufs_free_inode
r_void
id|ufs_free_inode
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
id|ufs_super_block_first
op_star
id|usb1
suffix:semicolon
r_struct
id|ufs_cg_private_info
op_star
id|ucpi
suffix:semicolon
r_struct
id|ufs_cylinder_group
op_star
id|ucg
suffix:semicolon
r_int
id|is_directory
suffix:semicolon
r_int
id|ino
comma
id|cg
comma
id|bit
suffix:semicolon
id|UFSD
c_func
(paren
(paren
l_string|&quot;ENTER, ino %lu&bslash;n&quot;
comma
id|inode-&gt;i_ino
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
id|usb1
op_assign
id|ubh_get_usb_first
c_func
(paren
id|USPI_UBH
)paren
suffix:semicolon
id|ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|lock_super
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|ino
OG
l_int|1
)paren
op_logical_and
(paren
id|ino
OL
(paren
id|uspi-&gt;s_ncg
op_star
id|uspi-&gt;s_ipg
)paren
)paren
)paren
)paren
(brace
id|ufs_warning
c_func
(paren
id|sb
comma
l_string|&quot;ufs_free_inode&quot;
comma
l_string|&quot;reserved inode or nonexistent inode %u&bslash;n&quot;
comma
id|ino
)paren
suffix:semicolon
id|unlock_super
(paren
id|sb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|cg
op_assign
id|ufs_inotocg
(paren
id|ino
)paren
suffix:semicolon
id|bit
op_assign
id|ufs_inotocgoff
(paren
id|ino
)paren
suffix:semicolon
id|ucpi
op_assign
id|ufs_load_cylinder
(paren
id|sb
comma
id|cg
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ucpi
)paren
(brace
id|unlock_super
(paren
id|sb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ucg
op_assign
id|ubh_get_ucg
c_func
(paren
id|UCPI_UBH
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ufs_cg_chkmagic
c_func
(paren
id|sb
comma
id|ucg
)paren
)paren
id|ufs_panic
(paren
id|sb
comma
l_string|&quot;ufs_free_fragments&quot;
comma
l_string|&quot;internal error, bad cg magic number&quot;
)paren
suffix:semicolon
id|ucg-&gt;cg_time
op_assign
id|cpu_to_fs32
c_func
(paren
id|sb
comma
id|CURRENT_TIME
)paren
suffix:semicolon
id|is_directory
op_assign
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
suffix:semicolon
id|DQUOT_FREE_INODE
c_func
(paren
id|inode
)paren
suffix:semicolon
id|DQUOT_DROP
c_func
(paren
id|inode
)paren
suffix:semicolon
id|clear_inode
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ubh_isclr
(paren
id|UCPI_UBH
comma
id|ucpi-&gt;c_iusedoff
comma
id|bit
)paren
)paren
id|ufs_error
c_func
(paren
id|sb
comma
l_string|&quot;ufs_free_inode&quot;
comma
l_string|&quot;bit already cleared for inode %u&quot;
comma
id|ino
)paren
suffix:semicolon
r_else
(brace
id|ubh_clrbit
(paren
id|UCPI_UBH
comma
id|ucpi-&gt;c_iusedoff
comma
id|bit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ino
OL
id|ucpi-&gt;c_irotor
)paren
id|ucpi-&gt;c_irotor
op_assign
id|ino
suffix:semicolon
id|fs32_add
c_func
(paren
id|sb
comma
op_amp
id|ucg-&gt;cg_cs.cs_nifree
comma
l_int|1
)paren
suffix:semicolon
id|fs32_add
c_func
(paren
id|sb
comma
op_amp
id|usb1-&gt;fs_cstotal.cs_nifree
comma
l_int|1
)paren
suffix:semicolon
id|fs32_add
c_func
(paren
id|sb
comma
op_amp
id|sb
op_member_access_from_pointer
id|fs_cs
c_func
(paren
id|cg
)paren
dot
id|cs_nifree
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_directory
)paren
(brace
id|fs32_sub
c_func
(paren
id|sb
comma
op_amp
id|ucg-&gt;cg_cs.cs_ndir
comma
l_int|1
)paren
suffix:semicolon
id|fs32_sub
c_func
(paren
id|sb
comma
op_amp
id|usb1-&gt;fs_cstotal.cs_ndir
comma
l_int|1
)paren
suffix:semicolon
id|fs32_sub
c_func
(paren
id|sb
comma
op_amp
id|sb
op_member_access_from_pointer
id|fs_cs
c_func
(paren
id|cg
)paren
dot
id|cs_ndir
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
id|ubh_mark_buffer_dirty
(paren
id|USPI_UBH
)paren
suffix:semicolon
id|ubh_mark_buffer_dirty
(paren
id|UCPI_UBH
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_flags
op_amp
id|MS_SYNCHRONOUS
)paren
(brace
id|ubh_ll_rw_block
(paren
id|WRITE
comma
l_int|1
comma
(paren
r_struct
id|ufs_buffer_head
op_star
op_star
)paren
op_amp
id|ucpi
)paren
suffix:semicolon
id|ubh_wait_on_buffer
(paren
id|UCPI_UBH
)paren
suffix:semicolon
)brace
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
id|unlock_super
(paren
id|sb
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
multiline_comment|/*&n; * There are two policies for allocating an inode.  If the new inode is&n; * a directory, then a forward search is made for a block group with both&n; * free space and a low directory-to-inode ratio; if that fails, then of&n; * the groups with above-average free space, that group with the fewest&n; * directories already is chosen.&n; *&n; * For other inodes, search forward from the parent directory&squot;s block&n; * group to find a free inode.&n; */
DECL|function|ufs_new_inode
r_struct
id|inode
op_star
id|ufs_new_inode
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_int
id|mode
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
id|ufs_super_block_first
op_star
id|usb1
suffix:semicolon
r_struct
id|ufs_cg_private_info
op_star
id|ucpi
suffix:semicolon
r_struct
id|ufs_cylinder_group
op_star
id|ucg
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|cg
comma
id|bit
comma
id|i
comma
id|j
comma
id|start
suffix:semicolon
r_struct
id|ufs_inode_info
op_star
id|ufsi
suffix:semicolon
id|UFSD
c_func
(paren
(paren
l_string|&quot;ENTER&bslash;n&quot;
)paren
)paren
multiline_comment|/* Cannot create files in a deleted directory */
r_if
c_cond
(paren
op_logical_neg
id|dir
op_logical_or
op_logical_neg
id|dir-&gt;i_nlink
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EPERM
)paren
suffix:semicolon
id|sb
op_assign
id|dir-&gt;i_sb
suffix:semicolon
id|inode
op_assign
id|new_inode
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|ufsi
op_assign
id|UFS_I
c_func
(paren
id|inode
)paren
suffix:semicolon
id|uspi
op_assign
id|sb-&gt;u.ufs_sb.s_uspi
suffix:semicolon
id|usb1
op_assign
id|ubh_get_usb_first
c_func
(paren
id|USPI_UBH
)paren
suffix:semicolon
id|lock_super
(paren
id|sb
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Try to place the inode in its parent directory&n;&t; */
id|i
op_assign
id|ufs_inotocg
c_func
(paren
id|dir-&gt;i_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb
op_member_access_from_pointer
id|fs_cs
c_func
(paren
id|i
)paren
dot
id|cs_nifree
)paren
(brace
id|cg
op_assign
id|i
suffix:semicolon
r_goto
id|cg_found
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Use a quadratic hash to find a group with a free inode&n;&t; */
r_for
c_loop
(paren
id|j
op_assign
l_int|1
suffix:semicolon
id|j
OL
id|uspi-&gt;s_ncg
suffix:semicolon
id|j
op_lshift_assign
l_int|1
)paren
(brace
id|i
op_add_assign
id|j
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|uspi-&gt;s_ncg
)paren
id|i
op_sub_assign
id|uspi-&gt;s_ncg
suffix:semicolon
r_if
c_cond
(paren
id|sb
op_member_access_from_pointer
id|fs_cs
c_func
(paren
id|i
)paren
dot
id|cs_nifree
)paren
(brace
id|cg
op_assign
id|i
suffix:semicolon
r_goto
id|cg_found
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * That failed: try linear search for a free inode&n;&t; */
id|i
op_assign
id|ufs_inotocg
c_func
(paren
id|dir-&gt;i_ino
)paren
op_plus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|2
suffix:semicolon
id|j
OL
id|uspi-&gt;s_ncg
suffix:semicolon
id|j
op_increment
)paren
(brace
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|uspi-&gt;s_ncg
)paren
id|i
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sb
op_member_access_from_pointer
id|fs_cs
c_func
(paren
id|i
)paren
dot
id|cs_nifree
)paren
(brace
id|cg
op_assign
id|i
suffix:semicolon
r_goto
id|cg_found
suffix:semicolon
)brace
)brace
r_goto
id|failed
suffix:semicolon
id|cg_found
suffix:colon
id|ucpi
op_assign
id|ufs_load_cylinder
(paren
id|sb
comma
id|cg
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ucpi
)paren
r_goto
id|failed
suffix:semicolon
id|ucg
op_assign
id|ubh_get_ucg
c_func
(paren
id|UCPI_UBH
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ufs_cg_chkmagic
c_func
(paren
id|sb
comma
id|ucg
)paren
)paren
id|ufs_panic
(paren
id|sb
comma
l_string|&quot;ufs_new_inode&quot;
comma
l_string|&quot;internal error, bad cg magic number&quot;
)paren
suffix:semicolon
id|start
op_assign
id|ucpi-&gt;c_irotor
suffix:semicolon
id|bit
op_assign
id|ubh_find_next_zero_bit
(paren
id|UCPI_UBH
comma
id|ucpi-&gt;c_iusedoff
comma
id|uspi-&gt;s_ipg
comma
id|start
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bit
OL
id|uspi-&gt;s_ipg
)paren
)paren
(brace
id|bit
op_assign
id|ubh_find_first_zero_bit
(paren
id|UCPI_UBH
comma
id|ucpi-&gt;c_iusedoff
comma
id|start
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bit
OL
id|start
)paren
)paren
(brace
id|ufs_error
(paren
id|sb
comma
l_string|&quot;ufs_new_inode&quot;
comma
l_string|&quot;cylinder group %u corrupted - error in inode bitmap&bslash;n&quot;
comma
id|cg
)paren
suffix:semicolon
r_goto
id|failed
suffix:semicolon
)brace
)brace
id|UFSD
c_func
(paren
(paren
l_string|&quot;start = %u, bit = %u, ipg = %u&bslash;n&quot;
comma
id|start
comma
id|bit
comma
id|uspi-&gt;s_ipg
)paren
)paren
r_if
c_cond
(paren
id|ubh_isclr
(paren
id|UCPI_UBH
comma
id|ucpi-&gt;c_iusedoff
comma
id|bit
)paren
)paren
id|ubh_setbit
(paren
id|UCPI_UBH
comma
id|ucpi-&gt;c_iusedoff
comma
id|bit
)paren
suffix:semicolon
r_else
(brace
id|ufs_panic
(paren
id|sb
comma
l_string|&quot;ufs_new_inode&quot;
comma
l_string|&quot;internal error&quot;
)paren
suffix:semicolon
r_goto
id|failed
suffix:semicolon
)brace
id|fs32_sub
c_func
(paren
id|sb
comma
op_amp
id|ucg-&gt;cg_cs.cs_nifree
comma
l_int|1
)paren
suffix:semicolon
id|fs32_sub
c_func
(paren
id|sb
comma
op_amp
id|usb1-&gt;fs_cstotal.cs_nifree
comma
l_int|1
)paren
suffix:semicolon
id|fs32_sub
c_func
(paren
id|sb
comma
op_amp
id|sb
op_member_access_from_pointer
id|fs_cs
c_func
(paren
id|cg
)paren
dot
id|cs_nifree
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
(brace
id|fs32_add
c_func
(paren
id|sb
comma
op_amp
id|ucg-&gt;cg_cs.cs_ndir
comma
l_int|1
)paren
suffix:semicolon
id|fs32_add
c_func
(paren
id|sb
comma
op_amp
id|usb1-&gt;fs_cstotal.cs_ndir
comma
l_int|1
)paren
suffix:semicolon
id|fs32_add
c_func
(paren
id|sb
comma
op_amp
id|sb
op_member_access_from_pointer
id|fs_cs
c_func
(paren
id|cg
)paren
dot
id|cs_ndir
comma
l_int|1
)paren
suffix:semicolon
)brace
id|ubh_mark_buffer_dirty
(paren
id|USPI_UBH
)paren
suffix:semicolon
id|ubh_mark_buffer_dirty
(paren
id|UCPI_UBH
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_flags
op_amp
id|MS_SYNCHRONOUS
)paren
(brace
id|ubh_ll_rw_block
(paren
id|WRITE
comma
l_int|1
comma
(paren
r_struct
id|ufs_buffer_head
op_star
op_star
)paren
op_amp
id|ucpi
)paren
suffix:semicolon
id|ubh_wait_on_buffer
(paren
id|UCPI_UBH
)paren
suffix:semicolon
)brace
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|mode
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|current-&gt;fsuid
suffix:semicolon
r_if
c_cond
(paren
id|dir-&gt;i_mode
op_amp
id|S_ISGID
)paren
(brace
id|inode-&gt;i_gid
op_assign
id|dir-&gt;i_gid
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
id|inode-&gt;i_mode
op_or_assign
id|S_ISGID
suffix:semicolon
)brace
r_else
id|inode-&gt;i_gid
op_assign
id|current-&gt;fsgid
suffix:semicolon
id|inode-&gt;i_ino
op_assign
id|cg
op_star
id|uspi-&gt;s_ipg
op_plus
id|bit
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
id|PAGE_SIZE
suffix:semicolon
multiline_comment|/* This is the optimal IO size (for stat), not the fs block size */
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|ufsi-&gt;i_flags
op_assign
id|UFS_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|i_flags
suffix:semicolon
id|ufsi-&gt;i_lastfrag
op_assign
l_int|0
suffix:semicolon
id|ufsi-&gt;i_gen
op_assign
l_int|0
suffix:semicolon
id|ufsi-&gt;i_shadow
op_assign
l_int|0
suffix:semicolon
id|ufsi-&gt;i_osync
op_assign
l_int|0
suffix:semicolon
id|ufsi-&gt;i_oeftflag
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|ufsi-&gt;i_u1
comma
l_int|0
comma
r_sizeof
(paren
id|ufsi-&gt;i_u1
)paren
)paren
suffix:semicolon
id|insert_inode_hash
c_func
(paren
id|inode
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|unlock_super
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|DQUOT_ALLOC_INODE
c_func
(paren
id|inode
)paren
)paren
(brace
id|DQUOT_DROP
c_func
(paren
id|inode
)paren
suffix:semicolon
id|inode-&gt;i_flags
op_or_assign
id|S_NOQUOTA
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EDQUOT
)paren
suffix:semicolon
)brace
id|UFSD
c_func
(paren
(paren
l_string|&quot;allocating inode %lu&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
)paren
id|UFSD
c_func
(paren
(paren
l_string|&quot;EXIT&bslash;n&quot;
)paren
)paren
r_return
id|inode
suffix:semicolon
id|failed
suffix:colon
id|unlock_super
(paren
id|sb
)paren
suffix:semicolon
id|make_bad_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
(paren
id|inode
)paren
suffix:semicolon
id|UFSD
c_func
(paren
(paren
l_string|&quot;EXIT (FAILED)&bslash;n&quot;
)paren
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOSPC
)paren
suffix:semicolon
)brace
eof
