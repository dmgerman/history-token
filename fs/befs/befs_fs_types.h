multiline_comment|/*&n; * include/linux/befs_fs_types.h&n; *&n; * Copyright (C) 2001 Will Dyson (will@cs.earlham.edu)&n; *&n; *&n; *&n; * from linux/include/linux/befs_fs.h&n; *&n; * Copyright (C) 1999 Makoto Kato (m_kato@ga2.so-net.ne.jp)&n; *&n; */
macro_line|#ifndef _LINUX_BEFS_FS_TYPES
DECL|macro|_LINUX_BEFS_FS_TYPES
mdefine_line|#define _LINUX_BEFS_FS_TYPES
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#endif /*__KERNEL__*/
DECL|macro|PACKED
mdefine_line|#define PACKED __attribute__ ((__packed__))
multiline_comment|/*&n; * Max name lengths of BFS&n; */
DECL|macro|BEFS_NAME_LEN
mdefine_line|#define BEFS_NAME_LEN 255
DECL|macro|BEFS_SYMLINK_LEN
mdefine_line|#define BEFS_SYMLINK_LEN 144
DECL|macro|BEFS_NUM_DIRECT_BLOCKS
mdefine_line|#define BEFS_NUM_DIRECT_BLOCKS 12
DECL|macro|B_OS_NAME_LENGTH
mdefine_line|#define B_OS_NAME_LENGTH 32
multiline_comment|/* The datastream blocks mapped by the double-indirect&n; * block are always 4 fs blocks long.&n; * This eliminates the need for linear searches among&n; * the potentially huge number of indirect blocks&n; *&n; * Err. Should that be 4 fs blocks or 4k???&n; * It matters on large blocksize volumes&n; */
DECL|macro|BEFS_DBLINDIR_BRUN_LEN
mdefine_line|#define BEFS_DBLINDIR_BRUN_LEN 4
multiline_comment|/*&n; * Flags of superblock&n; */
DECL|enum|super_flags
r_enum
id|super_flags
(brace
DECL|enumerator|BEFS_BYTESEX_BE
id|BEFS_BYTESEX_BE
comma
DECL|enumerator|BEFS_BYTESEX_LE
id|BEFS_BYTESEX_LE
comma
DECL|enumerator|BEFS_CLEAN
id|BEFS_CLEAN
op_assign
l_int|0x434c454e
comma
DECL|enumerator|BEFS_DIRTY
id|BEFS_DIRTY
op_assign
l_int|0x44495254
comma
DECL|enumerator|BEFS_SUPER_MAGIC1
id|BEFS_SUPER_MAGIC1
op_assign
l_int|0x42465331
comma
multiline_comment|/* BFS1 */
DECL|enumerator|BEFS_SUPER_MAGIC2
id|BEFS_SUPER_MAGIC2
op_assign
l_int|0xdd121031
comma
DECL|enumerator|BEFS_SUPER_MAGIC3
id|BEFS_SUPER_MAGIC3
op_assign
l_int|0x15b6830e
comma
)brace
suffix:semicolon
DECL|macro|BEFS_BYTEORDER_NATIVE
mdefine_line|#define BEFS_BYTEORDER_NATIVE 0x42494745
DECL|macro|BEFS_SUPER_MAGIC
mdefine_line|#define BEFS_SUPER_MAGIC BEFS_SUPER_MAGIC1
multiline_comment|/*&n; * Flags of inode&n; */
DECL|macro|BEFS_INODE_MAGIC1
mdefine_line|#define BEFS_INODE_MAGIC1 0x3bbe0ad9
DECL|enum|inode_flags
r_enum
id|inode_flags
(brace
DECL|enumerator|BEFS_INODE_IN_USE
id|BEFS_INODE_IN_USE
op_assign
l_int|0x00000001
comma
DECL|enumerator|BEFS_ATTR_INODE
id|BEFS_ATTR_INODE
op_assign
l_int|0x00000004
comma
DECL|enumerator|BEFS_INODE_LOGGED
id|BEFS_INODE_LOGGED
op_assign
l_int|0x00000008
comma
DECL|enumerator|BEFS_INODE_DELETED
id|BEFS_INODE_DELETED
op_assign
l_int|0x00000010
comma
DECL|enumerator|BEFS_LONG_SYMLINK
id|BEFS_LONG_SYMLINK
op_assign
l_int|0x00000040
comma
DECL|enumerator|BEFS_PERMANENT_FLAG
id|BEFS_PERMANENT_FLAG
op_assign
l_int|0x0000ffff
comma
DECL|enumerator|BEFS_INODE_NO_CREATE
id|BEFS_INODE_NO_CREATE
op_assign
l_int|0x00010000
comma
DECL|enumerator|BEFS_INODE_WAS_WRITTEN
id|BEFS_INODE_WAS_WRITTEN
op_assign
l_int|0x00020000
comma
DECL|enumerator|BEFS_NO_TRANSACTION
id|BEFS_NO_TRANSACTION
op_assign
l_int|0x00040000
comma
)brace
suffix:semicolon
multiline_comment|/* &n; * On-Disk datastructures of BeFS&n; */
DECL|typedef|befs_off_t
r_typedef
id|u64
id|befs_off_t
suffix:semicolon
DECL|typedef|befs_time_t
r_typedef
id|u64
id|befs_time_t
suffix:semicolon
DECL|typedef|befs_binode_etc
r_typedef
r_void
id|befs_binode_etc
suffix:semicolon
multiline_comment|/* Block runs */
r_typedef
r_struct
(brace
DECL|member|allocation_group
id|u32
id|allocation_group
suffix:semicolon
DECL|member|start
id|u16
id|start
suffix:semicolon
DECL|member|len
id|u16
id|len
suffix:semicolon
DECL|typedef|befs_block_run
)brace
id|PACKED
id|befs_block_run
suffix:semicolon
DECL|typedef|befs_inode_addr
r_typedef
id|befs_block_run
id|befs_inode_addr
suffix:semicolon
multiline_comment|/*&n; * The Superblock Structure&n; */
r_typedef
r_struct
(brace
DECL|member|name
r_char
id|name
(braket
id|B_OS_NAME_LENGTH
)braket
suffix:semicolon
DECL|member|magic1
id|u32
id|magic1
suffix:semicolon
DECL|member|fs_byte_order
id|u32
id|fs_byte_order
suffix:semicolon
DECL|member|block_size
id|u32
id|block_size
suffix:semicolon
DECL|member|block_shift
id|u32
id|block_shift
suffix:semicolon
DECL|member|num_blocks
id|befs_off_t
id|num_blocks
suffix:semicolon
DECL|member|used_blocks
id|befs_off_t
id|used_blocks
suffix:semicolon
DECL|member|inode_size
id|u32
id|inode_size
suffix:semicolon
DECL|member|magic2
id|u32
id|magic2
suffix:semicolon
DECL|member|blocks_per_ag
id|u32
id|blocks_per_ag
suffix:semicolon
DECL|member|ag_shift
id|u32
id|ag_shift
suffix:semicolon
DECL|member|num_ags
id|u32
id|num_ags
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|log_blocks
id|befs_block_run
id|log_blocks
suffix:semicolon
DECL|member|log_start
id|befs_off_t
id|log_start
suffix:semicolon
DECL|member|log_end
id|befs_off_t
id|log_end
suffix:semicolon
DECL|member|magic3
id|u32
id|magic3
suffix:semicolon
DECL|member|root_dir
id|befs_inode_addr
id|root_dir
suffix:semicolon
DECL|member|indices
id|befs_inode_addr
id|indices
suffix:semicolon
DECL|typedef|befs_super_block
)brace
id|PACKED
id|befs_super_block
suffix:semicolon
multiline_comment|/* &n; * Note: the indirect and dbl_indir block_runs may&n; * be longer than one block!&n; */
r_typedef
r_struct
(brace
DECL|member|direct
id|befs_block_run
id|direct
(braket
id|BEFS_NUM_DIRECT_BLOCKS
)braket
suffix:semicolon
DECL|member|max_direct_range
id|befs_off_t
id|max_direct_range
suffix:semicolon
DECL|member|indirect
id|befs_block_run
id|indirect
suffix:semicolon
DECL|member|max_indirect_range
id|befs_off_t
id|max_indirect_range
suffix:semicolon
DECL|member|double_indirect
id|befs_block_run
id|double_indirect
suffix:semicolon
DECL|member|max_double_indirect_range
id|befs_off_t
id|max_double_indirect_range
suffix:semicolon
DECL|member|size
id|befs_off_t
id|size
suffix:semicolon
DECL|typedef|befs_data_stream
)brace
id|PACKED
id|befs_data_stream
suffix:semicolon
multiline_comment|/* Attribute */
r_typedef
r_struct
(brace
DECL|member|type
id|u32
id|type
suffix:semicolon
DECL|member|name_size
id|u16
id|name_size
suffix:semicolon
DECL|member|data_size
id|u16
id|data_size
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|befs_small_data
)brace
id|PACKED
id|befs_small_data
suffix:semicolon
multiline_comment|/* Inode structure */
r_typedef
r_struct
(brace
DECL|member|magic1
id|u32
id|magic1
suffix:semicolon
DECL|member|inode_num
id|befs_inode_addr
id|inode_num
suffix:semicolon
DECL|member|uid
id|u32
id|uid
suffix:semicolon
DECL|member|gid
id|u32
id|gid
suffix:semicolon
DECL|member|mode
id|u32
id|mode
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|create_time
id|befs_time_t
id|create_time
suffix:semicolon
DECL|member|last_modified_time
id|befs_time_t
id|last_modified_time
suffix:semicolon
DECL|member|parent
id|befs_inode_addr
id|parent
suffix:semicolon
DECL|member|attributes
id|befs_inode_addr
id|attributes
suffix:semicolon
DECL|member|type
id|u32
id|type
suffix:semicolon
DECL|member|inode_size
id|u32
id|inode_size
suffix:semicolon
DECL|member|etc
id|u32
id|etc
suffix:semicolon
multiline_comment|/* not use */
r_union
(brace
DECL|member|datastream
id|befs_data_stream
id|datastream
suffix:semicolon
DECL|member|symlink
r_char
id|symlink
(braket
id|BEFS_SYMLINK_LEN
)braket
suffix:semicolon
DECL|member|data
)brace
id|data
suffix:semicolon
DECL|member|pad
id|u32
id|pad
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* not use */
DECL|member|small_data
id|befs_small_data
id|small_data
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|befs_inode
)brace
id|PACKED
id|befs_inode
suffix:semicolon
multiline_comment|/*&n; * B+tree superblock&n; */
DECL|macro|BEFS_BTREE_MAGIC
mdefine_line|#define BEFS_BTREE_MAGIC 0x69f6c2e8
DECL|enum|btree_types
r_enum
id|btree_types
(brace
DECL|enumerator|BTREE_STRING_TYPE
id|BTREE_STRING_TYPE
op_assign
l_int|0
comma
DECL|enumerator|BTREE_INT32_TYPE
id|BTREE_INT32_TYPE
op_assign
l_int|1
comma
DECL|enumerator|BTREE_UINT32_TYPE
id|BTREE_UINT32_TYPE
op_assign
l_int|2
comma
DECL|enumerator|BTREE_INT64_TYPE
id|BTREE_INT64_TYPE
op_assign
l_int|3
comma
DECL|enumerator|BTREE_UINT64_TYPE
id|BTREE_UINT64_TYPE
op_assign
l_int|4
comma
DECL|enumerator|BTREE_FLOAT_TYPE
id|BTREE_FLOAT_TYPE
op_assign
l_int|5
comma
DECL|enumerator|BTREE_DOUBLE_TYPE
id|BTREE_DOUBLE_TYPE
op_assign
l_int|6
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|magic
id|u32
id|magic
suffix:semicolon
DECL|member|node_size
id|u32
id|node_size
suffix:semicolon
DECL|member|max_depth
id|u32
id|max_depth
suffix:semicolon
DECL|member|data_type
id|u32
id|data_type
suffix:semicolon
DECL|member|root_node_ptr
id|befs_off_t
id|root_node_ptr
suffix:semicolon
DECL|member|free_node_ptr
id|befs_off_t
id|free_node_ptr
suffix:semicolon
DECL|member|max_size
id|befs_off_t
id|max_size
suffix:semicolon
DECL|typedef|befs_btree_super
)brace
id|PACKED
id|befs_btree_super
suffix:semicolon
multiline_comment|/*&n; * Header stucture of each btree node&n; */
r_typedef
r_struct
(brace
DECL|member|left
id|befs_off_t
id|left
suffix:semicolon
DECL|member|right
id|befs_off_t
id|right
suffix:semicolon
DECL|member|overflow
id|befs_off_t
id|overflow
suffix:semicolon
DECL|member|all_key_count
id|u16
id|all_key_count
suffix:semicolon
DECL|member|all_key_length
id|u16
id|all_key_length
suffix:semicolon
DECL|typedef|befs_btree_nodehead
)brace
id|PACKED
id|befs_btree_nodehead
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _LINUX_BEFS_FS_TYPES */
eof
