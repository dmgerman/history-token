multiline_comment|/*&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#include &quot;xfs.h&quot;
macro_line|#include &quot;xfs_fs.h&quot;
macro_line|#include &quot;xfs_inum.h&quot;
macro_line|#include &quot;xfs_log.h&quot;
macro_line|#include &quot;xfs_trans.h&quot;
macro_line|#include &quot;xfs_sb.h&quot;
macro_line|#include &quot;xfs_ag.h&quot;
macro_line|#include &quot;xfs_dir.h&quot;
macro_line|#include &quot;xfs_dir2.h&quot;
macro_line|#include &quot;xfs_alloc.h&quot;
macro_line|#include &quot;xfs_dmapi.h&quot;
macro_line|#include &quot;xfs_quota.h&quot;
macro_line|#include &quot;xfs_mount.h&quot;
macro_line|#include &quot;xfs_alloc_btree.h&quot;
macro_line|#include &quot;xfs_bmap_btree.h&quot;
macro_line|#include &quot;xfs_ialloc_btree.h&quot;
macro_line|#include &quot;xfs_btree.h&quot;
macro_line|#include &quot;xfs_ialloc.h&quot;
macro_line|#include &quot;xfs_attr_sf.h&quot;
macro_line|#include &quot;xfs_dir_sf.h&quot;
macro_line|#include &quot;xfs_dir2_sf.h&quot;
macro_line|#include &quot;xfs_dinode.h&quot;
macro_line|#include &quot;xfs_inode.h&quot;
macro_line|#include &quot;xfs_bmap.h&quot;
macro_line|#include &quot;xfs_bit.h&quot;
macro_line|#include &quot;xfs_rtalloc.h&quot;
macro_line|#include &quot;xfs_error.h&quot;
macro_line|#include &quot;xfs_itable.h&quot;
macro_line|#include &quot;xfs_rw.h&quot;
macro_line|#include &quot;xfs_acl.h&quot;
macro_line|#include &quot;xfs_cap.h&quot;
macro_line|#include &quot;xfs_mac.h&quot;
macro_line|#include &quot;xfs_attr.h&quot;
macro_line|#include &quot;xfs_buf_item.h&quot;
macro_line|#include &quot;xfs_trans_space.h&quot;
macro_line|#include &quot;xfs_utils.h&quot;
macro_line|#include &quot;xfs_iomap.h&quot;
DECL|macro|XFS_WRITEIO_ALIGN
mdefine_line|#define XFS_WRITEIO_ALIGN(mp,off)&t;(((off) &gt;&gt; mp-&gt;m_writeio_log) &bslash;&n;&t;&t;&t;&t;&t;&t;&lt;&lt; mp-&gt;m_writeio_log)
DECL|macro|XFS_STRAT_WRITE_IMAPS
mdefine_line|#define XFS_STRAT_WRITE_IMAPS&t;2
DECL|macro|XFS_WRITE_IMAPS
mdefine_line|#define XFS_WRITE_IMAPS&t;&t;XFS_BMAP_MAX_NMAP
id|STATIC
r_int
DECL|function|xfs_imap_to_bmap
id|xfs_imap_to_bmap
c_func
(paren
id|xfs_iocore_t
op_star
id|io
comma
id|xfs_off_t
id|offset
comma
id|xfs_bmbt_irec_t
op_star
id|imap
comma
id|xfs_iomap_t
op_star
id|iomapp
comma
r_int
id|imaps
comma
multiline_comment|/* Number of imap entries */
r_int
id|iomaps
comma
multiline_comment|/* Number of iomap entries */
r_int
id|flags
)paren
(brace
id|xfs_mount_t
op_star
id|mp
suffix:semicolon
id|xfs_fsize_t
id|nisize
suffix:semicolon
r_int
id|pbm
suffix:semicolon
id|xfs_fsblock_t
id|start_block
suffix:semicolon
id|mp
op_assign
id|io-&gt;io_mount
suffix:semicolon
id|nisize
op_assign
id|XFS_SIZE
c_func
(paren
id|mp
comma
id|io
)paren
suffix:semicolon
r_if
c_cond
(paren
id|io-&gt;io_new_size
OG
id|nisize
)paren
id|nisize
op_assign
id|io-&gt;io_new_size
suffix:semicolon
r_for
c_loop
(paren
id|pbm
op_assign
l_int|0
suffix:semicolon
id|imaps
op_logical_and
id|pbm
OL
id|iomaps
suffix:semicolon
id|imaps
op_decrement
comma
id|iomapp
op_increment
comma
id|imap
op_increment
comma
id|pbm
op_increment
)paren
(brace
id|iomapp-&gt;iomap_target
op_assign
id|io-&gt;io_flags
op_amp
id|XFS_IOCORE_RT
ques
c_cond
id|mp-&gt;m_rtdev_targp
suffix:colon
id|mp-&gt;m_ddev_targp
suffix:semicolon
id|iomapp-&gt;iomap_offset
op_assign
id|XFS_FSB_TO_B
c_func
(paren
id|mp
comma
id|imap-&gt;br_startoff
)paren
suffix:semicolon
id|iomapp-&gt;iomap_delta
op_assign
id|offset
op_minus
id|iomapp-&gt;iomap_offset
suffix:semicolon
id|iomapp-&gt;iomap_bsize
op_assign
id|XFS_FSB_TO_B
c_func
(paren
id|mp
comma
id|imap-&gt;br_blockcount
)paren
suffix:semicolon
id|iomapp-&gt;iomap_flags
op_assign
id|flags
suffix:semicolon
id|start_block
op_assign
id|imap-&gt;br_startblock
suffix:semicolon
r_if
c_cond
(paren
id|start_block
op_eq
id|HOLESTARTBLOCK
)paren
(brace
id|iomapp-&gt;iomap_bn
op_assign
id|IOMAP_DADDR_NULL
suffix:semicolon
id|iomapp-&gt;iomap_flags
op_assign
id|IOMAP_HOLE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|start_block
op_eq
id|DELAYSTARTBLOCK
)paren
(brace
id|iomapp-&gt;iomap_bn
op_assign
id|IOMAP_DADDR_NULL
suffix:semicolon
id|iomapp-&gt;iomap_flags
op_assign
id|IOMAP_DELAY
suffix:semicolon
)brace
r_else
(brace
id|iomapp-&gt;iomap_bn
op_assign
id|XFS_FSB_TO_DB_IO
c_func
(paren
id|io
comma
id|start_block
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ISUNWRITTEN
c_func
(paren
id|imap
)paren
)paren
id|iomapp-&gt;iomap_flags
op_or_assign
id|IOMAP_UNWRITTEN
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|iomapp-&gt;iomap_offset
op_plus
id|iomapp-&gt;iomap_bsize
)paren
op_ge
id|nisize
)paren
(brace
id|iomapp-&gt;iomap_flags
op_or_assign
id|IOMAP_EOF
suffix:semicolon
)brace
id|offset
op_add_assign
id|iomapp-&gt;iomap_bsize
op_minus
id|iomapp-&gt;iomap_delta
suffix:semicolon
)brace
r_return
id|pbm
suffix:semicolon
multiline_comment|/* Return the number filled */
)brace
r_int
DECL|function|xfs_iomap
id|xfs_iomap
c_func
(paren
id|xfs_iocore_t
op_star
id|io
comma
id|xfs_off_t
id|offset
comma
id|ssize_t
id|count
comma
r_int
id|flags
comma
id|xfs_iomap_t
op_star
id|iomapp
comma
r_int
op_star
id|niomaps
)paren
(brace
id|xfs_mount_t
op_star
id|mp
op_assign
id|io-&gt;io_mount
suffix:semicolon
id|xfs_fileoff_t
id|offset_fsb
comma
id|end_fsb
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_int
id|lockmode
op_assign
l_int|0
suffix:semicolon
id|xfs_bmbt_irec_t
id|imap
suffix:semicolon
r_int
id|nimaps
op_assign
l_int|1
suffix:semicolon
r_int
id|bmapi_flags
op_assign
l_int|0
suffix:semicolon
r_int
id|iomap_flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|XFS_FORCED_SHUTDOWN
c_func
(paren
id|mp
)paren
)paren
r_return
id|XFS_ERROR
c_func
(paren
id|EIO
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|flags
op_amp
(paren
id|BMAPI_READ
op_or
id|BMAPI_WRITE
op_or
id|BMAPI_ALLOCATE
op_or
id|BMAPI_UNWRITTEN
op_or
id|BMAPI_DEVICE
)paren
)paren
(brace
r_case
id|BMAPI_READ
suffix:colon
id|lockmode
op_assign
id|XFS_LCK_MAP_SHARED
c_func
(paren
id|mp
comma
id|io
)paren
suffix:semicolon
id|bmapi_flags
op_assign
id|XFS_BMAPI_ENTIRE
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|BMAPI_IGNSTATE
)paren
id|bmapi_flags
op_or_assign
id|XFS_BMAPI_IGSTATE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BMAPI_WRITE
suffix:colon
id|lockmode
op_assign
id|XFS_ILOCK_EXCL
op_or
id|XFS_EXTSIZE_WR
suffix:semicolon
id|bmapi_flags
op_assign
l_int|0
suffix:semicolon
id|XFS_ILOCK
c_func
(paren
id|mp
comma
id|io
comma
id|lockmode
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BMAPI_ALLOCATE
suffix:colon
id|lockmode
op_assign
id|XFS_ILOCK_SHARED
op_or
id|XFS_EXTSIZE_RD
suffix:semicolon
id|bmapi_flags
op_assign
id|XFS_BMAPI_ENTIRE
suffix:semicolon
multiline_comment|/* Attempt non-blocking lock */
r_if
c_cond
(paren
id|flags
op_amp
id|BMAPI_TRYLOCK
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|XFS_ILOCK_NOWAIT
c_func
(paren
id|mp
comma
id|io
comma
id|lockmode
)paren
)paren
r_return
id|XFS_ERROR
c_func
(paren
id|EAGAIN
)paren
suffix:semicolon
)brace
r_else
(brace
id|XFS_ILOCK
c_func
(paren
id|mp
comma
id|io
comma
id|lockmode
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|BMAPI_UNWRITTEN
suffix:colon
r_goto
id|phase2
suffix:semicolon
r_case
id|BMAPI_DEVICE
suffix:colon
id|lockmode
op_assign
id|XFS_LCK_MAP_SHARED
c_func
(paren
id|mp
comma
id|io
)paren
suffix:semicolon
id|iomapp-&gt;iomap_target
op_assign
id|io-&gt;io_flags
op_amp
id|XFS_IOCORE_RT
ques
c_cond
id|mp-&gt;m_rtdev_targp
suffix:colon
id|mp-&gt;m_ddev_targp
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
op_star
id|niomaps
op_assign
l_int|1
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|ASSERT
c_func
(paren
id|offset
op_le
id|mp-&gt;m_maxioffset
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|xfs_fsize_t
)paren
id|offset
op_plus
id|count
OG
id|mp-&gt;m_maxioffset
)paren
id|count
op_assign
id|mp-&gt;m_maxioffset
op_minus
id|offset
suffix:semicolon
id|end_fsb
op_assign
id|XFS_B_TO_FSB
c_func
(paren
id|mp
comma
(paren
id|xfs_ufsize_t
)paren
id|offset
op_plus
id|count
)paren
suffix:semicolon
id|offset_fsb
op_assign
id|XFS_B_TO_FSBT
c_func
(paren
id|mp
comma
id|offset
)paren
suffix:semicolon
id|error
op_assign
id|XFS_BMAPI
c_func
(paren
id|mp
comma
l_int|NULL
comma
id|io
comma
id|offset_fsb
comma
(paren
id|xfs_filblks_t
)paren
(paren
id|end_fsb
op_minus
id|offset_fsb
)paren
comma
id|bmapi_flags
comma
l_int|NULL
comma
l_int|0
comma
op_amp
id|imap
comma
op_amp
id|nimaps
comma
l_int|NULL
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
id|phase2
suffix:colon
r_switch
c_cond
(paren
id|flags
op_amp
(paren
id|BMAPI_WRITE
op_or
id|BMAPI_ALLOCATE
op_or
id|BMAPI_UNWRITTEN
)paren
)paren
(brace
r_case
id|BMAPI_WRITE
suffix:colon
multiline_comment|/* If we found an extent, return it */
r_if
c_cond
(paren
id|nimaps
op_logical_and
(paren
id|imap.br_startblock
op_ne
id|HOLESTARTBLOCK
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
(paren
id|BMAPI_DIRECT
op_or
id|BMAPI_MMAP
)paren
)paren
(brace
id|error
op_assign
id|XFS_IOMAP_WRITE_DIRECT
c_func
(paren
id|mp
comma
id|io
comma
id|offset
comma
id|count
comma
id|flags
comma
op_amp
id|imap
comma
op_amp
id|nimaps
comma
id|nimaps
)paren
suffix:semicolon
)brace
r_else
(brace
id|error
op_assign
id|XFS_IOMAP_WRITE_DELAY
c_func
(paren
id|mp
comma
id|io
comma
id|offset
comma
id|count
comma
id|flags
comma
op_amp
id|imap
comma
op_amp
id|nimaps
)paren
suffix:semicolon
)brace
id|iomap_flags
op_assign
id|IOMAP_NEW
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BMAPI_ALLOCATE
suffix:colon
multiline_comment|/* If we found an extent, return it */
id|XFS_IUNLOCK
c_func
(paren
id|mp
comma
id|io
comma
id|lockmode
)paren
suffix:semicolon
id|lockmode
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nimaps
op_logical_and
op_logical_neg
id|ISNULLSTARTBLOCK
c_func
(paren
id|imap.br_startblock
)paren
)paren
r_break
suffix:semicolon
id|error
op_assign
id|XFS_IOMAP_WRITE_ALLOCATE
c_func
(paren
id|mp
comma
id|io
comma
op_amp
id|imap
comma
op_amp
id|nimaps
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BMAPI_UNWRITTEN
suffix:colon
id|lockmode
op_assign
l_int|0
suffix:semicolon
id|error
op_assign
id|XFS_IOMAP_WRITE_UNWRITTEN
c_func
(paren
id|mp
comma
id|io
comma
id|offset
comma
id|count
)paren
suffix:semicolon
id|nimaps
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nimaps
)paren
(brace
op_star
id|niomaps
op_assign
id|xfs_imap_to_bmap
c_func
(paren
id|io
comma
id|offset
comma
op_amp
id|imap
comma
id|iomapp
comma
id|nimaps
comma
op_star
id|niomaps
comma
id|iomap_flags
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|niomaps
)paren
(brace
op_star
id|niomaps
op_assign
l_int|0
suffix:semicolon
)brace
id|out
suffix:colon
r_if
c_cond
(paren
id|lockmode
)paren
id|XFS_IUNLOCK
c_func
(paren
id|mp
comma
id|io
comma
id|lockmode
)paren
suffix:semicolon
r_return
id|XFS_ERROR
c_func
(paren
id|error
)paren
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|xfs_flush_space
id|xfs_flush_space
c_func
(paren
id|xfs_inode_t
op_star
id|ip
comma
r_int
op_star
id|fsynced
comma
r_int
op_star
id|ioflags
)paren
(brace
r_switch
c_cond
(paren
op_star
id|fsynced
)paren
(brace
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
id|ip-&gt;i_delayed_blks
)paren
(brace
id|xfs_iunlock
c_func
(paren
id|ip
comma
id|XFS_ILOCK_EXCL
)paren
suffix:semicolon
id|xfs_flush_inode
c_func
(paren
id|ip
)paren
suffix:semicolon
id|xfs_ilock
c_func
(paren
id|ip
comma
id|XFS_ILOCK_EXCL
)paren
suffix:semicolon
op_star
id|fsynced
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
op_star
id|ioflags
op_or_assign
id|BMAPI_SYNC
suffix:semicolon
op_star
id|fsynced
op_assign
l_int|2
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_case
l_int|1
suffix:colon
op_star
id|fsynced
op_assign
l_int|2
suffix:semicolon
op_star
id|ioflags
op_or_assign
id|BMAPI_SYNC
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
l_int|2
suffix:colon
id|xfs_iunlock
c_func
(paren
id|ip
comma
id|XFS_ILOCK_EXCL
)paren
suffix:semicolon
id|xfs_flush_device
c_func
(paren
id|ip
)paren
suffix:semicolon
id|xfs_ilock
c_func
(paren
id|ip
comma
id|XFS_ILOCK_EXCL
)paren
suffix:semicolon
op_star
id|fsynced
op_assign
l_int|3
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_int
DECL|function|xfs_iomap_write_direct
id|xfs_iomap_write_direct
c_func
(paren
id|xfs_inode_t
op_star
id|ip
comma
id|loff_t
id|offset
comma
r_int
id|count
comma
r_int
id|flags
comma
id|xfs_bmbt_irec_t
op_star
id|ret_imap
comma
r_int
op_star
id|nmaps
comma
r_int
id|found
)paren
(brace
id|xfs_mount_t
op_star
id|mp
op_assign
id|ip-&gt;i_mount
suffix:semicolon
id|xfs_iocore_t
op_star
id|io
op_assign
op_amp
id|ip-&gt;i_iocore
suffix:semicolon
id|xfs_fileoff_t
id|offset_fsb
suffix:semicolon
id|xfs_fileoff_t
id|last_fsb
suffix:semicolon
id|xfs_filblks_t
id|count_fsb
suffix:semicolon
id|xfs_fsize_t
id|isize
suffix:semicolon
id|xfs_fsblock_t
id|firstfsb
suffix:semicolon
r_int
id|nimaps
comma
id|maps
suffix:semicolon
r_int
id|error
suffix:semicolon
r_int
id|bmapi_flag
suffix:semicolon
r_int
id|rt
suffix:semicolon
id|xfs_trans_t
op_star
id|tp
suffix:semicolon
id|xfs_bmbt_irec_t
id|imap
(braket
id|XFS_WRITE_IMAPS
)braket
comma
op_star
id|imapp
suffix:semicolon
id|xfs_bmap_free_t
id|free_list
suffix:semicolon
r_int
id|aeof
suffix:semicolon
id|xfs_filblks_t
id|datablocks
suffix:semicolon
r_int
id|committed
suffix:semicolon
r_int
id|numrtextents
suffix:semicolon
id|uint
id|resblks
suffix:semicolon
multiline_comment|/*&n;&t; * Make sure that the dquots are there. This doesn&squot;t hold&n;&t; * the ilock across a disk read.&n;&t; */
id|error
op_assign
id|XFS_QM_DQATTACH
c_func
(paren
id|ip-&gt;i_mount
comma
id|ip
comma
id|XFS_QMOPT_ILOCKED
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|XFS_ERROR
c_func
(paren
id|error
)paren
suffix:semicolon
id|maps
op_assign
id|min
c_func
(paren
id|XFS_WRITE_IMAPS
comma
op_star
id|nmaps
)paren
suffix:semicolon
id|nimaps
op_assign
id|maps
suffix:semicolon
id|isize
op_assign
id|ip-&gt;i_d.di_size
suffix:semicolon
id|aeof
op_assign
(paren
id|offset
op_plus
id|count
)paren
OG
id|isize
suffix:semicolon
r_if
c_cond
(paren
id|io-&gt;io_new_size
OG
id|isize
)paren
id|isize
op_assign
id|io-&gt;io_new_size
suffix:semicolon
id|offset_fsb
op_assign
id|XFS_B_TO_FSBT
c_func
(paren
id|mp
comma
id|offset
)paren
suffix:semicolon
id|last_fsb
op_assign
id|XFS_B_TO_FSB
c_func
(paren
id|mp
comma
(paren
(paren
id|xfs_ufsize_t
)paren
(paren
id|offset
op_plus
id|count
)paren
)paren
)paren
suffix:semicolon
id|count_fsb
op_assign
id|last_fsb
op_minus
id|offset_fsb
suffix:semicolon
r_if
c_cond
(paren
id|found
op_logical_and
(paren
id|ret_imap-&gt;br_startblock
op_eq
id|HOLESTARTBLOCK
)paren
)paren
(brace
id|xfs_fileoff_t
id|map_last_fsb
suffix:semicolon
id|map_last_fsb
op_assign
id|ret_imap-&gt;br_blockcount
op_plus
id|ret_imap-&gt;br_startoff
suffix:semicolon
r_if
c_cond
(paren
id|map_last_fsb
OL
id|last_fsb
)paren
(brace
id|last_fsb
op_assign
id|map_last_fsb
suffix:semicolon
id|count_fsb
op_assign
id|last_fsb
op_minus
id|offset_fsb
suffix:semicolon
)brace
id|ASSERT
c_func
(paren
id|count_fsb
OG
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * determine if reserving space on&n;&t; * the data or realtime partition.&n;&t; */
r_if
c_cond
(paren
(paren
id|rt
op_assign
id|XFS_IS_REALTIME_INODE
c_func
(paren
id|ip
)paren
)paren
)paren
(brace
r_int
id|sbrtextsize
comma
id|iprtextsize
suffix:semicolon
id|sbrtextsize
op_assign
id|mp-&gt;m_sb.sb_rextsize
suffix:semicolon
id|iprtextsize
op_assign
id|ip-&gt;i_d.di_extsize
ques
c_cond
id|ip-&gt;i_d.di_extsize
suffix:colon
id|sbrtextsize
suffix:semicolon
id|numrtextents
op_assign
(paren
id|count_fsb
op_plus
id|iprtextsize
op_minus
l_int|1
)paren
suffix:semicolon
id|do_div
c_func
(paren
id|numrtextents
comma
id|sbrtextsize
)paren
suffix:semicolon
id|datablocks
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|datablocks
op_assign
id|count_fsb
suffix:semicolon
id|numrtextents
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * allocate and setup the transaction&n;&t; */
id|xfs_iunlock
c_func
(paren
id|ip
comma
id|XFS_ILOCK_EXCL
)paren
suffix:semicolon
id|tp
op_assign
id|xfs_trans_alloc
c_func
(paren
id|mp
comma
id|XFS_TRANS_DIOSTRAT
)paren
suffix:semicolon
id|resblks
op_assign
id|XFS_DIOSTRAT_SPACE_RES
c_func
(paren
id|mp
comma
id|datablocks
)paren
suffix:semicolon
id|error
op_assign
id|xfs_trans_reserve
c_func
(paren
id|tp
comma
id|resblks
comma
id|XFS_WRITE_LOG_RES
c_func
(paren
id|mp
)paren
comma
id|numrtextents
comma
id|XFS_TRANS_PERM_LOG_RES
comma
id|XFS_WRITE_LOG_COUNT
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * check for running out of space&n;&t; */
r_if
c_cond
(paren
id|error
)paren
multiline_comment|/*&n;&t;&t; * Free the transaction structure.&n;&t;&t; */
id|xfs_trans_cancel
c_func
(paren
id|tp
comma
l_int|0
)paren
suffix:semicolon
id|xfs_ilock
c_func
(paren
id|ip
comma
id|XFS_ILOCK_EXCL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|error_out
suffix:semicolon
multiline_comment|/* Don&squot;t return in above if .. trans ..,&n;&t;&t;&t;&t;&t;need lock to return */
r_if
c_cond
(paren
id|XFS_TRANS_RESERVE_BLKQUOTA
c_func
(paren
id|mp
comma
id|tp
comma
id|ip
comma
id|resblks
)paren
)paren
(brace
id|error
op_assign
(paren
id|EDQUOT
)paren
suffix:semicolon
r_goto
id|error1
suffix:semicolon
)brace
id|nimaps
op_assign
l_int|1
suffix:semicolon
id|bmapi_flag
op_assign
id|XFS_BMAPI_WRITE
suffix:semicolon
id|xfs_trans_ijoin
c_func
(paren
id|tp
comma
id|ip
comma
id|XFS_ILOCK_EXCL
)paren
suffix:semicolon
id|xfs_trans_ihold
c_func
(paren
id|tp
comma
id|ip
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|BMAPI_MMAP
)paren
op_logical_and
(paren
id|offset
OL
id|ip-&gt;i_d.di_size
op_logical_or
id|rt
)paren
)paren
id|bmapi_flag
op_or_assign
id|XFS_BMAPI_PREALLOC
suffix:semicolon
multiline_comment|/*&n;&t; * issue the bmapi() call to allocate the blocks&n;&t; */
id|XFS_BMAP_INIT
c_func
(paren
op_amp
id|free_list
comma
op_amp
id|firstfsb
)paren
suffix:semicolon
id|imapp
op_assign
op_amp
id|imap
(braket
l_int|0
)braket
suffix:semicolon
id|error
op_assign
id|xfs_bmapi
c_func
(paren
id|tp
comma
id|ip
comma
id|offset_fsb
comma
id|count_fsb
comma
id|bmapi_flag
comma
op_amp
id|firstfsb
comma
l_int|0
comma
id|imapp
comma
op_amp
id|nimaps
comma
op_amp
id|free_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
r_goto
id|error0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * complete the transaction&n;&t; */
id|error
op_assign
id|xfs_bmap_finish
c_func
(paren
op_amp
id|tp
comma
op_amp
id|free_list
comma
id|firstfsb
comma
op_amp
id|committed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
r_goto
id|error0
suffix:semicolon
)brace
id|error
op_assign
id|xfs_trans_commit
c_func
(paren
id|tp
comma
id|XFS_TRANS_RELEASE_LOG_RES
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
r_goto
id|error_out
suffix:semicolon
)brace
multiline_comment|/* copy any maps to caller&squot;s array and return any error. */
r_if
c_cond
(paren
id|nimaps
op_eq
l_int|0
)paren
(brace
id|error
op_assign
(paren
id|ENOSPC
)paren
suffix:semicolon
r_goto
id|error_out
suffix:semicolon
)brace
op_star
id|ret_imap
op_assign
id|imap
(braket
l_int|0
)braket
suffix:semicolon
op_star
id|nmaps
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|error0
suffix:colon
multiline_comment|/* Cancel bmap, unlock inode, and cancel trans */
id|xfs_bmap_cancel
c_func
(paren
op_amp
id|free_list
)paren
suffix:semicolon
id|error1
suffix:colon
multiline_comment|/* Just cancel transaction */
id|xfs_trans_cancel
c_func
(paren
id|tp
comma
id|XFS_TRANS_RELEASE_LOG_RES
op_or
id|XFS_TRANS_ABORT
)paren
suffix:semicolon
op_star
id|nmaps
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* nothing set-up here */
id|error_out
suffix:colon
r_return
id|XFS_ERROR
c_func
(paren
id|error
)paren
suffix:semicolon
)brace
r_int
DECL|function|xfs_iomap_write_delay
id|xfs_iomap_write_delay
c_func
(paren
id|xfs_inode_t
op_star
id|ip
comma
id|loff_t
id|offset
comma
r_int
id|count
comma
r_int
id|ioflag
comma
id|xfs_bmbt_irec_t
op_star
id|ret_imap
comma
r_int
op_star
id|nmaps
)paren
(brace
id|xfs_mount_t
op_star
id|mp
op_assign
id|ip-&gt;i_mount
suffix:semicolon
id|xfs_iocore_t
op_star
id|io
op_assign
op_amp
id|ip-&gt;i_iocore
suffix:semicolon
id|xfs_fileoff_t
id|offset_fsb
suffix:semicolon
id|xfs_fileoff_t
id|last_fsb
suffix:semicolon
id|xfs_fsize_t
id|isize
suffix:semicolon
id|xfs_fsblock_t
id|firstblock
suffix:semicolon
r_int
id|nimaps
suffix:semicolon
r_int
id|error
suffix:semicolon
id|xfs_bmbt_irec_t
id|imap
(braket
id|XFS_WRITE_IMAPS
)braket
suffix:semicolon
r_int
id|aeof
suffix:semicolon
r_int
id|fsynced
op_assign
l_int|0
suffix:semicolon
id|ASSERT
c_func
(paren
id|ismrlocked
c_func
(paren
op_amp
id|ip-&gt;i_lock
comma
id|MR_UPDATE
)paren
op_ne
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Make sure that the dquots are there. This doesn&squot;t hold&n;&t; * the ilock across a disk read.&n;&t; */
id|error
op_assign
id|XFS_QM_DQATTACH
c_func
(paren
id|mp
comma
id|ip
comma
id|XFS_QMOPT_ILOCKED
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|XFS_ERROR
c_func
(paren
id|error
)paren
suffix:semicolon
id|retry
suffix:colon
id|isize
op_assign
id|ip-&gt;i_d.di_size
suffix:semicolon
r_if
c_cond
(paren
id|io-&gt;io_new_size
OG
id|isize
)paren
(brace
id|isize
op_assign
id|io-&gt;io_new_size
suffix:semicolon
)brace
id|aeof
op_assign
l_int|0
suffix:semicolon
id|offset_fsb
op_assign
id|XFS_B_TO_FSBT
c_func
(paren
id|mp
comma
id|offset
)paren
suffix:semicolon
id|last_fsb
op_assign
id|XFS_B_TO_FSB
c_func
(paren
id|mp
comma
(paren
(paren
id|xfs_ufsize_t
)paren
(paren
id|offset
op_plus
id|count
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If the caller is doing a write at the end of the file,&n;&t; * then extend the allocation (and the buffer used for the write)&n;&t; * out to the file system&squot;s write iosize.  We clean up any extra&n;&t; * space left over when the file is closed in xfs_inactive().&n;&t; *&n;&t; * We don&squot;t bother with this for sync writes, because we need&n;&t; * to minimize the amount we write for good performance.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|ioflag
op_amp
id|BMAPI_SYNC
)paren
op_logical_and
(paren
(paren
id|offset
op_plus
id|count
)paren
OG
id|ip-&gt;i_d.di_size
)paren
)paren
(brace
id|xfs_off_t
id|aligned_offset
suffix:semicolon
r_int
r_int
id|iosize
suffix:semicolon
id|xfs_fileoff_t
id|ioalign
suffix:semicolon
id|iosize
op_assign
id|mp-&gt;m_writeio_blocks
suffix:semicolon
id|aligned_offset
op_assign
id|XFS_WRITEIO_ALIGN
c_func
(paren
id|mp
comma
(paren
id|offset
op_plus
id|count
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|ioalign
op_assign
id|XFS_B_TO_FSBT
c_func
(paren
id|mp
comma
id|aligned_offset
)paren
suffix:semicolon
id|last_fsb
op_assign
id|ioalign
op_plus
id|iosize
suffix:semicolon
id|aeof
op_assign
l_int|1
suffix:semicolon
)brace
id|nimaps
op_assign
id|XFS_WRITE_IMAPS
suffix:semicolon
id|firstblock
op_assign
id|NULLFSBLOCK
suffix:semicolon
multiline_comment|/*&n;&t; * roundup the allocation request to m_dalign boundary if file size&n;&t; * is greater that 512K and we are allocating past the allocation eof&n;&t; */
r_if
c_cond
(paren
id|mp-&gt;m_dalign
op_logical_and
(paren
id|isize
op_ge
id|mp-&gt;m_dalign
)paren
op_logical_and
id|aeof
)paren
(brace
r_int
id|eof
suffix:semicolon
id|xfs_fileoff_t
id|new_last_fsb
suffix:semicolon
id|new_last_fsb
op_assign
id|roundup_64
c_func
(paren
id|last_fsb
comma
id|mp-&gt;m_dalign
)paren
suffix:semicolon
id|error
op_assign
id|xfs_bmap_eof
c_func
(paren
id|ip
comma
id|new_last_fsb
comma
id|XFS_DATA_FORK
comma
op_amp
id|eof
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
r_return
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|eof
)paren
(brace
id|last_fsb
op_assign
id|new_last_fsb
suffix:semicolon
)brace
)brace
id|error
op_assign
id|xfs_bmapi
c_func
(paren
l_int|NULL
comma
id|ip
comma
id|offset_fsb
comma
(paren
id|xfs_filblks_t
)paren
(paren
id|last_fsb
op_minus
id|offset_fsb
)paren
comma
id|XFS_BMAPI_DELAY
op_or
id|XFS_BMAPI_WRITE
op_or
id|XFS_BMAPI_ENTIRE
comma
op_amp
id|firstblock
comma
l_int|1
comma
id|imap
comma
op_amp
id|nimaps
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This can be EDQUOT, if nimaps == 0&n;&t; */
r_if
c_cond
(paren
id|error
op_logical_and
(paren
id|error
op_ne
id|ENOSPC
)paren
)paren
(brace
r_return
id|XFS_ERROR
c_func
(paren
id|error
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If bmapi returned us nothing, and if we didn&squot;t get back EDQUOT,&n;&t; * then we must have run out of space.&n;&t; */
r_if
c_cond
(paren
id|nimaps
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|xfs_flush_space
c_func
(paren
id|ip
comma
op_amp
id|fsynced
comma
op_amp
id|ioflag
)paren
)paren
r_return
id|XFS_ERROR
c_func
(paren
id|ENOSPC
)paren
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
r_goto
id|retry
suffix:semicolon
)brace
op_star
id|ret_imap
op_assign
id|imap
(braket
l_int|0
)braket
suffix:semicolon
op_star
id|nmaps
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Pass in a delayed allocate extent, convert it to real extents;&n; * return to the caller the extent we create which maps on top of&n; * the originating callers request.&n; *&n; * Called without a lock on the inode.&n; */
r_int
DECL|function|xfs_iomap_write_allocate
id|xfs_iomap_write_allocate
c_func
(paren
id|xfs_inode_t
op_star
id|ip
comma
id|xfs_bmbt_irec_t
op_star
id|map
comma
r_int
op_star
id|retmap
)paren
(brace
id|xfs_mount_t
op_star
id|mp
op_assign
id|ip-&gt;i_mount
suffix:semicolon
id|xfs_fileoff_t
id|offset_fsb
comma
id|last_block
suffix:semicolon
id|xfs_fileoff_t
id|end_fsb
comma
id|map_start_fsb
suffix:semicolon
id|xfs_fsblock_t
id|first_block
suffix:semicolon
id|xfs_bmap_free_t
id|free_list
suffix:semicolon
id|xfs_filblks_t
id|count_fsb
suffix:semicolon
id|xfs_bmbt_irec_t
id|imap
(braket
id|XFS_STRAT_WRITE_IMAPS
)braket
suffix:semicolon
id|xfs_trans_t
op_star
id|tp
suffix:semicolon
r_int
id|i
comma
id|nimaps
comma
id|committed
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_int
id|nres
suffix:semicolon
op_star
id|retmap
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Make sure that the dquots are there.&n;&t; */
r_if
c_cond
(paren
(paren
id|error
op_assign
id|XFS_QM_DQATTACH
c_func
(paren
id|mp
comma
id|ip
comma
l_int|0
)paren
)paren
)paren
r_return
id|XFS_ERROR
c_func
(paren
id|error
)paren
suffix:semicolon
id|offset_fsb
op_assign
id|map-&gt;br_startoff
suffix:semicolon
id|count_fsb
op_assign
id|map-&gt;br_blockcount
suffix:semicolon
id|map_start_fsb
op_assign
id|offset_fsb
suffix:semicolon
id|XFS_STATS_ADD
c_func
(paren
id|xs_xstrat_bytes
comma
id|XFS_FSB_TO_B
c_func
(paren
id|mp
comma
id|count_fsb
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count_fsb
op_ne
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * Set up a transaction with which to allocate the&n;&t;&t; * backing store for the file.  Do allocations in a&n;&t;&t; * loop until we get some space in the range we are&n;&t;&t; * interested in.  The other space that might be allocated&n;&t;&t; * is in the delayed allocation extent on which we sit&n;&t;&t; * but before our buffer starts.&n;&t;&t; */
id|nimaps
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|nimaps
op_eq
l_int|0
)paren
(brace
id|tp
op_assign
id|xfs_trans_alloc
c_func
(paren
id|mp
comma
id|XFS_TRANS_STRAT_WRITE
)paren
suffix:semicolon
id|nres
op_assign
id|XFS_EXTENTADD_SPACE_RES
c_func
(paren
id|mp
comma
id|XFS_DATA_FORK
)paren
suffix:semicolon
id|error
op_assign
id|xfs_trans_reserve
c_func
(paren
id|tp
comma
id|nres
comma
id|XFS_WRITE_LOG_RES
c_func
(paren
id|mp
)paren
comma
l_int|0
comma
id|XFS_TRANS_PERM_LOG_RES
comma
id|XFS_WRITE_LOG_COUNT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
id|ENOSPC
)paren
(brace
id|error
op_assign
id|xfs_trans_reserve
c_func
(paren
id|tp
comma
l_int|0
comma
id|XFS_WRITE_LOG_RES
c_func
(paren
id|mp
)paren
comma
l_int|0
comma
id|XFS_TRANS_PERM_LOG_RES
comma
id|XFS_WRITE_LOG_COUNT
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|error
)paren
(brace
id|xfs_trans_cancel
c_func
(paren
id|tp
comma
l_int|0
)paren
suffix:semicolon
r_return
id|XFS_ERROR
c_func
(paren
id|error
)paren
suffix:semicolon
)brace
id|xfs_ilock
c_func
(paren
id|ip
comma
id|XFS_ILOCK_EXCL
)paren
suffix:semicolon
id|xfs_trans_ijoin
c_func
(paren
id|tp
comma
id|ip
comma
id|XFS_ILOCK_EXCL
)paren
suffix:semicolon
id|xfs_trans_ihold
c_func
(paren
id|tp
comma
id|ip
)paren
suffix:semicolon
id|XFS_BMAP_INIT
c_func
(paren
op_amp
id|free_list
comma
op_amp
id|first_block
)paren
suffix:semicolon
id|nimaps
op_assign
id|XFS_STRAT_WRITE_IMAPS
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Ensure we don&squot;t go beyond eof - it is possible&n;&t;&t;&t; * the extents changed since we did the read call,&n;&t;&t;&t; * we dropped the ilock in the interim.&n;&t;&t;&t; */
id|end_fsb
op_assign
id|XFS_B_TO_FSB
c_func
(paren
id|mp
comma
id|ip-&gt;i_d.di_size
)paren
suffix:semicolon
id|xfs_bmap_last_offset
c_func
(paren
l_int|NULL
comma
id|ip
comma
op_amp
id|last_block
comma
id|XFS_DATA_FORK
)paren
suffix:semicolon
id|last_block
op_assign
id|XFS_FILEOFF_MAX
c_func
(paren
id|last_block
comma
id|end_fsb
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|map_start_fsb
op_plus
id|count_fsb
)paren
OG
id|last_block
)paren
(brace
id|count_fsb
op_assign
id|last_block
op_minus
id|map_start_fsb
suffix:semicolon
r_if
c_cond
(paren
id|count_fsb
op_eq
l_int|0
)paren
(brace
id|error
op_assign
id|EAGAIN
suffix:semicolon
r_goto
id|trans_cancel
suffix:semicolon
)brace
)brace
multiline_comment|/* Go get the actual blocks */
id|error
op_assign
id|xfs_bmapi
c_func
(paren
id|tp
comma
id|ip
comma
id|map_start_fsb
comma
id|count_fsb
comma
id|XFS_BMAPI_WRITE
comma
op_amp
id|first_block
comma
l_int|1
comma
id|imap
comma
op_amp
id|nimaps
comma
op_amp
id|free_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|trans_cancel
suffix:semicolon
id|error
op_assign
id|xfs_bmap_finish
c_func
(paren
op_amp
id|tp
comma
op_amp
id|free_list
comma
id|first_block
comma
op_amp
id|committed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|trans_cancel
suffix:semicolon
id|error
op_assign
id|xfs_trans_commit
c_func
(paren
id|tp
comma
id|XFS_TRANS_RELEASE_LOG_RES
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|error0
suffix:semicolon
id|xfs_iunlock
c_func
(paren
id|ip
comma
id|XFS_ILOCK_EXCL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * See if we were able to allocate an extent that&n;&t;&t; * covers at least part of the callers request&n;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nimaps
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|map-&gt;br_startoff
op_ge
id|imap
(braket
id|i
)braket
dot
id|br_startoff
)paren
op_logical_and
(paren
id|map-&gt;br_startoff
OL
(paren
id|imap
(braket
id|i
)braket
dot
id|br_startoff
op_plus
id|imap
(braket
id|i
)braket
dot
id|br_blockcount
)paren
)paren
)paren
(brace
op_star
id|map
op_assign
id|imap
(braket
id|i
)braket
suffix:semicolon
op_star
id|retmap
op_assign
l_int|1
suffix:semicolon
id|XFS_STATS_INC
c_func
(paren
id|xs_xstrat_quick
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|count_fsb
op_sub_assign
id|imap
(braket
id|i
)braket
dot
id|br_blockcount
suffix:semicolon
)brace
multiline_comment|/* So far we have not mapped the requested part of the&n;&t;&t; * file, just surrounding data, try again.&n;&t;&t; */
id|nimaps
op_decrement
suffix:semicolon
id|offset_fsb
op_assign
id|imap
(braket
id|nimaps
)braket
dot
id|br_startoff
op_plus
id|imap
(braket
id|nimaps
)braket
dot
id|br_blockcount
suffix:semicolon
id|map_start_fsb
op_assign
id|offset_fsb
suffix:semicolon
)brace
id|trans_cancel
suffix:colon
id|xfs_bmap_cancel
c_func
(paren
op_amp
id|free_list
)paren
suffix:semicolon
id|xfs_trans_cancel
c_func
(paren
id|tp
comma
id|XFS_TRANS_RELEASE_LOG_RES
op_or
id|XFS_TRANS_ABORT
)paren
suffix:semicolon
id|error0
suffix:colon
id|xfs_iunlock
c_func
(paren
id|ip
comma
id|XFS_ILOCK_EXCL
)paren
suffix:semicolon
r_return
id|XFS_ERROR
c_func
(paren
id|error
)paren
suffix:semicolon
)brace
r_int
DECL|function|xfs_iomap_write_unwritten
id|xfs_iomap_write_unwritten
c_func
(paren
id|xfs_inode_t
op_star
id|ip
comma
id|loff_t
id|offset
comma
r_int
id|count
)paren
(brace
id|xfs_mount_t
op_star
id|mp
op_assign
id|ip-&gt;i_mount
suffix:semicolon
id|xfs_trans_t
op_star
id|tp
suffix:semicolon
id|xfs_fileoff_t
id|offset_fsb
suffix:semicolon
id|xfs_filblks_t
id|count_fsb
suffix:semicolon
id|xfs_filblks_t
id|numblks_fsb
suffix:semicolon
id|xfs_bmbt_irec_t
id|imap
suffix:semicolon
r_int
id|committed
suffix:semicolon
r_int
id|error
suffix:semicolon
r_int
id|nres
suffix:semicolon
r_int
id|nimaps
suffix:semicolon
id|xfs_fsblock_t
id|firstfsb
suffix:semicolon
id|xfs_bmap_free_t
id|free_list
suffix:semicolon
id|offset_fsb
op_assign
id|XFS_B_TO_FSBT
c_func
(paren
id|mp
comma
id|offset
)paren
suffix:semicolon
id|count_fsb
op_assign
id|XFS_B_TO_FSB
c_func
(paren
id|mp
comma
id|count
)paren
suffix:semicolon
r_do
(brace
id|nres
op_assign
id|XFS_DIOSTRAT_SPACE_RES
c_func
(paren
id|mp
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * set up a transaction to convert the range of extents&n;&t;&t; * from unwritten to real. Do allocations in a loop until&n;&t;&t; * we have covered the range passed in.&n;&t;&t; */
id|tp
op_assign
id|xfs_trans_alloc
c_func
(paren
id|mp
comma
id|XFS_TRANS_STRAT_WRITE
)paren
suffix:semicolon
id|error
op_assign
id|xfs_trans_reserve
c_func
(paren
id|tp
comma
id|nres
comma
id|XFS_WRITE_LOG_RES
c_func
(paren
id|mp
)paren
comma
l_int|0
comma
id|XFS_TRANS_PERM_LOG_RES
comma
id|XFS_WRITE_LOG_COUNT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|xfs_trans_cancel
c_func
(paren
id|tp
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|error0
suffix:semicolon
)brace
id|xfs_ilock
c_func
(paren
id|ip
comma
id|XFS_ILOCK_EXCL
)paren
suffix:semicolon
id|xfs_trans_ijoin
c_func
(paren
id|tp
comma
id|ip
comma
id|XFS_ILOCK_EXCL
)paren
suffix:semicolon
id|xfs_trans_ihold
c_func
(paren
id|tp
comma
id|ip
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Modify the unwritten extent state of the buffer.&n;&t;&t; */
id|XFS_BMAP_INIT
c_func
(paren
op_amp
id|free_list
comma
op_amp
id|firstfsb
)paren
suffix:semicolon
id|nimaps
op_assign
l_int|1
suffix:semicolon
id|error
op_assign
id|xfs_bmapi
c_func
(paren
id|tp
comma
id|ip
comma
id|offset_fsb
comma
id|count_fsb
comma
id|XFS_BMAPI_WRITE
comma
op_amp
id|firstfsb
comma
l_int|1
comma
op_amp
id|imap
comma
op_amp
id|nimaps
comma
op_amp
id|free_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|error_on_bmapi_transaction
suffix:semicolon
id|error
op_assign
id|xfs_bmap_finish
c_func
(paren
op_amp
(paren
id|tp
)paren
comma
op_amp
(paren
id|free_list
)paren
comma
id|firstfsb
comma
op_amp
id|committed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|error_on_bmapi_transaction
suffix:semicolon
id|error
op_assign
id|xfs_trans_commit
c_func
(paren
id|tp
comma
id|XFS_TRANS_RELEASE_LOG_RES
comma
l_int|NULL
)paren
suffix:semicolon
id|xfs_iunlock
c_func
(paren
id|ip
comma
id|XFS_ILOCK_EXCL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|error0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|numblks_fsb
op_assign
id|imap.br_blockcount
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * The numblks_fsb value should always get&n;&t;&t;&t; * smaller, otherwise the loop is stuck.&n;&t;&t;&t; */
id|ASSERT
c_func
(paren
id|imap.br_blockcount
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|offset_fsb
op_add_assign
id|numblks_fsb
suffix:semicolon
id|count_fsb
op_sub_assign
id|numblks_fsb
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count_fsb
OG
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|error_on_bmapi_transaction
suffix:colon
id|xfs_bmap_cancel
c_func
(paren
op_amp
id|free_list
)paren
suffix:semicolon
id|xfs_trans_cancel
c_func
(paren
id|tp
comma
(paren
id|XFS_TRANS_RELEASE_LOG_RES
op_or
id|XFS_TRANS_ABORT
)paren
)paren
suffix:semicolon
id|xfs_iunlock
c_func
(paren
id|ip
comma
id|XFS_ILOCK_EXCL
)paren
suffix:semicolon
id|error0
suffix:colon
r_return
id|XFS_ERROR
c_func
(paren
id|error
)paren
suffix:semicolon
)brace
eof
