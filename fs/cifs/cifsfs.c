multiline_comment|/*&n; *   fs/cifs/cifsfs.c&n; *&n; *   Copyright (c) International Business Machines  Corp., 2002&n; *   Author(s): Steve French (sfrench@us.ibm.com)&n; *&n; *   Common Internet FileSystem (CIFS) client&n; *&n; *   This library is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU Lesser General Public License as published&n; *   by the Free Software Foundation; either version 2.1 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This library is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU Lesser General Public License for more details.&n; *&n; *   You should have received a copy of the GNU Lesser General Public License&n; *   along with this library; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
multiline_comment|/* Note that BB means BUGBUG (ie something to fix eventually) */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mount.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/vfs.h&gt;
macro_line|#include &quot;cifsfs.h&quot;
macro_line|#include &quot;cifspdu.h&quot;
DECL|macro|DECLARE_GLOBALS_HERE
mdefine_line|#define DECLARE_GLOBALS_HERE
macro_line|#include &quot;cifsglob.h&quot;
macro_line|#include &quot;cifsproto.h&quot;
macro_line|#include &quot;cifs_debug.h&quot;
macro_line|#include &quot;cifs_fs_sb.h&quot;
macro_line|#include &lt;linux/mm.h&gt;
DECL|macro|CIFS_MAGIC_NUMBER
mdefine_line|#define CIFS_MAGIC_NUMBER 0xFF534D42&t;/* the first four bytes of all SMB PDUs */
r_extern
r_struct
id|file_system_type
id|cifs_fs_type
suffix:semicolon
DECL|variable|cifsFYI
r_int
id|cifsFYI
op_assign
l_int|0
suffix:semicolon
DECL|variable|cifsERROR
r_int
id|cifsERROR
op_assign
l_int|1
suffix:semicolon
DECL|variable|traceSMB
r_int
id|traceSMB
op_assign
l_int|0
suffix:semicolon
DECL|variable|oplockEnabled
r_int
r_int
id|oplockEnabled
op_assign
l_int|0
suffix:semicolon
DECL|variable|multiuser_mount
r_int
r_int
id|multiuser_mount
op_assign
l_int|0
suffix:semicolon
DECL|variable|extended_security
r_int
r_int
id|extended_security
op_assign
l_int|0
suffix:semicolon
DECL|variable|ntlmv2_support
r_int
r_int
id|ntlmv2_support
op_assign
l_int|0
suffix:semicolon
DECL|variable|sign_CIFS_PDUs
r_int
r_int
id|sign_CIFS_PDUs
op_assign
l_int|0
suffix:semicolon
DECL|variable|CIFSMaximumBufferSize
r_int
r_int
id|CIFSMaximumBufferSize
op_assign
id|CIFS_MAX_MSGSIZE
suffix:semicolon
r_extern
r_int
id|cifs_mount
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|cifs_sb_info
op_star
comma
r_char
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cifs_umount
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|cifs_sb_info
op_star
)paren
suffix:semicolon
r_void
id|cifs_proc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|cifs_proc_clean
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
DECL|function|cifs_read_super
id|cifs_read_super
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
r_char
op_star
id|devname
comma
r_int
id|silent
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|cifs_sb_info
op_star
id|cifs_sb
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
id|sb-&gt;s_fs_info
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|cifs_sb_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|cifs_sb
op_assign
id|CIFS_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cifs_sb
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|cifs_sb-&gt;local_nls
op_assign
id|load_nls_default
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* needed for ASCII cp to Unicode converts */
id|rc
op_assign
id|cifs_mount
c_func
(paren
id|sb
comma
id|cifs_sb
comma
id|data
comma
id|devname
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
id|cERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;cifs_mount failed w/return code = %d&quot;
comma
id|rc
)paren
)paren
suffix:semicolon
r_goto
id|out_mount_failed
suffix:semicolon
)brace
id|sb-&gt;s_magic
op_assign
id|CIFS_MAGIC_NUMBER
suffix:semicolon
id|sb-&gt;s_op
op_assign
op_amp
id|cifs_super_ops
suffix:semicolon
r_if
c_cond
(paren
id|cifs_sb-&gt;tcon-&gt;ses-&gt;server-&gt;maxBuf
OG
id|MAX_CIFS_HDR_SIZE
op_plus
l_int|512
)paren
(brace
id|sb-&gt;s_blocksize
op_assign
id|cifs_sb-&gt;tcon-&gt;ses-&gt;server-&gt;maxBuf
op_minus
id|MAX_CIFS_HDR_SIZE
suffix:semicolon
)brace
r_else
id|sb-&gt;s_blocksize
op_assign
id|CIFSMaximumBufferSize
suffix:semicolon
id|sb-&gt;s_blocksize_bits
op_assign
l_int|14
suffix:semicolon
multiline_comment|/* default 2**14 = CIFS_MAX_MSGSIZE */
id|inode
op_assign
id|iget
c_func
(paren
id|sb
comma
id|ROOT_I
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_goto
id|out_no_root
suffix:semicolon
id|sb-&gt;s_root
op_assign
id|d_alloc_root
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;s_root
)paren
r_goto
id|out_no_root
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_no_root
suffix:colon
id|cERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;cifs_read_super: get root inode failed&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
)paren
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|out_mount_failed
suffix:colon
r_if
c_cond
(paren
id|cifs_sb
)paren
(brace
id|kfree
c_func
(paren
id|cifs_sb
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_void
DECL|function|cifs_put_super
id|cifs_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_struct
id|cifs_sb_info
op_star
id|cifs_sb
suffix:semicolon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;In cifs_put_super&quot;
)paren
)paren
suffix:semicolon
id|cifs_sb
op_assign
id|CIFS_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cifs_sb
op_eq
l_int|NULL
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Empty cifs superblock info passed to unmount&quot;
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|rc
op_assign
id|cifs_umount
c_func
(paren
id|sb
comma
id|cifs_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|cERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;cifs_umount failed with return code %d&quot;
comma
id|rc
)paren
)paren
suffix:semicolon
)brace
id|unload_nls
c_func
(paren
id|cifs_sb-&gt;local_nls
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|cifs_sb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_int
DECL|function|cifs_statfs
id|cifs_statfs
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|statfs
op_star
id|buf
)paren
(brace
r_int
id|xid
comma
id|rc
suffix:semicolon
r_struct
id|cifs_sb_info
op_star
id|cifs_sb
suffix:semicolon
r_struct
id|cifsTconInfo
op_star
id|pTcon
suffix:semicolon
id|xid
op_assign
id|GetXid
c_func
(paren
)paren
suffix:semicolon
id|cifs_sb
op_assign
id|CIFS_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
id|pTcon
op_assign
id|cifs_sb-&gt;tcon
suffix:semicolon
id|buf-&gt;f_type
op_assign
id|CIFS_MAGIC_NUMBER
suffix:semicolon
multiline_comment|/* instead could get the real value via SMB_QUERY_FS_ATTRIBUTE_INFO */
id|buf-&gt;f_namelen
op_assign
id|PATH_MAX
suffix:semicolon
multiline_comment|/* PATH_MAX may be too long - it would presumably&n;&t;&t;&t;&t;&t;   be length of total path, note that some servers may be &n;&t;&t;&t;&t;&t;   able to support more than this, but best to be safe&n;&t;&t;&t;&t;&t;   since Win2k and others can not handle very long filenames */
id|buf-&gt;f_files
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* undefined */
id|buf-&gt;f_ffree
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* unlimited */
id|rc
op_assign
id|CIFSSMBQFSInfo
c_func
(paren
id|xid
comma
id|pTcon
comma
id|buf
comma
id|cifs_sb-&gt;local_nls
)paren
suffix:semicolon
multiline_comment|/*     &n;&t;   int f_type;&n;&t;   __fsid_t f_fsid;&n;&t;   int f_namelen;  */
multiline_comment|/* BB get from info put in tcon struct at mount time with call to QFSAttrInfo */
id|FreeXid
c_func
(paren
id|xid
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* always return success? what if volume is no longer available? */
)brace
DECL|function|cifs_permission
r_static
r_int
id|cifs_permission
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|mask
)paren
(brace
multiline_comment|/* the server does permission checks, we do not need to do it here */
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cifs_inode_cachep
r_static
id|kmem_cache_t
op_star
id|cifs_inode_cachep
suffix:semicolon
DECL|variable|cifs_req_cachep
id|kmem_cache_t
op_star
id|cifs_req_cachep
suffix:semicolon
DECL|variable|cifs_mid_cachep
id|kmem_cache_t
op_star
id|cifs_mid_cachep
suffix:semicolon
r_static
r_struct
id|inode
op_star
DECL|function|cifs_alloc_inode
id|cifs_alloc_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|cifsInodeInfo
op_star
id|cifs_inode
suffix:semicolon
id|cifs_inode
op_assign
(paren
r_struct
id|cifsInodeInfo
op_star
)paren
id|kmem_cache_alloc
c_func
(paren
id|cifs_inode_cachep
comma
id|SLAB_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cifs_inode
)paren
r_return
l_int|NULL
suffix:semicolon
id|cifs_inode-&gt;cifsAttrs
op_assign
l_int|0x20
suffix:semicolon
multiline_comment|/* default */
id|atomic_set
c_func
(paren
op_amp
id|cifs_inode-&gt;inUse
comma
l_int|0
)paren
suffix:semicolon
id|cifs_inode-&gt;time
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|oplockEnabled
)paren
(brace
id|cifs_inode-&gt;clientCanCacheRead
op_assign
l_int|1
suffix:semicolon
id|cifs_inode-&gt;clientCanCacheAll
op_assign
l_int|1
suffix:semicolon
)brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|cifs_inode-&gt;openFileList
)paren
suffix:semicolon
r_return
op_amp
id|cifs_inode-&gt;vfs_inode
suffix:semicolon
)brace
r_static
r_void
DECL|function|cifs_destroy_inode
id|cifs_destroy_inode
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
id|cifs_inode_cachep
comma
id|CIFS_I
c_func
(paren
id|inode
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * cifs_show_options() is for displaying mount options in /proc/mounts.&n; * It tries to avoid showing settings that were not changed from their&n; * defaults.&n; */
r_static
r_int
DECL|function|cifs_show_options
id|cifs_show_options
c_func
(paren
r_struct
id|seq_file
op_star
id|s
comma
r_struct
id|vfsmount
op_star
id|m
)paren
(brace
r_struct
id|cifs_sb_info
op_star
id|cifs_sb
suffix:semicolon
id|cifs_sb
op_assign
id|CIFS_SB
c_func
(paren
id|m-&gt;mnt_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cifs_sb
)paren
r_if
c_cond
(paren
id|cifs_sb-&gt;tcon
)paren
(brace
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot;, TARGET: %s &quot;
comma
id|cifs_sb-&gt;tcon-&gt;treeName
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot;FS TYPE: %s &quot;
comma
id|cifs_sb-&gt;tcon-&gt;nativeFileSystem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cifs_sb-&gt;tcon-&gt;ses-&gt;userName
)paren
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot; USER: %s &quot;
comma
id|cifs_sb-&gt;tcon-&gt;ses-&gt;userName
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cifs_super_ops
r_struct
id|super_operations
id|cifs_super_ops
op_assign
(brace
dot
id|read_inode
op_assign
id|cifs_read_inode
comma
dot
id|put_super
op_assign
id|cifs_put_super
comma
dot
id|statfs
op_assign
id|cifs_statfs
comma
dot
id|alloc_inode
op_assign
id|cifs_alloc_inode
comma
dot
id|destroy_inode
op_assign
id|cifs_destroy_inode
comma
multiline_comment|/*&t;.drop_inode&t;    = generic_delete_inode, &n;&t;.delete_inode&t;= cifs_delete_inode,  */
multiline_comment|/* Do not need the above two functions     &n;   unless later we add lazy close of inodes or unless the kernel forgets to call&n;   us with the same number of releases (closes) as opens */
dot
id|show_options
op_assign
id|cifs_show_options
comma
multiline_comment|/*    .umount_begin   = cifs_umount_begin, */
multiline_comment|/* consider adding in the future */
)brace
suffix:semicolon
r_static
r_struct
id|super_block
op_star
DECL|function|cifs_get_sb
id|cifs_get_sb
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
r_char
op_star
id|dev_name
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|rc
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
op_assign
id|sget
c_func
(paren
id|fs_type
comma
l_int|NULL
comma
id|set_anon_super
comma
l_int|NULL
)paren
suffix:semicolon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Devname: %s flags: %d &quot;
comma
id|dev_name
comma
id|flags
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|sb
)paren
)paren
r_return
id|sb
suffix:semicolon
id|sb-&gt;s_flags
op_assign
id|flags
suffix:semicolon
id|rc
op_assign
id|cifs_read_super
c_func
(paren
id|sb
comma
id|data
comma
id|dev_name
comma
id|flags
op_amp
id|MS_VERBOSE
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|up_write
c_func
(paren
op_amp
id|sb-&gt;s_umount
)paren
suffix:semicolon
id|deactivate_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|rc
)paren
suffix:semicolon
)brace
id|sb-&gt;s_flags
op_or_assign
id|MS_ACTIVE
suffix:semicolon
r_return
id|sb
suffix:semicolon
)brace
DECL|variable|cifs_fs_type
r_static
r_struct
id|file_system_type
id|cifs_fs_type
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
l_string|&quot;cifs&quot;
comma
dot
id|get_sb
op_assign
id|cifs_get_sb
comma
dot
id|kill_sb
op_assign
id|kill_anon_super
comma
multiline_comment|/*  .fs_flags */
)brace
suffix:semicolon
DECL|variable|cifs_dir_inode_ops
r_struct
id|inode_operations
id|cifs_dir_inode_ops
op_assign
(brace
dot
id|create
op_assign
id|cifs_create
comma
dot
id|lookup
op_assign
id|cifs_lookup
comma
dot
id|getattr
op_assign
id|cifs_getattr
comma
dot
id|unlink
op_assign
id|cifs_unlink
comma
dot
id|link
op_assign
id|cifs_hardlink
comma
dot
id|mkdir
op_assign
id|cifs_mkdir
comma
dot
id|rmdir
op_assign
id|cifs_rmdir
comma
dot
id|rename
op_assign
id|cifs_rename
comma
dot
id|permission
op_assign
id|cifs_permission
comma
multiline_comment|/*&t;revalidate:cifs_revalidate,   */
dot
id|setattr
op_assign
id|cifs_setattr
comma
dot
id|symlink
op_assign
id|cifs_symlink
comma
)brace
suffix:semicolon
DECL|variable|cifs_file_inode_ops
r_struct
id|inode_operations
id|cifs_file_inode_ops
op_assign
(brace
multiline_comment|/*&t;revalidate:cifs_revalidate, */
dot
id|setattr
op_assign
id|cifs_setattr
comma
dot
id|getattr
op_assign
id|cifs_getattr
comma
multiline_comment|/* do we need this anymore? */
dot
id|rename
op_assign
id|cifs_rename
comma
dot
id|permission
op_assign
id|cifs_permission
comma
macro_line|#ifdef CIFS_XATTR
dot
id|setxattr
op_assign
id|cifs_setxattr
comma
dot
id|getxattr
op_assign
id|cifs_getxattr
comma
dot
id|listxattr
op_assign
id|cifs_listxattr
comma
dot
id|removexattr
op_assign
id|cifs_removexattr
comma
macro_line|#endif 
)brace
suffix:semicolon
DECL|variable|cifs_symlink_inode_ops
r_struct
id|inode_operations
id|cifs_symlink_inode_ops
op_assign
(brace
dot
id|readlink
op_assign
id|cifs_readlink
comma
dot
id|follow_link
op_assign
id|cifs_follow_link
comma
dot
id|permission
op_assign
id|cifs_permission
comma
multiline_comment|/* BB add the following two eventually */
multiline_comment|/* revalidate: cifs_revalidate,&n;&t;   setattr:    cifs_notify_change, */
multiline_comment|/* BB do we need notify change */
macro_line|#ifdef CIFS_XATTR
dot
id|setxattr
op_assign
id|cifs_setxattr
comma
dot
id|getxattr
op_assign
id|cifs_getxattr
comma
dot
id|listxattr
op_assign
id|cifs_listxattr
comma
dot
id|removexattr
op_assign
id|cifs_removexattr
comma
macro_line|#endif 
)brace
suffix:semicolon
DECL|variable|cifs_file_ops
r_struct
id|file_operations
id|cifs_file_ops
op_assign
(brace
dot
id|read
op_assign
id|generic_file_read
comma
dot
id|write
op_assign
id|generic_file_write
comma
dot
id|open
op_assign
id|cifs_open
comma
dot
id|release
op_assign
id|cifs_close
comma
dot
id|lock
op_assign
id|cifs_lock
comma
dot
id|fsync
op_assign
id|cifs_fsync
comma
dot
id|flush
op_assign
id|cifs_flush
comma
dot
id|mmap
op_assign
id|cifs_file_mmap
comma
dot
id|sendfile
op_assign
id|generic_file_sendfile
comma
)brace
suffix:semicolon
DECL|variable|cifs_dir_ops
r_struct
id|file_operations
id|cifs_dir_ops
op_assign
(brace
dot
id|readdir
op_assign
id|cifs_readdir
comma
dot
id|release
op_assign
id|cifs_closedir
comma
dot
id|read
op_assign
id|generic_read_dir
comma
)brace
suffix:semicolon
r_static
r_void
DECL|function|cifs_init_once
id|cifs_init_once
c_func
(paren
r_void
op_star
id|inode
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
id|cifsInodeInfo
op_star
id|cifsi
op_assign
(paren
r_struct
id|cifsInodeInfo
op_star
)paren
id|inode
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
(brace
id|inode_init_once
c_func
(paren
op_amp
id|cifsi-&gt;vfs_inode
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|cifsi-&gt;lockList
)paren
suffix:semicolon
)brace
)brace
r_int
DECL|function|cifs_init_inodecache
id|cifs_init_inodecache
c_func
(paren
r_void
)paren
(brace
id|cifs_inode_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;cifs_inode_cache&quot;
comma
r_sizeof
(paren
r_struct
id|cifsInodeInfo
)paren
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
comma
id|cifs_init_once
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cifs_inode_cachep
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|cifs_destroy_inodecache
id|cifs_destroy_inodecache
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|kmem_cache_destroy
c_func
(paren
id|cifs_inode_cachep
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;cifs_inode_cache: error freeing&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_int
DECL|function|cifs_init_request_bufs
id|cifs_init_request_bufs
c_func
(paren
r_void
)paren
(brace
id|cifs_req_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;cifs_request&quot;
comma
id|CIFS_MAX_MSGSIZE
op_plus
id|MAX_CIFS_HDR_SIZE
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cifs_req_cachep
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|cifs_destroy_request_bufs
id|cifs_destroy_request_bufs
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|kmem_cache_destroy
c_func
(paren
id|cifs_req_cachep
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;cifs_destroy_request_cache: error not all structures were freed&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_int
DECL|function|cifs_init_mids
id|cifs_init_mids
c_func
(paren
r_void
)paren
(brace
id|cifs_mid_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;cifs_mpx_ids&quot;
comma
r_sizeof
(paren
r_struct
id|mid_q_entry
)paren
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cifs_mid_cachep
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|cifs_destroy_mids
id|cifs_destroy_mids
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|kmem_cache_destroy
c_func
(paren
id|cifs_mid_cachep
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;cifs_destroy_mids: error not all structures were freed&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|init_cifs
id|init_cifs
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
macro_line|#if CONFIG_PROC_FS
id|cifs_proc_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|GlobalServerList
)paren
suffix:semicolon
multiline_comment|/* BB not implemented yet */
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|GlobalSMBSessionList
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|GlobalTreeConnectionList
)paren
suffix:semicolon
multiline_comment|/*&n; *  Initialize Global counters&n; */
id|atomic_set
c_func
(paren
op_amp
id|sesInfoAllocCount
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|tconInfoAllocCount
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|bufAllocCount
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|midCount
comma
l_int|0
)paren
suffix:semicolon
id|GlobalCurrentXid
op_assign
l_int|0
suffix:semicolon
id|GlobalTotalActiveXid
op_assign
l_int|0
suffix:semicolon
id|GlobalMaxActiveXid
op_assign
l_int|0
suffix:semicolon
id|GlobalSMBSeslock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
id|GlobalMid_Lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
id|rc
op_assign
id|cifs_init_inodecache
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
(brace
id|rc
op_assign
id|cifs_init_mids
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
(brace
id|rc
op_assign
id|cifs_init_request_bufs
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
(brace
id|rc
op_assign
id|register_filesystem
c_func
(paren
op_amp
id|cifs_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
r_return
id|rc
suffix:semicolon
multiline_comment|/* Success */
r_else
id|cifs_destroy_request_bufs
c_func
(paren
)paren
suffix:semicolon
)brace
id|cifs_destroy_mids
c_func
(paren
)paren
suffix:semicolon
)brace
id|cifs_destroy_inodecache
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#if CONFIG_PROC_FS
id|cifs_proc_clean
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|rc
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|exit_cifs
id|exit_cifs
c_func
(paren
r_void
)paren
(brace
id|cFYI
c_func
(paren
l_int|0
comma
(paren
l_string|&quot;In unregister ie exit_cifs&quot;
)paren
)paren
suffix:semicolon
macro_line|#if CONFIG_PROC_FS
id|cifs_proc_clean
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|unregister_filesystem
c_func
(paren
op_amp
id|cifs_fs_type
)paren
suffix:semicolon
id|cifs_destroy_inodecache
c_func
(paren
)paren
suffix:semicolon
id|cifs_destroy_mids
c_func
(paren
)paren
suffix:semicolon
id|cifs_destroy_request_bufs
c_func
(paren
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Steve French &lt;sfrench@us.ibm.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/* combination of LGPL + GPL source behaves as GPL */
id|MODULE_DESCRIPTION
(paren
l_string|&quot;VFS to access servers complying with the SNIA CIFS Specification e.g. Samba and Windows&quot;
)paren
suffix:semicolon
id|module_init
c_func
(paren
id|init_cifs
)paren
id|module_exit
c_func
(paren
id|exit_cifs
)paren
eof
