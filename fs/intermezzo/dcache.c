multiline_comment|/* -*- mode: c; c-basic-offset: 8; indent-tabs-mode: nil; -*-&n; * vim:expandtab:shiftwidth=8:tabstop=8:&n; *&n; *  Original version: Copyright (C) 1996 P. Braam and M. Callahan&n; *  Rewritten for Linux 2.1. Copyright (C) 1997 Carnegie Mellon University&n; *  d_fsdata and NFS compatiblity fixes Copyright (C) 2001 Tacit Networks, Inc.&n; *&n; *   This file is part of InterMezzo, http://www.inter-mezzo.org.&n; *&n; *   InterMezzo is free software; you can redistribute it and/or&n; *   modify it under the terms of version 2 of the GNU General Public&n; *   License as published by the Free Software Foundation.&n; *&n; *   InterMezzo is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with InterMezzo; if not, write to the Free Software&n; *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Directory operations for InterMezzo filesystem&n; */
multiline_comment|/* inode dentry alias list walking code adapted from linux/fs/dcache.c&n; *&n; * fs/dcache.c&n; *&n; * (C) 1997 Thomas Schoebel-Theuer,&n; * with heavy changes by Linus Torvalds&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/intermezzo_fs.h&gt;
DECL|variable|presto_dentry_slab
id|kmem_cache_t
op_star
id|presto_dentry_slab
suffix:semicolon
multiline_comment|/* called when a cache lookup succeeds */
DECL|function|presto_d_revalidate
r_static
r_int
id|presto_d_revalidate
c_func
(paren
r_struct
id|dentry
op_star
id|de
comma
r_int
id|flag
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|de-&gt;d_inode
suffix:semicolon
r_struct
id|presto_file_set
op_star
id|root_fset
suffix:semicolon
id|ENTRY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
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
id|is_bad_inode
c_func
(paren
id|inode
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
op_logical_neg
id|presto_d2d
c_func
(paren
id|de
)paren
)paren
(brace
id|presto_set_dd
c_func
(paren
id|de
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|presto_d2d
c_func
(paren
id|de
)paren
)paren
(brace
id|EXIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|root_fset
op_assign
id|presto_d2d
c_func
(paren
id|de-&gt;d_inode-&gt;i_sb-&gt;s_root
)paren
op_member_access_from_pointer
id|dd_fset
suffix:semicolon
r_if
c_cond
(paren
id|root_fset-&gt;fset_flags
op_amp
id|FSET_FLAT_BRANCH
op_logical_and
(paren
id|presto_d2d
c_func
(paren
id|de
)paren
op_member_access_from_pointer
id|dd_fset
op_ne
id|root_fset
)paren
)paren
(brace
id|presto_d2d
c_func
(paren
id|de
)paren
op_member_access_from_pointer
id|dd_fset
op_assign
id|root_fset
suffix:semicolon
)brace
id|EXIT
suffix:semicolon
r_return
l_int|1
suffix:semicolon
macro_line|#if 0
multiline_comment|/* The following is needed for metadata on demand. */
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
id|EXIT
suffix:semicolon
r_return
(paren
id|presto_chk
c_func
(paren
id|de
comma
id|PRESTO_DATA
)paren
op_logical_and
(paren
id|presto_chk
c_func
(paren
id|de
comma
id|PRESTO_ATTR
)paren
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|EXIT
suffix:semicolon
r_return
id|presto_chk
c_func
(paren
id|de
comma
id|PRESTO_ATTR
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|presto_d_release
r_static
r_void
id|presto_d_release
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
op_logical_neg
id|presto_d2d
c_func
(paren
id|dentry
)paren
)paren
(brace
multiline_comment|/* This can happen for dentries from NFSd */
r_return
suffix:semicolon
)brace
id|presto_d2d
c_func
(paren
id|dentry
)paren
op_member_access_from_pointer
id|dd_count
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|presto_d2d
c_func
(paren
id|dentry
)paren
op_member_access_from_pointer
id|dd_count
)paren
(brace
id|kmem_cache_free
c_func
(paren
id|presto_dentry_slab
comma
id|presto_d2d
c_func
(paren
id|dentry
)paren
)paren
suffix:semicolon
id|dentry-&gt;d_fsdata
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|variable|presto_dentry_ops
r_struct
id|dentry_operations
id|presto_dentry_ops
op_assign
(brace
dot
id|d_revalidate
op_assign
id|presto_d_revalidate
comma
dot
id|d_release
op_assign
id|presto_d_release
)brace
suffix:semicolon
DECL|function|presto_is_dentry_ROOT
r_static
r_inline
r_int
id|presto_is_dentry_ROOT
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_return
id|dentry_name_cmp
c_func
(paren
id|dentry
comma
l_string|&quot;ROOT&quot;
)paren
op_logical_and
op_logical_neg
id|dentry_name_cmp
c_func
(paren
id|dentry-&gt;d_parent
comma
l_string|&quot;.intermezzo&quot;
)paren
suffix:semicolon
)brace
DECL|function|presto_try_find_fset
r_static
r_struct
id|presto_file_set
op_star
id|presto_try_find_fset
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_int
op_star
id|is_under_d_intermezzo
)paren
(brace
r_struct
id|dentry
op_star
id|temp_dentry
suffix:semicolon
r_struct
id|presto_dentry_data
op_star
id|d_data
suffix:semicolon
r_int
id|found_root
op_assign
l_int|0
suffix:semicolon
id|ENTRY
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_FSDATA
comma
l_string|&quot;finding fileset for %p:%s&bslash;n&quot;
comma
id|dentry
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
op_star
id|is_under_d_intermezzo
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* walk up through the branch to get the fileset */
multiline_comment|/* The dentry we are passed presumably does not have the correct&n;         * fset information. However, we still want to start walking up&n;         * the branch from this dentry to get our found_root and &n;         * is_under_d_intermezzo decisions correct&n;         */
r_for
c_loop
(paren
id|temp_dentry
op_assign
id|dentry
suffix:semicolon
suffix:semicolon
id|temp_dentry
op_assign
id|temp_dentry-&gt;d_parent
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_FSDATA
comma
l_string|&quot;---&gt;dentry %p:%*s&bslash;n&quot;
comma
id|temp_dentry
comma
id|temp_dentry-&gt;d_name.len
comma
id|temp_dentry-&gt;d_name.name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|presto_is_dentry_ROOT
c_func
(paren
id|temp_dentry
)paren
)paren
id|found_root
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|found_root
op_logical_and
id|dentry_name_cmp
c_func
(paren
id|temp_dentry
comma
l_string|&quot;.intermezzo&quot;
)paren
)paren
(brace
op_star
id|is_under_d_intermezzo
op_assign
l_int|1
suffix:semicolon
)brace
id|d_data
op_assign
id|presto_d2d
c_func
(paren
id|temp_dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|d_data
)paren
(brace
multiline_comment|/* If we found a &quot;ROOT&quot; dentry while walking up the&n;                         * branch, we will journal regardless of whether&n;                         * we are under .intermezzo or not.&n;                         * If we are already under d_intermezzo don&squot;t reverse&n;                         * the decision here...even if we found a &quot;ROOT&quot;&n;                         * dentry above .intermezzo (if we were ever to&n;                         * modify the directory structure).&n;                         */
r_if
c_cond
(paren
op_logical_neg
op_star
id|is_under_d_intermezzo
)paren
op_star
id|is_under_d_intermezzo
op_assign
op_logical_neg
id|found_root
op_logical_and
(paren
id|d_data-&gt;dd_flags
op_amp
id|PRESTO_DONT_JOURNAL
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
id|d_data-&gt;dd_fset
suffix:semicolon
)brace
r_if
c_cond
(paren
id|temp_dentry-&gt;d_parent
op_eq
id|temp_dentry
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
id|EXIT
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Only call this function on positive dentries */
DECL|function|presto_try_find_alias_with_dd
r_static
r_struct
id|presto_dentry_data
op_star
id|presto_try_find_alias_with_dd
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_struct
id|list_head
op_star
id|head
comma
op_star
id|next
comma
op_star
id|tmp
suffix:semicolon
r_struct
id|dentry
op_star
id|tmp_dentry
suffix:semicolon
multiline_comment|/* Search through the alias list for dentries with d_fsdata */
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
id|head
op_assign
op_amp
id|inode-&gt;i_dentry
suffix:semicolon
id|next
op_assign
id|inode-&gt;i_dentry.next
suffix:semicolon
r_while
c_loop
(paren
id|next
op_ne
id|head
)paren
(brace
id|tmp
op_assign
id|next
suffix:semicolon
id|next
op_assign
id|tmp-&gt;next
suffix:semicolon
id|tmp_dentry
op_assign
id|list_entry
c_func
(paren
id|tmp
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
op_logical_neg
id|presto_d2d
c_func
(paren
id|tmp_dentry
)paren
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
r_return
id|presto_d2d
c_func
(paren
id|tmp_dentry
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Only call this function on positive dentries */
DECL|function|presto_set_alias_dd
r_static
r_void
id|presto_set_alias_dd
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|presto_dentry_data
op_star
id|dd
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_struct
id|list_head
op_star
id|head
comma
op_star
id|next
comma
op_star
id|tmp
suffix:semicolon
r_struct
id|dentry
op_star
id|tmp_dentry
suffix:semicolon
multiline_comment|/* Set d_fsdata for this dentry */
id|dd-&gt;dd_count
op_increment
suffix:semicolon
id|dentry-&gt;d_fsdata
op_assign
id|dd
suffix:semicolon
multiline_comment|/* Now set d_fsdata for all dentries in the alias list. */
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
id|head
op_assign
op_amp
id|inode-&gt;i_dentry
suffix:semicolon
id|next
op_assign
id|inode-&gt;i_dentry.next
suffix:semicolon
r_while
c_loop
(paren
id|next
op_ne
id|head
)paren
(brace
id|tmp
op_assign
id|next
suffix:semicolon
id|next
op_assign
id|tmp-&gt;next
suffix:semicolon
id|tmp_dentry
op_assign
id|list_entry
c_func
(paren
id|tmp
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
op_logical_neg
id|presto_d2d
c_func
(paren
id|tmp_dentry
)paren
)paren
(brace
id|dd-&gt;dd_count
op_increment
suffix:semicolon
id|tmp_dentry-&gt;d_fsdata
op_assign
id|dd
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|izo_alloc_ddata
r_inline
r_struct
id|presto_dentry_data
op_star
id|izo_alloc_ddata
c_func
(paren
r_void
)paren
(brace
r_struct
id|presto_dentry_data
op_star
id|dd
suffix:semicolon
id|dd
op_assign
id|kmem_cache_alloc
c_func
(paren
id|presto_dentry_slab
comma
id|SLAB_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dd
op_eq
l_int|NULL
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;IZO: out of memory trying to allocate presto_dentry_data&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|dd
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|dd
)paren
)paren
suffix:semicolon
id|dd-&gt;dd_count
op_assign
l_int|1
suffix:semicolon
r_return
id|dd
suffix:semicolon
)brace
multiline_comment|/* This uses the BKL! */
DECL|function|presto_set_dd
r_int
id|presto_set_dd
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
r_struct
id|presto_dentry_data
op_star
id|dd
suffix:semicolon
r_int
id|is_under_d_izo
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|ENTRY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dentry
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Did we lose a race? */
r_if
c_cond
(paren
id|dentry-&gt;d_fsdata
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;dentry %p already has d_fsdata set&bslash;n&quot;
comma
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_inode
)paren
id|CERROR
c_func
(paren
l_string|&quot;    inode: %ld&bslash;n&quot;
comma
id|dentry-&gt;d_inode-&gt;i_ino
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dentry-&gt;d_inode
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* NFSd runs find_fh_dentry which instantiates disconnected&n;                 * dentries which are then connected without a lookup(). &n;                 * So it is possible to have connected dentries that do not &n;                 * have d_fsdata set. So we walk the list trying to find &n;                 * an alias which has its d_fsdata set and then use that &n;                 * for all the other dentries  as well. &n;                 * - SHP,Vinny. &n;                 */
multiline_comment|/* If there is an alias with d_fsdata use it. */
r_if
c_cond
(paren
(paren
id|dd
op_assign
id|presto_try_find_alias_with_dd
(paren
id|dentry
)paren
)paren
)paren
(brace
id|presto_set_alias_dd
(paren
id|dentry
comma
id|dd
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Negative dentry */
id|CDEBUG
c_func
(paren
id|D_FSDATA
comma
l_string|&quot;negative dentry %p: %*s&bslash;n&quot;
comma
id|dentry
comma
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
)brace
multiline_comment|/* No pre-existing d_fsdata, we need to construct one.&n;         * First, we must walk up the tree to find the fileset &n;         * If a fileset can&squot;t be found, we leave a null fsdata&n;         * and return EROFS to indicate that we can&squot;t journal&n;         * updates. &n;         */
id|fset
op_assign
id|presto_try_find_fset
(paren
id|dentry
comma
op_amp
id|is_under_d_izo
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fset
)paren
(brace
macro_line|#ifdef PRESTO_NO_NFS
id|CERROR
c_func
(paren
l_string|&quot;No fileset for dentry %p: %*s&bslash;n&quot;
comma
id|dentry
comma
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
macro_line|#endif
id|error
op_assign
op_minus
id|EROFS
suffix:semicolon
id|EXIT
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
)brace
id|dentry-&gt;d_fsdata
op_assign
id|izo_alloc_ddata
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|presto_d2d
c_func
(paren
id|dentry
)paren
)paren
(brace
id|CERROR
(paren
l_string|&quot;InterMezzo: out of memory allocating d_fsdata&bslash;n&quot;
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out_unlock
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
r_if
c_cond
(paren
id|is_under_d_izo
)paren
id|presto_d2d
c_func
(paren
id|dentry
)paren
op_member_access_from_pointer
id|dd_flags
op_or_assign
id|PRESTO_DONT_JOURNAL
suffix:semicolon
id|EXIT
suffix:semicolon
id|out_unlock
suffix:colon
id|CDEBUG
c_func
(paren
id|D_FSDATA
comma
l_string|&quot;presto_set_dd dentry %p: %*s, d_fsdata %p&bslash;n&quot;
comma
id|dentry
comma
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_fsdata
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|presto_init_ddata_cache
r_int
id|presto_init_ddata_cache
c_func
(paren
r_void
)paren
(brace
id|ENTRY
suffix:semicolon
id|presto_dentry_slab
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;presto_cache&quot;
comma
r_sizeof
(paren
r_struct
id|presto_dentry_data
)paren
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
(paren
id|presto_dentry_slab
op_ne
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|presto_cleanup_ddata_cache
r_void
id|presto_cleanup_ddata_cache
c_func
(paren
r_void
)paren
(brace
id|kmem_cache_destroy
c_func
(paren
id|presto_dentry_slab
)paren
suffix:semicolon
)brace
eof
