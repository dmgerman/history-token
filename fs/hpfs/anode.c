multiline_comment|/*&n; *  linux/fs/hpfs/anode.c&n; *&n; *  Mikulas Patocka (mikulas@artax.karlin.mff.cuni.cz), 1998-1999&n; *&n; *  handling HPFS anode tree that contains file allocation info&n; */
macro_line|#include &quot;hpfs_fn.h&quot;
multiline_comment|/* Find a sector in allocation tree */
DECL|function|hpfs_bplus_lookup
id|secno
id|hpfs_bplus_lookup
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|bplus_header
op_star
id|btree
comma
r_int
id|sec
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
id|anode_secno
id|a
op_assign
op_minus
l_int|1
suffix:semicolon
r_struct
id|anode
op_star
id|anode
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|c1
comma
id|c2
op_assign
l_int|0
suffix:semicolon
id|go_down
suffix:colon
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
id|hpfs_stop_cycles
c_func
(paren
id|s
comma
id|a
comma
op_amp
id|c1
comma
op_amp
id|c2
comma
l_string|&quot;hpfs_bplus_lookup&quot;
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|btree-&gt;internal
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
id|btree-&gt;n_used_nodes
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|btree-&gt;u.internal
(braket
id|i
)braket
dot
id|file_secno
OG
id|sec
)paren
(brace
id|a
op_assign
id|btree-&gt;u.internal
(braket
id|i
)braket
dot
id|down
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|anode
op_assign
id|hpfs_map_anode
c_func
(paren
id|s
comma
id|a
comma
op_amp
id|bh
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|btree
op_assign
op_amp
id|anode-&gt;btree
suffix:semicolon
r_goto
id|go_down
suffix:semicolon
)brace
id|hpfs_error
c_func
(paren
id|s
comma
l_string|&quot;sector %08x not found in internal anode %08x&quot;
comma
id|sec
comma
id|a
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
op_minus
l_int|1
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
id|btree-&gt;n_used_nodes
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|btree-&gt;u.external
(braket
id|i
)braket
dot
id|file_secno
op_le
id|sec
op_logical_and
id|btree-&gt;u.external
(braket
id|i
)braket
dot
id|file_secno
op_plus
id|btree-&gt;u.external
(braket
id|i
)braket
dot
id|length
OG
id|sec
)paren
(brace
id|a
op_assign
id|btree-&gt;u.external
(braket
id|i
)braket
dot
id|disk_secno
op_plus
id|sec
op_minus
id|btree-&gt;u.external
(braket
id|i
)braket
dot
id|file_secno
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
id|sb_chk
)paren
r_if
c_cond
(paren
id|hpfs_chk_sectors
c_func
(paren
id|s
comma
id|a
comma
l_int|1
comma
l_string|&quot;data&quot;
)paren
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode
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
id|inode
)paren
suffix:semicolon
id|hpfs_inode-&gt;i_file_sec
op_assign
id|btree-&gt;u.external
(braket
id|i
)braket
dot
id|file_secno
suffix:semicolon
id|hpfs_inode-&gt;i_disk_sec
op_assign
id|btree-&gt;u.external
(braket
id|i
)braket
dot
id|disk_secno
suffix:semicolon
id|hpfs_inode-&gt;i_n_secs
op_assign
id|btree-&gt;u.external
(braket
id|i
)braket
dot
id|length
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|a
suffix:semicolon
)brace
id|hpfs_error
c_func
(paren
id|s
comma
l_string|&quot;sector %08x not found in external anode %08x&quot;
comma
id|sec
comma
id|a
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Add a sector to tree */
DECL|function|hpfs_add_sector_to_btree
id|secno
id|hpfs_add_sector_to_btree
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
id|secno
id|node
comma
r_int
id|fnod
comma
r_int
id|fsecno
)paren
(brace
r_struct
id|bplus_header
op_star
id|btree
suffix:semicolon
r_struct
id|anode
op_star
id|anode
op_assign
l_int|NULL
comma
op_star
id|ranode
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|fnode
op_star
id|fnode
suffix:semicolon
id|anode_secno
id|a
comma
id|na
op_assign
op_minus
l_int|1
comma
id|ra
comma
id|up
op_assign
op_minus
l_int|1
suffix:semicolon
id|secno
id|se
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
comma
op_star
id|bh1
comma
op_star
id|bh2
suffix:semicolon
r_int
id|n
suffix:semicolon
r_int
id|fs
suffix:semicolon
r_int
id|c1
comma
id|c2
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|fnod
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|fnode
op_assign
id|hpfs_map_fnode
c_func
(paren
id|s
comma
id|node
comma
op_amp
id|bh
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|btree
op_assign
op_amp
id|fnode-&gt;btree
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|anode
op_assign
id|hpfs_map_anode
c_func
(paren
id|s
comma
id|node
comma
op_amp
id|bh
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|btree
op_assign
op_amp
id|anode-&gt;btree
suffix:semicolon
)brace
id|a
op_assign
id|node
suffix:semicolon
id|go_down
suffix:colon
r_if
c_cond
(paren
(paren
id|n
op_assign
id|btree-&gt;n_used_nodes
op_minus
l_int|1
)paren
OL
op_minus
op_logical_neg
op_logical_neg
id|fnod
)paren
(brace
id|hpfs_error
c_func
(paren
id|s
comma
l_string|&quot;anode %08x has no entries&quot;
comma
id|a
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|btree-&gt;internal
)paren
(brace
id|a
op_assign
id|btree-&gt;u.internal
(braket
id|n
)braket
dot
id|down
suffix:semicolon
id|btree-&gt;u.internal
(braket
id|n
)braket
dot
id|file_secno
op_assign
op_minus
l_int|1
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
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
id|sb_chk
)paren
r_if
c_cond
(paren
id|hpfs_stop_cycles
c_func
(paren
id|s
comma
id|a
comma
op_amp
id|c1
comma
op_amp
id|c2
comma
l_string|&quot;hpfs_add_sector_to_btree #1&quot;
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|anode
op_assign
id|hpfs_map_anode
c_func
(paren
id|s
comma
id|a
comma
op_amp
id|bh
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|btree
op_assign
op_amp
id|anode-&gt;btree
suffix:semicolon
r_goto
id|go_down
suffix:semicolon
)brace
r_if
c_cond
(paren
id|n
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|btree-&gt;u.external
(braket
id|n
)braket
dot
id|file_secno
op_plus
id|btree-&gt;u.external
(braket
id|n
)braket
dot
id|length
op_ne
id|fsecno
)paren
(brace
id|hpfs_error
c_func
(paren
id|s
comma
l_string|&quot;allocated size %08x, trying to add sector %08x, %cnode %08x&quot;
comma
id|btree-&gt;u.external
(braket
id|n
)braket
dot
id|file_secno
op_plus
id|btree-&gt;u.external
(braket
id|n
)braket
dot
id|length
comma
id|fsecno
comma
id|fnod
ques
c_cond
l_char|&squot;f&squot;
suffix:colon
l_char|&squot;a&squot;
comma
id|node
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hpfs_alloc_if_possible
c_func
(paren
id|s
comma
id|se
op_assign
id|btree-&gt;u.external
(braket
id|n
)braket
dot
id|disk_secno
op_plus
id|btree-&gt;u.external
(braket
id|n
)braket
dot
id|length
)paren
)paren
(brace
id|btree-&gt;u.external
(braket
id|n
)braket
dot
id|length
op_increment
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|se
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|fsecno
)paren
(brace
id|hpfs_error
c_func
(paren
id|s
comma
l_string|&quot;empty file %08x, trying to add sector %08x&quot;
comma
id|node
comma
id|fsecno
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|se
op_assign
op_logical_neg
id|fnod
ques
c_cond
id|node
suffix:colon
(paren
id|node
op_plus
l_int|16384
)paren
op_amp
op_complement
l_int|16383
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|se
op_assign
id|hpfs_alloc_sector
c_func
(paren
id|s
comma
id|se
comma
l_int|1
comma
id|fsecno
op_star
id|ALLOC_M
OG
id|ALLOC_FWD_MAX
ques
c_cond
id|ALLOC_FWD_MAX
suffix:colon
id|fsecno
op_star
id|ALLOC_M
OL
id|ALLOC_FWD_MIN
ques
c_cond
id|ALLOC_FWD_MIN
suffix:colon
id|fsecno
op_star
id|ALLOC_M
comma
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
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|fs
op_assign
id|n
OL
l_int|0
ques
c_cond
l_int|0
suffix:colon
id|btree-&gt;u.external
(braket
id|n
)braket
dot
id|file_secno
op_plus
id|btree-&gt;u.external
(braket
id|n
)braket
dot
id|length
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|btree-&gt;n_free_nodes
)paren
(brace
id|up
op_assign
id|a
op_ne
id|node
ques
c_cond
id|anode-&gt;up
suffix:colon
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|anode
op_assign
id|hpfs_alloc_anode
c_func
(paren
id|s
comma
id|a
comma
op_amp
id|na
comma
op_amp
id|bh1
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
id|hpfs_free_sectors
c_func
(paren
id|s
comma
id|se
comma
l_int|1
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|a
op_eq
id|node
op_logical_and
id|fnod
)paren
(brace
id|anode-&gt;up
op_assign
id|node
suffix:semicolon
id|anode-&gt;btree.fnode_parent
op_assign
l_int|1
suffix:semicolon
id|anode-&gt;btree.n_used_nodes
op_assign
id|btree-&gt;n_used_nodes
suffix:semicolon
id|anode-&gt;btree.first_free
op_assign
id|btree-&gt;first_free
suffix:semicolon
id|anode-&gt;btree.n_free_nodes
op_assign
l_int|40
op_minus
id|anode-&gt;btree.n_used_nodes
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|anode-&gt;u
comma
op_amp
id|btree-&gt;u
comma
id|btree-&gt;n_used_nodes
op_star
l_int|12
)paren
suffix:semicolon
id|btree-&gt;internal
op_assign
l_int|1
suffix:semicolon
id|btree-&gt;n_free_nodes
op_assign
l_int|11
suffix:semicolon
id|btree-&gt;n_used_nodes
op_assign
l_int|1
suffix:semicolon
id|btree-&gt;first_free
op_assign
(paren
r_char
op_star
)paren
op_amp
(paren
id|btree-&gt;u.internal
(braket
l_int|1
)braket
)paren
op_minus
(paren
r_char
op_star
)paren
id|btree
suffix:semicolon
id|btree-&gt;u.internal
(braket
l_int|0
)braket
dot
id|file_secno
op_assign
op_minus
l_int|1
suffix:semicolon
id|btree-&gt;u.internal
(braket
l_int|0
)braket
dot
id|down
op_assign
id|na
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|ranode
op_assign
id|hpfs_alloc_anode
c_func
(paren
id|s
comma
multiline_comment|/*a*/
l_int|0
comma
op_amp
id|ra
comma
op_amp
id|bh2
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
id|brelse
c_func
(paren
id|bh1
)paren
suffix:semicolon
id|hpfs_free_sectors
c_func
(paren
id|s
comma
id|se
comma
l_int|1
)paren
suffix:semicolon
id|hpfs_free_sectors
c_func
(paren
id|s
comma
id|na
comma
l_int|1
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh
op_assign
id|bh1
suffix:semicolon
id|btree
op_assign
op_amp
id|anode-&gt;btree
suffix:semicolon
)brace
id|btree-&gt;n_free_nodes
op_decrement
suffix:semicolon
id|n
op_assign
id|btree-&gt;n_used_nodes
op_increment
suffix:semicolon
id|btree-&gt;first_free
op_add_assign
l_int|12
suffix:semicolon
id|btree-&gt;u.external
(braket
id|n
)braket
dot
id|disk_secno
op_assign
id|se
suffix:semicolon
id|btree-&gt;u.external
(braket
id|n
)braket
dot
id|file_secno
op_assign
id|fs
suffix:semicolon
id|btree-&gt;u.external
(braket
id|n
)braket
dot
id|length
op_assign
l_int|1
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|a
op_eq
id|node
op_logical_and
id|fnod
)paren
op_logical_or
id|na
op_eq
op_minus
l_int|1
)paren
r_return
id|se
suffix:semicolon
id|c2
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|up
op_ne
op_minus
l_int|1
)paren
(brace
r_struct
id|anode
op_star
id|new_anode
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
id|sb_chk
)paren
r_if
c_cond
(paren
id|hpfs_stop_cycles
c_func
(paren
id|s
comma
id|up
comma
op_amp
id|c1
comma
op_amp
id|c2
comma
l_string|&quot;hpfs_add_sector_to_btree #2&quot;
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|up
op_ne
id|node
op_logical_or
op_logical_neg
id|fnod
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|anode
op_assign
id|hpfs_map_anode
c_func
(paren
id|s
comma
id|up
comma
op_amp
id|bh
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|btree
op_assign
op_amp
id|anode-&gt;btree
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|fnode
op_assign
id|hpfs_map_fnode
c_func
(paren
id|s
comma
id|up
comma
op_amp
id|bh
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|btree
op_assign
op_amp
id|fnode-&gt;btree
suffix:semicolon
)brace
r_if
c_cond
(paren
id|btree-&gt;n_free_nodes
)paren
(brace
id|btree-&gt;n_free_nodes
op_decrement
suffix:semicolon
id|n
op_assign
id|btree-&gt;n_used_nodes
op_increment
suffix:semicolon
id|btree-&gt;first_free
op_add_assign
l_int|8
suffix:semicolon
id|btree-&gt;u.internal
(braket
id|n
)braket
dot
id|file_secno
op_assign
op_minus
l_int|1
suffix:semicolon
id|btree-&gt;u.internal
(braket
id|n
)braket
dot
id|down
op_assign
id|na
suffix:semicolon
id|btree-&gt;u.internal
(braket
id|n
op_minus
l_int|1
)braket
dot
id|file_secno
op_assign
id|fs
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh2
)paren
suffix:semicolon
id|hpfs_free_sectors
c_func
(paren
id|s
comma
id|ra
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|anode
op_assign
id|hpfs_map_anode
c_func
(paren
id|s
comma
id|na
comma
op_amp
id|bh
)paren
)paren
)paren
(brace
id|anode-&gt;up
op_assign
id|up
suffix:semicolon
id|anode-&gt;btree.fnode_parent
op_assign
id|up
op_eq
id|node
op_logical_and
id|fnod
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
r_return
id|se
suffix:semicolon
)brace
id|up
op_assign
id|up
op_ne
id|node
ques
c_cond
id|anode-&gt;up
suffix:colon
op_minus
l_int|1
suffix:semicolon
id|btree-&gt;u.internal
(braket
id|btree-&gt;n_used_nodes
op_minus
l_int|1
)braket
dot
id|file_secno
op_assign
multiline_comment|/*fs*/
op_minus
l_int|1
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|a
op_assign
id|na
suffix:semicolon
r_if
c_cond
(paren
(paren
id|new_anode
op_assign
id|hpfs_alloc_anode
c_func
(paren
id|s
comma
id|a
comma
op_amp
id|na
comma
op_amp
id|bh
)paren
)paren
)paren
(brace
id|anode
op_assign
id|new_anode
suffix:semicolon
multiline_comment|/*anode-&gt;up = up != -1 ? up : ra;*/
id|anode-&gt;btree.internal
op_assign
l_int|1
suffix:semicolon
id|anode-&gt;btree.n_used_nodes
op_assign
l_int|1
suffix:semicolon
id|anode-&gt;btree.n_free_nodes
op_assign
l_int|59
suffix:semicolon
id|anode-&gt;btree.first_free
op_assign
l_int|16
suffix:semicolon
id|anode-&gt;btree.u.internal
(braket
l_int|0
)braket
dot
id|down
op_assign
id|a
suffix:semicolon
id|anode-&gt;btree.u.internal
(braket
l_int|0
)braket
dot
id|file_secno
op_assign
op_minus
l_int|1
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|anode
op_assign
id|hpfs_map_anode
c_func
(paren
id|s
comma
id|a
comma
op_amp
id|bh
)paren
)paren
)paren
(brace
id|anode-&gt;up
op_assign
id|na
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
)brace
r_else
id|na
op_assign
id|a
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|anode
op_assign
id|hpfs_map_anode
c_func
(paren
id|s
comma
id|na
comma
op_amp
id|bh
)paren
)paren
)paren
(brace
id|anode-&gt;up
op_assign
id|node
suffix:semicolon
r_if
c_cond
(paren
id|fnod
)paren
id|anode-&gt;btree.fnode_parent
op_assign
l_int|1
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|fnod
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|anode
op_assign
id|hpfs_map_anode
c_func
(paren
id|s
comma
id|node
comma
op_amp
id|bh
)paren
)paren
)paren
(brace
id|brelse
c_func
(paren
id|bh2
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|btree
op_assign
op_amp
id|anode-&gt;btree
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|fnode
op_assign
id|hpfs_map_fnode
c_func
(paren
id|s
comma
id|node
comma
op_amp
id|bh
)paren
)paren
)paren
(brace
id|brelse
c_func
(paren
id|bh2
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|btree
op_assign
op_amp
id|fnode-&gt;btree
suffix:semicolon
)brace
id|ranode-&gt;up
op_assign
id|node
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|ranode-&gt;btree
comma
id|btree
comma
id|btree-&gt;first_free
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fnod
)paren
id|ranode-&gt;btree.fnode_parent
op_assign
l_int|1
suffix:semicolon
id|ranode-&gt;btree.n_free_nodes
op_assign
(paren
id|ranode-&gt;btree.internal
ques
c_cond
l_int|60
suffix:colon
l_int|40
)paren
op_minus
id|ranode-&gt;btree.n_used_nodes
suffix:semicolon
r_if
c_cond
(paren
id|ranode-&gt;btree.internal
)paren
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|ranode-&gt;btree.n_used_nodes
suffix:semicolon
id|n
op_increment
)paren
(brace
r_struct
id|anode
op_star
id|unode
suffix:semicolon
r_if
c_cond
(paren
(paren
id|unode
op_assign
id|hpfs_map_anode
c_func
(paren
id|s
comma
id|ranode-&gt;u.internal
(braket
id|n
)braket
dot
id|down
comma
op_amp
id|bh1
)paren
)paren
)paren
(brace
id|unode-&gt;up
op_assign
id|ra
suffix:semicolon
id|unode-&gt;btree.fnode_parent
op_assign
l_int|0
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh1
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh1
)paren
suffix:semicolon
)brace
)brace
id|btree-&gt;internal
op_assign
l_int|1
suffix:semicolon
id|btree-&gt;n_free_nodes
op_assign
id|fnod
ques
c_cond
l_int|10
suffix:colon
l_int|58
suffix:semicolon
id|btree-&gt;n_used_nodes
op_assign
l_int|2
suffix:semicolon
id|btree-&gt;first_free
op_assign
(paren
r_char
op_star
)paren
op_amp
id|btree-&gt;u.internal
(braket
l_int|2
)braket
op_minus
(paren
r_char
op_star
)paren
id|btree
suffix:semicolon
id|btree-&gt;u.internal
(braket
l_int|0
)braket
dot
id|file_secno
op_assign
id|fs
suffix:semicolon
id|btree-&gt;u.internal
(braket
l_int|0
)braket
dot
id|down
op_assign
id|ra
suffix:semicolon
id|btree-&gt;u.internal
(braket
l_int|1
)braket
dot
id|file_secno
op_assign
op_minus
l_int|1
suffix:semicolon
id|btree-&gt;u.internal
(braket
l_int|1
)braket
dot
id|down
op_assign
id|na
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh2
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh2
)paren
suffix:semicolon
r_return
id|se
suffix:semicolon
)brace
multiline_comment|/*&n; * Remove allocation tree. Recursion would look much nicer but&n; * I want to avoid it because it can cause stack overflow.&n; */
DECL|function|hpfs_remove_btree
r_void
id|hpfs_remove_btree
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_struct
id|bplus_header
op_star
id|btree
)paren
(brace
r_struct
id|bplus_header
op_star
id|btree1
op_assign
id|btree
suffix:semicolon
r_struct
id|anode
op_star
id|anode
op_assign
l_int|NULL
suffix:semicolon
id|anode_secno
id|ano
op_assign
l_int|0
comma
id|oano
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|level
op_assign
l_int|0
suffix:semicolon
r_int
id|pos
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|c1
comma
id|c2
op_assign
l_int|0
suffix:semicolon
r_int
id|d1
comma
id|d2
suffix:semicolon
id|go_down
suffix:colon
id|d2
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|btree1-&gt;internal
)paren
(brace
id|ano
op_assign
id|btree1-&gt;u.internal
(braket
id|pos
)braket
dot
id|down
suffix:semicolon
r_if
c_cond
(paren
id|level
)paren
id|brelse
c_func
(paren
id|bh
)paren
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
id|sb_chk
)paren
r_if
c_cond
(paren
id|hpfs_stop_cycles
c_func
(paren
id|s
comma
id|ano
comma
op_amp
id|d1
comma
op_amp
id|d2
comma
l_string|&quot;hpfs_remove_btree #1&quot;
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|anode
op_assign
id|hpfs_map_anode
c_func
(paren
id|s
comma
id|ano
comma
op_amp
id|bh
)paren
)paren
)paren
r_return
suffix:semicolon
id|btree1
op_assign
op_amp
id|anode-&gt;btree
suffix:semicolon
id|level
op_increment
suffix:semicolon
id|pos
op_assign
l_int|0
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
id|btree1-&gt;n_used_nodes
suffix:semicolon
id|i
op_increment
)paren
id|hpfs_free_sectors
c_func
(paren
id|s
comma
id|btree1-&gt;u.external
(braket
id|i
)braket
dot
id|disk_secno
comma
id|btree1-&gt;u.external
(braket
id|i
)braket
dot
id|length
)paren
suffix:semicolon
id|go_up
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|level
)paren
r_return
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
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
id|sb_chk
)paren
r_if
c_cond
(paren
id|hpfs_stop_cycles
c_func
(paren
id|s
comma
id|ano
comma
op_amp
id|c1
comma
op_amp
id|c2
comma
l_string|&quot;hpfs_remove_btree #2&quot;
)paren
)paren
r_return
suffix:semicolon
id|hpfs_free_sectors
c_func
(paren
id|s
comma
id|ano
comma
l_int|1
)paren
suffix:semicolon
id|oano
op_assign
id|ano
suffix:semicolon
id|ano
op_assign
id|anode-&gt;up
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|level
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|anode
op_assign
id|hpfs_map_anode
c_func
(paren
id|s
comma
id|ano
comma
op_amp
id|bh
)paren
)paren
)paren
r_return
suffix:semicolon
id|btree1
op_assign
op_amp
id|anode-&gt;btree
suffix:semicolon
)brace
r_else
id|btree1
op_assign
id|btree
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
id|btree1-&gt;n_used_nodes
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|btree1-&gt;u.internal
(braket
id|i
)braket
dot
id|down
op_eq
id|oano
)paren
(brace
r_if
c_cond
(paren
(paren
id|pos
op_assign
id|i
op_plus
l_int|1
)paren
OL
id|btree1-&gt;n_used_nodes
)paren
r_goto
id|go_down
suffix:semicolon
r_else
r_goto
id|go_up
suffix:semicolon
)brace
)brace
id|hpfs_error
c_func
(paren
id|s
comma
l_string|&quot;reference to anode %08x not found in anode %08x &quot;
l_string|&quot;(probably bad up pointer)&quot;
comma
id|oano
comma
id|level
ques
c_cond
id|ano
suffix:colon
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|level
)paren
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
multiline_comment|/* Just a wrapper around hpfs_bplus_lookup .. used for reading eas */
DECL|function|anode_lookup
r_static
id|secno
id|anode_lookup
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
id|anode_secno
id|a
comma
r_int
id|sec
)paren
(brace
r_struct
id|anode
op_star
id|anode
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|anode
op_assign
id|hpfs_map_anode
c_func
(paren
id|s
comma
id|a
comma
op_amp
id|bh
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
id|hpfs_bplus_lookup
c_func
(paren
id|s
comma
l_int|NULL
comma
op_amp
id|anode-&gt;btree
comma
id|sec
comma
id|bh
)paren
suffix:semicolon
)brace
DECL|function|hpfs_ea_read
r_int
id|hpfs_ea_read
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
id|secno
id|a
comma
r_int
id|ano
comma
r_int
id|pos
comma
r_int
id|len
comma
r_char
op_star
id|buf
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
id|secno
id|sec
suffix:semicolon
r_int
id|l
suffix:semicolon
r_while
c_loop
(paren
id|len
)paren
(brace
r_if
c_cond
(paren
id|ano
)paren
(brace
r_if
c_cond
(paren
(paren
id|sec
op_assign
id|anode_lookup
c_func
(paren
id|s
comma
id|a
comma
id|pos
op_rshift
l_int|9
)paren
)paren
op_eq
op_minus
l_int|1
)paren
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_else
id|sec
op_assign
id|a
op_plus
(paren
id|pos
op_rshift
l_int|9
)paren
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
id|sb_chk
)paren
r_if
c_cond
(paren
id|hpfs_chk_sectors
c_func
(paren
id|s
comma
id|sec
comma
l_int|1
comma
l_string|&quot;ea #1&quot;
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|data
op_assign
id|hpfs_map_sector
c_func
(paren
id|s
comma
id|sec
comma
op_amp
id|bh
comma
(paren
id|len
op_minus
l_int|1
)paren
op_rshift
l_int|9
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|l
op_assign
l_int|0x200
op_minus
(paren
id|pos
op_amp
l_int|0x1ff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|l
OG
id|len
)paren
id|l
op_assign
id|len
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|data
op_plus
(paren
id|pos
op_amp
l_int|0x1ff
)paren
comma
id|l
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|buf
op_add_assign
id|l
suffix:semicolon
id|pos
op_add_assign
id|l
suffix:semicolon
id|len
op_sub_assign
id|l
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hpfs_ea_write
r_int
id|hpfs_ea_write
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
id|secno
id|a
comma
r_int
id|ano
comma
r_int
id|pos
comma
r_int
id|len
comma
r_char
op_star
id|buf
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
id|secno
id|sec
suffix:semicolon
r_int
id|l
suffix:semicolon
r_while
c_loop
(paren
id|len
)paren
(brace
r_if
c_cond
(paren
id|ano
)paren
(brace
r_if
c_cond
(paren
(paren
id|sec
op_assign
id|anode_lookup
c_func
(paren
id|s
comma
id|a
comma
id|pos
op_rshift
l_int|9
)paren
)paren
op_eq
op_minus
l_int|1
)paren
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_else
id|sec
op_assign
id|a
op_plus
(paren
id|pos
op_rshift
l_int|9
)paren
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
id|sb_chk
)paren
r_if
c_cond
(paren
id|hpfs_chk_sectors
c_func
(paren
id|s
comma
id|sec
comma
l_int|1
comma
l_string|&quot;ea #2&quot;
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|data
op_assign
id|hpfs_map_sector
c_func
(paren
id|s
comma
id|sec
comma
op_amp
id|bh
comma
(paren
id|len
op_minus
l_int|1
)paren
op_rshift
l_int|9
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|l
op_assign
l_int|0x200
op_minus
(paren
id|pos
op_amp
l_int|0x1ff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|l
OG
id|len
)paren
id|l
op_assign
id|len
suffix:semicolon
id|memcpy
c_func
(paren
id|data
op_plus
(paren
id|pos
op_amp
l_int|0x1ff
)paren
comma
id|buf
comma
id|l
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|buf
op_add_assign
id|l
suffix:semicolon
id|pos
op_add_assign
id|l
suffix:semicolon
id|len
op_sub_assign
id|l
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hpfs_ea_remove
r_void
id|hpfs_ea_remove
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
id|secno
id|a
comma
r_int
id|ano
comma
r_int
id|len
)paren
(brace
r_struct
id|anode
op_star
id|anode
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_if
c_cond
(paren
id|ano
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|anode
op_assign
id|hpfs_map_anode
c_func
(paren
id|s
comma
id|a
comma
op_amp
id|bh
)paren
)paren
)paren
r_return
suffix:semicolon
id|hpfs_remove_btree
c_func
(paren
id|s
comma
op_amp
id|anode-&gt;btree
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|hpfs_free_sectors
c_func
(paren
id|s
comma
id|a
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
id|hpfs_free_sectors
c_func
(paren
id|s
comma
id|a
comma
(paren
id|len
op_plus
l_int|511
)paren
op_rshift
l_int|9
)paren
suffix:semicolon
)brace
multiline_comment|/* Truncate allocation tree. Doesn&squot;t join anodes - I hope it doesn&squot;t matter */
DECL|function|hpfs_truncate_btree
r_void
id|hpfs_truncate_btree
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
id|secno
id|f
comma
r_int
id|fno
comma
r_int
id|secs
)paren
(brace
r_struct
id|fnode
op_star
id|fnode
suffix:semicolon
r_struct
id|anode
op_star
id|anode
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|bplus_header
op_star
id|btree
suffix:semicolon
id|anode_secno
id|node
op_assign
id|f
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|nodes
suffix:semicolon
r_int
id|c1
comma
id|c2
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|fno
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|fnode
op_assign
id|hpfs_map_fnode
c_func
(paren
id|s
comma
id|f
comma
op_amp
id|bh
)paren
)paren
)paren
r_return
suffix:semicolon
id|btree
op_assign
op_amp
id|fnode-&gt;btree
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|anode
op_assign
id|hpfs_map_anode
c_func
(paren
id|s
comma
id|f
comma
op_amp
id|bh
)paren
)paren
)paren
r_return
suffix:semicolon
id|btree
op_assign
op_amp
id|anode-&gt;btree
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|secs
)paren
(brace
id|hpfs_remove_btree
c_func
(paren
id|s
comma
id|btree
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fno
)paren
(brace
id|btree-&gt;n_free_nodes
op_assign
l_int|8
suffix:semicolon
id|btree-&gt;n_used_nodes
op_assign
l_int|0
suffix:semicolon
id|btree-&gt;first_free
op_assign
l_int|8
suffix:semicolon
id|btree-&gt;internal
op_assign
l_int|0
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
r_else
id|hpfs_free_sectors
c_func
(paren
id|s
comma
id|f
comma
l_int|1
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_while
c_loop
(paren
id|btree-&gt;internal
)paren
(brace
id|nodes
op_assign
id|btree-&gt;n_used_nodes
op_plus
id|btree-&gt;n_free_nodes
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
id|btree-&gt;n_used_nodes
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|btree-&gt;u.internal
(braket
id|i
)braket
dot
id|file_secno
op_ge
id|secs
)paren
r_goto
id|f
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|hpfs_error
c_func
(paren
id|s
comma
l_string|&quot;internal btree %08x doesn&squot;t end with -1&quot;
comma
id|node
)paren
suffix:semicolon
r_return
suffix:semicolon
id|f
suffix:colon
r_for
c_loop
(paren
id|j
op_assign
id|i
op_plus
l_int|1
suffix:semicolon
id|j
OL
id|btree-&gt;n_used_nodes
suffix:semicolon
id|j
op_increment
)paren
id|hpfs_ea_remove
c_func
(paren
id|s
comma
id|btree-&gt;u.internal
(braket
id|j
)braket
dot
id|down
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
id|btree-&gt;n_used_nodes
op_assign
id|i
op_plus
l_int|1
suffix:semicolon
id|btree-&gt;n_free_nodes
op_assign
id|nodes
op_minus
id|btree-&gt;n_used_nodes
suffix:semicolon
id|btree-&gt;first_free
op_assign
l_int|8
op_plus
l_int|8
op_star
id|btree-&gt;n_used_nodes
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|btree-&gt;u.internal
(braket
id|i
)braket
dot
id|file_secno
op_eq
id|secs
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|node
op_assign
id|btree-&gt;u.internal
(braket
id|i
)braket
dot
id|down
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
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
id|sb_chk
)paren
r_if
c_cond
(paren
id|hpfs_stop_cycles
c_func
(paren
id|s
comma
id|node
comma
op_amp
id|c1
comma
op_amp
id|c2
comma
l_string|&quot;hpfs_truncate_btree&quot;
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|anode
op_assign
id|hpfs_map_anode
c_func
(paren
id|s
comma
id|node
comma
op_amp
id|bh
)paren
)paren
)paren
r_return
suffix:semicolon
id|btree
op_assign
op_amp
id|anode-&gt;btree
suffix:semicolon
)brace
id|nodes
op_assign
id|btree-&gt;n_used_nodes
op_plus
id|btree-&gt;n_free_nodes
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
id|btree-&gt;n_used_nodes
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|btree-&gt;u.external
(braket
id|i
)braket
dot
id|file_secno
op_plus
id|btree-&gt;u.external
(braket
id|i
)braket
dot
id|length
op_ge
id|secs
)paren
r_goto
id|ff
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
suffix:semicolon
id|ff
suffix:colon
r_if
c_cond
(paren
id|secs
op_le
id|btree-&gt;u.external
(braket
id|i
)braket
dot
id|file_secno
)paren
(brace
id|hpfs_error
c_func
(paren
id|s
comma
l_string|&quot;there is an allocation error in file %08x, sector %08x&quot;
comma
id|f
comma
id|secs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
id|i
op_decrement
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|btree-&gt;u.external
(braket
id|i
)braket
dot
id|file_secno
op_plus
id|btree-&gt;u.external
(braket
id|i
)braket
dot
id|length
OG
id|secs
)paren
(brace
id|hpfs_free_sectors
c_func
(paren
id|s
comma
id|btree-&gt;u.external
(braket
id|i
)braket
dot
id|disk_secno
op_plus
id|secs
op_minus
id|btree-&gt;u.external
(braket
id|i
)braket
dot
id|file_secno
comma
id|btree-&gt;u.external
(braket
id|i
)braket
dot
id|length
op_minus
id|secs
op_plus
id|btree-&gt;u.external
(braket
id|i
)braket
dot
id|file_secno
)paren
suffix:semicolon
multiline_comment|/* I hope gcc optimizes this :-) */
id|btree-&gt;u.external
(braket
id|i
)braket
dot
id|length
op_assign
id|secs
op_minus
id|btree-&gt;u.external
(braket
id|i
)braket
dot
id|file_secno
suffix:semicolon
)brace
r_for
c_loop
(paren
id|j
op_assign
id|i
op_plus
l_int|1
suffix:semicolon
id|j
OL
id|btree-&gt;n_used_nodes
suffix:semicolon
id|j
op_increment
)paren
id|hpfs_free_sectors
c_func
(paren
id|s
comma
id|btree-&gt;u.external
(braket
id|j
)braket
dot
id|disk_secno
comma
id|btree-&gt;u.external
(braket
id|j
)braket
dot
id|length
)paren
suffix:semicolon
id|btree-&gt;n_used_nodes
op_assign
id|i
op_plus
l_int|1
suffix:semicolon
id|btree-&gt;n_free_nodes
op_assign
id|nodes
op_minus
id|btree-&gt;n_used_nodes
suffix:semicolon
id|btree-&gt;first_free
op_assign
l_int|8
op_plus
l_int|12
op_star
id|btree-&gt;n_used_nodes
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
multiline_comment|/* Remove file or directory and it&squot;s eas - note that directory must&n;   be empty when this is called. */
DECL|function|hpfs_remove_fnode
r_void
id|hpfs_remove_fnode
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
id|fnode_secno
id|fno
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|fnode
op_star
id|fnode
suffix:semicolon
r_struct
id|extended_attribute
op_star
id|ea
suffix:semicolon
r_struct
id|extended_attribute
op_star
id|ea_end
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|fnode
op_assign
id|hpfs_map_fnode
c_func
(paren
id|s
comma
id|fno
comma
op_amp
id|bh
)paren
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fnode-&gt;dirflag
)paren
id|hpfs_remove_btree
c_func
(paren
id|s
comma
op_amp
id|fnode-&gt;btree
)paren
suffix:semicolon
r_else
id|hpfs_remove_dtree
c_func
(paren
id|s
comma
id|fnode-&gt;u.external
(braket
l_int|0
)braket
dot
id|disk_secno
)paren
suffix:semicolon
id|ea_end
op_assign
id|fnode_end_ea
c_func
(paren
id|fnode
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ea
op_assign
id|fnode_ea
c_func
(paren
id|fnode
)paren
suffix:semicolon
id|ea
OL
id|ea_end
suffix:semicolon
id|ea
op_assign
id|next_ea
c_func
(paren
id|ea
)paren
)paren
r_if
c_cond
(paren
id|ea-&gt;indirect
)paren
id|hpfs_ea_remove
c_func
(paren
id|s
comma
id|ea_sec
c_func
(paren
id|ea
)paren
comma
id|ea-&gt;anode
comma
id|ea_len
c_func
(paren
id|ea
)paren
)paren
suffix:semicolon
id|hpfs_ea_ext_remove
c_func
(paren
id|s
comma
id|fnode-&gt;ea_secno
comma
id|fnode-&gt;ea_anode
comma
id|fnode-&gt;ea_size_l
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|hpfs_free_sectors
c_func
(paren
id|s
comma
id|fno
comma
l_int|1
)paren
suffix:semicolon
)brace
eof
