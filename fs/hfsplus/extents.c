multiline_comment|/*&n; *  linux/fs/hfsplus/extents.c&n; *&n; * Copyright (C) 2001&n; * Brad Boyer (flar@allandria.com)&n; * (C) 2003 Ardis Technologies &lt;roman@ardistech.com&gt;&n; *&n; * Handling of Extents both in catalog and extents overflow trees&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &quot;hfsplus_fs.h&quot;
macro_line|#include &quot;hfsplus_raw.h&quot;
multiline_comment|/* Compare two extents keys, returns 0 on same, pos/neg for difference */
DECL|function|hfsplus_ext_cmp_key
r_int
id|hfsplus_ext_cmp_key
c_func
(paren
id|hfsplus_btree_key
op_star
id|k1
comma
id|hfsplus_btree_key
op_star
id|k2
)paren
(brace
id|__be32
id|k1id
comma
id|k2id
suffix:semicolon
id|__be32
id|k1s
comma
id|k2s
suffix:semicolon
id|k1id
op_assign
id|k1-&gt;ext.cnid
suffix:semicolon
id|k2id
op_assign
id|k2-&gt;ext.cnid
suffix:semicolon
r_if
c_cond
(paren
id|k1id
op_ne
id|k2id
)paren
r_return
id|be32_to_cpu
c_func
(paren
id|k1id
)paren
OL
id|be32_to_cpu
c_func
(paren
id|k2id
)paren
ques
c_cond
op_minus
l_int|1
suffix:colon
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|k1-&gt;ext.fork_type
op_ne
id|k2-&gt;ext.fork_type
)paren
r_return
id|k1-&gt;ext.fork_type
OL
id|k2-&gt;ext.fork_type
ques
c_cond
op_minus
l_int|1
suffix:colon
l_int|1
suffix:semicolon
id|k1s
op_assign
id|k1-&gt;ext.start_block
suffix:semicolon
id|k2s
op_assign
id|k2-&gt;ext.start_block
suffix:semicolon
r_if
c_cond
(paren
id|k1s
op_eq
id|k2s
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|be32_to_cpu
c_func
(paren
id|k1s
)paren
OL
id|be32_to_cpu
c_func
(paren
id|k2s
)paren
ques
c_cond
op_minus
l_int|1
suffix:colon
l_int|1
suffix:semicolon
)brace
DECL|function|hfsplus_ext_build_key
r_void
id|hfsplus_ext_build_key
c_func
(paren
id|hfsplus_btree_key
op_star
id|key
comma
id|u32
id|cnid
comma
id|u32
id|block
comma
id|u8
id|type
)paren
(brace
id|key-&gt;key_len
op_assign
id|cpu_to_be16
c_func
(paren
id|HFSPLUS_EXT_KEYLEN
op_minus
l_int|2
)paren
suffix:semicolon
id|key-&gt;ext.cnid
op_assign
id|cpu_to_be32
c_func
(paren
id|cnid
)paren
suffix:semicolon
id|key-&gt;ext.start_block
op_assign
id|cpu_to_be32
c_func
(paren
id|block
)paren
suffix:semicolon
id|key-&gt;ext.fork_type
op_assign
id|type
suffix:semicolon
id|key-&gt;ext.pad
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|hfsplus_ext_find_block
r_static
id|u32
id|hfsplus_ext_find_block
c_func
(paren
r_struct
id|hfsplus_extent
op_star
id|ext
comma
id|u32
id|off
)paren
(brace
r_int
id|i
suffix:semicolon
id|u32
id|count
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
l_int|8
suffix:semicolon
id|ext
op_increment
comma
id|i
op_increment
)paren
(brace
id|count
op_assign
id|be32_to_cpu
c_func
(paren
id|ext-&gt;block_count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|off
OL
id|count
)paren
r_return
id|be32_to_cpu
c_func
(paren
id|ext-&gt;start_block
)paren
op_plus
id|off
suffix:semicolon
id|off
op_sub_assign
id|count
suffix:semicolon
)brace
multiline_comment|/* panic? */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hfsplus_ext_block_count
r_static
r_int
id|hfsplus_ext_block_count
c_func
(paren
r_struct
id|hfsplus_extent
op_star
id|ext
)paren
(brace
r_int
id|i
suffix:semicolon
id|u32
id|count
op_assign
l_int|0
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
l_int|8
suffix:semicolon
id|ext
op_increment
comma
id|i
op_increment
)paren
id|count
op_add_assign
id|be32_to_cpu
c_func
(paren
id|ext-&gt;block_count
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|hfsplus_ext_lastblock
r_static
id|u32
id|hfsplus_ext_lastblock
c_func
(paren
r_struct
id|hfsplus_extent
op_star
id|ext
)paren
(brace
r_int
id|i
suffix:semicolon
id|ext
op_add_assign
l_int|7
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
l_int|7
suffix:semicolon
id|ext
op_decrement
comma
id|i
op_increment
)paren
r_if
c_cond
(paren
id|ext-&gt;block_count
)paren
r_break
suffix:semicolon
r_return
id|be32_to_cpu
c_func
(paren
id|ext-&gt;start_block
)paren
op_plus
id|be32_to_cpu
c_func
(paren
id|ext-&gt;block_count
)paren
suffix:semicolon
)brace
DECL|function|__hfsplus_ext_write_extent
r_static
r_void
id|__hfsplus_ext_write_extent
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|hfs_find_data
op_star
id|fd
)paren
(brace
r_int
id|res
suffix:semicolon
id|hfsplus_ext_build_key
c_func
(paren
id|fd-&gt;search_key
comma
id|inode-&gt;i_ino
comma
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_start
comma
id|HFSPLUS_IS_RSRC
c_func
(paren
id|inode
)paren
ques
c_cond
id|HFSPLUS_TYPE_RSRC
suffix:colon
id|HFSPLUS_TYPE_DATA
)paren
suffix:semicolon
id|res
op_assign
id|hfs_brec_find
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|flags
op_amp
id|HFSPLUS_FLG_EXT_NEW
)paren
(brace
r_if
c_cond
(paren
id|res
op_ne
op_minus
id|ENOENT
)paren
r_return
suffix:semicolon
id|hfs_brec_insert
c_func
(paren
id|fd
comma
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_extents
comma
r_sizeof
(paren
id|hfsplus_extent_rec
)paren
)paren
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|flags
op_and_assign
op_complement
(paren
id|HFSPLUS_FLG_EXT_DIRTY
op_or
id|HFSPLUS_FLG_EXT_NEW
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|res
)paren
r_return
suffix:semicolon
id|hfs_bnode_write
c_func
(paren
id|fd-&gt;bnode
comma
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_extents
comma
id|fd-&gt;entryoffset
comma
id|fd-&gt;entrylength
)paren
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|flags
op_and_assign
op_complement
id|HFSPLUS_FLG_EXT_DIRTY
suffix:semicolon
)brace
)brace
DECL|function|hfsplus_ext_write_extent
r_void
id|hfsplus_ext_write_extent
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_if
c_cond
(paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|flags
op_amp
id|HFSPLUS_FLG_EXT_DIRTY
)paren
(brace
r_struct
id|hfs_find_data
id|fd
suffix:semicolon
id|hfs_find_init
c_func
(paren
id|HFSPLUS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
dot
id|ext_tree
comma
op_amp
id|fd
)paren
suffix:semicolon
id|__hfsplus_ext_write_extent
c_func
(paren
id|inode
comma
op_amp
id|fd
)paren
suffix:semicolon
id|hfs_find_exit
c_func
(paren
op_amp
id|fd
)paren
suffix:semicolon
)brace
)brace
DECL|function|__hfsplus_ext_read_extent
r_static
r_inline
r_int
id|__hfsplus_ext_read_extent
c_func
(paren
r_struct
id|hfs_find_data
op_star
id|fd
comma
r_struct
id|hfsplus_extent
op_star
id|extent
comma
id|u32
id|cnid
comma
id|u32
id|block
comma
id|u8
id|type
)paren
(brace
r_int
id|res
suffix:semicolon
id|hfsplus_ext_build_key
c_func
(paren
id|fd-&gt;search_key
comma
id|cnid
comma
id|block
comma
id|type
)paren
suffix:semicolon
id|fd-&gt;key-&gt;ext.cnid
op_assign
l_int|0
suffix:semicolon
id|res
op_assign
id|hfs_brec_find
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
op_logical_and
id|res
op_ne
op_minus
id|ENOENT
)paren
r_return
id|res
suffix:semicolon
r_if
c_cond
(paren
id|fd-&gt;key-&gt;ext.cnid
op_ne
id|fd-&gt;search_key-&gt;ext.cnid
op_logical_or
id|fd-&gt;key-&gt;ext.fork_type
op_ne
id|fd-&gt;search_key-&gt;ext.fork_type
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
id|fd-&gt;entrylength
op_ne
r_sizeof
(paren
id|hfsplus_extent_rec
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|hfs_bnode_read
c_func
(paren
id|fd-&gt;bnode
comma
id|extent
comma
id|fd-&gt;entryoffset
comma
r_sizeof
(paren
id|hfsplus_extent_rec
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|__hfsplus_ext_cache_extent
r_static
r_inline
r_int
id|__hfsplus_ext_cache_extent
c_func
(paren
r_struct
id|hfs_find_data
op_star
id|fd
comma
r_struct
id|inode
op_star
id|inode
comma
id|u32
id|block
)paren
(brace
r_int
id|res
suffix:semicolon
r_if
c_cond
(paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|flags
op_amp
id|HFSPLUS_FLG_EXT_DIRTY
)paren
id|__hfsplus_ext_write_extent
c_func
(paren
id|inode
comma
id|fd
)paren
suffix:semicolon
id|res
op_assign
id|__hfsplus_ext_read_extent
c_func
(paren
id|fd
comma
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_extents
comma
id|inode-&gt;i_ino
comma
id|block
comma
id|HFSPLUS_IS_RSRC
c_func
(paren
id|inode
)paren
ques
c_cond
id|HFSPLUS_TYPE_RSRC
suffix:colon
id|HFSPLUS_TYPE_DATA
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
(brace
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_start
op_assign
id|be32_to_cpu
c_func
(paren
id|fd-&gt;key-&gt;ext.start_block
)paren
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_blocks
op_assign
id|hfsplus_ext_block_count
c_func
(paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_extents
)paren
suffix:semicolon
)brace
r_else
(brace
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_start
op_assign
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_blocks
op_assign
l_int|0
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|flags
op_and_assign
op_complement
(paren
id|HFSPLUS_FLG_EXT_DIRTY
op_or
id|HFSPLUS_FLG_EXT_NEW
)paren
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
DECL|function|hfsplus_ext_read_extent
r_static
r_int
id|hfsplus_ext_read_extent
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|u32
id|block
)paren
(brace
r_struct
id|hfs_find_data
id|fd
suffix:semicolon
r_int
id|res
suffix:semicolon
r_if
c_cond
(paren
id|block
op_ge
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_start
op_logical_and
id|block
OL
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_start
op_plus
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_blocks
)paren
r_return
l_int|0
suffix:semicolon
id|hfs_find_init
c_func
(paren
id|HFSPLUS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
dot
id|ext_tree
comma
op_amp
id|fd
)paren
suffix:semicolon
id|res
op_assign
id|__hfsplus_ext_cache_extent
c_func
(paren
op_amp
id|fd
comma
id|inode
comma
id|block
)paren
suffix:semicolon
id|hfs_find_exit
c_func
(paren
op_amp
id|fd
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/* Get a block at iblock for inode, possibly allocating if create */
DECL|function|hfsplus_get_block
r_int
id|hfsplus_get_block
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|sector_t
id|iblock
comma
r_struct
id|buffer_head
op_star
id|bh_result
comma
r_int
id|create
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_int
id|res
op_assign
op_minus
id|EIO
suffix:semicolon
id|u32
id|ablock
comma
id|dblock
comma
id|mask
suffix:semicolon
r_int
id|shift
suffix:semicolon
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
multiline_comment|/* Convert inode block to disk allocation block */
id|shift
op_assign
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|alloc_blksz_shift
op_minus
id|sb-&gt;s_blocksize_bits
suffix:semicolon
id|ablock
op_assign
id|iblock
op_rshift
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|fs_shift
suffix:semicolon
r_if
c_cond
(paren
id|iblock
op_ge
id|inode-&gt;i_blocks
)paren
(brace
r_if
c_cond
(paren
id|iblock
OG
id|inode-&gt;i_blocks
op_logical_or
op_logical_neg
id|create
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|ablock
op_ge
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|alloc_blocks
)paren
(brace
id|res
op_assign
id|hfsplus_file_extend
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
id|res
suffix:semicolon
)brace
)brace
r_else
id|create
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ablock
OL
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|first_blocks
)paren
(brace
id|dblock
op_assign
id|hfsplus_ext_find_block
c_func
(paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|first_extents
comma
id|ablock
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|extents_lock
)paren
suffix:semicolon
id|res
op_assign
id|hfsplus_ext_read_extent
c_func
(paren
id|inode
comma
id|ablock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
(brace
id|dblock
op_assign
id|hfsplus_ext_find_block
c_func
(paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_extents
comma
id|ablock
op_minus
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_start
)paren
suffix:semicolon
)brace
r_else
(brace
id|up
c_func
(paren
op_amp
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|extents_lock
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|extents_lock
)paren
suffix:semicolon
id|done
suffix:colon
id|dprint
c_func
(paren
id|DBG_EXTENT
comma
l_string|&quot;get_block(%lu): %llu - %u&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
(paren
r_int
r_int
)paren
id|iblock
comma
id|dblock
)paren
suffix:semicolon
id|mask
op_assign
(paren
l_int|1
op_lshift
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|fs_shift
)paren
op_minus
l_int|1
suffix:semicolon
id|map_bh
c_func
(paren
id|bh_result
comma
id|sb
comma
(paren
id|dblock
op_lshift
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|fs_shift
)paren
op_plus
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|blockoffset
op_plus
(paren
id|iblock
op_amp
id|mask
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|create
)paren
(brace
id|set_buffer_new
c_func
(paren
id|bh_result
)paren
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|phys_size
op_add_assign
id|sb-&gt;s_blocksize
suffix:semicolon
id|inode-&gt;i_blocks
op_increment
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hfsplus_dump_extent
r_static
r_void
id|hfsplus_dump_extent
c_func
(paren
r_struct
id|hfsplus_extent
op_star
id|extent
)paren
(brace
r_int
id|i
suffix:semicolon
id|dprint
c_func
(paren
id|DBG_EXTENT
comma
l_string|&quot;   &quot;
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|dprint
c_func
(paren
id|DBG_EXTENT
comma
l_string|&quot; %u:%u&quot;
comma
id|be32_to_cpu
c_func
(paren
id|extent
(braket
id|i
)braket
dot
id|start_block
)paren
comma
id|be32_to_cpu
c_func
(paren
id|extent
(braket
id|i
)braket
dot
id|block_count
)paren
)paren
suffix:semicolon
id|dprint
c_func
(paren
id|DBG_EXTENT
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|hfsplus_add_extent
r_static
r_int
id|hfsplus_add_extent
c_func
(paren
r_struct
id|hfsplus_extent
op_star
id|extent
comma
id|u32
id|offset
comma
id|u32
id|alloc_block
comma
id|u32
id|block_count
)paren
(brace
id|u32
id|count
comma
id|start
suffix:semicolon
r_int
id|i
suffix:semicolon
id|hfsplus_dump_extent
c_func
(paren
id|extent
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
l_int|8
suffix:semicolon
id|extent
op_increment
comma
id|i
op_increment
)paren
(brace
id|count
op_assign
id|be32_to_cpu
c_func
(paren
id|extent-&gt;block_count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_eq
id|count
)paren
(brace
id|start
op_assign
id|be32_to_cpu
c_func
(paren
id|extent-&gt;start_block
)paren
suffix:semicolon
r_if
c_cond
(paren
id|alloc_block
op_ne
id|start
op_plus
id|count
)paren
(brace
r_if
c_cond
(paren
op_increment
id|i
op_ge
l_int|8
)paren
r_return
op_minus
id|ENOSPC
suffix:semicolon
id|extent
op_increment
suffix:semicolon
id|extent-&gt;start_block
op_assign
id|cpu_to_be32
c_func
(paren
id|alloc_block
)paren
suffix:semicolon
)brace
r_else
id|block_count
op_add_assign
id|count
suffix:semicolon
id|extent-&gt;block_count
op_assign
id|cpu_to_be32
c_func
(paren
id|block_count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|offset
OL
id|count
)paren
r_break
suffix:semicolon
id|offset
op_sub_assign
id|count
suffix:semicolon
)brace
multiline_comment|/* panic? */
r_return
op_minus
id|EIO
suffix:semicolon
)brace
DECL|function|hfsplus_free_extents
r_int
id|hfsplus_free_extents
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|hfsplus_extent
op_star
id|extent
comma
id|u32
id|offset
comma
id|u32
id|block_nr
)paren
(brace
id|u32
id|count
comma
id|start
suffix:semicolon
r_int
id|i
suffix:semicolon
id|hfsplus_dump_extent
c_func
(paren
id|extent
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
l_int|8
suffix:semicolon
id|extent
op_increment
comma
id|i
op_increment
)paren
(brace
id|count
op_assign
id|be32_to_cpu
c_func
(paren
id|extent-&gt;block_count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_eq
id|count
)paren
r_goto
id|found
suffix:semicolon
r_else
r_if
c_cond
(paren
id|offset
OL
id|count
)paren
r_break
suffix:semicolon
id|offset
op_sub_assign
id|count
suffix:semicolon
)brace
multiline_comment|/* panic? */
r_return
op_minus
id|EIO
suffix:semicolon
id|found
suffix:colon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|start
op_assign
id|be32_to_cpu
c_func
(paren
id|extent-&gt;start_block
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_le
id|block_nr
)paren
(brace
id|hfsplus_block_free
c_func
(paren
id|sb
comma
id|start
comma
id|count
)paren
suffix:semicolon
id|extent-&gt;block_count
op_assign
l_int|0
suffix:semicolon
id|extent-&gt;start_block
op_assign
l_int|0
suffix:semicolon
id|block_nr
op_sub_assign
id|count
suffix:semicolon
)brace
r_else
(brace
id|count
op_sub_assign
id|block_nr
suffix:semicolon
id|hfsplus_block_free
c_func
(paren
id|sb
comma
id|start
op_plus
id|count
comma
id|block_nr
)paren
suffix:semicolon
id|extent-&gt;block_count
op_assign
id|cpu_to_be32
c_func
(paren
id|count
)paren
suffix:semicolon
id|block_nr
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|block_nr
op_logical_or
op_logical_neg
id|i
)paren
r_return
l_int|0
suffix:semicolon
id|i
op_decrement
suffix:semicolon
id|extent
op_decrement
suffix:semicolon
id|count
op_assign
id|be32_to_cpu
c_func
(paren
id|extent-&gt;block_count
)paren
suffix:semicolon
)brace
)brace
DECL|function|hfsplus_free_fork
r_int
id|hfsplus_free_fork
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|u32
id|cnid
comma
r_struct
id|hfsplus_fork_raw
op_star
id|fork
comma
r_int
id|type
)paren
(brace
r_struct
id|hfs_find_data
id|fd
suffix:semicolon
id|hfsplus_extent_rec
id|ext_entry
suffix:semicolon
id|u32
id|total_blocks
comma
id|blocks
comma
id|start
suffix:semicolon
r_int
id|res
comma
id|i
suffix:semicolon
id|total_blocks
op_assign
id|be32_to_cpu
c_func
(paren
id|fork-&gt;total_blocks
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|total_blocks
)paren
r_return
l_int|0
suffix:semicolon
id|blocks
op_assign
l_int|0
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|blocks
op_add_assign
id|be32_to_cpu
c_func
(paren
id|fork-&gt;extents
(braket
id|i
)braket
dot
id|block_count
)paren
suffix:semicolon
id|res
op_assign
id|hfsplus_free_extents
c_func
(paren
id|sb
comma
id|fork-&gt;extents
comma
id|blocks
comma
id|blocks
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_return
id|res
suffix:semicolon
r_if
c_cond
(paren
id|total_blocks
op_eq
id|blocks
)paren
r_return
l_int|0
suffix:semicolon
id|hfs_find_init
c_func
(paren
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|ext_tree
comma
op_amp
id|fd
)paren
suffix:semicolon
r_do
(brace
id|res
op_assign
id|__hfsplus_ext_read_extent
c_func
(paren
op_amp
id|fd
comma
id|ext_entry
comma
id|cnid
comma
id|total_blocks
comma
id|type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_break
suffix:semicolon
id|start
op_assign
id|be32_to_cpu
c_func
(paren
id|fd.key-&gt;ext.start_block
)paren
suffix:semicolon
id|hfsplus_free_extents
c_func
(paren
id|sb
comma
id|ext_entry
comma
id|total_blocks
op_minus
id|start
comma
id|total_blocks
)paren
suffix:semicolon
id|hfs_brec_remove
c_func
(paren
op_amp
id|fd
)paren
suffix:semicolon
id|total_blocks
op_assign
id|start
suffix:semicolon
)brace
r_while
c_loop
(paren
id|total_blocks
OG
id|blocks
)paren
suffix:semicolon
id|hfs_find_exit
c_func
(paren
op_amp
id|fd
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|hfsplus_file_extend
r_int
id|hfsplus_file_extend
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
id|u32
id|start
comma
id|len
comma
id|goal
suffix:semicolon
r_int
id|res
suffix:semicolon
r_if
c_cond
(paren
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|alloc_file-&gt;i_size
op_star
l_int|8
OL
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|total_blocks
op_minus
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|free_blocks
op_plus
l_int|8
)paren
(brace
singleline_comment|// extend alloc file
id|printk
c_func
(paren
l_string|&quot;extend alloc file! (%Lu,%u,%u)&bslash;n&quot;
comma
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|alloc_file-&gt;i_size
op_star
l_int|8
comma
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|total_blocks
comma
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|free_blocks
)paren
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
singleline_comment|//BUG();
)brace
id|down
c_func
(paren
op_amp
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|extents_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|alloc_blocks
op_eq
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|first_blocks
)paren
id|goal
op_assign
id|hfsplus_ext_lastblock
c_func
(paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|first_extents
)paren
suffix:semicolon
r_else
(brace
id|res
op_assign
id|hfsplus_ext_read_extent
c_func
(paren
id|inode
comma
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|alloc_blocks
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_goto
id|out
suffix:semicolon
id|goal
op_assign
id|hfsplus_ext_lastblock
c_func
(paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_extents
)paren
suffix:semicolon
)brace
id|len
op_assign
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|clump_blocks
suffix:semicolon
id|start
op_assign
id|hfsplus_block_allocate
c_func
(paren
id|sb
comma
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|total_blocks
comma
id|goal
comma
op_amp
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|start
op_ge
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|total_blocks
)paren
(brace
id|start
op_assign
id|hfsplus_block_allocate
c_func
(paren
id|sb
comma
id|goal
comma
l_int|0
comma
op_amp
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|start
op_ge
id|goal
)paren
(brace
id|res
op_assign
op_minus
id|ENOSPC
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
id|dprint
c_func
(paren
id|DBG_EXTENT
comma
l_string|&quot;extend %lu: %u,%u&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|start
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|alloc_blocks
op_le
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|first_blocks
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|first_blocks
)paren
(brace
id|dprint
c_func
(paren
id|DBG_EXTENT
comma
l_string|&quot;first extents&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* no extents yet */
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|first_extents
(braket
l_int|0
)braket
dot
id|start_block
op_assign
id|cpu_to_be32
c_func
(paren
id|start
)paren
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|first_extents
(braket
l_int|0
)braket
dot
id|block_count
op_assign
id|cpu_to_be32
c_func
(paren
id|len
)paren
suffix:semicolon
id|res
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* try to append to extents in inode */
id|res
op_assign
id|hfsplus_add_extent
c_func
(paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|first_extents
comma
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|alloc_blocks
comma
id|start
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
op_eq
op_minus
id|ENOSPC
)paren
r_goto
id|insert_extent
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
(brace
id|hfsplus_dump_extent
c_func
(paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|first_extents
)paren
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|first_blocks
op_add_assign
id|len
suffix:semicolon
)brace
)brace
r_else
(brace
id|res
op_assign
id|hfsplus_add_extent
c_func
(paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_extents
comma
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|alloc_blocks
op_minus
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_start
comma
id|start
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
(brace
id|hfsplus_dump_extent
c_func
(paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_extents
)paren
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|flags
op_or_assign
id|HFSPLUS_FLG_EXT_DIRTY
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_blocks
op_add_assign
id|len
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|res
op_eq
op_minus
id|ENOSPC
)paren
r_goto
id|insert_extent
suffix:semicolon
)brace
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|extents_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
(brace
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|alloc_blocks
op_add_assign
id|len
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
id|insert_extent
suffix:colon
id|dprint
c_func
(paren
id|DBG_EXTENT
comma
l_string|&quot;insert new extent&bslash;n&quot;
)paren
suffix:semicolon
id|hfsplus_ext_write_extent
c_func
(paren
id|inode
)paren
suffix:semicolon
id|memset
c_func
(paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_extents
comma
l_int|0
comma
r_sizeof
(paren
id|hfsplus_extent_rec
)paren
)paren
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_extents
(braket
l_int|0
)braket
dot
id|start_block
op_assign
id|cpu_to_be32
c_func
(paren
id|start
)paren
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_extents
(braket
l_int|0
)braket
dot
id|block_count
op_assign
id|cpu_to_be32
c_func
(paren
id|len
)paren
suffix:semicolon
id|hfsplus_dump_extent
c_func
(paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_extents
)paren
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|flags
op_or_assign
id|HFSPLUS_FLG_EXT_DIRTY
op_or
id|HFSPLUS_FLG_EXT_NEW
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_start
op_assign
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|alloc_blocks
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_blocks
op_assign
id|len
suffix:semicolon
id|res
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|function|hfsplus_file_truncate
r_void
id|hfsplus_file_truncate
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_struct
id|hfs_find_data
id|fd
suffix:semicolon
id|u32
id|alloc_cnt
comma
id|blk_cnt
comma
id|start
suffix:semicolon
r_int
id|res
suffix:semicolon
id|dprint
c_func
(paren
id|DBG_INODE
comma
l_string|&quot;truncate: %lu, %Lu -&gt; %Lu&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
(paren
r_int
r_int
)paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|phys_size
comma
id|inode-&gt;i_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_size
OG
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|phys_size
)paren
(brace
r_struct
id|address_space
op_star
id|mapping
op_assign
id|inode-&gt;i_mapping
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
id|u32
id|size
op_assign
id|inode-&gt;i_size
op_minus
l_int|1
suffix:semicolon
r_int
id|res
suffix:semicolon
id|page
op_assign
id|grab_cache_page
c_func
(paren
id|mapping
comma
id|size
op_rshift
id|PAGE_CACHE_SHIFT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
suffix:semicolon
id|size
op_and_assign
id|PAGE_CACHE_SIZE
op_minus
l_int|1
suffix:semicolon
id|size
op_increment
suffix:semicolon
id|res
op_assign
id|mapping-&gt;a_ops
op_member_access_from_pointer
id|prepare_write
c_func
(paren
l_int|NULL
comma
id|page
comma
id|size
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
id|res
op_assign
id|mapping-&gt;a_ops
op_member_access_from_pointer
id|commit_write
c_func
(paren
l_int|NULL
comma
id|page
comma
id|size
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
id|inode-&gt;i_size
op_assign
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|phys_size
suffix:semicolon
id|unlock_page
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
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|blk_cnt
op_assign
(paren
id|inode-&gt;i_size
op_plus
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|alloc_blksz
op_minus
l_int|1
)paren
op_rshift
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|alloc_blksz_shift
suffix:semicolon
id|alloc_cnt
op_assign
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|alloc_blocks
suffix:semicolon
r_if
c_cond
(paren
id|blk_cnt
op_eq
id|alloc_cnt
)paren
r_goto
id|out
suffix:semicolon
id|down
c_func
(paren
op_amp
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|extents_lock
)paren
suffix:semicolon
id|hfs_find_init
c_func
(paren
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|ext_tree
comma
op_amp
id|fd
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|alloc_cnt
op_eq
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|first_blocks
)paren
(brace
id|hfsplus_free_extents
c_func
(paren
id|sb
comma
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|first_extents
comma
id|alloc_cnt
comma
id|alloc_cnt
op_minus
id|blk_cnt
)paren
suffix:semicolon
id|hfsplus_dump_extent
c_func
(paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|first_extents
)paren
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|first_blocks
op_assign
id|blk_cnt
suffix:semicolon
r_break
suffix:semicolon
)brace
id|res
op_assign
id|__hfsplus_ext_cache_extent
c_func
(paren
op_amp
id|fd
comma
id|inode
comma
id|alloc_cnt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_break
suffix:semicolon
id|start
op_assign
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_start
suffix:semicolon
id|hfsplus_free_extents
c_func
(paren
id|sb
comma
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_extents
comma
id|alloc_cnt
op_minus
id|start
comma
id|alloc_cnt
op_minus
id|blk_cnt
)paren
suffix:semicolon
id|hfsplus_dump_extent
c_func
(paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_extents
)paren
suffix:semicolon
r_if
c_cond
(paren
id|blk_cnt
OG
id|start
)paren
(brace
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|flags
op_or_assign
id|HFSPLUS_FLG_EXT_DIRTY
suffix:semicolon
r_break
suffix:semicolon
)brace
id|alloc_cnt
op_assign
id|start
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_start
op_assign
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_blocks
op_assign
l_int|0
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|flags
op_and_assign
op_complement
(paren
id|HFSPLUS_FLG_EXT_DIRTY
op_or
id|HFSPLUS_FLG_EXT_NEW
)paren
suffix:semicolon
id|hfs_brec_remove
c_func
(paren
op_amp
id|fd
)paren
suffix:semicolon
)brace
id|hfs_find_exit
c_func
(paren
op_amp
id|fd
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|extents_lock
)paren
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|alloc_blocks
op_assign
id|blk_cnt
suffix:semicolon
id|out
suffix:colon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|phys_size
op_assign
id|inode-&gt;i_size
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
(paren
id|inode-&gt;i_size
op_plus
id|sb-&gt;s_blocksize
op_minus
l_int|1
)paren
op_rshift
id|sb-&gt;s_blocksize_bits
suffix:semicolon
)brace
eof
