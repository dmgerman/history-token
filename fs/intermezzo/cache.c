multiline_comment|/* -*- mode: c; c-basic-offset: 8; indent-tabs-mode: nil; -*-&n; * vim:expandtab:shiftwidth=8:tabstop=8:&n; *&n; *  Copyright (C) 2000 Stelias Computing, Inc.&n; *  Copyright (C) 2000 Red Hat, Inc.&n; *&n; *   This file is part of InterMezzo, http://www.inter-mezzo.org.&n; *&n; *   InterMezzo is free software; you can redistribute it and/or&n; *   modify it under the terms of version 2 of the GNU General Public&n; *   License as published by the Free Software Foundation.&n; *&n; *   InterMezzo is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with InterMezzo; if not, write to the Free Software&n; *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/module.h&gt;
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
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;intermezzo_fs.h&quot;
macro_line|#include &quot;intermezzo_psdev.h&quot;
multiline_comment|/*&n;   This file contains the routines associated with managing a&n;   cache of files for InterMezzo.  These caches have two reqs:&n;   - need to be found fast so they are hashed by the device, &n;     with an attempt to have collision chains of length 1.&n;   The methods for the cache are set up in methods.&n;*/
r_extern
id|kmem_cache_t
op_star
id|presto_dentry_slab
suffix:semicolon
multiline_comment|/* the intent of this hash is to have collision chains of length 1 */
DECL|macro|CACHES_BITS
mdefine_line|#define CACHES_BITS 8
DECL|macro|CACHES_SIZE
mdefine_line|#define CACHES_SIZE (1 &lt;&lt; CACHES_BITS)
DECL|macro|CACHES_MASK
mdefine_line|#define CACHES_MASK CACHES_SIZE - 1
DECL|variable|presto_caches
r_static
r_struct
id|list_head
id|presto_caches
(braket
id|CACHES_SIZE
)braket
suffix:semicolon
DECL|function|presto_cache_hash
r_static
r_inline
r_int
id|presto_cache_hash
c_func
(paren
r_struct
id|super_block
op_star
id|s
)paren
(brace
r_return
(paren
id|CACHES_MASK
)paren
op_amp
(paren
(paren
r_int
r_int
)paren
id|s
op_rshift
id|L1_CACHE_SHIFT
)paren
suffix:semicolon
)brace
DECL|function|presto_cache_add
r_inline
r_void
id|presto_cache_add
c_func
(paren
r_struct
id|presto_cache
op_star
id|cache
)paren
(brace
id|list_add
c_func
(paren
op_amp
id|cache-&gt;cache_chain
comma
op_amp
id|presto_caches
(braket
id|presto_cache_hash
c_func
(paren
id|cache-&gt;cache_sb
)paren
)braket
)paren
suffix:semicolon
)brace
DECL|function|presto_cache_init_hash
r_inline
r_void
id|presto_cache_init_hash
c_func
(paren
r_void
)paren
(brace
r_int
id|i
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
id|CACHES_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|presto_caches
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* map a device to a cache */
DECL|function|presto_cache_find
r_struct
id|presto_cache
op_star
id|presto_cache_find
c_func
(paren
r_struct
id|super_block
op_star
id|s
)paren
(brace
r_struct
id|presto_cache
op_star
id|cache
suffix:semicolon
r_struct
id|list_head
op_star
id|lh
comma
op_star
id|tmp
suffix:semicolon
id|lh
op_assign
id|tmp
op_assign
op_amp
(paren
id|presto_caches
(braket
id|presto_cache_hash
c_func
(paren
id|s
)paren
)braket
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|tmp
op_assign
id|lh-&gt;next
)paren
op_ne
id|lh
)paren
(brace
id|cache
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|presto_cache
comma
id|cache_chain
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cache-&gt;cache_sb
op_eq
id|s
)paren
r_return
id|cache
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* map an inode to a cache */
DECL|function|presto_get_cache
r_struct
id|presto_cache
op_star
id|presto_get_cache
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
multiline_comment|/* find the correct presto_cache here, based on the device */
id|cache
op_assign
id|presto_cache_find
c_func
(paren
id|inode-&gt;i_sb
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
l_string|&quot;WARNING: no presto cache for %s, ino %ld&bslash;n&quot;
comma
id|inode-&gt;i_sb-&gt;s_id
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|EXIT
suffix:semicolon
r_return
id|cache
suffix:semicolon
)brace
multiline_comment|/* another debugging routine: check fs is InterMezzo fs */
DECL|function|presto_ispresto
r_int
id|presto_ispresto
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
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
l_int|0
suffix:semicolon
id|cache
op_assign
id|presto_get_cache
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cache
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|inode-&gt;i_sb
op_eq
id|cache-&gt;cache_sb
suffix:semicolon
)brace
multiline_comment|/* setup a cache structure when we need one */
DECL|function|presto_cache_init
r_struct
id|presto_cache
op_star
id|presto_cache_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|presto_cache
op_star
id|cache
suffix:semicolon
id|PRESTO_ALLOC
c_func
(paren
id|cache
comma
r_sizeof
(paren
r_struct
id|presto_cache
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cache
)paren
(brace
id|memset
c_func
(paren
id|cache
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|presto_cache
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|cache-&gt;cache_chain
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|cache-&gt;cache_fset_list
)paren
suffix:semicolon
id|cache-&gt;cache_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
id|cache-&gt;cache_reserved
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|cache
suffix:semicolon
)brace
multiline_comment|/* free a cache structure and all of the memory it is pointing to */
DECL|function|presto_free_cache
r_inline
r_void
id|presto_free_cache
c_func
(paren
r_struct
id|presto_cache
op_star
id|cache
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cache
)paren
r_return
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|cache-&gt;cache_chain
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cache-&gt;cache_sb
op_logical_and
id|cache-&gt;cache_sb-&gt;s_root
op_logical_and
id|presto_d2d
c_func
(paren
id|cache-&gt;cache_sb-&gt;s_root
)paren
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
id|cache-&gt;cache_sb-&gt;s_root
)paren
)paren
suffix:semicolon
id|cache-&gt;cache_sb-&gt;s_root-&gt;d_fsdata
op_assign
l_int|NULL
suffix:semicolon
)brace
id|PRESTO_FREE
c_func
(paren
id|cache
comma
r_sizeof
(paren
r_struct
id|presto_cache
)paren
)paren
suffix:semicolon
)brace
DECL|function|presto_reserve_space
r_int
id|presto_reserve_space
c_func
(paren
r_struct
id|presto_cache
op_star
id|cache
comma
id|loff_t
id|req
)paren
(brace
r_struct
id|filter_fs
op_star
id|filter
suffix:semicolon
id|loff_t
id|avail
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
op_assign
id|cache-&gt;cache_sb
suffix:semicolon
id|filter
op_assign
id|cache-&gt;cache_filter
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|filter
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
id|filter-&gt;o_trops
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
id|filter-&gt;o_trops-&gt;tr_avail
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
id|cache-&gt;cache_lock
)paren
suffix:semicolon
id|avail
op_assign
id|filter-&gt;o_trops
op_member_access_from_pointer
id|tr_avail
c_func
(paren
id|cache
comma
id|sb
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;ESC::%ld +++&gt; %ld &bslash;n&quot;
comma
(paren
r_int
)paren
id|cache-&gt;cache_reserved
comma
(paren
r_int
)paren
(paren
id|cache-&gt;cache_reserved
op_plus
id|req
)paren
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;ESC::Avail::%ld &bslash;n&quot;
comma
(paren
r_int
)paren
id|avail
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req
op_plus
id|cache-&gt;cache_reserved
OG
id|avail
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|cache-&gt;cache_lock
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|cache-&gt;cache_reserved
op_add_assign
id|req
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|cache-&gt;cache_lock
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|presto_release_space
r_void
id|presto_release_space
c_func
(paren
r_struct
id|presto_cache
op_star
id|cache
comma
id|loff_t
id|req
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;ESC::%ld ---&gt; %ld &bslash;n&quot;
comma
(paren
r_int
)paren
id|cache-&gt;cache_reserved
comma
(paren
r_int
)paren
(paren
id|cache-&gt;cache_reserved
op_minus
id|req
)paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|cache-&gt;cache_lock
)paren
suffix:semicolon
id|cache-&gt;cache_reserved
op_sub_assign
id|req
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|cache-&gt;cache_lock
)paren
suffix:semicolon
)brace
eof
