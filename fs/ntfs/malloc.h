multiline_comment|/*&n; * malloc.h - NTFS kernel memory handling. Part of the Linux-NTFS project.&n; *&n; * Copyright (c) 2001,2002 Anton Altaparmakov.&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be &n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty &n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS &n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _LINUX_NTFS_MALLOC_H
DECL|macro|_LINUX_NTFS_MALLOC_H
mdefine_line|#define _LINUX_NTFS_MALLOC_H
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
multiline_comment|/**&n; * vmalloc_nofs - allocate any pages but don&squot;t allow calls into fs layer&n; * @size:&t;number of bytes to allocate&n; *&n; * Allocate any pages but don&squot;t allow calls into fs layer. Return allocated&n; * memory or NULL if insufficient memory.&n; */
DECL|function|vmalloc_nofs
r_static
r_inline
r_void
op_star
id|vmalloc_nofs
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
id|likely
c_func
(paren
id|size
op_rshift
id|PAGE_SHIFT
OL
id|num_physpages
)paren
)paren
r_return
id|__vmalloc
c_func
(paren
id|size
comma
id|GFP_NOFS
op_or
id|__GFP_HIGHMEM
comma
id|PAGE_KERNEL
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/**&n; * ntfs_malloc_nofs - allocate memory in multiples of pages&n; * @size&t;number of bytes to allocate&n; *&n; * Allocates @size bytes of memory, rounded up to multiples of PAGE_SIZE and&n; * returns a pointer to the allocated memory.&n; *&n; * If there was insufficient memory to complete the request, return NULL.&n; */
DECL|function|ntfs_malloc_nofs
r_static
r_inline
r_void
op_star
id|ntfs_malloc_nofs
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
id|likely
c_func
(paren
id|size
op_le
id|PAGE_SIZE
)paren
)paren
(brace
r_if
c_cond
(paren
id|likely
c_func
(paren
id|size
)paren
)paren
(brace
multiline_comment|/* kmalloc() has per-CPU caches so if faster for now. */
r_return
id|kmalloc
c_func
(paren
id|PAGE_SIZE
comma
id|GFP_NOFS
)paren
suffix:semicolon
multiline_comment|/* return (void *)__get_free_page(GFP_NOFS |&n;&t;&t;&t;&t;&t;__GFP_HIGHMEM); */
)brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|likely
c_func
(paren
id|size
op_rshift
id|PAGE_SHIFT
OL
id|num_physpages
)paren
)paren
r_return
id|__vmalloc
c_func
(paren
id|size
comma
id|GFP_NOFS
op_or
id|__GFP_HIGHMEM
comma
id|PAGE_KERNEL
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|ntfs_free
r_static
r_inline
r_void
id|ntfs_free
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
r_if
c_cond
(paren
id|likely
c_func
(paren
(paren
r_int
r_int
)paren
id|addr
OL
id|VMALLOC_START
)paren
)paren
(brace
r_return
id|kfree
c_func
(paren
id|addr
)paren
suffix:semicolon
multiline_comment|/* return free_page((unsigned long)addr); */
)brace
id|vfree
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
macro_line|#endif /* _LINUX_NTFS_MALLOC_H */
eof
