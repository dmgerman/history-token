multiline_comment|/*&n; * linux/kernel/id.c&n; *&n; * 2002-10-18  written by Jim Houston jim.houston@ccur.com&n; *&t;Copyright (C) 2002 by Concurrent Computer Corporation&n; *&t;Distributed under the GNU GPL license version 2.&n; *&n; * Small id to pointer translation service.  &n; *&n; * It uses a radix tree like structure as a sparse array indexed &n; * by the id to obtain the pointer.  The bitmap makes allocating&n; * a new id quick.  &n;&n; * Modified by George Anzinger to reuse immediately and to use&n; * find bit instructions.  Also removed _irq on spinlocks.&n;&n; * So here is what this bit of code does:&n;&n; * You call it to allocate an id (an int) an associate with that id a&n; * pointer or what ever, we treat it as a (void *).  You can pass this&n; * id to a user for him to pass back at a later time.  You then pass&n; * that id to this code and it returns your pointer.&n;&n; * You can release ids at any time. When all ids are released, most of &n; * the memory is returned (we keep IDR_FREE_MAX) in a local pool so we&n; * don&squot;t need to go to the memory &quot;store&quot; during an id allocate, just &n; * so you don&squot;t need to be too concerned about locking and conflicts&n; * with the slab allocator.&n;&n; * A word on reuse.  We reuse empty id slots as soon as we can, always&n; * using the lowest one available.  But we also merge a counter in the&n; * high bits of the id.  The counter is RESERVED_ID_BITS (8 at this time)&n; * long.  This means that if you allocate and release the same id in a &n; * loop we will reuse an id after about 256 times around the loop.  The&n; * word about is used here as we will NOT return a valid id of -1 so if&n; * you loop on the largest possible id (and that is 24 bits, wow!) we&n; * will kick the counter to avoid -1.  (Paranoid?  You bet!)&n; *&n; * What you need to do is, since we don&squot;t keep the counter as part of&n; * id / ptr pair, to keep a copy of it in the pointed to structure&n; * (or else where) so that when you ask for a ptr you can varify that&n; * the returned ptr is correct by comparing the id it contains with the one&n; * you asked for.  In other words, we only did half the reuse protection.&n; * Since the code depends on your code doing this check, we ignore high&n; * order bits in the id, not just the count, but bits that would, if used,&n; * index outside of the allocated ids.  In other words, if the largest id&n; * currently allocated is 32 a look up will only look at the low 5 bits of&n; * the id.  Since you will want to keep this id in the structure anyway&n; * (if for no other reason than to be able to eliminate the id when the&n; * structure is found in some other way) this seems reasonable.  If you&n; * really think otherwise, the code to check these bits here, it is just&n; * disabled with a #if 0.&n;&n;&n; * So here are the complete details:&n;&n; *  include &lt;linux/idr.h&gt;&n;&n; * void idr_init(struct idr *idp)&n;&n; *   This function is use to set up the handle (idp) that you will pass&n; *   to the rest of the functions.  The structure is defined in the&n; *   header.&n;&n; * int idr_pre_get(struct idr *idp, unsigned gfp_mask)&n;&n; *   This function should be called prior to locking and calling the&n; *   following function.  It pre allocates enough memory to satisfy the&n; *   worst possible allocation.  Unless gfp_mask is GFP_ATOMIC, it can&n; *   sleep, so must not be called with any spinlocks held.  If the system is&n; *   REALLY out of memory this function returns 0, other wise 1.&n;&n; * int idr_get_new(struct idr *idp, void *ptr);&n; &n; *   This is the allocate id function.  It should be called with any&n; *   required locks.  In fact, in the SMP case, you MUST lock prior to&n; *   calling this function to avoid possible out of memory problems.  If&n; *   memory is required, it will return a -1, in which case you should&n; *   unlock and go back to the idr_pre_get() call.  ptr is the pointer&n; *   you want associated with the id.  In other words:&n;&n; * void *idr_find(struct idr *idp, int id);&n; &n; *   returns the &quot;ptr&quot;, given the id.  A NULL return indicates that the&n; *   id is not valid (or you passed NULL in the idr_get_new(), shame on&n; *   you).  This function must be called with a spinlock that prevents&n; *   calling either idr_get_new() or idr_remove() or idr_find() while it&n; *   is working.&n;&n; * void idr_remove(struct idr *idp, int id);&n;&n; *   removes the given id, freeing that slot and any memory that may&n; *   now be unused.  See idr_find() for locking restrictions.&n;&n; */
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
r_inline
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
op_logical_neg
(paren
id|p
op_assign
id|idp-&gt;id_free
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
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
l_int|0
suffix:semicolon
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
r_inline
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
id|idp-&gt;layers
op_plus
l_int|1
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
r_inline
r_int
id|sub_alloc
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
r_void
op_star
id|ptr
)paren
(brace
r_int
id|n
comma
id|v
op_assign
l_int|0
suffix:semicolon
r_struct
id|idr_layer
op_star
id|p
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
multiline_comment|/*&n;&t; * By keeping each pointer in an array we can do the &n;&t; * &quot;after&quot; recursion processing.  In this case, that means&n;&t; * we can update the upper level bit map.&n;&t; */
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|p
op_assign
op_star
op_star
id|paa
suffix:semicolon
id|n
op_assign
id|ffz
c_func
(paren
id|p-&gt;bitmap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shift
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * We run around this while until we&n;&t;&t;&t; * reach the leaf node...&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;ary
(braket
id|n
)braket
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * If no node, allocate one, AFTER&n;&t;&t;&t;&t; * we insure that we will not&n;&t;&t;&t;&t; * intrude on the reserved bit field.&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|n
op_lshift
id|shift
)paren
op_ge
id|MAX_ID_BIT
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|p-&gt;ary
(braket
id|n
)braket
op_assign
id|alloc_layer
c_func
(paren
id|idp
)paren
suffix:semicolon
id|p-&gt;count
op_increment
suffix:semicolon
)brace
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
id|v
op_add_assign
(paren
id|n
op_lshift
id|shift
)paren
suffix:semicolon
id|shift
op_sub_assign
id|IDR_BITS
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * We have reached the leaf node, plant the&n;&t;&t;&t; * users pointer and return the raw id.&n;&t;&t;&t; */
id|p-&gt;ary
(braket
id|n
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
id|n
comma
op_amp
id|p-&gt;bitmap
)paren
suffix:semicolon
id|v
op_add_assign
id|n
suffix:semicolon
id|p-&gt;count
op_increment
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * This is the post recursion processing.  Once&n;&t;&t;&t; * we find a bitmap that is not full we are&n;&t;&t;&t; * done&n;&t;&t;&t; */
r_while
c_loop
(paren
op_star
(paren
id|paa
op_minus
l_int|1
)paren
op_logical_and
(paren
op_star
op_star
id|paa
)paren
op_member_access_from_pointer
id|bitmap
op_eq
id|IDR_FULL
)paren
(brace
id|n
op_assign
op_star
id|paa
op_minus
op_amp
(paren
op_star
op_star
(paren
id|paa
op_minus
l_int|1
)paren
)paren
op_member_access_from_pointer
id|ary
(braket
l_int|0
)braket
suffix:semicolon
id|__set_bit
c_func
(paren
id|n
comma
op_amp
(paren
op_star
op_star
op_decrement
id|paa
)paren
op_member_access_from_pointer
id|bitmap
)paren
suffix:semicolon
)brace
r_return
id|v
suffix:semicolon
)brace
)brace
)brace
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
)paren
(brace
r_int
id|v
suffix:semicolon
r_if
c_cond
(paren
id|idp-&gt;id_free_cnt
OL
id|idp-&gt;layers
op_plus
l_int|1
)paren
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Add a new layer if the array is full &n;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|idp-&gt;top
op_logical_or
id|idp-&gt;top-&gt;bitmap
op_eq
id|IDR_FULL
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * This is a bit different than the lower layers because&n;&t;&t; * we have one branch already allocated and full.&n;&t;&t; */
r_struct
id|idr_layer
op_star
r_new
op_assign
id|alloc_layer
c_func
(paren
id|idp
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|ary
(braket
l_int|0
)braket
op_assign
id|idp-&gt;top
suffix:semicolon
r_if
c_cond
(paren
id|idp-&gt;top
)paren
op_increment
r_new
op_member_access_from_pointer
id|count
suffix:semicolon
id|idp-&gt;top
op_assign
r_new
suffix:semicolon
r_if
c_cond
(paren
id|idp-&gt;layers
op_increment
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
)brace
id|v
op_assign
id|sub_alloc
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
id|ptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|v
op_ge
l_int|0
)paren
)paren
(brace
id|idp-&gt;count
op_increment
suffix:semicolon
id|v
op_add_assign
(paren
id|idp-&gt;count
op_lshift
id|MAX_ID_SHIFT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|v
op_eq
op_minus
l_int|1
)paren
)paren
id|v
op_add_assign
(paren
l_int|1L
op_lshift
id|MAX_ID_SHIFT
)paren
suffix:semicolon
)brace
r_return
id|v
suffix:semicolon
)brace
DECL|variable|idr_get_new
id|EXPORT_SYMBOL
c_func
(paren
id|idr_get_new
)paren
suffix:semicolon
DECL|function|sub_remove
r_static
r_inline
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
r_int
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
r_if
c_cond
(paren
id|likely
c_func
(paren
id|p
op_ne
l_int|NULL
)paren
)paren
(brace
r_int
id|n
op_assign
id|id
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
)brace
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
macro_line|#if 0
multiline_comment|/*&n;&t; * This tests to see if bits outside the current tree are&n;&t; * present.  If so, tain&squot;t one of ours!&n;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
(paren
id|id
op_amp
op_complement
(paren
op_complement
l_int|0
op_lshift
id|MAX_ID_SHIFT
)paren
)paren
op_rshift
(paren
id|n
op_plus
id|IDR_BITS
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
macro_line|#endif
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
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
