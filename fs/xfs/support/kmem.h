multiline_comment|/*&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_SUPPORT_KMEM_H__
DECL|macro|__XFS_SUPPORT_KMEM_H__
mdefine_line|#define __XFS_SUPPORT_KMEM_H__
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
multiline_comment|/*&n; * Cutoff point to use vmalloc instead of kmalloc.&n; */
DECL|macro|MAX_SLAB_SIZE
mdefine_line|#define MAX_SLAB_SIZE&t;0x10000
multiline_comment|/*&n; * XFS uses slightly different names for these due to the&n; * IRIX heritage.&n; */
DECL|macro|kmem_zone
mdefine_line|#define&t;kmem_zone&t;kmem_cache_s
DECL|macro|kmem_zone_t
mdefine_line|#define kmem_zone_t&t;kmem_cache_t
DECL|macro|KM_SLEEP
mdefine_line|#define KM_SLEEP&t;0x0001
DECL|macro|KM_NOSLEEP
mdefine_line|#define KM_NOSLEEP&t;0x0002
DECL|macro|KM_NOFS
mdefine_line|#define KM_NOFS&t;&t;0x0004
DECL|typedef|xfs_pflags_t
r_typedef
r_int
r_int
id|xfs_pflags_t
suffix:semicolon
DECL|macro|PFLAGS_TEST_FSTRANS
mdefine_line|#define PFLAGS_TEST_FSTRANS()&t;&t;(current-&gt;flags &amp; PF_FSTRANS)
DECL|macro|PFLAGS_SET_FSTRANS
mdefine_line|#define PFLAGS_SET_FSTRANS(STATEP) do {&t;&bslash;&n;&t;*(STATEP) = current-&gt;flags;&t;&bslash;&n;&t;current-&gt;flags |= PF_FSTRANS;&t;&bslash;&n;} while (0)
DECL|macro|PFLAGS_RESTORE
mdefine_line|#define PFLAGS_RESTORE(STATEP) do {&t;&bslash;&n;&t;current-&gt;flags = *(STATEP);&t;&bslash;&n;} while (0)
DECL|macro|PFLAGS_DUP
mdefine_line|#define PFLAGS_DUP(OSTATEP, NSTATEP) do { &bslash;&n;&t;*(NSTATEP) = *(OSTATEP);&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * XXX get rid of the unconditional  __GFP_NOFAIL by adding&n; * a KM_FAIL flag and using it where we&squot;re allowed to fail.&n; */
r_static
id|__inline
r_int
r_int
DECL|function|kmem_flags_convert
id|kmem_flags_convert
c_func
(paren
r_int
id|flags
)paren
(brace
r_int
id|lflags
suffix:semicolon
macro_line|#if DEBUG
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|flags
op_amp
op_complement
(paren
id|KM_SLEEP
op_or
id|KM_NOSLEEP
op_or
id|KM_NOFS
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;XFS: memory allocation with wrong flags (%x)&bslash;n&quot;
comma
id|flags
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
id|lflags
op_assign
(paren
id|flags
op_amp
id|KM_NOSLEEP
)paren
ques
c_cond
id|GFP_ATOMIC
suffix:colon
(paren
id|GFP_KERNEL
op_or
id|__GFP_NOFAIL
)paren
suffix:semicolon
multiline_comment|/* avoid recusive callbacks to filesystem during transactions */
r_if
c_cond
(paren
id|PFLAGS_TEST_FSTRANS
c_func
(paren
)paren
)paren
id|lflags
op_and_assign
op_complement
id|__GFP_FS
suffix:semicolon
r_return
id|lflags
suffix:semicolon
)brace
r_static
id|__inline
r_void
op_star
DECL|function|kmem_alloc
id|kmem_alloc
c_func
(paren
r_int
id|size
comma
r_int
id|flags
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|MAX_SLAB_SIZE
OL
id|size
)paren
)paren
multiline_comment|/* Avoid doing filesystem sensitive stuff to get this */
r_return
id|__vmalloc
c_func
(paren
id|size
comma
id|kmem_flags_convert
c_func
(paren
id|flags
)paren
comma
id|PAGE_KERNEL
)paren
suffix:semicolon
r_return
id|kmalloc
c_func
(paren
id|size
comma
id|kmem_flags_convert
c_func
(paren
id|flags
)paren
)paren
suffix:semicolon
)brace
r_static
id|__inline
r_void
op_star
DECL|function|kmem_zalloc
id|kmem_zalloc
c_func
(paren
r_int
id|size
comma
r_int
id|flags
)paren
(brace
r_void
op_star
id|ptr
op_assign
id|kmem_alloc
c_func
(paren
id|size
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|ptr
op_ne
l_int|NULL
)paren
)paren
id|memset
c_func
(paren
id|ptr
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
r_return
id|ptr
suffix:semicolon
)brace
r_static
id|__inline
r_void
DECL|function|kmem_free
id|kmem_free
c_func
(paren
r_void
op_star
id|ptr
comma
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
(paren
r_int
r_int
)paren
id|ptr
OL
id|VMALLOC_START
op_logical_or
(paren
r_int
r_int
)paren
id|ptr
op_ge
id|VMALLOC_END
)paren
)paren
id|kfree
c_func
(paren
id|ptr
)paren
suffix:semicolon
r_else
id|vfree
c_func
(paren
id|ptr
)paren
suffix:semicolon
)brace
r_static
id|__inline
r_void
op_star
DECL|function|kmem_realloc
id|kmem_realloc
c_func
(paren
r_void
op_star
id|ptr
comma
r_int
id|newsize
comma
r_int
id|oldsize
comma
r_int
id|flags
)paren
(brace
r_void
op_star
r_new
op_assign
id|kmem_alloc
c_func
(paren
id|newsize
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|ptr
op_ne
l_int|NULL
)paren
)paren
(brace
r_if
c_cond
(paren
id|likely
c_func
(paren
r_new
op_ne
l_int|NULL
)paren
)paren
id|memcpy
c_func
(paren
r_new
comma
id|ptr
comma
id|min
c_func
(paren
id|oldsize
comma
id|newsize
)paren
)paren
suffix:semicolon
id|kmem_free
c_func
(paren
id|ptr
comma
id|oldsize
)paren
suffix:semicolon
)brace
r_return
r_new
suffix:semicolon
)brace
r_static
id|__inline
id|kmem_zone_t
op_star
DECL|function|kmem_zone_init
id|kmem_zone_init
c_func
(paren
r_int
id|size
comma
r_char
op_star
id|zone_name
)paren
(brace
r_return
id|kmem_cache_create
c_func
(paren
id|zone_name
comma
id|size
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_static
id|__inline
r_void
op_star
DECL|function|kmem_zone_alloc
id|kmem_zone_alloc
c_func
(paren
id|kmem_zone_t
op_star
id|zone
comma
r_int
id|flags
)paren
(brace
r_return
id|kmem_cache_alloc
c_func
(paren
id|zone
comma
id|kmem_flags_convert
c_func
(paren
id|flags
)paren
)paren
suffix:semicolon
)brace
r_static
id|__inline
r_void
op_star
DECL|function|kmem_zone_zalloc
id|kmem_zone_zalloc
c_func
(paren
id|kmem_zone_t
op_star
id|zone
comma
r_int
id|flags
)paren
(brace
r_void
op_star
id|ptr
op_assign
id|kmem_zone_alloc
c_func
(paren
id|zone
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|ptr
op_ne
l_int|NULL
)paren
)paren
id|memset
c_func
(paren
id|ptr
comma
l_int|0
comma
id|kmem_cache_size
c_func
(paren
id|zone
)paren
)paren
suffix:semicolon
r_return
id|ptr
suffix:semicolon
)brace
r_static
id|__inline
r_void
DECL|function|kmem_zone_free
id|kmem_zone_free
c_func
(paren
id|kmem_zone_t
op_star
id|zone
comma
r_void
op_star
id|ptr
)paren
(brace
id|kmem_cache_free
c_func
(paren
id|zone
comma
id|ptr
)paren
suffix:semicolon
)brace
DECL|typedef|kmem_shaker_t
r_typedef
r_struct
id|shrinker
op_star
id|kmem_shaker_t
suffix:semicolon
DECL|typedef|kmem_shake_func_t
r_typedef
r_int
(paren
op_star
id|kmem_shake_func_t
)paren
(paren
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_static
id|__inline
id|kmem_shaker_t
DECL|function|kmem_shake_register
id|kmem_shake_register
c_func
(paren
id|kmem_shake_func_t
id|sfunc
)paren
(brace
r_return
id|set_shrinker
c_func
(paren
id|DEFAULT_SEEKS
comma
id|sfunc
)paren
suffix:semicolon
)brace
r_static
id|__inline
r_void
DECL|function|kmem_shake_deregister
id|kmem_shake_deregister
c_func
(paren
id|kmem_shaker_t
id|shrinker
)paren
(brace
id|remove_shrinker
c_func
(paren
id|shrinker
)paren
suffix:semicolon
)brace
r_static
id|__inline
r_int
DECL|function|kmem_shake_allow
id|kmem_shake_allow
c_func
(paren
r_int
r_int
id|gfp_mask
)paren
(brace
r_return
(paren
id|gfp_mask
op_amp
id|__GFP_WAIT
)paren
suffix:semicolon
)brace
macro_line|#endif /* __XFS_SUPPORT_KMEM_H__ */
eof
