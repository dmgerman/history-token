macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/minix_fs.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
DECL|enumerator|DEPTH
DECL|enumerator|DIRECT
r_enum
(brace
id|DEPTH
op_assign
l_int|3
comma
id|DIRECT
op_assign
l_int|7
)brace
suffix:semicolon
multiline_comment|/* Only double indirect */
DECL|typedef|block_t
r_typedef
id|u16
id|block_t
suffix:semicolon
multiline_comment|/* 16 bit, host order */
DECL|function|block_to_cpu
r_static
r_inline
r_int
r_int
id|block_to_cpu
c_func
(paren
id|block_t
id|n
)paren
(brace
r_return
id|n
suffix:semicolon
)brace
DECL|function|cpu_to_block
r_static
r_inline
id|block_t
id|cpu_to_block
c_func
(paren
r_int
r_int
id|n
)paren
(brace
r_return
id|n
suffix:semicolon
)brace
DECL|function|i_data
r_static
r_inline
id|block_t
op_star
id|i_data
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
(paren
id|block_t
op_star
)paren
id|minix_i
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|u.i1_data
suffix:semicolon
)brace
DECL|function|block_to_path
r_static
r_int
id|block_to_path
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|block
comma
r_int
id|offsets
(braket
id|DEPTH
)braket
)paren
(brace
r_int
id|n
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|block
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;minix_bmap: block&lt;0&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|block
op_ge
(paren
id|minix_sb
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|s_max_size
op_div
id|BLOCK_SIZE
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;minix_bmap: block&gt;big&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|block
OL
l_int|7
)paren
(brace
id|offsets
(braket
id|n
op_increment
)braket
op_assign
id|block
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|block
op_sub_assign
l_int|7
)paren
OL
l_int|512
)paren
(brace
id|offsets
(braket
id|n
op_increment
)braket
op_assign
l_int|7
suffix:semicolon
id|offsets
(braket
id|n
op_increment
)braket
op_assign
id|block
suffix:semicolon
)brace
r_else
(brace
id|block
op_sub_assign
l_int|512
suffix:semicolon
id|offsets
(braket
id|n
op_increment
)braket
op_assign
l_int|8
suffix:semicolon
id|offsets
(braket
id|n
op_increment
)braket
op_assign
id|block
op_rshift
l_int|9
suffix:semicolon
id|offsets
(braket
id|n
op_increment
)braket
op_assign
id|block
op_amp
l_int|511
suffix:semicolon
)brace
r_return
id|n
suffix:semicolon
)brace
macro_line|#include &quot;itree_common.c&quot;
DECL|function|V1_minix_get_block
r_int
id|V1_minix_get_block
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|block
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
r_return
id|get_block
c_func
(paren
id|inode
comma
id|block
comma
id|bh_result
comma
id|create
)paren
suffix:semicolon
)brace
DECL|function|V1_minix_truncate
r_void
id|V1_minix_truncate
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|truncate
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
eof
