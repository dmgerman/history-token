multiline_comment|/*&n; * A simple kernel FIFO implementation.&n; *&n; * Copyright (C) 2004 Stelian Pop &lt;stelian@popies.net&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &lt;linux/kfifo.h&gt;
multiline_comment|/**&n; * kfifo_init - allocates a new FIFO using a preallocated buffer&n; * @buffer: the preallocated buffer to be used.&n; * @size: the size of the internal buffer, this have to be a power of 2.&n; * @gfp_mask: get_free_pages mask, passed to kmalloc()&n; * @lock: the lock to be used to protect the fifo buffer&n; *&n; * Do NOT pass the kfifo to kfifo_free() after use ! Simply free the&n; * struct kfifo with kfree().&n; */
DECL|function|kfifo_init
r_struct
id|kfifo
op_star
id|kfifo_init
c_func
(paren
r_int
r_char
op_star
id|buffer
comma
r_int
r_int
id|size
comma
r_int
r_int
id|__nocast
id|gfp_mask
comma
id|spinlock_t
op_star
id|lock
)paren
(brace
r_struct
id|kfifo
op_star
id|fifo
suffix:semicolon
multiline_comment|/* size must be a power of 2 */
id|BUG_ON
c_func
(paren
id|size
op_amp
(paren
id|size
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|fifo
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|kfifo
)paren
comma
id|gfp_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fifo
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|fifo-&gt;buffer
op_assign
id|buffer
suffix:semicolon
id|fifo-&gt;size
op_assign
id|size
suffix:semicolon
id|fifo-&gt;in
op_assign
id|fifo-&gt;out
op_assign
l_int|0
suffix:semicolon
id|fifo-&gt;lock
op_assign
id|lock
suffix:semicolon
r_return
id|fifo
suffix:semicolon
)brace
DECL|variable|kfifo_init
id|EXPORT_SYMBOL
c_func
(paren
id|kfifo_init
)paren
suffix:semicolon
multiline_comment|/**&n; * kfifo_alloc - allocates a new FIFO and its internal buffer&n; * @size: the size of the internal buffer to be allocated.&n; * @gfp_mask: get_free_pages mask, passed to kmalloc()&n; * @lock: the lock to be used to protect the fifo buffer&n; *&n; * The size will be rounded-up to a power of 2.&n; */
DECL|function|kfifo_alloc
r_struct
id|kfifo
op_star
id|kfifo_alloc
c_func
(paren
r_int
r_int
id|size
comma
r_int
r_int
id|__nocast
id|gfp_mask
comma
id|spinlock_t
op_star
id|lock
)paren
(brace
r_int
r_char
op_star
id|buffer
suffix:semicolon
r_struct
id|kfifo
op_star
id|ret
suffix:semicolon
multiline_comment|/*&n;&t; * round up to the next power of 2, since our &squot;let the indices&n;&t; * wrap&squot; tachnique works only in this case.&n;&t; */
r_if
c_cond
(paren
id|size
op_amp
(paren
id|size
op_minus
l_int|1
)paren
)paren
(brace
id|BUG_ON
c_func
(paren
id|size
OG
l_int|0x80000000
)paren
suffix:semicolon
id|size
op_assign
id|roundup_pow_of_two
c_func
(paren
id|size
)paren
suffix:semicolon
)brace
id|buffer
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|gfp_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|ret
op_assign
id|kfifo_init
c_func
(paren
id|buffer
comma
id|size
comma
id|gfp_mask
comma
id|lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|ret
)paren
)paren
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|kfifo_alloc
id|EXPORT_SYMBOL
c_func
(paren
id|kfifo_alloc
)paren
suffix:semicolon
multiline_comment|/**&n; * kfifo_free - frees the FIFO&n; * @fifo: the fifo to be freed.&n; */
DECL|function|kfifo_free
r_void
id|kfifo_free
c_func
(paren
r_struct
id|kfifo
op_star
id|fifo
)paren
(brace
id|kfree
c_func
(paren
id|fifo-&gt;buffer
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|fifo
)paren
suffix:semicolon
)brace
DECL|variable|kfifo_free
id|EXPORT_SYMBOL
c_func
(paren
id|kfifo_free
)paren
suffix:semicolon
multiline_comment|/**&n; * __kfifo_put - puts some data into the FIFO, no locking version&n; * @fifo: the fifo to be used.&n; * @buffer: the data to be added.&n; * @len: the length of the data to be added.&n; *&n; * This function copies at most &squot;len&squot; bytes from the &squot;buffer&squot; into&n; * the FIFO depending on the free space, and returns the number of&n; * bytes copied.&n; *&n; * Note that with only one concurrent reader and one concurrent&n; * writer, you don&squot;t need extra locking to use these functions.&n; */
DECL|function|__kfifo_put
r_int
r_int
id|__kfifo_put
c_func
(paren
r_struct
id|kfifo
op_star
id|fifo
comma
r_int
r_char
op_star
id|buffer
comma
r_int
r_int
id|len
)paren
(brace
r_int
r_int
id|l
suffix:semicolon
id|len
op_assign
id|min
c_func
(paren
id|len
comma
id|fifo-&gt;size
op_minus
id|fifo-&gt;in
op_plus
id|fifo-&gt;out
)paren
suffix:semicolon
multiline_comment|/* first put the data starting from fifo-&gt;in to buffer end */
id|l
op_assign
id|min
c_func
(paren
id|len
comma
id|fifo-&gt;size
op_minus
(paren
id|fifo-&gt;in
op_amp
(paren
id|fifo-&gt;size
op_minus
l_int|1
)paren
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|fifo-&gt;buffer
op_plus
(paren
id|fifo-&gt;in
op_amp
(paren
id|fifo-&gt;size
op_minus
l_int|1
)paren
)paren
comma
id|buffer
comma
id|l
)paren
suffix:semicolon
multiline_comment|/* then put the rest (if any) at the beginning of the buffer */
id|memcpy
c_func
(paren
id|fifo-&gt;buffer
comma
id|buffer
op_plus
id|l
comma
id|len
op_minus
id|l
)paren
suffix:semicolon
id|fifo-&gt;in
op_add_assign
id|len
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|variable|__kfifo_put
id|EXPORT_SYMBOL
c_func
(paren
id|__kfifo_put
)paren
suffix:semicolon
multiline_comment|/**&n; * __kfifo_get - gets some data from the FIFO, no locking version&n; * @fifo: the fifo to be used.&n; * @buffer: where the data must be copied.&n; * @len: the size of the destination buffer.&n; *&n; * This function copies at most &squot;len&squot; bytes from the FIFO into the&n; * &squot;buffer&squot; and returns the number of copied bytes.&n; *&n; * Note that with only one concurrent reader and one concurrent&n; * writer, you don&squot;t need extra locking to use these functions.&n; */
DECL|function|__kfifo_get
r_int
r_int
id|__kfifo_get
c_func
(paren
r_struct
id|kfifo
op_star
id|fifo
comma
r_int
r_char
op_star
id|buffer
comma
r_int
r_int
id|len
)paren
(brace
r_int
r_int
id|l
suffix:semicolon
id|len
op_assign
id|min
c_func
(paren
id|len
comma
id|fifo-&gt;in
op_minus
id|fifo-&gt;out
)paren
suffix:semicolon
multiline_comment|/* first get the data from fifo-&gt;out until the end of the buffer */
id|l
op_assign
id|min
c_func
(paren
id|len
comma
id|fifo-&gt;size
op_minus
(paren
id|fifo-&gt;out
op_amp
(paren
id|fifo-&gt;size
op_minus
l_int|1
)paren
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|buffer
comma
id|fifo-&gt;buffer
op_plus
(paren
id|fifo-&gt;out
op_amp
(paren
id|fifo-&gt;size
op_minus
l_int|1
)paren
)paren
comma
id|l
)paren
suffix:semicolon
multiline_comment|/* then get the rest (if any) from the beginning of the buffer */
id|memcpy
c_func
(paren
id|buffer
op_plus
id|l
comma
id|fifo-&gt;buffer
comma
id|len
op_minus
id|l
)paren
suffix:semicolon
id|fifo-&gt;out
op_add_assign
id|len
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|variable|__kfifo_get
id|EXPORT_SYMBOL
c_func
(paren
id|__kfifo_get
)paren
suffix:semicolon
eof
