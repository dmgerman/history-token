multiline_comment|/* &n; * QNX4 file system, Linux implementation.&n; * &n; * Version : 0.1&n; * &n; * Using parts of the xiafs filesystem.&n; * &n; * History :&n; * &n; * 24-03-1998 by Richard Frowijn : first release.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/qnx4_fs.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * The functions for qnx4 fs file synchronization.&n; */
macro_line|#ifdef CONFIG_QNX4FS_RW
DECL|function|sync_block
r_static
r_int
id|sync_block
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
op_star
id|block
comma
r_int
id|wait
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|block
)paren
r_return
l_int|0
suffix:semicolon
id|tmp
op_assign
op_star
id|block
suffix:semicolon
id|bh
op_assign
id|sb_get_hash_table
c_func
(paren
id|inode-&gt;i_sb
comma
op_star
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|block
op_ne
id|tmp
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|wait
op_logical_and
id|buffer_req
c_func
(paren
id|bh
)paren
op_logical_and
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|wait
op_logical_or
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bh
)paren
op_logical_or
op_logical_neg
id|buffer_dirty
c_func
(paren
id|bh
)paren
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|ll_rw_block
c_func
(paren
id|WRITE
comma
l_int|1
comma
op_amp
id|bh
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|bh-&gt;b_count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef WTF
DECL|function|sync_iblock
r_static
r_int
id|sync_iblock
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
op_star
id|iblock
comma
r_struct
id|buffer_head
op_star
op_star
id|bh
comma
r_int
id|wait
)paren
(brace
r_int
id|rc
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|tmp
op_assign
op_star
id|iblock
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
id|rc
op_assign
id|sync_block
c_func
(paren
id|inode
comma
id|iblock
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
op_star
id|bh
op_assign
id|sb_bread
c_func
(paren
id|inode-&gt;i_sb
comma
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ne
op_star
id|iblock
)paren
(brace
id|brelse
c_func
(paren
op_star
id|bh
)paren
suffix:semicolon
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|bh
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|function|sync_direct
r_static
r_int
id|sync_direct
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|wait
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|rc
comma
id|err
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
l_int|7
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rc
op_assign
id|sync_block
c_func
(paren
id|inode
comma
(paren
r_int
r_int
op_star
)paren
id|qnx4_raw_inode
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|di_first_xtnt.xtnt_blk
op_plus
id|i
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OG
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
id|err
op_assign
id|rc
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
macro_line|#ifdef WTF
DECL|function|sync_indirect
r_static
r_int
id|sync_indirect
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
op_star
id|iblock
comma
r_int
id|wait
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|buffer_head
op_star
id|ind_bh
suffix:semicolon
r_int
id|rc
comma
id|err
op_assign
l_int|0
suffix:semicolon
id|rc
op_assign
id|sync_iblock
c_func
(paren
id|inode
comma
id|iblock
comma
op_amp
id|ind_bh
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_logical_or
op_logical_neg
id|ind_bh
)paren
r_return
id|rc
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
l_int|512
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rc
op_assign
id|sync_block
c_func
(paren
id|inode
comma
(paren
(paren
r_int
r_int
op_star
)paren
id|ind_bh-&gt;b_data
)paren
op_plus
id|i
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OG
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
id|err
op_assign
id|rc
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|ind_bh
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|sync_dindirect
r_static
r_int
id|sync_dindirect
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
op_star
id|diblock
comma
r_int
id|wait
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|buffer_head
op_star
id|dind_bh
suffix:semicolon
r_int
id|rc
comma
id|err
op_assign
l_int|0
suffix:semicolon
id|rc
op_assign
id|sync_iblock
c_func
(paren
id|inode
comma
id|diblock
comma
op_amp
id|dind_bh
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_logical_or
op_logical_neg
id|dind_bh
)paren
r_return
id|rc
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
l_int|512
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rc
op_assign
id|sync_indirect
c_func
(paren
id|inode
comma
(paren
(paren
r_int
r_int
op_star
)paren
id|dind_bh-&gt;b_data
)paren
op_plus
id|i
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OG
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
id|err
op_assign
id|rc
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|dind_bh
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
macro_line|#endif
DECL|function|qnx4_sync_file
r_int
id|qnx4_sync_file
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|unused
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_int
id|wait
comma
id|err
op_assign
l_int|0
suffix:semicolon
(paren
r_void
)paren
id|file
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
op_minus
id|EINVAL
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|wait
op_assign
l_int|0
suffix:semicolon
id|wait
op_le
l_int|1
suffix:semicolon
id|wait
op_increment
)paren
(brace
id|err
op_or_assign
id|sync_direct
c_func
(paren
id|inode
comma
id|wait
)paren
suffix:semicolon
)brace
id|err
op_or_assign
id|qnx4_sync_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
id|err
OL
l_int|0
)paren
ques
c_cond
op_minus
id|EIO
suffix:colon
l_int|0
suffix:semicolon
)brace
macro_line|#endif
eof
