multiline_comment|/*&n; * fs/isofs/export.c&n; *&n; *  (C) 2004  Paul Serice - The new inode scheme requires switching&n; *                          from iget() to iget5_locked() which means&n; *                          the NFS export operations have to be hand&n; *                          coded because the default routines rely on&n; *                          iget().&n; *&n; * The following files are helpful:&n; *&n; *     Documentation/filesystems/Exporting&n; *     fs/exportfs/expfs.c.&n; */
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/iso_fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
r_static
r_struct
id|dentry
op_star
DECL|function|isofs_export_iget
id|isofs_export_iget
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|block
comma
r_int
r_int
id|offset
comma
id|__u32
id|generation
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|dentry
op_star
id|result
suffix:semicolon
r_if
c_cond
(paren
id|block
op_eq
l_int|0
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ESTALE
)paren
suffix:semicolon
id|inode
op_assign
id|isofs_iget
c_func
(paren
id|sb
comma
id|block
comma
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
op_eq
l_int|NULL
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
id|is_bad_inode
c_func
(paren
id|inode
)paren
op_logical_or
(paren
id|generation
op_logical_and
id|inode-&gt;i_generation
op_ne
id|generation
)paren
)paren
(brace
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
id|ESTALE
)paren
suffix:semicolon
)brace
id|result
op_assign
id|d_alloc_anon
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|result
)paren
(brace
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
id|ENOMEM
)paren
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
r_static
r_struct
id|dentry
op_star
DECL|function|isofs_export_get_dentry
id|isofs_export_get_dentry
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_void
op_star
id|vobjp
)paren
(brace
id|__u32
op_star
id|objp
op_assign
id|vobjp
suffix:semicolon
r_int
r_int
id|block
op_assign
id|objp
(braket
l_int|0
)braket
suffix:semicolon
r_int
r_int
id|offset
op_assign
id|objp
(braket
l_int|1
)braket
suffix:semicolon
id|__u32
id|generation
op_assign
id|objp
(braket
l_int|2
)braket
suffix:semicolon
r_return
id|isofs_export_iget
c_func
(paren
id|sb
comma
id|block
comma
id|offset
comma
id|generation
)paren
suffix:semicolon
)brace
multiline_comment|/* This function is surprisingly simple.  The trick is understanding&n; * that &quot;child&quot; is always a directory. So, to find its parent, you&n; * simply need to find its &quot;..&quot; entry, normalize its block and offset,&n; * and return the underlying inode.  See the comments for&n; * isofs_normalize_block_and_offset(). */
DECL|function|isofs_export_get_parent
r_static
r_struct
id|dentry
op_star
id|isofs_export_get_parent
c_func
(paren
r_struct
id|dentry
op_star
id|child
)paren
(brace
r_int
r_int
id|parent_block
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|parent_offset
op_assign
l_int|0
suffix:semicolon
r_struct
id|inode
op_star
id|child_inode
op_assign
id|child-&gt;d_inode
suffix:semicolon
r_struct
id|iso_inode_info
op_star
id|e_child_inode
op_assign
id|ISOFS_I
c_func
(paren
id|child_inode
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|parent_inode
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|iso_directory_record
op_star
id|de
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|dentry
op_star
id|rv
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* &quot;child&quot; must always be a directory. */
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|child_inode-&gt;i_mode
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;isofs: isofs_export_get_parent(): &quot;
l_string|&quot;child is not a directory!&bslash;n&quot;
)paren
suffix:semicolon
id|rv
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|EACCES
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* It is an invariant that the directory offset is zero.  If&n;&t; * it is not zero, it means the directory failed to be&n;&t; * normalized for some reason. */
r_if
c_cond
(paren
id|e_child_inode-&gt;i_iget5_offset
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;isofs: isofs_export_get_parent(): &quot;
l_string|&quot;child directory not normalized!&bslash;n&quot;
)paren
suffix:semicolon
id|rv
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|EACCES
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* The child inode has been normalized such that its&n;&t; * i_iget5_block value points to the &quot;.&quot; entry.  Fortunately,&n;&t; * the &quot;..&quot; entry is located in the same block. */
id|parent_block
op_assign
id|e_child_inode-&gt;i_iget5_block
suffix:semicolon
multiline_comment|/* Get the block in question. */
id|bh
op_assign
id|sb_bread
c_func
(paren
id|child_inode-&gt;i_sb
comma
id|parent_block
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
op_eq
l_int|NULL
)paren
(brace
id|rv
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|EACCES
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* This is the &quot;.&quot; entry. */
id|de
op_assign
(paren
r_struct
id|iso_directory_record
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
multiline_comment|/* The &quot;..&quot; entry is always the second entry. */
id|parent_offset
op_assign
(paren
r_int
r_int
)paren
id|isonum_711
c_func
(paren
id|de-&gt;length
)paren
suffix:semicolon
id|de
op_assign
(paren
r_struct
id|iso_directory_record
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
id|parent_offset
)paren
suffix:semicolon
multiline_comment|/* Verify it is in fact the &quot;..&quot; entry. */
r_if
c_cond
(paren
(paren
id|isonum_711
c_func
(paren
id|de-&gt;name_len
)paren
op_ne
l_int|1
)paren
op_logical_or
(paren
id|de-&gt;name
(braket
l_int|0
)braket
op_ne
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;isofs: Unable to find the &bslash;&quot;..&bslash;&quot; &quot;
l_string|&quot;directory for NFS.&bslash;n&quot;
)paren
suffix:semicolon
id|rv
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|EACCES
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Normalize */
id|isofs_normalize_block_and_offset
c_func
(paren
id|de
comma
op_amp
id|parent_block
comma
op_amp
id|parent_offset
)paren
suffix:semicolon
multiline_comment|/* Get the inode. */
id|parent_inode
op_assign
id|isofs_iget
c_func
(paren
id|child_inode-&gt;i_sb
comma
id|parent_block
comma
id|parent_offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parent_inode
op_eq
l_int|NULL
)paren
(brace
id|rv
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|EACCES
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Allocate the dentry. */
id|rv
op_assign
id|d_alloc_anon
c_func
(paren
id|parent_inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rv
op_eq
l_int|NULL
)paren
(brace
id|rv
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|out
suffix:colon
r_if
c_cond
(paren
id|bh
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
r_return
id|rv
suffix:semicolon
)brace
r_static
r_int
DECL|function|isofs_export_encode_fh
id|isofs_export_encode_fh
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
id|__u32
op_star
id|fh32
comma
r_int
op_star
id|max_len
comma
r_int
id|connectable
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_struct
id|iso_inode_info
op_star
id|ei
op_assign
id|ISOFS_I
c_func
(paren
id|inode
)paren
suffix:semicolon
r_int
id|len
op_assign
op_star
id|max_len
suffix:semicolon
r_int
id|type
op_assign
l_int|1
suffix:semicolon
id|__u16
op_star
id|fh16
op_assign
(paren
id|__u16
op_star
)paren
id|fh32
suffix:semicolon
multiline_comment|/*&n;&t; * WARNING: max_len is 5 for NFSv2.  Because of this&n;&t; * limitation, we use the lower 16 bits of fh32[1] to hold the&n;&t; * offset of the inode and the upper 16 bits of fh32[1] to&n;&t; * hold the offset of the parent.&n;&t; */
r_if
c_cond
(paren
id|len
OL
l_int|3
op_logical_or
(paren
id|connectable
op_logical_and
id|len
OL
l_int|5
)paren
)paren
r_return
l_int|255
suffix:semicolon
id|len
op_assign
l_int|3
suffix:semicolon
id|fh32
(braket
l_int|0
)braket
op_assign
id|ei-&gt;i_iget5_block
suffix:semicolon
id|fh16
(braket
l_int|2
)braket
op_assign
(paren
id|__u16
)paren
id|ei-&gt;i_iget5_offset
suffix:semicolon
multiline_comment|/* fh16 [sic] */
id|fh32
(braket
l_int|2
)braket
op_assign
id|inode-&gt;i_generation
suffix:semicolon
r_if
c_cond
(paren
id|connectable
op_logical_and
op_logical_neg
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
r_struct
id|inode
op_star
id|parent
suffix:semicolon
r_struct
id|iso_inode_info
op_star
id|eparent
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dentry-&gt;d_lock
)paren
suffix:semicolon
id|parent
op_assign
id|dentry-&gt;d_parent-&gt;d_inode
suffix:semicolon
id|eparent
op_assign
id|ISOFS_I
c_func
(paren
id|parent
)paren
suffix:semicolon
id|fh32
(braket
l_int|3
)braket
op_assign
id|eparent-&gt;i_iget5_block
suffix:semicolon
id|fh16
(braket
l_int|3
)braket
op_assign
(paren
id|__u16
)paren
id|eparent-&gt;i_iget5_offset
suffix:semicolon
multiline_comment|/* fh16 [sic] */
id|fh32
(braket
l_int|4
)braket
op_assign
id|parent-&gt;i_generation
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dentry-&gt;d_lock
)paren
suffix:semicolon
id|len
op_assign
l_int|5
suffix:semicolon
id|type
op_assign
l_int|2
suffix:semicolon
)brace
op_star
id|max_len
op_assign
id|len
suffix:semicolon
r_return
id|type
suffix:semicolon
)brace
r_static
r_struct
id|dentry
op_star
DECL|function|isofs_export_decode_fh
id|isofs_export_decode_fh
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|__u32
op_star
id|fh32
comma
r_int
id|fh_len
comma
r_int
id|fileid_type
comma
r_int
(paren
op_star
id|acceptable
)paren
(paren
r_void
op_star
id|context
comma
r_struct
id|dentry
op_star
id|de
)paren
comma
r_void
op_star
id|context
)paren
(brace
id|__u16
op_star
id|fh16
op_assign
(paren
id|__u16
op_star
)paren
id|fh32
suffix:semicolon
id|__u32
id|child
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* The child is what triggered all this. */
id|__u32
id|parent
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* The parent is just along for the ride. */
r_if
c_cond
(paren
id|fh_len
template_param
l_int|2
)paren
r_return
l_int|NULL
suffix:semicolon
id|child
(braket
l_int|0
)braket
op_assign
id|fh32
(braket
l_int|0
)braket
suffix:semicolon
id|child
(braket
l_int|1
)braket
op_assign
id|fh16
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* fh16 [sic] */
id|child
(braket
l_int|2
)braket
op_assign
id|fh32
(braket
l_int|2
)braket
suffix:semicolon
id|parent
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|parent
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|parent
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|fileid_type
op_eq
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|fh_len
OG
l_int|2
)paren
id|parent
(braket
l_int|0
)braket
op_assign
id|fh32
(braket
l_int|3
)braket
suffix:semicolon
id|parent
(braket
l_int|1
)braket
op_assign
id|fh16
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* fh16 [sic] */
r_if
c_cond
(paren
id|fh_len
OG
l_int|4
)paren
id|parent
(braket
l_int|2
)braket
op_assign
id|fh32
(braket
l_int|4
)braket
suffix:semicolon
)brace
r_return
id|sb-&gt;s_export_op
op_member_access_from_pointer
id|find_exported_dentry
c_func
(paren
id|sb
comma
id|child
comma
id|parent
comma
id|acceptable
comma
id|context
)paren
suffix:semicolon
)brace
DECL|variable|isofs_export_ops
r_struct
id|export_operations
id|isofs_export_ops
op_assign
(brace
dot
id|decode_fh
op_assign
id|isofs_export_decode_fh
comma
dot
id|encode_fh
op_assign
id|isofs_export_encode_fh
comma
dot
id|get_dentry
op_assign
id|isofs_export_get_dentry
comma
dot
id|get_parent
op_assign
id|isofs_export_get_parent
comma
)brace
suffix:semicolon
eof
