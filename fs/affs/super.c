multiline_comment|/*&n; *  linux/fs/affs/inode.c&n; *&n; *  (c) 1996  Hans-Joachim Widmaier - Rewritten&n; *&n; *  (C) 1993  Ray Burr - Modified for Amiga FFS filesystem.&n; *&n; *  (C) 1992  Eric Youngdale Modified for ISO 9660 filesystem.&n; *&n; *  (C) 1991  Linus Torvalds - minix filesystem&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/affs_fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/amigaffs.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_extern
r_int
op_star
id|blk_size
(braket
)braket
suffix:semicolon
r_extern
r_struct
id|timezone
id|sys_tz
suffix:semicolon
r_static
r_int
id|affs_statfs
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
suffix:semicolon
r_static
r_int
id|affs_remount
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
suffix:semicolon
r_static
r_void
DECL|function|affs_put_super
id|affs_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: put_super()&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
(brace
id|AFFS_ROOT_TAIL
c_func
(paren
id|sb
comma
id|AFFS_SB-&gt;s_root_bh
)paren
op_member_access_from_pointer
id|bm_flag
op_assign
id|be32_to_cpu
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|secs_to_datestamp
c_func
(paren
id|CURRENT_TIME
comma
op_amp
id|AFFS_ROOT_TAIL
c_func
(paren
id|sb
comma
id|AFFS_SB-&gt;s_root_bh
)paren
op_member_access_from_pointer
id|disk_change
)paren
suffix:semicolon
id|affs_fix_checksum
c_func
(paren
id|sb
comma
id|AFFS_SB-&gt;s_root_bh
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|AFFS_SB-&gt;s_root_bh
)paren
suffix:semicolon
)brace
id|affs_brelse
c_func
(paren
id|AFFS_SB-&gt;s_bmap_bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|AFFS_SB-&gt;s_prefix
)paren
id|kfree
c_func
(paren
id|AFFS_SB-&gt;s_prefix
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|AFFS_SB-&gt;s_bitmap
)paren
suffix:semicolon
id|affs_brelse
c_func
(paren
id|AFFS_SB-&gt;s_root_bh
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_static
r_void
DECL|function|affs_write_super
id|affs_write_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_int
id|clean
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
(brace
singleline_comment|//&t;if (AFFS_SB-&gt;s_bitmap[i].bm_bh) {
singleline_comment|//&t;&t;if (buffer_dirty(AFFS_SB-&gt;s_bitmap[i].bm_bh)) {
singleline_comment|//&t;&t;&t;clean = 0;
id|AFFS_ROOT_TAIL
c_func
(paren
id|sb
comma
id|AFFS_SB-&gt;s_root_bh
)paren
op_member_access_from_pointer
id|bm_flag
op_assign
id|be32_to_cpu
c_func
(paren
id|clean
)paren
suffix:semicolon
id|secs_to_datestamp
c_func
(paren
id|CURRENT_TIME
comma
op_amp
id|AFFS_ROOT_TAIL
c_func
(paren
id|sb
comma
id|AFFS_SB-&gt;s_root_bh
)paren
op_member_access_from_pointer
id|disk_change
)paren
suffix:semicolon
id|affs_fix_checksum
c_func
(paren
id|sb
comma
id|AFFS_SB-&gt;s_root_bh
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|AFFS_SB-&gt;s_root_bh
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
op_logical_neg
id|clean
suffix:semicolon
multiline_comment|/* redo until bitmap synced */
)brace
r_else
id|sb-&gt;s_dirt
op_assign
l_int|0
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: write_super() at %lu, clean=%d&bslash;n&quot;
comma
id|CURRENT_TIME
comma
id|clean
)paren
suffix:semicolon
)brace
DECL|variable|affs_sops
r_static
r_struct
id|super_operations
id|affs_sops
op_assign
(brace
id|read_inode
suffix:colon
id|affs_read_inode
comma
id|write_inode
suffix:colon
id|affs_write_inode
comma
id|put_inode
suffix:colon
id|affs_put_inode
comma
id|delete_inode
suffix:colon
id|affs_delete_inode
comma
id|clear_inode
suffix:colon
id|affs_clear_inode
comma
id|put_super
suffix:colon
id|affs_put_super
comma
id|write_super
suffix:colon
id|affs_write_super
comma
id|statfs
suffix:colon
id|affs_statfs
comma
id|remount_fs
suffix:colon
id|affs_remount
comma
)brace
suffix:semicolon
r_static
r_int
DECL|function|parse_options
id|parse_options
c_func
(paren
r_char
op_star
id|options
comma
id|uid_t
op_star
id|uid
comma
id|gid_t
op_star
id|gid
comma
r_int
op_star
id|mode
comma
r_int
op_star
id|reserved
comma
id|s32
op_star
id|root
comma
r_int
op_star
id|blocksize
comma
r_char
op_star
op_star
id|prefix
comma
r_char
op_star
id|volume
comma
r_int
r_int
op_star
id|mount_opts
)paren
(brace
r_char
op_star
id|this_char
comma
op_star
id|value
comma
op_star
id|optn
suffix:semicolon
r_int
id|f
suffix:semicolon
multiline_comment|/* Fill in defaults */
op_star
id|uid
op_assign
id|current-&gt;uid
suffix:semicolon
op_star
id|gid
op_assign
id|current-&gt;gid
suffix:semicolon
op_star
id|reserved
op_assign
l_int|2
suffix:semicolon
op_star
id|root
op_assign
op_minus
l_int|1
suffix:semicolon
op_star
id|blocksize
op_assign
op_minus
l_int|1
suffix:semicolon
id|volume
(braket
l_int|0
)braket
op_assign
l_char|&squot;:&squot;
suffix:semicolon
id|volume
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
op_star
id|mount_opts
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|options
)paren
r_return
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|this_char
op_assign
id|strtok
c_func
(paren
id|options
comma
l_string|&quot;,&quot;
)paren
suffix:semicolon
id|this_char
suffix:semicolon
id|this_char
op_assign
id|strtok
c_func
(paren
l_int|NULL
comma
l_string|&quot;,&quot;
)paren
)paren
(brace
id|f
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|value
op_assign
id|strchr
c_func
(paren
id|this_char
comma
l_char|&squot;=&squot;
)paren
)paren
op_ne
l_int|NULL
)paren
op_star
id|value
op_increment
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|optn
op_assign
l_string|&quot;protect&quot;
)paren
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
id|optn
)paren
)paren
(brace
r_if
c_cond
(paren
id|value
)paren
r_goto
id|out_inv_arg
suffix:semicolon
op_star
id|mount_opts
op_or_assign
id|SF_IMMUTABLE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|optn
op_assign
l_string|&quot;verbose&quot;
)paren
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
id|optn
)paren
)paren
(brace
r_if
c_cond
(paren
id|value
)paren
r_goto
id|out_inv_arg
suffix:semicolon
op_star
id|mount_opts
op_or_assign
id|SF_VERBOSE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|optn
op_assign
l_string|&quot;mufs&quot;
)paren
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
id|optn
)paren
)paren
(brace
r_if
c_cond
(paren
id|value
)paren
r_goto
id|out_inv_arg
suffix:semicolon
op_star
id|mount_opts
op_or_assign
id|SF_MUFS
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|f
op_assign
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;setuid&quot;
)paren
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;setgid&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|value
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|value
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;AFFS: Argument for set[ug]id option missing&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
(paren
id|f
ques
c_cond
op_star
id|uid
suffix:colon
op_star
id|gid
)paren
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
(brace
id|printk
c_func
(paren
l_string|&quot;AFFS: Bad set[ug]id argument&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|mount_opts
op_or_assign
id|f
ques
c_cond
id|SF_SETUID
suffix:colon
id|SF_SETGID
suffix:semicolon
)brace
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;prefix&quot;
)paren
)paren
(brace
id|optn
op_assign
l_string|&quot;prefix&quot;
suffix:semicolon
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
r_goto
id|out_no_arg
suffix:semicolon
r_if
c_cond
(paren
op_star
id|prefix
)paren
(brace
multiline_comment|/* Free any previous prefix */
id|kfree
c_func
(paren
op_star
id|prefix
)paren
suffix:semicolon
op_star
id|prefix
op_assign
l_int|NULL
suffix:semicolon
)brace
op_star
id|prefix
op_assign
id|kmalloc
c_func
(paren
id|strlen
c_func
(paren
id|value
)paren
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|prefix
)paren
r_return
l_int|0
suffix:semicolon
id|strcpy
c_func
(paren
op_star
id|prefix
comma
id|value
)paren
suffix:semicolon
op_star
id|mount_opts
op_or_assign
id|SF_PREFIX
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
id|this_char
comma
l_string|&quot;volume&quot;
)paren
)paren
(brace
id|optn
op_assign
l_string|&quot;volume&quot;
suffix:semicolon
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
r_goto
id|out_no_arg
suffix:semicolon
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|value
)paren
OG
l_int|30
)paren
id|value
(braket
l_int|30
)braket
op_assign
l_int|0
suffix:semicolon
id|strncpy
c_func
(paren
id|volume
comma
id|value
comma
l_int|30
)paren
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
id|this_char
comma
l_string|&quot;mode&quot;
)paren
)paren
(brace
id|optn
op_assign
l_string|&quot;mode&quot;
suffix:semicolon
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
r_goto
id|out_no_arg
suffix:semicolon
op_star
id|mode
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
op_amp
l_int|0777
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|mount_opts
op_or_assign
id|SF_SETMODE
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
id|this_char
comma
l_string|&quot;reserved&quot;
)paren
)paren
(brace
id|optn
op_assign
l_string|&quot;reserved&quot;
suffix:semicolon
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
r_goto
id|out_no_arg
suffix:semicolon
op_star
id|reserved
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
l_int|0
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
id|this_char
comma
l_string|&quot;root&quot;
)paren
)paren
(brace
id|optn
op_assign
l_string|&quot;root&quot;
suffix:semicolon
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
r_goto
id|out_no_arg
suffix:semicolon
op_star
id|root
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
l_int|0
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
id|this_char
comma
l_string|&quot;bs&quot;
)paren
)paren
(brace
id|optn
op_assign
l_string|&quot;bs&quot;
suffix:semicolon
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
r_goto
id|out_no_arg
suffix:semicolon
op_star
id|blocksize
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
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|blocksize
op_ne
l_int|512
op_logical_and
op_star
id|blocksize
op_ne
l_int|1024
op_logical_and
op_star
id|blocksize
op_ne
l_int|2048
op_logical_and
op_star
id|blocksize
op_ne
l_int|4096
)paren
(brace
id|printk
(paren
l_string|&quot;AFFS: Invalid blocksize (512, 1024, 2048, 4096 allowed)&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
(paren
id|this_char
comma
l_string|&quot;grpquota&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
(paren
id|this_char
comma
l_string|&quot;noquota&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
(paren
id|this_char
comma
l_string|&quot;quota&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
(paren
id|this_char
comma
l_string|&quot;usrquota&quot;
)paren
)paren
multiline_comment|/* Silently ignore the quota options */
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;AFFS: Unrecognized mount option %s&bslash;n&quot;
comma
id|this_char
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
id|out_no_arg
suffix:colon
id|printk
c_func
(paren
l_string|&quot;AFFS: The %s option requires an argument&bslash;n&quot;
comma
id|optn
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_inv_arg
suffix:colon
id|printk
c_func
(paren
l_string|&quot;AFFS: Option %s does not take an argument&bslash;n&quot;
comma
id|optn
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* This function definitely needs to be split up. Some fine day I&squot;ll&n; * hopefully have the guts to do so. Until then: sorry for the mess.&n; */
r_static
r_struct
id|super_block
op_star
DECL|function|affs_read_super
id|affs_read_super
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
id|buffer_head
op_star
id|root_bh
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|buffer_head
op_star
id|boot_bh
suffix:semicolon
r_struct
id|inode
op_star
id|root_inode
op_assign
l_int|NULL
suffix:semicolon
id|kdev_t
id|dev
op_assign
id|sb-&gt;s_dev
suffix:semicolon
id|s32
id|root_block
suffix:semicolon
r_int
id|blocks
comma
id|size
comma
id|blocksize
suffix:semicolon
id|u32
id|chksum
suffix:semicolon
r_int
id|num_bm
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
id|s32
id|key
suffix:semicolon
id|uid_t
id|uid
suffix:semicolon
id|gid_t
id|gid
suffix:semicolon
r_int
id|reserved
suffix:semicolon
r_int
r_int
id|mount_flags
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: read_super(%s)&bslash;n&quot;
comma
id|data
ques
c_cond
(paren
r_const
r_char
op_star
)paren
id|data
suffix:colon
l_string|&quot;no options&quot;
)paren
suffix:semicolon
id|sb-&gt;s_magic
op_assign
id|AFFS_SUPER_MAGIC
suffix:semicolon
id|sb-&gt;s_op
op_assign
op_amp
id|affs_sops
suffix:semicolon
id|memset
c_func
(paren
id|AFFS_SB
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|affs_sb_info
)paren
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|AFFS_SB-&gt;s_bmlock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parse_options
c_func
(paren
id|data
comma
op_amp
id|uid
comma
op_amp
id|gid
comma
op_amp
id|i
comma
op_amp
id|reserved
comma
op_amp
id|root_block
comma
op_amp
id|blocksize
comma
op_amp
id|AFFS_SB-&gt;s_prefix
comma
id|AFFS_SB-&gt;s_volume
comma
op_amp
id|mount_flags
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AFFS: Error parsing options&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* N.B. after this point s_prefix must be released */
id|AFFS_SB-&gt;s_flags
op_assign
id|mount_flags
suffix:semicolon
id|AFFS_SB-&gt;s_mode
op_assign
id|i
suffix:semicolon
id|AFFS_SB-&gt;s_uid
op_assign
id|uid
suffix:semicolon
id|AFFS_SB-&gt;s_gid
op_assign
id|gid
suffix:semicolon
id|AFFS_SB-&gt;s_reserved
op_assign
id|reserved
suffix:semicolon
multiline_comment|/* Get the size of the device in 512-byte blocks.&n;&t; * If we later see that the partition uses bigger&n;&t; * blocks, we will have to change it.&n;&t; */
id|blocks
op_assign
id|blk_size
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
ques
c_cond
id|blk_size
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
(braket
id|MINOR
c_func
(paren
id|dev
)paren
)braket
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|blocks
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AFFS: Could not determine device size&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_error
suffix:semicolon
)brace
id|size
op_assign
(paren
id|BLOCK_SIZE
op_div
l_int|512
)paren
op_star
id|blocks
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: initial blksize=%d, blocks=%d&bslash;n&quot;
comma
l_int|512
comma
id|blocks
)paren
suffix:semicolon
macro_line|#warning
id|affs_set_blocksize
c_func
(paren
id|sb
comma
id|PAGE_SIZE
)paren
suffix:semicolon
multiline_comment|/* Try to find root block. Its location depends on the block size. */
id|i
op_assign
l_int|512
suffix:semicolon
id|j
op_assign
l_int|4096
suffix:semicolon
r_if
c_cond
(paren
id|blocksize
OG
l_int|0
)paren
(brace
id|i
op_assign
id|j
op_assign
id|blocksize
suffix:semicolon
id|size
op_assign
id|size
op_div
(paren
id|blocksize
op_div
l_int|512
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|blocksize
op_assign
id|i
comma
id|key
op_assign
l_int|0
suffix:semicolon
id|blocksize
op_le
id|j
suffix:semicolon
id|blocksize
op_lshift_assign
l_int|1
comma
id|size
op_rshift_assign
l_int|1
)paren
(brace
id|AFFS_SB-&gt;s_root_block
op_assign
id|root_block
suffix:semicolon
r_if
c_cond
(paren
id|root_block
OL
l_int|0
)paren
id|AFFS_SB-&gt;s_root_block
op_assign
(paren
id|reserved
op_plus
id|size
op_minus
l_int|1
)paren
op_div
l_int|2
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: setting blocksize to %d&bslash;n&quot;
comma
id|blocksize
)paren
suffix:semicolon
id|affs_set_blocksize
c_func
(paren
id|sb
comma
id|blocksize
)paren
suffix:semicolon
id|AFFS_SB-&gt;s_partition_size
op_assign
id|size
suffix:semicolon
multiline_comment|/* The root block location that was calculated above is not&n;&t;&t; * correct if the partition size is an odd number of 512-&n;&t;&t; * byte blocks, which will be rounded down to a number of&n;&t;&t; * 1024-byte blocks, and if there were an even number of&n;&t;&t; * reserved blocks. Ideally, all partition checkers should&n;&t;&t; * report the real number of blocks of the real blocksize,&n;&t;&t; * but since this just cannot be done, we have to try to&n;&t;&t; * find the root block anyways. In the above case, it is one&n;&t;&t; * block behind the calculated one. So we check this one, too.&n;&t;&t; */
r_for
c_loop
(paren
id|num_bm
op_assign
l_int|0
suffix:semicolon
id|num_bm
OL
l_int|2
suffix:semicolon
id|num_bm
op_increment
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: Dev %s, trying root=%u, bs=%d, &quot;
l_string|&quot;size=%d, reserved=%d&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|dev
)paren
comma
id|AFFS_SB-&gt;s_root_block
op_plus
id|num_bm
comma
id|blocksize
comma
id|size
comma
id|reserved
)paren
suffix:semicolon
id|root_bh
op_assign
id|affs_bread
c_func
(paren
id|sb
comma
id|AFFS_SB-&gt;s_root_block
op_plus
id|num_bm
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root_bh
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|affs_checksum_block
c_func
(paren
id|sb
comma
id|root_bh
)paren
op_logical_and
id|be32_to_cpu
c_func
(paren
id|AFFS_ROOT_HEAD
c_func
(paren
id|root_bh
)paren
op_member_access_from_pointer
id|ptype
)paren
op_eq
id|T_SHORT
op_logical_and
id|be32_to_cpu
c_func
(paren
id|AFFS_ROOT_TAIL
c_func
(paren
id|sb
comma
id|root_bh
)paren
op_member_access_from_pointer
id|stype
)paren
op_eq
id|ST_ROOT
)paren
(brace
id|AFFS_SB-&gt;s_hashsize
op_assign
id|blocksize
op_div
l_int|4
op_minus
l_int|56
suffix:semicolon
id|AFFS_SB-&gt;s_root_block
op_add_assign
id|num_bm
suffix:semicolon
id|key
op_assign
l_int|1
suffix:semicolon
r_goto
id|got_root
suffix:semicolon
)brace
id|affs_brelse
c_func
(paren
id|root_bh
)paren
suffix:semicolon
id|root_bh
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
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
l_string|&quot;AFFS: No valid root block on device %s&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_goto
id|out_error
suffix:semicolon
multiline_comment|/* N.B. after this point bh must be released */
id|got_root
suffix:colon
id|root_block
op_assign
id|AFFS_SB-&gt;s_root_block
suffix:semicolon
id|sb-&gt;s_blocksize_bits
op_assign
id|blocksize
op_eq
l_int|512
ques
c_cond
l_int|9
suffix:colon
id|blocksize
op_eq
l_int|1024
ques
c_cond
l_int|10
suffix:colon
id|blocksize
op_eq
l_int|2048
ques
c_cond
l_int|11
suffix:colon
l_int|12
suffix:semicolon
multiline_comment|/* Find out which kind of FS we have */
id|boot_bh
op_assign
id|bread
c_func
(paren
id|sb-&gt;s_dev
comma
l_int|0
comma
id|sb-&gt;s_blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|boot_bh
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AFFS: Cannot read boot block&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_error
suffix:semicolon
)brace
id|chksum
op_assign
id|be32_to_cpu
c_func
(paren
op_star
(paren
id|u32
op_star
)paren
id|boot_bh-&gt;b_data
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|boot_bh
)paren
suffix:semicolon
multiline_comment|/* Dircache filesystems are compatible with non-dircache ones&n;&t; * when reading. As long as they aren&squot;t supported, writing is&n;&t; * not recommended.&n;&t; */
r_if
c_cond
(paren
(paren
id|chksum
op_eq
id|FS_DCFFS
op_logical_or
id|chksum
op_eq
id|MUFS_DCFFS
op_logical_or
id|chksum
op_eq
id|FS_DCOFS
op_logical_or
id|chksum
op_eq
id|MUFS_DCOFS
)paren
op_logical_and
op_logical_neg
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;AFFS: Dircache FS - mounting %s read only&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
id|sb-&gt;s_flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
id|AFFS_SB-&gt;s_flags
op_or_assign
id|SF_READONLY
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|chksum
)paren
(brace
r_case
id|MUFS_FS
suffix:colon
r_case
id|MUFS_INTLFFS
suffix:colon
r_case
id|MUFS_DCFFS
suffix:colon
id|AFFS_SB-&gt;s_flags
op_or_assign
id|SF_MUFS
suffix:semicolon
multiline_comment|/* fall thru */
r_case
id|FS_INTLFFS
suffix:colon
r_case
id|FS_DCFFS
suffix:colon
id|AFFS_SB-&gt;s_flags
op_or_assign
id|SF_INTL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MUFS_FFS
suffix:colon
id|AFFS_SB-&gt;s_flags
op_or_assign
id|SF_MUFS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FS_FFS
suffix:colon
r_break
suffix:semicolon
r_case
id|MUFS_OFS
suffix:colon
id|AFFS_SB-&gt;s_flags
op_or_assign
id|SF_MUFS
suffix:semicolon
multiline_comment|/* fall thru */
r_case
id|FS_OFS
suffix:colon
id|AFFS_SB-&gt;s_flags
op_or_assign
id|SF_OFS
suffix:semicolon
id|sb-&gt;s_flags
op_or_assign
id|MS_NOEXEC
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MUFS_DCOFS
suffix:colon
r_case
id|MUFS_INTLOFS
suffix:colon
id|AFFS_SB-&gt;s_flags
op_or_assign
id|SF_MUFS
suffix:semicolon
r_case
id|FS_DCOFS
suffix:colon
r_case
id|FS_INTLOFS
suffix:colon
id|AFFS_SB-&gt;s_flags
op_or_assign
id|SF_INTL
op_or
id|SF_OFS
suffix:semicolon
id|sb-&gt;s_flags
op_or_assign
id|MS_NOEXEC
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AFFS: Unknown filesystem on device %s: %08X&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|dev
)paren
comma
id|chksum
)paren
suffix:semicolon
r_goto
id|out_error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mount_flags
op_amp
id|SF_VERBOSE
)paren
(brace
id|chksum
op_assign
id|cpu_to_be32
c_func
(paren
id|chksum
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;AFFS: Mounting volume &bslash;&quot;%*s&bslash;&quot;: Type=%.3s&bslash;&bslash;%c, Blocksize=%d&bslash;n&quot;
comma
id|AFFS_ROOT_TAIL
c_func
(paren
id|sb
comma
id|root_bh
)paren
op_member_access_from_pointer
id|disk_name
(braket
l_int|0
)braket
comma
id|AFFS_ROOT_TAIL
c_func
(paren
id|sb
comma
id|root_bh
)paren
op_member_access_from_pointer
id|disk_name
op_plus
l_int|1
comma
(paren
r_char
op_star
)paren
op_amp
id|chksum
comma
(paren
(paren
r_char
op_star
)paren
op_amp
id|chksum
)paren
(braket
l_int|3
)braket
op_plus
l_char|&squot;0&squot;
comma
id|blocksize
)paren
suffix:semicolon
)brace
id|sb-&gt;s_flags
op_or_assign
id|MS_NODEV
op_or
id|MS_NOSUID
suffix:semicolon
id|AFFS_SB-&gt;s_data_blksize
op_assign
id|sb-&gt;s_blocksize
suffix:semicolon
r_if
c_cond
(paren
id|AFFS_SB-&gt;s_flags
op_amp
id|SF_OFS
)paren
id|AFFS_SB-&gt;s_data_blksize
op_sub_assign
l_int|24
suffix:semicolon
multiline_comment|/* Keep super block in cache */
id|AFFS_SB-&gt;s_root_bh
op_assign
id|root_bh
suffix:semicolon
multiline_comment|/* N.B. after this point s_root_bh must be released */
r_if
c_cond
(paren
id|affs_init_bitmap
c_func
(paren
id|sb
)paren
)paren
r_goto
id|out_error
suffix:semicolon
multiline_comment|/* set up enough so that it can read an inode */
id|root_inode
op_assign
id|iget
c_func
(paren
id|sb
comma
id|root_block
)paren
suffix:semicolon
id|sb-&gt;s_root
op_assign
id|d_alloc_root
c_func
(paren
id|root_inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;s_root
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AFFS: Get root inode failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_error
suffix:semicolon
)brace
id|sb-&gt;s_root-&gt;d_op
op_assign
op_amp
id|affs_dentry_operations
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: s_flags=%lX&bslash;n&quot;
comma
id|sb-&gt;s_flags
)paren
suffix:semicolon
r_return
id|sb
suffix:semicolon
multiline_comment|/*&n;&t; * Begin the cascaded cleanup ...&n;&t; */
id|out_error
suffix:colon
r_if
c_cond
(paren
id|root_inode
)paren
id|iput
c_func
(paren
id|root_inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|AFFS_SB-&gt;s_bitmap
)paren
id|kfree
c_func
(paren
id|AFFS_SB-&gt;s_bitmap
)paren
suffix:semicolon
id|affs_brelse
c_func
(paren
id|root_bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|AFFS_SB-&gt;s_prefix
)paren
id|kfree
c_func
(paren
id|AFFS_SB-&gt;s_prefix
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
r_int
DECL|function|affs_remount
id|affs_remount
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
r_int
id|blocksize
suffix:semicolon
id|uid_t
id|uid
suffix:semicolon
id|gid_t
id|gid
suffix:semicolon
r_int
id|mode
suffix:semicolon
r_int
id|reserved
suffix:semicolon
r_int
id|root_block
suffix:semicolon
r_int
r_int
id|mount_flags
suffix:semicolon
r_int
r_int
id|read_only
op_assign
id|AFFS_SB-&gt;s_flags
op_amp
id|SF_READONLY
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: remount(flags=0x%x,opts=&bslash;&quot;%s&bslash;&quot;)&bslash;n&quot;
comma
op_star
id|flags
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parse_options
c_func
(paren
id|data
comma
op_amp
id|uid
comma
op_amp
id|gid
comma
op_amp
id|mode
comma
op_amp
id|reserved
comma
op_amp
id|root_block
comma
op_amp
id|blocksize
comma
op_amp
id|AFFS_SB-&gt;s_prefix
comma
id|AFFS_SB-&gt;s_volume
comma
op_amp
id|mount_flags
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|AFFS_SB-&gt;s_flags
op_assign
id|mount_flags
op_or
id|read_only
suffix:semicolon
id|AFFS_SB-&gt;s_mode
op_assign
id|mode
suffix:semicolon
id|AFFS_SB-&gt;s_uid
op_assign
id|uid
suffix:semicolon
id|AFFS_SB-&gt;s_gid
op_assign
id|gid
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|flags
op_amp
id|MS_RDONLY
)paren
op_eq
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|flags
op_amp
id|MS_RDONLY
)paren
(brace
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|sb-&gt;s_dirt
)paren
id|affs_write_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|sb-&gt;s_flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|AFFS_SB-&gt;s_flags
op_amp
id|SF_READONLY
)paren
)paren
(brace
id|sb-&gt;s_flags
op_and_assign
op_complement
id|MS_RDONLY
suffix:semicolon
)brace
r_else
(brace
id|affs_warning
c_func
(paren
id|sb
comma
l_string|&quot;remount&quot;
comma
l_string|&quot;Cannot remount fs read/write because of errors&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|affs_statfs
id|affs_statfs
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
r_int
id|free
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: statfs() partsize=%d, reserved=%d&bslash;n&quot;
comma
id|AFFS_SB-&gt;s_partition_size
comma
id|AFFS_SB-&gt;s_reserved
)paren
suffix:semicolon
id|free
op_assign
id|affs_count_free_blocks
c_func
(paren
id|sb
)paren
suffix:semicolon
id|buf-&gt;f_type
op_assign
id|AFFS_SUPER_MAGIC
suffix:semicolon
id|buf-&gt;f_bsize
op_assign
id|sb-&gt;s_blocksize
suffix:semicolon
id|buf-&gt;f_blocks
op_assign
id|AFFS_SB-&gt;s_partition_size
op_minus
id|AFFS_SB-&gt;s_reserved
suffix:semicolon
id|buf-&gt;f_bfree
op_assign
id|free
suffix:semicolon
id|buf-&gt;f_bavail
op_assign
id|free
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|DECLARE_FSTYPE_DEV
c_func
(paren
id|affs_fs_type
comma
l_string|&quot;affs&quot;
comma
id|affs_read_super
)paren
suffix:semicolon
DECL|function|init_affs_fs
r_static
r_int
id|__init
id|init_affs_fs
c_func
(paren
r_void
)paren
(brace
r_return
id|register_filesystem
c_func
(paren
op_amp
id|affs_fs_type
)paren
suffix:semicolon
)brace
DECL|function|exit_affs_fs
r_static
r_void
id|__exit
id|exit_affs_fs
c_func
(paren
r_void
)paren
(brace
id|unregister_filesystem
c_func
(paren
op_amp
id|affs_fs_type
)paren
suffix:semicolon
)brace
id|EXPORT_NO_SYMBOLS
suffix:semicolon
id|module_init
c_func
(paren
id|init_affs_fs
)paren
id|module_exit
c_func
(paren
id|exit_affs_fs
)paren
eof
