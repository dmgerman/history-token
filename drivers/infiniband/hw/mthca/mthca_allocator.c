multiline_comment|/*&n; * Copyright (c) 2004 Topspin Communications.  All rights reserved.&n; *&n; * This software is available to you under a choice of one of two&n; * licenses.  You may choose to be licensed under the terms of the GNU&n; * General Public License (GPL) Version 2, available from the file&n; * COPYING in the main directory of this source tree, or the&n; * OpenIB.org BSD license below:&n; *&n; *     Redistribution and use in source and binary forms, with or&n; *     without modification, are permitted provided that the following&n; *     conditions are met:&n; *&n; *      - Redistributions of source code must retain the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer.&n; *&n; *      - Redistributions in binary form must reproduce the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer in the documentation and/or other materials&n; *        provided with the distribution.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND,&n; * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF&n; * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND&n; * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS&n; * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN&n; * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN&n; * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE&n; * SOFTWARE.&n; *&n; * $Id: mthca_allocator.c 1349 2004-12-16 21:09:43Z roland $&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/bitmap.h&gt;
macro_line|#include &quot;mthca_dev.h&quot;
multiline_comment|/* Trivial bitmap-based allocator */
DECL|function|mthca_alloc
id|u32
id|mthca_alloc
c_func
(paren
r_struct
id|mthca_alloc
op_star
id|alloc
)paren
(brace
id|u32
id|obj
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|alloc-&gt;lock
)paren
suffix:semicolon
id|obj
op_assign
id|find_next_zero_bit
c_func
(paren
id|alloc-&gt;table
comma
id|alloc-&gt;max
comma
id|alloc-&gt;last
)paren
suffix:semicolon
r_if
c_cond
(paren
id|obj
op_ge
id|alloc-&gt;max
)paren
(brace
id|alloc-&gt;top
op_assign
(paren
id|alloc-&gt;top
op_plus
id|alloc-&gt;max
)paren
op_amp
id|alloc-&gt;mask
suffix:semicolon
id|obj
op_assign
id|find_first_zero_bit
c_func
(paren
id|alloc-&gt;table
comma
id|alloc-&gt;max
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|obj
OL
id|alloc-&gt;max
)paren
(brace
id|set_bit
c_func
(paren
id|obj
comma
id|alloc-&gt;table
)paren
suffix:semicolon
id|obj
op_or_assign
id|alloc-&gt;top
suffix:semicolon
)brace
r_else
id|obj
op_assign
op_minus
l_int|1
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|alloc-&gt;lock
)paren
suffix:semicolon
r_return
id|obj
suffix:semicolon
)brace
DECL|function|mthca_free
r_void
id|mthca_free
c_func
(paren
r_struct
id|mthca_alloc
op_star
id|alloc
comma
id|u32
id|obj
)paren
(brace
id|obj
op_and_assign
id|alloc-&gt;max
op_minus
l_int|1
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|alloc-&gt;lock
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|obj
comma
id|alloc-&gt;table
)paren
suffix:semicolon
id|alloc-&gt;last
op_assign
id|min
c_func
(paren
id|alloc-&gt;last
comma
id|obj
)paren
suffix:semicolon
id|alloc-&gt;top
op_assign
(paren
id|alloc-&gt;top
op_plus
id|alloc-&gt;max
)paren
op_amp
id|alloc-&gt;mask
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|alloc-&gt;lock
)paren
suffix:semicolon
)brace
DECL|function|mthca_alloc_init
r_int
id|mthca_alloc_init
c_func
(paren
r_struct
id|mthca_alloc
op_star
id|alloc
comma
id|u32
id|num
comma
id|u32
id|mask
comma
id|u32
id|reserved
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* num must be a power of 2 */
r_if
c_cond
(paren
id|num
op_ne
l_int|1
op_lshift
(paren
id|ffs
c_func
(paren
id|num
)paren
op_minus
l_int|1
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|alloc-&gt;last
op_assign
l_int|0
suffix:semicolon
id|alloc-&gt;top
op_assign
l_int|0
suffix:semicolon
id|alloc-&gt;max
op_assign
id|num
suffix:semicolon
id|alloc-&gt;mask
op_assign
id|mask
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|alloc-&gt;lock
)paren
suffix:semicolon
id|alloc-&gt;table
op_assign
id|kmalloc
c_func
(paren
id|BITS_TO_LONGS
c_func
(paren
id|num
)paren
op_star
r_sizeof
(paren
r_int
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|alloc-&gt;table
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|bitmap_zero
c_func
(paren
id|alloc-&gt;table
comma
id|num
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
id|reserved
suffix:semicolon
op_increment
id|i
)paren
id|set_bit
c_func
(paren
id|i
comma
id|alloc-&gt;table
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mthca_alloc_cleanup
r_void
id|mthca_alloc_cleanup
c_func
(paren
r_struct
id|mthca_alloc
op_star
id|alloc
)paren
(brace
id|kfree
c_func
(paren
id|alloc-&gt;table
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Array of pointers with lazy allocation of leaf pages.  Callers of&n; * _get, _set and _clear methods must use a lock or otherwise&n; * serialize access to the array.&n; */
DECL|function|mthca_array_get
r_void
op_star
id|mthca_array_get
c_func
(paren
r_struct
id|mthca_array
op_star
id|array
comma
r_int
id|index
)paren
(brace
r_int
id|p
op_assign
(paren
id|index
op_star
r_sizeof
(paren
r_void
op_star
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|array-&gt;page_list
(braket
id|p
)braket
dot
id|page
)paren
(brace
r_int
id|i
op_assign
id|index
op_amp
(paren
id|PAGE_SIZE
op_div
r_sizeof
(paren
r_void
op_star
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_return
id|array-&gt;page_list
(braket
id|p
)braket
dot
id|page
(braket
id|i
)braket
suffix:semicolon
)brace
r_else
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|mthca_array_set
r_int
id|mthca_array_set
c_func
(paren
r_struct
id|mthca_array
op_star
id|array
comma
r_int
id|index
comma
r_void
op_star
id|value
)paren
(brace
r_int
id|p
op_assign
(paren
id|index
op_star
r_sizeof
(paren
r_void
op_star
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
multiline_comment|/* Allocate with GFP_ATOMIC because we&squot;ll be called with locks held. */
r_if
c_cond
(paren
op_logical_neg
id|array-&gt;page_list
(braket
id|p
)braket
dot
id|page
)paren
id|array-&gt;page_list
(braket
id|p
)braket
dot
id|page
op_assign
(paren
r_void
op_star
op_star
)paren
id|get_zeroed_page
c_func
(paren
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|array-&gt;page_list
(braket
id|p
)braket
dot
id|page
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|array-&gt;page_list
(braket
id|p
)braket
dot
id|page
(braket
id|index
op_amp
(paren
id|PAGE_SIZE
op_div
r_sizeof
(paren
r_void
op_star
)paren
op_minus
l_int|1
)paren
)braket
op_assign
id|value
suffix:semicolon
op_increment
id|array-&gt;page_list
(braket
id|p
)braket
dot
id|used
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mthca_array_clear
r_void
id|mthca_array_clear
c_func
(paren
r_struct
id|mthca_array
op_star
id|array
comma
r_int
id|index
)paren
(brace
r_int
id|p
op_assign
(paren
id|index
op_star
r_sizeof
(paren
r_void
op_star
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|array-&gt;page_list
(braket
id|p
)braket
dot
id|used
op_eq
l_int|0
)paren
(brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|array-&gt;page_list
(braket
id|p
)braket
dot
id|page
)paren
suffix:semicolon
id|array-&gt;page_list
(braket
id|p
)braket
dot
id|page
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|array-&gt;page_list
(braket
id|p
)braket
dot
id|used
OL
l_int|0
)paren
id|pr_debug
c_func
(paren
l_string|&quot;Array %p index %d page %d with ref count %d &lt; 0&bslash;n&quot;
comma
id|array
comma
id|index
comma
id|p
comma
id|array-&gt;page_list
(braket
id|p
)braket
dot
id|used
)paren
suffix:semicolon
)brace
DECL|function|mthca_array_init
r_int
id|mthca_array_init
c_func
(paren
r_struct
id|mthca_array
op_star
id|array
comma
r_int
id|nent
)paren
(brace
r_int
id|npage
op_assign
(paren
id|nent
op_star
r_sizeof
(paren
r_void
op_star
)paren
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_div
id|PAGE_SIZE
suffix:semicolon
r_int
id|i
suffix:semicolon
id|array-&gt;page_list
op_assign
id|kmalloc
c_func
(paren
id|npage
op_star
r_sizeof
op_star
id|array-&gt;page_list
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|array-&gt;page_list
)paren
r_return
op_minus
id|ENOMEM
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
id|npage
suffix:semicolon
op_increment
id|i
)paren
(brace
id|array-&gt;page_list
(braket
id|i
)braket
dot
id|page
op_assign
l_int|NULL
suffix:semicolon
id|array-&gt;page_list
(braket
id|i
)braket
dot
id|used
op_assign
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mthca_array_cleanup
r_void
id|mthca_array_cleanup
c_func
(paren
r_struct
id|mthca_array
op_star
id|array
comma
r_int
id|nent
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
(paren
id|nent
op_star
r_sizeof
(paren
r_void
op_star
)paren
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_div
id|PAGE_SIZE
suffix:semicolon
op_increment
id|i
)paren
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|array-&gt;page_list
(braket
id|i
)braket
dot
id|page
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|array-&gt;page_list
)paren
suffix:semicolon
)brace
eof
