multiline_comment|/*&n; * Copyright (c) 2000-2004 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#include &quot;xfs.h&quot;
macro_line|#include &quot;xfs_inum.h&quot;
macro_line|#include &quot;xfs_log.h&quot;
macro_line|#include &quot;xfs_clnt.h&quot;
macro_line|#include &quot;xfs_trans.h&quot;
macro_line|#include &quot;xfs_sb.h&quot;
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
macro_line|#include &quot;xfs_utils.h&quot;
macro_line|#include &quot;xfs_version.h&quot;
macro_line|#include &lt;linux/namei.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mount.h&gt;
macro_line|#include &lt;linux/suspend.h&gt;
DECL|variable|linvfs_qops
id|STATIC
r_struct
id|quotactl_ops
id|linvfs_qops
suffix:semicolon
DECL|variable|linvfs_sops
id|STATIC
r_struct
id|super_operations
id|linvfs_sops
suffix:semicolon
DECL|variable|linvfs_export_ops
id|STATIC
r_struct
id|export_operations
id|linvfs_export_ops
suffix:semicolon
DECL|variable|linvfs_inode_cachep
id|STATIC
id|kmem_cache_t
op_star
id|linvfs_inode_cachep
suffix:semicolon
id|STATIC
r_struct
id|xfs_mount_args
op_star
DECL|function|xfs_args_allocate
id|xfs_args_allocate
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|xfs_mount_args
op_star
id|args
suffix:semicolon
id|args
op_assign
id|kmem_zalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|xfs_mount_args
)paren
comma
id|KM_SLEEP
)paren
suffix:semicolon
id|args-&gt;logbufs
op_assign
id|args-&gt;logbufsize
op_assign
op_minus
l_int|1
suffix:semicolon
id|strncpy
c_func
(paren
id|args-&gt;fsname
comma
id|sb-&gt;s_id
comma
id|MAXNAMELEN
)paren
suffix:semicolon
multiline_comment|/* Copy the already-parsed mount(2) flags we&squot;re interested in */
r_if
c_cond
(paren
id|sb-&gt;s_flags
op_amp
id|MS_NOATIME
)paren
id|args-&gt;flags
op_or_assign
id|XFSMNT_NOATIME
suffix:semicolon
multiline_comment|/* Default to 32 bit inodes on Linux all the time */
id|args-&gt;flags
op_or_assign
id|XFSMNT_32BITINODES
suffix:semicolon
r_return
id|args
suffix:semicolon
)brace
id|__uint64_t
DECL|function|xfs_max_file_offset
id|xfs_max_file_offset
c_func
(paren
r_int
r_int
id|blockshift
)paren
(brace
r_int
r_int
id|pagefactor
op_assign
l_int|1
suffix:semicolon
r_int
r_int
id|bitshift
op_assign
id|BITS_PER_LONG
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Figure out maximum filesize, on Linux this can depend on&n;&t; * the filesystem blocksize (on 32 bit platforms).&n;&t; * __block_prepare_write does this in an [unsigned] long...&n;&t; *      page-&gt;index &lt;&lt; (PAGE_CACHE_SHIFT - bbits)&n;&t; * So, for page sized blocks (4K on 32 bit platforms),&n;&t; * this wraps at around 8Tb (hence MAX_LFS_FILESIZE which is&n;&t; *      (((u64)PAGE_CACHE_SIZE &lt;&lt; (BITS_PER_LONG-1))-1)&n;&t; * but for smaller blocksizes it is less (bbits = log2 bsize).&n;&t; * Note1: get_block_t takes a long (implicit cast from above)&n;&t; * Note2: The Large Block Device (LBD and HAVE_SECTOR_T) patch&n;&t; * can optionally convert the [unsigned] long from above into&n;&t; * an [unsigned] long long.&n;&t; */
macro_line|#if BITS_PER_LONG == 32
macro_line|# if defined(CONFIG_LBD)
id|ASSERT
c_func
(paren
r_sizeof
(paren
id|sector_t
)paren
op_eq
l_int|8
)paren
suffix:semicolon
id|pagefactor
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|bitshift
op_assign
id|BITS_PER_LONG
suffix:semicolon
macro_line|# else
id|pagefactor
op_assign
id|PAGE_CACHE_SIZE
op_rshift
(paren
id|PAGE_CACHE_SHIFT
op_minus
id|blockshift
)paren
suffix:semicolon
macro_line|# endif
macro_line|#endif
r_return
(paren
(paren
(paren
id|__uint64_t
)paren
id|pagefactor
)paren
op_lshift
id|bitshift
)paren
op_minus
l_int|1
suffix:semicolon
)brace
id|STATIC
id|__inline__
r_void
DECL|function|xfs_set_inodeops
id|xfs_set_inodeops
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|vnode_t
op_star
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vp-&gt;v_type
op_eq
id|VNON
)paren
(brace
id|make_bad_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|linvfs_file_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|linvfs_file_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|linvfs_aops
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|linvfs_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|linvfs_dir_operations
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|linvfs_symlink_inode_operations
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_blocks
)paren
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|linvfs_aops
suffix:semicolon
)brace
r_else
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|linvfs_file_inode_operations
suffix:semicolon
id|init_special_inode
c_func
(paren
id|inode
comma
id|inode-&gt;i_mode
comma
id|inode-&gt;i_rdev
)paren
suffix:semicolon
)brace
)brace
id|STATIC
id|__inline__
r_void
DECL|function|xfs_revalidate_inode
id|xfs_revalidate_inode
c_func
(paren
id|xfs_mount_t
op_star
id|mp
comma
id|vnode_t
op_star
id|vp
comma
id|xfs_inode_t
op_star
id|ip
)paren
(brace
r_struct
id|inode
op_star
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
(paren
id|ip-&gt;i_d.di_mode
op_amp
id|MODEMASK
)paren
op_or
id|VTTOIF
c_func
(paren
id|vp-&gt;v_type
)paren
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
id|ip-&gt;i_d.di_nlink
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|ip-&gt;i_d.di_uid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|ip-&gt;i_d.di_gid
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
l_int|1
op_lshift
id|vp-&gt;v_type
)paren
op_amp
(paren
(paren
l_int|1
op_lshift
id|VBLK
)paren
op_or
(paren
l_int|1
op_lshift
id|VCHR
)paren
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|inode-&gt;i_rdev
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|xfs_dev_t
id|dev
op_assign
id|ip-&gt;i_df.if_u2.if_rdev
suffix:semicolon
id|inode-&gt;i_rdev
op_assign
id|MKDEV
c_func
(paren
id|sysv_major
c_func
(paren
id|dev
)paren
op_amp
l_int|0x1ff
comma
id|sysv_minor
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
)brace
id|inode-&gt;i_blksize
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|inode-&gt;i_generation
op_assign
id|ip-&gt;i_d.di_gen
suffix:semicolon
id|i_size_write
c_func
(paren
id|inode
comma
id|ip-&gt;i_d.di_size
)paren
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
id|XFS_FSB_TO_BB
c_func
(paren
id|mp
comma
id|ip-&gt;i_d.di_nblocks
op_plus
id|ip-&gt;i_delayed_blks
)paren
suffix:semicolon
id|inode-&gt;i_atime.tv_sec
op_assign
id|ip-&gt;i_d.di_atime.t_sec
suffix:semicolon
id|inode-&gt;i_atime.tv_nsec
op_assign
id|ip-&gt;i_d.di_atime.t_nsec
suffix:semicolon
id|inode-&gt;i_mtime.tv_sec
op_assign
id|ip-&gt;i_d.di_mtime.t_sec
suffix:semicolon
id|inode-&gt;i_mtime.tv_nsec
op_assign
id|ip-&gt;i_d.di_mtime.t_nsec
suffix:semicolon
id|inode-&gt;i_ctime.tv_sec
op_assign
id|ip-&gt;i_d.di_ctime.t_sec
suffix:semicolon
id|inode-&gt;i_ctime.tv_nsec
op_assign
id|ip-&gt;i_d.di_ctime.t_nsec
suffix:semicolon
r_if
c_cond
(paren
id|ip-&gt;i_d.di_flags
op_amp
id|XFS_DIFLAG_IMMUTABLE
)paren
id|inode-&gt;i_flags
op_or_assign
id|S_IMMUTABLE
suffix:semicolon
r_else
id|inode-&gt;i_flags
op_and_assign
op_complement
id|S_IMMUTABLE
suffix:semicolon
r_if
c_cond
(paren
id|ip-&gt;i_d.di_flags
op_amp
id|XFS_DIFLAG_APPEND
)paren
id|inode-&gt;i_flags
op_or_assign
id|S_APPEND
suffix:semicolon
r_else
id|inode-&gt;i_flags
op_and_assign
op_complement
id|S_APPEND
suffix:semicolon
r_if
c_cond
(paren
id|ip-&gt;i_d.di_flags
op_amp
id|XFS_DIFLAG_SYNC
)paren
id|inode-&gt;i_flags
op_or_assign
id|S_SYNC
suffix:semicolon
r_else
id|inode-&gt;i_flags
op_and_assign
op_complement
id|S_SYNC
suffix:semicolon
r_if
c_cond
(paren
id|ip-&gt;i_d.di_flags
op_amp
id|XFS_DIFLAG_NOATIME
)paren
id|inode-&gt;i_flags
op_or_assign
id|S_NOATIME
suffix:semicolon
r_else
id|inode-&gt;i_flags
op_and_assign
op_complement
id|S_NOATIME
suffix:semicolon
id|vp-&gt;v_flag
op_and_assign
op_complement
id|VMODIFIED
suffix:semicolon
)brace
r_void
DECL|function|xfs_initialize_vnode
id|xfs_initialize_vnode
c_func
(paren
id|bhv_desc_t
op_star
id|bdp
comma
id|vnode_t
op_star
id|vp
comma
id|bhv_desc_t
op_star
id|inode_bhv
comma
r_int
id|unlock
)paren
(brace
id|xfs_inode_t
op_star
id|ip
op_assign
id|XFS_BHVTOI
c_func
(paren
id|inode_bhv
)paren
suffix:semicolon
r_struct
id|inode
op_star
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
op_logical_neg
id|inode_bhv-&gt;bd_vobj
)paren
(brace
id|vp-&gt;v_vfsp
op_assign
id|bhvtovfs
c_func
(paren
id|bdp
)paren
suffix:semicolon
id|bhv_desc_init
c_func
(paren
id|inode_bhv
comma
id|ip
comma
id|vp
comma
op_amp
id|xfs_vnodeops
)paren
suffix:semicolon
id|bhv_insert
c_func
(paren
id|VN_BHV_HEAD
c_func
(paren
id|vp
)paren
comma
id|inode_bhv
)paren
suffix:semicolon
)brace
id|vp-&gt;v_type
op_assign
id|IFTOVT
c_func
(paren
id|ip-&gt;i_d.di_mode
)paren
suffix:semicolon
multiline_comment|/* Have we been called during the new inode create process,&n;&t; * in which case we are too early to fill in the Linux inode.&n;&t; */
r_if
c_cond
(paren
id|vp-&gt;v_type
op_eq
id|VNON
)paren
r_return
suffix:semicolon
id|xfs_revalidate_inode
c_func
(paren
id|XFS_BHVTOM
c_func
(paren
id|bdp
)paren
comma
id|vp
comma
id|ip
)paren
suffix:semicolon
multiline_comment|/* For new inodes we need to set the ops vectors,&n;&t; * and unlock the inode.&n;&t; */
r_if
c_cond
(paren
id|unlock
op_logical_and
(paren
id|inode-&gt;i_state
op_amp
id|I_NEW
)paren
)paren
(brace
id|xfs_set_inodeops
c_func
(paren
id|inode
)paren
suffix:semicolon
id|unlock_new_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|xfs_flush_inode
id|xfs_flush_inode
c_func
(paren
id|xfs_inode_t
op_star
id|ip
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|LINVFS_GET_IP
c_func
(paren
id|XFS_ITOV
c_func
(paren
id|ip
)paren
)paren
suffix:semicolon
id|filemap_flush
c_func
(paren
id|inode-&gt;i_mapping
)paren
suffix:semicolon
)brace
r_void
DECL|function|xfs_flush_device
id|xfs_flush_device
c_func
(paren
id|xfs_inode_t
op_star
id|ip
)paren
(brace
id|sync_blockdev
c_func
(paren
id|XFS_ITOV
c_func
(paren
id|ip
)paren
op_member_access_from_pointer
id|v_vfsp-&gt;vfs_super-&gt;s_bdev
)paren
suffix:semicolon
id|xfs_log_force
c_func
(paren
id|ip-&gt;i_mount
comma
(paren
id|xfs_lsn_t
)paren
l_int|0
comma
id|XFS_LOG_FORCE
op_or
id|XFS_LOG_SYNC
)paren
suffix:semicolon
)brace
r_int
DECL|function|xfs_blkdev_get
id|xfs_blkdev_get
c_func
(paren
id|xfs_mount_t
op_star
id|mp
comma
r_const
r_char
op_star
id|name
comma
r_struct
id|block_device
op_star
op_star
id|bdevp
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
op_star
id|bdevp
op_assign
id|open_bdev_excl
c_func
(paren
id|name
comma
l_int|0
comma
id|mp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
op_star
id|bdevp
)paren
)paren
(brace
id|error
op_assign
id|PTR_ERR
c_func
(paren
op_star
id|bdevp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;XFS: Invalid device [%s], error=%d&bslash;n&quot;
comma
id|name
comma
id|error
)paren
suffix:semicolon
)brace
r_return
op_minus
id|error
suffix:semicolon
)brace
r_void
DECL|function|xfs_blkdev_put
id|xfs_blkdev_put
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
)paren
(brace
r_if
c_cond
(paren
id|bdev
)paren
id|close_bdev_excl
c_func
(paren
id|bdev
)paren
suffix:semicolon
)brace
id|STATIC
r_struct
id|inode
op_star
DECL|function|linvfs_alloc_inode
id|linvfs_alloc_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|vnode_t
op_star
id|vp
suffix:semicolon
id|vp
op_assign
(paren
id|vnode_t
op_star
)paren
id|kmem_cache_alloc
c_func
(paren
id|linvfs_inode_cachep
comma
id|kmem_flags_convert
c_func
(paren
id|KM_SLEEP
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vp
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|LINVFS_GET_IP
c_func
(paren
id|vp
)paren
suffix:semicolon
)brace
id|STATIC
r_void
DECL|function|linvfs_destroy_inode
id|linvfs_destroy_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|kmem_cache_free
c_func
(paren
id|linvfs_inode_cachep
comma
id|LINVFS_GET_VP
c_func
(paren
id|inode
)paren
)paren
suffix:semicolon
)brace
id|STATIC
r_void
DECL|function|init_once
id|init_once
c_func
(paren
r_void
op_star
id|data
comma
id|kmem_cache_t
op_star
id|cachep
comma
r_int
r_int
id|flags
)paren
(brace
id|vnode_t
op_star
id|vp
op_assign
(paren
id|vnode_t
op_star
)paren
id|data
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
(paren
id|SLAB_CTOR_VERIFY
op_or
id|SLAB_CTOR_CONSTRUCTOR
)paren
)paren
op_eq
id|SLAB_CTOR_CONSTRUCTOR
)paren
id|inode_init_once
c_func
(paren
id|LINVFS_GET_IP
c_func
(paren
id|vp
)paren
)paren
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|init_inodecache
id|init_inodecache
c_func
(paren
r_void
)paren
(brace
id|linvfs_inode_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;linvfs_icache&quot;
comma
r_sizeof
(paren
id|vnode_t
)paren
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
op_or
id|SLAB_RECLAIM_ACCOUNT
comma
id|init_once
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|linvfs_inode_cachep
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|STATIC
r_void
DECL|function|destroy_inodecache
id|destroy_inodecache
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|kmem_cache_destroy
c_func
(paren
id|linvfs_inode_cachep
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: cache still in use!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Attempt to flush the inode, this will actually fail&n; * if the inode is pinned, but we dirty the inode again&n; * at the point when it is unpinned after a log write,&n; * since this is when the inode itself becomes flushable. &n; */
id|STATIC
r_void
DECL|function|linvfs_write_inode
id|linvfs_write_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|sync
)paren
(brace
id|vnode_t
op_star
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|inode
)paren
suffix:semicolon
r_int
id|error
comma
id|flags
op_assign
id|FLUSH_INODE
suffix:semicolon
r_if
c_cond
(paren
id|vp
)paren
(brace
id|vn_trace_entry
c_func
(paren
id|vp
comma
id|__FUNCTION__
comma
(paren
id|inst_t
op_star
)paren
id|__return_address
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sync
)paren
id|flags
op_or_assign
id|FLUSH_SYNC
suffix:semicolon
id|VOP_IFLUSH
c_func
(paren
id|vp
comma
id|flags
comma
id|error
)paren
suffix:semicolon
)brace
)brace
id|STATIC
r_void
DECL|function|linvfs_clear_inode
id|linvfs_clear_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|vnode_t
op_star
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vp
)paren
(brace
id|vn_rele
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
id|__FUNCTION__
comma
(paren
id|inst_t
op_star
)paren
id|__return_address
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Do all our cleanup, and remove this vnode.&n;&t;&t; */
id|vn_remove
c_func
(paren
id|vp
)paren
suffix:semicolon
)brace
)brace
DECL|macro|SYNCD_FLAGS
mdefine_line|#define SYNCD_FLAGS&t;(SYNC_FSDATA|SYNC_BDFLUSH|SYNC_ATTR)
id|STATIC
r_int
DECL|function|xfssyncd
id|xfssyncd
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
id|vfs_t
op_star
id|vfsp
op_assign
(paren
id|vfs_t
op_star
)paren
id|arg
suffix:semicolon
r_int
id|error
suffix:semicolon
id|daemonize
c_func
(paren
l_string|&quot;xfssyncd&quot;
)paren
suffix:semicolon
id|vfsp-&gt;vfs_sync_task
op_assign
id|current
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|vfsp-&gt;vfs_wait_sync_task
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|xfs_syncd_interval
)paren
suffix:semicolon
multiline_comment|/* swsusp */
r_if
c_cond
(paren
id|current-&gt;flags
op_amp
id|PF_FREEZE
)paren
id|refrigerator
c_func
(paren
id|PF_FREEZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vfsp-&gt;vfs_flag
op_amp
id|VFS_UMOUNT
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|vfsp-&gt;vfs_flag
op_amp
id|VFS_RDONLY
)paren
r_continue
suffix:semicolon
id|VFS_SYNC
c_func
(paren
id|vfsp
comma
id|SYNCD_FLAGS
comma
l_int|NULL
comma
id|error
)paren
suffix:semicolon
)brace
id|vfsp-&gt;vfs_sync_task
op_assign
l_int|NULL
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|vfsp-&gt;vfs_wait_sync_task
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_start_syncd
id|linvfs_start_syncd
c_func
(paren
id|vfs_t
op_star
id|vfsp
)paren
(brace
r_int
id|pid
suffix:semicolon
id|pid
op_assign
id|kernel_thread
c_func
(paren
id|xfssyncd
comma
(paren
r_void
op_star
)paren
id|vfsp
comma
id|CLONE_VM
op_or
id|CLONE_FS
op_or
id|CLONE_FILES
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
r_return
op_minus
id|pid
suffix:semicolon
id|wait_event
c_func
(paren
id|vfsp-&gt;vfs_wait_sync_task
comma
id|vfsp-&gt;vfs_sync_task
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|STATIC
r_void
DECL|function|linvfs_stop_syncd
id|linvfs_stop_syncd
c_func
(paren
id|vfs_t
op_star
id|vfsp
)paren
(brace
id|vfsp-&gt;vfs_flag
op_or_assign
id|VFS_UMOUNT
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|wake_up_process
c_func
(paren
id|vfsp-&gt;vfs_sync_task
)paren
suffix:semicolon
id|wait_event
c_func
(paren
id|vfsp-&gt;vfs_wait_sync_task
comma
op_logical_neg
id|vfsp-&gt;vfs_sync_task
)paren
suffix:semicolon
)brace
id|STATIC
r_void
DECL|function|linvfs_put_super
id|linvfs_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|vfs_t
op_star
id|vfsp
op_assign
id|LINVFS_GET_VFS
c_func
(paren
id|sb
)paren
suffix:semicolon
r_int
id|error
suffix:semicolon
id|linvfs_stop_syncd
c_func
(paren
id|vfsp
)paren
suffix:semicolon
id|VFS_SYNC
c_func
(paren
id|vfsp
comma
id|SYNC_ATTR
op_or
id|SYNC_DELWRI
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
id|VFS_UNMOUNT
c_func
(paren
id|vfsp
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
id|error
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;XFS unmount got error %d&bslash;n&quot;
comma
id|error
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: vfsp/0x%p left dangling!&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|vfsp
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|vfs_deallocate
c_func
(paren
id|vfsp
)paren
suffix:semicolon
)brace
id|STATIC
r_void
DECL|function|linvfs_write_super
id|linvfs_write_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|vfs_t
op_star
id|vfsp
op_assign
id|LINVFS_GET_VFS
c_func
(paren
id|sb
)paren
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
(brace
id|sb-&gt;s_dirt
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* paranoia */
r_return
suffix:semicolon
)brace
multiline_comment|/* Push the log and superblock a little */
id|VFS_SYNC
c_func
(paren
id|vfsp
comma
id|SYNC_FSDATA
comma
l_int|NULL
comma
id|error
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|0
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_sync_super
id|linvfs_sync_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|wait
)paren
(brace
id|vfs_t
op_star
id|vfsp
op_assign
id|LINVFS_GET_VFS
c_func
(paren
id|sb
)paren
suffix:semicolon
r_int
id|error
suffix:semicolon
r_int
id|flags
op_assign
id|SYNC_FSDATA
suffix:semicolon
r_if
c_cond
(paren
id|wait
)paren
id|flags
op_or_assign
id|SYNC_WAIT
suffix:semicolon
id|VFS_SYNC
c_func
(paren
id|vfsp
comma
id|flags
comma
l_int|NULL
comma
id|error
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|error
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_statfs
id|linvfs_statfs
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|kstatfs
op_star
id|statp
)paren
(brace
id|vfs_t
op_star
id|vfsp
op_assign
id|LINVFS_GET_VFS
c_func
(paren
id|sb
)paren
suffix:semicolon
r_int
id|error
suffix:semicolon
id|VFS_STATVFS
c_func
(paren
id|vfsp
comma
id|statp
comma
l_int|NULL
comma
id|error
)paren
suffix:semicolon
r_return
op_minus
id|error
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_remount
id|linvfs_remount
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
op_star
id|flags
comma
r_char
op_star
id|options
)paren
(brace
id|vfs_t
op_star
id|vfsp
op_assign
id|LINVFS_GET_VFS
c_func
(paren
id|sb
)paren
suffix:semicolon
r_struct
id|xfs_mount_args
op_star
id|args
op_assign
id|xfs_args_allocate
c_func
(paren
id|sb
)paren
suffix:semicolon
r_int
id|error
suffix:semicolon
id|VFS_PARSEARGS
c_func
(paren
id|vfsp
comma
id|options
comma
id|args
comma
l_int|1
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
id|VFS_MNTUPDATE
c_func
(paren
id|vfsp
comma
id|flags
comma
id|args
comma
id|error
)paren
suffix:semicolon
id|kmem_free
c_func
(paren
id|args
comma
r_sizeof
(paren
op_star
id|args
)paren
)paren
suffix:semicolon
r_return
op_minus
id|error
suffix:semicolon
)brace
id|STATIC
r_void
DECL|function|linvfs_freeze_fs
id|linvfs_freeze_fs
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|VFS_FREEZE
c_func
(paren
id|LINVFS_GET_VFS
c_func
(paren
id|sb
)paren
)paren
suffix:semicolon
)brace
id|STATIC
r_struct
id|dentry
op_star
DECL|function|linvfs_get_parent
id|linvfs_get_parent
c_func
(paren
r_struct
id|dentry
op_star
id|child
)paren
(brace
r_int
id|error
suffix:semicolon
id|vnode_t
op_star
id|vp
comma
op_star
id|cvp
suffix:semicolon
r_struct
id|dentry
op_star
id|parent
suffix:semicolon
r_struct
id|inode
op_star
id|ip
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|dentry
id|dotdot
suffix:semicolon
id|dotdot.d_name.name
op_assign
l_string|&quot;..&quot;
suffix:semicolon
id|dotdot.d_name.len
op_assign
l_int|2
suffix:semicolon
id|dotdot.d_inode
op_assign
l_int|0
suffix:semicolon
id|cvp
op_assign
l_int|NULL
suffix:semicolon
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|child-&gt;d_inode
)paren
suffix:semicolon
id|VOP_LOOKUP
c_func
(paren
id|vp
comma
op_amp
id|dotdot
comma
op_amp
id|cvp
comma
l_int|0
comma
l_int|NULL
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
id|ASSERT
c_func
(paren
id|cvp
)paren
suffix:semicolon
id|ip
op_assign
id|LINVFS_GET_IP
c_func
(paren
id|cvp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ip
)paren
(brace
id|VN_RELE
c_func
(paren
id|cvp
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EACCES
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|error
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|error
)paren
suffix:semicolon
id|parent
op_assign
id|d_alloc_anon
c_func
(paren
id|ip
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parent
)paren
(brace
id|VN_RELE
c_func
(paren
id|cvp
)paren
suffix:semicolon
id|parent
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
)brace
r_return
id|parent
suffix:semicolon
)brace
id|STATIC
r_struct
id|dentry
op_star
DECL|function|linvfs_get_dentry
id|linvfs_get_dentry
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_void
op_star
id|data
)paren
(brace
id|vnode_t
op_star
id|vp
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|dentry
op_star
id|result
suffix:semicolon
id|xfs_fid2_t
id|xfid
suffix:semicolon
id|vfs_t
op_star
id|vfsp
op_assign
id|LINVFS_GET_VFS
c_func
(paren
id|sb
)paren
suffix:semicolon
r_int
id|error
suffix:semicolon
id|xfid.fid_len
op_assign
r_sizeof
(paren
id|xfs_fid2_t
)paren
op_minus
r_sizeof
(paren
id|xfid.fid_len
)paren
suffix:semicolon
id|xfid.fid_pad
op_assign
l_int|0
suffix:semicolon
id|xfid.fid_gen
op_assign
(paren
(paren
id|__u32
op_star
)paren
id|data
)paren
(braket
l_int|1
)braket
suffix:semicolon
id|xfid.fid_ino
op_assign
(paren
(paren
id|__u32
op_star
)paren
id|data
)paren
(braket
l_int|0
)braket
suffix:semicolon
id|VFS_VGET
c_func
(paren
id|vfsp
comma
op_amp
id|vp
comma
(paren
id|fid_t
op_star
)paren
op_amp
id|xfid
comma
id|error
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_logical_or
id|vp
op_eq
l_int|NULL
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ESTALE
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
id|result
op_assign
id|d_alloc_anon
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|result
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_show_options
id|linvfs_show_options
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_struct
id|vfsmount
op_star
id|mnt
)paren
(brace
r_struct
id|vfs
op_star
id|vfsp
op_assign
id|LINVFS_GET_VFS
c_func
(paren
id|mnt-&gt;mnt_sb
)paren
suffix:semicolon
r_int
id|error
suffix:semicolon
id|VFS_SHOWARGS
c_func
(paren
id|vfsp
comma
id|m
comma
id|error
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_getxstate
id|linvfs_getxstate
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|fs_quota_stat
op_star
id|fqs
)paren
(brace
r_struct
id|vfs
op_star
id|vfsp
op_assign
id|LINVFS_GET_VFS
c_func
(paren
id|sb
)paren
suffix:semicolon
r_int
id|error
suffix:semicolon
id|VFS_QUOTACTL
c_func
(paren
id|vfsp
comma
id|Q_XGETQSTAT
comma
l_int|0
comma
(paren
id|caddr_t
)paren
id|fqs
comma
id|error
)paren
suffix:semicolon
r_return
op_minus
id|error
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_setxstate
id|linvfs_setxstate
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|flags
comma
r_int
id|op
)paren
(brace
r_struct
id|vfs
op_star
id|vfsp
op_assign
id|LINVFS_GET_VFS
c_func
(paren
id|sb
)paren
suffix:semicolon
r_int
id|error
suffix:semicolon
id|VFS_QUOTACTL
c_func
(paren
id|vfsp
comma
id|op
comma
l_int|0
comma
(paren
id|caddr_t
)paren
op_amp
id|flags
comma
id|error
)paren
suffix:semicolon
r_return
op_minus
id|error
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_getxquota
id|linvfs_getxquota
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|type
comma
id|qid_t
id|id
comma
r_struct
id|fs_disk_quota
op_star
id|fdq
)paren
(brace
r_struct
id|vfs
op_star
id|vfsp
op_assign
id|LINVFS_GET_VFS
c_func
(paren
id|sb
)paren
suffix:semicolon
r_int
id|error
comma
id|getmode
suffix:semicolon
id|getmode
op_assign
(paren
id|type
op_eq
id|GRPQUOTA
)paren
ques
c_cond
id|Q_XGETGQUOTA
suffix:colon
id|Q_XGETQUOTA
suffix:semicolon
id|VFS_QUOTACTL
c_func
(paren
id|vfsp
comma
id|getmode
comma
id|id
comma
(paren
id|caddr_t
)paren
id|fdq
comma
id|error
)paren
suffix:semicolon
r_return
op_minus
id|error
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_setxquota
id|linvfs_setxquota
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|type
comma
id|qid_t
id|id
comma
r_struct
id|fs_disk_quota
op_star
id|fdq
)paren
(brace
r_struct
id|vfs
op_star
id|vfsp
op_assign
id|LINVFS_GET_VFS
c_func
(paren
id|sb
)paren
suffix:semicolon
r_int
id|error
comma
id|setmode
suffix:semicolon
id|setmode
op_assign
(paren
id|type
op_eq
id|GRPQUOTA
)paren
ques
c_cond
id|Q_XSETGQLIM
suffix:colon
id|Q_XSETQLIM
suffix:semicolon
id|VFS_QUOTACTL
c_func
(paren
id|vfsp
comma
id|setmode
comma
id|id
comma
(paren
id|caddr_t
)paren
id|fdq
comma
id|error
)paren
suffix:semicolon
r_return
op_minus
id|error
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_fill_super
id|linvfs_fill_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_void
op_star
id|data
comma
r_int
id|silent
)paren
(brace
id|vnode_t
op_star
id|rootvp
suffix:semicolon
r_struct
id|vfs
op_star
id|vfsp
op_assign
id|vfs_allocate
c_func
(paren
)paren
suffix:semicolon
r_struct
id|xfs_mount_args
op_star
id|args
op_assign
id|xfs_args_allocate
c_func
(paren
id|sb
)paren
suffix:semicolon
r_struct
id|kstatfs
id|statvfs
suffix:semicolon
r_int
id|error
comma
id|error2
suffix:semicolon
id|vfsp-&gt;vfs_super
op_assign
id|sb
suffix:semicolon
id|LINVFS_SET_VFS
c_func
(paren
id|sb
comma
id|vfsp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
id|vfsp-&gt;vfs_flag
op_or_assign
id|VFS_RDONLY
suffix:semicolon
id|bhv_insert_all_vfsops
c_func
(paren
id|vfsp
)paren
suffix:semicolon
id|VFS_PARSEARGS
c_func
(paren
id|vfsp
comma
(paren
r_char
op_star
)paren
id|data
comma
id|args
comma
l_int|0
comma
id|error
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|bhv_remove_all_vfsops
c_func
(paren
id|vfsp
comma
l_int|1
)paren
suffix:semicolon
r_goto
id|fail_vfsop
suffix:semicolon
)brace
id|sb_min_blocksize
c_func
(paren
id|sb
comma
id|BBSIZE
)paren
suffix:semicolon
id|sb-&gt;s_export_op
op_assign
op_amp
id|linvfs_export_ops
suffix:semicolon
id|sb-&gt;s_qcop
op_assign
op_amp
id|linvfs_qops
suffix:semicolon
id|sb-&gt;s_op
op_assign
op_amp
id|linvfs_sops
suffix:semicolon
id|VFS_MOUNT
c_func
(paren
id|vfsp
comma
id|args
comma
l_int|NULL
comma
id|error
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|bhv_remove_all_vfsops
c_func
(paren
id|vfsp
comma
l_int|1
)paren
suffix:semicolon
r_goto
id|fail_vfsop
suffix:semicolon
)brace
id|VFS_STATVFS
c_func
(paren
id|vfsp
comma
op_amp
id|statvfs
comma
l_int|NULL
comma
id|error
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|fail_unmount
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
id|sb-&gt;s_magic
op_assign
id|statvfs.f_type
suffix:semicolon
id|sb-&gt;s_blocksize
op_assign
id|statvfs.f_bsize
suffix:semicolon
id|sb-&gt;s_blocksize_bits
op_assign
id|ffs
c_func
(paren
id|statvfs.f_bsize
)paren
op_minus
l_int|1
suffix:semicolon
id|sb-&gt;s_maxbytes
op_assign
id|xfs_max_file_offset
c_func
(paren
id|sb-&gt;s_blocksize_bits
)paren
suffix:semicolon
id|set_posix_acl_flag
c_func
(paren
id|sb
)paren
suffix:semicolon
id|VFS_ROOT
c_func
(paren
id|vfsp
comma
op_amp
id|rootvp
comma
id|error
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|fail_unmount
suffix:semicolon
id|sb-&gt;s_root
op_assign
id|d_alloc_root
c_func
(paren
id|LINVFS_GET_IP
c_func
(paren
id|rootvp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;s_root
)paren
(brace
id|error
op_assign
id|ENOMEM
suffix:semicolon
r_goto
id|fail_vnrele
suffix:semicolon
)brace
r_if
c_cond
(paren
id|is_bad_inode
c_func
(paren
id|sb-&gt;s_root-&gt;d_inode
)paren
)paren
(brace
id|error
op_assign
id|EINVAL
suffix:semicolon
r_goto
id|fail_vnrele
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|error
op_assign
id|linvfs_start_syncd
c_func
(paren
id|vfsp
)paren
)paren
)paren
r_goto
id|fail_vnrele
suffix:semicolon
id|vn_trace_exit
c_func
(paren
id|rootvp
comma
id|__FUNCTION__
comma
(paren
id|inst_t
op_star
)paren
id|__return_address
)paren
suffix:semicolon
id|kmem_free
c_func
(paren
id|args
comma
r_sizeof
(paren
op_star
id|args
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|fail_vnrele
suffix:colon
r_if
c_cond
(paren
id|sb-&gt;s_root
)paren
(brace
id|dput
c_func
(paren
id|sb-&gt;s_root
)paren
suffix:semicolon
id|sb-&gt;s_root
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|VN_RELE
c_func
(paren
id|rootvp
)paren
suffix:semicolon
)brace
id|fail_unmount
suffix:colon
id|VFS_UNMOUNT
c_func
(paren
id|vfsp
comma
l_int|0
comma
l_int|NULL
comma
id|error2
)paren
suffix:semicolon
id|fail_vfsop
suffix:colon
id|vfs_deallocate
c_func
(paren
id|vfsp
)paren
suffix:semicolon
id|kmem_free
c_func
(paren
id|args
comma
r_sizeof
(paren
op_star
id|args
)paren
)paren
suffix:semicolon
r_return
op_minus
id|error
suffix:semicolon
)brace
id|STATIC
r_struct
id|super_block
op_star
DECL|function|linvfs_get_sb
id|linvfs_get_sb
c_func
(paren
r_struct
id|file_system_type
op_star
id|fs_type
comma
r_int
id|flags
comma
r_const
r_char
op_star
id|dev_name
comma
r_void
op_star
id|data
)paren
(brace
r_return
id|get_sb_bdev
c_func
(paren
id|fs_type
comma
id|flags
comma
id|dev_name
comma
id|data
comma
id|linvfs_fill_super
)paren
suffix:semicolon
)brace
DECL|variable|linvfs_export_ops
id|STATIC
r_struct
id|export_operations
id|linvfs_export_ops
op_assign
(brace
dot
id|get_parent
op_assign
id|linvfs_get_parent
comma
dot
id|get_dentry
op_assign
id|linvfs_get_dentry
comma
)brace
suffix:semicolon
DECL|variable|linvfs_sops
id|STATIC
r_struct
id|super_operations
id|linvfs_sops
op_assign
(brace
dot
id|alloc_inode
op_assign
id|linvfs_alloc_inode
comma
dot
id|destroy_inode
op_assign
id|linvfs_destroy_inode
comma
dot
id|write_inode
op_assign
id|linvfs_write_inode
comma
dot
id|clear_inode
op_assign
id|linvfs_clear_inode
comma
dot
id|put_super
op_assign
id|linvfs_put_super
comma
dot
id|write_super
op_assign
id|linvfs_write_super
comma
dot
id|sync_fs
op_assign
id|linvfs_sync_super
comma
dot
id|write_super_lockfs
op_assign
id|linvfs_freeze_fs
comma
dot
id|statfs
op_assign
id|linvfs_statfs
comma
dot
id|remount_fs
op_assign
id|linvfs_remount
comma
dot
id|show_options
op_assign
id|linvfs_show_options
comma
)brace
suffix:semicolon
DECL|variable|linvfs_qops
id|STATIC
r_struct
id|quotactl_ops
id|linvfs_qops
op_assign
(brace
dot
id|get_xstate
op_assign
id|linvfs_getxstate
comma
dot
id|set_xstate
op_assign
id|linvfs_setxstate
comma
dot
id|get_xquota
op_assign
id|linvfs_getxquota
comma
dot
id|set_xquota
op_assign
id|linvfs_setxquota
comma
)brace
suffix:semicolon
DECL|variable|xfs_fs_type
id|STATIC
r_struct
id|file_system_type
id|xfs_fs_type
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;xfs&quot;
comma
dot
id|get_sb
op_assign
id|linvfs_get_sb
comma
dot
id|kill_sb
op_assign
id|kill_block_super
comma
dot
id|fs_flags
op_assign
id|FS_REQUIRES_DEV
comma
)brace
suffix:semicolon
id|STATIC
r_int
id|__init
DECL|function|init_xfs_fs
id|init_xfs_fs
c_func
(paren
r_void
)paren
(brace
r_int
id|error
suffix:semicolon
r_struct
id|sysinfo
id|si
suffix:semicolon
r_static
r_char
id|message
(braket
)braket
id|__initdata
op_assign
id|KERN_INFO
"&bslash;"
id|XFS_VERSION_STRING
l_string|&quot; with &quot;
id|XFS_BUILD_OPTIONS
l_string|&quot; enabled&bslash;n&quot;
suffix:semicolon
id|printk
c_func
(paren
id|message
)paren
suffix:semicolon
id|si_meminfo
c_func
(paren
op_amp
id|si
)paren
suffix:semicolon
id|xfs_physmem
op_assign
id|si.totalram
suffix:semicolon
id|ktrace_init
c_func
(paren
l_int|64
)paren
suffix:semicolon
id|error
op_assign
id|init_inodecache
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_goto
id|undo_inodecache
suffix:semicolon
id|error
op_assign
id|pagebuf_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_goto
id|undo_pagebuf
suffix:semicolon
id|vn_init
c_func
(paren
)paren
suffix:semicolon
id|xfs_init
c_func
(paren
)paren
suffix:semicolon
id|uuid_init
c_func
(paren
)paren
suffix:semicolon
id|vfs_initdmapi
c_func
(paren
)paren
suffix:semicolon
id|vfs_initquota
c_func
(paren
)paren
suffix:semicolon
id|error
op_assign
id|register_filesystem
c_func
(paren
op_amp
id|xfs_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|undo_register
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|undo_register
suffix:colon
id|pagebuf_terminate
c_func
(paren
)paren
suffix:semicolon
id|undo_pagebuf
suffix:colon
id|destroy_inodecache
c_func
(paren
)paren
suffix:semicolon
id|undo_inodecache
suffix:colon
r_return
id|error
suffix:semicolon
)brace
id|STATIC
r_void
id|__exit
DECL|function|exit_xfs_fs
id|exit_xfs_fs
c_func
(paren
r_void
)paren
(brace
id|vfs_exitquota
c_func
(paren
)paren
suffix:semicolon
id|vfs_exitdmapi
c_func
(paren
)paren
suffix:semicolon
id|unregister_filesystem
c_func
(paren
op_amp
id|xfs_fs_type
)paren
suffix:semicolon
id|XFS_DM_EXIT
c_func
(paren
)paren
suffix:semicolon
id|xfs_cleanup
c_func
(paren
)paren
suffix:semicolon
id|pagebuf_terminate
c_func
(paren
)paren
suffix:semicolon
id|destroy_inodecache
c_func
(paren
)paren
suffix:semicolon
id|ktrace_uninit
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|init_xfs_fs
id|module_init
c_func
(paren
id|init_xfs_fs
)paren
suffix:semicolon
DECL|variable|exit_xfs_fs
id|module_exit
c_func
(paren
id|exit_xfs_fs
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Silicon Graphics, Inc.&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
id|XFS_VERSION_STRING
l_string|&quot; with &quot;
id|XFS_BUILD_OPTIONS
l_string|&quot; enabled&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
