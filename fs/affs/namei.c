multiline_comment|/*&n; *  linux/fs/affs/namei.c&n; *&n; *  (c) 1996  Hans-Joachim Widmaier - Rewritten&n; *&n; *  (C) 1993  Ray Burr - Modified for Amiga FFS filesystem.&n; *&n; *  (C) 1991  Linus Torvalds - minix filesystem&n; */
macro_line|#include &quot;affs.h&quot;
DECL|typedef|toupper_t
r_typedef
r_int
(paren
op_star
id|toupper_t
)paren
(paren
r_int
)paren
suffix:semicolon
r_static
r_int
id|affs_toupper
c_func
(paren
r_int
id|ch
)paren
suffix:semicolon
r_static
r_int
id|affs_hash_dentry
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|qstr
op_star
)paren
suffix:semicolon
r_static
r_int
id|affs_compare_dentry
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|qstr
op_star
comma
r_struct
id|qstr
op_star
)paren
suffix:semicolon
r_static
r_int
id|affs_intl_toupper
c_func
(paren
r_int
id|ch
)paren
suffix:semicolon
r_static
r_int
id|affs_intl_hash_dentry
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|qstr
op_star
)paren
suffix:semicolon
r_static
r_int
id|affs_intl_compare_dentry
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|qstr
op_star
comma
r_struct
id|qstr
op_star
)paren
suffix:semicolon
DECL|variable|affs_dentry_operations
r_struct
id|dentry_operations
id|affs_dentry_operations
op_assign
(brace
dot
id|d_hash
op_assign
id|affs_hash_dentry
comma
dot
id|d_compare
op_assign
id|affs_compare_dentry
comma
)brace
suffix:semicolon
DECL|variable|affs_intl_dentry_operations
r_static
r_struct
id|dentry_operations
id|affs_intl_dentry_operations
op_assign
(brace
dot
id|d_hash
op_assign
id|affs_intl_hash_dentry
comma
dot
id|d_compare
op_assign
id|affs_intl_compare_dentry
comma
)brace
suffix:semicolon
multiline_comment|/* Simple toupper() for DOS&bslash;1 */
r_static
r_int
DECL|function|affs_toupper
id|affs_toupper
c_func
(paren
r_int
id|ch
)paren
(brace
r_return
id|ch
op_ge
l_char|&squot;a&squot;
op_logical_and
id|ch
op_le
l_char|&squot;z&squot;
ques
c_cond
id|ch
op_sub_assign
(paren
l_char|&squot;a&squot;
op_minus
l_char|&squot;A&squot;
)paren
suffix:colon
id|ch
suffix:semicolon
)brace
multiline_comment|/* International toupper() for DOS&bslash;3 (&quot;international&quot;) */
r_static
r_int
DECL|function|affs_intl_toupper
id|affs_intl_toupper
c_func
(paren
r_int
id|ch
)paren
(brace
r_return
(paren
id|ch
op_ge
l_char|&squot;a&squot;
op_logical_and
id|ch
op_le
l_char|&squot;z&squot;
)paren
op_logical_or
(paren
id|ch
op_ge
l_int|0xE0
op_logical_and
id|ch
op_le
l_int|0xFE
op_logical_and
id|ch
op_ne
l_int|0xF7
)paren
ques
c_cond
id|ch
op_minus
(paren
l_char|&squot;a&squot;
op_minus
l_char|&squot;A&squot;
)paren
suffix:colon
id|ch
suffix:semicolon
)brace
r_static
r_inline
id|toupper_t
DECL|function|affs_get_toupper
id|affs_get_toupper
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_return
id|AFFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_flags
op_amp
id|SF_INTL
ques
c_cond
id|affs_intl_toupper
suffix:colon
id|affs_toupper
suffix:semicolon
)brace
multiline_comment|/*&n; * Note: the dentry argument is the parent dentry.&n; */
r_static
r_inline
r_int
DECL|function|__affs_hash_dentry
id|__affs_hash_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|qstr
op_star
id|qstr
comma
id|toupper_t
id|toupper
)paren
(brace
r_const
id|u8
op_star
id|name
op_assign
id|qstr-&gt;name
suffix:semicolon
r_int
r_int
id|hash
suffix:semicolon
r_int
id|i
suffix:semicolon
id|i
op_assign
id|affs_check_name
c_func
(paren
id|qstr-&gt;name
comma
id|qstr-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
id|hash
op_assign
id|init_name_hash
c_func
(paren
)paren
suffix:semicolon
id|i
op_assign
id|min
c_func
(paren
id|qstr-&gt;len
comma
l_int|30u
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|name
op_increment
comma
id|i
op_decrement
)paren
id|hash
op_assign
id|partial_name_hash
c_func
(paren
id|toupper
c_func
(paren
op_star
id|name
)paren
comma
id|hash
)paren
suffix:semicolon
id|qstr-&gt;hash
op_assign
id|end_name_hash
c_func
(paren
id|hash
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|affs_hash_dentry
id|affs_hash_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|qstr
op_star
id|qstr
)paren
(brace
r_return
id|__affs_hash_dentry
c_func
(paren
id|dentry
comma
id|qstr
comma
id|affs_toupper
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|affs_intl_hash_dentry
id|affs_intl_hash_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|qstr
op_star
id|qstr
)paren
(brace
r_return
id|__affs_hash_dentry
c_func
(paren
id|dentry
comma
id|qstr
comma
id|affs_intl_toupper
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|__affs_compare_dentry
id|__affs_compare_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|qstr
op_star
id|a
comma
r_struct
id|qstr
op_star
id|b
comma
id|toupper_t
id|toupper
)paren
(brace
r_const
id|u8
op_star
id|aname
op_assign
id|a-&gt;name
suffix:semicolon
r_const
id|u8
op_star
id|bname
op_assign
id|b-&gt;name
suffix:semicolon
r_int
id|len
suffix:semicolon
multiline_comment|/* &squot;a&squot; is the qstr of an already existing dentry, so the name&n;&t; * must be valid. &squot;b&squot; must be validated first.&n;&t; */
r_if
c_cond
(paren
id|affs_check_name
c_func
(paren
id|b-&gt;name
comma
id|b-&gt;len
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* If the names are longer than the allowed 30 chars,&n;&t; * the excess is ignored, so their length may differ.&n;&t; */
id|len
op_assign
id|a-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
l_int|30
)paren
(brace
r_if
c_cond
(paren
id|b-&gt;len
OL
l_int|30
)paren
r_return
l_int|1
suffix:semicolon
id|len
op_assign
l_int|30
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|len
op_ne
id|b-&gt;len
)paren
r_return
l_int|1
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|len
OG
l_int|0
suffix:semicolon
id|len
op_decrement
)paren
r_if
c_cond
(paren
id|toupper
c_func
(paren
op_star
id|aname
op_increment
)paren
op_ne
id|toupper
c_func
(paren
op_star
id|bname
op_increment
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|affs_compare_dentry
id|affs_compare_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|qstr
op_star
id|a
comma
r_struct
id|qstr
op_star
id|b
)paren
(brace
r_return
id|__affs_compare_dentry
c_func
(paren
id|dentry
comma
id|a
comma
id|b
comma
id|affs_toupper
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|affs_intl_compare_dentry
id|affs_intl_compare_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|qstr
op_star
id|a
comma
r_struct
id|qstr
op_star
id|b
)paren
(brace
r_return
id|__affs_compare_dentry
c_func
(paren
id|dentry
comma
id|a
comma
id|b
comma
id|affs_intl_toupper
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * NOTE! unlike strncmp, affs_match returns 1 for success, 0 for failure.&n; */
r_static
r_inline
r_int
DECL|function|affs_match
id|affs_match
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_const
id|u8
op_star
id|name2
comma
id|toupper_t
id|toupper
)paren
(brace
r_const
id|u8
op_star
id|name
op_assign
id|dentry-&gt;d_name.name
suffix:semicolon
r_int
id|len
op_assign
id|dentry-&gt;d_name.len
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
l_int|30
)paren
(brace
r_if
c_cond
(paren
op_star
id|name2
OL
l_int|30
)paren
r_return
l_int|0
suffix:semicolon
id|len
op_assign
l_int|30
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|len
op_ne
op_star
id|name2
)paren
r_return
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|name2
op_increment
suffix:semicolon
id|len
OG
l_int|0
suffix:semicolon
id|len
op_decrement
)paren
r_if
c_cond
(paren
id|toupper
c_func
(paren
op_star
id|name
op_increment
)paren
op_ne
id|toupper
c_func
(paren
op_star
id|name2
op_increment
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_int
DECL|function|affs_hash_name
id|affs_hash_name
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_const
id|u8
op_star
id|name
comma
r_int
r_int
id|len
)paren
(brace
id|toupper_t
id|toupper
op_assign
id|affs_get_toupper
c_func
(paren
id|sb
)paren
suffix:semicolon
r_int
id|hash
suffix:semicolon
id|hash
op_assign
id|len
op_assign
id|min
c_func
(paren
id|len
comma
l_int|30u
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|len
OG
l_int|0
suffix:semicolon
id|len
op_decrement
)paren
id|hash
op_assign
(paren
id|hash
op_star
l_int|13
op_plus
id|toupper
c_func
(paren
op_star
id|name
op_increment
)paren
)paren
op_amp
l_int|0x7ff
suffix:semicolon
r_return
id|hash
op_mod
id|AFFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_hashsize
suffix:semicolon
)brace
r_static
r_struct
id|buffer_head
op_star
DECL|function|affs_find_entry
id|affs_find_entry
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|dir-&gt;i_sb
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|toupper_t
id|toupper
op_assign
id|affs_get_toupper
c_func
(paren
id|sb
)paren
suffix:semicolon
id|u32
id|key
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: find_entry(&bslash;&quot;%.*s&bslash;&quot;)&bslash;n&quot;
comma
(paren
r_int
)paren
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
id|bh
op_assign
id|affs_bread
c_func
(paren
id|sb
comma
id|dir-&gt;i_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EIO
)paren
suffix:semicolon
id|key
op_assign
id|be32_to_cpu
c_func
(paren
id|AFFS_HEAD
c_func
(paren
id|bh
)paren
op_member_access_from_pointer
id|table
(braket
id|affs_hash_name
c_func
(paren
id|sb
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
)paren
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|affs_brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|key
op_eq
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
id|bh
op_assign
id|affs_bread
c_func
(paren
id|sb
comma
id|key
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EIO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|affs_match
c_func
(paren
id|dentry
comma
id|AFFS_TAIL
c_func
(paren
id|sb
comma
id|bh
)paren
op_member_access_from_pointer
id|name
comma
id|toupper
)paren
)paren
r_return
id|bh
suffix:semicolon
id|key
op_assign
id|be32_to_cpu
c_func
(paren
id|AFFS_TAIL
c_func
(paren
id|sb
comma
id|bh
)paren
op_member_access_from_pointer
id|hash_chain
)paren
suffix:semicolon
)brace
)brace
r_struct
id|dentry
op_star
DECL|function|affs_lookup
id|affs_lookup
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|nameidata
op_star
id|nd
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|dir-&gt;i_sb
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
l_int|NULL
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: lookup(&bslash;&quot;%.*s&bslash;&quot;)&bslash;n&quot;
comma
(paren
r_int
)paren
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
id|affs_lock_dir
c_func
(paren
id|dir
)paren
suffix:semicolon
id|bh
op_assign
id|affs_find_entry
c_func
(paren
id|dir
comma
id|dentry
)paren
suffix:semicolon
id|affs_unlock_dir
c_func
(paren
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|bh
)paren
)paren
(brace
r_return
id|ERR_PTR
c_func
(paren
id|PTR_ERR
c_func
(paren
id|bh
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bh
)paren
(brace
id|u32
id|ino
op_assign
id|bh-&gt;b_blocknr
suffix:semicolon
multiline_comment|/* store the real header ino in d_fsdata for faster lookups */
id|dentry-&gt;d_fsdata
op_assign
(paren
r_void
op_star
)paren
(paren
r_int
)paren
id|ino
suffix:semicolon
r_switch
c_cond
(paren
id|be32_to_cpu
c_func
(paren
id|AFFS_TAIL
c_func
(paren
id|sb
comma
id|bh
)paren
op_member_access_from_pointer
id|stype
)paren
)paren
(brace
singleline_comment|//link to dirs disabled
singleline_comment|//case ST_LINKDIR:
r_case
id|ST_LINKFILE
suffix:colon
id|ino
op_assign
id|be32_to_cpu
c_func
(paren
id|AFFS_TAIL
c_func
(paren
id|sb
comma
id|bh
)paren
op_member_access_from_pointer
id|original
)paren
suffix:semicolon
)brace
id|affs_brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|inode
op_assign
id|iget
c_func
(paren
id|sb
comma
id|ino
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
(brace
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EACCES
)paren
suffix:semicolon
)brace
)brace
id|dentry-&gt;d_op
op_assign
id|AFFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_flags
op_amp
id|SF_INTL
ques
c_cond
op_amp
id|affs_intl_dentry_operations
suffix:colon
op_amp
id|affs_dentry_operations
suffix:semicolon
id|d_add
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_int
DECL|function|affs_unlink
id|affs_unlink
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: unlink(dir=%d, &bslash;&quot;%.*s&bslash;&quot;)&bslash;n&quot;
comma
(paren
id|u32
)paren
id|dir-&gt;i_ino
comma
(paren
r_int
)paren
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
r_return
id|affs_remove_header
c_func
(paren
id|dentry
)paren
suffix:semicolon
)brace
r_int
DECL|function|affs_create
id|affs_create
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mode
comma
r_struct
id|nameidata
op_star
id|nd
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|dir-&gt;i_sb
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|error
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: create(%lu,&bslash;&quot;%.*s&bslash;&quot;,0%o)&bslash;n&quot;
comma
id|dir-&gt;i_ino
comma
(paren
r_int
)paren
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
comma
id|mode
)paren
suffix:semicolon
id|inode
op_assign
id|affs_new_inode
c_func
(paren
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
op_minus
id|ENOSPC
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|mode
suffix:semicolon
id|mode_to_prot
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
id|inode-&gt;i_op
op_assign
op_amp
id|affs_file_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|affs_file_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
(paren
id|AFFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_flags
op_amp
id|SF_OFS
)paren
ques
c_cond
op_amp
id|affs_aops_ofs
suffix:colon
op_amp
id|affs_aops
suffix:semicolon
id|error
op_assign
id|affs_add_entry
c_func
(paren
id|dir
comma
id|inode
comma
id|dentry
comma
id|ST_FILE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
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
id|error
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|affs_mkdir
id|affs_mkdir
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mode
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|error
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: mkdir(%lu,&bslash;&quot;%.*s&bslash;&quot;,0%o)&bslash;n&quot;
comma
id|dir-&gt;i_ino
comma
(paren
r_int
)paren
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
comma
id|mode
)paren
suffix:semicolon
id|inode
op_assign
id|affs_new_inode
c_func
(paren
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
op_minus
id|ENOSPC
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IFDIR
op_or
id|mode
suffix:semicolon
id|mode_to_prot
c_func
(paren
id|inode
)paren
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|affs_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|affs_dir_operations
suffix:semicolon
id|error
op_assign
id|affs_add_entry
c_func
(paren
id|dir
comma
id|inode
comma
id|dentry
comma
id|ST_USERDIR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|affs_rmdir
id|affs_rmdir
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: rmdir(dir=%u, &bslash;&quot;%.*s&bslash;&quot;)&bslash;n&quot;
comma
(paren
id|u32
)paren
id|dir-&gt;i_ino
comma
(paren
r_int
)paren
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
r_return
id|affs_remove_header
c_func
(paren
id|dentry
)paren
suffix:semicolon
)brace
r_int
DECL|function|affs_symlink
id|affs_symlink
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_const
r_char
op_star
id|symname
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|dir-&gt;i_sb
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_int
id|i
comma
id|maxlen
comma
id|error
suffix:semicolon
r_char
id|c
comma
id|lc
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: symlink(%lu,&bslash;&quot;%.*s&bslash;&quot; -&gt; &bslash;&quot;%s&bslash;&quot;)&bslash;n&quot;
comma
id|dir-&gt;i_ino
comma
(paren
r_int
)paren
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
comma
id|symname
)paren
suffix:semicolon
id|maxlen
op_assign
id|AFFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_hashsize
op_star
r_sizeof
(paren
id|u32
)paren
op_minus
l_int|1
suffix:semicolon
id|inode
op_assign
id|affs_new_inode
c_func
(paren
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
op_minus
id|ENOSPC
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|affs_symlink_inode_operations
suffix:semicolon
id|inode-&gt;i_data.a_ops
op_assign
op_amp
id|affs_symlink_aops
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IFLNK
op_or
l_int|0777
suffix:semicolon
id|mode_to_prot
c_func
(paren
id|inode
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|EIO
suffix:semicolon
id|bh
op_assign
id|affs_bread
c_func
(paren
id|sb
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_goto
id|err
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
id|p
op_assign
(paren
r_char
op_star
)paren
id|AFFS_HEAD
c_func
(paren
id|bh
)paren
op_member_access_from_pointer
id|table
suffix:semicolon
id|lc
op_assign
l_char|&squot;/&squot;
suffix:semicolon
r_if
c_cond
(paren
op_star
id|symname
op_eq
l_char|&squot;/&squot;
)paren
(brace
r_while
c_loop
(paren
op_star
id|symname
op_eq
l_char|&squot;/&squot;
)paren
id|symname
op_increment
suffix:semicolon
r_while
c_loop
(paren
id|AFFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_volume
(braket
id|i
)braket
)paren
multiline_comment|/* Cannot overflow */
op_star
id|p
op_increment
op_assign
id|AFFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_volume
(braket
id|i
op_increment
)braket
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
OL
id|maxlen
op_logical_and
(paren
id|c
op_assign
op_star
id|symname
op_increment
)paren
)paren
(brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;.&squot;
op_logical_and
id|lc
op_eq
l_char|&squot;/&squot;
op_logical_and
op_star
id|symname
op_eq
l_char|&squot;.&squot;
op_logical_and
id|symname
(braket
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
)paren
(brace
op_star
id|p
op_increment
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|symname
op_add_assign
l_int|2
suffix:semicolon
id|lc
op_assign
l_char|&squot;/&squot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;.&squot;
op_logical_and
id|lc
op_eq
l_char|&squot;/&squot;
op_logical_and
op_star
id|symname
op_eq
l_char|&squot;/&squot;
)paren
(brace
id|symname
op_increment
suffix:semicolon
id|lc
op_assign
l_char|&squot;/&squot;
suffix:semicolon
)brace
r_else
(brace
op_star
id|p
op_increment
op_assign
id|c
suffix:semicolon
id|lc
op_assign
id|c
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lc
op_eq
l_char|&squot;/&squot;
)paren
r_while
c_loop
(paren
op_star
id|symname
op_eq
l_char|&squot;/&squot;
)paren
id|symname
op_increment
suffix:semicolon
)brace
op_star
id|p
op_assign
l_int|0
suffix:semicolon
id|mark_buffer_dirty_inode
c_func
(paren
id|bh
comma
id|inode
)paren
suffix:semicolon
id|affs_brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|error
op_assign
id|affs_add_entry
c_func
(paren
id|dir
comma
id|inode
comma
id|dentry
comma
id|ST_SOFTLINK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|err
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err
suffix:colon
id|inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
r_int
DECL|function|affs_link
id|affs_link
c_func
(paren
r_struct
id|dentry
op_star
id|old_dentry
comma
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|old_dentry-&gt;d_inode
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: link(%u, %u, &bslash;&quot;%.*s&bslash;&quot;)&bslash;n&quot;
comma
(paren
id|u32
)paren
id|inode-&gt;i_ino
comma
(paren
id|u32
)paren
id|dir-&gt;i_ino
comma
(paren
r_int
)paren
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
r_return
id|affs_add_entry
c_func
(paren
id|dir
comma
id|inode
comma
id|dentry
comma
id|ST_LINKFILE
)paren
suffix:semicolon
)brace
r_int
DECL|function|affs_rename
id|affs_rename
c_func
(paren
r_struct
id|inode
op_star
id|old_dir
comma
r_struct
id|dentry
op_star
id|old_dentry
comma
r_struct
id|inode
op_star
id|new_dir
comma
r_struct
id|dentry
op_star
id|new_dentry
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|old_dir-&gt;i_sb
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: rename(old=%u,&bslash;&quot;%*s&bslash;&quot; to new=%u,&bslash;&quot;%*s&bslash;&quot;)&bslash;n&quot;
comma
(paren
id|u32
)paren
id|old_dir-&gt;i_ino
comma
(paren
r_int
)paren
id|old_dentry-&gt;d_name.len
comma
id|old_dentry-&gt;d_name.name
comma
(paren
id|u32
)paren
id|new_dir-&gt;i_ino
comma
(paren
r_int
)paren
id|new_dentry-&gt;d_name.len
comma
id|new_dentry-&gt;d_name.name
)paren
suffix:semicolon
id|retval
op_assign
id|affs_check_name
c_func
(paren
id|new_dentry-&gt;d_name.name
comma
id|new_dentry-&gt;d_name.len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
multiline_comment|/* Unlink destination if it already exists */
r_if
c_cond
(paren
id|new_dentry-&gt;d_inode
)paren
(brace
id|retval
op_assign
id|affs_remove_header
c_func
(paren
id|new_dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
)brace
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
id|bh
op_assign
id|affs_bread
c_func
(paren
id|sb
comma
id|old_dentry-&gt;d_inode-&gt;i_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_goto
id|done
suffix:semicolon
multiline_comment|/* Remove header from its parent directory. */
id|affs_lock_dir
c_func
(paren
id|old_dir
)paren
suffix:semicolon
id|retval
op_assign
id|affs_remove_hash
c_func
(paren
id|old_dir
comma
id|bh
)paren
suffix:semicolon
id|affs_unlock_dir
c_func
(paren
id|old_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|done
suffix:semicolon
multiline_comment|/* And insert it into the new directory with the new name. */
id|affs_copy_name
c_func
(paren
id|AFFS_TAIL
c_func
(paren
id|sb
comma
id|bh
)paren
op_member_access_from_pointer
id|name
comma
id|new_dentry
)paren
suffix:semicolon
id|affs_fix_checksum
c_func
(paren
id|sb
comma
id|bh
)paren
suffix:semicolon
id|affs_lock_dir
c_func
(paren
id|new_dir
)paren
suffix:semicolon
id|retval
op_assign
id|affs_insert_hash
c_func
(paren
id|new_dir
comma
id|bh
)paren
suffix:semicolon
id|affs_unlock_dir
c_func
(paren
id|new_dir
)paren
suffix:semicolon
multiline_comment|/* TODO: move it back to old_dir, if error? */
id|done
suffix:colon
id|mark_buffer_dirty_inode
c_func
(paren
id|bh
comma
id|retval
ques
c_cond
id|old_dir
suffix:colon
id|new_dir
)paren
suffix:semicolon
id|affs_brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
eof
