multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_TYPES_H__
DECL|macro|__XFS_TYPES_H__
mdefine_line|#define __XFS_TYPES_H__
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n; * POSIX Extensions&n; */
DECL|typedef|uchar_t
r_typedef
r_int
r_char
id|uchar_t
suffix:semicolon
DECL|typedef|ushort_t
r_typedef
r_int
r_int
id|ushort_t
suffix:semicolon
DECL|typedef|uint_t
r_typedef
r_int
r_int
id|uint_t
suffix:semicolon
DECL|typedef|ulong_t
r_typedef
r_int
r_int
id|ulong_t
suffix:semicolon
multiline_comment|/*&n; * Additional type declarations for XFS&n; */
DECL|typedef|__int8_t
r_typedef
r_int
r_char
id|__int8_t
suffix:semicolon
DECL|typedef|__uint8_t
r_typedef
r_int
r_char
id|__uint8_t
suffix:semicolon
DECL|typedef|__int16_t
r_typedef
r_int
r_int
r_int
id|__int16_t
suffix:semicolon
DECL|typedef|__uint16_t
r_typedef
r_int
r_int
r_int
id|__uint16_t
suffix:semicolon
DECL|typedef|__int32_t
r_typedef
r_int
r_int
id|__int32_t
suffix:semicolon
DECL|typedef|__uint32_t
r_typedef
r_int
r_int
id|__uint32_t
suffix:semicolon
DECL|typedef|__int64_t
r_typedef
r_int
r_int
r_int
r_int
id|__int64_t
suffix:semicolon
DECL|typedef|__uint64_t
r_typedef
r_int
r_int
r_int
r_int
id|__uint64_t
suffix:semicolon
DECL|enumerator|B_FALSE
DECL|enumerator|B_TRUE
DECL|typedef|boolean_t
r_typedef
r_enum
(brace
id|B_FALSE
comma
id|B_TRUE
)brace
id|boolean_t
suffix:semicolon
DECL|typedef|prid_t
r_typedef
id|__int64_t
id|prid_t
suffix:semicolon
multiline_comment|/* project ID */
DECL|typedef|inst_t
r_typedef
id|__uint32_t
id|inst_t
suffix:semicolon
multiline_comment|/* an instruction */
DECL|typedef|xfs_off_t
r_typedef
id|__u64
id|xfs_off_t
suffix:semicolon
DECL|typedef|xfs_ino_t
r_typedef
id|__u64
id|xfs_ino_t
suffix:semicolon
multiline_comment|/* &lt;inode&gt; type */
DECL|typedef|xfs_daddr_t
r_typedef
id|__s64
id|xfs_daddr_t
suffix:semicolon
multiline_comment|/* &lt;disk address&gt; type */
DECL|typedef|xfs_caddr_t
r_typedef
r_char
op_star
id|xfs_caddr_t
suffix:semicolon
multiline_comment|/* &lt;core address&gt; type */
DECL|typedef|xfs_dev_t
r_typedef
id|__u32
id|xfs_dev_t
suffix:semicolon
DECL|typedef|timespec_t
r_typedef
r_struct
id|timespec
id|timespec_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|__u_bits
r_int
r_char
id|__u_bits
(braket
l_int|16
)braket
suffix:semicolon
DECL|typedef|uuid_t
)brace
id|uuid_t
suffix:semicolon
multiline_comment|/* __psint_t is the same size as a pointer */
macro_line|#if (BITS_PER_LONG == 32)
DECL|typedef|__psint_t
r_typedef
id|__int32_t
id|__psint_t
suffix:semicolon
DECL|typedef|__psunsigned_t
r_typedef
id|__uint32_t
id|__psunsigned_t
suffix:semicolon
macro_line|#elif (BITS_PER_LONG == 64)
DECL|typedef|__psint_t
r_typedef
id|__int64_t
id|__psint_t
suffix:semicolon
DECL|typedef|__psunsigned_t
r_typedef
id|__uint64_t
id|__psunsigned_t
suffix:semicolon
macro_line|#else
macro_line|#error BITS_PER_LONG must be 32 or 64
macro_line|#endif
macro_line|#endif&t;/* __KERNEL__ */
multiline_comment|/*&n; * Some types are conditional based on the selected configuration.&n; * Set XFS_BIG_FILESYSTEMS=1 or 0 depending on the desired configuration.&n; * XFS_BIG_FILESYSTEMS needs daddr_t to be 64 bits&n; *&n; * On linux right now we are limited to 2^32 512 byte blocks in a&n; * filesystem, Once this limit is changed, setting this to 1&n; * will allow XFS to go larger. With BIG_FILESYSTEMS set to 0&n; * a 4K block filesystem could still theoretically be 16Gbytes&n; * long, so on an ia32 box the 32 bit page index will then be&n; * the limiting factor.&n; */
macro_line|#ifndef XFS_BIG_FILESYSTEMS
DECL|macro|XFS_BIG_FILESYSTEMS
mdefine_line|#define XFS_BIG_FILESYSTEMS&t;0
macro_line|#endif
DECL|typedef|xfs_agblock_t
r_typedef
id|__uint32_t
id|xfs_agblock_t
suffix:semicolon
multiline_comment|/* blockno in alloc. group */
DECL|typedef|xfs_extlen_t
r_typedef
id|__uint32_t
id|xfs_extlen_t
suffix:semicolon
multiline_comment|/* extent length in blocks */
DECL|typedef|xfs_agnumber_t
r_typedef
id|__uint32_t
id|xfs_agnumber_t
suffix:semicolon
multiline_comment|/* allocation group number */
DECL|typedef|xfs_extnum_t
r_typedef
id|__int32_t
id|xfs_extnum_t
suffix:semicolon
multiline_comment|/* # of extents in a file */
DECL|typedef|xfs_aextnum_t
r_typedef
id|__int16_t
id|xfs_aextnum_t
suffix:semicolon
multiline_comment|/* # extents in an attribute fork */
DECL|typedef|xfs_fsize_t
r_typedef
id|__int64_t
id|xfs_fsize_t
suffix:semicolon
multiline_comment|/* bytes in a file */
DECL|typedef|xfs_ufsize_t
r_typedef
id|__uint64_t
id|xfs_ufsize_t
suffix:semicolon
multiline_comment|/* unsigned bytes in a file */
DECL|typedef|xfs_suminfo_t
r_typedef
id|__int32_t
id|xfs_suminfo_t
suffix:semicolon
multiline_comment|/* type of bitmap summary info */
DECL|typedef|xfs_rtword_t
r_typedef
id|__int32_t
id|xfs_rtword_t
suffix:semicolon
multiline_comment|/* word type for bitmap manipulations */
DECL|typedef|xfs_lsn_t
r_typedef
id|__int64_t
id|xfs_lsn_t
suffix:semicolon
multiline_comment|/* log sequence number */
DECL|typedef|xfs_tid_t
r_typedef
id|__int32_t
id|xfs_tid_t
suffix:semicolon
multiline_comment|/* transaction identifier */
DECL|typedef|xfs_dablk_t
r_typedef
id|__uint32_t
id|xfs_dablk_t
suffix:semicolon
multiline_comment|/* dir/attr block number (in file) */
DECL|typedef|xfs_dahash_t
r_typedef
id|__uint32_t
id|xfs_dahash_t
suffix:semicolon
multiline_comment|/* dir/attr hash value */
DECL|typedef|xfs_prid_t
r_typedef
id|__uint16_t
id|xfs_prid_t
suffix:semicolon
multiline_comment|/* prid_t truncated to 16bits in XFS */
multiline_comment|/*&n; * These types are 64 bits on disk but are either 32 or 64 bits in memory.&n; * Disk based types:&n; */
DECL|typedef|xfs_dfsbno_t
r_typedef
id|__uint64_t
id|xfs_dfsbno_t
suffix:semicolon
multiline_comment|/* blockno in filesystem (agno|agbno) */
DECL|typedef|xfs_drfsbno_t
r_typedef
id|__uint64_t
id|xfs_drfsbno_t
suffix:semicolon
multiline_comment|/* blockno in filesystem (raw) */
DECL|typedef|xfs_drtbno_t
r_typedef
id|__uint64_t
id|xfs_drtbno_t
suffix:semicolon
multiline_comment|/* extent (block) in realtime area */
DECL|typedef|xfs_dfiloff_t
r_typedef
id|__uint64_t
id|xfs_dfiloff_t
suffix:semicolon
multiline_comment|/* block number in a file */
DECL|typedef|xfs_dfilblks_t
r_typedef
id|__uint64_t
id|xfs_dfilblks_t
suffix:semicolon
multiline_comment|/* number of blocks in a file */
multiline_comment|/*&n; * Memory based types are conditional.&n; */
macro_line|#if XFS_BIG_FILESYSTEMS
DECL|typedef|xfs_fsblock_t
r_typedef
id|__uint64_t
id|xfs_fsblock_t
suffix:semicolon
multiline_comment|/* blockno in filesystem (agno|agbno) */
DECL|typedef|xfs_rfsblock_t
r_typedef
id|__uint64_t
id|xfs_rfsblock_t
suffix:semicolon
multiline_comment|/* blockno in filesystem (raw) */
DECL|typedef|xfs_rtblock_t
r_typedef
id|__uint64_t
id|xfs_rtblock_t
suffix:semicolon
multiline_comment|/* extent (block) in realtime area */
DECL|typedef|xfs_srtblock_t
r_typedef
id|__int64_t
id|xfs_srtblock_t
suffix:semicolon
multiline_comment|/* signed version of xfs_rtblock_t */
macro_line|#else
DECL|typedef|xfs_fsblock_t
r_typedef
id|__uint32_t
id|xfs_fsblock_t
suffix:semicolon
multiline_comment|/* blockno in filesystem (agno|agbno) */
DECL|typedef|xfs_rfsblock_t
r_typedef
id|__uint32_t
id|xfs_rfsblock_t
suffix:semicolon
multiline_comment|/* blockno in filesystem (raw) */
DECL|typedef|xfs_rtblock_t
r_typedef
id|__uint32_t
id|xfs_rtblock_t
suffix:semicolon
multiline_comment|/* extent (block) in realtime area */
DECL|typedef|xfs_srtblock_t
r_typedef
id|__int32_t
id|xfs_srtblock_t
suffix:semicolon
multiline_comment|/* signed version of xfs_rtblock_t */
macro_line|#endif
DECL|typedef|xfs_fileoff_t
r_typedef
id|__uint64_t
id|xfs_fileoff_t
suffix:semicolon
multiline_comment|/* block number in a file */
DECL|typedef|xfs_sfiloff_t
r_typedef
id|__int64_t
id|xfs_sfiloff_t
suffix:semicolon
multiline_comment|/* signed block number in a file */
DECL|typedef|xfs_filblks_t
r_typedef
id|__uint64_t
id|xfs_filblks_t
suffix:semicolon
multiline_comment|/* number of blocks in a file */
DECL|typedef|xfs_arch_t
r_typedef
id|__uint8_t
id|xfs_arch_t
suffix:semicolon
multiline_comment|/* architecutre of an xfs fs */
multiline_comment|/*&n; * Null values for the types.&n; */
DECL|macro|NULLDFSBNO
mdefine_line|#define NULLDFSBNO&t;((xfs_dfsbno_t)-1)
DECL|macro|NULLDRFSBNO
mdefine_line|#define NULLDRFSBNO&t;((xfs_drfsbno_t)-1)
DECL|macro|NULLDRTBNO
mdefine_line|#define NULLDRTBNO&t;((xfs_drtbno_t)-1)
DECL|macro|NULLDFILOFF
mdefine_line|#define NULLDFILOFF&t;((xfs_dfiloff_t)-1)
DECL|macro|NULLFSBLOCK
mdefine_line|#define NULLFSBLOCK&t;((xfs_fsblock_t)-1)
DECL|macro|NULLRFSBLOCK
mdefine_line|#define NULLRFSBLOCK&t;((xfs_rfsblock_t)-1)
DECL|macro|NULLRTBLOCK
mdefine_line|#define NULLRTBLOCK&t;((xfs_rtblock_t)-1)
DECL|macro|NULLFILEOFF
mdefine_line|#define NULLFILEOFF&t;((xfs_fileoff_t)-1)
DECL|macro|NULLAGBLOCK
mdefine_line|#define NULLAGBLOCK&t;((xfs_agblock_t)-1)
DECL|macro|NULLAGNUMBER
mdefine_line|#define NULLAGNUMBER&t;((xfs_agnumber_t)-1)
DECL|macro|NULLEXTNUM
mdefine_line|#define NULLEXTNUM&t;((xfs_extnum_t)-1)
DECL|macro|NULLCOMMITLSN
mdefine_line|#define NULLCOMMITLSN&t;((xfs_lsn_t)-1)
multiline_comment|/*&n; * Max values for extlen, extnum, aextnum.&n; */
DECL|macro|MAXEXTLEN
mdefine_line|#define MAXEXTLEN&t;((xfs_extlen_t)0x001fffff)&t;/* 21 bits */
DECL|macro|MAXEXTNUM
mdefine_line|#define MAXEXTNUM&t;((xfs_extnum_t)0x7fffffff)&t;/* signed int */
DECL|macro|MAXAEXTNUM
mdefine_line|#define MAXAEXTNUM&t;((xfs_aextnum_t)0x7fff)&t;&t;/* signed short */
multiline_comment|/*&n; * MAXNAMELEN is the length (including the terminating null) of&n; * the longest permissible file (component) name.&n; */
DECL|macro|MAXNAMELEN
mdefine_line|#define MAXNAMELEN&t;256
r_typedef
r_enum
(brace
DECL|enumerator|XFS_LOOKUP_EQi
DECL|enumerator|XFS_LOOKUP_LEi
DECL|enumerator|XFS_LOOKUP_GEi
id|XFS_LOOKUP_EQi
comma
id|XFS_LOOKUP_LEi
comma
id|XFS_LOOKUP_GEi
DECL|typedef|xfs_lookup_t
)brace
id|xfs_lookup_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|XFS_BTNUM_BNOi
DECL|enumerator|XFS_BTNUM_CNTi
DECL|enumerator|XFS_BTNUM_BMAPi
DECL|enumerator|XFS_BTNUM_INOi
id|XFS_BTNUM_BNOi
comma
id|XFS_BTNUM_CNTi
comma
id|XFS_BTNUM_BMAPi
comma
id|XFS_BTNUM_INOi
comma
DECL|enumerator|XFS_BTNUM_MAX
id|XFS_BTNUM_MAX
DECL|typedef|xfs_btnum_t
)brace
id|xfs_btnum_t
suffix:semicolon
macro_line|#if defined(CONFIG_PROC_FS) &amp;&amp; defined(__KERNEL__) &amp;&amp; !defined(XFS_STATS_OFF)
multiline_comment|/*&n; * XFS global statistics&n; */
DECL|struct|xfsstats
r_struct
id|xfsstats
(brace
DECL|macro|XFSSTAT_END_EXTENT_ALLOC
macro_line|# define XFSSTAT_END_EXTENT_ALLOC&t;4
DECL|member|xs_allocx
id|__uint32_t
id|xs_allocx
suffix:semicolon
DECL|member|xs_allocb
id|__uint32_t
id|xs_allocb
suffix:semicolon
DECL|member|xs_freex
id|__uint32_t
id|xs_freex
suffix:semicolon
DECL|member|xs_freeb
id|__uint32_t
id|xs_freeb
suffix:semicolon
DECL|macro|XFSSTAT_END_ALLOC_BTREE
macro_line|# define XFSSTAT_END_ALLOC_BTREE&t;(XFSSTAT_END_EXTENT_ALLOC+4)
DECL|member|xs_abt_lookup
id|__uint32_t
id|xs_abt_lookup
suffix:semicolon
DECL|member|xs_abt_compare
id|__uint32_t
id|xs_abt_compare
suffix:semicolon
DECL|member|xs_abt_insrec
id|__uint32_t
id|xs_abt_insrec
suffix:semicolon
DECL|member|xs_abt_delrec
id|__uint32_t
id|xs_abt_delrec
suffix:semicolon
DECL|macro|XFSSTAT_END_BLOCK_MAPPING
macro_line|# define XFSSTAT_END_BLOCK_MAPPING&t;(XFSSTAT_END_ALLOC_BTREE+7)
DECL|member|xs_blk_mapr
id|__uint32_t
id|xs_blk_mapr
suffix:semicolon
DECL|member|xs_blk_mapw
id|__uint32_t
id|xs_blk_mapw
suffix:semicolon
DECL|member|xs_blk_unmap
id|__uint32_t
id|xs_blk_unmap
suffix:semicolon
DECL|member|xs_add_exlist
id|__uint32_t
id|xs_add_exlist
suffix:semicolon
DECL|member|xs_del_exlist
id|__uint32_t
id|xs_del_exlist
suffix:semicolon
DECL|member|xs_look_exlist
id|__uint32_t
id|xs_look_exlist
suffix:semicolon
DECL|member|xs_cmp_exlist
id|__uint32_t
id|xs_cmp_exlist
suffix:semicolon
DECL|macro|XFSSTAT_END_BLOCK_MAP_BTREE
macro_line|# define XFSSTAT_END_BLOCK_MAP_BTREE&t;(XFSSTAT_END_BLOCK_MAPPING+4)
DECL|member|xs_bmbt_lookup
id|__uint32_t
id|xs_bmbt_lookup
suffix:semicolon
DECL|member|xs_bmbt_compare
id|__uint32_t
id|xs_bmbt_compare
suffix:semicolon
DECL|member|xs_bmbt_insrec
id|__uint32_t
id|xs_bmbt_insrec
suffix:semicolon
DECL|member|xs_bmbt_delrec
id|__uint32_t
id|xs_bmbt_delrec
suffix:semicolon
DECL|macro|XFSSTAT_END_DIRECTORY_OPS
macro_line|# define XFSSTAT_END_DIRECTORY_OPS&t;(XFSSTAT_END_BLOCK_MAP_BTREE+4)
DECL|member|xs_dir_lookup
id|__uint32_t
id|xs_dir_lookup
suffix:semicolon
DECL|member|xs_dir_create
id|__uint32_t
id|xs_dir_create
suffix:semicolon
DECL|member|xs_dir_remove
id|__uint32_t
id|xs_dir_remove
suffix:semicolon
DECL|member|xs_dir_getdents
id|__uint32_t
id|xs_dir_getdents
suffix:semicolon
DECL|macro|XFSSTAT_END_TRANSACTIONS
macro_line|# define XFSSTAT_END_TRANSACTIONS&t;(XFSSTAT_END_DIRECTORY_OPS+3)
DECL|member|xs_trans_sync
id|__uint32_t
id|xs_trans_sync
suffix:semicolon
DECL|member|xs_trans_async
id|__uint32_t
id|xs_trans_async
suffix:semicolon
DECL|member|xs_trans_empty
id|__uint32_t
id|xs_trans_empty
suffix:semicolon
DECL|macro|XFSSTAT_END_INODE_OPS
macro_line|# define XFSSTAT_END_INODE_OPS&t;&t;(XFSSTAT_END_TRANSACTIONS+7)
DECL|member|xs_ig_attempts
id|__uint32_t
id|xs_ig_attempts
suffix:semicolon
DECL|member|xs_ig_found
id|__uint32_t
id|xs_ig_found
suffix:semicolon
DECL|member|xs_ig_frecycle
id|__uint32_t
id|xs_ig_frecycle
suffix:semicolon
DECL|member|xs_ig_missed
id|__uint32_t
id|xs_ig_missed
suffix:semicolon
DECL|member|xs_ig_dup
id|__uint32_t
id|xs_ig_dup
suffix:semicolon
DECL|member|xs_ig_reclaims
id|__uint32_t
id|xs_ig_reclaims
suffix:semicolon
DECL|member|xs_ig_attrchg
id|__uint32_t
id|xs_ig_attrchg
suffix:semicolon
DECL|macro|XFSSTAT_END_LOG_OPS
macro_line|# define XFSSTAT_END_LOG_OPS&t;&t;(XFSSTAT_END_INODE_OPS+5)
DECL|member|xs_log_writes
id|__uint32_t
id|xs_log_writes
suffix:semicolon
DECL|member|xs_log_blocks
id|__uint32_t
id|xs_log_blocks
suffix:semicolon
DECL|member|xs_log_noiclogs
id|__uint32_t
id|xs_log_noiclogs
suffix:semicolon
DECL|member|xs_log_force
id|__uint32_t
id|xs_log_force
suffix:semicolon
DECL|member|xs_log_force_sleep
id|__uint32_t
id|xs_log_force_sleep
suffix:semicolon
DECL|macro|XFSSTAT_END_TAIL_PUSHING
macro_line|# define XFSSTAT_END_TAIL_PUSHING&t;(XFSSTAT_END_LOG_OPS+10)
DECL|member|xs_try_logspace
id|__uint32_t
id|xs_try_logspace
suffix:semicolon
DECL|member|xs_sleep_logspace
id|__uint32_t
id|xs_sleep_logspace
suffix:semicolon
DECL|member|xs_push_ail
id|__uint32_t
id|xs_push_ail
suffix:semicolon
DECL|member|xs_push_ail_success
id|__uint32_t
id|xs_push_ail_success
suffix:semicolon
DECL|member|xs_push_ail_pushbuf
id|__uint32_t
id|xs_push_ail_pushbuf
suffix:semicolon
DECL|member|xs_push_ail_pinned
id|__uint32_t
id|xs_push_ail_pinned
suffix:semicolon
DECL|member|xs_push_ail_locked
id|__uint32_t
id|xs_push_ail_locked
suffix:semicolon
DECL|member|xs_push_ail_flushing
id|__uint32_t
id|xs_push_ail_flushing
suffix:semicolon
DECL|member|xs_push_ail_restarts
id|__uint32_t
id|xs_push_ail_restarts
suffix:semicolon
DECL|member|xs_push_ail_flush
id|__uint32_t
id|xs_push_ail_flush
suffix:semicolon
DECL|macro|XFSSTAT_END_WRITE_CONVERT
macro_line|# define XFSSTAT_END_WRITE_CONVERT&t;(XFSSTAT_END_TAIL_PUSHING+2)
DECL|member|xs_xstrat_quick
id|__uint32_t
id|xs_xstrat_quick
suffix:semicolon
DECL|member|xs_xstrat_split
id|__uint32_t
id|xs_xstrat_split
suffix:semicolon
DECL|macro|XFSSTAT_END_READ_WRITE_OPS
macro_line|# define XFSSTAT_END_READ_WRITE_OPS&t;(XFSSTAT_END_WRITE_CONVERT+2)
DECL|member|xs_write_calls
id|__uint32_t
id|xs_write_calls
suffix:semicolon
DECL|member|xs_read_calls
id|__uint32_t
id|xs_read_calls
suffix:semicolon
DECL|macro|XFSSTAT_END_ATTRIBUTE_OPS
macro_line|# define XFSSTAT_END_ATTRIBUTE_OPS&t;(XFSSTAT_END_READ_WRITE_OPS+4)
DECL|member|xs_attr_get
id|__uint32_t
id|xs_attr_get
suffix:semicolon
DECL|member|xs_attr_set
id|__uint32_t
id|xs_attr_set
suffix:semicolon
DECL|member|xs_attr_remove
id|__uint32_t
id|xs_attr_remove
suffix:semicolon
DECL|member|xs_attr_list
id|__uint32_t
id|xs_attr_list
suffix:semicolon
DECL|macro|XFSSTAT_END_QUOTA_OPS
macro_line|# define XFSSTAT_END_QUOTA_OPS&t;&t;(XFSSTAT_END_ATTRIBUTE_OPS+8)
DECL|member|xs_qm_dqreclaims
id|__uint32_t
id|xs_qm_dqreclaims
suffix:semicolon
DECL|member|xs_qm_dqreclaim_misses
id|__uint32_t
id|xs_qm_dqreclaim_misses
suffix:semicolon
DECL|member|xs_qm_dquot_dups
id|__uint32_t
id|xs_qm_dquot_dups
suffix:semicolon
DECL|member|xs_qm_dqcachemisses
id|__uint32_t
id|xs_qm_dqcachemisses
suffix:semicolon
DECL|member|xs_qm_dqcachehits
id|__uint32_t
id|xs_qm_dqcachehits
suffix:semicolon
DECL|member|xs_qm_dqwants
id|__uint32_t
id|xs_qm_dqwants
suffix:semicolon
DECL|member|xs_qm_dqshake_reclaims
id|__uint32_t
id|xs_qm_dqshake_reclaims
suffix:semicolon
DECL|member|xs_qm_dqinact_reclaims
id|__uint32_t
id|xs_qm_dqinact_reclaims
suffix:semicolon
DECL|macro|XFSSTAT_END_INODE_CLUSTER
macro_line|# define XFSSTAT_END_INODE_CLUSTER&t;(XFSSTAT_END_QUOTA_OPS+3)
DECL|member|xs_iflush_count
id|__uint32_t
id|xs_iflush_count
suffix:semicolon
DECL|member|xs_icluster_flushcnt
id|__uint32_t
id|xs_icluster_flushcnt
suffix:semicolon
DECL|member|xs_icluster_flushinode
id|__uint32_t
id|xs_icluster_flushinode
suffix:semicolon
DECL|macro|XFSSTAT_END_VNODE_OPS
macro_line|# define XFSSTAT_END_VNODE_OPS&t;&t;(XFSSTAT_END_INODE_CLUSTER+8)
DECL|member|vn_active
id|__uint32_t
id|vn_active
suffix:semicolon
multiline_comment|/* # vnodes not on free lists */
DECL|member|vn_alloc
id|__uint32_t
id|vn_alloc
suffix:semicolon
multiline_comment|/* # times vn_alloc called */
DECL|member|vn_get
id|__uint32_t
id|vn_get
suffix:semicolon
multiline_comment|/* # times vn_get called */
DECL|member|vn_hold
id|__uint32_t
id|vn_hold
suffix:semicolon
multiline_comment|/* # times vn_hold called */
DECL|member|vn_rele
id|__uint32_t
id|vn_rele
suffix:semicolon
multiline_comment|/* # times vn_rele called */
DECL|member|vn_reclaim
id|__uint32_t
id|vn_reclaim
suffix:semicolon
multiline_comment|/* # times vn_reclaim called */
DECL|member|vn_remove
id|__uint32_t
id|vn_remove
suffix:semicolon
multiline_comment|/* # times vn_remove called */
DECL|member|vn_free
id|__uint32_t
id|vn_free
suffix:semicolon
multiline_comment|/* # times vn_free called */
multiline_comment|/* Extra precision counters */
DECL|member|xs_xstrat_bytes
id|__uint64_t
id|xs_xstrat_bytes
suffix:semicolon
DECL|member|xs_write_bytes
id|__uint64_t
id|xs_write_bytes
suffix:semicolon
DECL|member|xs_read_bytes
id|__uint64_t
id|xs_read_bytes
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|xfsstats
id|xfsstats
suffix:semicolon
DECL|macro|XFS_STATS_INC
macro_line|# define XFS_STATS_INC(count)&t;&t;( (count)++ )
DECL|macro|XFS_STATS_DEC
macro_line|# define XFS_STATS_DEC(count)&t;&t;( (count)-- )
DECL|macro|XFS_STATS_ADD
macro_line|# define XFS_STATS_ADD(count, inc)&t;( (count) += (inc) )
macro_line|#else&t;/* !CONFIG_PROC_FS */
DECL|macro|XFS_STATS_INC
macro_line|# define XFS_STATS_INC(count)
DECL|macro|XFS_STATS_DEC
macro_line|# define XFS_STATS_DEC(count)
DECL|macro|XFS_STATS_ADD
macro_line|# define XFS_STATS_ADD(count, inc)
macro_line|#endif&t;/* !CONFIG_PROC_FS */
multiline_comment|/* juggle IRIX device numbers - still used in ondisk structures */
macro_line|#ifndef __KERNEL__
DECL|macro|MKDEV
mdefine_line|#define MKDEV(major, minor)&t;makedev(major, minor)
macro_line|#endif
DECL|macro|IRIX_DEV_BITSMAJOR
mdefine_line|#define IRIX_DEV_BITSMAJOR&t;14
DECL|macro|IRIX_DEV_BITSMINOR
mdefine_line|#define IRIX_DEV_BITSMINOR&t;18
DECL|macro|IRIX_DEV_MAXMAJ
mdefine_line|#define IRIX_DEV_MAXMAJ&t;&t;0x1ff
DECL|macro|IRIX_DEV_MAXMIN
mdefine_line|#define IRIX_DEV_MAXMIN&t;&t;0x3ffff
DECL|macro|IRIX_DEV_MAJOR
mdefine_line|#define IRIX_DEV_MAJOR(dev)&t;((int)(((unsigned)(dev)&gt;&gt;IRIX_DEV_BITSMINOR) &bslash;&n;&t;&t;&t;&t;    &amp; IRIX_DEV_MAXMAJ))
DECL|macro|IRIX_DEV_MINOR
mdefine_line|#define IRIX_DEV_MINOR(dev)&t;((int)((dev)&amp;IRIX_DEV_MAXMIN))
DECL|macro|IRIX_MKDEV
mdefine_line|#define IRIX_MKDEV(major,minor) ((xfs_dev_t)(((major)&lt;&lt;IRIX_DEV_BITSMINOR) &bslash;&n;&t;&t;&t;&t;    | (minor&amp;IRIX_DEV_MAXMIN)))
DECL|macro|IRIX_DEV_TO_KDEVT
mdefine_line|#define IRIX_DEV_TO_KDEVT(dev)&t;MKDEV(IRIX_DEV_MAJOR(dev),IRIX_DEV_MINOR(dev))
macro_line|#endif&t;/* !__XFS_TYPES_H */
eof
