multiline_comment|/*&n; *  linux/fs/minix/inode.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  Copyright (C) 1996  Gertjan van Wingerde    (gertjan@cs.vu.nl)&n; *&t;Minix V2 fs support.&n; *&n; *  Modified for 680x0 by Andreas Schwab&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/minix_fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/highuid.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
r_static
r_void
id|minix_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_static
r_void
id|minix_write_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|wait
)paren
suffix:semicolon
r_static
r_int
id|minix_statfs
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
id|minix_remount
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
DECL|function|minix_delete_inode
r_static
r_void
id|minix_delete_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|inode-&gt;i_size
op_assign
l_int|0
suffix:semicolon
id|minix_truncate
c_func
(paren
id|inode
)paren
suffix:semicolon
id|minix_free_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|minix_commit_super
r_static
r_void
id|minix_commit_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|mark_buffer_dirty
c_func
(paren
id|sb-&gt;u.minix_sb.s_sbh
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|minix_write_super
r_static
r_void
id|minix_write_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|minix_super_block
op_star
id|ms
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
id|ms
op_assign
id|sb-&gt;u.minix_sb.s_ms
suffix:semicolon
r_if
c_cond
(paren
id|ms-&gt;s_state
op_amp
id|MINIX_VALID_FS
)paren
id|ms-&gt;s_state
op_and_assign
op_complement
id|MINIX_VALID_FS
suffix:semicolon
id|minix_commit_super
c_func
(paren
id|sb
)paren
suffix:semicolon
)brace
id|sb-&gt;s_dirt
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|minix_put_super
r_static
r_void
id|minix_put_super
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
id|sb-&gt;u.minix_sb.s_ms-&gt;s_state
op_assign
id|sb-&gt;u.minix_sb.s_mount_state
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|sb-&gt;u.minix_sb.s_sbh
)paren
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
id|sb-&gt;u.minix_sb.s_imap_blocks
suffix:semicolon
id|i
op_increment
)paren
id|brelse
c_func
(paren
id|sb-&gt;u.minix_sb.s_imap
(braket
id|i
)braket
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
id|sb-&gt;u.minix_sb.s_zmap_blocks
suffix:semicolon
id|i
op_increment
)paren
id|brelse
c_func
(paren
id|sb-&gt;u.minix_sb.s_zmap
(braket
id|i
)braket
)paren
suffix:semicolon
id|brelse
(paren
id|sb-&gt;u.minix_sb.s_sbh
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sb-&gt;u.minix_sb.s_imap
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|variable|minix_sops
r_static
r_struct
id|super_operations
id|minix_sops
op_assign
(brace
id|read_inode
suffix:colon
id|minix_read_inode
comma
id|write_inode
suffix:colon
id|minix_write_inode
comma
id|delete_inode
suffix:colon
id|minix_delete_inode
comma
id|put_super
suffix:colon
id|minix_put_super
comma
id|write_super
suffix:colon
id|minix_write_super
comma
id|statfs
suffix:colon
id|minix_statfs
comma
id|remount_fs
suffix:colon
id|minix_remount
comma
)brace
suffix:semicolon
DECL|function|minix_remount
r_static
r_int
id|minix_remount
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
r_struct
id|minix_super_block
op_star
id|ms
suffix:semicolon
id|ms
op_assign
id|sb-&gt;u.minix_sb.s_ms
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
r_if
c_cond
(paren
id|ms-&gt;s_state
op_amp
id|MINIX_VALID_FS
op_logical_or
op_logical_neg
(paren
id|sb-&gt;u.minix_sb.s_mount_state
op_amp
id|MINIX_VALID_FS
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Mounting a rw partition read-only. */
id|ms-&gt;s_state
op_assign
id|sb-&gt;u.minix_sb.s_mount_state
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|sb-&gt;u.minix_sb.s_sbh
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
id|minix_commit_super
c_func
(paren
id|sb
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Mount a partition which is read-only, read-write. */
id|sb-&gt;u.minix_sb.s_mount_state
op_assign
id|ms-&gt;s_state
suffix:semicolon
id|ms-&gt;s_state
op_and_assign
op_complement
id|MINIX_VALID_FS
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|sb-&gt;u.minix_sb.s_sbh
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb-&gt;u.minix_sb.s_mount_state
op_amp
id|MINIX_VALID_FS
)paren
)paren
id|printk
(paren
l_string|&quot;MINIX-fs warning: remounting unchecked fs, &quot;
l_string|&quot;running fsck is recommended.&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|sb-&gt;u.minix_sb.s_mount_state
op_amp
id|MINIX_ERROR_FS
)paren
)paren
id|printk
(paren
l_string|&quot;MINIX-fs warning: remounting fs with errors, &quot;
l_string|&quot;running fsck is recommended.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|minix_read_super
r_static
r_struct
id|super_block
op_star
id|minix_read_super
c_func
(paren
r_struct
id|super_block
op_star
id|s
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
id|bh
suffix:semicolon
r_struct
id|buffer_head
op_star
op_star
id|map
suffix:semicolon
r_struct
id|minix_super_block
op_star
id|ms
suffix:semicolon
r_int
id|i
comma
id|block
suffix:semicolon
id|kdev_t
id|dev
op_assign
id|s-&gt;s_dev
suffix:semicolon
r_struct
id|inode
op_star
id|root_inode
suffix:semicolon
r_int
r_int
id|hblock
suffix:semicolon
r_struct
id|minix_sb_info
op_star
id|sbi
op_assign
op_amp
id|s-&gt;u.minix_sb
suffix:semicolon
multiline_comment|/* N.B. These should be compile-time tests.&n;&t;   Unfortunately that is impossible. */
r_if
c_cond
(paren
l_int|32
op_ne
r_sizeof
(paren
r_struct
id|minix_inode
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;bad V1 i-node size&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|64
op_ne
r_sizeof
(paren
r_struct
id|minix2_inode
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;bad V2 i-node size&quot;
)paren
suffix:semicolon
id|hblock
op_assign
id|get_hardsect_size
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hblock
OG
id|BLOCK_SIZE
)paren
r_goto
id|out_bad_hblock
suffix:semicolon
id|set_blocksize
c_func
(paren
id|dev
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
id|bread
c_func
(paren
id|dev
comma
l_int|1
comma
id|BLOCK_SIZE
)paren
)paren
)paren
r_goto
id|out_bad_sb
suffix:semicolon
id|ms
op_assign
(paren
r_struct
id|minix_super_block
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|sbi-&gt;s_ms
op_assign
id|ms
suffix:semicolon
id|sbi-&gt;s_sbh
op_assign
id|bh
suffix:semicolon
id|sbi-&gt;s_mount_state
op_assign
id|ms-&gt;s_state
suffix:semicolon
id|s-&gt;s_blocksize
op_assign
id|BLOCK_SIZE
suffix:semicolon
id|s-&gt;s_blocksize_bits
op_assign
id|BLOCK_SIZE_BITS
suffix:semicolon
id|sbi-&gt;s_ninodes
op_assign
id|ms-&gt;s_ninodes
suffix:semicolon
id|sbi-&gt;s_nzones
op_assign
id|ms-&gt;s_nzones
suffix:semicolon
id|sbi-&gt;s_imap_blocks
op_assign
id|ms-&gt;s_imap_blocks
suffix:semicolon
id|sbi-&gt;s_zmap_blocks
op_assign
id|ms-&gt;s_zmap_blocks
suffix:semicolon
id|sbi-&gt;s_firstdatazone
op_assign
id|ms-&gt;s_firstdatazone
suffix:semicolon
id|sbi-&gt;s_log_zone_size
op_assign
id|ms-&gt;s_log_zone_size
suffix:semicolon
id|sbi-&gt;s_max_size
op_assign
id|ms-&gt;s_max_size
suffix:semicolon
id|s-&gt;s_magic
op_assign
id|ms-&gt;s_magic
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;s_magic
op_eq
id|MINIX_SUPER_MAGIC
)paren
(brace
id|sbi-&gt;s_version
op_assign
id|MINIX_V1
suffix:semicolon
id|sbi-&gt;s_dirsize
op_assign
l_int|16
suffix:semicolon
id|sbi-&gt;s_namelen
op_assign
l_int|14
suffix:semicolon
id|sbi-&gt;s_link_max
op_assign
id|MINIX_LINK_MAX
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|s-&gt;s_magic
op_eq
id|MINIX_SUPER_MAGIC2
)paren
(brace
id|sbi-&gt;s_version
op_assign
id|MINIX_V1
suffix:semicolon
id|sbi-&gt;s_dirsize
op_assign
l_int|32
suffix:semicolon
id|sbi-&gt;s_namelen
op_assign
l_int|30
suffix:semicolon
id|sbi-&gt;s_link_max
op_assign
id|MINIX_LINK_MAX
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|s-&gt;s_magic
op_eq
id|MINIX2_SUPER_MAGIC
)paren
(brace
id|sbi-&gt;s_version
op_assign
id|MINIX_V2
suffix:semicolon
id|sbi-&gt;s_nzones
op_assign
id|ms-&gt;s_zones
suffix:semicolon
id|sbi-&gt;s_dirsize
op_assign
l_int|16
suffix:semicolon
id|sbi-&gt;s_namelen
op_assign
l_int|14
suffix:semicolon
id|sbi-&gt;s_link_max
op_assign
id|MINIX2_LINK_MAX
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|s-&gt;s_magic
op_eq
id|MINIX2_SUPER_MAGIC2
)paren
(brace
id|sbi-&gt;s_version
op_assign
id|MINIX_V2
suffix:semicolon
id|sbi-&gt;s_nzones
op_assign
id|ms-&gt;s_zones
suffix:semicolon
id|sbi-&gt;s_dirsize
op_assign
l_int|32
suffix:semicolon
id|sbi-&gt;s_namelen
op_assign
l_int|30
suffix:semicolon
id|sbi-&gt;s_link_max
op_assign
id|MINIX2_LINK_MAX
suffix:semicolon
)brace
r_else
r_goto
id|out_no_fs
suffix:semicolon
multiline_comment|/*&n;&t; * Allocate the buffer map to keep the superblock small.&n;&t; */
id|i
op_assign
(paren
id|sbi-&gt;s_imap_blocks
op_plus
id|sbi-&gt;s_zmap_blocks
)paren
op_star
r_sizeof
(paren
id|bh
)paren
suffix:semicolon
id|map
op_assign
id|kmalloc
c_func
(paren
id|i
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|map
)paren
r_goto
id|out_no_map
suffix:semicolon
id|memset
c_func
(paren
id|map
comma
l_int|0
comma
id|i
)paren
suffix:semicolon
id|sbi-&gt;s_imap
op_assign
op_amp
id|map
(braket
l_int|0
)braket
suffix:semicolon
id|sbi-&gt;s_zmap
op_assign
op_amp
id|map
(braket
id|sbi-&gt;s_imap_blocks
)braket
suffix:semicolon
id|block
op_assign
l_int|2
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
id|sbi-&gt;s_imap_blocks
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|sbi-&gt;s_imap
(braket
id|i
)braket
op_assign
id|bread
c_func
(paren
id|dev
comma
id|block
comma
id|BLOCK_SIZE
)paren
)paren
)paren
r_goto
id|out_no_bitmap
suffix:semicolon
id|block
op_increment
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
id|sbi-&gt;s_zmap_blocks
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|sbi-&gt;s_zmap
(braket
id|i
)braket
op_assign
id|bread
c_func
(paren
id|dev
comma
id|block
comma
id|BLOCK_SIZE
)paren
)paren
)paren
r_goto
id|out_no_bitmap
suffix:semicolon
id|block
op_increment
suffix:semicolon
)brace
id|minix_set_bit
c_func
(paren
l_int|0
comma
id|sbi-&gt;s_imap
(braket
l_int|0
)braket
op_member_access_from_pointer
id|b_data
)paren
suffix:semicolon
id|minix_set_bit
c_func
(paren
l_int|0
comma
id|sbi-&gt;s_zmap
(braket
l_int|0
)braket
op_member_access_from_pointer
id|b_data
)paren
suffix:semicolon
multiline_comment|/* set up enough so that it can read an inode */
id|s-&gt;s_op
op_assign
op_amp
id|minix_sops
suffix:semicolon
id|root_inode
op_assign
id|iget
c_func
(paren
id|s
comma
id|MINIX_ROOT_INO
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root_inode
)paren
r_goto
id|out_no_root
suffix:semicolon
id|s-&gt;s_root
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
id|s-&gt;s_root
)paren
r_goto
id|out_iput
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|NO_TRUNCATE
)paren
id|s-&gt;s_root-&gt;d_op
op_assign
op_amp
id|minix_dentry_operations
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
id|ms-&gt;s_state
op_and_assign
op_complement
id|MINIX_VALID_FS
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|s-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|sbi-&gt;s_mount_state
op_amp
id|MINIX_VALID_FS
)paren
)paren
id|printk
(paren
l_string|&quot;MINIX-fs: mounting unchecked file system, &quot;
l_string|&quot;running fsck is recommended.&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sbi-&gt;s_mount_state
op_amp
id|MINIX_ERROR_FS
)paren
id|printk
(paren
l_string|&quot;MINIX-fs: mounting file system with errors, &quot;
l_string|&quot;running fsck is recommended.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|s
suffix:semicolon
id|out_iput
suffix:colon
id|iput
c_func
(paren
id|root_inode
)paren
suffix:semicolon
r_goto
id|out_freemap
suffix:semicolon
id|out_no_root
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
id|printk
c_func
(paren
l_string|&quot;MINIX-fs: get root inode failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_freemap
suffix:semicolon
id|out_no_bitmap
suffix:colon
id|printk
c_func
(paren
l_string|&quot;MINIX-fs: bad superblock or unable to read bitmaps&bslash;n&quot;
)paren
suffix:semicolon
id|out_freemap
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|sbi-&gt;s_imap_blocks
suffix:semicolon
id|i
op_increment
)paren
id|brelse
c_func
(paren
id|sbi-&gt;s_imap
(braket
id|i
)braket
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
id|sbi-&gt;s_zmap_blocks
suffix:semicolon
id|i
op_increment
)paren
id|brelse
c_func
(paren
id|sbi-&gt;s_zmap
(braket
id|i
)braket
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sbi-&gt;s_imap
)paren
suffix:semicolon
r_goto
id|out_release
suffix:semicolon
id|out_no_map
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
id|printk
(paren
l_string|&quot;MINIX-fs: can&squot;t allocate map&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_release
suffix:semicolon
id|out_no_fs
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
id|printk
c_func
(paren
l_string|&quot;VFS: Can&squot;t find a Minix or Minix V2 filesystem on device &quot;
l_string|&quot;%s.&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
id|out_release
suffix:colon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|out_bad_hblock
suffix:colon
id|printk
c_func
(paren
l_string|&quot;MINIX-fs: blocksize too small for device.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|out_bad_sb
suffix:colon
id|printk
c_func
(paren
l_string|&quot;MINIX-fs: unable to read superblock&bslash;n&quot;
)paren
suffix:semicolon
id|out
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|minix_statfs
r_static
r_int
id|minix_statfs
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
id|buf-&gt;f_type
op_assign
id|sb-&gt;s_magic
suffix:semicolon
id|buf-&gt;f_bsize
op_assign
id|sb-&gt;s_blocksize
suffix:semicolon
id|buf-&gt;f_blocks
op_assign
(paren
id|sb-&gt;u.minix_sb.s_nzones
op_minus
id|sb-&gt;u.minix_sb.s_firstdatazone
)paren
op_lshift
id|sb-&gt;u.minix_sb.s_log_zone_size
suffix:semicolon
id|buf-&gt;f_bfree
op_assign
id|minix_count_free_blocks
c_func
(paren
id|sb
)paren
suffix:semicolon
id|buf-&gt;f_bavail
op_assign
id|buf-&gt;f_bfree
suffix:semicolon
id|buf-&gt;f_files
op_assign
id|sb-&gt;u.minix_sb.s_ninodes
suffix:semicolon
id|buf-&gt;f_ffree
op_assign
id|minix_count_free_inodes
c_func
(paren
id|sb
)paren
suffix:semicolon
id|buf-&gt;f_namelen
op_assign
id|sb-&gt;u.minix_sb.s_namelen
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|minix_get_block
r_static
r_int
id|minix_get_block
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|block
comma
r_struct
id|buffer_head
op_star
id|bh_result
comma
r_int
id|create
)paren
(brace
r_if
c_cond
(paren
id|INODE_VERSION
c_func
(paren
id|inode
)paren
op_eq
id|MINIX_V1
)paren
r_return
id|V1_minix_get_block
c_func
(paren
id|inode
comma
id|block
comma
id|bh_result
comma
id|create
)paren
suffix:semicolon
r_else
r_return
id|V2_minix_get_block
c_func
(paren
id|inode
comma
id|block
comma
id|bh_result
comma
id|create
)paren
suffix:semicolon
)brace
DECL|function|minix_writepage
r_static
r_int
id|minix_writepage
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_return
id|block_write_full_page
c_func
(paren
id|page
comma
id|minix_get_block
)paren
suffix:semicolon
)brace
DECL|function|minix_readpage
r_static
r_int
id|minix_readpage
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_return
id|block_read_full_page
c_func
(paren
id|page
comma
id|minix_get_block
)paren
suffix:semicolon
)brace
DECL|function|minix_prepare_write
r_static
r_int
id|minix_prepare_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
comma
r_int
id|from
comma
r_int
id|to
)paren
(brace
r_return
id|block_prepare_write
c_func
(paren
id|page
comma
id|from
comma
id|to
comma
id|minix_get_block
)paren
suffix:semicolon
)brace
DECL|function|minix_bmap
r_static
r_int
id|minix_bmap
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_int
id|block
)paren
(brace
r_return
id|generic_block_bmap
c_func
(paren
id|mapping
comma
id|block
comma
id|minix_get_block
)paren
suffix:semicolon
)brace
DECL|variable|minix_aops
r_static
r_struct
id|address_space_operations
id|minix_aops
op_assign
(brace
id|readpage
suffix:colon
id|minix_readpage
comma
id|writepage
suffix:colon
id|minix_writepage
comma
id|sync_page
suffix:colon
id|block_sync_page
comma
id|prepare_write
suffix:colon
id|minix_prepare_write
comma
id|commit_write
suffix:colon
id|generic_commit_write
comma
id|bmap
suffix:colon
id|minix_bmap
)brace
suffix:semicolon
DECL|function|minix_set_inode
r_void
id|minix_set_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|dev_t
id|rdev
)paren
(brace
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|minix_file_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|minix_file_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|minix_aops
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|minix_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|minix_dir_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|minix_aops
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|page_symlink_inode_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|minix_aops
suffix:semicolon
)brace
r_else
id|init_special_inode
c_func
(paren
id|inode
comma
id|inode-&gt;i_mode
comma
id|rdev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The minix V1 function to read an inode.&n; */
DECL|function|V1_minix_read_inode
r_static
r_void
id|V1_minix_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|minix_inode
op_star
id|raw_inode
suffix:semicolon
r_int
id|i
suffix:semicolon
id|raw_inode
op_assign
id|minix_V1_raw_inode
c_func
(paren
id|inode-&gt;i_sb
comma
id|inode-&gt;i_ino
comma
op_amp
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|raw_inode
)paren
r_return
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|raw_inode-&gt;i_mode
suffix:semicolon
id|inode-&gt;i_uid
op_assign
(paren
id|uid_t
)paren
id|raw_inode-&gt;i_uid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
(paren
id|gid_t
)paren
id|raw_inode-&gt;i_gid
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
id|raw_inode-&gt;i_nlinks
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|raw_inode-&gt;i_size
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_ctime
op_assign
id|raw_inode-&gt;i_time
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
id|inode-&gt;i_blksize
op_assign
l_int|0
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
l_int|9
suffix:semicolon
id|i
op_increment
)paren
id|inode-&gt;u.minix_i.u.i1_data
(braket
id|i
)braket
op_assign
id|raw_inode-&gt;i_zone
(braket
id|i
)braket
suffix:semicolon
id|minix_set_inode
c_func
(paren
id|inode
comma
id|raw_inode-&gt;i_zone
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The minix V2 function to read an inode.&n; */
DECL|function|V2_minix_read_inode
r_static
r_void
id|V2_minix_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|minix2_inode
op_star
id|raw_inode
suffix:semicolon
r_int
id|i
suffix:semicolon
id|raw_inode
op_assign
id|minix_V2_raw_inode
c_func
(paren
id|inode-&gt;i_sb
comma
id|inode-&gt;i_ino
comma
op_amp
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|raw_inode
)paren
r_return
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|raw_inode-&gt;i_mode
suffix:semicolon
id|inode-&gt;i_uid
op_assign
(paren
id|uid_t
)paren
id|raw_inode-&gt;i_uid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
(paren
id|gid_t
)paren
id|raw_inode-&gt;i_gid
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
id|raw_inode-&gt;i_nlinks
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|raw_inode-&gt;i_size
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|raw_inode-&gt;i_mtime
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|raw_inode-&gt;i_atime
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|raw_inode-&gt;i_ctime
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
id|inode-&gt;i_blksize
op_assign
l_int|0
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
l_int|10
suffix:semicolon
id|i
op_increment
)paren
id|inode-&gt;u.minix_i.u.i2_data
(braket
id|i
)braket
op_assign
id|raw_inode-&gt;i_zone
(braket
id|i
)braket
suffix:semicolon
id|minix_set_inode
c_func
(paren
id|inode
comma
id|raw_inode-&gt;i_zone
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The global function to read an inode.&n; */
DECL|function|minix_read_inode
r_static
r_void
id|minix_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_if
c_cond
(paren
id|INODE_VERSION
c_func
(paren
id|inode
)paren
op_eq
id|MINIX_V1
)paren
id|V1_minix_read_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_else
id|V2_minix_read_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The minix V1 function to synchronize an inode.&n; */
DECL|function|V1_minix_update_inode
r_static
r_struct
id|buffer_head
op_star
id|V1_minix_update_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|minix_inode
op_star
id|raw_inode
suffix:semicolon
r_int
id|i
suffix:semicolon
id|raw_inode
op_assign
id|minix_V1_raw_inode
c_func
(paren
id|inode-&gt;i_sb
comma
id|inode-&gt;i_ino
comma
op_amp
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|raw_inode
)paren
r_return
l_int|0
suffix:semicolon
id|raw_inode-&gt;i_mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
id|raw_inode-&gt;i_uid
op_assign
id|fs_high2lowuid
c_func
(paren
id|inode-&gt;i_uid
)paren
suffix:semicolon
id|raw_inode-&gt;i_gid
op_assign
id|fs_high2lowgid
c_func
(paren
id|inode-&gt;i_gid
)paren
suffix:semicolon
id|raw_inode-&gt;i_nlinks
op_assign
id|inode-&gt;i_nlink
suffix:semicolon
id|raw_inode-&gt;i_size
op_assign
id|inode-&gt;i_size
suffix:semicolon
id|raw_inode-&gt;i_time
op_assign
id|inode-&gt;i_mtime
suffix:semicolon
r_if
c_cond
(paren
id|S_ISCHR
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_or
id|S_ISBLK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
id|raw_inode-&gt;i_zone
(braket
l_int|0
)braket
op_assign
id|kdev_t_to_nr
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_else
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|9
suffix:semicolon
id|i
op_increment
)paren
id|raw_inode-&gt;i_zone
(braket
id|i
)braket
op_assign
id|inode-&gt;u.minix_i.u.i1_data
(braket
id|i
)braket
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|bh
suffix:semicolon
)brace
multiline_comment|/*&n; * The minix V2 function to synchronize an inode.&n; */
DECL|function|V2_minix_update_inode
r_static
r_struct
id|buffer_head
op_star
id|V2_minix_update_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|minix2_inode
op_star
id|raw_inode
suffix:semicolon
r_int
id|i
suffix:semicolon
id|raw_inode
op_assign
id|minix_V2_raw_inode
c_func
(paren
id|inode-&gt;i_sb
comma
id|inode-&gt;i_ino
comma
op_amp
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|raw_inode
)paren
r_return
l_int|0
suffix:semicolon
id|raw_inode-&gt;i_mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
id|raw_inode-&gt;i_uid
op_assign
id|fs_high2lowuid
c_func
(paren
id|inode-&gt;i_uid
)paren
suffix:semicolon
id|raw_inode-&gt;i_gid
op_assign
id|fs_high2lowgid
c_func
(paren
id|inode-&gt;i_gid
)paren
suffix:semicolon
id|raw_inode-&gt;i_nlinks
op_assign
id|inode-&gt;i_nlink
suffix:semicolon
id|raw_inode-&gt;i_size
op_assign
id|inode-&gt;i_size
suffix:semicolon
id|raw_inode-&gt;i_mtime
op_assign
id|inode-&gt;i_mtime
suffix:semicolon
id|raw_inode-&gt;i_atime
op_assign
id|inode-&gt;i_atime
suffix:semicolon
id|raw_inode-&gt;i_ctime
op_assign
id|inode-&gt;i_ctime
suffix:semicolon
r_if
c_cond
(paren
id|S_ISCHR
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_or
id|S_ISBLK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
id|raw_inode-&gt;i_zone
(braket
l_int|0
)braket
op_assign
id|kdev_t_to_nr
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_else
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|10
suffix:semicolon
id|i
op_increment
)paren
id|raw_inode-&gt;i_zone
(braket
id|i
)braket
op_assign
id|inode-&gt;u.minix_i.u.i2_data
(braket
id|i
)braket
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|bh
suffix:semicolon
)brace
DECL|function|minix_update_inode
r_static
r_struct
id|buffer_head
op_star
id|minix_update_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_if
c_cond
(paren
id|INODE_VERSION
c_func
(paren
id|inode
)paren
op_eq
id|MINIX_V1
)paren
r_return
id|V1_minix_update_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_else
r_return
id|V2_minix_update_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|function|minix_write_inode
r_static
r_void
id|minix_write_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|wait
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|bh
op_assign
id|minix_update_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
DECL|function|minix_sync_inode
r_int
id|minix_sync_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|bh
op_assign
id|minix_update_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
op_logical_and
id|buffer_dirty
c_func
(paren
id|bh
)paren
)paren
(brace
id|ll_rw_block
c_func
(paren
id|WRITE
comma
l_int|1
comma
op_amp
id|bh
)paren
suffix:semicolon
id|wait_on_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer_req
c_func
(paren
id|bh
)paren
op_logical_and
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;IO error syncing minix inode [&quot;
l_string|&quot;%s:%08lx]&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|inode-&gt;i_dev
)paren
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|err
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
id|err
op_assign
op_minus
l_int|1
suffix:semicolon
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * The function that is called for file truncation.&n; */
DECL|function|minix_truncate
r_void
id|minix_truncate
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_if
c_cond
(paren
id|INODE_VERSION
c_func
(paren
id|inode
)paren
op_eq
id|MINIX_V1
)paren
id|V1_minix_truncate
c_func
(paren
id|inode
)paren
suffix:semicolon
r_else
id|V2_minix_truncate
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_static
id|DECLARE_FSTYPE_DEV
c_func
(paren
id|minix_fs_type
comma
l_string|&quot;minix&quot;
comma
id|minix_read_super
)paren
suffix:semicolon
DECL|function|init_minix_fs
r_static
r_int
id|__init
id|init_minix_fs
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
id|minix_fs_type
)paren
suffix:semicolon
)brace
DECL|function|exit_minix_fs
r_static
r_void
id|__exit
id|exit_minix_fs
c_func
(paren
r_void
)paren
(brace
id|unregister_filesystem
c_func
(paren
op_amp
id|minix_fs_type
)paren
suffix:semicolon
)brace
id|EXPORT_NO_SYMBOLS
suffix:semicolon
id|module_init
c_func
(paren
id|init_minix_fs
)paren
id|module_exit
c_func
(paren
id|exit_minix_fs
)paren
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
