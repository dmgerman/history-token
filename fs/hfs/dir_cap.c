multiline_comment|/*&n; * Copyright (C) 1995-1997  Paul H. Hargrove&n; * This file may be distributed under the terms of the GNU General Public License.&n; *&n; * This file contains the inode_operations and file_operations&n; * structures for HFS directories under the CAP scheme.&n; *&n; * Based on the minix file system code, (C) 1991, 1992 by Linus Torvalds&n; *&n; * The source code distribution of the Columbia AppleTalk Package for&n; * UNIX, version 6.0, (CAP) was used as a specification of the&n; * location and format of files used by CAP&squot;s Aufs.  No code from CAP&n; * appears in hfs_fs.  hfs_fs is not a work ``derived&squot;&squot; from CAP in&n; * the sense of intellectual property law.&n; *&n; * &quot;XXX&quot; in a comment is a note to myself to consider changing something.&n; *&n; * In function preconditions the term &quot;valid&quot; applied to a pointer to&n; * a structure means that the pointer is non-NULL and the structure it&n; * points to has all fields initialized to consistent values.&n; */
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
id|cap_lookup
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
id|nameidata
op_star
)paren
suffix:semicolon
r_static
r_int
id|cap_readdir
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
multiline_comment|/*================ Global variables ================*/
DECL|macro|DOT_LEN
mdefine_line|#define DOT_LEN&t;&t;&t;1
DECL|macro|DOT_DOT_LEN
mdefine_line|#define DOT_DOT_LEN&t;&t;2
DECL|macro|DOT_RESOURCE_LEN
mdefine_line|#define DOT_RESOURCE_LEN&t;9
DECL|macro|DOT_FINDERINFO_LEN
mdefine_line|#define DOT_FINDERINFO_LEN&t;11
DECL|macro|DOT_ROOTINFO_LEN
mdefine_line|#define DOT_ROOTINFO_LEN&t;9
DECL|variable|hfs_cap_reserved1
r_const
r_struct
id|hfs_name
id|hfs_cap_reserved1
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
id|DOT_RESOURCE_LEN
comma
l_string|&quot;.resource&quot;
)brace
comma
(brace
id|DOT_FINDERINFO_LEN
comma
l_string|&quot;.finderinfo&quot;
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
DECL|variable|hfs_cap_reserved2
r_const
r_struct
id|hfs_name
id|hfs_cap_reserved2
(braket
)braket
op_assign
(brace
(brace
id|DOT_ROOTINFO_LEN
comma
l_string|&quot;.rootinfo&quot;
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
mdefine_line|#define DOT&t;&t;(&amp;hfs_cap_reserved1[0])
DECL|macro|DOT_DOT
mdefine_line|#define DOT_DOT&t;&t;(&amp;hfs_cap_reserved1[1])
DECL|macro|DOT_RESOURCE
mdefine_line|#define DOT_RESOURCE&t;(&amp;hfs_cap_reserved1[2])
DECL|macro|DOT_FINDERINFO
mdefine_line|#define DOT_FINDERINFO&t;(&amp;hfs_cap_reserved1[3])
DECL|macro|DOT_ROOTINFO
mdefine_line|#define DOT_ROOTINFO&t;(&amp;hfs_cap_reserved2[0])
DECL|variable|hfs_cap_dir_operations
r_struct
id|file_operations
id|hfs_cap_dir_operations
op_assign
(brace
dot
id|read
op_assign
id|generic_read_dir
comma
dot
id|readdir
op_assign
id|cap_readdir
comma
dot
id|fsync
op_assign
id|file_fsync
comma
)brace
suffix:semicolon
DECL|variable|hfs_cap_ndir_inode_operations
r_struct
id|inode_operations
id|hfs_cap_ndir_inode_operations
op_assign
(brace
dot
id|create
op_assign
id|hfs_create
comma
dot
id|lookup
op_assign
id|cap_lookup
comma
dot
id|unlink
op_assign
id|hfs_unlink
comma
dot
id|mkdir
op_assign
id|hfs_mkdir
comma
dot
id|rmdir
op_assign
id|hfs_rmdir
comma
dot
id|rename
op_assign
id|hfs_rename
comma
dot
id|setattr
op_assign
id|hfs_notify_change
comma
)brace
suffix:semicolon
DECL|variable|hfs_cap_fdir_inode_operations
r_struct
id|inode_operations
id|hfs_cap_fdir_inode_operations
op_assign
(brace
dot
id|lookup
op_assign
id|cap_lookup
comma
dot
id|setattr
op_assign
id|hfs_notify_change
comma
)brace
suffix:semicolon
DECL|variable|hfs_cap_rdir_inode_operations
r_struct
id|inode_operations
id|hfs_cap_rdir_inode_operations
op_assign
(brace
dot
id|create
op_assign
id|hfs_create
comma
dot
id|lookup
op_assign
id|cap_lookup
comma
dot
id|setattr
op_assign
id|hfs_notify_change
comma
)brace
suffix:semicolon
multiline_comment|/*================ File-local functions ================*/
multiline_comment|/*&n; * cap_lookup()&n; *&n; * This is the lookup() entry in the inode_operations structure for&n; * HFS directories in the CAP scheme.  The purpose is to generate the&n; * inode corresponding to an entry in a directory, given the inode for&n; * the directory and the name (and its length) of the entry.&n; */
DECL|function|cap_lookup
r_static
r_struct
id|dentry
op_star
id|cap_lookup
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
id|ino_t
id|dtype
suffix:semicolon
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
id|dtype
op_assign
id|HFS_ITYPE
c_func
(paren
id|dir-&gt;i_ino
)paren
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
multiline_comment|/* Check for epecial directories if in a normal directory.&n;&t;   Note that cap_dupdir() does an iput(dir). */
r_if
c_cond
(paren
id|dtype
op_eq
id|HFS_CAP_NDIR
)paren
(brace
multiline_comment|/* Check for &quot;.resource&quot;, &quot;.finderinfo&quot; and &quot;.rootinfo&quot; */
r_if
c_cond
(paren
id|hfs_streq
c_func
(paren
id|cname.Name
comma
id|cname.Len
comma
id|DOT_RESOURCE-&gt;Name
comma
id|DOT_RESOURCE_LEN
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
id|HFS_CAP_RDIR
comma
id|dentry
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|hfs_streq
c_func
(paren
id|cname.Name
comma
id|cname.Len
comma
id|DOT_FINDERINFO-&gt;Name
comma
id|DOT_FINDERINFO_LEN
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
id|HFS_CAP_FDIR
comma
id|dentry
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_else
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
id|DOT_ROOTINFO-&gt;Name
comma
id|DOT_ROOTINFO_LEN
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
id|HFS_CAP_FNDR
comma
id|dentry
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
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
id|HFS_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|file_type
comma
id|dentry
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t return a resource fork for a directory */
r_if
c_cond
(paren
id|inode
op_logical_and
(paren
id|dtype
op_eq
id|HFS_CAP_RDIR
)paren
op_logical_and
(paren
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|entry-&gt;type
op_eq
id|HFS_CDR_DIR
)paren
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
multiline_comment|/* this does an hfs_cat_put */
id|inode
op_assign
l_int|NULL
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
multiline_comment|/*&n; * cap_readdir()&n; *&n; * This is the readdir() entry in the file_operations structure for&n; * HFS directories in the CAP scheme.  The purpose is to enumerate the&n; * entries in a directory, given the inode of the directory and a&n; * (struct file *), the &squot;f_pos&squot; field of which indicates the location&n; * in the directory.  The (struct file *) is updated so that the next&n; * call with the same &squot;dir&squot; and &squot;filp&squot; arguments will produce the next&n; * directory entry.  The entries are returned in &squot;dirent&squot;, which is&n; * &quot;filled-in&quot; by calling filldir().  This allows the same readdir()&n; * function be used for different dirent formats.  We try to read in&n; * as many entries as we can before filldir() refuses to take any more.&n; *&n; * XXX: In the future it may be a good idea to consider not generating&n; * metadata files for covered directories since the data doesn&squot;t&n; * correspond to the mounted directory.&t; However this requires an&n; * iget() for every directory which could be considered an excessive&n; * amount of overhead.&t;Since the inode for a mount point is always&n; * in-core this is another argument for a call to get an inode if it&n; * is in-core or NULL if it is not.&n; */
DECL|function|cap_readdir
r_static
r_int
id|cap_readdir
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
id|ino_t
id|type
suffix:semicolon
r_int
id|skip_dirs
suffix:semicolon
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
id|lock_kernel
c_func
(paren
)paren
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
id|type
op_assign
id|HFS_ITYPE
c_func
(paren
id|dir-&gt;i_ino
)paren
suffix:semicolon
id|skip_dirs
op_assign
(paren
id|type
op_eq
id|HFS_CAP_RDIR
)paren
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
r_goto
id|out
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
id|hfs_u32
id|cnid
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|HFS_CAP_NDIR
)paren
(brace
id|cnid
op_assign
id|hfs_get_nl
c_func
(paren
id|entry-&gt;key.ParID
)paren
suffix:semicolon
)brace
r_else
(brace
id|cnid
op_assign
id|entry-&gt;cnid
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
id|DOT_DOT-&gt;Name
comma
id|DOT_DOT_LEN
comma
l_int|1
comma
id|ntohl
c_func
(paren
id|cnid
)paren
comma
id|DT_DIR
)paren
)paren
(brace
r_goto
id|out
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
l_int|3
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
id|filp-&gt;f_pos
op_minus
l_int|2
comma
op_amp
id|cnid
comma
op_amp
id|type
)paren
)paren
(brace
r_goto
id|out
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
l_int|3
)paren
)paren
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
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|skip_dirs
op_logical_or
(paren
id|type
op_ne
id|HFS_CDR_DIR
)paren
)paren
(brace
id|ino_t
id|ino
suffix:semicolon
r_int
r_int
id|len
suffix:semicolon
r_int
r_char
id|tmp_name
(braket
id|HFS_NAMEMAX
)braket
suffix:semicolon
id|ino
op_assign
id|ntohl
c_func
(paren
id|cnid
)paren
op_or
id|HFS_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|file_type
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
r_goto
id|out
suffix:semicolon
)brace
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
l_int|3
)paren
)paren
(brace
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
(paren
id|type
op_eq
id|HFS_CAP_NDIR
)paren
)paren
(brace
multiline_comment|/* In root dir last-2 entry is for &quot;.rootinfo&quot; */
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
id|DOT_ROOTINFO-&gt;Name
comma
id|DOT_ROOTINFO_LEN
comma
id|filp-&gt;f_pos
comma
id|ntohl
c_func
(paren
id|entry-&gt;cnid
)paren
op_or
id|HFS_CAP_FNDR
comma
id|DT_UNKNOWN
)paren
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
)brace
op_increment
id|filp-&gt;f_pos
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
l_int|2
)paren
)paren
(brace
r_if
c_cond
(paren
id|type
op_eq
id|HFS_CAP_NDIR
)paren
(brace
multiline_comment|/* In normal dirs last-1 entry is for &quot;.finderinfo&quot; */
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
id|DOT_FINDERINFO-&gt;Name
comma
id|DOT_FINDERINFO_LEN
comma
id|filp-&gt;f_pos
comma
id|ntohl
c_func
(paren
id|entry-&gt;cnid
)paren
op_or
id|HFS_CAP_FDIR
comma
id|DT_UNKNOWN
)paren
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
)brace
op_increment
id|filp-&gt;f_pos
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
id|type
op_eq
id|HFS_CAP_NDIR
)paren
(brace
multiline_comment|/* In normal dirs last entry is for &quot;.resource&quot; */
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
id|DOT_RESOURCE-&gt;Name
comma
id|DOT_RESOURCE_LEN
comma
id|filp-&gt;f_pos
comma
id|ntohl
c_func
(paren
id|entry-&gt;cnid
)paren
op_or
id|HFS_CAP_RDIR
comma
id|DT_UNKNOWN
)paren
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
)brace
op_increment
id|filp-&gt;f_pos
suffix:semicolon
)brace
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* due to the dcache caching negative dentries for non-existent files,&n; * we need to drop those entries when a file silently gets created.&n; * as far as i can tell, the calls that need to do this are the file&n; * related calls (create, rename, and mknod). the directory calls&n; * should be immune. the relevant calls in dir.c call drop_dentry &n; * upon successful completion. */
DECL|function|hfs_cap_drop_dentry
r_void
id|hfs_cap_drop_dentry
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
r_if
c_cond
(paren
id|type
op_eq
id|HFS_CAP_DATA
)paren
(brace
multiline_comment|/* given name */
id|hfs_drop_special
c_func
(paren
id|dentry-&gt;d_parent
comma
id|DOT_FINDERINFO
comma
id|dentry
)paren
suffix:semicolon
id|hfs_drop_special
c_func
(paren
id|dentry-&gt;d_parent
comma
id|DOT_RESOURCE
comma
id|dentry
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|dentry
op_star
id|de
suffix:semicolon
multiline_comment|/* given {.resource,.finderinfo}/name, look for name */
r_if
c_cond
(paren
(paren
id|de
op_assign
id|hfs_lookup_dentry
c_func
(paren
id|dentry-&gt;d_parent-&gt;d_parent
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
)paren
)paren
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
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|HFS_CAP_RSRC
suffix:colon
multiline_comment|/* given .resource/name */
multiline_comment|/* look for .finderinfo/name */
id|hfs_drop_special
c_func
(paren
id|dentry-&gt;d_parent-&gt;d_parent
comma
id|DOT_FINDERINFO
comma
id|dentry
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HFS_CAP_FNDR
suffix:colon
multiline_comment|/* given .finderinfo/name. i don&squot;t this &n;&t;&t;&t;* happens. */
multiline_comment|/* look for .resource/name */
id|hfs_drop_special
c_func
(paren
id|dentry-&gt;d_parent-&gt;d_parent
comma
id|DOT_RESOURCE
comma
id|dentry
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
eof
