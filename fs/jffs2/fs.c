multiline_comment|/*&n; * JFFS2 -- Journalling Flash File System, Version 2.&n; *&n; * Copyright (C) 2001, 2002 Red Hat, Inc.&n; *&n; * Created by David Woodhouse &lt;dwmw2@cambridge.redhat.com&gt;&n; *&n; * For licensing information, see the file &squot;LICENCE&squot; in this directory.&n; *&n; * $Id: fs.c,v 1.19 2002/11/12 09:53:40 dwmw2 Exp $&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &quot;nodelist.h&quot;
DECL|function|jffs2_statfs
r_int
id|jffs2_statfs
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
id|jffs2_sb_info
op_star
id|c
op_assign
id|JFFS2_SB_INFO
c_func
(paren
id|sb
)paren
suffix:semicolon
r_int
r_int
id|avail
suffix:semicolon
id|buf-&gt;f_type
op_assign
id|JFFS2_SUPER_MAGIC
suffix:semicolon
id|buf-&gt;f_bsize
op_assign
l_int|1
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|buf-&gt;f_blocks
op_assign
id|c-&gt;flash_size
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|buf-&gt;f_files
op_assign
l_int|0
suffix:semicolon
id|buf-&gt;f_ffree
op_assign
l_int|0
suffix:semicolon
id|buf-&gt;f_namelen
op_assign
id|JFFS2_MAX_NAME_LEN
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|c-&gt;erase_completion_lock
)paren
suffix:semicolon
id|avail
op_assign
id|c-&gt;dirty_size
op_plus
id|c-&gt;free_size
suffix:semicolon
r_if
c_cond
(paren
id|avail
OG
id|c-&gt;sector_size
op_star
id|JFFS2_RESERVED_BLOCKS_WRITE
)paren
id|avail
op_sub_assign
id|c-&gt;sector_size
op_star
id|JFFS2_RESERVED_BLOCKS_WRITE
suffix:semicolon
r_else
id|avail
op_assign
l_int|0
suffix:semicolon
id|buf-&gt;f_bavail
op_assign
id|buf-&gt;f_bfree
op_assign
id|avail
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|D1
c_func
(paren
id|jffs2_dump_block_lists
c_func
(paren
id|c
)paren
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|c-&gt;erase_completion_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|jffs2_clear_inode
r_void
id|jffs2_clear_inode
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
multiline_comment|/* We can forget about this inode for now - drop all &n;&t; *  the nodelists associated with it, etc.&n;&t; */
r_struct
id|jffs2_sb_info
op_star
id|c
op_assign
id|JFFS2_SB_INFO
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_struct
id|jffs2_inode_info
op_star
id|f
op_assign
id|JFFS2_INODE_INFO
c_func
(paren
id|inode
)paren
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_clear_inode(): ino #%lu mode %o&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|inode-&gt;i_mode
)paren
)paren
suffix:semicolon
id|jffs2_do_clear_inode
c_func
(paren
id|c
comma
id|f
)paren
suffix:semicolon
)brace
DECL|function|jffs2_read_inode
r_void
id|jffs2_read_inode
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|jffs2_inode_info
op_star
id|f
suffix:semicolon
r_struct
id|jffs2_sb_info
op_star
id|c
suffix:semicolon
r_struct
id|jffs2_raw_inode
id|latest_node
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_read_inode(): inode-&gt;i_ino == %lu&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
)paren
suffix:semicolon
id|f
op_assign
id|JFFS2_INODE_INFO
c_func
(paren
id|inode
)paren
suffix:semicolon
id|c
op_assign
id|JFFS2_SB_INFO
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
id|jffs2_init_inode_info
c_func
(paren
id|f
)paren
suffix:semicolon
id|ret
op_assign
id|jffs2_do_read_inode
c_func
(paren
id|c
comma
id|f
comma
id|inode-&gt;i_ino
comma
op_amp
id|latest_node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|make_bad_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|f-&gt;sem
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|inode-&gt;i_mode
op_assign
id|je32_to_cpu
c_func
(paren
id|latest_node.mode
)paren
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|je16_to_cpu
c_func
(paren
id|latest_node.uid
)paren
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|je16_to_cpu
c_func
(paren
id|latest_node.gid
)paren
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|je32_to_cpu
c_func
(paren
id|latest_node.isize
)paren
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|je32_to_cpu
c_func
(paren
id|latest_node.atime
)paren
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|je32_to_cpu
c_func
(paren
id|latest_node.mtime
)paren
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|je32_to_cpu
c_func
(paren
id|latest_node.ctime
)paren
suffix:semicolon
id|inode-&gt;i_atime.tv_nsec
op_assign
id|inode-&gt;i_mtime.tv_nsec
op_assign
id|inode-&gt;i_ctime.tv_nsec
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
id|f-&gt;inocache-&gt;nlink
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
id|PAGE_SIZE
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
(paren
id|inode-&gt;i_size
op_plus
l_int|511
)paren
op_rshift
l_int|9
suffix:semicolon
r_switch
c_cond
(paren
id|inode-&gt;i_mode
op_amp
id|S_IFMT
)paren
(brace
r_int
r_int
id|rdev
suffix:semicolon
r_case
id|S_IFLNK
suffix:colon
id|inode-&gt;i_op
op_assign
op_amp
id|jffs2_symlink_inode_operations
suffix:semicolon
r_break
suffix:semicolon
r_case
id|S_IFDIR
suffix:colon
(brace
r_struct
id|jffs2_full_dirent
op_star
id|fd
suffix:semicolon
r_for
c_loop
(paren
id|fd
op_assign
id|f-&gt;dents
suffix:semicolon
id|fd
suffix:semicolon
id|fd
op_assign
id|fd-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|fd-&gt;type
op_eq
id|DT_DIR
op_logical_and
id|fd-&gt;ino
)paren
id|inode-&gt;i_nlink
op_increment
suffix:semicolon
)brace
multiline_comment|/* and &squot;..&squot; */
id|inode-&gt;i_nlink
op_increment
suffix:semicolon
multiline_comment|/* Root dir gets i_nlink 3 for some reason */
r_if
c_cond
(paren
id|inode-&gt;i_ino
op_eq
l_int|1
)paren
id|inode-&gt;i_nlink
op_increment
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|jffs2_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|jffs2_dir_operations
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|S_IFREG
suffix:colon
id|inode-&gt;i_op
op_assign
op_amp
id|jffs2_file_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|jffs2_file_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|jffs2_file_address_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;nrpages
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|S_IFBLK
suffix:colon
r_case
id|S_IFCHR
suffix:colon
multiline_comment|/* Read the device numbers from the media */
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Reading device numbers from flash&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|jffs2_read_dnode
c_func
(paren
id|c
comma
id|f-&gt;metadata
comma
(paren
r_char
op_star
)paren
op_amp
id|rdev
comma
l_int|0
comma
r_sizeof
(paren
id|rdev
)paren
)paren
OL
l_int|0
)paren
(brace
multiline_comment|/* Eep */
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Read device numbers for inode %lu failed&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|f-&gt;sem
)paren
suffix:semicolon
id|jffs2_do_clear_inode
c_func
(paren
id|c
comma
id|f
)paren
suffix:semicolon
id|make_bad_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_case
id|S_IFSOCK
suffix:colon
r_case
id|S_IFIFO
suffix:colon
id|inode-&gt;i_op
op_assign
op_amp
id|jffs2_file_inode_operations
suffix:semicolon
id|init_special_inode
c_func
(paren
id|inode
comma
id|inode-&gt;i_mode
comma
id|kdev_t_to_nr
c_func
(paren
id|mk_kdev
c_func
(paren
id|rdev
op_rshift
l_int|8
comma
id|rdev
op_amp
l_int|0xff
)paren
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;jffs2_read_inode(): Bogus imode %o for ino %lu&bslash;n&quot;
comma
id|inode-&gt;i_mode
comma
(paren
r_int
r_int
)paren
id|inode-&gt;i_ino
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|f-&gt;sem
)paren
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_read_inode() returning&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
DECL|function|jffs2_remount_fs
r_int
id|jffs2_remount_fs
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
id|jffs2_sb_info
op_star
id|c
op_assign
id|JFFS2_SB_INFO
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;flags
op_amp
id|JFFS2_SB_FLAG_RO
op_logical_and
op_logical_neg
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
r_return
op_minus
id|EROFS
suffix:semicolon
multiline_comment|/* We stop if it was running, then restart if it needs to.&n;&t;   This also catches the case where it was stopped and this&n;&t;   is just a remount to restart it */
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
id|jffs2_stop_garbage_collect_thread
c_func
(paren
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|flags
op_amp
id|MS_RDONLY
)paren
)paren
id|jffs2_start_garbage_collect_thread
c_func
(paren
id|c
)paren
suffix:semicolon
id|sb-&gt;s_flags
op_assign
(paren
id|sb-&gt;s_flags
op_amp
op_complement
id|MS_RDONLY
)paren
op_or
(paren
op_star
id|flags
op_amp
id|MS_RDONLY
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|jffs2_write_super
r_void
id|jffs2_write_super
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|jffs2_sb_info
op_star
id|c
op_assign
id|JFFS2_SB_INFO
c_func
(paren
id|sb
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
r_return
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_write_super()&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|jffs2_garbage_collect_trigger
c_func
(paren
id|c
)paren
suffix:semicolon
id|jffs2_erase_pending_blocks
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
multiline_comment|/* jffs2_new_inode: allocate a new inode and inocache, add it to the hash,&n;   fill in the raw_inode while you&squot;re at it. */
DECL|function|jffs2_new_inode
r_struct
id|inode
op_star
id|jffs2_new_inode
(paren
r_struct
id|inode
op_star
id|dir_i
comma
r_int
id|mode
comma
r_struct
id|jffs2_raw_inode
op_star
id|ri
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
op_assign
id|dir_i-&gt;i_sb
suffix:semicolon
r_struct
id|jffs2_sb_info
op_star
id|c
suffix:semicolon
r_struct
id|jffs2_inode_info
op_star
id|f
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_new_inode(): dir_i %ld, mode 0x%x&bslash;n&quot;
comma
id|dir_i-&gt;i_ino
comma
id|mode
)paren
)paren
suffix:semicolon
id|c
op_assign
id|JFFS2_SB_INFO
c_func
(paren
id|sb
)paren
suffix:semicolon
id|inode
op_assign
id|new_inode
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|f
op_assign
id|JFFS2_INODE_INFO
c_func
(paren
id|inode
)paren
suffix:semicolon
id|jffs2_init_inode_info
c_func
(paren
id|f
)paren
suffix:semicolon
id|memset
c_func
(paren
id|ri
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|ri
)paren
)paren
suffix:semicolon
multiline_comment|/* Set OS-specific defaults for new inodes */
id|ri-&gt;uid
op_assign
id|cpu_to_je16
c_func
(paren
id|current-&gt;fsuid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dir_i-&gt;i_mode
op_amp
id|S_ISGID
)paren
(brace
id|ri-&gt;gid
op_assign
id|cpu_to_je16
c_func
(paren
id|dir_i-&gt;i_gid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
id|mode
op_or_assign
id|S_ISGID
suffix:semicolon
)brace
r_else
(brace
id|ri-&gt;gid
op_assign
id|cpu_to_je16
c_func
(paren
id|current-&gt;fsgid
)paren
suffix:semicolon
)brace
id|ri-&gt;mode
op_assign
id|cpu_to_je32
c_func
(paren
id|mode
)paren
suffix:semicolon
id|ret
op_assign
id|jffs2_do_new_inode
(paren
id|c
comma
id|f
comma
id|mode
comma
id|ri
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|make_bad_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|ret
)paren
suffix:semicolon
)brace
id|inode-&gt;i_nlink
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_ino
op_assign
id|je32_to_cpu
c_func
(paren
id|ri-&gt;ino
)paren
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|je32_to_cpu
c_func
(paren
id|ri-&gt;mode
)paren
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|je16_to_cpu
c_func
(paren
id|ri-&gt;gid
)paren
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|je16_to_cpu
c_func
(paren
id|ri-&gt;uid
)paren
suffix:semicolon
id|inode-&gt;i_atime.tv_nsec
op_assign
id|inode-&gt;i_ctime.tv_nsec
op_assign
id|inode-&gt;i_mtime.tv_nsec
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_atime.tv_sec
op_assign
id|inode-&gt;i_ctime.tv_sec
op_assign
id|inode-&gt;i_mtime.tv_sec
op_assign
id|get_seconds
c_func
(paren
)paren
suffix:semicolon
id|ri-&gt;atime
op_assign
id|ri-&gt;mtime
op_assign
id|ri-&gt;ctime
op_assign
id|cpu_to_je32
c_func
(paren
id|inode-&gt;i_mtime.tv_sec
)paren
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
id|PAGE_SIZE
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_size
op_assign
l_int|0
suffix:semicolon
id|insert_inode_hash
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|inode
suffix:semicolon
)brace
DECL|function|jffs2_do_fill_super
r_int
id|jffs2_do_fill_super
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
id|jffs2_sb_info
op_star
id|c
suffix:semicolon
r_struct
id|inode
op_star
id|root_i
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|c
op_assign
id|JFFS2_SB_INFO
c_func
(paren
id|sb
)paren
suffix:semicolon
id|c-&gt;sector_size
op_assign
id|c-&gt;mtd-&gt;erasesize
suffix:semicolon
id|c-&gt;flash_size
op_assign
id|c-&gt;mtd-&gt;size
suffix:semicolon
macro_line|#if 0
r_if
c_cond
(paren
id|c-&gt;sector_size
OL
l_int|0x10000
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;jffs2: Erase block size too small (%dKiB). Using 64KiB instead&bslash;n&quot;
comma
id|c-&gt;sector_size
op_div
l_int|1024
)paren
suffix:semicolon
id|c-&gt;sector_size
op_assign
l_int|0x10000
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|c-&gt;flash_size
OL
l_int|5
op_star
id|c-&gt;sector_size
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;jffs2: Too few erase blocks (%d)&bslash;n&quot;
comma
id|c-&gt;flash_size
op_div
id|c-&gt;sector_size
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|c-&gt;cleanmarker_size
op_assign
r_sizeof
(paren
r_struct
id|jffs2_unknown_node
)paren
suffix:semicolon
multiline_comment|/* J&#xfffd;rn -- stick alignment for weird 8-byte-page flash here */
r_if
c_cond
(paren
id|jffs2_cleanmarker_oob
c_func
(paren
id|c
)paren
)paren
(brace
multiline_comment|/* Cleanmarker is out-of-band, so inline size zero */
id|c-&gt;cleanmarker_size
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c-&gt;mtd-&gt;type
op_eq
id|MTD_NANDFLASH
)paren
(brace
multiline_comment|/* Initialise write buffer */
id|c-&gt;wbuf_pagesize
op_assign
id|c-&gt;mtd-&gt;oobblock
suffix:semicolon
id|c-&gt;wbuf_ofs
op_assign
l_int|0xFFFFFFFF
suffix:semicolon
id|c-&gt;wbuf
op_assign
id|kmalloc
c_func
(paren
id|c-&gt;wbuf_pagesize
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c-&gt;wbuf
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* Initialise process for timed wbuf flush */
id|INIT_WORK
c_func
(paren
op_amp
id|c-&gt;wbuf_task
comma
(paren
r_void
op_star
)paren
id|jffs2_wbuf_process
comma
(paren
r_void
op_star
)paren
id|c
)paren
suffix:semicolon
multiline_comment|/* Initialise timer for timed wbuf flush */
id|init_timer
c_func
(paren
op_amp
id|c-&gt;wbuf_timer
)paren
suffix:semicolon
id|c-&gt;wbuf_timer.function
op_assign
id|jffs2_wbuf_timeout
suffix:semicolon
id|c-&gt;wbuf_timer.data
op_assign
(paren
r_int
r_int
)paren
id|c
suffix:semicolon
)brace
id|c-&gt;inocache_list
op_assign
id|kmalloc
c_func
(paren
id|INOCACHE_HASHSIZE
op_star
r_sizeof
(paren
r_struct
id|jffs2_inode_cache
op_star
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c-&gt;inocache_list
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out_wbuf
suffix:semicolon
)brace
id|memset
c_func
(paren
id|c-&gt;inocache_list
comma
l_int|0
comma
id|INOCACHE_HASHSIZE
op_star
r_sizeof
(paren
r_struct
id|jffs2_inode_cache
op_star
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|jffs2_do_mount_fs
c_func
(paren
id|c
)paren
)paren
)paren
r_goto
id|out_inohash
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_do_fill_super(): Getting root inode&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|root_i
op_assign
id|iget
c_func
(paren
id|sb
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_bad_inode
c_func
(paren
id|root_i
)paren
)paren
(brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;get root inode failed&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_goto
id|out_nodes
suffix:semicolon
)brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_do_fill_super(): d_alloc_root()&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|sb-&gt;s_root
op_assign
id|d_alloc_root
c_func
(paren
id|root_i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;s_root
)paren
r_goto
id|out_root_i
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= 0x20403
id|sb-&gt;s_maxbytes
op_assign
l_int|0xFFFFFFFF
suffix:semicolon
macro_line|#endif
id|sb-&gt;s_blocksize
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|sb-&gt;s_blocksize_bits
op_assign
id|PAGE_CACHE_SHIFT
suffix:semicolon
id|sb-&gt;s_magic
op_assign
id|JFFS2_SUPER_MAGIC
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
id|jffs2_start_garbage_collect_thread
c_func
(paren
id|c
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_root_i
suffix:colon
id|iput
c_func
(paren
id|root_i
)paren
suffix:semicolon
id|out_nodes
suffix:colon
id|jffs2_free_ino_caches
c_func
(paren
id|c
)paren
suffix:semicolon
id|jffs2_free_raw_node_refs
c_func
(paren
id|c
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|c-&gt;blocks
)paren
suffix:semicolon
id|out_inohash
suffix:colon
id|kfree
c_func
(paren
id|c-&gt;inocache_list
)paren
suffix:semicolon
id|out_wbuf
suffix:colon
r_if
c_cond
(paren
id|c-&gt;wbuf
)paren
id|kfree
c_func
(paren
id|c-&gt;wbuf
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
