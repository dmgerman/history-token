multiline_comment|/*&n; * 2002-10-18  written by Jim Houston jim.houston@ccur.com&n; *&t;Copyright (C) 2002 by Concurrent Computer Corporation&n; *&t;Distributed under the GNU GPL license version 2.&n; *&n; * Modified by George Anzinger to reuse immediately and to use&n; * find bit instructions.  Also removed _irq on spinlocks.&n; *&n; * Small id to pointer translation service.  &n; *&n; * It uses a radix tree like structure as a sparse array indexed &n; * by the id to obtain the pointer.  The bitmap makes allocating&n; * a new id quick.  &n; *&n; * You call it to allocate an id (an int) an associate with that id a&n; * pointer or what ever, we treat it as a (void *).  You can pass this&n; * id to a user for him to pass back at a later time.  You then pass&n; * that id to this code and it returns your pointer.&n;&n; * You can release ids at any time. When all ids are released, most of &n; * the memory is returned (we keep IDR_FREE_MAX) in a local pool so we&n; * don&squot;t need to go to the memory &quot;store&quot; during an id allocate, just &n; * so you don&squot;t need to be too concerned about locking and conflicts&n; * with the slab allocator.&n; */
macro_line|#ifndef TEST                        
singleline_comment|// to test in user space...
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/idr.h&gt;
DECL|variable|idr_layer_cache
r_static
id|kmem_cache_t
op_star
id|idr_layer_cache
suffix:semicolon
DECL|function|alloc_layer
r_static
r_struct
id|idr_layer
op_star
id|alloc_layer
c_func
(paren
r_struct
id|idr
op_star
id|idp
)paren
(brace
r_struct
id|idr_layer
op_star
id|p
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|idp-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|idp-&gt;id_free
)paren
)paren
(brace
id|idp-&gt;id_free
op_assign
id|p-&gt;ary
(braket
l_int|0
)braket
suffix:semicolon
id|idp-&gt;id_free_cnt
op_decrement
suffix:semicolon
id|p-&gt;ary
(braket
l_int|0
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|idp-&gt;lock
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
DECL|function|free_layer
r_static
r_void
id|free_layer
c_func
(paren
r_struct
id|idr
op_star
id|idp
comma
r_struct
id|idr_layer
op_star
id|p
)paren
(brace
multiline_comment|/*&n;&t; * Depends on the return element being zeroed.&n;&t; */
id|spin_lock
c_func
(paren
op_amp
id|idp-&gt;lock
)paren
suffix:semicolon
id|p-&gt;ary
(braket
l_int|0
)braket
op_assign
id|idp-&gt;id_free
suffix:semicolon
id|idp-&gt;id_free
op_assign
id|p
suffix:semicolon
id|idp-&gt;id_free_cnt
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|idp-&gt;lock
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * idr_pre_get - reserver resources for idr allocation&n; * @idp:&t;idr handle&n; * @gfp_mask:&t;memory allocation flags&n; *&n; * This function should be called prior to locking and calling the&n; * following function.  It preallocates enough memory to satisfy&n; * the worst possible allocation.&n; *&n; * If the system is REALLY out of memory this function returns 0,&n; * otherwise 1.&n; */
DECL|function|idr_pre_get
r_int
id|idr_pre_get
c_func
(paren
r_struct
id|idr
op_star
id|idp
comma
r_int
id|gfp_mask
)paren
(brace
r_while
c_loop
(paren
id|idp-&gt;id_free_cnt
OL
id|IDR_FREE_MAX
)paren
(brace
r_struct
id|idr_layer
op_star
r_new
suffix:semicolon
r_new
op_assign
id|kmem_cache_alloc
c_func
(paren
id|idr_layer_cache
comma
id|gfp_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
op_eq
l_int|NULL
)paren
(brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|free_layer
c_func
(paren
id|idp
comma
r_new
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|idr_pre_get
id|EXPORT_SYMBOL
c_func
(paren
id|idr_pre_get
)paren
suffix:semicolon
DECL|function|sub_alloc
r_static
r_int
id|sub_alloc
c_func
(paren
r_struct
id|idr
op_star
id|idp
comma
r_void
op_star
id|ptr
comma
r_int
op_star
id|starting_id
)paren
(brace
r_int
id|n
comma
id|m
comma
id|sh
suffix:semicolon
r_struct
id|idr_layer
op_star
id|p
comma
op_star
r_new
suffix:semicolon
r_struct
id|idr_layer
op_star
id|pa
(braket
id|MAX_LEVEL
)braket
suffix:semicolon
r_int
id|l
comma
id|id
suffix:semicolon
r_int
id|bm
suffix:semicolon
id|id
op_assign
op_star
id|starting_id
suffix:semicolon
id|p
op_assign
id|idp-&gt;top
suffix:semicolon
id|l
op_assign
id|idp-&gt;layers
suffix:semicolon
id|pa
(braket
id|l
op_decrement
)braket
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
multiline_comment|/*&n;&t;&t; * We run around this while until we reach the leaf node...&n;&t;&t; */
id|n
op_assign
(paren
id|id
op_rshift
(paren
id|IDR_BITS
op_star
id|l
)paren
)paren
op_amp
id|IDR_MASK
suffix:semicolon
id|bm
op_assign
op_complement
id|p-&gt;bitmap
suffix:semicolon
id|m
op_assign
id|find_next_bit
c_func
(paren
op_amp
id|bm
comma
id|IDR_SIZE
comma
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m
op_eq
id|IDR_SIZE
)paren
(brace
multiline_comment|/* no space available go back to previous layer. */
id|l
op_increment
suffix:semicolon
id|id
op_assign
(paren
id|id
op_or
(paren
(paren
l_int|1
op_lshift
(paren
id|IDR_BITS
op_star
id|l
)paren
)paren
op_minus
l_int|1
)paren
)paren
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|pa
(braket
id|l
)braket
)paren
)paren
(brace
op_star
id|starting_id
op_assign
id|id
suffix:semicolon
r_return
op_minus
l_int|2
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|m
op_ne
id|n
)paren
(brace
id|sh
op_assign
id|IDR_BITS
op_star
id|l
suffix:semicolon
id|id
op_assign
(paren
(paren
id|id
op_rshift
id|sh
)paren
op_xor
id|n
op_xor
id|m
)paren
op_lshift
id|sh
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|id
op_ge
id|MAX_ID_BIT
)paren
op_logical_or
(paren
id|id
OL
l_int|0
)paren
)paren
r_return
op_minus
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|l
op_eq
l_int|0
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Create the layer below if it is missing.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;ary
(braket
id|m
)braket
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
r_new
op_assign
id|alloc_layer
c_func
(paren
id|idp
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|p-&gt;ary
(braket
id|m
)braket
op_assign
r_new
suffix:semicolon
id|p-&gt;count
op_increment
suffix:semicolon
)brace
id|pa
(braket
id|l
op_decrement
)braket
op_assign
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;ary
(braket
id|m
)braket
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * We have reached the leaf node, plant the&n;&t; * users pointer and return the raw id.&n;&t; */
id|p-&gt;ary
(braket
id|m
)braket
op_assign
(paren
r_struct
id|idr_layer
op_star
)paren
id|ptr
suffix:semicolon
id|__set_bit
c_func
(paren
id|m
comma
op_amp
id|p-&gt;bitmap
)paren
suffix:semicolon
id|p-&gt;count
op_increment
suffix:semicolon
multiline_comment|/*&n;&t; * If this layer is full mark the bit in the layer above&n;&t; * to show that this part of the radix tree is full.&n;&t; * This may complete the layer above and require walking&n;&t; * up the radix tree.&n;&t; */
id|n
op_assign
id|id
suffix:semicolon
r_while
c_loop
(paren
id|p-&gt;bitmap
op_eq
id|IDR_FULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|pa
(braket
op_increment
id|l
)braket
)paren
)paren
r_break
suffix:semicolon
id|n
op_assign
id|n
op_rshift
id|IDR_BITS
suffix:semicolon
id|__set_bit
c_func
(paren
(paren
id|n
op_amp
id|IDR_MASK
)paren
comma
op_amp
id|p-&gt;bitmap
)paren
suffix:semicolon
)brace
r_return
id|id
suffix:semicolon
)brace
DECL|function|idr_get_new_above_int
r_static
r_int
id|idr_get_new_above_int
c_func
(paren
r_struct
id|idr
op_star
id|idp
comma
r_void
op_star
id|ptr
comma
r_int
id|starting_id
)paren
(brace
r_struct
id|idr_layer
op_star
id|p
comma
op_star
r_new
suffix:semicolon
r_int
id|layers
comma
id|v
comma
id|id
suffix:semicolon
id|id
op_assign
id|starting_id
suffix:semicolon
id|build_up
suffix:colon
id|p
op_assign
id|idp-&gt;top
suffix:semicolon
id|layers
op_assign
id|idp-&gt;layers
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|p
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|alloc_layer
c_func
(paren
id|idp
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|layers
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Add a new layer to the top of the tree if the requested&n;&t; * id is larger than the currently allocated space.&n;&t; */
r_while
c_loop
(paren
(paren
id|layers
OL
id|MAX_LEVEL
)paren
op_logical_and
(paren
id|id
op_ge
(paren
l_int|1
op_lshift
(paren
id|layers
op_star
id|IDR_BITS
)paren
)paren
)paren
)paren
(brace
id|layers
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;count
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
r_new
op_assign
id|alloc_layer
c_func
(paren
id|idp
)paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * The allocation failed.  If we built part of&n;&t;&t;&t; * the structure tear it down.&n;&t;&t;&t; */
r_for
c_loop
(paren
r_new
op_assign
id|p
suffix:semicolon
id|p
op_logical_and
id|p
op_ne
id|idp-&gt;top
suffix:semicolon
r_new
op_assign
id|p
)paren
(brace
id|p
op_assign
id|p-&gt;ary
(braket
l_int|0
)braket
suffix:semicolon
r_new
op_member_access_from_pointer
id|ary
(braket
l_int|0
)braket
op_assign
l_int|NULL
suffix:semicolon
r_new
op_member_access_from_pointer
id|bitmap
op_assign
r_new
op_member_access_from_pointer
id|count
op_assign
l_int|0
suffix:semicolon
id|free_layer
c_func
(paren
id|idp
comma
r_new
)paren
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_new
op_member_access_from_pointer
id|ary
(braket
l_int|0
)braket
op_assign
id|p
suffix:semicolon
r_new
op_member_access_from_pointer
id|count
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;bitmap
op_eq
id|IDR_FULL
)paren
id|__set_bit
c_func
(paren
l_int|0
comma
op_amp
r_new
op_member_access_from_pointer
id|bitmap
)paren
suffix:semicolon
id|p
op_assign
r_new
suffix:semicolon
)brace
id|idp-&gt;top
op_assign
id|p
suffix:semicolon
id|idp-&gt;layers
op_assign
id|layers
suffix:semicolon
id|v
op_assign
id|sub_alloc
c_func
(paren
id|idp
comma
id|ptr
comma
op_amp
id|id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|v
op_eq
op_minus
l_int|2
)paren
r_goto
id|build_up
suffix:semicolon
r_return
id|v
suffix:semicolon
)brace
multiline_comment|/**&n; * idr_get_new_above - allocate new idr entry above a start id&n; * @idp: idr handle&n; * @ptr: pointer you want associated with the ide&n; * @start_id: id to start search at&n; * @id: pointer to the allocated handle&n; *&n; * This is the allocate id function.  It should be called with any&n; * required locks.&n; *&n; * If memory is required, it will return -EAGAIN, you should unlock&n; * and go back to the idr_pre_get() call.  If the idr is full, it will&n; * return -ENOSPC.&n; *&n; * @id returns a value in the range 0 ... 0x7fffffff&n; */
DECL|function|idr_get_new_above
r_int
id|idr_get_new_above
c_func
(paren
r_struct
id|idr
op_star
id|idp
comma
r_void
op_star
id|ptr
comma
r_int
id|starting_id
comma
r_int
op_star
id|id
)paren
(brace
r_int
id|rv
suffix:semicolon
id|rv
op_assign
id|idr_get_new_above_int
c_func
(paren
id|idp
comma
id|ptr
comma
id|starting_id
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This is a cheap hack until the IDR code can be fixed to&n;&t; * return proper error values.&n;&t; */
r_if
c_cond
(paren
id|rv
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|rv
op_eq
op_minus
l_int|1
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_else
multiline_comment|/* Will be -3 */
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
op_star
id|id
op_assign
id|rv
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|idr_get_new_above
id|EXPORT_SYMBOL
c_func
(paren
id|idr_get_new_above
)paren
suffix:semicolon
multiline_comment|/**&n; * idr_get_new - allocate new idr entry&n; * @idp: idr handle&n; * @ptr: pointer you want associated with the ide&n; * @id: pointer to the allocated handle&n; *&n; * This is the allocate id function.  It should be called with any&n; * required locks.&n; *&n; * If memory is required, it will return -EAGAIN, you should unlock&n; * and go back to the idr_pre_get() call.  If the idr is full, it will&n; * return -ENOSPC.&n; *&n; * @id returns a value in the range 0 ... 0x7fffffff&n; */
DECL|function|idr_get_new
r_int
id|idr_get_new
c_func
(paren
r_struct
id|idr
op_star
id|idp
comma
r_void
op_star
id|ptr
comma
r_int
op_star
id|id
)paren
(brace
r_int
id|rv
suffix:semicolon
id|rv
op_assign
id|idr_get_new_above_int
c_func
(paren
id|idp
comma
id|ptr
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This is a cheap hack until the IDR code can be fixed to&n;&t; * return proper error values.&n;&t; */
r_if
c_cond
(paren
id|rv
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|rv
op_eq
op_minus
l_int|1
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_else
multiline_comment|/* Will be -3 */
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
op_star
id|id
op_assign
id|rv
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|idr_get_new
id|EXPORT_SYMBOL
c_func
(paren
id|idr_get_new
)paren
suffix:semicolon
DECL|function|idr_remove_warning
r_static
r_void
id|idr_remove_warning
c_func
(paren
r_int
id|id
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;idr_remove called for id=%d which is not allocated.&bslash;n&quot;
comma
id|id
)paren
suffix:semicolon
id|dump_stack
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|sub_remove
r_static
r_void
id|sub_remove
c_func
(paren
r_struct
id|idr
op_star
id|idp
comma
r_int
id|shift
comma
r_int
id|id
)paren
(brace
r_struct
id|idr_layer
op_star
id|p
op_assign
id|idp-&gt;top
suffix:semicolon
r_struct
id|idr_layer
op_star
op_star
id|pa
(braket
id|MAX_LEVEL
)braket
suffix:semicolon
r_struct
id|idr_layer
op_star
op_star
op_star
id|paa
op_assign
op_amp
id|pa
(braket
l_int|0
)braket
suffix:semicolon
r_int
id|n
suffix:semicolon
op_star
id|paa
op_assign
l_int|NULL
suffix:semicolon
op_star
op_increment
id|paa
op_assign
op_amp
id|idp-&gt;top
suffix:semicolon
r_while
c_loop
(paren
(paren
id|shift
OG
l_int|0
)paren
op_logical_and
id|p
)paren
(brace
id|n
op_assign
(paren
id|id
op_rshift
id|shift
)paren
op_amp
id|IDR_MASK
suffix:semicolon
id|__clear_bit
c_func
(paren
id|n
comma
op_amp
id|p-&gt;bitmap
)paren
suffix:semicolon
op_star
op_increment
id|paa
op_assign
op_amp
id|p-&gt;ary
(braket
id|n
)braket
suffix:semicolon
id|p
op_assign
id|p-&gt;ary
(braket
id|n
)braket
suffix:semicolon
id|shift
op_sub_assign
id|IDR_BITS
suffix:semicolon
)brace
id|n
op_assign
id|id
op_amp
id|IDR_MASK
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|p
op_ne
l_int|NULL
op_logical_and
id|test_bit
c_func
(paren
id|n
comma
op_amp
id|p-&gt;bitmap
)paren
)paren
)paren
(brace
id|__clear_bit
c_func
(paren
id|n
comma
op_amp
id|p-&gt;bitmap
)paren
suffix:semicolon
id|p-&gt;ary
(braket
id|n
)braket
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
op_star
id|paa
op_logical_and
op_logical_neg
op_decrement
(paren
(paren
op_star
op_star
id|paa
)paren
op_member_access_from_pointer
id|count
)paren
)paren
(brace
id|free_layer
c_func
(paren
id|idp
comma
op_star
op_star
id|paa
)paren
suffix:semicolon
op_star
op_star
id|paa
op_decrement
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|paa
)paren
id|idp-&gt;layers
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|idr_remove_warning
c_func
(paren
id|id
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * idr_remove - remove the given id and free it&squot;s slot&n; * idp: idr handle&n; * id: uniqueue key&n; */
DECL|function|idr_remove
r_void
id|idr_remove
c_func
(paren
r_struct
id|idr
op_star
id|idp
comma
r_int
id|id
)paren
(brace
r_struct
id|idr_layer
op_star
id|p
suffix:semicolon
multiline_comment|/* Mask off upper bits we don&squot;t use for the search. */
id|id
op_and_assign
id|MAX_ID_MASK
suffix:semicolon
id|sub_remove
c_func
(paren
id|idp
comma
(paren
id|idp-&gt;layers
op_minus
l_int|1
)paren
op_star
id|IDR_BITS
comma
id|id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idp-&gt;top
op_logical_and
id|idp-&gt;top-&gt;count
op_eq
l_int|1
op_logical_and
(paren
id|idp-&gt;layers
OG
l_int|1
)paren
op_logical_and
id|idp-&gt;top-&gt;ary
(braket
l_int|0
)braket
)paren
(brace
singleline_comment|// We can drop a layer
id|p
op_assign
id|idp-&gt;top-&gt;ary
(braket
l_int|0
)braket
suffix:semicolon
id|idp-&gt;top-&gt;bitmap
op_assign
id|idp-&gt;top-&gt;count
op_assign
l_int|0
suffix:semicolon
id|free_layer
c_func
(paren
id|idp
comma
id|idp-&gt;top
)paren
suffix:semicolon
id|idp-&gt;top
op_assign
id|p
suffix:semicolon
op_decrement
id|idp-&gt;layers
suffix:semicolon
)brace
r_while
c_loop
(paren
id|idp-&gt;id_free_cnt
op_ge
id|IDR_FREE_MAX
)paren
(brace
id|p
op_assign
id|alloc_layer
c_func
(paren
id|idp
)paren
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|idr_layer_cache
comma
id|p
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
DECL|variable|idr_remove
id|EXPORT_SYMBOL
c_func
(paren
id|idr_remove
)paren
suffix:semicolon
multiline_comment|/**&n; * idr_find - return pointer for given id&n; * @idp: idr handle&n; * @id: lookup key&n; *&n; * Return the pointer given the id it has been registered with.  A %NULL&n; * return indicates that @id is not valid or you passed %NULL in&n; * idr_get_new().&n; *&n; * The caller must serialize idr_find() vs idr_get_new() and idr_remove().&n; */
DECL|function|idr_find
r_void
op_star
id|idr_find
c_func
(paren
r_struct
id|idr
op_star
id|idp
comma
r_int
id|id
)paren
(brace
r_int
id|n
suffix:semicolon
r_struct
id|idr_layer
op_star
id|p
suffix:semicolon
id|n
op_assign
id|idp-&gt;layers
op_star
id|IDR_BITS
suffix:semicolon
id|p
op_assign
id|idp-&gt;top
suffix:semicolon
multiline_comment|/* Mask off upper bits we don&squot;t use for the search. */
id|id
op_and_assign
id|MAX_ID_MASK
suffix:semicolon
r_if
c_cond
(paren
id|id
op_ge
(paren
l_int|1
op_lshift
id|n
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|n
OG
l_int|0
op_logical_and
id|p
)paren
(brace
id|n
op_sub_assign
id|IDR_BITS
suffix:semicolon
id|p
op_assign
id|p-&gt;ary
(braket
(paren
id|id
op_rshift
id|n
)paren
op_amp
id|IDR_MASK
)braket
suffix:semicolon
)brace
r_return
(paren
r_void
op_star
)paren
id|p
suffix:semicolon
)brace
DECL|variable|idr_find
id|EXPORT_SYMBOL
c_func
(paren
id|idr_find
)paren
suffix:semicolon
DECL|function|idr_cache_ctor
r_static
r_void
id|idr_cache_ctor
c_func
(paren
r_void
op_star
id|idr_layer
comma
id|kmem_cache_t
op_star
id|idr_layer_cache
comma
r_int
r_int
id|flags
)paren
(brace
id|memset
c_func
(paren
id|idr_layer
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|idr_layer
)paren
)paren
suffix:semicolon
)brace
DECL|function|init_id_cache
r_static
r_int
id|init_id_cache
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|idr_layer_cache
)paren
id|idr_layer_cache
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;idr_layer_cache&quot;
comma
r_sizeof
(paren
r_struct
id|idr_layer
)paren
comma
l_int|0
comma
l_int|0
comma
id|idr_cache_ctor
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * idr_init - initialize idr handle&n; * @idp:&t;idr handle&n; *&n; * This function is use to set up the handle (@idp) that you will pass&n; * to the rest of the functions.&n; */
DECL|function|idr_init
r_void
id|idr_init
c_func
(paren
r_struct
id|idr
op_star
id|idp
)paren
(brace
id|init_id_cache
c_func
(paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|idp
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|idr
)paren
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|idp-&gt;lock
)paren
suffix:semicolon
)brace
DECL|variable|idr_init
id|EXPORT_SYMBOL
c_func
(paren
id|idr_init
)paren
suffix:semicolon
eof
