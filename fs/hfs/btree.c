multiline_comment|/*&n; *  linux/fs/hfs/btree.c&n; *&n; * Copyright (C) 2001&n; * Brad Boyer (flar@allandria.com)&n; * (C) 2003 Ardis Technologies &lt;roman@ardistech.com&gt;&n; *&n; * Handle opening/closing btree&n; */
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &quot;btree.h&quot;
multiline_comment|/* Get a reference to a B*Tree and do some initial checks */
DECL|function|hfs_btree_open
r_struct
id|hfs_btree
op_star
id|hfs_btree_open
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|u32
id|id
comma
id|btree_keycmp
id|keycmp
)paren
(brace
r_struct
id|hfs_btree
op_star
id|tree
suffix:semicolon
r_struct
id|hfs_btree_header_rec
op_star
id|head
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
r_int
id|size
suffix:semicolon
id|tree
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|tree
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|tree
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|tree
)paren
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|tree-&gt;tree_lock
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|tree-&gt;hash_lock
)paren
suffix:semicolon
multiline_comment|/* Set the correct compare function */
id|tree-&gt;sb
op_assign
id|sb
suffix:semicolon
id|tree-&gt;cnid
op_assign
id|id
suffix:semicolon
id|tree-&gt;keycmp
op_assign
id|keycmp
suffix:semicolon
id|tree-&gt;inode
op_assign
id|iget_locked
c_func
(paren
id|sb
comma
id|id
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree-&gt;inode
)paren
r_goto
id|free_tree
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|tree-&gt;inode-&gt;i_state
op_amp
id|I_NEW
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
(brace
r_struct
id|hfs_mdb
op_star
id|mdb
op_assign
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|mdb
suffix:semicolon
id|HFS_I
c_func
(paren
id|tree-&gt;inode
)paren
op_member_access_from_pointer
id|flags
op_assign
l_int|0
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|HFS_I
c_func
(paren
id|tree-&gt;inode
)paren
op_member_access_from_pointer
id|extents_lock
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|id
)paren
(brace
r_case
id|HFS_EXT_CNID
suffix:colon
id|hfs_inode_read_fork
c_func
(paren
id|tree-&gt;inode
comma
id|mdb-&gt;drXTExtRec
comma
id|mdb-&gt;drXTFlSize
comma
id|mdb-&gt;drXTFlSize
comma
id|be32_to_cpu
c_func
(paren
id|mdb-&gt;drXTClpSiz
)paren
)paren
suffix:semicolon
id|tree-&gt;inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|hfs_btree_aops
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HFS_CAT_CNID
suffix:colon
id|hfs_inode_read_fork
c_func
(paren
id|tree-&gt;inode
comma
id|mdb-&gt;drCTExtRec
comma
id|mdb-&gt;drCTFlSize
comma
id|mdb-&gt;drCTFlSize
comma
id|be32_to_cpu
c_func
(paren
id|mdb-&gt;drCTClpSiz
)paren
)paren
suffix:semicolon
id|tree-&gt;inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|hfs_btree_aops
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
id|unlock_new_inode
c_func
(paren
id|tree-&gt;inode
)paren
suffix:semicolon
id|mapping
op_assign
id|tree-&gt;inode-&gt;i_mapping
suffix:semicolon
id|page
op_assign
id|read_cache_page
c_func
(paren
id|mapping
comma
l_int|0
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
id|free_tree
suffix:semicolon
multiline_comment|/* Load the header */
id|head
op_assign
(paren
r_struct
id|hfs_btree_header_rec
op_star
)paren
(paren
id|kmap
c_func
(paren
id|page
)paren
op_plus
r_sizeof
(paren
r_struct
id|hfs_bnode_desc
)paren
)paren
suffix:semicolon
id|tree-&gt;root
op_assign
id|be32_to_cpu
c_func
(paren
id|head-&gt;root
)paren
suffix:semicolon
id|tree-&gt;leaf_count
op_assign
id|be32_to_cpu
c_func
(paren
id|head-&gt;leaf_count
)paren
suffix:semicolon
id|tree-&gt;leaf_head
op_assign
id|be32_to_cpu
c_func
(paren
id|head-&gt;leaf_head
)paren
suffix:semicolon
id|tree-&gt;leaf_tail
op_assign
id|be32_to_cpu
c_func
(paren
id|head-&gt;leaf_tail
)paren
suffix:semicolon
id|tree-&gt;node_count
op_assign
id|be32_to_cpu
c_func
(paren
id|head-&gt;node_count
)paren
suffix:semicolon
id|tree-&gt;free_nodes
op_assign
id|be32_to_cpu
c_func
(paren
id|head-&gt;free_nodes
)paren
suffix:semicolon
id|tree-&gt;attributes
op_assign
id|be32_to_cpu
c_func
(paren
id|head-&gt;attributes
)paren
suffix:semicolon
id|tree-&gt;node_size
op_assign
id|be16_to_cpu
c_func
(paren
id|head-&gt;node_size
)paren
suffix:semicolon
id|tree-&gt;max_key_len
op_assign
id|be16_to_cpu
c_func
(paren
id|head-&gt;max_key_len
)paren
suffix:semicolon
id|tree-&gt;depth
op_assign
id|be16_to_cpu
c_func
(paren
id|head-&gt;depth
)paren
suffix:semicolon
id|size
op_assign
id|tree-&gt;node_size
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
op_logical_or
id|size
op_amp
(paren
id|size
op_minus
l_int|1
)paren
)paren
r_goto
id|fail_page
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree-&gt;node_count
)paren
r_goto
id|fail_page
suffix:semicolon
id|tree-&gt;node_size_shift
op_assign
id|ffs
c_func
(paren
id|size
)paren
op_minus
l_int|1
suffix:semicolon
id|tree-&gt;pages_per_bnode
op_assign
(paren
id|tree-&gt;node_size
op_plus
id|PAGE_CACHE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|tree
suffix:semicolon
id|fail_page
suffix:colon
id|tree-&gt;inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|hfs_aops
suffix:semicolon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
id|free_tree
suffix:colon
id|iput
c_func
(paren
id|tree-&gt;inode
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tree
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Release resources used by a btree */
DECL|function|hfs_btree_close
r_void
id|hfs_btree_close
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
id|node
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree
)paren
r_return
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
id|NODE_HASH_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_while
c_loop
(paren
(paren
id|node
op_assign
id|tree-&gt;node_hash
(braket
id|i
)braket
)paren
)paren
(brace
id|tree-&gt;node_hash
(braket
id|i
)braket
op_assign
id|node-&gt;next_hash
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|node-&gt;refcnt
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;HFS: node %d:%d still has %d user(s)!&bslash;n&quot;
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
id|hfs_bnode_free
c_func
(paren
id|node
)paren
suffix:semicolon
id|tree-&gt;node_hash_cnt
op_decrement
suffix:semicolon
)brace
)brace
id|iput
c_func
(paren
id|tree-&gt;inode
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tree
)paren
suffix:semicolon
)brace
DECL|function|hfs_btree_write
r_void
id|hfs_btree_write
c_func
(paren
r_struct
id|hfs_btree
op_star
id|tree
)paren
(brace
r_struct
id|hfs_btree_header_rec
op_star
id|head
suffix:semicolon
r_struct
id|hfs_bnode
op_star
id|node
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
id|node
op_assign
id|hfs_bnode_find
c_func
(paren
id|tree
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|node
)paren
)paren
multiline_comment|/* panic? */
r_return
suffix:semicolon
multiline_comment|/* Load the header */
id|page
op_assign
id|node-&gt;page
(braket
l_int|0
)braket
suffix:semicolon
id|head
op_assign
(paren
r_struct
id|hfs_btree_header_rec
op_star
)paren
(paren
id|kmap
c_func
(paren
id|page
)paren
op_plus
r_sizeof
(paren
r_struct
id|hfs_bnode_desc
)paren
)paren
suffix:semicolon
id|head-&gt;root
op_assign
id|cpu_to_be32
c_func
(paren
id|tree-&gt;root
)paren
suffix:semicolon
id|head-&gt;leaf_count
op_assign
id|cpu_to_be32
c_func
(paren
id|tree-&gt;leaf_count
)paren
suffix:semicolon
id|head-&gt;leaf_head
op_assign
id|cpu_to_be32
c_func
(paren
id|tree-&gt;leaf_head
)paren
suffix:semicolon
id|head-&gt;leaf_tail
op_assign
id|cpu_to_be32
c_func
(paren
id|tree-&gt;leaf_tail
)paren
suffix:semicolon
id|head-&gt;node_count
op_assign
id|cpu_to_be32
c_func
(paren
id|tree-&gt;node_count
)paren
suffix:semicolon
id|head-&gt;free_nodes
op_assign
id|cpu_to_be32
c_func
(paren
id|tree-&gt;free_nodes
)paren
suffix:semicolon
id|head-&gt;attributes
op_assign
id|cpu_to_be32
c_func
(paren
id|tree-&gt;attributes
)paren
suffix:semicolon
id|head-&gt;depth
op_assign
id|cpu_to_be16
c_func
(paren
id|tree-&gt;depth
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
id|hfs_bnode_put
c_func
(paren
id|node
)paren
suffix:semicolon
)brace
DECL|function|hfs_bmap_new_bmap
r_static
r_struct
id|hfs_bnode
op_star
id|hfs_bmap_new_bmap
c_func
(paren
r_struct
id|hfs_bnode
op_star
id|prev
comma
id|u32
id|idx
)paren
(brace
r_struct
id|hfs_btree
op_star
id|tree
op_assign
id|prev-&gt;tree
suffix:semicolon
r_struct
id|hfs_bnode
op_star
id|node
suffix:semicolon
r_struct
id|hfs_bnode_desc
id|desc
suffix:semicolon
id|__be32
id|cnid
suffix:semicolon
id|node
op_assign
id|hfs_bnode_create
c_func
(paren
id|tree
comma
id|idx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|node
)paren
)paren
r_return
id|node
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree-&gt;free_nodes
)paren
id|panic
c_func
(paren
l_string|&quot;FIXME!!!&quot;
)paren
suffix:semicolon
id|tree-&gt;free_nodes
op_decrement
suffix:semicolon
id|prev-&gt;next
op_assign
id|idx
suffix:semicolon
id|cnid
op_assign
id|cpu_to_be32
c_func
(paren
id|idx
)paren
suffix:semicolon
id|hfs_bnode_write
c_func
(paren
id|prev
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
id|node-&gt;type
op_assign
id|HFS_NODE_MAP
suffix:semicolon
id|node-&gt;num_recs
op_assign
l_int|1
suffix:semicolon
id|hfs_bnode_clear
c_func
(paren
id|node
comma
l_int|0
comma
id|tree-&gt;node_size
)paren
suffix:semicolon
id|desc.next
op_assign
l_int|0
suffix:semicolon
id|desc.prev
op_assign
l_int|0
suffix:semicolon
id|desc.type
op_assign
id|HFS_NODE_MAP
suffix:semicolon
id|desc.height
op_assign
l_int|0
suffix:semicolon
id|desc.num_recs
op_assign
id|cpu_to_be16
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|desc.reserved
op_assign
l_int|0
suffix:semicolon
id|hfs_bnode_write
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
id|hfs_bnode_write_u16
c_func
(paren
id|node
comma
l_int|14
comma
l_int|0x8000
)paren
suffix:semicolon
id|hfs_bnode_write_u16
c_func
(paren
id|node
comma
id|tree-&gt;node_size
op_minus
l_int|2
comma
l_int|14
)paren
suffix:semicolon
id|hfs_bnode_write_u16
c_func
(paren
id|node
comma
id|tree-&gt;node_size
op_minus
l_int|4
comma
id|tree-&gt;node_size
op_minus
l_int|6
)paren
suffix:semicolon
r_return
id|node
suffix:semicolon
)brace
DECL|function|hfs_bmap_alloc
r_struct
id|hfs_bnode
op_star
id|hfs_bmap_alloc
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
id|node
comma
op_star
id|next_node
suffix:semicolon
r_struct
id|page
op_star
op_star
id|pagep
suffix:semicolon
id|u32
id|nidx
comma
id|idx
suffix:semicolon
id|u16
id|off
comma
id|len
suffix:semicolon
id|u8
op_star
id|data
comma
id|byte
comma
id|m
suffix:semicolon
r_int
id|i
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|tree-&gt;free_nodes
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|tree-&gt;inode
suffix:semicolon
id|u32
id|count
suffix:semicolon
r_int
id|res
suffix:semicolon
id|res
op_assign
id|hfs_extend_file
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_return
id|ERR_PTR
c_func
(paren
id|res
)paren
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|phys_size
op_assign
id|inode-&gt;i_size
op_assign
(paren
id|loff_t
)paren
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|alloc_blocks
op_star
id|HFS_SB
c_func
(paren
id|tree-&gt;sb
)paren
op_member_access_from_pointer
id|alloc_blksz
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|fs_blocks
op_assign
id|inode-&gt;i_size
op_rshift
id|tree-&gt;sb-&gt;s_blocksize_bits
suffix:semicolon
id|inode_set_bytes
c_func
(paren
id|inode
comma
id|inode-&gt;i_size
)paren
suffix:semicolon
id|count
op_assign
id|inode-&gt;i_size
op_rshift
id|tree-&gt;node_size_shift
suffix:semicolon
id|tree-&gt;free_nodes
op_assign
id|count
op_minus
id|tree-&gt;node_count
suffix:semicolon
id|tree-&gt;node_count
op_assign
id|count
suffix:semicolon
)brace
id|nidx
op_assign
l_int|0
suffix:semicolon
id|node
op_assign
id|hfs_bnode_find
c_func
(paren
id|tree
comma
id|nidx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|node
)paren
)paren
r_return
id|node
suffix:semicolon
id|len
op_assign
id|hfs_brec_lenoff
c_func
(paren
id|node
comma
l_int|2
comma
op_amp
id|off
)paren
suffix:semicolon
id|off
op_add_assign
id|node-&gt;page_offset
suffix:semicolon
id|pagep
op_assign
id|node-&gt;page
op_plus
(paren
id|off
op_rshift
id|PAGE_CACHE_SHIFT
)paren
suffix:semicolon
id|data
op_assign
id|kmap
c_func
(paren
op_star
id|pagep
)paren
suffix:semicolon
id|off
op_and_assign
op_complement
id|PAGE_CACHE_MASK
suffix:semicolon
id|idx
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
r_while
c_loop
(paren
id|len
)paren
(brace
id|byte
op_assign
id|data
(braket
id|off
)braket
suffix:semicolon
r_if
c_cond
(paren
id|byte
op_ne
l_int|0xff
)paren
(brace
r_for
c_loop
(paren
id|m
op_assign
l_int|0x80
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|m
op_rshift_assign
l_int|1
comma
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|byte
op_amp
id|m
)paren
)paren
(brace
id|idx
op_add_assign
id|i
suffix:semicolon
id|data
(braket
id|off
)braket
op_or_assign
id|m
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
id|tree-&gt;free_nodes
op_decrement
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|tree-&gt;inode
)paren
suffix:semicolon
id|hfs_bnode_put
c_func
(paren
id|node
)paren
suffix:semicolon
r_return
id|hfs_bnode_create
c_func
(paren
id|tree
comma
id|idx
)paren
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
op_increment
id|off
op_ge
id|PAGE_CACHE_SIZE
)paren
(brace
id|kunmap
c_func
(paren
op_star
id|pagep
)paren
suffix:semicolon
id|data
op_assign
id|kmap
c_func
(paren
op_star
op_increment
id|pagep
)paren
suffix:semicolon
id|off
op_assign
l_int|0
suffix:semicolon
)brace
id|idx
op_add_assign
l_int|8
suffix:semicolon
id|len
op_decrement
suffix:semicolon
)brace
id|kunmap
c_func
(paren
op_star
id|pagep
)paren
suffix:semicolon
id|nidx
op_assign
id|node-&gt;next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nidx
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;create new bmap node...&bslash;n&quot;
)paren
suffix:semicolon
id|next_node
op_assign
id|hfs_bmap_new_bmap
c_func
(paren
id|node
comma
id|idx
)paren
suffix:semicolon
)brace
r_else
id|next_node
op_assign
id|hfs_bnode_find
c_func
(paren
id|tree
comma
id|nidx
)paren
suffix:semicolon
id|hfs_bnode_put
c_func
(paren
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|next_node
)paren
)paren
r_return
id|next_node
suffix:semicolon
id|node
op_assign
id|next_node
suffix:semicolon
id|len
op_assign
id|hfs_brec_lenoff
c_func
(paren
id|node
comma
l_int|0
comma
op_amp
id|off
)paren
suffix:semicolon
id|off
op_add_assign
id|node-&gt;page_offset
suffix:semicolon
id|pagep
op_assign
id|node-&gt;page
op_plus
(paren
id|off
op_rshift
id|PAGE_CACHE_SHIFT
)paren
suffix:semicolon
id|data
op_assign
id|kmap
c_func
(paren
op_star
id|pagep
)paren
suffix:semicolon
id|off
op_and_assign
op_complement
id|PAGE_CACHE_MASK
suffix:semicolon
)brace
)brace
DECL|function|hfs_bmap_free
r_void
id|hfs_bmap_free
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
id|page
op_star
id|page
suffix:semicolon
id|u16
id|off
comma
id|len
suffix:semicolon
id|u32
id|nidx
suffix:semicolon
id|u8
op_star
id|data
comma
id|byte
comma
id|m
suffix:semicolon
id|dprint
c_func
(paren
id|DBG_BNODE_MOD
comma
l_string|&quot;btree_free_node: %u&bslash;n&quot;
comma
id|node-&gt;this
)paren
suffix:semicolon
id|tree
op_assign
id|node-&gt;tree
suffix:semicolon
id|nidx
op_assign
id|node-&gt;this
suffix:semicolon
id|node
op_assign
id|hfs_bnode_find
c_func
(paren
id|tree
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|node
)paren
)paren
r_return
suffix:semicolon
id|len
op_assign
id|hfs_brec_lenoff
c_func
(paren
id|node
comma
l_int|2
comma
op_amp
id|off
)paren
suffix:semicolon
r_while
c_loop
(paren
id|nidx
op_ge
id|len
op_star
l_int|8
)paren
(brace
id|u32
id|i
suffix:semicolon
id|nidx
op_sub_assign
id|len
op_star
l_int|8
suffix:semicolon
id|i
op_assign
id|node-&gt;next
suffix:semicolon
id|hfs_bnode_put
c_func
(paren
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i
)paren
(brace
multiline_comment|/* panic */
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;HFS: unable to free bnode %u. bmap not found!&bslash;n&quot;
comma
id|node-&gt;this
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|node
op_assign
id|hfs_bnode_find
c_func
(paren
id|tree
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|node
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|node-&gt;type
op_ne
id|HFS_NODE_MAP
)paren
(brace
multiline_comment|/* panic */
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;HFS: invalid bmap found! (%u,%d)&bslash;n&quot;
comma
id|node-&gt;this
comma
id|node-&gt;type
)paren
suffix:semicolon
id|hfs_bnode_put
c_func
(paren
id|node
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|len
op_assign
id|hfs_brec_lenoff
c_func
(paren
id|node
comma
l_int|0
comma
op_amp
id|off
)paren
suffix:semicolon
)brace
id|off
op_add_assign
id|node-&gt;page_offset
op_plus
id|nidx
op_div
l_int|8
suffix:semicolon
id|page
op_assign
id|node-&gt;page
(braket
id|off
op_rshift
id|PAGE_CACHE_SHIFT
)braket
suffix:semicolon
id|data
op_assign
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|off
op_and_assign
op_complement
id|PAGE_CACHE_MASK
suffix:semicolon
id|m
op_assign
l_int|1
op_lshift
(paren
op_complement
id|nidx
op_amp
l_int|7
)paren
suffix:semicolon
id|byte
op_assign
id|data
(braket
id|off
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|byte
op_amp
id|m
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;HFS: trying to free free bnode %u(%d)&bslash;n&quot;
comma
id|node-&gt;this
comma
id|node-&gt;type
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|hfs_bnode_put
c_func
(paren
id|node
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|data
(braket
id|off
)braket
op_assign
id|byte
op_amp
op_complement
id|m
suffix:semicolon
id|set_page_dirty
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|hfs_bnode_put
c_func
(paren
id|node
)paren
suffix:semicolon
id|tree-&gt;free_nodes
op_increment
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|tree-&gt;inode
)paren
suffix:semicolon
)brace
eof
