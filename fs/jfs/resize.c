multiline_comment|/*&n; *   Copyright (C) International Business Machines  Corp., 2000-2003&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n;*/
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &quot;jfs_incore.h&quot;
macro_line|#include &quot;jfs_filsys.h&quot;
macro_line|#include &quot;jfs_metapage.h&quot;
macro_line|#include &quot;jfs_dinode.h&quot;
macro_line|#include &quot;jfs_imap.h&quot;
macro_line|#include &quot;jfs_dmap.h&quot;
macro_line|#include &quot;jfs_superblock.h&quot;
macro_line|#include &quot;jfs_txnmgr.h&quot;
macro_line|#include &quot;jfs_debug.h&quot;
DECL|macro|BITSPERPAGE
mdefine_line|#define BITSPERPAGE     (PSIZE &lt;&lt; 3)
DECL|macro|L2MEGABYTE
mdefine_line|#define L2MEGABYTE      20
DECL|macro|MEGABYTE
mdefine_line|#define MEGABYTE        (1 &lt;&lt; L2MEGABYTE)
DECL|macro|MEGABYTE32
mdefine_line|#define MEGABYTE32     (MEGABYTE &lt;&lt; 5)
multiline_comment|/* convert block number to bmap file page number */
DECL|macro|BLKTODMAPN
mdefine_line|#define BLKTODMAPN(b)&bslash;&n;        (((b) &gt;&gt; 13) + ((b) &gt;&gt; 23) + ((b) &gt;&gt; 33) + 3 + 1)
multiline_comment|/*&n; *      jfs_extendfs()&n; *&n; * function: extend file system;&n; *&n; *   |-------------------------------|----------|----------|&n; *   file system space               fsck       inline log&n; *                                   workspace  space&n; *&n; * input:&n; *      new LVSize: in LV blocks (required)&n; *      new LogSize: in LV blocks (optional)&n; *      new FSSize: in LV blocks (optional)&n; *&n; * new configuration:&n; * 1. set new LogSize as specified or default from new LVSize;&n; * 2. compute new FSCKSize from new LVSize;&n; * 3. set new FSSize as MIN(FSSize, LVSize-(LogSize+FSCKSize)) where&n; *    assert(new FSSize &gt;= old FSSize),&n; *    i.e., file system must not be shrinked;&n; */
DECL|function|jfs_extendfs
r_int
id|jfs_extendfs
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|s64
id|newLVSize
comma
r_int
id|newLogSize
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_struct
id|jfs_sb_info
op_star
id|sbi
op_assign
id|JFS_SBI
c_func
(paren
id|sb
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|ipbmap
op_assign
id|sbi-&gt;ipbmap
suffix:semicolon
r_struct
id|inode
op_star
id|ipbmap2
suffix:semicolon
r_struct
id|inode
op_star
id|ipimap
op_assign
id|sbi-&gt;ipimap
suffix:semicolon
r_struct
id|jfs_log
op_star
id|log
op_assign
id|sbi-&gt;log
suffix:semicolon
r_struct
id|bmap
op_star
id|bmp
op_assign
id|sbi-&gt;bmap
suffix:semicolon
id|s64
id|newLogAddress
comma
id|newFSCKAddress
suffix:semicolon
r_int
id|newFSCKSize
suffix:semicolon
id|s64
id|newMapSize
op_assign
l_int|0
comma
id|mapSize
suffix:semicolon
id|s64
id|XAddress
comma
id|XSize
comma
id|nblocks
comma
id|xoff
comma
id|xaddr
comma
id|t64
suffix:semicolon
id|s64
id|oldLVSize
suffix:semicolon
id|s64
id|newFSSize
suffix:semicolon
id|s64
id|VolumeSize
suffix:semicolon
r_int
id|newNpages
op_assign
l_int|0
comma
id|nPages
comma
id|newPage
comma
id|xlen
comma
id|t32
suffix:semicolon
r_int
id|tid
suffix:semicolon
r_int
id|log_formatted
op_assign
l_int|0
suffix:semicolon
r_struct
id|inode
op_star
id|iplist
(braket
l_int|1
)braket
suffix:semicolon
r_struct
id|jfs_superblock
op_star
id|j_sb
comma
op_star
id|j_sb2
suffix:semicolon
id|uint
id|old_agsize
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
comma
op_star
id|bh2
suffix:semicolon
multiline_comment|/* If the volume hasn&squot;t grown, get out now */
r_if
c_cond
(paren
id|sbi-&gt;mntflag
op_amp
id|JFS_INLINELOG
)paren
id|oldLVSize
op_assign
id|addressPXD
c_func
(paren
op_amp
id|sbi-&gt;logpxd
)paren
op_plus
id|lengthPXD
c_func
(paren
op_amp
id|sbi-&gt;logpxd
)paren
suffix:semicolon
r_else
id|oldLVSize
op_assign
id|addressPXD
c_func
(paren
op_amp
id|sbi-&gt;fsckpxd
)paren
op_plus
id|lengthPXD
c_func
(paren
op_amp
id|sbi-&gt;fsckpxd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|oldLVSize
op_ge
id|newLVSize
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;jfs_extendfs: volume hasn&squot;t grown, returning&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|VolumeSize
op_assign
id|sb-&gt;s_bdev-&gt;bd_inode-&gt;i_size
op_rshift
id|sb-&gt;s_blocksize_bits
suffix:semicolon
r_if
c_cond
(paren
id|VolumeSize
)paren
(brace
r_if
c_cond
(paren
id|newLVSize
OG
id|VolumeSize
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;jfs_extendfs: invalid size&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* check the device */
id|bh
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
id|newLVSize
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;jfs_extendfs: invalid size&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|bforget
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
multiline_comment|/* Can&squot;t extend write-protected drive */
r_if
c_cond
(paren
id|isReadOnly
c_func
(paren
id|ipbmap
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;jfs_extendfs: read-only file system&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EROFS
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *      reconfigure LV spaces&n;&t; *      ---------------------&n;&t; *&n;&t; * validate new size, or, if not specified, determine new size&n;&t; */
multiline_comment|/*&n;&t; * reconfigure inline log space:&n;&t; */
r_if
c_cond
(paren
(paren
id|sbi-&gt;mntflag
op_amp
id|JFS_INLINELOG
)paren
)paren
(brace
r_if
c_cond
(paren
id|newLogSize
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * no size specified: default to 1/256 of aggregate&n;&t;&t;&t; * size; rounded up to a megabyte boundary;&n;&t;&t;&t; */
id|newLogSize
op_assign
id|newLVSize
op_rshift
l_int|8
suffix:semicolon
id|t32
op_assign
(paren
l_int|1
op_lshift
(paren
l_int|20
op_minus
id|sbi-&gt;l2bsize
)paren
)paren
op_minus
l_int|1
suffix:semicolon
id|newLogSize
op_assign
(paren
id|newLogSize
op_plus
id|t32
)paren
op_amp
op_complement
id|t32
suffix:semicolon
id|newLogSize
op_assign
id|min
c_func
(paren
id|newLogSize
comma
id|MEGABYTE32
op_rshift
id|sbi-&gt;l2bsize
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * convert the newLogSize to fs blocks.&n;&t;&t;&t; *&n;&t;&t;&t; * Since this is given in megabytes, it will always be&n;&t;&t;&t; * an even number of pages.&n;&t;&t;&t; */
id|newLogSize
op_assign
(paren
id|newLogSize
op_star
id|MEGABYTE
)paren
op_rshift
id|sbi-&gt;l2bsize
suffix:semicolon
)brace
)brace
r_else
id|newLogSize
op_assign
l_int|0
suffix:semicolon
id|newLogAddress
op_assign
id|newLVSize
op_minus
id|newLogSize
suffix:semicolon
multiline_comment|/*&n;&t; * reconfigure fsck work space:&n;&t; *&n;&t; * configure it to the end of the logical volume regardless of&n;&t; * whether file system extends to the end of the aggregate;&n;&t; * Need enough 4k pages to cover:&n;&t; *  - 1 bit per block in aggregate rounded up to BPERDMAP boundary&n;&t; *  - 1 extra page to handle control page and intermediate level pages&n;&t; *  - 50 extra pages for the chkdsk service log&n;&t; */
id|t64
op_assign
(paren
(paren
id|newLVSize
op_minus
id|newLogSize
op_plus
id|BPERDMAP
op_minus
l_int|1
)paren
op_rshift
id|L2BPERDMAP
)paren
op_lshift
id|L2BPERDMAP
suffix:semicolon
id|t32
op_assign
(paren
(paren
id|t64
op_plus
(paren
id|BITSPERPAGE
op_minus
l_int|1
)paren
)paren
op_div
id|BITSPERPAGE
)paren
op_plus
l_int|1
op_plus
l_int|50
suffix:semicolon
id|newFSCKSize
op_assign
id|t32
op_lshift
id|sbi-&gt;l2nbperpage
suffix:semicolon
id|newFSCKAddress
op_assign
id|newLogAddress
op_minus
id|newFSCKSize
suffix:semicolon
multiline_comment|/*&n;&t; * compute new file system space;&n;&t; */
id|newFSSize
op_assign
id|newLVSize
op_minus
id|newLogSize
op_minus
id|newFSCKSize
suffix:semicolon
multiline_comment|/* file system cannot be shrinked */
r_if
c_cond
(paren
id|newFSSize
OL
id|bmp-&gt;db_mapsize
)paren
(brace
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If we&squot;re expanding enough that the inline log does not overlap&n;&t; * the old one, we can format the new log before we quiesce the&n;&t; * filesystem.&n;&t; */
r_if
c_cond
(paren
(paren
id|sbi-&gt;mntflag
op_amp
id|JFS_INLINELOG
)paren
op_logical_and
(paren
id|newLogAddress
OG
id|oldLVSize
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|lmLogFormat
c_func
(paren
id|log
comma
id|newLogAddress
comma
id|newLogSize
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|log_formatted
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *      quiesce file system&n;&t; *&n;&t; * (prepare to move the inline log and to prevent map update)&n;&t; *&n;&t; * block any new transactions and wait for completion of&n;&t; * all wip transactions and flush modified pages s.t.&n;&t; * on-disk file system is in consistent state and&n;&t; * log is not required for recovery.&n;&t; */
id|txQuiesce
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sbi-&gt;mntflag
op_amp
id|JFS_INLINELOG
)paren
(brace
multiline_comment|/*&n;&t;&t; * deactivate old inline log&n;&t;&t; */
id|lmLogShutdown
c_func
(paren
id|log
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * mark on-disk super block for fs in transition;&n;&t;&t; *&n;&t;&t; * update on-disk superblock for the new space configuration&n;&t;&t; * of inline log space and fsck work space descriptors:&n;&t;&t; * N.B. FS descriptor is NOT updated;&n;&t;&t; *&n;&t;&t; * crash recovery:&n;&t;&t; * logredo(): if FM_EXTENDFS, return to fsck() for cleanup;&n;&t;&t; * fsck(): if FM_EXTENDFS, reformat inline log and fsck&n;&t;&t; * workspace from superblock inline log descriptor and fsck&n;&t;&t; * workspace descriptor;&n;&t;&t; */
multiline_comment|/* read in superblock */
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|readSuper
c_func
(paren
id|sb
comma
op_amp
id|bh
)paren
)paren
)paren
r_goto
id|error_out
suffix:semicolon
id|j_sb
op_assign
(paren
r_struct
id|jfs_superblock
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
multiline_comment|/* mark extendfs() in progress */
id|j_sb-&gt;s_state
op_or_assign
id|cpu_to_le32
c_func
(paren
id|FM_EXTENDFS
)paren
suffix:semicolon
id|j_sb-&gt;s_xsize
op_assign
id|cpu_to_le64
c_func
(paren
id|newFSSize
)paren
suffix:semicolon
id|PXDaddress
c_func
(paren
op_amp
id|j_sb-&gt;s_xfsckpxd
comma
id|newFSCKAddress
)paren
suffix:semicolon
id|PXDlength
c_func
(paren
op_amp
id|j_sb-&gt;s_xfsckpxd
comma
id|newFSCKSize
)paren
suffix:semicolon
id|PXDaddress
c_func
(paren
op_amp
id|j_sb-&gt;s_xlogpxd
comma
id|newLogAddress
)paren
suffix:semicolon
id|PXDlength
c_func
(paren
op_amp
id|j_sb-&gt;s_xlogpxd
comma
id|newLogSize
)paren
suffix:semicolon
multiline_comment|/* synchronously update superblock */
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|sync_dirty_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * format new inline log synchronously;&n;&t;&t; *&n;&t;&t; * crash recovery: if log move in progress,&n;&t;&t; * reformat log and exit success;&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|log_formatted
)paren
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|lmLogFormat
c_func
(paren
id|log
comma
id|newLogAddress
comma
id|newLogSize
)paren
)paren
)paren
r_goto
id|error_out
suffix:semicolon
multiline_comment|/*&n;&t;&t; * activate new log&n;&t;&t; */
id|log-&gt;base
op_assign
id|newLogAddress
suffix:semicolon
id|log-&gt;size
op_assign
id|newLogSize
op_rshift
(paren
id|L2LOGPSIZE
op_minus
id|sb-&gt;s_blocksize_bits
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|lmLogInit
c_func
(paren
id|log
)paren
)paren
)paren
r_goto
id|error_out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *      extend block allocation map&n;&t; *      ---------------------------&n;&t; *&n;&t; * extendfs() for new extension, retry after crash recovery;&n;&t; *&n;&t; * note: both logredo() and fsck() rebuild map from&n;&t; * the bitmap and configuration parameter from superblock&n;&t; * (disregarding all other control information in the map);&n;&t; *&n;&t; * superblock:&n;&t; *  s_size: aggregate size in physical blocks;&n;&t; */
multiline_comment|/*&n;&t; *      compute the new block allocation map configuration&n;&t; *&n;&t; * map dinode:&n;&t; *  di_size: map file size in byte;&n;&t; *  di_nblocks: number of blocks allocated for map file;&n;&t; *  di_mapsize: number of blocks in aggregate (covered by map);&n;&t; * map control page:&n;&t; *  db_mapsize: number of blocks in aggregate (covered by map);&n;&t; */
id|newMapSize
op_assign
id|newFSSize
suffix:semicolon
multiline_comment|/* number of data pages of new bmap file:&n;&t; * roundup new size to full dmap page boundary and&n;&t; * add 1 extra dmap page for next extendfs()&n;&t; */
id|t64
op_assign
(paren
id|newMapSize
op_minus
l_int|1
)paren
op_plus
id|BPERDMAP
suffix:semicolon
id|newNpages
op_assign
id|BLKTODMAPN
c_func
(paren
id|t64
)paren
op_plus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; *      extend map from current map (WITHOUT growing mapfile)&n;&t; *&n;&t; * map new extension with unmapped part of the last partial&n;&t; * dmap page, if applicable, and extra page(s) allocated&n;&t; * at end of bmap by mkfs() or previous extendfs();&n;&t; */
id|extendBmap
suffix:colon
multiline_comment|/* compute number of blocks requested to extend */
id|mapSize
op_assign
id|bmp-&gt;db_mapsize
suffix:semicolon
id|XAddress
op_assign
id|mapSize
suffix:semicolon
multiline_comment|/* eXtension Address */
id|XSize
op_assign
id|newMapSize
op_minus
id|mapSize
suffix:semicolon
multiline_comment|/* eXtension Size */
id|old_agsize
op_assign
id|bmp-&gt;db_agsize
suffix:semicolon
multiline_comment|/* We need to know if this changes */
multiline_comment|/* compute number of blocks that can be extended by current mapfile */
id|t64
op_assign
id|dbMapFileSizeToMapSize
c_func
(paren
id|ipbmap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mapSize
OG
id|t64
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;jfs_extendfs: mapSize (0x%Lx) &gt; t64 (0x%Lx)&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|mapSize
comma
(paren
r_int
r_int
)paren
id|t64
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|error_out
suffix:semicolon
)brace
id|nblocks
op_assign
id|min
c_func
(paren
id|t64
op_minus
id|mapSize
comma
id|XSize
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * update map pages for new extension:&n;&t; *&n;&t; * update/init dmap and bubble up the control hierarchy&n;&t; * incrementally fold up dmaps into upper levels;&n;&t; * update bmap control page;&n;&t; */
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|dbExtendFS
c_func
(paren
id|ipbmap
comma
id|XAddress
comma
id|nblocks
)paren
)paren
)paren
r_goto
id|error_out
suffix:semicolon
multiline_comment|/*&n;&t; * the map now has extended to cover additional nblocks:&n;&t; * dn_mapsize = oldMapsize + nblocks;&n;&t; */
multiline_comment|/* ipbmap-&gt;i_mapsize += nblocks; */
id|XSize
op_sub_assign
id|nblocks
suffix:semicolon
multiline_comment|/*&n;&t; *      grow map file to cover remaining extension&n;&t; *      and/or one extra dmap page for next extendfs();&n;&t; *&n;&t; * allocate new map pages and its backing blocks, and&n;&t; * update map file xtree&n;&t; */
multiline_comment|/* compute number of data pages of current bmap file */
id|nPages
op_assign
id|ipbmap-&gt;i_size
op_rshift
id|L2PSIZE
suffix:semicolon
multiline_comment|/* need to grow map file ? */
r_if
c_cond
(paren
id|nPages
op_eq
id|newNpages
)paren
r_goto
id|finalizeBmap
suffix:semicolon
multiline_comment|/*&n;&t; * grow bmap file for the new map pages required:&n;&t; *&n;&t; * allocate growth at the start of newly extended region;&n;&t; * bmap file only grows sequentially, i.e., both data pages&n;&t; * and possibly xtree index pages may grow in append mode,&n;&t; * s.t. logredo() can reconstruct pre-extension state&n;&t; * by washing away bmap file of pages outside s_size boundary;&n;&t; */
multiline_comment|/*&n;&t; * journal map file growth as if a regular file growth:&n;&t; * (note: bmap is created with di_mode = IFJOURNAL|IFREG);&n;&t; *&n;&t; * journaling of bmap file growth is not required since&n;&t; * logredo() do/can not use log records of bmap file growth&n;&t; * but it provides careful write semantics, pmap update, etc.;&n;&t; */
multiline_comment|/* synchronous write of data pages: bmap data pages are&n;&t; * cached in meta-data cache, and not written out&n;&t; * by txCommit();&n;&t; */
id|filemap_fdatawait
c_func
(paren
id|ipbmap-&gt;i_mapping
)paren
suffix:semicolon
id|filemap_fdatawrite
c_func
(paren
id|ipbmap-&gt;i_mapping
)paren
suffix:semicolon
id|filemap_fdatawait
c_func
(paren
id|ipbmap-&gt;i_mapping
)paren
suffix:semicolon
id|diWriteSpecial
c_func
(paren
id|ipbmap
comma
l_int|0
)paren
suffix:semicolon
id|newPage
op_assign
id|nPages
suffix:semicolon
multiline_comment|/* first new page number */
id|xoff
op_assign
id|newPage
op_lshift
id|sbi-&gt;l2nbperpage
suffix:semicolon
id|xlen
op_assign
(paren
id|newNpages
op_minus
id|nPages
)paren
op_lshift
id|sbi-&gt;l2nbperpage
suffix:semicolon
id|xlen
op_assign
id|min
c_func
(paren
id|xlen
comma
(paren
r_int
)paren
id|nblocks
)paren
op_amp
op_complement
(paren
id|sbi-&gt;nbperpage
op_minus
l_int|1
)paren
suffix:semicolon
id|xaddr
op_assign
id|XAddress
suffix:semicolon
id|tid
op_assign
id|txBegin
c_func
(paren
id|sb
comma
id|COMMIT_FORCE
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|xtAppend
c_func
(paren
id|tid
comma
id|ipbmap
comma
l_int|0
comma
id|xoff
comma
id|nblocks
comma
op_amp
id|xlen
comma
op_amp
id|xaddr
comma
l_int|0
)paren
)paren
)paren
(brace
id|txEnd
c_func
(paren
id|tid
)paren
suffix:semicolon
r_goto
id|error_out
suffix:semicolon
)brace
multiline_comment|/* update bmap file size */
id|ipbmap-&gt;i_size
op_add_assign
id|xlen
op_lshift
id|sbi-&gt;l2bsize
suffix:semicolon
id|ipbmap-&gt;i_blocks
op_add_assign
id|LBLK2PBLK
c_func
(paren
id|sb
comma
id|xlen
)paren
suffix:semicolon
id|iplist
(braket
l_int|0
)braket
op_assign
id|ipbmap
suffix:semicolon
id|rc
op_assign
id|txCommit
c_func
(paren
id|tid
comma
l_int|1
comma
op_amp
id|iplist
(braket
l_int|0
)braket
comma
id|COMMIT_FORCE
)paren
suffix:semicolon
id|txEnd
c_func
(paren
id|tid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_goto
id|error_out
suffix:semicolon
multiline_comment|/*&n;&t; * map file has been grown now to cover extension to further out;&n;&t; * di_size = new map file size;&n;&t; *&n;&t; * if huge extension, the previous extension based on previous&n;&t; * map file size may not have been sufficient to cover whole extension&n;&t; * (it could have been used up for new map pages),&n;&t; * but the newly grown map file now covers lot bigger new free space&n;&t; * available for further extension of map;&n;&t; */
multiline_comment|/* any more blocks to extend ? */
r_if
c_cond
(paren
id|XSize
)paren
r_goto
id|extendBmap
suffix:semicolon
id|finalizeBmap
suffix:colon
multiline_comment|/* finalize bmap */
id|dbFinalizeBmap
c_func
(paren
id|ipbmap
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *      update inode allocation map&n;&t; *      ---------------------------&n;&t; *&n;&t; * move iag lists from old to new iag;&n;&t; * agstart field is not updated for logredo() to reconstruct&n;&t; * iag lists if system crash occurs.&n;&t; * (computation of ag number from agstart based on agsize&n;&t; * will correctly identify the new ag);&n;&t; */
multiline_comment|/* if new AG size the same as old AG size, done! */
r_if
c_cond
(paren
id|bmp-&gt;db_agsize
op_ne
id|old_agsize
)paren
(brace
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|diExtendFS
c_func
(paren
id|ipimap
comma
id|ipbmap
)paren
)paren
)paren
r_goto
id|error_out
suffix:semicolon
multiline_comment|/* finalize imap */
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|diSync
c_func
(paren
id|ipimap
)paren
)paren
)paren
r_goto
id|error_out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *      finalize&n;&t; *      --------&n;&t; *&n;&t; * extension is committed when on-disk super block is&n;&t; * updated with new descriptors: logredo will recover&n;&t; * crash before it to pre-extension state;&n;&t; */
multiline_comment|/* sync log to skip log replay of bmap file growth transaction; */
multiline_comment|/* lmLogSync(log, 1); */
multiline_comment|/*&n;&t; * synchronous write bmap global control page;&n;&t; * for crash before completion of write&n;&t; * logredo() will recover to pre-extendfs state;&n;&t; * for crash after completion of write,&n;&t; * logredo() will recover post-extendfs state;&n;&t; */
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|dbSync
c_func
(paren
id|ipbmap
)paren
)paren
)paren
r_goto
id|error_out
suffix:semicolon
multiline_comment|/*&n;&t; * copy primary bmap inode to secondary bmap inode&n;&t; */
id|ipbmap2
op_assign
id|diReadSpecial
c_func
(paren
id|sb
comma
id|BMAP_I
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ipbmap2
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;jfs_extendfs: diReadSpecial(bmap) failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|error_out
suffix:semicolon
)brace
id|memcpy
c_func
(paren
op_amp
id|JFS_IP
c_func
(paren
id|ipbmap2
)paren
op_member_access_from_pointer
id|i_xtroot
comma
op_amp
id|JFS_IP
c_func
(paren
id|ipbmap
)paren
op_member_access_from_pointer
id|i_xtroot
comma
l_int|288
)paren
suffix:semicolon
id|ipbmap2-&gt;i_size
op_assign
id|ipbmap-&gt;i_size
suffix:semicolon
id|ipbmap2-&gt;i_blocks
op_assign
id|ipbmap-&gt;i_blocks
suffix:semicolon
id|diWriteSpecial
c_func
(paren
id|ipbmap2
comma
l_int|1
)paren
suffix:semicolon
id|diFreeSpecial
c_func
(paren
id|ipbmap2
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *      update superblock&n;&t; */
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|readSuper
c_func
(paren
id|sb
comma
op_amp
id|bh
)paren
)paren
)paren
r_goto
id|error_out
suffix:semicolon
id|j_sb
op_assign
(paren
r_struct
id|jfs_superblock
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
multiline_comment|/* mark extendfs() completion */
id|j_sb-&gt;s_state
op_and_assign
id|cpu_to_le32
c_func
(paren
op_complement
id|FM_EXTENDFS
)paren
suffix:semicolon
id|j_sb-&gt;s_size
op_assign
id|cpu_to_le64
c_func
(paren
id|bmp-&gt;db_mapsize
op_lshift
id|le16_to_cpu
c_func
(paren
id|j_sb-&gt;s_l2bfactor
)paren
)paren
suffix:semicolon
id|j_sb-&gt;s_agsize
op_assign
id|cpu_to_le32
c_func
(paren
id|bmp-&gt;db_agsize
)paren
suffix:semicolon
multiline_comment|/* update inline log space descriptor */
r_if
c_cond
(paren
id|sbi-&gt;mntflag
op_amp
id|JFS_INLINELOG
)paren
(brace
id|PXDaddress
c_func
(paren
op_amp
(paren
id|j_sb-&gt;s_logpxd
)paren
comma
id|newLogAddress
)paren
suffix:semicolon
id|PXDlength
c_func
(paren
op_amp
(paren
id|j_sb-&gt;s_logpxd
)paren
comma
id|newLogSize
)paren
suffix:semicolon
)brace
multiline_comment|/* record log&squot;s mount serial number */
id|j_sb-&gt;s_logserial
op_assign
id|cpu_to_le32
c_func
(paren
id|log-&gt;serial
)paren
suffix:semicolon
multiline_comment|/* update fsck work space descriptor */
id|PXDaddress
c_func
(paren
op_amp
(paren
id|j_sb-&gt;s_fsckpxd
)paren
comma
id|newFSCKAddress
)paren
suffix:semicolon
id|PXDlength
c_func
(paren
op_amp
(paren
id|j_sb-&gt;s_fsckpxd
)paren
comma
id|newFSCKSize
)paren
suffix:semicolon
id|j_sb-&gt;s_fscklog
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* sb-&gt;s_fsckloglen remains the same */
multiline_comment|/* Update secondary superblock */
id|bh2
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
id|SUPER2_OFF
op_rshift
id|sb-&gt;s_blocksize_bits
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh2
)paren
(brace
id|j_sb2
op_assign
(paren
r_struct
id|jfs_superblock
op_star
)paren
id|bh2-&gt;b_data
suffix:semicolon
id|memcpy
c_func
(paren
id|j_sb2
comma
id|j_sb
comma
r_sizeof
(paren
r_struct
id|jfs_superblock
)paren
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|sync_dirty_buffer
c_func
(paren
id|bh2
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh2
)paren
suffix:semicolon
)brace
multiline_comment|/* write primary superblock */
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|sync_dirty_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_goto
id|resume
suffix:semicolon
id|error_out
suffix:colon
id|jfs_error
c_func
(paren
id|sb
comma
l_string|&quot;jfs_extendfs&quot;
)paren
suffix:semicolon
id|resume
suffix:colon
multiline_comment|/*&n;&t; *      resume file system transactions&n;&t; */
id|txResume
c_func
(paren
id|sb
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
)brace
eof
