multiline_comment|/*&n; * QNX4 file system, Linux implementation.&n; *&n; * Version : 0.2.1&n; *&n; * Using parts of the xiafs filesystem.&n; *&n; * History :&n; *&n; * 01-06-1998 by Richard Frowijn : first release.&n; * 20-06-1998 by Frank Denis : Linux 2.1.99+ support, boot signature, misc.&n; * 30-06-1998 by Frank Denis : first step to write inodes.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/qnx4_fs.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/highuid.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|QNX4_VERSION
mdefine_line|#define QNX4_VERSION  4
DECL|macro|QNX4_BMNAME
mdefine_line|#define QNX4_BMNAME   &quot;.bitmap&quot;
DECL|variable|qnx4_sops
r_static
r_struct
id|super_operations
id|qnx4_sops
suffix:semicolon
macro_line|#ifdef CONFIG_QNX4FS_RW
DECL|function|qnx4_sync_inode
r_int
id|qnx4_sync_inode
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
macro_line|# if 0
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|bh
op_assign
id|qnx4_update_inode
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
l_string|&quot;IO error syncing qnx4 inode [%s:%08lx]&bslash;n&quot;
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
id|brelse
(paren
id|bh
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|err
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|# endif
r_return
id|err
suffix:semicolon
)brace
DECL|function|qnx4_delete_inode
r_static
r_void
id|qnx4_delete_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|QNX4DEBUG
c_func
(paren
(paren
l_string|&quot;qnx4: deleting inode [%lu]&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|inode-&gt;i_ino
)paren
)paren
suffix:semicolon
id|inode-&gt;i_size
op_assign
l_int|0
suffix:semicolon
id|qnx4_truncate
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
id|qnx4_free_inode
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
DECL|function|qnx4_write_super
r_static
r_void
id|qnx4_write_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|QNX4DEBUG
c_func
(paren
(paren
l_string|&quot;qnx4: write_super&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|qnx4_write_inode
r_static
r_void
id|qnx4_write_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|unused
)paren
(brace
r_struct
id|qnx4_inode_entry
op_star
id|raw_inode
suffix:semicolon
r_int
id|block
comma
id|ino
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|QNX4DEBUG
c_func
(paren
(paren
l_string|&quot;qnx4: write inode 1.&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_nlink
op_eq
l_int|0
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ino
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;qnx4: bad inode number on dev %s: %d is out of range&bslash;n&quot;
comma
id|inode-&gt;i_sb-&gt;s_id
comma
id|ino
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|QNX4DEBUG
c_func
(paren
(paren
l_string|&quot;qnx4: write inode 2.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|block
op_assign
id|ino
op_div
id|QNX4_INODES_PER_BLOCK
suffix:semicolon
id|lock_kernel
c_func
(paren
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
id|inode-&gt;i_sb
comma
id|block
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;qnx4: major problem: unable to read inode from dev &quot;
l_string|&quot;%s&bslash;n&quot;
comma
id|inode-&gt;i_sb-&gt;s_id
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|raw_inode
op_assign
(paren
(paren
r_struct
id|qnx4_inode_entry
op_star
)paren
id|bh-&gt;b_data
)paren
op_plus
(paren
id|ino
op_mod
id|QNX4_INODES_PER_BLOCK
)paren
suffix:semicolon
id|raw_inode-&gt;di_mode
op_assign
id|cpu_to_le16
c_func
(paren
id|inode-&gt;i_mode
)paren
suffix:semicolon
id|raw_inode-&gt;di_uid
op_assign
id|cpu_to_le16
c_func
(paren
id|fs_high2lowuid
c_func
(paren
id|inode-&gt;i_uid
)paren
)paren
suffix:semicolon
id|raw_inode-&gt;di_gid
op_assign
id|cpu_to_le16
c_func
(paren
id|fs_high2lowgid
c_func
(paren
id|inode-&gt;i_gid
)paren
)paren
suffix:semicolon
id|raw_inode-&gt;di_nlink
op_assign
id|cpu_to_le16
c_func
(paren
id|inode-&gt;i_nlink
)paren
suffix:semicolon
id|raw_inode-&gt;di_size
op_assign
id|cpu_to_le32
c_func
(paren
id|inode-&gt;i_size
)paren
suffix:semicolon
id|raw_inode-&gt;di_mtime
op_assign
id|cpu_to_le32
c_func
(paren
id|inode-&gt;i_mtime
)paren
suffix:semicolon
id|raw_inode-&gt;di_atime
op_assign
id|cpu_to_le32
c_func
(paren
id|inode-&gt;i_atime
)paren
suffix:semicolon
id|raw_inode-&gt;di_ctime
op_assign
id|cpu_to_le32
c_func
(paren
id|inode-&gt;i_ctime
)paren
suffix:semicolon
id|raw_inode-&gt;di_first_xtnt.xtnt_size
op_assign
id|cpu_to_le32
c_func
(paren
id|inode-&gt;i_blocks
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
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
macro_line|#endif
r_static
r_void
id|qnx4_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_static
r_struct
id|inode
op_star
id|qnx4_alloc_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_static
r_void
id|qnx4_destroy_inode
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
id|qnx4_read_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_static
r_int
id|qnx4_remount
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
suffix:semicolon
r_static
r_int
id|qnx4_statfs
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|statfs
op_star
)paren
suffix:semicolon
DECL|variable|qnx4_sops
r_static
r_struct
id|super_operations
id|qnx4_sops
op_assign
(brace
id|alloc_inode
suffix:colon
id|qnx4_alloc_inode
comma
id|destroy_inode
suffix:colon
id|qnx4_destroy_inode
comma
id|read_inode
suffix:colon
id|qnx4_read_inode
comma
macro_line|#ifdef CONFIG_QNX4FS_RW
id|write_inode
suffix:colon
id|qnx4_write_inode
comma
id|delete_inode
suffix:colon
id|qnx4_delete_inode
comma
macro_line|#endif
id|put_super
suffix:colon
id|qnx4_put_super
comma
macro_line|#ifdef CONFIG_QNX4FS_RW
id|write_super
suffix:colon
id|qnx4_write_super
comma
macro_line|#endif
id|statfs
suffix:colon
id|qnx4_statfs
comma
id|remount_fs
suffix:colon
id|qnx4_remount
comma
)brace
suffix:semicolon
DECL|function|qnx4_remount
r_static
r_int
id|qnx4_remount
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
r_struct
id|qnx4_sb_info
op_star
id|qs
suffix:semicolon
id|qs
op_assign
op_amp
id|sb-&gt;u.qnx4_sb
suffix:semicolon
id|qs-&gt;Version
op_assign
id|QNX4_VERSION
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
r_return
l_int|0
suffix:semicolon
)brace
id|mark_buffer_dirty
c_func
(paren
id|qs-&gt;sb_buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|qnx4_getblk
r_struct
id|buffer_head
op_star
id|qnx4_getblk
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|nr
comma
r_int
id|create
)paren
(brace
r_struct
id|buffer_head
op_star
id|result
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|nr
op_ge
l_int|0
)paren
id|nr
op_assign
id|qnx4_block_map
c_func
(paren
id|inode
comma
id|nr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr
)paren
(brace
id|result
op_assign
id|sb_getblk
c_func
(paren
id|inode-&gt;i_sb
comma
id|nr
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|create
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#if 0
id|tmp
op_assign
id|qnx4_new_block
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|result
op_assign
id|sb_getblk
c_func
(paren
id|inode-&gt;i_sb
comma
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tst
)paren
(brace
id|qnx4_free_block
c_func
(paren
id|inode-&gt;i_sb
comma
id|tmp
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|result
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|tst
op_assign
id|tmp
suffix:semicolon
macro_line|#endif
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|qnx4_bread
r_struct
id|buffer_head
op_star
id|qnx4_bread
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
r_int
id|create
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|bh
op_assign
id|qnx4_getblk
c_func
(paren
id|inode
comma
id|block
comma
id|create
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
op_logical_or
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
(brace
r_return
id|bh
suffix:semicolon
)brace
id|ll_rw_block
c_func
(paren
id|READ
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
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
(brace
r_return
id|bh
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|qnx4_get_block
r_int
id|qnx4_get_block
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|sector_t
id|iblock
comma
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|create
)paren
(brace
r_int
r_int
id|phys
suffix:semicolon
id|QNX4DEBUG
c_func
(paren
(paren
l_string|&quot;qnx4: qnx4_get_block inode=[%ld] iblock=[%ld]&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|iblock
)paren
)paren
suffix:semicolon
id|phys
op_assign
id|qnx4_block_map
c_func
(paren
id|inode
comma
id|iblock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|phys
)paren
(brace
singleline_comment|// logical block is before EOF
id|map_bh
c_func
(paren
id|bh
comma
id|inode-&gt;i_sb
comma
id|phys
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|create
)paren
(brace
singleline_comment|// to be done.
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|qnx4_block_map
r_int
r_int
id|qnx4_block_map
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|iblock
)paren
(brace
r_int
id|ix
suffix:semicolon
r_int
id|offset
comma
id|i_xblk
suffix:semicolon
r_int
r_int
id|block
op_assign
l_int|0
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|0
suffix:semicolon
r_struct
id|qnx4_xblk
op_star
id|xblk
op_assign
l_int|0
suffix:semicolon
r_struct
id|qnx4_inode_entry
op_star
id|qnx4_inode
op_assign
id|qnx4_raw_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|qnx4_nxtnt_t
id|nxtnt
op_assign
id|le16_to_cpu
c_func
(paren
id|qnx4_inode-&gt;di_num_xtnts
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iblock
OL
id|le32_to_cpu
c_func
(paren
id|qnx4_inode-&gt;di_first_xtnt.xtnt_size
)paren
)paren
(brace
singleline_comment|// iblock is in the first extent. This is easy.
id|block
op_assign
id|le32_to_cpu
c_func
(paren
id|qnx4_inode-&gt;di_first_xtnt.xtnt_blk
)paren
op_plus
id|iblock
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// iblock is beyond first extent. We have to follow the extent chain.
id|i_xblk
op_assign
id|le32_to_cpu
c_func
(paren
id|qnx4_inode-&gt;di_xblk
)paren
suffix:semicolon
id|offset
op_assign
id|iblock
op_minus
id|le32_to_cpu
c_func
(paren
id|qnx4_inode-&gt;di_first_xtnt.xtnt_size
)paren
suffix:semicolon
id|ix
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|nxtnt
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|ix
op_eq
l_int|0
)paren
(brace
singleline_comment|// read next xtnt block.
id|bh
op_assign
id|sb_bread
c_func
(paren
id|inode-&gt;i_sb
comma
id|i_xblk
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|QNX4DEBUG
c_func
(paren
(paren
l_string|&quot;qnx4: I/O error reading xtnt block [%ld])&bslash;n&quot;
comma
id|i_xblk
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|xblk
op_assign
(paren
r_struct
id|qnx4_xblk
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|xblk-&gt;xblk_signature
comma
l_string|&quot;IamXblk&quot;
comma
l_int|7
)paren
)paren
(brace
id|QNX4DEBUG
c_func
(paren
(paren
l_string|&quot;qnx4: block at %ld is not a valid xtnt&bslash;n&quot;
comma
id|qnx4_inode-&gt;i_xblk
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|offset
OL
id|le32_to_cpu
c_func
(paren
id|xblk-&gt;xblk_xtnts
(braket
id|ix
)braket
dot
id|xtnt_size
)paren
)paren
(brace
singleline_comment|// got it!
id|block
op_assign
id|le32_to_cpu
c_func
(paren
id|xblk-&gt;xblk_xtnts
(braket
id|ix
)braket
dot
id|xtnt_blk
)paren
op_plus
id|offset
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|offset
op_sub_assign
id|le32_to_cpu
c_func
(paren
id|xblk-&gt;xblk_xtnts
(braket
id|ix
)braket
dot
id|xtnt_size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|ix
op_ge
id|xblk-&gt;xblk_num_xtnts
)paren
(brace
id|i_xblk
op_assign
id|le32_to_cpu
c_func
(paren
id|xblk-&gt;xblk_next_xblk
)paren
suffix:semicolon
id|ix
op_assign
l_int|0
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|bh
)paren
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
id|QNX4DEBUG
c_func
(paren
(paren
l_string|&quot;qnx4: mapping block %ld of inode %ld = %ld&bslash;n&quot;
comma
id|iblock
comma
id|inode-&gt;i_ino
comma
id|block
)paren
)paren
suffix:semicolon
r_return
id|block
suffix:semicolon
)brace
DECL|function|qnx4_statfs
r_static
r_int
id|qnx4_statfs
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
id|le32_to_cpu
c_func
(paren
id|sb-&gt;u.qnx4_sb.BitMap-&gt;di_size
)paren
op_star
l_int|8
suffix:semicolon
id|buf-&gt;f_bfree
op_assign
id|qnx4_count_free_blocks
c_func
(paren
id|sb
)paren
suffix:semicolon
id|buf-&gt;f_bavail
op_assign
id|buf-&gt;f_bfree
suffix:semicolon
id|buf-&gt;f_namelen
op_assign
id|QNX4_NAME_MAX
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Check the root directory of the filesystem to make sure&n; * it really _is_ a qnx4 filesystem, and to check the size&n; * of the directory entry.&n; */
DECL|function|qnx4_checkroot
r_static
r_const
r_char
op_star
id|qnx4_checkroot
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|qnx4_inode_entry
op_star
id|rootdir
suffix:semicolon
r_int
id|rd
comma
id|rl
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_int
id|found
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
(paren
id|sb-&gt;u.qnx4_sb.sb-&gt;RootDir.di_fname
)paren
op_ne
l_char|&squot;/&squot;
)paren
(brace
r_return
l_string|&quot;no qnx4 filesystem (no root dir).&quot;
suffix:semicolon
)brace
r_else
(brace
id|QNX4DEBUG
c_func
(paren
(paren
l_string|&quot;QNX4 filesystem found on dev %s.&bslash;n&quot;
comma
id|sb-&gt;s_id
)paren
)paren
suffix:semicolon
id|rd
op_assign
id|le32_to_cpu
c_func
(paren
id|sb-&gt;u.qnx4_sb.sb-&gt;RootDir.di_first_xtnt.xtnt_blk
)paren
op_minus
l_int|1
suffix:semicolon
id|rl
op_assign
id|le32_to_cpu
c_func
(paren
id|sb-&gt;u.qnx4_sb.sb-&gt;RootDir.di_first_xtnt.xtnt_size
)paren
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
id|rl
suffix:semicolon
id|j
op_increment
)paren
(brace
id|bh
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
id|rd
op_plus
id|j
)paren
suffix:semicolon
multiline_comment|/* root dir, first block */
r_if
c_cond
(paren
id|bh
op_eq
l_int|NULL
)paren
(brace
r_return
l_string|&quot;unable to read root entry.&quot;
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
id|QNX4_INODES_PER_BLOCK
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rootdir
op_assign
(paren
r_struct
id|qnx4_inode_entry
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
id|i
op_star
id|QNX4_DIR_ENTRY_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rootdir-&gt;di_fname
op_ne
l_int|NULL
)paren
(brace
id|QNX4DEBUG
c_func
(paren
(paren
l_string|&quot;Rootdir entry found : [%s]&bslash;n&quot;
comma
id|rootdir-&gt;di_fname
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|rootdir-&gt;di_fname
comma
id|QNX4_BMNAME
comma
r_sizeof
id|QNX4_BMNAME
)paren
)paren
(brace
id|found
op_assign
l_int|1
suffix:semicolon
id|sb-&gt;u.qnx4_sb.BitMap
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|qnx4_inode_entry
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|sb-&gt;u.qnx4_sb.BitMap
comma
id|rootdir
comma
r_sizeof
(paren
r_struct
id|qnx4_inode_entry
)paren
)paren
suffix:semicolon
multiline_comment|/* keep bitmap inode known */
r_break
suffix:semicolon
)brace
)brace
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
id|found
op_ne
l_int|0
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|found
op_eq
l_int|0
)paren
(brace
r_return
l_string|&quot;bitmap file not found.&quot;
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|qnx4_fill_super
r_static
r_int
id|qnx4_fill_super
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
id|inode
op_star
id|root
suffix:semicolon
r_const
r_char
op_star
id|errmsg
suffix:semicolon
id|sb_set_blocksize
c_func
(paren
id|s
comma
id|QNX4_BLOCK_SIZE
)paren
suffix:semicolon
multiline_comment|/* Check the boot signature. Since the qnx4 code is&n;&t;   dangerous, we should leave as quickly as possible&n;&t;   if we don&squot;t belong here... */
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
l_string|&quot;qnx4: unable to read the boot sector&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|outnobh
suffix:semicolon
)brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
(paren
r_char
op_star
)paren
id|bh-&gt;b_data
op_plus
l_int|4
comma
l_string|&quot;QNX4FS&quot;
comma
l_int|6
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
l_string|&quot;qnx4: wrong fsid in boot sector.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
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
id|sb_bread
c_func
(paren
id|s
comma
l_int|1
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
l_string|&quot;qnx4: unable to read the superblock&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|outnobh
suffix:semicolon
)brace
id|s-&gt;s_op
op_assign
op_amp
id|qnx4_sops
suffix:semicolon
id|s-&gt;s_magic
op_assign
id|QNX4_SUPER_MAGIC
suffix:semicolon
macro_line|#ifndef CONFIG_QNX4FS_RW
id|s-&gt;s_flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
multiline_comment|/* Yup, read-only yet */
macro_line|#endif
id|s-&gt;u.qnx4_sb.sb_buf
op_assign
id|bh
suffix:semicolon
id|s-&gt;u.qnx4_sb.sb
op_assign
(paren
r_struct
id|qnx4_super_block
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
multiline_comment|/* check before allocating dentries, inodes, .. */
id|errmsg
op_assign
id|qnx4_checkroot
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|errmsg
op_ne
l_int|NULL
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
l_string|&quot;qnx4: %s&bslash;n&quot;
comma
id|errmsg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* does root not have inode number QNX4_ROOT_INO ?? */
id|root
op_assign
id|iget
c_func
(paren
id|s
comma
id|QNX4_ROOT_INO
op_star
id|QNX4_INODES_PER_BLOCK
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;qnx4: get inode failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|s-&gt;s_root
op_assign
id|d_alloc_root
c_func
(paren
id|root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;s_root
op_eq
l_int|NULL
)paren
r_goto
id|outi
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|outi
suffix:colon
id|iput
c_func
(paren
id|root
)paren
suffix:semicolon
id|out
suffix:colon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|outnobh
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|qnx4_put_super
r_static
r_void
id|qnx4_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|kfree
c_func
(paren
id|sb-&gt;u.qnx4_sb.BitMap
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|qnx4_writepage
r_static
r_int
id|qnx4_writepage
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
id|qnx4_get_block
)paren
suffix:semicolon
)brace
DECL|function|qnx4_readpage
r_static
r_int
id|qnx4_readpage
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
id|qnx4_get_block
)paren
suffix:semicolon
)brace
DECL|function|qnx4_prepare_write
r_static
r_int
id|qnx4_prepare_write
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
r_struct
id|qnx4_inode_info
op_star
id|qnx4_inode
op_assign
id|qnx4_i
c_func
(paren
id|page-&gt;mapping-&gt;host
)paren
suffix:semicolon
r_return
id|cont_prepare_write
c_func
(paren
id|page
comma
id|from
comma
id|to
comma
id|qnx4_get_block
comma
op_amp
id|qnx4_inode-&gt;mmu_private
)paren
suffix:semicolon
)brace
DECL|function|qnx4_bmap
r_static
r_int
id|qnx4_bmap
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
id|qnx4_get_block
)paren
suffix:semicolon
)brace
DECL|variable|qnx4_aops
r_struct
id|address_space_operations
id|qnx4_aops
op_assign
(brace
id|readpage
suffix:colon
id|qnx4_readpage
comma
id|writepage
suffix:colon
id|qnx4_writepage
comma
id|sync_page
suffix:colon
id|block_sync_page
comma
id|prepare_write
suffix:colon
id|qnx4_prepare_write
comma
id|commit_write
suffix:colon
id|generic_commit_write
comma
id|bmap
suffix:colon
id|qnx4_bmap
)brace
suffix:semicolon
DECL|function|qnx4_read_inode
r_static
r_void
id|qnx4_read_inode
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
id|qnx4_inode_entry
op_star
id|raw_inode
suffix:semicolon
r_int
id|block
comma
id|ino
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_struct
id|qnx4_inode_entry
op_star
id|qnx4_inode
op_assign
id|qnx4_raw_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|inode-&gt;i_mode
op_assign
l_int|0
suffix:semicolon
id|QNX4DEBUG
c_func
(paren
(paren
l_string|&quot;Reading inode : [%d]&bslash;n&quot;
comma
id|ino
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ino
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;qnx4: bad inode number on dev %s: %d is out of range&bslash;n&quot;
comma
id|sb-&gt;s_id
comma
id|ino
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|block
op_assign
id|ino
op_div
id|QNX4_INODES_PER_BLOCK
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
id|block
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;qnx4: major problem: unable to read inode from dev &quot;
l_string|&quot;%s&bslash;n&quot;
comma
id|sb-&gt;s_id
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|raw_inode
op_assign
(paren
(paren
r_struct
id|qnx4_inode_entry
op_star
)paren
id|bh-&gt;b_data
)paren
op_plus
(paren
id|ino
op_mod
id|QNX4_INODES_PER_BLOCK
)paren
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|le16_to_cpu
c_func
(paren
id|raw_inode-&gt;di_mode
)paren
suffix:semicolon
id|inode-&gt;i_uid
op_assign
(paren
id|uid_t
)paren
id|le16_to_cpu
c_func
(paren
id|raw_inode-&gt;di_uid
)paren
suffix:semicolon
id|inode-&gt;i_gid
op_assign
(paren
id|gid_t
)paren
id|le16_to_cpu
c_func
(paren
id|raw_inode-&gt;di_gid
)paren
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
id|le16_to_cpu
c_func
(paren
id|raw_inode-&gt;di_nlink
)paren
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|le32_to_cpu
c_func
(paren
id|raw_inode-&gt;di_size
)paren
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|le32_to_cpu
c_func
(paren
id|raw_inode-&gt;di_mtime
)paren
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|le32_to_cpu
c_func
(paren
id|raw_inode-&gt;di_atime
)paren
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|le32_to_cpu
c_func
(paren
id|raw_inode-&gt;di_ctime
)paren
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
id|le32_to_cpu
c_func
(paren
id|raw_inode-&gt;di_first_xtnt.xtnt_size
)paren
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
id|QNX4_DIR_ENTRY_SIZE
suffix:semicolon
id|memcpy
c_func
(paren
id|qnx4_inode
comma
id|raw_inode
comma
id|QNX4_DIR_ENTRY_SIZE
)paren
suffix:semicolon
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
id|qnx4_file_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|qnx4_file_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|qnx4_aops
suffix:semicolon
id|qnx4_i
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|mmu_private
op_assign
id|inode-&gt;i_size
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
id|qnx4_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|qnx4_dir_operations
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
id|qnx4_aops
suffix:semicolon
id|qnx4_i
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|mmu_private
op_assign
id|inode-&gt;i_size
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;qnx4: bad inode %d on dev %s&bslash;n&quot;
comma
id|ino
comma
id|sb-&gt;s_id
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
DECL|variable|qnx4_inode_cachep
r_static
id|kmem_cache_t
op_star
id|qnx4_inode_cachep
suffix:semicolon
DECL|function|qnx4_alloc_inode
r_static
r_struct
id|inode
op_star
id|qnx4_alloc_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|qnx4_inode_info
op_star
id|ei
suffix:semicolon
id|ei
op_assign
id|kmem_cache_alloc
c_func
(paren
id|qnx4_inode_cachep
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
DECL|function|qnx4_destroy_inode
r_static
r_void
id|qnx4_destroy_inode
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
id|qnx4_inode_cachep
comma
id|qnx4_i
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
id|qnx4_inode_info
op_star
id|ei
op_assign
(paren
r_struct
id|qnx4_inode_info
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
id|qnx4_inode_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;qnx4_inode_cache&quot;
comma
r_sizeof
(paren
r_struct
id|qnx4_inode_info
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
id|qnx4_inode_cachep
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
id|qnx4_inode_cachep
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;qnx4_inode_cache: not all structures were freed&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|qnx4_get_sb
r_static
r_struct
id|super_block
op_star
id|qnx4_get_sb
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
id|qnx4_fill_super
)paren
suffix:semicolon
)brace
DECL|variable|qnx4_fs_type
r_static
r_struct
id|file_system_type
id|qnx4_fs_type
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|name
suffix:colon
l_string|&quot;qnx4&quot;
comma
id|get_sb
suffix:colon
id|qnx4_get_sb
comma
id|kill_sb
suffix:colon
id|kill_block_super
comma
id|fs_flags
suffix:colon
id|FS_REQUIRES_DEV
comma
)brace
suffix:semicolon
DECL|function|init_qnx4_fs
r_static
r_int
id|__init
id|init_qnx4_fs
c_func
(paren
r_void
)paren
(brace
r_int
id|err
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
r_return
id|err
suffix:semicolon
id|err
op_assign
id|register_filesystem
c_func
(paren
op_amp
id|qnx4_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|destroy_inodecache
c_func
(paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;QNX4 filesystem 0.2.2 registered.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|exit_qnx4_fs
r_static
r_void
id|__exit
id|exit_qnx4_fs
c_func
(paren
r_void
)paren
(brace
id|unregister_filesystem
c_func
(paren
op_amp
id|qnx4_fs_type
)paren
suffix:semicolon
id|destroy_inodecache
c_func
(paren
)paren
suffix:semicolon
)brace
id|EXPORT_NO_SYMBOLS
suffix:semicolon
id|module_init
c_func
(paren
id|init_qnx4_fs
)paren
id|module_exit
c_func
(paren
id|exit_qnx4_fs
)paren
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
