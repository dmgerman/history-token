multiline_comment|/*&n; * super.c&n; *&n; * Copyright (c) 1999 Al Smith&n; *&n; * Portions derived from work (c) 1995,1996 Christian Vogelgsang.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/efs_fs.h&gt;
macro_line|#include &lt;linux/efs_vh.h&gt;
macro_line|#include &lt;linux/efs_fs_sb.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;linux/vfs.h&gt;
DECL|function|efs_get_sb
r_static
r_struct
id|super_block
op_star
id|efs_get_sb
c_func
(paren
r_struct
id|file_system_type
op_star
id|fs_type
comma
r_int
id|flags
comma
r_const
r_char
op_star
id|dev_name
comma
r_void
op_star
id|data
)paren
(brace
r_return
id|get_sb_bdev
c_func
(paren
id|fs_type
comma
id|flags
comma
id|dev_name
comma
id|data
comma
id|efs_fill_super
)paren
suffix:semicolon
)brace
DECL|variable|efs_fs_type
r_static
r_struct
id|file_system_type
id|efs_fs_type
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;efs&quot;
comma
dot
id|get_sb
op_assign
id|efs_get_sb
comma
dot
id|kill_sb
op_assign
id|kill_block_super
comma
dot
id|fs_flags
op_assign
id|FS_REQUIRES_DEV
comma
)brace
suffix:semicolon
DECL|variable|efs_inode_cachep
r_static
id|kmem_cache_t
op_star
id|efs_inode_cachep
suffix:semicolon
DECL|function|efs_alloc_inode
r_static
r_struct
id|inode
op_star
id|efs_alloc_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|efs_inode_info
op_star
id|ei
suffix:semicolon
id|ei
op_assign
(paren
r_struct
id|efs_inode_info
op_star
)paren
id|kmem_cache_alloc
c_func
(paren
id|efs_inode_cachep
comma
id|SLAB_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ei
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
op_amp
id|ei-&gt;vfs_inode
suffix:semicolon
)brace
DECL|function|efs_destroy_inode
r_static
r_void
id|efs_destroy_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|kmem_cache_free
c_func
(paren
id|efs_inode_cachep
comma
id|INODE_INFO
c_func
(paren
id|inode
)paren
)paren
suffix:semicolon
)brace
DECL|function|init_once
r_static
r_void
id|init_once
c_func
(paren
r_void
op_star
id|foo
comma
id|kmem_cache_t
op_star
id|cachep
comma
r_int
r_int
id|flags
)paren
(brace
r_struct
id|efs_inode_info
op_star
id|ei
op_assign
(paren
r_struct
id|efs_inode_info
op_star
)paren
id|foo
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
(paren
id|SLAB_CTOR_VERIFY
op_or
id|SLAB_CTOR_CONSTRUCTOR
)paren
)paren
op_eq
id|SLAB_CTOR_CONSTRUCTOR
)paren
id|inode_init_once
c_func
(paren
op_amp
id|ei-&gt;vfs_inode
)paren
suffix:semicolon
)brace
DECL|function|init_inodecache
r_static
r_int
id|init_inodecache
c_func
(paren
r_void
)paren
(brace
id|efs_inode_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;efs_inode_cache&quot;
comma
r_sizeof
(paren
r_struct
id|efs_inode_info
)paren
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
op_or
id|SLAB_RECLAIM_ACCOUNT
comma
id|init_once
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|efs_inode_cachep
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|destroy_inodecache
r_static
r_void
id|destroy_inodecache
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|kmem_cache_destroy
c_func
(paren
id|efs_inode_cachep
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;efs_inode_cache: not all structures were freed&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|efs_put_super
r_void
id|efs_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|s
)paren
(brace
id|kfree
c_func
(paren
id|s-&gt;s_fs_info
)paren
suffix:semicolon
id|s-&gt;s_fs_info
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|variable|efs_superblock_operations
r_static
r_struct
id|super_operations
id|efs_superblock_operations
op_assign
(brace
dot
id|alloc_inode
op_assign
id|efs_alloc_inode
comma
dot
id|destroy_inode
op_assign
id|efs_destroy_inode
comma
dot
id|read_inode
op_assign
id|efs_read_inode
comma
dot
id|put_super
op_assign
id|efs_put_super
comma
dot
id|statfs
op_assign
id|efs_statfs
comma
)brace
suffix:semicolon
DECL|function|init_efs_fs
r_static
r_int
id|__init
id|init_efs_fs
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;EFS: &quot;
id|EFS_VERSION
l_string|&quot; - http://aeschi.ch.eu.org/efs/&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
id|init_inodecache
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out1
suffix:semicolon
id|err
op_assign
id|register_filesystem
c_func
(paren
op_amp
id|efs_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out
suffix:colon
id|destroy_inodecache
c_func
(paren
)paren
suffix:semicolon
id|out1
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|exit_efs_fs
r_static
r_void
id|__exit
id|exit_efs_fs
c_func
(paren
r_void
)paren
(brace
id|unregister_filesystem
c_func
(paren
op_amp
id|efs_fs_type
)paren
suffix:semicolon
id|destroy_inodecache
c_func
(paren
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|init_efs_fs
)paren
id|module_exit
c_func
(paren
id|exit_efs_fs
)paren
DECL|function|efs_validate_vh
r_static
id|efs_block_t
id|efs_validate_vh
c_func
(paren
r_struct
id|volume_header
op_star
id|vh
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|cs
comma
id|csum
comma
op_star
id|ui
suffix:semicolon
id|efs_block_t
id|sblock
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* shuts up gcc */
r_struct
id|pt_types
op_star
id|pt_entry
suffix:semicolon
r_int
id|pt_type
comma
id|slice
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|be32_to_cpu
c_func
(paren
id|vh-&gt;vh_magic
)paren
op_ne
id|VHMAGIC
)paren
(brace
multiline_comment|/*&n;&t;&t; * assume that we&squot;re dealing with a partition and allow&n;&t;&t; * read_super() to try and detect a valid superblock&n;&t;&t; * on the next block.&n;&t;&t; */
r_return
l_int|0
suffix:semicolon
)brace
id|ui
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
(paren
id|vh
op_plus
l_int|1
)paren
)paren
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|csum
op_assign
l_int|0
suffix:semicolon
id|ui
op_ge
(paren
(paren
r_int
r_int
op_star
)paren
id|vh
)paren
suffix:semicolon
)paren
(brace
id|cs
op_assign
op_star
id|ui
op_decrement
suffix:semicolon
id|csum
op_add_assign
id|be32_to_cpu
c_func
(paren
id|cs
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|csum
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;EFS: SGI disklabel: checksum bad, label corrupted&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;EFS: bf: &bslash;&quot;%16s&bslash;&quot;&bslash;n&quot;
comma
id|vh-&gt;vh_bootfile
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
id|NVDIR
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|j
suffix:semicolon
r_char
id|name
(braket
id|VDNAMESIZE
op_plus
l_int|1
)braket
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|VDNAMESIZE
suffix:semicolon
id|j
op_increment
)paren
(brace
id|name
(braket
id|j
)braket
op_assign
id|vh-&gt;vh_vd
(braket
id|i
)braket
dot
id|vd_name
(braket
id|j
)braket
suffix:semicolon
)brace
id|name
(braket
id|j
)braket
op_assign
(paren
r_char
)paren
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|name
(braket
l_int|0
)braket
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;EFS: vh: %8s block: 0x%08x size: 0x%08x&bslash;n&quot;
comma
id|name
comma
(paren
r_int
)paren
id|be32_to_cpu
c_func
(paren
id|vh-&gt;vh_vd
(braket
id|i
)braket
dot
id|vd_lbn
)paren
comma
(paren
r_int
)paren
id|be32_to_cpu
c_func
(paren
id|vh-&gt;vh_vd
(braket
id|i
)braket
dot
id|vd_nbytes
)paren
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NPARTAB
suffix:semicolon
id|i
op_increment
)paren
(brace
id|pt_type
op_assign
(paren
r_int
)paren
id|be32_to_cpu
c_func
(paren
id|vh-&gt;vh_pt
(braket
id|i
)braket
dot
id|pt_type
)paren
suffix:semicolon
r_for
c_loop
(paren
id|pt_entry
op_assign
id|sgi_pt_types
suffix:semicolon
id|pt_entry-&gt;pt_name
suffix:semicolon
id|pt_entry
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pt_type
op_eq
id|pt_entry-&gt;pt_type
)paren
r_break
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
r_if
c_cond
(paren
id|be32_to_cpu
c_func
(paren
id|vh-&gt;vh_pt
(braket
id|i
)braket
dot
id|pt_nblks
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;EFS: pt %2d: start: %08d size: %08d type: 0x%02x (%s)&bslash;n&quot;
comma
id|i
comma
(paren
r_int
)paren
id|be32_to_cpu
c_func
(paren
id|vh-&gt;vh_pt
(braket
id|i
)braket
dot
id|pt_firstlbn
)paren
comma
(paren
r_int
)paren
id|be32_to_cpu
c_func
(paren
id|vh-&gt;vh_pt
(braket
id|i
)braket
dot
id|pt_nblks
)paren
comma
id|pt_type
comma
(paren
id|pt_entry-&gt;pt_name
)paren
ques
c_cond
id|pt_entry-&gt;pt_name
suffix:colon
l_string|&quot;unknown&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|IS_EFS
c_func
(paren
id|pt_type
)paren
)paren
(brace
id|sblock
op_assign
id|be32_to_cpu
c_func
(paren
id|vh-&gt;vh_pt
(braket
id|i
)braket
dot
id|pt_firstlbn
)paren
suffix:semicolon
id|slice
op_assign
id|i
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|slice
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;EFS: partition table contained no EFS partitions&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;EFS: using slice %d (type %s, offset 0x%x)&bslash;n&quot;
comma
id|slice
comma
(paren
id|pt_entry-&gt;pt_name
)paren
ques
c_cond
id|pt_entry-&gt;pt_name
suffix:colon
l_string|&quot;unknown&quot;
comma
id|sblock
)paren
suffix:semicolon
macro_line|#endif
)brace
r_return
id|sblock
suffix:semicolon
)brace
DECL|function|efs_validate_super
r_static
r_int
id|efs_validate_super
c_func
(paren
r_struct
id|efs_sb_info
op_star
id|sb
comma
r_struct
id|efs_super
op_star
id|super
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|IS_EFS_MAGIC
c_func
(paren
id|be32_to_cpu
c_func
(paren
id|super-&gt;fs_magic
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|sb-&gt;fs_magic
op_assign
id|be32_to_cpu
c_func
(paren
id|super-&gt;fs_magic
)paren
suffix:semicolon
id|sb-&gt;total_blocks
op_assign
id|be32_to_cpu
c_func
(paren
id|super-&gt;fs_size
)paren
suffix:semicolon
id|sb-&gt;first_block
op_assign
id|be32_to_cpu
c_func
(paren
id|super-&gt;fs_firstcg
)paren
suffix:semicolon
id|sb-&gt;group_size
op_assign
id|be32_to_cpu
c_func
(paren
id|super-&gt;fs_cgfsize
)paren
suffix:semicolon
id|sb-&gt;data_free
op_assign
id|be32_to_cpu
c_func
(paren
id|super-&gt;fs_tfree
)paren
suffix:semicolon
id|sb-&gt;inode_free
op_assign
id|be32_to_cpu
c_func
(paren
id|super-&gt;fs_tinode
)paren
suffix:semicolon
id|sb-&gt;inode_blocks
op_assign
id|be16_to_cpu
c_func
(paren
id|super-&gt;fs_cgisize
)paren
suffix:semicolon
id|sb-&gt;total_groups
op_assign
id|be16_to_cpu
c_func
(paren
id|super-&gt;fs_ncg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|efs_fill_super
r_int
id|efs_fill_super
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_void
op_star
id|d
comma
r_int
id|silent
)paren
(brace
r_struct
id|efs_sb_info
op_star
id|sb
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|sb
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|efs_sb_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|s-&gt;s_fs_info
op_assign
id|sb
suffix:semicolon
id|memset
c_func
(paren
id|sb
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|efs_sb_info
)paren
)paren
suffix:semicolon
id|s-&gt;s_magic
op_assign
id|EFS_SUPER_MAGIC
suffix:semicolon
id|sb_set_blocksize
c_func
(paren
id|s
comma
id|EFS_BLOCKSIZE
)paren
suffix:semicolon
multiline_comment|/* read the vh (volume header) block */
id|bh
op_assign
id|sb_bread
c_func
(paren
id|s
comma
l_int|0
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
l_string|&quot;EFS: cannot read volume header&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_no_fs_ul
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * if this returns zero then we didn&squot;t find any partition table.&n;&t; * this isn&squot;t (yet) an error - just assume for the moment that&n;&t; * the device is valid and go on to search for a superblock.&n;&t; */
id|sb-&gt;fs_start
op_assign
id|efs_validate_vh
c_func
(paren
(paren
r_struct
id|volume_header
op_star
)paren
id|bh-&gt;b_data
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
id|sb-&gt;fs_start
op_eq
op_minus
l_int|1
)paren
(brace
r_goto
id|out_no_fs_ul
suffix:semicolon
)brace
id|bh
op_assign
id|sb_bread
c_func
(paren
id|s
comma
id|sb-&gt;fs_start
op_plus
id|EFS_SUPER
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
l_string|&quot;EFS: cannot read superblock&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_no_fs_ul
suffix:semicolon
)brace
r_if
c_cond
(paren
id|efs_validate_super
c_func
(paren
id|sb
comma
(paren
r_struct
id|efs_super
op_star
)paren
id|bh-&gt;b_data
)paren
)paren
(brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;EFS: invalid superblock at block %u&bslash;n&quot;
comma
id|sb-&gt;fs_start
op_plus
id|EFS_SUPER
)paren
suffix:semicolon
macro_line|#endif
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_goto
id|out_no_fs_ul
suffix:semicolon
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
op_logical_neg
(paren
id|s-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
(brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;EFS: forcing read-only mode&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|s-&gt;s_flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
)brace
id|s-&gt;s_op
op_assign
op_amp
id|efs_superblock_operations
suffix:semicolon
id|s-&gt;s_root
op_assign
id|d_alloc_root
c_func
(paren
id|iget
c_func
(paren
id|s
comma
id|EFS_ROOTINODE
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|s-&gt;s_root
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;EFS: get root inode failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_no_fs
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|out_no_fs_ul
suffix:colon
id|out_no_fs
suffix:colon
id|s-&gt;s_fs_info
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|efs_statfs
r_int
id|efs_statfs
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_struct
id|statfs
op_star
id|buf
)paren
(brace
r_struct
id|efs_sb_info
op_star
id|sb
op_assign
id|SUPER_INFO
c_func
(paren
id|s
)paren
suffix:semicolon
id|buf-&gt;f_type
op_assign
id|EFS_SUPER_MAGIC
suffix:semicolon
multiline_comment|/* efs magic number */
id|buf-&gt;f_bsize
op_assign
id|EFS_BLOCKSIZE
suffix:semicolon
multiline_comment|/* blocksize */
id|buf-&gt;f_blocks
op_assign
id|sb-&gt;total_groups
op_star
multiline_comment|/* total data blocks */
(paren
id|sb-&gt;group_size
op_minus
id|sb-&gt;inode_blocks
)paren
suffix:semicolon
id|buf-&gt;f_bfree
op_assign
id|sb-&gt;data_free
suffix:semicolon
multiline_comment|/* free data blocks */
id|buf-&gt;f_bavail
op_assign
id|sb-&gt;data_free
suffix:semicolon
multiline_comment|/* free blocks for non-root */
id|buf-&gt;f_files
op_assign
id|sb-&gt;total_groups
op_star
multiline_comment|/* total inodes */
id|sb-&gt;inode_blocks
op_star
(paren
id|EFS_BLOCKSIZE
op_div
r_sizeof
(paren
r_struct
id|efs_dinode
)paren
)paren
suffix:semicolon
id|buf-&gt;f_ffree
op_assign
id|sb-&gt;inode_free
suffix:semicolon
multiline_comment|/* free inodes */
id|buf-&gt;f_fsid.val
(braket
l_int|0
)braket
op_assign
(paren
id|sb-&gt;fs_magic
op_rshift
l_int|16
)paren
op_amp
l_int|0xffff
suffix:semicolon
multiline_comment|/* fs ID */
id|buf-&gt;f_fsid.val
(braket
l_int|1
)braket
op_assign
id|sb-&gt;fs_magic
op_amp
l_int|0xffff
suffix:semicolon
multiline_comment|/* fs ID */
id|buf-&gt;f_namelen
op_assign
id|EFS_MAXNAMELEN
suffix:semicolon
multiline_comment|/* max filename length */
r_return
l_int|0
suffix:semicolon
)brace
eof
