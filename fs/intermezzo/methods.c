multiline_comment|/* -*- mode: c; c-basic-offset: 8; indent-tabs-mode: nil; -*-&n; * vim:expandtab:shiftwidth=8:tabstop=8:&n; *&n; *  Copyright (C) 2000 Stelias Computing, Inc.&n; *  Copyright (C) 2000 Red Hat, Inc.&n; *  Copyright (C) 2000 Mountain View Data, Inc.&n; *&n; *  Extended Attribute Support&n; *  Copyright (C) 2001 Shirish H. Phatak, Tacit Networks, Inc.&n; *&n; *   This file is part of InterMezzo, http://www.inter-mezzo.org.&n; *&n; *   InterMezzo is free software; you can redistribute it and/or&n; *   modify it under the terms of version 2 of the GNU General Public&n; *   License as published by the Free Software Foundation.&n; *&n; *   InterMezzo is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with InterMezzo; if not, write to the Free Software&n; *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fsfilter.h&gt;
macro_line|#include &quot;intermezzo_fs.h&quot;
DECL|variable|filter_print_entry
r_int
id|filter_print_entry
op_assign
l_int|0
suffix:semicolon
DECL|variable|filter_debug
r_int
id|filter_debug
op_assign
l_int|0xfffffff
suffix:semicolon
multiline_comment|/*&n; * The function in this file are responsible for setting up the &n; * correct methods layered file systems like InterMezzo and snapfs&n; */
DECL|variable|filter_oppar
r_static
r_struct
id|filter_fs
id|filter_oppar
(braket
id|FILTER_FS_TYPES
)braket
suffix:semicolon
multiline_comment|/* get to the upper methods (intermezzo, snapfs) */
DECL|function|filter_c2usops
r_inline
r_struct
id|super_operations
op_star
id|filter_c2usops
c_func
(paren
r_struct
id|filter_fs
op_star
id|cache
)paren
(brace
r_return
op_amp
id|cache-&gt;o_fops.filter_sops
suffix:semicolon
)brace
DECL|function|filter_c2udiops
r_inline
r_struct
id|inode_operations
op_star
id|filter_c2udiops
c_func
(paren
r_struct
id|filter_fs
op_star
id|cache
)paren
(brace
r_return
op_amp
id|cache-&gt;o_fops.filter_dir_iops
suffix:semicolon
)brace
DECL|function|filter_c2ufiops
r_inline
r_struct
id|inode_operations
op_star
id|filter_c2ufiops
c_func
(paren
r_struct
id|filter_fs
op_star
id|cache
)paren
(brace
r_return
op_amp
id|cache-&gt;o_fops.filter_file_iops
suffix:semicolon
)brace
DECL|function|filter_c2usiops
r_inline
r_struct
id|inode_operations
op_star
id|filter_c2usiops
c_func
(paren
r_struct
id|filter_fs
op_star
id|cache
)paren
(brace
r_return
op_amp
id|cache-&gt;o_fops.filter_sym_iops
suffix:semicolon
)brace
DECL|function|filter_c2udfops
r_inline
r_struct
id|file_operations
op_star
id|filter_c2udfops
c_func
(paren
r_struct
id|filter_fs
op_star
id|cache
)paren
(brace
r_return
op_amp
id|cache-&gt;o_fops.filter_dir_fops
suffix:semicolon
)brace
DECL|function|filter_c2uffops
r_inline
r_struct
id|file_operations
op_star
id|filter_c2uffops
c_func
(paren
r_struct
id|filter_fs
op_star
id|cache
)paren
(brace
r_return
op_amp
id|cache-&gt;o_fops.filter_file_fops
suffix:semicolon
)brace
DECL|function|filter_c2usfops
r_inline
r_struct
id|file_operations
op_star
id|filter_c2usfops
c_func
(paren
r_struct
id|filter_fs
op_star
id|cache
)paren
(brace
r_return
op_amp
id|cache-&gt;o_fops.filter_sym_fops
suffix:semicolon
)brace
DECL|function|filter_c2udops
r_inline
r_struct
id|dentry_operations
op_star
id|filter_c2udops
c_func
(paren
r_struct
id|filter_fs
op_star
id|cache
)paren
(brace
r_return
op_amp
id|cache-&gt;o_fops.filter_dentry_ops
suffix:semicolon
)brace
multiline_comment|/* get to the cache (lower) methods */
DECL|function|filter_c2csops
r_inline
r_struct
id|super_operations
op_star
id|filter_c2csops
c_func
(paren
r_struct
id|filter_fs
op_star
id|cache
)paren
(brace
r_return
id|cache-&gt;o_caops.cache_sops
suffix:semicolon
)brace
DECL|function|filter_c2cdiops
r_inline
r_struct
id|inode_operations
op_star
id|filter_c2cdiops
c_func
(paren
r_struct
id|filter_fs
op_star
id|cache
)paren
(brace
r_return
id|cache-&gt;o_caops.cache_dir_iops
suffix:semicolon
)brace
DECL|function|filter_c2cfiops
r_inline
r_struct
id|inode_operations
op_star
id|filter_c2cfiops
c_func
(paren
r_struct
id|filter_fs
op_star
id|cache
)paren
(brace
r_return
id|cache-&gt;o_caops.cache_file_iops
suffix:semicolon
)brace
DECL|function|filter_c2csiops
r_inline
r_struct
id|inode_operations
op_star
id|filter_c2csiops
c_func
(paren
r_struct
id|filter_fs
op_star
id|cache
)paren
(brace
r_return
id|cache-&gt;o_caops.cache_sym_iops
suffix:semicolon
)brace
DECL|function|filter_c2cdfops
r_inline
r_struct
id|file_operations
op_star
id|filter_c2cdfops
c_func
(paren
r_struct
id|filter_fs
op_star
id|cache
)paren
(brace
r_return
id|cache-&gt;o_caops.cache_dir_fops
suffix:semicolon
)brace
DECL|function|filter_c2cffops
r_inline
r_struct
id|file_operations
op_star
id|filter_c2cffops
c_func
(paren
r_struct
id|filter_fs
op_star
id|cache
)paren
(brace
r_return
id|cache-&gt;o_caops.cache_file_fops
suffix:semicolon
)brace
DECL|function|filter_c2csfops
r_inline
r_struct
id|file_operations
op_star
id|filter_c2csfops
c_func
(paren
r_struct
id|filter_fs
op_star
id|cache
)paren
(brace
r_return
id|cache-&gt;o_caops.cache_sym_fops
suffix:semicolon
)brace
DECL|function|filter_c2cdops
r_inline
r_struct
id|dentry_operations
op_star
id|filter_c2cdops
c_func
(paren
r_struct
id|filter_fs
op_star
id|cache
)paren
(brace
r_return
id|cache-&gt;o_caops.cache_dentry_ops
suffix:semicolon
)brace
DECL|function|filter_setup_journal_ops
r_void
id|filter_setup_journal_ops
c_func
(paren
r_struct
id|filter_fs
op_star
id|ops
comma
r_char
op_star
id|cache_type
)paren
(brace
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|cache_type
)paren
op_eq
id|strlen
c_func
(paren
l_string|&quot;ext2&quot;
)paren
op_logical_and
id|memcmp
c_func
(paren
id|cache_type
comma
l_string|&quot;ext2&quot;
comma
id|strlen
c_func
(paren
l_string|&quot;ext2&quot;
)paren
)paren
op_eq
l_int|0
)paren
(brace
macro_line|#ifdef CONFIG_EXT2_FS
id|ops-&gt;o_trops
op_assign
op_amp
id|presto_ext2_journal_ops
suffix:semicolon
macro_line|#else
id|ops-&gt;o_trops
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
id|FDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;ops at %p&bslash;n&quot;
comma
id|ops
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|cache_type
)paren
op_eq
id|strlen
c_func
(paren
l_string|&quot;ext3&quot;
)paren
op_logical_and
id|memcmp
c_func
(paren
id|cache_type
comma
l_string|&quot;ext3&quot;
comma
id|strlen
c_func
(paren
l_string|&quot;ext3&quot;
)paren
)paren
op_eq
l_int|0
)paren
(brace
macro_line|#if defined(CONFIG_EXT3_FS) || defined (CONFIG_EXT3_FS_MODULE)
id|ops-&gt;o_trops
op_assign
op_amp
id|presto_ext3_journal_ops
suffix:semicolon
macro_line|#else
id|ops-&gt;o_trops
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
id|FDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;ops at %p&bslash;n&quot;
comma
id|ops
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|cache_type
)paren
op_eq
id|strlen
c_func
(paren
l_string|&quot;tmpfs&quot;
)paren
op_logical_and
id|memcmp
c_func
(paren
id|cache_type
comma
l_string|&quot;tmpfs&quot;
comma
id|strlen
c_func
(paren
l_string|&quot;tmpfs&quot;
)paren
)paren
op_eq
l_int|0
)paren
(brace
macro_line|#if defined(CONFIG_TMPFS)
id|ops-&gt;o_trops
op_assign
op_amp
id|presto_tmpfs_journal_ops
suffix:semicolon
macro_line|#else
id|ops-&gt;o_trops
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
id|FDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;ops at %p&bslash;n&quot;
comma
id|ops
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|cache_type
)paren
op_eq
id|strlen
c_func
(paren
l_string|&quot;reiserfs&quot;
)paren
op_logical_and
id|memcmp
c_func
(paren
id|cache_type
comma
l_string|&quot;reiserfs&quot;
comma
id|strlen
c_func
(paren
l_string|&quot;reiserfs&quot;
)paren
)paren
op_eq
l_int|0
)paren
(brace
macro_line|#if 0
multiline_comment|/* #if defined(CONFIG_REISERFS_FS) || defined(CONFIG_REISERFS_FS_MODULE) */
id|ops-&gt;o_trops
op_assign
op_amp
id|presto_reiserfs_journal_ops
suffix:semicolon
macro_line|#else
id|ops-&gt;o_trops
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
id|FDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;ops at %p&bslash;n&quot;
comma
id|ops
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|cache_type
)paren
op_eq
id|strlen
c_func
(paren
l_string|&quot;xfs&quot;
)paren
op_logical_and
id|memcmp
c_func
(paren
id|cache_type
comma
l_string|&quot;xfs&quot;
comma
id|strlen
c_func
(paren
l_string|&quot;xfs&quot;
)paren
)paren
op_eq
l_int|0
)paren
(brace
macro_line|#if 0
multiline_comment|/*#if defined(CONFIG_XFS_FS) || defined (CONFIG_XFS_FS_MODULE) */
id|ops-&gt;o_trops
op_assign
op_amp
id|presto_xfs_journal_ops
suffix:semicolon
macro_line|#else
id|ops-&gt;o_trops
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
id|FDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;ops at %p&bslash;n&quot;
comma
id|ops
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|cache_type
)paren
op_eq
id|strlen
c_func
(paren
l_string|&quot;obdfs&quot;
)paren
op_logical_and
id|memcmp
c_func
(paren
id|cache_type
comma
l_string|&quot;obdfs&quot;
comma
id|strlen
c_func
(paren
l_string|&quot;obdfs&quot;
)paren
)paren
op_eq
l_int|0
)paren
(brace
macro_line|#if defined(CONFIG_OBDFS_FS) || defined (CONFIG_OBDFS_FS_MODULE)
id|ops-&gt;o_trops
op_assign
id|presto_obdfs_journal_ops
suffix:semicolon
macro_line|#else
id|ops-&gt;o_trops
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
id|FDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;ops at %p&bslash;n&quot;
comma
id|ops
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* find the cache for this FS */
DECL|function|filter_get_filter_fs
r_struct
id|filter_fs
op_star
id|filter_get_filter_fs
c_func
(paren
r_const
r_char
op_star
id|cache_type
)paren
(brace
r_struct
id|filter_fs
op_star
id|ops
op_assign
l_int|NULL
suffix:semicolon
id|FENTRY
suffix:semicolon
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|cache_type
)paren
op_eq
id|strlen
c_func
(paren
l_string|&quot;ext2&quot;
)paren
op_logical_and
id|memcmp
c_func
(paren
id|cache_type
comma
l_string|&quot;ext2&quot;
comma
id|strlen
c_func
(paren
l_string|&quot;ext2&quot;
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|ops
op_assign
op_amp
id|filter_oppar
(braket
id|FILTER_FS_EXT2
)braket
suffix:semicolon
id|FDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;ops at %p&bslash;n&quot;
comma
id|ops
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|cache_type
)paren
op_eq
id|strlen
c_func
(paren
l_string|&quot;xfs&quot;
)paren
op_logical_and
id|memcmp
c_func
(paren
id|cache_type
comma
l_string|&quot;xfs&quot;
comma
id|strlen
c_func
(paren
l_string|&quot;xfs&quot;
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|ops
op_assign
op_amp
id|filter_oppar
(braket
id|FILTER_FS_XFS
)braket
suffix:semicolon
id|FDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;ops at %p&bslash;n&quot;
comma
id|ops
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|cache_type
)paren
op_eq
id|strlen
c_func
(paren
l_string|&quot;ext3&quot;
)paren
op_logical_and
id|memcmp
c_func
(paren
id|cache_type
comma
l_string|&quot;ext3&quot;
comma
id|strlen
c_func
(paren
l_string|&quot;ext3&quot;
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|ops
op_assign
op_amp
id|filter_oppar
(braket
id|FILTER_FS_EXT3
)braket
suffix:semicolon
id|FDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;ops at %p&bslash;n&quot;
comma
id|ops
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|cache_type
)paren
op_eq
id|strlen
c_func
(paren
l_string|&quot;tmpfs&quot;
)paren
op_logical_and
id|memcmp
c_func
(paren
id|cache_type
comma
l_string|&quot;tmpfs&quot;
comma
id|strlen
c_func
(paren
l_string|&quot;tmpfs&quot;
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|ops
op_assign
op_amp
id|filter_oppar
(braket
id|FILTER_FS_TMPFS
)braket
suffix:semicolon
id|FDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;ops at %p&bslash;n&quot;
comma
id|ops
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|cache_type
)paren
op_eq
id|strlen
c_func
(paren
l_string|&quot;reiserfs&quot;
)paren
op_logical_and
id|memcmp
c_func
(paren
id|cache_type
comma
l_string|&quot;reiserfs&quot;
comma
id|strlen
c_func
(paren
l_string|&quot;reiserfs&quot;
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|ops
op_assign
op_amp
id|filter_oppar
(braket
id|FILTER_FS_REISERFS
)braket
suffix:semicolon
id|FDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;ops at %p&bslash;n&quot;
comma
id|ops
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|cache_type
)paren
op_eq
id|strlen
c_func
(paren
l_string|&quot;obdfs&quot;
)paren
op_logical_and
id|memcmp
c_func
(paren
id|cache_type
comma
l_string|&quot;obdfs&quot;
comma
id|strlen
c_func
(paren
l_string|&quot;obdfs&quot;
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|ops
op_assign
op_amp
id|filter_oppar
(braket
id|FILTER_FS_OBDFS
)braket
suffix:semicolon
id|FDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;ops at %p&bslash;n&quot;
comma
id|ops
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ops
op_eq
l_int|NULL
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;prepare to die: unrecognized cache type for Filter&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|FEXIT
suffix:semicolon
r_return
id|ops
suffix:semicolon
)brace
multiline_comment|/*&n; *  Frobnicate the InterMezzo operations&n; *    this establishes the link between the InterMezzo file system&n; *    and the underlying file system used for the cache.&n; */
DECL|function|filter_setup_super_ops
r_void
id|filter_setup_super_ops
c_func
(paren
r_struct
id|filter_fs
op_star
id|cache
comma
r_struct
id|super_operations
op_star
id|cache_sops
comma
r_struct
id|super_operations
op_star
id|filter_sops
)paren
(brace
multiline_comment|/* Get ptr to the shared struct snapfs_ops structure. */
r_struct
id|filter_ops
op_star
id|props
op_assign
op_amp
id|cache-&gt;o_fops
suffix:semicolon
multiline_comment|/* Get ptr to the shared struct cache_ops structure. */
r_struct
id|cache_ops
op_star
id|caops
op_assign
op_amp
id|cache-&gt;o_caops
suffix:semicolon
id|FENTRY
suffix:semicolon
r_if
c_cond
(paren
id|cache-&gt;o_flags
op_amp
id|FILTER_DID_SUPER_OPS
)paren
(brace
id|FEXIT
suffix:semicolon
r_return
suffix:semicolon
)brace
id|cache-&gt;o_flags
op_or_assign
id|FILTER_DID_SUPER_OPS
suffix:semicolon
multiline_comment|/* Set the cache superblock operations to point to the&n;           superblock operations of the underlying file system.  */
id|caops-&gt;cache_sops
op_assign
id|cache_sops
suffix:semicolon
multiline_comment|/*&n;         * Copy the cache (real fs) superblock ops to the &quot;filter&quot;&n;         * superblock ops as defaults. Some will be changed below&n;         */
id|memcpy
c_func
(paren
op_amp
id|props-&gt;filter_sops
comma
id|cache_sops
comma
r_sizeof
(paren
op_star
id|cache_sops
)paren
)paren
suffix:semicolon
multiline_comment|/* &squot;put_super&squot; unconditionally is that of filter */
r_if
c_cond
(paren
id|filter_sops-&gt;put_super
)paren
(brace
id|props-&gt;filter_sops.put_super
op_assign
id|filter_sops-&gt;put_super
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cache_sops-&gt;read_inode
)paren
(brace
id|props-&gt;filter_sops.read_inode
op_assign
id|filter_sops-&gt;read_inode
suffix:semicolon
id|FDEBUG
c_func
(paren
id|D_INODE
comma
l_string|&quot;setting filter_read_inode, cache_ops %p, cache %p, ri at %p&bslash;n&quot;
comma
id|cache
comma
id|cache
comma
id|props-&gt;filter_sops.read_inode
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cache_sops-&gt;remount_fs
)paren
id|props-&gt;filter_sops.remount_fs
op_assign
id|filter_sops-&gt;remount_fs
suffix:semicolon
id|FEXIT
suffix:semicolon
)brace
DECL|function|filter_setup_dir_ops
r_void
id|filter_setup_dir_ops
c_func
(paren
r_struct
id|filter_fs
op_star
id|cache
comma
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|inode_operations
op_star
id|filter_iops
comma
r_struct
id|file_operations
op_star
id|filter_fops
)paren
(brace
r_struct
id|inode_operations
op_star
id|cache_filter_iops
suffix:semicolon
r_struct
id|inode_operations
op_star
id|cache_iops
op_assign
id|inode-&gt;i_op
suffix:semicolon
r_struct
id|file_operations
op_star
id|cache_fops
op_assign
id|inode-&gt;i_fop
suffix:semicolon
id|FENTRY
suffix:semicolon
r_if
c_cond
(paren
id|cache-&gt;o_flags
op_amp
id|FILTER_DID_DIR_OPS
)paren
(brace
id|FEXIT
suffix:semicolon
r_return
suffix:semicolon
)brace
id|cache-&gt;o_flags
op_or_assign
id|FILTER_DID_DIR_OPS
suffix:semicolon
multiline_comment|/* former ops become cache_ops */
id|cache-&gt;o_caops.cache_dir_iops
op_assign
id|cache_iops
suffix:semicolon
id|cache-&gt;o_caops.cache_dir_fops
op_assign
id|cache_fops
suffix:semicolon
id|FDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;filter at %p, cache iops %p, iops %p&bslash;n&quot;
comma
id|cache
comma
id|cache_iops
comma
id|filter_c2udiops
c_func
(paren
id|cache
)paren
)paren
suffix:semicolon
multiline_comment|/* setup our dir iops: copy and modify */
id|memcpy
c_func
(paren
id|filter_c2udiops
c_func
(paren
id|cache
)paren
comma
id|cache_iops
comma
r_sizeof
(paren
op_star
id|cache_iops
)paren
)paren
suffix:semicolon
multiline_comment|/* abbreviate */
id|cache_filter_iops
op_assign
id|filter_c2udiops
c_func
(paren
id|cache
)paren
suffix:semicolon
multiline_comment|/* methods that filter if cache filesystem has these ops */
r_if
c_cond
(paren
id|cache_iops-&gt;lookup
op_logical_and
id|filter_iops-&gt;lookup
)paren
id|cache_filter_iops-&gt;lookup
op_assign
id|filter_iops-&gt;lookup
suffix:semicolon
r_if
c_cond
(paren
id|cache_iops-&gt;create
op_logical_and
id|filter_iops-&gt;create
)paren
id|cache_filter_iops-&gt;create
op_assign
id|filter_iops-&gt;create
suffix:semicolon
r_if
c_cond
(paren
id|cache_iops-&gt;link
op_logical_and
id|filter_iops-&gt;link
)paren
id|cache_filter_iops-&gt;link
op_assign
id|filter_iops-&gt;link
suffix:semicolon
r_if
c_cond
(paren
id|cache_iops-&gt;unlink
op_logical_and
id|filter_iops-&gt;unlink
)paren
id|cache_filter_iops-&gt;unlink
op_assign
id|filter_iops-&gt;unlink
suffix:semicolon
r_if
c_cond
(paren
id|cache_iops-&gt;mkdir
op_logical_and
id|filter_iops-&gt;mkdir
)paren
id|cache_filter_iops-&gt;mkdir
op_assign
id|filter_iops-&gt;mkdir
suffix:semicolon
r_if
c_cond
(paren
id|cache_iops-&gt;rmdir
op_logical_and
id|filter_iops-&gt;rmdir
)paren
id|cache_filter_iops-&gt;rmdir
op_assign
id|filter_iops-&gt;rmdir
suffix:semicolon
r_if
c_cond
(paren
id|cache_iops-&gt;symlink
op_logical_and
id|filter_iops-&gt;symlink
)paren
id|cache_filter_iops-&gt;symlink
op_assign
id|filter_iops-&gt;symlink
suffix:semicolon
r_if
c_cond
(paren
id|cache_iops-&gt;rename
op_logical_and
id|filter_iops-&gt;rename
)paren
id|cache_filter_iops-&gt;rename
op_assign
id|filter_iops-&gt;rename
suffix:semicolon
r_if
c_cond
(paren
id|cache_iops-&gt;mknod
op_logical_and
id|filter_iops-&gt;mknod
)paren
id|cache_filter_iops-&gt;mknod
op_assign
id|filter_iops-&gt;mknod
suffix:semicolon
r_if
c_cond
(paren
id|cache_iops-&gt;permission
op_logical_and
id|filter_iops-&gt;permission
)paren
id|cache_filter_iops-&gt;permission
op_assign
id|filter_iops-&gt;permission
suffix:semicolon
r_if
c_cond
(paren
id|cache_iops-&gt;getattr
)paren
id|cache_filter_iops-&gt;getattr
op_assign
id|filter_iops-&gt;getattr
suffix:semicolon
multiline_comment|/* Some filesystems do not use a setattr method of their own&n;           instead relying on inode_setattr/write_inode. We still need to&n;           journal these so we make setattr an unconditional operation. &n;           XXX: we should probably check for write_inode. SHP&n;        */
multiline_comment|/*if (cache_iops-&gt;setattr)*/
id|cache_filter_iops-&gt;setattr
op_assign
id|filter_iops-&gt;setattr
suffix:semicolon
macro_line|#ifdef CONFIG_FS_EXT_ATTR
multiline_comment|/* For now we assume that posix acls are handled through extended&n;&t;* attributes. If this is not the case, we must explicitly trap &n;&t;* posix_set_acl. SHP&n;&t;*/
r_if
c_cond
(paren
id|cache_iops-&gt;set_ext_attr
op_logical_and
id|filter_iops-&gt;set_ext_attr
)paren
id|cache_filter_iops-&gt;set_ext_attr
op_assign
id|filter_iops-&gt;set_ext_attr
suffix:semicolon
macro_line|#endif
multiline_comment|/* copy dir fops */
id|memcpy
c_func
(paren
id|filter_c2udfops
c_func
(paren
id|cache
)paren
comma
id|cache_fops
comma
r_sizeof
(paren
op_star
id|cache_fops
)paren
)paren
suffix:semicolon
multiline_comment|/* unconditional filtering operations */
id|filter_c2udfops
c_func
(paren
id|cache
)paren
op_member_access_from_pointer
id|ioctl
op_assign
id|filter_fops-&gt;ioctl
suffix:semicolon
id|FEXIT
suffix:semicolon
)brace
DECL|function|filter_setup_file_ops
r_void
id|filter_setup_file_ops
c_func
(paren
r_struct
id|filter_fs
op_star
id|cache
comma
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|inode_operations
op_star
id|filter_iops
comma
r_struct
id|file_operations
op_star
id|filter_fops
)paren
(brace
r_struct
id|inode_operations
op_star
id|pr_iops
suffix:semicolon
r_struct
id|inode_operations
op_star
id|cache_iops
op_assign
id|inode-&gt;i_op
suffix:semicolon
r_struct
id|file_operations
op_star
id|cache_fops
op_assign
id|inode-&gt;i_fop
suffix:semicolon
id|FENTRY
suffix:semicolon
r_if
c_cond
(paren
id|cache-&gt;o_flags
op_amp
id|FILTER_DID_FILE_OPS
)paren
(brace
id|FEXIT
suffix:semicolon
r_return
suffix:semicolon
)brace
id|cache-&gt;o_flags
op_or_assign
id|FILTER_DID_FILE_OPS
suffix:semicolon
multiline_comment|/* steal the old ops */
multiline_comment|/* former ops become cache_ops */
id|cache-&gt;o_caops.cache_file_iops
op_assign
id|cache_iops
suffix:semicolon
id|cache-&gt;o_caops.cache_file_fops
op_assign
id|cache_fops
suffix:semicolon
multiline_comment|/* abbreviate */
id|pr_iops
op_assign
id|filter_c2ufiops
c_func
(paren
id|cache
)paren
suffix:semicolon
multiline_comment|/* setup our dir iops: copy and modify */
id|memcpy
c_func
(paren
id|pr_iops
comma
id|cache_iops
comma
r_sizeof
(paren
op_star
id|cache_iops
)paren
)paren
suffix:semicolon
multiline_comment|/* copy dir fops */
id|CERROR
c_func
(paren
l_string|&quot;*** cache file ops at %p&bslash;n&quot;
comma
id|cache_fops
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|filter_c2uffops
c_func
(paren
id|cache
)paren
comma
id|cache_fops
comma
r_sizeof
(paren
op_star
id|cache_fops
)paren
)paren
suffix:semicolon
multiline_comment|/* assign */
multiline_comment|/* See comments above in filter_setup_dir_ops. SHP */
multiline_comment|/*if (cache_iops-&gt;setattr)*/
id|pr_iops-&gt;setattr
op_assign
id|filter_iops-&gt;setattr
suffix:semicolon
r_if
c_cond
(paren
id|cache_iops-&gt;getattr
)paren
id|pr_iops-&gt;getattr
op_assign
id|filter_iops-&gt;getattr
suffix:semicolon
multiline_comment|/* XXX Should this be conditional rmr ? */
id|pr_iops-&gt;permission
op_assign
id|filter_iops-&gt;permission
suffix:semicolon
macro_line|#ifdef CONFIG_FS_EXT_ATTR
multiline_comment|/* For now we assume that posix acls are handled through extended&n;&t;* attributes. If this is not the case, we must explicitly trap and &n;&t;* posix_set_acl&n;&t;*/
r_if
c_cond
(paren
id|cache_iops-&gt;set_ext_attr
op_logical_and
id|filter_iops-&gt;set_ext_attr
)paren
id|pr_iops-&gt;set_ext_attr
op_assign
id|filter_iops-&gt;set_ext_attr
suffix:semicolon
macro_line|#endif
multiline_comment|/* unconditional filtering operations */
id|filter_c2uffops
c_func
(paren
id|cache
)paren
op_member_access_from_pointer
id|open
op_assign
id|filter_fops-&gt;open
suffix:semicolon
id|filter_c2uffops
c_func
(paren
id|cache
)paren
op_member_access_from_pointer
id|release
op_assign
id|filter_fops-&gt;release
suffix:semicolon
id|filter_c2uffops
c_func
(paren
id|cache
)paren
op_member_access_from_pointer
id|write
op_assign
id|filter_fops-&gt;write
suffix:semicolon
id|filter_c2uffops
c_func
(paren
id|cache
)paren
op_member_access_from_pointer
id|ioctl
op_assign
id|filter_fops-&gt;ioctl
suffix:semicolon
id|FEXIT
suffix:semicolon
)brace
multiline_comment|/* XXX in 2.3 there are &quot;fast&quot; and &quot;slow&quot; symlink ops for ext2 XXX */
DECL|function|filter_setup_symlink_ops
r_void
id|filter_setup_symlink_ops
c_func
(paren
r_struct
id|filter_fs
op_star
id|cache
comma
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|inode_operations
op_star
id|filter_iops
comma
r_struct
id|file_operations
op_star
id|filter_fops
)paren
(brace
r_struct
id|inode_operations
op_star
id|pr_iops
suffix:semicolon
r_struct
id|inode_operations
op_star
id|cache_iops
op_assign
id|inode-&gt;i_op
suffix:semicolon
r_struct
id|file_operations
op_star
id|cache_fops
op_assign
id|inode-&gt;i_fop
suffix:semicolon
id|FENTRY
suffix:semicolon
r_if
c_cond
(paren
id|cache-&gt;o_flags
op_amp
id|FILTER_DID_SYMLINK_OPS
)paren
(brace
id|FEXIT
suffix:semicolon
r_return
suffix:semicolon
)brace
id|cache-&gt;o_flags
op_or_assign
id|FILTER_DID_SYMLINK_OPS
suffix:semicolon
multiline_comment|/* steal the old ops */
id|cache-&gt;o_caops.cache_sym_iops
op_assign
id|cache_iops
suffix:semicolon
id|cache-&gt;o_caops.cache_sym_fops
op_assign
id|cache_fops
suffix:semicolon
multiline_comment|/* abbreviate */
id|pr_iops
op_assign
id|filter_c2usiops
c_func
(paren
id|cache
)paren
suffix:semicolon
multiline_comment|/* setup our dir iops: copy and modify */
id|memcpy
c_func
(paren
id|pr_iops
comma
id|cache_iops
comma
r_sizeof
(paren
op_star
id|cache_iops
)paren
)paren
suffix:semicolon
multiline_comment|/* See comments above in filter_setup_dir_ops. SHP */
multiline_comment|/* if (cache_iops-&gt;setattr) */
id|pr_iops-&gt;setattr
op_assign
id|filter_iops-&gt;setattr
suffix:semicolon
r_if
c_cond
(paren
id|cache_iops-&gt;getattr
)paren
id|pr_iops-&gt;getattr
op_assign
id|filter_iops-&gt;getattr
suffix:semicolon
multiline_comment|/* assign */
multiline_comment|/* copy fops - careful for symlinks they might be NULL */
r_if
c_cond
(paren
id|cache_fops
)paren
(brace
id|memcpy
c_func
(paren
id|filter_c2usfops
c_func
(paren
id|cache
)paren
comma
id|cache_fops
comma
r_sizeof
(paren
op_star
id|cache_fops
)paren
)paren
suffix:semicolon
)brace
id|FEXIT
suffix:semicolon
)brace
DECL|function|filter_setup_dentry_ops
r_void
id|filter_setup_dentry_ops
c_func
(paren
r_struct
id|filter_fs
op_star
id|cache
comma
r_struct
id|dentry_operations
op_star
id|cache_dop
comma
r_struct
id|dentry_operations
op_star
id|filter_dop
)paren
(brace
r_if
c_cond
(paren
id|cache-&gt;o_flags
op_amp
id|FILTER_DID_DENTRY_OPS
)paren
(brace
id|FEXIT
suffix:semicolon
r_return
suffix:semicolon
)brace
id|cache-&gt;o_flags
op_or_assign
id|FILTER_DID_DENTRY_OPS
suffix:semicolon
id|cache-&gt;o_caops.cache_dentry_ops
op_assign
id|cache_dop
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|cache-&gt;o_fops.filter_dentry_ops
comma
id|filter_dop
comma
r_sizeof
(paren
op_star
id|filter_dop
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cache_dop
op_logical_and
id|cache_dop
op_ne
id|filter_dop
op_logical_and
id|cache_dop-&gt;d_revalidate
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;WARNING: filter overriding revalidation!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
eof
