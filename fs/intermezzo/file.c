multiline_comment|/* -*- mode: c; c-basic-offset: 8; indent-tabs-mode: nil; -*-&n; * vim:expandtab:shiftwidth=8:tabstop=8:&n; *&n; *  Copyright (C) 2000 Stelias Computing, Inc.&n; *  Copyright (C) 2000 Red Hat, Inc.&n; *  Copyright (C) 2000 TurboLinux, Inc.&n; *  Copyright (C) 2000 Los Alamos National Laboratory.&n; *  Copyright (C) 2000, 2001 Tacit Networks, Inc.&n; *  Copyright (C) 2000 Peter J. Braam&n; *  Copyright (C) 2001 Mountain View Data, Inc. &n; *  Copyright (C) 2001 Cluster File Systems, Inc. &n; *&n; *   This file is part of InterMezzo, http://www.inter-mezzo.org.&n; *&n; *   InterMezzo is free software; you can redistribute it and/or&n; *   modify it under the terms of version 2 of the GNU General Public&n; *   License as published by the Free Software Foundation.&n; *&n; *   InterMezzo is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with InterMezzo; if not, write to the Free Software&n; *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *  This file manages file I/O&n; * &n; */
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
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fsfilter.h&gt;
macro_line|#include &quot;intermezzo_fs.h&quot;
macro_line|#include &quot;intermezzo_psdev.h&quot;
multiline_comment|/*&n; * these are initialized in super.c&n; */
r_extern
r_int
id|presto_permission
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|mask
comma
r_struct
id|nameidata
op_star
id|nd
)paren
suffix:semicolon
DECL|function|presto_open_upcall
r_static
r_int
id|presto_open_upcall
c_func
(paren
r_int
id|minor
comma
r_struct
id|dentry
op_star
id|de
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|path
comma
op_star
id|buffer
suffix:semicolon
r_struct
id|presto_file_set
op_star
id|fset
suffix:semicolon
r_int
id|pathlen
suffix:semicolon
r_struct
id|lento_vfs_context
id|info
suffix:semicolon
r_struct
id|presto_dentry_data
op_star
id|dd
op_assign
id|presto_d2d
c_func
(paren
id|de
)paren
suffix:semicolon
id|PRESTO_ALLOC
c_func
(paren
id|buffer
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;PRESTO: out of memory!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|fset
op_assign
id|presto_fset
c_func
(paren
id|de
)paren
suffix:semicolon
id|path
op_assign
id|presto_path
c_func
(paren
id|de
comma
id|fset-&gt;fset_dentry
comma
id|buffer
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|pathlen
op_assign
id|MYPATHLEN
c_func
(paren
id|buffer
comma
id|path
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_FILE
comma
l_string|&quot;de %p, dd %p&bslash;n&quot;
comma
id|de
comma
id|dd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dd-&gt;remote_ino
op_eq
l_int|0
)paren
(brace
id|rc
op_assign
id|presto_get_fileid
c_func
(paren
id|minor
comma
id|fset
comma
id|de
)paren
suffix:semicolon
)brace
id|memset
(paren
op_amp
id|info
comma
l_int|0
comma
r_sizeof
(paren
id|info
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dd-&gt;remote_ino
OG
l_int|0
)paren
(brace
id|info.remote_ino
op_assign
id|dd-&gt;remote_ino
suffix:semicolon
id|info.remote_generation
op_assign
id|dd-&gt;remote_generation
suffix:semicolon
)brace
r_else
id|CERROR
c_func
(paren
l_string|&quot;get_fileid failed %d, ino: %Lx, fetching by name&bslash;n&quot;
comma
id|rc
comma
id|dd-&gt;remote_ino
)paren
suffix:semicolon
id|rc
op_assign
id|izo_upc_open
c_func
(paren
id|minor
comma
id|pathlen
comma
id|path
comma
id|fset-&gt;fset_name
comma
op_amp
id|info
)paren
suffix:semicolon
id|PRESTO_FREE
c_func
(paren
id|buffer
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|open_check_dod
r_static
r_inline
r_int
id|open_check_dod
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|presto_file_set
op_star
id|fset
)paren
(brace
r_int
id|gen
comma
id|is_iopen
op_assign
l_int|0
comma
id|minor
suffix:semicolon
r_struct
id|presto_cache
op_star
id|cache
op_assign
id|fset-&gt;fset_cache
suffix:semicolon
id|ino_t
id|inum
suffix:semicolon
id|minor
op_assign
id|presto_c2m
c_func
(paren
id|cache
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ISLENTO
c_func
(paren
id|minor
)paren
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_CACHE
comma
l_string|&quot;is lento, not doing DOD.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Files are only ever opened by inode during backfetches, when by&n;         * definition we have the authoritative copy of the data.  No DOD. */
id|is_iopen
op_assign
id|izo_dentry_is_ilookup
c_func
(paren
id|file-&gt;f_dentry
comma
op_amp
id|inum
comma
op_amp
id|gen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_iopen
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_CACHE
comma
l_string|&quot;doing iopen, not doing DOD.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|fset-&gt;fset_flags
op_amp
id|FSET_DATA_ON_DEMAND
)paren
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_CACHE
comma
l_string|&quot;fileset not on demand.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_TRUNC
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_CACHE
comma
l_string|&quot;fileset dod: O_TRUNC.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|presto_chk
c_func
(paren
id|file-&gt;f_dentry
comma
id|PRESTO_DONT_JOURNAL
)paren
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_CACHE
comma
l_string|&quot;file under .intermezzo, not doing DOD&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|presto_chk
c_func
(paren
id|file-&gt;f_dentry
comma
id|PRESTO_DATA
)paren
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_CACHE
comma
l_string|&quot;PRESTO_DATA is set, not doing DOD.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cache-&gt;cache_filter-&gt;o_trops
op_member_access_from_pointer
id|tr_all_data
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_CACHE
comma
l_string|&quot;file not sparse, not doing DOD.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|presto_file_open
r_static
r_int
id|presto_file_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_struct
id|file_operations
op_star
id|fops
suffix:semicolon
r_struct
id|presto_cache
op_star
id|cache
suffix:semicolon
r_struct
id|presto_file_set
op_star
id|fset
suffix:semicolon
r_struct
id|presto_file_data
op_star
id|fdata
suffix:semicolon
r_int
id|writable
op_assign
(paren
id|file-&gt;f_flags
op_amp
(paren
id|O_RDWR
op_or
id|O_WRONLY
)paren
)paren
suffix:semicolon
r_int
id|minor
comma
id|i
suffix:semicolon
id|ENTRY
suffix:semicolon
r_if
c_cond
(paren
id|presto_prep
c_func
(paren
id|file-&gt;f_dentry
comma
op_amp
id|cache
comma
op_amp
id|fset
)paren
OL
l_int|0
)paren
(brace
id|EXIT
suffix:semicolon
r_return
op_minus
id|EBADF
suffix:semicolon
)brace
id|minor
op_assign
id|presto_c2m
c_func
(paren
id|cache
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_CACHE
comma
l_string|&quot;DATA_OK: %d, ino: %ld, islento: %d&bslash;n&quot;
comma
id|presto_chk
c_func
(paren
id|file-&gt;f_dentry
comma
id|PRESTO_DATA
)paren
comma
id|inode-&gt;i_ino
comma
id|ISLENTO
c_func
(paren
id|minor
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ISLENTO
c_func
(paren
id|minor
)paren
op_logical_and
(paren
id|file-&gt;f_flags
op_amp
id|O_RDWR
op_logical_or
id|file-&gt;f_flags
op_amp
id|O_WRONLY
)paren
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_CACHE
comma
l_string|&quot;calling presto_get_permit&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|presto_get_permit
c_func
(paren
id|inode
)paren
OL
l_int|0
)paren
(brace
id|EXIT
suffix:semicolon
r_return
op_minus
id|EROFS
suffix:semicolon
)brace
id|presto_put_permit
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|open_check_dod
c_func
(paren
id|file
comma
id|fset
)paren
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_CACHE
comma
l_string|&quot;presto_open_upcall&bslash;n&quot;
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_CACHE
comma
l_string|&quot;dentry: %p setting DATA, ATTR&bslash;n&quot;
comma
id|file-&gt;f_dentry
)paren
suffix:semicolon
id|presto_set
c_func
(paren
id|file-&gt;f_dentry
comma
id|PRESTO_ATTR
op_or
id|PRESTO_DATA
)paren
suffix:semicolon
id|rc
op_assign
id|presto_open_upcall
c_func
(paren
id|minor
comma
id|file-&gt;f_dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|EXIT
suffix:semicolon
id|CERROR
c_func
(paren
l_string|&quot;%s: returning error %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|rc
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
)brace
multiline_comment|/* file was truncated upon open: do not refetch */
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_TRUNC
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_CACHE
comma
l_string|&quot;setting DATA, ATTR&bslash;n&quot;
)paren
suffix:semicolon
id|presto_set
c_func
(paren
id|file-&gt;f_dentry
comma
id|PRESTO_ATTR
op_or
id|PRESTO_DATA
)paren
suffix:semicolon
)brace
id|fops
op_assign
id|filter_c2cffops
c_func
(paren
id|cache-&gt;cache_filter
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fops-&gt;open
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_CACHE
comma
l_string|&quot;calling fs open&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
id|fops
op_member_access_from_pointer
id|open
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|EXIT
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|writable
)paren
(brace
id|PRESTO_ALLOC
c_func
(paren
id|fdata
comma
r_sizeof
(paren
op_star
id|fdata
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fdata
)paren
(brace
id|EXIT
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* LOCK: XXX check that the kernel lock protects this alloc */
id|fdata-&gt;fd_do_lml
op_assign
l_int|0
suffix:semicolon
id|fdata-&gt;fd_bytes_written
op_assign
l_int|0
suffix:semicolon
id|fdata-&gt;fd_fsuid
op_assign
id|current-&gt;fsuid
suffix:semicolon
id|fdata-&gt;fd_fsgid
op_assign
id|current-&gt;fsgid
suffix:semicolon
id|fdata-&gt;fd_mode
op_assign
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_mode
suffix:semicolon
id|fdata-&gt;fd_uid
op_assign
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_uid
suffix:semicolon
id|fdata-&gt;fd_gid
op_assign
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_gid
suffix:semicolon
id|fdata-&gt;fd_ngroups
op_assign
id|current-&gt;ngroups
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|current-&gt;ngroups
suffix:semicolon
id|i
op_increment
)paren
id|fdata-&gt;fd_groups
(braket
id|i
)braket
op_assign
id|current-&gt;groups
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ISLENTO
c_func
(paren
id|minor
)paren
)paren
id|fdata-&gt;fd_info.flags
op_assign
id|LENTO_FL_KML
suffix:semicolon
r_else
(brace
multiline_comment|/* this is for the case of DOD, &n;                           reint_close will adjust flags if needed */
id|fdata-&gt;fd_info.flags
op_assign
l_int|0
suffix:semicolon
)brace
id|presto_getversion
c_func
(paren
op_amp
id|fdata-&gt;fd_version
comma
id|inode
)paren
suffix:semicolon
id|file-&gt;private_data
op_assign
id|fdata
suffix:semicolon
)brace
r_else
(brace
id|file-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
)brace
id|EXIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|presto_adjust_lml
r_int
id|presto_adjust_lml
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|lento_vfs_context
op_star
id|info
)paren
(brace
r_struct
id|presto_file_data
op_star
id|fdata
op_assign
(paren
r_struct
id|presto_file_data
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fdata
)paren
(brace
id|EXIT
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|memcpy
c_func
(paren
op_amp
id|fdata-&gt;fd_info
comma
id|info
comma
r_sizeof
(paren
op_star
id|info
)paren
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|presto_file_release
r_static
r_int
id|presto_file_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
id|rc
suffix:semicolon
r_struct
id|file_operations
op_star
id|fops
suffix:semicolon
r_struct
id|presto_cache
op_star
id|cache
suffix:semicolon
r_struct
id|presto_file_set
op_star
id|fset
suffix:semicolon
r_struct
id|presto_file_data
op_star
id|fdata
op_assign
(paren
r_struct
id|presto_file_data
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
id|ENTRY
suffix:semicolon
id|rc
op_assign
id|presto_prep
c_func
(paren
id|file-&gt;f_dentry
comma
op_amp
id|cache
comma
op_amp
id|fset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|EXIT
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
id|fops
op_assign
id|filter_c2cffops
c_func
(paren
id|cache-&gt;cache_filter
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fops
op_logical_and
id|fops-&gt;release
)paren
id|rc
op_assign
id|fops
op_member_access_from_pointer
id|release
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_CACHE
comma
l_string|&quot;islento = %d (minor %d), rc %d, data %p&bslash;n&quot;
comma
id|ISLENTO
c_func
(paren
id|cache-&gt;cache_psdev-&gt;uc_minor
)paren
comma
id|cache-&gt;cache_psdev-&gt;uc_minor
comma
id|rc
comma
id|fdata
)paren
suffix:semicolon
multiline_comment|/* this file was modified: ignore close errors, write KML */
r_if
c_cond
(paren
id|fdata
op_logical_and
id|fdata-&gt;fd_do_lml
)paren
(brace
multiline_comment|/* XXX: remove when lento gets file granularity cd */
r_if
c_cond
(paren
id|presto_get_permit
c_func
(paren
id|inode
)paren
OL
l_int|0
)paren
(brace
id|EXIT
suffix:semicolon
r_return
op_minus
id|EROFS
suffix:semicolon
)brace
id|fdata-&gt;fd_info.updated_time
op_assign
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_mtime
suffix:semicolon
id|rc
op_assign
id|presto_do_close
c_func
(paren
id|fset
comma
id|file
)paren
suffix:semicolon
id|presto_put_permit
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|rc
op_logical_and
id|fdata
)paren
(brace
id|PRESTO_FREE
c_func
(paren
id|fdata
comma
r_sizeof
(paren
op_star
id|fdata
)paren
)paren
suffix:semicolon
id|file-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
)brace
id|EXIT
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|presto_apply_write_policy
r_static
r_void
id|presto_apply_write_policy
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|presto_file_set
op_star
id|fset
comma
id|loff_t
id|res
)paren
(brace
r_struct
id|presto_file_data
op_star
id|fdata
op_assign
(paren
r_struct
id|presto_file_data
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_struct
id|presto_cache
op_star
id|cache
op_assign
id|fset-&gt;fset_cache
suffix:semicolon
r_struct
id|presto_version
id|new_file_ver
suffix:semicolon
r_int
id|error
suffix:semicolon
r_struct
id|rec_info
id|rec
suffix:semicolon
multiline_comment|/* Here we do a journal close after a fixed or a specified&n;         amount of KBytes, currently a global parameter set with&n;         sysctl. If files are open for a long time, this gives added&n;         protection. (XXX todo: per cache, add ioctl, handle&n;         journaling in a thread, add more options etc.)&n;        */
r_if
c_cond
(paren
(paren
id|fset-&gt;fset_flags
op_amp
id|FSET_JCLOSE_ON_WRITE
)paren
op_logical_and
(paren
op_logical_neg
id|ISLENTO
c_func
(paren
id|cache-&gt;cache_psdev-&gt;uc_minor
)paren
)paren
)paren
(brace
id|fdata-&gt;fd_bytes_written
op_add_assign
id|res
suffix:semicolon
r_if
c_cond
(paren
id|fdata-&gt;fd_bytes_written
op_ge
id|fset-&gt;fset_file_maxio
)paren
(brace
id|presto_getversion
c_func
(paren
op_amp
id|new_file_ver
comma
id|file-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
multiline_comment|/* This is really heavy weight and should be fixed&n;                           ASAP. At most we should be recording the number&n;                           of bytes written and not locking the kernel, &n;                           wait for permits, etc, on the write path. SHP&n;                        */
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|presto_get_permit
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
OL
l_int|0
)paren
(brace
id|EXIT
suffix:semicolon
multiline_comment|/* we must be disconnected, not to worry */
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|error
op_assign
id|presto_journal_close
c_func
(paren
op_amp
id|rec
comma
id|fset
comma
id|file
comma
id|file-&gt;f_dentry
comma
op_amp
id|fdata-&gt;fd_version
comma
op_amp
id|new_file_ver
)paren
suffix:semicolon
id|presto_put_permit
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;presto_close: cannot journal close&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* XXX these errors are really bad */
multiline_comment|/* panic(); */
r_return
suffix:semicolon
)brace
id|fdata-&gt;fd_bytes_written
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
DECL|function|presto_file_write
r_static
id|ssize_t
id|presto_file_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|size
comma
id|loff_t
op_star
id|off
)paren
(brace
r_struct
id|rec_info
id|rec
suffix:semicolon
r_int
id|error
suffix:semicolon
r_struct
id|presto_cache
op_star
id|cache
suffix:semicolon
r_struct
id|presto_file_set
op_star
id|fset
suffix:semicolon
r_struct
id|file_operations
op_star
id|fops
suffix:semicolon
id|ssize_t
id|res
suffix:semicolon
r_int
id|do_lml_here
suffix:semicolon
r_void
op_star
id|handle
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|blocks
suffix:semicolon
r_struct
id|presto_file_data
op_star
id|fdata
suffix:semicolon
id|loff_t
id|res_size
suffix:semicolon
id|error
op_assign
id|presto_prep
c_func
(paren
id|file-&gt;f_dentry
comma
op_amp
id|cache
comma
op_amp
id|fset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|EXIT
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|blocks
op_assign
(paren
id|size
op_rshift
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_sb-&gt;s_blocksize_bits
)paren
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* XXX 3 is for ext2 indirect blocks ... */
id|res_size
op_assign
l_int|2
op_star
id|PRESTO_REQHIGH
op_plus
(paren
(paren
id|blocks
op_plus
l_int|3
)paren
op_lshift
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_sb-&gt;s_blocksize_bits
)paren
suffix:semicolon
id|error
op_assign
id|presto_reserve_space
c_func
(paren
id|fset-&gt;fset_cache
comma
id|res_size
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_INODE
comma
l_string|&quot;Reserved %Ld for %d&bslash;n&quot;
comma
id|res_size
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|EXIT
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|CDEBUG
c_func
(paren
id|D_INODE
comma
l_string|&quot;islento %d, minor: %d&bslash;n&quot;
comma
id|ISLENTO
c_func
(paren
id|cache-&gt;cache_psdev-&gt;uc_minor
)paren
comma
id|cache-&gt;cache_psdev-&gt;uc_minor
)paren
suffix:semicolon
multiline_comment|/* &n;         *  XXX this lock should become a per inode lock when &n;         *  Vinny&squot;s changes are in; we could just use i_sem.&n;         */
id|read_lock
c_func
(paren
op_amp
id|fset-&gt;fset_lml.fd_lock
)paren
suffix:semicolon
id|fdata
op_assign
(paren
r_struct
id|presto_file_data
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
id|do_lml_here
op_assign
id|size
op_logical_and
(paren
id|fdata-&gt;fd_do_lml
op_eq
l_int|0
)paren
op_logical_and
op_logical_neg
id|presto_chk
c_func
(paren
id|file-&gt;f_dentry
comma
id|PRESTO_DONT_JOURNAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|do_lml_here
)paren
id|fdata-&gt;fd_do_lml
op_assign
l_int|1
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|fset-&gt;fset_lml.fd_lock
)paren
suffix:semicolon
multiline_comment|/* XXX &n;           There might be a bug here.  We need to make &n;           absolutely sure that the ext3_file_write commits &n;           after our transaction that writes the LML record.&n;           Nesting the file write helps if new blocks are allocated. &n;        */
id|res
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|do_lml_here
)paren
(brace
r_struct
id|presto_version
id|file_version
suffix:semicolon
multiline_comment|/* handle different space reqs from file system below! */
id|handle
op_assign
id|presto_trans_start
c_func
(paren
id|fset
comma
id|file-&gt;f_dentry-&gt;d_inode
comma
id|KML_OPCODE_WRITE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|handle
)paren
)paren
(brace
id|presto_release_space
c_func
(paren
id|fset-&gt;fset_cache
comma
id|res_size
)paren
suffix:semicolon
id|CERROR
c_func
(paren
l_string|&quot;presto_write: no space for transaction&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|presto_getversion
c_func
(paren
op_amp
id|file_version
comma
id|file-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
id|res
op_assign
id|presto_write_lml_close
c_func
(paren
op_amp
id|rec
comma
id|fset
comma
id|file
comma
id|fdata-&gt;fd_info.remote_ino
comma
id|fdata-&gt;fd_info.remote_generation
comma
op_amp
id|fdata-&gt;fd_info.remote_version
comma
op_amp
id|file_version
)paren
suffix:semicolon
id|fdata-&gt;fd_lml_offset
op_assign
id|rec.offset
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;intermezzo: PANIC failed to write LML&bslash;n&quot;
)paren
suffix:semicolon
op_star
(paren
r_int
op_star
)paren
l_int|0
op_assign
l_int|1
suffix:semicolon
id|EXIT
suffix:semicolon
r_goto
id|exit_write
suffix:semicolon
)brace
id|presto_trans_commit
c_func
(paren
id|fset
comma
id|handle
)paren
suffix:semicolon
)brace
id|fops
op_assign
id|filter_c2cffops
c_func
(paren
id|cache-&gt;cache_filter
)paren
suffix:semicolon
id|res
op_assign
id|fops
op_member_access_from_pointer
id|write
c_func
(paren
id|file
comma
id|buf
comma
id|size
comma
id|off
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
op_ne
id|size
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_FILE
comma
l_string|&quot;file write returns short write: size %d, res %d&bslash;n&quot;
comma
id|size
comma
id|res
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|res
OG
l_int|0
)paren
op_logical_and
id|fdata
)paren
id|presto_apply_write_policy
c_func
(paren
id|file
comma
id|fset
comma
id|res
)paren
suffix:semicolon
id|exit_write
suffix:colon
id|presto_release_space
c_func
(paren
id|fset-&gt;fset_cache
comma
id|res_size
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|variable|presto_file_fops
r_struct
id|file_operations
id|presto_file_fops
op_assign
(brace
dot
id|write
op_assign
id|presto_file_write
comma
dot
id|open
op_assign
id|presto_file_open
comma
dot
id|release
op_assign
id|presto_file_release
comma
dot
id|ioctl
op_assign
id|presto_ioctl
)brace
suffix:semicolon
DECL|variable|presto_file_iops
r_struct
id|inode_operations
id|presto_file_iops
op_assign
(brace
dot
id|permission
op_assign
id|presto_permission
comma
dot
id|setattr
op_assign
id|presto_setattr
comma
macro_line|#ifdef CONFIG_FS_EXT_ATTR
dot
id|set_ext_attr
op_assign
id|presto_set_ext_attr
comma
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* FIXME: I bet we want to add a lock here and in presto_file_open. */
DECL|function|izo_purge_file
r_int
id|izo_purge_file
c_func
(paren
r_struct
id|presto_file_set
op_star
id|fset
comma
r_char
op_star
id|file
)paren
(brace
macro_line|#if 0
r_void
op_star
id|handle
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|path
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|nameidata
id|nd
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
comma
id|len
suffix:semicolon
id|loff_t
id|oldsize
suffix:semicolon
multiline_comment|/* FIXME: not mtpt it&squot;s gone */
id|len
op_assign
id|strlen
c_func
(paren
id|fset-&gt;fset_cache-&gt;cache_mtpt
)paren
op_plus
id|strlen
c_func
(paren
id|file
)paren
op_plus
l_int|1
suffix:semicolon
id|PRESTO_ALLOC
c_func
(paren
id|path
comma
id|len
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|path
op_eq
l_int|NULL
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|sprintf
c_func
(paren
id|path
comma
l_string|&quot;%s/%s&quot;
comma
id|fset-&gt;fset_cache-&gt;cache_mtpt
comma
id|file
)paren
suffix:semicolon
id|rc
op_assign
id|izo_lookup_file
c_func
(paren
id|fset
comma
id|path
comma
op_amp
id|nd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_goto
id|error
suffix:semicolon
id|dentry
op_assign
id|nd.dentry
suffix:semicolon
multiline_comment|/* FIXME: take a lock here */
r_if
c_cond
(paren
id|dentry-&gt;d_inode-&gt;i_atime.tv_sec
OG
id|get_seconds
c_func
(paren
)paren
op_minus
l_int|5
)paren
(brace
multiline_comment|/* We lost the race; this file was accessed while we were doing&n;                 * ioctls and lookups and whatnot. */
id|rc
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|error_unlock
suffix:semicolon
)brace
multiline_comment|/* FIXME: Check if this file is open. */
id|handle
op_assign
id|presto_trans_start
c_func
(paren
id|fset
comma
id|dentry-&gt;d_inode
comma
id|KML_OPCODE_TRUNC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|handle
)paren
)paren
(brace
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|error_unlock
suffix:semicolon
)brace
multiline_comment|/* FIXME: Write LML record */
id|oldsize
op_assign
id|dentry-&gt;d_inode-&gt;i_size
suffix:semicolon
id|rc
op_assign
id|izo_do_truncate
c_func
(paren
id|fset
comma
id|dentry
comma
l_int|0
comma
id|oldsize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
r_goto
id|error_clear
suffix:semicolon
id|rc
op_assign
id|izo_do_truncate
c_func
(paren
id|fset
comma
id|dentry
comma
id|oldsize
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
r_goto
id|error_clear
suffix:semicolon
id|error_clear
suffix:colon
multiline_comment|/* FIXME: clear LML record */
id|error_unlock
suffix:colon
multiline_comment|/* FIXME: release the lock here */
id|error
suffix:colon
r_if
c_cond
(paren
id|handle
op_ne
l_int|NULL
op_logical_and
op_logical_neg
id|IS_ERR
c_func
(paren
id|handle
)paren
)paren
id|presto_trans_commit
c_func
(paren
id|fset
comma
id|handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|path
op_ne
l_int|NULL
)paren
id|PRESTO_FREE
c_func
(paren
id|path
comma
id|len
op_plus
l_int|1
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
macro_line|#else
r_return
l_int|0
suffix:semicolon
macro_line|#endif
)brace
eof
