multiline_comment|/*&n; *  linux/fs/hfs/bnode.c&n; *&n; * Copyright (C) 2001&n; * Brad Boyer (flar@allandria.com)&n; * (C) 2003 Ardis Technologies &lt;roman@ardistech.com&gt;&n; *&n; * Handle basic btree node operations&n; */
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &quot;btree.h&quot;
DECL|macro|REF_PAGES
mdefine_line|#define REF_PAGES&t;0
DECL|function|hfs_bnode_read
r_void
id|hfs_bnode_read
c_func
(paren
r_struct
id|hfs_bnode
op_star
id|node
comma
r_void
op_star
id|buf
comma
r_int
id|off
comma
r_int
id|len
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
id|off
op_add_assign
id|node-&gt;page_offset
suffix:semicolon
id|page
op_assign
id|node-&gt;page
(braket
l_int|0
)braket
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|kmap
c_func
(paren
id|page
)paren
op_plus
id|off
comma
id|len
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
DECL|function|hfs_bnode_read_u16
id|u16
id|hfs_bnode_read_u16
c_func
(paren
r_struct
id|hfs_bnode
op_star
id|node
comma
r_int
id|off
)paren
(brace
id|__be16
id|data
suffix:semicolon
singleline_comment|// optimize later...
id|hfs_bnode_read
c_func
(paren
id|node
comma
op_amp
id|data
comma
id|off
comma
l_int|2
)paren
suffix:semicolon
r_return
id|be16_to_cpu
c_func
(paren
id|data
)paren
suffix:semicolon
)brace
DECL|function|hfs_bnode_read_u8
id|u8
id|hfs_bnode_read_u8
c_func
(paren
r_struct
id|hfs_bnode
op_star
id|node
comma
r_int
id|off
)paren
(brace
id|u8
id|data
suffix:semicolon
singleline_comment|// optimize later...
id|hfs_bnode_read
c_func
(paren
id|node
comma
op_amp
id|data
comma
id|off
comma
l_int|1
)paren
suffix:semicolon
r_return
id|data
suffix:semicolon
)brace
DECL|function|hfs_bnode_read_key
r_void
id|hfs_bnode_read_key
c_func
(paren
r_struct
id|hfs_bnode
op_star
id|node
comma
r_void
op_star
id|key
comma
r_int
id|off
)paren
(brace
r_struct
id|hfs_btree
op_star
id|tree
suffix:semicolon
r_int
id|key_len
suffix:semicolon
id|tree
op_assign
id|node-&gt;tree
suffix:semicolon
r_if
c_cond
(paren
id|node-&gt;type
op_eq
id|HFS_NODE_LEAF
op_logical_or
id|tree-&gt;attributes
op_amp
id|HFS_TREE_VARIDXKEYS
)paren
id|key_len
op_assign
id|hfs_bnode_read_u8
c_func
(paren
id|node
comma
id|off
)paren
op_plus
l_int|1
suffix:semicolon
r_else
id|key_len
op_assign
id|tree-&gt;max_key_len
op_plus
l_int|1
suffix:semicolon
id|hfs_bnode_read
c_func
(paren
id|node
comma
id|key
comma
id|off
comma
id|key_len
)paren
suffix:semicolon
)brace
DECL|function|hfs_bnode_write
r_void
id|hfs_bnode_write
c_func
(paren
r_struct
id|hfs_bnode
op_star
id|node
comma
r_void
op_star
id|buf
comma
r_int
id|off
comma
r_int
id|len
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
id|off
op_add_assign
id|node-&gt;page_offset
suffix:semicolon
id|page
op_assign
id|node-&gt;page
(braket
l_int|0
)braket
suffix:semicolon
id|memcpy
c_func
(paren
id|kmap
c_func
(paren
id|page
)paren
op_plus
id|off
comma
id|buf
comma
id|len
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|set_page_dirty
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
DECL|function|hfs_bnode_write_u16
r_void
id|hfs_bnode_write_u16
c_func
(paren
r_struct
id|hfs_bnode
op_star
id|node
comma
r_int
id|off
comma
id|u16
id|data
)paren
(brace
id|__be16
id|v
op_assign
id|cpu_to_be16
c_func
(paren
id|data
)paren
suffix:semicolon
singleline_comment|// optimize later...
id|hfs_bnode_write
c_func
(paren
id|node
comma
op_amp
id|v
comma
id|off
comma
l_int|2
)paren
suffix:semicolon
)brace
DECL|function|hfs_bnode_write_u8
r_void
id|hfs_bnode_write_u8
c_func
(paren
r_struct
id|hfs_bnode
op_star
id|node
comma
r_int
id|off
comma
id|u8
id|data
)paren
(brace
singleline_comment|// optimize later...
id|hfs_bnode_write
c_func
(paren
id|node
comma
op_amp
id|data
comma
id|off
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|hfs_bnode_clear
r_void
id|hfs_bnode_clear
c_func
(paren
r_struct
id|hfs_bnode
op_star
id|node
comma
r_int
id|off
comma
r_int
id|len
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
id|off
op_add_assign
id|node-&gt;page_offset
suffix:semicolon
id|page
op_assign
id|node-&gt;page
(braket
l_int|0
)braket
suffix:semicolon
id|memset
c_func
(paren
id|kmap
c_func
(paren
id|page
)paren
op_plus
id|off
comma
l_int|0
comma
id|len
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|set_page_dirty
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
DECL|function|hfs_bnode_copy
r_void
id|hfs_bnode_copy
c_func
(paren
r_struct
id|hfs_bnode
op_star
id|dst_node
comma
r_int
id|dst
comma
r_struct
id|hfs_bnode
op_star
id|src_node
comma
r_int
id|src
comma
r_int
id|len
)paren
(brace
r_struct
id|hfs_btree
op_star
id|tree
suffix:semicolon
r_struct
id|page
op_star
id|src_page
comma
op_star
id|dst_page
suffix:semicolon
id|dprint
c_func
(paren
id|DBG_BNODE_MOD
comma
l_string|&quot;copybytes: %u,%u,%u&bslash;n&quot;
comma
id|dst
comma
id|src
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_return
suffix:semicolon
id|tree
op_assign
id|src_node-&gt;tree
suffix:semicolon
id|src
op_add_assign
id|src_node-&gt;page_offset
suffix:semicolon
id|dst
op_add_assign
id|dst_node-&gt;page_offset
suffix:semicolon
id|src_page
op_assign
id|src_node-&gt;page
(braket
l_int|0
)braket
suffix:semicolon
id|dst_page
op_assign
id|dst_node-&gt;page
(braket
l_int|0
)braket
suffix:semicolon
id|memcpy
c_func
(paren
id|kmap
c_func
(paren
id|dst_page
)paren
op_plus
id|dst
comma
id|kmap
c_func
(paren
id|src_page
)paren
op_plus
id|src
comma
id|len
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|src_page
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|dst_page
)paren
suffix:semicolon
id|set_page_dirty
c_func
(paren
id|dst_page
)paren
suffix:semicolon
)brace
DECL|function|hfs_bnode_move
r_void
id|hfs_bnode_move
c_func
(paren
r_struct
id|hfs_bnode
op_star
id|node
comma
r_int
id|dst
comma
r_int
id|src
comma
r_int
id|len
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
r_void
op_star
id|ptr
suffix:semicolon
id|dprint
c_func
(paren
id|DBG_BNODE_MOD
comma
l_string|&quot;movebytes: %u,%u,%u&bslash;n&quot;
comma
id|dst
comma
id|src
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_return
suffix:semicolon
id|src
op_add_assign
id|node-&gt;page_offset
suffix:semicolon
id|dst
op_add_assign
id|node-&gt;page_offset
suffix:semicolon
id|page
op_assign
id|node-&gt;page
(braket
l_int|0
)braket
suffix:semicolon
id|ptr
op_assign
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|memmove
c_func
(paren
id|ptr
op_plus
id|dst
comma
id|ptr
op_plus
id|src
comma
id|len
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|set_page_dirty
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
DECL|function|hfs_bnode_dump
r_void
id|hfs_bnode_dump
c_func
(paren
r_struct
id|hfs_bnode
op_star
id|node
)paren
(brace
r_struct
id|hfs_bnode_desc
id|desc
suffix:semicolon
id|__be32
id|cnid
suffix:semicolon
r_int
id|i
comma
id|off
comma
id|key_off
suffix:semicolon
id|dprint
c_func
(paren
id|DBG_BNODE_MOD
comma
l_string|&quot;bnode: %d&bslash;n&quot;
comma
id|node-&gt;this
)paren
suffix:semicolon
id|hfs_bnode_read
c_func
(paren
id|node
comma
op_amp
id|desc
comma
l_int|0
comma
r_sizeof
(paren
id|desc
)paren
)paren
suffix:semicolon
id|dprint
c_func
(paren
id|DBG_BNODE_MOD
comma
l_string|&quot;%d, %d, %d, %d, %d&bslash;n&quot;
comma
id|be32_to_cpu
c_func
(paren
id|desc.next
)paren
comma
id|be32_to_cpu
c_func
(paren
id|desc.prev
)paren
comma
id|desc.type
comma
id|desc.height
comma
id|be16_to_cpu
c_func
(paren
id|desc.num_recs
)paren
)paren
suffix:semicolon
id|off
op_assign
id|node-&gt;tree-&gt;node_size
op_minus
l_int|2
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|be16_to_cpu
c_func
(paren
id|desc.num_recs
)paren
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|off
op_sub_assign
l_int|2
comma
id|i
op_decrement
)paren
(brace
id|key_off
op_assign
id|hfs_bnode_read_u16
c_func
(paren
id|node
comma
id|off
)paren
suffix:semicolon
id|dprint
c_func
(paren
id|DBG_BNODE_MOD
comma
l_string|&quot; %d&quot;
comma
id|key_off
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_logical_and
id|node-&gt;type
op_eq
id|HFS_NODE_INDEX
)paren
(brace
r_int
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|node-&gt;tree-&gt;attributes
op_amp
id|HFS_TREE_VARIDXKEYS
)paren
id|tmp
op_assign
(paren
id|hfs_bnode_read_u8
c_func
(paren
id|node
comma
id|key_off
)paren
op_or
l_int|1
)paren
op_plus
l_int|1
suffix:semicolon
r_else
id|tmp
op_assign
id|node-&gt;tree-&gt;max_key_len
op_plus
l_int|1
suffix:semicolon
id|dprint
c_func
(paren
id|DBG_BNODE_MOD
comma
l_string|&quot; (%d,%d&quot;
comma
id|tmp
comma
id|hfs_bnode_read_u8
c_func
(paren
id|node
comma
id|key_off
)paren
)paren
suffix:semicolon
id|hfs_bnode_read
c_func
(paren
id|node
comma
op_amp
id|cnid
comma
id|key_off
op_plus
id|tmp
comma
l_int|4
)paren
suffix:semicolon
id|dprint
c_func
(paren
id|DBG_BNODE_MOD
comma
l_string|&quot;,%d)&quot;
comma
id|be32_to_cpu
c_func
(paren
id|cnid
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
op_logical_and
id|node-&gt;type
op_eq
id|HFS_NODE_LEAF
)paren
(brace
r_int
id|tmp
suffix:semicolon
id|tmp
op_assign
id|hfs_bnode_read_u8
c_func
(paren
id|node
comma
id|key_off
)paren
suffix:semicolon
id|dprint
c_func
(paren
id|DBG_BNODE_MOD
comma
l_string|&quot; (%d)&quot;
comma
id|tmp
)paren
suffix:semicolon
)brace
)brace
id|dprint
c_func
(paren
id|DBG_BNODE_MOD
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|hfs_bnode_unlink
r_void
id|hfs_bnode_unlink
c_func
(paren
r_struct
id|hfs_bnode
op_star
id|node
)paren
(brace
r_struct
id|hfs_btree
op_star
id|tree
suffix:semicolon
r_struct
id|hfs_bnode
op_star
id|tmp
suffix:semicolon
id|__be32
id|cnid
suffix:semicolon
id|tree
op_assign
id|node-&gt;tree
suffix:semicolon
r_if
c_cond
(paren
id|node-&gt;prev
)paren
(brace
id|tmp
op_assign
id|hfs_bnode_find
c_func
(paren
id|tree
comma
id|node-&gt;prev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|tmp
)paren
)paren
r_return
suffix:semicolon
id|tmp-&gt;next
op_assign
id|node-&gt;next
suffix:semicolon
id|cnid
op_assign
id|cpu_to_be32
c_func
(paren
id|tmp-&gt;next
)paren
suffix:semicolon
id|hfs_bnode_write
c_func
(paren
id|tmp
comma
op_amp
id|cnid
comma
m_offsetof
(paren
r_struct
id|hfs_bnode_desc
comma
id|next
)paren
comma
l_int|4
)paren
suffix:semicolon
id|hfs_bnode_put
c_func
(paren
id|tmp
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|node-&gt;type
op_eq
id|HFS_NODE_LEAF
)paren
id|tree-&gt;leaf_head
op_assign
id|node-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|node-&gt;next
)paren
(brace
id|tmp
op_assign
id|hfs_bnode_find
c_func
(paren
id|tree
comma
id|node-&gt;next
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|tmp
)paren
)paren
r_return
suffix:semicolon
id|tmp-&gt;prev
op_assign
id|node-&gt;prev
suffix:semicolon
id|cnid
op_assign
id|cpu_to_be32
c_func
(paren
id|tmp-&gt;prev
)paren
suffix:semicolon
id|hfs_bnode_write
c_func
(paren
id|tmp
comma
op_amp
id|cnid
comma
m_offsetof
(paren
r_struct
id|hfs_bnode_desc
comma
id|prev
)paren
comma
l_int|4
)paren
suffix:semicolon
id|hfs_bnode_put
c_func
(paren
id|tmp
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|node-&gt;type
op_eq
id|HFS_NODE_LEAF
)paren
id|tree-&gt;leaf_tail
op_assign
id|node-&gt;prev
suffix:semicolon
singleline_comment|// move down?
r_if
c_cond
(paren
op_logical_neg
id|node-&gt;prev
op_logical_and
op_logical_neg
id|node-&gt;next
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;hfs_btree_del_level&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|node-&gt;parent
)paren
(brace
id|tree-&gt;root
op_assign
l_int|0
suffix:semicolon
id|tree-&gt;depth
op_assign
l_int|0
suffix:semicolon
)brace
id|set_bit
c_func
(paren
id|HFS_BNODE_DELETED
comma
op_amp
id|node-&gt;flags
)paren
suffix:semicolon
)brace
DECL|function|hfs_bnode_hash
r_static
r_inline
r_int
id|hfs_bnode_hash
c_func
(paren
id|u32
id|num
)paren
(brace
id|num
op_assign
(paren
id|num
op_rshift
l_int|16
)paren
op_plus
id|num
suffix:semicolon
id|num
op_add_assign
id|num
op_rshift
l_int|8
suffix:semicolon
r_return
id|num
op_amp
(paren
id|NODE_HASH_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|hfs_bnode_findhash
r_struct
id|hfs_bnode
op_star
id|hfs_bnode_findhash
c_func
(paren
r_struct
id|hfs_btree
op_star
id|tree
comma
id|u32
id|cnid
)paren
(brace
r_struct
id|hfs_bnode
op_star
id|node
suffix:semicolon
r_if
c_cond
(paren
id|cnid
op_ge
id|tree-&gt;node_count
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;HFS: request for non-existent node %d in B*Tree&bslash;n&quot;
comma
id|cnid
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_for
c_loop
(paren
id|node
op_assign
id|tree-&gt;node_hash
(braket
id|hfs_bnode_hash
c_func
(paren
id|cnid
)paren
)braket
suffix:semicolon
id|node
suffix:semicolon
id|node
op_assign
id|node-&gt;next_hash
)paren
(brace
r_if
c_cond
(paren
id|node-&gt;this
op_eq
id|cnid
)paren
(brace
r_return
id|node
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|__hfs_bnode_create
r_static
r_struct
id|hfs_bnode
op_star
id|__hfs_bnode_create
c_func
(paren
r_struct
id|hfs_btree
op_star
id|tree
comma
id|u32
id|cnid
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_struct
id|hfs_bnode
op_star
id|node
comma
op_star
id|node2
suffix:semicolon
r_struct
id|address_space
op_star
id|mapping
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_int
id|size
comma
id|block
comma
id|i
comma
id|hash
suffix:semicolon
id|loff_t
id|off
suffix:semicolon
r_if
c_cond
(paren
id|cnid
op_ge
id|tree-&gt;node_count
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;HFS: request for non-existent node %d in B*Tree&bslash;n&quot;
comma
id|cnid
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|sb
op_assign
id|tree-&gt;inode-&gt;i_sb
suffix:semicolon
id|size
op_assign
r_sizeof
(paren
r_struct
id|hfs_bnode
)paren
op_plus
id|tree-&gt;pages_per_bnode
op_star
r_sizeof
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
id|node
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|node
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
id|node-&gt;tree
op_assign
id|tree
suffix:semicolon
id|node-&gt;this
op_assign
id|cnid
suffix:semicolon
id|set_bit
c_func
(paren
id|HFS_BNODE_NEW
comma
op_amp
id|node-&gt;flags
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|node-&gt;refcnt
comma
l_int|1
)paren
suffix:semicolon
id|dprint
c_func
(paren
id|DBG_BNODE_REFS
comma
l_string|&quot;new_node(%d:%d): 1&bslash;n&quot;
comma
id|node-&gt;tree-&gt;cnid
comma
id|node-&gt;this
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|node-&gt;lock_wq
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|tree-&gt;hash_lock
)paren
suffix:semicolon
id|node2
op_assign
id|hfs_bnode_findhash
c_func
(paren
id|tree
comma
id|cnid
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node2
)paren
(brace
id|hash
op_assign
id|hfs_bnode_hash
c_func
(paren
id|cnid
)paren
suffix:semicolon
id|node-&gt;next_hash
op_assign
id|tree-&gt;node_hash
(braket
id|hash
)braket
suffix:semicolon
id|tree-&gt;node_hash
(braket
id|hash
)braket
op_assign
id|node
suffix:semicolon
id|tree-&gt;node_hash_cnt
op_increment
suffix:semicolon
)brace
r_else
(brace
id|spin_unlock
c_func
(paren
op_amp
id|tree-&gt;hash_lock
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|node
)paren
suffix:semicolon
id|wait_event
c_func
(paren
id|node2-&gt;lock_wq
comma
op_logical_neg
id|test_bit
c_func
(paren
id|HFS_BNODE_NEW
comma
op_amp
id|node2-&gt;flags
)paren
)paren
suffix:semicolon
r_return
id|node2
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|tree-&gt;hash_lock
)paren
suffix:semicolon
id|mapping
op_assign
id|tree-&gt;inode-&gt;i_mapping
suffix:semicolon
id|off
op_assign
(paren
id|loff_t
)paren
id|cnid
op_star
id|tree-&gt;node_size
suffix:semicolon
id|block
op_assign
id|off
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
id|node-&gt;page_offset
op_assign
id|off
op_amp
op_complement
id|PAGE_CACHE_MASK
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
id|tree-&gt;pages_per_bnode
suffix:semicolon
id|i
op_increment
)paren
(brace
id|page
op_assign
id|read_cache_page
c_func
(paren
id|mapping
comma
id|block
op_increment
comma
(paren
id|filler_t
op_star
)paren
id|mapping-&gt;a_ops-&gt;readpage
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|page
)paren
)paren
r_goto
id|fail
suffix:semicolon
r_if
c_cond
(paren
id|PageError
c_func
(paren
id|page
)paren
)paren
(brace
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
macro_line|#if !REF_PAGES
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
macro_line|#endif
id|node-&gt;page
(braket
id|i
)braket
op_assign
id|page
suffix:semicolon
)brace
r_return
id|node
suffix:semicolon
id|fail
suffix:colon
id|set_bit
c_func
(paren
id|HFS_BNODE_ERROR
comma
op_amp
id|node-&gt;flags
)paren
suffix:semicolon
r_return
id|node
suffix:semicolon
)brace
DECL|function|hfs_bnode_unhash
r_void
id|hfs_bnode_unhash
c_func
(paren
r_struct
id|hfs_bnode
op_star
id|node
)paren
(brace
r_struct
id|hfs_bnode
op_star
op_star
id|p
suffix:semicolon
id|dprint
c_func
(paren
id|DBG_BNODE_REFS
comma
l_string|&quot;remove_node(%d:%d): %d&bslash;n&quot;
comma
id|node-&gt;tree-&gt;cnid
comma
id|node-&gt;this
comma
id|atomic_read
c_func
(paren
op_amp
id|node-&gt;refcnt
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|node-&gt;tree-&gt;node_hash
(braket
id|hfs_bnode_hash
c_func
(paren
id|node-&gt;this
)paren
)braket
suffix:semicolon
op_star
id|p
op_logical_and
op_star
id|p
op_ne
id|node
suffix:semicolon
id|p
op_assign
op_amp
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|next_hash
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|p
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
op_star
id|p
op_assign
id|node-&gt;next_hash
suffix:semicolon
id|node-&gt;tree-&gt;node_hash_cnt
op_decrement
suffix:semicolon
)brace
multiline_comment|/* Load a particular node out of a tree */
DECL|function|hfs_bnode_find
r_struct
id|hfs_bnode
op_star
id|hfs_bnode_find
c_func
(paren
r_struct
id|hfs_btree
op_star
id|tree
comma
id|u32
id|num
)paren
(brace
r_struct
id|hfs_bnode
op_star
id|node
suffix:semicolon
r_struct
id|hfs_bnode_desc
op_star
id|desc
suffix:semicolon
r_int
id|i
comma
id|rec_off
comma
id|off
comma
id|next_off
suffix:semicolon
r_int
id|entry_size
comma
id|key_size
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|tree-&gt;hash_lock
)paren
suffix:semicolon
id|node
op_assign
id|hfs_bnode_findhash
c_func
(paren
id|tree
comma
id|num
)paren
suffix:semicolon
r_if
c_cond
(paren
id|node
)paren
(brace
id|hfs_bnode_get
c_func
(paren
id|node
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|tree-&gt;hash_lock
)paren
suffix:semicolon
id|wait_event
c_func
(paren
id|node-&gt;lock_wq
comma
op_logical_neg
id|test_bit
c_func
(paren
id|HFS_BNODE_NEW
comma
op_amp
id|node-&gt;flags
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|HFS_BNODE_ERROR
comma
op_amp
id|node-&gt;flags
)paren
)paren
r_goto
id|node_error
suffix:semicolon
r_return
id|node
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|tree-&gt;hash_lock
)paren
suffix:semicolon
id|node
op_assign
id|__hfs_bnode_create
c_func
(paren
id|tree
comma
id|num
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|HFS_BNODE_ERROR
comma
op_amp
id|node-&gt;flags
)paren
)paren
r_goto
id|node_error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|HFS_BNODE_NEW
comma
op_amp
id|node-&gt;flags
)paren
)paren
r_return
id|node
suffix:semicolon
id|desc
op_assign
(paren
r_struct
id|hfs_bnode_desc
op_star
)paren
(paren
id|kmap
c_func
(paren
id|node-&gt;page
(braket
l_int|0
)braket
)paren
op_plus
id|node-&gt;page_offset
)paren
suffix:semicolon
id|node-&gt;prev
op_assign
id|be32_to_cpu
c_func
(paren
id|desc-&gt;prev
)paren
suffix:semicolon
id|node-&gt;next
op_assign
id|be32_to_cpu
c_func
(paren
id|desc-&gt;next
)paren
suffix:semicolon
id|node-&gt;num_recs
op_assign
id|be16_to_cpu
c_func
(paren
id|desc-&gt;num_recs
)paren
suffix:semicolon
id|node-&gt;type
op_assign
id|desc-&gt;type
suffix:semicolon
id|node-&gt;height
op_assign
id|desc-&gt;height
suffix:semicolon
id|kunmap
c_func
(paren
id|node-&gt;page
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|node-&gt;type
)paren
(brace
r_case
id|HFS_NODE_HEADER
suffix:colon
r_case
id|HFS_NODE_MAP
suffix:colon
r_if
c_cond
(paren
id|node-&gt;height
op_ne
l_int|0
)paren
r_goto
id|node_error
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HFS_NODE_LEAF
suffix:colon
r_if
c_cond
(paren
id|node-&gt;height
op_ne
l_int|1
)paren
r_goto
id|node_error
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HFS_NODE_INDEX
suffix:colon
r_if
c_cond
(paren
id|node-&gt;height
op_le
l_int|1
op_logical_or
id|node-&gt;height
OG
id|tree-&gt;depth
)paren
r_goto
id|node_error
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_goto
id|node_error
suffix:semicolon
)brace
id|rec_off
op_assign
id|tree-&gt;node_size
op_minus
l_int|2
suffix:semicolon
id|off
op_assign
id|hfs_bnode_read_u16
c_func
(paren
id|node
comma
id|rec_off
)paren
suffix:semicolon
r_if
c_cond
(paren
id|off
op_ne
r_sizeof
(paren
r_struct
id|hfs_bnode_desc
)paren
)paren
r_goto
id|node_error
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
id|node-&gt;num_recs
suffix:semicolon
id|off
op_assign
id|next_off
comma
id|i
op_increment
)paren
(brace
id|rec_off
op_sub_assign
l_int|2
suffix:semicolon
id|next_off
op_assign
id|hfs_bnode_read_u16
c_func
(paren
id|node
comma
id|rec_off
)paren
suffix:semicolon
r_if
c_cond
(paren
id|next_off
op_le
id|off
op_logical_or
id|next_off
OG
id|tree-&gt;node_size
op_logical_or
id|next_off
op_amp
l_int|1
)paren
r_goto
id|node_error
suffix:semicolon
id|entry_size
op_assign
id|next_off
op_minus
id|off
suffix:semicolon
r_if
c_cond
(paren
id|node-&gt;type
op_ne
id|HFS_NODE_INDEX
op_logical_and
id|node-&gt;type
op_ne
id|HFS_NODE_LEAF
)paren
r_continue
suffix:semicolon
id|key_size
op_assign
id|hfs_bnode_read_u8
c_func
(paren
id|node
comma
id|off
)paren
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|key_size
op_ge
id|entry_size
multiline_comment|/*|| key_size &amp; 1*/
)paren
r_goto
id|node_error
suffix:semicolon
)brace
id|clear_bit
c_func
(paren
id|HFS_BNODE_NEW
comma
op_amp
id|node-&gt;flags
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|node-&gt;lock_wq
)paren
suffix:semicolon
r_return
id|node
suffix:semicolon
id|node_error
suffix:colon
id|set_bit
c_func
(paren
id|HFS_BNODE_ERROR
comma
op_amp
id|node-&gt;flags
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|HFS_BNODE_NEW
comma
op_amp
id|node-&gt;flags
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|node-&gt;lock_wq
)paren
suffix:semicolon
id|hfs_bnode_put
c_func
(paren
id|node
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EIO
)paren
suffix:semicolon
)brace
DECL|function|hfs_bnode_free
r_void
id|hfs_bnode_free
c_func
(paren
r_struct
id|hfs_bnode
op_star
id|node
)paren
(brace
singleline_comment|//int i;
singleline_comment|//for (i = 0; i &lt; node-&gt;tree-&gt;pages_per_bnode; i++)
singleline_comment|//&t;if (node-&gt;page[i])
singleline_comment|//&t;&t;page_cache_release(node-&gt;page[i]);
id|kfree
c_func
(paren
id|node
)paren
suffix:semicolon
)brace
DECL|function|hfs_bnode_create
r_struct
id|hfs_bnode
op_star
id|hfs_bnode_create
c_func
(paren
r_struct
id|hfs_btree
op_star
id|tree
comma
id|u32
id|num
)paren
(brace
r_struct
id|hfs_bnode
op_star
id|node
suffix:semicolon
r_struct
id|page
op_star
op_star
id|pagep
suffix:semicolon
r_int
id|i
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|tree-&gt;hash_lock
)paren
suffix:semicolon
id|node
op_assign
id|hfs_bnode_findhash
c_func
(paren
id|tree
comma
id|num
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|tree-&gt;hash_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|node
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|node
op_assign
id|__hfs_bnode_create
c_func
(paren
id|tree
comma
id|num
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|HFS_BNODE_ERROR
comma
op_amp
id|node-&gt;flags
)paren
)paren
(brace
id|hfs_bnode_put
c_func
(paren
id|node
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EIO
)paren
suffix:semicolon
)brace
id|pagep
op_assign
id|node-&gt;page
suffix:semicolon
id|memset
c_func
(paren
id|kmap
c_func
(paren
op_star
id|pagep
)paren
op_plus
id|node-&gt;page_offset
comma
l_int|0
comma
id|min
c_func
(paren
(paren
r_int
)paren
id|PAGE_CACHE_SIZE
comma
(paren
r_int
)paren
id|tree-&gt;node_size
)paren
)paren
suffix:semicolon
id|set_page_dirty
c_func
(paren
op_star
id|pagep
)paren
suffix:semicolon
id|kunmap
c_func
(paren
op_star
id|pagep
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|tree-&gt;pages_per_bnode
suffix:semicolon
id|i
op_increment
)paren
(brace
id|memset
c_func
(paren
id|kmap
c_func
(paren
op_star
op_increment
id|pagep
)paren
comma
l_int|0
comma
id|PAGE_CACHE_SIZE
)paren
suffix:semicolon
id|set_page_dirty
c_func
(paren
op_star
id|pagep
)paren
suffix:semicolon
id|kunmap
c_func
(paren
op_star
id|pagep
)paren
suffix:semicolon
)brace
id|clear_bit
c_func
(paren
id|HFS_BNODE_NEW
comma
op_amp
id|node-&gt;flags
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|node-&gt;lock_wq
)paren
suffix:semicolon
r_return
id|node
suffix:semicolon
)brace
DECL|function|hfs_bnode_get
r_void
id|hfs_bnode_get
c_func
(paren
r_struct
id|hfs_bnode
op_star
id|node
)paren
(brace
r_if
c_cond
(paren
id|node
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|node-&gt;refcnt
)paren
suffix:semicolon
macro_line|#if REF_PAGES
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
id|node-&gt;tree-&gt;pages_per_bnode
suffix:semicolon
id|i
op_increment
)paren
id|get_page
c_func
(paren
id|node-&gt;page
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif
id|dprint
c_func
(paren
id|DBG_BNODE_REFS
comma
l_string|&quot;get_node(%d:%d): %d&bslash;n&quot;
comma
id|node-&gt;tree-&gt;cnid
comma
id|node-&gt;this
comma
id|atomic_read
c_func
(paren
op_amp
id|node-&gt;refcnt
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Dispose of resources used by a node */
DECL|function|hfs_bnode_put
r_void
id|hfs_bnode_put
c_func
(paren
r_struct
id|hfs_bnode
op_star
id|node
)paren
(brace
r_if
c_cond
(paren
id|node
)paren
(brace
r_struct
id|hfs_btree
op_star
id|tree
op_assign
id|node-&gt;tree
suffix:semicolon
r_int
id|i
suffix:semicolon
id|dprint
c_func
(paren
id|DBG_BNODE_REFS
comma
l_string|&quot;put_node(%d:%d): %d&bslash;n&quot;
comma
id|node-&gt;tree-&gt;cnid
comma
id|node-&gt;this
comma
id|atomic_read
c_func
(paren
op_amp
id|node-&gt;refcnt
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|node-&gt;refcnt
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|atomic_dec_and_lock
c_func
(paren
op_amp
id|node-&gt;refcnt
comma
op_amp
id|tree-&gt;hash_lock
)paren
)paren
(brace
macro_line|#if REF_PAGES
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|tree-&gt;pages_per_bnode
suffix:semicolon
id|i
op_increment
)paren
id|put_page
c_func
(paren
id|node-&gt;page
(braket
id|i
)braket
)paren
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|tree-&gt;pages_per_bnode
suffix:semicolon
id|i
op_increment
)paren
(brace
id|mark_page_accessed
c_func
(paren
id|node-&gt;page
(braket
id|i
)braket
)paren
suffix:semicolon
macro_line|#if REF_PAGES
id|put_page
c_func
(paren
id|node-&gt;page
(braket
id|i
)braket
)paren
suffix:semicolon
macro_line|#endif
)brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|HFS_BNODE_DELETED
comma
op_amp
id|node-&gt;flags
)paren
)paren
(brace
id|hfs_bnode_unhash
c_func
(paren
id|node
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|tree-&gt;hash_lock
)paren
suffix:semicolon
id|hfs_bmap_free
c_func
(paren
id|node
)paren
suffix:semicolon
id|hfs_bnode_free
c_func
(paren
id|node
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|tree-&gt;hash_lock
)paren
suffix:semicolon
)brace
)brace
eof
