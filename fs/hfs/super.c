multiline_comment|/*&n; *  linux/fs/hfs/super.c&n; *&n; * Copyright (C) 1995-1997  Paul H. Hargrove&n; * (C) 2003 Ardis Technologies &lt;roman@ardistech.com&gt;&n; * This file may be distributed under the terms of the GNU General Public License.&n; *&n; * This file contains hfs_read_super(), some of the super_ops and&n; * init_module() and cleanup_module().&t;The remaining super_ops are in&n; * inode.c since they deal with inodes.&n; *&n; * Based on the minix file system code, (C) 1991, 1992 by Linus Torvalds&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/vfs.h&gt;
macro_line|#include &quot;hfs_fs.h&quot;
macro_line|#include &quot;btree.h&quot;
DECL|variable|hfs_version
r_const
r_char
id|hfs_version
(braket
)braket
op_assign
l_string|&quot;0.96&quot;
suffix:semicolon
DECL|variable|hfs_inode_cachep
r_static
id|kmem_cache_t
op_star
id|hfs_inode_cachep
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * hfs_write_super()&n; *&n; * Description:&n; *   This function is called by the VFS only. When the filesystem&n; *   is mounted r/w it updates the MDB on disk.&n; * Input Variable(s):&n; *   struct super_block *sb: Pointer to the hfs superblock&n; * Output Variable(s):&n; *   NONE&n; * Returns:&n; *   void&n; * Preconditions:&n; *   &squot;sb&squot; points to a &quot;valid&quot; (struct super_block).&n; * Postconditions:&n; *   The MDB is marked &squot;unsuccessfully unmounted&squot; by clearing bit 8 of drAtrb&n; *   (hfs_put_super() must set this flag!). Some MDB fields are updated&n; *   and the MDB buffer is written to disk by calling hfs_mdb_commit().&n; */
DECL|function|hfs_write_super
r_static
r_void
id|hfs_write_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|sb-&gt;s_dirt
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
r_return
suffix:semicolon
multiline_comment|/* sync everything to the buffers */
id|hfs_mdb_commit
c_func
(paren
id|sb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_put_super()&n; *&n; * This is the put_super() entry in the super_operations structure for&n; * HFS filesystems.  The purpose is to release the resources&n; * associated with the superblock sb.&n; */
DECL|function|hfs_put_super
r_static
r_void
id|hfs_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|hfs_mdb_close
c_func
(paren
id|sb
)paren
suffix:semicolon
multiline_comment|/* release the MDB&squot;s resources */
id|hfs_mdb_put
c_func
(paren
id|sb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_statfs()&n; *&n; * This is the statfs() entry in the super_operations structure for&n; * HFS filesystems.  The purpose is to return various data about the&n; * filesystem.&n; *&n; * changed f_files/f_ffree to reflect the fs_ablock/free_ablocks.&n; */
DECL|function|hfs_statfs
r_static
r_int
id|hfs_statfs
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|kstatfs
op_star
id|buf
)paren
(brace
id|buf-&gt;f_type
op_assign
id|HFS_SUPER_MAGIC
suffix:semicolon
id|buf-&gt;f_bsize
op_assign
id|sb-&gt;s_blocksize
suffix:semicolon
id|buf-&gt;f_blocks
op_assign
(paren
id|u32
)paren
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|fs_ablocks
op_star
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|fs_div
suffix:semicolon
id|buf-&gt;f_bfree
op_assign
(paren
id|u32
)paren
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|free_ablocks
op_star
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|fs_div
suffix:semicolon
id|buf-&gt;f_bavail
op_assign
id|buf-&gt;f_bfree
suffix:semicolon
id|buf-&gt;f_files
op_assign
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|fs_ablocks
suffix:semicolon
id|buf-&gt;f_ffree
op_assign
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|free_ablocks
suffix:semicolon
id|buf-&gt;f_namelen
op_assign
id|HFS_NAMELEN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hfs_remount
r_int
id|hfs_remount
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
op_star
id|flags
comma
r_char
op_star
id|data
)paren
(brace
op_star
id|flags
op_or_assign
id|MS_NODIRATIME
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|flags
op_amp
id|MS_RDONLY
)paren
op_eq
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|flags
op_amp
id|MS_RDONLY
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|mdb-&gt;drAtrb
op_amp
id|cpu_to_be16
c_func
(paren
id|HFS_SB_ATTRIB_UNMNT
)paren
)paren
op_logical_or
(paren
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|mdb-&gt;drAtrb
op_amp
id|cpu_to_be16
c_func
(paren
id|HFS_SB_ATTRIB_INCNSTNT
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;HFS-fs warning: Filesystem was not cleanly unmounted, &quot;
l_string|&quot;running fsck.hfs is recommended.  leaving read-only.&bslash;n&quot;
)paren
suffix:semicolon
id|sb-&gt;s_flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
op_star
id|flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|mdb-&gt;drAtrb
op_amp
id|cpu_to_be16
c_func
(paren
id|HFS_SB_ATTRIB_SLOCK
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;HFS-fs: Filesystem is marked locked, leaving read-only.&bslash;n&quot;
)paren
suffix:semicolon
id|sb-&gt;s_flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
op_star
id|flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hfs_alloc_inode
r_static
r_struct
id|inode
op_star
id|hfs_alloc_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|hfs_inode_info
op_star
id|i
suffix:semicolon
id|i
op_assign
id|kmem_cache_alloc
c_func
(paren
id|hfs_inode_cachep
comma
id|SLAB_KERNEL
)paren
suffix:semicolon
r_return
id|i
ques
c_cond
op_amp
id|i-&gt;vfs_inode
suffix:colon
l_int|NULL
suffix:semicolon
)brace
DECL|function|hfs_destroy_inode
r_static
r_void
id|hfs_destroy_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|kmem_cache_free
c_func
(paren
id|hfs_inode_cachep
comma
id|HFS_I
c_func
(paren
id|inode
)paren
)paren
suffix:semicolon
)brace
DECL|variable|hfs_super_operations
r_static
r_struct
id|super_operations
id|hfs_super_operations
op_assign
(brace
dot
id|alloc_inode
op_assign
id|hfs_alloc_inode
comma
dot
id|destroy_inode
op_assign
id|hfs_destroy_inode
comma
dot
id|write_inode
op_assign
id|hfs_write_inode
comma
dot
id|clear_inode
op_assign
id|hfs_clear_inode
comma
dot
id|put_super
op_assign
id|hfs_put_super
comma
dot
id|write_super
op_assign
id|hfs_write_super
comma
dot
id|statfs
op_assign
id|hfs_statfs
comma
dot
id|remount_fs
op_assign
id|hfs_remount
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * parse_options()&n; *&n; * adapted from linux/fs/msdos/inode.c written 1992,93 by Werner Almesberger&n; * This function is called by hfs_read_super() to parse the mount options.&n; */
DECL|function|parse_options
r_static
r_int
id|parse_options
c_func
(paren
r_char
op_star
id|options
comma
r_struct
id|hfs_sb_info
op_star
id|hsb
)paren
(brace
r_char
op_star
id|this_char
comma
op_star
id|value
suffix:semicolon
multiline_comment|/* initialize the sb with defaults */
id|hsb-&gt;s_uid
op_assign
id|current-&gt;uid
suffix:semicolon
id|hsb-&gt;s_gid
op_assign
id|current-&gt;gid
suffix:semicolon
id|hsb-&gt;s_file_umask
op_assign
l_int|0644
suffix:semicolon
id|hsb-&gt;s_dir_umask
op_assign
l_int|0755
suffix:semicolon
id|hsb-&gt;s_type
op_assign
l_int|0x3f3f3f3f
suffix:semicolon
multiline_comment|/* == &squot;????&squot; */
id|hsb-&gt;s_creator
op_assign
l_int|0x3f3f3f3f
suffix:semicolon
multiline_comment|/* == &squot;????&squot; */
id|hsb-&gt;s_quiet
op_assign
l_int|0
suffix:semicolon
id|hsb-&gt;part
op_assign
op_minus
l_int|1
suffix:semicolon
id|hsb-&gt;session
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|options
)paren
r_return
l_int|1
suffix:semicolon
r_while
c_loop
(paren
(paren
id|this_char
op_assign
id|strsep
c_func
(paren
op_amp
id|options
comma
l_string|&quot;,&quot;
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|this_char
)paren
r_continue
suffix:semicolon
id|value
op_assign
id|strchr
c_func
(paren
id|this_char
comma
l_char|&squot;=&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
)paren
op_star
id|value
op_increment
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Numeric-valued options */
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;uid&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
r_return
l_int|0
suffix:semicolon
id|hsb-&gt;s_uid
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;gid&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
r_return
l_int|0
suffix:semicolon
id|hsb-&gt;s_gid
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;umask&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
r_return
l_int|0
suffix:semicolon
id|hsb-&gt;s_file_umask
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|8
)paren
suffix:semicolon
id|hsb-&gt;s_dir_umask
op_assign
id|hsb-&gt;s_file_umask
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;file_umask&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
r_return
l_int|0
suffix:semicolon
id|hsb-&gt;s_file_umask
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;dir_umask&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
r_return
l_int|0
suffix:semicolon
id|hsb-&gt;s_dir_umask
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;part&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
r_return
l_int|0
suffix:semicolon
id|hsb-&gt;part
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;session&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
r_return
l_int|0
suffix:semicolon
id|hsb-&gt;session
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* String-valued options */
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;type&quot;
)paren
op_logical_and
id|value
)paren
(brace
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|value
)paren
op_ne
l_int|4
)paren
r_return
l_int|0
suffix:semicolon
id|hsb-&gt;s_type
op_assign
op_star
(paren
id|u32
op_star
)paren
id|value
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;creator&quot;
)paren
op_logical_and
id|value
)paren
(brace
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|value
)paren
op_ne
l_int|4
)paren
r_return
l_int|0
suffix:semicolon
id|hsb-&gt;s_creator
op_assign
op_star
(paren
id|u32
op_star
)paren
id|value
suffix:semicolon
multiline_comment|/* Boolean-valued options */
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;quiet&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|value
)paren
r_return
l_int|0
suffix:semicolon
id|hsb-&gt;s_quiet
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
id|hsb-&gt;s_dir_umask
op_and_assign
l_int|0777
suffix:semicolon
id|hsb-&gt;s_file_umask
op_and_assign
l_int|0777
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_read_super()&n; *&n; * This is the function that is responsible for mounting an HFS&n; * filesystem.&t;It performs all the tasks necessary to get enough data&n; * from the disk to read the root inode.  This includes parsing the&n; * mount options, dealing with Macintosh partitions, reading the&n; * superblock and the allocation bitmap blocks, calling&n; * hfs_btree_init() to get the necessary data about the extents and&n; * catalog B-trees and, finally, reading the root inode into memory.&n; */
DECL|function|hfs_fill_super
r_static
r_int
id|hfs_fill_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_void
op_star
id|data
comma
r_int
id|silent
)paren
(brace
r_struct
id|hfs_sb_info
op_star
id|sbi
suffix:semicolon
r_struct
id|hfs_find_data
id|fd
suffix:semicolon
id|hfs_cat_rec
id|rec
suffix:semicolon
r_struct
id|inode
op_star
id|root_inode
suffix:semicolon
r_int
id|res
suffix:semicolon
id|sbi
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|hfs_sb_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbi
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|sb-&gt;s_fs_info
op_assign
id|sbi
suffix:semicolon
id|memset
c_func
(paren
id|sbi
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|hfs_sb_info
)paren
)paren
suffix:semicolon
id|INIT_HLIST_HEAD
c_func
(paren
op_amp
id|sbi-&gt;rsrc_inodes
)paren
suffix:semicolon
id|res
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parse_options
c_func
(paren
(paren
r_char
op_star
)paren
id|data
comma
id|sbi
)paren
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_fs: unable to parse mount options.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|bail3
suffix:semicolon
)brace
id|sb-&gt;s_op
op_assign
op_amp
id|hfs_super_operations
suffix:semicolon
id|sb-&gt;s_flags
op_or_assign
id|MS_NODIRATIME
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|sbi-&gt;bitmap_lock
)paren
suffix:semicolon
id|res
op_assign
id|hfs_mdb_get
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
id|hfs_warn
c_func
(paren
l_string|&quot;VFS: Can&squot;t find a HFS filesystem on dev %s.&bslash;n&quot;
comma
id|hfs_mdb_name
c_func
(paren
id|sb
)paren
)paren
suffix:semicolon
id|res
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|bail2
suffix:semicolon
)brace
multiline_comment|/* try to get the root inode */
id|hfs_find_init
c_func
(paren
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cat_tree
comma
op_amp
id|fd
)paren
suffix:semicolon
id|res
op_assign
id|hfs_cat_find_brec
c_func
(paren
id|sb
comma
id|HFS_ROOT_CNID
comma
op_amp
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
id|hfs_bnode_read
c_func
(paren
id|fd.bnode
comma
op_amp
id|rec
comma
id|fd.entryoffset
comma
id|fd.entrylength
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
(brace
id|hfs_find_exit
c_func
(paren
op_amp
id|fd
)paren
suffix:semicolon
r_goto
id|bail_no_root
suffix:semicolon
)brace
id|root_inode
op_assign
id|hfs_iget
c_func
(paren
id|sb
comma
op_amp
id|fd.search_key-&gt;cat
comma
op_amp
id|rec
)paren
suffix:semicolon
id|hfs_find_exit
c_func
(paren
op_amp
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root_inode
)paren
r_goto
id|bail_no_root
suffix:semicolon
id|sb-&gt;s_root
op_assign
id|d_alloc_root
c_func
(paren
id|root_inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;s_root
)paren
r_goto
id|bail_iput
suffix:semicolon
id|sb-&gt;s_root-&gt;d_op
op_assign
op_amp
id|hfs_dentry_operations
suffix:semicolon
multiline_comment|/* everything&squot;s okay */
r_return
l_int|0
suffix:semicolon
id|bail_iput
suffix:colon
id|iput
c_func
(paren
id|root_inode
)paren
suffix:semicolon
id|bail_no_root
suffix:colon
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_fs: get root inode failed.&bslash;n&quot;
)paren
suffix:semicolon
id|hfs_mdb_put
c_func
(paren
id|sb
)paren
suffix:semicolon
id|bail2
suffix:colon
id|bail3
suffix:colon
id|kfree
c_func
(paren
id|sbi
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|hfs_get_sb
r_static
r_struct
id|super_block
op_star
id|hfs_get_sb
c_func
(paren
r_struct
id|file_system_type
op_star
id|fs_type
comma
r_int
id|flags
comma
r_const
r_char
op_star
id|dev_name
comma
r_void
op_star
id|data
)paren
(brace
r_return
id|get_sb_bdev
c_func
(paren
id|fs_type
comma
id|flags
comma
id|dev_name
comma
id|data
comma
id|hfs_fill_super
)paren
suffix:semicolon
)brace
DECL|variable|hfs_fs_type
r_static
r_struct
id|file_system_type
id|hfs_fs_type
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;hfs&quot;
comma
dot
id|get_sb
op_assign
id|hfs_get_sb
comma
dot
id|kill_sb
op_assign
id|kill_block_super
comma
dot
id|fs_flags
op_assign
id|FS_REQUIRES_DEV
comma
)brace
suffix:semicolon
DECL|function|hfs_init_once
r_static
r_void
id|hfs_init_once
c_func
(paren
r_void
op_star
id|p
comma
id|kmem_cache_t
op_star
id|cachep
comma
r_int
r_int
id|flags
)paren
(brace
r_struct
id|hfs_inode_info
op_star
id|i
op_assign
id|p
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
(paren
id|SLAB_CTOR_VERIFY
op_or
id|SLAB_CTOR_CONSTRUCTOR
)paren
)paren
op_eq
id|SLAB_CTOR_CONSTRUCTOR
)paren
id|inode_init_once
c_func
(paren
op_amp
id|i-&gt;vfs_inode
)paren
suffix:semicolon
)brace
DECL|function|init_hfs_fs
r_static
r_int
id|__init
id|init_hfs_fs
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
id|hfs_inode_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;hfs_inode_cache&quot;
comma
r_sizeof
(paren
r_struct
id|hfs_inode_info
)paren
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
comma
id|hfs_init_once
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hfs_inode_cachep
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|err
op_assign
id|register_filesystem
c_func
(paren
op_amp
id|hfs_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|kmem_cache_destroy
c_func
(paren
id|hfs_inode_cachep
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|exit_hfs_fs
r_static
r_void
id|__exit
id|exit_hfs_fs
c_func
(paren
r_void
)paren
(brace
id|unregister_filesystem
c_func
(paren
op_amp
id|hfs_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kmem_cache_destroy
c_func
(paren
id|hfs_inode_cachep
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;hfs_inode_cache: not all structures were freed&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|init_hfs_fs
)paren
id|module_exit
c_func
(paren
id|exit_hfs_fs
)paren
eof
