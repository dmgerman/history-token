multiline_comment|/*&n; *   Copyright (c) International Business Machines Corp., 2000-2002&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#ifndef _H_JFS_INCORE
DECL|macro|_H_JFS_INCORE
mdefine_line|#define _H_JFS_INCORE
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &quot;jfs_types.h&quot;
macro_line|#include &quot;jfs_xtree.h&quot;
macro_line|#include &quot;jfs_dtree.h&quot;
multiline_comment|/*&n; * JFS magic number&n; */
DECL|macro|JFS_SUPER_MAGIC
mdefine_line|#define JFS_SUPER_MAGIC 0x3153464a /* &quot;JFS1&quot; */
multiline_comment|/*&n; * Due to header ordering problems this can&squot;t be in jfs_lock.h&n; */
DECL|struct|jfs_rwlock
r_typedef
r_struct
id|jfs_rwlock
(brace
DECL|member|rw_sem
r_struct
id|rw_semaphore
id|rw_sem
suffix:semicolon
DECL|member|in_use
id|atomic_t
id|in_use
suffix:semicolon
multiline_comment|/* for hacked implementation of trylock */
DECL|typedef|jfs_rwlock_t
)brace
id|jfs_rwlock_t
suffix:semicolon
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
DECL|member|pad
id|unchar
id|pad
suffix:semicolon
multiline_comment|/* pad&t;&t;&t;*/
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
DECL|member|anon_inode_list
r_struct
id|list_head
id|anon_inode_list
suffix:semicolon
multiline_comment|/* inodes having anonymous txns */
DECL|member|mp_list
r_struct
id|list_head
id|mp_list
suffix:semicolon
multiline_comment|/* metapages in inode&squot;s address space */
DECL|member|rdwrlock
id|jfs_rwlock_t
id|rdwrlock
suffix:semicolon
multiline_comment|/* read/write lock&t;*/
DECL|member|xtlid
id|lid_t
id|xtlid
suffix:semicolon
multiline_comment|/* lid of xtree lock on directory */
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
id|dir_table_slot_t
id|_table
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* 96: directory index */
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
DECL|member|link
)brace
id|link
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
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
multiline_comment|/*&n; * cflag&n; */
DECL|enum|cflags
r_enum
id|cflags
(brace
DECL|enumerator|COMMIT_New
id|COMMIT_New
comma
multiline_comment|/* never committed inode   */
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
DECL|enumerator|COMMIT_Holdlock
id|COMMIT_Holdlock
comma
multiline_comment|/* Hold the IWRITE_LOCK until commit is done */
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
DECL|member|mntflag
r_int
r_int
id|mntflag
suffix:semicolon
multiline_comment|/* 4: aggregate attributes&t;*/
DECL|member|ipbmap
r_struct
id|inode
op_star
id|ipbmap
suffix:semicolon
multiline_comment|/* 4: block map inode&t;&t;*/
DECL|member|ipaimap
r_struct
id|inode
op_star
id|ipaimap
suffix:semicolon
multiline_comment|/* 4: aggregate inode map inode&t;*/
DECL|member|ipaimap2
r_struct
id|inode
op_star
id|ipaimap2
suffix:semicolon
multiline_comment|/* 4: secondary aimap inode&t;*/
DECL|member|ipimap
r_struct
id|inode
op_star
id|ipimap
suffix:semicolon
multiline_comment|/* 4: aggregate inode map inode&t;*/
DECL|member|log
r_struct
id|jfs_log
op_star
id|log
suffix:semicolon
multiline_comment|/* 4: log&t;&t;&t;*/
DECL|member|bsize
r_int
id|bsize
suffix:semicolon
multiline_comment|/* 2: logical block size&t;*/
DECL|member|l2bsize
r_int
id|l2bsize
suffix:semicolon
multiline_comment|/* 2: log2 logical block size&t;*/
DECL|member|nbperpage
r_int
id|nbperpage
suffix:semicolon
multiline_comment|/* 2: blocks per page&t;&t;*/
DECL|member|l2nbperpage
r_int
id|l2nbperpage
suffix:semicolon
multiline_comment|/* 2: log2 blocks per page&t;*/
DECL|member|l2niperblk
r_int
id|l2niperblk
suffix:semicolon
multiline_comment|/* 2: log2 inodes per page&t;*/
DECL|member|logdev
id|kdev_t
id|logdev
suffix:semicolon
multiline_comment|/* 2: external log device&t;*/
DECL|member|logpxd
id|pxd_t
id|logpxd
suffix:semicolon
multiline_comment|/* 8: pxd describing log&t;*/
DECL|member|ait2
id|pxd_t
id|ait2
suffix:semicolon
multiline_comment|/* 8: pxd describing AIT copy&t;*/
multiline_comment|/* Formerly in ipimap */
DECL|member|gengen
id|uint
id|gengen
suffix:semicolon
multiline_comment|/* 4: inode generation generator*/
DECL|member|inostamp
id|uint
id|inostamp
suffix:semicolon
multiline_comment|/* 4: shows inode belongs to fileset*/
multiline_comment|/* Formerly in ipbmap */
DECL|member|bmap
r_struct
id|bmap
op_star
id|bmap
suffix:semicolon
multiline_comment|/* 4: incore bmap descriptor&t;*/
DECL|member|nls_tab
r_struct
id|nls_table
op_star
id|nls_tab
suffix:semicolon
multiline_comment|/* 4: current codepage&t;&t;*/
DECL|member|direct_inode
r_struct
id|inode
op_star
id|direct_inode
suffix:semicolon
multiline_comment|/* 4: inode for physical I/O&t;*/
DECL|member|direct_mapping
r_struct
id|address_space
op_star
id|direct_mapping
suffix:semicolon
multiline_comment|/* 4: mapping for physical I/O */
DECL|member|state
id|uint
id|state
suffix:semicolon
multiline_comment|/* 4: mount/recovery state&t;*/
)brace
suffix:semicolon
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
DECL|macro|JFS_SBI
mdefine_line|#define JFS_SBI(sb)&t;((struct jfs_sb_info *)(sb)-&gt;u.generic_sbp)
DECL|macro|isReadOnly
mdefine_line|#define isReadOnly(ip)&t;((JFS_SBI((ip)-&gt;i_sb)-&gt;log) ? 0 : 1)
macro_line|#endif /* _H_JFS_INCORE */
eof
