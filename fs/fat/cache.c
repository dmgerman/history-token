multiline_comment|/*&n; *  linux/fs/fat/cache.c&n; *&n; *  Written 1992,1993 by Werner Almesberger&n; *&n; *  Mar 1999. AV. Changed cache, so that it uses the starting cluster instead&n; *&t;of inode number.&n; *  May 1999. AV. Fixed the bogosity with FAT32 (read &quot;FAT28&quot;). Fscking lusers.&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
DECL|variable|fat_cache
DECL|variable|cache
r_static
r_struct
id|fat_cache
op_star
id|fat_cache
comma
id|cache
(braket
id|FAT_CACHE
)braket
suffix:semicolon
DECL|variable|fat_cache_lock
r_static
id|spinlock_t
id|fat_cache_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|__fat_access
r_int
id|__fat_access
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|nr
comma
r_int
id|new_value
)paren
(brace
r_struct
id|msdos_sb_info
op_star
id|sbi
op_assign
id|MSDOS_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
comma
op_star
id|bh2
comma
op_star
id|c_bh
comma
op_star
id|c_bh2
suffix:semicolon
r_int
r_char
op_star
id|p_first
comma
op_star
id|p_last
suffix:semicolon
r_int
id|copy
comma
id|first
comma
id|last
comma
id|next
comma
id|b
suffix:semicolon
r_if
c_cond
(paren
id|sbi-&gt;fat_bits
op_eq
l_int|32
)paren
(brace
id|first
op_assign
id|last
op_assign
id|nr
op_star
l_int|4
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|sbi-&gt;fat_bits
op_eq
l_int|16
)paren
(brace
id|first
op_assign
id|last
op_assign
id|nr
op_star
l_int|2
suffix:semicolon
)brace
r_else
(brace
id|first
op_assign
id|nr
op_star
l_int|3
op_div
l_int|2
suffix:semicolon
id|last
op_assign
id|first
op_plus
l_int|1
suffix:semicolon
)brace
id|b
op_assign
id|sbi-&gt;fat_start
op_plus
(paren
id|first
op_rshift
id|sb-&gt;s_blocksize_bits
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
id|b
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;FAT: bread(block %d) in&quot;
l_string|&quot; fat_access failed&bslash;n&quot;
comma
id|b
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|first
op_rshift
id|sb-&gt;s_blocksize_bits
)paren
op_eq
(paren
id|last
op_rshift
id|sb-&gt;s_blocksize_bits
)paren
)paren
(brace
id|bh2
op_assign
id|bh
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh2
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
id|b
op_plus
l_int|1
)paren
)paren
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;FAT: bread(block %d) in&quot;
l_string|&quot; fat_access failed&bslash;n&quot;
comma
id|b
op_plus
l_int|1
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|sbi-&gt;fat_bits
op_eq
l_int|32
)paren
(brace
id|p_first
op_assign
id|p_last
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* GCC needs that stuff */
id|next
op_assign
id|CF_LE_L
c_func
(paren
(paren
(paren
id|__u32
op_star
)paren
id|bh-&gt;b_data
)paren
(braket
(paren
id|first
op_amp
(paren
id|sb-&gt;s_blocksize
op_minus
l_int|1
)paren
)paren
op_rshift
l_int|2
)braket
)paren
suffix:semicolon
multiline_comment|/* Fscking Microsoft marketing department. Their &quot;32&quot; is 28. */
id|next
op_and_assign
l_int|0x0fffffff
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|sbi-&gt;fat_bits
op_eq
l_int|16
)paren
(brace
id|p_first
op_assign
id|p_last
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* GCC needs that stuff */
id|next
op_assign
id|CF_LE_W
c_func
(paren
(paren
(paren
id|__u16
op_star
)paren
id|bh-&gt;b_data
)paren
(braket
(paren
id|first
op_amp
(paren
id|sb-&gt;s_blocksize
op_minus
l_int|1
)paren
)paren
op_rshift
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
id|p_first
op_assign
op_amp
(paren
(paren
id|__u8
op_star
)paren
id|bh-&gt;b_data
)paren
(braket
id|first
op_amp
(paren
id|sb-&gt;s_blocksize
op_minus
l_int|1
)paren
)braket
suffix:semicolon
id|p_last
op_assign
op_amp
(paren
(paren
id|__u8
op_star
)paren
id|bh2-&gt;b_data
)paren
(braket
(paren
id|first
op_plus
l_int|1
)paren
op_amp
(paren
id|sb-&gt;s_blocksize
op_minus
l_int|1
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|nr
op_amp
l_int|1
)paren
id|next
op_assign
(paren
(paren
op_star
id|p_first
op_rshift
l_int|4
)paren
op_or
(paren
op_star
id|p_last
op_lshift
l_int|4
)paren
)paren
op_amp
l_int|0xfff
suffix:semicolon
r_else
id|next
op_assign
(paren
op_star
id|p_first
op_plus
(paren
op_star
id|p_last
op_lshift
l_int|8
)paren
)paren
op_amp
l_int|0xfff
suffix:semicolon
)brace
r_if
c_cond
(paren
id|new_value
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|sbi-&gt;fat_bits
op_eq
l_int|32
)paren
(brace
(paren
(paren
id|__u32
op_star
)paren
id|bh-&gt;b_data
)paren
(braket
(paren
id|first
op_amp
(paren
id|sb-&gt;s_blocksize
op_minus
l_int|1
)paren
)paren
op_rshift
l_int|2
)braket
op_assign
id|CT_LE_L
c_func
(paren
id|new_value
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|sbi-&gt;fat_bits
op_eq
l_int|16
)paren
(brace
(paren
(paren
id|__u16
op_star
)paren
id|bh-&gt;b_data
)paren
(braket
(paren
id|first
op_amp
(paren
id|sb-&gt;s_blocksize
op_minus
l_int|1
)paren
)paren
op_rshift
l_int|1
)braket
op_assign
id|CT_LE_W
c_func
(paren
id|new_value
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|nr
op_amp
l_int|1
)paren
(brace
op_star
id|p_first
op_assign
(paren
op_star
id|p_first
op_amp
l_int|0xf
)paren
op_or
(paren
id|new_value
op_lshift
l_int|4
)paren
suffix:semicolon
op_star
id|p_last
op_assign
id|new_value
op_rshift
l_int|4
suffix:semicolon
)brace
r_else
(brace
op_star
id|p_first
op_assign
id|new_value
op_amp
l_int|0xff
suffix:semicolon
op_star
id|p_last
op_assign
(paren
op_star
id|p_last
op_amp
l_int|0xf0
)paren
op_or
(paren
id|new_value
op_rshift
l_int|8
)paren
suffix:semicolon
)brace
id|mark_buffer_dirty
c_func
(paren
id|bh2
)paren
suffix:semicolon
)brace
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
r_for
c_loop
(paren
id|copy
op_assign
l_int|1
suffix:semicolon
id|copy
OL
id|sbi-&gt;fats
suffix:semicolon
id|copy
op_increment
)paren
(brace
id|b
op_assign
id|sbi-&gt;fat_start
op_plus
(paren
id|first
op_rshift
id|sb-&gt;s_blocksize_bits
)paren
op_plus
id|sbi-&gt;fat_length
op_star
id|copy
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|c_bh
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
id|b
)paren
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|bh
op_ne
id|bh2
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|c_bh2
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
id|b
op_plus
l_int|1
)paren
)paren
)paren
(brace
id|brelse
c_func
(paren
id|c_bh
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|c_bh2-&gt;b_data
comma
id|bh2-&gt;b_data
comma
id|sb-&gt;s_blocksize
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|c_bh2
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|c_bh2
)paren
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|c_bh-&gt;b_data
comma
id|bh-&gt;b_data
comma
id|sb-&gt;s_blocksize
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|c_bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|c_bh
)paren
suffix:semicolon
)brace
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
op_ne
id|bh2
)paren
id|brelse
c_func
(paren
id|bh2
)paren
suffix:semicolon
r_return
id|next
suffix:semicolon
)brace
multiline_comment|/* &n; * Returns the this&squot;th FAT entry, -1 if it is an end-of-file entry. If&n; * new_value is != -1, that FAT entry is replaced by it.&n; */
DECL|function|fat_access
r_int
id|fat_access
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|nr
comma
r_int
id|new_value
)paren
(brace
r_int
id|next
suffix:semicolon
id|next
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|nr
OL
l_int|2
op_logical_or
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|clusters
op_plus
l_int|2
op_le
id|nr
)paren
(brace
id|fat_fs_panic
c_func
(paren
id|sb
comma
l_string|&quot;invalid access to FAT (entry 0x%08x)&quot;
comma
id|nr
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|new_value
op_eq
id|FAT_ENT_EOF
)paren
id|new_value
op_assign
id|EOF_FAT
c_func
(paren
id|sb
)paren
suffix:semicolon
id|next
op_assign
id|__fat_access
c_func
(paren
id|sb
comma
id|nr
comma
id|new_value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|next
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|next
op_ge
id|BAD_FAT
c_func
(paren
id|sb
)paren
)paren
id|next
op_assign
id|FAT_ENT_EOF
suffix:semicolon
id|out
suffix:colon
r_return
id|next
suffix:semicolon
)brace
DECL|function|fat_cache_init
r_void
id|fat_cache_init
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|initialized
suffix:semicolon
r_int
id|count
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|fat_cache_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|initialized
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|fat_cache_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|fat_cache
op_assign
op_amp
id|cache
(braket
l_int|0
)braket
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
id|FAT_CACHE
suffix:semicolon
id|count
op_increment
)paren
(brace
id|cache
(braket
id|count
)braket
dot
id|sb
op_assign
l_int|NULL
suffix:semicolon
id|cache
(braket
id|count
)braket
dot
id|next
op_assign
id|count
op_eq
id|FAT_CACHE
op_minus
l_int|1
ques
c_cond
l_int|NULL
suffix:colon
op_amp
id|cache
(braket
id|count
op_plus
l_int|1
)braket
suffix:semicolon
)brace
id|initialized
op_assign
l_int|1
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|fat_cache_lock
)paren
suffix:semicolon
)brace
DECL|function|fat_cache_lookup
r_void
id|fat_cache_lookup
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|cluster
comma
r_int
op_star
id|f_clu
comma
r_int
op_star
id|d_clu
)paren
(brace
r_struct
id|fat_cache
op_star
id|walk
suffix:semicolon
r_int
id|first
op_assign
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_start
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|first
)paren
r_return
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|fat_cache_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|walk
op_assign
id|fat_cache
suffix:semicolon
id|walk
suffix:semicolon
id|walk
op_assign
id|walk-&gt;next
)paren
r_if
c_cond
(paren
id|inode-&gt;i_sb
op_eq
id|walk-&gt;sb
op_logical_and
id|walk-&gt;start_cluster
op_eq
id|first
op_logical_and
id|walk-&gt;file_cluster
op_le
id|cluster
op_logical_and
id|walk-&gt;file_cluster
OG
op_star
id|f_clu
)paren
(brace
op_star
id|d_clu
op_assign
id|walk-&gt;disk_cluster
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;cache hit: %d (%d)&bslash;n&quot;
comma
id|walk-&gt;file_cluster
comma
op_star
id|d_clu
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
(paren
op_star
id|f_clu
op_assign
id|walk-&gt;file_cluster
)paren
op_eq
id|cluster
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|fat_cache_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|fat_cache_lock
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;cache miss&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#ifdef DEBUG
DECL|function|list_cache
r_static
r_void
id|list_cache
c_func
(paren
r_void
)paren
(brace
r_struct
id|fat_cache
op_star
id|walk
suffix:semicolon
r_for
c_loop
(paren
id|walk
op_assign
id|fat_cache
suffix:semicolon
id|walk
suffix:semicolon
id|walk
op_assign
id|walk-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|walk-&gt;sb
)paren
id|printk
c_func
(paren
l_string|&quot;&lt;%s,%d&gt;(%d,%d) &quot;
comma
id|walk-&gt;sb-&gt;s_id
comma
id|walk-&gt;start_cluster
comma
id|walk-&gt;file_cluster
comma
id|walk-&gt;disk_cluster
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;-- &quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|fat_cache_add
r_void
id|fat_cache_add
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|f_clu
comma
r_int
id|d_clu
)paren
(brace
r_struct
id|fat_cache
op_star
id|walk
comma
op_star
id|last
suffix:semicolon
r_int
id|first
op_assign
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_start
suffix:semicolon
id|last
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|fat_cache_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|walk
op_assign
id|fat_cache
suffix:semicolon
id|walk-&gt;next
suffix:semicolon
id|walk
op_assign
(paren
id|last
op_assign
id|walk
)paren
op_member_access_from_pointer
id|next
)paren
r_if
c_cond
(paren
id|inode-&gt;i_sb
op_eq
id|walk-&gt;sb
op_logical_and
id|walk-&gt;start_cluster
op_eq
id|first
op_logical_and
id|walk-&gt;file_cluster
op_eq
id|f_clu
)paren
(brace
r_if
c_cond
(paren
id|walk-&gt;disk_cluster
op_ne
id|d_clu
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;FAT: cache corruption&quot;
l_string|&quot; (ino %lu)&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|fat_cache_lock
)paren
suffix:semicolon
id|fat_cache_inval_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* update LRU */
r_if
c_cond
(paren
id|last
op_eq
l_int|NULL
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|fat_cache_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|last-&gt;next
op_assign
id|walk-&gt;next
suffix:semicolon
id|walk-&gt;next
op_assign
id|fat_cache
suffix:semicolon
id|fat_cache
op_assign
id|walk
suffix:semicolon
macro_line|#ifdef DEBUG
id|list_cache
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|spin_unlock
c_func
(paren
op_amp
id|fat_cache_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|walk-&gt;sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
id|walk-&gt;start_cluster
op_assign
id|first
suffix:semicolon
id|walk-&gt;file_cluster
op_assign
id|f_clu
suffix:semicolon
id|walk-&gt;disk_cluster
op_assign
id|d_clu
suffix:semicolon
id|last-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|walk-&gt;next
op_assign
id|fat_cache
suffix:semicolon
id|fat_cache
op_assign
id|walk
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|fat_cache_lock
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|list_cache
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* Cache invalidation occurs rarely, thus the LRU chain is not updated. It&n;   fixes itself after a while. */
DECL|function|fat_cache_inval_inode
r_void
id|fat_cache_inval_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|fat_cache
op_star
id|walk
suffix:semicolon
r_int
id|first
op_assign
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_start
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|fat_cache_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|walk
op_assign
id|fat_cache
suffix:semicolon
id|walk
suffix:semicolon
id|walk
op_assign
id|walk-&gt;next
)paren
r_if
c_cond
(paren
id|walk-&gt;sb
op_eq
id|inode-&gt;i_sb
op_logical_and
id|walk-&gt;start_cluster
op_eq
id|first
)paren
id|walk-&gt;sb
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|fat_cache_lock
)paren
suffix:semicolon
)brace
DECL|function|fat_cache_inval_dev
r_void
id|fat_cache_inval_dev
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|fat_cache
op_star
id|walk
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|fat_cache_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|walk
op_assign
id|fat_cache
suffix:semicolon
id|walk
suffix:semicolon
id|walk
op_assign
id|walk-&gt;next
)paren
r_if
c_cond
(paren
id|walk-&gt;sb
op_eq
id|sb
)paren
id|walk-&gt;sb
op_assign
l_int|0
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|fat_cache_lock
)paren
suffix:semicolon
)brace
DECL|function|fat_get_cluster
r_static
r_int
id|fat_get_cluster
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|cluster
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_int
id|nr
comma
id|count
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|nr
op_assign
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_start
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cluster
)paren
r_return
id|nr
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|fat_cache_lookup
c_func
(paren
id|inode
comma
id|cluster
comma
op_amp
id|count
comma
op_amp
id|nr
)paren
suffix:semicolon
id|count
OL
id|cluster
suffix:semicolon
id|count
op_increment
)paren
(brace
id|nr
op_assign
id|fat_access
c_func
(paren
id|sb
comma
id|nr
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr
op_eq
id|FAT_ENT_EOF
)paren
(brace
id|fat_fs_panic
c_func
(paren
id|sb
comma
l_string|&quot;%s: request beyond EOF (ino %lu)&quot;
comma
id|__FUNCTION__
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|nr
op_eq
id|FAT_ENT_FREE
)paren
(brace
id|fat_fs_panic
c_func
(paren
id|sb
comma
l_string|&quot;%s: invalid cluster chain (ino %lu)&quot;
comma
id|__FUNCTION__
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|nr
OL
l_int|0
)paren
r_return
id|nr
suffix:semicolon
)brace
id|fat_cache_add
c_func
(paren
id|inode
comma
id|cluster
comma
id|nr
)paren
suffix:semicolon
r_return
id|nr
suffix:semicolon
)brace
DECL|function|fat_bmap
r_int
id|fat_bmap
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|sector_t
id|sector
comma
id|sector_t
op_star
id|phys
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
id|msdos_sb_info
op_star
id|sbi
op_assign
id|MSDOS_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
id|sector_t
id|last_block
suffix:semicolon
r_int
id|cluster
comma
id|offset
suffix:semicolon
op_star
id|phys
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sbi-&gt;fat_bits
op_ne
l_int|32
)paren
op_logical_and
(paren
id|inode-&gt;i_ino
op_eq
id|MSDOS_ROOT_INO
op_logical_or
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_and
op_logical_neg
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_start
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|sector
OL
(paren
id|sbi-&gt;dir_entries
op_rshift
id|sbi-&gt;dir_per_block_bits
)paren
)paren
op_star
id|phys
op_assign
id|sector
op_plus
id|sbi-&gt;dir_start
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|last_block
op_assign
(paren
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|mmu_private
op_plus
(paren
id|sb-&gt;s_blocksize
op_minus
l_int|1
)paren
)paren
op_rshift
id|sb-&gt;s_blocksize_bits
suffix:semicolon
r_if
c_cond
(paren
id|sector
op_ge
id|last_block
)paren
r_return
l_int|0
suffix:semicolon
id|cluster
op_assign
id|sector
op_rshift
(paren
id|sbi-&gt;cluster_bits
op_minus
id|sb-&gt;s_blocksize_bits
)paren
suffix:semicolon
id|offset
op_assign
id|sector
op_amp
(paren
id|sbi-&gt;cluster_size
op_minus
l_int|1
)paren
suffix:semicolon
id|cluster
op_assign
id|fat_get_cluster
c_func
(paren
id|inode
comma
id|cluster
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cluster
OL
l_int|0
)paren
r_return
id|cluster
suffix:semicolon
r_else
r_if
c_cond
(paren
id|cluster
)paren
(brace
op_star
id|phys
op_assign
(paren
(paren
id|sector_t
)paren
id|cluster
op_minus
l_int|2
)paren
op_star
id|sbi-&gt;cluster_size
op_plus
id|sbi-&gt;data_start
op_plus
id|offset
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Free all clusters after the skip&squot;th cluster. Doesn&squot;t use the cache,&n;   because this way we get an additional sanity check. */
DECL|function|fat_free
r_int
id|fat_free
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|skip
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_int
id|nr
comma
id|last
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|nr
op_assign
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_start
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|last
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|skip
op_decrement
)paren
(brace
id|last
op_assign
id|nr
suffix:semicolon
id|nr
op_assign
id|fat_access
c_func
(paren
id|sb
comma
id|nr
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr
op_eq
id|FAT_ENT_EOF
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|nr
op_eq
id|FAT_ENT_FREE
)paren
(brace
id|fat_fs_panic
c_func
(paren
id|sb
comma
l_string|&quot;%s: invalid cluster chain (ino %lu)&quot;
comma
id|__FUNCTION__
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|nr
OL
l_int|0
)paren
r_return
id|nr
suffix:semicolon
)brace
r_if
c_cond
(paren
id|last
)paren
(brace
id|fat_access
c_func
(paren
id|sb
comma
id|last
comma
id|FAT_ENT_EOF
)paren
suffix:semicolon
id|fat_cache_inval_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_else
(brace
id|fat_cache_inval_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_start
op_assign
l_int|0
suffix:semicolon
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_logstart
op_assign
l_int|0
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
id|lock_fat
c_func
(paren
id|sb
)paren
suffix:semicolon
r_while
c_loop
(paren
id|nr
op_ne
id|FAT_ENT_EOF
)paren
(brace
id|nr
op_assign
id|fat_access
c_func
(paren
id|sb
comma
id|nr
comma
id|FAT_ENT_FREE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr
OL
l_int|0
)paren
r_goto
id|error
suffix:semicolon
r_else
r_if
c_cond
(paren
id|nr
op_eq
id|FAT_ENT_FREE
)paren
(brace
id|fat_fs_panic
c_func
(paren
id|sb
comma
l_string|&quot;%s: deleting beyond EOF (ino %lu)&quot;
comma
id|__FUNCTION__
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|nr
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|free_clusters
op_ne
op_minus
l_int|1
)paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|free_clusters
op_increment
suffix:semicolon
id|inode-&gt;i_blocks
op_sub_assign
(paren
l_int|1
op_lshift
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cluster_bits
)paren
op_rshift
l_int|9
suffix:semicolon
)brace
id|fat_clusters_flush
c_func
(paren
id|sb
)paren
suffix:semicolon
id|nr
op_assign
l_int|0
suffix:semicolon
id|error
suffix:colon
id|unlock_fat
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
id|nr
suffix:semicolon
)brace
eof
