multiline_comment|/*&n; * linux/fs/ext2/acl.c&n; *&n; * Copyright (C) 2001-2003 Andreas Gruenbacher, &lt;agruen@suse.de&gt;&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &quot;ext2.h&quot;
macro_line|#include &quot;xattr.h&quot;
macro_line|#include &quot;acl.h&quot;
multiline_comment|/*&n; * Convert from filesystem to in-memory representation.&n; */
r_static
r_struct
id|posix_acl
op_star
DECL|function|ext2_acl_from_disk
id|ext2_acl_from_disk
c_func
(paren
r_const
r_void
op_star
id|value
comma
r_int
id|size
)paren
(brace
r_const
r_char
op_star
id|end
op_assign
(paren
r_char
op_star
)paren
id|value
op_plus
id|size
suffix:semicolon
r_int
id|n
comma
id|count
suffix:semicolon
r_struct
id|posix_acl
op_star
id|acl
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
r_sizeof
(paren
id|ext2_acl_header
)paren
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|ext2_acl_header
op_star
)paren
id|value
)paren
op_member_access_from_pointer
id|a_version
op_ne
id|cpu_to_le32
c_func
(paren
id|EXT2_ACL_VERSION
)paren
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
id|value
op_assign
(paren
r_char
op_star
)paren
id|value
op_plus
r_sizeof
(paren
id|ext2_acl_header
)paren
suffix:semicolon
id|count
op_assign
id|ext2_acl_count
c_func
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|0
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
id|acl
op_assign
id|posix_acl_alloc
c_func
(paren
id|count
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acl
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|count
suffix:semicolon
id|n
op_increment
)paren
(brace
id|ext2_acl_entry
op_star
id|entry
op_assign
(paren
id|ext2_acl_entry
op_star
)paren
id|value
suffix:semicolon
r_if
c_cond
(paren
(paren
r_char
op_star
)paren
id|value
op_plus
r_sizeof
(paren
id|ext2_acl_entry_short
)paren
OG
id|end
)paren
r_goto
id|fail
suffix:semicolon
id|acl-&gt;a_entries
(braket
id|n
)braket
dot
id|e_tag
op_assign
id|le16_to_cpu
c_func
(paren
id|entry-&gt;e_tag
)paren
suffix:semicolon
id|acl-&gt;a_entries
(braket
id|n
)braket
dot
id|e_perm
op_assign
id|le16_to_cpu
c_func
(paren
id|entry-&gt;e_perm
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|acl-&gt;a_entries
(braket
id|n
)braket
dot
id|e_tag
)paren
(brace
r_case
id|ACL_USER_OBJ
suffix:colon
r_case
id|ACL_GROUP_OBJ
suffix:colon
r_case
id|ACL_MASK
suffix:colon
r_case
id|ACL_OTHER
suffix:colon
id|value
op_assign
(paren
r_char
op_star
)paren
id|value
op_plus
r_sizeof
(paren
id|ext2_acl_entry_short
)paren
suffix:semicolon
id|acl-&gt;a_entries
(braket
id|n
)braket
dot
id|e_id
op_assign
id|ACL_UNDEFINED_ID
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACL_USER
suffix:colon
r_case
id|ACL_GROUP
suffix:colon
id|value
op_assign
(paren
r_char
op_star
)paren
id|value
op_plus
r_sizeof
(paren
id|ext2_acl_entry
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_char
op_star
)paren
id|value
OG
id|end
)paren
r_goto
id|fail
suffix:semicolon
id|acl-&gt;a_entries
(braket
id|n
)braket
dot
id|e_id
op_assign
id|le32_to_cpu
c_func
(paren
id|entry-&gt;e_id
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_goto
id|fail
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|value
op_ne
id|end
)paren
r_goto
id|fail
suffix:semicolon
r_return
id|acl
suffix:semicolon
id|fail
suffix:colon
id|posix_acl_release
c_func
(paren
id|acl
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Convert from in-memory to filesystem representation.&n; */
r_static
r_void
op_star
DECL|function|ext2_acl_to_disk
id|ext2_acl_to_disk
c_func
(paren
r_const
r_struct
id|posix_acl
op_star
id|acl
comma
r_int
op_star
id|size
)paren
(brace
id|ext2_acl_header
op_star
id|ext_acl
suffix:semicolon
r_char
op_star
id|e
suffix:semicolon
r_int
id|n
suffix:semicolon
op_star
id|size
op_assign
id|ext2_acl_size
c_func
(paren
id|acl-&gt;a_count
)paren
suffix:semicolon
id|ext_acl
op_assign
(paren
id|ext2_acl_header
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|ext2_acl_header
)paren
op_plus
id|acl-&gt;a_count
op_star
r_sizeof
(paren
id|ext2_acl_entry
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ext_acl
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|ext_acl-&gt;a_version
op_assign
id|cpu_to_le32
c_func
(paren
id|EXT2_ACL_VERSION
)paren
suffix:semicolon
id|e
op_assign
(paren
r_char
op_star
)paren
id|ext_acl
op_plus
r_sizeof
(paren
id|ext2_acl_header
)paren
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|acl-&gt;a_count
suffix:semicolon
id|n
op_increment
)paren
(brace
id|ext2_acl_entry
op_star
id|entry
op_assign
(paren
id|ext2_acl_entry
op_star
)paren
id|e
suffix:semicolon
id|entry-&gt;e_tag
op_assign
id|cpu_to_le16
c_func
(paren
id|acl-&gt;a_entries
(braket
id|n
)braket
dot
id|e_tag
)paren
suffix:semicolon
id|entry-&gt;e_perm
op_assign
id|cpu_to_le16
c_func
(paren
id|acl-&gt;a_entries
(braket
id|n
)braket
dot
id|e_perm
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|acl-&gt;a_entries
(braket
id|n
)braket
dot
id|e_tag
)paren
(brace
r_case
id|ACL_USER
suffix:colon
r_case
id|ACL_GROUP
suffix:colon
id|entry-&gt;e_id
op_assign
id|cpu_to_le32
c_func
(paren
id|acl-&gt;a_entries
(braket
id|n
)braket
dot
id|e_id
)paren
suffix:semicolon
id|e
op_add_assign
r_sizeof
(paren
id|ext2_acl_entry
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACL_USER_OBJ
suffix:colon
r_case
id|ACL_GROUP_OBJ
suffix:colon
r_case
id|ACL_MASK
suffix:colon
r_case
id|ACL_OTHER
suffix:colon
id|e
op_add_assign
r_sizeof
(paren
id|ext2_acl_entry_short
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_goto
id|fail
suffix:semicolon
)brace
)brace
r_return
(paren
r_char
op_star
)paren
id|ext_acl
suffix:semicolon
id|fail
suffix:colon
id|kfree
c_func
(paren
id|ext_acl
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
)brace
r_static
r_inline
r_struct
id|posix_acl
op_star
DECL|function|ext2_iget_acl
id|ext2_iget_acl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|posix_acl
op_star
op_star
id|i_acl
)paren
(brace
r_struct
id|posix_acl
op_star
id|acl
op_assign
id|EXT2_ACL_NOT_CACHED
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|inode-&gt;i_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|i_acl
op_ne
id|EXT2_ACL_NOT_CACHED
)paren
id|acl
op_assign
id|posix_acl_dup
c_func
(paren
op_star
id|i_acl
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|inode-&gt;i_lock
)paren
suffix:semicolon
r_return
id|acl
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ext2_iset_acl
id|ext2_iset_acl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|posix_acl
op_star
op_star
id|i_acl
comma
r_struct
id|posix_acl
op_star
id|acl
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|inode-&gt;i_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|i_acl
op_ne
id|EXT2_ACL_NOT_CACHED
)paren
id|posix_acl_release
c_func
(paren
op_star
id|i_acl
)paren
suffix:semicolon
op_star
id|i_acl
op_assign
id|posix_acl_dup
c_func
(paren
id|acl
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|inode-&gt;i_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * inode-&gt;i_sem: don&squot;t care&n; */
r_static
r_struct
id|posix_acl
op_star
DECL|function|ext2_get_acl
id|ext2_get_acl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|type
)paren
(brace
r_const
r_int
id|max_size
op_assign
id|ext2_acl_size
c_func
(paren
id|EXT2_ACL_MAX_ENTRIES
)paren
suffix:semicolon
r_struct
id|ext2_inode_info
op_star
id|ei
op_assign
id|EXT2_I
c_func
(paren
id|inode
)paren
suffix:semicolon
r_int
id|name_index
suffix:semicolon
r_char
op_star
id|value
suffix:semicolon
r_struct
id|posix_acl
op_star
id|acl
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_opt
c_func
(paren
id|inode-&gt;i_sb
comma
id|POSIX_ACL
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|ACL_TYPE_ACCESS
suffix:colon
id|acl
op_assign
id|ext2_iget_acl
c_func
(paren
id|inode
comma
op_amp
id|ei-&gt;i_acl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acl
op_ne
id|EXT2_ACL_NOT_CACHED
)paren
r_return
id|acl
suffix:semicolon
id|name_index
op_assign
id|EXT2_XATTR_INDEX_POSIX_ACL_ACCESS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACL_TYPE_DEFAULT
suffix:colon
id|acl
op_assign
id|ext2_iget_acl
c_func
(paren
id|inode
comma
op_amp
id|ei-&gt;i_default_acl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acl
op_ne
id|EXT2_ACL_NOT_CACHED
)paren
r_return
id|acl
suffix:semicolon
id|name_index
op_assign
id|EXT2_XATTR_INDEX_POSIX_ACL_DEFAULT
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
)brace
id|value
op_assign
id|kmalloc
c_func
(paren
id|max_size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|retval
op_assign
id|ext2_xattr_get
c_func
(paren
id|inode
comma
id|name_index
comma
l_string|&quot;&quot;
comma
id|value
comma
id|max_size
)paren
suffix:semicolon
id|acl
op_assign
id|ERR_PTR
c_func
(paren
id|retval
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ge
l_int|0
)paren
id|acl
op_assign
id|ext2_acl_from_disk
c_func
(paren
id|value
comma
id|retval
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|retval
op_eq
op_minus
id|ENODATA
op_logical_or
id|retval
op_eq
op_minus
id|ENOSYS
)paren
id|acl
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|acl
)paren
)paren
(brace
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|ACL_TYPE_ACCESS
suffix:colon
id|ext2_iset_acl
c_func
(paren
id|inode
comma
op_amp
id|ei-&gt;i_acl
comma
id|acl
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACL_TYPE_DEFAULT
suffix:colon
id|ext2_iset_acl
c_func
(paren
id|inode
comma
op_amp
id|ei-&gt;i_default_acl
comma
id|acl
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|acl
suffix:semicolon
)brace
multiline_comment|/*&n; * inode-&gt;i_sem: down&n; */
r_static
r_int
DECL|function|ext2_set_acl
id|ext2_set_acl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|type
comma
r_struct
id|posix_acl
op_star
id|acl
)paren
(brace
r_struct
id|ext2_inode_info
op_star
id|ei
op_assign
id|EXT2_I
c_func
(paren
id|inode
)paren
suffix:semicolon
r_int
id|name_index
suffix:semicolon
r_void
op_star
id|value
op_assign
l_int|NULL
suffix:semicolon
r_int
id|size
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_opt
c_func
(paren
id|inode-&gt;i_sb
comma
id|POSIX_ACL
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|ACL_TYPE_ACCESS
suffix:colon
id|name_index
op_assign
id|EXT2_XATTR_INDEX_POSIX_ACL_ACCESS
suffix:semicolon
r_if
c_cond
(paren
id|acl
)paren
(brace
id|mode_t
id|mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
id|error
op_assign
id|posix_acl_equiv_mode
c_func
(paren
id|acl
comma
op_amp
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_return
id|error
suffix:semicolon
r_else
(brace
id|inode-&gt;i_mode
op_assign
id|mode
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
id|error
op_eq
l_int|0
)paren
id|acl
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|ACL_TYPE_DEFAULT
suffix:colon
id|name_index
op_assign
id|EXT2_XATTR_INDEX_POSIX_ACL_DEFAULT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_return
id|acl
ques
c_cond
op_minus
id|EACCES
suffix:colon
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acl
)paren
(brace
r_if
c_cond
(paren
id|acl-&gt;a_count
OG
id|EXT2_ACL_MAX_ENTRIES
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|value
op_assign
id|ext2_acl_to_disk
c_func
(paren
id|acl
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|value
)paren
)paren
r_return
(paren
r_int
)paren
id|PTR_ERR
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
id|error
op_assign
id|ext2_xattr_set
c_func
(paren
id|inode
comma
id|name_index
comma
l_string|&quot;&quot;
comma
id|value
comma
id|size
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
)paren
id|kfree
c_func
(paren
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|ACL_TYPE_ACCESS
suffix:colon
id|ext2_iset_acl
c_func
(paren
id|inode
comma
op_amp
id|ei-&gt;i_acl
comma
id|acl
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACL_TYPE_DEFAULT
suffix:colon
id|ext2_iset_acl
c_func
(paren
id|inode
comma
op_amp
id|ei-&gt;i_default_acl
comma
id|acl
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * Inode operation permission().&n; *&n; * inode-&gt;i_sem: don&squot;t care&n; */
r_int
DECL|function|ext2_permission
id|ext2_permission
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|mask
comma
r_struct
id|nameidata
op_star
id|nd
)paren
(brace
r_int
id|mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
multiline_comment|/* Nobody gets write access to a read-only fs */
r_if
c_cond
(paren
(paren
id|mask
op_amp
id|MAY_WRITE
)paren
op_logical_and
id|IS_RDONLY
c_func
(paren
id|inode
)paren
op_logical_and
(paren
id|S_ISREG
c_func
(paren
id|mode
)paren
op_logical_or
id|S_ISDIR
c_func
(paren
id|mode
)paren
op_logical_or
id|S_ISLNK
c_func
(paren
id|mode
)paren
)paren
)paren
r_return
op_minus
id|EROFS
suffix:semicolon
multiline_comment|/* Nobody gets write access to an immutable file */
r_if
c_cond
(paren
(paren
id|mask
op_amp
id|MAY_WRITE
)paren
op_logical_and
id|IS_IMMUTABLE
c_func
(paren
id|inode
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;fsuid
op_eq
id|inode-&gt;i_uid
)paren
(brace
id|mode
op_rshift_assign
l_int|6
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|test_opt
c_func
(paren
id|inode-&gt;i_sb
comma
id|POSIX_ACL
)paren
)paren
(brace
r_struct
id|posix_acl
op_star
id|acl
suffix:semicolon
multiline_comment|/* The access ACL cannot grant access if the group class&n;&t;&t;   permission bits don&squot;t contain all requested permissions. */
r_if
c_cond
(paren
(paren
(paren
id|mode
op_rshift
l_int|3
)paren
op_amp
id|mask
op_amp
id|S_IRWXO
)paren
op_ne
id|mask
)paren
r_goto
id|check_groups
suffix:semicolon
id|acl
op_assign
id|ext2_get_acl
c_func
(paren
id|inode
comma
id|ACL_TYPE_ACCESS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acl
)paren
(brace
r_int
id|error
op_assign
id|posix_acl_permission
c_func
(paren
id|inode
comma
id|acl
comma
id|mask
)paren
suffix:semicolon
id|posix_acl_release
c_func
(paren
id|acl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
op_minus
id|EACCES
)paren
r_goto
id|check_capabilities
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
r_else
r_goto
id|check_groups
suffix:semicolon
)brace
r_else
(brace
id|check_groups
suffix:colon
r_if
c_cond
(paren
id|in_group_p
c_func
(paren
id|inode-&gt;i_gid
)paren
)paren
id|mode
op_rshift_assign
l_int|3
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|mode
op_amp
id|mask
op_amp
id|S_IRWXO
)paren
op_eq
id|mask
)paren
r_return
l_int|0
suffix:semicolon
id|check_capabilities
suffix:colon
multiline_comment|/* Allowed to override Discretionary Access Control? */
r_if
c_cond
(paren
op_logical_neg
(paren
id|mask
op_amp
id|MAY_EXEC
)paren
op_logical_or
(paren
id|inode-&gt;i_mode
op_amp
id|S_IXUGO
)paren
op_logical_or
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_if
c_cond
(paren
id|capable
c_func
(paren
id|CAP_DAC_OVERRIDE
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Read and search granted if capable(CAP_DAC_READ_SEARCH) */
r_if
c_cond
(paren
id|capable
c_func
(paren
id|CAP_DAC_READ_SEARCH
)paren
op_logical_and
(paren
(paren
id|mask
op_eq
id|MAY_READ
)paren
op_logical_or
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_and
op_logical_neg
(paren
id|mask
op_amp
id|MAY_WRITE
)paren
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize the ACLs of a new inode. Called from ext2_new_inode.&n; *&n; * dir-&gt;i_sem: down&n; * inode-&gt;i_sem: up (access to inode is still exclusive)&n; */
r_int
DECL|function|ext2_init_acl
id|ext2_init_acl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|inode
op_star
id|dir
)paren
(brace
r_struct
id|posix_acl
op_star
id|acl
op_assign
l_int|NULL
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
r_if
c_cond
(paren
id|test_opt
c_func
(paren
id|dir-&gt;i_sb
comma
id|POSIX_ACL
)paren
)paren
(brace
id|acl
op_assign
id|ext2_get_acl
c_func
(paren
id|dir
comma
id|ACL_TYPE_DEFAULT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|acl
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|acl
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|acl
)paren
id|inode-&gt;i_mode
op_and_assign
op_complement
id|current-&gt;fs-&gt;umask
suffix:semicolon
)brace
r_if
c_cond
(paren
id|test_opt
c_func
(paren
id|inode-&gt;i_sb
comma
id|POSIX_ACL
)paren
op_logical_and
id|acl
)paren
(brace
r_struct
id|posix_acl
op_star
id|clone
suffix:semicolon
id|mode_t
id|mode
suffix:semicolon
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
id|error
op_assign
id|ext2_set_acl
c_func
(paren
id|inode
comma
id|ACL_TYPE_DEFAULT
comma
id|acl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|cleanup
suffix:semicolon
)brace
id|clone
op_assign
id|posix_acl_clone
c_func
(paren
id|acl
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|clone
)paren
r_goto
id|cleanup
suffix:semicolon
id|mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
id|error
op_assign
id|posix_acl_create_masq
c_func
(paren
id|clone
comma
op_amp
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ge
l_int|0
)paren
(brace
id|inode-&gt;i_mode
op_assign
id|mode
suffix:semicolon
r_if
c_cond
(paren
id|error
OG
l_int|0
)paren
(brace
multiline_comment|/* This is an extended ACL */
id|error
op_assign
id|ext2_set_acl
c_func
(paren
id|inode
comma
id|ACL_TYPE_ACCESS
comma
id|clone
)paren
suffix:semicolon
)brace
)brace
id|posix_acl_release
c_func
(paren
id|clone
)paren
suffix:semicolon
)brace
id|cleanup
suffix:colon
id|posix_acl_release
c_func
(paren
id|acl
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * Does chmod for an inode that may have an Access Control List. The&n; * inode-&gt;i_mode field must be updated to the desired value by the caller&n; * before calling this function.&n; * Returns 0 on success, or a negative error number.&n; *&n; * We change the ACL rather than storing some ACL entries in the file&n; * mode permission bits (which would be more efficient), because that&n; * would break once additional permissions (like  ACL_APPEND, ACL_DELETE&n; * for directories) are added. There are no more bits available in the&n; * file mode.&n; *&n; * inode-&gt;i_sem: down&n; */
r_int
DECL|function|ext2_acl_chmod
id|ext2_acl_chmod
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|posix_acl
op_star
id|acl
comma
op_star
id|clone
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_opt
c_func
(paren
id|inode-&gt;i_sb
comma
id|POSIX_ACL
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
id|acl
op_assign
id|ext2_get_acl
c_func
(paren
id|inode
comma
id|ACL_TYPE_ACCESS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|acl
)paren
op_logical_or
op_logical_neg
id|acl
)paren
r_return
id|PTR_ERR
c_func
(paren
id|acl
)paren
suffix:semicolon
id|clone
op_assign
id|posix_acl_clone
c_func
(paren
id|acl
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|posix_acl_release
c_func
(paren
id|acl
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|clone
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|error
op_assign
id|posix_acl_chmod_masq
c_func
(paren
id|clone
comma
id|inode-&gt;i_mode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|error
op_assign
id|ext2_set_acl
c_func
(paren
id|inode
comma
id|ACL_TYPE_ACCESS
comma
id|clone
)paren
suffix:semicolon
id|posix_acl_release
c_func
(paren
id|clone
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * Extended attribut handlers&n; */
r_static
r_int
DECL|function|ext2_xattr_list_acl_access
id|ext2_xattr_list_acl_access
c_func
(paren
r_char
op_star
id|list
comma
r_struct
id|inode
op_star
id|inode
comma
r_const
r_char
op_star
id|name
comma
r_int
id|name_len
)paren
(brace
r_const
r_int
id|size
op_assign
r_sizeof
(paren
id|XATTR_NAME_ACL_ACCESS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_opt
c_func
(paren
id|inode-&gt;i_sb
comma
id|POSIX_ACL
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|list
)paren
id|memcpy
c_func
(paren
id|list
comma
id|XATTR_NAME_ACL_ACCESS
comma
id|size
)paren
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
r_static
r_int
DECL|function|ext2_xattr_list_acl_default
id|ext2_xattr_list_acl_default
c_func
(paren
r_char
op_star
id|list
comma
r_struct
id|inode
op_star
id|inode
comma
r_const
r_char
op_star
id|name
comma
r_int
id|name_len
)paren
(brace
r_const
r_int
id|size
op_assign
r_sizeof
(paren
id|XATTR_NAME_ACL_DEFAULT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_opt
c_func
(paren
id|inode-&gt;i_sb
comma
id|POSIX_ACL
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|list
)paren
id|memcpy
c_func
(paren
id|list
comma
id|XATTR_NAME_ACL_DEFAULT
comma
id|size
)paren
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
r_static
r_int
DECL|function|ext2_xattr_get_acl
id|ext2_xattr_get_acl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|type
comma
r_void
op_star
id|buffer
comma
r_int
id|size
)paren
(brace
r_struct
id|posix_acl
op_star
id|acl
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_opt
c_func
(paren
id|inode-&gt;i_sb
comma
id|POSIX_ACL
)paren
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
id|acl
op_assign
id|ext2_get_acl
c_func
(paren
id|inode
comma
id|type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|acl
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|acl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acl
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODATA
suffix:semicolon
id|error
op_assign
id|posix_acl_to_xattr
c_func
(paren
id|acl
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
id|posix_acl_release
c_func
(paren
id|acl
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
r_static
r_int
DECL|function|ext2_xattr_get_acl_access
id|ext2_xattr_get_acl_access
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_const
r_char
op_star
id|name
comma
r_void
op_star
id|buffer
comma
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;&quot;
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|ext2_xattr_get_acl
c_func
(paren
id|inode
comma
id|ACL_TYPE_ACCESS
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|ext2_xattr_get_acl_default
id|ext2_xattr_get_acl_default
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_const
r_char
op_star
id|name
comma
r_void
op_star
id|buffer
comma
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;&quot;
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|ext2_xattr_get_acl
c_func
(paren
id|inode
comma
id|ACL_TYPE_DEFAULT
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|ext2_xattr_set_acl
id|ext2_xattr_set_acl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|type
comma
r_const
r_void
op_star
id|value
comma
r_int
id|size
)paren
(brace
r_struct
id|posix_acl
op_star
id|acl
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_opt
c_func
(paren
id|inode-&gt;i_sb
comma
id|POSIX_ACL
)paren
)paren
r_return
op_minus
id|EOPNOTSUPP
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
id|value
)paren
(brace
id|acl
op_assign
id|posix_acl_from_xattr
c_func
(paren
id|value
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|acl
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|acl
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|acl
)paren
(brace
id|error
op_assign
id|posix_acl_valid
c_func
(paren
id|acl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|release_and_out
suffix:semicolon
)brace
)brace
r_else
id|acl
op_assign
l_int|NULL
suffix:semicolon
id|error
op_assign
id|ext2_set_acl
c_func
(paren
id|inode
comma
id|type
comma
id|acl
)paren
suffix:semicolon
id|release_and_out
suffix:colon
id|posix_acl_release
c_func
(paren
id|acl
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
r_static
r_int
DECL|function|ext2_xattr_set_acl_access
id|ext2_xattr_set_acl_access
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_const
r_char
op_star
id|name
comma
r_const
r_void
op_star
id|value
comma
r_int
id|size
comma
r_int
id|flags
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;&quot;
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|ext2_xattr_set_acl
c_func
(paren
id|inode
comma
id|ACL_TYPE_ACCESS
comma
id|value
comma
id|size
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|ext2_xattr_set_acl_default
id|ext2_xattr_set_acl_default
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_const
r_char
op_star
id|name
comma
r_const
r_void
op_star
id|value
comma
r_int
id|size
comma
r_int
id|flags
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;&quot;
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|ext2_xattr_set_acl
c_func
(paren
id|inode
comma
id|ACL_TYPE_DEFAULT
comma
id|value
comma
id|size
)paren
suffix:semicolon
)brace
DECL|variable|ext2_xattr_acl_access_handler
r_struct
id|ext2_xattr_handler
id|ext2_xattr_acl_access_handler
op_assign
(brace
dot
id|prefix
op_assign
id|XATTR_NAME_ACL_ACCESS
comma
dot
id|list
op_assign
id|ext2_xattr_list_acl_access
comma
dot
id|get
op_assign
id|ext2_xattr_get_acl_access
comma
dot
id|set
op_assign
id|ext2_xattr_set_acl_access
comma
)brace
suffix:semicolon
DECL|variable|ext2_xattr_acl_default_handler
r_struct
id|ext2_xattr_handler
id|ext2_xattr_acl_default_handler
op_assign
(brace
dot
id|prefix
op_assign
id|XATTR_NAME_ACL_DEFAULT
comma
dot
id|list
op_assign
id|ext2_xattr_list_acl_default
comma
dot
id|get
op_assign
id|ext2_xattr_get_acl_default
comma
dot
id|set
op_assign
id|ext2_xattr_set_acl_default
comma
)brace
suffix:semicolon
r_void
DECL|function|exit_ext2_acl
id|exit_ext2_acl
c_func
(paren
r_void
)paren
(brace
id|ext2_xattr_unregister
c_func
(paren
id|EXT2_XATTR_INDEX_POSIX_ACL_ACCESS
comma
op_amp
id|ext2_xattr_acl_access_handler
)paren
suffix:semicolon
id|ext2_xattr_unregister
c_func
(paren
id|EXT2_XATTR_INDEX_POSIX_ACL_DEFAULT
comma
op_amp
id|ext2_xattr_acl_default_handler
)paren
suffix:semicolon
)brace
r_int
id|__init
DECL|function|init_ext2_acl
id|init_ext2_acl
c_func
(paren
r_void
)paren
(brace
r_int
id|error
suffix:semicolon
id|error
op_assign
id|ext2_xattr_register
c_func
(paren
id|EXT2_XATTR_INDEX_POSIX_ACL_ACCESS
comma
op_amp
id|ext2_xattr_acl_access_handler
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|fail
suffix:semicolon
id|error
op_assign
id|ext2_xattr_register
c_func
(paren
id|EXT2_XATTR_INDEX_POSIX_ACL_DEFAULT
comma
op_amp
id|ext2_xattr_acl_default_handler
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|fail
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
id|exit_ext2_acl
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
eof
