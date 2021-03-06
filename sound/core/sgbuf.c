multiline_comment|/*&n; * Scatter-Gather buffer&n; *&n; *  Copyright (c) by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;sound/memalloc.h&gt;
multiline_comment|/* table entries are align to 32 */
DECL|macro|SGBUF_TBL_ALIGN
mdefine_line|#define SGBUF_TBL_ALIGN&t;&t;32
DECL|macro|sgbuf_align_table
mdefine_line|#define sgbuf_align_table(tbl)&t;((((tbl) + SGBUF_TBL_ALIGN - 1) / SGBUF_TBL_ALIGN) * SGBUF_TBL_ALIGN)
DECL|function|snd_free_sgbuf_pages
r_int
id|snd_free_sgbuf_pages
c_func
(paren
r_struct
id|snd_dma_buffer
op_star
id|dmab
)paren
(brace
r_struct
id|snd_sg_buf
op_star
id|sgbuf
op_assign
id|dmab-&gt;private_data
suffix:semicolon
r_struct
id|snd_dma_buffer
id|tmpb
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sgbuf
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|tmpb.dev.type
op_assign
id|SNDRV_DMA_TYPE_DEV
suffix:semicolon
id|tmpb.dev.dev
op_assign
id|sgbuf-&gt;dev
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
id|sgbuf-&gt;pages
suffix:semicolon
id|i
op_increment
)paren
(brace
id|tmpb.area
op_assign
id|sgbuf-&gt;table
(braket
id|i
)braket
dot
id|buf
suffix:semicolon
id|tmpb.addr
op_assign
id|sgbuf-&gt;table
(braket
id|i
)braket
dot
id|addr
suffix:semicolon
id|tmpb.bytes
op_assign
id|PAGE_SIZE
suffix:semicolon
id|snd_dma_free_pages
c_func
(paren
op_amp
id|tmpb
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dmab-&gt;area
)paren
id|vunmap
c_func
(paren
id|dmab-&gt;area
)paren
suffix:semicolon
id|dmab-&gt;area
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|sgbuf-&gt;table
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sgbuf-&gt;page_table
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sgbuf
)paren
suffix:semicolon
id|dmab-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_malloc_sgbuf_pages
r_void
op_star
id|snd_malloc_sgbuf_pages
c_func
(paren
r_struct
id|device
op_star
id|device
comma
r_int
id|size
comma
r_struct
id|snd_dma_buffer
op_star
id|dmab
comma
r_int
op_star
id|res_size
)paren
(brace
r_struct
id|snd_sg_buf
op_star
id|sgbuf
suffix:semicolon
r_int
r_int
id|i
comma
id|pages
suffix:semicolon
r_struct
id|snd_dma_buffer
id|tmpb
suffix:semicolon
id|dmab-&gt;area
op_assign
l_int|NULL
suffix:semicolon
id|dmab-&gt;addr
op_assign
l_int|0
suffix:semicolon
id|dmab-&gt;private_data
op_assign
id|sgbuf
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|sgbuf
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sgbuf
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|sgbuf
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|sgbuf
)paren
)paren
suffix:semicolon
id|sgbuf-&gt;dev
op_assign
id|device
suffix:semicolon
id|pages
op_assign
id|snd_sgbuf_aligned_pages
c_func
(paren
id|size
)paren
suffix:semicolon
id|sgbuf-&gt;tblsize
op_assign
id|sgbuf_align_table
c_func
(paren
id|pages
)paren
suffix:semicolon
id|sgbuf-&gt;table
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|sgbuf-&gt;table
)paren
op_star
id|sgbuf-&gt;tblsize
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sgbuf-&gt;table
)paren
r_goto
id|_failed
suffix:semicolon
id|memset
c_func
(paren
id|sgbuf-&gt;table
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|sgbuf-&gt;table
)paren
op_star
id|sgbuf-&gt;tblsize
)paren
suffix:semicolon
id|sgbuf-&gt;page_table
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|sgbuf-&gt;page_table
)paren
op_star
id|sgbuf-&gt;tblsize
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sgbuf-&gt;page_table
)paren
r_goto
id|_failed
suffix:semicolon
id|memset
c_func
(paren
id|sgbuf-&gt;page_table
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|sgbuf-&gt;page_table
)paren
op_star
id|sgbuf-&gt;tblsize
)paren
suffix:semicolon
multiline_comment|/* allocate each page */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|pages
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|snd_dma_alloc_pages
c_func
(paren
id|SNDRV_DMA_TYPE_DEV
comma
id|device
comma
id|PAGE_SIZE
comma
op_amp
id|tmpb
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|res_size
op_eq
l_int|NULL
)paren
r_goto
id|_failed
suffix:semicolon
op_star
id|res_size
op_assign
id|size
op_assign
id|sgbuf-&gt;pages
op_star
id|PAGE_SIZE
suffix:semicolon
r_break
suffix:semicolon
)brace
id|sgbuf-&gt;table
(braket
id|i
)braket
dot
id|buf
op_assign
id|tmpb.area
suffix:semicolon
id|sgbuf-&gt;table
(braket
id|i
)braket
dot
id|addr
op_assign
id|tmpb.addr
suffix:semicolon
id|sgbuf-&gt;page_table
(braket
id|i
)braket
op_assign
id|virt_to_page
c_func
(paren
id|tmpb.area
)paren
suffix:semicolon
id|sgbuf-&gt;pages
op_increment
suffix:semicolon
)brace
id|sgbuf-&gt;size
op_assign
id|size
suffix:semicolon
id|dmab-&gt;area
op_assign
id|vmap
c_func
(paren
id|sgbuf-&gt;page_table
comma
id|sgbuf-&gt;pages
comma
id|VM_MAP
comma
id|PAGE_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dmab-&gt;area
)paren
r_goto
id|_failed
suffix:semicolon
r_return
id|dmab-&gt;area
suffix:semicolon
id|_failed
suffix:colon
id|snd_free_sgbuf_pages
c_func
(paren
id|dmab
)paren
suffix:semicolon
multiline_comment|/* free the table */
r_return
l_int|NULL
suffix:semicolon
)brace
eof
