macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/posix_acl.h&gt;
macro_line|#include &lt;linux/reiserfs_fs.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/xattr.h&gt;
macro_line|#include &lt;linux/xattr_acl.h&gt;
macro_line|#include &lt;linux/reiserfs_xattr.h&gt;
macro_line|#include &lt;linux/reiserfs_acl.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_static
r_int
DECL|function|xattr_set_acl
id|xattr_set_acl
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
id|reiserfs_posixacl
c_func
(paren
id|inode-&gt;i_sb
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
(brace
r_return
id|PTR_ERR
c_func
(paren
id|acl
)paren
suffix:semicolon
)brace
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
id|reiserfs_set_acl
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
DECL|function|xattr_get_acl
id|xattr_get_acl
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
id|reiserfs_posixacl
c_func
(paren
id|inode-&gt;i_sb
)paren
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
id|acl
op_assign
id|reiserfs_get_acl
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
multiline_comment|/*&n; * Convert from filesystem to in-memory representation.&n; */
r_static
r_struct
id|posix_acl
op_star
DECL|function|posix_acl_from_disk
id|posix_acl_from_disk
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
id|reiserfs_acl_header
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
id|reiserfs_acl_header
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
id|REISERFS_ACL_VERSION
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
id|reiserfs_acl_header
)paren
suffix:semicolon
id|count
op_assign
id|reiserfs_acl_count
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
id|GFP_NOFS
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
id|reiserfs_acl_entry
op_star
id|entry
op_assign
(paren
id|reiserfs_acl_entry
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
id|reiserfs_acl_entry_short
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
id|reiserfs_acl_entry_short
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
id|reiserfs_acl_entry
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
DECL|function|posix_acl_to_disk
id|posix_acl_to_disk
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
id|reiserfs_acl_header
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
id|reiserfs_acl_size
c_func
(paren
id|acl-&gt;a_count
)paren
suffix:semicolon
id|ext_acl
op_assign
(paren
id|reiserfs_acl_header
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|reiserfs_acl_header
)paren
op_plus
id|acl-&gt;a_count
op_star
r_sizeof
(paren
id|reiserfs_acl_entry
)paren
comma
id|GFP_NOFS
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
id|REISERFS_ACL_VERSION
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
id|reiserfs_acl_header
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
id|reiserfs_acl_entry
op_star
id|entry
op_assign
(paren
id|reiserfs_acl_entry
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
id|reiserfs_acl_entry
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
id|reiserfs_acl_entry_short
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
multiline_comment|/*&n; * Inode operation get_posix_acl().&n; *&n; * inode-&gt;i_sem: down&n; * BKL held [before 2.5.x]&n; */
r_struct
id|posix_acl
op_star
DECL|function|reiserfs_get_acl
id|reiserfs_get_acl
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
r_char
op_star
id|name
comma
op_star
id|value
suffix:semicolon
r_struct
id|posix_acl
op_star
id|acl
comma
op_star
op_star
id|p_acl
suffix:semicolon
r_int
id|size
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_struct
id|reiserfs_inode_info
op_star
id|reiserfs_i
op_assign
id|REISERFS_I
c_func
(paren
id|inode
)paren
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
id|name
op_assign
id|XATTR_NAME_ACL_ACCESS
suffix:semicolon
id|p_acl
op_assign
op_amp
id|reiserfs_i-&gt;i_acl_access
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACL_TYPE_DEFAULT
suffix:colon
id|name
op_assign
id|XATTR_NAME_ACL_DEFAULT
suffix:semicolon
id|p_acl
op_assign
op_amp
id|reiserfs_i-&gt;i_acl_default
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
id|ERR_PTR
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|IS_ERR
(paren
op_star
id|p_acl
)paren
)paren
(brace
r_if
c_cond
(paren
id|PTR_ERR
(paren
op_star
id|p_acl
)paren
op_eq
op_minus
id|ENODATA
)paren
r_return
l_int|NULL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
id|p_acl
op_ne
l_int|NULL
)paren
r_return
id|posix_acl_dup
(paren
op_star
id|p_acl
)paren
suffix:semicolon
id|size
op_assign
id|reiserfs_xattr_get
(paren
id|inode
comma
id|name
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|size
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|size
op_eq
op_minus
id|ENODATA
op_logical_or
id|size
op_eq
op_minus
id|ENOSYS
)paren
(brace
op_star
id|p_acl
op_assign
id|ERR_PTR
(paren
op_minus
id|ENODATA
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|ERR_PTR
(paren
id|size
)paren
suffix:semicolon
)brace
id|value
op_assign
id|kmalloc
(paren
id|size
comma
id|GFP_NOFS
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
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|retval
op_assign
id|reiserfs_xattr_get
c_func
(paren
id|inode
comma
id|name
comma
id|value
comma
id|size
)paren
suffix:semicolon
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
(brace
multiline_comment|/* This shouldn&squot;t actually happen as it should have&n;&t;&t;   been caught above.. but just in case */
id|acl
op_assign
l_int|NULL
suffix:semicolon
op_star
id|p_acl
op_assign
id|ERR_PTR
(paren
op_minus
id|ENODATA
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
(brace
id|acl
op_assign
id|ERR_PTR
c_func
(paren
id|retval
)paren
suffix:semicolon
)brace
r_else
(brace
id|acl
op_assign
id|posix_acl_from_disk
c_func
(paren
id|value
comma
id|retval
)paren
suffix:semicolon
op_star
id|p_acl
op_assign
id|posix_acl_dup
(paren
id|acl
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|value
)paren
suffix:semicolon
r_return
id|acl
suffix:semicolon
)brace
multiline_comment|/*&n; * Inode operation set_posix_acl().&n; *&n; * inode-&gt;i_sem: down&n; * BKL held [before 2.5.x]&n; */
r_int
DECL|function|reiserfs_set_acl
id|reiserfs_set_acl
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
r_char
op_star
id|name
suffix:semicolon
r_void
op_star
id|value
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|posix_acl
op_star
op_star
id|p_acl
suffix:semicolon
r_int
id|size
suffix:semicolon
r_int
id|error
suffix:semicolon
r_struct
id|reiserfs_inode_info
op_star
id|reiserfs_i
op_assign
id|REISERFS_I
c_func
(paren
id|inode
)paren
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
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|ACL_TYPE_ACCESS
suffix:colon
id|name
op_assign
id|XATTR_NAME_ACL_ACCESS
suffix:semicolon
id|p_acl
op_assign
op_amp
id|reiserfs_i-&gt;i_acl_access
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
id|name
op_assign
id|XATTR_NAME_ACL_DEFAULT
suffix:semicolon
id|p_acl
op_assign
op_amp
id|reiserfs_i-&gt;i_acl_default
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
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
id|value
op_assign
id|posix_acl_to_disk
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
id|error
op_assign
id|reiserfs_xattr_set
c_func
(paren
id|inode
comma
id|name
comma
id|value
comma
id|size
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|error
op_assign
id|reiserfs_xattr_del
(paren
id|inode
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
op_minus
id|ENODATA
)paren
(brace
multiline_comment|/* This may seem odd here, but it means that the ACL was set&n;                 * with a value representable with mode bits. If there was&n;                 * an ACL before, reiserfs_xattr_del already dirtied the inode.&n;                 */
id|mark_inode_dirty
(paren
id|inode
)paren
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
)brace
)brace
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
multiline_comment|/* Release the old one */
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
(paren
op_star
id|p_acl
)paren
op_logical_and
op_star
id|p_acl
)paren
id|posix_acl_release
(paren
op_star
id|p_acl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acl
op_eq
l_int|NULL
)paren
op_star
id|p_acl
op_assign
id|ERR_PTR
(paren
op_minus
id|ENODATA
)paren
suffix:semicolon
r_else
op_star
id|p_acl
op_assign
id|posix_acl_dup
(paren
id|acl
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/* dir-&gt;i_sem: down,&n; * inode is new and not released into the wild yet */
r_int
DECL|function|reiserfs_inherit_default_acl
id|reiserfs_inherit_default_acl
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
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|posix_acl
op_star
id|acl
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* ACLs only get applied to files and directories */
r_if
c_cond
(paren
id|S_ISLNK
(paren
id|inode-&gt;i_mode
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* ACLs can only be used on &quot;new&quot; objects, so if it&squot;s an old object&n;     * there is nothing to inherit from */
r_if
c_cond
(paren
id|get_inode_sd_version
(paren
id|dir
)paren
op_eq
id|STAT_DATA_V1
)paren
r_goto
id|apply_umask
suffix:semicolon
multiline_comment|/* Don&squot;t apply ACLs to objects in the .reiserfs_priv tree.. This&n;     * would be useless since permissions are ignored, and a pain because&n;     * it introduces locking cycles */
r_if
c_cond
(paren
id|is_reiserfs_priv_object
(paren
id|dir
)paren
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
id|i_priv_object
suffix:semicolon
r_goto
id|apply_umask
suffix:semicolon
)brace
id|acl
op_assign
id|reiserfs_get_acl
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
(paren
id|acl
)paren
)paren
(brace
r_if
c_cond
(paren
id|PTR_ERR
(paren
id|acl
)paren
op_eq
op_minus
id|ENODATA
)paren
r_goto
id|apply_umask
suffix:semicolon
r_return
id|PTR_ERR
(paren
id|acl
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acl
)paren
(brace
r_struct
id|posix_acl
op_star
id|acl_copy
suffix:semicolon
id|mode_t
id|mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
r_int
id|need_acl
suffix:semicolon
multiline_comment|/* Copy the default ACL to the default ACL of a new directory */
r_if
c_cond
(paren
id|S_ISDIR
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|err
op_assign
id|reiserfs_set_acl
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
id|err
)paren
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/* Now we reconcile the new ACL and the mode,&n;           potentially modifying both */
id|acl_copy
op_assign
id|posix_acl_clone
(paren
id|acl
comma
id|GFP_NOFS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acl_copy
)paren
(brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
id|need_acl
op_assign
id|posix_acl_create_masq
(paren
id|acl_copy
comma
op_amp
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|need_acl
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|mode
op_ne
id|inode-&gt;i_mode
)paren
(brace
id|inode-&gt;i_mode
op_assign
id|mode
suffix:semicolon
)brace
multiline_comment|/* If we need an ACL.. */
r_if
c_cond
(paren
id|need_acl
OG
l_int|0
)paren
(brace
id|err
op_assign
id|reiserfs_set_acl
(paren
id|inode
comma
id|ACL_TYPE_ACCESS
comma
id|acl_copy
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|cleanup_copy
suffix:semicolon
)brace
)brace
id|cleanup_copy
suffix:colon
id|posix_acl_release
(paren
id|acl_copy
)paren
suffix:semicolon
id|cleanup
suffix:colon
id|posix_acl_release
(paren
id|acl
)paren
suffix:semicolon
)brace
r_else
(brace
id|apply_umask
suffix:colon
multiline_comment|/* no ACL, apply umask */
id|inode-&gt;i_mode
op_and_assign
op_complement
id|current-&gt;fs-&gt;umask
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* Looks up and caches the result of the default ACL.&n; * We do this so that we don&squot;t need to carry the xattr_sem into&n; * reiserfs_new_inode if we don&squot;t need to */
r_int
DECL|function|reiserfs_cache_default_acl
id|reiserfs_cache_default_acl
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|reiserfs_posixacl
(paren
id|inode-&gt;i_sb
)paren
op_logical_and
op_logical_neg
id|is_reiserfs_priv_object
(paren
id|inode
)paren
)paren
(brace
r_struct
id|posix_acl
op_star
id|acl
suffix:semicolon
id|reiserfs_read_lock_xattr_i
(paren
id|inode
)paren
suffix:semicolon
id|reiserfs_read_lock_xattrs
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
id|acl
op_assign
id|reiserfs_get_acl
(paren
id|inode
comma
id|ACL_TYPE_DEFAULT
)paren
suffix:semicolon
id|reiserfs_read_unlock_xattrs
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
id|reiserfs_read_unlock_xattr_i
(paren
id|inode
)paren
suffix:semicolon
id|ret
op_assign
id|acl
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|posix_acl_release
(paren
id|acl
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
r_int
DECL|function|reiserfs_acl_chmod
id|reiserfs_acl_chmod
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
id|get_inode_sd_version
(paren
id|inode
)paren
op_eq
id|STAT_DATA_V1
op_logical_or
op_logical_neg
id|reiserfs_posixacl
c_func
(paren
id|inode-&gt;i_sb
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|reiserfs_read_lock_xattrs
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
id|acl
op_assign
id|reiserfs_get_acl
c_func
(paren
id|inode
comma
id|ACL_TYPE_ACCESS
)paren
suffix:semicolon
id|reiserfs_read_unlock_xattrs
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acl
)paren
r_return
l_int|0
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
id|clone
op_assign
id|posix_acl_clone
c_func
(paren
id|acl
comma
id|GFP_NOFS
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
(brace
r_int
id|lock
op_assign
op_logical_neg
id|has_xattr_dir
(paren
id|inode
)paren
suffix:semicolon
id|reiserfs_write_lock_xattr_i
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lock
)paren
id|reiserfs_write_lock_xattrs
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_else
id|reiserfs_read_lock_xattrs
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
id|error
op_assign
id|reiserfs_set_acl
c_func
(paren
id|inode
comma
id|ACL_TYPE_ACCESS
comma
id|clone
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lock
)paren
id|reiserfs_write_unlock_xattrs
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_else
id|reiserfs_read_unlock_xattrs
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
id|reiserfs_write_unlock_xattr_i
(paren
id|inode
)paren
suffix:semicolon
)brace
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
r_static
r_int
DECL|function|posix_acl_access_get
id|posix_acl_access_get
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
id|strlen
c_func
(paren
id|name
)paren
op_ne
r_sizeof
(paren
id|XATTR_NAME_ACL_ACCESS
)paren
op_minus
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|xattr_get_acl
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
DECL|function|posix_acl_access_set
id|posix_acl_access_set
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
id|strlen
c_func
(paren
id|name
)paren
op_ne
r_sizeof
(paren
id|XATTR_NAME_ACL_ACCESS
)paren
op_minus
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|xattr_set_acl
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
DECL|function|posix_acl_access_del
id|posix_acl_access_del
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
)paren
(brace
r_struct
id|reiserfs_inode_info
op_star
id|reiserfs_i
op_assign
id|REISERFS_I
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|posix_acl
op_star
op_star
id|acl
op_assign
op_amp
id|reiserfs_i-&gt;i_acl_access
suffix:semicolon
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|name
)paren
op_ne
r_sizeof
(paren
id|XATTR_NAME_ACL_ACCESS
)paren
op_minus
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
(paren
op_star
id|acl
)paren
op_logical_and
op_star
id|acl
)paren
(brace
id|posix_acl_release
(paren
op_star
id|acl
)paren
suffix:semicolon
op_star
id|acl
op_assign
id|ERR_PTR
(paren
op_minus
id|ENODATA
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|posix_acl_access_list
id|posix_acl_access_list
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
r_int
id|namelen
comma
r_char
op_star
id|out
)paren
(brace
r_int
id|len
op_assign
id|namelen
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|reiserfs_posixacl
(paren
id|inode-&gt;i_sb
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|out
)paren
id|memcpy
(paren
id|out
comma
id|name
comma
id|len
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|variable|posix_acl_access_handler
r_struct
id|reiserfs_xattr_handler
id|posix_acl_access_handler
op_assign
(brace
id|prefix
suffix:colon
id|XATTR_NAME_ACL_ACCESS
comma
id|get
suffix:colon
id|posix_acl_access_get
comma
id|set
suffix:colon
id|posix_acl_access_set
comma
id|del
suffix:colon
id|posix_acl_access_del
comma
id|list
suffix:colon
id|posix_acl_access_list
comma
)brace
suffix:semicolon
r_static
r_int
DECL|function|posix_acl_default_get
id|posix_acl_default_get
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
id|strlen
c_func
(paren
id|name
)paren
op_ne
r_sizeof
(paren
id|XATTR_NAME_ACL_DEFAULT
)paren
op_minus
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|xattr_get_acl
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
DECL|function|posix_acl_default_set
id|posix_acl_default_set
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
id|strlen
c_func
(paren
id|name
)paren
op_ne
r_sizeof
(paren
id|XATTR_NAME_ACL_DEFAULT
)paren
op_minus
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|xattr_set_acl
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
r_static
r_int
DECL|function|posix_acl_default_del
id|posix_acl_default_del
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
)paren
(brace
r_struct
id|reiserfs_inode_info
op_star
id|reiserfs_i
op_assign
id|REISERFS_I
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|posix_acl
op_star
op_star
id|acl
op_assign
op_amp
id|reiserfs_i-&gt;i_acl_default
suffix:semicolon
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|name
)paren
op_ne
r_sizeof
(paren
id|XATTR_NAME_ACL_DEFAULT
)paren
op_minus
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
(paren
op_star
id|acl
)paren
op_logical_and
op_star
id|acl
)paren
(brace
id|posix_acl_release
(paren
op_star
id|acl
)paren
suffix:semicolon
op_star
id|acl
op_assign
id|ERR_PTR
(paren
op_minus
id|ENODATA
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|posix_acl_default_list
id|posix_acl_default_list
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
r_int
id|namelen
comma
r_char
op_star
id|out
)paren
(brace
r_int
id|len
op_assign
id|namelen
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|reiserfs_posixacl
(paren
id|inode-&gt;i_sb
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|out
)paren
id|memcpy
(paren
id|out
comma
id|name
comma
id|len
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|variable|posix_acl_default_handler
r_struct
id|reiserfs_xattr_handler
id|posix_acl_default_handler
op_assign
(brace
id|prefix
suffix:colon
id|XATTR_NAME_ACL_DEFAULT
comma
id|get
suffix:colon
id|posix_acl_default_get
comma
id|set
suffix:colon
id|posix_acl_default_set
comma
id|del
suffix:colon
id|posix_acl_default_del
comma
id|list
suffix:colon
id|posix_acl_default_list
comma
)brace
suffix:semicolon
eof
