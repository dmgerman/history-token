multiline_comment|/*&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#include &lt;xfs.h&gt;
DECL|variable|vn_generation
r_uint64
id|vn_generation
suffix:semicolon
multiline_comment|/* vnode generation number */
DECL|variable|vnumber_lock
id|spinlock_t
id|vnumber_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; * Dedicated vnode inactive/reclaim sync semaphores.&n; * Prime number of hash buckets since address is used as the key.&n; */
DECL|macro|NVSYNC
mdefine_line|#define NVSYNC&t;&t;&t;37
DECL|macro|vptosync
mdefine_line|#define vptosync(v)&t;&t;(&amp;vsync[((unsigned long)v) % NVSYNC])
DECL|variable|vsync
id|sv_t
id|vsync
(braket
id|NVSYNC
)braket
suffix:semicolon
multiline_comment|/*&n; * Translate stat(2) file types to vnode types and vice versa.&n; * Aware of numeric order of S_IFMT and vnode type values.&n; */
DECL|variable|iftovt_tab
r_enum
id|vtype
id|iftovt_tab
(braket
)braket
op_assign
(brace
id|VNON
comma
id|VFIFO
comma
id|VCHR
comma
id|VNON
comma
id|VDIR
comma
id|VNON
comma
id|VBLK
comma
id|VNON
comma
id|VREG
comma
id|VNON
comma
id|VLNK
comma
id|VNON
comma
id|VSOCK
comma
id|VNON
comma
id|VNON
comma
id|VNON
)brace
suffix:semicolon
DECL|variable|vttoif_tab
id|u_short
id|vttoif_tab
(braket
)braket
op_assign
(brace
l_int|0
comma
id|S_IFREG
comma
id|S_IFDIR
comma
id|S_IFBLK
comma
id|S_IFCHR
comma
id|S_IFLNK
comma
id|S_IFIFO
comma
l_int|0
comma
id|S_IFSOCK
)brace
suffix:semicolon
r_void
DECL|function|vn_init
id|vn_init
c_func
(paren
r_void
)paren
(brace
r_register
id|sv_t
op_star
id|svp
suffix:semicolon
r_register
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|svp
op_assign
id|vsync
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NVSYNC
suffix:semicolon
id|i
op_increment
comma
id|svp
op_increment
)paren
id|init_sv
c_func
(paren
id|svp
comma
id|SV_DEFAULT
comma
l_string|&quot;vsy&quot;
comma
id|i
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Clean a vnode of filesystem-specific data and prepare it for reuse.&n; */
id|STATIC
r_int
DECL|function|vn_reclaim
id|vn_reclaim
c_func
(paren
r_struct
id|vnode
op_star
id|vp
)paren
(brace
r_int
id|error
suffix:semicolon
id|XFS_STATS_INC
c_func
(paren
id|xfsstats.vn_reclaim
)paren
suffix:semicolon
id|vn_trace_entry
c_func
(paren
id|vp
comma
l_string|&quot;vn_reclaim&quot;
comma
(paren
id|inst_t
op_star
)paren
id|__return_address
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Only make the VOP_RECLAIM call if there are behaviors&n;&t; * to call.&n;&t; */
r_if
c_cond
(paren
id|vp-&gt;v_fbhv
)paren
(brace
id|VOP_RECLAIM
c_func
(paren
id|vp
comma
id|error
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
op_minus
id|error
suffix:semicolon
)brace
id|ASSERT
c_func
(paren
id|vp-&gt;v_fbhv
op_eq
l_int|NULL
)paren
suffix:semicolon
id|VN_LOCK
c_func
(paren
id|vp
)paren
suffix:semicolon
id|vp-&gt;v_flag
op_and_assign
(paren
id|VRECLM
op_or
id|VWAIT
)paren
suffix:semicolon
id|VN_UNLOCK
c_func
(paren
id|vp
comma
l_int|0
)paren
suffix:semicolon
id|vp-&gt;v_type
op_assign
id|VNON
suffix:semicolon
id|vp-&gt;v_fbhv
op_assign
l_int|NULL
suffix:semicolon
macro_line|#ifdef CONFIG_XFS_VNODE_TRACING
id|ktrace_free
c_func
(paren
id|vp-&gt;v_trace
)paren
suffix:semicolon
id|vp-&gt;v_trace
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
id|STATIC
r_void
DECL|function|vn_wakeup
id|vn_wakeup
c_func
(paren
r_struct
id|vnode
op_star
id|vp
)paren
(brace
id|VN_LOCK
c_func
(paren
id|vp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vp-&gt;v_flag
op_amp
id|VWAIT
)paren
id|sv_broadcast
c_func
(paren
id|vptosync
c_func
(paren
id|vp
)paren
)paren
suffix:semicolon
id|vp-&gt;v_flag
op_and_assign
op_complement
(paren
id|VRECLM
op_or
id|VWAIT
op_or
id|VMODIFIED
)paren
suffix:semicolon
id|VN_UNLOCK
c_func
(paren
id|vp
comma
l_int|0
)paren
suffix:semicolon
)brace
r_int
DECL|function|vn_wait
id|vn_wait
c_func
(paren
r_struct
id|vnode
op_star
id|vp
)paren
(brace
id|VN_LOCK
c_func
(paren
id|vp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vp-&gt;v_flag
op_amp
(paren
id|VINACT
op_or
id|VRECLM
)paren
)paren
(brace
id|vp-&gt;v_flag
op_or_assign
id|VWAIT
suffix:semicolon
id|sv_wait
c_func
(paren
id|vptosync
c_func
(paren
id|vp
)paren
comma
id|PINOD
comma
op_amp
id|vp-&gt;v_lock
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|VN_UNLOCK
c_func
(paren
id|vp
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_struct
id|vnode
op_star
DECL|function|vn_initialize
id|vn_initialize
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|vnode
op_star
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|inode
)paren
suffix:semicolon
id|XFS_STATS_INC
c_func
(paren
id|xfsstats.vn_active
)paren
suffix:semicolon
id|XFS_STATS_INC
c_func
(paren
id|xfsstats.vn_alloc
)paren
suffix:semicolon
id|vp-&gt;v_flag
op_assign
id|VMODIFIED
suffix:semicolon
id|spinlock_init
c_func
(paren
op_amp
id|vp-&gt;v_lock
comma
l_string|&quot;v_lock&quot;
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|vnumber_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_increment
id|vn_generation
)paren
multiline_comment|/* v_number shouldn&squot;t be zero */
id|vn_generation
op_increment
suffix:semicolon
id|vp-&gt;v_number
op_assign
id|vn_generation
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|vnumber_lock
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|VN_CACHED
c_func
(paren
id|vp
)paren
op_eq
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Initialize the first behavior and the behavior chain head. */
id|vn_bhv_head_init
c_func
(paren
id|VN_BHV_HEAD
c_func
(paren
id|vp
)paren
comma
l_string|&quot;vnode&quot;
)paren
suffix:semicolon
macro_line|#ifdef&t;CONFIG_XFS_VNODE_TRACING
id|vp-&gt;v_trace
op_assign
id|ktrace_alloc
c_func
(paren
id|VNODE_TRACE_SIZE
comma
id|KM_SLEEP
)paren
suffix:semicolon
macro_line|#endif&t;/* CONFIG_XFS_VNODE_TRACING */
id|vn_trace_exit
c_func
(paren
id|vp
comma
l_string|&quot;vn_initialize&quot;
comma
(paren
id|inst_t
op_star
)paren
id|__return_address
)paren
suffix:semicolon
r_return
id|vp
suffix:semicolon
)brace
multiline_comment|/*&n; * Get a reference on a vnode.&n; */
id|vnode_t
op_star
DECL|function|vn_get
id|vn_get
c_func
(paren
r_struct
id|vnode
op_star
id|vp
comma
id|vmap_t
op_star
id|vmap
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|XFS_STATS_INC
c_func
(paren
id|xfsstats.vn_get
)paren
suffix:semicolon
id|inode
op_assign
id|LINVFS_GET_IP
c_func
(paren
id|vp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_state
op_amp
id|I_FREEING
)paren
r_return
l_int|NULL
suffix:semicolon
id|inode
op_assign
id|ilookup
c_func
(paren
id|vmap-&gt;v_vfsp-&gt;vfs_super
comma
id|vmap-&gt;v_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
multiline_comment|/* Inode not present */
r_return
l_int|NULL
suffix:semicolon
id|vn_trace_exit
c_func
(paren
id|vp
comma
l_string|&quot;vn_get&quot;
comma
(paren
id|inst_t
op_star
)paren
id|__return_address
)paren
suffix:semicolon
r_return
id|vp
suffix:semicolon
)brace
multiline_comment|/*&n; * Revalidate the Linux inode from the vnode.&n; */
r_int
DECL|function|vn_revalidate
id|vn_revalidate
c_func
(paren
r_struct
id|vnode
op_star
id|vp
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|vattr_t
id|va
suffix:semicolon
r_int
id|error
suffix:semicolon
id|vn_trace_entry
c_func
(paren
id|vp
comma
l_string|&quot;vn_revalidate&quot;
comma
(paren
id|inst_t
op_star
)paren
id|__return_address
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|vp-&gt;v_fbhv
op_ne
l_int|NULL
)paren
suffix:semicolon
id|va.va_mask
op_assign
id|XFS_AT_STAT
op_or
id|XFS_AT_GENCOUNT
suffix:semicolon
id|VOP_GETATTR
c_func
(paren
id|vp
comma
op_amp
id|va
comma
l_int|0
comma
l_int|NULL
comma
id|error
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|inode
op_assign
id|LINVFS_GET_IP
c_func
(paren
id|vp
)paren
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|VTTOIF
c_func
(paren
id|va.va_type
)paren
op_or
id|va.va_mode
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
id|va.va_nlink
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|va.va_uid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|va.va_gid
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|va.va_size
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
id|va.va_nblocks
suffix:semicolon
id|inode-&gt;i_mtime.tv_sec
op_assign
id|va.va_mtime.tv_sec
suffix:semicolon
id|inode-&gt;i_mtime.tv_nsec
op_assign
id|va.va_mtime.tv_nsec
suffix:semicolon
id|inode-&gt;i_ctime.tv_sec
op_assign
id|va.va_ctime.tv_sec
suffix:semicolon
id|inode-&gt;i_ctime.tv_nsec
op_assign
id|va.va_ctime.tv_nsec
suffix:semicolon
id|inode-&gt;i_atime.tv_sec
op_assign
id|va.va_atime.tv_sec
suffix:semicolon
id|inode-&gt;i_atime.tv_nsec
op_assign
id|va.va_atime.tv_nsec
suffix:semicolon
id|VUNMODIFY
c_func
(paren
id|vp
)paren
suffix:semicolon
)brace
r_return
op_minus
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * purge a vnode from the cache&n; * At this point the vnode is guaranteed to have no references (vn_count == 0)&n; * The caller has to make sure that there are no ways someone could&n; * get a handle (via vn_get) on the vnode (usually done via a mount/vfs lock).&n; */
r_void
DECL|function|vn_purge
id|vn_purge
c_func
(paren
r_struct
id|vnode
op_star
id|vp
comma
id|vmap_t
op_star
id|vmap
)paren
(brace
id|vn_trace_entry
c_func
(paren
id|vp
comma
l_string|&quot;vn_purge&quot;
comma
(paren
id|inst_t
op_star
)paren
id|__return_address
)paren
suffix:semicolon
id|again
suffix:colon
multiline_comment|/*&n;&t; * Check whether vp has already been reclaimed since our caller&n;&t; * sampled its version while holding a filesystem cache lock that&n;&t; * its VOP_RECLAIM function acquires.&n;&t; */
id|VN_LOCK
c_func
(paren
id|vp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vp-&gt;v_number
op_ne
id|vmap-&gt;v_number
)paren
(brace
id|VN_UNLOCK
c_func
(paren
id|vp
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If vp is being reclaimed or inactivated, wait until it is inert,&n;&t; * then proceed.  Can&squot;t assume that vnode is actually reclaimed&n;&t; * just because the reclaimed flag is asserted -- a vn_alloc&n;&t; * reclaim can fail.&n;&t; */
r_if
c_cond
(paren
id|vp-&gt;v_flag
op_amp
(paren
id|VINACT
op_or
id|VRECLM
)paren
)paren
(brace
id|ASSERT
c_func
(paren
id|vn_count
c_func
(paren
id|vp
)paren
op_eq
l_int|0
)paren
suffix:semicolon
id|vp-&gt;v_flag
op_or_assign
id|VWAIT
suffix:semicolon
id|sv_wait
c_func
(paren
id|vptosync
c_func
(paren
id|vp
)paren
comma
id|PINOD
comma
op_amp
id|vp-&gt;v_lock
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|again
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Another process could have raced in and gotten this vnode...&n;&t; */
r_if
c_cond
(paren
id|vn_count
c_func
(paren
id|vp
)paren
OG
l_int|0
)paren
(brace
id|VN_UNLOCK
c_func
(paren
id|vp
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|XFS_STATS_DEC
c_func
(paren
id|xfsstats.vn_active
)paren
suffix:semicolon
id|vp-&gt;v_flag
op_or_assign
id|VRECLM
suffix:semicolon
id|VN_UNLOCK
c_func
(paren
id|vp
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Call VOP_RECLAIM and clean vp. The FSYNC_INVAL flag tells&n;&t; * vp&squot;s filesystem to flush and invalidate all cached resources.&n;&t; * When vn_reclaim returns, vp should have no private data,&n;&t; * either in a system cache or attached to v_data.&n;&t; */
r_if
c_cond
(paren
id|vn_reclaim
c_func
(paren
id|vp
)paren
op_ne
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;vn_purge: cannot reclaim&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Wakeup anyone waiting for vp to be reclaimed.&n;&t; */
id|vn_wakeup
c_func
(paren
id|vp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Add a reference to a referenced vnode.&n; */
r_struct
id|vnode
op_star
DECL|function|vn_hold
id|vn_hold
c_func
(paren
r_struct
id|vnode
op_star
id|vp
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|XFS_STATS_INC
c_func
(paren
id|xfsstats.vn_hold
)paren
suffix:semicolon
id|VN_LOCK
c_func
(paren
id|vp
)paren
suffix:semicolon
id|inode
op_assign
id|igrab
c_func
(paren
id|LINVFS_GET_IP
c_func
(paren
id|vp
)paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|inode
)paren
suffix:semicolon
id|VN_UNLOCK
c_func
(paren
id|vp
comma
l_int|0
)paren
suffix:semicolon
r_return
id|vp
suffix:semicolon
)brace
multiline_comment|/*&n; *  Call VOP_INACTIVE on last reference.&n; */
r_void
DECL|function|vn_rele
id|vn_rele
c_func
(paren
r_struct
id|vnode
op_star
id|vp
)paren
(brace
r_int
id|vcnt
suffix:semicolon
r_int
id|cache
suffix:semicolon
id|XFS_STATS_INC
c_func
(paren
id|xfsstats.vn_rele
)paren
suffix:semicolon
id|VN_LOCK
c_func
(paren
id|vp
)paren
suffix:semicolon
id|vn_trace_entry
c_func
(paren
id|vp
comma
l_string|&quot;vn_rele&quot;
comma
(paren
id|inst_t
op_star
)paren
id|__return_address
)paren
suffix:semicolon
id|vcnt
op_assign
id|vn_count
c_func
(paren
id|vp
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Since we always get called from put_inode we know&n;&t; * that i_count won&squot;t be decremented after we&n;&t; * return.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|vcnt
)paren
(brace
multiline_comment|/*&n;&t;&t; * As soon as we turn this on, noone can find us in vn_get&n;&t;&t; * until we turn off VINACT or VRECLM&n;&t;&t; */
id|vp-&gt;v_flag
op_or_assign
id|VINACT
suffix:semicolon
id|VN_UNLOCK
c_func
(paren
id|vp
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Do not make the VOP_INACTIVE call if there&n;&t;&t; * are no behaviors attached to the vnode to call.&n;&t;&t; */
r_if
c_cond
(paren
id|vp-&gt;v_fbhv
)paren
id|VOP_INACTIVE
c_func
(paren
id|vp
comma
l_int|NULL
comma
id|cache
)paren
suffix:semicolon
id|VN_LOCK
c_func
(paren
id|vp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vp-&gt;v_flag
op_amp
id|VWAIT
)paren
id|sv_broadcast
c_func
(paren
id|vptosync
c_func
(paren
id|vp
)paren
)paren
suffix:semicolon
id|vp-&gt;v_flag
op_and_assign
op_complement
(paren
id|VINACT
op_or
id|VWAIT
op_or
id|VRECLM
op_or
id|VMODIFIED
)paren
suffix:semicolon
)brace
id|VN_UNLOCK
c_func
(paren
id|vp
comma
l_int|0
)paren
suffix:semicolon
id|vn_trace_exit
c_func
(paren
id|vp
comma
l_string|&quot;vn_rele&quot;
comma
(paren
id|inst_t
op_star
)paren
id|__return_address
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Finish the removal of a vnode.&n; */
r_void
DECL|function|vn_remove
id|vn_remove
c_func
(paren
r_struct
id|vnode
op_star
id|vp
)paren
(brace
id|vmap_t
id|vmap
suffix:semicolon
multiline_comment|/* Make sure we don&squot;t do this to the same vnode twice */
r_if
c_cond
(paren
op_logical_neg
(paren
id|vp-&gt;v_fbhv
)paren
)paren
r_return
suffix:semicolon
id|XFS_STATS_INC
c_func
(paren
id|xfsstats.vn_remove
)paren
suffix:semicolon
id|vn_trace_exit
c_func
(paren
id|vp
comma
l_string|&quot;vn_remove&quot;
comma
(paren
id|inst_t
op_star
)paren
id|__return_address
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * After the following purge the vnode&n;&t; * will no longer exist.&n;&t; */
id|VMAP
c_func
(paren
id|vp
comma
id|vmap
)paren
suffix:semicolon
id|vn_purge
c_func
(paren
id|vp
comma
op_amp
id|vmap
)paren
suffix:semicolon
)brace
macro_line|#ifdef&t;CONFIG_XFS_VNODE_TRACING
DECL|macro|KTRACE_ENTER
mdefine_line|#define KTRACE_ENTER(vp, vk, s, line, ra)&t;&t;&t;&bslash;&n;&t;ktrace_enter(&t;(vp)-&gt;v_trace,&t;&t;&t;&t;&bslash;&n;/*  0 */&t;&t;(void *)(__psint_t)(vk),&t;&t;&bslash;&n;/*  1 */&t;&t;(void *)(s),&t;&t;&t;&t;&bslash;&n;/*  2 */&t;&t;(void *)(__psint_t) line,&t;&t;&bslash;&n;/*  3 */&t;&t;(void *)(vn_count(vp)), &bslash;&n;/*  4 */&t;&t;(void *)(ra),&t;&t;&t;&t;&bslash;&n;/*  5 */&t;&t;(void *)(__psunsigned_t)(vp)-&gt;v_flag,&t;&bslash;&n;/*  6 */&t;&t;(void *)(__psint_t)smp_processor_id(),&t;&bslash;&n;/*  7 */&t;&t;(void *)(__psint_t)(current-&gt;pid),&t;&bslash;&n;/*  8 */&t;&t;(void *)__return_address,&t;&t;&bslash;&n;/*  9 */&t;&t;0, 0, 0, 0, 0, 0, 0)
multiline_comment|/*&n; * Vnode tracing code.&n; */
r_void
DECL|function|vn_trace_entry
id|vn_trace_entry
c_func
(paren
id|vnode_t
op_star
id|vp
comma
r_char
op_star
id|func
comma
id|inst_t
op_star
id|ra
)paren
(brace
id|KTRACE_ENTER
c_func
(paren
id|vp
comma
id|VNODE_KTRACE_ENTRY
comma
id|func
comma
l_int|0
comma
id|ra
)paren
suffix:semicolon
)brace
r_void
DECL|function|vn_trace_exit
id|vn_trace_exit
c_func
(paren
id|vnode_t
op_star
id|vp
comma
r_char
op_star
id|func
comma
id|inst_t
op_star
id|ra
)paren
(brace
id|KTRACE_ENTER
c_func
(paren
id|vp
comma
id|VNODE_KTRACE_EXIT
comma
id|func
comma
l_int|0
comma
id|ra
)paren
suffix:semicolon
)brace
r_void
DECL|function|vn_trace_hold
id|vn_trace_hold
c_func
(paren
id|vnode_t
op_star
id|vp
comma
r_char
op_star
id|file
comma
r_int
id|line
comma
id|inst_t
op_star
id|ra
)paren
(brace
id|KTRACE_ENTER
c_func
(paren
id|vp
comma
id|VNODE_KTRACE_HOLD
comma
id|file
comma
id|line
comma
id|ra
)paren
suffix:semicolon
)brace
r_void
DECL|function|vn_trace_ref
id|vn_trace_ref
c_func
(paren
id|vnode_t
op_star
id|vp
comma
r_char
op_star
id|file
comma
r_int
id|line
comma
id|inst_t
op_star
id|ra
)paren
(brace
id|KTRACE_ENTER
c_func
(paren
id|vp
comma
id|VNODE_KTRACE_REF
comma
id|file
comma
id|line
comma
id|ra
)paren
suffix:semicolon
)brace
r_void
DECL|function|vn_trace_rele
id|vn_trace_rele
c_func
(paren
id|vnode_t
op_star
id|vp
comma
r_char
op_star
id|file
comma
r_int
id|line
comma
id|inst_t
op_star
id|ra
)paren
(brace
id|KTRACE_ENTER
c_func
(paren
id|vp
comma
id|VNODE_KTRACE_RELE
comma
id|file
comma
id|line
comma
id|ra
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* CONFIG_XFS_VNODE_TRACING */
eof
