multiline_comment|/*&n; * linux/fs/hfs/balloc.c&n; *&n; * Copyright (C) 1995-1997  Paul H. Hargrove&n; * This file may be distributed under the terms of the GNU General Public License.&n; *&n; * hfs_bnode_alloc() and hfs_bnode_bitop() are based on GPLed code&n; * Copyright (C) 1995  Michael Dreher&n; *&n; * This file contains the code to create and destroy nodes&n; * in the B-tree structure.&n; *&n; * &quot;XXX&quot; in a comment is a note to myself to consider changing something.&n; *&n; * In function preconditions the term &quot;valid&quot; applied to a pointer to&n; * a structure means that the pointer is non-NULL and the structure it&n; * points to has all fields initialized to consistent values.&n; *&n; * The code in this file initializes some structures which contain&n; * pointers by calling memset(&amp;foo, 0, sizeof(foo)).&n; * This produces the desired behavior only due to the non-ANSI&n; * assumption that the machine representation of NULL is all zeros.&n; */
macro_line|#include &quot;hfs_btree.h&quot;
multiline_comment|/*================ File-local functions ================*/
multiline_comment|/*&n; * get_new_node()&n; *&n; * Get a buffer for a new node with out reading it from disk.&n; */
DECL|function|get_new_node
r_static
id|hfs_buffer
id|get_new_node
c_func
(paren
r_struct
id|hfs_btree
op_star
id|tree
comma
id|hfs_u32
id|node
)paren
(brace
r_int
id|tmp
suffix:semicolon
id|hfs_buffer
id|retval
op_assign
id|HFS_BAD_BUFFER
suffix:semicolon
id|tmp
op_assign
id|hfs_extent_map
c_func
(paren
op_amp
id|tree-&gt;entry.u.file.data_fork
comma
id|node
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
)paren
(brace
id|retval
op_assign
id|hfs_buffer_get
c_func
(paren
id|tree-&gt;sys_mdb
comma
id|tmp
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_bnode_init()&n; *&n; * Description:&n; *   Initialize a newly allocated bnode.&n; * Input Variable(s):&n; *   struct hfs_btree *tree: Pointer to a B-tree&n; *   hfs_u32 node: the node number to allocate&n; * Output Variable(s):&n; *   NONE&n; * Returns:&n; *   struct hfs_bnode_ref for the new node&n; * Preconditions:&n; *   &squot;tree&squot; points to a &quot;valid&quot; (struct hfs_btree)&n; *   &squot;node&squot; exists and has been allocated in the bitmap of bnodes.&n; * Postconditions:&n; *   On success:&n; *    The node is not read from disk, nor added to the bnode cache.&n; *    The &squot;sticky&squot; and locking-related fields are all zero/NULL.&n; *    The bnode&squot;s nd{[FB]Link, Type, NHeight} fields are uninitialized.&n; *    The bnode&squot;s ndNRecs field and offsets table indicate an empty bnode.&n; *   On failure:&n; *    The node is deallocated.&n; */
DECL|function|hfs_bnode_init
r_static
r_struct
id|hfs_bnode_ref
id|hfs_bnode_init
c_func
(paren
r_struct
id|hfs_btree
op_star
id|tree
comma
id|hfs_u32
id|node
)paren
(brace
macro_line|#if defined(DEBUG_BNODES) || defined(DEBUG_ALL)
r_extern
r_int
id|bnode_count
suffix:semicolon
macro_line|#endif
r_struct
id|hfs_bnode_ref
id|retval
suffix:semicolon
id|retval.lock_type
op_assign
id|HFS_LOCK_NONE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|HFS_NEW
c_func
(paren
id|retval.bn
)paren
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_bnode_init: out of memory.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|bail2
suffix:semicolon
)brace
multiline_comment|/* Partially initialize the in-core structure */
id|memset
c_func
(paren
id|retval.bn
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|retval.bn
)paren
)paren
suffix:semicolon
id|retval.bn-&gt;magic
op_assign
id|HFS_BNODE_MAGIC
suffix:semicolon
id|retval.bn-&gt;tree
op_assign
id|tree
suffix:semicolon
id|retval.bn-&gt;node
op_assign
id|node
suffix:semicolon
id|hfs_init_waitqueue
c_func
(paren
op_amp
id|retval.bn-&gt;wqueue
)paren
suffix:semicolon
id|hfs_init_waitqueue
c_func
(paren
op_amp
id|retval.bn-&gt;rqueue
)paren
suffix:semicolon
id|hfs_bnode_lock
c_func
(paren
op_amp
id|retval
comma
id|HFS_LOCK_WRITE
)paren
suffix:semicolon
id|retval.bn-&gt;buf
op_assign
id|get_new_node
c_func
(paren
id|tree
comma
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hfs_buffer_ok
c_func
(paren
id|retval.bn-&gt;buf
)paren
)paren
(brace
r_goto
id|bail1
suffix:semicolon
)brace
macro_line|#if defined(DEBUG_BNODES) || defined(DEBUG_ALL)
op_increment
id|bnode_count
suffix:semicolon
macro_line|#endif
multiline_comment|/* Partially initialize the on-disk structure */
id|memset
c_func
(paren
id|hfs_buffer_data
c_func
(paren
id|retval.bn-&gt;buf
)paren
comma
l_int|0
comma
id|HFS_SECTOR_SIZE
)paren
suffix:semicolon
id|hfs_put_hs
c_func
(paren
r_sizeof
(paren
r_struct
id|NodeDescriptor
)paren
comma
id|RECTBL
c_func
(paren
id|retval.bn
comma
l_int|1
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
id|bail1
suffix:colon
id|HFS_DELETE
c_func
(paren
id|retval.bn
)paren
suffix:semicolon
id|bail2
suffix:colon
multiline_comment|/* clear the bit in the bitmap */
id|hfs_bnode_bitop
c_func
(paren
id|tree
comma
id|node
comma
l_int|0
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * init_mapnode()&n; *&n; * Description:&n; *   Initializes a given node as a mapnode in the given tree.&n; * Input Variable(s):&n; *   struct hfs_bnode *bn: the node to add the mapnode after.&n; *   hfs_u32: the node to use as a mapnode.&n; * Output Variable(s):&n; *   NONE&n; * Returns:&n; *   struct hfs_bnode *: the new mapnode or NULL&n; * Preconditions:&n; *   &squot;tree&squot; is a valid (struct hfs_btree).&n; *   &squot;node&squot; is the number of the first node in &squot;tree&squot; that is not&n; *    represented by a bit in the existing mapnodes.&n; * Postconditions:&n; *   On failure &squot;tree&squot; is unchanged and NULL is returned.&n; *   On success the node given by &squot;node&squot; has been added to the linked&n; *    list of mapnodes attached to &squot;tree&squot;, and has been initialized as&n; *    a valid mapnode with its first bit set to indicate itself as&n; *    allocated.&n; */
DECL|function|init_mapnode
r_static
r_struct
id|hfs_bnode
op_star
id|init_mapnode
c_func
(paren
r_struct
id|hfs_bnode
op_star
id|bn
comma
id|hfs_u32
id|node
)paren
(brace
macro_line|#if defined(DEBUG_BNODES) || defined(DEBUG_ALL)
r_extern
r_int
id|bnode_count
suffix:semicolon
macro_line|#endif
r_struct
id|hfs_bnode
op_star
id|retval
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|HFS_NEW
c_func
(paren
id|retval
)paren
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_bnode_add: out of memory.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|retval
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|retval
)paren
)paren
suffix:semicolon
id|retval-&gt;magic
op_assign
id|HFS_BNODE_MAGIC
suffix:semicolon
id|retval-&gt;tree
op_assign
id|bn-&gt;tree
suffix:semicolon
id|retval-&gt;node
op_assign
id|node
suffix:semicolon
id|retval-&gt;sticky
op_assign
id|HFS_STICKY
suffix:semicolon
id|retval-&gt;buf
op_assign
id|get_new_node
c_func
(paren
id|bn-&gt;tree
comma
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hfs_buffer_ok
c_func
(paren
id|retval-&gt;buf
)paren
)paren
(brace
id|HFS_DELETE
c_func
(paren
id|retval
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#if defined(DEBUG_BNODES) || defined(DEBUG_ALL)
op_increment
id|bnode_count
suffix:semicolon
macro_line|#endif
multiline_comment|/* Initialize the bnode data structure */
id|memset
c_func
(paren
id|hfs_buffer_data
c_func
(paren
id|retval-&gt;buf
)paren
comma
l_int|0
comma
id|HFS_SECTOR_SIZE
)paren
suffix:semicolon
id|retval-&gt;ndFLink
op_assign
l_int|0
suffix:semicolon
id|retval-&gt;ndBLink
op_assign
id|bn-&gt;node
suffix:semicolon
id|retval-&gt;ndType
op_assign
id|ndMapNode
suffix:semicolon
id|retval-&gt;ndNHeight
op_assign
l_int|0
suffix:semicolon
id|retval-&gt;ndNRecs
op_assign
l_int|1
suffix:semicolon
id|hfs_put_hs
c_func
(paren
r_sizeof
(paren
r_struct
id|NodeDescriptor
)paren
comma
id|RECTBL
c_func
(paren
id|retval
comma
l_int|1
)paren
)paren
suffix:semicolon
id|hfs_put_hs
c_func
(paren
l_int|0x1fa
comma
id|RECTBL
c_func
(paren
id|retval
comma
l_int|2
)paren
)paren
suffix:semicolon
op_star
(paren
(paren
id|hfs_u8
op_star
)paren
id|bnode_key
c_func
(paren
id|retval
comma
l_int|1
)paren
)paren
op_assign
l_int|0x80
suffix:semicolon
multiline_comment|/* set first bit of bitmap */
id|retval-&gt;prev
op_assign
id|bn
suffix:semicolon
id|hfs_bnode_commit
c_func
(paren
id|retval
)paren
suffix:semicolon
id|bn-&gt;ndFLink
op_assign
id|node
suffix:semicolon
id|bn-&gt;next
op_assign
id|retval
suffix:semicolon
id|hfs_bnode_commit
c_func
(paren
id|bn
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*================ Global functions ================*/
multiline_comment|/*&n; * hfs_bnode_bitop()&n; *&n; * Description:&n; *   Allocate/free the requested node of a B-tree of the hfs filesystem&n; *   by setting/clearing the corresponding bit in the B-tree bitmap.&n; *   The size of the B-tree will not be changed.&n; * Input Variable(s):&n; *   struct hfs_btree *tree: Pointer to a B-tree&n; *   hfs_u32 bitnr: The node number to free&n; *   int set: 0 to clear the bit, non-zero to set it.&n; * Output Variable(s):&n; *   None&n; * Returns:&n; *    0: no error&n; *   -1: The node was already allocated/free, nothing has been done.&n; *   -2: The node is out of range of the B-tree.&n; *   -4: not enough map nodes to hold all the bits&n; * Preconditions:&n; *   &squot;tree&squot; points to a &quot;valid&quot; (struct hfs_btree)&n; *   &squot;bitnr&squot; is a node number within the range of the btree, which is&n; *   currently free/allocated.&n; * Postconditions:&n; *   The bit number &squot;bitnr&squot; of the node bitmap is set/cleared and the&n; *   number of free nodes in the btree is decremented/incremented by one.&n; */
DECL|function|hfs_bnode_bitop
r_int
id|hfs_bnode_bitop
c_func
(paren
r_struct
id|hfs_btree
op_star
id|tree
comma
id|hfs_u32
id|bitnr
comma
r_int
id|set
)paren
(brace
r_struct
id|hfs_bnode
op_star
id|bn
suffix:semicolon
multiline_comment|/* the current bnode */
id|hfs_u16
id|start
suffix:semicolon
multiline_comment|/* the start (in bits) of the bitmap in node */
id|hfs_u16
id|len
suffix:semicolon
multiline_comment|/* the len (in bits) of the bitmap in node */
id|hfs_u32
op_star
id|u32
suffix:semicolon
multiline_comment|/* address of the u32 containing the bit */
r_if
c_cond
(paren
id|bitnr
op_ge
id|tree-&gt;bthNNodes
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_bnode_bitop: node number out of range.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|2
suffix:semicolon
)brace
id|bn
op_assign
op_amp
id|tree-&gt;head
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|start
op_assign
id|bnode_offset
c_func
(paren
id|bn
comma
id|bn-&gt;ndNRecs
)paren
op_lshift
l_int|3
suffix:semicolon
id|len
op_assign
(paren
id|bnode_offset
c_func
(paren
id|bn
comma
id|bn-&gt;ndNRecs
op_plus
l_int|1
)paren
op_lshift
l_int|3
)paren
op_minus
id|start
suffix:semicolon
r_if
c_cond
(paren
id|bitnr
OL
id|len
)paren
(brace
r_break
suffix:semicolon
)brace
multiline_comment|/* continue on to next map node if available */
r_if
c_cond
(paren
op_logical_neg
(paren
id|bn
op_assign
id|bn-&gt;next
)paren
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_bnode_bitop: too few map nodes.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|4
suffix:semicolon
)brace
id|bitnr
op_sub_assign
id|len
suffix:semicolon
)brace
multiline_comment|/* Change the correct bit */
id|bitnr
op_add_assign
id|start
suffix:semicolon
id|u32
op_assign
(paren
id|hfs_u32
op_star
)paren
id|hfs_buffer_data
c_func
(paren
id|bn-&gt;buf
)paren
op_plus
(paren
id|bitnr
op_rshift
l_int|5
)paren
suffix:semicolon
id|bitnr
op_mod_assign
l_int|32
suffix:semicolon
r_if
c_cond
(paren
(paren
id|set
op_logical_and
id|hfs_set_bit
c_func
(paren
id|bitnr
comma
id|u32
)paren
)paren
op_logical_or
(paren
op_logical_neg
id|set
op_logical_and
op_logical_neg
id|hfs_clear_bit
c_func
(paren
id|bitnr
comma
id|u32
)paren
)paren
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_bnode_bitop: bitmap corruption.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|hfs_buffer_dirty
c_func
(paren
id|bn-&gt;buf
)paren
suffix:semicolon
multiline_comment|/* adjust the free count */
id|tree-&gt;bthFree
op_add_assign
(paren
id|set
ques
c_cond
op_minus
l_int|1
suffix:colon
l_int|1
)paren
suffix:semicolon
id|tree-&gt;dirt
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_bnode_alloc()&n; *&n; * Description:&n; *   Find a cleared bit in the B-tree node bitmap of the hfs filesystem,&n; *   set it and return the corresponding bnode, with its contents zeroed.&n; *   When there is no free bnode in the tree, an error is returned, no&n; *   new nodes will be added by this function!&n; * Input Variable(s):&n; *   struct hfs_btree *tree: Pointer to a B-tree&n; * Output Variable(s):&n; *   NONE&n; * Returns:&n; *   struct hfs_bnode_ref for the new bnode&n; * Preconditions:&n; *   &squot;tree&squot; points to a &quot;valid&quot; (struct hfs_btree)&n; *   There is at least one free bnode.&n; * Postconditions:&n; *   On success:&n; *     The corresponding bit in the btree bitmap is set.&n; *     The number of free nodes in the btree is decremented by one.&n; *   The node is not read from disk, nor added to the bnode cache.&n; *   The &squot;sticky&squot; field is uninitialized.&n; */
DECL|function|hfs_bnode_alloc
r_struct
id|hfs_bnode_ref
id|hfs_bnode_alloc
c_func
(paren
r_struct
id|hfs_btree
op_star
id|tree
)paren
(brace
r_struct
id|hfs_bnode
op_star
id|bn
suffix:semicolon
multiline_comment|/* the current bnode */
id|hfs_u32
id|bitnr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* which bit are we examining */
id|hfs_u16
id|first
suffix:semicolon
multiline_comment|/* the first clear bit in this bnode */
id|hfs_u16
id|start
suffix:semicolon
multiline_comment|/* the start (in bits) of the bitmap in node */
id|hfs_u16
id|end
suffix:semicolon
multiline_comment|/* the end (in bits) of the bitmap in node */
id|hfs_u32
op_star
id|data
suffix:semicolon
multiline_comment|/* address of the data in this bnode */
id|bn
op_assign
op_amp
id|tree-&gt;head
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|start
op_assign
id|bnode_offset
c_func
(paren
id|bn
comma
id|bn-&gt;ndNRecs
)paren
op_lshift
l_int|3
suffix:semicolon
id|end
op_assign
id|bnode_offset
c_func
(paren
id|bn
comma
id|bn-&gt;ndNRecs
op_plus
l_int|1
)paren
op_lshift
l_int|3
suffix:semicolon
id|data
op_assign
(paren
id|hfs_u32
op_star
)paren
id|hfs_buffer_data
c_func
(paren
id|bn-&gt;buf
)paren
suffix:semicolon
multiline_comment|/* search the current node */
id|first
op_assign
id|hfs_find_zero_bit
c_func
(paren
id|data
comma
id|end
comma
id|start
)paren
suffix:semicolon
r_if
c_cond
(paren
id|first
OL
id|end
)paren
(brace
r_break
suffix:semicolon
)brace
multiline_comment|/* continue search in next map node */
id|bn
op_assign
id|bn-&gt;next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bn
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_bnode_alloc: too few map nodes.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|bail
suffix:semicolon
)brace
id|bitnr
op_add_assign
(paren
id|end
op_minus
id|start
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|bitnr
op_add_assign
(paren
id|first
op_minus
id|start
)paren
)paren
op_ge
id|tree-&gt;bthNNodes
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_bnode_alloc: no free nodes found, &quot;
l_string|&quot;count wrong?&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|bail
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hfs_set_bit
c_func
(paren
id|first
op_mod
l_int|32
comma
id|data
op_plus
(paren
id|first
op_rshift
l_int|5
)paren
)paren
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_bnode_alloc: bitmap corruption.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|bail
suffix:semicolon
)brace
id|hfs_buffer_dirty
c_func
(paren
id|bn-&gt;buf
)paren
suffix:semicolon
multiline_comment|/* decrement the free count */
op_decrement
id|tree-&gt;bthFree
suffix:semicolon
id|tree-&gt;dirt
op_assign
l_int|1
suffix:semicolon
r_return
id|hfs_bnode_init
c_func
(paren
id|tree
comma
id|bitnr
)paren
suffix:semicolon
id|bail
suffix:colon
r_return
(paren
r_struct
id|hfs_bnode_ref
)paren
(brace
l_int|NULL
comma
id|HFS_LOCK_NONE
)brace
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_btree_extend()&n; *&n; * Description:&n; *   Adds nodes to a B*-tree if possible.&n; * Input Variable(s):&n; *   struct hfs_btree *tree: the btree to add nodes to.&n; * Output Variable(s):&n; *   NONE&n; * Returns:&n; *   void&n; * Preconditions:&n; *   &squot;tree&squot; is a valid (struct hfs_btree *).&n; * Postconditions:&n; *   If possible the number of nodes indicated by the tree&squot;s clumpsize&n; *    have been added to the tree, updating all in-core and on-disk&n; *    allocation information.&n; *   If insufficient disk-space was available then fewer nodes may have&n; *    been added than would be expected based on the clumpsize.&n; *   In the case of the extents B*-tree this function will add fewer&n; *    nodes than expected if adding more would result in an extent&n; *    record for the extents tree being added to the extents tree.&n; *    The situation could be dealt with, but doing so confuses Macs.&n; */
DECL|function|hfs_btree_extend
r_void
id|hfs_btree_extend
c_func
(paren
r_struct
id|hfs_btree
op_star
id|tree
)paren
(brace
r_struct
id|hfs_bnode_ref
id|head
suffix:semicolon
r_struct
id|hfs_bnode
op_star
id|bn
comma
op_star
id|tmp
suffix:semicolon
r_struct
id|hfs_cat_entry
op_star
id|entry
op_assign
op_amp
id|tree-&gt;entry
suffix:semicolon
r_struct
id|hfs_mdb
op_star
id|mdb
op_assign
id|entry-&gt;mdb
suffix:semicolon
id|hfs_u32
id|old_nodes
comma
id|new_nodes
comma
id|total_nodes
comma
id|new_mapnodes
comma
id|seen
suffix:semicolon
id|old_nodes
op_assign
id|entry-&gt;u.file.data_fork.psize
suffix:semicolon
id|entry-&gt;u.file.data_fork.lsize
op_add_assign
l_int|1
suffix:semicolon
multiline_comment|/* rounded up to clumpsize */
id|hfs_extent_adj
c_func
(paren
op_amp
id|entry-&gt;u.file.data_fork
)paren
suffix:semicolon
id|total_nodes
op_assign
id|entry-&gt;u.file.data_fork.psize
suffix:semicolon
id|entry-&gt;u.file.data_fork.lsize
op_assign
id|total_nodes
op_lshift
id|HFS_SECTOR_SIZE_BITS
suffix:semicolon
id|new_nodes
op_assign
id|total_nodes
op_minus
id|old_nodes
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_nodes
)paren
(brace
r_return
suffix:semicolon
)brace
id|head
op_assign
id|hfs_bnode_find
c_func
(paren
id|tree
comma
l_int|0
comma
id|HFS_LOCK_WRITE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bn
op_assign
id|head.bn
)paren
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_btree_extend: header node not found.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|seen
op_assign
l_int|0
suffix:semicolon
id|new_mapnodes
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|seen
op_add_assign
id|bnode_rsize
c_func
(paren
id|bn
comma
id|bn-&gt;ndNRecs
)paren
op_lshift
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|seen
op_ge
id|total_nodes
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|bn-&gt;next
)paren
(brace
id|tmp
op_assign
id|init_mapnode
c_func
(paren
id|bn
comma
id|seen
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_btree_extend: &quot;
l_string|&quot;can&squot;t build mapnode.&bslash;n&quot;
)paren
suffix:semicolon
id|hfs_bnode_relse
c_func
(paren
op_amp
id|head
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
op_increment
id|new_mapnodes
suffix:semicolon
)brace
id|bn
op_assign
id|bn-&gt;next
suffix:semicolon
)brace
id|hfs_bnode_relse
c_func
(paren
op_amp
id|head
)paren
suffix:semicolon
id|tree-&gt;bthNNodes
op_assign
id|total_nodes
suffix:semicolon
id|tree-&gt;bthFree
op_add_assign
(paren
id|new_nodes
op_minus
id|new_mapnodes
)paren
suffix:semicolon
id|tree-&gt;dirt
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* write the backup MDB, not returning until it is written */
id|hfs_mdb_commit
c_func
(paren
id|mdb
comma
l_int|1
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_bnode_free()&n; *&n; * Remove a node from the cache and mark it free in the bitmap.&n; */
DECL|function|hfs_bnode_free
r_int
id|hfs_bnode_free
c_func
(paren
r_struct
id|hfs_bnode_ref
op_star
id|bnr
)paren
(brace
id|hfs_u32
id|node
op_assign
id|bnr-&gt;bn-&gt;node
suffix:semicolon
r_struct
id|hfs_btree
op_star
id|tree
op_assign
id|bnr-&gt;bn-&gt;tree
suffix:semicolon
r_if
c_cond
(paren
id|bnr-&gt;bn-&gt;count
op_ne
l_int|1
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_bnode_free: count != 1.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|hfs_bnode_relse
c_func
(paren
id|bnr
)paren
suffix:semicolon
id|hfs_bnode_bitop
c_func
(paren
id|tree
comma
id|node
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
