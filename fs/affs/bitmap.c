multiline_comment|/*&n; *  linux/fs/affs/bitmap.c&n; *&n; *  (c) 1996 Hans-Joachim Widmaier&n; *&n; *  bitmap.c contains the code that handles all bitmap related stuff -&n; *  block allocation, deallocation, calculation of free space.&n; */
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/affs_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/amigaffs.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
multiline_comment|/* This is, of course, shamelessly stolen from fs/minix */
DECL|variable|nibblemap
r_static
r_int
id|nibblemap
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|2
comma
l_int|1
comma
l_int|2
comma
l_int|2
comma
l_int|3
comma
l_int|1
comma
l_int|2
comma
l_int|2
comma
l_int|3
comma
l_int|2
comma
l_int|3
comma
l_int|3
comma
l_int|4
)brace
suffix:semicolon
id|u32
DECL|function|affs_count_free_bits
id|affs_count_free_bits
c_func
(paren
id|u32
id|blocksize
comma
r_const
r_void
op_star
id|data
)paren
(brace
r_const
id|u32
op_star
id|map
suffix:semicolon
id|u32
id|free
suffix:semicolon
id|u32
id|tmp
suffix:semicolon
id|map
op_assign
id|data
suffix:semicolon
id|free
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|blocksize
op_div_assign
l_int|4
suffix:semicolon
id|blocksize
OG
l_int|0
suffix:semicolon
id|blocksize
op_decrement
)paren
(brace
id|tmp
op_assign
op_star
id|map
op_increment
suffix:semicolon
r_while
c_loop
(paren
id|tmp
)paren
(brace
id|free
op_add_assign
id|nibblemap
(braket
id|tmp
op_amp
l_int|0xf
)braket
suffix:semicolon
id|tmp
op_rshift_assign
l_int|4
suffix:semicolon
)brace
)brace
r_return
id|free
suffix:semicolon
)brace
id|u32
DECL|function|affs_count_free_blocks
id|affs_count_free_blocks
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|affs_bm_info
op_star
id|bm
suffix:semicolon
id|u32
id|free
suffix:semicolon
r_int
id|i
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: count_free_blocks()&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
r_return
l_int|0
suffix:semicolon
id|down
c_func
(paren
op_amp
id|AFFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_bmlock
)paren
suffix:semicolon
id|bm
op_assign
id|AFFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_bitmap
suffix:semicolon
id|free
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|AFFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_bmap_count
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|bm
op_increment
comma
id|i
op_decrement
)paren
id|free
op_add_assign
id|bm-&gt;bm_free
suffix:semicolon
id|up
c_func
(paren
op_amp
id|AFFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_bmlock
)paren
suffix:semicolon
r_return
id|free
suffix:semicolon
)brace
r_void
DECL|function|affs_free_block
id|affs_free_block
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|u32
id|block
)paren
(brace
r_struct
id|affs_sb_info
op_star
id|sbi
op_assign
id|AFFS_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
r_struct
id|affs_bm_info
op_star
id|bm
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|u32
id|blk
comma
id|bmap
comma
id|bit
comma
id|mask
comma
id|tmp
suffix:semicolon
id|u32
op_star
id|data
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: free_block(%u)&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block
OG
id|sbi-&gt;s_partition_size
)paren
r_goto
id|err_range
suffix:semicolon
id|blk
op_assign
id|block
op_minus
id|sbi-&gt;s_reserved
suffix:semicolon
id|bmap
op_assign
id|blk
op_div
id|sbi-&gt;s_bmap_bits
suffix:semicolon
id|bit
op_assign
id|blk
op_mod
id|sbi-&gt;s_bmap_bits
suffix:semicolon
id|bm
op_assign
op_amp
id|sbi-&gt;s_bitmap
(braket
id|bmap
)braket
suffix:semicolon
id|down
c_func
(paren
op_amp
id|sbi-&gt;s_bmlock
)paren
suffix:semicolon
id|bh
op_assign
id|sbi-&gt;s_bmap_bh
suffix:semicolon
r_if
c_cond
(paren
id|sbi-&gt;s_last_bmap
op_ne
id|bmap
)paren
(brace
id|affs_brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh
op_assign
id|affs_bread
c_func
(paren
id|sb
comma
id|bm-&gt;bm_key
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_goto
id|err_bh_read
suffix:semicolon
id|sbi-&gt;s_bmap_bh
op_assign
id|bh
suffix:semicolon
id|sbi-&gt;s_last_bmap
op_assign
id|bmap
suffix:semicolon
)brace
id|mask
op_assign
l_int|1
op_lshift
(paren
id|bit
op_amp
l_int|31
)paren
suffix:semicolon
id|data
op_assign
(paren
id|u32
op_star
)paren
id|bh-&gt;b_data
op_plus
id|bit
op_div
l_int|32
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* mark block free */
id|tmp
op_assign
id|be32_to_cpu
c_func
(paren
op_star
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|mask
)paren
r_goto
id|err_free
suffix:semicolon
op_star
id|data
op_assign
id|cpu_to_be32
c_func
(paren
id|tmp
op_or
id|mask
)paren
suffix:semicolon
multiline_comment|/* fix checksum */
id|tmp
op_assign
id|be32_to_cpu
c_func
(paren
op_star
(paren
id|u32
op_star
)paren
id|bh-&gt;b_data
)paren
suffix:semicolon
op_star
(paren
id|u32
op_star
)paren
id|bh-&gt;b_data
op_assign
id|cpu_to_be32
c_func
(paren
id|tmp
op_minus
id|mask
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
id|bm-&gt;bm_free
op_increment
suffix:semicolon
id|up
c_func
(paren
op_amp
id|sbi-&gt;s_bmlock
)paren
suffix:semicolon
r_return
suffix:semicolon
id|err_free
suffix:colon
id|affs_warning
c_func
(paren
id|sb
comma
l_string|&quot;affs_free_block&quot;
comma
l_string|&quot;Trying to free block %u which is already free&quot;
comma
id|block
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|sbi-&gt;s_bmlock
)paren
suffix:semicolon
r_return
suffix:semicolon
id|err_bh_read
suffix:colon
id|affs_error
c_func
(paren
id|sb
comma
l_string|&quot;affs_free_block&quot;
comma
l_string|&quot;Cannot read bitmap block %u&quot;
comma
id|bm-&gt;bm_key
)paren
suffix:semicolon
id|sbi-&gt;s_bmap_bh
op_assign
l_int|NULL
suffix:semicolon
id|sbi-&gt;s_last_bmap
op_assign
op_complement
l_int|0
suffix:semicolon
id|up
c_func
(paren
op_amp
id|sbi-&gt;s_bmlock
)paren
suffix:semicolon
r_return
suffix:semicolon
id|err_range
suffix:colon
id|affs_error
c_func
(paren
id|sb
comma
l_string|&quot;affs_free_block&quot;
comma
l_string|&quot;Block %u outside partition&quot;
comma
id|block
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Allocate a block in the given allocation zone.&n; * Since we have to byte-swap the bitmap on little-endian&n; * machines, this is rather expensive. Therefor we will&n; * preallocate up to 16 blocks from the same word, if&n; * possible. We are not doing preallocations in the&n; * header zone, though.&n; */
id|u32
DECL|function|affs_alloc_block
id|affs_alloc_block
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|u32
id|goal
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_struct
id|affs_sb_info
op_star
id|sbi
suffix:semicolon
r_struct
id|affs_bm_info
op_star
id|bm
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|u32
op_star
id|data
comma
op_star
id|enddata
suffix:semicolon
id|u32
id|blk
comma
id|bmap
comma
id|bit
comma
id|mask
comma
id|mask2
comma
id|tmp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
id|sbi
op_assign
id|AFFS_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: balloc(inode=%lu,goal=%u): &quot;
comma
id|inode-&gt;i_ino
comma
id|goal
)paren
suffix:semicolon
r_if
c_cond
(paren
id|AFFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_pa_cnt
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%d&bslash;n&quot;
comma
id|AFFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_lastalloc
op_plus
l_int|1
)paren
suffix:semicolon
id|AFFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_pa_cnt
op_decrement
suffix:semicolon
r_return
op_increment
id|AFFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_lastalloc
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|goal
op_logical_or
id|goal
OG
id|sbi-&gt;s_partition_size
)paren
(brace
r_if
c_cond
(paren
id|goal
)paren
id|affs_warning
c_func
(paren
id|sb
comma
l_string|&quot;affs_balloc&quot;
comma
l_string|&quot;invalid goal %d&quot;
comma
id|goal
)paren
suffix:semicolon
singleline_comment|//if (!AFFS_I(inode)-&gt;i_last_block)
singleline_comment|//&t;affs_warning(sb, &quot;affs_balloc&quot;, &quot;no last alloc block&quot;);
id|goal
op_assign
id|sbi-&gt;s_reserved
suffix:semicolon
)brace
id|blk
op_assign
id|goal
op_minus
id|sbi-&gt;s_reserved
suffix:semicolon
id|bmap
op_assign
id|blk
op_div
id|sbi-&gt;s_bmap_bits
suffix:semicolon
id|bm
op_assign
op_amp
id|sbi-&gt;s_bitmap
(braket
id|bmap
)braket
suffix:semicolon
id|down
c_func
(paren
op_amp
id|sbi-&gt;s_bmlock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bm-&gt;bm_free
)paren
r_goto
id|find_bmap_bit
suffix:semicolon
id|find_bmap
suffix:colon
multiline_comment|/* search for the next bmap buffer with free bits */
id|i
op_assign
id|sbi-&gt;s_bmap_count
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
op_decrement
id|i
OL
l_int|0
)paren
r_goto
id|err_full
suffix:semicolon
id|bmap
op_increment
suffix:semicolon
id|bm
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|bmap
OL
id|sbi-&gt;s_bmap_count
)paren
r_continue
suffix:semicolon
multiline_comment|/* restart search at zero */
id|bmap
op_assign
l_int|0
suffix:semicolon
id|bm
op_assign
id|sbi-&gt;s_bitmap
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|bm-&gt;bm_free
)paren
suffix:semicolon
id|blk
op_assign
id|bmap
op_star
id|sbi-&gt;s_bmap_bits
suffix:semicolon
id|find_bmap_bit
suffix:colon
id|bh
op_assign
id|sbi-&gt;s_bmap_bh
suffix:semicolon
r_if
c_cond
(paren
id|sbi-&gt;s_last_bmap
op_ne
id|bmap
)paren
(brace
id|affs_brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh
op_assign
id|affs_bread
c_func
(paren
id|sb
comma
id|bm-&gt;bm_key
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_goto
id|err_bh_read
suffix:semicolon
id|sbi-&gt;s_bmap_bh
op_assign
id|bh
suffix:semicolon
id|sbi-&gt;s_last_bmap
op_assign
id|bmap
suffix:semicolon
)brace
multiline_comment|/* find an unused block in this bitmap block */
id|bit
op_assign
id|blk
op_mod
id|sbi-&gt;s_bmap_bits
suffix:semicolon
id|data
op_assign
(paren
id|u32
op_star
)paren
id|bh-&gt;b_data
op_plus
id|bit
op_div
l_int|32
op_plus
l_int|1
suffix:semicolon
id|enddata
op_assign
(paren
id|u32
op_star
)paren
(paren
(paren
id|u8
op_star
)paren
id|bh-&gt;b_data
op_plus
id|sb-&gt;s_blocksize
)paren
suffix:semicolon
id|mask
op_assign
op_complement
l_int|0UL
op_lshift
(paren
id|bit
op_amp
l_int|31
)paren
suffix:semicolon
id|blk
op_and_assign
op_complement
l_int|31UL
suffix:semicolon
id|tmp
op_assign
id|be32_to_cpu
c_func
(paren
op_star
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|mask
)paren
r_goto
id|find_bit
suffix:semicolon
multiline_comment|/* scan the rest of the buffer */
r_do
(brace
id|blk
op_add_assign
l_int|32
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|data
op_ge
id|enddata
)paren
multiline_comment|/* didn&squot;t find something, can only happen&n;&t;&t;&t; * if scan didn&squot;t start at 0, try next bmap&n;&t;&t;&t; */
r_goto
id|find_bmap
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|tmp
op_assign
op_star
id|data
)paren
)paren
suffix:semicolon
id|tmp
op_assign
id|be32_to_cpu
c_func
(paren
id|tmp
)paren
suffix:semicolon
id|mask
op_assign
op_complement
l_int|0
suffix:semicolon
id|find_bit
suffix:colon
multiline_comment|/* finally look for a free bit in the word */
id|bit
op_assign
id|ffs
c_func
(paren
id|tmp
op_amp
id|mask
)paren
op_minus
l_int|1
suffix:semicolon
id|blk
op_add_assign
id|bit
op_plus
id|sbi-&gt;s_reserved
suffix:semicolon
id|mask2
op_assign
id|mask
op_assign
l_int|1
op_lshift
(paren
id|bit
op_amp
l_int|31
)paren
suffix:semicolon
id|AFFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_lastalloc
op_assign
id|blk
suffix:semicolon
multiline_comment|/* prealloc as much as possible within this word */
r_while
c_loop
(paren
(paren
id|mask2
op_lshift_assign
l_int|1
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|tmp
op_amp
id|mask2
)paren
)paren
r_break
suffix:semicolon
id|AFFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_pa_cnt
op_increment
suffix:semicolon
id|mask
op_or_assign
id|mask2
suffix:semicolon
)brace
id|bm-&gt;bm_free
op_sub_assign
id|AFFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_pa_cnt
op_plus
l_int|1
suffix:semicolon
op_star
id|data
op_assign
id|cpu_to_be32
c_func
(paren
id|tmp
op_amp
op_complement
id|mask
)paren
suffix:semicolon
multiline_comment|/* fix checksum */
id|tmp
op_assign
id|be32_to_cpu
c_func
(paren
op_star
(paren
id|u32
op_star
)paren
id|bh-&gt;b_data
)paren
suffix:semicolon
op_star
(paren
id|u32
op_star
)paren
id|bh-&gt;b_data
op_assign
id|cpu_to_be32
c_func
(paren
id|tmp
op_plus
id|mask
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
id|up
c_func
(paren
op_amp
id|sbi-&gt;s_bmlock
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%d&bslash;n&quot;
comma
id|blk
)paren
suffix:semicolon
r_return
id|blk
suffix:semicolon
id|err_bh_read
suffix:colon
id|affs_error
c_func
(paren
id|sb
comma
l_string|&quot;affs_read_block&quot;
comma
l_string|&quot;Cannot read bitmap block %u&quot;
comma
id|bm-&gt;bm_key
)paren
suffix:semicolon
id|sbi-&gt;s_bmap_bh
op_assign
l_int|NULL
suffix:semicolon
id|sbi-&gt;s_last_bmap
op_assign
op_complement
l_int|0
suffix:semicolon
id|err_full
suffix:colon
id|up
c_func
(paren
op_amp
id|sbi-&gt;s_bmlock
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|affs_init_bitmap
r_int
id|affs_init_bitmap
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
op_star
id|flags
)paren
(brace
r_struct
id|affs_bm_info
op_star
id|bm
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bmap_bh
op_assign
l_int|NULL
comma
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|u32
op_star
id|bmap_blk
suffix:semicolon
id|u32
id|size
comma
id|blk
comma
id|end
comma
id|offset
comma
id|mask
suffix:semicolon
r_int
id|i
comma
id|res
op_assign
l_int|0
suffix:semicolon
r_struct
id|affs_sb_info
op_star
id|sbi
op_assign
id|AFFS_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|flags
op_amp
id|MS_RDONLY
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|AFFS_ROOT_TAIL
c_func
(paren
id|sb
comma
id|sbi-&gt;s_root_bh
)paren
op_member_access_from_pointer
id|bm_flag
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;AFFS: Bitmap invalid - mounting %s read only&bslash;n&quot;
comma
id|sb-&gt;s_id
)paren
suffix:semicolon
op_star
id|flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|sbi-&gt;s_last_bmap
op_assign
op_complement
l_int|0
suffix:semicolon
id|sbi-&gt;s_bmap_bh
op_assign
l_int|NULL
suffix:semicolon
id|sbi-&gt;s_bmap_bits
op_assign
id|sb-&gt;s_blocksize
op_star
l_int|8
op_minus
l_int|32
suffix:semicolon
id|sbi-&gt;s_bmap_count
op_assign
(paren
id|sbi-&gt;s_partition_size
op_minus
id|sbi-&gt;s_reserved
op_plus
id|sbi-&gt;s_bmap_bits
op_minus
l_int|1
)paren
op_div
id|sbi-&gt;s_bmap_bits
suffix:semicolon
id|size
op_assign
id|sbi-&gt;s_bmap_count
op_star
r_sizeof
(paren
op_star
id|bm
)paren
suffix:semicolon
id|bm
op_assign
id|sbi-&gt;s_bitmap
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
id|sbi-&gt;s_bitmap
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AFFS: Bitmap allocation failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|sbi-&gt;s_bitmap
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
id|bmap_blk
op_assign
(paren
id|u32
op_star
)paren
id|sbi-&gt;s_root_bh-&gt;b_data
suffix:semicolon
id|blk
op_assign
id|sb-&gt;s_blocksize
op_div
l_int|4
op_minus
l_int|49
suffix:semicolon
id|end
op_assign
id|blk
op_plus
l_int|25
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|sbi-&gt;s_bmap_count
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|bm
op_increment
comma
id|i
op_decrement
)paren
(brace
id|affs_brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bm-&gt;bm_key
op_assign
id|be32_to_cpu
c_func
(paren
id|bmap_blk
(braket
id|blk
)braket
)paren
suffix:semicolon
id|bh
op_assign
id|affs_bread
c_func
(paren
id|sb
comma
id|bm-&gt;bm_key
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AFFS: Cannot read bitmap&bslash;n&quot;
)paren
suffix:semicolon
id|res
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|affs_checksum_block
c_func
(paren
id|sb
comma
id|bh
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;AFFS: Bitmap %u invalid - mounting %s read only.&bslash;n&quot;
comma
id|bm-&gt;bm_key
comma
id|sb-&gt;s_id
)paren
suffix:semicolon
op_star
id|flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: read bitmap block %d: %d&bslash;n&quot;
comma
id|blk
comma
id|bm-&gt;bm_key
)paren
suffix:semicolon
id|bm-&gt;bm_free
op_assign
id|affs_count_free_bits
c_func
(paren
id|sb-&gt;s_blocksize
op_minus
l_int|4
comma
id|bh-&gt;b_data
op_plus
l_int|4
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t try read the extension if this is the last block,&n;&t;&t; * but we also need the right bm pointer below&n;&t;&t; */
r_if
c_cond
(paren
op_increment
id|blk
OL
id|end
op_logical_or
id|i
op_eq
l_int|1
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|bmap_bh
)paren
id|affs_brelse
c_func
(paren
id|bmap_bh
)paren
suffix:semicolon
id|bmap_bh
op_assign
id|affs_bread
c_func
(paren
id|sb
comma
id|be32_to_cpu
c_func
(paren
id|bmap_blk
(braket
id|blk
)braket
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bmap_bh
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AFFS: Cannot read bitmap extension&bslash;n&quot;
)paren
suffix:semicolon
id|res
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|bmap_blk
op_assign
(paren
id|u32
op_star
)paren
id|bmap_bh-&gt;b_data
suffix:semicolon
id|blk
op_assign
l_int|0
suffix:semicolon
id|end
op_assign
id|sb-&gt;s_blocksize
op_div
l_int|4
op_minus
l_int|1
suffix:semicolon
)brace
id|offset
op_assign
(paren
id|sbi-&gt;s_partition_size
op_minus
id|sbi-&gt;s_reserved
)paren
op_mod
id|sbi-&gt;s_bmap_bits
suffix:semicolon
id|mask
op_assign
op_complement
(paren
l_int|0xFFFFFFFFU
op_lshift
(paren
id|offset
op_amp
l_int|31
)paren
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;last word: %d %d %d&bslash;n&quot;
comma
id|offset
comma
id|offset
op_div
l_int|32
op_plus
l_int|1
comma
id|mask
)paren
suffix:semicolon
id|offset
op_assign
id|offset
op_div
l_int|32
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|mask
)paren
(brace
id|u32
id|old
comma
r_new
suffix:semicolon
multiline_comment|/* Mark unused bits in the last word as allocated */
id|old
op_assign
id|be32_to_cpu
c_func
(paren
(paren
(paren
id|u32
op_star
)paren
id|bh-&gt;b_data
)paren
(braket
id|offset
)braket
)paren
suffix:semicolon
r_new
op_assign
id|old
op_amp
id|mask
suffix:semicolon
singleline_comment|//if (old != new) {
(paren
(paren
id|u32
op_star
)paren
id|bh-&gt;b_data
)paren
(braket
id|offset
)braket
op_assign
id|cpu_to_be32
c_func
(paren
r_new
)paren
suffix:semicolon
multiline_comment|/* fix checksum */
singleline_comment|//new -= old;
singleline_comment|//old = be32_to_cpu(*(u32 *)bh-&gt;b_data);
singleline_comment|//*(u32 *)bh-&gt;b_data = cpu_to_be32(old - new);
singleline_comment|//mark_buffer_dirty(bh);
singleline_comment|//}
multiline_comment|/* correct offset for the bitmap count below */
singleline_comment|//offset++;
)brace
r_while
c_loop
(paren
op_increment
id|offset
OL
id|sb-&gt;s_blocksize
op_div
l_int|4
)paren
(paren
(paren
id|u32
op_star
)paren
id|bh-&gt;b_data
)paren
(braket
id|offset
)braket
op_assign
l_int|0
suffix:semicolon
(paren
(paren
id|u32
op_star
)paren
id|bh-&gt;b_data
)paren
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
(paren
(paren
id|u32
op_star
)paren
id|bh-&gt;b_data
)paren
(braket
l_int|0
)braket
op_assign
id|cpu_to_be32
c_func
(paren
op_minus
id|affs_checksum_block
c_func
(paren
id|sb
comma
id|bh
)paren
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
multiline_comment|/* recalculate bitmap count for last block */
id|bm
op_decrement
suffix:semicolon
id|bm-&gt;bm_free
op_assign
id|affs_count_free_bits
c_func
(paren
id|sb-&gt;s_blocksize
op_minus
l_int|4
comma
id|bh-&gt;b_data
op_plus
l_int|4
)paren
suffix:semicolon
id|out
suffix:colon
id|affs_brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|affs_brelse
c_func
(paren
id|bmap_bh
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|affs_free_bitmap
r_void
id|affs_free_bitmap
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|affs_sb_info
op_star
id|sbi
op_assign
id|AFFS_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbi-&gt;s_bitmap
)paren
r_return
suffix:semicolon
id|affs_brelse
c_func
(paren
id|sbi-&gt;s_bmap_bh
)paren
suffix:semicolon
id|sbi-&gt;s_bmap_bh
op_assign
l_int|NULL
suffix:semicolon
id|sbi-&gt;s_last_bmap
op_assign
op_complement
l_int|0
suffix:semicolon
id|kfree
c_func
(paren
id|sbi-&gt;s_bitmap
)paren
suffix:semicolon
id|sbi-&gt;s_bitmap
op_assign
l_int|NULL
suffix:semicolon
)brace
eof
