multiline_comment|/*&n; * Copyright 2000 by Hans Reiser, licensing governed by reiserfs/README&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/reiserfs_fs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
multiline_comment|/*&n;** reiserfs_ioctl - handler for ioctl for inode&n;** supported commands:&n;**  1) REISERFS_IOC_UNPACK - try to unpack tail from direct item into indirect&n;**                           and prevent packing file (argument arg has to be non-zero)&n;**  2) That&squot;s all for a while ...&n;*/
DECL|function|reiserfs_ioctl
r_int
id|reiserfs_ioctl
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
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
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|REISERFS_IOC_UNPACK
suffix:colon
r_if
c_cond
(paren
id|arg
)paren
r_return
id|reiserfs_unpack
(paren
id|inode
comma
id|filp
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENOTTY
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;** reiserfs_unpack&n;** Function try to convert tail from direct item into indirect.&n;** It set up nopack attribute in the inode.u.reiserfs_i.nopack&n;*/
DECL|function|reiserfs_unpack
r_int
id|reiserfs_unpack
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
id|index
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_int
r_int
id|write_from
suffix:semicolon
r_int
r_int
id|blocksize
op_assign
id|inode-&gt;i_sb-&gt;s_blocksize
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_size
op_eq
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* ioctl already done */
r_if
c_cond
(paren
id|REISERFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_flags
op_amp
id|i_nopack_mask
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* we need to make sure nobody is changing the file size beneath&n;    ** us&n;    */
id|down
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
id|write_from
op_assign
id|inode-&gt;i_size
op_amp
(paren
id|blocksize
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* if we are on a block boundary, we are already unpacked.  */
r_if
c_cond
(paren
id|write_from
op_eq
l_int|0
)paren
(brace
id|REISERFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_flags
op_or_assign
id|i_nopack_mask
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* we unpack by finding the page with the tail, and calling&n;    ** reiserfs_prepare_write on that page.  This will force a &n;    ** reiserfs_get_block to unpack the tail for us.&n;    */
id|index
op_assign
id|inode-&gt;i_size
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
id|page
op_assign
id|grab_cache_page
c_func
(paren
id|inode-&gt;i_mapping
comma
id|index
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
id|retval
op_assign
id|reiserfs_prepare_write
c_func
(paren
l_int|NULL
comma
id|page
comma
id|write_from
comma
id|blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|out_unlock
suffix:semicolon
multiline_comment|/* conversion can change page contents, must flush */
id|flush_dcache_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|REISERFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_flags
op_or_assign
id|i_nopack_mask
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
multiline_comment|/* mapped by prepare_write */
id|out_unlock
suffix:colon
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
eof
