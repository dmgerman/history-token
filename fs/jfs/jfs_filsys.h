multiline_comment|/*&n; *   Copyright (c) International Business Machines Corp., 2000-2001&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#ifndef _H_JFS_FILSYS
DECL|macro|_H_JFS_FILSYS
mdefine_line|#define _H_JFS_FILSYS
multiline_comment|/*&n; *&t;jfs_filsys.h&n; *&n; * file system (implementation-dependent) constants &n; *&n; * refer to &lt;limits.h&gt; for system wide implementation-dependent constants &n; */
multiline_comment|/*&n; *&t; file system option (superblock flag)&n; */
multiline_comment|/* platform option (conditional compilation) */
DECL|macro|JFS_AIX
mdefine_line|#define JFS_AIX&t;&t;0x80000000&t;/* AIX support */
multiline_comment|/*&t;POSIX name/directory  support */
DECL|macro|JFS_OS2
mdefine_line|#define JFS_OS2&t;&t;0x40000000&t;/* OS/2 support */
multiline_comment|/*&t;case-insensitive name/directory support */
DECL|macro|JFS_DFS
mdefine_line|#define JFS_DFS&t;&t;0x20000000&t;/* DCE DFS LFS support */
DECL|macro|JFS_LINUX
mdefine_line|#define JFS_LINUX      &t;0x10000000&t;/* Linux support */
multiline_comment|/*&t;case-sensitive name/directory support */
multiline_comment|/* directory option */
DECL|macro|JFS_UNICODE
mdefine_line|#define JFS_UNICODE&t;0x00000001&t;/* unicode name */
multiline_comment|/* commit option */
DECL|macro|JFS_COMMIT
mdefine_line|#define&t;JFS_COMMIT&t;0x00000f00&t;/* commit option mask */
DECL|macro|JFS_GROUPCOMMIT
mdefine_line|#define&t;JFS_GROUPCOMMIT&t;0x00000100&t;/* group (of 1) commit */
DECL|macro|JFS_LAZYCOMMIT
mdefine_line|#define&t;JFS_LAZYCOMMIT&t;0x00000200&t;/* lazy commit */
DECL|macro|JFS_TMPFS
mdefine_line|#define&t;JFS_TMPFS&t;0x00000400&t;/* temporary file system - &n;&t;&t;&t;&t;&t; * do not log/commit:&n;&t;&t;&t;&t;&t; */
multiline_comment|/* log logical volume option */
DECL|macro|JFS_INLINELOG
mdefine_line|#define&t;JFS_INLINELOG&t;0x00000800&t;/* inline log within file system */
DECL|macro|JFS_INLINEMOVE
mdefine_line|#define JFS_INLINEMOVE&t;0x00001000&t;/* inline log being moved */
multiline_comment|/* Secondary aggregate inode table */
DECL|macro|JFS_BAD_SAIT
mdefine_line|#define JFS_BAD_SAIT&t;0x00010000&t;/* current secondary ait is bad */
multiline_comment|/* sparse regular file support */
DECL|macro|JFS_SPARSE
mdefine_line|#define JFS_SPARSE&t;0x00020000&t;/* sparse regular file */
multiline_comment|/* DASD Limits&t;&t;F226941 */
DECL|macro|JFS_DASD_ENABLED
mdefine_line|#define JFS_DASD_ENABLED&t;0x00040000&t;/* DASD limits enabled */
DECL|macro|JFS_DASD_PRIME
mdefine_line|#define&t;JFS_DASD_PRIME&t;&t;0x00080000&t;/* Prime DASD usage on boot */
multiline_comment|/* big endian flag */
DECL|macro|JFS_SWAP_BYTES
mdefine_line|#define&t;JFS_SWAP_BYTES&t;&t;0x00100000&t;/* running on big endian computer */
multiline_comment|/* Directory index */
DECL|macro|JFS_DIR_INDEX
mdefine_line|#define JFS_DIR_INDEX&t;&t;0x00200000&t;/* Persistant index for */
multiline_comment|/* directory entries    */
multiline_comment|/*&n; *&t;buffer cache configuration&n; */
multiline_comment|/* page size */
macro_line|#ifdef PSIZE
DECL|macro|PSIZE
macro_line|#undef PSIZE
macro_line|#endif
DECL|macro|PSIZE
mdefine_line|#define&t;PSIZE&t;&t;4096&t;/* page size (in byte) */
DECL|macro|L2PSIZE
mdefine_line|#define&t;L2PSIZE&t;&t;12&t;/* log2(PSIZE) */
DECL|macro|POFFSET
mdefine_line|#define&t;POFFSET&t;&t;4095&t;/* offset within page */
multiline_comment|/* buffer page size */
DECL|macro|BPSIZE
mdefine_line|#define BPSIZE&t;PSIZE
multiline_comment|/*&n; *&t;fs fundamental size&n; *&n; * PSIZE &gt;= file system block size &gt;= PBSIZE &gt;= DISIZE&n; */
DECL|macro|PBSIZE
mdefine_line|#define&t;PBSIZE&t;&t;512&t;/* physical block size (in byte) */
DECL|macro|L2PBSIZE
mdefine_line|#define&t;L2PBSIZE&t;9&t;/* log2(PBSIZE) */
DECL|macro|DISIZE
mdefine_line|#define DISIZE&t;&t;512&t;/* on-disk inode size (in byte) */
DECL|macro|L2DISIZE
mdefine_line|#define L2DISIZE&t;9&t;/* log2(DISIZE) */
DECL|macro|IDATASIZE
mdefine_line|#define IDATASIZE&t;256&t;/* inode inline data size */
DECL|macro|IXATTRSIZE
mdefine_line|#define&t;IXATTRSIZE&t;128&t;/* inode inline extended attribute size */
DECL|macro|XTPAGE_SIZE
mdefine_line|#define XTPAGE_SIZE     4096
DECL|macro|log2_PAGESIZE
mdefine_line|#define log2_PAGESIZE     12
DECL|macro|IAG_SIZE
mdefine_line|#define IAG_SIZE        4096
DECL|macro|IAG_EXTENT_SIZE
mdefine_line|#define IAG_EXTENT_SIZE 4096
DECL|macro|INOSPERIAG
mdefine_line|#define&t;INOSPERIAG&t;4096&t;/* number of disk inodes per iag */
DECL|macro|L2INOSPERIAG
mdefine_line|#define&t;L2INOSPERIAG&t;12&t;/* l2 number of disk inodes per iag */
DECL|macro|INOSPEREXT
mdefine_line|#define INOSPEREXT&t;32&t;/* number of disk inode per extent */
DECL|macro|L2INOSPEREXT
mdefine_line|#define L2INOSPEREXT&t;5&t;/* l2 number of disk inode per extent */
DECL|macro|IXSIZE
mdefine_line|#define&t;IXSIZE&t;&t;(DISIZE * INOSPEREXT)&t;/* inode extent size */
DECL|macro|INOSPERPAGE
mdefine_line|#define&t;INOSPERPAGE&t;8&t;/* number of disk inodes per 4K page */
DECL|macro|L2INOSPERPAGE
mdefine_line|#define&t;L2INOSPERPAGE&t;3&t;/* log2(INOSPERPAGE) */
DECL|macro|IAGFREELIST_LWM
mdefine_line|#define&t;IAGFREELIST_LWM&t;64
DECL|macro|INODE_EXTENT_SIZE
mdefine_line|#define INODE_EXTENT_SIZE&t;IXSIZE&t;/* inode extent size */
DECL|macro|NUM_INODE_PER_EXTENT
mdefine_line|#define NUM_INODE_PER_EXTENT&t;INOSPEREXT
DECL|macro|NUM_INODE_PER_IAG
mdefine_line|#define NUM_INODE_PER_IAG&t;INOSPERIAG
DECL|macro|MINBLOCKSIZE
mdefine_line|#define MINBLOCKSIZE&t;&t;512
DECL|macro|MAXBLOCKSIZE
mdefine_line|#define MAXBLOCKSIZE&t;&t;4096
DECL|macro|MAXFILESIZE
mdefine_line|#define&t;MAXFILESIZE&t;&t;((s64)1 &lt;&lt; 52)
DECL|macro|JFS_LINK_MAX
mdefine_line|#define JFS_LINK_MAX&t;&t;65535&t;/* nlink_t is unsigned short */
multiline_comment|/* Minimum number of bytes supported for a JFS partition */
DECL|macro|MINJFS
mdefine_line|#define MINJFS&t;&t;&t;(0x1000000)
DECL|macro|MINJFSTEXT
mdefine_line|#define MINJFSTEXT&t;&t;&quot;16&quot;
multiline_comment|/*&n; * file system block size -&gt; physical block size&n; */
DECL|macro|LBOFFSET
mdefine_line|#define LBOFFSET(x)&t;((x) &amp; (PBSIZE - 1))
DECL|macro|LBNUMBER
mdefine_line|#define LBNUMBER(x)&t;((x) &gt;&gt; L2PBSIZE)
DECL|macro|LBLK2PBLK
mdefine_line|#define&t;LBLK2PBLK(sb,b)&t;((b) &lt;&lt; (sb-&gt;s_blocksize_bits - L2PBSIZE))
DECL|macro|PBLK2LBLK
mdefine_line|#define&t;PBLK2LBLK(sb,b)&t;((b) &gt;&gt; (sb-&gt;s_blocksize_bits - L2PBSIZE))
multiline_comment|/* size in byte -&gt; last page number */
DECL|macro|SIZE2PN
mdefine_line|#define&t;SIZE2PN(size)&t;( ((s64)((size) - 1)) &gt;&gt; (L2PSIZE) )
multiline_comment|/* size in byte -&gt; last file system block number */
DECL|macro|SIZE2BN
mdefine_line|#define&t;SIZE2BN(size, l2bsize) ( ((s64)((size) - 1)) &gt;&gt; (l2bsize) )
multiline_comment|/*&n; * fixed physical block address (physical block size = 512 byte)&n; *&n; * NOTE: since we can&squot;t guarantee a physical block size of 512 bytes the use of&n; *&t; these macros should be removed and the byte offset macros used instead.&n; */
DECL|macro|SUPER1_B
mdefine_line|#define SUPER1_B&t;64&t;/* primary superblock */
DECL|macro|AIMAP_B
mdefine_line|#define&t;AIMAP_B&t;&t;(SUPER1_B + 8)&t;/* 1st extent of aggregate inode map */
DECL|macro|AITBL_B
mdefine_line|#define&t;AITBL_B&t;&t;(AIMAP_B + 16)&t;/*&n;&t;&t;&t;&t;&t; * 1st extent of aggregate inode table&n;&t;&t;&t;&t;&t; */
DECL|macro|SUPER2_B
mdefine_line|#define&t;SUPER2_B&t;(AITBL_B + 32)&t;/* 2ndary superblock pbn */
DECL|macro|BMAP_B
mdefine_line|#define&t;BMAP_B&t;&t;(SUPER2_B + 8)&t;/* block allocation map */
multiline_comment|/*&n; * SIZE_OF_SUPER defines the total amount of space reserved on disk for the&n; * superblock.  This is not the same as the superblock structure, since all of&n; * this space is not currently being used.&n; */
DECL|macro|SIZE_OF_SUPER
mdefine_line|#define SIZE_OF_SUPER&t;PSIZE
multiline_comment|/*&n; * SIZE_OF_AG_TABLE defines the amount of space reserved to hold the AG table&n; */
DECL|macro|SIZE_OF_AG_TABLE
mdefine_line|#define SIZE_OF_AG_TABLE&t;PSIZE
multiline_comment|/*&n; * SIZE_OF_MAP_PAGE defines the amount of disk space reserved for each page of&n; * the inode allocation map (to hold iag)&n; */
DECL|macro|SIZE_OF_MAP_PAGE
mdefine_line|#define SIZE_OF_MAP_PAGE&t;PSIZE
multiline_comment|/*&n; * fixed byte offset address&n; */
DECL|macro|SUPER1_OFF
mdefine_line|#define SUPER1_OFF&t;0x8000&t;/* primary superblock */
DECL|macro|AIMAP_OFF
mdefine_line|#define AIMAP_OFF&t;(SUPER1_OFF + SIZE_OF_SUPER)
multiline_comment|/*&n;&t;&t;&t;&t;&t; * Control page of aggregate inode map&n;&t;&t;&t;&t;&t; * followed by 1st extent of map&n;&t;&t;&t;&t;&t; */
DECL|macro|AITBL_OFF
mdefine_line|#define AITBL_OFF&t;(AIMAP_OFF + (SIZE_OF_MAP_PAGE &lt;&lt; 1))
multiline_comment|/* &n;&t;&t;&t;&t;&t; * 1st extent of aggregate inode table&n;&t;&t;&t;&t;&t; */
DECL|macro|SUPER2_OFF
mdefine_line|#define SUPER2_OFF&t;(AITBL_OFF + INODE_EXTENT_SIZE)
multiline_comment|/*&n;&t;&t;&t;&t;&t; * secondary superblock&n;&t;&t;&t;&t;&t; */
DECL|macro|BMAP_OFF
mdefine_line|#define BMAP_OFF&t;(SUPER2_OFF + SIZE_OF_SUPER)
multiline_comment|/*&n;&t;&t;&t;&t;&t; * block allocation map&n;&t;&t;&t;&t;&t; */
multiline_comment|/*&n; * The following macro is used to indicate the number of reserved disk blocks at&n; * the front of an aggregate, in terms of physical blocks.  This value is&n; * currently defined to be 32K.  This turns out to be the same as the primary&n; * superblock&squot;s address, since it directly follows the reserved blocks.&n; */
DECL|macro|AGGR_RSVD_BLOCKS
mdefine_line|#define AGGR_RSVD_BLOCKS&t;SUPER1_B
multiline_comment|/*&n; * The following macro is used to indicate the number of reserved bytes at the&n; * front of an aggregate.  This value is currently defined to be 32K.  This&n; * turns out to be the same as the primary superblock&squot;s byte offset, since it&n; * directly follows the reserved blocks.&n; */
DECL|macro|AGGR_RSVD_BYTES
mdefine_line|#define AGGR_RSVD_BYTES&t;SUPER1_OFF
multiline_comment|/*&n; * The following macro defines the byte offset for the first inode extent in&n; * the aggregate inode table.  This allows us to find the self inode to find the&n; * rest of the table.  Currently this value is 44K.&n; */
DECL|macro|AGGR_INODE_TABLE_START
mdefine_line|#define AGGR_INODE_TABLE_START&t;AITBL_OFF
multiline_comment|/*&n; *&t;fixed reserved inode number&n; */
multiline_comment|/* aggregate inode */
DECL|macro|AGGR_RESERVED_I
mdefine_line|#define AGGR_RESERVED_I&t;0&t;/* aggregate inode (reserved) */
DECL|macro|AGGREGATE_I
mdefine_line|#define&t;AGGREGATE_I&t;1&t;/* aggregate inode map inode */
DECL|macro|BMAP_I
mdefine_line|#define&t;BMAP_I&t;&t;2&t;/* aggregate block allocation map inode */
DECL|macro|LOG_I
mdefine_line|#define&t;LOG_I&t;&t;3&t;/* aggregate inline log inode */
DECL|macro|BADBLOCK_I
mdefine_line|#define BADBLOCK_I&t;4&t;/* aggregate bad block inode */
DECL|macro|FILESYSTEM_I
mdefine_line|#define&t;FILESYSTEM_I&t;16&t;/* 1st/only fileset inode in ait:&n;&t;&t;&t;&t; * fileset inode map inode&n;&t;&t;&t;&t; */
multiline_comment|/* per fileset inode */
DECL|macro|FILESET_RSVD_I
mdefine_line|#define FILESET_RSVD_I&t;0&t;/* fileset inode (reserved) */
DECL|macro|FILESET_EXT_I
mdefine_line|#define FILESET_EXT_I&t;1&t;/* fileset inode extension */
DECL|macro|ROOT_I
mdefine_line|#define&t;ROOT_I&t;&t;2&t;/* fileset root inode */
DECL|macro|ACL_I
mdefine_line|#define ACL_I&t;&t;3&t;/* fileset ACL inode */
DECL|macro|FILESET_OBJECT_I
mdefine_line|#define FILESET_OBJECT_I 4&t;/* the first fileset inode available for a file&n;&t;&t;&t;&t; * or directory or link...&n;&t;&t;&t;&t; */
DECL|macro|FIRST_FILESET_INO
mdefine_line|#define FIRST_FILESET_INO 16&t;/* the first aggregate inode which describes&n;&t;&t;&t;&t; * an inode.  (To fsck this is also the first&n;&t;&t;&t;&t; * inode in part 2 of the agg inode table.)&n;&t;&t;&t;&t; */
multiline_comment|/*&n; *&t;directory configuration&n; */
DECL|macro|JFS_NAME_MAX
mdefine_line|#define JFS_NAME_MAX&t;255
DECL|macro|JFS_PATH_MAX
mdefine_line|#define JFS_PATH_MAX&t;BPSIZE
multiline_comment|/*&n; *&t;file system state (superblock state)&n; */
DECL|macro|FM_CLEAN
mdefine_line|#define FM_CLEAN 0x00000000&t;/* file system is unmounted and clean */
DECL|macro|FM_MOUNT
mdefine_line|#define FM_MOUNT 0x00000001&t;/* file system is mounted cleanly */
DECL|macro|FM_DIRTY
mdefine_line|#define FM_DIRTY 0x00000002&t;/* file system was not unmounted and clean &n;&t;&t;&t;&t; * when mounted or &n;&t;&t;&t;&t; * commit failure occurred while being mounted:&n;&t;&t;&t;&t; * fsck() must be run to repair &n;&t;&t;&t;&t; */
DECL|macro|FM_LOGREDO
mdefine_line|#define&t;FM_LOGREDO 0x00000004&t;/* log based recovery (logredo()) failed:&n;&t;&t;&t;&t; * fsck() must be run to repair &n;&t;&t;&t;&t; */
DECL|macro|FM_EXTENDFS
mdefine_line|#define&t;FM_EXTENDFS 0x00000008&t;/* file system extendfs() in progress */
macro_line|#endif&t;&t;&t;&t;/* _H_JFS_FILSYS */
eof
