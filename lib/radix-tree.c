multiline_comment|/*&n; * Copyright (C) 2001 Momchil Velikov&n; * Portions Copyright (C) 2001 Christoph Hellwig&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as&n; * published by the Free Software Foundation; either version 2, or (at&n; * your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/radix-tree.h&gt;
macro_line|#include &lt;linux/percpu.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/gfp.h&gt;
macro_line|#include &lt;linux/string.h&gt;
multiline_comment|/*&n; * Radix tree node definition.&n; */
DECL|macro|RADIX_TREE_MAP_SHIFT
mdefine_line|#define RADIX_TREE_MAP_SHIFT  6
DECL|macro|RADIX_TREE_MAP_SIZE
mdefine_line|#define RADIX_TREE_MAP_SIZE  (1UL &lt;&lt; RADIX_TREE_MAP_SHIFT)
DECL|macro|RADIX_TREE_MAP_MASK
mdefine_line|#define RADIX_TREE_MAP_MASK  (RADIX_TREE_MAP_SIZE-1)
DECL|struct|radix_tree_node
r_struct
id|radix_tree_node
(brace
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
DECL|member|slots
r_void
op_star
id|slots
(braket
id|RADIX_TREE_MAP_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|radix_tree_path
r_struct
id|radix_tree_path
(brace
DECL|member|node
DECL|member|slot
r_struct
id|radix_tree_node
op_star
id|node
comma
op_star
op_star
id|slot
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RADIX_TREE_INDEX_BITS
mdefine_line|#define RADIX_TREE_INDEX_BITS  (8 /* CHAR_BIT */ * sizeof(unsigned long))
DECL|macro|RADIX_TREE_MAX_PATH
mdefine_line|#define RADIX_TREE_MAX_PATH (RADIX_TREE_INDEX_BITS/RADIX_TREE_MAP_SHIFT + 2)
DECL|variable|height_to_maxindex
r_static
r_int
r_int
id|height_to_maxindex
(braket
id|RADIX_TREE_MAX_PATH
)braket
suffix:semicolon
multiline_comment|/*&n; * Radix tree node cache.&n; */
DECL|variable|radix_tree_node_cachep
r_static
id|kmem_cache_t
op_star
id|radix_tree_node_cachep
suffix:semicolon
multiline_comment|/*&n; * Per-cpu pool of preloaded nodes&n; */
DECL|struct|radix_tree_preload
r_struct
id|radix_tree_preload
(brace
DECL|member|nr
r_int
id|nr
suffix:semicolon
DECL|member|nodes
r_struct
id|radix_tree_node
op_star
id|nodes
(braket
id|RADIX_TREE_MAX_PATH
)braket
suffix:semicolon
)brace
suffix:semicolon
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|radix_tree_preload
comma
id|radix_tree_preloads
)paren
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * This assumes that the caller has performed appropriate preallocation, and&n; * that the caller has pinned this thread of control to the current CPU.&n; */
r_static
r_struct
id|radix_tree_node
op_star
DECL|function|radix_tree_node_alloc
id|radix_tree_node_alloc
c_func
(paren
r_struct
id|radix_tree_root
op_star
id|root
)paren
(brace
r_struct
id|radix_tree_node
op_star
id|ret
suffix:semicolon
id|ret
op_assign
id|kmem_cache_alloc
c_func
(paren
id|radix_tree_node_cachep
comma
id|root-&gt;gfp_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|NULL
op_logical_and
op_logical_neg
(paren
id|root-&gt;gfp_mask
op_amp
id|__GFP_WAIT
)paren
)paren
(brace
r_struct
id|radix_tree_preload
op_star
id|rtp
suffix:semicolon
id|rtp
op_assign
op_amp
id|__get_cpu_var
c_func
(paren
id|radix_tree_preloads
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rtp-&gt;nr
)paren
(brace
id|ret
op_assign
id|rtp-&gt;nodes
(braket
id|rtp-&gt;nr
op_minus
l_int|1
)braket
suffix:semicolon
id|rtp-&gt;nodes
(braket
id|rtp-&gt;nr
op_minus
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
id|rtp-&gt;nr
op_decrement
suffix:semicolon
)brace
)brace
r_return
id|ret
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|radix_tree_node_free
id|radix_tree_node_free
c_func
(paren
r_struct
id|radix_tree_node
op_star
id|node
)paren
(brace
id|kmem_cache_free
c_func
(paren
id|radix_tree_node_cachep
comma
id|node
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Load up this CPU&squot;s radix_tree_node buffer with sufficient objects to&n; * ensure that the addition of a single element in the tree cannot fail.  On&n; * success, return zero, with preemption disabled.  On error, return -ENOMEM&n; * with preemption not disabled.&n; */
DECL|function|radix_tree_preload
r_int
id|radix_tree_preload
c_func
(paren
r_int
id|gfp_mask
)paren
(brace
r_struct
id|radix_tree_preload
op_star
id|rtp
suffix:semicolon
r_struct
id|radix_tree_node
op_star
id|node
suffix:semicolon
r_int
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|rtp
op_assign
op_amp
id|__get_cpu_var
c_func
(paren
id|radix_tree_preloads
)paren
suffix:semicolon
r_while
c_loop
(paren
id|rtp-&gt;nr
OL
id|ARRAY_SIZE
c_func
(paren
id|rtp-&gt;nodes
)paren
)paren
(brace
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
id|node
op_assign
id|kmem_cache_alloc
c_func
(paren
id|radix_tree_node_cachep
comma
id|gfp_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|node
op_eq
l_int|NULL
)paren
r_goto
id|out
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|rtp
op_assign
op_amp
id|__get_cpu_var
c_func
(paren
id|radix_tree_preloads
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rtp-&gt;nr
OL
id|ARRAY_SIZE
c_func
(paren
id|rtp-&gt;nodes
)paren
)paren
id|rtp-&gt;nodes
(braket
id|rtp-&gt;nr
op_increment
)braket
op_assign
id|node
suffix:semicolon
r_else
id|kmem_cache_free
c_func
(paren
id|radix_tree_node_cachep
comma
id|node
)paren
suffix:semicolon
)brace
id|ret
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Return the maximum key which can be store into a&n; *&t;radix tree with height HEIGHT.&n; */
DECL|function|radix_tree_maxindex
r_static
r_inline
r_int
r_int
id|radix_tree_maxindex
c_func
(paren
r_int
r_int
id|height
)paren
(brace
r_return
id|height_to_maxindex
(braket
id|height
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Extend a radix tree so it can store key @index.&n; */
DECL|function|radix_tree_extend
r_static
r_int
id|radix_tree_extend
c_func
(paren
r_struct
id|radix_tree_root
op_star
id|root
comma
r_int
r_int
id|index
)paren
(brace
r_struct
id|radix_tree_node
op_star
id|node
suffix:semicolon
r_int
r_int
id|height
suffix:semicolon
multiline_comment|/* Figure out what the height should be.  */
id|height
op_assign
id|root-&gt;height
op_plus
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|index
OG
id|radix_tree_maxindex
c_func
(paren
id|height
)paren
)paren
id|height
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|root-&gt;rnode
)paren
(brace
r_do
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|node
op_assign
id|radix_tree_node_alloc
c_func
(paren
id|root
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* Increase the height.  */
id|node-&gt;slots
(braket
l_int|0
)braket
op_assign
id|root-&gt;rnode
suffix:semicolon
id|node-&gt;count
op_assign
l_int|1
suffix:semicolon
id|root-&gt;rnode
op_assign
id|node
suffix:semicolon
id|root-&gt;height
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|height
OG
id|root-&gt;height
)paren
suffix:semicolon
)brace
r_else
id|root-&gt;height
op_assign
id|height
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;radix_tree_insert    -    insert into a radix tree&n; *&t;@root:&t;&t;radix tree root&n; *&t;@index:&t;&t;index key&n; *&t;@item:&t;&t;item to insert&n; *&n; *&t;Insert an item into the radix tree at position @index.&n; */
DECL|function|radix_tree_insert
r_int
id|radix_tree_insert
c_func
(paren
r_struct
id|radix_tree_root
op_star
id|root
comma
r_int
r_int
id|index
comma
r_void
op_star
id|item
)paren
(brace
r_struct
id|radix_tree_node
op_star
id|node
op_assign
l_int|NULL
comma
op_star
id|tmp
comma
op_star
op_star
id|slot
suffix:semicolon
r_int
r_int
id|height
comma
id|shift
suffix:semicolon
r_int
id|error
suffix:semicolon
multiline_comment|/* Make sure the tree is high enough.  */
r_if
c_cond
(paren
id|index
OG
id|radix_tree_maxindex
c_func
(paren
id|root-&gt;height
)paren
)paren
(brace
id|error
op_assign
id|radix_tree_extend
c_func
(paren
id|root
comma
id|index
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
)brace
id|slot
op_assign
op_amp
id|root-&gt;rnode
suffix:semicolon
id|height
op_assign
id|root-&gt;height
suffix:semicolon
id|shift
op_assign
(paren
id|height
op_minus
l_int|1
)paren
op_star
id|RADIX_TREE_MAP_SHIFT
suffix:semicolon
r_while
c_loop
(paren
id|height
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_star
id|slot
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* Have to add a child node.  */
r_if
c_cond
(paren
op_logical_neg
(paren
id|tmp
op_assign
id|radix_tree_node_alloc
c_func
(paren
id|root
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
op_star
id|slot
op_assign
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|node
)paren
id|node-&gt;count
op_increment
suffix:semicolon
)brace
multiline_comment|/* Go a level down.  */
id|node
op_assign
op_star
id|slot
suffix:semicolon
id|slot
op_assign
(paren
r_struct
id|radix_tree_node
op_star
op_star
)paren
(paren
id|node-&gt;slots
op_plus
(paren
(paren
id|index
op_rshift
id|shift
)paren
op_amp
id|RADIX_TREE_MAP_MASK
)paren
)paren
suffix:semicolon
id|shift
op_sub_assign
id|RADIX_TREE_MAP_SHIFT
suffix:semicolon
id|height
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|slot
op_ne
l_int|NULL
)paren
r_return
op_minus
id|EEXIST
suffix:semicolon
r_if
c_cond
(paren
id|node
)paren
id|node-&gt;count
op_increment
suffix:semicolon
op_star
id|slot
op_assign
id|item
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|radix_tree_insert
id|EXPORT_SYMBOL
c_func
(paren
id|radix_tree_insert
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;radix_tree_lookup    -    perform lookup operation on a radix tree&n; *&t;@root:&t;&t;radix tree root&n; *&t;@index:&t;&t;index key&n; *&n; *&t;Lookup them item at the position @index in the radix tree @root.&n; */
DECL|function|radix_tree_lookup
r_void
op_star
id|radix_tree_lookup
c_func
(paren
r_struct
id|radix_tree_root
op_star
id|root
comma
r_int
r_int
id|index
)paren
(brace
r_int
r_int
id|height
comma
id|shift
suffix:semicolon
r_struct
id|radix_tree_node
op_star
op_star
id|slot
suffix:semicolon
id|height
op_assign
id|root-&gt;height
suffix:semicolon
r_if
c_cond
(paren
id|index
OG
id|radix_tree_maxindex
c_func
(paren
id|height
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|shift
op_assign
(paren
id|height
op_minus
l_int|1
)paren
op_star
id|RADIX_TREE_MAP_SHIFT
suffix:semicolon
id|slot
op_assign
op_amp
id|root-&gt;rnode
suffix:semicolon
r_while
c_loop
(paren
id|height
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_star
id|slot
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|slot
op_assign
(paren
r_struct
id|radix_tree_node
op_star
op_star
)paren
(paren
(paren
op_star
id|slot
)paren
op_member_access_from_pointer
id|slots
op_plus
(paren
(paren
id|index
op_rshift
id|shift
)paren
op_amp
id|RADIX_TREE_MAP_MASK
)paren
)paren
suffix:semicolon
id|shift
op_sub_assign
id|RADIX_TREE_MAP_SHIFT
suffix:semicolon
id|height
op_decrement
suffix:semicolon
)brace
r_return
(paren
r_void
op_star
)paren
op_star
id|slot
suffix:semicolon
)brace
DECL|variable|radix_tree_lookup
id|EXPORT_SYMBOL
c_func
(paren
id|radix_tree_lookup
)paren
suffix:semicolon
r_static
multiline_comment|/* inline */
r_int
r_int
DECL|function|__lookup
id|__lookup
c_func
(paren
r_struct
id|radix_tree_root
op_star
id|root
comma
r_void
op_star
op_star
id|results
comma
r_int
r_int
id|index
comma
r_int
r_int
id|max_items
comma
r_int
r_int
op_star
id|next_index
)paren
(brace
r_int
r_int
id|nr_found
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|shift
suffix:semicolon
r_int
r_int
id|height
op_assign
id|root-&gt;height
suffix:semicolon
r_struct
id|radix_tree_node
op_star
id|slot
suffix:semicolon
id|shift
op_assign
(paren
id|height
op_minus
l_int|1
)paren
op_star
id|RADIX_TREE_MAP_SHIFT
suffix:semicolon
id|slot
op_assign
id|root-&gt;rnode
suffix:semicolon
r_while
c_loop
(paren
id|height
OG
l_int|0
)paren
(brace
r_int
r_int
id|i
op_assign
(paren
id|index
op_rshift
id|shift
)paren
op_amp
id|RADIX_TREE_MAP_MASK
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
id|RADIX_TREE_MAP_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|slot-&gt;slots
(braket
id|i
)braket
op_ne
l_int|NULL
)paren
r_break
suffix:semicolon
id|index
op_and_assign
op_complement
(paren
(paren
l_int|1
op_lshift
id|shift
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|index
op_add_assign
l_int|1
op_lshift
id|shift
suffix:semicolon
r_if
c_cond
(paren
id|index
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* 32-bit wraparound */
)brace
r_if
c_cond
(paren
id|i
op_eq
id|RADIX_TREE_MAP_SIZE
)paren
r_goto
id|out
suffix:semicolon
id|height
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|height
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Bottom level: grab some items */
r_int
r_int
id|j
op_assign
id|index
op_amp
id|RADIX_TREE_MAP_MASK
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|j
OL
id|RADIX_TREE_MAP_SIZE
suffix:semicolon
id|j
op_increment
)paren
(brace
id|index
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|slot-&gt;slots
(braket
id|j
)braket
)paren
(brace
id|results
(braket
id|nr_found
op_increment
)braket
op_assign
id|slot-&gt;slots
(braket
id|j
)braket
suffix:semicolon
r_if
c_cond
(paren
id|nr_found
op_eq
id|max_items
)paren
r_goto
id|out
suffix:semicolon
)brace
)brace
)brace
id|shift
op_sub_assign
id|RADIX_TREE_MAP_SHIFT
suffix:semicolon
id|slot
op_assign
id|slot-&gt;slots
(braket
id|i
)braket
suffix:semicolon
)brace
id|out
suffix:colon
op_star
id|next_index
op_assign
id|index
suffix:semicolon
r_return
id|nr_found
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;radix_tree_gang_lookup - perform multiple lookup on a radix tree&n; *&t;@root:&t;&t;radix tree root&n; *&t;@results:&t;where the results of the lookup are placed&n; *&t;@first_index:&t;start the lookup from this key&n; *&t;@max_items:&t;place up to this many items at *results&n; *&n; *&t;Performs an index-ascending scan of the tree for present items.  Places&n; *&t;them at *@results and returns the number of items which were placed at&n; *&t;*@results.&n; *&n; *&t;The implementation is naive.&n; */
r_int
r_int
DECL|function|radix_tree_gang_lookup
id|radix_tree_gang_lookup
c_func
(paren
r_struct
id|radix_tree_root
op_star
id|root
comma
r_void
op_star
op_star
id|results
comma
r_int
r_int
id|first_index
comma
r_int
r_int
id|max_items
)paren
(brace
r_const
r_int
r_int
id|max_index
op_assign
id|radix_tree_maxindex
c_func
(paren
id|root-&gt;height
)paren
suffix:semicolon
r_int
r_int
id|cur_index
op_assign
id|first_index
suffix:semicolon
r_int
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|root-&gt;rnode
op_eq
l_int|NULL
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|max_index
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Bah.  Special case */
r_if
c_cond
(paren
id|first_index
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|max_items
OG
l_int|0
)paren
(brace
op_star
id|results
op_assign
id|root-&gt;rnode
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_goto
id|out
suffix:semicolon
)brace
r_while
c_loop
(paren
id|ret
OL
id|max_items
)paren
(brace
r_int
r_int
id|nr_found
suffix:semicolon
r_int
r_int
id|next_index
suffix:semicolon
multiline_comment|/* Index of next search */
r_if
c_cond
(paren
id|cur_index
OG
id|max_index
)paren
r_break
suffix:semicolon
id|nr_found
op_assign
id|__lookup
c_func
(paren
id|root
comma
id|results
op_plus
id|ret
comma
id|cur_index
comma
id|max_items
op_minus
id|ret
comma
op_amp
id|next_index
)paren
suffix:semicolon
id|ret
op_add_assign
id|nr_found
suffix:semicolon
r_if
c_cond
(paren
id|next_index
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|cur_index
op_assign
id|next_index
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|radix_tree_gang_lookup
id|EXPORT_SYMBOL
c_func
(paren
id|radix_tree_gang_lookup
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;radix_tree_delete    -    delete an item from a radix tree&n; *&t;@root:&t;&t;radix tree root&n; *&t;@index:&t;&t;index key&n; *&n; *&t;Remove the item at @index from the radix tree rooted at @root.&n; *&n; *&t;Returns the address of the deleted item, or NULL if it was not present.&n; */
DECL|function|radix_tree_delete
r_void
op_star
id|radix_tree_delete
c_func
(paren
r_struct
id|radix_tree_root
op_star
id|root
comma
r_int
r_int
id|index
)paren
(brace
r_struct
id|radix_tree_path
id|path
(braket
id|RADIX_TREE_MAX_PATH
)braket
comma
op_star
id|pathp
op_assign
id|path
suffix:semicolon
r_int
r_int
id|height
comma
id|shift
suffix:semicolon
r_void
op_star
id|ret
op_assign
l_int|NULL
suffix:semicolon
id|height
op_assign
id|root-&gt;height
suffix:semicolon
r_if
c_cond
(paren
id|index
OG
id|radix_tree_maxindex
c_func
(paren
id|height
)paren
)paren
r_goto
id|out
suffix:semicolon
id|shift
op_assign
(paren
id|height
op_minus
l_int|1
)paren
op_star
id|RADIX_TREE_MAP_SHIFT
suffix:semicolon
id|pathp-&gt;node
op_assign
l_int|NULL
suffix:semicolon
id|pathp-&gt;slot
op_assign
op_amp
id|root-&gt;rnode
suffix:semicolon
r_while
c_loop
(paren
id|height
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_star
id|pathp-&gt;slot
op_eq
l_int|NULL
)paren
r_goto
id|out
suffix:semicolon
id|pathp
(braket
l_int|1
)braket
dot
id|node
op_assign
op_star
id|pathp
(braket
l_int|0
)braket
dot
id|slot
suffix:semicolon
id|pathp
(braket
l_int|1
)braket
dot
id|slot
op_assign
(paren
r_struct
id|radix_tree_node
op_star
op_star
)paren
(paren
id|pathp
(braket
l_int|1
)braket
dot
id|node-&gt;slots
op_plus
(paren
(paren
id|index
op_rshift
id|shift
)paren
op_amp
id|RADIX_TREE_MAP_MASK
)paren
)paren
suffix:semicolon
id|pathp
op_increment
suffix:semicolon
id|shift
op_sub_assign
id|RADIX_TREE_MAP_SHIFT
suffix:semicolon
id|height
op_decrement
suffix:semicolon
)brace
id|ret
op_assign
op_star
id|pathp
(braket
l_int|0
)braket
dot
id|slot
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|NULL
)paren
r_goto
id|out
suffix:semicolon
op_star
id|pathp
(braket
l_int|0
)braket
dot
id|slot
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|pathp
(braket
l_int|0
)braket
dot
id|node
op_logical_and
op_decrement
id|pathp
(braket
l_int|0
)braket
dot
id|node-&gt;count
op_eq
l_int|0
)paren
(brace
id|pathp
op_decrement
suffix:semicolon
op_star
id|pathp
(braket
l_int|0
)braket
dot
id|slot
op_assign
l_int|NULL
suffix:semicolon
id|radix_tree_node_free
c_func
(paren
id|pathp
(braket
l_int|1
)braket
dot
id|node
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|root-&gt;rnode
op_eq
l_int|NULL
)paren
id|root-&gt;height
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Empty tree, we can reset the height */
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|radix_tree_delete
id|EXPORT_SYMBOL
c_func
(paren
id|radix_tree_delete
)paren
suffix:semicolon
r_static
r_void
DECL|function|radix_tree_node_ctor
id|radix_tree_node_ctor
c_func
(paren
r_void
op_star
id|node
comma
id|kmem_cache_t
op_star
id|cachep
comma
r_int
r_int
id|flags
)paren
(brace
id|memset
c_func
(paren
id|node
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|radix_tree_node
)paren
)paren
suffix:semicolon
)brace
DECL|function|__maxindex
r_static
id|__init
r_int
r_int
id|__maxindex
c_func
(paren
r_int
r_int
id|height
)paren
(brace
r_int
r_int
id|tmp
op_assign
id|height
op_star
id|RADIX_TREE_MAP_SHIFT
suffix:semicolon
r_int
r_int
id|index
op_assign
(paren
op_complement
l_int|0UL
op_rshift
(paren
id|RADIX_TREE_INDEX_BITS
op_minus
id|tmp
op_minus
l_int|1
)paren
)paren
op_rshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ge
id|RADIX_TREE_INDEX_BITS
)paren
id|index
op_assign
op_complement
l_int|0UL
suffix:semicolon
r_return
id|index
suffix:semicolon
)brace
DECL|function|radix_tree_init_maxindex
r_static
id|__init
r_void
id|radix_tree_init_maxindex
c_func
(paren
r_void
)paren
(brace
r_int
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
id|ARRAY_SIZE
c_func
(paren
id|height_to_maxindex
)paren
suffix:semicolon
id|i
op_increment
)paren
id|height_to_maxindex
(braket
id|i
)braket
op_assign
id|__maxindex
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
DECL|function|radix_tree_init
r_void
id|__init
id|radix_tree_init
c_func
(paren
r_void
)paren
(brace
id|radix_tree_node_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;radix_tree_node&quot;
comma
r_sizeof
(paren
r_struct
id|radix_tree_node
)paren
comma
l_int|0
comma
l_int|0
comma
id|radix_tree_node_ctor
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|radix_tree_node_cachep
)paren
id|panic
(paren
l_string|&quot;Failed to create radix_tree_node cache&bslash;n&quot;
)paren
suffix:semicolon
id|radix_tree_init_maxindex
c_func
(paren
)paren
suffix:semicolon
)brace
eof
