multiline_comment|/*&n; * Copyright (c) 2000 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_STATS_H__
DECL|macro|__XFS_STATS_H__
mdefine_line|#define __XFS_STATS_H__
macro_line|#if defined(CONFIG_PROC_FS) &amp;&amp; !defined(XFS_STATS_OFF)
macro_line|#include &lt;linux/percpu.h&gt;
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
DECL|macro|XFSSTAT_END_INODE_CLUSTER
macro_line|# define XFSSTAT_END_INODE_CLUSTER&t;(XFSSTAT_END_ATTRIBUTE_OPS+3)
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
id|DECLARE_PER_CPU
c_func
(paren
r_struct
id|xfsstats
comma
id|xfsstats
)paren
suffix:semicolon
multiline_comment|/* We don&squot;t disable preempt, not too worried about poking the&n; * wrong cpu&squot;s stat for now */
DECL|macro|XFS_STATS_INC
mdefine_line|#define XFS_STATS_INC(count)&t;&t;(__get_cpu_var(xfsstats).count++)
DECL|macro|XFS_STATS_DEC
mdefine_line|#define XFS_STATS_DEC(count)&t;&t;(__get_cpu_var(xfsstats).count--)
DECL|macro|XFS_STATS_ADD
mdefine_line|#define XFS_STATS_ADD(count, inc)&t;(__get_cpu_var(xfsstats).count += (inc))
r_extern
r_void
id|xfs_init_procfs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|xfs_cleanup_procfs
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else&t;/* !CONFIG_PROC_FS */
DECL|macro|XFS_STATS_INC
macro_line|# define XFS_STATS_INC(count)
DECL|macro|XFS_STATS_DEC
macro_line|# define XFS_STATS_DEC(count)
DECL|macro|XFS_STATS_ADD
macro_line|# define XFS_STATS_ADD(count, inc)
DECL|function|xfs_init_procfs
r_static
id|__inline
r_void
id|xfs_init_procfs
c_func
(paren
r_void
)paren
(brace
)brace
suffix:semicolon
DECL|function|xfs_cleanup_procfs
r_static
id|__inline
r_void
id|xfs_cleanup_procfs
c_func
(paren
r_void
)paren
(brace
)brace
suffix:semicolon
macro_line|#endif&t;/* !CONFIG_PROC_FS */
macro_line|#endif /* __XFS_STATS_H__ */
eof
