multiline_comment|/* -*- mode: c; c-basic-offset: 8; indent-tabs-mode: nil; -*-&n; * vim:expandtab:shiftwidth=8:tabstop=8:&n; *&n; *  Copyright (C) 2001 Cluster File Systems, Inc. &lt;braam@clusterfs.com&gt;&n; *&n; *   This file is part of InterMezzo, http://www.inter-mezzo.org.&n; *&n; *   InterMezzo is free software; you can redistribute it and/or&n; *   modify it under the terms of version 2 of the GNU General Public&n; *   License as published by the Free Software Foundation.&n; *&n; *   InterMezzo is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with InterMezzo; if not, write to the Free Software&n; *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *  Managing filesets&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/namei.h&gt;
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
macro_line|#include &quot;intermezzo_fs.h&quot;
macro_line|#include &quot;intermezzo_psdev.h&quot;
DECL|function|presto_dentry2fset
r_static
r_inline
r_struct
id|presto_file_set
op_star
id|presto_dentry2fset
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_if
c_cond
(paren
id|presto_d2d
c_func
(paren
id|dentry
)paren
op_eq
l_int|NULL
)paren
(brace
id|EXIT
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|presto_d2d
c_func
(paren
id|dentry
)paren
op_member_access_from_pointer
id|dd_fset
suffix:semicolon
)brace
multiline_comment|/* find the fileset dentry for this dentry */
DECL|function|presto_fset
r_struct
id|presto_file_set
op_star
id|presto_fset
c_func
(paren
r_struct
id|dentry
op_star
id|de
)paren
(brace
r_struct
id|dentry
op_star
id|fsde
suffix:semicolon
id|ENTRY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|de-&gt;d_inode
)paren
(brace
multiline_comment|/* FIXME: is this ok to be NULL? */
id|CDEBUG
c_func
(paren
id|D_INODE
comma
l_string|&quot;presto_fset: warning %*s has NULL inode.&bslash;n&quot;
comma
id|de-&gt;d_name.len
comma
id|de-&gt;d_name.name
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|fsde
op_assign
id|de
suffix:semicolon
suffix:semicolon
id|fsde
op_assign
id|fsde-&gt;d_parent
)paren
(brace
r_if
c_cond
(paren
id|presto_dentry2fset
c_func
(paren
id|fsde
)paren
)paren
(brace
id|EXIT
suffix:semicolon
r_return
id|presto_dentry2fset
c_func
(paren
id|fsde
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fsde-&gt;d_parent
op_eq
id|fsde
)paren
r_break
suffix:semicolon
)brace
id|EXIT
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|presto_get_lastrecno
r_int
id|presto_get_lastrecno
c_func
(paren
r_char
op_star
id|path
comma
id|off_t
op_star
id|recno
)paren
(brace
r_struct
id|nameidata
id|nd
suffix:semicolon
r_struct
id|presto_file_set
op_star
id|fset
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
r_int
id|error
suffix:semicolon
id|ENTRY
suffix:semicolon
id|error
op_assign
id|presto_walk
c_func
(paren
id|path
comma
op_amp
id|nd
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
id|dentry
op_assign
id|nd.dentry
suffix:semicolon
id|error
op_assign
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|presto_ispresto
c_func
(paren
id|dentry-&gt;d_inode
)paren
)paren
(brace
id|EXIT
suffix:semicolon
r_goto
id|kml_out
suffix:semicolon
)brace
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|presto_dentry2fset
c_func
(paren
id|dentry
)paren
)paren
(brace
id|EXIT
suffix:semicolon
r_goto
id|kml_out
suffix:semicolon
)brace
id|fset
op_assign
id|presto_dentry2fset
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fset
)paren
(brace
id|EXIT
suffix:semicolon
r_goto
id|kml_out
suffix:semicolon
)brace
id|error
op_assign
l_int|0
suffix:semicolon
op_star
id|recno
op_assign
id|fset-&gt;fset_kml.fd_recno
suffix:semicolon
id|kml_out
suffix:colon
id|path_release
c_func
(paren
op_amp
id|nd
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|_izo_make_path
r_static
r_char
op_star
id|_izo_make_path
c_func
(paren
r_char
op_star
id|fsetname
comma
r_char
op_star
id|name
)paren
(brace
r_char
op_star
id|path
op_assign
l_int|NULL
suffix:semicolon
r_int
id|len
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
l_string|&quot;/.intermezzo/&quot;
)paren
op_plus
id|strlen
c_func
(paren
id|fsetname
)paren
op_plus
l_int|1
op_plus
id|strlen
c_func
(paren
id|name
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
l_int|NULL
suffix:semicolon
id|sprintf
c_func
(paren
id|path
comma
l_string|&quot;/.intermezzo/%s/%s&quot;
comma
id|fsetname
comma
id|name
)paren
suffix:semicolon
r_return
id|path
suffix:semicolon
)brace
DECL|function|izo_make_path
r_char
op_star
id|izo_make_path
c_func
(paren
r_struct
id|presto_file_set
op_star
id|fset
comma
r_char
op_star
id|name
)paren
(brace
r_return
id|_izo_make_path
c_func
(paren
id|fset-&gt;fset_name
comma
id|name
)paren
suffix:semicolon
)brace
DECL|function|_izo_fset_open
r_static
r_struct
id|file
op_star
id|_izo_fset_open
c_func
(paren
r_char
op_star
id|fsetname
comma
r_char
op_star
id|name
comma
r_int
id|flags
comma
r_int
id|mode
)paren
(brace
r_char
op_star
id|path
suffix:semicolon
r_struct
id|file
op_star
id|f
suffix:semicolon
r_int
id|error
suffix:semicolon
id|ENTRY
suffix:semicolon
id|path
op_assign
id|_izo_make_path
c_func
(paren
id|fsetname
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|path
op_eq
l_int|NULL
)paren
(brace
id|EXIT
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
id|CDEBUG
c_func
(paren
id|D_INODE
comma
l_string|&quot;opening file %s&bslash;n&quot;
comma
id|path
)paren
suffix:semicolon
id|f
op_assign
id|filp_open
c_func
(paren
id|path
comma
id|flags
comma
id|mode
)paren
suffix:semicolon
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|f
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|f
)paren
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_INODE
comma
l_string|&quot;Error %d&bslash;n&quot;
comma
id|error
)paren
suffix:semicolon
)brace
id|PRESTO_FREE
c_func
(paren
id|path
comma
id|strlen
c_func
(paren
id|path
)paren
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
id|f
suffix:semicolon
)brace
DECL|function|izo_fset_open
r_struct
id|file
op_star
id|izo_fset_open
c_func
(paren
r_struct
id|presto_file_set
op_star
id|fset
comma
r_char
op_star
id|name
comma
r_int
id|flags
comma
r_int
id|mode
)paren
(brace
r_return
id|_izo_fset_open
c_func
(paren
id|fset-&gt;fset_name
comma
id|name
comma
id|flags
comma
id|mode
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  note: this routine &quot;pins&quot; a dentry for a fileset root&n; */
DECL|function|presto_set_fsetroot
r_int
id|presto_set_fsetroot
c_func
(paren
r_struct
id|dentry
op_star
id|ioctl_dentry
comma
r_char
op_star
id|fsetname
comma
r_int
r_int
id|flags
)paren
(brace
r_struct
id|presto_file_set
op_star
id|fset
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|presto_cache
op_star
id|cache
suffix:semicolon
r_int
id|error
suffix:semicolon
r_struct
id|file
op_star
id|fset_root
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
id|ENTRY
suffix:semicolon
id|fset_root
op_assign
id|_izo_fset_open
c_func
(paren
id|fsetname
comma
l_string|&quot;ROOT&quot;
comma
id|O_RDONLY
comma
l_int|000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|fset_root
)paren
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;Can&squot;t open %s/ROOT&bslash;n&quot;
comma
id|fsetname
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|fset_root
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|dentry
op_assign
id|dget
c_func
(paren
id|fset_root-&gt;f_dentry
)paren
suffix:semicolon
id|filp_close
c_func
(paren
id|fset_root
comma
l_int|NULL
)paren
suffix:semicolon
id|dentry-&gt;d_inode-&gt;i_op
op_assign
id|ioctl_dentry-&gt;d_inode-&gt;i_op
suffix:semicolon
id|dentry-&gt;d_inode-&gt;i_fop
op_assign
id|ioctl_dentry-&gt;d_inode-&gt;i_fop
suffix:semicolon
id|dentry-&gt;d_op
op_assign
id|ioctl_dentry-&gt;d_op
suffix:semicolon
id|fset
op_assign
id|presto_dentry2fset
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fset
op_logical_and
(paren
id|fset-&gt;fset_dentry
op_eq
id|dentry
)paren
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;Fsetroot already set (inode %ld)&bslash;n&quot;
comma
id|dentry-&gt;d_inode-&gt;i_ino
)paren
suffix:semicolon
multiline_comment|/* XXX: ignore because clear_fsetroot is broken  */
macro_line|#if 0
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
id|error
op_assign
op_minus
id|EEXIST
suffix:semicolon
r_goto
id|out
suffix:semicolon
macro_line|#endif
)brace
id|cache
op_assign
id|presto_get_cache
c_func
(paren
id|dentry-&gt;d_inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cache
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;No cache found for inode %ld&bslash;n&quot;
comma
id|dentry-&gt;d_inode-&gt;i_ino
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
id|error
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
id|PRESTO_ALLOC
c_func
(paren
id|fset
comma
r_sizeof
(paren
op_star
id|fset
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fset
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;No memory allocating fset for %s&bslash;n&quot;
comma
id|fsetname
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
id|CDEBUG
c_func
(paren
id|D_INODE
comma
l_string|&quot;fset at %p&bslash;n&quot;
comma
id|fset
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_INODE
comma
l_string|&quot;InterMezzo: fsetroot: inode %ld, fileset name %s&bslash;n&quot;
comma
id|dentry-&gt;d_inode-&gt;i_ino
comma
id|fsetname
)paren
suffix:semicolon
id|fset-&gt;fset_mnt
op_assign
id|mntget
c_func
(paren
id|current-&gt;fs-&gt;pwdmnt
)paren
suffix:semicolon
id|fset-&gt;fset_cache
op_assign
id|cache
suffix:semicolon
id|fset-&gt;fset_dentry
op_assign
id|dentry
suffix:semicolon
id|fset-&gt;fset_name
op_assign
id|strdup
c_func
(paren
id|fsetname
)paren
suffix:semicolon
id|fset-&gt;fset_chunkbits
op_assign
id|CHUNK_BITS
suffix:semicolon
id|fset-&gt;fset_flags
op_assign
id|flags
suffix:semicolon
id|fset-&gt;fset_file_maxio
op_assign
id|FSET_DEFAULT_MAX_FILEIO
suffix:semicolon
id|fset-&gt;fset_permit_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
id|PRESTO_ALLOC
c_func
(paren
id|fset-&gt;fset_reint_buf
comma
l_int|64
op_star
l_int|1024
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fset-&gt;fset_reint_buf
op_eq
l_int|NULL
)paren
(brace
id|EXIT
suffix:semicolon
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
id|init_waitqueue_head
c_func
(paren
op_amp
id|fset-&gt;fset_permit_queue
)paren
suffix:semicolon
r_if
c_cond
(paren
id|presto_d2d
c_func
(paren
id|dentry
)paren
op_eq
l_int|NULL
)paren
(brace
id|dentry-&gt;d_fsdata
op_assign
id|izo_alloc_ddata
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|presto_d2d
c_func
(paren
id|dentry
)paren
op_eq
l_int|NULL
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;InterMezzo: %s: no memory&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
id|presto_d2d
c_func
(paren
id|dentry
)paren
op_member_access_from_pointer
id|dd_fset
op_assign
id|fset
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|fset-&gt;fset_list
comma
op_amp
id|cache-&gt;cache_fset_list
)paren
suffix:semicolon
id|error
op_assign
id|izo_init_kml_file
c_func
(paren
id|fset
comma
op_amp
id|fset-&gt;fset_kml
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
id|CDEBUG
c_func
(paren
id|D_JOURNAL
comma
l_string|&quot;Error init_kml %d&bslash;n&quot;
comma
id|error
)paren
suffix:semicolon
r_goto
id|out_list_del
suffix:semicolon
)brace
id|error
op_assign
id|izo_init_lml_file
c_func
(paren
id|fset
comma
op_amp
id|fset-&gt;fset_lml
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
r_int
id|rc
suffix:semicolon
id|EXIT
suffix:semicolon
id|rc
op_assign
id|izo_log_close
c_func
(paren
op_amp
id|fset-&gt;fset_kml
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_JOURNAL
comma
l_string|&quot;Error init_lml %d, cleanup %d&bslash;n&quot;
comma
id|error
comma
id|rc
)paren
suffix:semicolon
r_goto
id|out_list_del
suffix:semicolon
)brace
multiline_comment|/* init_last_rcvd_file could trigger a presto_file_write(), which&n;         * requires that the lml structure be initialized. -phil */
id|error
op_assign
id|izo_init_last_rcvd_file
c_func
(paren
id|fset
comma
op_amp
id|fset-&gt;fset_rcvd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
r_int
id|rc
suffix:semicolon
id|EXIT
suffix:semicolon
id|rc
op_assign
id|izo_log_close
c_func
(paren
op_amp
id|fset-&gt;fset_kml
)paren
suffix:semicolon
id|rc
op_assign
id|izo_log_close
c_func
(paren
op_amp
id|fset-&gt;fset_lml
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_JOURNAL
comma
l_string|&quot;Error init_lastrcvd %d, cleanup %d&bslash;n&quot;
comma
id|error
comma
id|rc
)paren
suffix:semicolon
r_goto
id|out_list_del
suffix:semicolon
)brace
id|CDEBUG
c_func
(paren
id|D_PIOCTL
comma
l_string|&quot;-------&gt; fset at %p, dentry at %p, mtpt %p,&quot;
l_string|&quot;fset %s, cache %p, presto_d2d(dentry)-&gt;dd_fset %p&bslash;n&quot;
comma
id|fset
comma
id|dentry
comma
id|fset-&gt;fset_dentry
comma
id|fset-&gt;fset_name
comma
id|cache
comma
id|presto_d2d
c_func
(paren
id|dentry
)paren
op_member_access_from_pointer
id|dd_fset
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_list_del
suffix:colon
id|list_del
c_func
(paren
op_amp
id|fset-&gt;fset_list
)paren
suffix:semicolon
id|presto_d2d
c_func
(paren
id|dentry
)paren
op_member_access_from_pointer
id|dd_fset
op_assign
l_int|NULL
suffix:semicolon
id|out_free
suffix:colon
r_if
c_cond
(paren
id|fset
)paren
(brace
id|mntput
c_func
(paren
id|fset-&gt;fset_mnt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fset-&gt;fset_reint_buf
op_ne
l_int|NULL
)paren
id|PRESTO_FREE
c_func
(paren
id|fset-&gt;fset_reint_buf
comma
l_int|64
op_star
l_int|1024
)paren
suffix:semicolon
id|PRESTO_FREE
c_func
(paren
id|fset
comma
r_sizeof
(paren
op_star
id|fset
)paren
)paren
suffix:semicolon
)brace
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
DECL|function|izo_cleanup_fset
r_static
r_int
id|izo_cleanup_fset
c_func
(paren
r_struct
id|presto_file_set
op_star
id|fset
)paren
(brace
r_int
id|error
suffix:semicolon
r_struct
id|presto_cache
op_star
id|cache
suffix:semicolon
id|ENTRY
suffix:semicolon
id|CERROR
c_func
(paren
l_string|&quot;Cleaning up fset %s&bslash;n&quot;
comma
id|fset-&gt;fset_name
)paren
suffix:semicolon
id|error
op_assign
id|izo_log_close
c_func
(paren
op_amp
id|fset-&gt;fset_kml
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
id|CERROR
c_func
(paren
l_string|&quot;InterMezzo: Closing kml for fset %s: %d&bslash;n&quot;
comma
id|fset-&gt;fset_name
comma
id|error
)paren
suffix:semicolon
id|error
op_assign
id|izo_log_close
c_func
(paren
op_amp
id|fset-&gt;fset_lml
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
id|CERROR
c_func
(paren
l_string|&quot;InterMezzo: Closing lml for fset %s: %d&bslash;n&quot;
comma
id|fset-&gt;fset_name
comma
id|error
)paren
suffix:semicolon
id|error
op_assign
id|izo_log_close
c_func
(paren
op_amp
id|fset-&gt;fset_rcvd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
id|CERROR
c_func
(paren
l_string|&quot;InterMezzo: Closing last_rcvd for fset %s: %d&bslash;n&quot;
comma
id|fset-&gt;fset_name
comma
id|error
)paren
suffix:semicolon
id|cache
op_assign
id|fset-&gt;fset_cache
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|fset-&gt;fset_list
)paren
suffix:semicolon
id|presto_d2d
c_func
(paren
id|fset-&gt;fset_dentry
)paren
op_member_access_from_pointer
id|dd_fset
op_assign
l_int|NULL
suffix:semicolon
id|dput
c_func
(paren
id|fset-&gt;fset_dentry
)paren
suffix:semicolon
id|mntput
c_func
(paren
id|fset-&gt;fset_mnt
)paren
suffix:semicolon
id|PRESTO_FREE
c_func
(paren
id|fset-&gt;fset_name
comma
id|strlen
c_func
(paren
id|fset-&gt;fset_name
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|PRESTO_FREE
c_func
(paren
id|fset-&gt;fset_reint_buf
comma
l_int|64
op_star
l_int|1024
)paren
suffix:semicolon
id|PRESTO_FREE
c_func
(paren
id|fset
comma
r_sizeof
(paren
op_star
id|fset
)paren
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|izo_clear_fsetroot
r_int
id|izo_clear_fsetroot
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_struct
id|presto_file_set
op_star
id|fset
suffix:semicolon
id|ENTRY
suffix:semicolon
id|fset
op_assign
id|presto_dentry2fset
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fset
)paren
(brace
id|EXIT
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|izo_cleanup_fset
c_func
(paren
id|fset
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|izo_clear_all_fsetroots
r_int
id|izo_clear_all_fsetroots
c_func
(paren
r_struct
id|presto_cache
op_star
id|cache
)paren
(brace
r_struct
id|presto_file_set
op_star
id|fset
suffix:semicolon
r_struct
id|list_head
op_star
id|tmp
comma
op_star
id|tmpnext
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
id|tmp
op_assign
op_amp
id|cache-&gt;cache_fset_list
suffix:semicolon
id|tmpnext
op_assign
id|tmp-&gt;next
suffix:semicolon
r_while
c_loop
(paren
id|tmpnext
op_ne
op_amp
id|cache-&gt;cache_fset_list
)paren
(brace
id|tmp
op_assign
id|tmpnext
suffix:semicolon
id|tmpnext
op_assign
id|tmp-&gt;next
suffix:semicolon
id|fset
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|presto_file_set
comma
id|fset_list
)paren
suffix:semicolon
id|error
op_assign
id|izo_cleanup_fset
c_func
(paren
id|fset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_break
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|izo_alloc_vfsmnt
r_static
r_struct
id|vfsmount
op_star
id|izo_alloc_vfsmnt
c_func
(paren
r_void
)paren
(brace
r_struct
id|vfsmount
op_star
id|mnt
suffix:semicolon
id|PRESTO_ALLOC
c_func
(paren
id|mnt
comma
r_sizeof
(paren
op_star
id|mnt
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mnt
)paren
(brace
id|memset
c_func
(paren
id|mnt
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|vfsmount
)paren
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|mnt-&gt;mnt_count
comma
l_int|1
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|mnt-&gt;mnt_hash
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|mnt-&gt;mnt_child
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|mnt-&gt;mnt_mounts
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|mnt-&gt;mnt_list
)paren
suffix:semicolon
)brace
r_return
id|mnt
suffix:semicolon
)brace
DECL|function|izo_setup_ctxt
r_static
r_void
id|izo_setup_ctxt
c_func
(paren
r_struct
id|dentry
op_star
id|root
comma
r_struct
id|vfsmount
op_star
id|mnt
comma
r_struct
id|run_ctxt
op_star
id|save
)paren
(brace
r_struct
id|run_ctxt
r_new
suffix:semicolon
id|mnt-&gt;mnt_root
op_assign
id|root
suffix:semicolon
id|mnt-&gt;mnt_sb
op_assign
id|root-&gt;d_inode-&gt;i_sb
suffix:semicolon
id|unlock_super
c_func
(paren
id|mnt-&gt;mnt_sb
)paren
suffix:semicolon
r_new
dot
id|rootmnt
op_assign
id|mnt
suffix:semicolon
r_new
dot
id|root
op_assign
id|root
suffix:semicolon
r_new
dot
id|pwdmnt
op_assign
id|mnt
suffix:semicolon
r_new
dot
id|pwd
op_assign
id|root
suffix:semicolon
r_new
dot
id|fsuid
op_assign
l_int|0
suffix:semicolon
r_new
dot
id|fsgid
op_assign
l_int|0
suffix:semicolon
r_new
dot
id|fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* XXX where can we get the groups from? */
r_new
dot
id|ngroups
op_assign
l_int|0
suffix:semicolon
id|push_ctxt
c_func
(paren
id|save
comma
op_amp
r_new
)paren
suffix:semicolon
)brace
DECL|function|izo_cleanup_ctxt
r_static
r_void
id|izo_cleanup_ctxt
c_func
(paren
r_struct
id|vfsmount
op_star
id|mnt
comma
r_struct
id|run_ctxt
op_star
id|save
)paren
(brace
id|lock_super
c_func
(paren
id|mnt-&gt;mnt_sb
)paren
suffix:semicolon
id|pop_ctxt
c_func
(paren
id|save
)paren
suffix:semicolon
)brace
DECL|function|izo_simple_mkdir
r_static
r_int
id|izo_simple_mkdir
c_func
(paren
r_struct
id|dentry
op_star
id|dir
comma
r_char
op_star
id|name
comma
r_int
id|mode
)paren
(brace
r_struct
id|dentry
op_star
id|dchild
suffix:semicolon
r_int
id|err
suffix:semicolon
id|ENTRY
suffix:semicolon
id|dchild
op_assign
id|lookup_one_len
c_func
(paren
id|name
comma
id|dir
comma
id|strlen
c_func
(paren
id|name
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|dchild
)paren
)paren
(brace
id|EXIT
suffix:semicolon
r_return
id|PTR_ERR
c_func
(paren
id|dchild
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dchild-&gt;d_inode
)paren
(brace
id|dput
c_func
(paren
id|dchild
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
op_minus
id|EEXIST
suffix:semicolon
)brace
id|err
op_assign
id|vfs_mkdir
c_func
(paren
id|dir-&gt;d_inode
comma
id|dchild
comma
id|mode
)paren
suffix:semicolon
id|dput
c_func
(paren
id|dchild
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|izo_simple_symlink
r_static
r_int
id|izo_simple_symlink
c_func
(paren
r_struct
id|dentry
op_star
id|dir
comma
r_char
op_star
id|name
comma
r_char
op_star
id|tgt
)paren
(brace
r_struct
id|dentry
op_star
id|dchild
suffix:semicolon
r_int
id|err
suffix:semicolon
id|ENTRY
suffix:semicolon
id|dchild
op_assign
id|lookup_one_len
c_func
(paren
id|name
comma
id|dir
comma
id|strlen
c_func
(paren
id|name
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|dchild
)paren
)paren
(brace
id|EXIT
suffix:semicolon
r_return
id|PTR_ERR
c_func
(paren
id|dchild
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dchild-&gt;d_inode
)paren
(brace
id|dput
c_func
(paren
id|dchild
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
op_minus
id|EEXIST
suffix:semicolon
)brace
id|err
op_assign
id|vfs_symlink
c_func
(paren
id|dir-&gt;d_inode
comma
id|dchild
comma
id|tgt
)paren
suffix:semicolon
id|dput
c_func
(paren
id|dchild
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * run set_fsetroot in chroot environment&n; */
DECL|function|presto_set_fsetroot_from_ioc
r_int
id|presto_set_fsetroot_from_ioc
c_func
(paren
r_struct
id|dentry
op_star
id|root
comma
r_char
op_star
id|fsetname
comma
r_int
r_int
id|flags
)paren
(brace
r_int
id|rc
suffix:semicolon
r_struct
id|presto_cache
op_star
id|cache
suffix:semicolon
r_struct
id|vfsmount
op_star
id|mnt
suffix:semicolon
r_struct
id|run_ctxt
id|save
suffix:semicolon
r_if
c_cond
(paren
id|root
op_ne
id|root-&gt;d_inode-&gt;i_sb-&gt;s_root
)paren
(brace
id|CERROR
(paren
l_string|&quot;IOC_SET_FSET must be called on mount point&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|cache
op_assign
id|presto_get_cache
c_func
(paren
id|root-&gt;d_inode
)paren
suffix:semicolon
id|mnt
op_assign
id|cache-&gt;cache_vfsmount
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mnt
)paren
(brace
id|EXIT
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|izo_setup_ctxt
c_func
(paren
id|root
comma
id|mnt
comma
op_amp
id|save
)paren
suffix:semicolon
id|rc
op_assign
id|presto_set_fsetroot
c_func
(paren
id|root
comma
id|fsetname
comma
id|flags
)paren
suffix:semicolon
id|izo_cleanup_ctxt
c_func
(paren
id|mnt
comma
op_amp
id|save
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/* XXX: this function should detect if fsetname is already in use for&n;   the cache under root&n;*/
DECL|function|izo_prepare_fileset
r_int
id|izo_prepare_fileset
c_func
(paren
r_struct
id|dentry
op_star
id|root
comma
r_char
op_star
id|fsetname
)paren
(brace
r_int
id|err
suffix:semicolon
r_struct
id|dentry
op_star
id|dotizo
op_assign
l_int|NULL
comma
op_star
id|fsetdir
op_assign
l_int|NULL
comma
op_star
id|dotiopen
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|presto_cache
op_star
id|cache
suffix:semicolon
r_struct
id|vfsmount
op_star
id|mnt
suffix:semicolon
r_struct
id|run_ctxt
id|save
suffix:semicolon
id|cache
op_assign
id|presto_get_cache
c_func
(paren
id|root-&gt;d_inode
)paren
suffix:semicolon
id|mnt
op_assign
id|cache-&gt;cache_vfsmount
op_assign
id|izo_alloc_vfsmnt
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mnt
)paren
(brace
id|EXIT
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|fsetname
)paren
id|fsetname
op_assign
l_string|&quot;rootfset&quot;
suffix:semicolon
id|izo_setup_ctxt
c_func
(paren
id|root
comma
id|mnt
comma
op_amp
id|save
)paren
suffix:semicolon
id|err
op_assign
id|izo_simple_mkdir
c_func
(paren
id|root
comma
l_string|&quot;.intermezzo&quot;
comma
l_int|0755
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_CACHE
comma
l_string|&quot;mkdir on .intermezzo err %d&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
id|err
op_assign
id|izo_simple_mkdir
c_func
(paren
id|root
comma
l_string|&quot;..iopen..&quot;
comma
l_int|0755
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_CACHE
comma
l_string|&quot;mkdir on ..iopen.. err %d&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
id|dotiopen
op_assign
id|lookup_one_len
c_func
(paren
l_string|&quot;..iopen..&quot;
comma
id|root
comma
id|strlen
c_func
(paren
l_string|&quot;..iopen..&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|dotiopen
)paren
)paren
(brace
id|EXIT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|dotiopen-&gt;d_inode-&gt;i_op
op_assign
op_amp
id|presto_dir_iops
suffix:semicolon
id|dput
c_func
(paren
id|dotiopen
)paren
suffix:semicolon
id|dotizo
op_assign
id|lookup_one_len
c_func
(paren
l_string|&quot;.intermezzo&quot;
comma
id|root
comma
id|strlen
c_func
(paren
l_string|&quot;.intermezzo&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|dotizo
)paren
)paren
(brace
id|EXIT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|err
op_assign
id|izo_simple_mkdir
c_func
(paren
id|dotizo
comma
id|fsetname
comma
l_int|0755
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_CACHE
comma
l_string|&quot;mkdir err %d&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
multiline_comment|/* XXX find the dentry of the root of the fileset (root for now) */
id|fsetdir
op_assign
id|lookup_one_len
c_func
(paren
id|fsetname
comma
id|dotizo
comma
id|strlen
c_func
(paren
id|fsetname
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|fsetdir
)paren
)paren
(brace
id|EXIT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|err
op_assign
id|izo_simple_symlink
c_func
(paren
id|fsetdir
comma
l_string|&quot;ROOT&quot;
comma
l_string|&quot;../..&quot;
)paren
suffix:semicolon
multiline_comment|/* XXX read flags from flags file */
id|err
op_assign
id|presto_set_fsetroot
c_func
(paren
id|root
comma
id|fsetname
comma
l_int|0
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_CACHE
comma
l_string|&quot;set_fsetroot err %d&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
id|out
suffix:colon
r_if
c_cond
(paren
id|dotizo
op_logical_and
op_logical_neg
id|IS_ERR
c_func
(paren
id|dotizo
)paren
)paren
id|dput
c_func
(paren
id|dotizo
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fsetdir
op_logical_and
op_logical_neg
id|IS_ERR
c_func
(paren
id|fsetdir
)paren
)paren
id|dput
c_func
(paren
id|fsetdir
)paren
suffix:semicolon
id|izo_cleanup_ctxt
c_func
(paren
id|mnt
comma
op_amp
id|save
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|izo_set_fileid
r_int
id|izo_set_fileid
c_func
(paren
r_struct
id|file
op_star
id|dir
comma
r_struct
id|izo_ioctl_data
op_star
id|data
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_struct
id|presto_cache
op_star
id|cache
suffix:semicolon
r_struct
id|vfsmount
op_star
id|mnt
suffix:semicolon
r_struct
id|run_ctxt
id|save
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
r_struct
id|presto_dentry_data
op_star
id|dd
suffix:semicolon
r_struct
id|dentry
op_star
id|root
suffix:semicolon
r_char
op_star
id|buf
op_assign
l_int|NULL
suffix:semicolon
id|ENTRY
suffix:semicolon
id|root
op_assign
id|dir-&gt;f_dentry
suffix:semicolon
multiline_comment|/* actually, needs to be called on ROOT of fset, not mount point  &n;        if (root != root-&gt;d_inode-&gt;i_sb-&gt;s_root) {&n;                CERROR (&quot;IOC_SET_FSET must be called on mount point&bslash;n&quot;);&n;                return -ENODEV;&n;        }&n;        */
id|cache
op_assign
id|presto_get_cache
c_func
(paren
id|root-&gt;d_inode
)paren
suffix:semicolon
id|mnt
op_assign
id|cache-&gt;cache_vfsmount
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mnt
)paren
(brace
id|EXIT
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|izo_setup_ctxt
c_func
(paren
id|root
comma
id|mnt
comma
op_amp
id|save
)paren
suffix:semicolon
id|PRESTO_ALLOC
c_func
(paren
id|buf
comma
id|data-&gt;ioc_plen1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
(brace
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|EXIT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|buf
comma
id|data-&gt;ioc_pbuf1
comma
id|data-&gt;ioc_plen1
)paren
)paren
(brace
id|rc
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|EXIT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|rc
op_assign
id|presto_walk
c_func
(paren
id|buf
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
(brace
id|CERROR
c_func
(paren
l_string|&quot;Unable to open: %s&bslash;n&quot;
comma
id|buf
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|dentry
op_assign
id|nd.dentry
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dentry
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;no dentry!&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|EXIT
suffix:semicolon
r_goto
id|out_close
suffix:semicolon
)brace
id|dd
op_assign
id|presto_d2d
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dd
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;no dentry_data!&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|EXIT
suffix:semicolon
r_goto
id|out_close
suffix:semicolon
)brace
id|CDEBUG
c_func
(paren
id|D_FILE
comma
l_string|&quot;de:%p dd:%p&bslash;n&quot;
comma
id|dentry
comma
id|dd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dd-&gt;remote_ino
op_ne
l_int|0
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;remote_ino already set? %Lx:%Lx&bslash;n&quot;
comma
id|dd-&gt;remote_ino
comma
id|dd-&gt;remote_generation
)paren
suffix:semicolon
id|rc
op_assign
l_int|0
suffix:semicolon
id|EXIT
suffix:semicolon
r_goto
id|out_close
suffix:semicolon
)brace
id|CDEBUG
c_func
(paren
id|D_FILE
comma
l_string|&quot;setting %p %p, %s to %Lx:%Lx&bslash;n&quot;
comma
id|dentry
comma
id|dd
comma
id|buf
comma
id|data-&gt;ioc_ino
comma
id|data-&gt;ioc_generation
)paren
suffix:semicolon
id|dd-&gt;remote_ino
op_assign
id|data-&gt;ioc_ino
suffix:semicolon
id|dd-&gt;remote_generation
op_assign
id|data-&gt;ioc_generation
suffix:semicolon
id|EXIT
suffix:semicolon
id|out_close
suffix:colon
id|path_release
c_func
(paren
op_amp
id|nd
)paren
suffix:semicolon
id|out
suffix:colon
r_if
c_cond
(paren
id|buf
)paren
id|PRESTO_FREE
c_func
(paren
id|buf
comma
id|data-&gt;ioc_plen1
)paren
suffix:semicolon
id|izo_cleanup_ctxt
c_func
(paren
id|mnt
comma
op_amp
id|save
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
eof
