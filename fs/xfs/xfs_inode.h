multiline_comment|/*&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef&t;__XFS_INODE_H__
DECL|macro|__XFS_INODE_H__
mdefine_line|#define&t;__XFS_INODE_H__
multiline_comment|/*&n; * File incore extent information, present for each of data &amp; attr forks.&n; */
DECL|macro|XFS_INLINE_EXTS
mdefine_line|#define&t;XFS_INLINE_EXTS&t;2
DECL|macro|XFS_INLINE_DATA
mdefine_line|#define&t;XFS_INLINE_DATA&t;32
DECL|struct|xfs_ifork
r_typedef
r_struct
id|xfs_ifork
(brace
DECL|member|if_bytes
r_int
id|if_bytes
suffix:semicolon
multiline_comment|/* bytes in if_u1 */
DECL|member|if_real_bytes
r_int
id|if_real_bytes
suffix:semicolon
multiline_comment|/* bytes allocated in if_u1 */
DECL|member|if_broot
id|xfs_bmbt_block_t
op_star
id|if_broot
suffix:semicolon
multiline_comment|/* file&squot;s incore btree root */
DECL|member|if_broot_bytes
r_int
id|if_broot_bytes
suffix:semicolon
multiline_comment|/* bytes allocated for root */
DECL|member|if_flags
r_int
r_char
id|if_flags
suffix:semicolon
multiline_comment|/* per-fork flags */
DECL|member|if_ext_max
r_int
r_char
id|if_ext_max
suffix:semicolon
multiline_comment|/* max # of extent records */
DECL|member|if_lastex
id|xfs_extnum_t
id|if_lastex
suffix:semicolon
multiline_comment|/* last if_extents used */
r_union
(brace
DECL|member|if_extents
id|xfs_bmbt_rec_t
op_star
id|if_extents
suffix:semicolon
multiline_comment|/* linear map file exts */
DECL|member|if_data
r_char
op_star
id|if_data
suffix:semicolon
multiline_comment|/* inline file data */
DECL|member|if_u1
)brace
id|if_u1
suffix:semicolon
r_union
(brace
DECL|member|if_inline_ext
id|xfs_bmbt_rec_t
id|if_inline_ext
(braket
id|XFS_INLINE_EXTS
)braket
suffix:semicolon
multiline_comment|/* very small file extents */
DECL|member|if_inline_data
r_char
id|if_inline_data
(braket
id|XFS_INLINE_DATA
)braket
suffix:semicolon
multiline_comment|/* very small file data */
DECL|member|if_rdev
id|xfs_dev_t
id|if_rdev
suffix:semicolon
multiline_comment|/* dev number if special */
DECL|member|if_uuid
id|uuid_t
id|if_uuid
suffix:semicolon
multiline_comment|/* mount point value */
DECL|member|if_u2
)brace
id|if_u2
suffix:semicolon
DECL|typedef|xfs_ifork_t
)brace
id|xfs_ifork_t
suffix:semicolon
multiline_comment|/*&n; * Flags for xfs_ichgtime().&n; */
DECL|macro|XFS_ICHGTIME_MOD
mdefine_line|#define&t;XFS_ICHGTIME_MOD&t;0x1&t;/* data fork modification timestamp */
DECL|macro|XFS_ICHGTIME_ACC
mdefine_line|#define&t;XFS_ICHGTIME_ACC&t;0x2&t;/* data fork access timestamp */
DECL|macro|XFS_ICHGTIME_CHG
mdefine_line|#define&t;XFS_ICHGTIME_CHG&t;0x4&t;/* inode field change timestamp */
multiline_comment|/*&n; * Per-fork incore inode flags.&n; */
DECL|macro|XFS_IFINLINE
mdefine_line|#define&t;XFS_IFINLINE&t;0x0001&t;/* Inline data is read in */
DECL|macro|XFS_IFEXTENTS
mdefine_line|#define&t;XFS_IFEXTENTS&t;0x0002&t;/* All extent pointers are read in */
DECL|macro|XFS_IFBROOT
mdefine_line|#define&t;XFS_IFBROOT&t;0x0004&t;/* i_broot points to the bmap b-tree root */
multiline_comment|/*&n; * Flags for xfs_imap() and xfs_dilocate().&n; */
DECL|macro|XFS_IMAP_LOOKUP
mdefine_line|#define&t;XFS_IMAP_LOOKUP&t;&t;0x1
multiline_comment|/*&n; * Maximum number of extent pointers in if_u1.if_extents.&n; */
DECL|macro|XFS_MAX_INCORE_EXTENTS
mdefine_line|#define&t;XFS_MAX_INCORE_EXTENTS&t;32768
macro_line|#ifdef __KERNEL__
r_struct
id|bhv_desc
suffix:semicolon
r_struct
id|cred
suffix:semicolon
r_struct
id|ktrace
suffix:semicolon
r_struct
id|vnode
suffix:semicolon
r_struct
id|xfs_buf
suffix:semicolon
r_struct
id|xfs_bmap_free
suffix:semicolon
r_struct
id|xfs_bmbt_irec
suffix:semicolon
r_struct
id|xfs_bmbt_block
suffix:semicolon
r_struct
id|xfs_inode
suffix:semicolon
r_struct
id|xfs_inode_log_item
suffix:semicolon
r_struct
id|xfs_mount
suffix:semicolon
r_struct
id|xfs_trans
suffix:semicolon
r_struct
id|xfs_dquot
suffix:semicolon
macro_line|#if defined(XFS_ILOCK_TRACE)
DECL|macro|XFS_ILOCK_KTRACE_SIZE
mdefine_line|#define XFS_ILOCK_KTRACE_SIZE&t;32
r_extern
id|ktrace_t
op_star
id|xfs_ilock_trace_buf
suffix:semicolon
r_extern
r_void
id|xfs_ilock_trace
c_func
(paren
r_struct
id|xfs_inode
op_star
comma
r_int
comma
r_int
r_int
comma
id|inst_t
op_star
)paren
suffix:semicolon
macro_line|#else
DECL|macro|xfs_ilock_trace
mdefine_line|#define&t;xfs_ilock_trace(i,n,f,ra)
macro_line|#endif
multiline_comment|/*&n; * This structure is used to communicate which extents of a file&n; * were holes when a write started from xfs_write_file() to&n; * xfs_strat_read().  This is necessary so that we can know which&n; * blocks need to be zeroed when they are read in in xfs_strat_read()&n; * if they weren&bslash;&squot;t allocated when the buffer given to xfs_strat_read()&n; * was mapped.&n; *&n; * We keep a list of these attached to the inode.  The list is&n; * protected by the inode lock and the fact that the io lock is&n; * held exclusively by writers.&n; */
DECL|struct|xfs_gap
r_typedef
r_struct
id|xfs_gap
(brace
DECL|member|xg_next
r_struct
id|xfs_gap
op_star
id|xg_next
suffix:semicolon
DECL|member|xg_offset_fsb
id|xfs_fileoff_t
id|xg_offset_fsb
suffix:semicolon
DECL|member|xg_count_fsb
id|xfs_extlen_t
id|xg_count_fsb
suffix:semicolon
DECL|typedef|xfs_gap_t
)brace
id|xfs_gap_t
suffix:semicolon
DECL|struct|dm_attrs_s
r_typedef
r_struct
id|dm_attrs_s
(brace
DECL|member|da_dmevmask
id|__uint32_t
id|da_dmevmask
suffix:semicolon
multiline_comment|/* DMIG event mask */
DECL|member|da_dmstate
id|__uint16_t
id|da_dmstate
suffix:semicolon
multiline_comment|/* DMIG state info */
DECL|member|da_pad
id|__uint16_t
id|da_pad
suffix:semicolon
multiline_comment|/* DMIG extra padding */
DECL|typedef|dm_attrs_t
)brace
id|dm_attrs_t
suffix:semicolon
DECL|struct|xfs_iocore
r_typedef
r_struct
id|xfs_iocore
(brace
DECL|member|io_obj
r_void
op_star
id|io_obj
suffix:semicolon
multiline_comment|/* pointer to container&n;&t;&t;&t;&t;&t;&t; * inode or dcxvn structure */
DECL|member|io_mount
r_struct
id|xfs_mount
op_star
id|io_mount
suffix:semicolon
multiline_comment|/* fs mount struct ptr */
macro_line|#ifdef DEBUG
DECL|member|io_lock
id|mrlock_t
op_star
id|io_lock
suffix:semicolon
multiline_comment|/* inode IO lock */
DECL|member|io_iolock
id|mrlock_t
op_star
id|io_iolock
suffix:semicolon
multiline_comment|/* inode IO lock */
macro_line|#endif
multiline_comment|/* I/O state */
DECL|member|io_new_size
id|xfs_fsize_t
id|io_new_size
suffix:semicolon
multiline_comment|/* sz when write completes */
multiline_comment|/* Miscellaneous state. */
DECL|member|io_flags
r_int
r_int
id|io_flags
suffix:semicolon
multiline_comment|/* IO related flags */
multiline_comment|/* DMAPI state */
DECL|member|io_dmattrs
id|dm_attrs_t
id|io_dmattrs
suffix:semicolon
DECL|typedef|xfs_iocore_t
)brace
id|xfs_iocore_t
suffix:semicolon
DECL|macro|io_dmevmask
mdefine_line|#define        io_dmevmask     io_dmattrs.da_dmevmask
DECL|macro|io_dmstate
mdefine_line|#define        io_dmstate      io_dmattrs.da_dmstate
DECL|macro|XFS_IO_INODE
mdefine_line|#define XFS_IO_INODE(io)&t;((xfs_inode_t *) ((io)-&gt;io_obj))
DECL|macro|XFS_IO_DCXVN
mdefine_line|#define XFS_IO_DCXVN(io)&t;((dcxvn_t *) ((io)-&gt;io_obj))
multiline_comment|/*&n; * Flags in the flags field&n; */
DECL|macro|XFS_IOCORE_RT
mdefine_line|#define XFS_IOCORE_RT&t;&t;0x1
multiline_comment|/*&n; * xfs_iocore prototypes&n; */
r_extern
r_void
id|xfs_iocore_inode_init
c_func
(paren
r_struct
id|xfs_inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_iocore_inode_reinit
c_func
(paren
r_struct
id|xfs_inode
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * This is the type used in the xfs inode hash table.&n; * An array of these is allocated for each mounted&n; * file system to hash the inodes for that file system.&n; */
DECL|struct|xfs_ihash
r_typedef
r_struct
id|xfs_ihash
(brace
DECL|member|ih_next
r_struct
id|xfs_inode
op_star
id|ih_next
suffix:semicolon
DECL|member|ih_lock
id|rwlock_t
id|ih_lock
suffix:semicolon
DECL|member|ih_version
id|uint
id|ih_version
suffix:semicolon
DECL|typedef|xfs_ihash_t
)brace
id|xfs_ihash_t
suffix:semicolon
multiline_comment|/*&n; * Inode hashing and hash bucket locking.&n; */
DECL|macro|XFS_BUCKETS
mdefine_line|#define XFS_BUCKETS(mp) (37*(mp)-&gt;m_sb.sb_agcount-1)
DECL|macro|XFS_IHASH
mdefine_line|#define XFS_IHASH(mp,ino) ((mp)-&gt;m_ihash + (((uint)(ino)) % (mp)-&gt;m_ihsize))
multiline_comment|/*&n; * This is the xfs inode cluster hash.  This hash is used by xfs_iflush to&n; * find inodes that share a cluster and can be flushed to disk at the same&n; * time.&n; */
DECL|struct|xfs_chashlist
r_typedef
r_struct
id|xfs_chashlist
(brace
DECL|member|chl_next
r_struct
id|xfs_chashlist
op_star
id|chl_next
suffix:semicolon
DECL|member|chl_ip
r_struct
id|xfs_inode
op_star
id|chl_ip
suffix:semicolon
DECL|member|chl_blkno
id|xfs_daddr_t
id|chl_blkno
suffix:semicolon
multiline_comment|/* starting block number of&n;&t;&t;&t;&t;&t;&t; * the cluster */
DECL|member|chl_buf
r_struct
id|xfs_buf
op_star
id|chl_buf
suffix:semicolon
multiline_comment|/* the inode buffer */
DECL|typedef|xfs_chashlist_t
)brace
id|xfs_chashlist_t
suffix:semicolon
DECL|struct|xfs_chash
r_typedef
r_struct
id|xfs_chash
(brace
DECL|member|ch_list
id|xfs_chashlist_t
op_star
id|ch_list
suffix:semicolon
DECL|member|ch_lock
id|lock_t
id|ch_lock
suffix:semicolon
DECL|typedef|xfs_chash_t
)brace
id|xfs_chash_t
suffix:semicolon
multiline_comment|/*&n; * This is the xfs in-core inode structure.&n; * Most of the on-disk inode is embedded in the i_d field.&n; *&n; * The extent pointers/inline file space, however, are managed&n; * separately.  The memory for this information is pointed to by&n; * the if_u1 unions depending on the type of the data.&n; * This is used to linearize the array of extents for fast in-core&n; * access.  This is used until the file&squot;s number of extents&n; * surpasses XFS_MAX_INCORE_EXTENTS, at which point all extent pointers&n; * are accessed through the buffer cache.&n; *&n; * Other state kept in the in-core inode is used for identification,&n; * locking, transactional updating, etc of the inode.&n; *&n; * Generally, we do not want to hold the i_rlock while holding the&n; * i_ilock. Hierarchy is i_iolock followed by i_rlock.&n; *&n; * xfs_iptr_t contains all the inode fields upto and including the&n; * i_mnext and i_mprev fields, it is used as a marker in the inode&n; * chain off the mount structure by xfs_sync calls.&n; */
r_typedef
r_struct
(brace
DECL|member|ip_hash
r_struct
id|xfs_ihash
op_star
id|ip_hash
suffix:semicolon
multiline_comment|/* pointer to hash header */
DECL|member|ip_next
r_struct
id|xfs_inode
op_star
id|ip_next
suffix:semicolon
multiline_comment|/* inode hash link forw */
DECL|member|ip_mnext
r_struct
id|xfs_inode
op_star
id|ip_mnext
suffix:semicolon
multiline_comment|/* next inode in mount list */
DECL|member|ip_mprev
r_struct
id|xfs_inode
op_star
id|ip_mprev
suffix:semicolon
multiline_comment|/* ptr to prev inode */
DECL|member|ip_prevp
r_struct
id|xfs_inode
op_star
op_star
id|ip_prevp
suffix:semicolon
multiline_comment|/* ptr to prev i_next */
DECL|member|ip_mount
r_struct
id|xfs_mount
op_star
id|ip_mount
suffix:semicolon
multiline_comment|/* fs mount struct ptr */
DECL|typedef|xfs_iptr_t
)brace
id|xfs_iptr_t
suffix:semicolon
DECL|struct|xfs_inode
r_typedef
r_struct
id|xfs_inode
(brace
multiline_comment|/* Inode linking and identification information. */
DECL|member|i_hash
r_struct
id|xfs_ihash
op_star
id|i_hash
suffix:semicolon
multiline_comment|/* pointer to hash header */
DECL|member|i_next
r_struct
id|xfs_inode
op_star
id|i_next
suffix:semicolon
multiline_comment|/* inode hash link forw */
DECL|member|i_mnext
r_struct
id|xfs_inode
op_star
id|i_mnext
suffix:semicolon
multiline_comment|/* next inode in mount list */
DECL|member|i_mprev
r_struct
id|xfs_inode
op_star
id|i_mprev
suffix:semicolon
multiline_comment|/* ptr to prev inode */
DECL|member|i_prevp
r_struct
id|xfs_inode
op_star
op_star
id|i_prevp
suffix:semicolon
multiline_comment|/* ptr to prev i_next */
DECL|member|i_mount
r_struct
id|xfs_mount
op_star
id|i_mount
suffix:semicolon
multiline_comment|/* fs mount struct ptr */
DECL|member|i_reclaim
r_struct
id|list_head
id|i_reclaim
suffix:semicolon
multiline_comment|/* reclaim list */
DECL|member|i_bhv_desc
r_struct
id|bhv_desc
id|i_bhv_desc
suffix:semicolon
multiline_comment|/* inode behavior descriptor*/
DECL|member|i_udquot
r_struct
id|xfs_dquot
op_star
id|i_udquot
suffix:semicolon
multiline_comment|/* user dquot */
DECL|member|i_gdquot
r_struct
id|xfs_dquot
op_star
id|i_gdquot
suffix:semicolon
multiline_comment|/* group dquot */
multiline_comment|/* Inode location stuff */
DECL|member|i_ino
id|xfs_ino_t
id|i_ino
suffix:semicolon
multiline_comment|/* inode number (agno/agino)*/
DECL|member|i_blkno
id|xfs_daddr_t
id|i_blkno
suffix:semicolon
multiline_comment|/* blkno of inode buffer */
DECL|member|i_len
id|ushort
id|i_len
suffix:semicolon
multiline_comment|/* len of inode buffer */
DECL|member|i_boffset
id|ushort
id|i_boffset
suffix:semicolon
multiline_comment|/* off of inode in buffer */
multiline_comment|/* Extent information. */
DECL|member|i_afp
id|xfs_ifork_t
op_star
id|i_afp
suffix:semicolon
multiline_comment|/* attribute fork pointer */
DECL|member|i_df
id|xfs_ifork_t
id|i_df
suffix:semicolon
multiline_comment|/* data fork */
multiline_comment|/* Transaction and locking information. */
DECL|member|i_transp
r_struct
id|xfs_trans
op_star
id|i_transp
suffix:semicolon
multiline_comment|/* ptr to owning transaction*/
DECL|member|i_itemp
r_struct
id|xfs_inode_log_item
op_star
id|i_itemp
suffix:semicolon
multiline_comment|/* logging information */
DECL|member|i_lock
id|mrlock_t
id|i_lock
suffix:semicolon
multiline_comment|/* inode lock */
DECL|member|i_iolock
id|mrlock_t
id|i_iolock
suffix:semicolon
multiline_comment|/* inode IO lock */
DECL|member|i_flock
id|sema_t
id|i_flock
suffix:semicolon
multiline_comment|/* inode flush lock */
DECL|member|i_pincount
id|atomic_t
id|i_pincount
suffix:semicolon
multiline_comment|/* inode pin count */
DECL|member|i_ipin_wait
id|wait_queue_head_t
id|i_ipin_wait
suffix:semicolon
multiline_comment|/* inode pinning wait queue */
macro_line|#ifdef HAVE_REFCACHE
DECL|member|i_refcache
r_struct
id|xfs_inode
op_star
op_star
id|i_refcache
suffix:semicolon
multiline_comment|/* ptr to entry in ref cache */
DECL|member|i_release
r_struct
id|xfs_inode
op_star
id|i_release
suffix:semicolon
multiline_comment|/* inode to unref */
macro_line|#endif
multiline_comment|/* I/O state */
DECL|member|i_iocore
id|xfs_iocore_t
id|i_iocore
suffix:semicolon
multiline_comment|/* I/O core */
multiline_comment|/* Miscellaneous state. */
DECL|member|i_flags
r_int
r_int
id|i_flags
suffix:semicolon
multiline_comment|/* see defined flags below */
DECL|member|i_update_core
r_int
r_char
id|i_update_core
suffix:semicolon
multiline_comment|/* timestamps/size is dirty */
DECL|member|i_update_size
r_int
r_char
id|i_update_size
suffix:semicolon
multiline_comment|/* di_size field is dirty */
DECL|member|i_gen
r_int
r_int
id|i_gen
suffix:semicolon
multiline_comment|/* generation count */
DECL|member|i_delayed_blks
r_int
r_int
id|i_delayed_blks
suffix:semicolon
multiline_comment|/* count of delay alloc blks */
DECL|member|i_d
id|xfs_dinode_core_t
id|i_d
suffix:semicolon
multiline_comment|/* most of ondisk inode */
DECL|member|i_chash
id|xfs_chashlist_t
op_star
id|i_chash
suffix:semicolon
multiline_comment|/* cluster hash list header */
DECL|member|i_cnext
r_struct
id|xfs_inode
op_star
id|i_cnext
suffix:semicolon
multiline_comment|/* cluster hash link forward */
DECL|member|i_cprev
r_struct
id|xfs_inode
op_star
id|i_cprev
suffix:semicolon
multiline_comment|/* cluster hash link backward */
multiline_comment|/* Trace buffers per inode. */
macro_line|#ifdef XFS_BMAP_TRACE
DECL|member|i_xtrace
r_struct
id|ktrace
op_star
id|i_xtrace
suffix:semicolon
multiline_comment|/* inode extent list trace */
macro_line|#endif
macro_line|#ifdef XFS_BMBT_TRACE
DECL|member|i_btrace
r_struct
id|ktrace
op_star
id|i_btrace
suffix:semicolon
multiline_comment|/* inode bmap btree trace */
macro_line|#endif
macro_line|#ifdef XFS_RW_TRACE
DECL|member|i_rwtrace
r_struct
id|ktrace
op_star
id|i_rwtrace
suffix:semicolon
multiline_comment|/* inode read/write trace */
macro_line|#endif
macro_line|#ifdef XFS_ILOCK_TRACE
DECL|member|i_lock_trace
r_struct
id|ktrace
op_star
id|i_lock_trace
suffix:semicolon
multiline_comment|/* inode lock/unlock trace */
macro_line|#endif
macro_line|#ifdef XFS_DIR2_TRACE
DECL|member|i_dir_trace
r_struct
id|ktrace
op_star
id|i_dir_trace
suffix:semicolon
multiline_comment|/* inode directory trace */
macro_line|#endif
DECL|typedef|xfs_inode_t
)brace
id|xfs_inode_t
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
multiline_comment|/*&n; * Fork handling.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_IFORK_PTR)
id|xfs_ifork_t
op_star
id|xfs_ifork_ptr
c_func
(paren
id|xfs_inode_t
op_star
id|ip
comma
r_int
id|w
)paren
suffix:semicolon
DECL|macro|XFS_IFORK_PTR
mdefine_line|#define&t;XFS_IFORK_PTR(ip,w)&t;&t;xfs_ifork_ptr(ip,w)
macro_line|#else
DECL|macro|XFS_IFORK_PTR
mdefine_line|#define&t;XFS_IFORK_PTR(ip,w)   ((w) == XFS_DATA_FORK ? &amp;(ip)-&gt;i_df : (ip)-&gt;i_afp)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_IFORK_Q)
r_int
id|xfs_ifork_q
c_func
(paren
id|xfs_inode_t
op_star
id|ip
)paren
suffix:semicolon
DECL|macro|XFS_IFORK_Q
mdefine_line|#define&t;XFS_IFORK_Q(ip)&t;&t;&t;xfs_ifork_q(ip)
macro_line|#else
DECL|macro|XFS_IFORK_Q
mdefine_line|#define&t;XFS_IFORK_Q(ip)&t;&t;&t;XFS_CFORK_Q(&amp;(ip)-&gt;i_d)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_IFORK_DSIZE)
r_int
id|xfs_ifork_dsize
c_func
(paren
id|xfs_inode_t
op_star
id|ip
)paren
suffix:semicolon
DECL|macro|XFS_IFORK_DSIZE
mdefine_line|#define&t;XFS_IFORK_DSIZE(ip)&t;&t;xfs_ifork_dsize(ip)
macro_line|#else
DECL|macro|XFS_IFORK_DSIZE
mdefine_line|#define&t;XFS_IFORK_DSIZE(ip)&t;&t;XFS_CFORK_DSIZE(&amp;ip-&gt;i_d, ip-&gt;i_mount)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_IFORK_ASIZE)
r_int
id|xfs_ifork_asize
c_func
(paren
id|xfs_inode_t
op_star
id|ip
)paren
suffix:semicolon
DECL|macro|XFS_IFORK_ASIZE
mdefine_line|#define&t;XFS_IFORK_ASIZE(ip)&t;&t;xfs_ifork_asize(ip)
macro_line|#else
DECL|macro|XFS_IFORK_ASIZE
mdefine_line|#define&t;XFS_IFORK_ASIZE(ip)&t;&t;XFS_CFORK_ASIZE(&amp;ip-&gt;i_d, ip-&gt;i_mount)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_IFORK_SIZE)
r_int
id|xfs_ifork_size
c_func
(paren
id|xfs_inode_t
op_star
id|ip
comma
r_int
id|w
)paren
suffix:semicolon
DECL|macro|XFS_IFORK_SIZE
mdefine_line|#define&t;XFS_IFORK_SIZE(ip,w)&t;&t;xfs_ifork_size(ip,w)
macro_line|#else
DECL|macro|XFS_IFORK_SIZE
mdefine_line|#define&t;XFS_IFORK_SIZE(ip,w)&t;&t;XFS_CFORK_SIZE(&amp;ip-&gt;i_d, ip-&gt;i_mount, w)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_IFORK_FORMAT)
r_int
id|xfs_ifork_format
c_func
(paren
id|xfs_inode_t
op_star
id|ip
comma
r_int
id|w
)paren
suffix:semicolon
DECL|macro|XFS_IFORK_FORMAT
mdefine_line|#define&t;XFS_IFORK_FORMAT(ip,w)&t;&t;xfs_ifork_format(ip,w)
macro_line|#else
DECL|macro|XFS_IFORK_FORMAT
mdefine_line|#define&t;XFS_IFORK_FORMAT(ip,w)&t;&t;XFS_CFORK_FORMAT(&amp;ip-&gt;i_d, w)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_IFORK_FMT_SET)
r_void
id|xfs_ifork_fmt_set
c_func
(paren
id|xfs_inode_t
op_star
id|ip
comma
r_int
id|w
comma
r_int
id|n
)paren
suffix:semicolon
DECL|macro|XFS_IFORK_FMT_SET
mdefine_line|#define&t;XFS_IFORK_FMT_SET(ip,w,n)&t;xfs_ifork_fmt_set(ip,w,n)
macro_line|#else
DECL|macro|XFS_IFORK_FMT_SET
mdefine_line|#define&t;XFS_IFORK_FMT_SET(ip,w,n)&t;XFS_CFORK_FMT_SET(&amp;ip-&gt;i_d, w, n)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_IFORK_NEXTENTS)
r_int
id|xfs_ifork_nextents
c_func
(paren
id|xfs_inode_t
op_star
id|ip
comma
r_int
id|w
)paren
suffix:semicolon
DECL|macro|XFS_IFORK_NEXTENTS
mdefine_line|#define&t;XFS_IFORK_NEXTENTS(ip,w)&t;xfs_ifork_nextents(ip,w)
macro_line|#else
DECL|macro|XFS_IFORK_NEXTENTS
mdefine_line|#define&t;XFS_IFORK_NEXTENTS(ip,w)&t;XFS_CFORK_NEXTENTS(&amp;ip-&gt;i_d, w)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_IFORK_NEXT_SET)
r_void
id|xfs_ifork_next_set
c_func
(paren
id|xfs_inode_t
op_star
id|ip
comma
r_int
id|w
comma
r_int
id|n
)paren
suffix:semicolon
DECL|macro|XFS_IFORK_NEXT_SET
mdefine_line|#define&t;XFS_IFORK_NEXT_SET(ip,w,n)&t;xfs_ifork_next_set(ip,w,n)
macro_line|#else
DECL|macro|XFS_IFORK_NEXT_SET
mdefine_line|#define&t;XFS_IFORK_NEXT_SET(ip,w,n)&t;XFS_CFORK_NEXT_SET(&amp;ip-&gt;i_d, w, n)
macro_line|#endif
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * In-core inode flags.&n; */
DECL|macro|XFS_IGRIO
mdefine_line|#define XFS_IGRIO&t;0x0001  /* inode used for guaranteed rate i/o */
DECL|macro|XFS_IUIOSZ
mdefine_line|#define XFS_IUIOSZ&t;0x0002  /* inode i/o sizes have been explicitly set */
DECL|macro|XFS_IQUIESCE
mdefine_line|#define XFS_IQUIESCE    0x0004  /* we have started quiescing for this inode */
DECL|macro|XFS_IRECLAIM
mdefine_line|#define XFS_IRECLAIM    0x0008  /* we have started reclaiming this inode    */
DECL|macro|XFS_ISTALE
mdefine_line|#define XFS_ISTALE&t;0x0010&t;/* inode has been staled */
DECL|macro|XFS_IRECLAIMABLE
mdefine_line|#define XFS_IRECLAIMABLE 0x0020 /* inode can be reclaimed */
DECL|macro|XFS_INEW
mdefine_line|#define XFS_INEW&t;0x0040
multiline_comment|/*&n; * Flags for inode locking.&n; */
DECL|macro|XFS_IOLOCK_EXCL
mdefine_line|#define&t;XFS_IOLOCK_EXCL&t;&t;0x001
DECL|macro|XFS_IOLOCK_SHARED
mdefine_line|#define&t;XFS_IOLOCK_SHARED&t;0x002
DECL|macro|XFS_ILOCK_EXCL
mdefine_line|#define&t;XFS_ILOCK_EXCL&t;&t;0x004
DECL|macro|XFS_ILOCK_SHARED
mdefine_line|#define&t;XFS_ILOCK_SHARED&t;0x008
DECL|macro|XFS_IUNLOCK_NONOTIFY
mdefine_line|#define&t;XFS_IUNLOCK_NONOTIFY&t;0x010
DECL|macro|XFS_EXTENT_TOKEN_RD
mdefine_line|#define XFS_EXTENT_TOKEN_RD&t;0x040
DECL|macro|XFS_SIZE_TOKEN_RD
mdefine_line|#define XFS_SIZE_TOKEN_RD&t;0x080
DECL|macro|XFS_EXTSIZE_RD
mdefine_line|#define XFS_EXTSIZE_RD&t;&t;(XFS_EXTENT_TOKEN_RD|XFS_SIZE_TOKEN_RD)
DECL|macro|XFS_WILLLEND
mdefine_line|#define XFS_WILLLEND&t;&t;0x100&t;/* Always acquire tokens for lending */
DECL|macro|XFS_EXTENT_TOKEN_WR
mdefine_line|#define XFS_EXTENT_TOKEN_WR&t;(XFS_EXTENT_TOKEN_RD | XFS_WILLLEND)
DECL|macro|XFS_SIZE_TOKEN_WR
mdefine_line|#define XFS_SIZE_TOKEN_WR       (XFS_SIZE_TOKEN_RD | XFS_WILLLEND)
DECL|macro|XFS_EXTSIZE_WR
mdefine_line|#define XFS_EXTSIZE_WR&t;&t;(XFS_EXTSIZE_RD | XFS_WILLLEND)
DECL|macro|XFS_LOCK_MASK
mdefine_line|#define XFS_LOCK_MASK&t;&bslash;&n;&t;(XFS_IOLOCK_EXCL | XFS_IOLOCK_SHARED | XFS_ILOCK_EXCL | &bslash;&n;&t; XFS_ILOCK_SHARED | XFS_EXTENT_TOKEN_RD | XFS_SIZE_TOKEN_RD | &bslash;&n;&t; XFS_WILLLEND)
multiline_comment|/*&n; * Flags for xfs_iflush()&n; */
DECL|macro|XFS_IFLUSH_DELWRI_ELSE_SYNC
mdefine_line|#define&t;XFS_IFLUSH_DELWRI_ELSE_SYNC&t;1
DECL|macro|XFS_IFLUSH_DELWRI_ELSE_ASYNC
mdefine_line|#define&t;XFS_IFLUSH_DELWRI_ELSE_ASYNC&t;2
DECL|macro|XFS_IFLUSH_SYNC
mdefine_line|#define&t;XFS_IFLUSH_SYNC&t;&t;&t;3
DECL|macro|XFS_IFLUSH_ASYNC
mdefine_line|#define&t;XFS_IFLUSH_ASYNC&t;&t;4
DECL|macro|XFS_IFLUSH_DELWRI
mdefine_line|#define&t;XFS_IFLUSH_DELWRI&t;&t;5
multiline_comment|/*&n; * Flags for xfs_iflush_all.&n; */
DECL|macro|XFS_FLUSH_ALL
mdefine_line|#define&t;XFS_FLUSH_ALL&t;&t;0x1
multiline_comment|/*&n; * Flags for xfs_itruncate_start().&n; */
DECL|macro|XFS_ITRUNC_DEFINITE
mdefine_line|#define&t;XFS_ITRUNC_DEFINITE&t;0x1
DECL|macro|XFS_ITRUNC_MAYBE
mdefine_line|#define&t;XFS_ITRUNC_MAYBE&t;0x2
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_ITOV)
r_struct
id|vnode
op_star
id|xfs_itov
c_func
(paren
id|xfs_inode_t
op_star
id|ip
)paren
suffix:semicolon
DECL|macro|XFS_ITOV
mdefine_line|#define&t;XFS_ITOV(ip)&t;&t;xfs_itov(ip)
macro_line|#else
DECL|macro|XFS_ITOV
mdefine_line|#define&t;XFS_ITOV(ip)&t;&t;BHV_TO_VNODE(XFS_ITOBHV(ip))
macro_line|#endif
DECL|macro|XFS_ITOV_NULL
mdefine_line|#define&t;XFS_ITOV_NULL(ip)&t;BHV_TO_VNODE_NULL(XFS_ITOBHV(ip))
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_ITOBHV)
r_struct
id|bhv_desc
op_star
id|xfs_itobhv
c_func
(paren
id|xfs_inode_t
op_star
id|ip
)paren
suffix:semicolon
DECL|macro|XFS_ITOBHV
mdefine_line|#define&t;XFS_ITOBHV(ip)&t;&t;xfs_itobhv(ip)
macro_line|#else
DECL|macro|XFS_ITOBHV
mdefine_line|#define&t;XFS_ITOBHV(ip)&t;&t;((struct bhv_desc *)(&amp;((ip)-&gt;i_bhv_desc)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BHVTOI)
id|xfs_inode_t
op_star
id|xfs_bhvtoi
c_func
(paren
r_struct
id|bhv_desc
op_star
id|bhvp
)paren
suffix:semicolon
DECL|macro|XFS_BHVTOI
mdefine_line|#define&t;XFS_BHVTOI(bhvp)&t;xfs_bhvtoi(bhvp)
macro_line|#else
DECL|macro|XFS_BHVTOI
mdefine_line|#define&t;XFS_BHVTOI(bhvp)&t;&bslash;&n;&t;((xfs_inode_t *)((char *)(bhvp) - &bslash;&n;&t;&t;&t; (char *)&amp;(((xfs_inode_t *)0)-&gt;i_bhv_desc)))
macro_line|#endif
DECL|macro|BHV_IS_XFS
mdefine_line|#define BHV_IS_XFS(bdp)&t;&t;(BHV_OPS(bdp) == &amp;xfs_vnodeops)
multiline_comment|/*&n; * Pick the inode cluster hash bucket&n; * (m_chash is the same size as m_ihash)&n; */
DECL|macro|XFS_CHASH
mdefine_line|#define XFS_CHASH(mp,blk) ((mp)-&gt;m_chash + (((uint)blk) % (mp)-&gt;m_chsize))
multiline_comment|/*&n; * For multiple groups support: if S_ISGID bit is set in the parent&n; * directory, group of new file is set to that of the parent, and&n; * new subdirectory gets S_ISGID bit from parent.&n; */
DECL|macro|XFS_INHERIT_GID
mdefine_line|#define XFS_INHERIT_GID(pip, vfsp)&t;&bslash;&n;&t;(((vfsp)-&gt;vfs_flag &amp; VFS_GRPID) || ((pip)-&gt;i_d.di_mode &amp; S_ISGID))
multiline_comment|/*&n; * xfs_iget.c prototypes.&n; */
DECL|macro|IGET_CREATE
mdefine_line|#define IGET_CREATE&t;1
r_void
id|xfs_ihash_init
c_func
(paren
r_struct
id|xfs_mount
op_star
)paren
suffix:semicolon
r_void
id|xfs_ihash_free
c_func
(paren
r_struct
id|xfs_mount
op_star
)paren
suffix:semicolon
r_void
id|xfs_chash_init
c_func
(paren
r_struct
id|xfs_mount
op_star
)paren
suffix:semicolon
r_void
id|xfs_chash_free
c_func
(paren
r_struct
id|xfs_mount
op_star
)paren
suffix:semicolon
id|xfs_inode_t
op_star
id|xfs_inode_incore
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
id|xfs_ino_t
comma
r_struct
id|xfs_trans
op_star
)paren
suffix:semicolon
r_void
id|xfs_inode_lock_init
c_func
(paren
id|xfs_inode_t
op_star
comma
r_struct
id|vnode
op_star
)paren
suffix:semicolon
r_int
id|xfs_iget
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
r_struct
id|xfs_trans
op_star
comma
id|xfs_ino_t
comma
id|uint
comma
id|uint
comma
id|xfs_inode_t
op_star
op_star
comma
id|xfs_daddr_t
)paren
suffix:semicolon
r_void
id|xfs_iput
c_func
(paren
id|xfs_inode_t
op_star
comma
id|uint
)paren
suffix:semicolon
r_void
id|xfs_iput_new
c_func
(paren
id|xfs_inode_t
op_star
comma
id|uint
)paren
suffix:semicolon
r_void
id|xfs_ilock
c_func
(paren
id|xfs_inode_t
op_star
comma
id|uint
)paren
suffix:semicolon
r_int
id|xfs_ilock_nowait
c_func
(paren
id|xfs_inode_t
op_star
comma
id|uint
)paren
suffix:semicolon
r_void
id|xfs_iunlock
c_func
(paren
id|xfs_inode_t
op_star
comma
id|uint
)paren
suffix:semicolon
r_void
id|xfs_ilock_demote
c_func
(paren
id|xfs_inode_t
op_star
comma
id|uint
)paren
suffix:semicolon
r_void
id|xfs_iflock
c_func
(paren
id|xfs_inode_t
op_star
)paren
suffix:semicolon
r_int
id|xfs_iflock_nowait
c_func
(paren
id|xfs_inode_t
op_star
)paren
suffix:semicolon
id|uint
id|xfs_ilock_map_shared
c_func
(paren
id|xfs_inode_t
op_star
)paren
suffix:semicolon
r_void
id|xfs_iunlock_map_shared
c_func
(paren
id|xfs_inode_t
op_star
comma
id|uint
)paren
suffix:semicolon
r_void
id|xfs_ifunlock
c_func
(paren
id|xfs_inode_t
op_star
)paren
suffix:semicolon
r_void
id|xfs_ireclaim
c_func
(paren
id|xfs_inode_t
op_star
)paren
suffix:semicolon
r_int
id|xfs_finish_reclaim
c_func
(paren
id|xfs_inode_t
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_int
id|xfs_finish_reclaim_all
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * xfs_inode.c prototypes.&n; */
r_int
id|xfs_inotobp
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
r_struct
id|xfs_trans
op_star
comma
id|xfs_ino_t
comma
id|xfs_dinode_t
op_star
op_star
comma
r_struct
id|xfs_buf
op_star
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_int
id|xfs_itobp
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
r_struct
id|xfs_trans
op_star
comma
id|xfs_inode_t
op_star
comma
id|xfs_dinode_t
op_star
op_star
comma
r_struct
id|xfs_buf
op_star
op_star
comma
id|xfs_daddr_t
)paren
suffix:semicolon
r_int
id|xfs_iread
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
r_struct
id|xfs_trans
op_star
comma
id|xfs_ino_t
comma
id|xfs_inode_t
op_star
op_star
comma
id|xfs_daddr_t
)paren
suffix:semicolon
r_int
id|xfs_iread_extents
c_func
(paren
r_struct
id|xfs_trans
op_star
comma
id|xfs_inode_t
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|xfs_ialloc
c_func
(paren
r_struct
id|xfs_trans
op_star
comma
id|xfs_inode_t
op_star
comma
id|mode_t
comma
id|nlink_t
comma
id|xfs_dev_t
comma
r_struct
id|cred
op_star
comma
id|xfs_prid_t
comma
r_int
comma
r_struct
id|xfs_buf
op_star
op_star
comma
id|boolean_t
op_star
comma
id|xfs_inode_t
op_star
op_star
)paren
suffix:semicolon
r_void
id|xfs_xlate_dinode_core
c_func
(paren
id|xfs_caddr_t
comma
r_struct
id|xfs_dinode_core
op_star
comma
r_int
comma
id|xfs_arch_t
)paren
suffix:semicolon
id|uint
id|xfs_dic2xflags
c_func
(paren
r_struct
id|xfs_dinode_core
op_star
comma
id|xfs_arch_t
)paren
suffix:semicolon
r_int
id|xfs_ifree
c_func
(paren
r_struct
id|xfs_trans
op_star
comma
id|xfs_inode_t
op_star
comma
r_struct
id|xfs_bmap_free
op_star
)paren
suffix:semicolon
r_void
id|xfs_itruncate_start
c_func
(paren
id|xfs_inode_t
op_star
comma
id|uint
comma
id|xfs_fsize_t
)paren
suffix:semicolon
r_int
id|xfs_itruncate_finish
c_func
(paren
r_struct
id|xfs_trans
op_star
op_star
comma
id|xfs_inode_t
op_star
comma
id|xfs_fsize_t
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_int
id|xfs_iunlink
c_func
(paren
r_struct
id|xfs_trans
op_star
comma
id|xfs_inode_t
op_star
)paren
suffix:semicolon
r_int
id|xfs_igrow_start
c_func
(paren
id|xfs_inode_t
op_star
comma
id|xfs_fsize_t
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
r_void
id|xfs_igrow_finish
c_func
(paren
r_struct
id|xfs_trans
op_star
comma
id|xfs_inode_t
op_star
comma
id|xfs_fsize_t
comma
r_int
)paren
suffix:semicolon
r_void
id|xfs_idestroy_fork
c_func
(paren
id|xfs_inode_t
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|xfs_idestroy
c_func
(paren
id|xfs_inode_t
op_star
)paren
suffix:semicolon
r_void
id|xfs_idata_realloc
c_func
(paren
id|xfs_inode_t
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_void
id|xfs_iextract
c_func
(paren
id|xfs_inode_t
op_star
)paren
suffix:semicolon
r_void
id|xfs_iext_realloc
c_func
(paren
id|xfs_inode_t
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_void
id|xfs_iroot_realloc
c_func
(paren
id|xfs_inode_t
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_void
id|xfs_ipin
c_func
(paren
id|xfs_inode_t
op_star
)paren
suffix:semicolon
r_void
id|xfs_iunpin
c_func
(paren
id|xfs_inode_t
op_star
)paren
suffix:semicolon
r_int
id|xfs_iextents_copy
c_func
(paren
id|xfs_inode_t
op_star
comma
id|xfs_bmbt_rec_t
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|xfs_iflush
c_func
(paren
id|xfs_inode_t
op_star
comma
id|uint
)paren
suffix:semicolon
r_int
id|xfs_iflush_all
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|xfs_iaccess
c_func
(paren
id|xfs_inode_t
op_star
comma
id|mode_t
comma
id|cred_t
op_star
)paren
suffix:semicolon
id|uint
id|xfs_iroundup
c_func
(paren
id|uint
)paren
suffix:semicolon
r_void
id|xfs_ichgtime
c_func
(paren
id|xfs_inode_t
op_star
comma
r_int
)paren
suffix:semicolon
id|xfs_fsize_t
id|xfs_file_last_byte
c_func
(paren
id|xfs_inode_t
op_star
)paren
suffix:semicolon
r_void
id|xfs_lock_inodes
c_func
(paren
id|xfs_inode_t
op_star
op_star
comma
r_int
comma
r_int
comma
id|uint
)paren
suffix:semicolon
DECL|macro|xfs_ipincount
mdefine_line|#define xfs_ipincount(ip)&t;((unsigned int) atomic_read(&amp;ip-&gt;i_pincount))
macro_line|#ifdef DEBUG
r_void
id|xfs_isize_check
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
id|xfs_inode_t
op_star
comma
id|xfs_fsize_t
)paren
suffix:semicolon
macro_line|#else&t;/* DEBUG */
DECL|macro|xfs_isize_check
mdefine_line|#define xfs_isize_check(mp, ip, isize)
macro_line|#endif&t;/* DEBUG */
macro_line|#if defined(DEBUG)
r_void
id|xfs_inobp_check
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
r_struct
id|xfs_buf
op_star
)paren
suffix:semicolon
macro_line|#else
DECL|macro|xfs_inobp_check
mdefine_line|#define&t;xfs_inobp_check(mp, bp)
macro_line|#endif /* DEBUG */
r_extern
r_struct
id|kmem_zone
op_star
id|xfs_chashlist_zone
suffix:semicolon
r_extern
r_struct
id|kmem_zone
op_star
id|xfs_ifork_zone
suffix:semicolon
r_extern
r_struct
id|kmem_zone
op_star
id|xfs_inode_zone
suffix:semicolon
r_extern
r_struct
id|kmem_zone
op_star
id|xfs_ili_zone
suffix:semicolon
r_extern
r_struct
id|vnodeops
id|xfs_vnodeops
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* __XFS_INODE_H__ */
eof
