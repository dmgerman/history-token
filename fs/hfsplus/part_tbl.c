multiline_comment|/*&n; * linux/fs/hfs/part_tbl.c&n; *&n; * Copyright (C) 1996-1997  Paul H. Hargrove&n; * This file may be distributed under the terms of the GNU General Public License.&n; *&n; * Original code to handle the new style Mac partition table based on&n; * a patch contributed by Holger Schemel (aeglos@valinor.owl.de).&n; *&n; * In function preconditions the term &quot;valid&quot; applied to a pointer to&n; * a structure means that the pointer is non-NULL and the structure it&n; * points to has all fields initialized to consistent values.&n; *&n; */
macro_line|#include &quot;hfsplus_fs.h&quot;
multiline_comment|/* offsets to various blocks */
DECL|macro|HFS_DD_BLK
mdefine_line|#define HFS_DD_BLK&t;&t;0 /* Driver Descriptor block */
DECL|macro|HFS_PMAP_BLK
mdefine_line|#define HFS_PMAP_BLK&t;&t;1 /* First block of partition map */
DECL|macro|HFS_MDB_BLK
mdefine_line|#define HFS_MDB_BLK&t;&t;2 /* Block (w/i partition) of MDB */
multiline_comment|/* magic numbers for various disk blocks */
DECL|macro|HFS_DRVR_DESC_MAGIC
mdefine_line|#define HFS_DRVR_DESC_MAGIC&t;0x4552 /* &quot;ER&quot;: driver descriptor map */
DECL|macro|HFS_OLD_PMAP_MAGIC
mdefine_line|#define HFS_OLD_PMAP_MAGIC&t;0x5453 /* &quot;TS&quot;: old-type partition map */
DECL|macro|HFS_NEW_PMAP_MAGIC
mdefine_line|#define HFS_NEW_PMAP_MAGIC&t;0x504D /* &quot;PM&quot;: new-type partition map */
DECL|macro|HFS_SUPER_MAGIC
mdefine_line|#define HFS_SUPER_MAGIC&t;&t;0x4244 /* &quot;BD&quot;: HFS MDB (super block) */
DECL|macro|HFS_MFS_SUPER_MAGIC
mdefine_line|#define HFS_MFS_SUPER_MAGIC&t;0xD2D7 /* MFS MDB (super block) */
multiline_comment|/*&n; * The new style Mac partition map&n; *&n; * For each partition on the media there is a physical block (512-byte&n; * block) containing one of these structures.  These blocks are&n; * contiguous starting at block 1.&n; */
DECL|struct|new_pmap
r_struct
id|new_pmap
(brace
DECL|member|pmSig
id|__be16
id|pmSig
suffix:semicolon
multiline_comment|/* signature */
DECL|member|reSigPad
id|__be16
id|reSigPad
suffix:semicolon
multiline_comment|/* padding */
DECL|member|pmMapBlkCnt
id|__be32
id|pmMapBlkCnt
suffix:semicolon
multiline_comment|/* partition blocks count */
DECL|member|pmPyPartStart
id|__be32
id|pmPyPartStart
suffix:semicolon
multiline_comment|/* physical block start of partition */
DECL|member|pmPartBlkCnt
id|__be32
id|pmPartBlkCnt
suffix:semicolon
multiline_comment|/* physical block count of partition */
DECL|member|pmPartName
id|u8
id|pmPartName
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* (null terminated?) string&n;&t;&t;&t;&t;   giving the name of this&n;&t;&t;&t;&t;   partition */
DECL|member|pmPartType
id|u8
id|pmPartType
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* (null terminated?) string&n;&t;&t;&t;&t;   giving the type of this&n;&t;&t;&t;&t;   partition */
multiline_comment|/* a bunch more stuff we don&squot;t need */
DECL|variable|__packed
)brace
id|__packed
suffix:semicolon
multiline_comment|/*&n; * The old style Mac partition map&n; *&n; * The partition map consists for a 2-byte signature followed by an&n; * array of these structures.  The map is terminated with an all-zero&n; * one of these.&n; */
DECL|struct|old_pmap
r_struct
id|old_pmap
(brace
DECL|member|pdSig
id|__be16
id|pdSig
suffix:semicolon
multiline_comment|/* Signature bytes */
DECL|struct|old_pmap_entry
r_struct
id|old_pmap_entry
(brace
DECL|member|pdStart
id|__be32
id|pdStart
suffix:semicolon
DECL|member|pdSize
id|__be32
id|pdSize
suffix:semicolon
DECL|member|pdFSID
id|__be32
id|pdFSID
suffix:semicolon
DECL|member|pdEntry
)brace
id|pdEntry
(braket
l_int|42
)braket
suffix:semicolon
DECL|variable|__packed
)brace
id|__packed
suffix:semicolon
multiline_comment|/*&n; * hfs_part_find()&n; *&n; * Parse the partition map looking for the&n; * start and length of the &squot;part&squot;th HFS partition.&n; */
DECL|function|hfs_part_find
r_int
id|hfs_part_find
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|sector_t
op_star
id|part_start
comma
id|sector_t
op_star
id|part_size
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|__be16
op_star
id|data
suffix:semicolon
r_int
id|i
comma
id|size
comma
id|res
suffix:semicolon
id|res
op_assign
op_minus
id|ENOENT
suffix:semicolon
id|bh
op_assign
id|sb_bread512
c_func
(paren
id|sb
comma
op_star
id|part_start
op_plus
id|HFS_PMAP_BLK
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_switch
c_cond
(paren
id|be16_to_cpu
c_func
(paren
op_star
id|data
)paren
)paren
(brace
r_case
id|HFS_OLD_PMAP_MAGIC
suffix:colon
(brace
r_struct
id|old_pmap
op_star
id|pm
suffix:semicolon
r_struct
id|old_pmap_entry
op_star
id|p
suffix:semicolon
id|pm
op_assign
(paren
r_struct
id|old_pmap
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|p
op_assign
id|pm-&gt;pdEntry
suffix:semicolon
id|size
op_assign
l_int|42
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
id|size
suffix:semicolon
id|p
op_increment
comma
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;pdStart
op_logical_and
id|p-&gt;pdSize
op_logical_and
id|p-&gt;pdFSID
op_eq
id|cpu_to_be32
c_func
(paren
l_int|0x54465331
)paren
multiline_comment|/*&quot;TFS1&quot;*/
op_logical_and
(paren
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|part
OL
l_int|0
op_logical_or
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|part
op_eq
id|i
)paren
)paren
(brace
op_star
id|part_start
op_add_assign
id|be32_to_cpu
c_func
(paren
id|p-&gt;pdStart
)paren
suffix:semicolon
op_star
id|part_size
op_assign
id|be32_to_cpu
c_func
(paren
id|p-&gt;pdSize
)paren
suffix:semicolon
id|res
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
)brace
r_case
id|HFS_NEW_PMAP_MAGIC
suffix:colon
(brace
r_struct
id|new_pmap
op_star
id|pm
suffix:semicolon
id|pm
op_assign
(paren
r_struct
id|new_pmap
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|size
op_assign
id|be32_to_cpu
c_func
(paren
id|pm-&gt;pmMapBlkCnt
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
id|size
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|pm-&gt;pmPartType
comma
l_string|&quot;Apple_HFS&quot;
comma
l_int|9
)paren
op_logical_and
(paren
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|part
OL
l_int|0
op_logical_or
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|part
op_eq
id|i
)paren
)paren
(brace
op_star
id|part_start
op_add_assign
id|be32_to_cpu
c_func
(paren
id|pm-&gt;pmPyPartStart
)paren
suffix:semicolon
op_star
id|part_size
op_assign
id|be32_to_cpu
c_func
(paren
id|pm-&gt;pmPartBlkCnt
)paren
suffix:semicolon
id|res
op_assign
l_int|0
suffix:semicolon
r_break
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
id|sb_bread512
c_func
(paren
id|sb
comma
op_star
id|part_start
op_plus
id|HFS_PMAP_BLK
op_plus
op_increment
id|i
comma
id|pm
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|pm-&gt;pmSig
op_ne
id|cpu_to_be16
c_func
(paren
id|HFS_NEW_PMAP_MAGIC
)paren
)paren
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
eof
