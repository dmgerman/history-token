multiline_comment|/*&n;    zr36120_mem.c - Zoran 36120/36125 based framegrabbers&n;&n;    Copyright (C) 1998-1999 Pauline Middelink &lt;middelin@polyware.nl&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/wrapper.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#ifdef CONFIG_BIGPHYS_AREA
macro_line|#include &lt;linux/bigphysarea.h&gt;
macro_line|#endif
macro_line|#include &quot;zr36120.h&quot;
macro_line|#include &quot;zr36120_mem.h&quot;
multiline_comment|/*******************************/
multiline_comment|/* Memory management functions */
multiline_comment|/*******************************/
DECL|function|bmalloc
r_void
op_star
id|bmalloc
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_void
op_star
id|mem
suffix:semicolon
macro_line|#ifdef CONFIG_BIGPHYS_AREA
id|mem
op_assign
id|bigphysarea_alloc_pages
c_func
(paren
id|size
op_div
id|PAGE_SIZE
comma
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/*&n;&t; * The following function got a lot of memory at boottime,&n;&t; * so we know its always there...&n;&t; */
id|mem
op_assign
(paren
r_void
op_star
)paren
id|__get_free_pages
c_func
(paren
id|GFP_USER
op_or
id|GFP_DMA
comma
id|get_order
c_func
(paren
id|size
)paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|mem
)paren
(brace
r_int
r_int
id|adr
op_assign
(paren
r_int
r_int
)paren
id|mem
suffix:semicolon
r_while
c_loop
(paren
id|size
OG
l_int|0
)paren
(brace
id|SetPageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|phys_to_virt
c_func
(paren
id|adr
)paren
)paren
)paren
suffix:semicolon
id|adr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|size
op_sub_assign
id|PAGE_SIZE
suffix:semicolon
)brace
)brace
r_return
id|mem
suffix:semicolon
)brace
DECL|function|bfree
r_void
id|bfree
c_func
(paren
r_void
op_star
id|mem
comma
r_int
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
id|mem
)paren
(brace
r_int
r_int
id|adr
op_assign
(paren
r_int
r_int
)paren
id|mem
suffix:semicolon
r_int
r_int
id|siz
op_assign
id|size
suffix:semicolon
r_while
c_loop
(paren
id|siz
OG
l_int|0
)paren
(brace
id|ClearPageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|phys_to_virt
c_func
(paren
id|adr
)paren
)paren
)paren
suffix:semicolon
id|adr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|siz
op_sub_assign
id|PAGE_SIZE
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BIGPHYS_AREA
id|bigphysarea_free_pages
c_func
(paren
id|mem
)paren
suffix:semicolon
macro_line|#else
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|mem
comma
id|get_order
c_func
(paren
id|size
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
