multiline_comment|/* sis_ds.h -- Private header for Direct Rendering Manager -*- linux-c -*-&n; * Created: Mon Jan  4 10:05:05 1999 by sclin@sis.com.tw&n; *&n; * Copyright 2000 Silicon Integrated Systems Corp, Inc., HsinChu, Taiwan.&n; * All rights reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; * &n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; * &n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; * &n; * Authors:&n; *    Sung-Ching Lin &lt;sclin@sis.com.tw&gt;&n; * &n; */
macro_line|#ifndef __SIS_DS_H__
DECL|macro|__SIS_DS_H__
mdefine_line|#define __SIS_DS_H__
multiline_comment|/* Set Data Structure */
DECL|macro|SET_SIZE
mdefine_line|#define SET_SIZE 5000
DECL|typedef|ITEM_TYPE
r_typedef
r_int
r_int
id|ITEM_TYPE
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|val
id|ITEM_TYPE
id|val
suffix:semicolon
DECL|member|alloc_next
DECL|member|free_next
r_int
id|alloc_next
comma
id|free_next
suffix:semicolon
DECL|typedef|list_item_t
)brace
id|list_item_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|alloc
r_int
id|alloc
suffix:semicolon
DECL|member|free
r_int
id|free
suffix:semicolon
DECL|member|trace
r_int
id|trace
suffix:semicolon
DECL|member|list
id|list_item_t
id|list
(braket
id|SET_SIZE
)braket
suffix:semicolon
DECL|typedef|set_t
)brace
id|set_t
suffix:semicolon
id|set_t
op_star
id|setInit
c_func
(paren
r_void
)paren
suffix:semicolon
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
suffix:semicolon
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
suffix:semicolon
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
suffix:semicolon
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
suffix:semicolon
r_int
id|setDestroy
c_func
(paren
id|set_t
op_star
id|set
)paren
suffix:semicolon
multiline_comment|/*&n; * GLX Hardware Device Driver common code&n; * Copyright (C) 1999 Wittawat Yamwong&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice shall be included&n; * in all copies or substantial portions of the Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n; * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * WITTAWAT YAMWONG, OR ANY OTHER CONTRIBUTORS BE LIABLE FOR ANY CLAIM, &n; * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR &n; * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE &n; * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.&n; *&n; */
DECL|struct|mem_block_t
r_struct
id|mem_block_t
(brace
DECL|member|next
r_struct
id|mem_block_t
op_star
id|next
suffix:semicolon
DECL|member|heap
r_struct
id|mem_block_t
op_star
id|heap
suffix:semicolon
DECL|member|ofs
DECL|member|size
r_int
id|ofs
comma
id|size
suffix:semicolon
DECL|member|align
r_int
id|align
suffix:semicolon
DECL|member|free
r_int
r_int
id|free
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
r_int
r_int
id|reserved
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|TMemBlock
r_typedef
r_struct
id|mem_block_t
id|TMemBlock
suffix:semicolon
DECL|typedef|PMemBlock
r_typedef
r_struct
id|mem_block_t
op_star
id|PMemBlock
suffix:semicolon
multiline_comment|/* a heap is just the first block in a chain */
DECL|typedef|memHeap_t
r_typedef
r_struct
id|mem_block_t
id|memHeap_t
suffix:semicolon
DECL|function|mmBlockSize
r_static
id|__inline__
r_int
id|mmBlockSize
c_func
(paren
id|PMemBlock
id|b
)paren
(brace
r_return
id|b-&gt;size
suffix:semicolon
)brace
DECL|function|mmOffset
r_static
id|__inline__
r_int
id|mmOffset
c_func
(paren
id|PMemBlock
id|b
)paren
(brace
r_return
id|b-&gt;ofs
suffix:semicolon
)brace
DECL|function|mmMarkReserved
r_static
id|__inline__
r_void
id|mmMarkReserved
c_func
(paren
id|PMemBlock
id|b
)paren
(brace
id|b-&gt;reserved
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* &n; * input: total size in bytes&n; * return: a heap pointer if OK, NULL if error&n; */
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
suffix:semicolon
multiline_comment|/*&n; * Allocate &squot;size&squot; bytes with 2^align2 bytes alignment,&n; * restrict the search to free memory after &squot;startSearch&squot;&n; * depth and back buffers should be in different 4mb banks&n; * to get better page hits if possible&n; * input:&t;size = size of block&n; *       &t;align2 = 2^align2 bytes alignment&n; *&t;&t;startSearch = linear offset from start of heap to begin search&n; * return: pointer to the allocated block, 0 if error&n; */
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
suffix:semicolon
multiline_comment|/*&n; * Returns 1 if the block &squot;b&squot; is part of the heap &squot;heap&squot;&n; */
r_int
id|mmBlockInHeap
c_func
(paren
id|PMemBlock
id|heap
comma
id|PMemBlock
id|b
)paren
suffix:semicolon
multiline_comment|/*&n; * Free block starts at offset&n; * input: pointer to a block&n; * return: 0 if OK, -1 if error&n; */
r_int
id|mmFreeMem
c_func
(paren
id|PMemBlock
id|b
)paren
suffix:semicolon
multiline_comment|/* For debuging purpose. */
r_void
id|mmDumpMemInfo
c_func
(paren
id|memHeap_t
op_star
id|mmInit
)paren
suffix:semicolon
macro_line|#endif /* __SIS_DS_H__ */
eof
