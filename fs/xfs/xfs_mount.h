multiline_comment|/*&n; * Copyright (c) 2000-2004 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_MOUNT_H__
DECL|macro|__XFS_MOUNT_H__
mdefine_line|#define&t;__XFS_MOUNT_H__
DECL|struct|xfs_trans_reservations
r_typedef
r_struct
id|xfs_trans_reservations
(brace
DECL|member|tr_write
id|uint
id|tr_write
suffix:semicolon
multiline_comment|/* extent alloc trans */
DECL|member|tr_itruncate
id|uint
id|tr_itruncate
suffix:semicolon
multiline_comment|/* truncate trans */
DECL|member|tr_rename
id|uint
id|tr_rename
suffix:semicolon
multiline_comment|/* rename trans */
DECL|member|tr_link
id|uint
id|tr_link
suffix:semicolon
multiline_comment|/* link trans */
DECL|member|tr_remove
id|uint
id|tr_remove
suffix:semicolon
multiline_comment|/* unlink trans */
DECL|member|tr_symlink
id|uint
id|tr_symlink
suffix:semicolon
multiline_comment|/* symlink trans */
DECL|member|tr_create
id|uint
id|tr_create
suffix:semicolon
multiline_comment|/* create trans */
DECL|member|tr_mkdir
id|uint
id|tr_mkdir
suffix:semicolon
multiline_comment|/* mkdir trans */
DECL|member|tr_ifree
id|uint
id|tr_ifree
suffix:semicolon
multiline_comment|/* inode free trans */
DECL|member|tr_ichange
id|uint
id|tr_ichange
suffix:semicolon
multiline_comment|/* inode update trans */
DECL|member|tr_growdata
id|uint
id|tr_growdata
suffix:semicolon
multiline_comment|/* fs data section grow trans */
DECL|member|tr_swrite
id|uint
id|tr_swrite
suffix:semicolon
multiline_comment|/* sync write inode trans */
DECL|member|tr_addafork
id|uint
id|tr_addafork
suffix:semicolon
multiline_comment|/* cvt inode to attributed trans */
DECL|member|tr_writeid
id|uint
id|tr_writeid
suffix:semicolon
multiline_comment|/* write setuid/setgid file */
DECL|member|tr_attrinval
id|uint
id|tr_attrinval
suffix:semicolon
multiline_comment|/* attr fork buffer invalidation */
DECL|member|tr_attrset
id|uint
id|tr_attrset
suffix:semicolon
multiline_comment|/* set/create an attribute */
DECL|member|tr_attrrm
id|uint
id|tr_attrrm
suffix:semicolon
multiline_comment|/* remove an attribute */
DECL|member|tr_clearagi
id|uint
id|tr_clearagi
suffix:semicolon
multiline_comment|/* clear bad agi unlinked ino bucket */
DECL|member|tr_growrtalloc
id|uint
id|tr_growrtalloc
suffix:semicolon
multiline_comment|/* grow realtime allocations */
DECL|member|tr_growrtzero
id|uint
id|tr_growrtzero
suffix:semicolon
multiline_comment|/* grow realtime zeroing */
DECL|member|tr_growrtfree
id|uint
id|tr_growrtfree
suffix:semicolon
multiline_comment|/* grow realtime freeing */
DECL|typedef|xfs_trans_reservations_t
)brace
id|xfs_trans_reservations_t
suffix:semicolon
macro_line|#ifndef __KERNEL__
multiline_comment|/*&n; * Moved here from xfs_ag.h to avoid reordering header files&n; */
DECL|macro|XFS_DADDR_TO_AGNO
mdefine_line|#define XFS_DADDR_TO_AGNO(mp,d) &bslash;&n;&t;((xfs_agnumber_t)(XFS_BB_TO_FSBT(mp, d) / (mp)-&gt;m_sb.sb_agblocks))
DECL|macro|XFS_DADDR_TO_AGBNO
mdefine_line|#define XFS_DADDR_TO_AGBNO(mp,d) &bslash;&n;&t;((xfs_agblock_t)(XFS_BB_TO_FSBT(mp, d) % (mp)-&gt;m_sb.sb_agblocks))
macro_line|#else
r_struct
id|cred
suffix:semicolon
r_struct
id|log
suffix:semicolon
r_struct
id|vfs
suffix:semicolon
r_struct
id|vnode
suffix:semicolon
r_struct
id|xfs_mount_args
suffix:semicolon
r_struct
id|xfs_ihash
suffix:semicolon
r_struct
id|xfs_chash
suffix:semicolon
r_struct
id|xfs_inode
suffix:semicolon
r_struct
id|xfs_perag
suffix:semicolon
r_struct
id|xfs_iocore
suffix:semicolon
r_struct
id|xfs_bmbt_irec
suffix:semicolon
r_struct
id|xfs_bmap_free
suffix:semicolon
DECL|macro|AIL_LOCK_T
mdefine_line|#define&t;AIL_LOCK_T&t;&t;lock_t
DECL|macro|AIL_LOCKINIT
mdefine_line|#define&t;AIL_LOCKINIT(x,y)&t;spinlock_init(x,y)
DECL|macro|AIL_LOCK_DESTROY
mdefine_line|#define&t;AIL_LOCK_DESTROY(x)&t;spinlock_destroy(x)
DECL|macro|AIL_LOCK
mdefine_line|#define&t;AIL_LOCK(mp,s)&t;&t;s=mutex_spinlock(&amp;(mp)-&gt;m_ail_lock)
DECL|macro|AIL_UNLOCK
mdefine_line|#define&t;AIL_UNLOCK(mp,s)&t;mutex_spinunlock(&amp;(mp)-&gt;m_ail_lock, s)
multiline_comment|/*&n; * Prototypes and functions for the Data Migration subsystem.&n; */
DECL|typedef|xfs_send_data_t
r_typedef
r_int
(paren
op_star
id|xfs_send_data_t
)paren
(paren
r_int
comma
r_struct
id|vnode
op_star
comma
id|xfs_off_t
comma
r_int
comma
r_int
comma
id|vrwlock_t
op_star
)paren
suffix:semicolon
DECL|typedef|xfs_send_mmap_t
r_typedef
r_int
(paren
op_star
id|xfs_send_mmap_t
)paren
(paren
r_struct
id|vm_area_struct
op_star
comma
id|uint
)paren
suffix:semicolon
DECL|typedef|xfs_send_destroy_t
r_typedef
r_int
(paren
op_star
id|xfs_send_destroy_t
)paren
(paren
r_struct
id|vnode
op_star
comma
id|dm_right_t
)paren
suffix:semicolon
DECL|typedef|xfs_send_namesp_t
r_typedef
r_int
(paren
op_star
id|xfs_send_namesp_t
)paren
(paren
id|dm_eventtype_t
comma
r_struct
id|vfs
op_star
comma
r_struct
id|vnode
op_star
comma
id|dm_right_t
comma
r_struct
id|vnode
op_star
comma
id|dm_right_t
comma
r_char
op_star
comma
r_char
op_star
comma
id|mode_t
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|typedef|xfs_send_unmount_t
r_typedef
r_void
(paren
op_star
id|xfs_send_unmount_t
)paren
(paren
r_struct
id|vfs
op_star
comma
r_struct
id|vnode
op_star
comma
id|dm_right_t
comma
id|mode_t
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|struct|xfs_dmops
r_typedef
r_struct
id|xfs_dmops
(brace
DECL|member|xfs_send_data
id|xfs_send_data_t
id|xfs_send_data
suffix:semicolon
DECL|member|xfs_send_mmap
id|xfs_send_mmap_t
id|xfs_send_mmap
suffix:semicolon
DECL|member|xfs_send_destroy
id|xfs_send_destroy_t
id|xfs_send_destroy
suffix:semicolon
DECL|member|xfs_send_namesp
id|xfs_send_namesp_t
id|xfs_send_namesp
suffix:semicolon
DECL|member|xfs_send_unmount
id|xfs_send_unmount_t
id|xfs_send_unmount
suffix:semicolon
DECL|typedef|xfs_dmops_t
)brace
id|xfs_dmops_t
suffix:semicolon
DECL|macro|XFS_SEND_DATA
mdefine_line|#define XFS_SEND_DATA(mp, ev,vp,off,len,fl,lock) &bslash;&n;&t;(*(mp)-&gt;m_dm_ops.xfs_send_data)(ev,vp,off,len,fl,lock)
DECL|macro|XFS_SEND_MMAP
mdefine_line|#define XFS_SEND_MMAP(mp, vma,fl) &bslash;&n;&t;(*(mp)-&gt;m_dm_ops.xfs_send_mmap)(vma,fl)
DECL|macro|XFS_SEND_DESTROY
mdefine_line|#define XFS_SEND_DESTROY(mp, vp,right) &bslash;&n;&t;(*(mp)-&gt;m_dm_ops.xfs_send_destroy)(vp,right)
DECL|macro|XFS_SEND_NAMESP
mdefine_line|#define XFS_SEND_NAMESP(mp, ev,b1,r1,b2,r2,n1,n2,mode,rval,fl) &bslash;&n;&t;(*(mp)-&gt;m_dm_ops.xfs_send_namesp)(ev,NULL,b1,r1,b2,r2,n1,n2,mode,rval,fl)
DECL|macro|XFS_SEND_PREUNMOUNT
mdefine_line|#define XFS_SEND_PREUNMOUNT(mp, vfs,b1,r1,b2,r2,n1,n2,mode,rval,fl) &bslash;&n;&t;(*(mp)-&gt;m_dm_ops.xfs_send_namesp)(DM_EVENT_PREUNMOUNT,vfs,b1,r1,b2,r2,n1,n2,mode,rval,fl)
DECL|macro|XFS_SEND_UNMOUNT
mdefine_line|#define XFS_SEND_UNMOUNT(mp, vfsp,vp,right,mode,rval,fl) &bslash;&n;&t;(*(mp)-&gt;m_dm_ops.xfs_send_unmount)(vfsp,vp,right,mode,rval,fl)
multiline_comment|/*&n; * Prototypes and functions for the Quota Management subsystem.&n; */
r_struct
id|xfs_dquot
suffix:semicolon
r_struct
id|xfs_dqtrxops
suffix:semicolon
r_struct
id|xfs_quotainfo
suffix:semicolon
DECL|typedef|xfs_qminit_t
r_typedef
r_int
(paren
op_star
id|xfs_qminit_t
)paren
(paren
r_struct
id|xfs_mount
op_star
comma
id|uint
op_star
comma
id|uint
op_star
)paren
suffix:semicolon
DECL|typedef|xfs_qmmount_t
r_typedef
r_int
(paren
op_star
id|xfs_qmmount_t
)paren
(paren
r_struct
id|xfs_mount
op_star
comma
id|uint
comma
id|uint
comma
r_int
)paren
suffix:semicolon
DECL|typedef|xfs_qmunmount_t
r_typedef
r_int
(paren
op_star
id|xfs_qmunmount_t
)paren
(paren
r_struct
id|xfs_mount
op_star
)paren
suffix:semicolon
DECL|typedef|xfs_qmdone_t
r_typedef
r_void
(paren
op_star
id|xfs_qmdone_t
)paren
(paren
r_struct
id|xfs_mount
op_star
)paren
suffix:semicolon
DECL|typedef|xfs_dqrele_t
r_typedef
r_void
(paren
op_star
id|xfs_dqrele_t
)paren
(paren
r_struct
id|xfs_dquot
op_star
)paren
suffix:semicolon
DECL|typedef|xfs_dqattach_t
r_typedef
r_int
(paren
op_star
id|xfs_dqattach_t
)paren
(paren
r_struct
id|xfs_inode
op_star
comma
id|uint
)paren
suffix:semicolon
DECL|typedef|xfs_dqdetach_t
r_typedef
r_void
(paren
op_star
id|xfs_dqdetach_t
)paren
(paren
r_struct
id|xfs_inode
op_star
)paren
suffix:semicolon
DECL|typedef|xfs_dqpurgeall_t
r_typedef
r_int
(paren
op_star
id|xfs_dqpurgeall_t
)paren
(paren
r_struct
id|xfs_mount
op_star
comma
id|uint
)paren
suffix:semicolon
DECL|typedef|xfs_dqvopalloc_t
r_typedef
r_int
(paren
op_star
id|xfs_dqvopalloc_t
)paren
(paren
r_struct
id|xfs_mount
op_star
comma
r_struct
id|xfs_inode
op_star
comma
id|uid_t
comma
id|gid_t
comma
id|uint
comma
r_struct
id|xfs_dquot
op_star
op_star
comma
r_struct
id|xfs_dquot
op_star
op_star
)paren
suffix:semicolon
DECL|typedef|xfs_dqvopcreate_t
r_typedef
r_void
(paren
op_star
id|xfs_dqvopcreate_t
)paren
(paren
r_struct
id|xfs_trans
op_star
comma
r_struct
id|xfs_inode
op_star
comma
r_struct
id|xfs_dquot
op_star
comma
r_struct
id|xfs_dquot
op_star
)paren
suffix:semicolon
DECL|typedef|xfs_dqvoprename_t
r_typedef
r_int
(paren
op_star
id|xfs_dqvoprename_t
)paren
(paren
r_struct
id|xfs_inode
op_star
op_star
)paren
suffix:semicolon
DECL|typedef|xfs_dqvopchown_t
r_typedef
r_struct
id|xfs_dquot
op_star
(paren
op_star
id|xfs_dqvopchown_t
)paren
(paren
r_struct
id|xfs_trans
op_star
comma
r_struct
id|xfs_inode
op_star
comma
r_struct
id|xfs_dquot
op_star
op_star
comma
r_struct
id|xfs_dquot
op_star
)paren
suffix:semicolon
DECL|typedef|xfs_dqvopchownresv_t
r_typedef
r_int
(paren
op_star
id|xfs_dqvopchownresv_t
)paren
(paren
r_struct
id|xfs_trans
op_star
comma
r_struct
id|xfs_inode
op_star
comma
r_struct
id|xfs_dquot
op_star
comma
r_struct
id|xfs_dquot
op_star
comma
id|uint
)paren
suffix:semicolon
DECL|struct|xfs_qmops
r_typedef
r_struct
id|xfs_qmops
(brace
DECL|member|xfs_qminit
id|xfs_qminit_t
id|xfs_qminit
suffix:semicolon
DECL|member|xfs_qmdone
id|xfs_qmdone_t
id|xfs_qmdone
suffix:semicolon
DECL|member|xfs_qmmount
id|xfs_qmmount_t
id|xfs_qmmount
suffix:semicolon
DECL|member|xfs_qmunmount
id|xfs_qmunmount_t
id|xfs_qmunmount
suffix:semicolon
DECL|member|xfs_dqrele
id|xfs_dqrele_t
id|xfs_dqrele
suffix:semicolon
DECL|member|xfs_dqattach
id|xfs_dqattach_t
id|xfs_dqattach
suffix:semicolon
DECL|member|xfs_dqdetach
id|xfs_dqdetach_t
id|xfs_dqdetach
suffix:semicolon
DECL|member|xfs_dqpurgeall
id|xfs_dqpurgeall_t
id|xfs_dqpurgeall
suffix:semicolon
DECL|member|xfs_dqvopalloc
id|xfs_dqvopalloc_t
id|xfs_dqvopalloc
suffix:semicolon
DECL|member|xfs_dqvopcreate
id|xfs_dqvopcreate_t
id|xfs_dqvopcreate
suffix:semicolon
DECL|member|xfs_dqvoprename
id|xfs_dqvoprename_t
id|xfs_dqvoprename
suffix:semicolon
DECL|member|xfs_dqvopchown
id|xfs_dqvopchown_t
id|xfs_dqvopchown
suffix:semicolon
DECL|member|xfs_dqvopchownresv
id|xfs_dqvopchownresv_t
id|xfs_dqvopchownresv
suffix:semicolon
DECL|member|xfs_dqtrxops
r_struct
id|xfs_dqtrxops
op_star
id|xfs_dqtrxops
suffix:semicolon
DECL|typedef|xfs_qmops_t
)brace
id|xfs_qmops_t
suffix:semicolon
DECL|macro|XFS_QM_INIT
mdefine_line|#define XFS_QM_INIT(mp, mnt, fl) &bslash;&n;&t;(*(mp)-&gt;m_qm_ops.xfs_qminit)(mp, mnt, fl)
DECL|macro|XFS_QM_MOUNT
mdefine_line|#define XFS_QM_MOUNT(mp, mnt, fl, mfsi_flags) &bslash;&n;&t;(*(mp)-&gt;m_qm_ops.xfs_qmmount)(mp, mnt, fl, mfsi_flags)
DECL|macro|XFS_QM_UNMOUNT
mdefine_line|#define XFS_QM_UNMOUNT(mp) &bslash;&n;&t;(*(mp)-&gt;m_qm_ops.xfs_qmunmount)(mp)
DECL|macro|XFS_QM_DONE
mdefine_line|#define XFS_QM_DONE(mp) &bslash;&n;&t;(*(mp)-&gt;m_qm_ops.xfs_qmdone)(mp)
DECL|macro|XFS_QM_DQRELE
mdefine_line|#define XFS_QM_DQRELE(mp, dq) &bslash;&n;&t;(*(mp)-&gt;m_qm_ops.xfs_dqrele)(dq)
DECL|macro|XFS_QM_DQATTACH
mdefine_line|#define XFS_QM_DQATTACH(mp, ip, fl) &bslash;&n;&t;(*(mp)-&gt;m_qm_ops.xfs_dqattach)(ip, fl)
DECL|macro|XFS_QM_DQDETACH
mdefine_line|#define XFS_QM_DQDETACH(mp, ip) &bslash;&n;&t;(*(mp)-&gt;m_qm_ops.xfs_dqdetach)(ip)
DECL|macro|XFS_QM_DQPURGEALL
mdefine_line|#define XFS_QM_DQPURGEALL(mp, fl) &bslash;&n;&t;(*(mp)-&gt;m_qm_ops.xfs_dqpurgeall)(mp, fl)
DECL|macro|XFS_QM_DQVOPALLOC
mdefine_line|#define XFS_QM_DQVOPALLOC(mp, ip, uid, gid, fl, dq1, dq2) &bslash;&n;&t;(*(mp)-&gt;m_qm_ops.xfs_dqvopalloc)(mp, ip, uid, gid, fl, dq1, dq2)
DECL|macro|XFS_QM_DQVOPCREATE
mdefine_line|#define XFS_QM_DQVOPCREATE(mp, tp, ip, dq1, dq2) &bslash;&n;&t;(*(mp)-&gt;m_qm_ops.xfs_dqvopcreate)(tp, ip, dq1, dq2)
DECL|macro|XFS_QM_DQVOPRENAME
mdefine_line|#define XFS_QM_DQVOPRENAME(mp, ip) &bslash;&n;&t;(*(mp)-&gt;m_qm_ops.xfs_dqvoprename)(ip)
DECL|macro|XFS_QM_DQVOPCHOWN
mdefine_line|#define XFS_QM_DQVOPCHOWN(mp, tp, ip, dqp, dq) &bslash;&n;&t;(*(mp)-&gt;m_qm_ops.xfs_dqvopchown)(tp, ip, dqp, dq)
DECL|macro|XFS_QM_DQVOPCHOWNRESV
mdefine_line|#define XFS_QM_DQVOPCHOWNRESV(mp, tp, ip, dq1, dq2, fl) &bslash;&n;&t;(*(mp)-&gt;m_qm_ops.xfs_dqvopchownresv)(tp, ip, dq1, dq2, fl)
multiline_comment|/*&n; * Prototypes and functions for I/O core modularization.&n; */
DECL|typedef|xfs_ioinit_t
r_typedef
r_int
(paren
op_star
id|xfs_ioinit_t
)paren
(paren
r_struct
id|vfs
op_star
comma
r_struct
id|xfs_mount_args
op_star
comma
r_int
)paren
suffix:semicolon
DECL|typedef|xfs_bmapi_t
r_typedef
r_int
(paren
op_star
id|xfs_bmapi_t
)paren
(paren
r_struct
id|xfs_trans
op_star
comma
r_void
op_star
comma
id|xfs_fileoff_t
comma
id|xfs_filblks_t
comma
r_int
comma
id|xfs_fsblock_t
op_star
comma
id|xfs_extlen_t
comma
r_struct
id|xfs_bmbt_irec
op_star
comma
r_int
op_star
comma
r_struct
id|xfs_bmap_free
op_star
)paren
suffix:semicolon
DECL|typedef|xfs_bmap_eof_t
r_typedef
r_int
(paren
op_star
id|xfs_bmap_eof_t
)paren
(paren
r_void
op_star
comma
id|xfs_fileoff_t
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
DECL|typedef|xfs_iomap_write_direct_t
r_typedef
r_int
(paren
op_star
id|xfs_iomap_write_direct_t
)paren
(paren
r_void
op_star
comma
id|loff_t
comma
r_int
comma
r_int
comma
r_struct
id|xfs_bmbt_irec
op_star
comma
r_int
op_star
comma
r_int
)paren
suffix:semicolon
DECL|typedef|xfs_iomap_write_delay_t
r_typedef
r_int
(paren
op_star
id|xfs_iomap_write_delay_t
)paren
(paren
r_void
op_star
comma
id|loff_t
comma
r_int
comma
r_int
comma
r_struct
id|xfs_bmbt_irec
op_star
comma
r_int
op_star
)paren
suffix:semicolon
DECL|typedef|xfs_iomap_write_allocate_t
r_typedef
r_int
(paren
op_star
id|xfs_iomap_write_allocate_t
)paren
(paren
r_void
op_star
comma
r_struct
id|xfs_bmbt_irec
op_star
comma
r_int
op_star
)paren
suffix:semicolon
DECL|typedef|xfs_iomap_write_unwritten_t
r_typedef
r_int
(paren
op_star
id|xfs_iomap_write_unwritten_t
)paren
(paren
r_void
op_star
comma
id|loff_t
comma
r_int
)paren
suffix:semicolon
DECL|typedef|xfs_lck_map_shared_t
r_typedef
id|uint
(paren
op_star
id|xfs_lck_map_shared_t
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|typedef|xfs_lock_t
r_typedef
r_void
(paren
op_star
id|xfs_lock_t
)paren
(paren
r_void
op_star
comma
id|uint
)paren
suffix:semicolon
DECL|typedef|xfs_lock_demote_t
r_typedef
r_void
(paren
op_star
id|xfs_lock_demote_t
)paren
(paren
r_void
op_star
comma
id|uint
)paren
suffix:semicolon
DECL|typedef|xfs_lock_nowait_t
r_typedef
r_int
(paren
op_star
id|xfs_lock_nowait_t
)paren
(paren
r_void
op_star
comma
id|uint
)paren
suffix:semicolon
DECL|typedef|xfs_unlk_t
r_typedef
r_void
(paren
op_star
id|xfs_unlk_t
)paren
(paren
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|typedef|xfs_size_t
r_typedef
id|xfs_fsize_t
(paren
op_star
id|xfs_size_t
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|typedef|xfs_iodone_t
r_typedef
id|xfs_fsize_t
(paren
op_star
id|xfs_iodone_t
)paren
(paren
r_struct
id|vfs
op_star
)paren
suffix:semicolon
DECL|struct|xfs_ioops
r_typedef
r_struct
id|xfs_ioops
(brace
DECL|member|xfs_ioinit
id|xfs_ioinit_t
id|xfs_ioinit
suffix:semicolon
DECL|member|xfs_bmapi_func
id|xfs_bmapi_t
id|xfs_bmapi_func
suffix:semicolon
DECL|member|xfs_bmap_eof_func
id|xfs_bmap_eof_t
id|xfs_bmap_eof_func
suffix:semicolon
DECL|member|xfs_iomap_write_direct
id|xfs_iomap_write_direct_t
id|xfs_iomap_write_direct
suffix:semicolon
DECL|member|xfs_iomap_write_delay
id|xfs_iomap_write_delay_t
id|xfs_iomap_write_delay
suffix:semicolon
DECL|member|xfs_iomap_write_allocate
id|xfs_iomap_write_allocate_t
id|xfs_iomap_write_allocate
suffix:semicolon
DECL|member|xfs_iomap_write_unwritten
id|xfs_iomap_write_unwritten_t
id|xfs_iomap_write_unwritten
suffix:semicolon
DECL|member|xfs_ilock
id|xfs_lock_t
id|xfs_ilock
suffix:semicolon
DECL|member|xfs_lck_map_shared
id|xfs_lck_map_shared_t
id|xfs_lck_map_shared
suffix:semicolon
DECL|member|xfs_ilock_demote
id|xfs_lock_demote_t
id|xfs_ilock_demote
suffix:semicolon
DECL|member|xfs_ilock_nowait
id|xfs_lock_nowait_t
id|xfs_ilock_nowait
suffix:semicolon
DECL|member|xfs_unlock
id|xfs_unlk_t
id|xfs_unlock
suffix:semicolon
DECL|member|xfs_size_func
id|xfs_size_t
id|xfs_size_func
suffix:semicolon
DECL|member|xfs_iodone
id|xfs_iodone_t
id|xfs_iodone
suffix:semicolon
DECL|typedef|xfs_ioops_t
)brace
id|xfs_ioops_t
suffix:semicolon
DECL|macro|XFS_IOINIT
mdefine_line|#define XFS_IOINIT(vfsp, args, flags) &bslash;&n;&t;(*(mp)-&gt;m_io_ops.xfs_ioinit)(vfsp, args, flags)
DECL|macro|XFS_BMAPI
mdefine_line|#define XFS_BMAPI(mp, trans,io,bno,len,f,first,tot,mval,nmap,flist)&t;&bslash;&n;&t;(*(mp)-&gt;m_io_ops.xfs_bmapi_func) &bslash;&n;&t;&t;(trans,(io)-&gt;io_obj,bno,len,f,first,tot,mval,nmap,flist)
DECL|macro|XFS_BMAP_EOF
mdefine_line|#define XFS_BMAP_EOF(mp, io, endoff, whichfork, eof) &bslash;&n;&t;(*(mp)-&gt;m_io_ops.xfs_bmap_eof_func) &bslash;&n;&t;&t;((io)-&gt;io_obj, endoff, whichfork, eof)
DECL|macro|XFS_IOMAP_WRITE_DIRECT
mdefine_line|#define XFS_IOMAP_WRITE_DIRECT(mp, io, offset, count, flags, mval, nmap, found)&bslash;&n;&t;(*(mp)-&gt;m_io_ops.xfs_iomap_write_direct) &bslash;&n;&t;&t;((io)-&gt;io_obj, offset, count, flags, mval, nmap, found)
DECL|macro|XFS_IOMAP_WRITE_DELAY
mdefine_line|#define XFS_IOMAP_WRITE_DELAY(mp, io, offset, count, flags, mval, nmap) &bslash;&n;&t;(*(mp)-&gt;m_io_ops.xfs_iomap_write_delay) &bslash;&n;&t;&t;((io)-&gt;io_obj, offset, count, flags, mval, nmap)
DECL|macro|XFS_IOMAP_WRITE_ALLOCATE
mdefine_line|#define XFS_IOMAP_WRITE_ALLOCATE(mp, io, mval, nmap) &bslash;&n;&t;(*(mp)-&gt;m_io_ops.xfs_iomap_write_allocate) &bslash;&n;&t;&t;((io)-&gt;io_obj, mval, nmap)
DECL|macro|XFS_IOMAP_WRITE_UNWRITTEN
mdefine_line|#define XFS_IOMAP_WRITE_UNWRITTEN(mp, io, offset, count) &bslash;&n;&t;(*(mp)-&gt;m_io_ops.xfs_iomap_write_unwritten) &bslash;&n;&t;&t;((io)-&gt;io_obj, offset, count)
DECL|macro|XFS_LCK_MAP_SHARED
mdefine_line|#define XFS_LCK_MAP_SHARED(mp, io) &bslash;&n;&t;(*(mp)-&gt;m_io_ops.xfs_lck_map_shared)((io)-&gt;io_obj)
DECL|macro|XFS_ILOCK
mdefine_line|#define XFS_ILOCK(mp, io, mode) &bslash;&n;&t;(*(mp)-&gt;m_io_ops.xfs_ilock)((io)-&gt;io_obj, mode)
DECL|macro|XFS_ILOCK_NOWAIT
mdefine_line|#define XFS_ILOCK_NOWAIT(mp, io, mode) &bslash;&n;&t;(*(mp)-&gt;m_io_ops.xfs_ilock_nowait)((io)-&gt;io_obj, mode)
DECL|macro|XFS_IUNLOCK
mdefine_line|#define XFS_IUNLOCK(mp, io, mode) &bslash;&n;&t;(*(mp)-&gt;m_io_ops.xfs_unlock)((io)-&gt;io_obj, mode)
DECL|macro|XFS_ILOCK_DEMOTE
mdefine_line|#define XFS_ILOCK_DEMOTE(mp, io, mode) &bslash;&n;&t;(*(mp)-&gt;m_io_ops.xfs_ilock_demote)((io)-&gt;io_obj, mode)
DECL|macro|XFS_SIZE
mdefine_line|#define XFS_SIZE(mp, io) &bslash;&n;&t;(*(mp)-&gt;m_io_ops.xfs_size_func)((io)-&gt;io_obj)
DECL|macro|XFS_IODONE
mdefine_line|#define XFS_IODONE(vfsp) &bslash;&n;&t;(*(mp)-&gt;m_io_ops.xfs_iodone)(vfsp)
DECL|struct|xfs_mount
r_typedef
r_struct
id|xfs_mount
(brace
DECL|member|m_bhv
id|bhv_desc_t
id|m_bhv
suffix:semicolon
multiline_comment|/* vfs xfs behavior */
DECL|member|m_tid
id|xfs_tid_t
id|m_tid
suffix:semicolon
multiline_comment|/* next unused tid for fs */
DECL|member|m_ail_lock
id|AIL_LOCK_T
id|m_ail_lock
suffix:semicolon
multiline_comment|/* fs AIL mutex */
DECL|member|m_ail
id|xfs_ail_entry_t
id|m_ail
suffix:semicolon
multiline_comment|/* fs active log item list */
DECL|member|m_ail_gen
id|uint
id|m_ail_gen
suffix:semicolon
multiline_comment|/* fs AIL generation count */
DECL|member|m_sb
id|xfs_sb_t
id|m_sb
suffix:semicolon
multiline_comment|/* copy of fs superblock */
DECL|member|m_sb_lock
id|lock_t
id|m_sb_lock
suffix:semicolon
multiline_comment|/* sb counter mutex */
DECL|member|m_sb_bp
r_struct
id|xfs_buf
op_star
id|m_sb_bp
suffix:semicolon
multiline_comment|/* buffer for superblock */
DECL|member|m_fsname
r_char
op_star
id|m_fsname
suffix:semicolon
multiline_comment|/* filesystem name */
DECL|member|m_fsname_len
r_int
id|m_fsname_len
suffix:semicolon
multiline_comment|/* strlen of fs name */
DECL|member|m_bsize
r_int
id|m_bsize
suffix:semicolon
multiline_comment|/* fs logical block size */
DECL|member|m_agfrotor
id|xfs_agnumber_t
id|m_agfrotor
suffix:semicolon
multiline_comment|/* last ag where space found */
DECL|member|m_agirotor
id|xfs_agnumber_t
id|m_agirotor
suffix:semicolon
multiline_comment|/* last ag dir inode alloced */
DECL|member|m_agirotor_lock
id|lock_t
id|m_agirotor_lock
suffix:semicolon
multiline_comment|/* .. and lock protecting it */
DECL|member|m_maxagi
id|xfs_agnumber_t
id|m_maxagi
suffix:semicolon
multiline_comment|/* highest inode alloc group */
DECL|member|m_ihsize
id|uint
id|m_ihsize
suffix:semicolon
multiline_comment|/* size of next field */
DECL|member|m_ihash
r_struct
id|xfs_ihash
op_star
id|m_ihash
suffix:semicolon
multiline_comment|/* fs private inode hash table*/
DECL|member|m_inodes
r_struct
id|xfs_inode
op_star
id|m_inodes
suffix:semicolon
multiline_comment|/* active inode list */
DECL|member|m_del_inodes
r_struct
id|list_head
id|m_del_inodes
suffix:semicolon
multiline_comment|/* inodes to reclaim */
DECL|member|m_ilock
id|mutex_t
id|m_ilock
suffix:semicolon
multiline_comment|/* inode list mutex */
DECL|member|m_ireclaims
id|uint
id|m_ireclaims
suffix:semicolon
multiline_comment|/* count of calls to reclaim*/
DECL|member|m_readio_log
id|uint
id|m_readio_log
suffix:semicolon
multiline_comment|/* min read size log bytes */
DECL|member|m_readio_blocks
id|uint
id|m_readio_blocks
suffix:semicolon
multiline_comment|/* min read size blocks */
DECL|member|m_writeio_log
id|uint
id|m_writeio_log
suffix:semicolon
multiline_comment|/* min write size log bytes */
DECL|member|m_writeio_blocks
id|uint
id|m_writeio_blocks
suffix:semicolon
multiline_comment|/* min write size blocks */
DECL|member|m_log
r_struct
id|log
op_star
id|m_log
suffix:semicolon
multiline_comment|/* log specific stuff */
DECL|member|m_logbufs
r_int
id|m_logbufs
suffix:semicolon
multiline_comment|/* number of log buffers */
DECL|member|m_logbsize
r_int
id|m_logbsize
suffix:semicolon
multiline_comment|/* size of each log buffer */
DECL|member|m_rsumlevels
id|uint
id|m_rsumlevels
suffix:semicolon
multiline_comment|/* rt summary levels */
DECL|member|m_rsumsize
id|uint
id|m_rsumsize
suffix:semicolon
multiline_comment|/* size of rt summary, bytes */
DECL|member|m_rbmip
r_struct
id|xfs_inode
op_star
id|m_rbmip
suffix:semicolon
multiline_comment|/* pointer to bitmap inode */
DECL|member|m_rsumip
r_struct
id|xfs_inode
op_star
id|m_rsumip
suffix:semicolon
multiline_comment|/* pointer to summary inode */
DECL|member|m_rootip
r_struct
id|xfs_inode
op_star
id|m_rootip
suffix:semicolon
multiline_comment|/* pointer to root directory */
DECL|member|m_quotainfo
r_struct
id|xfs_quotainfo
op_star
id|m_quotainfo
suffix:semicolon
multiline_comment|/* disk quota information */
DECL|member|m_ddev_targp
id|xfs_buftarg_t
op_star
id|m_ddev_targp
suffix:semicolon
multiline_comment|/* saves taking the address */
DECL|member|m_logdev_targp
id|xfs_buftarg_t
op_star
id|m_logdev_targp
suffix:semicolon
multiline_comment|/* ptr to log device */
DECL|member|m_rtdev_targp
id|xfs_buftarg_t
op_star
id|m_rtdev_targp
suffix:semicolon
multiline_comment|/* ptr to rt device */
DECL|macro|m_dev
mdefine_line|#define m_dev&t;&t;m_ddev_targp-&gt;pbr_dev
DECL|member|m_dircook_elog
id|__uint8_t
id|m_dircook_elog
suffix:semicolon
multiline_comment|/* log d-cookie entry bits */
DECL|member|m_blkbit_log
id|__uint8_t
id|m_blkbit_log
suffix:semicolon
multiline_comment|/* blocklog + NBBY */
DECL|member|m_blkbb_log
id|__uint8_t
id|m_blkbb_log
suffix:semicolon
multiline_comment|/* blocklog - BBSHIFT */
DECL|member|m_agno_log
id|__uint8_t
id|m_agno_log
suffix:semicolon
multiline_comment|/* log #ag&squot;s */
DECL|member|m_agino_log
id|__uint8_t
id|m_agino_log
suffix:semicolon
multiline_comment|/* #bits for agino in inum */
DECL|member|m_nreadaheads
id|__uint8_t
id|m_nreadaheads
suffix:semicolon
multiline_comment|/* #readahead buffers */
DECL|member|m_inode_cluster_size
id|__uint16_t
id|m_inode_cluster_size
suffix:semicolon
multiline_comment|/* min inode buf size */
DECL|member|m_blockmask
id|uint
id|m_blockmask
suffix:semicolon
multiline_comment|/* sb_blocksize-1 */
DECL|member|m_blockwsize
id|uint
id|m_blockwsize
suffix:semicolon
multiline_comment|/* sb_blocksize in words */
DECL|member|m_blockwmask
id|uint
id|m_blockwmask
suffix:semicolon
multiline_comment|/* blockwsize-1 */
DECL|member|m_alloc_mxr
id|uint
id|m_alloc_mxr
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* XFS_ALLOC_BLOCK_MAXRECS */
DECL|member|m_alloc_mnr
id|uint
id|m_alloc_mnr
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* XFS_ALLOC_BLOCK_MINRECS */
DECL|member|m_bmap_dmxr
id|uint
id|m_bmap_dmxr
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* XFS_BMAP_BLOCK_DMAXRECS */
DECL|member|m_bmap_dmnr
id|uint
id|m_bmap_dmnr
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* XFS_BMAP_BLOCK_DMINRECS */
DECL|member|m_inobt_mxr
id|uint
id|m_inobt_mxr
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* XFS_INOBT_BLOCK_MAXRECS */
DECL|member|m_inobt_mnr
id|uint
id|m_inobt_mnr
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* XFS_INOBT_BLOCK_MINRECS */
DECL|member|m_ag_maxlevels
id|uint
id|m_ag_maxlevels
suffix:semicolon
multiline_comment|/* XFS_AG_MAXLEVELS */
DECL|member|m_bm_maxlevels
id|uint
id|m_bm_maxlevels
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* XFS_BM_MAXLEVELS */
DECL|member|m_in_maxlevels
id|uint
id|m_in_maxlevels
suffix:semicolon
multiline_comment|/* XFS_IN_MAXLEVELS */
DECL|member|m_perag
r_struct
id|xfs_perag
op_star
id|m_perag
suffix:semicolon
multiline_comment|/* per-ag accounting info */
DECL|member|m_peraglock
r_struct
id|rw_semaphore
id|m_peraglock
suffix:semicolon
multiline_comment|/* lock for m_perag (pointer) */
DECL|member|m_growlock
id|sema_t
id|m_growlock
suffix:semicolon
multiline_comment|/* growfs mutex */
DECL|member|m_fixedfsid
r_int
id|m_fixedfsid
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* unchanged for life of FS */
DECL|member|m_dmevmask
id|uint
id|m_dmevmask
suffix:semicolon
multiline_comment|/* DMI events for this FS */
DECL|member|m_flags
id|uint
id|m_flags
suffix:semicolon
multiline_comment|/* global mount flags */
DECL|member|m_attroffset
id|uint
id|m_attroffset
suffix:semicolon
multiline_comment|/* inode attribute offset */
DECL|member|m_dir_node_ents
id|uint
id|m_dir_node_ents
suffix:semicolon
multiline_comment|/* #entries in a dir danode */
DECL|member|m_attr_node_ents
id|uint
id|m_attr_node_ents
suffix:semicolon
multiline_comment|/* #entries in attr danode */
DECL|member|m_ialloc_inos
r_int
id|m_ialloc_inos
suffix:semicolon
multiline_comment|/* inodes in inode allocation */
DECL|member|m_ialloc_blks
r_int
id|m_ialloc_blks
suffix:semicolon
multiline_comment|/* blocks in inode allocation */
DECL|member|m_litino
r_int
id|m_litino
suffix:semicolon
multiline_comment|/* size of inode union area */
DECL|member|m_inoalign_mask
r_int
id|m_inoalign_mask
suffix:semicolon
multiline_comment|/* mask sb_inoalignmt if used */
DECL|member|m_qflags
id|uint
id|m_qflags
suffix:semicolon
multiline_comment|/* quota status flags */
DECL|member|m_reservations
id|xfs_trans_reservations_t
id|m_reservations
suffix:semicolon
multiline_comment|/* precomputed res values */
DECL|member|m_maxicount
id|__uint64_t
id|m_maxicount
suffix:semicolon
multiline_comment|/* maximum inode count */
DECL|member|m_maxioffset
id|__uint64_t
id|m_maxioffset
suffix:semicolon
multiline_comment|/* maximum inode offset */
DECL|member|m_resblks
id|__uint64_t
id|m_resblks
suffix:semicolon
multiline_comment|/* total reserved blocks */
DECL|member|m_resblks_avail
id|__uint64_t
id|m_resblks_avail
suffix:semicolon
multiline_comment|/* available reserved blocks */
macro_line|#if XFS_BIG_INUMS
DECL|member|m_inoadd
id|xfs_ino_t
id|m_inoadd
suffix:semicolon
multiline_comment|/* add value for ino64_offset */
macro_line|#endif
DECL|member|m_dalign
r_int
id|m_dalign
suffix:semicolon
multiline_comment|/* stripe unit */
DECL|member|m_swidth
r_int
id|m_swidth
suffix:semicolon
multiline_comment|/* stripe width */
DECL|member|m_sinoalign
r_int
id|m_sinoalign
suffix:semicolon
multiline_comment|/* stripe unit inode alignmnt */
DECL|member|m_attr_magicpct
r_int
id|m_attr_magicpct
suffix:semicolon
multiline_comment|/* 37% of the blocksize */
DECL|member|m_dir_magicpct
r_int
id|m_dir_magicpct
suffix:semicolon
multiline_comment|/* 37% of the dir blocksize */
DECL|member|m_mk_sharedro
id|__uint8_t
id|m_mk_sharedro
suffix:semicolon
multiline_comment|/* mark shared ro on unmount */
DECL|member|m_inode_quiesce
id|__uint8_t
id|m_inode_quiesce
suffix:semicolon
multiline_comment|/* call quiesce on new inodes.&n;&t;&t;&t;&t;&t;&t;   field governed by m_ilock */
DECL|member|m_sectbb_log
id|__uint8_t
id|m_sectbb_log
suffix:semicolon
multiline_comment|/* sectlog - BBSHIFT */
DECL|member|m_dirversion
id|__uint8_t
id|m_dirversion
suffix:semicolon
multiline_comment|/* 1 or 2 */
DECL|member|m_dirops
id|xfs_dirops_t
id|m_dirops
suffix:semicolon
multiline_comment|/* table of dir funcs */
DECL|member|m_dirblksize
r_int
id|m_dirblksize
suffix:semicolon
multiline_comment|/* directory block sz--bytes */
DECL|member|m_dirblkfsbs
r_int
id|m_dirblkfsbs
suffix:semicolon
multiline_comment|/* directory block sz--fsbs */
DECL|member|m_dirdatablk
id|xfs_dablk_t
id|m_dirdatablk
suffix:semicolon
multiline_comment|/* blockno of dir data v2 */
DECL|member|m_dirleafblk
id|xfs_dablk_t
id|m_dirleafblk
suffix:semicolon
multiline_comment|/* blockno of dir non-data v2 */
DECL|member|m_dirfreeblk
id|xfs_dablk_t
id|m_dirfreeblk
suffix:semicolon
multiline_comment|/* blockno of dirfreeindex v2 */
DECL|member|m_chsize
id|uint
id|m_chsize
suffix:semicolon
multiline_comment|/* size of next field */
DECL|member|m_chash
r_struct
id|xfs_chash
op_star
id|m_chash
suffix:semicolon
multiline_comment|/* fs private inode per-cluster&n;&t;&t;&t;&t;&t;&t; * hash table */
DECL|member|m_dm_ops
r_struct
id|xfs_dmops
id|m_dm_ops
suffix:semicolon
multiline_comment|/* vector of DMI ops */
DECL|member|m_qm_ops
r_struct
id|xfs_qmops
id|m_qm_ops
suffix:semicolon
multiline_comment|/* vector of XQM ops */
DECL|member|m_io_ops
r_struct
id|xfs_ioops
id|m_io_ops
suffix:semicolon
multiline_comment|/* vector of I/O ops */
DECL|member|m_active_trans
id|atomic_t
id|m_active_trans
suffix:semicolon
multiline_comment|/* number trans frozen */
DECL|typedef|xfs_mount_t
)brace
id|xfs_mount_t
suffix:semicolon
multiline_comment|/*&n; * Flags for m_flags.&n; */
DECL|macro|XFS_MOUNT_WSYNC
mdefine_line|#define&t;XFS_MOUNT_WSYNC&t;&t;0x00000001&t;/* for nfs - all metadata ops&n;&t;&t;&t;&t;&t;&t;   must be synchronous except&n;&t;&t;&t;&t;&t;&t;   for space allocations */
DECL|macro|XFS_MOUNT_INO64
mdefine_line|#define&t;XFS_MOUNT_INO64&t;&t;0x00000002
multiline_comment|/* 0x00000004&t;-- currently unused */
multiline_comment|/* 0x00000008&t;-- currently unused */
DECL|macro|XFS_MOUNT_FS_SHUTDOWN
mdefine_line|#define XFS_MOUNT_FS_SHUTDOWN&t;0x00000010&t;/* atomic stop of all filesystem&n;&t;&t;&t;&t;&t;&t;   operations, typically for&n;&t;&t;&t;&t;&t;&t;   disk errors in metadata */
DECL|macro|XFS_MOUNT_NOATIME
mdefine_line|#define XFS_MOUNT_NOATIME&t;0x00000020&t;/* don&squot;t modify inode access&n;&t;&t;&t;&t;&t;&t;   times on reads */
DECL|macro|XFS_MOUNT_RETERR
mdefine_line|#define XFS_MOUNT_RETERR&t;0x00000040      /* return alignment errors to&n;&t;&t;&t;&t;&t;&t;   user */
DECL|macro|XFS_MOUNT_NOALIGN
mdefine_line|#define XFS_MOUNT_NOALIGN&t;0x00000080&t;/* turn off stripe alignment&n;&t;&t;&t;&t;&t;&t;   allocations */
multiline_comment|/* 0x00000100&t;-- currently unused */
multiline_comment|/*&t;0x00000200&t;-- currently unused */
DECL|macro|XFS_MOUNT_NORECOVERY
mdefine_line|#define XFS_MOUNT_NORECOVERY&t;0x00000400&t;/* no recovery - dirty fs */
DECL|macro|XFS_MOUNT_SHARED
mdefine_line|#define XFS_MOUNT_SHARED&t;0x00000800&t;/* shared mount */
DECL|macro|XFS_MOUNT_DFLT_IOSIZE
mdefine_line|#define XFS_MOUNT_DFLT_IOSIZE&t;0x00001000&t;/* set default i/o size */
DECL|macro|XFS_MOUNT_OSYNCISOSYNC
mdefine_line|#define XFS_MOUNT_OSYNCISOSYNC&t;0x00002000&t;/* o_sync is REALLY o_sync */
multiline_comment|/* osyncisdsync is now default*/
DECL|macro|XFS_MOUNT_32BITINODES
mdefine_line|#define XFS_MOUNT_32BITINODES&t;0x00004000&t;/* do not create inodes above&n;&t;&t;&t;&t;&t;&t; * 32 bits in size */
DECL|macro|XFS_MOUNT_32BITINOOPT
mdefine_line|#define XFS_MOUNT_32BITINOOPT&t;0x00008000&t;/* saved mount option state */
DECL|macro|XFS_MOUNT_NOUUID
mdefine_line|#define XFS_MOUNT_NOUUID&t;0x00010000&t;/* ignore uuid during mount */
DECL|macro|XFS_MOUNT_NOLOGFLUSH
mdefine_line|#define XFS_MOUNT_NOLOGFLUSH&t;0x00020000
DECL|macro|XFS_MOUNT_IDELETE
mdefine_line|#define XFS_MOUNT_IDELETE&t;0x00040000&t;/* delete empty inode clusters*/
DECL|macro|XFS_MOUNT_SWALLOC
mdefine_line|#define XFS_MOUNT_SWALLOC&t;0x00080000&t;/* turn on stripe width&n;&t;&t;&t;&t;&t;&t; * allocation */
multiline_comment|/*&n; * Default minimum read and write sizes.&n; */
DECL|macro|XFS_READIO_LOG_LARGE
mdefine_line|#define XFS_READIO_LOG_LARGE&t;16
DECL|macro|XFS_WRITEIO_LOG_LARGE
mdefine_line|#define XFS_WRITEIO_LOG_LARGE&t;16
multiline_comment|/*&n; * Max and min values for UIO and mount-option defined I/O sizes;&n; * min value can&squot;t be less than a page.  Currently unused.&n; */
DECL|macro|XFS_MAX_IO_LOG
mdefine_line|#define XFS_MAX_IO_LOG&t;&t;16&t;/* 64K */
DECL|macro|XFS_MIN_IO_LOG
mdefine_line|#define XFS_MIN_IO_LOG&t;&t;PAGE_SHIFT
multiline_comment|/*&n; * Synchronous read and write sizes.  This should be&n; * better for NFSv2 wsync filesystems.&n; */
DECL|macro|XFS_WSYNC_READIO_LOG
mdefine_line|#define&t;XFS_WSYNC_READIO_LOG&t;15&t;/* 32K */
DECL|macro|XFS_WSYNC_WRITEIO_LOG
mdefine_line|#define&t;XFS_WSYNC_WRITEIO_LOG&t;14&t;/* 16K */
DECL|macro|XFS_MAXIOFFSET
mdefine_line|#define XFS_MAXIOFFSET(mp)&t;((mp)-&gt;m_maxioffset)
DECL|macro|XFS_FORCED_SHUTDOWN
mdefine_line|#define XFS_FORCED_SHUTDOWN(mp)&t;((mp)-&gt;m_flags &amp; XFS_MOUNT_FS_SHUTDOWN)
DECL|macro|xfs_force_shutdown
mdefine_line|#define xfs_force_shutdown(m,f)&t;&bslash;&n;&t;VFS_FORCE_SHUTDOWN((XFS_MTOVFS(m)), f, __FILE__, __LINE__)
multiline_comment|/*&n; * Flags sent to xfs_force_shutdown.&n; */
DECL|macro|XFS_METADATA_IO_ERROR
mdefine_line|#define XFS_METADATA_IO_ERROR&t;0x1
DECL|macro|XFS_LOG_IO_ERROR
mdefine_line|#define XFS_LOG_IO_ERROR&t;0x2
DECL|macro|XFS_FORCE_UMOUNT
mdefine_line|#define XFS_FORCE_UMOUNT&t;0x4
DECL|macro|XFS_CORRUPT_INCORE
mdefine_line|#define XFS_CORRUPT_INCORE&t;0x8&t;/* Corrupt in-memory data structures */
DECL|macro|XFS_SHUTDOWN_REMOTE_REQ
mdefine_line|#define XFS_SHUTDOWN_REMOTE_REQ 0x10&t;/* Shutdown came from remote cell */
multiline_comment|/*&n; * xflags for xfs_syncsub&n; */
DECL|macro|XFS_XSYNC_RELOC
mdefine_line|#define XFS_XSYNC_RELOC&t;&t;0x01
multiline_comment|/*&n; * Flags for xfs_mountfs&n; */
DECL|macro|XFS_MFSI_SECOND
mdefine_line|#define XFS_MFSI_SECOND&t;&t;0x01&t;/* Secondary mount -- skip stuff */
DECL|macro|XFS_MFSI_CLIENT
mdefine_line|#define XFS_MFSI_CLIENT&t;&t;0x02&t;/* Is a client -- skip lots of stuff */
DECL|macro|XFS_MFSI_NOUNLINK
mdefine_line|#define XFS_MFSI_NOUNLINK&t;0x08&t;/* Skip unlinked inode processing in */
multiline_comment|/* log recovery */
DECL|macro|XFS_MFSI_NO_QUOTACHECK
mdefine_line|#define XFS_MFSI_NO_QUOTACHECK&t;0x10&t;/* Skip quotacheck processing */
multiline_comment|/*&n; * Macros for getting from mount to vfs and back.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_MTOVFS)
r_struct
id|vfs
op_star
id|xfs_mtovfs
c_func
(paren
id|xfs_mount_t
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_MTOVFS
mdefine_line|#define&t;XFS_MTOVFS(mp)&t;&t;xfs_mtovfs(mp)
macro_line|#else
DECL|macro|XFS_MTOVFS
mdefine_line|#define&t;XFS_MTOVFS(mp)&t;&t;(bhvtovfs(&amp;(mp)-&gt;m_bhv))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BHVTOM)
id|xfs_mount_t
op_star
id|xfs_bhvtom
c_func
(paren
id|bhv_desc_t
op_star
id|bdp
)paren
suffix:semicolon
DECL|macro|XFS_BHVTOM
mdefine_line|#define&t;XFS_BHVTOM(bdp)&t;xfs_bhvtom(bdp)
macro_line|#else
DECL|macro|XFS_BHVTOM
mdefine_line|#define XFS_BHVTOM(bdp)&t;&t;((xfs_mount_t *)BHV_PDATA(bdp))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_VFSTOM)
id|xfs_mount_t
op_star
id|xfs_vfstom
c_func
(paren
id|vfs_t
op_star
id|vfs
)paren
suffix:semicolon
DECL|macro|XFS_VFSTOM
mdefine_line|#define XFS_VFSTOM(vfs) xfs_vfstom(vfs)
macro_line|#else
DECL|macro|XFS_VFSTOM
mdefine_line|#define XFS_VFSTOM(vfs)&t;&t;&bslash;&n;&t;(XFS_BHVTOM(bhv_lookup(VFS_BHVHEAD(vfs), &amp;xfs_vfsops)))
macro_line|#endif
multiline_comment|/*&n; * Moved here from xfs_ag.h to avoid reordering header files&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DADDR_TO_AGNO)
id|xfs_agnumber_t
id|xfs_daddr_to_agno
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_daddr_t
id|d
)paren
suffix:semicolon
DECL|macro|XFS_DADDR_TO_AGNO
mdefine_line|#define XFS_DADDR_TO_AGNO(mp,d)         xfs_daddr_to_agno(mp,d)
macro_line|#else
DECL|function|XFS_DADDR_TO_AGNO
r_static
r_inline
id|xfs_agnumber_t
id|XFS_DADDR_TO_AGNO
c_func
(paren
id|xfs_mount_t
op_star
id|mp
comma
id|xfs_daddr_t
id|d
)paren
(brace
id|d
op_assign
id|XFS_BB_TO_FSBT
c_func
(paren
id|mp
comma
id|d
)paren
suffix:semicolon
id|do_div
c_func
(paren
id|d
comma
id|mp-&gt;m_sb.sb_agblocks
)paren
suffix:semicolon
r_return
(paren
id|xfs_agnumber_t
)paren
id|d
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DADDR_TO_AGBNO)
id|xfs_agblock_t
id|xfs_daddr_to_agbno
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_daddr_t
id|d
)paren
suffix:semicolon
DECL|macro|XFS_DADDR_TO_AGBNO
mdefine_line|#define XFS_DADDR_TO_AGBNO(mp,d)        xfs_daddr_to_agbno(mp,d)
macro_line|#else
DECL|function|XFS_DADDR_TO_AGBNO
r_static
r_inline
id|xfs_agblock_t
id|XFS_DADDR_TO_AGBNO
c_func
(paren
id|xfs_mount_t
op_star
id|mp
comma
id|xfs_daddr_t
id|d
)paren
(brace
id|d
op_assign
id|XFS_BB_TO_FSBT
c_func
(paren
id|mp
comma
id|d
)paren
suffix:semicolon
r_return
(paren
id|xfs_agblock_t
)paren
id|do_div
c_func
(paren
id|d
comma
id|mp-&gt;m_sb.sb_agblocks
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * This structure is for use by the xfs_mod_incore_sb_batch() routine.&n; */
DECL|struct|xfs_mod_sb
r_typedef
r_struct
id|xfs_mod_sb
(brace
DECL|member|msb_field
id|xfs_sb_field_t
id|msb_field
suffix:semicolon
multiline_comment|/* Field to modify, see below */
DECL|member|msb_delta
r_int
id|msb_delta
suffix:semicolon
multiline_comment|/* Change to make to specified field */
DECL|typedef|xfs_mod_sb_t
)brace
id|xfs_mod_sb_t
suffix:semicolon
DECL|macro|XFS_MOUNT_ILOCK
mdefine_line|#define&t;XFS_MOUNT_ILOCK(mp)&t;mutex_lock(&amp;((mp)-&gt;m_ilock), PINOD)
DECL|macro|XFS_MOUNT_IUNLOCK
mdefine_line|#define&t;XFS_MOUNT_IUNLOCK(mp)&t;mutex_unlock(&amp;((mp)-&gt;m_ilock))
DECL|macro|XFS_SB_LOCK
mdefine_line|#define&t;XFS_SB_LOCK(mp)&t;&t;mutex_spinlock(&amp;(mp)-&gt;m_sb_lock)
DECL|macro|XFS_SB_UNLOCK
mdefine_line|#define&t;XFS_SB_UNLOCK(mp,s)&t;mutex_spinunlock(&amp;(mp)-&gt;m_sb_lock,(s))
r_extern
id|xfs_mount_t
op_star
id|xfs_mount_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|xfs_mod_sb
c_func
(paren
id|xfs_trans_t
op_star
comma
id|__int64_t
)paren
suffix:semicolon
r_extern
r_void
id|xfs_mount_free
c_func
(paren
id|xfs_mount_t
op_star
id|mp
comma
r_int
id|remove_bhv
)paren
suffix:semicolon
r_extern
r_int
id|xfs_mountfs
c_func
(paren
r_struct
id|vfs
op_star
comma
id|xfs_mount_t
op_star
id|mp
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|xfs_unmountfs
c_func
(paren
id|xfs_mount_t
op_star
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_unmountfs_wait
c_func
(paren
id|xfs_mount_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_unmountfs_close
c_func
(paren
id|xfs_mount_t
op_star
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_unmountfs_writesb
c_func
(paren
id|xfs_mount_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_unmount_flush
c_func
(paren
id|xfs_mount_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|xfs_mod_incore_sb
c_func
(paren
id|xfs_mount_t
op_star
comma
id|xfs_sb_field_t
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|xfs_mod_incore_sb_batch
c_func
(paren
id|xfs_mount_t
op_star
comma
id|xfs_mod_sb_t
op_star
comma
id|uint
comma
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|xfs_buf
op_star
id|xfs_getsb
c_func
(paren
id|xfs_mount_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|xfs_readsb
c_func
(paren
id|xfs_mount_t
op_star
id|mp
)paren
suffix:semicolon
r_extern
r_void
id|xfs_freesb
c_func
(paren
id|xfs_mount_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_do_force_shutdown
c_func
(paren
id|bhv_desc_t
op_star
comma
r_int
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|xfs_syncsub
c_func
(paren
id|xfs_mount_t
op_star
comma
r_int
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
id|xfs_agnumber_t
id|xfs_initialize_perag
c_func
(paren
id|xfs_mount_t
op_star
comma
id|xfs_agnumber_t
)paren
suffix:semicolon
r_extern
r_void
id|xfs_xlatesb
c_func
(paren
r_void
op_star
comma
r_struct
id|xfs_sb
op_star
comma
r_int
comma
id|xfs_arch_t
comma
id|__int64_t
)paren
suffix:semicolon
r_extern
r_struct
id|vfsops
id|xfs_vfsops
suffix:semicolon
r_extern
r_struct
id|vnodeops
id|xfs_vnodeops
suffix:semicolon
r_extern
r_struct
id|xfs_dmops
id|xfs_dmcore_stub
suffix:semicolon
r_extern
r_struct
id|xfs_qmops
id|xfs_qmcore_stub
suffix:semicolon
r_extern
r_struct
id|xfs_ioops
id|xfs_iocore_xfs
suffix:semicolon
r_extern
r_int
id|xfs_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|xfs_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* __XFS_MOUNT_H__ */
eof
