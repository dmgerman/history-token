multiline_comment|/*&n; * linux/fs/hfs/inode.c&n; *&n; * Copyright (C) 1995-1997  Paul H. Hargrove&n; * This file may be distributed under the terms of the GNU General Public License.&n; *&n; * This file contains inode-related functions which do not depend on&n; * which scheme is being used to represent forks.&n; *&n; * Based on the minix file system code, (C) 1991, 1992 by Linus Torvalds&n; *&n; * &quot;XXX&quot; in a comment is a note to myself to consider changing something.&n; *&n; * In function preconditions the term &quot;valid&quot; applied to a pointer to&n; * a structure means that the pointer is non-NULL and the structure it&n; * points to has all fields initialized to consistent values.&n; */
macro_line|#include &quot;hfs.h&quot;
macro_line|#include &lt;linux/hfs_fs_sb.h&gt;
macro_line|#include &lt;linux/hfs_fs_i.h&gt;
macro_line|#include &lt;linux/hfs_fs.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
multiline_comment|/*================ Variable-like macros ================*/
DECL|macro|HFS_VALID_MODE_BITS
mdefine_line|#define HFS_VALID_MODE_BITS  (S_IFREG | S_IFDIR | S_IRWXUGO)
multiline_comment|/*================ File-local functions ================*/
multiline_comment|/*&n; * init_file_inode()&n; *&n; * Given an HFS catalog entry initialize an inode for a file.&n; */
DECL|function|init_file_inode
r_static
r_void
id|init_file_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|hfs_u8
id|fork
)paren
(brace
r_struct
id|hfs_fork
op_star
id|fk
suffix:semicolon
r_struct
id|hfs_cat_entry
op_star
id|entry
op_assign
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|entry
suffix:semicolon
r_if
c_cond
(paren
id|fork
op_eq
id|HFS_FK_DATA
)paren
(brace
id|inode-&gt;i_mode
op_assign
id|S_IRWXUGO
op_or
id|S_IFREG
suffix:semicolon
)brace
r_else
(brace
id|inode-&gt;i_mode
op_assign
id|S_IRUGO
op_or
id|S_IWUGO
op_or
id|S_IFREG
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fork
op_eq
id|HFS_FK_DATA
)paren
(brace
macro_line|#if 0 /* XXX: disable crlf translations for now */
id|hfs_u32
id|type
op_assign
id|hfs_get_nl
c_func
(paren
id|entry-&gt;info.file.finfo.fdType
)paren
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|convert
op_assign
(paren
(paren
id|HFS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|s_conv
op_eq
l_char|&squot;t&squot;
)paren
op_logical_or
(paren
(paren
id|HFS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|s_conv
op_eq
l_char|&squot;a&squot;
)paren
op_logical_and
(paren
(paren
id|type
op_eq
id|htonl
c_func
(paren
l_int|0x54455854
)paren
)paren
op_logical_or
multiline_comment|/* &quot;TEXT&quot; */
(paren
id|type
op_eq
id|htonl
c_func
(paren
l_int|0x7474726f
)paren
)paren
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* &quot;ttro&quot; */
macro_line|#else
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|convert
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|fk
op_assign
op_amp
id|entry-&gt;u.file.data_fork
suffix:semicolon
)brace
r_else
(brace
id|fk
op_assign
op_amp
id|entry-&gt;u.file.rsrc_fork
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|convert
op_assign
l_int|0
suffix:semicolon
)brace
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|fork
op_assign
id|fk
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|fk-&gt;lsize
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
id|fk-&gt;psize
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*================ Global functions ================*/
multiline_comment|/*&n; * hfs_put_inode()&n; *&n; * This is the put_inode() entry in the super_operations for HFS&n; * filesystems.  The purpose is to perform any filesystem-dependent &n; * cleanup necessary when the use-count of an inode falls to zero.&n; */
DECL|function|hfs_put_inode
r_void
id|hfs_put_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
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
id|inode
)paren
op_member_access_from_pointer
id|entry
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|hfs_cat_put
c_func
(paren
id|entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|inode-&gt;i_count
)paren
op_eq
l_int|1
)paren
(brace
r_struct
id|hfs_hdr_layout
op_star
id|tmp
op_assign
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|layout
suffix:semicolon
r_if
c_cond
(paren
id|tmp
)paren
(brace
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|layout
op_assign
l_int|NULL
suffix:semicolon
id|HFS_DELETE
c_func
(paren
id|tmp
)paren
suffix:semicolon
)brace
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_notify_change()&n; *&n; * Based very closely on fs/msdos/inode.c by Werner Almesberger&n; *&n; * This is the notify_change() field in the super_operations structure&n; * for HFS file systems.  The purpose is to take that changes made to&n; * an inode and apply then in a filesystem-dependent manner.  In this&n; * case the process has a few of tasks to do:&n; *  1) prevent changes to the i_uid and i_gid fields.&n; *  2) map file permissions to the closest allowable permissions&n; *  3) Since multiple Linux files can share the same on-disk inode under&n; *     HFS (for instance the data and resource forks of a file) a change&n; *     to permissions must be applied to all other in-core inodes which &n; *     correspond to the same HFS file.&n; */
DECL|enumerator|HFS_NORM
DECL|enumerator|HFS_HDR
DECL|enumerator|HFS_CAP
r_enum
(brace
id|HFS_NORM
comma
id|HFS_HDR
comma
id|HFS_CAP
)brace
suffix:semicolon
DECL|function|__hfs_notify_change
r_static
r_int
id|__hfs_notify_change
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|iattr
op_star
id|attr
comma
r_int
id|kind
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
id|hfs_cat_entry
op_star
id|entry
op_assign
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|entry
suffix:semicolon
r_struct
id|dentry
op_star
op_star
id|de
op_assign
id|entry-&gt;sys_entry
suffix:semicolon
r_struct
id|hfs_sb_info
op_star
id|hsb
op_assign
id|HFS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_int
id|error
op_assign
l_int|0
comma
id|i
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|error
op_assign
id|inode_change_ok
c_func
(paren
id|inode
comma
id|attr
)paren
suffix:semicolon
multiline_comment|/* basic permission checks */
r_if
c_cond
(paren
id|error
)paren
(brace
multiline_comment|/* Let netatalk&squot;s afpd think chmod() always succeeds */
r_if
c_cond
(paren
id|hsb-&gt;s_afpd
op_logical_and
(paren
id|attr-&gt;ia_valid
op_eq
(paren
id|ATTR_MODE
op_or
id|ATTR_CTIME
)paren
)paren
)paren
(brace
id|error
op_assign
l_int|0
suffix:semicolon
)brace
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* no uig/gid changes and limit which mode bits can be set */
r_if
c_cond
(paren
(paren
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_UID
)paren
op_logical_and
(paren
id|attr-&gt;ia_uid
op_ne
id|hsb-&gt;s_uid
)paren
)paren
op_logical_or
(paren
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_GID
)paren
op_logical_and
(paren
id|attr-&gt;ia_gid
op_ne
id|hsb-&gt;s_gid
)paren
)paren
op_logical_or
(paren
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_MODE
)paren
op_logical_and
(paren
(paren
(paren
id|entry-&gt;type
op_eq
id|HFS_CDR_DIR
)paren
op_logical_and
(paren
id|attr-&gt;ia_mode
op_ne
id|inode-&gt;i_mode
)paren
)paren
op_logical_or
(paren
id|attr-&gt;ia_mode
op_amp
op_complement
id|HFS_VALID_MODE_BITS
)paren
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|hsb-&gt;s_quiet
)paren
(brace
id|error
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|entry-&gt;type
op_eq
id|HFS_CDR_DIR
)paren
(brace
id|attr-&gt;ia_valid
op_and_assign
op_complement
id|ATTR_MODE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_MODE
)paren
(brace
multiline_comment|/* Only the &squot;w&squot; bits can ever change and only all together. */
r_if
c_cond
(paren
id|attr-&gt;ia_mode
op_amp
id|S_IWUSR
)paren
(brace
id|attr-&gt;ia_mode
op_assign
id|inode-&gt;i_mode
op_or
id|S_IWUGO
suffix:semicolon
)brace
r_else
(brace
id|attr-&gt;ia_mode
op_assign
id|inode-&gt;i_mode
op_amp
op_complement
id|S_IWUGO
suffix:semicolon
)brace
id|attr-&gt;ia_mode
op_and_assign
op_complement
id|hsb-&gt;s_umask
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Normal files handle size change in normal way.&n;&t; * Oddballs are served here.&n;&t; */
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_SIZE
)paren
(brace
r_if
c_cond
(paren
id|kind
op_eq
id|HFS_CAP
)paren
(brace
id|inode-&gt;i_size
op_assign
id|attr-&gt;ia_size
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_size
OG
id|HFS_FORK_MAX
)paren
id|inode-&gt;i_size
op_assign
id|HFS_FORK_MAX
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|attr-&gt;ia_valid
op_and_assign
op_complement
id|ATTR_SIZE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|kind
op_eq
id|HFS_HDR
)paren
(brace
id|hdr_truncate
c_func
(paren
id|inode
comma
id|attr-&gt;ia_size
)paren
suffix:semicolon
id|attr-&gt;ia_valid
op_and_assign
op_complement
id|ATTR_SIZE
suffix:semicolon
)brace
)brace
id|error
op_assign
id|inode_setattr
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
id|error
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* We wouldn&squot;t want to mess with the sizes of the other fork */
id|attr-&gt;ia_valid
op_and_assign
op_complement
id|ATTR_SIZE
suffix:semicolon
multiline_comment|/* We must change all in-core inodes corresponding to this file. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|de
(braket
id|i
)braket
op_logical_and
(paren
id|de
(braket
id|i
)braket
op_ne
id|dentry
)paren
)paren
(brace
id|inode_setattr
c_func
(paren
id|de
(braket
id|i
)braket
op_member_access_from_pointer
id|d_inode
comma
id|attr
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Change the catalog entry if needed */
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_MTIME
)paren
(brace
id|entry-&gt;modify_date
op_assign
id|hfs_u_to_mtime
c_func
(paren
id|inode-&gt;i_mtime
)paren
suffix:semicolon
id|hfs_cat_mark_dirty
c_func
(paren
id|entry
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_MODE
)paren
(brace
id|hfs_u8
id|new_flags
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_mode
op_amp
id|S_IWUSR
)paren
(brace
id|new_flags
op_assign
id|entry-&gt;u.file.flags
op_amp
op_complement
id|HFS_FIL_LOCK
suffix:semicolon
)brace
r_else
(brace
id|new_flags
op_assign
id|entry-&gt;u.file.flags
op_or
id|HFS_FIL_LOCK
suffix:semicolon
)brace
r_if
c_cond
(paren
id|new_flags
op_ne
id|entry-&gt;u.file.flags
)paren
(brace
id|entry-&gt;u.file.flags
op_assign
id|new_flags
suffix:semicolon
id|hfs_cat_mark_dirty
c_func
(paren
id|entry
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* size changes handled in hfs_extent_adj() */
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|hfs_notify_change
r_int
id|hfs_notify_change
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|iattr
op_star
id|attr
)paren
(brace
r_return
id|__hfs_notify_change
c_func
(paren
id|dentry
comma
id|attr
comma
id|HFS_NORM
)paren
suffix:semicolon
)brace
DECL|function|hfs_notify_change_cap
r_int
id|hfs_notify_change_cap
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|iattr
op_star
id|attr
)paren
(brace
r_return
id|__hfs_notify_change
c_func
(paren
id|dentry
comma
id|attr
comma
id|HFS_CAP
)paren
suffix:semicolon
)brace
DECL|function|hfs_notify_change_hdr
r_int
id|hfs_notify_change_hdr
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|iattr
op_star
id|attr
)paren
(brace
r_return
id|__hfs_notify_change
c_func
(paren
id|dentry
comma
id|attr
comma
id|HFS_HDR
)paren
suffix:semicolon
)brace
DECL|function|hfs_writepage
r_static
r_int
id|hfs_writepage
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_return
id|block_write_full_page
c_func
(paren
id|page
comma
id|hfs_get_block
)paren
suffix:semicolon
)brace
DECL|function|hfs_readpage
r_static
r_int
id|hfs_readpage
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_return
id|block_read_full_page
c_func
(paren
id|page
comma
id|hfs_get_block
)paren
suffix:semicolon
)brace
DECL|function|hfs_prepare_write
r_static
r_int
id|hfs_prepare_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
comma
r_int
id|from
comma
r_int
id|to
)paren
(brace
r_return
id|cont_prepare_write
c_func
(paren
id|page
comma
id|from
comma
id|to
comma
id|hfs_get_block
comma
op_amp
id|HFS_I
c_func
(paren
id|page-&gt;mapping-&gt;host
)paren
op_member_access_from_pointer
id|mmu_private
)paren
suffix:semicolon
)brace
DECL|function|hfs_bmap
r_static
r_int
id|hfs_bmap
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_int
id|block
)paren
(brace
r_return
id|generic_block_bmap
c_func
(paren
id|mapping
comma
id|block
comma
id|hfs_get_block
)paren
suffix:semicolon
)brace
DECL|variable|hfs_aops
r_struct
id|address_space_operations
id|hfs_aops
op_assign
(brace
id|readpage
suffix:colon
id|hfs_readpage
comma
id|writepage
suffix:colon
id|hfs_writepage
comma
id|sync_page
suffix:colon
id|block_sync_page
comma
id|prepare_write
suffix:colon
id|hfs_prepare_write
comma
id|commit_write
suffix:colon
id|generic_commit_write
comma
id|bmap
suffix:colon
id|hfs_bmap
)brace
suffix:semicolon
multiline_comment|/*&n; * __hfs_iget()&n; *&n; * Given the MDB for a HFS filesystem, a &squot;key&squot; and an &squot;entry&squot; in&n; * the catalog B-tree and the &squot;type&squot; of the desired file return the&n; * inode for that file/directory or NULL.  Note that &squot;type&squot; indicates&n; * whether we want the actual file or directory, or the corresponding&n; * metadata (AppleDouble header file or CAP metadata file).&n; *&n; * In an ideal world we could call iget() and would not need this&n; * function.  However, since there is no way to even know the inode&n; * number until we&squot;ve found the file/directory in the catalog B-tree&n; * that simply won&squot;t happen.&n; *&n; * The main idea here is to look in the catalog B-tree to get the&n; * vital info about the file or directory (including the file id which&n; * becomes the inode number) and then to call iget() and return the&n; * inode if it is complete.  If it is not then we use the catalog&n; * entry to fill in the missing info, by calling the appropriate&n; * &squot;fillin&squot; function.  Note that these fillin functions are&n; * essentially hfs_*_read_inode() functions, but since there is no way&n; * to pass the catalog entry through iget() to such a read_inode()&n; * function, we have to call them after iget() returns an incomplete&n; * inode to us.&t; This is pretty much the same problem faced in the NFS&n; * code, and pretty much the same solution. The SMB filesystem deals&n; * with this in a different way: by using the address of the&n; * kmalloc()&squot;d space which holds the data as the inode number.&n; *&n; * XXX: Both this function and NFS&squot;s corresponding nfs_fhget() would&n; * benefit from a way to pass an additional (void *) through iget() to&n; * the VFS read_inode() function.&n; *&n; * this will hfs_cat_put() the entry if it fails.&n; */
DECL|function|hfs_iget
r_struct
id|inode
op_star
id|hfs_iget
c_func
(paren
r_struct
id|hfs_cat_entry
op_star
id|entry
comma
id|ino_t
id|type
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_struct
id|dentry
op_star
op_star
id|sys_entry
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* If there are several processes all calling __iget() for&n;&t;   the same inode then they will all get the same one back.&n;&t;   The first one to return from __iget() will notice that the&n;&t;   i_mode field of the inode is blank and KNOW that it is&n;&t;   the first to return.  Therefore, it will set the appropriate&n;&t;   &squot;sys_entry&squot; field in the entry and initialize the inode.&n;&t;   All the initialization must be done without sleeping,&n;&t;   or else other processes could end up using a partially&n;&t;   initialized inode.&t;&t;&t;&t;*/
id|sb
op_assign
id|entry-&gt;mdb-&gt;sys_mdb
suffix:semicolon
id|sys_entry
op_assign
op_amp
id|entry-&gt;sys_entry
(braket
id|HFS_ITYPE_TO_INT
c_func
(paren
id|type
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode
op_assign
id|iget
c_func
(paren
id|sb
comma
id|ntohl
c_func
(paren
id|entry-&gt;cnid
)paren
op_or
id|type
)paren
)paren
)paren
(brace
id|hfs_cat_put
c_func
(paren
id|entry
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_mode
op_logical_or
(paren
op_star
id|sys_entry
op_eq
l_int|NULL
)paren
)paren
(brace
multiline_comment|/* Initialize the inode */
r_struct
id|hfs_sb_info
op_star
id|hsb
op_assign
id|HFS_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
id|inode-&gt;i_rdev
op_assign
id|NODEV
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_mtime
op_assign
id|hfs_m_to_utime
c_func
(paren
id|entry-&gt;modify_date
)paren
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
id|HFS_SECTOR_SIZE
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|hsb-&gt;s_uid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|hsb-&gt;s_gid
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|mmu_private
op_assign
l_int|0
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|fork
op_assign
l_int|NULL
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|convert
op_assign
l_int|0
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|file_type
op_assign
l_int|0
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|dir_size
op_assign
l_int|0
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|default_layout
op_assign
l_int|NULL
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|layout
op_assign
l_int|NULL
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|magic
op_assign
id|HFS_INO_MAGIC
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|entry
op_assign
id|entry
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|tz_secondswest
op_assign
id|hfs_to_utc
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|hsb
op_member_access_from_pointer
id|s_ifill
c_func
(paren
id|inode
comma
id|type
comma
id|hsb-&gt;s_version
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hsb-&gt;s_afpd
op_logical_and
(paren
id|entry-&gt;type
op_eq
id|HFS_CDR_FIL
)paren
op_logical_and
(paren
id|entry-&gt;u.file.flags
op_amp
id|HFS_FIL_LOCK
)paren
)paren
(brace
id|inode-&gt;i_mode
op_and_assign
op_complement
id|S_IWUGO
suffix:semicolon
)brace
id|inode-&gt;i_mode
op_and_assign
op_complement
id|hsb-&gt;s_umask
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_mode
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
multiline_comment|/* does an hfs_cat_put */
id|inode
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
op_star
id|sys_entry
op_assign
id|dentry
suffix:semicolon
multiline_comment|/* cache dentry */
)brace
r_return
id|inode
suffix:semicolon
)brace
multiline_comment|/*================ Scheme-specific functions ================*/
multiline_comment|/* &n; * hfs_cap_ifill()&n; *&n; * This function serves the same purpose as a read_inode() function does&n; * in other filesystems.  It is called by __hfs_iget() to fill in&n; * the missing fields of an uninitialized inode under the CAP scheme.&n; */
DECL|function|hfs_cap_ifill
r_void
id|hfs_cap_ifill
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|ino_t
id|type
comma
r_const
r_int
id|version
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
id|inode
)paren
op_member_access_from_pointer
id|entry
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|d_drop_op
op_assign
id|hfs_cap_drop_dentry
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|HFS_CAP_FNDR
)paren
(brace
id|inode-&gt;i_size
op_assign
r_sizeof
(paren
r_struct
id|hfs_cap_info
)paren
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IRUGO
op_or
id|S_IWUGO
op_or
id|S_IFREG
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|hfs_cap_info_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|hfs_cap_info_operations
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|entry-&gt;type
op_eq
id|HFS_CDR_FIL
)paren
(brace
id|init_file_inode
c_func
(paren
id|inode
comma
(paren
id|type
op_eq
id|HFS_CAP_DATA
)paren
ques
c_cond
id|HFS_FK_DATA
suffix:colon
id|HFS_FK_RSRC
)paren
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|hfs_file_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|hfs_file_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|hfs_aops
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|mmu_private
op_assign
id|inode-&gt;i_size
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Directory */
r_struct
id|hfs_dir
op_star
id|hdir
op_assign
op_amp
id|entry-&gt;u.dir
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|hdir-&gt;files
op_plus
id|hdir-&gt;dirs
op_plus
l_int|5
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|dir_size
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|HFS_CAP_NDIR
)paren
(brace
id|inode-&gt;i_mode
op_assign
id|S_IRWXUGO
op_or
id|S_IFDIR
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
id|hdir-&gt;dirs
op_plus
l_int|4
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|hfs_cap_ndir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|hfs_cap_dir_operations
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|file_type
op_assign
id|HFS_CAP_NORM
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|type
op_eq
id|HFS_CAP_FDIR
)paren
(brace
id|inode-&gt;i_mode
op_assign
id|S_IRUGO
op_or
id|S_IXUGO
op_or
id|S_IFDIR
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|2
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|hfs_cap_fdir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|hfs_cap_dir_operations
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|file_type
op_assign
id|HFS_CAP_FNDR
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|type
op_eq
id|HFS_CAP_RDIR
)paren
(brace
id|inode-&gt;i_mode
op_assign
id|S_IRUGO
op_or
id|S_IXUGO
op_or
id|S_IFDIR
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|2
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|hfs_cap_rdir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|hfs_cap_dir_operations
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|file_type
op_assign
id|HFS_CAP_RSRC
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* &n; * hfs_dbl_ifill()&n; *&n; * This function serves the same purpose as a read_inode() function does&n; * in other filesystems.  It is called by __hfs_iget() to fill in&n; * the missing fields of an uninitialized inode under the AppleDouble&n; * scheme.&n; */
DECL|function|hfs_dbl_ifill
r_void
id|hfs_dbl_ifill
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|ino_t
id|type
comma
r_const
r_int
id|version
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
id|inode
)paren
op_member_access_from_pointer
id|entry
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|d_drop_op
op_assign
id|hfs_dbl_drop_dentry
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|HFS_DBL_HDR
)paren
(brace
r_if
c_cond
(paren
id|entry-&gt;type
op_eq
id|HFS_CDR_FIL
)paren
(brace
id|init_file_inode
c_func
(paren
id|inode
comma
id|HFS_FK_RSRC
)paren
suffix:semicolon
id|inode-&gt;i_size
op_add_assign
id|HFS_DBL_HDR_LEN
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|default_layout
op_assign
op_amp
id|hfs_dbl_fil_hdr_layout
suffix:semicolon
)brace
r_else
(brace
id|inode-&gt;i_size
op_assign
id|HFS_DBL_HDR_LEN
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IRUGO
op_or
id|S_IWUGO
op_or
id|S_IFREG
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|1
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|default_layout
op_assign
op_amp
id|hfs_dbl_dir_hdr_layout
suffix:semicolon
)brace
id|inode-&gt;i_op
op_assign
op_amp
id|hfs_hdr_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|hfs_hdr_operations
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|entry-&gt;type
op_eq
id|HFS_CDR_FIL
)paren
(brace
id|init_file_inode
c_func
(paren
id|inode
comma
id|HFS_FK_DATA
)paren
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|hfs_file_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|hfs_file_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|hfs_aops
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|mmu_private
op_assign
id|inode-&gt;i_size
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Directory */
r_struct
id|hfs_dir
op_star
id|hdir
op_assign
op_amp
id|entry-&gt;u.dir
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
id|hdir-&gt;dirs
op_plus
l_int|2
suffix:semicolon
id|inode-&gt;i_size
op_assign
l_int|3
op_plus
l_int|2
op_star
(paren
id|hdir-&gt;dirs
op_plus
id|hdir-&gt;files
)paren
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IRWXUGO
op_or
id|S_IFDIR
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|hfs_dbl_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|hfs_dbl_dir_operations
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|file_type
op_assign
id|HFS_DBL_NORM
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|dir_size
op_assign
l_int|2
suffix:semicolon
)brace
)brace
multiline_comment|/* &n; * hfs_nat_ifill()&n; *&n; * This function serves the same purpose as a read_inode() function does&n; * in other filesystems.  It is called by __hfs_iget() to fill in&n; * the missing fields of an uninitialized inode under the Netatalk&n; * scheme.&n; */
DECL|function|hfs_nat_ifill
r_void
id|hfs_nat_ifill
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|ino_t
id|type
comma
r_const
r_int
id|version
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
id|inode
)paren
op_member_access_from_pointer
id|entry
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|d_drop_op
op_assign
id|hfs_nat_drop_dentry
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|HFS_NAT_HDR
)paren
(brace
r_if
c_cond
(paren
id|entry-&gt;type
op_eq
id|HFS_CDR_FIL
)paren
(brace
id|init_file_inode
c_func
(paren
id|inode
comma
id|HFS_FK_RSRC
)paren
suffix:semicolon
id|inode-&gt;i_size
op_add_assign
id|HFS_NAT_HDR_LEN
suffix:semicolon
)brace
r_else
(brace
id|inode-&gt;i_size
op_assign
id|HFS_NAT_HDR_LEN
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IRUGO
op_or
id|S_IWUGO
op_or
id|S_IFREG
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|1
suffix:semicolon
)brace
id|inode-&gt;i_op
op_assign
op_amp
id|hfs_hdr_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|hfs_hdr_operations
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|default_layout
op_assign
(paren
id|version
op_eq
l_int|2
)paren
ques
c_cond
op_amp
id|hfs_nat2_hdr_layout
suffix:colon
op_amp
id|hfs_nat_hdr_layout
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|entry-&gt;type
op_eq
id|HFS_CDR_FIL
)paren
(brace
id|init_file_inode
c_func
(paren
id|inode
comma
id|HFS_FK_DATA
)paren
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|hfs_file_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|hfs_file_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|hfs_aops
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|mmu_private
op_assign
id|inode-&gt;i_size
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Directory */
r_struct
id|hfs_dir
op_star
id|hdir
op_assign
op_amp
id|entry-&gt;u.dir
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|hdir-&gt;files
op_plus
id|hdir-&gt;dirs
op_plus
l_int|4
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IRWXUGO
op_or
id|S_IFDIR
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|dir_size
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|HFS_NAT_NDIR
)paren
(brace
id|inode-&gt;i_nlink
op_assign
id|hdir-&gt;dirs
op_plus
l_int|3
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|hfs_nat_ndir_inode_operations
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|file_type
op_assign
id|HFS_NAT_NORM
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|type
op_eq
id|HFS_NAT_HDIR
)paren
(brace
id|inode-&gt;i_nlink
op_assign
l_int|2
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|hfs_nat_hdir_inode_operations
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|file_type
op_assign
id|HFS_NAT_HDR
suffix:semicolon
)brace
id|inode-&gt;i_fop
op_assign
op_amp
id|hfs_nat_dir_operations
suffix:semicolon
)brace
)brace
eof
