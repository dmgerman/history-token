multiline_comment|/* cnode related routines for the coda kernel code&n;   (C) 1996 Peter Braam&n;   */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/coda.h&gt;
macro_line|#include &lt;linux/coda_linux.h&gt;
macro_line|#include &lt;linux/coda_fs_i.h&gt;
macro_line|#include &lt;linux/coda_psdev.h&gt;
DECL|function|coda_fideq
r_inline
r_int
id|coda_fideq
c_func
(paren
id|ViceFid
op_star
id|fid1
comma
id|ViceFid
op_star
id|fid2
)paren
(brace
r_return
id|memcmp
c_func
(paren
id|fid1
comma
id|fid2
comma
r_sizeof
(paren
op_star
id|fid1
)paren
)paren
op_eq
l_int|0
suffix:semicolon
)brace
DECL|variable|coda_symlink_inode_operations
r_static
r_struct
id|inode_operations
id|coda_symlink_inode_operations
op_assign
(brace
dot
id|readlink
op_assign
id|page_readlink
comma
dot
id|follow_link
op_assign
id|page_follow_link
comma
dot
id|setattr
op_assign
id|coda_setattr
comma
)brace
suffix:semicolon
multiline_comment|/* cnode.c */
DECL|function|coda_fill_inode
r_static
r_void
id|coda_fill_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|coda_vattr
op_star
id|attr
)paren
(brace
id|coda_vattr_to_iattr
c_func
(paren
id|inode
comma
id|attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|coda_file_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|coda_file_operations
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|coda_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|coda_dir_operations
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|coda_symlink_inode_operations
suffix:semicolon
id|inode-&gt;i_data.a_ops
op_assign
op_amp
id|coda_symlink_aops
suffix:semicolon
id|inode-&gt;i_mapping
op_assign
op_amp
id|inode-&gt;i_data
suffix:semicolon
)brace
r_else
id|init_special_inode
c_func
(paren
id|inode
comma
id|inode-&gt;i_mode
comma
id|attr-&gt;va_rdev
)paren
suffix:semicolon
)brace
DECL|function|coda_test_inode
r_static
r_int
id|coda_test_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_void
op_star
id|data
)paren
(brace
id|ViceFid
op_star
id|fid
op_assign
(paren
id|ViceFid
op_star
)paren
id|data
suffix:semicolon
r_return
id|coda_fideq
c_func
(paren
op_amp
(paren
id|ITOC
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|c_fid
)paren
comma
id|fid
)paren
suffix:semicolon
)brace
DECL|function|coda_set_inode
r_static
r_int
id|coda_set_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_void
op_star
id|data
)paren
(brace
id|ViceFid
op_star
id|fid
op_assign
(paren
id|ViceFid
op_star
)paren
id|data
suffix:semicolon
id|ITOC
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|c_fid
op_assign
op_star
id|fid
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|coda_fail_inode
r_static
r_int
id|coda_fail_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_void
op_star
id|data
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|coda_iget
r_struct
id|inode
op_star
id|coda_iget
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|ViceFid
op_star
id|fid
comma
r_struct
id|coda_vattr
op_star
id|attr
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|coda_inode_info
op_star
id|cii
suffix:semicolon
r_struct
id|coda_sb_info
op_star
id|sbi
op_assign
id|coda_sbp
c_func
(paren
id|sb
)paren
suffix:semicolon
r_int
r_int
id|hash
op_assign
id|coda_f2i
c_func
(paren
id|fid
)paren
suffix:semicolon
id|inode
op_assign
id|iget5_locked
c_func
(paren
id|sb
comma
id|hash
comma
id|coda_test_inode
comma
id|coda_set_inode
comma
id|fid
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
r_if
c_cond
(paren
id|inode-&gt;i_state
op_amp
id|I_NEW
)paren
(brace
id|cii
op_assign
id|ITOC
c_func
(paren
id|inode
)paren
suffix:semicolon
multiline_comment|/* we still need to set i_ino for things like stat(2) */
id|inode-&gt;i_ino
op_assign
id|hash
suffix:semicolon
id|cii-&gt;c_mapcount
op_assign
l_int|0
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|cii-&gt;c_cilist
comma
op_amp
id|sbi-&gt;sbi_cihead
)paren
suffix:semicolon
id|unlock_new_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
multiline_comment|/* always replace the attributes, type might have changed */
id|coda_fill_inode
c_func
(paren
id|inode
comma
id|attr
)paren
suffix:semicolon
r_return
id|inode
suffix:semicolon
)brace
multiline_comment|/* this is effectively coda_iget:&n;   - get attributes (might be cached)&n;   - get the inode for the fid using vfs iget&n;   - link the two up if this is needed&n;   - fill in the attributes&n;*/
DECL|function|coda_cnode_make
r_int
id|coda_cnode_make
c_func
(paren
r_struct
id|inode
op_star
op_star
id|inode
comma
id|ViceFid
op_star
id|fid
comma
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|coda_vattr
id|attr
suffix:semicolon
r_int
id|error
suffix:semicolon
multiline_comment|/* We get inode numbers from Venus -- see venus source */
id|error
op_assign
id|venus_getattr
c_func
(paren
id|sb
comma
id|fid
comma
op_amp
id|attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
op_star
id|inode
op_assign
l_int|NULL
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
op_star
id|inode
op_assign
id|coda_iget
c_func
(paren
id|sb
comma
id|fid
comma
op_amp
id|attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
op_star
id|inode
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;coda_cnode_make: coda_iget failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|PTR_ERR
c_func
(paren
op_star
id|inode
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|coda_replace_fid
r_void
id|coda_replace_fid
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|ViceFid
op_star
id|oldfid
comma
r_struct
id|ViceFid
op_star
id|newfid
)paren
(brace
r_struct
id|coda_inode_info
op_star
id|cii
suffix:semicolon
r_int
r_int
id|hash
op_assign
id|coda_f2i
c_func
(paren
id|newfid
)paren
suffix:semicolon
id|cii
op_assign
id|ITOC
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|coda_fideq
c_func
(paren
op_amp
id|cii-&gt;c_fid
comma
id|oldfid
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* replace fid and rehash inode */
multiline_comment|/* XXX we probably need to hold some lock here! */
id|remove_inode_hash
c_func
(paren
id|inode
)paren
suffix:semicolon
id|cii-&gt;c_fid
op_assign
op_star
id|newfid
suffix:semicolon
id|inode-&gt;i_ino
op_assign
id|hash
suffix:semicolon
id|__insert_inode_hash
c_func
(paren
id|inode
comma
id|hash
)paren
suffix:semicolon
)brace
multiline_comment|/* convert a fid to an inode. */
DECL|function|coda_fid_to_inode
r_struct
id|inode
op_star
id|coda_fid_to_inode
c_func
(paren
id|ViceFid
op_star
id|fid
comma
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
r_int
id|hash
op_assign
id|coda_f2i
c_func
(paren
id|fid
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;coda_fid_to_inode: no sb!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|inode
op_assign
id|iget5_locked
c_func
(paren
id|sb
comma
id|hash
comma
id|coda_test_inode
comma
id|coda_fail_inode
comma
id|fid
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* we should never see newly created inodes because we intentionally&n;&t; * fail in the initialization callback */
id|BUG_ON
c_func
(paren
id|inode-&gt;i_state
op_amp
id|I_NEW
)paren
suffix:semicolon
r_return
id|inode
suffix:semicolon
)brace
multiline_comment|/* the CONTROL inode is made without asking attributes from Venus */
DECL|function|coda_cnode_makectl
r_int
id|coda_cnode_makectl
c_func
(paren
r_struct
id|inode
op_star
op_star
id|inode
comma
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_int
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
op_star
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
op_star
id|inode
)paren
(brace
(paren
op_star
id|inode
)paren
op_member_access_from_pointer
id|i_ino
op_assign
id|CTL_INO
suffix:semicolon
(paren
op_star
id|inode
)paren
op_member_access_from_pointer
id|i_op
op_assign
op_amp
id|coda_ioctl_inode_operations
suffix:semicolon
(paren
op_star
id|inode
)paren
op_member_access_from_pointer
id|i_fop
op_assign
op_amp
id|coda_ioctl_operations
suffix:semicolon
(paren
op_star
id|inode
)paren
op_member_access_from_pointer
id|i_mode
op_assign
l_int|0444
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
eof
