multiline_comment|/*&n; * linux/fs/hfs/dir_dbl.c&n; *&n; * Copyright (C) 1995-1997  Paul H. Hargrove&n; * This file may be distributed under the terms of the GNU General Public License.&n; *&n; * This file contains the inode_operations and file_operations&n; * structures for HFS directories.&n; *&n; * Based on the minix file system code, (C) 1991, 1992 by Linus Torvalds&n; *&n; * &quot;XXX&quot; in a comment is a note to myself to consider changing something.&n; *&n; * In function preconditions the term &quot;valid&quot; applied to a pointer to&n; * a structure means that the pointer is non-NULL and the structure it&n; * points to has all fields initialized to consistent values.&n; */
macro_line|#include &quot;hfs.h&quot;
macro_line|#include &lt;linux/hfs_fs_sb.h&gt;
macro_line|#include &lt;linux/hfs_fs_i.h&gt;
macro_line|#include &lt;linux/hfs_fs.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
multiline_comment|/*================ Forward declarations ================*/
r_static
r_struct
id|dentry
op_star
id|dbl_lookup
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_static
r_int
id|dbl_readdir
c_func
(paren
r_struct
id|file
op_star
comma
r_void
op_star
comma
id|filldir_t
)paren
suffix:semicolon
r_static
r_int
id|dbl_create
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|dbl_mkdir
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|dbl_unlink
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_static
r_int
id|dbl_rmdir
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_static
r_int
id|dbl_rename
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
comma
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
multiline_comment|/*================ Global variables ================*/
DECL|macro|DOT_LEN
mdefine_line|#define DOT_LEN&t;&t;&t;1
DECL|macro|DOT_DOT_LEN
mdefine_line|#define DOT_DOT_LEN&t;&t;2
DECL|macro|ROOTINFO_LEN
mdefine_line|#define ROOTINFO_LEN&t;&t;8
DECL|macro|PCNT_ROOTINFO_LEN
mdefine_line|#define PCNT_ROOTINFO_LEN&t;9
DECL|variable|hfs_dbl_reserved1
r_const
r_struct
id|hfs_name
id|hfs_dbl_reserved1
(braket
)braket
op_assign
(brace
(brace
id|DOT_LEN
comma
l_string|&quot;.&quot;
)brace
comma
(brace
id|DOT_DOT_LEN
comma
l_string|&quot;..&quot;
)brace
comma
(brace
l_int|0
comma
l_string|&quot;&quot;
)brace
comma
)brace
suffix:semicolon
DECL|variable|hfs_dbl_reserved2
r_const
r_struct
id|hfs_name
id|hfs_dbl_reserved2
(braket
)braket
op_assign
(brace
(brace
id|ROOTINFO_LEN
comma
l_string|&quot;RootInfo&quot;
)brace
comma
(brace
id|PCNT_ROOTINFO_LEN
comma
l_string|&quot;%RootInfo&quot;
)brace
comma
(brace
l_int|0
comma
l_string|&quot;&quot;
)brace
comma
)brace
suffix:semicolon
DECL|macro|DOT
mdefine_line|#define DOT&t;&t;(&amp;hfs_dbl_reserved1[0])
DECL|macro|DOT_DOT
mdefine_line|#define DOT_DOT&t;&t;(&amp;hfs_dbl_reserved1[1])
DECL|macro|ROOTINFO
mdefine_line|#define ROOTINFO&t;(&amp;hfs_dbl_reserved2[0])
DECL|macro|PCNT_ROOTINFO
mdefine_line|#define PCNT_ROOTINFO&t;(&amp;hfs_dbl_reserved2[1])
DECL|variable|hfs_dbl_dir_operations
r_struct
id|file_operations
id|hfs_dbl_dir_operations
op_assign
(brace
id|read
suffix:colon
id|generic_read_dir
comma
id|readdir
suffix:colon
id|dbl_readdir
comma
id|fsync
suffix:colon
id|file_fsync
comma
)brace
suffix:semicolon
DECL|variable|hfs_dbl_dir_inode_operations
r_struct
id|inode_operations
id|hfs_dbl_dir_inode_operations
op_assign
(brace
id|create
suffix:colon
id|dbl_create
comma
id|lookup
suffix:colon
id|dbl_lookup
comma
id|unlink
suffix:colon
id|dbl_unlink
comma
id|mkdir
suffix:colon
id|dbl_mkdir
comma
id|rmdir
suffix:colon
id|dbl_rmdir
comma
id|rename
suffix:colon
id|dbl_rename
comma
id|setattr
suffix:colon
id|hfs_notify_change
comma
)brace
suffix:semicolon
multiline_comment|/*================ File-local functions ================*/
multiline_comment|/*&n; * is_hdr()&n; */
DECL|function|is_hdr
r_static
r_int
id|is_hdr
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|len
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|name
(braket
l_int|0
)braket
op_eq
l_char|&squot;%&squot;
)paren
(brace
r_struct
id|hfs_cat_entry
op_star
id|entry
op_assign
id|HFS_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|entry
suffix:semicolon
r_struct
id|hfs_cat_entry
op_star
id|victim
suffix:semicolon
r_struct
id|hfs_name
id|cname
suffix:semicolon
r_struct
id|hfs_cat_key
id|key
suffix:semicolon
id|hfs_nameout
c_func
(paren
id|dir
comma
op_amp
id|cname
comma
id|name
op_plus
l_int|1
comma
id|len
op_minus
l_int|1
)paren
suffix:semicolon
id|hfs_cat_build_key
c_func
(paren
id|entry-&gt;cnid
comma
op_amp
id|cname
comma
op_amp
id|key
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|victim
op_assign
id|hfs_cat_get
c_func
(paren
id|entry-&gt;mdb
comma
op_amp
id|key
)paren
)paren
)paren
(brace
id|hfs_cat_put
c_func
(paren
id|victim
)paren
suffix:semicolon
id|retval
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * dbl_lookup()&n; *&n; * This is the lookup() entry in the inode_operations structure for&n; * HFS directories in the AppleDouble scheme.  The purpose is to&n; * generate the inode corresponding to an entry in a directory, given&n; * the inode for the directory and the name (and its length) of the&n; * entry.&n; */
DECL|function|dbl_lookup
r_static
r_struct
id|dentry
op_star
id|dbl_lookup
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
id|hfs_name
id|cname
suffix:semicolon
r_struct
id|hfs_cat_entry
op_star
id|entry
suffix:semicolon
r_struct
id|hfs_cat_key
id|key
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
l_int|NULL
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|dentry-&gt;d_op
op_assign
op_amp
id|hfs_dentry_operations
suffix:semicolon
id|entry
op_assign
id|HFS_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|entry
suffix:semicolon
multiline_comment|/* Perform name-mangling */
id|hfs_nameout
c_func
(paren
id|dir
comma
op_amp
id|cname
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
)paren
suffix:semicolon
multiline_comment|/* no need to check for &quot;.&quot;  or &quot;..&quot; */
multiline_comment|/* Check for &quot;%RootInfo&quot; if in the root directory. */
r_if
c_cond
(paren
(paren
id|entry-&gt;cnid
op_eq
id|htonl
c_func
(paren
id|HFS_ROOT_CNID
)paren
)paren
op_logical_and
id|hfs_streq
c_func
(paren
id|cname.Name
comma
id|cname.Len
comma
id|PCNT_ROOTINFO-&gt;Name
comma
id|PCNT_ROOTINFO_LEN
)paren
)paren
(brace
op_increment
id|entry-&gt;count
suffix:semicolon
multiline_comment|/* __hfs_iget() eats one */
id|inode
op_assign
id|hfs_iget
c_func
(paren
id|entry
comma
id|HFS_DBL_HDR
comma
id|dentry
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
multiline_comment|/* Do an hfs_iget() on the mangled name. */
id|hfs_cat_build_key
c_func
(paren
id|entry-&gt;cnid
comma
op_amp
id|cname
comma
op_amp
id|key
)paren
suffix:semicolon
id|inode
op_assign
id|hfs_iget
c_func
(paren
id|hfs_cat_get
c_func
(paren
id|entry-&gt;mdb
comma
op_amp
id|key
)paren
comma
id|HFS_DBL_NORM
comma
id|dentry
)paren
suffix:semicolon
multiline_comment|/* Try as a header if not found and first character is &squot;%&squot; */
r_if
c_cond
(paren
op_logical_neg
id|inode
op_logical_and
(paren
id|dentry-&gt;d_name.name
(braket
l_int|0
)braket
op_eq
l_char|&squot;%&squot;
)paren
)paren
(brace
id|hfs_nameout
c_func
(paren
id|dir
comma
op_amp
id|cname
comma
id|dentry-&gt;d_name.name
op_plus
l_int|1
comma
id|dentry-&gt;d_name.len
op_minus
l_int|1
)paren
suffix:semicolon
id|hfs_cat_build_key
c_func
(paren
id|entry-&gt;cnid
comma
op_amp
id|cname
comma
op_amp
id|key
)paren
suffix:semicolon
id|inode
op_assign
id|hfs_iget
c_func
(paren
id|hfs_cat_get
c_func
(paren
id|entry-&gt;mdb
comma
op_amp
id|key
)paren
comma
id|HFS_DBL_HDR
comma
id|dentry
)paren
suffix:semicolon
)brace
id|done
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
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
multiline_comment|/*&n; * dbl_readdir()&n; *&n; * This is the readdir() entry in the file_operations structure for&n; * HFS directories in the AppleDouble scheme.  The purpose is to&n; * enumerate the entries in a directory, given the inode of the&n; * directory and a (struct file *), the &squot;f_pos&squot; field of which&n; * indicates the location in the directory.  The (struct file *) is&n; * updated so that the next call with the same &squot;dir&squot; and &squot;filp&squot;&n; * arguments will produce the next directory entry.  The entries are&n; * returned in &squot;dirent&squot;, which is &quot;filled-in&quot; by calling filldir().&n; * This allows the same readdir() function be used for different&n; * formats.  We try to read in as many entries as we can before&n; * filldir() refuses to take any more.&n; *&n; * XXX: In the future it may be a good idea to consider not generating&n; * metadata files for covered directories since the data doesn&squot;t&n; * correspond to the mounted directory.&t; However this requires an&n; * iget() for every directory which could be considered an excessive&n; * amount of overhead.&t;Since the inode for a mount point is always&n; * in-core this is another argument for a call to get an inode if it&n; * is in-core or NULL if it is not.&n; */
DECL|function|dbl_readdir
r_static
r_int
id|dbl_readdir
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|dirent
comma
id|filldir_t
id|filldir
)paren
(brace
r_struct
id|hfs_brec
id|brec
suffix:semicolon
r_struct
id|hfs_cat_entry
op_star
id|entry
suffix:semicolon
r_struct
id|inode
op_star
id|dir
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|entry
op_assign
id|HFS_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|entry
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_pos
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Entry 0 is for &quot;.&quot; */
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
id|DOT-&gt;Name
comma
id|DOT_LEN
comma
l_int|0
comma
id|dir-&gt;i_ino
comma
id|DT_DIR
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|filp-&gt;f_pos
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|filp-&gt;f_pos
op_eq
l_int|1
)paren
(brace
multiline_comment|/* Entry 1 is for &quot;..&quot; */
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
id|DOT_DOT-&gt;Name
comma
id|DOT_DOT_LEN
comma
l_int|1
comma
id|hfs_get_hl
c_func
(paren
id|entry-&gt;key.ParID
)paren
comma
id|DT_DIR
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|filp-&gt;f_pos
op_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|filp-&gt;f_pos
OL
(paren
id|dir-&gt;i_size
op_minus
l_int|1
)paren
)paren
(brace
id|hfs_u32
id|cnid
suffix:semicolon
id|hfs_u8
id|type
suffix:semicolon
r_if
c_cond
(paren
id|hfs_cat_open
c_func
(paren
id|entry
comma
op_amp
id|brec
)paren
op_logical_or
id|hfs_cat_next
c_func
(paren
id|entry
comma
op_amp
id|brec
comma
(paren
id|filp-&gt;f_pos
op_minus
l_int|1
)paren
op_rshift
l_int|1
comma
op_amp
id|cnid
comma
op_amp
id|type
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_while
c_loop
(paren
id|filp-&gt;f_pos
OL
(paren
id|dir-&gt;i_size
op_minus
l_int|1
)paren
)paren
(brace
r_int
r_char
id|tmp_name
(braket
id|HFS_NAMEMAX
op_plus
l_int|1
)braket
suffix:semicolon
id|ino_t
id|ino
suffix:semicolon
r_int
id|is_hdr
op_assign
(paren
id|filp-&gt;f_pos
op_amp
l_int|1
)paren
suffix:semicolon
r_int
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|is_hdr
)paren
(brace
id|ino
op_assign
id|ntohl
c_func
(paren
id|cnid
)paren
op_or
id|HFS_DBL_HDR
suffix:semicolon
id|tmp_name
(braket
l_int|0
)braket
op_assign
l_char|&squot;%&squot;
suffix:semicolon
id|len
op_assign
l_int|1
op_plus
id|hfs_namein
c_func
(paren
id|dir
comma
id|tmp_name
op_plus
l_int|1
comma
op_amp
(paren
(paren
r_struct
id|hfs_cat_key
op_star
)paren
id|brec.key
)paren
op_member_access_from_pointer
id|CName
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|hfs_cat_next
c_func
(paren
id|entry
comma
op_amp
id|brec
comma
l_int|1
comma
op_amp
id|cnid
comma
op_amp
id|type
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|ino
op_assign
id|ntohl
c_func
(paren
id|cnid
)paren
suffix:semicolon
id|len
op_assign
id|hfs_namein
c_func
(paren
id|dir
comma
id|tmp_name
comma
op_amp
(paren
(paren
r_struct
id|hfs_cat_key
op_star
)paren
id|brec.key
)paren
op_member_access_from_pointer
id|CName
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
id|tmp_name
comma
id|len
comma
id|filp-&gt;f_pos
comma
id|ino
comma
id|DT_UNKNOWN
)paren
)paren
(brace
id|hfs_cat_close
c_func
(paren
id|entry
comma
op_amp
id|brec
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_increment
id|filp-&gt;f_pos
suffix:semicolon
)brace
id|hfs_cat_close
c_func
(paren
id|entry
comma
op_amp
id|brec
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|filp-&gt;f_pos
op_eq
(paren
id|dir-&gt;i_size
op_minus
l_int|1
)paren
)paren
(brace
r_if
c_cond
(paren
id|entry-&gt;cnid
op_eq
id|htonl
c_func
(paren
id|HFS_ROOT_CNID
)paren
)paren
(brace
multiline_comment|/* In root dir last entry is for &quot;%RootInfo&quot; */
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
id|PCNT_ROOTINFO-&gt;Name
comma
id|PCNT_ROOTINFO_LEN
comma
id|filp-&gt;f_pos
comma
id|ntohl
c_func
(paren
id|entry-&gt;cnid
)paren
op_or
id|HFS_DBL_HDR
comma
id|DT_UNKNOWN
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
op_increment
id|filp-&gt;f_pos
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * dbl_create()&n; *&n; * This is the create() entry in the inode_operations structure for&n; * AppleDouble directories.  The purpose is to create a new file in&n; * a directory and return a corresponding inode, given the inode for&n; * the directory and the name (and its length) of the new file.&n; */
DECL|function|dbl_create
r_static
r_int
id|dbl_create
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
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|is_hdr
c_func
(paren
id|dir
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
)paren
)paren
(brace
id|error
op_assign
op_minus
id|EEXIST
suffix:semicolon
)brace
r_else
(brace
id|error
op_assign
id|hfs_create
c_func
(paren
id|dir
comma
id|dentry
comma
id|mode
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * dbl_mkdir()&n; *&n; * This is the mkdir() entry in the inode_operations structure for&n; * AppleDouble directories.  The purpose is to create a new directory&n; * in a directory, given the inode for the parent directory and the&n; * name (and its length) of the new directory.&n; */
DECL|function|dbl_mkdir
r_static
r_int
id|dbl_mkdir
c_func
(paren
r_struct
id|inode
op_star
id|parent
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
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|is_hdr
c_func
(paren
id|parent
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
)paren
)paren
(brace
id|error
op_assign
op_minus
id|EEXIST
suffix:semicolon
)brace
r_else
(brace
id|error
op_assign
id|hfs_mkdir
c_func
(paren
id|parent
comma
id|dentry
comma
id|mode
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * dbl_unlink()&n; *&n; * This is the unlink() entry in the inode_operations structure for&n; * AppleDouble directories.  The purpose is to delete an existing&n; * file, given the inode for the parent directory and the name&n; * (and its length) of the existing file.&n; */
DECL|function|dbl_unlink
r_static
r_int
id|dbl_unlink
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
r_int
id|error
suffix:semicolon
id|error
op_assign
id|hfs_unlink
c_func
(paren
id|dir
comma
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_eq
op_minus
id|ENOENT
)paren
op_logical_and
id|is_hdr
c_func
(paren
id|dir
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
)paren
)paren
(brace
id|error
op_assign
op_minus
id|EPERM
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * dbl_rmdir()&n; *&n; * This is the rmdir() entry in the inode_operations structure for&n; * AppleDouble directories.  The purpose is to delete an existing&n; * directory, given the inode for the parent directory and the name&n; * (and its length) of the existing directory.&n; */
DECL|function|dbl_rmdir
r_static
r_int
id|dbl_rmdir
c_func
(paren
r_struct
id|inode
op_star
id|parent
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_int
id|error
suffix:semicolon
id|error
op_assign
id|hfs_rmdir
c_func
(paren
id|parent
comma
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_eq
op_minus
id|ENOENT
)paren
op_logical_and
id|is_hdr
c_func
(paren
id|parent
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
)paren
)paren
(brace
id|error
op_assign
op_minus
id|ENOTDIR
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * dbl_rename()&n; *&n; * This is the rename() entry in the inode_operations structure for&n; * AppleDouble directories.  The purpose is to rename an existing&n; * file or directory, given the inode for the current directory and&n; * the name (and its length) of the existing file/directory and the&n; * inode for the new directory and the name (and its length) of the&n; * new file/directory.&n; * &n; * XXX: how do we handle must_be_dir?&n; */
DECL|function|dbl_rename
r_static
r_int
id|dbl_rename
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
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|is_hdr
c_func
(paren
id|new_dir
comma
id|new_dentry-&gt;d_name.name
comma
id|new_dentry-&gt;d_name.len
)paren
)paren
(brace
id|error
op_assign
op_minus
id|EPERM
suffix:semicolon
)brace
r_else
(brace
id|error
op_assign
id|hfs_rename
c_func
(paren
id|old_dir
comma
id|old_dentry
comma
id|new_dir
comma
id|new_dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_eq
op_minus
id|ENOENT
)paren
multiline_comment|/*&amp;&amp; !must_be_dir*/
op_logical_and
id|is_hdr
c_func
(paren
id|old_dir
comma
id|old_dentry-&gt;d_name.name
comma
id|old_dentry-&gt;d_name.len
)paren
)paren
(brace
id|error
op_assign
op_minus
id|EPERM
suffix:semicolon
)brace
)brace
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/* due to the dcache caching negative dentries for non-existent files,&n; * we need to drop those entries when a file silently gets created.&n; * as far as i can tell, the calls that need to do this are the file&n; * related calls (create, rename, and mknod). the directory calls&n; * should be immune. the relevant calls in dir.c call drop_dentry &n; * upon successful completion. */
DECL|function|hfs_dbl_drop_dentry
r_void
id|hfs_dbl_drop_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_const
id|ino_t
id|type
)paren
(brace
r_int
r_char
id|tmp_name
(braket
id|HFS_NAMEMAX
op_plus
l_int|1
)braket
suffix:semicolon
r_struct
id|dentry
op_star
id|de
op_assign
l_int|NULL
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|HFS_DBL_HDR
suffix:colon
multiline_comment|/* given %name, look for name. i don&squot;t think this happens. */
id|de
op_assign
id|hfs_lookup_dentry
c_func
(paren
id|dentry-&gt;d_parent
comma
id|dentry-&gt;d_name.name
op_plus
l_int|1
comma
id|dentry-&gt;d_name.len
op_minus
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HFS_DBL_DATA
suffix:colon
multiline_comment|/* given name, look for %name */
id|tmp_name
(braket
l_int|0
)braket
op_assign
l_char|&squot;%&squot;
suffix:semicolon
id|strncpy
c_func
(paren
id|tmp_name
op_plus
l_int|1
comma
id|dentry-&gt;d_name.name
comma
id|HFS_NAMELEN
op_minus
l_int|1
)paren
suffix:semicolon
id|de
op_assign
id|hfs_lookup_dentry
c_func
(paren
id|dentry-&gt;d_parent
comma
id|tmp_name
comma
id|dentry-&gt;d_name.len
op_plus
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|de
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|de-&gt;d_inode
)paren
id|d_drop
c_func
(paren
id|de
)paren
suffix:semicolon
id|dput
c_func
(paren
id|de
)paren
suffix:semicolon
)brace
)brace
eof
