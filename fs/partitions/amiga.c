multiline_comment|/*&n; *  fs/partitions/amiga.c&n; *&n; *  Code extracted from drivers/block/genhd.c&n; *&n; *  Copyright (C) 1991-1998  Linus Torvalds&n; *  Re-organised Feb 1998 Russell King&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/affs_hardblocks.h&gt;
macro_line|#include &quot;check.h&quot;
macro_line|#include &quot;amiga.h&quot;
r_static
id|__inline__
id|u32
DECL|function|checksum_block
id|checksum_block
c_func
(paren
id|u32
op_star
id|m
comma
r_int
id|size
)paren
(brace
id|u32
id|sum
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|size
op_decrement
)paren
id|sum
op_add_assign
id|be32_to_cpu
c_func
(paren
op_star
id|m
op_increment
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
r_int
DECL|function|amiga_partition
id|amiga_partition
c_func
(paren
r_struct
id|parsed_partitions
op_star
id|state
comma
r_struct
id|block_device
op_star
id|bdev
)paren
(brace
id|Sector
id|sect
suffix:semicolon
r_int
r_char
op_star
id|data
suffix:semicolon
r_struct
id|RigidDiskBlock
op_star
id|rdb
suffix:semicolon
r_struct
id|PartitionBlock
op_star
id|pb
suffix:semicolon
r_int
id|start_sect
comma
id|nr_sects
comma
id|blk
comma
id|part
comma
id|res
op_assign
l_int|0
suffix:semicolon
r_int
id|slot
op_assign
l_int|1
suffix:semicolon
r_char
id|b
(braket
id|BDEVNAME_SIZE
)braket
suffix:semicolon
r_for
c_loop
(paren
id|blk
op_assign
l_int|0
suffix:semicolon
suffix:semicolon
id|blk
op_increment
comma
id|put_dev_sector
c_func
(paren
id|sect
)paren
)paren
(brace
r_if
c_cond
(paren
id|blk
op_eq
id|RDB_ALLOCATION_LIMIT
)paren
r_goto
id|rdb_done
suffix:semicolon
id|data
op_assign
id|read_dev_sector
c_func
(paren
id|bdev
comma
id|blk
comma
op_amp
id|sect
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
(brace
r_if
c_cond
(paren
id|warn_no_part
)paren
id|printk
c_func
(paren
l_string|&quot;Dev %s: unable to read RDB block %d&bslash;n&quot;
comma
id|bdevname
c_func
(paren
id|bdev
comma
id|b
)paren
comma
id|blk
)paren
suffix:semicolon
r_goto
id|rdb_done
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
(paren
id|u32
op_star
)paren
id|data
op_ne
id|cpu_to_be32
c_func
(paren
id|IDNAME_RIGIDDISK
)paren
)paren
r_continue
suffix:semicolon
id|rdb
op_assign
(paren
r_struct
id|RigidDiskBlock
op_star
)paren
id|data
suffix:semicolon
r_if
c_cond
(paren
id|checksum_block
c_func
(paren
(paren
id|u32
op_star
)paren
id|data
comma
id|be32_to_cpu
c_func
(paren
id|rdb-&gt;rdb_SummedLongs
)paren
op_amp
l_int|0x7F
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
multiline_comment|/* Try again with 0xdc..0xdf zeroed, Windows might have&n;&t;&t; * trashed it.&n;&t;&t; */
op_star
(paren
id|u32
op_star
)paren
(paren
id|data
op_plus
l_int|0xdc
)paren
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|checksum_block
c_func
(paren
(paren
id|u32
op_star
)paren
id|data
comma
id|be32_to_cpu
c_func
(paren
id|rdb-&gt;rdb_SummedLongs
)paren
op_amp
l_int|0x7F
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Warning: Trashed word at 0xd0 in block %d &quot;
l_string|&quot;ignored in checksum calculation&bslash;n&quot;
comma
id|blk
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Dev %s: RDB in block %d has bad checksum&bslash;n&quot;
comma
id|bdevname
c_func
(paren
id|bdev
comma
id|b
)paren
comma
id|blk
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; RDSK&quot;
)paren
suffix:semicolon
id|blk
op_assign
id|be32_to_cpu
c_func
(paren
id|rdb-&gt;rdb_PartitionList
)paren
suffix:semicolon
id|put_dev_sector
c_func
(paren
id|sect
)paren
suffix:semicolon
r_for
c_loop
(paren
id|part
op_assign
l_int|1
suffix:semicolon
id|blk
OG
l_int|0
op_logical_and
id|part
op_le
l_int|16
suffix:semicolon
id|part
op_increment
comma
id|put_dev_sector
c_func
(paren
id|sect
)paren
)paren
(brace
id|data
op_assign
id|read_dev_sector
c_func
(paren
id|bdev
comma
id|blk
comma
op_amp
id|sect
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
(brace
r_if
c_cond
(paren
id|warn_no_part
)paren
id|printk
c_func
(paren
l_string|&quot;Dev %s: unable to read partition block %d&bslash;n&quot;
comma
id|bdevname
c_func
(paren
id|bdev
comma
id|b
)paren
comma
id|blk
)paren
suffix:semicolon
r_goto
id|rdb_done
suffix:semicolon
)brace
id|pb
op_assign
(paren
r_struct
id|PartitionBlock
op_star
)paren
id|data
suffix:semicolon
id|blk
op_assign
id|be32_to_cpu
c_func
(paren
id|pb-&gt;pb_Next
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pb-&gt;pb_ID
op_ne
id|cpu_to_be32
c_func
(paren
id|IDNAME_PARTITION
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|checksum_block
c_func
(paren
(paren
id|u32
op_star
)paren
id|pb
comma
id|be32_to_cpu
c_func
(paren
id|pb-&gt;pb_SummedLongs
)paren
op_amp
l_int|0x7F
)paren
op_ne
l_int|0
)paren
r_continue
suffix:semicolon
multiline_comment|/* Tell Kernel about it */
id|nr_sects
op_assign
(paren
id|be32_to_cpu
c_func
(paren
id|pb-&gt;pb_Environment
(braket
l_int|10
)braket
)paren
op_plus
l_int|1
op_minus
id|be32_to_cpu
c_func
(paren
id|pb-&gt;pb_Environment
(braket
l_int|9
)braket
)paren
)paren
op_star
id|be32_to_cpu
c_func
(paren
id|pb-&gt;pb_Environment
(braket
l_int|3
)braket
)paren
op_star
id|be32_to_cpu
c_func
(paren
id|pb-&gt;pb_Environment
(braket
l_int|5
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nr_sects
)paren
r_continue
suffix:semicolon
id|start_sect
op_assign
id|be32_to_cpu
c_func
(paren
id|pb-&gt;pb_Environment
(braket
l_int|9
)braket
)paren
op_star
id|be32_to_cpu
c_func
(paren
id|pb-&gt;pb_Environment
(braket
l_int|3
)braket
)paren
op_star
id|be32_to_cpu
c_func
(paren
id|pb-&gt;pb_Environment
(braket
l_int|5
)braket
)paren
suffix:semicolon
id|put_partition
c_func
(paren
id|state
comma
id|slot
op_increment
comma
id|start_sect
comma
id|nr_sects
)paren
suffix:semicolon
id|res
op_assign
l_int|1
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|rdb_done
suffix:colon
r_return
id|res
suffix:semicolon
)brace
eof
