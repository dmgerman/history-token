multiline_comment|/*&n; *  linux/fs/hpfs/alloc.c&n; *&n; *  Mikulas Patocka (mikulas@artax.karlin.mff.cuni.cz), 1998-1999&n; *&n; *  HPFS bitmap operations&n; */
macro_line|#include &quot;hpfs_fn.h&quot;
multiline_comment|/*&n; * Check if a sector is allocated in bitmap&n; * This is really slow. Turned on only if chk==2&n; */
DECL|function|chk_if_allocated
r_static
r_int
id|chk_if_allocated
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
id|secno
id|sec
comma
r_char
op_star
id|msg
)paren
(brace
r_struct
id|quad_buffer_head
id|qbh
suffix:semicolon
r_int
op_star
id|bmp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bmp
op_assign
id|hpfs_map_bitmap
c_func
(paren
id|s
comma
id|sec
op_rshift
l_int|14
comma
op_amp
id|qbh
comma
l_string|&quot;chk&quot;
)paren
)paren
)paren
r_goto
id|fail
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bmp
(braket
(paren
id|sec
op_amp
l_int|0x3fff
)paren
op_rshift
l_int|5
)braket
op_rshift
(paren
id|sec
op_amp
l_int|0x1f
)paren
)paren
op_amp
l_int|1
)paren
(brace
id|hpfs_error
c_func
(paren
id|s
comma
l_string|&quot;sector &squot;%s&squot; - %08x not allocated in bitmap&quot;
comma
id|msg
comma
id|sec
)paren
suffix:semicolon
r_goto
id|fail1
suffix:semicolon
)brace
id|hpfs_brelse4
c_func
(paren
op_amp
id|qbh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sec
op_ge
id|hpfs_sb
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|sb_dirband_start
op_logical_and
id|sec
OL
id|hpfs_sb
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|sb_dirband_start
op_plus
id|hpfs_sb
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|sb_dirband_size
)paren
(brace
r_int
id|ssec
op_assign
(paren
id|sec
op_minus
id|hpfs_sb
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|sb_dirband_start
)paren
op_div
l_int|4
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bmp
op_assign
id|hpfs_map_dnode_bitmap
c_func
(paren
id|s
comma
op_amp
id|qbh
)paren
)paren
)paren
r_goto
id|fail
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bmp
(braket
id|ssec
op_rshift
l_int|5
)braket
op_rshift
(paren
id|ssec
op_amp
l_int|0x1f
)paren
)paren
op_amp
l_int|1
)paren
(brace
id|hpfs_error
c_func
(paren
id|s
comma
l_string|&quot;sector &squot;%s&squot; - %08x not allocated in directory bitmap&quot;
comma
id|msg
comma
id|sec
)paren
suffix:semicolon
r_goto
id|fail1
suffix:semicolon
)brace
id|hpfs_brelse4
c_func
(paren
op_amp
id|qbh
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|fail1
suffix:colon
id|hpfs_brelse4
c_func
(paren
op_amp
id|qbh
)paren
suffix:semicolon
id|fail
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Check if sector(s) have proper number and additionally check if they&squot;re&n; * allocated in bitmap.&n; */
DECL|function|hpfs_chk_sectors
r_int
id|hpfs_chk_sectors
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
id|secno
id|start
comma
r_int
id|len
comma
r_char
op_star
id|msg
)paren
(brace
r_if
c_cond
(paren
id|start
op_plus
id|len
OL
id|start
op_logical_or
id|start
template_param
id|hpfs_sb
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|sb_fs_size
)paren
(brace
id|hpfs_error
c_func
(paren
id|s
comma
l_string|&quot;sector(s) &squot;%s&squot; badly placed at %08x&quot;
comma
id|msg
comma
id|start
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hpfs_sb
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|sb_chk
op_ge
l_int|2
)paren
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
id|len
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|chk_if_allocated
c_func
(paren
id|s
comma
id|start
op_plus
id|i
comma
id|msg
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alloc_in_bmp
r_static
id|secno
id|alloc_in_bmp
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
id|secno
id|near
comma
r_int
id|n
comma
r_int
id|forward
)paren
(brace
r_struct
id|quad_buffer_head
id|qbh
suffix:semicolon
r_int
op_star
id|bmp
suffix:semicolon
r_int
id|bs
op_assign
id|near
op_amp
op_complement
l_int|0x3fff
suffix:semicolon
r_int
id|nr
op_assign
(paren
id|near
op_amp
l_int|0x3fff
)paren
op_amp
op_complement
(paren
id|n
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/*unsigned mnr;*/
r_int
id|i
comma
id|q
suffix:semicolon
r_int
id|a
comma
id|b
suffix:semicolon
id|secno
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ne
l_int|1
op_logical_and
id|n
op_ne
l_int|4
)paren
(brace
id|hpfs_error
c_func
(paren
id|s
comma
l_string|&quot;Bad allocation size: %d&quot;
comma
id|n
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|lock_super
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bs
op_ne
op_complement
l_int|0x3fff
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|bmp
op_assign
id|hpfs_map_bitmap
c_func
(paren
id|s
comma
id|near
op_rshift
l_int|14
comma
op_amp
id|qbh
comma
l_string|&quot;aib&quot;
)paren
)paren
)paren
r_goto
id|uls
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|bmp
op_assign
id|hpfs_map_dnode_bitmap
c_func
(paren
id|s
comma
op_amp
id|qbh
)paren
)paren
)paren
r_goto
id|uls
suffix:semicolon
)brace
multiline_comment|/*if (!tstbits(bmp, nr + n, n + forward)) {&n;&t;&t;ret = bs + nr;&n;&t;&t;goto rt;&n;&t;}&n;&t;if (!tstbits(bmp, nr + 2*n, n + forward)) {&n;&t;&t;ret = bs + nr + n;&n;&t;&t;goto rt;&n;&t;}*/
id|q
op_assign
id|nr
op_plus
id|n
suffix:semicolon
id|b
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|a
op_assign
id|tstbits
c_func
(paren
id|bmp
comma
id|q
comma
id|n
op_plus
id|forward
)paren
)paren
)paren
(brace
id|q
op_add_assign
id|a
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ne
l_int|1
)paren
id|q
op_assign
(paren
(paren
id|q
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|n
op_minus
l_int|1
)paren
)paren
op_plus
id|n
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|b
)paren
(brace
r_if
c_cond
(paren
id|q
op_rshift
l_int|5
op_ne
id|nr
op_rshift
l_int|5
)paren
(brace
id|b
op_assign
l_int|1
suffix:semicolon
id|q
op_assign
id|nr
op_amp
l_int|0x1f
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|q
OG
id|nr
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|a
)paren
(brace
id|ret
op_assign
id|bs
op_plus
id|q
suffix:semicolon
r_goto
id|rt
suffix:semicolon
)brace
id|nr
op_rshift_assign
l_int|5
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|nr
op_plus
l_int|1
suffix:semicolon
id|i
op_ne
id|nr
suffix:semicolon
id|i
op_increment
comma
id|i
op_and_assign
l_int|0x1ff
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|bmp
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|n
op_plus
id|forward
op_ge
l_int|0x3f
op_logical_and
id|bmp
(braket
id|i
)braket
op_ne
op_minus
l_int|1
)paren
r_continue
suffix:semicolon
id|q
op_assign
id|i
op_lshift
l_int|5
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
l_int|0
)paren
(brace
r_int
id|k
op_assign
id|bmp
(braket
id|i
op_minus
l_int|1
)braket
suffix:semicolon
r_while
c_loop
(paren
id|k
op_amp
l_int|0x80000000
)paren
(brace
id|q
op_decrement
suffix:semicolon
id|k
op_lshift_assign
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|n
op_ne
l_int|1
)paren
id|q
op_assign
(paren
(paren
id|q
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|n
op_minus
l_int|1
)paren
)paren
op_plus
id|n
suffix:semicolon
r_while
c_loop
(paren
(paren
id|a
op_assign
id|tstbits
c_func
(paren
id|bmp
comma
id|q
comma
id|n
op_plus
id|forward
)paren
)paren
)paren
(brace
id|q
op_add_assign
id|a
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ne
l_int|1
)paren
id|q
op_assign
(paren
(paren
id|q
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|n
op_minus
l_int|1
)paren
)paren
op_plus
id|n
suffix:semicolon
r_if
c_cond
(paren
id|q
op_rshift
l_int|5
OG
id|i
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|a
)paren
(brace
id|ret
op_assign
id|bs
op_plus
id|q
suffix:semicolon
r_goto
id|rt
suffix:semicolon
)brace
)brace
id|rt
suffix:colon
r_if
c_cond
(paren
id|ret
)paren
(brace
r_if
c_cond
(paren
id|hpfs_sb
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|sb_chk
op_logical_and
(paren
(paren
id|ret
op_rshift
l_int|14
)paren
op_ne
(paren
id|bs
op_rshift
l_int|14
)paren
op_logical_or
(paren
id|bmp
(braket
(paren
id|ret
op_amp
l_int|0x3fff
)paren
op_rshift
l_int|5
)braket
op_or
op_complement
(paren
(paren
(paren
l_int|1
op_lshift
id|n
)paren
op_minus
l_int|1
)paren
op_lshift
(paren
id|ret
op_amp
l_int|0x1f
)paren
)paren
)paren
op_ne
l_int|0xffffffff
)paren
)paren
(brace
id|hpfs_error
c_func
(paren
id|s
comma
l_string|&quot;Allocation doesn&squot;t work! Wanted %d, allocated at %08x&quot;
comma
id|n
comma
id|ret
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|b
suffix:semicolon
)brace
id|bmp
(braket
(paren
id|ret
op_amp
l_int|0x3fff
)paren
op_rshift
l_int|5
)braket
op_and_assign
op_complement
(paren
(paren
(paren
l_int|1
op_lshift
id|n
)paren
op_minus
l_int|1
)paren
op_lshift
(paren
id|ret
op_amp
l_int|0x1f
)paren
)paren
suffix:semicolon
id|hpfs_mark_4buffers_dirty
c_func
(paren
op_amp
id|qbh
)paren
suffix:semicolon
)brace
id|b
suffix:colon
id|hpfs_brelse4
c_func
(paren
op_amp
id|qbh
)paren
suffix:semicolon
id|uls
suffix:colon
id|unlock_super
c_func
(paren
id|s
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Allocation strategy:&t;1) search place near the sector specified&n; *&t;&t;&t;2) search bitmap where free sectors last found&n; *&t;&t;&t;3) search all bitmaps&n; *&t;&t;&t;4) search all bitmaps ignoring number of pre-allocated&n; *&t;&t;&t;&t;sectors&n; */
DECL|function|hpfs_alloc_sector
id|secno
id|hpfs_alloc_sector
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
id|secno
id|near
comma
r_int
id|n
comma
r_int
id|forward
comma
r_int
id|lock
)paren
(brace
id|secno
id|sec
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|n_bmps
suffix:semicolon
r_struct
id|hpfs_sb_info
op_star
id|sbi
op_assign
id|hpfs_sb
c_func
(paren
id|s
)paren
suffix:semicolon
r_int
id|b
op_assign
id|sbi-&gt;sb_c_bitmap
suffix:semicolon
r_int
id|f_p
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|forward
OL
l_int|0
)paren
(brace
id|forward
op_assign
op_minus
id|forward
suffix:semicolon
id|f_p
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lock
)paren
id|hpfs_lock_creation
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|near
op_logical_and
id|near
OL
id|sbi-&gt;sb_fs_size
)paren
r_if
c_cond
(paren
(paren
id|sec
op_assign
id|alloc_in_bmp
c_func
(paren
id|s
comma
id|near
comma
id|n
comma
id|f_p
ques
c_cond
id|forward
suffix:colon
id|forward
op_div
l_int|4
)paren
)paren
)paren
r_goto
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|b
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
(paren
id|sec
op_assign
id|alloc_in_bmp
c_func
(paren
id|s
comma
id|b
op_lshift
l_int|14
comma
id|n
comma
id|f_p
ques
c_cond
id|forward
suffix:colon
id|forward
op_div
l_int|2
)paren
)paren
)paren
(brace
id|b
op_and_assign
l_int|0x0fffffff
suffix:semicolon
r_goto
id|ret
suffix:semicolon
)brace
r_if
c_cond
(paren
id|b
OG
l_int|0x10000000
)paren
r_if
c_cond
(paren
(paren
id|sec
op_assign
id|alloc_in_bmp
c_func
(paren
id|s
comma
(paren
id|b
op_amp
l_int|0xfffffff
)paren
op_lshift
l_int|14
comma
id|n
comma
id|f_p
ques
c_cond
id|forward
suffix:colon
l_int|0
)paren
)paren
)paren
r_goto
id|ret
suffix:semicolon
)brace
id|n_bmps
op_assign
(paren
id|sbi-&gt;sb_fs_size
op_plus
l_int|0x4000
op_minus
l_int|1
)paren
op_rshift
l_int|14
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
id|n_bmps
op_div
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|sec
op_assign
id|alloc_in_bmp
c_func
(paren
id|s
comma
(paren
id|n_bmps
op_div
l_int|2
op_plus
id|i
)paren
op_lshift
l_int|14
comma
id|n
comma
id|forward
)paren
)paren
)paren
(brace
id|sbi-&gt;sb_c_bitmap
op_assign
id|n_bmps
op_div
l_int|2
op_plus
id|i
suffix:semicolon
r_goto
id|ret
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|sec
op_assign
id|alloc_in_bmp
c_func
(paren
id|s
comma
(paren
id|n_bmps
op_div
l_int|2
op_minus
id|i
op_minus
l_int|1
)paren
op_lshift
l_int|14
comma
id|n
comma
id|forward
)paren
)paren
)paren
(brace
id|sbi-&gt;sb_c_bitmap
op_assign
id|n_bmps
op_div
l_int|2
op_minus
id|i
op_minus
l_int|1
suffix:semicolon
r_goto
id|ret
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|sec
op_assign
id|alloc_in_bmp
c_func
(paren
id|s
comma
(paren
id|n_bmps
op_minus
l_int|1
)paren
op_lshift
l_int|14
comma
id|n
comma
id|forward
)paren
)paren
)paren
(brace
id|sbi-&gt;sb_c_bitmap
op_assign
id|n_bmps
op_minus
l_int|1
suffix:semicolon
r_goto
id|ret
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|f_p
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|n_bmps
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
id|sec
op_assign
id|alloc_in_bmp
c_func
(paren
id|s
comma
id|i
op_lshift
l_int|14
comma
id|n
comma
l_int|0
)paren
)paren
)paren
(brace
id|sbi-&gt;sb_c_bitmap
op_assign
l_int|0x10000000
op_plus
id|i
suffix:semicolon
r_goto
id|ret
suffix:semicolon
)brace
)brace
id|sec
op_assign
l_int|0
suffix:semicolon
id|ret
suffix:colon
r_if
c_cond
(paren
id|sec
op_logical_and
id|f_p
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|forward
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|hpfs_alloc_if_possible_nolock
c_func
(paren
id|s
comma
id|sec
op_plus
id|i
op_plus
l_int|1
)paren
)paren
(brace
id|hpfs_error
c_func
(paren
id|s
comma
l_string|&quot;Prealloc doesn&squot;t work! Wanted %d, allocated at %08x, can&squot;t allocate %d&quot;
comma
id|forward
comma
id|sec
comma
id|i
)paren
suffix:semicolon
id|sec
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|lock
)paren
id|hpfs_unlock_creation
c_func
(paren
id|s
)paren
suffix:semicolon
r_return
id|sec
suffix:semicolon
)brace
DECL|function|alloc_in_dirband
r_static
id|secno
id|alloc_in_dirband
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
id|secno
id|near
comma
r_int
id|lock
)paren
(brace
r_int
id|nr
op_assign
id|near
suffix:semicolon
id|secno
id|sec
suffix:semicolon
r_struct
id|hpfs_sb_info
op_star
id|sbi
op_assign
id|hpfs_sb
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr
OL
id|sbi-&gt;sb_dirband_start
)paren
id|nr
op_assign
id|sbi-&gt;sb_dirband_start
suffix:semicolon
r_if
c_cond
(paren
id|nr
op_ge
id|sbi-&gt;sb_dirband_start
op_plus
id|sbi-&gt;sb_dirband_size
)paren
id|nr
op_assign
id|sbi-&gt;sb_dirband_start
op_plus
id|sbi-&gt;sb_dirband_size
op_minus
l_int|4
suffix:semicolon
id|nr
op_sub_assign
id|sbi-&gt;sb_dirband_start
suffix:semicolon
id|nr
op_rshift_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|lock
)paren
id|hpfs_lock_creation
c_func
(paren
id|s
)paren
suffix:semicolon
id|sec
op_assign
id|alloc_in_bmp
c_func
(paren
id|s
comma
(paren
op_complement
l_int|0x3fff
)paren
op_or
id|nr
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lock
)paren
id|hpfs_unlock_creation
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sec
)paren
r_return
l_int|0
suffix:semicolon
r_return
(paren
(paren
id|sec
op_amp
l_int|0x3fff
)paren
op_lshift
l_int|2
)paren
op_plus
id|sbi-&gt;sb_dirband_start
suffix:semicolon
)brace
multiline_comment|/* Alloc sector if it&squot;s free */
DECL|function|hpfs_alloc_if_possible_nolock
r_int
id|hpfs_alloc_if_possible_nolock
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
id|secno
id|sec
)paren
(brace
r_struct
id|quad_buffer_head
id|qbh
suffix:semicolon
r_int
op_star
id|bmp
suffix:semicolon
id|lock_super
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bmp
op_assign
id|hpfs_map_bitmap
c_func
(paren
id|s
comma
id|sec
op_rshift
l_int|14
comma
op_amp
id|qbh
comma
l_string|&quot;aip&quot;
)paren
)paren
)paren
r_goto
id|end
suffix:semicolon
r_if
c_cond
(paren
id|bmp
(braket
(paren
id|sec
op_amp
l_int|0x3fff
)paren
op_rshift
l_int|5
)braket
op_amp
(paren
l_int|1
op_lshift
(paren
id|sec
op_amp
l_int|0x1f
)paren
)paren
)paren
(brace
id|bmp
(braket
(paren
id|sec
op_amp
l_int|0x3fff
)paren
op_rshift
l_int|5
)braket
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|sec
op_amp
l_int|0x1f
)paren
)paren
suffix:semicolon
id|hpfs_mark_4buffers_dirty
c_func
(paren
op_amp
id|qbh
)paren
suffix:semicolon
id|hpfs_brelse4
c_func
(paren
op_amp
id|qbh
)paren
suffix:semicolon
id|unlock_super
c_func
(paren
id|s
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|hpfs_brelse4
c_func
(paren
op_amp
id|qbh
)paren
suffix:semicolon
id|end
suffix:colon
id|unlock_super
c_func
(paren
id|s
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hpfs_alloc_if_possible
r_int
id|hpfs_alloc_if_possible
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
id|secno
id|sec
)paren
(brace
r_int
id|r
suffix:semicolon
id|hpfs_lock_creation
c_func
(paren
id|s
)paren
suffix:semicolon
id|r
op_assign
id|hpfs_alloc_if_possible_nolock
c_func
(paren
id|s
comma
id|sec
)paren
suffix:semicolon
id|hpfs_unlock_creation
c_func
(paren
id|s
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
multiline_comment|/* Free sectors in bitmaps */
DECL|function|hpfs_free_sectors
r_void
id|hpfs_free_sectors
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
id|secno
id|sec
comma
r_int
id|n
)paren
(brace
r_struct
id|quad_buffer_head
id|qbh
suffix:semicolon
r_int
op_star
id|bmp
suffix:semicolon
multiline_comment|/*printk(&quot;2 - &quot;);*/
r_if
c_cond
(paren
op_logical_neg
id|n
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|sec
OL
l_int|0x12
)paren
(brace
id|hpfs_error
c_func
(paren
id|s
comma
l_string|&quot;Trying to free reserved sector %08x&quot;
comma
id|sec
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|lock_super
c_func
(paren
id|s
)paren
suffix:semicolon
id|new_map
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bmp
op_assign
id|hpfs_map_bitmap
c_func
(paren
id|s
comma
id|sec
op_rshift
l_int|14
comma
op_amp
id|qbh
comma
l_string|&quot;free&quot;
)paren
)paren
)paren
(brace
id|unlock_super
c_func
(paren
id|s
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|new_tst
suffix:colon
r_if
c_cond
(paren
(paren
id|bmp
(braket
(paren
id|sec
op_amp
l_int|0x3fff
)paren
op_rshift
l_int|5
)braket
op_rshift
(paren
id|sec
op_amp
l_int|0x1f
)paren
op_amp
l_int|1
)paren
)paren
(brace
id|hpfs_error
c_func
(paren
id|s
comma
l_string|&quot;sector %08x not allocated&quot;
comma
id|sec
)paren
suffix:semicolon
id|hpfs_brelse4
c_func
(paren
op_amp
id|qbh
)paren
suffix:semicolon
id|unlock_super
c_func
(paren
id|s
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|bmp
(braket
(paren
id|sec
op_amp
l_int|0x3fff
)paren
op_rshift
l_int|5
)braket
op_or_assign
l_int|1
op_lshift
(paren
id|sec
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|n
)paren
(brace
id|hpfs_mark_4buffers_dirty
c_func
(paren
op_amp
id|qbh
)paren
suffix:semicolon
id|hpfs_brelse4
c_func
(paren
op_amp
id|qbh
)paren
suffix:semicolon
id|unlock_super
c_func
(paren
id|s
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
op_increment
id|sec
op_amp
l_int|0x3fff
)paren
)paren
(brace
id|hpfs_mark_4buffers_dirty
c_func
(paren
op_amp
id|qbh
)paren
suffix:semicolon
id|hpfs_brelse4
c_func
(paren
op_amp
id|qbh
)paren
suffix:semicolon
r_goto
id|new_map
suffix:semicolon
)brace
r_goto
id|new_tst
suffix:semicolon
)brace
multiline_comment|/*&n; * Check if there are at least n free dnodes on the filesystem.&n; * Called before adding to dnode. If we run out of space while&n; * splitting dnodes, it would corrupt dnode tree.&n; */
DECL|function|hpfs_check_free_dnodes
r_int
id|hpfs_check_free_dnodes
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_int
id|n
)paren
(brace
r_int
id|n_bmps
op_assign
(paren
id|hpfs_sb
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|sb_fs_size
op_plus
l_int|0x4000
op_minus
l_int|1
)paren
op_rshift
l_int|14
suffix:semicolon
r_int
id|b
op_assign
id|hpfs_sb
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|sb_c_bitmap
op_amp
l_int|0x0fffffff
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_int
op_star
id|bmp
suffix:semicolon
r_struct
id|quad_buffer_head
id|qbh
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bmp
op_assign
id|hpfs_map_dnode_bitmap
c_func
(paren
id|s
comma
op_amp
id|qbh
)paren
)paren
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|512
suffix:semicolon
id|j
op_increment
)paren
(brace
r_int
id|k
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bmp
(braket
id|j
)braket
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
id|bmp
(braket
id|j
)braket
suffix:semicolon
id|k
suffix:semicolon
id|k
op_rshift_assign
l_int|1
)paren
r_if
c_cond
(paren
id|k
op_amp
l_int|1
)paren
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|n
)paren
(brace
id|hpfs_brelse4
c_func
(paren
op_amp
id|qbh
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
)brace
id|hpfs_brelse4
c_func
(paren
op_amp
id|qbh
)paren
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|hpfs_sb
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|sb_c_bitmap
op_ne
op_minus
l_int|1
)paren
(brace
id|bmp
op_assign
id|hpfs_map_bitmap
c_func
(paren
id|s
comma
id|b
comma
op_amp
id|qbh
comma
l_string|&quot;chkdn1&quot;
)paren
suffix:semicolon
r_goto
id|chk_bmp
suffix:semicolon
)brace
id|chk_next
suffix:colon
r_if
c_cond
(paren
id|i
op_eq
id|b
)paren
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|n_bmps
)paren
r_return
l_int|1
suffix:semicolon
id|bmp
op_assign
id|hpfs_map_bitmap
c_func
(paren
id|s
comma
id|i
comma
op_amp
id|qbh
comma
l_string|&quot;chkdn2&quot;
)paren
suffix:semicolon
id|chk_bmp
suffix:colon
r_if
c_cond
(paren
id|bmp
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|512
suffix:semicolon
id|j
op_increment
)paren
(brace
r_int
id|k
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bmp
(braket
id|j
)braket
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0xf
suffix:semicolon
id|k
suffix:semicolon
id|k
op_lshift_assign
l_int|4
)paren
r_if
c_cond
(paren
(paren
id|bmp
(braket
id|j
)braket
op_amp
id|k
)paren
op_eq
id|k
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|n
)paren
(brace
id|hpfs_brelse4
c_func
(paren
op_amp
id|qbh
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
)brace
id|hpfs_brelse4
c_func
(paren
op_amp
id|qbh
)paren
suffix:semicolon
)brace
id|i
op_increment
suffix:semicolon
r_goto
id|chk_next
suffix:semicolon
)brace
DECL|function|hpfs_free_dnode
r_void
id|hpfs_free_dnode
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
id|dnode_secno
id|dno
)paren
(brace
r_if
c_cond
(paren
id|hpfs_sb
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|sb_chk
)paren
r_if
c_cond
(paren
id|dno
op_amp
l_int|3
)paren
(brace
id|hpfs_error
c_func
(paren
id|s
comma
l_string|&quot;hpfs_free_dnode: dnode %08x not aligned&quot;
comma
id|dno
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dno
OL
id|hpfs_sb
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|sb_dirband_start
op_logical_or
id|dno
op_ge
id|hpfs_sb
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|sb_dirband_start
op_plus
id|hpfs_sb
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|sb_dirband_size
)paren
(brace
id|hpfs_free_sectors
c_func
(paren
id|s
comma
id|dno
comma
l_int|4
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|quad_buffer_head
id|qbh
suffix:semicolon
r_int
op_star
id|bmp
suffix:semicolon
r_int
id|ssec
op_assign
(paren
id|dno
op_minus
id|hpfs_sb
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|sb_dirband_start
)paren
op_div
l_int|4
suffix:semicolon
id|lock_super
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bmp
op_assign
id|hpfs_map_dnode_bitmap
c_func
(paren
id|s
comma
op_amp
id|qbh
)paren
)paren
)paren
(brace
id|unlock_super
c_func
(paren
id|s
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|bmp
(braket
id|ssec
op_rshift
l_int|5
)braket
op_or_assign
l_int|1
op_lshift
(paren
id|ssec
op_amp
l_int|0x1f
)paren
suffix:semicolon
id|hpfs_mark_4buffers_dirty
c_func
(paren
op_amp
id|qbh
)paren
suffix:semicolon
id|hpfs_brelse4
c_func
(paren
op_amp
id|qbh
)paren
suffix:semicolon
id|unlock_super
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
)brace
DECL|function|hpfs_alloc_dnode
r_struct
id|dnode
op_star
id|hpfs_alloc_dnode
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
id|secno
id|near
comma
id|dnode_secno
op_star
id|dno
comma
r_struct
id|quad_buffer_head
op_star
id|qbh
comma
r_int
id|lock
)paren
(brace
r_struct
id|dnode
op_star
id|d
suffix:semicolon
r_if
c_cond
(paren
id|hpfs_count_one_bitmap
c_func
(paren
id|s
comma
id|hpfs_sb
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|sb_dmap
)paren
OG
id|FREE_DNODES_ADD
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|dno
op_assign
id|alloc_in_dirband
c_func
(paren
id|s
comma
id|near
comma
id|lock
)paren
)paren
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|dno
op_assign
id|hpfs_alloc_sector
c_func
(paren
id|s
comma
id|near
comma
l_int|4
comma
l_int|0
comma
id|lock
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|dno
op_assign
id|hpfs_alloc_sector
c_func
(paren
id|s
comma
id|near
comma
l_int|4
comma
l_int|0
comma
id|lock
)paren
)paren
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|dno
op_assign
id|alloc_in_dirband
c_func
(paren
id|s
comma
id|near
comma
id|lock
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|d
op_assign
id|hpfs_get_4sectors
c_func
(paren
id|s
comma
op_star
id|dno
comma
id|qbh
)paren
)paren
)paren
(brace
id|hpfs_free_dnode
c_func
(paren
id|s
comma
op_star
id|dno
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|d
comma
l_int|0
comma
l_int|2048
)paren
suffix:semicolon
id|d-&gt;magic
op_assign
id|DNODE_MAGIC
suffix:semicolon
id|d-&gt;first_free
op_assign
l_int|52
suffix:semicolon
id|d-&gt;dirent
(braket
l_int|0
)braket
op_assign
l_int|32
suffix:semicolon
id|d-&gt;dirent
(braket
l_int|2
)braket
op_assign
l_int|8
suffix:semicolon
id|d-&gt;dirent
(braket
l_int|30
)braket
op_assign
l_int|1
suffix:semicolon
id|d-&gt;dirent
(braket
l_int|31
)braket
op_assign
l_int|255
suffix:semicolon
id|d-&gt;self
op_assign
op_star
id|dno
suffix:semicolon
r_return
id|d
suffix:semicolon
)brace
DECL|function|hpfs_alloc_fnode
r_struct
id|fnode
op_star
id|hpfs_alloc_fnode
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
id|secno
id|near
comma
id|fnode_secno
op_star
id|fno
comma
r_struct
id|buffer_head
op_star
op_star
id|bh
)paren
(brace
r_struct
id|fnode
op_star
id|f
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|fno
op_assign
id|hpfs_alloc_sector
c_func
(paren
id|s
comma
id|near
comma
l_int|1
comma
id|FNODE_ALLOC_FWD
comma
l_int|1
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|f
op_assign
id|hpfs_get_sector
c_func
(paren
id|s
comma
op_star
id|fno
comma
id|bh
)paren
)paren
)paren
(brace
id|hpfs_free_sectors
c_func
(paren
id|s
comma
op_star
id|fno
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|f
comma
l_int|0
comma
l_int|512
)paren
suffix:semicolon
id|f-&gt;magic
op_assign
id|FNODE_MAGIC
suffix:semicolon
id|f-&gt;ea_offs
op_assign
l_int|0xc4
suffix:semicolon
id|f-&gt;btree.n_free_nodes
op_assign
l_int|8
suffix:semicolon
id|f-&gt;btree.first_free
op_assign
l_int|8
suffix:semicolon
r_return
id|f
suffix:semicolon
)brace
DECL|function|hpfs_alloc_anode
r_struct
id|anode
op_star
id|hpfs_alloc_anode
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
id|secno
id|near
comma
id|anode_secno
op_star
id|ano
comma
r_struct
id|buffer_head
op_star
op_star
id|bh
)paren
(brace
r_struct
id|anode
op_star
id|a
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|ano
op_assign
id|hpfs_alloc_sector
c_func
(paren
id|s
comma
id|near
comma
l_int|1
comma
id|ANODE_ALLOC_FWD
comma
l_int|1
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|a
op_assign
id|hpfs_get_sector
c_func
(paren
id|s
comma
op_star
id|ano
comma
id|bh
)paren
)paren
)paren
(brace
id|hpfs_free_sectors
c_func
(paren
id|s
comma
op_star
id|ano
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|a
comma
l_int|0
comma
l_int|512
)paren
suffix:semicolon
id|a-&gt;magic
op_assign
id|ANODE_MAGIC
suffix:semicolon
id|a-&gt;self
op_assign
op_star
id|ano
suffix:semicolon
id|a-&gt;btree.n_free_nodes
op_assign
l_int|40
suffix:semicolon
id|a-&gt;btree.n_used_nodes
op_assign
l_int|0
suffix:semicolon
id|a-&gt;btree.first_free
op_assign
l_int|8
suffix:semicolon
r_return
id|a
suffix:semicolon
)brace
eof
