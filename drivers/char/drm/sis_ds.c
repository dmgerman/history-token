multiline_comment|/* sis_ds.c -- Private header for Direct Rendering Manager -*- linux-c -*-&n; * Created: Mon Jan  4 10:05:05 1999 by sclin@sis.com.tw&n; *&n; * Copyright 2000 Silicon Integrated Systems Corp, Inc., HsinChu, Taiwan.&n; * All rights reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; * &n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; * &n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; * &n; * Authors:&n; *    Sung-Ching Lin &lt;sclin@sis.com.tw&gt;&n; * &n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &quot;sis_ds.h&quot;
multiline_comment|/* Set Data Structure, not check repeated value&n; * temporarily used&n; */
DECL|function|setInit
id|set_t
op_star
id|setInit
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|set_t
op_star
id|set
suffix:semicolon
id|set
op_assign
(paren
id|set_t
op_star
)paren
id|MALLOC
c_func
(paren
r_sizeof
(paren
id|set_t
)paren
)paren
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
id|SET_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|set-&gt;list
(braket
id|i
)braket
dot
id|free_next
op_assign
id|i
op_plus
l_int|1
suffix:semicolon
id|set-&gt;list
(braket
id|i
)braket
dot
id|alloc_next
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
id|set-&gt;list
(braket
id|SET_SIZE
op_minus
l_int|1
)braket
dot
id|free_next
op_assign
op_minus
l_int|1
suffix:semicolon
id|set-&gt;free
op_assign
l_int|0
suffix:semicolon
id|set-&gt;alloc
op_assign
op_minus
l_int|1
suffix:semicolon
id|set-&gt;trace
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
id|set
suffix:semicolon
)brace
DECL|function|setAdd
r_int
id|setAdd
c_func
(paren
id|set_t
op_star
id|set
comma
id|ITEM_TYPE
id|item
)paren
(brace
r_int
id|free
op_assign
id|set-&gt;free
suffix:semicolon
r_if
c_cond
(paren
id|free
op_ne
op_minus
l_int|1
)paren
(brace
id|set-&gt;list
(braket
id|free
)braket
dot
id|val
op_assign
id|item
suffix:semicolon
id|set-&gt;free
op_assign
id|set-&gt;list
(braket
id|free
)braket
dot
id|free_next
suffix:semicolon
)brace
r_else
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|set-&gt;list
(braket
id|free
)braket
dot
id|alloc_next
op_assign
id|set-&gt;alloc
suffix:semicolon
id|set-&gt;alloc
op_assign
id|free
suffix:semicolon
id|set-&gt;list
(braket
id|free
)braket
dot
id|free_next
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|setDel
r_int
id|setDel
c_func
(paren
id|set_t
op_star
id|set
comma
id|ITEM_TYPE
id|item
)paren
(brace
r_int
id|alloc
op_assign
id|set-&gt;alloc
suffix:semicolon
r_int
id|prev
op_assign
op_minus
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|alloc
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|set-&gt;list
(braket
id|alloc
)braket
dot
id|val
op_eq
id|item
)paren
(brace
r_if
c_cond
(paren
id|prev
op_ne
op_minus
l_int|1
)paren
(brace
id|set-&gt;list
(braket
id|prev
)braket
dot
id|alloc_next
op_assign
id|set-&gt;list
(braket
id|alloc
)braket
dot
id|alloc_next
suffix:semicolon
)brace
r_else
id|set-&gt;alloc
op_assign
id|set-&gt;list
(braket
id|alloc
)braket
dot
id|alloc_next
suffix:semicolon
r_break
suffix:semicolon
)brace
id|prev
op_assign
id|alloc
suffix:semicolon
id|alloc
op_assign
id|set-&gt;list
(braket
id|alloc
)braket
dot
id|alloc_next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|alloc
op_eq
op_minus
l_int|1
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|set-&gt;list
(braket
id|alloc
)braket
dot
id|free_next
op_assign
id|set-&gt;free
suffix:semicolon
id|set-&gt;free
op_assign
id|alloc
suffix:semicolon
id|set-&gt;list
(braket
id|alloc
)braket
dot
id|alloc_next
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* setFirst -&gt; setAdd -&gt; setNext is wrong */
DECL|function|setFirst
r_int
id|setFirst
c_func
(paren
id|set_t
op_star
id|set
comma
id|ITEM_TYPE
op_star
id|item
)paren
(brace
r_if
c_cond
(paren
id|set-&gt;alloc
op_eq
op_minus
l_int|1
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|item
op_assign
id|set-&gt;list
(braket
id|set-&gt;alloc
)braket
dot
id|val
suffix:semicolon
id|set-&gt;trace
op_assign
id|set-&gt;list
(braket
id|set-&gt;alloc
)braket
dot
id|alloc_next
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|setNext
r_int
id|setNext
c_func
(paren
id|set_t
op_star
id|set
comma
id|ITEM_TYPE
op_star
id|item
)paren
(brace
r_if
c_cond
(paren
id|set-&gt;trace
op_eq
op_minus
l_int|1
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|item
op_assign
id|set-&gt;list
(braket
id|set-&gt;trace
)braket
dot
id|val
suffix:semicolon
id|set-&gt;trace
op_assign
id|set-&gt;list
(braket
id|set-&gt;trace
)braket
dot
id|alloc_next
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|setDestroy
r_int
id|setDestroy
c_func
(paren
id|set_t
op_star
id|set
)paren
(brace
id|FREE
c_func
(paren
id|set
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * GLX Hardware Device Driver common code&n; * Copyright (C) 1999 Keith Whitwell&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice shall be included&n; * in all copies or substantial portions of the Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n; * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * KEITH WHITWELL, OR ANY OTHER CONTRIBUTORS BE LIABLE FOR ANY CLAIM, &n; * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR &n; * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE &n; * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.&n; *&n; */
DECL|macro|ISFREE
mdefine_line|#define ISFREE(bptr) ((bptr)-&gt;free)
DECL|macro|PRINTF
mdefine_line|#define PRINTF(fmt, arg...) do{}while(0)
DECL|macro|fprintf
mdefine_line|#define fprintf(fmt, arg...) do{}while(0)
DECL|function|calloc
r_static
r_void
op_star
id|calloc
c_func
(paren
r_int
id|nmemb
comma
r_int
id|size
)paren
(brace
r_void
op_star
id|addr
suffix:semicolon
id|addr
op_assign
id|kmalloc
c_func
(paren
id|nmemb
op_star
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|memset
c_func
(paren
id|addr
comma
l_int|0
comma
id|nmemb
op_star
id|size
)paren
suffix:semicolon
r_return
id|addr
suffix:semicolon
)brace
DECL|macro|free
mdefine_line|#define free(n) kfree(n)
DECL|function|mmDumpMemInfo
r_void
id|mmDumpMemInfo
c_func
(paren
id|memHeap_t
op_star
id|heap
)paren
(brace
id|TMemBlock
op_star
id|p
suffix:semicolon
id|PRINTF
(paren
l_string|&quot;Memory heap %p:&bslash;n&quot;
comma
id|heap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|heap
op_eq
l_int|0
)paren
(brace
id|PRINTF
(paren
l_string|&quot;  heap == 0&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|p
op_assign
(paren
id|TMemBlock
op_star
)paren
id|heap
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
(brace
id|PRINTF
(paren
l_string|&quot;  Offset:%08x, Size:%08x, %c%c&bslash;n&quot;
comma
id|p-&gt;ofs
comma
id|p-&gt;size
comma
id|p-&gt;free
ques
c_cond
l_char|&squot;.&squot;
suffix:colon
l_char|&squot;U&squot;
comma
id|p-&gt;reserved
ques
c_cond
l_char|&squot;R&squot;
suffix:colon
l_char|&squot;.&squot;
)paren
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
)brace
id|PRINTF
(paren
l_string|&quot;End of memory blocks&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|mmInit
id|memHeap_t
op_star
id|mmInit
c_func
(paren
r_int
id|ofs
comma
r_int
id|size
)paren
(brace
id|PMemBlock
id|blocks
suffix:semicolon
r_if
c_cond
(paren
id|size
op_le
l_int|0
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|blocks
op_assign
(paren
id|TMemBlock
op_star
)paren
id|calloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
id|TMemBlock
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|blocks
)paren
(brace
id|blocks-&gt;ofs
op_assign
id|ofs
suffix:semicolon
id|blocks-&gt;size
op_assign
id|size
suffix:semicolon
id|blocks-&gt;free
op_assign
l_int|1
suffix:semicolon
r_return
(paren
id|memHeap_t
op_star
)paren
id|blocks
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Kludgey workaround for existing i810 server.  Remove soon.&n; */
DECL|function|mmAddRange
id|memHeap_t
op_star
id|mmAddRange
c_func
(paren
id|memHeap_t
op_star
id|heap
comma
r_int
id|ofs
comma
r_int
id|size
)paren
(brace
id|PMemBlock
id|blocks
suffix:semicolon
id|blocks
op_assign
(paren
id|TMemBlock
op_star
)paren
id|calloc
c_func
(paren
l_int|2
comma
r_sizeof
(paren
id|TMemBlock
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|blocks
)paren
(brace
id|blocks
(braket
l_int|0
)braket
dot
id|size
op_assign
id|size
suffix:semicolon
id|blocks
(braket
l_int|0
)braket
dot
id|free
op_assign
l_int|1
suffix:semicolon
id|blocks
(braket
l_int|0
)braket
dot
id|ofs
op_assign
id|ofs
suffix:semicolon
id|blocks
(braket
l_int|0
)braket
dot
id|next
op_assign
op_amp
id|blocks
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Discontinuity - stops JoinBlock from trying to join non-adjacent&n;       * ranges.&n;       */
id|blocks
(braket
l_int|1
)braket
dot
id|size
op_assign
l_int|0
suffix:semicolon
id|blocks
(braket
l_int|1
)braket
dot
id|free
op_assign
l_int|0
suffix:semicolon
id|blocks
(braket
l_int|1
)braket
dot
id|ofs
op_assign
id|ofs
op_plus
id|size
suffix:semicolon
id|blocks
(braket
l_int|1
)braket
dot
id|next
op_assign
(paren
id|PMemBlock
)paren
id|heap
suffix:semicolon
r_return
(paren
id|memHeap_t
op_star
)paren
id|blocks
suffix:semicolon
)brace
r_else
r_return
id|heap
suffix:semicolon
)brace
DECL|function|SliceBlock
r_static
id|TMemBlock
op_star
id|SliceBlock
c_func
(paren
id|TMemBlock
op_star
id|p
comma
r_int
id|startofs
comma
r_int
id|size
comma
r_int
id|reserved
comma
r_int
id|alignment
)paren
(brace
id|TMemBlock
op_star
id|newblock
suffix:semicolon
multiline_comment|/* break left */
r_if
c_cond
(paren
id|startofs
OG
id|p-&gt;ofs
)paren
(brace
id|newblock
op_assign
(paren
id|TMemBlock
op_star
)paren
id|calloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
id|TMemBlock
)paren
)paren
suffix:semicolon
id|newblock-&gt;ofs
op_assign
id|startofs
suffix:semicolon
id|newblock-&gt;size
op_assign
id|p-&gt;size
op_minus
(paren
id|startofs
op_minus
id|p-&gt;ofs
)paren
suffix:semicolon
id|newblock-&gt;free
op_assign
l_int|1
suffix:semicolon
id|newblock-&gt;next
op_assign
id|p-&gt;next
suffix:semicolon
id|p-&gt;size
op_sub_assign
id|newblock-&gt;size
suffix:semicolon
id|p-&gt;next
op_assign
id|newblock
suffix:semicolon
id|p
op_assign
id|newblock
suffix:semicolon
)brace
multiline_comment|/* break right */
r_if
c_cond
(paren
id|size
OL
id|p-&gt;size
)paren
(brace
id|newblock
op_assign
(paren
id|TMemBlock
op_star
)paren
id|calloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
id|TMemBlock
)paren
)paren
suffix:semicolon
id|newblock-&gt;ofs
op_assign
id|startofs
op_plus
id|size
suffix:semicolon
id|newblock-&gt;size
op_assign
id|p-&gt;size
op_minus
id|size
suffix:semicolon
id|newblock-&gt;free
op_assign
l_int|1
suffix:semicolon
id|newblock-&gt;next
op_assign
id|p-&gt;next
suffix:semicolon
id|p-&gt;size
op_assign
id|size
suffix:semicolon
id|p-&gt;next
op_assign
id|newblock
suffix:semicolon
)brace
multiline_comment|/* p = middle block */
id|p-&gt;align
op_assign
id|alignment
suffix:semicolon
id|p-&gt;free
op_assign
l_int|0
suffix:semicolon
id|p-&gt;reserved
op_assign
id|reserved
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
DECL|function|mmAllocMem
id|PMemBlock
id|mmAllocMem
c_func
(paren
id|memHeap_t
op_star
id|heap
comma
r_int
id|size
comma
r_int
id|align2
comma
r_int
id|startSearch
)paren
(brace
r_int
id|mask
comma
id|startofs
comma
id|endofs
suffix:semicolon
id|TMemBlock
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|heap
op_logical_or
id|align2
OL
l_int|0
op_logical_or
id|size
op_le
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
id|mask
op_assign
(paren
l_int|1
op_lshift
id|align2
)paren
op_minus
l_int|1
suffix:semicolon
id|startofs
op_assign
l_int|0
suffix:semicolon
id|p
op_assign
(paren
id|TMemBlock
op_star
)paren
id|heap
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
id|ISFREE
c_func
(paren
id|p
)paren
)paren
(brace
id|startofs
op_assign
(paren
id|p-&gt;ofs
op_plus
id|mask
)paren
op_amp
op_complement
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|startofs
OL
id|startSearch
)paren
(brace
id|startofs
op_assign
id|startSearch
suffix:semicolon
)brace
id|endofs
op_assign
id|startofs
op_plus
id|size
suffix:semicolon
r_if
c_cond
(paren
id|endofs
op_le
(paren
id|p-&gt;ofs
op_plus
id|p-&gt;size
)paren
)paren
r_break
suffix:semicolon
)brace
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
l_int|NULL
suffix:semicolon
id|p
op_assign
id|SliceBlock
c_func
(paren
id|p
comma
id|startofs
comma
id|size
comma
l_int|0
comma
id|mask
op_plus
l_int|1
)paren
suffix:semicolon
id|p-&gt;heap
op_assign
id|heap
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
DECL|function|Join2Blocks
r_static
id|__inline__
r_int
id|Join2Blocks
c_func
(paren
id|TMemBlock
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;free
op_logical_and
id|p-&gt;next
op_logical_and
id|p-&gt;next-&gt;free
)paren
(brace
id|TMemBlock
op_star
id|q
op_assign
id|p-&gt;next
suffix:semicolon
id|p-&gt;size
op_add_assign
id|q-&gt;size
suffix:semicolon
id|p-&gt;next
op_assign
id|q-&gt;next
suffix:semicolon
id|free
c_func
(paren
id|q
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mmFreeMem
r_int
id|mmFreeMem
c_func
(paren
id|PMemBlock
id|b
)paren
(brace
id|TMemBlock
op_star
id|p
comma
op_star
id|prev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|b
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|b-&gt;heap
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;no heap&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|p
op_assign
id|b-&gt;heap
suffix:semicolon
id|prev
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|p
op_logical_and
id|p
op_ne
id|b
)paren
(brace
id|prev
op_assign
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
id|p-&gt;free
op_logical_or
id|p-&gt;reserved
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;block not found in heap&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|p-&gt;free
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;block already free&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;block is reserved&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|p-&gt;free
op_assign
l_int|1
suffix:semicolon
id|Join2Blocks
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prev
)paren
id|Join2Blocks
c_func
(paren
id|prev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mmReserveMem
r_int
id|mmReserveMem
c_func
(paren
id|memHeap_t
op_star
id|heap
comma
r_int
id|offset
comma
r_int
id|size
)paren
(brace
r_int
id|endofs
suffix:semicolon
id|TMemBlock
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|heap
op_logical_or
id|size
op_le
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|endofs
op_assign
id|offset
op_plus
id|size
suffix:semicolon
id|p
op_assign
(paren
id|TMemBlock
op_star
)paren
id|heap
suffix:semicolon
r_while
c_loop
(paren
id|p
op_logical_and
id|p-&gt;ofs
op_le
id|offset
)paren
(brace
r_if
c_cond
(paren
id|ISFREE
c_func
(paren
id|p
)paren
op_logical_and
id|endofs
op_le
(paren
id|p-&gt;ofs
op_plus
id|p-&gt;size
)paren
)paren
(brace
id|SliceBlock
c_func
(paren
id|p
comma
id|offset
comma
id|size
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|mmFreeReserved
r_int
id|mmFreeReserved
c_func
(paren
id|memHeap_t
op_star
id|heap
comma
r_int
id|offset
)paren
(brace
id|TMemBlock
op_star
id|p
comma
op_star
id|prev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|heap
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|p
op_assign
(paren
id|TMemBlock
op_star
)paren
id|heap
suffix:semicolon
id|prev
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|p
op_logical_and
id|p-&gt;ofs
op_ne
id|offset
)paren
(brace
id|prev
op_assign
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
op_logical_neg
id|p-&gt;reserved
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|p-&gt;free
op_assign
l_int|1
suffix:semicolon
id|p-&gt;reserved
op_assign
l_int|0
suffix:semicolon
id|Join2Blocks
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prev
)paren
id|Join2Blocks
c_func
(paren
id|prev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mmDestroy
r_void
id|mmDestroy
c_func
(paren
id|memHeap_t
op_star
id|heap
)paren
(brace
id|TMemBlock
op_star
id|p
comma
op_star
id|q
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|heap
)paren
r_return
suffix:semicolon
id|p
op_assign
(paren
id|TMemBlock
op_star
)paren
id|heap
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
(brace
id|q
op_assign
id|p-&gt;next
suffix:semicolon
id|free
c_func
(paren
id|p
)paren
suffix:semicolon
id|p
op_assign
id|q
suffix:semicolon
)brace
)brace
eof