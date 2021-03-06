multiline_comment|/*&n; *   Copyright (C) International Business Machines Corp., 2000-2004&n; *   Portions Copyright (C) Christoph Hellwig, 2001-2002&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#ifndef _H_JFS_INCORE
DECL|macro|_H_JFS_INCORE
mdefine_line|#define _H_JFS_INCORE
macro_line|#include &lt;linux/rwsem.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &quot;jfs_types.h&quot;
macro_line|#include &quot;jfs_xtree.h&quot;
macro_line|#include &quot;jfs_dtree.h&quot;
multiline_comment|/*&n; * JFS magic number&n; */
DECL|macro|JFS_SUPER_MAGIC
mdefine_line|#define JFS_SUPER_MAGIC 0x3153464a /* &quot;JFS1&quot; */
multiline_comment|/*&n; * JFS-private inode information&n; */
DECL|struct|jfs_inode_info
r_struct
id|jfs_inode_info
(brace
DECL|member|fileset
r_int
id|fileset
suffix:semicolon
multiline_comment|/* fileset number (always 16)*/
DECL|member|mode2
id|uint
id|mode2
suffix:semicolon
multiline_comment|/* jfs-specific mode&t;&t;*/
DECL|member|ixpxd
id|pxd_t
id|ixpxd
suffix:semicolon
multiline_comment|/* inode extent descriptor&t;*/
DECL|member|acl
id|dxd_t
id|acl
suffix:semicolon
multiline_comment|/* dxd describing acl&t;*/
DECL|member|ea
id|dxd_t
id|ea
suffix:semicolon
multiline_comment|/* dxd describing ea&t;*/
DECL|member|otime
id|time_t
id|otime
suffix:semicolon
multiline_comment|/* time created&t;*/
DECL|member|next_index
id|uint
id|next_index
suffix:semicolon
multiline_comment|/* next available directory entry index */
DECL|member|acltype
r_int
id|acltype
suffix:semicolon
multiline_comment|/* Type of ACL&t;*/
DECL|member|btorder
r_int
id|btorder
suffix:semicolon
multiline_comment|/* access order&t;*/
DECL|member|btindex
r_int
id|btindex
suffix:semicolon
multiline_comment|/* btpage entry index*/
DECL|member|ipimap
r_struct
id|inode
op_star
id|ipimap
suffix:semicolon
multiline_comment|/* inode map&t;&t;&t;*/
DECL|member|cflag
r_int
id|cflag
suffix:semicolon
multiline_comment|/* commit flags&t;&t;*/
DECL|member|bxflag
id|u16
id|bxflag
suffix:semicolon
multiline_comment|/* xflag of pseudo buffer?&t;*/
DECL|member|agno
id|unchar
id|agno
suffix:semicolon
multiline_comment|/* ag number&t;&t;&t;*/
DECL|member|active_ag
r_int
r_char
id|active_ag
suffix:semicolon
multiline_comment|/* ag currently allocating from&t;*/
DECL|member|blid
id|lid_t
id|blid
suffix:semicolon
multiline_comment|/* lid of pseudo buffer?&t;*/
DECL|member|atlhead
id|lid_t
id|atlhead
suffix:semicolon
multiline_comment|/* anonymous tlock list head&t;*/
DECL|member|atltail
id|lid_t
id|atltail
suffix:semicolon
multiline_comment|/* anonymous tlock list tail&t;*/
DECL|member|ag_lock
id|spinlock_t
id|ag_lock
suffix:semicolon
multiline_comment|/* protects active_ag&t;&t;*/
DECL|member|anon_inode_list
r_struct
id|list_head
id|anon_inode_list
suffix:semicolon
multiline_comment|/* inodes having anonymous txns */
multiline_comment|/*&n;&t; * rdwrlock serializes xtree between reads &amp; writes and synchronizes&n;&t; * changes to special inodes.  It&squot;s use would be redundant on&n;&t; * directories since the i_sem taken in the VFS is sufficient.&n;&t; */
DECL|member|rdwrlock
r_struct
id|rw_semaphore
id|rdwrlock
suffix:semicolon
multiline_comment|/*&n;&t; * commit_sem serializes transaction processing on an inode.&n;&t; * It must be taken after beginning a transaction (txBegin), since&n;&t; * dirty inodes may be committed while a new transaction on the&n;&t; * inode is blocked in txBegin or TxBeginAnon&n;&t; */
DECL|member|commit_sem
r_struct
id|semaphore
id|commit_sem
suffix:semicolon
multiline_comment|/* xattr_sem allows us to access the xattrs without taking i_sem */
DECL|member|xattr_sem
r_struct
id|rw_semaphore
id|xattr_sem
suffix:semicolon
DECL|member|xtlid
id|lid_t
id|xtlid
suffix:semicolon
multiline_comment|/* lid of xtree lock on directory */
macro_line|#ifdef CONFIG_JFS_POSIX_ACL
DECL|member|i_acl
r_struct
id|posix_acl
op_star
id|i_acl
suffix:semicolon
DECL|member|i_default_acl
r_struct
id|posix_acl
op_star
id|i_default_acl
suffix:semicolon
macro_line|#endif
r_union
(brace
r_struct
(brace
DECL|member|_xtroot
id|xtpage_t
id|_xtroot
suffix:semicolon
multiline_comment|/* 288: xtree root */
DECL|member|_imap
r_struct
id|inomap
op_star
id|_imap
suffix:semicolon
multiline_comment|/* 4: inode map header&t;*/
DECL|member|file
)brace
id|file
suffix:semicolon
r_struct
(brace
DECL|member|_table
r_struct
id|dir_table_slot
id|_table
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* 96: dir index */
DECL|member|_dtroot
id|dtroot_t
id|_dtroot
suffix:semicolon
multiline_comment|/* 288: dtree root */
DECL|member|dir
)brace
id|dir
suffix:semicolon
r_struct
(brace
DECL|member|_unused
id|unchar
id|_unused
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 16: */
DECL|member|_dxd
id|dxd_t
id|_dxd
suffix:semicolon
multiline_comment|/* 16: */
DECL|member|_inline
id|unchar
id|_inline
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* 128: inline symlink */
multiline_comment|/* _inline_ea may overlay the last part of&n;&t;&t;&t; * file._xtroot if maxentry = XTROOTINITSLOT&n;&t;&t;&t; */
DECL|member|_inline_ea
id|unchar
id|_inline_ea
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* 128: inline extended attr */
DECL|member|link
)brace
id|link
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|dev
id|u32
id|dev
suffix:semicolon
multiline_comment|/* will die when we get wide dev_t */
DECL|member|vfs_inode
r_struct
id|inode
id|vfs_inode
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|i_xtroot
mdefine_line|#define i_xtroot u.file._xtroot
DECL|macro|i_imap
mdefine_line|#define i_imap u.file._imap
DECL|macro|i_dirtable
mdefine_line|#define i_dirtable u.dir._table
DECL|macro|i_dtroot
mdefine_line|#define i_dtroot u.dir._dtroot
DECL|macro|i_inline
mdefine_line|#define i_inline u.link._inline
DECL|macro|i_inline_ea
mdefine_line|#define i_inline_ea u.link._inline_ea
DECL|macro|JFS_ACL_NOT_CACHED
mdefine_line|#define JFS_ACL_NOT_CACHED ((void *)-1)
DECL|macro|IREAD_LOCK
mdefine_line|#define IREAD_LOCK(ip)&t;&t;down_read(&amp;JFS_IP(ip)-&gt;rdwrlock)
DECL|macro|IREAD_UNLOCK
mdefine_line|#define IREAD_UNLOCK(ip)&t;up_read(&amp;JFS_IP(ip)-&gt;rdwrlock)
DECL|macro|IWRITE_LOCK
mdefine_line|#define IWRITE_LOCK(ip)&t;&t;down_write(&amp;JFS_IP(ip)-&gt;rdwrlock)
DECL|macro|IWRITE_UNLOCK
mdefine_line|#define IWRITE_UNLOCK(ip)&t;up_write(&amp;JFS_IP(ip)-&gt;rdwrlock)
multiline_comment|/*&n; * cflag&n; */
DECL|enum|cflags
r_enum
id|cflags
(brace
DECL|enumerator|COMMIT_Nolink
id|COMMIT_Nolink
comma
multiline_comment|/* inode committed with zero link count */
DECL|enumerator|COMMIT_Inlineea
id|COMMIT_Inlineea
comma
multiline_comment|/* commit inode inline EA */
DECL|enumerator|COMMIT_Freewmap
id|COMMIT_Freewmap
comma
multiline_comment|/* free WMAP at iClose() */
DECL|enumerator|COMMIT_Dirty
id|COMMIT_Dirty
comma
multiline_comment|/* Inode is really dirty */
DECL|enumerator|COMMIT_Dirtable
id|COMMIT_Dirtable
comma
multiline_comment|/* commit changes to di_dirtable */
DECL|enumerator|COMMIT_Stale
id|COMMIT_Stale
comma
multiline_comment|/* data extent is no longer valid */
DECL|enumerator|COMMIT_Synclist
id|COMMIT_Synclist
comma
multiline_comment|/* metadata pages on group commit synclist */
)brace
suffix:semicolon
DECL|macro|set_cflag
mdefine_line|#define set_cflag(flag, ip)&t;set_bit(flag, &amp;(JFS_IP(ip)-&gt;cflag))
DECL|macro|clear_cflag
mdefine_line|#define clear_cflag(flag, ip)&t;clear_bit(flag, &amp;(JFS_IP(ip)-&gt;cflag))
DECL|macro|test_cflag
mdefine_line|#define test_cflag(flag, ip)&t;test_bit(flag, &amp;(JFS_IP(ip)-&gt;cflag))
DECL|macro|test_and_clear_cflag
mdefine_line|#define test_and_clear_cflag(flag, ip) &bslash;&n;&t;test_and_clear_bit(flag, &amp;(JFS_IP(ip)-&gt;cflag))
multiline_comment|/*&n; * JFS-private superblock information.&n; */
DECL|struct|jfs_sb_info
r_struct
id|jfs_sb_info
(brace
DECL|member|sb
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
multiline_comment|/* Point back to vfs super block */
DECL|member|mntflag
r_int
r_int
id|mntflag
suffix:semicolon
multiline_comment|/* aggregate attributes&t;*/
DECL|member|ipbmap
r_struct
id|inode
op_star
id|ipbmap
suffix:semicolon
multiline_comment|/* block map inode&t;&t;*/
DECL|member|ipaimap
r_struct
id|inode
op_star
id|ipaimap
suffix:semicolon
multiline_comment|/* aggregate inode map inode&t;*/
DECL|member|ipaimap2
r_struct
id|inode
op_star
id|ipaimap2
suffix:semicolon
multiline_comment|/* secondary aimap inode&t;*/
DECL|member|ipimap
r_struct
id|inode
op_star
id|ipimap
suffix:semicolon
multiline_comment|/* aggregate inode map inode&t;*/
DECL|member|log
r_struct
id|jfs_log
op_star
id|log
suffix:semicolon
multiline_comment|/* log&t;&t;&t;*/
DECL|member|log_list
r_struct
id|list_head
id|log_list
suffix:semicolon
multiline_comment|/* volumes associated with a journal */
DECL|member|bsize
r_int
id|bsize
suffix:semicolon
multiline_comment|/* logical block size&t;*/
DECL|member|l2bsize
r_int
id|l2bsize
suffix:semicolon
multiline_comment|/* log2 logical block size&t;*/
DECL|member|nbperpage
r_int
id|nbperpage
suffix:semicolon
multiline_comment|/* blocks per page&t;&t;*/
DECL|member|l2nbperpage
r_int
id|l2nbperpage
suffix:semicolon
multiline_comment|/* log2 blocks per page&t;*/
DECL|member|l2niperblk
r_int
id|l2niperblk
suffix:semicolon
multiline_comment|/* log2 inodes per page&t;*/
DECL|member|logdev
id|dev_t
id|logdev
suffix:semicolon
multiline_comment|/* external log device&t;*/
DECL|member|aggregate
id|uint
id|aggregate
suffix:semicolon
multiline_comment|/* volume identifier in log record */
DECL|member|logpxd
id|pxd_t
id|logpxd
suffix:semicolon
multiline_comment|/* pxd describing log&t;*/
DECL|member|fsckpxd
id|pxd_t
id|fsckpxd
suffix:semicolon
multiline_comment|/* pxd describing fsck wkspc */
DECL|member|ait2
id|pxd_t
id|ait2
suffix:semicolon
multiline_comment|/* pxd describing AIT copy&t;*/
DECL|member|uuid
r_char
id|uuid
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 128-bit uuid for volume&t;*/
DECL|member|loguuid
r_char
id|loguuid
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 128-bit uuid for log&t;*/
multiline_comment|/*&n;&t; * commit_state is used for synchronization of the jfs_commit&n;&t; * threads.  It is protected by LAZY_LOCK().&n;&t; */
DECL|member|commit_state
r_int
id|commit_state
suffix:semicolon
multiline_comment|/* commit state */
multiline_comment|/* Formerly in ipimap */
DECL|member|gengen
id|uint
id|gengen
suffix:semicolon
multiline_comment|/* inode generation generator*/
DECL|member|inostamp
id|uint
id|inostamp
suffix:semicolon
multiline_comment|/* shows inode belongs to fileset*/
multiline_comment|/* Formerly in ipbmap */
DECL|member|bmap
r_struct
id|bmap
op_star
id|bmap
suffix:semicolon
multiline_comment|/* incore bmap descriptor&t;*/
DECL|member|nls_tab
r_struct
id|nls_table
op_star
id|nls_tab
suffix:semicolon
multiline_comment|/* current codepage&t;&t;*/
DECL|member|state
id|uint
id|state
suffix:semicolon
multiline_comment|/* mount/recovery state&t;*/
DECL|member|flag
r_int
r_int
id|flag
suffix:semicolon
multiline_comment|/* mount time flags */
DECL|member|p_state
id|uint
id|p_state
suffix:semicolon
multiline_comment|/* state prior to going no integrity */
)brace
suffix:semicolon
multiline_comment|/* jfs_sb_info commit_state */
DECL|macro|IN_LAZYCOMMIT
mdefine_line|#define IN_LAZYCOMMIT 1
DECL|function|JFS_IP
r_static
r_inline
r_struct
id|jfs_inode_info
op_star
id|JFS_IP
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
id|list_entry
c_func
(paren
id|inode
comma
r_struct
id|jfs_inode_info
comma
id|vfs_inode
)paren
suffix:semicolon
)brace
DECL|function|jfs_dirtable_inline
r_static
r_inline
r_int
id|jfs_dirtable_inline
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
(paren
id|JFS_IP
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|next_index
op_le
(paren
id|MAX_INLINE_DIRTABLE_ENTRY
op_plus
l_int|1
)paren
)paren
suffix:semicolon
)brace
DECL|function|JFS_SBI
r_static
r_inline
r_struct
id|jfs_sb_info
op_star
id|JFS_SBI
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_return
id|sb-&gt;s_fs_info
suffix:semicolon
)brace
DECL|function|isReadOnly
r_static
r_inline
r_int
id|isReadOnly
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_if
c_cond
(paren
id|JFS_SBI
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|log
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif /* _H_JFS_INCORE */
eof
