multiline_comment|/*&n; *   fs/cifs/cifsfs.c&n; *&n; *   Copyright (C) International Business Machines  Corp., 2002,2003&n; *   Author(s): Steve French (sfrench@us.ibm.com)&n; *&n; *   Common Internet FileSystem (CIFS) client&n; *&n; *   This library is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU Lesser General Public License as published&n; *   by the Free Software Foundation; either version 2.1 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This library is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU Lesser General Public License for more details.&n; *&n; *   You should have received a copy of the GNU Lesser General Public License&n; *   along with this library; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
multiline_comment|/* Note that BB means BUGBUG (ie something to fix eventually) */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mount.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
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
macro_line|#ifdef CIFS_QUOTA
DECL|variable|cifs_quotactl_ops
r_static
r_struct
id|quotactl_ops
id|cifs_quotactl_ops
suffix:semicolon
macro_line|#endif
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
l_int|1
suffix:semicolon
DECL|variable|quotaEnabled
r_int
r_int
id|quotaEnabled
op_assign
l_int|0
suffix:semicolon
DECL|variable|linuxExtEnabled
r_int
r_int
id|linuxExtEnabled
op_assign
l_int|1
suffix:semicolon
DECL|variable|lookupCacheEnabled
r_int
r_int
id|lookupCacheEnabled
op_assign
l_int|1
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
l_int|1
suffix:semicolon
DECL|variable|CIFSMaximumBufferSize
r_int
r_int
id|CIFSMaximumBufferSize
op_assign
id|CIFS_MAX_MSGSIZE
suffix:semicolon
DECL|variable|oplockThread
r_struct
id|task_struct
op_star
id|oplockThread
op_assign
l_int|NULL
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
r_const
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
id|DECLARE_COMPLETION
c_func
(paren
id|cifs_oplock_exited
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
r_const
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
id|sb-&gt;s_flags
op_or_assign
id|MS_NODIRATIME
suffix:semicolon
multiline_comment|/* and probably even noatime */
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
r_else
id|memset
c_func
(paren
id|cifs_sb
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|cifs_sb_info
)paren
)paren
suffix:semicolon
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
multiline_comment|/*&t;if(cifs_sb-&gt;tcon-&gt;ses-&gt;server-&gt;maxBuf &gt; MAX_CIFS_HDR_SIZE + 512)&n;&t;    sb-&gt;s_blocksize = cifs_sb-&gt;tcon-&gt;ses-&gt;server-&gt;maxBuf - MAX_CIFS_HDR_SIZE; */
macro_line|#ifdef CIFS_QUOTA
id|sb-&gt;s_qcop
op_assign
op_amp
id|cifs_quotactl_ops
suffix:semicolon
macro_line|#endif
id|sb-&gt;s_blocksize
op_assign
id|CIFS_MAX_MSGSIZE
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
(brace
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out_no_root
suffix:semicolon
)brace
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
(brace
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out_no_root
suffix:semicolon
)brace
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
id|cifs_sb-&gt;local_nls
)paren
(brace
id|unload_nls
c_func
(paren
id|cifs_sb-&gt;local_nls
)paren
suffix:semicolon
)brace
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
id|rc
suffix:semicolon
)brace
r_static
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
r_static
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
id|kstatfs
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
l_int|0
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
comma
r_struct
id|nameidata
op_star
id|nd
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
DECL|variable|cifs_oplock_cachep
id|kmem_cache_t
op_star
id|cifs_oplock_cachep
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
multiline_comment|/* Until the file is open and we have gotten oplock&n;&t;info back from the server, can not assume caching of&n;&t;file data or metadata */
id|cifs_inode-&gt;clientCanCacheRead
op_assign
id|FALSE
suffix:semicolon
id|cifs_inode-&gt;clientCanCacheAll
op_assign
id|FALSE
suffix:semicolon
id|cifs_inode-&gt;vfs_inode.i_blksize
op_assign
id|CIFS_MAX_MSGSIZE
suffix:semicolon
id|cifs_inode-&gt;vfs_inode.i_blkbits
op_assign
l_int|14
suffix:semicolon
multiline_comment|/* 2**14 = CIFS_MAX_MSGSIZE */
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
multiline_comment|/*&n; * cifs_show_options() is for displaying mount options in /proc/mounts.&n; * Not all settable options are displayed but most of the important&n; * ones are.&n; */
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
(brace
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
l_string|&quot;,unc=%s&quot;
comma
id|cifs_sb-&gt;tcon-&gt;treeName
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cifs_sb-&gt;tcon-&gt;ses
)paren
op_logical_and
(paren
id|cifs_sb-&gt;tcon-&gt;ses-&gt;userName
)paren
)paren
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot;,username=%s&quot;
comma
id|cifs_sb-&gt;tcon-&gt;ses-&gt;userName
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cifs_sb-&gt;tcon-&gt;ses-&gt;domainName
)paren
(brace
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot;,domain=%s&quot;
comma
id|cifs_sb-&gt;tcon-&gt;ses-&gt;domainName
)paren
suffix:semicolon
)brace
)brace
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot;,rsize=%d&quot;
comma
id|cifs_sb-&gt;rsize
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot;,wsize=%d&quot;
comma
id|cifs_sb-&gt;wsize
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CIFS_QUOTA
DECL|function|cifs_xquota_set
r_int
id|cifs_xquota_set
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|quota_type
comma
id|qid_t
id|qid
comma
r_struct
id|fs_disk_quota
op_star
id|pdquota
)paren
(brace
r_int
id|xid
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_struct
id|cifs_sb_info
op_star
id|cifs_sb
op_assign
id|CIFS_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
r_struct
id|cifsTconInfo
op_star
id|pTcon
suffix:semicolon
r_if
c_cond
(paren
id|cifs_sb
)paren
(brace
id|pTcon
op_assign
id|cifs_sb-&gt;tcon
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EIO
suffix:semicolon
id|xid
op_assign
id|GetXid
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pTcon
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;set type: 0x%x id: %d&quot;
comma
id|quota_type
comma
id|qid
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|FreeXid
c_func
(paren
id|xid
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|cifs_xquota_get
r_int
id|cifs_xquota_get
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|quota_type
comma
id|qid_t
id|qid
comma
r_struct
id|fs_disk_quota
op_star
id|pdquota
)paren
(brace
r_int
id|xid
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_struct
id|cifs_sb_info
op_star
id|cifs_sb
op_assign
id|CIFS_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
r_struct
id|cifsTconInfo
op_star
id|pTcon
suffix:semicolon
r_if
c_cond
(paren
id|cifs_sb
)paren
(brace
id|pTcon
op_assign
id|cifs_sb-&gt;tcon
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EIO
suffix:semicolon
id|xid
op_assign
id|GetXid
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pTcon
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;set type: 0x%x id: %d&quot;
comma
id|quota_type
comma
id|qid
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
id|FreeXid
c_func
(paren
id|xid
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|cifs_xstate_set
r_int
id|cifs_xstate_set
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|flags
comma
r_int
id|operation
)paren
(brace
r_int
id|xid
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_struct
id|cifs_sb_info
op_star
id|cifs_sb
op_assign
id|CIFS_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
r_struct
id|cifsTconInfo
op_star
id|pTcon
suffix:semicolon
r_if
c_cond
(paren
id|cifs_sb
)paren
(brace
id|pTcon
op_assign
id|cifs_sb-&gt;tcon
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EIO
suffix:semicolon
id|xid
op_assign
id|GetXid
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pTcon
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;flags: 0x%x operation: 0x%x&quot;
comma
id|flags
comma
id|operation
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
id|FreeXid
c_func
(paren
id|xid
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|cifs_xstate_get
r_int
id|cifs_xstate_get
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|fs_quota_stat
op_star
id|qstats
)paren
(brace
r_int
id|xid
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_struct
id|cifs_sb_info
op_star
id|cifs_sb
op_assign
id|CIFS_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
r_struct
id|cifsTconInfo
op_star
id|pTcon
suffix:semicolon
r_if
c_cond
(paren
id|cifs_sb
)paren
(brace
id|pTcon
op_assign
id|cifs_sb-&gt;tcon
suffix:semicolon
)brace
r_else
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|xid
op_assign
id|GetXid
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pTcon
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;pqstats %p&quot;
comma
id|qstats
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
id|FreeXid
c_func
(paren
id|xid
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|variable|cifs_quotactl_ops
r_static
r_struct
id|quotactl_ops
id|cifs_quotactl_ops
op_assign
(brace
dot
id|set_xquota
op_assign
id|cifs_xquota_set
comma
dot
id|get_xquota
op_assign
id|cifs_xquota_set
comma
dot
id|set_xstate
op_assign
id|cifs_xstate_set
comma
dot
id|get_xstate
op_assign
id|cifs_xstate_get
comma
)brace
suffix:semicolon
macro_line|#endif
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
r_static
id|ssize_t
DECL|function|cifs_read_wrapper
id|cifs_read_wrapper
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|read_data
comma
r_int
id|read_size
comma
id|loff_t
op_star
id|poffset
)paren
(brace
r_if
c_cond
(paren
id|file
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|file-&gt;f_dentry
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|file-&gt;f_dentry-&gt;d_inode
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|CIFS_I
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
op_member_access_from_pointer
id|clientCanCacheRead
)paren
(brace
r_return
id|generic_file_read
c_func
(paren
id|file
comma
id|read_data
comma
id|read_size
comma
id|poffset
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* BB do we need to lock inode from here until after invalidate? */
r_if
c_cond
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_mapping
)paren
(brace
id|filemap_fdatawrite
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_mapping
)paren
suffix:semicolon
id|filemap_fdatawait
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_mapping
)paren
suffix:semicolon
)brace
multiline_comment|/* force read from the server since we do not have oplock */
multiline_comment|/* BB we should relax this and do it on a timer and call cifs_revalidate */
multiline_comment|/* BB we should make timer configurable */
id|invalidate_remote_inode
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
r_return
id|generic_file_read
c_func
(paren
id|file
comma
id|read_data
comma
id|read_size
comma
id|poffset
)paren
suffix:semicolon
)brace
)brace
r_static
id|ssize_t
DECL|function|cifs_write_wrapper
id|cifs_write_wrapper
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|write_data
comma
r_int
id|write_size
comma
id|loff_t
op_star
id|poffset
)paren
(brace
id|ssize_t
id|written
suffix:semicolon
r_if
c_cond
(paren
id|file
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|file-&gt;f_dentry
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|file-&gt;f_dentry-&gt;d_inode
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/* check whether we can cache writes locally */
id|written
op_assign
id|generic_file_write
c_func
(paren
id|file
comma
id|write_data
comma
id|write_size
comma
id|poffset
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|CIFS_I
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
op_member_access_from_pointer
id|clientCanCacheAll
)paren
(brace
r_if
c_cond
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_mapping
)paren
(brace
id|filemap_fdatawrite
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_mapping
)paren
suffix:semicolon
)brace
)brace
r_return
id|written
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
dot
id|mknod
op_assign
id|cifs_mknod
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
id|cifs_read_wrapper
comma
dot
id|write
op_assign
id|cifs_write_wrapper
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
r_static
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
op_or
id|SLAB_RECLAIM_ACCOUNT
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
r_static
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
r_static
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
r_static
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
r_static
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
id|cifs_oplock_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;cifs_oplock_structs&quot;
comma
r_sizeof
(paren
r_struct
id|oplock_q_entry
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
id|cifs_oplock_cachep
op_eq
l_int|NULL
)paren
(brace
id|kmem_cache_destroy
c_func
(paren
id|cifs_mid_cachep
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
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
r_if
c_cond
(paren
id|kmem_cache_destroy
c_func
(paren
id|cifs_oplock_cachep
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;error not all oplock structures were freed&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|cifs_oplock_thread
r_static
r_int
id|cifs_oplock_thread
c_func
(paren
r_void
op_star
id|dummyarg
)paren
(brace
r_struct
id|oplock_q_entry
op_star
id|oplock_item
suffix:semicolon
r_struct
id|cifsTconInfo
op_star
id|pTcon
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|__u16
id|netfid
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|daemonize
c_func
(paren
l_string|&quot;cifsoplockd&quot;
)paren
suffix:semicolon
id|allow_signal
c_func
(paren
id|SIGTERM
)paren
suffix:semicolon
id|oplockThread
op_assign
id|current
suffix:semicolon
r_do
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|1
op_star
id|HZ
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|GlobalOplock_Q
)paren
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|39
op_star
id|HZ
)paren
suffix:semicolon
)brace
r_else
(brace
id|oplock_item
op_assign
id|list_entry
c_func
(paren
id|GlobalOplock_Q.next
comma
r_struct
id|oplock_q_entry
comma
id|qhead
)paren
suffix:semicolon
r_if
c_cond
(paren
id|oplock_item
)paren
(brace
id|pTcon
op_assign
id|oplock_item-&gt;tcon
suffix:semicolon
id|inode
op_assign
id|oplock_item-&gt;pinode
suffix:semicolon
id|netfid
op_assign
id|oplock_item-&gt;netfid
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
id|DeleteOplockQEntry
c_func
(paren
id|oplock_item
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
id|rc
op_assign
id|filemap_fdatawrite
c_func
(paren
id|inode-&gt;i_mapping
)paren
suffix:semicolon
r_if
c_cond
(paren
id|CIFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|clientCanCacheRead
op_eq
l_int|0
)paren
(brace
id|invalidate_remote_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
)brace
r_else
id|rc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
id|CIFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|write_behind_rc
op_assign
id|rc
suffix:semicolon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Oplock flush inode %p rc %d&quot;
comma
id|inode
comma
id|rc
)paren
)paren
suffix:semicolon
multiline_comment|/* releasing a stale oplock after recent reconnection &n;&t;&t;&t;&t;of smb session using a now incorrect file &n;&t;&t;&t;&t;handle is not a data integrity issue but do  &n;&t;&t;&t;&t;not bother sending an oplock release if session &n;&t;&t;&t;&t;to server still is disconnected since oplock &n;&t;&t;&t;&t;already released by the server in that case */
r_if
c_cond
(paren
id|pTcon-&gt;tidStatus
op_ne
id|CifsNeedReconnect
)paren
(brace
id|rc
op_assign
id|CIFSSMBLock
c_func
(paren
l_int|0
comma
id|pTcon
comma
id|netfid
comma
l_int|0
multiline_comment|/* len */
comma
l_int|0
multiline_comment|/* offset */
comma
l_int|0
comma
l_int|0
comma
id|LOCKING_ANDX_OPLOCK_RELEASE
comma
l_int|0
multiline_comment|/* wait flag */
)paren
suffix:semicolon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Oplock release rc = %d &quot;
comma
id|rc
)paren
)paren
suffix:semicolon
)brace
)brace
r_else
id|spin_unlock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
op_logical_neg
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
suffix:semicolon
)brace
id|complete_and_exit
(paren
op_amp
id|cifs_oplock_exited
comma
l_int|0
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
macro_line|#ifdef CONFIG_PROC_FS
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
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|GlobalOplock_Q
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
id|tcpSesReconnectCount
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|tconInfoReconnectCount
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
id|SPIN_LOCK_UNLOCKED
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
(brace
id|kernel_thread
c_func
(paren
id|cifs_oplock_thread
comma
l_int|NULL
comma
id|CLONE_FS
op_or
id|CLONE_FILES
op_or
id|CLONE_VM
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
multiline_comment|/* Success */
)brace
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
macro_line|#ifdef CONFIG_PROC_FS
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
macro_line|#ifdef CONFIG_PROC_FS
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
r_if
c_cond
(paren
id|oplockThread
)paren
(brace
id|send_sig
c_func
(paren
id|SIGTERM
comma
id|oplockThread
comma
l_int|1
)paren
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|cifs_oplock_exited
)paren
suffix:semicolon
)brace
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
