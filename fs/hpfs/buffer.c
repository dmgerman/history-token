multiline_comment|/*&n; *  linux/fs/hpfs/buffer.c&n; *&n; *  Mikulas Patocka (mikulas@artax.karlin.mff.cuni.cz), 1998-1999&n; *&n; *  general buffer i/o&n; */
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &quot;hpfs_fn.h&quot;
DECL|function|hpfs_lock_creation
r_void
id|hpfs_lock_creation
c_func
(paren
r_struct
id|super_block
op_star
id|s
)paren
(brace
macro_line|#ifdef DEBUG_LOCKS
id|printk
c_func
(paren
l_string|&quot;lock creation&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|down
c_func
(paren
op_amp
id|hpfs_sb
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|hpfs_creation_de
)paren
suffix:semicolon
)brace
DECL|function|hpfs_unlock_creation
r_void
id|hpfs_unlock_creation
c_func
(paren
r_struct
id|super_block
op_star
id|s
)paren
(brace
macro_line|#ifdef DEBUG_LOCKS
id|printk
c_func
(paren
l_string|&quot;unlock creation&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|up
c_func
(paren
op_amp
id|hpfs_sb
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|hpfs_creation_de
)paren
suffix:semicolon
)brace
DECL|function|hpfs_lock_iget
r_void
id|hpfs_lock_iget
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_int
id|mode
)paren
(brace
macro_line|#ifdef DEBUG_LOCKS
id|printk
c_func
(paren
l_string|&quot;lock iget&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_while
c_loop
(paren
id|hpfs_sb
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|sb_rd_inode
)paren
id|sleep_on
c_func
(paren
op_amp
id|hpfs_sb
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|sb_iget_q
)paren
suffix:semicolon
id|hpfs_sb
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|sb_rd_inode
op_assign
id|mode
suffix:semicolon
)brace
DECL|function|hpfs_unlock_iget
r_void
id|hpfs_unlock_iget
c_func
(paren
r_struct
id|super_block
op_star
id|s
)paren
(brace
macro_line|#ifdef DEBUG_LOCKS
id|printk
c_func
(paren
l_string|&quot;unlock iget&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|hpfs_sb
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|sb_rd_inode
op_assign
l_int|0
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|hpfs_sb
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|sb_iget_q
)paren
suffix:semicolon
)brace
DECL|function|hpfs_lock_inode
r_void
id|hpfs_lock_inode
c_func
(paren
r_struct
id|inode
op_star
id|i
)paren
(brace
r_if
c_cond
(paren
id|i
)paren
(brace
r_struct
id|hpfs_inode_info
op_star
id|hpfs_inode
op_assign
id|hpfs_i
c_func
(paren
id|i
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|hpfs_inode-&gt;i_sem
)paren
suffix:semicolon
)brace
)brace
DECL|function|hpfs_unlock_inode
r_void
id|hpfs_unlock_inode
c_func
(paren
r_struct
id|inode
op_star
id|i
)paren
(brace
r_if
c_cond
(paren
id|i
)paren
(brace
r_struct
id|hpfs_inode_info
op_star
id|hpfs_inode
op_assign
id|hpfs_i
c_func
(paren
id|i
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|hpfs_inode-&gt;i_sem
)paren
suffix:semicolon
)brace
)brace
DECL|function|hpfs_lock_2inodes
r_void
id|hpfs_lock_2inodes
c_func
(paren
r_struct
id|inode
op_star
id|i1
comma
r_struct
id|inode
op_star
id|i2
)paren
(brace
r_struct
id|hpfs_inode_info
op_star
id|hpfs_i1
op_assign
l_int|NULL
comma
op_star
id|hpfs_i2
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i1
)paren
(brace
r_if
c_cond
(paren
id|i2
)paren
(brace
id|hpfs_i2
op_assign
id|hpfs_i
c_func
(paren
id|i2
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|hpfs_i2-&gt;i_sem
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|i2
)paren
(brace
r_if
c_cond
(paren
id|i1
)paren
(brace
id|hpfs_i1
op_assign
id|hpfs_i
c_func
(paren
id|i1
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|hpfs_i1-&gt;i_sem
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i1-&gt;i_ino
OL
id|i2-&gt;i_ino
)paren
(brace
id|down
c_func
(paren
op_amp
id|hpfs_i1-&gt;i_sem
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|hpfs_i2-&gt;i_sem
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i1-&gt;i_ino
OG
id|i2-&gt;i_ino
)paren
(brace
id|down
c_func
(paren
op_amp
id|hpfs_i2-&gt;i_sem
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|hpfs_i1-&gt;i_sem
)paren
suffix:semicolon
)brace
r_else
id|down
c_func
(paren
op_amp
id|hpfs_i1-&gt;i_sem
)paren
suffix:semicolon
)brace
DECL|function|hpfs_unlock_2inodes
r_void
id|hpfs_unlock_2inodes
c_func
(paren
r_struct
id|inode
op_star
id|i1
comma
r_struct
id|inode
op_star
id|i2
)paren
(brace
r_struct
id|hpfs_inode_info
op_star
id|hpfs_i1
op_assign
l_int|NULL
comma
op_star
id|hpfs_i2
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i1
)paren
(brace
r_if
c_cond
(paren
id|i2
)paren
(brace
id|hpfs_i2
op_assign
id|hpfs_i
c_func
(paren
id|i2
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|hpfs_i2-&gt;i_sem
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|i2
)paren
(brace
r_if
c_cond
(paren
id|i1
)paren
(brace
id|hpfs_i1
op_assign
id|hpfs_i
c_func
(paren
id|i1
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|hpfs_i1-&gt;i_sem
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i1-&gt;i_ino
OL
id|i2-&gt;i_ino
)paren
(brace
id|up
c_func
(paren
op_amp
id|hpfs_i2-&gt;i_sem
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|hpfs_i1-&gt;i_sem
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i1-&gt;i_ino
OG
id|i2-&gt;i_ino
)paren
(brace
id|up
c_func
(paren
op_amp
id|hpfs_i1-&gt;i_sem
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|hpfs_i2-&gt;i_sem
)paren
suffix:semicolon
)brace
r_else
id|up
c_func
(paren
op_amp
id|hpfs_i1-&gt;i_sem
)paren
suffix:semicolon
)brace
DECL|function|hpfs_lock_3inodes
r_void
id|hpfs_lock_3inodes
c_func
(paren
r_struct
id|inode
op_star
id|i1
comma
r_struct
id|inode
op_star
id|i2
comma
r_struct
id|inode
op_star
id|i3
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|i1
)paren
(brace
id|hpfs_lock_2inodes
c_func
(paren
id|i2
comma
id|i3
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|i2
)paren
(brace
id|hpfs_lock_2inodes
c_func
(paren
id|i1
comma
id|i3
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|i3
)paren
(brace
id|hpfs_lock_2inodes
c_func
(paren
id|i1
comma
id|i2
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i1-&gt;i_ino
OL
id|i2-&gt;i_ino
op_logical_and
id|i1-&gt;i_ino
OL
id|i3-&gt;i_ino
)paren
(brace
r_struct
id|hpfs_inode_info
op_star
id|hpfs_i1
op_assign
id|hpfs_i
c_func
(paren
id|i1
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|hpfs_i1-&gt;i_sem
)paren
suffix:semicolon
id|hpfs_lock_2inodes
c_func
(paren
id|i2
comma
id|i3
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i2-&gt;i_ino
OL
id|i1-&gt;i_ino
op_logical_and
id|i2-&gt;i_ino
OL
id|i3-&gt;i_ino
)paren
(brace
r_struct
id|hpfs_inode_info
op_star
id|hpfs_i2
op_assign
id|hpfs_i
c_func
(paren
id|i2
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|hpfs_i2-&gt;i_sem
)paren
suffix:semicolon
id|hpfs_lock_2inodes
c_func
(paren
id|i1
comma
id|i3
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i3-&gt;i_ino
OL
id|i1-&gt;i_ino
op_logical_and
id|i3-&gt;i_ino
OL
id|i2-&gt;i_ino
)paren
(brace
r_struct
id|hpfs_inode_info
op_star
id|hpfs_i3
op_assign
id|hpfs_i
c_func
(paren
id|i3
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|hpfs_i3-&gt;i_sem
)paren
suffix:semicolon
id|hpfs_lock_2inodes
c_func
(paren
id|i1
comma
id|i2
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i1-&gt;i_ino
op_ne
id|i2-&gt;i_ino
)paren
id|hpfs_lock_2inodes
c_func
(paren
id|i1
comma
id|i2
)paren
suffix:semicolon
r_else
id|hpfs_lock_2inodes
c_func
(paren
id|i1
comma
id|i3
)paren
suffix:semicolon
)brace
DECL|function|hpfs_unlock_3inodes
r_void
id|hpfs_unlock_3inodes
c_func
(paren
r_struct
id|inode
op_star
id|i1
comma
r_struct
id|inode
op_star
id|i2
comma
r_struct
id|inode
op_star
id|i3
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|i1
)paren
(brace
id|hpfs_unlock_2inodes
c_func
(paren
id|i2
comma
id|i3
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|i2
)paren
(brace
id|hpfs_unlock_2inodes
c_func
(paren
id|i1
comma
id|i3
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|i3
)paren
(brace
id|hpfs_unlock_2inodes
c_func
(paren
id|i1
comma
id|i2
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i1-&gt;i_ino
OL
id|i2-&gt;i_ino
op_logical_and
id|i1-&gt;i_ino
OL
id|i3-&gt;i_ino
)paren
(brace
r_struct
id|hpfs_inode_info
op_star
id|hpfs_i1
op_assign
id|hpfs_i
c_func
(paren
id|i1
)paren
suffix:semicolon
id|hpfs_unlock_2inodes
c_func
(paren
id|i2
comma
id|i3
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|hpfs_i1-&gt;i_sem
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i2-&gt;i_ino
OL
id|i1-&gt;i_ino
op_logical_and
id|i2-&gt;i_ino
OL
id|i3-&gt;i_ino
)paren
(brace
r_struct
id|hpfs_inode_info
op_star
id|hpfs_i2
op_assign
id|hpfs_i
c_func
(paren
id|i2
)paren
suffix:semicolon
id|hpfs_unlock_2inodes
c_func
(paren
id|i1
comma
id|i3
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|hpfs_i2-&gt;i_sem
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i3-&gt;i_ino
OL
id|i1-&gt;i_ino
op_logical_and
id|i3-&gt;i_ino
OL
id|i2-&gt;i_ino
)paren
(brace
r_struct
id|hpfs_inode_info
op_star
id|hpfs_i3
op_assign
id|hpfs_i
c_func
(paren
id|i3
)paren
suffix:semicolon
id|hpfs_unlock_2inodes
c_func
(paren
id|i1
comma
id|i2
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|hpfs_i3-&gt;i_sem
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i1-&gt;i_ino
op_ne
id|i2-&gt;i_ino
)paren
id|hpfs_unlock_2inodes
c_func
(paren
id|i1
comma
id|i2
)paren
suffix:semicolon
r_else
id|hpfs_unlock_2inodes
c_func
(paren
id|i1
comma
id|i3
)paren
suffix:semicolon
)brace
multiline_comment|/* Map a sector into a buffer and return pointers to it and to the buffer. */
DECL|function|hpfs_map_sector
r_void
op_star
id|hpfs_map_sector
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_int
id|secno
comma
r_struct
id|buffer_head
op_star
op_star
id|bhp
comma
r_int
id|ahead
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
op_star
id|bhp
op_assign
id|bh
op_assign
id|sb_bread
c_func
(paren
id|s
comma
id|secno
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
op_ne
l_int|NULL
)paren
r_return
id|bh-&gt;b_data
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;HPFS: hpfs_map_sector: read error&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
multiline_comment|/* Like hpfs_map_sector but don&squot;t read anything */
DECL|function|hpfs_get_sector
r_void
op_star
id|hpfs_get_sector
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_int
id|secno
comma
r_struct
id|buffer_head
op_star
op_star
id|bhp
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
multiline_comment|/*return hpfs_map_sector(s, secno, bhp, 0);*/
r_if
c_cond
(paren
(paren
op_star
id|bhp
op_assign
id|bh
op_assign
id|sb_getblk
c_func
(paren
id|s
comma
id|secno
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
id|wait_on_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
id|set_buffer_uptodate
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|bh-&gt;b_data
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;HPFS: hpfs_get_sector: getblk failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
multiline_comment|/* Map 4 sectors into a 4buffer and return pointers to it and to the buffer. */
DECL|function|hpfs_map_4sectors
r_void
op_star
id|hpfs_map_4sectors
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_int
id|secno
comma
r_struct
id|quad_buffer_head
op_star
id|qbh
comma
r_int
id|ahead
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_char
op_star
id|data
suffix:semicolon
r_if
c_cond
(paren
id|secno
op_amp
l_int|3
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;HPFS: hpfs_map_4sectors: unaligned read&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|qbh-&gt;data
op_assign
id|data
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
c_func
(paren
l_int|2048
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;HPFS: hpfs_map_4sectors: out of memory&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|bail
suffix:semicolon
)brace
id|qbh-&gt;bh
(braket
l_int|0
)braket
op_assign
id|bh
op_assign
id|sb_bread
c_func
(paren
id|s
comma
id|secno
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_goto
id|bail0
suffix:semicolon
id|memcpy
c_func
(paren
id|data
comma
id|bh-&gt;b_data
comma
l_int|512
)paren
suffix:semicolon
id|qbh-&gt;bh
(braket
l_int|1
)braket
op_assign
id|bh
op_assign
id|sb_bread
c_func
(paren
id|s
comma
id|secno
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_goto
id|bail1
suffix:semicolon
id|memcpy
c_func
(paren
id|data
op_plus
l_int|512
comma
id|bh-&gt;b_data
comma
l_int|512
)paren
suffix:semicolon
id|qbh-&gt;bh
(braket
l_int|2
)braket
op_assign
id|bh
op_assign
id|sb_bread
c_func
(paren
id|s
comma
id|secno
op_plus
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_goto
id|bail2
suffix:semicolon
id|memcpy
c_func
(paren
id|data
op_plus
l_int|2
op_star
l_int|512
comma
id|bh-&gt;b_data
comma
l_int|512
)paren
suffix:semicolon
id|qbh-&gt;bh
(braket
l_int|3
)braket
op_assign
id|bh
op_assign
id|sb_bread
c_func
(paren
id|s
comma
id|secno
op_plus
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_goto
id|bail3
suffix:semicolon
id|memcpy
c_func
(paren
id|data
op_plus
l_int|3
op_star
l_int|512
comma
id|bh-&gt;b_data
comma
l_int|512
)paren
suffix:semicolon
r_return
id|data
suffix:semicolon
id|bail3
suffix:colon
id|brelse
c_func
(paren
id|qbh-&gt;bh
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|bail2
suffix:colon
id|brelse
c_func
(paren
id|qbh-&gt;bh
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|bail1
suffix:colon
id|brelse
c_func
(paren
id|qbh-&gt;bh
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|bail0
suffix:colon
id|kfree
c_func
(paren
id|data
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;HPFS: hpfs_map_4sectors: read error&bslash;n&quot;
)paren
suffix:semicolon
id|bail
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Don&squot;t read sectors */
DECL|function|hpfs_get_4sectors
r_void
op_star
id|hpfs_get_4sectors
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_int
id|secno
comma
r_struct
id|quad_buffer_head
op_star
id|qbh
)paren
(brace
r_if
c_cond
(paren
id|secno
op_amp
l_int|3
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;HPFS: hpfs_get_4sectors: unaligned read&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*return hpfs_map_4sectors(s, secno, qbh, 0);*/
r_if
c_cond
(paren
op_logical_neg
(paren
id|qbh-&gt;data
op_assign
id|kmalloc
c_func
(paren
l_int|2048
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;HPFS: hpfs_get_4sectors: out of memory&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|hpfs_get_sector
c_func
(paren
id|s
comma
id|secno
comma
op_amp
id|qbh-&gt;bh
(braket
l_int|0
)braket
)paren
)paren
)paren
r_goto
id|bail0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|hpfs_get_sector
c_func
(paren
id|s
comma
id|secno
op_plus
l_int|1
comma
op_amp
id|qbh-&gt;bh
(braket
l_int|1
)braket
)paren
)paren
)paren
r_goto
id|bail1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|hpfs_get_sector
c_func
(paren
id|s
comma
id|secno
op_plus
l_int|2
comma
op_amp
id|qbh-&gt;bh
(braket
l_int|2
)braket
)paren
)paren
)paren
r_goto
id|bail2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|hpfs_get_sector
c_func
(paren
id|s
comma
id|secno
op_plus
l_int|3
comma
op_amp
id|qbh-&gt;bh
(braket
l_int|3
)braket
)paren
)paren
)paren
r_goto
id|bail3
suffix:semicolon
id|memcpy
c_func
(paren
id|qbh-&gt;data
comma
id|qbh-&gt;bh
(braket
l_int|0
)braket
op_member_access_from_pointer
id|b_data
comma
l_int|512
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|qbh-&gt;data
op_plus
l_int|512
comma
id|qbh-&gt;bh
(braket
l_int|1
)braket
op_member_access_from_pointer
id|b_data
comma
l_int|512
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|qbh-&gt;data
op_plus
l_int|2
op_star
l_int|512
comma
id|qbh-&gt;bh
(braket
l_int|2
)braket
op_member_access_from_pointer
id|b_data
comma
l_int|512
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|qbh-&gt;data
op_plus
l_int|3
op_star
l_int|512
comma
id|qbh-&gt;bh
(braket
l_int|3
)braket
op_member_access_from_pointer
id|b_data
comma
l_int|512
)paren
suffix:semicolon
r_return
id|qbh-&gt;data
suffix:semicolon
id|bail3
suffix:colon
id|brelse
c_func
(paren
id|qbh-&gt;bh
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|bail2
suffix:colon
id|brelse
c_func
(paren
id|qbh-&gt;bh
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|bail1
suffix:colon
id|brelse
c_func
(paren
id|qbh-&gt;bh
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|bail0
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|hpfs_brelse4
r_void
id|hpfs_brelse4
c_func
(paren
r_struct
id|quad_buffer_head
op_star
id|qbh
)paren
(brace
id|brelse
c_func
(paren
id|qbh-&gt;bh
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|qbh-&gt;bh
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|qbh-&gt;bh
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|qbh-&gt;bh
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|qbh-&gt;data
)paren
suffix:semicolon
)brace
DECL|function|hpfs_mark_4buffers_dirty
r_void
id|hpfs_mark_4buffers_dirty
c_func
(paren
r_struct
id|quad_buffer_head
op_star
id|qbh
)paren
(brace
id|PRINTK
c_func
(paren
(paren
l_string|&quot;hpfs_mark_4buffers_dirty&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|qbh-&gt;bh
(braket
l_int|0
)braket
op_member_access_from_pointer
id|b_data
comma
id|qbh-&gt;data
comma
l_int|512
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|qbh-&gt;bh
(braket
l_int|1
)braket
op_member_access_from_pointer
id|b_data
comma
id|qbh-&gt;data
op_plus
l_int|512
comma
l_int|512
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|qbh-&gt;bh
(braket
l_int|2
)braket
op_member_access_from_pointer
id|b_data
comma
id|qbh-&gt;data
op_plus
l_int|2
op_star
l_int|512
comma
l_int|512
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|qbh-&gt;bh
(braket
l_int|3
)braket
op_member_access_from_pointer
id|b_data
comma
id|qbh-&gt;data
op_plus
l_int|3
op_star
l_int|512
comma
l_int|512
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|qbh-&gt;bh
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|qbh-&gt;bh
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|qbh-&gt;bh
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|qbh-&gt;bh
(braket
l_int|3
)braket
)paren
suffix:semicolon
)brace
eof
