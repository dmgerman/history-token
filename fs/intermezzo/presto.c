multiline_comment|/* -*- mode: c; c-basic-offset: 8; indent-tabs-mode: nil; -*-&n; * vim:expandtab:shiftwidth=8:tabstop=8:&n; *&n; *  Author: Peter J. Braam &lt;braam@clusterfs.com&gt;&n; *  Copyright (C) 1998 Stelias Computing Inc&n; *  Copyright (C) 1999 Red Hat Inc.&n; *&n; *   This file is part of InterMezzo, http://www.inter-mezzo.org.&n; *&n; *   InterMezzo is free software; you can redistribute it and/or&n; *   modify it under the terms of version 2 of the GNU General Public&n; *   License as published by the Free Software Foundation.&n; *&n; *   InterMezzo is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with InterMezzo; if not, write to the Free Software&n; *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * This file implements basic routines supporting the semantics&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/namei.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &quot;intermezzo_fs.h&quot;
macro_line|#include &quot;intermezzo_psdev.h&quot;
DECL|function|presto_walk
r_int
id|presto_walk
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|nameidata
op_star
id|nd
)paren
(brace
r_int
id|err
suffix:semicolon
multiline_comment|/* we do not follow symlinks to support symlink operations &n;           correctly. The vfs should always hand us resolved dentries&n;           so we should not be required to use LOOKUP_FOLLOW. At the&n;           reintegrating end, lento again should be working with the &n;           resolved pathname and not the symlink. SHP&n;           XXX: This code implies that direct symlinks do not work. SHP&n;        */
r_int
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
singleline_comment|//LOOKUP_POSITIVE;
id|ENTRY
suffix:semicolon
id|err
op_assign
id|path_lookup
c_func
(paren
id|name
comma
id|flags
comma
id|nd
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* find the presto minor device for this inode */
DECL|function|presto_i2m
r_int
id|presto_i2m
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|presto_cache
op_star
id|cache
suffix:semicolon
id|ENTRY
suffix:semicolon
id|cache
op_assign
id|presto_get_cache
c_func
(paren
id|inode
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;&bslash;n&quot;
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
l_string|&quot;PRESTO: BAD: cannot find cache for dev %s, ino %ld&bslash;n&quot;
comma
id|inode-&gt;i_sb-&gt;s_id
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|EXIT
suffix:semicolon
r_return
id|cache-&gt;cache_psdev-&gt;uc_minor
suffix:semicolon
)brace
DECL|function|presto_f2m
r_inline
r_int
id|presto_f2m
c_func
(paren
r_struct
id|presto_file_set
op_star
id|fset
)paren
(brace
r_return
id|fset-&gt;fset_cache-&gt;cache_psdev-&gt;uc_minor
suffix:semicolon
)brace
DECL|function|presto_c2m
r_inline
r_int
id|presto_c2m
c_func
(paren
r_struct
id|presto_cache
op_star
id|cache
)paren
(brace
r_return
id|cache-&gt;cache_psdev-&gt;uc_minor
suffix:semicolon
)brace
multiline_comment|/* XXX check this out */
DECL|function|presto_path2fileset
r_struct
id|presto_file_set
op_star
id|presto_path2fileset
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|nameidata
id|nd
suffix:semicolon
r_struct
id|presto_file_set
op_star
id|fileset
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
id|name
comma
op_amp
id|nd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
macro_line|#if 0
id|error
op_assign
id|do_revalidate
c_func
(paren
id|nd.dentry
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|fileset
op_assign
id|presto_fset
c_func
(paren
id|nd.dentry
)paren
suffix:semicolon
id|path_release
c_func
(paren
op_amp
id|nd
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
)brace
r_else
id|fileset
op_assign
id|ERR_PTR
c_func
(paren
id|error
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
id|fileset
suffix:semicolon
)brace
multiline_comment|/* check a flag on this dentry or fset root.  Semantics:&n;   - most flags: test if it is set&n;   - PRESTO_ATTR, PRESTO_DATA return 1 if PRESTO_FSETINSYNC is set&n;*/
DECL|function|presto_chk
r_int
id|presto_chk
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|flag
)paren
(brace
r_int
id|minor
suffix:semicolon
r_struct
id|presto_file_set
op_star
id|fset
op_assign
id|presto_fset
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|ENTRY
suffix:semicolon
id|minor
op_assign
id|presto_i2m
c_func
(paren
id|dentry-&gt;d_inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|izo_channels
(braket
id|minor
)braket
dot
id|uc_no_filter
)paren
(brace
id|EXIT
suffix:semicolon
r_return
op_complement
l_int|0
suffix:semicolon
)brace
multiline_comment|/* if the fileset is in sync DATA and ATTR are OK */
r_if
c_cond
(paren
id|fset
op_logical_and
(paren
id|flag
op_eq
id|PRESTO_ATTR
op_logical_or
id|flag
op_eq
id|PRESTO_DATA
)paren
op_logical_and
(paren
id|fset-&gt;fset_flags
op_amp
id|FSET_INSYNC
)paren
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_INODE
comma
l_string|&quot;fset in sync (ino %ld)!&bslash;n&quot;
comma
id|fset-&gt;fset_dentry-&gt;d_inode-&gt;i_ino
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|EXIT
suffix:semicolon
r_return
(paren
id|presto_d2d
c_func
(paren
id|dentry
)paren
op_member_access_from_pointer
id|dd_flags
op_amp
id|flag
)paren
suffix:semicolon
)brace
multiline_comment|/* set a bit in the dentry flags */
DECL|function|presto_set
r_void
id|presto_set
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|flag
)paren
(brace
id|ENTRY
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_inode
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_INODE
comma
l_string|&quot;SET ino %ld, flag %x&bslash;n&quot;
comma
id|dentry-&gt;d_inode-&gt;i_ino
comma
id|flag
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
l_string|&quot;dentry without d_fsdata in presto_set: %p: %*s&quot;
comma
id|dentry
comma
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|presto_d2d
c_func
(paren
id|dentry
)paren
op_member_access_from_pointer
id|dd_flags
op_or_assign
id|flag
suffix:semicolon
id|EXIT
suffix:semicolon
)brace
multiline_comment|/* given a path: complete the closes on the fset */
DECL|function|lento_complete_closes
r_int
id|lento_complete_closes
c_func
(paren
r_char
op_star
id|path
)paren
(brace
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
id|error
suffix:semicolon
r_struct
id|presto_file_set
op_star
id|fset
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
id|out_complete
suffix:semicolon
)brace
id|fset
op_assign
id|presto_fset
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|EINVAL
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
l_string|&quot;No fileset!&bslash;n&quot;
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_goto
id|out_complete
suffix:semicolon
)brace
multiline_comment|/* transactions and locking are internal to this function */
id|error
op_assign
id|presto_complete_lml
c_func
(paren
id|fset
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
id|out_complete
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
macro_line|#if 0
multiline_comment|/* given a path: write a close record and cancel an LML record, finally&n;   call truncate LML.  Lento is doing this so it goes in with uid/gid&squot;s &n;   root. &n;*/
r_int
id|lento_cancel_lml
c_func
(paren
r_char
op_star
id|path
comma
id|__u64
id|lml_offset
comma
id|__u64
id|remote_ino
comma
id|__u32
id|remote_generation
comma
id|__u32
id|remote_version
comma
r_struct
id|lento_vfs_context
op_star
id|info
)paren
(brace
r_struct
id|nameidata
id|nd
suffix:semicolon
r_struct
id|rec_info
id|rec
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
r_int
id|error
suffix:semicolon
r_struct
id|presto_file_set
op_star
id|fset
suffix:semicolon
r_void
op_star
id|handle
suffix:semicolon
r_struct
id|presto_version
id|new_ver
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
id|out_cancel_lml
suffix:semicolon
)brace
id|fset
op_assign
id|presto_fset
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|fset
op_eq
l_int|NULL
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;No fileset!&bslash;n&quot;
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_goto
id|out_cancel_lml
suffix:semicolon
)brace
multiline_comment|/* this only requires a transaction below which is automatic */
id|handle
op_assign
id|presto_trans_start
c_func
(paren
id|fset
comma
id|dentry-&gt;d_inode
comma
id|PRESTO_OP_RELEASE
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
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|EXIT
suffix:semicolon
r_goto
id|out_cancel_lml
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;flags
op_amp
id|LENTO_FL_CANCEL_LML
)paren
(brace
id|error
op_assign
id|presto_clear_lml_close
c_func
(paren
id|fset
comma
id|lml_offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|presto_trans_commit
c_func
(paren
id|fset
comma
id|handle
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_goto
id|out_cancel_lml
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|info-&gt;flags
op_amp
id|LENTO_FL_WRITE_KML
)paren
(brace
id|presto_getversion
c_func
(paren
op_amp
id|new_ver
comma
id|dentry-&gt;d_inode
)paren
suffix:semicolon
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
l_int|NULL
comma
id|dentry
comma
op_amp
id|new_ver
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
id|presto_trans_commit
c_func
(paren
id|fset
comma
id|handle
)paren
suffix:semicolon
r_goto
id|out_cancel_lml
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|info-&gt;flags
op_amp
id|LENTO_FL_WRITE_EXPECT
)paren
(brace
id|error
op_assign
id|presto_write_last_rcvd
c_func
(paren
op_amp
id|rec
comma
id|fset
comma
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
(brace
id|EXIT
suffix:semicolon
id|presto_trans_commit
c_func
(paren
id|fset
comma
id|handle
)paren
suffix:semicolon
r_goto
id|out_cancel_lml
suffix:semicolon
)brace
)brace
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
id|info-&gt;flags
op_amp
id|LENTO_FL_CANCEL_LML
)paren
(brace
id|presto_truncate_lml
c_func
(paren
id|fset
)paren
suffix:semicolon
)brace
id|out_cancel_lml
suffix:colon
id|EXIT
suffix:semicolon
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
macro_line|#endif 
multiline_comment|/* given a dentry, operate on the flags in its dentry.  Used by downcalls */
DECL|function|izo_mark_dentry
r_int
id|izo_mark_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|and_flag
comma
r_int
id|or_flag
comma
r_int
op_star
id|res
)paren
(brace
r_int
id|error
op_assign
l_int|0
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
id|CERROR
c_func
(paren
l_string|&quot;InterMezzo: no ddata for inode %ld in %s&bslash;n&quot;
comma
id|dentry-&gt;d_inode-&gt;i_ino
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|CDEBUG
c_func
(paren
id|D_INODE
comma
l_string|&quot;inode: %ld, and flag %x, or flag %x, dd_flags %x&bslash;n&quot;
comma
id|dentry-&gt;d_inode-&gt;i_ino
comma
id|and_flag
comma
id|or_flag
comma
id|presto_d2d
c_func
(paren
id|dentry
)paren
op_member_access_from_pointer
id|dd_flags
)paren
suffix:semicolon
id|presto_d2d
c_func
(paren
id|dentry
)paren
op_member_access_from_pointer
id|dd_flags
op_and_assign
id|and_flag
suffix:semicolon
id|presto_d2d
c_func
(paren
id|dentry
)paren
op_member_access_from_pointer
id|dd_flags
op_or_assign
id|or_flag
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
op_star
id|res
op_assign
id|presto_d2d
c_func
(paren
id|dentry
)paren
op_member_access_from_pointer
id|dd_flags
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/* given a path, operate on the flags in its cache.  Used by mark_ioctl */
DECL|function|izo_mark_cache
r_int
id|izo_mark_cache
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|and_flag
comma
r_int
id|or_flag
comma
r_int
op_star
id|res
)paren
(brace
r_struct
id|presto_cache
op_star
id|cache
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
id|CERROR
c_func
(paren
l_string|&quot;InterMezzo: no ddata for inode %ld in %s&bslash;n&quot;
comma
id|dentry-&gt;d_inode-&gt;i_ino
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|CDEBUG
c_func
(paren
id|D_INODE
comma
l_string|&quot;inode: %ld, and flag %x, or flag %x, dd_flags %x&bslash;n&quot;
comma
id|dentry-&gt;d_inode-&gt;i_ino
comma
id|and_flag
comma
id|or_flag
comma
id|presto_d2d
c_func
(paren
id|dentry
)paren
op_member_access_from_pointer
id|dd_flags
)paren
suffix:semicolon
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
l_string|&quot;PRESTO: BAD: cannot find cache in izo_mark_cache&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBADF
suffix:semicolon
)brace
(paren
(paren
r_int
)paren
id|cache-&gt;cache_flags
)paren
op_and_assign
id|and_flag
suffix:semicolon
(paren
(paren
r_int
)paren
id|cache-&gt;cache_flags
)paren
op_or_assign
id|or_flag
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
op_star
id|res
op_assign
(paren
r_int
)paren
id|cache-&gt;cache_flags
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|presto_set_max_kml_size
r_int
id|presto_set_max_kml_size
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
r_int
id|max_size
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
id|presto_path2fileset
c_func
(paren
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|fset
)paren
)paren
(brace
id|EXIT
suffix:semicolon
r_return
id|PTR_ERR
c_func
(paren
id|fset
)paren
suffix:semicolon
)brace
id|fset-&gt;kml_truncate_size
op_assign
id|max_size
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_CACHE
comma
l_string|&quot;KML truncate size set to %lu bytes for fset %s.&bslash;n&quot;
comma
id|max_size
comma
id|path
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|izo_mark_fset
r_int
id|izo_mark_fset
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|and_flag
comma
r_int
id|or_flag
comma
r_int
op_star
id|res
)paren
(brace
r_struct
id|presto_file_set
op_star
id|fset
suffix:semicolon
id|fset
op_assign
id|presto_fset
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
id|CERROR
c_func
(paren
l_string|&quot;PRESTO: BAD: cannot find cache in izo_mark_cache&bslash;n&quot;
)paren
suffix:semicolon
id|make_bad_inode
c_func
(paren
id|dentry-&gt;d_inode
)paren
suffix:semicolon
r_return
op_minus
id|EBADF
suffix:semicolon
)brace
(paren
(paren
r_int
)paren
id|fset-&gt;fset_flags
)paren
op_and_assign
id|and_flag
suffix:semicolon
(paren
(paren
r_int
)paren
id|fset-&gt;fset_flags
)paren
op_or_assign
id|or_flag
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
op_star
id|res
op_assign
(paren
r_int
)paren
id|fset-&gt;fset_flags
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* talk to Lento about the permit */
DECL|function|presto_permit_upcall
r_static
r_int
id|presto_permit_upcall
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_int
id|rc
suffix:semicolon
r_char
op_star
id|path
comma
op_star
id|buffer
suffix:semicolon
r_int
id|pathlen
suffix:semicolon
r_int
id|minor
suffix:semicolon
r_int
id|fsetnamelen
suffix:semicolon
r_struct
id|presto_file_set
op_star
id|fset
op_assign
l_int|NULL
suffix:semicolon
id|ENTRY
suffix:semicolon
r_if
c_cond
(paren
(paren
id|minor
op_assign
id|presto_i2m
c_func
(paren
id|dentry-&gt;d_inode
)paren
)paren
OL
l_int|0
)paren
(brace
id|EXIT
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|fset
op_assign
id|presto_fset
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
id|ENOTCONN
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|presto_lento_up
c_func
(paren
id|minor
)paren
)paren
(brace
r_if
c_cond
(paren
id|fset-&gt;fset_flags
op_amp
id|FSET_STEAL_PERMIT
)paren
(brace
id|EXIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|EXIT
suffix:semicolon
r_return
op_minus
id|ENOTCONN
suffix:semicolon
)brace
)brace
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
id|EXIT
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|path
op_assign
id|presto_path
c_func
(paren
id|dentry
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
id|fsetnamelen
op_assign
id|strlen
c_func
(paren
id|fset-&gt;fset_name
)paren
suffix:semicolon
id|rc
op_assign
id|izo_upc_permit
c_func
(paren
id|minor
comma
id|dentry
comma
id|pathlen
comma
id|path
comma
id|fset-&gt;fset_name
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
id|EXIT
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/* get a write permit for the fileset of this inode&n; *  - if this returns a negative value there was an error&n; *  - if 0 is returned the permit was already in the kernel -- or --&n; *    Lento gave us the permit without reintegration&n; *  - lento returns the number of records it reintegrated &n; *&n; * Note that if this fileset has branches, a permit will -never- to a normal&n; * process for writing in the data area (ie, outside of .intermezzo)&n; */
DECL|function|presto_get_permit
r_int
id|presto_get_permit
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|dentry
op_star
id|de
suffix:semicolon
r_struct
id|presto_file_set
op_star
id|fset
suffix:semicolon
r_int
id|minor
op_assign
id|presto_i2m
c_func
(paren
id|inode
)paren
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
id|ENTRY
suffix:semicolon
r_if
c_cond
(paren
id|minor
OL
l_int|0
)paren
(brace
id|EXIT
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
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
id|EXIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|inode-&gt;i_dentry
)paren
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;No alias for inode %d&bslash;n&quot;
comma
(paren
r_int
)paren
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|de
op_assign
id|list_entry
c_func
(paren
id|inode-&gt;i_dentry.next
comma
r_struct
id|dentry
comma
id|d_alias
)paren
suffix:semicolon
r_if
c_cond
(paren
id|presto_chk
c_func
(paren
id|de
comma
id|PRESTO_DONT_JOURNAL
)paren
)paren
(brace
id|EXIT
suffix:semicolon
r_return
l_int|0
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
l_string|&quot;Presto: no fileset in presto_get_permit!&bslash;n&quot;
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fset-&gt;fset_flags
op_amp
id|FSET_HAS_BRANCHES
)paren
(brace
id|EXIT
suffix:semicolon
r_return
op_minus
id|EROFS
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|fset-&gt;fset_permit_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fset-&gt;fset_flags
op_amp
id|FSET_HASPERMIT
)paren
(brace
id|fset-&gt;fset_permit_count
op_increment
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_INODE
comma
l_string|&quot;permit count now %d, inode %lx&bslash;n&quot;
comma
id|fset-&gt;fset_permit_count
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|fset-&gt;fset_permit_lock
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Allow reintegration to proceed without locks -SHP */
id|fset-&gt;fset_permit_upcall_count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|fset-&gt;fset_permit_upcall_count
op_eq
l_int|1
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|fset-&gt;fset_permit_lock
)paren
suffix:semicolon
id|rc
op_assign
id|presto_permit_upcall
c_func
(paren
id|fset-&gt;fset_dentry
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|fset-&gt;fset_permit_lock
)paren
suffix:semicolon
id|fset-&gt;fset_permit_upcall_count
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
(brace
id|izo_mark_fset
c_func
(paren
id|fset-&gt;fset_dentry
comma
op_complement
l_int|0
comma
id|FSET_HASPERMIT
comma
l_int|NULL
)paren
suffix:semicolon
id|fset-&gt;fset_permit_count
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|rc
op_eq
id|ENOTCONN
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;InterMezzo: disconnected operation. stealing permit.&bslash;n&quot;
)paren
suffix:semicolon
id|izo_mark_fset
c_func
(paren
id|fset-&gt;fset_dentry
comma
op_complement
l_int|0
comma
id|FSET_HASPERMIT
comma
l_int|NULL
)paren
suffix:semicolon
id|fset-&gt;fset_permit_count
op_increment
suffix:semicolon
multiline_comment|/* set a disconnected flag here to stop upcalls */
id|rc
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|CERROR
c_func
(paren
l_string|&quot;InterMezzo: presto_permit_upcall failed: %d&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EROFS
suffix:semicolon
multiline_comment|/* go to sleep here and try again? */
)brace
id|wake_up_interruptible
c_func
(paren
op_amp
id|fset-&gt;fset_permit_queue
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Someone is already doing an upcall; go to sleep. */
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|fset-&gt;fset_permit_lock
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|fset-&gt;fset_permit_queue
comma
op_amp
id|wait
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|fset-&gt;fset_permit_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fset-&gt;fset_permit_upcall_count
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|fset-&gt;fset_permit_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|remove_wait_queue
c_func
(paren
op_amp
id|fset-&gt;fset_permit_queue
comma
op_amp
id|wait
)paren
suffix:semicolon
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
)brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|remove_wait_queue
c_func
(paren
op_amp
id|fset-&gt;fset_permit_queue
comma
op_amp
id|wait
)paren
suffix:semicolon
multiline_comment|/* We&squot;ve been woken up: do we have the permit? */
r_if
c_cond
(paren
id|fset-&gt;fset_flags
op_amp
id|FSET_HASPERMIT
)paren
multiline_comment|/* FIXME: Is this the right thing? */
id|rc
op_assign
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|CDEBUG
c_func
(paren
id|D_INODE
comma
l_string|&quot;permit count now %d, ino %ld (likely 1), &quot;
l_string|&quot;rc %d&bslash;n&quot;
comma
id|fset-&gt;fset_permit_count
comma
id|inode-&gt;i_ino
comma
id|rc
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|fset-&gt;fset_permit_lock
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|presto_put_permit
r_int
id|presto_put_permit
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|dentry
op_star
id|de
suffix:semicolon
r_struct
id|presto_file_set
op_star
id|fset
suffix:semicolon
r_int
id|minor
op_assign
id|presto_i2m
c_func
(paren
id|inode
)paren
suffix:semicolon
id|ENTRY
suffix:semicolon
r_if
c_cond
(paren
id|minor
OL
l_int|0
)paren
(brace
id|EXIT
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
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
id|EXIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|inode-&gt;i_dentry
)paren
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;No alias for inode %d&bslash;n&quot;
comma
(paren
r_int
)paren
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|de
op_assign
id|list_entry
c_func
(paren
id|inode-&gt;i_dentry.next
comma
r_struct
id|dentry
comma
id|d_alias
)paren
suffix:semicolon
id|fset
op_assign
id|presto_fset
c_func
(paren
id|de
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
l_string|&quot;InterMezzo: no fileset in %s!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|presto_chk
c_func
(paren
id|de
comma
id|PRESTO_DONT_JOURNAL
)paren
)paren
(brace
id|EXIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|fset-&gt;fset_permit_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fset-&gt;fset_flags
op_amp
id|FSET_HASPERMIT
)paren
(brace
r_if
c_cond
(paren
id|fset-&gt;fset_permit_count
OG
l_int|0
)paren
id|fset-&gt;fset_permit_count
op_decrement
suffix:semicolon
r_else
id|CERROR
c_func
(paren
l_string|&quot;Put permit while permit count is 0, &quot;
l_string|&quot;inode %ld!&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
)brace
r_else
(brace
id|fset-&gt;fset_permit_count
op_assign
l_int|0
suffix:semicolon
id|CERROR
c_func
(paren
l_string|&quot;InterMezzo: put permit while no permit, inode %ld, &quot;
l_string|&quot;flags %x!&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|fset-&gt;fset_flags
)paren
suffix:semicolon
)brace
id|CDEBUG
c_func
(paren
id|D_INODE
comma
l_string|&quot;permit count now %d, inode %ld&bslash;n&quot;
comma
id|fset-&gt;fset_permit_count
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fset-&gt;fset_flags
op_amp
id|FSET_PERMIT_WAITING
op_logical_and
id|fset-&gt;fset_permit_count
op_eq
l_int|0
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_INODE
comma
l_string|&quot;permit count now 0, ino %ld, wake sleepers&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|fset-&gt;fset_permit_queue
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|fset-&gt;fset_permit_lock
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|presto_getversion
r_void
id|presto_getversion
c_func
(paren
r_struct
id|presto_version
op_star
id|presto_version
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|presto_version-&gt;pv_mtime_sec
op_assign
id|inode-&gt;i_mtime.tv_sec
suffix:semicolon
id|presto_version-&gt;pv_mtime_nsec
op_assign
id|inode-&gt;i_mtime.tv_nsec
suffix:semicolon
id|presto_version-&gt;pv_ctime_sec
op_assign
id|inode-&gt;i_ctime.tv_sec
suffix:semicolon
id|presto_version-&gt;pv_ctime_nsec
op_assign
id|inode-&gt;i_ctime.tv_nsec
suffix:semicolon
id|presto_version-&gt;pv_size
op_assign
(paren
id|__u64
)paren
id|inode-&gt;i_size
suffix:semicolon
)brace
multiline_comment|/* If uuid is non-null, it is the uuid of the peer that&squot;s making the revocation&n; * request.  If it is null, this request was made locally, without external&n; * pressure to give up the permit.  This most often occurs when a client&n; * starts up.&n; *&n; * FIXME: this function needs to be refactored slightly once we start handling&n; * multiple clients.&n; */
DECL|function|izo_revoke_permit
r_int
id|izo_revoke_permit
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
id|__u8
id|uuid
(braket
l_int|16
)braket
)paren
(brace
r_struct
id|presto_file_set
op_star
id|fset
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_int
id|minor
comma
id|rc
suffix:semicolon
id|ENTRY
suffix:semicolon
id|minor
op_assign
id|presto_i2m
c_func
(paren
id|dentry-&gt;d_inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|minor
OL
l_int|0
)paren
(brace
id|EXIT
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|fset
op_assign
id|presto_fset
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fset
op_eq
l_int|NULL
)paren
(brace
id|EXIT
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|fset-&gt;fset_permit_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fset-&gt;fset_flags
op_amp
id|FSET_PERMIT_WAITING
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;InterMezzo: Two processes are waiting on the same permit--this not yet supported!  Aborting this particular permit request...&bslash;n&quot;
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|fset-&gt;fset_permit_lock
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fset-&gt;fset_permit_count
op_eq
l_int|0
)paren
r_goto
id|got_permit
suffix:semicolon
multiline_comment|/* Something is still using this permit.  Mark that we&squot;re waiting for it&n;         * and go to sleep. */
id|rc
op_assign
id|izo_mark_fset
c_func
(paren
id|dentry
comma
op_complement
l_int|0
comma
id|FSET_PERMIT_WAITING
comma
l_int|NULL
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|fset-&gt;fset_permit_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
(brace
id|EXIT
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
id|add_wait_queue
c_func
(paren
op_amp
id|fset-&gt;fset_permit_queue
comma
op_amp
id|wait
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|fset-&gt;fset_permit_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fset-&gt;fset_permit_count
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|fset-&gt;fset_permit_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
multiline_comment|/* FIXME: there must be a better thing to return... */
id|remove_wait_queue
c_func
(paren
op_amp
id|fset-&gt;fset_permit_queue
comma
op_amp
id|wait
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
)brace
multiline_comment|/* FIXME: maybe there should be a timeout here. */
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|remove_wait_queue
c_func
(paren
op_amp
id|fset-&gt;fset_permit_queue
comma
op_amp
id|wait
)paren
suffix:semicolon
id|got_permit
suffix:colon
multiline_comment|/* By this point fset-&gt;fset_permit_count is zero and we&squot;re holding the&n;         * lock. */
id|CDEBUG
c_func
(paren
id|D_CACHE
comma
l_string|&quot;InterMezzo: releasing permit inode %ld&bslash;n&quot;
comma
id|dentry-&gt;d_inode-&gt;i_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
id|uuid
op_ne
l_int|NULL
)paren
(brace
id|rc
op_assign
id|izo_upc_revoke_permit
c_func
(paren
id|minor
comma
id|fset-&gt;fset_name
comma
id|uuid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|fset-&gt;fset_permit_lock
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
)brace
id|izo_mark_fset
c_func
(paren
id|fset-&gt;fset_dentry
comma
op_complement
id|FSET_PERMIT_WAITING
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|izo_mark_fset
c_func
(paren
id|fset-&gt;fset_dentry
comma
op_complement
id|FSET_HASPERMIT
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|fset-&gt;fset_permit_lock
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|presto_is_read_only
r_inline
r_int
id|presto_is_read_only
c_func
(paren
r_struct
id|presto_file_set
op_star
id|fset
)paren
(brace
r_int
id|minor
comma
id|mask
suffix:semicolon
r_struct
id|presto_cache
op_star
id|cache
op_assign
id|fset-&gt;fset_cache
suffix:semicolon
id|minor
op_assign
id|cache-&gt;cache_psdev-&gt;uc_minor
suffix:semicolon
id|mask
op_assign
(paren
id|ISLENTO
c_func
(paren
id|minor
)paren
ques
c_cond
id|FSET_LENTO_RO
suffix:colon
id|FSET_CLIENT_RO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fset-&gt;fset_flags
op_amp
id|mask
)paren
r_return
l_int|1
suffix:semicolon
id|mask
op_assign
(paren
id|ISLENTO
c_func
(paren
id|minor
)paren
ques
c_cond
id|CACHE_LENTO_RO
suffix:colon
id|CACHE_CLIENT_RO
)paren
suffix:semicolon
r_return
(paren
(paren
id|cache-&gt;cache_flags
op_amp
id|mask
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
eof
