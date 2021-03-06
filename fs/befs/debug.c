multiline_comment|/*&n; *  linux/fs/befs/debug.c&n; * &n; * Copyright (C) 2001 Will Dyson (will_dyson at pobox.com)&n; *&n; * With help from the ntfs-tng driver by Anton Altparmakov&n; *&n; * Copyright (C) 1999  Makoto Kato (m_kato@ga2.so-net.ne.jp)&n; *&n; * debug functions&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
macro_line|#include &quot;befs.h&quot;
macro_line|#include &quot;endian.h&quot;
DECL|macro|ERRBUFSIZE
mdefine_line|#define ERRBUFSIZE 1024
r_void
DECL|function|befs_error
id|befs_error
c_func
(paren
r_const
r_struct
id|super_block
op_star
id|sb
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_char
op_star
id|err_buf
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
c_func
(paren
id|ERRBUFSIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err_buf
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;could not allocate %d bytes&bslash;n&quot;
comma
id|ERRBUFSIZE
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|vsnprintf
c_func
(paren
id|err_buf
comma
id|ERRBUFSIZE
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;BeFS(%s): %s&bslash;n&quot;
comma
id|sb-&gt;s_id
comma
id|err_buf
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|err_buf
)paren
suffix:semicolon
)brace
r_void
DECL|function|befs_warning
id|befs_warning
c_func
(paren
r_const
r_struct
id|super_block
op_star
id|sb
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_char
op_star
id|err_buf
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
c_func
(paren
id|ERRBUFSIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err_buf
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;could not allocate %d bytes&bslash;n&quot;
comma
id|ERRBUFSIZE
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|vsnprintf
c_func
(paren
id|err_buf
comma
id|ERRBUFSIZE
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;BeFS(%s): %s&bslash;n&quot;
comma
id|sb-&gt;s_id
comma
id|err_buf
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|err_buf
)paren
suffix:semicolon
)brace
r_void
DECL|function|befs_debug
id|befs_debug
c_func
(paren
r_const
r_struct
id|super_block
op_star
id|sb
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
macro_line|#ifdef CONFIG_BEFS_DEBUG
id|va_list
id|args
suffix:semicolon
r_char
op_star
id|err_buf
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|BEFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|mount_opts.debug
)paren
(brace
id|err_buf
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
c_func
(paren
id|ERRBUFSIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err_buf
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;could not allocate %d bytes&bslash;n&quot;
comma
id|ERRBUFSIZE
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|vsnprintf
c_func
(paren
id|err_buf
comma
id|ERRBUFSIZE
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;BeFS(%s): %s&bslash;n&quot;
comma
id|sb-&gt;s_id
comma
id|err_buf
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|err_buf
)paren
suffix:semicolon
)brace
macro_line|#endif&t;&t;&t;&t;
singleline_comment|//CONFIG_BEFS_DEBUG
)brace
r_void
DECL|function|befs_dump_inode
id|befs_dump_inode
c_func
(paren
r_const
r_struct
id|super_block
op_star
id|sb
comma
id|befs_inode
op_star
id|inode
)paren
(brace
macro_line|#ifdef CONFIG_BEFS_DEBUG
id|befs_block_run
id|tmp_run
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;befs_inode information&quot;
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  magic1 %08x&quot;
comma
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|inode-&gt;magic1
)paren
)paren
suffix:semicolon
id|tmp_run
op_assign
id|fsrun_to_cpu
c_func
(paren
id|sb
comma
id|inode-&gt;inode_num
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  inode_num %u, %hu, %hu&quot;
comma
id|tmp_run.allocation_group
comma
id|tmp_run.start
comma
id|tmp_run.len
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  uid %u&quot;
comma
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|inode-&gt;uid
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  gid %u&quot;
comma
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|inode-&gt;gid
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  mode %08x&quot;
comma
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|inode-&gt;mode
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  flags %08x&quot;
comma
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|inode-&gt;flags
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  create_time %Lu&quot;
comma
id|fs64_to_cpu
c_func
(paren
id|sb
comma
id|inode-&gt;create_time
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  last_modified_time %Lu&quot;
comma
id|fs64_to_cpu
c_func
(paren
id|sb
comma
id|inode-&gt;last_modified_time
)paren
)paren
suffix:semicolon
id|tmp_run
op_assign
id|fsrun_to_cpu
c_func
(paren
id|sb
comma
id|inode-&gt;parent
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  parent [%u, %hu, %hu]&quot;
comma
id|tmp_run.allocation_group
comma
id|tmp_run.start
comma
id|tmp_run.len
)paren
suffix:semicolon
id|tmp_run
op_assign
id|fsrun_to_cpu
c_func
(paren
id|sb
comma
id|inode-&gt;attributes
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  attributes [%u, %hu, %hu]&quot;
comma
id|tmp_run.allocation_group
comma
id|tmp_run.start
comma
id|tmp_run.len
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  type %08x&quot;
comma
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|inode-&gt;type
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  inode_size %u&quot;
comma
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|inode-&gt;inode_size
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|inode-&gt;mode
)paren
)paren
(brace
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  Symbolic link [%s]&quot;
comma
id|inode-&gt;data.symlink
)paren
suffix:semicolon
)brace
r_else
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
id|BEFS_NUM_DIRECT_BLOCKS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|tmp_run
op_assign
id|fsrun_to_cpu
c_func
(paren
id|sb
comma
id|inode-&gt;data.datastream.direct
(braket
id|i
)braket
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  direct %d [%u, %hu, %hu]&quot;
comma
id|i
comma
id|tmp_run.allocation_group
comma
id|tmp_run.start
comma
id|tmp_run.len
)paren
suffix:semicolon
)brace
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  max_direct_range %Lu&quot;
comma
id|fs64_to_cpu
c_func
(paren
id|sb
comma
id|inode-&gt;data.datastream
dot
id|max_direct_range
)paren
)paren
suffix:semicolon
id|tmp_run
op_assign
id|fsrun_to_cpu
c_func
(paren
id|sb
comma
id|inode-&gt;data.datastream.indirect
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  indirect [%u, %hu, %hu]&quot;
comma
id|tmp_run.allocation_group
comma
id|tmp_run.start
comma
id|tmp_run.len
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  max_indirect_range %Lu&quot;
comma
id|fs64_to_cpu
c_func
(paren
id|sb
comma
id|inode-&gt;data.datastream
dot
id|max_indirect_range
)paren
)paren
suffix:semicolon
id|tmp_run
op_assign
id|fsrun_to_cpu
c_func
(paren
id|sb
comma
id|inode-&gt;data.datastream.double_indirect
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  double indirect [%u, %hu, %hu]&quot;
comma
id|tmp_run.allocation_group
comma
id|tmp_run.start
comma
id|tmp_run.len
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  max_double_indirect_range %Lu&quot;
comma
id|fs64_to_cpu
c_func
(paren
id|sb
comma
id|inode-&gt;data.datastream
dot
id|max_double_indirect_range
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  size %Lu&quot;
comma
id|fs64_to_cpu
c_func
(paren
id|sb
comma
id|inode-&gt;data.datastream.size
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif&t;&t;&t;&t;
singleline_comment|//CONFIG_BEFS_DEBUG
)brace
multiline_comment|/*&n; * Display super block structure for debug.&n; */
r_void
DECL|function|befs_dump_super_block
id|befs_dump_super_block
c_func
(paren
r_const
r_struct
id|super_block
op_star
id|sb
comma
id|befs_super_block
op_star
id|sup
)paren
(brace
macro_line|#ifdef CONFIG_BEFS_DEBUG
id|befs_block_run
id|tmp_run
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;befs_super_block information&quot;
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  name %s&quot;
comma
id|sup-&gt;name
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  magic1 %08x&quot;
comma
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|sup-&gt;magic1
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  fs_byte_order %08x&quot;
comma
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|sup-&gt;fs_byte_order
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  block_size %u&quot;
comma
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|sup-&gt;block_size
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  block_shift %u&quot;
comma
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|sup-&gt;block_shift
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  num_blocks %Lu&quot;
comma
id|fs64_to_cpu
c_func
(paren
id|sb
comma
id|sup-&gt;num_blocks
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  used_blocks %Lu&quot;
comma
id|fs64_to_cpu
c_func
(paren
id|sb
comma
id|sup-&gt;used_blocks
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  magic2 %08x&quot;
comma
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|sup-&gt;magic2
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  blocks_per_ag %u&quot;
comma
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|sup-&gt;blocks_per_ag
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  ag_shift %u&quot;
comma
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|sup-&gt;ag_shift
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  num_ags %u&quot;
comma
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|sup-&gt;num_ags
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  flags %08x&quot;
comma
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|sup-&gt;flags
)paren
)paren
suffix:semicolon
id|tmp_run
op_assign
id|fsrun_to_cpu
c_func
(paren
id|sb
comma
id|sup-&gt;log_blocks
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  log_blocks %u, %hu, %hu&quot;
comma
id|tmp_run.allocation_group
comma
id|tmp_run.start
comma
id|tmp_run.len
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  log_start %Ld&quot;
comma
id|fs64_to_cpu
c_func
(paren
id|sb
comma
id|sup-&gt;log_start
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  log_end %Ld&quot;
comma
id|fs64_to_cpu
c_func
(paren
id|sb
comma
id|sup-&gt;log_end
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  magic3 %08x&quot;
comma
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|sup-&gt;magic3
)paren
)paren
suffix:semicolon
id|tmp_run
op_assign
id|fsrun_to_cpu
c_func
(paren
id|sb
comma
id|sup-&gt;root_dir
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  root_dir %u, %hu, %hu&quot;
comma
id|tmp_run.allocation_group
comma
id|tmp_run.start
comma
id|tmp_run.len
)paren
suffix:semicolon
id|tmp_run
op_assign
id|fsrun_to_cpu
c_func
(paren
id|sb
comma
id|sup-&gt;indices
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  indices %u, %hu, %hu&quot;
comma
id|tmp_run.allocation_group
comma
id|tmp_run.start
comma
id|tmp_run.len
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;
singleline_comment|//CONFIG_BEFS_DEBUG
)brace
macro_line|#if 0
multiline_comment|/* unused */
r_void
id|befs_dump_small_data
c_func
(paren
r_const
r_struct
id|super_block
op_star
id|sb
comma
id|befs_small_data
op_star
id|sd
)paren
(brace
)brace
multiline_comment|/* unused */
r_void
id|befs_dump_run
c_func
(paren
r_const
r_struct
id|super_block
op_star
id|sb
comma
id|befs_block_run
id|run
)paren
(brace
macro_line|#ifdef CONFIG_BEFS_DEBUG
id|run
op_assign
id|fsrun_to_cpu
c_func
(paren
id|sb
comma
id|run
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;[%u, %hu, %hu]&quot;
comma
id|run.allocation_group
comma
id|run.start
comma
id|run.len
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;
singleline_comment|//CONFIG_BEFS_DEBUG
)brace
macro_line|#endif  /*  0  */
r_void
DECL|function|befs_dump_index_entry
id|befs_dump_index_entry
c_func
(paren
r_const
r_struct
id|super_block
op_star
id|sb
comma
id|befs_btree_super
op_star
id|super
)paren
(brace
macro_line|#ifdef CONFIG_BEFS_DEBUG
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;Btree super structure&quot;
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  magic %08x&quot;
comma
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|super-&gt;magic
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  node_size %u&quot;
comma
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|super-&gt;node_size
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  max_depth %08x&quot;
comma
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|super-&gt;max_depth
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  data_type %08x&quot;
comma
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|super-&gt;data_type
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  root_node_pointer %016LX&quot;
comma
id|fs64_to_cpu
c_func
(paren
id|sb
comma
id|super-&gt;root_node_ptr
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  free_node_pointer %016LX&quot;
comma
id|fs64_to_cpu
c_func
(paren
id|sb
comma
id|super-&gt;free_node_ptr
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  maximum size %016LX&quot;
comma
id|fs64_to_cpu
c_func
(paren
id|sb
comma
id|super-&gt;max_size
)paren
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;
singleline_comment|//CONFIG_BEFS_DEBUG
)brace
r_void
DECL|function|befs_dump_index_node
id|befs_dump_index_node
c_func
(paren
r_const
r_struct
id|super_block
op_star
id|sb
comma
id|befs_btree_nodehead
op_star
id|node
)paren
(brace
macro_line|#ifdef CONFIG_BEFS_DEBUG
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;Btree node structure&quot;
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  left %016LX&quot;
comma
id|fs64_to_cpu
c_func
(paren
id|sb
comma
id|node-&gt;left
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  right %016LX&quot;
comma
id|fs64_to_cpu
c_func
(paren
id|sb
comma
id|node-&gt;right
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  overflow %016LX&quot;
comma
id|fs64_to_cpu
c_func
(paren
id|sb
comma
id|node-&gt;overflow
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  all_key_count %hu&quot;
comma
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|node-&gt;all_key_count
)paren
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;  all_key_length %hu&quot;
comma
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|node-&gt;all_key_length
)paren
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;
singleline_comment|//CONFIG_BEFS_DEBUG
)brace
eof
