multiline_comment|/*&n; *  linux/fs/adfs/super.c&n; *&n; *  Copyright (C) 1997-1999 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/adfs_fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &quot;adfs.h&quot;
macro_line|#include &quot;dir_f.h&quot;
macro_line|#include &quot;dir_fplus.h&quot;
DECL|function|__adfs_error
r_void
id|__adfs_error
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_const
r_char
op_star
id|function
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
r_char
id|error_buf
(braket
l_int|128
)braket
suffix:semicolon
id|va_list
id|args
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|vsprintf
c_func
(paren
id|error_buf
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
id|KERN_CRIT
l_string|&quot;ADFS-fs error (device %s)%s%s: %s&bslash;n&quot;
comma
id|sb-&gt;s_id
comma
id|function
ques
c_cond
l_string|&quot;: &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|function
ques
c_cond
id|function
suffix:colon
l_string|&quot;&quot;
comma
id|error_buf
)paren
suffix:semicolon
)brace
DECL|function|adfs_checkdiscrecord
r_static
r_int
id|adfs_checkdiscrecord
c_func
(paren
r_struct
id|adfs_discrecord
op_star
id|dr
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* sector size must be 256, 512 or 1024 bytes */
r_if
c_cond
(paren
id|dr-&gt;log2secsize
op_ne
l_int|8
op_logical_and
id|dr-&gt;log2secsize
op_ne
l_int|9
op_logical_and
id|dr-&gt;log2secsize
op_ne
l_int|10
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* idlen must be at least log2secsize + 3 */
r_if
c_cond
(paren
id|dr-&gt;idlen
OL
id|dr-&gt;log2secsize
op_plus
l_int|3
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* we cannot have such a large disc that we&n;&t; * are unable to represent sector offsets in&n;&t; * 32 bits.  This works out at 2.0 TB.&n;&t; */
r_if
c_cond
(paren
id|dr-&gt;disc_size_high
op_rshift
id|dr-&gt;log2secsize
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* idlen must be no greater than 19 v2 [1.0] */
r_if
c_cond
(paren
id|dr-&gt;idlen
OG
l_int|19
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* reserved bytes should be zero */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
r_sizeof
(paren
id|dr-&gt;unused52
)paren
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|dr-&gt;unused52
(braket
id|i
)braket
op_ne
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|adfs_calczonecheck
r_static
r_int
r_char
id|adfs_calczonecheck
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_char
op_star
id|map
)paren
(brace
r_int
r_int
id|v0
comma
id|v1
comma
id|v2
comma
id|v3
suffix:semicolon
r_int
id|i
suffix:semicolon
id|v0
op_assign
id|v1
op_assign
id|v2
op_assign
id|v3
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|sb-&gt;s_blocksize
op_minus
l_int|4
suffix:semicolon
id|i
suffix:semicolon
id|i
op_sub_assign
l_int|4
)paren
(brace
id|v0
op_add_assign
id|map
(braket
id|i
)braket
op_plus
(paren
id|v3
op_rshift
l_int|8
)paren
suffix:semicolon
id|v3
op_and_assign
l_int|0xff
suffix:semicolon
id|v1
op_add_assign
id|map
(braket
id|i
op_plus
l_int|1
)braket
op_plus
(paren
id|v0
op_rshift
l_int|8
)paren
suffix:semicolon
id|v0
op_and_assign
l_int|0xff
suffix:semicolon
id|v2
op_add_assign
id|map
(braket
id|i
op_plus
l_int|2
)braket
op_plus
(paren
id|v1
op_rshift
l_int|8
)paren
suffix:semicolon
id|v1
op_and_assign
l_int|0xff
suffix:semicolon
id|v3
op_add_assign
id|map
(braket
id|i
op_plus
l_int|3
)braket
op_plus
(paren
id|v2
op_rshift
l_int|8
)paren
suffix:semicolon
id|v2
op_and_assign
l_int|0xff
suffix:semicolon
)brace
id|v0
op_add_assign
id|v3
op_rshift
l_int|8
suffix:semicolon
id|v1
op_add_assign
id|map
(braket
l_int|1
)braket
op_plus
(paren
id|v0
op_rshift
l_int|8
)paren
suffix:semicolon
id|v2
op_add_assign
id|map
(braket
l_int|2
)braket
op_plus
(paren
id|v1
op_rshift
l_int|8
)paren
suffix:semicolon
id|v3
op_add_assign
id|map
(braket
l_int|3
)braket
op_plus
(paren
id|v2
op_rshift
l_int|8
)paren
suffix:semicolon
r_return
id|v0
op_xor
id|v1
op_xor
id|v2
op_xor
id|v3
suffix:semicolon
)brace
DECL|function|adfs_checkmap
r_static
r_int
id|adfs_checkmap
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|adfs_discmap
op_star
id|dm
)paren
(brace
r_int
r_char
id|crosscheck
op_assign
l_int|0
comma
id|zonecheck
op_assign
l_int|1
suffix:semicolon
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
id|ADFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_map_size
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_char
op_star
id|map
suffix:semicolon
id|map
op_assign
id|dm
(braket
id|i
)braket
dot
id|dm_bh-&gt;b_data
suffix:semicolon
r_if
c_cond
(paren
id|adfs_calczonecheck
c_func
(paren
id|sb
comma
id|map
)paren
op_ne
id|map
(braket
l_int|0
)braket
)paren
(brace
id|adfs_error
c_func
(paren
id|sb
comma
l_string|&quot;zone %d fails zonecheck&quot;
comma
id|i
)paren
suffix:semicolon
id|zonecheck
op_assign
l_int|0
suffix:semicolon
)brace
id|crosscheck
op_xor_assign
id|map
(braket
l_int|3
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|crosscheck
op_ne
l_int|0xff
)paren
id|adfs_error
c_func
(paren
id|sb
comma
l_string|&quot;crosscheck != 0xff&quot;
)paren
suffix:semicolon
r_return
id|crosscheck
op_eq
l_int|0xff
op_logical_and
id|zonecheck
suffix:semicolon
)brace
DECL|function|adfs_put_super
r_static
r_void
id|adfs_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_int
id|i
suffix:semicolon
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|asb-&gt;s_map_size
suffix:semicolon
id|i
op_increment
)paren
id|brelse
c_func
(paren
id|asb-&gt;s_map
(braket
id|i
)braket
dot
id|dm_bh
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|asb-&gt;s_map
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|asb
)paren
suffix:semicolon
id|sb-&gt;s_fs_info
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|parse_options
r_static
r_int
id|parse_options
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_char
op_star
id|options
)paren
(brace
r_char
op_star
id|value
comma
op_star
id|opt
suffix:semicolon
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
r_if
c_cond
(paren
op_logical_neg
id|options
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|opt
op_assign
id|strsep
c_func
(paren
op_amp
id|options
comma
l_string|&quot;,&quot;
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
op_star
id|opt
)paren
r_continue
suffix:semicolon
id|value
op_assign
id|strchr
c_func
(paren
id|opt
comma
l_char|&squot;=&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
)paren
op_star
id|value
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|opt
comma
l_string|&quot;uid&quot;
)paren
)paren
(brace
multiline_comment|/* owner of all files */
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|asb-&gt;s_uid
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|opt
comma
l_string|&quot;gid&quot;
)paren
)paren
(brace
multiline_comment|/* group owner of all files */
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|asb-&gt;s_gid
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|opt
comma
l_string|&quot;ownmask&quot;
)paren
)paren
(brace
multiline_comment|/* owner permission mask */
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|asb-&gt;s_owner_mask
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|opt
comma
l_string|&quot;othmask&quot;
)paren
)paren
(brace
multiline_comment|/* others permission mask */
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|asb-&gt;s_other_mask
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* eh? say again. */
id|printk
c_func
(paren
l_string|&quot;ADFS-fs: unrecognised mount option %s&bslash;n&quot;
comma
id|opt
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|adfs_remount
r_static
r_int
id|adfs_remount
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
op_star
id|flags
comma
r_char
op_star
id|data
)paren
(brace
r_return
id|parse_options
c_func
(paren
id|sb
comma
id|data
)paren
suffix:semicolon
)brace
DECL|function|adfs_statfs
r_static
r_int
id|adfs_statfs
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|statfs
op_star
id|buf
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
id|buf-&gt;f_type
op_assign
id|ADFS_SUPER_MAGIC
suffix:semicolon
id|buf-&gt;f_namelen
op_assign
id|asb-&gt;s_namelen
suffix:semicolon
id|buf-&gt;f_bsize
op_assign
id|sb-&gt;s_blocksize
suffix:semicolon
id|buf-&gt;f_blocks
op_assign
id|asb-&gt;s_size
suffix:semicolon
id|buf-&gt;f_files
op_assign
id|asb-&gt;s_ids_per_zone
op_star
id|asb-&gt;s_map_size
suffix:semicolon
id|buf-&gt;f_bavail
op_assign
id|buf-&gt;f_bfree
op_assign
id|adfs_map_free
c_func
(paren
id|sb
)paren
suffix:semicolon
id|buf-&gt;f_ffree
op_assign
id|buf-&gt;f_bfree
op_star
id|buf-&gt;f_files
op_div
id|buf-&gt;f_blocks
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|adfs_inode_cachep
r_static
id|kmem_cache_t
op_star
id|adfs_inode_cachep
suffix:semicolon
DECL|function|adfs_alloc_inode
r_static
r_struct
id|inode
op_star
id|adfs_alloc_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|adfs_inode_info
op_star
id|ei
suffix:semicolon
id|ei
op_assign
(paren
r_struct
id|adfs_inode_info
op_star
)paren
id|kmem_cache_alloc
c_func
(paren
id|adfs_inode_cachep
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
DECL|function|adfs_destroy_inode
r_static
r_void
id|adfs_destroy_inode
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
id|adfs_inode_cachep
comma
id|ADFS_I
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
id|adfs_inode_info
op_star
id|ei
op_assign
(paren
r_struct
id|adfs_inode_info
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
id|adfs_inode_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;adfs_inode_cache&quot;
comma
r_sizeof
(paren
r_struct
id|adfs_inode_info
)paren
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
comma
id|init_once
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|adfs_inode_cachep
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
id|adfs_inode_cachep
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;adfs_inode_cache: not all structures were freed&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|adfs_sops
r_static
r_struct
id|super_operations
id|adfs_sops
op_assign
(brace
dot
id|alloc_inode
op_assign
id|adfs_alloc_inode
comma
dot
id|destroy_inode
op_assign
id|adfs_destroy_inode
comma
dot
id|write_inode
op_assign
id|adfs_write_inode
comma
dot
id|put_super
op_assign
id|adfs_put_super
comma
dot
id|statfs
op_assign
id|adfs_statfs
comma
dot
id|remount_fs
op_assign
id|adfs_remount
comma
)brace
suffix:semicolon
DECL|function|adfs_read_map
r_static
r_struct
id|adfs_discmap
op_star
id|adfs_read_map
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|adfs_discrecord
op_star
id|dr
)paren
(brace
r_struct
id|adfs_discmap
op_star
id|dm
suffix:semicolon
r_int
r_int
id|map_addr
comma
id|zone_size
comma
id|nzones
suffix:semicolon
r_int
id|i
comma
id|zone
suffix:semicolon
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
id|nzones
op_assign
id|asb-&gt;s_map_size
suffix:semicolon
id|zone_size
op_assign
(paren
l_int|8
op_lshift
id|dr-&gt;log2secsize
)paren
op_minus
id|le16_to_cpu
c_func
(paren
id|dr-&gt;zone_spare
)paren
suffix:semicolon
id|map_addr
op_assign
(paren
id|nzones
op_rshift
l_int|1
)paren
op_star
id|zone_size
op_minus
(paren
(paren
id|nzones
OG
l_int|1
)paren
ques
c_cond
id|ADFS_DR_SIZE_BITS
suffix:colon
l_int|0
)paren
suffix:semicolon
id|map_addr
op_assign
id|signed_asl
c_func
(paren
id|map_addr
comma
id|asb-&gt;s_map2blk
)paren
suffix:semicolon
id|asb-&gt;s_ids_per_zone
op_assign
id|zone_size
op_div
(paren
id|asb-&gt;s_idlen
op_plus
l_int|1
)paren
suffix:semicolon
id|dm
op_assign
id|kmalloc
c_func
(paren
id|nzones
op_star
r_sizeof
(paren
op_star
id|dm
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dm
op_eq
l_int|NULL
)paren
(brace
id|adfs_error
c_func
(paren
id|sb
comma
l_string|&quot;not enough memory&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_for
c_loop
(paren
id|zone
op_assign
l_int|0
suffix:semicolon
id|zone
OL
id|nzones
suffix:semicolon
id|zone
op_increment
comma
id|map_addr
op_increment
)paren
(brace
id|dm
(braket
id|zone
)braket
dot
id|dm_startbit
op_assign
l_int|0
suffix:semicolon
id|dm
(braket
id|zone
)braket
dot
id|dm_endbit
op_assign
id|zone_size
suffix:semicolon
id|dm
(braket
id|zone
)braket
dot
id|dm_startblk
op_assign
id|zone
op_star
id|zone_size
op_minus
id|ADFS_DR_SIZE_BITS
suffix:semicolon
id|dm
(braket
id|zone
)braket
dot
id|dm_bh
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
id|map_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dm
(braket
id|zone
)braket
dot
id|dm_bh
)paren
(brace
id|adfs_error
c_func
(paren
id|sb
comma
l_string|&quot;unable to read map&quot;
)paren
suffix:semicolon
r_goto
id|error_free
suffix:semicolon
)brace
)brace
multiline_comment|/* adjust the limits for the first and last map zones */
id|i
op_assign
id|zone
op_minus
l_int|1
suffix:semicolon
id|dm
(braket
l_int|0
)braket
dot
id|dm_startblk
op_assign
l_int|0
suffix:semicolon
id|dm
(braket
l_int|0
)braket
dot
id|dm_startbit
op_assign
id|ADFS_DR_SIZE_BITS
suffix:semicolon
id|dm
(braket
id|i
)braket
dot
id|dm_endbit
op_assign
(paren
id|dr-&gt;disc_size_high
op_lshift
(paren
l_int|32
op_minus
id|dr-&gt;log2bpmb
)paren
)paren
op_plus
(paren
id|dr-&gt;disc_size
op_rshift
id|dr-&gt;log2bpmb
)paren
op_plus
(paren
id|ADFS_DR_SIZE_BITS
op_minus
id|i
op_star
id|zone_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|adfs_checkmap
c_func
(paren
id|sb
comma
id|dm
)paren
)paren
r_return
id|dm
suffix:semicolon
id|adfs_error
c_func
(paren
id|sb
comma
l_int|NULL
comma
l_string|&quot;map corrupted&quot;
)paren
suffix:semicolon
id|error_free
suffix:colon
r_while
c_loop
(paren
op_decrement
id|zone
op_ge
l_int|0
)paren
id|brelse
c_func
(paren
id|dm
(braket
id|zone
)braket
dot
id|dm_bh
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dm
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|adfs_discsize
r_static
r_inline
r_int
r_int
id|adfs_discsize
c_func
(paren
r_struct
id|adfs_discrecord
op_star
id|dr
comma
r_int
id|block_bits
)paren
(brace
r_int
r_int
id|discsize
suffix:semicolon
id|discsize
op_assign
id|le32_to_cpu
c_func
(paren
id|dr-&gt;disc_size_high
)paren
op_lshift
(paren
l_int|32
op_minus
id|block_bits
)paren
suffix:semicolon
id|discsize
op_or_assign
id|le32_to_cpu
c_func
(paren
id|dr-&gt;disc_size
)paren
op_rshift
id|block_bits
suffix:semicolon
r_return
id|discsize
suffix:semicolon
)brace
DECL|function|adfs_fill_super
r_static
r_int
id|adfs_fill_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_void
op_star
id|data
comma
r_int
id|silent
)paren
(brace
r_struct
id|adfs_discrecord
op_star
id|dr
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|object_info
id|root_obj
suffix:semicolon
r_int
r_char
op_star
id|b_data
suffix:semicolon
r_struct
id|adfs_sb_info
op_star
id|asb
suffix:semicolon
id|asb
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|asb
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|asb
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|sb-&gt;s_fs_info
op_assign
id|asb
suffix:semicolon
id|memset
c_func
(paren
id|asb
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|asb
)paren
)paren
suffix:semicolon
multiline_comment|/* set default options */
id|asb-&gt;s_uid
op_assign
l_int|0
suffix:semicolon
id|asb-&gt;s_gid
op_assign
l_int|0
suffix:semicolon
id|asb-&gt;s_owner_mask
op_assign
id|S_IRWXU
suffix:semicolon
id|asb-&gt;s_other_mask
op_assign
id|S_IRWXG
op_or
id|S_IRWXO
suffix:semicolon
r_if
c_cond
(paren
id|parse_options
c_func
(paren
id|sb
comma
id|data
)paren
)paren
r_goto
id|error
suffix:semicolon
id|sb_set_blocksize
c_func
(paren
id|sb
comma
id|BLOCK_SIZE
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
id|ADFS_DISCRECORD
op_div
id|BLOCK_SIZE
)paren
)paren
)paren
(brace
id|adfs_error
c_func
(paren
id|sb
comma
l_string|&quot;unable to read superblock&quot;
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|b_data
op_assign
id|bh-&gt;b_data
op_plus
(paren
id|ADFS_DISCRECORD
op_mod
id|BLOCK_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|adfs_checkbblk
c_func
(paren
id|b_data
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
id|printk
c_func
(paren
l_string|&quot;VFS: Can&squot;t find an adfs filesystem on dev &quot;
l_string|&quot;%s.&bslash;n&quot;
comma
id|sb-&gt;s_id
)paren
suffix:semicolon
r_goto
id|error_free_bh
suffix:semicolon
)brace
id|dr
op_assign
(paren
r_struct
id|adfs_discrecord
op_star
)paren
(paren
id|b_data
op_plus
id|ADFS_DR_OFFSET
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Do some sanity checks on the ADFS disc record&n;&t; */
r_if
c_cond
(paren
id|adfs_checkdiscrecord
c_func
(paren
id|dr
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
id|printk
c_func
(paren
l_string|&quot;VPS: Can&squot;t find an adfs filesystem on dev &quot;
l_string|&quot;%s.&bslash;n&quot;
comma
id|sb-&gt;s_id
)paren
suffix:semicolon
r_goto
id|error_free_bh
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
id|sb_set_blocksize
c_func
(paren
id|sb
comma
l_int|1
op_lshift
id|dr-&gt;log2secsize
)paren
)paren
(brace
id|bh
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
id|ADFS_DISCRECORD
op_div
id|sb-&gt;s_blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|adfs_error
c_func
(paren
id|sb
comma
l_string|&quot;couldn&squot;t read superblock on &quot;
l_string|&quot;2nd try.&quot;
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|b_data
op_assign
id|bh-&gt;b_data
op_plus
(paren
id|ADFS_DISCRECORD
op_mod
id|sb-&gt;s_blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|adfs_checkbblk
c_func
(paren
id|b_data
)paren
)paren
(brace
id|adfs_error
c_func
(paren
id|sb
comma
l_string|&quot;disc record mismatch, very weird!&quot;
)paren
suffix:semicolon
r_goto
id|error_free_bh
suffix:semicolon
)brace
id|dr
op_assign
(paren
r_struct
id|adfs_discrecord
op_star
)paren
(paren
id|b_data
op_plus
id|ADFS_DR_OFFSET
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;VFS: Unsupported blocksize on dev &quot;
l_string|&quot;%s.&bslash;n&quot;
comma
id|sb-&gt;s_id
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * blocksize on this device should now be set to the ADFS log2secsize&n;&t; */
id|sb-&gt;s_magic
op_assign
id|ADFS_SUPER_MAGIC
suffix:semicolon
id|asb-&gt;s_idlen
op_assign
id|dr-&gt;idlen
suffix:semicolon
id|asb-&gt;s_map_size
op_assign
id|dr-&gt;nzones
op_or
(paren
id|dr-&gt;nzones_high
op_lshift
l_int|8
)paren
suffix:semicolon
id|asb-&gt;s_map2blk
op_assign
id|dr-&gt;log2bpmb
op_minus
id|dr-&gt;log2secsize
suffix:semicolon
id|asb-&gt;s_size
op_assign
id|adfs_discsize
c_func
(paren
id|dr
comma
id|sb-&gt;s_blocksize_bits
)paren
suffix:semicolon
id|asb-&gt;s_version
op_assign
id|dr-&gt;format_version
suffix:semicolon
id|asb-&gt;s_log2sharesize
op_assign
id|dr-&gt;log2sharesize
suffix:semicolon
id|asb-&gt;s_map
op_assign
id|adfs_read_map
c_func
(paren
id|sb
comma
id|dr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|asb-&gt;s_map
)paren
r_goto
id|error_free_bh
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * set up enough so that we can read an inode&n;&t; */
id|sb-&gt;s_op
op_assign
op_amp
id|adfs_sops
suffix:semicolon
id|dr
op_assign
(paren
r_struct
id|adfs_discrecord
op_star
)paren
(paren
id|asb-&gt;s_map
(braket
l_int|0
)braket
dot
id|dm_bh-&gt;b_data
op_plus
l_int|4
)paren
suffix:semicolon
id|root_obj.parent_id
op_assign
id|root_obj.file_id
op_assign
id|le32_to_cpu
c_func
(paren
id|dr-&gt;root
)paren
suffix:semicolon
id|root_obj.name_len
op_assign
l_int|0
suffix:semicolon
id|root_obj.loadaddr
op_assign
l_int|0
suffix:semicolon
id|root_obj.execaddr
op_assign
l_int|0
suffix:semicolon
id|root_obj.size
op_assign
id|ADFS_NEWDIR_SIZE
suffix:semicolon
id|root_obj.attr
op_assign
id|ADFS_NDA_DIRECTORY
op_or
id|ADFS_NDA_OWNER_READ
op_or
id|ADFS_NDA_OWNER_WRITE
op_or
id|ADFS_NDA_PUBLIC_READ
suffix:semicolon
multiline_comment|/*&n;&t; * If this is a F+ disk with variable length directories,&n;&t; * get the root_size from the disc record.&n;&t; */
r_if
c_cond
(paren
id|asb-&gt;s_version
)paren
(brace
id|root_obj.size
op_assign
id|dr-&gt;root_size
suffix:semicolon
id|asb-&gt;s_dir
op_assign
op_amp
id|adfs_fplus_dir_ops
suffix:semicolon
id|asb-&gt;s_namelen
op_assign
id|ADFS_FPLUS_NAME_LEN
suffix:semicolon
)brace
r_else
(brace
id|asb-&gt;s_dir
op_assign
op_amp
id|adfs_f_dir_ops
suffix:semicolon
id|asb-&gt;s_namelen
op_assign
id|ADFS_F_NAME_LEN
suffix:semicolon
)brace
id|sb-&gt;s_root
op_assign
id|d_alloc_root
c_func
(paren
id|adfs_iget
c_func
(paren
id|sb
comma
op_amp
id|root_obj
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;s_root
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
id|asb-&gt;s_map_size
suffix:semicolon
id|i
op_increment
)paren
id|brelse
c_func
(paren
id|asb-&gt;s_map
(braket
id|i
)braket
dot
id|dm_bh
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|asb-&gt;s_map
)paren
suffix:semicolon
id|adfs_error
c_func
(paren
id|sb
comma
l_string|&quot;get root inode failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
r_else
id|sb-&gt;s_root-&gt;d_op
op_assign
op_amp
id|adfs_dentry_operations
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|error_free_bh
suffix:colon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|error
suffix:colon
id|sb-&gt;s_fs_info
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|asb
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|adfs_get_sb
r_static
r_struct
id|super_block
op_star
id|adfs_get_sb
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
id|adfs_fill_super
)paren
suffix:semicolon
)brace
DECL|variable|adfs_fs_type
r_static
r_struct
id|file_system_type
id|adfs_fs_type
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
l_string|&quot;adfs&quot;
comma
dot
id|get_sb
op_assign
id|adfs_get_sb
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
DECL|function|init_adfs_fs
r_static
r_int
id|__init
id|init_adfs_fs
c_func
(paren
r_void
)paren
(brace
r_int
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
id|adfs_fs_type
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
DECL|function|exit_adfs_fs
r_static
r_void
id|__exit
id|exit_adfs_fs
c_func
(paren
r_void
)paren
(brace
id|unregister_filesystem
c_func
(paren
op_amp
id|adfs_fs_type
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
id|init_adfs_fs
)paren
id|module_exit
c_func
(paren
id|exit_adfs_fs
)paren
eof
