multiline_comment|/*&n; *  linux/fs/sysv/inode.c&n; *&n; *  minix/inode.c&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  xenix/inode.c&n; *  Copyright (C) 1992  Doug Evans&n; *&n; *  coh/inode.c&n; *  Copyright (C) 1993  Pascal Haible, Bruno Haible&n; *&n; *  sysv/inode.c&n; *  Copyright (C) 1993  Paul B. Monday&n; *&n; *  sysv/inode.c&n; *  Copyright (C) 1993  Bruno Haible&n; *  Copyright (C) 1997, 1998  Krzysztof G. Baranowski&n; *&n; *  This file contains code for allocating/freeing inodes and for read/writing&n; *  the superblock.&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sysv_fs.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/highuid.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
multiline_comment|/* This is only called on sync() and umount(), when s_dirt=1. */
DECL|function|sysv_write_super
r_static
r_void
id|sysv_write_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
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
multiline_comment|/* If we are going to write out the super block,&n;&t;&t;   then attach current time stamp.&n;&t;&t;   But if the filesystem was marked clean, keep it clean. */
r_int
r_int
id|time
op_assign
id|CURRENT_TIME
suffix:semicolon
r_int
r_int
id|old_time
op_assign
id|fs32_to_cpu
c_func
(paren
id|sb
comma
op_star
id|sb-&gt;sv_sb_time
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;sv_type
op_eq
id|FSTYPE_SYSV4
)paren
r_if
c_cond
(paren
op_star
id|sb-&gt;sv_sb_state
op_eq
id|cpu_to_fs32
c_func
(paren
id|sb
comma
l_int|0x7c269d38
op_minus
id|old_time
)paren
)paren
op_star
id|sb-&gt;sv_sb_state
op_assign
id|cpu_to_fs32
c_func
(paren
id|sb
comma
l_int|0x7c269d38
op_minus
id|time
)paren
suffix:semicolon
op_star
id|sb-&gt;sv_sb_time
op_assign
id|cpu_to_fs32
c_func
(paren
id|sb
comma
id|time
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|sb-&gt;sv_bh2
)paren
suffix:semicolon
)brace
id|sb-&gt;s_dirt
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|sysv_put_super
r_static
r_void
id|sysv_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
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
multiline_comment|/* XXX ext2 also updates the state here */
id|mark_buffer_dirty
c_func
(paren
id|sb-&gt;sv_bh1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;sv_bh1
op_ne
id|sb-&gt;sv_bh2
)paren
id|mark_buffer_dirty
c_func
(paren
id|sb-&gt;sv_bh2
)paren
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|sb-&gt;sv_bh1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;sv_bh1
op_ne
id|sb-&gt;sv_bh2
)paren
id|brelse
c_func
(paren
id|sb-&gt;sv_bh2
)paren
suffix:semicolon
)brace
DECL|function|sysv_statfs
r_static
r_int
id|sysv_statfs
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
id|sb-&gt;sv_ndatazones
suffix:semicolon
id|buf-&gt;f_bavail
op_assign
id|buf-&gt;f_bfree
op_assign
id|sysv_count_free_blocks
c_func
(paren
id|sb
)paren
suffix:semicolon
id|buf-&gt;f_files
op_assign
id|sb-&gt;sv_ninodes
suffix:semicolon
id|buf-&gt;f_ffree
op_assign
id|sysv_count_free_inodes
c_func
(paren
id|sb
)paren
suffix:semicolon
id|buf-&gt;f_namelen
op_assign
id|SYSV_NAMELEN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* &n; * NXI &lt;-&gt; N0XI for PDP, XIN &lt;-&gt; XIN0 for le32, NIX &lt;-&gt; 0NIX for be32&n; */
DECL|function|read3byte
r_static
r_inline
r_void
id|read3byte
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
id|from
comma
r_int
r_char
op_star
id|to
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;sv_bytesex
op_eq
id|BYTESEX_PDP
)paren
(brace
id|to
(braket
l_int|0
)braket
op_assign
id|from
(braket
l_int|0
)braket
suffix:semicolon
id|to
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|to
(braket
l_int|2
)braket
op_assign
id|from
(braket
l_int|1
)braket
suffix:semicolon
id|to
(braket
l_int|3
)braket
op_assign
id|from
(braket
l_int|2
)braket
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|sb-&gt;sv_bytesex
op_eq
id|BYTESEX_LE
)paren
(brace
id|to
(braket
l_int|0
)braket
op_assign
id|from
(braket
l_int|0
)braket
suffix:semicolon
id|to
(braket
l_int|1
)braket
op_assign
id|from
(braket
l_int|1
)braket
suffix:semicolon
id|to
(braket
l_int|2
)braket
op_assign
id|from
(braket
l_int|2
)braket
suffix:semicolon
id|to
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|to
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|to
(braket
l_int|1
)braket
op_assign
id|from
(braket
l_int|0
)braket
suffix:semicolon
id|to
(braket
l_int|2
)braket
op_assign
id|from
(braket
l_int|1
)braket
suffix:semicolon
id|to
(braket
l_int|3
)braket
op_assign
id|from
(braket
l_int|2
)braket
suffix:semicolon
)brace
)brace
DECL|function|write3byte
r_static
r_inline
r_void
id|write3byte
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
id|from
comma
r_int
r_char
op_star
id|to
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;sv_bytesex
op_eq
id|BYTESEX_PDP
)paren
(brace
id|to
(braket
l_int|0
)braket
op_assign
id|from
(braket
l_int|0
)braket
suffix:semicolon
id|to
(braket
l_int|1
)braket
op_assign
id|from
(braket
l_int|2
)braket
suffix:semicolon
id|to
(braket
l_int|2
)braket
op_assign
id|from
(braket
l_int|3
)braket
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|sb-&gt;sv_bytesex
op_eq
id|BYTESEX_LE
)paren
(brace
id|to
(braket
l_int|0
)braket
op_assign
id|from
(braket
l_int|0
)braket
suffix:semicolon
id|to
(braket
l_int|1
)braket
op_assign
id|from
(braket
l_int|1
)braket
suffix:semicolon
id|to
(braket
l_int|2
)braket
op_assign
id|from
(braket
l_int|2
)braket
suffix:semicolon
)brace
r_else
(brace
id|to
(braket
l_int|0
)braket
op_assign
id|from
(braket
l_int|1
)braket
suffix:semicolon
id|to
(braket
l_int|1
)braket
op_assign
id|from
(braket
l_int|2
)braket
suffix:semicolon
id|to
(braket
l_int|2
)braket
op_assign
id|from
(braket
l_int|3
)braket
suffix:semicolon
)brace
)brace
DECL|variable|sysv_symlink_inode_operations
r_static
r_struct
id|inode_operations
id|sysv_symlink_inode_operations
op_assign
(brace
id|readlink
suffix:colon
id|page_readlink
comma
id|follow_link
suffix:colon
id|page_follow_link
comma
)brace
suffix:semicolon
DECL|function|sysv_set_inode
r_void
id|sysv_set_inode
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
id|sysv_file_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|sysv_file_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|sysv_aops
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
id|sysv_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|sysv_dir_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|sysv_aops
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
r_if
c_cond
(paren
id|inode-&gt;i_blocks
)paren
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|sysv_symlink_inode_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|sysv_aops
suffix:semicolon
)brace
r_else
id|inode-&gt;i_op
op_assign
op_amp
id|sysv_fast_symlink_inode_operations
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
DECL|function|sysv_read_inode
r_static
r_void
id|sysv_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|sysv_inode
op_star
id|raw_inode
suffix:semicolon
r_struct
id|sysv_inode_info
op_star
id|si
suffix:semicolon
r_int
r_int
id|block
comma
id|ino
suffix:semicolon
id|dev_t
id|rdev
op_assign
l_int|0
suffix:semicolon
id|ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ino
op_logical_or
id|ino
OG
id|sb-&gt;sv_ninodes
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Bad inode number on dev %s: %d is out of range&bslash;n&quot;
comma
id|inode-&gt;i_sb-&gt;s_id
comma
id|ino
)paren
suffix:semicolon
r_goto
id|bad_inode
suffix:semicolon
)brace
id|raw_inode
op_assign
id|sysv_raw_inode
c_func
(paren
id|sb
comma
id|ino
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
(brace
id|printk
c_func
(paren
l_string|&quot;Major problem: unable to read inode from dev %s&bslash;n&quot;
comma
id|inode-&gt;i_sb-&gt;s_id
)paren
suffix:semicolon
r_goto
id|bad_inode
suffix:semicolon
)brace
multiline_comment|/* SystemV FS: kludge permissions if ino==SYSV_ROOT_INO ?? */
id|inode-&gt;i_mode
op_assign
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|raw_inode-&gt;i_mode
)paren
suffix:semicolon
id|inode-&gt;i_uid
op_assign
(paren
id|uid_t
)paren
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|raw_inode-&gt;i_uid
)paren
suffix:semicolon
id|inode-&gt;i_gid
op_assign
(paren
id|gid_t
)paren
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|raw_inode-&gt;i_gid
)paren
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|raw_inode-&gt;i_nlink
)paren
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|raw_inode-&gt;i_size
)paren
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|raw_inode-&gt;i_atime
)paren
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|raw_inode-&gt;i_mtime
)paren
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|raw_inode-&gt;i_ctime
)paren
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
id|inode-&gt;i_blksize
op_assign
l_int|0
suffix:semicolon
id|si
op_assign
id|SYSV_I
c_func
(paren
id|inode
)paren
suffix:semicolon
r_for
c_loop
(paren
id|block
op_assign
l_int|0
suffix:semicolon
id|block
OL
l_int|10
op_plus
l_int|1
op_plus
l_int|1
op_plus
l_int|1
suffix:semicolon
id|block
op_increment
)paren
id|read3byte
c_func
(paren
id|sb
comma
op_amp
id|raw_inode-&gt;i_a.i_addb
(braket
l_int|3
op_star
id|block
)braket
comma
(paren
r_int
r_char
op_star
)paren
op_amp
id|si-&gt;i_data
(braket
id|block
)braket
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
id|rdev
op_assign
(paren
id|u16
)paren
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|si-&gt;i_data
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|si-&gt;i_dir_start_lookup
op_assign
l_int|0
suffix:semicolon
id|sysv_set_inode
c_func
(paren
id|inode
comma
id|rdev
)paren
suffix:semicolon
r_return
suffix:semicolon
id|bad_inode
suffix:colon
id|make_bad_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|sysv_update_inode
r_static
r_struct
id|buffer_head
op_star
id|sysv_update_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|sysv_inode
op_star
id|raw_inode
suffix:semicolon
r_struct
id|sysv_inode_info
op_star
id|si
suffix:semicolon
r_int
r_int
id|ino
comma
id|block
suffix:semicolon
id|ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ino
op_logical_or
id|ino
OG
id|sb-&gt;sv_ninodes
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Bad inode number on dev %s: %d is out of range&bslash;n&quot;
comma
id|inode-&gt;i_sb-&gt;s_id
comma
id|ino
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|raw_inode
op_assign
id|sysv_raw_inode
c_func
(paren
id|sb
comma
id|ino
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
(brace
id|printk
c_func
(paren
l_string|&quot;unable to read i-node block&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|raw_inode-&gt;i_mode
op_assign
id|cpu_to_fs16
c_func
(paren
id|sb
comma
id|inode-&gt;i_mode
)paren
suffix:semicolon
id|raw_inode-&gt;i_uid
op_assign
id|cpu_to_fs16
c_func
(paren
id|sb
comma
id|fs_high2lowuid
c_func
(paren
id|inode-&gt;i_uid
)paren
)paren
suffix:semicolon
id|raw_inode-&gt;i_gid
op_assign
id|cpu_to_fs16
c_func
(paren
id|sb
comma
id|fs_high2lowgid
c_func
(paren
id|inode-&gt;i_gid
)paren
)paren
suffix:semicolon
id|raw_inode-&gt;i_nlink
op_assign
id|cpu_to_fs16
c_func
(paren
id|sb
comma
id|inode-&gt;i_nlink
)paren
suffix:semicolon
id|raw_inode-&gt;i_size
op_assign
id|cpu_to_fs32
c_func
(paren
id|sb
comma
id|inode-&gt;i_size
)paren
suffix:semicolon
id|raw_inode-&gt;i_atime
op_assign
id|cpu_to_fs32
c_func
(paren
id|sb
comma
id|inode-&gt;i_atime
)paren
suffix:semicolon
id|raw_inode-&gt;i_mtime
op_assign
id|cpu_to_fs32
c_func
(paren
id|sb
comma
id|inode-&gt;i_mtime
)paren
suffix:semicolon
id|raw_inode-&gt;i_ctime
op_assign
id|cpu_to_fs32
c_func
(paren
id|sb
comma
id|inode-&gt;i_ctime
)paren
suffix:semicolon
id|si
op_assign
id|SYSV_I
c_func
(paren
id|inode
)paren
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
id|si-&gt;i_data
(braket
l_int|0
)braket
op_assign
id|cpu_to_fs32
c_func
(paren
id|sb
comma
id|kdev_t_to_nr
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|block
op_assign
l_int|0
suffix:semicolon
id|block
OL
l_int|10
op_plus
l_int|1
op_plus
l_int|1
op_plus
l_int|1
suffix:semicolon
id|block
op_increment
)paren
id|write3byte
c_func
(paren
id|sb
comma
(paren
r_int
r_char
op_star
)paren
op_amp
id|si-&gt;i_data
(braket
id|block
)braket
comma
op_amp
id|raw_inode-&gt;i_a.i_addb
(braket
l_int|3
op_star
id|block
)braket
)paren
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
DECL|function|sysv_write_inode
r_void
id|sysv_write_inode
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
id|sysv_update_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|sysv_sync_inode
r_int
id|sysv_sync_inode
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
id|sysv_update_inode
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
l_string|&quot;IO error syncing sysv inode [%s:%08lx]&bslash;n&quot;
comma
id|inode-&gt;i_sb-&gt;s_id
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
DECL|function|sysv_delete_inode
r_static
r_void
id|sysv_delete_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|inode-&gt;i_size
op_assign
l_int|0
suffix:semicolon
id|sysv_truncate
c_func
(paren
id|inode
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|sysv_free_inode
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
DECL|variable|sysv_inode_cachep
r_static
id|kmem_cache_t
op_star
id|sysv_inode_cachep
suffix:semicolon
DECL|function|sysv_alloc_inode
r_static
r_struct
id|inode
op_star
id|sysv_alloc_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|sysv_inode_info
op_star
id|si
suffix:semicolon
id|si
op_assign
id|kmem_cache_alloc
c_func
(paren
id|sysv_inode_cachep
comma
id|SLAB_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|si
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
op_amp
id|si-&gt;vfs_inode
suffix:semicolon
)brace
DECL|function|sysv_destroy_inode
r_static
r_void
id|sysv_destroy_inode
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
id|sysv_inode_cachep
comma
id|SYSV_I
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
id|p
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
id|sysv_inode_info
op_star
id|si
op_assign
(paren
r_struct
id|sysv_inode_info
op_star
)paren
id|p
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
id|si-&gt;vfs_inode
)paren
suffix:semicolon
)brace
DECL|variable|sysv_sops
r_struct
id|super_operations
id|sysv_sops
op_assign
(brace
id|alloc_inode
suffix:colon
id|sysv_alloc_inode
comma
id|destroy_inode
suffix:colon
id|sysv_destroy_inode
comma
id|read_inode
suffix:colon
id|sysv_read_inode
comma
id|write_inode
suffix:colon
id|sysv_write_inode
comma
id|delete_inode
suffix:colon
id|sysv_delete_inode
comma
id|put_super
suffix:colon
id|sysv_put_super
comma
id|write_super
suffix:colon
id|sysv_write_super
comma
id|statfs
suffix:colon
id|sysv_statfs
comma
)brace
suffix:semicolon
DECL|function|sysv_init_icache
r_int
id|__init
id|sysv_init_icache
c_func
(paren
r_void
)paren
(brace
id|sysv_inode_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;sysv_inode_cache&quot;
comma
r_sizeof
(paren
r_struct
id|sysv_inode_info
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
op_logical_neg
id|sysv_inode_cachep
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sysv_destroy_icache
r_void
id|sysv_destroy_icache
c_func
(paren
r_void
)paren
(brace
id|kmem_cache_destroy
c_func
(paren
id|sysv_inode_cachep
)paren
suffix:semicolon
)brace
eof
