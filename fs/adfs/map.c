multiline_comment|/*&n; *  linux/fs/adfs/map.c&n; *&n; *  Copyright (C) 1997-2002 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/adfs_fs.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;asm/unaligned.h&gt;
macro_line|#include &quot;adfs.h&quot;
multiline_comment|/*&n; * The ADFS map is basically a set of sectors.  Each sector is called a&n; * zone which contains a bitstream made up of variable sized fragments.&n; * Each bit refers to a set of bytes in the filesystem, defined by&n; * log2bpmb.  This may be larger or smaller than the sector size, but&n; * the overall size it describes will always be a round number of&n; * sectors.  A fragment id is always idlen bits long.&n; *&n; *  &lt; idlen &gt; &lt;       n        &gt; &lt;1&gt;&n; * +---------+-------//---------+---+&n; * | frag id |  0000....000000  | 1 |&n; * +---------+-------//---------+---+&n; *&n; * The physical disk space used by a fragment is taken from the start of&n; * the fragment id up to and including the &squot;1&squot; bit - ie, idlen + n + 1&n; * bits.&n; *&n; * A fragment id can be repeated multiple times in the whole map for&n; * large or fragmented files.  The first map zone a fragment starts in&n; * is given by fragment id / ids_per_zone - this allows objects to start&n; * from any zone on the disk.&n; *&n; * Free space is described by a linked list of fragments.  Each free&n; * fragment describes free space in the same way as the other fragments,&n; * however, the frag id specifies an offset (in map bits) from the end&n; * of this fragment to the start of the next free fragment.&n; *&n; * Objects stored on the disk are allocated object ids (we use these as&n; * our inode numbers.)  Object ids contain a fragment id and an optional&n; * offset.  This allows a directory fragment to contain small files&n; * associated with that directory.&n; */
multiline_comment|/*&n; * For the future...&n; */
r_static
id|DEFINE_RWLOCK
c_func
(paren
id|adfs_map_lock
)paren
suffix:semicolon
multiline_comment|/*&n; * This is fun.  We need to load up to 19 bits from the map at an&n; * arbitary bit alignment.  (We&squot;re limited to 19 bits by F+ version 2).&n; */
DECL|macro|GET_FRAG_ID
mdefine_line|#define GET_FRAG_ID(_map,_start,_idmask)&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned char *_m = _map + (_start &gt;&gt; 3);&t;&t;&bslash;&n;&t;&t;u32 _frag = get_unaligned((u32 *)_m);&t;&t;&t;&bslash;&n;&t;&t;_frag &gt;&gt;= (_start &amp; 7);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;_frag &amp; _idmask;&t;&t;&t;&t;&t;&bslash;&n;&t;})
multiline_comment|/*&n; * return the map bit offset of the fragment frag_id in the zone dm.&n; * Note that the loop is optimised for best asm code - look at the&n; * output of:&n; *  gcc -D__KERNEL__ -O2 -I../../include -o - -S map.c&n; */
r_static
r_int
DECL|function|lookup_zone
id|lookup_zone
c_func
(paren
r_const
r_struct
id|adfs_discmap
op_star
id|dm
comma
r_const
r_int
r_int
id|idlen
comma
r_const
r_int
r_int
id|frag_id
comma
r_int
r_int
op_star
id|offset
)paren
(brace
r_const
r_int
r_int
id|mapsize
op_assign
id|dm-&gt;dm_endbit
suffix:semicolon
r_const
id|u32
id|idmask
op_assign
(paren
l_int|1
op_lshift
id|idlen
)paren
op_minus
l_int|1
suffix:semicolon
r_int
r_char
op_star
id|map
op_assign
id|dm-&gt;dm_bh-&gt;b_data
op_plus
l_int|4
suffix:semicolon
r_int
r_int
id|start
op_assign
id|dm-&gt;dm_startbit
suffix:semicolon
r_int
r_int
id|mapptr
suffix:semicolon
id|u32
id|frag
suffix:semicolon
r_do
(brace
id|frag
op_assign
id|GET_FRAG_ID
c_func
(paren
id|map
comma
id|start
comma
id|idmask
)paren
suffix:semicolon
id|mapptr
op_assign
id|start
op_plus
id|idlen
suffix:semicolon
multiline_comment|/*&n;&t;&t; * find end of fragment&n;&t;&t; */
(brace
id|__le32
op_star
id|_map
op_assign
(paren
id|__le32
op_star
)paren
id|map
suffix:semicolon
id|u32
id|v
op_assign
id|le32_to_cpu
c_func
(paren
id|_map
(braket
id|mapptr
op_rshift
l_int|5
)braket
)paren
op_rshift
(paren
id|mapptr
op_amp
l_int|31
)paren
suffix:semicolon
r_while
c_loop
(paren
id|v
op_eq
l_int|0
)paren
(brace
id|mapptr
op_assign
(paren
id|mapptr
op_amp
op_complement
l_int|31
)paren
op_plus
l_int|32
suffix:semicolon
r_if
c_cond
(paren
id|mapptr
op_ge
id|mapsize
)paren
r_goto
id|error
suffix:semicolon
id|v
op_assign
id|le32_to_cpu
c_func
(paren
id|_map
(braket
id|mapptr
op_rshift
l_int|5
)braket
)paren
suffix:semicolon
)brace
id|mapptr
op_add_assign
l_int|1
op_plus
id|ffz
c_func
(paren
op_complement
id|v
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|frag
op_eq
id|frag_id
)paren
r_goto
id|found
suffix:semicolon
id|again
suffix:colon
id|start
op_assign
id|mapptr
suffix:semicolon
)brace
r_while
c_loop
(paren
id|mapptr
OL
id|mapsize
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
id|error
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;adfs: oversized fragment 0x%x at 0x%x-0x%x&bslash;n&quot;
comma
id|frag
comma
id|start
comma
id|mapptr
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
id|found
suffix:colon
(brace
r_int
id|length
op_assign
id|mapptr
op_minus
id|start
suffix:semicolon
r_if
c_cond
(paren
op_star
id|offset
op_ge
id|length
)paren
(brace
op_star
id|offset
op_sub_assign
id|length
suffix:semicolon
r_goto
id|again
suffix:semicolon
)brace
)brace
r_return
id|start
op_plus
op_star
id|offset
suffix:semicolon
)brace
multiline_comment|/*&n; * Scan the free space map, for this zone, calculating the total&n; * number of map bits in each free space fragment.&n; *&n; * Note: idmask is limited to 15 bits [3.2]&n; */
r_static
r_int
r_int
DECL|function|scan_free_map
id|scan_free_map
c_func
(paren
r_struct
id|adfs_sb_info
op_star
id|asb
comma
r_struct
id|adfs_discmap
op_star
id|dm
)paren
(brace
r_const
r_int
r_int
id|mapsize
op_assign
id|dm-&gt;dm_endbit
op_plus
l_int|32
suffix:semicolon
r_const
r_int
r_int
id|idlen
op_assign
id|asb-&gt;s_idlen
suffix:semicolon
r_const
r_int
r_int
id|frag_idlen
op_assign
id|idlen
op_le
l_int|15
ques
c_cond
id|idlen
suffix:colon
l_int|15
suffix:semicolon
r_const
id|u32
id|idmask
op_assign
(paren
l_int|1
op_lshift
id|frag_idlen
)paren
op_minus
l_int|1
suffix:semicolon
r_int
r_char
op_star
id|map
op_assign
id|dm-&gt;dm_bh-&gt;b_data
suffix:semicolon
r_int
r_int
id|start
op_assign
l_int|8
comma
id|mapptr
suffix:semicolon
id|u32
id|frag
suffix:semicolon
r_int
r_int
id|total
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * get fragment id&n;&t; */
id|frag
op_assign
id|GET_FRAG_ID
c_func
(paren
id|map
comma
id|start
comma
id|idmask
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If the freelink is null, then no free fragments&n;&t; * exist in this zone.&n;&t; */
r_if
c_cond
(paren
id|frag
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_do
(brace
id|start
op_add_assign
id|frag
suffix:semicolon
multiline_comment|/*&n;&t;&t; * get fragment id&n;&t;&t; */
id|frag
op_assign
id|GET_FRAG_ID
c_func
(paren
id|map
comma
id|start
comma
id|idmask
)paren
suffix:semicolon
id|mapptr
op_assign
id|start
op_plus
id|idlen
suffix:semicolon
multiline_comment|/*&n;&t;&t; * find end of fragment&n;&t;&t; */
(brace
id|__le32
op_star
id|_map
op_assign
(paren
id|__le32
op_star
)paren
id|map
suffix:semicolon
id|u32
id|v
op_assign
id|le32_to_cpu
c_func
(paren
id|_map
(braket
id|mapptr
op_rshift
l_int|5
)braket
)paren
op_rshift
(paren
id|mapptr
op_amp
l_int|31
)paren
suffix:semicolon
r_while
c_loop
(paren
id|v
op_eq
l_int|0
)paren
(brace
id|mapptr
op_assign
(paren
id|mapptr
op_amp
op_complement
l_int|31
)paren
op_plus
l_int|32
suffix:semicolon
r_if
c_cond
(paren
id|mapptr
op_ge
id|mapsize
)paren
r_goto
id|error
suffix:semicolon
id|v
op_assign
id|le32_to_cpu
c_func
(paren
id|_map
(braket
id|mapptr
op_rshift
l_int|5
)braket
)paren
suffix:semicolon
)brace
id|mapptr
op_add_assign
l_int|1
op_plus
id|ffz
c_func
(paren
op_complement
id|v
)paren
suffix:semicolon
)brace
id|total
op_add_assign
id|mapptr
op_minus
id|start
suffix:semicolon
)brace
r_while
c_loop
(paren
id|frag
op_ge
id|idlen
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|frag
op_ne
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;adfs: undersized free fragment&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|total
suffix:semicolon
id|error
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;adfs: oversized free fragment&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|scan_map
id|scan_map
c_func
(paren
r_struct
id|adfs_sb_info
op_star
id|asb
comma
r_int
r_int
id|zone
comma
r_const
r_int
r_int
id|frag_id
comma
r_int
r_int
id|mapoff
)paren
(brace
r_const
r_int
r_int
id|idlen
op_assign
id|asb-&gt;s_idlen
suffix:semicolon
r_struct
id|adfs_discmap
op_star
id|dm
comma
op_star
id|dm_end
suffix:semicolon
r_int
id|result
suffix:semicolon
id|dm
op_assign
id|asb-&gt;s_map
op_plus
id|zone
suffix:semicolon
id|zone
op_assign
id|asb-&gt;s_map_size
suffix:semicolon
id|dm_end
op_assign
id|asb-&gt;s_map
op_plus
id|zone
suffix:semicolon
r_do
(brace
id|result
op_assign
id|lookup_zone
c_func
(paren
id|dm
comma
id|idlen
comma
id|frag_id
comma
op_amp
id|mapoff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ne
op_minus
l_int|1
)paren
r_goto
id|found
suffix:semicolon
id|dm
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|dm
op_eq
id|dm_end
)paren
id|dm
op_assign
id|asb-&gt;s_map
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|zone
OG
l_int|0
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
id|found
suffix:colon
id|result
op_sub_assign
id|dm-&gt;dm_startbit
suffix:semicolon
id|result
op_add_assign
id|dm-&gt;dm_startblk
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * calculate the amount of free blocks in the map.&n; *&n; *              n=1&n; *  total_free = E(free_in_zone_n)&n; *              nzones&n; */
r_int
r_int
DECL|function|adfs_map_free
id|adfs_map_free
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|adfs_sb_info
op_star
id|asb
op_assign
id|ADFS_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
r_struct
id|adfs_discmap
op_star
id|dm
suffix:semicolon
r_int
r_int
id|total
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|zone
suffix:semicolon
id|dm
op_assign
id|asb-&gt;s_map
suffix:semicolon
id|zone
op_assign
id|asb-&gt;s_map_size
suffix:semicolon
r_do
(brace
id|total
op_add_assign
id|scan_free_map
c_func
(paren
id|asb
comma
id|dm
op_increment
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|zone
OG
l_int|0
)paren
suffix:semicolon
r_return
id|signed_asl
c_func
(paren
id|total
comma
id|asb-&gt;s_map2blk
)paren
suffix:semicolon
)brace
r_int
DECL|function|adfs_map_lookup
id|adfs_map_lookup
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|frag_id
comma
r_int
r_int
id|offset
)paren
(brace
r_struct
id|adfs_sb_info
op_star
id|asb
op_assign
id|ADFS_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
r_int
r_int
id|zone
comma
id|mapoff
suffix:semicolon
r_int
id|result
suffix:semicolon
multiline_comment|/*&n;&t; * map &amp; root fragment is special - it starts in the center of the&n;&t; * disk.  The other fragments start at zone (frag / ids_per_zone)&n;&t; */
r_if
c_cond
(paren
id|frag_id
op_eq
id|ADFS_ROOT_FRAG
)paren
id|zone
op_assign
id|asb-&gt;s_map_size
op_rshift
l_int|1
suffix:semicolon
r_else
id|zone
op_assign
id|frag_id
op_div
id|asb-&gt;s_ids_per_zone
suffix:semicolon
r_if
c_cond
(paren
id|zone
op_ge
id|asb-&gt;s_map_size
)paren
r_goto
id|bad_fragment
suffix:semicolon
multiline_comment|/* Convert sector offset to map offset */
id|mapoff
op_assign
id|signed_asl
c_func
(paren
id|offset
comma
op_minus
id|asb-&gt;s_map2blk
)paren
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|adfs_map_lock
)paren
suffix:semicolon
id|result
op_assign
id|scan_map
c_func
(paren
id|asb
comma
id|zone
comma
id|frag_id
comma
id|mapoff
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|adfs_map_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OG
l_int|0
)paren
(brace
r_int
r_int
id|secoff
suffix:semicolon
multiline_comment|/* Calculate sector offset into map block */
id|secoff
op_assign
id|offset
op_minus
id|signed_asl
c_func
(paren
id|mapoff
comma
id|asb-&gt;s_map2blk
)paren
suffix:semicolon
r_return
id|secoff
op_plus
id|signed_asl
c_func
(paren
id|result
comma
id|asb-&gt;s_map2blk
)paren
suffix:semicolon
)brace
id|adfs_error
c_func
(paren
id|sb
comma
l_string|&quot;fragment 0x%04x at offset %d not found in map&quot;
comma
id|frag_id
comma
id|offset
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|bad_fragment
suffix:colon
id|adfs_error
c_func
(paren
id|sb
comma
l_string|&quot;invalid fragment 0x%04x (zone = %d, max = %d)&quot;
comma
id|frag_id
comma
id|zone
comma
id|asb-&gt;s_map_size
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
