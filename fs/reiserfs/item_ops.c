multiline_comment|/*&n; * Copyright 2000 by Hans Reiser, licensing governed by reiserfs/README&n; */
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/reiserfs_fs.h&gt;
singleline_comment|// this contains item handlers for old item types: sd, direct,
singleline_comment|// indirect, directory
multiline_comment|/* and where are the comments? how about saying where we can find an&n;   explanation of each item handler method? -Hans */
singleline_comment|//////////////////////////////////////////////////////////////////////////////
singleline_comment|// stat data functions
singleline_comment|//
DECL|function|sd_bytes_number
r_static
r_int
id|sd_bytes_number
(paren
r_struct
id|item_head
op_star
id|ih
comma
r_int
id|block_size
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sd_decrement_key
r_static
r_void
id|sd_decrement_key
(paren
r_struct
id|cpu_key
op_star
id|key
)paren
(brace
id|key-&gt;on_disk_key.k_objectid
op_decrement
suffix:semicolon
id|set_cpu_key_k_type
(paren
id|key
comma
id|TYPE_ANY
)paren
suffix:semicolon
id|set_cpu_key_k_offset
c_func
(paren
id|key
comma
(paren
id|loff_t
)paren
(paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
DECL|function|sd_is_left_mergeable
r_static
r_int
id|sd_is_left_mergeable
(paren
r_struct
id|reiserfs_key
op_star
id|key
comma
r_int
r_int
id|bsize
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|print_time
r_static
r_char
op_star
id|print_time
(paren
id|time_t
id|t
)paren
(brace
r_static
r_char
id|timebuf
(braket
l_int|256
)braket
suffix:semicolon
id|sprintf
(paren
id|timebuf
comma
l_string|&quot;%ld&quot;
comma
id|t
)paren
suffix:semicolon
r_return
id|timebuf
suffix:semicolon
)brace
DECL|function|sd_print_item
r_static
r_void
id|sd_print_item
(paren
r_struct
id|item_head
op_star
id|ih
comma
r_char
op_star
id|item
)paren
(brace
id|printk
(paren
l_string|&quot;&bslash;tmode | size | nlinks | first direct | mtime&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat_data_v1
(paren
id|ih
)paren
)paren
(brace
r_struct
id|stat_data_v1
op_star
id|sd
op_assign
(paren
r_struct
id|stat_data_v1
op_star
)paren
id|item
suffix:semicolon
id|printk
(paren
l_string|&quot;&bslash;t0%-6o | %6u | %2u | %d | %s&bslash;n&quot;
comma
id|sd_v1_mode
c_func
(paren
id|sd
)paren
comma
id|sd_v1_size
c_func
(paren
id|sd
)paren
comma
id|sd_v1_nlink
c_func
(paren
id|sd
)paren
comma
id|sd_v1_first_direct_byte
c_func
(paren
id|sd
)paren
comma
id|print_time
c_func
(paren
id|sd_v1_mtime
c_func
(paren
id|sd
)paren
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|stat_data
op_star
id|sd
op_assign
(paren
r_struct
id|stat_data
op_star
)paren
id|item
suffix:semicolon
id|printk
(paren
l_string|&quot;&bslash;t0%-6o | %6Lu | %2u | %d | %s&bslash;n&quot;
comma
id|sd_v2_mode
c_func
(paren
id|sd
)paren
comma
(paren
r_int
r_int
r_int
)paren
id|sd_v2_size
c_func
(paren
id|sd
)paren
comma
id|sd_v2_nlink
c_func
(paren
id|sd
)paren
comma
id|sd_v2_rdev
c_func
(paren
id|sd
)paren
comma
id|print_time
c_func
(paren
id|sd_v2_mtime
c_func
(paren
id|sd
)paren
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|sd_check_item
r_static
r_void
id|sd_check_item
(paren
r_struct
id|item_head
op_star
id|ih
comma
r_char
op_star
id|item
)paren
(brace
singleline_comment|// FIXME: type something here!
)brace
DECL|function|sd_create_vi
r_static
r_int
id|sd_create_vi
(paren
r_struct
id|virtual_node
op_star
id|vn
comma
r_struct
id|virtual_item
op_star
id|vi
comma
r_int
id|is_affected
comma
r_int
id|insert_size
)paren
(brace
id|vi-&gt;vi_index
op_assign
id|TYPE_STAT_DATA
suffix:semicolon
singleline_comment|//vi-&gt;vi_type |= VI_TYPE_STAT_DATA;// not needed?
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sd_check_left
r_static
r_int
id|sd_check_left
(paren
r_struct
id|virtual_item
op_star
id|vi
comma
r_int
id|free
comma
r_int
id|start_skip
comma
r_int
id|end_skip
)paren
(brace
r_if
c_cond
(paren
id|start_skip
op_logical_or
id|end_skip
)paren
id|BUG
(paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|sd_check_right
r_static
r_int
id|sd_check_right
(paren
r_struct
id|virtual_item
op_star
id|vi
comma
r_int
id|free
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|sd_part_size
r_static
r_int
id|sd_part_size
(paren
r_struct
id|virtual_item
op_star
id|vi
comma
r_int
id|first
comma
r_int
id|count
)paren
(brace
r_if
c_cond
(paren
id|count
)paren
id|BUG
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sd_unit_num
r_static
r_int
id|sd_unit_num
(paren
r_struct
id|virtual_item
op_star
id|vi
)paren
(brace
r_return
id|vi-&gt;vi_item_len
op_minus
id|IH_SIZE
suffix:semicolon
)brace
DECL|function|sd_print_vi
r_static
r_void
id|sd_print_vi
(paren
r_struct
id|virtual_item
op_star
id|vi
)paren
(brace
id|reiserfs_warning
(paren
l_int|NULL
comma
l_string|&quot;STATDATA, index %d, type 0x%x, %h&quot;
comma
id|vi-&gt;vi_index
comma
id|vi-&gt;vi_type
comma
id|vi-&gt;vi_ih
)paren
suffix:semicolon
)brace
DECL|variable|stat_data_ops
r_static
r_struct
id|item_operations
id|stat_data_ops
op_assign
(brace
dot
id|bytes_number
op_assign
id|sd_bytes_number
comma
dot
id|decrement_key
op_assign
id|sd_decrement_key
comma
dot
id|is_left_mergeable
op_assign
id|sd_is_left_mergeable
comma
dot
id|print_item
op_assign
id|sd_print_item
comma
dot
id|check_item
op_assign
id|sd_check_item
comma
dot
id|create_vi
op_assign
id|sd_create_vi
comma
dot
id|check_left
op_assign
id|sd_check_left
comma
dot
id|check_right
op_assign
id|sd_check_right
comma
dot
id|part_size
op_assign
id|sd_part_size
comma
dot
id|unit_num
op_assign
id|sd_unit_num
comma
dot
id|print_vi
op_assign
id|sd_print_vi
)brace
suffix:semicolon
singleline_comment|//////////////////////////////////////////////////////////////////////////////
singleline_comment|// direct item functions
singleline_comment|//
DECL|function|direct_bytes_number
r_static
r_int
id|direct_bytes_number
(paren
r_struct
id|item_head
op_star
id|ih
comma
r_int
id|block_size
)paren
(brace
r_return
id|ih_item_len
c_func
(paren
id|ih
)paren
suffix:semicolon
)brace
singleline_comment|// FIXME: this should probably switch to indirect as well
DECL|function|direct_decrement_key
r_static
r_void
id|direct_decrement_key
(paren
r_struct
id|cpu_key
op_star
id|key
)paren
(brace
id|cpu_key_k_offset_dec
(paren
id|key
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_key_k_offset
(paren
id|key
)paren
op_eq
l_int|0
)paren
id|set_cpu_key_k_type
(paren
id|key
comma
id|TYPE_STAT_DATA
)paren
suffix:semicolon
)brace
DECL|function|direct_is_left_mergeable
r_static
r_int
id|direct_is_left_mergeable
(paren
r_struct
id|reiserfs_key
op_star
id|key
comma
r_int
r_int
id|bsize
)paren
(brace
r_int
id|version
op_assign
id|le_key_version
(paren
id|key
)paren
suffix:semicolon
r_return
(paren
(paren
id|le_key_k_offset
(paren
id|version
comma
id|key
)paren
op_amp
(paren
id|bsize
op_minus
l_int|1
)paren
)paren
op_ne
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|direct_print_item
r_static
r_void
id|direct_print_item
(paren
r_struct
id|item_head
op_star
id|ih
comma
r_char
op_star
id|item
)paren
(brace
r_int
id|j
op_assign
l_int|0
suffix:semicolon
singleline_comment|//    return;
id|printk
(paren
l_string|&quot;&bslash;&quot;&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|j
OL
id|ih_item_len
c_func
(paren
id|ih
)paren
)paren
id|printk
(paren
l_string|&quot;%c&quot;
comma
id|item
(braket
id|j
op_increment
)braket
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;&bslash;&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|direct_check_item
r_static
r_void
id|direct_check_item
(paren
r_struct
id|item_head
op_star
id|ih
comma
r_char
op_star
id|item
)paren
(brace
singleline_comment|// FIXME: type something here!
)brace
DECL|function|direct_create_vi
r_static
r_int
id|direct_create_vi
(paren
r_struct
id|virtual_node
op_star
id|vn
comma
r_struct
id|virtual_item
op_star
id|vi
comma
r_int
id|is_affected
comma
r_int
id|insert_size
)paren
(brace
id|vi-&gt;vi_index
op_assign
id|TYPE_DIRECT
suffix:semicolon
singleline_comment|//vi-&gt;vi_type |= VI_TYPE_DIRECT;
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|direct_check_left
r_static
r_int
id|direct_check_left
(paren
r_struct
id|virtual_item
op_star
id|vi
comma
r_int
id|free
comma
r_int
id|start_skip
comma
r_int
id|end_skip
)paren
(brace
r_int
id|bytes
suffix:semicolon
id|bytes
op_assign
id|free
op_minus
id|free
op_mod
l_int|8
suffix:semicolon
r_return
id|bytes
ques
c_cond
suffix:colon
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|direct_check_right
r_static
r_int
id|direct_check_right
(paren
r_struct
id|virtual_item
op_star
id|vi
comma
r_int
id|free
)paren
(brace
r_return
id|direct_check_left
(paren
id|vi
comma
id|free
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|direct_part_size
r_static
r_int
id|direct_part_size
(paren
r_struct
id|virtual_item
op_star
id|vi
comma
r_int
id|first
comma
r_int
id|count
)paren
(brace
r_return
id|count
suffix:semicolon
)brace
DECL|function|direct_unit_num
r_static
r_int
id|direct_unit_num
(paren
r_struct
id|virtual_item
op_star
id|vi
)paren
(brace
r_return
id|vi-&gt;vi_item_len
op_minus
id|IH_SIZE
suffix:semicolon
)brace
DECL|function|direct_print_vi
r_static
r_void
id|direct_print_vi
(paren
r_struct
id|virtual_item
op_star
id|vi
)paren
(brace
id|reiserfs_warning
(paren
l_int|NULL
comma
l_string|&quot;DIRECT, index %d, type 0x%x, %h&quot;
comma
id|vi-&gt;vi_index
comma
id|vi-&gt;vi_type
comma
id|vi-&gt;vi_ih
)paren
suffix:semicolon
)brace
DECL|variable|direct_ops
r_static
r_struct
id|item_operations
id|direct_ops
op_assign
(brace
dot
id|bytes_number
op_assign
id|direct_bytes_number
comma
dot
id|decrement_key
op_assign
id|direct_decrement_key
comma
dot
id|is_left_mergeable
op_assign
id|direct_is_left_mergeable
comma
dot
id|print_item
op_assign
id|direct_print_item
comma
dot
id|check_item
op_assign
id|direct_check_item
comma
dot
id|create_vi
op_assign
id|direct_create_vi
comma
dot
id|check_left
op_assign
id|direct_check_left
comma
dot
id|check_right
op_assign
id|direct_check_right
comma
dot
id|part_size
op_assign
id|direct_part_size
comma
dot
id|unit_num
op_assign
id|direct_unit_num
comma
dot
id|print_vi
op_assign
id|direct_print_vi
)brace
suffix:semicolon
singleline_comment|//////////////////////////////////////////////////////////////////////////////
singleline_comment|// indirect item functions
singleline_comment|//
DECL|function|indirect_bytes_number
r_static
r_int
id|indirect_bytes_number
(paren
r_struct
id|item_head
op_star
id|ih
comma
r_int
id|block_size
)paren
(brace
r_return
id|ih_item_len
c_func
(paren
id|ih
)paren
op_div
id|UNFM_P_SIZE
op_star
id|block_size
suffix:semicolon
singleline_comment|//- get_ih_free_space (ih);
)brace
singleline_comment|// decrease offset, if it becomes 0, change type to stat data
DECL|function|indirect_decrement_key
r_static
r_void
id|indirect_decrement_key
(paren
r_struct
id|cpu_key
op_star
id|key
)paren
(brace
id|cpu_key_k_offset_dec
(paren
id|key
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_key_k_offset
(paren
id|key
)paren
op_eq
l_int|0
)paren
id|set_cpu_key_k_type
(paren
id|key
comma
id|TYPE_STAT_DATA
)paren
suffix:semicolon
)brace
singleline_comment|// if it is not first item of the body, then it is mergeable
DECL|function|indirect_is_left_mergeable
r_static
r_int
id|indirect_is_left_mergeable
(paren
r_struct
id|reiserfs_key
op_star
id|key
comma
r_int
r_int
id|bsize
)paren
(brace
r_int
id|version
op_assign
id|le_key_version
(paren
id|key
)paren
suffix:semicolon
r_return
(paren
id|le_key_k_offset
(paren
id|version
comma
id|key
)paren
op_ne
l_int|1
)paren
suffix:semicolon
)brace
singleline_comment|// printing of indirect item
DECL|function|start_new_sequence
r_static
r_void
id|start_new_sequence
(paren
id|__u32
op_star
id|start
comma
r_int
op_star
id|len
comma
id|__u32
r_new
)paren
(brace
op_star
id|start
op_assign
r_new
suffix:semicolon
op_star
id|len
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|sequence_finished
r_static
r_int
id|sequence_finished
(paren
id|__u32
id|start
comma
r_int
op_star
id|len
comma
id|__u32
r_new
)paren
(brace
r_if
c_cond
(paren
id|start
op_eq
id|INT_MAX
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|start
op_eq
l_int|0
op_logical_and
r_new
op_eq
l_int|0
)paren
(brace
(paren
op_star
id|len
)paren
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|start
op_ne
l_int|0
op_logical_and
(paren
id|start
op_plus
op_star
id|len
)paren
op_eq
r_new
)paren
(brace
(paren
op_star
id|len
)paren
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|print_sequence
r_static
r_void
id|print_sequence
(paren
id|__u32
id|start
comma
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
id|start
op_eq
id|INT_MAX
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|1
)paren
id|printk
(paren
l_string|&quot; %d&quot;
comma
id|start
)paren
suffix:semicolon
r_else
id|printk
(paren
l_string|&quot; %d(%d)&quot;
comma
id|start
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|indirect_print_item
r_static
r_void
id|indirect_print_item
(paren
r_struct
id|item_head
op_star
id|ih
comma
r_char
op_star
id|item
)paren
(brace
r_int
id|j
suffix:semicolon
id|__u32
op_star
id|unp
comma
id|prev
op_assign
id|INT_MAX
suffix:semicolon
r_int
id|num
suffix:semicolon
id|unp
op_assign
(paren
id|__u32
op_star
)paren
id|item
suffix:semicolon
r_if
c_cond
(paren
id|ih_item_len
c_func
(paren
id|ih
)paren
op_mod
id|UNFM_P_SIZE
)paren
id|reiserfs_warning
(paren
l_int|NULL
comma
l_string|&quot;indirect_print_item: invalid item len&quot;
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;%d pointers&bslash;n[ &quot;
comma
(paren
r_int
)paren
id|I_UNFM_NUM
(paren
id|ih
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|I_UNFM_NUM
(paren
id|ih
)paren
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sequence_finished
(paren
id|prev
comma
op_amp
id|num
comma
id|get_block_num
c_func
(paren
id|unp
comma
id|j
)paren
)paren
)paren
(brace
id|print_sequence
(paren
id|prev
comma
id|num
)paren
suffix:semicolon
id|start_new_sequence
(paren
op_amp
id|prev
comma
op_amp
id|num
comma
id|get_block_num
c_func
(paren
id|unp
comma
id|j
)paren
)paren
suffix:semicolon
)brace
)brace
id|print_sequence
(paren
id|prev
comma
id|num
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;]&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|indirect_check_item
r_static
r_void
id|indirect_check_item
(paren
r_struct
id|item_head
op_star
id|ih
comma
r_char
op_star
id|item
)paren
(brace
singleline_comment|// FIXME: type something here!
)brace
DECL|function|indirect_create_vi
r_static
r_int
id|indirect_create_vi
(paren
r_struct
id|virtual_node
op_star
id|vn
comma
r_struct
id|virtual_item
op_star
id|vi
comma
r_int
id|is_affected
comma
r_int
id|insert_size
)paren
(brace
id|vi-&gt;vi_index
op_assign
id|TYPE_INDIRECT
suffix:semicolon
singleline_comment|//vi-&gt;vi_type |= VI_TYPE_INDIRECT;
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|indirect_check_left
r_static
r_int
id|indirect_check_left
(paren
r_struct
id|virtual_item
op_star
id|vi
comma
r_int
id|free
comma
r_int
id|start_skip
comma
r_int
id|end_skip
)paren
(brace
r_int
id|bytes
suffix:semicolon
id|bytes
op_assign
id|free
op_minus
id|free
op_mod
id|UNFM_P_SIZE
suffix:semicolon
r_return
id|bytes
ques
c_cond
suffix:colon
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|indirect_check_right
r_static
r_int
id|indirect_check_right
(paren
r_struct
id|virtual_item
op_star
id|vi
comma
r_int
id|free
)paren
(brace
r_return
id|indirect_check_left
(paren
id|vi
comma
id|free
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
singleline_comment|// return size in bytes of &squot;units&squot; units. If first == 0 - calculate from the head (left), otherwise - from tail (right)
DECL|function|indirect_part_size
r_static
r_int
id|indirect_part_size
(paren
r_struct
id|virtual_item
op_star
id|vi
comma
r_int
id|first
comma
r_int
id|units
)paren
(brace
singleline_comment|// unit of indirect item is byte (yet)
r_return
id|units
suffix:semicolon
)brace
DECL|function|indirect_unit_num
r_static
r_int
id|indirect_unit_num
(paren
r_struct
id|virtual_item
op_star
id|vi
)paren
(brace
singleline_comment|// unit of indirect item is byte (yet)
r_return
id|vi-&gt;vi_item_len
op_minus
id|IH_SIZE
suffix:semicolon
)brace
DECL|function|indirect_print_vi
r_static
r_void
id|indirect_print_vi
(paren
r_struct
id|virtual_item
op_star
id|vi
)paren
(brace
id|reiserfs_warning
(paren
l_int|NULL
comma
l_string|&quot;INDIRECT, index %d, type 0x%x, %h&quot;
comma
id|vi-&gt;vi_index
comma
id|vi-&gt;vi_type
comma
id|vi-&gt;vi_ih
)paren
suffix:semicolon
)brace
DECL|variable|indirect_ops
r_static
r_struct
id|item_operations
id|indirect_ops
op_assign
(brace
dot
id|bytes_number
op_assign
id|indirect_bytes_number
comma
dot
id|decrement_key
op_assign
id|indirect_decrement_key
comma
dot
id|is_left_mergeable
op_assign
id|indirect_is_left_mergeable
comma
dot
id|print_item
op_assign
id|indirect_print_item
comma
dot
id|check_item
op_assign
id|indirect_check_item
comma
dot
id|create_vi
op_assign
id|indirect_create_vi
comma
dot
id|check_left
op_assign
id|indirect_check_left
comma
dot
id|check_right
op_assign
id|indirect_check_right
comma
dot
id|part_size
op_assign
id|indirect_part_size
comma
dot
id|unit_num
op_assign
id|indirect_unit_num
comma
dot
id|print_vi
op_assign
id|indirect_print_vi
)brace
suffix:semicolon
singleline_comment|//////////////////////////////////////////////////////////////////////////////
singleline_comment|// direntry functions
singleline_comment|//
DECL|function|direntry_bytes_number
r_static
r_int
id|direntry_bytes_number
(paren
r_struct
id|item_head
op_star
id|ih
comma
r_int
id|block_size
)paren
(brace
id|reiserfs_warning
(paren
l_int|NULL
comma
l_string|&quot;vs-16090: direntry_bytes_number: &quot;
l_string|&quot;bytes number is asked for direntry&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|direntry_decrement_key
r_static
r_void
id|direntry_decrement_key
(paren
r_struct
id|cpu_key
op_star
id|key
)paren
(brace
id|cpu_key_k_offset_dec
(paren
id|key
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_key_k_offset
(paren
id|key
)paren
op_eq
l_int|0
)paren
id|set_cpu_key_k_type
(paren
id|key
comma
id|TYPE_STAT_DATA
)paren
suffix:semicolon
)brace
DECL|function|direntry_is_left_mergeable
r_static
r_int
id|direntry_is_left_mergeable
(paren
r_struct
id|reiserfs_key
op_star
id|key
comma
r_int
r_int
id|bsize
)paren
(brace
r_if
c_cond
(paren
id|le32_to_cpu
(paren
id|key-&gt;u.k_offset_v1.k_offset
)paren
op_eq
id|DOT_OFFSET
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|direntry_print_item
r_static
r_void
id|direntry_print_item
(paren
r_struct
id|item_head
op_star
id|ih
comma
r_char
op_star
id|item
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|namelen
suffix:semicolon
r_struct
id|reiserfs_de_head
op_star
id|deh
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_static
r_char
id|namebuf
(braket
l_int|80
)braket
suffix:semicolon
id|printk
(paren
l_string|&quot;&bslash;n # %-15s%-30s%-15s%-15s%-15s&bslash;n&quot;
comma
l_string|&quot;Name&quot;
comma
l_string|&quot;Key of pointed object&quot;
comma
l_string|&quot;Hash&quot;
comma
l_string|&quot;Gen number&quot;
comma
l_string|&quot;Status&quot;
)paren
suffix:semicolon
id|deh
op_assign
(paren
r_struct
id|reiserfs_de_head
op_star
)paren
id|item
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
id|I_ENTRY_COUNT
(paren
id|ih
)paren
suffix:semicolon
id|i
op_increment
comma
id|deh
op_increment
)paren
(brace
id|namelen
op_assign
(paren
id|i
ques
c_cond
(paren
id|deh_location
c_func
(paren
id|deh
op_minus
l_int|1
)paren
)paren
suffix:colon
id|ih_item_len
c_func
(paren
id|ih
)paren
)paren
op_minus
id|deh_location
c_func
(paren
id|deh
)paren
suffix:semicolon
id|name
op_assign
id|item
op_plus
id|deh_location
c_func
(paren
id|deh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|name
(braket
id|namelen
op_minus
l_int|1
)braket
op_eq
l_int|0
)paren
id|namelen
op_assign
id|strlen
(paren
id|name
)paren
suffix:semicolon
id|namebuf
(braket
l_int|0
)braket
op_assign
l_char|&squot;&quot;&squot;
suffix:semicolon
r_if
c_cond
(paren
id|namelen
OG
r_sizeof
(paren
id|namebuf
)paren
op_minus
l_int|3
)paren
(brace
id|strncpy
(paren
id|namebuf
op_plus
l_int|1
comma
id|name
comma
r_sizeof
(paren
id|namebuf
)paren
op_minus
l_int|3
)paren
suffix:semicolon
id|namebuf
(braket
r_sizeof
(paren
id|namebuf
)paren
op_minus
l_int|2
)braket
op_assign
l_char|&squot;&quot;&squot;
suffix:semicolon
id|namebuf
(braket
r_sizeof
(paren
id|namebuf
)paren
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|memcpy
(paren
id|namebuf
op_plus
l_int|1
comma
id|name
comma
id|namelen
)paren
suffix:semicolon
id|namebuf
(braket
id|namelen
op_plus
l_int|1
)braket
op_assign
l_char|&squot;&quot;&squot;
suffix:semicolon
id|namebuf
(braket
id|namelen
op_plus
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;%d:  %-15s%-15d%-15d%-15Ld%-15Ld(%s)&bslash;n&quot;
comma
id|i
comma
id|namebuf
comma
id|deh_dir_id
c_func
(paren
id|deh
)paren
comma
id|deh_objectid
c_func
(paren
id|deh
)paren
comma
id|GET_HASH_VALUE
(paren
id|deh_offset
(paren
id|deh
)paren
)paren
comma
id|GET_GENERATION_NUMBER
(paren
(paren
id|deh_offset
(paren
id|deh
)paren
)paren
)paren
comma
(paren
id|de_hidden
(paren
id|deh
)paren
)paren
ques
c_cond
l_string|&quot;HIDDEN&quot;
suffix:colon
l_string|&quot;VISIBLE&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|direntry_check_item
r_static
r_void
id|direntry_check_item
(paren
r_struct
id|item_head
op_star
id|ih
comma
r_char
op_star
id|item
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|reiserfs_de_head
op_star
id|deh
suffix:semicolon
singleline_comment|// FIXME: type something here!
id|deh
op_assign
(paren
r_struct
id|reiserfs_de_head
op_star
)paren
id|item
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
id|I_ENTRY_COUNT
(paren
id|ih
)paren
suffix:semicolon
id|i
op_increment
comma
id|deh
op_increment
)paren
(brace
suffix:semicolon
)brace
)brace
DECL|macro|DIRENTRY_VI_FIRST_DIRENTRY_ITEM
mdefine_line|#define DIRENTRY_VI_FIRST_DIRENTRY_ITEM 1
multiline_comment|/*&n; * function returns old entry number in directory item in real node&n; * using new entry number in virtual item in virtual node */
DECL|function|old_entry_num
r_static
r_inline
r_int
id|old_entry_num
(paren
r_int
id|is_affected
comma
r_int
id|virtual_entry_num
comma
r_int
id|pos_in_item
comma
r_int
id|mode
)paren
(brace
r_if
c_cond
(paren
id|mode
op_eq
id|M_INSERT
op_logical_or
id|mode
op_eq
id|M_DELETE
)paren
r_return
id|virtual_entry_num
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_affected
)paren
multiline_comment|/* cut or paste is applied to another item */
r_return
id|virtual_entry_num
suffix:semicolon
r_if
c_cond
(paren
id|virtual_entry_num
OL
id|pos_in_item
)paren
r_return
id|virtual_entry_num
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_eq
id|M_CUT
)paren
r_return
id|virtual_entry_num
op_plus
l_int|1
suffix:semicolon
id|RFALSE
c_func
(paren
id|mode
op_ne
id|M_PASTE
op_logical_or
id|virtual_entry_num
op_eq
l_int|0
comma
l_string|&quot;vs-8015: old_entry_num: mode must be M_PASTE (mode = &bslash;&squot;%c&bslash;&squot;&quot;
comma
id|mode
)paren
suffix:semicolon
r_return
id|virtual_entry_num
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Create an array of sizes of directory entries for virtual&n;   item. Return space used by an item. FIXME: no control over&n;   consuming of space used by this item handler */
DECL|function|direntry_create_vi
r_static
r_int
id|direntry_create_vi
(paren
r_struct
id|virtual_node
op_star
id|vn
comma
r_struct
id|virtual_item
op_star
id|vi
comma
r_int
id|is_affected
comma
r_int
id|insert_size
)paren
(brace
r_struct
id|direntry_uarea
op_star
id|dir_u
op_assign
id|vi-&gt;vi_uarea
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_int
id|size
op_assign
r_sizeof
(paren
r_struct
id|direntry_uarea
)paren
suffix:semicolon
r_struct
id|reiserfs_de_head
op_star
id|deh
suffix:semicolon
id|vi-&gt;vi_index
op_assign
id|TYPE_DIRENTRY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|vi-&gt;vi_ih
)paren
op_logical_or
op_logical_neg
id|vi-&gt;vi_item
)paren
id|BUG
(paren
)paren
suffix:semicolon
id|dir_u-&gt;flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|le_ih_k_offset
(paren
id|vi-&gt;vi_ih
)paren
op_eq
id|DOT_OFFSET
)paren
id|dir_u-&gt;flags
op_or_assign
id|DIRENTRY_VI_FIRST_DIRENTRY_ITEM
suffix:semicolon
id|deh
op_assign
(paren
r_struct
id|reiserfs_de_head
op_star
)paren
(paren
id|vi-&gt;vi_item
)paren
suffix:semicolon
multiline_comment|/* virtual directory item have this amount of entry after */
id|dir_u-&gt;entry_count
op_assign
id|ih_entry_count
(paren
id|vi-&gt;vi_ih
)paren
op_plus
(paren
(paren
id|is_affected
)paren
ques
c_cond
(paren
(paren
id|vn-&gt;vn_mode
op_eq
id|M_CUT
)paren
ques
c_cond
op_minus
l_int|1
suffix:colon
(paren
id|vn-&gt;vn_mode
op_eq
id|M_PASTE
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
)paren
suffix:colon
l_int|0
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
id|dir_u-&gt;entry_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|j
op_assign
id|old_entry_num
(paren
id|is_affected
comma
id|i
comma
id|vn-&gt;vn_pos_in_item
comma
id|vn-&gt;vn_mode
)paren
suffix:semicolon
id|dir_u-&gt;entry_sizes
(braket
id|i
)braket
op_assign
(paren
id|j
ques
c_cond
id|deh_location
c_func
(paren
op_amp
(paren
id|deh
(braket
id|j
op_minus
l_int|1
)braket
)paren
)paren
suffix:colon
id|ih_item_len
(paren
id|vi-&gt;vi_ih
)paren
)paren
op_minus
id|deh_location
c_func
(paren
op_amp
(paren
id|deh
(braket
id|j
)braket
)paren
)paren
op_plus
id|DEH_SIZE
suffix:semicolon
)brace
id|size
op_add_assign
(paren
id|dir_u-&gt;entry_count
op_star
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
multiline_comment|/* set size of pasted entry */
r_if
c_cond
(paren
id|is_affected
op_logical_and
id|vn-&gt;vn_mode
op_eq
id|M_PASTE
)paren
id|dir_u-&gt;entry_sizes
(braket
id|vn-&gt;vn_pos_in_item
)braket
op_assign
id|insert_size
suffix:semicolon
macro_line|#ifdef CONFIG_REISERFS_CHECK
multiline_comment|/* compare total size of entries with item length */
(brace
r_int
id|k
comma
id|l
suffix:semicolon
id|l
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|dir_u-&gt;entry_count
suffix:semicolon
id|k
op_increment
)paren
id|l
op_add_assign
id|dir_u-&gt;entry_sizes
(braket
id|k
)braket
suffix:semicolon
r_if
c_cond
(paren
id|l
op_plus
id|IH_SIZE
op_ne
id|vi-&gt;vi_item_len
op_plus
(paren
(paren
id|is_affected
op_logical_and
(paren
id|vn-&gt;vn_mode
op_eq
id|M_PASTE
op_logical_or
id|vn-&gt;vn_mode
op_eq
id|M_CUT
)paren
)paren
ques
c_cond
id|insert_size
suffix:colon
l_int|0
)paren
)paren
(brace
id|reiserfs_panic
(paren
l_int|NULL
comma
l_string|&quot;vs-8025: set_entry_sizes: (mode==%c, insert_size==%d), invalid length of directory item&quot;
comma
id|vn-&gt;vn_mode
comma
id|insert_size
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
r_return
id|size
suffix:semicolon
)brace
singleline_comment|//
singleline_comment|// return number of entries which may fit into specified amount of
singleline_comment|// free space, or -1 if free space is not enough even for 1 entry
singleline_comment|//
DECL|function|direntry_check_left
r_static
r_int
id|direntry_check_left
(paren
r_struct
id|virtual_item
op_star
id|vi
comma
r_int
id|free
comma
r_int
id|start_skip
comma
r_int
id|end_skip
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|entries
op_assign
l_int|0
suffix:semicolon
r_struct
id|direntry_uarea
op_star
id|dir_u
op_assign
id|vi-&gt;vi_uarea
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|start_skip
suffix:semicolon
id|i
OL
id|dir_u-&gt;entry_count
op_minus
id|end_skip
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dir_u-&gt;entry_sizes
(braket
id|i
)braket
OG
id|free
)paren
multiline_comment|/* i-th entry doesn&squot;t fit into the remaining free space */
r_break
suffix:semicolon
id|free
op_sub_assign
id|dir_u-&gt;entry_sizes
(braket
id|i
)braket
suffix:semicolon
id|entries
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|entries
op_eq
id|dir_u-&gt;entry_count
)paren
(brace
id|reiserfs_panic
(paren
l_int|NULL
comma
l_string|&quot;free space %d, entry_count %d&bslash;n&quot;
comma
id|free
comma
id|dir_u-&gt;entry_count
)paren
suffix:semicolon
)brace
multiline_comment|/* &quot;.&quot; and &quot;..&quot; can not be separated from each other */
r_if
c_cond
(paren
id|start_skip
op_eq
l_int|0
op_logical_and
(paren
id|dir_u-&gt;flags
op_amp
id|DIRENTRY_VI_FIRST_DIRENTRY_ITEM
)paren
op_logical_and
id|entries
OL
l_int|2
)paren
id|entries
op_assign
l_int|0
suffix:semicolon
r_return
id|entries
ques
c_cond
suffix:colon
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|direntry_check_right
r_static
r_int
id|direntry_check_right
(paren
r_struct
id|virtual_item
op_star
id|vi
comma
r_int
id|free
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|entries
op_assign
l_int|0
suffix:semicolon
r_struct
id|direntry_uarea
op_star
id|dir_u
op_assign
id|vi-&gt;vi_uarea
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|dir_u-&gt;entry_count
op_minus
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|dir_u-&gt;entry_sizes
(braket
id|i
)braket
OG
id|free
)paren
multiline_comment|/* i-th entry doesn&squot;t fit into the remaining free space */
r_break
suffix:semicolon
id|free
op_sub_assign
id|dir_u-&gt;entry_sizes
(braket
id|i
)braket
suffix:semicolon
id|entries
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|entries
op_eq
id|dir_u-&gt;entry_count
)paren
id|BUG
(paren
)paren
suffix:semicolon
multiline_comment|/* &quot;.&quot; and &quot;..&quot; can not be separated from each other */
r_if
c_cond
(paren
(paren
id|dir_u-&gt;flags
op_amp
id|DIRENTRY_VI_FIRST_DIRENTRY_ITEM
)paren
op_logical_and
id|entries
OG
id|dir_u-&gt;entry_count
op_minus
l_int|2
)paren
id|entries
op_assign
id|dir_u-&gt;entry_count
op_minus
l_int|2
suffix:semicolon
r_return
id|entries
ques
c_cond
suffix:colon
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* sum of entry sizes between from-th and to-th entries including both edges */
DECL|function|direntry_part_size
r_static
r_int
id|direntry_part_size
(paren
r_struct
id|virtual_item
op_star
id|vi
comma
r_int
id|first
comma
r_int
id|count
)paren
(brace
r_int
id|i
comma
id|retval
suffix:semicolon
r_int
id|from
comma
id|to
suffix:semicolon
r_struct
id|direntry_uarea
op_star
id|dir_u
op_assign
id|vi-&gt;vi_uarea
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|first
op_eq
l_int|0
)paren
id|from
op_assign
l_int|0
suffix:semicolon
r_else
id|from
op_assign
id|dir_u-&gt;entry_count
op_minus
id|count
suffix:semicolon
id|to
op_assign
id|from
op_plus
id|count
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|from
suffix:semicolon
id|i
op_le
id|to
suffix:semicolon
id|i
op_increment
)paren
id|retval
op_add_assign
id|dir_u-&gt;entry_sizes
(braket
id|i
)braket
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|direntry_unit_num
r_static
r_int
id|direntry_unit_num
(paren
r_struct
id|virtual_item
op_star
id|vi
)paren
(brace
r_struct
id|direntry_uarea
op_star
id|dir_u
op_assign
id|vi-&gt;vi_uarea
suffix:semicolon
r_return
id|dir_u-&gt;entry_count
suffix:semicolon
)brace
DECL|function|direntry_print_vi
r_static
r_void
id|direntry_print_vi
(paren
r_struct
id|virtual_item
op_star
id|vi
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|direntry_uarea
op_star
id|dir_u
op_assign
id|vi-&gt;vi_uarea
suffix:semicolon
id|reiserfs_warning
(paren
l_int|NULL
comma
l_string|&quot;DIRENTRY, index %d, type 0x%x, %h, flags 0x%x&quot;
comma
id|vi-&gt;vi_index
comma
id|vi-&gt;vi_type
comma
id|vi-&gt;vi_ih
comma
id|dir_u-&gt;flags
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;%d entries: &quot;
comma
id|dir_u-&gt;entry_count
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
id|dir_u-&gt;entry_count
suffix:semicolon
id|i
op_increment
)paren
id|printk
(paren
l_string|&quot;%d &quot;
comma
id|dir_u-&gt;entry_sizes
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|direntry_ops
r_static
r_struct
id|item_operations
id|direntry_ops
op_assign
(brace
dot
id|bytes_number
op_assign
id|direntry_bytes_number
comma
dot
id|decrement_key
op_assign
id|direntry_decrement_key
comma
dot
id|is_left_mergeable
op_assign
id|direntry_is_left_mergeable
comma
dot
id|print_item
op_assign
id|direntry_print_item
comma
dot
id|check_item
op_assign
id|direntry_check_item
comma
dot
id|create_vi
op_assign
id|direntry_create_vi
comma
dot
id|check_left
op_assign
id|direntry_check_left
comma
dot
id|check_right
op_assign
id|direntry_check_right
comma
dot
id|part_size
op_assign
id|direntry_part_size
comma
dot
id|unit_num
op_assign
id|direntry_unit_num
comma
dot
id|print_vi
op_assign
id|direntry_print_vi
)brace
suffix:semicolon
singleline_comment|//////////////////////////////////////////////////////////////////////////////
singleline_comment|// Error catching functions to catch errors caused by incorrect item types.
singleline_comment|//
DECL|function|errcatch_bytes_number
r_static
r_int
id|errcatch_bytes_number
(paren
r_struct
id|item_head
op_star
id|ih
comma
r_int
id|block_size
)paren
(brace
id|reiserfs_warning
(paren
l_int|NULL
comma
l_string|&quot;green-16001: Invalid item type observed, run fsck ASAP&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|errcatch_decrement_key
r_static
r_void
id|errcatch_decrement_key
(paren
r_struct
id|cpu_key
op_star
id|key
)paren
(brace
id|reiserfs_warning
(paren
l_int|NULL
comma
l_string|&quot;green-16002: Invalid item type observed, run fsck ASAP&quot;
)paren
suffix:semicolon
)brace
DECL|function|errcatch_is_left_mergeable
r_static
r_int
id|errcatch_is_left_mergeable
(paren
r_struct
id|reiserfs_key
op_star
id|key
comma
r_int
r_int
id|bsize
)paren
(brace
id|reiserfs_warning
(paren
l_int|NULL
comma
l_string|&quot;green-16003: Invalid item type observed, run fsck ASAP&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|errcatch_print_item
r_static
r_void
id|errcatch_print_item
(paren
r_struct
id|item_head
op_star
id|ih
comma
r_char
op_star
id|item
)paren
(brace
id|reiserfs_warning
(paren
l_int|NULL
comma
l_string|&quot;green-16004: Invalid item type observed, run fsck ASAP&quot;
)paren
suffix:semicolon
)brace
DECL|function|errcatch_check_item
r_static
r_void
id|errcatch_check_item
(paren
r_struct
id|item_head
op_star
id|ih
comma
r_char
op_star
id|item
)paren
(brace
id|reiserfs_warning
(paren
l_int|NULL
comma
l_string|&quot;green-16005: Invalid item type observed, run fsck ASAP&quot;
)paren
suffix:semicolon
)brace
DECL|function|errcatch_create_vi
r_static
r_int
id|errcatch_create_vi
(paren
r_struct
id|virtual_node
op_star
id|vn
comma
r_struct
id|virtual_item
op_star
id|vi
comma
r_int
id|is_affected
comma
r_int
id|insert_size
)paren
(brace
id|reiserfs_warning
(paren
l_int|NULL
comma
l_string|&quot;green-16006: Invalid item type observed, run fsck ASAP&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
singleline_comment|// We might return -1 here as well, but it won&squot;t help as create_virtual_node() from where
singleline_comment|// this operation is called from is of return type void.
)brace
DECL|function|errcatch_check_left
r_static
r_int
id|errcatch_check_left
(paren
r_struct
id|virtual_item
op_star
id|vi
comma
r_int
id|free
comma
r_int
id|start_skip
comma
r_int
id|end_skip
)paren
(brace
id|reiserfs_warning
(paren
l_int|NULL
comma
l_string|&quot;green-16007: Invalid item type observed, run fsck ASAP&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|errcatch_check_right
r_static
r_int
id|errcatch_check_right
(paren
r_struct
id|virtual_item
op_star
id|vi
comma
r_int
id|free
)paren
(brace
id|reiserfs_warning
(paren
l_int|NULL
comma
l_string|&quot;green-16008: Invalid item type observed, run fsck ASAP&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|errcatch_part_size
r_static
r_int
id|errcatch_part_size
(paren
r_struct
id|virtual_item
op_star
id|vi
comma
r_int
id|first
comma
r_int
id|count
)paren
(brace
id|reiserfs_warning
(paren
l_int|NULL
comma
l_string|&quot;green-16009: Invalid item type observed, run fsck ASAP&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|errcatch_unit_num
r_static
r_int
id|errcatch_unit_num
(paren
r_struct
id|virtual_item
op_star
id|vi
)paren
(brace
id|reiserfs_warning
(paren
l_int|NULL
comma
l_string|&quot;green-16010: Invalid item type observed, run fsck ASAP&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|errcatch_print_vi
r_static
r_void
id|errcatch_print_vi
(paren
r_struct
id|virtual_item
op_star
id|vi
)paren
(brace
id|reiserfs_warning
(paren
l_int|NULL
comma
l_string|&quot;green-16011: Invalid item type observed, run fsck ASAP&quot;
)paren
suffix:semicolon
)brace
DECL|variable|errcatch_ops
r_static
r_struct
id|item_operations
id|errcatch_ops
op_assign
(brace
id|errcatch_bytes_number
comma
id|errcatch_decrement_key
comma
id|errcatch_is_left_mergeable
comma
id|errcatch_print_item
comma
id|errcatch_check_item
comma
id|errcatch_create_vi
comma
id|errcatch_check_left
comma
id|errcatch_check_right
comma
id|errcatch_part_size
comma
id|errcatch_unit_num
comma
id|errcatch_print_vi
)brace
suffix:semicolon
singleline_comment|//////////////////////////////////////////////////////////////////////////////
singleline_comment|//
singleline_comment|//
macro_line|#if ! (TYPE_STAT_DATA == 0 &amp;&amp; TYPE_INDIRECT == 1 &amp;&amp; TYPE_DIRECT == 2 &amp;&amp; TYPE_DIRENTRY == 3)
r_do
op_logical_neg
id|compile
macro_line|#endif
DECL|variable|item_ops
r_struct
id|item_operations
op_star
id|item_ops
(braket
id|TYPE_ANY
op_plus
l_int|1
)braket
op_assign
(brace
op_amp
id|stat_data_ops
comma
op_amp
id|indirect_ops
comma
op_amp
id|direct_ops
comma
op_amp
id|direntry_ops
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
op_amp
id|errcatch_ops
multiline_comment|/* This is to catch errors with invalid type (15th entry for TYPE_ANY) */
)brace
suffix:semicolon
eof
