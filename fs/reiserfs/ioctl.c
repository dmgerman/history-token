multiline_comment|/*&n; * Copyright 2000 by Hans Reiser, licensing governed by reiserfs/README&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/reiserfs_fs.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
r_static
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
suffix:semicolon
multiline_comment|/*&n;** reiserfs_ioctl - handler for ioctl for inode&n;** supported commands:&n;**  1) REISERFS_IOC_UNPACK - try to unpack tail from direct item into indirect&n;**                           and prevent packing file (argument arg has to be non-zero)&n;**  2) REISERFS_IOC_[GS]ETFLAGS, REISERFS_IOC_[GS]ETVERSION&n;**  3) That&squot;s all for a while ...&n;*/
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
r_int
r_int
id|flags
suffix:semicolon
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
id|S_ISREG
c_func
(paren
id|inode
op_member_access_from_pointer
id|i_mode
)paren
)paren
(brace
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
r_else
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_return
op_minus
id|ENOTTY
suffix:semicolon
multiline_comment|/* following two cases are taken from fs/ext2/ioctl.c by Remy&n;&t;   Card (card@masi.ibp.fr) */
r_case
id|REISERFS_IOC_GETFLAGS
suffix:colon
id|flags
op_assign
id|REISERFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_attrs
suffix:semicolon
id|i_attrs_to_sd_attrs
c_func
(paren
id|inode
comma
(paren
id|__u16
op_star
)paren
op_amp
id|flags
)paren
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|flags
comma
(paren
r_int
id|__user
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|REISERFS_IOC_SETFLAGS
suffix:colon
(brace
r_if
c_cond
(paren
id|IS_RDONLY
c_func
(paren
id|inode
)paren
)paren
r_return
op_minus
id|EROFS
suffix:semicolon
r_if
c_cond
(paren
(paren
id|current-&gt;fsuid
op_ne
id|inode-&gt;i_uid
)paren
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_FOWNER
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|flags
comma
(paren
r_int
id|__user
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|flags
op_xor
id|REISERFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_attrs
)paren
op_amp
(paren
id|REISERFS_IMMUTABLE_FL
op_or
id|REISERFS_APPEND_FL
)paren
)paren
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_LINUX_IMMUTABLE
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|REISERFS_NOTAIL_FL
)paren
op_logical_and
id|S_ISREG
c_func
(paren
id|inode
op_member_access_from_pointer
id|i_mode
)paren
)paren
(brace
r_int
id|result
suffix:semicolon
id|result
op_assign
id|reiserfs_unpack
c_func
(paren
id|inode
comma
id|filp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
r_return
id|result
suffix:semicolon
)brace
)brace
id|sd_attrs_to_i_attrs
c_func
(paren
id|flags
comma
id|inode
)paren
suffix:semicolon
id|REISERFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_attrs
op_assign
id|flags
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME_SEC
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|REISERFS_IOC_GETVERSION
suffix:colon
r_return
id|put_user
c_func
(paren
id|inode-&gt;i_generation
comma
(paren
r_int
id|__user
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|REISERFS_IOC_SETVERSION
suffix:colon
r_if
c_cond
(paren
(paren
id|current-&gt;fsuid
op_ne
id|inode-&gt;i_uid
)paren
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_FOWNER
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|IS_RDONLY
c_func
(paren
id|inode
)paren
)paren
r_return
op_minus
id|EROFS
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|inode-&gt;i_generation
comma
(paren
r_int
id|__user
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME_SEC
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENOTTY
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;** reiserfs_unpack&n;** Function try to convert tail from direct item into indirect.&n;** It set up nopack attribute in the REISERFS_I(inode)-&gt;nopack&n;*/
DECL|function|reiserfs_unpack
r_static
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
r_struct
id|address_space
op_star
id|mapping
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
r_return
l_int|0
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
id|reiserfs_write_lock
c_func
(paren
id|inode-&gt;i_sb
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
id|mapping
op_assign
id|inode-&gt;i_mapping
suffix:semicolon
id|page
op_assign
id|grab_cache_page
c_func
(paren
id|mapping
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
id|mapping-&gt;a_ops
op_member_access_from_pointer
id|prepare_write
c_func
(paren
l_int|NULL
comma
id|page
comma
id|write_from
comma
id|write_from
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
id|retval
op_assign
id|mapping-&gt;a_ops
op_member_access_from_pointer
id|commit_write
c_func
(paren
l_int|NULL
comma
id|page
comma
id|write_from
comma
id|write_from
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
id|out_unlock
suffix:colon
id|unlock_page
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
id|reiserfs_write_unlock
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
eof
