multiline_comment|/*&n; * Cryptographic API.&n; *&n; * Cipher operations.&n; *&n; * Copyright (c) 2002 James Morris &lt;jmorris@intercode.com.au&gt;&n; *               2002 Adam J. Richter &lt;adam@yggdrasil.com&gt;&n; *               2004 Jean-Luc Cooke &lt;jlcooke@certainkey.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the Free&n; * Software Foundation; either version 2 of the License, or (at your option)&n; * any later version.&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &quot;internal.h&quot;
macro_line|#include &quot;scatterwalk.h&quot;
DECL|variable|crypto_km_types
r_enum
id|km_type
id|crypto_km_types
(braket
)braket
op_assign
(brace
id|KM_USER0
comma
id|KM_USER1
comma
id|KM_SOFTIRQ0
comma
id|KM_SOFTIRQ1
comma
)brace
suffix:semicolon
DECL|function|scatterwalk_whichbuf
r_void
op_star
id|scatterwalk_whichbuf
c_func
(paren
r_struct
id|scatter_walk
op_star
id|walk
comma
r_int
r_int
id|nbytes
comma
r_void
op_star
id|scratch
)paren
(brace
r_if
c_cond
(paren
id|nbytes
op_le
id|walk-&gt;len_this_page
op_logical_and
(paren
(paren
(paren
r_int
r_int
)paren
id|walk-&gt;data
)paren
op_amp
(paren
id|PAGE_CACHE_SIZE
op_minus
l_int|1
)paren
)paren
op_plus
id|nbytes
op_le
id|PAGE_CACHE_SIZE
)paren
r_return
id|walk-&gt;data
suffix:semicolon
r_else
r_return
id|scratch
suffix:semicolon
)brace
DECL|function|memcpy_dir
r_static
r_void
id|memcpy_dir
c_func
(paren
r_void
op_star
id|buf
comma
r_void
op_star
id|sgdata
comma
r_int
id|nbytes
comma
r_int
id|out
)paren
(brace
r_if
c_cond
(paren
id|out
)paren
id|memcpy
c_func
(paren
id|sgdata
comma
id|buf
comma
id|nbytes
)paren
suffix:semicolon
r_else
id|memcpy
c_func
(paren
id|buf
comma
id|sgdata
comma
id|nbytes
)paren
suffix:semicolon
)brace
DECL|function|scatterwalk_start
r_void
id|scatterwalk_start
c_func
(paren
r_struct
id|scatter_walk
op_star
id|walk
comma
r_struct
id|scatterlist
op_star
id|sg
)paren
(brace
r_int
r_int
id|rest_of_page
suffix:semicolon
id|walk-&gt;sg
op_assign
id|sg
suffix:semicolon
id|walk-&gt;page
op_assign
id|sg-&gt;page
suffix:semicolon
id|walk-&gt;len_this_segment
op_assign
id|sg-&gt;length
suffix:semicolon
id|rest_of_page
op_assign
id|PAGE_CACHE_SIZE
op_minus
(paren
id|sg-&gt;offset
op_amp
(paren
id|PAGE_CACHE_SIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|walk-&gt;len_this_page
op_assign
id|min
c_func
(paren
id|sg-&gt;length
comma
id|rest_of_page
)paren
suffix:semicolon
id|walk-&gt;offset
op_assign
id|sg-&gt;offset
suffix:semicolon
)brace
DECL|function|scatterwalk_map
r_void
id|scatterwalk_map
c_func
(paren
r_struct
id|scatter_walk
op_star
id|walk
comma
r_int
id|out
)paren
(brace
id|walk-&gt;data
op_assign
id|crypto_kmap
c_func
(paren
id|walk-&gt;page
comma
id|out
)paren
op_plus
id|walk-&gt;offset
suffix:semicolon
)brace
DECL|function|scatterwalk_pagedone
r_static
r_void
id|scatterwalk_pagedone
c_func
(paren
r_struct
id|scatter_walk
op_star
id|walk
comma
r_int
id|out
comma
r_int
r_int
id|more
)paren
(brace
multiline_comment|/* walk-&gt;data may be pointing the first byte of the next page;&n;&t;   however, we know we transfered at least one byte.  So,&n;&t;   walk-&gt;data - 1 will be a virtual address in the mapped page. */
r_if
c_cond
(paren
id|out
)paren
id|flush_dcache_page
c_func
(paren
id|walk-&gt;page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|more
)paren
(brace
id|walk-&gt;len_this_segment
op_sub_assign
id|walk-&gt;len_this_page
suffix:semicolon
r_if
c_cond
(paren
id|walk-&gt;len_this_segment
)paren
(brace
id|walk-&gt;page
op_increment
suffix:semicolon
id|walk-&gt;len_this_page
op_assign
id|min
c_func
(paren
id|walk-&gt;len_this_segment
comma
(paren
r_int
)paren
id|PAGE_CACHE_SIZE
)paren
suffix:semicolon
id|walk-&gt;offset
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|scatterwalk_start
c_func
(paren
id|walk
comma
id|sg_next
c_func
(paren
id|walk-&gt;sg
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|scatterwalk_done
r_void
id|scatterwalk_done
c_func
(paren
r_struct
id|scatter_walk
op_star
id|walk
comma
r_int
id|out
comma
r_int
id|more
)paren
(brace
id|crypto_kunmap
c_func
(paren
id|walk-&gt;data
comma
id|out
)paren
suffix:semicolon
r_if
c_cond
(paren
id|walk-&gt;len_this_page
op_eq
l_int|0
op_logical_or
op_logical_neg
id|more
)paren
id|scatterwalk_pagedone
c_func
(paren
id|walk
comma
id|out
comma
id|more
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Do not call this unless the total length of all of the fragments&n; * has been verified as multiple of the block size.&n; */
DECL|function|scatterwalk_copychunks
r_int
id|scatterwalk_copychunks
c_func
(paren
r_void
op_star
id|buf
comma
r_struct
id|scatter_walk
op_star
id|walk
comma
r_int
id|nbytes
comma
r_int
id|out
)paren
(brace
r_if
c_cond
(paren
id|buf
op_ne
id|walk-&gt;data
)paren
(brace
r_while
c_loop
(paren
id|nbytes
OG
id|walk-&gt;len_this_page
)paren
(brace
id|memcpy_dir
c_func
(paren
id|buf
comma
id|walk-&gt;data
comma
id|walk-&gt;len_this_page
comma
id|out
)paren
suffix:semicolon
id|buf
op_add_assign
id|walk-&gt;len_this_page
suffix:semicolon
id|nbytes
op_sub_assign
id|walk-&gt;len_this_page
suffix:semicolon
id|crypto_kunmap
c_func
(paren
id|walk-&gt;data
comma
id|out
)paren
suffix:semicolon
id|scatterwalk_pagedone
c_func
(paren
id|walk
comma
id|out
comma
l_int|1
)paren
suffix:semicolon
id|scatterwalk_map
c_func
(paren
id|walk
comma
id|out
)paren
suffix:semicolon
)brace
id|memcpy_dir
c_func
(paren
id|buf
comma
id|walk-&gt;data
comma
id|nbytes
comma
id|out
)paren
suffix:semicolon
)brace
id|walk-&gt;offset
op_add_assign
id|nbytes
suffix:semicolon
id|walk-&gt;len_this_page
op_sub_assign
id|nbytes
suffix:semicolon
id|walk-&gt;len_this_segment
op_sub_assign
id|nbytes
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
