multiline_comment|/*&n; *  linux/fs/ext3/ialloc.c&n; *&n; * Copyright (C) 1992, 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  BSD ufs-inspired inode and directory allocation by&n; *  Stephen Tweedie (sct@redhat.com), 1993&n; *  Big-endian to little-endian byte-swapping/bitmaps by&n; *        David S. Miller (davem@caip.rutgers.edu), 1995&n; */
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/jbd.h&gt;
macro_line|#include &lt;linux/ext3_fs.h&gt;
macro_line|#include &lt;linux/ext3_jbd.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/quotaops.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
multiline_comment|/*&n; * ialloc.c contains the inodes allocation and deallocation routines&n; */
multiline_comment|/*&n; * The free inodes are managed by bitmaps.  A file system contains several&n; * blocks groups.  Each group contains 1 bitmap block for blocks, 1 bitmap&n; * block for inodes, N blocks for the inode table and data blocks.&n; *&n; * The file system contains group descriptors which are located after the&n; * super block.  Each descriptor contains the number of the bitmap block and&n; * the free blocks count in the block.  The descriptors are loaded in memory&n; * when a file system is mounted (see ext3_read_super).&n; */
multiline_comment|/*&n; * Read the inode allocation bitmap for a given block_group, reading&n; * into the specified slot in the superblock&squot;s bitmap cache.&n; *&n; * Return &gt;=0 on success or a -ve error code.&n; */
DECL|function|read_inode_bitmap
r_static
r_int
id|read_inode_bitmap
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|block_group
comma
r_int
r_int
id|bitmap_nr
)paren
(brace
r_struct
id|ext3_group_desc
op_star
id|gdp
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|gdp
op_assign
id|ext3_get_group_desc
(paren
id|sb
comma
id|block_group
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gdp
)paren
(brace
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|error_out
suffix:semicolon
)brace
id|bh
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
id|le32_to_cpu
c_func
(paren
id|gdp-&gt;bg_inode_bitmap
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|ext3_error
(paren
id|sb
comma
l_string|&quot;read_inode_bitmap&quot;
comma
l_string|&quot;Cannot read inode bitmap - &quot;
l_string|&quot;block_group = %lu, inode_bitmap = %lu&quot;
comma
id|block_group
comma
(paren
r_int
r_int
)paren
id|gdp-&gt;bg_inode_bitmap
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * On IO error, just leave a zero in the superblock&squot;s block pointer for&n;&t; * this group.  The IO will be retried next time.&n;&t; */
id|error_out
suffix:colon
id|sb-&gt;u.ext3_sb.s_inode_bitmap_number
(braket
id|bitmap_nr
)braket
op_assign
id|block_group
suffix:semicolon
id|sb-&gt;u.ext3_sb.s_inode_bitmap
(braket
id|bitmap_nr
)braket
op_assign
id|bh
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * load_inode_bitmap loads the inode bitmap for a blocks group&n; *&n; * It maintains a cache for the last bitmaps loaded.  This cache is managed&n; * with a LRU algorithm.&n; *&n; * Notes:&n; * 1/ There is one cache per mounted file system.&n; * 2/ If the file system contains less than EXT3_MAX_GROUP_LOADED groups,&n; *    this function reads the bitmap without maintaining a LRU cache.&n; *&n; * Return the slot used to store the bitmap, or a -ve error code.&n; */
DECL|function|load_inode_bitmap
r_static
r_int
id|load_inode_bitmap
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|block_group
)paren
(brace
r_struct
id|ext3_sb_info
op_star
id|sbi
op_assign
id|EXT3_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
r_int
r_int
id|inode_bitmap_number
suffix:semicolon
r_struct
id|buffer_head
op_star
id|inode_bitmap
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|retval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|block_group
op_ge
id|sbi-&gt;s_groups_count
)paren
id|ext3_panic
(paren
id|sb
comma
l_string|&quot;load_inode_bitmap&quot;
comma
l_string|&quot;block_group &gt;= groups_count - &quot;
l_string|&quot;block_group = %d, groups_count = %lu&quot;
comma
id|block_group
comma
id|sbi-&gt;s_groups_count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sbi-&gt;s_loaded_inode_bitmaps
OG
l_int|0
op_logical_and
id|sbi-&gt;s_inode_bitmap_number
(braket
l_int|0
)braket
op_eq
id|block_group
op_logical_and
id|sbi-&gt;s_inode_bitmap
(braket
l_int|0
)braket
op_ne
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sbi-&gt;s_groups_count
op_le
id|EXT3_MAX_GROUP_LOADED
)paren
(brace
r_if
c_cond
(paren
id|sbi-&gt;s_inode_bitmap
(braket
id|block_group
)braket
)paren
(brace
r_if
c_cond
(paren
id|sbi-&gt;s_inode_bitmap_number
(braket
id|block_group
)braket
op_ne
id|block_group
)paren
id|ext3_panic
c_func
(paren
id|sb
comma
l_string|&quot;load_inode_bitmap&quot;
comma
l_string|&quot;block_group != inode_bitmap_number&quot;
)paren
suffix:semicolon
r_return
id|block_group
suffix:semicolon
)brace
id|retval
op_assign
id|read_inode_bitmap
c_func
(paren
id|sb
comma
id|block_group
comma
id|block_group
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_return
id|retval
suffix:semicolon
r_return
id|block_group
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
id|sbi-&gt;s_loaded_inode_bitmaps
op_logical_and
id|sbi-&gt;s_inode_bitmap_number
(braket
id|i
)braket
op_ne
id|block_group
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* do nothing */
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|sbi-&gt;s_loaded_inode_bitmaps
op_logical_and
id|sbi-&gt;s_inode_bitmap_number
(braket
id|i
)braket
op_eq
id|block_group
)paren
(brace
id|inode_bitmap_number
op_assign
id|sbi-&gt;s_inode_bitmap_number
(braket
id|i
)braket
suffix:semicolon
id|inode_bitmap
op_assign
id|sbi-&gt;s_inode_bitmap
(braket
id|i
)braket
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
id|i
suffix:semicolon
id|j
OG
l_int|0
suffix:semicolon
id|j
op_decrement
)paren
(brace
id|sbi-&gt;s_inode_bitmap_number
(braket
id|j
)braket
op_assign
id|sbi-&gt;s_inode_bitmap_number
(braket
id|j
op_minus
l_int|1
)braket
suffix:semicolon
id|sbi-&gt;s_inode_bitmap
(braket
id|j
)braket
op_assign
id|sbi-&gt;s_inode_bitmap
(braket
id|j
op_minus
l_int|1
)braket
suffix:semicolon
)brace
id|sbi-&gt;s_inode_bitmap_number
(braket
l_int|0
)braket
op_assign
id|inode_bitmap_number
suffix:semicolon
id|sbi-&gt;s_inode_bitmap
(braket
l_int|0
)braket
op_assign
id|inode_bitmap
suffix:semicolon
multiline_comment|/*&n;&t;&t; * There&squot;s still one special case here --- if inode_bitmap == 0&n;&t;&t; * then our last attempt to read the bitmap failed and we have&n;&t;&t; * just ended up caching that failure.  Try again to read it.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|inode_bitmap
)paren
id|retval
op_assign
id|read_inode_bitmap
(paren
id|sb
comma
id|block_group
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|sbi-&gt;s_loaded_inode_bitmaps
OL
id|EXT3_MAX_GROUP_LOADED
)paren
id|sbi-&gt;s_loaded_inode_bitmaps
op_increment
suffix:semicolon
r_else
id|brelse
c_func
(paren
id|sbi-&gt;s_inode_bitmap
(braket
id|EXT3_MAX_GROUP_LOADED
op_minus
l_int|1
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
id|sbi-&gt;s_loaded_inode_bitmaps
op_minus
l_int|1
suffix:semicolon
id|j
OG
l_int|0
suffix:semicolon
id|j
op_decrement
)paren
(brace
id|sbi-&gt;s_inode_bitmap_number
(braket
id|j
)braket
op_assign
id|sbi-&gt;s_inode_bitmap_number
(braket
id|j
op_minus
l_int|1
)braket
suffix:semicolon
id|sbi-&gt;s_inode_bitmap
(braket
id|j
)braket
op_assign
id|sbi-&gt;s_inode_bitmap
(braket
id|j
op_minus
l_int|1
)braket
suffix:semicolon
)brace
id|retval
op_assign
id|read_inode_bitmap
(paren
id|sb
comma
id|block_group
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * NOTE! When we get the inode, we&squot;re the only people&n; * that have access to it, and as such there are no&n; * race conditions we have to worry about. The inode&n; * is not on the hash-lists, and it cannot be reached&n; * through the filesystem because the directory entry&n; * has been deleted earlier.&n; *&n; * HOWEVER: we must make sure that we get no aliases,&n; * which means that we have to call &quot;clear_inode()&quot;&n; * _before_ we mark the inode not in use in the inode&n; * bitmaps. Otherwise a newly created file might use&n; * the same inode number (not actually the same pointer&n; * though), and then we&squot;d have two inodes sharing the&n; * same inode number and space on the harddisk.&n; */
DECL|function|ext3_free_inode
r_void
id|ext3_free_inode
(paren
id|handle_t
op_star
id|handle
comma
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
r_int
id|is_directory
suffix:semicolon
r_int
r_int
id|ino
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh2
suffix:semicolon
r_int
r_int
id|block_group
suffix:semicolon
r_int
r_int
id|bit
suffix:semicolon
r_int
id|bitmap_nr
suffix:semicolon
r_struct
id|ext3_group_desc
op_star
id|gdp
suffix:semicolon
r_struct
id|ext3_super_block
op_star
id|es
suffix:semicolon
r_int
id|fatal
op_assign
l_int|0
comma
id|err
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|inode-&gt;i_count
)paren
OG
l_int|1
)paren
(brace
id|printk
(paren
l_string|&quot;ext3_free_inode: inode has count=%d&bslash;n&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|inode-&gt;i_count
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode-&gt;i_nlink
)paren
(brace
id|printk
(paren
l_string|&quot;ext3_free_inode: inode has nlink=%d&bslash;n&quot;
comma
id|inode-&gt;i_nlink
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|sb
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ext3_free_inode: inode on nonexistent device&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|ext3_debug
(paren
l_string|&quot;freeing inode %lu&bslash;n&quot;
comma
id|ino
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Note: we must free any quota before locking the superblock,&n;&t; * as writing the quota to disk may need the lock as well.&n;&t; */
id|DQUOT_INIT
c_func
(paren
id|inode
)paren
suffix:semicolon
id|DQUOT_FREE_INODE
c_func
(paren
id|inode
)paren
suffix:semicolon
id|DQUOT_DROP
c_func
(paren
id|inode
)paren
suffix:semicolon
id|is_directory
op_assign
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
suffix:semicolon
multiline_comment|/* Do this BEFORE marking the inode not in use or returning an error */
id|clear_inode
(paren
id|inode
)paren
suffix:semicolon
id|lock_super
(paren
id|sb
)paren
suffix:semicolon
id|es
op_assign
id|sb-&gt;u.ext3_sb.s_es
suffix:semicolon
r_if
c_cond
(paren
id|ino
template_param
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_inodes_count
)paren
)paren
(brace
id|ext3_error
(paren
id|sb
comma
l_string|&quot;ext3_free_inode&quot;
comma
l_string|&quot;reserved or nonexistent inode %lu&quot;
comma
id|ino
)paren
suffix:semicolon
r_goto
id|error_return
suffix:semicolon
)brace
id|block_group
op_assign
(paren
id|ino
op_minus
l_int|1
)paren
op_div
id|EXT3_INODES_PER_GROUP
c_func
(paren
id|sb
)paren
suffix:semicolon
id|bit
op_assign
(paren
id|ino
op_minus
l_int|1
)paren
op_mod
id|EXT3_INODES_PER_GROUP
c_func
(paren
id|sb
)paren
suffix:semicolon
id|bitmap_nr
op_assign
id|load_inode_bitmap
(paren
id|sb
comma
id|block_group
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bitmap_nr
OL
l_int|0
)paren
r_goto
id|error_return
suffix:semicolon
id|bh
op_assign
id|sb-&gt;u.ext3_sb.s_inode_bitmap
(braket
id|bitmap_nr
)braket
suffix:semicolon
id|BUFFER_TRACE
c_func
(paren
id|bh
comma
l_string|&quot;get_write_access&quot;
)paren
suffix:semicolon
id|fatal
op_assign
id|ext3_journal_get_write_access
c_func
(paren
id|handle
comma
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fatal
)paren
r_goto
id|error_return
suffix:semicolon
multiline_comment|/* Ok, now we can actually update the inode bitmaps.. */
r_if
c_cond
(paren
op_logical_neg
id|ext3_clear_bit
(paren
id|bit
comma
id|bh-&gt;b_data
)paren
)paren
id|ext3_error
(paren
id|sb
comma
l_string|&quot;ext3_free_inode&quot;
comma
l_string|&quot;bit already cleared for inode %lu&quot;
comma
id|ino
)paren
suffix:semicolon
r_else
(brace
id|gdp
op_assign
id|ext3_get_group_desc
(paren
id|sb
comma
id|block_group
comma
op_amp
id|bh2
)paren
suffix:semicolon
id|BUFFER_TRACE
c_func
(paren
id|bh2
comma
l_string|&quot;get_write_access&quot;
)paren
suffix:semicolon
id|fatal
op_assign
id|ext3_journal_get_write_access
c_func
(paren
id|handle
comma
id|bh2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fatal
)paren
r_goto
id|error_return
suffix:semicolon
id|BUFFER_TRACE
c_func
(paren
id|sb-&gt;u.ext3_sb.s_sbh
comma
l_string|&quot;get write access&quot;
)paren
suffix:semicolon
id|fatal
op_assign
id|ext3_journal_get_write_access
c_func
(paren
id|handle
comma
id|sb-&gt;u.ext3_sb.s_sbh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fatal
)paren
r_goto
id|error_return
suffix:semicolon
r_if
c_cond
(paren
id|gdp
)paren
(brace
id|gdp-&gt;bg_free_inodes_count
op_assign
id|cpu_to_le16
c_func
(paren
id|le16_to_cpu
c_func
(paren
id|gdp-&gt;bg_free_inodes_count
)paren
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_directory
)paren
id|gdp-&gt;bg_used_dirs_count
op_assign
id|cpu_to_le16
c_func
(paren
id|le16_to_cpu
c_func
(paren
id|gdp-&gt;bg_used_dirs_count
)paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
id|BUFFER_TRACE
c_func
(paren
id|bh2
comma
l_string|&quot;call ext3_journal_dirty_metadata&quot;
)paren
suffix:semicolon
id|err
op_assign
id|ext3_journal_dirty_metadata
c_func
(paren
id|handle
comma
id|bh2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fatal
)paren
id|fatal
op_assign
id|err
suffix:semicolon
id|es-&gt;s_free_inodes_count
op_assign
id|cpu_to_le32
c_func
(paren
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_free_inodes_count
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|BUFFER_TRACE
c_func
(paren
id|sb-&gt;u.ext3_sb.s_sbh
comma
l_string|&quot;call ext3_journal_dirty_metadata&quot;
)paren
suffix:semicolon
id|err
op_assign
id|ext3_journal_dirty_metadata
c_func
(paren
id|handle
comma
id|sb-&gt;u.ext3_sb.s_sbh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fatal
)paren
id|fatal
op_assign
id|err
suffix:semicolon
)brace
id|BUFFER_TRACE
c_func
(paren
id|bh
comma
l_string|&quot;call ext3_journal_dirty_metadata&quot;
)paren
suffix:semicolon
id|err
op_assign
id|ext3_journal_dirty_metadata
c_func
(paren
id|handle
comma
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fatal
)paren
id|fatal
op_assign
id|err
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
id|error_return
suffix:colon
id|ext3_std_error
c_func
(paren
id|sb
comma
id|fatal
)paren
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * There are two policies for allocating an inode.  If the new inode is&n; * a directory, then a forward search is made for a block group with both&n; * free space and a low directory-to-inode ratio; if that fails, then of&n; * the groups with above-average free space, that group with the fewest&n; * directories already is chosen.&n; *&n; * For other inodes, search forward from the parent directory&squot;s block&n; * group to find a free inode.&n; */
DECL|function|ext3_new_inode
r_struct
id|inode
op_star
id|ext3_new_inode
(paren
id|handle_t
op_star
id|handle
comma
r_struct
id|inode
op_star
id|dir
comma
r_int
id|mode
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh2
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|avefreei
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|bitmap_nr
suffix:semicolon
r_struct
id|ext3_group_desc
op_star
id|gdp
suffix:semicolon
r_struct
id|ext3_group_desc
op_star
id|tmp
suffix:semicolon
r_struct
id|ext3_super_block
op_star
id|es
suffix:semicolon
r_struct
id|ext3_inode_info
op_star
id|ei
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Cannot create files in a deleted directory */
r_if
c_cond
(paren
op_logical_neg
id|dir
op_logical_or
op_logical_neg
id|dir-&gt;i_nlink
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EPERM
)paren
suffix:semicolon
id|sb
op_assign
id|dir-&gt;i_sb
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
id|ei
op_assign
id|EXT3_I
c_func
(paren
id|inode
)paren
suffix:semicolon
id|lock_super
(paren
id|sb
)paren
suffix:semicolon
id|es
op_assign
id|sb-&gt;u.ext3_sb.s_es
suffix:semicolon
id|repeat
suffix:colon
id|gdp
op_assign
l_int|NULL
suffix:semicolon
id|i
op_assign
l_int|0
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
(brace
id|avefreei
op_assign
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_free_inodes_count
)paren
op_div
id|sb-&gt;u.ext3_sb.s_groups_count
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gdp
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|sb-&gt;u.ext3_sb.s_groups_count
suffix:semicolon
id|j
op_increment
)paren
(brace
r_struct
id|buffer_head
op_star
id|temp_buffer
suffix:semicolon
id|tmp
op_assign
id|ext3_get_group_desc
(paren
id|sb
comma
id|j
comma
op_amp
id|temp_buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_logical_and
id|le16_to_cpu
c_func
(paren
id|tmp-&gt;bg_free_inodes_count
)paren
op_logical_and
id|le16_to_cpu
c_func
(paren
id|tmp-&gt;bg_free_inodes_count
)paren
op_ge
id|avefreei
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|gdp
op_logical_or
(paren
id|le16_to_cpu
c_func
(paren
id|tmp-&gt;bg_free_blocks_count
)paren
OG
id|le16_to_cpu
c_func
(paren
id|gdp-&gt;bg_free_blocks_count
)paren
)paren
)paren
(brace
id|i
op_assign
id|j
suffix:semicolon
id|gdp
op_assign
id|tmp
suffix:semicolon
id|bh2
op_assign
id|temp_buffer
suffix:semicolon
)brace
)brace
)brace
)brace
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Try to place the inode in its parent directory&n;&t;&t; */
id|i
op_assign
id|EXT3_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|i_block_group
suffix:semicolon
id|tmp
op_assign
id|ext3_get_group_desc
(paren
id|sb
comma
id|i
comma
op_amp
id|bh2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_logical_and
id|le16_to_cpu
c_func
(paren
id|tmp-&gt;bg_free_inodes_count
)paren
)paren
id|gdp
op_assign
id|tmp
suffix:semicolon
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * Use a quadratic hash to find a group with a&n;&t;&t;&t; * free inode&n;&t;&t;&t; */
r_for
c_loop
(paren
id|j
op_assign
l_int|1
suffix:semicolon
id|j
OL
id|sb-&gt;u.ext3_sb.s_groups_count
suffix:semicolon
id|j
op_lshift_assign
l_int|1
)paren
(brace
id|i
op_add_assign
id|j
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|sb-&gt;u.ext3_sb.s_groups_count
)paren
id|i
op_sub_assign
id|sb-&gt;u.ext3_sb.s_groups_count
suffix:semicolon
id|tmp
op_assign
id|ext3_get_group_desc
(paren
id|sb
comma
id|i
comma
op_amp
id|bh2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_logical_and
id|le16_to_cpu
c_func
(paren
id|tmp-&gt;bg_free_inodes_count
)paren
)paren
(brace
id|gdp
op_assign
id|tmp
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|gdp
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * That failed: try linear search for a free inode&n;&t;&t;&t; */
id|i
op_assign
id|EXT3_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|i_block_group
op_plus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|2
suffix:semicolon
id|j
OL
id|sb-&gt;u.ext3_sb.s_groups_count
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
op_increment
id|i
op_ge
id|sb-&gt;u.ext3_sb.s_groups_count
)paren
id|i
op_assign
l_int|0
suffix:semicolon
id|tmp
op_assign
id|ext3_get_group_desc
(paren
id|sb
comma
id|i
comma
op_amp
id|bh2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_logical_and
id|le16_to_cpu
c_func
(paren
id|tmp-&gt;bg_free_inodes_count
)paren
)paren
(brace
id|gdp
op_assign
id|tmp
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
)brace
id|err
op_assign
op_minus
id|ENOSPC
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gdp
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
id|bitmap_nr
op_assign
id|load_inode_bitmap
(paren
id|sb
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bitmap_nr
OL
l_int|0
)paren
r_goto
id|fail
suffix:semicolon
id|bh
op_assign
id|sb-&gt;u.ext3_sb.s_inode_bitmap
(braket
id|bitmap_nr
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|j
op_assign
id|ext3_find_first_zero_bit
(paren
(paren
r_int
r_int
op_star
)paren
id|bh-&gt;b_data
comma
id|EXT3_INODES_PER_GROUP
c_func
(paren
id|sb
)paren
)paren
)paren
OL
id|EXT3_INODES_PER_GROUP
c_func
(paren
id|sb
)paren
)paren
(brace
id|BUFFER_TRACE
c_func
(paren
id|bh
comma
l_string|&quot;get_write_access&quot;
)paren
suffix:semicolon
id|err
op_assign
id|ext3_journal_get_write_access
c_func
(paren
id|handle
comma
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|fail
suffix:semicolon
r_if
c_cond
(paren
id|ext3_set_bit
(paren
id|j
comma
id|bh-&gt;b_data
)paren
)paren
(brace
id|ext3_error
(paren
id|sb
comma
l_string|&quot;ext3_new_inode&quot;
comma
l_string|&quot;bit already set for inode %d&quot;
comma
id|j
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|BUFFER_TRACE
c_func
(paren
id|bh
comma
l_string|&quot;call ext3_journal_dirty_metadata&quot;
)paren
suffix:semicolon
id|err
op_assign
id|ext3_journal_dirty_metadata
c_func
(paren
id|handle
comma
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|fail
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|le16_to_cpu
c_func
(paren
id|gdp-&gt;bg_free_inodes_count
)paren
op_ne
l_int|0
)paren
(brace
id|ext3_error
(paren
id|sb
comma
l_string|&quot;ext3_new_inode&quot;
comma
l_string|&quot;Free inodes count corrupted in group %d&quot;
comma
id|i
)paren
suffix:semicolon
multiline_comment|/* Is it really ENOSPC? */
id|err
op_assign
op_minus
id|ENOSPC
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
r_goto
id|fail
suffix:semicolon
id|BUFFER_TRACE
c_func
(paren
id|bh2
comma
l_string|&quot;get_write_access&quot;
)paren
suffix:semicolon
id|err
op_assign
id|ext3_journal_get_write_access
c_func
(paren
id|handle
comma
id|bh2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|fail
suffix:semicolon
id|gdp-&gt;bg_free_inodes_count
op_assign
l_int|0
suffix:semicolon
id|BUFFER_TRACE
c_func
(paren
id|bh2
comma
l_string|&quot;call ext3_journal_dirty_metadata&quot;
)paren
suffix:semicolon
id|err
op_assign
id|ext3_journal_dirty_metadata
c_func
(paren
id|handle
comma
id|bh2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|fail
suffix:semicolon
)brace
r_goto
id|repeat
suffix:semicolon
)brace
id|j
op_add_assign
id|i
op_star
id|EXT3_INODES_PER_GROUP
c_func
(paren
id|sb
)paren
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|j
template_param
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_inodes_count
)paren
)paren
(brace
id|ext3_error
(paren
id|sb
comma
l_string|&quot;ext3_new_inode&quot;
comma
l_string|&quot;reserved inode or inode &gt; inodes count - &quot;
l_string|&quot;block_group = %d,inode=%d&quot;
comma
id|i
comma
id|j
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
id|BUFFER_TRACE
c_func
(paren
id|bh2
comma
l_string|&quot;get_write_access&quot;
)paren
suffix:semicolon
id|err
op_assign
id|ext3_journal_get_write_access
c_func
(paren
id|handle
comma
id|bh2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|fail
suffix:semicolon
id|gdp-&gt;bg_free_inodes_count
op_assign
id|cpu_to_le16
c_func
(paren
id|le16_to_cpu
c_func
(paren
id|gdp-&gt;bg_free_inodes_count
)paren
op_minus
l_int|1
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
id|gdp-&gt;bg_used_dirs_count
op_assign
id|cpu_to_le16
c_func
(paren
id|le16_to_cpu
c_func
(paren
id|gdp-&gt;bg_used_dirs_count
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|BUFFER_TRACE
c_func
(paren
id|bh2
comma
l_string|&quot;call ext3_journal_dirty_metadata&quot;
)paren
suffix:semicolon
id|err
op_assign
id|ext3_journal_dirty_metadata
c_func
(paren
id|handle
comma
id|bh2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|fail
suffix:semicolon
id|BUFFER_TRACE
c_func
(paren
id|sb-&gt;u.ext3_sb.s_sbh
comma
l_string|&quot;get_write_access&quot;
)paren
suffix:semicolon
id|err
op_assign
id|ext3_journal_get_write_access
c_func
(paren
id|handle
comma
id|sb-&gt;u.ext3_sb.s_sbh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|fail
suffix:semicolon
id|es-&gt;s_free_inodes_count
op_assign
id|cpu_to_le32
c_func
(paren
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_free_inodes_count
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|BUFFER_TRACE
c_func
(paren
id|sb-&gt;u.ext3_sb.s_sbh
comma
l_string|&quot;call ext3_journal_dirty_metadata&quot;
)paren
suffix:semicolon
id|err
op_assign
id|ext3_journal_dirty_metadata
c_func
(paren
id|handle
comma
id|sb-&gt;u.ext3_sb.s_sbh
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|fail
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|current-&gt;fsuid
suffix:semicolon
r_if
c_cond
(paren
id|test_opt
(paren
id|sb
comma
id|GRPID
)paren
)paren
id|inode-&gt;i_gid
op_assign
id|dir-&gt;i_gid
suffix:semicolon
r_else
r_if
c_cond
(paren
id|dir-&gt;i_mode
op_amp
id|S_ISGID
)paren
(brace
id|inode-&gt;i_gid
op_assign
id|dir-&gt;i_gid
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
id|inode-&gt;i_gid
op_assign
id|current-&gt;fsgid
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|mode
suffix:semicolon
id|inode-&gt;i_ino
op_assign
id|j
suffix:semicolon
multiline_comment|/* This is the optimal IO size (for stat), not the fs block size */
id|inode-&gt;i_blksize
op_assign
id|PAGE_SIZE
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|memset
c_func
(paren
id|ei-&gt;i_data
comma
l_int|0
comma
r_sizeof
(paren
id|ei-&gt;i_data
)paren
)paren
suffix:semicolon
id|ei-&gt;i_next_alloc_block
op_assign
l_int|0
suffix:semicolon
id|ei-&gt;i_next_alloc_goal
op_assign
l_int|0
suffix:semicolon
id|ei-&gt;i_dir_start_lookup
op_assign
l_int|0
suffix:semicolon
id|ei-&gt;i_disksize
op_assign
l_int|0
suffix:semicolon
id|ei-&gt;i_flags
op_assign
id|EXT3_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|i_flags
op_amp
op_complement
id|EXT3_INDEX_FL
suffix:semicolon
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|mode
)paren
)paren
id|ei-&gt;i_flags
op_and_assign
op_complement
(paren
id|EXT3_IMMUTABLE_FL
op_or
id|EXT3_APPEND_FL
)paren
suffix:semicolon
multiline_comment|/* dirsync only applies to directories */
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
id|ei-&gt;i_flags
op_and_assign
op_complement
id|EXT3_DIRSYNC_FL
suffix:semicolon
macro_line|#ifdef EXT3_FRAGMENTS
id|ei-&gt;i_faddr
op_assign
l_int|0
suffix:semicolon
id|ei-&gt;i_frag_no
op_assign
l_int|0
suffix:semicolon
id|ei-&gt;i_frag_size
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|ei-&gt;i_file_acl
op_assign
l_int|0
suffix:semicolon
id|ei-&gt;i_dir_acl
op_assign
l_int|0
suffix:semicolon
id|ei-&gt;i_dtime
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef EXT3_PREALLOCATE
id|ei-&gt;i_prealloc_block
op_assign
l_int|0
suffix:semicolon
id|ei-&gt;i_prealloc_count
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|ei-&gt;i_block_group
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
id|ei-&gt;i_flags
op_amp
id|EXT3_SYNC_FL
)paren
id|inode-&gt;i_flags
op_or_assign
id|S_SYNC
suffix:semicolon
r_if
c_cond
(paren
id|ei-&gt;i_flags
op_amp
id|EXT3_DIRSYNC_FL
)paren
id|inode-&gt;i_flags
op_or_assign
id|S_DIRSYNC
suffix:semicolon
r_if
c_cond
(paren
id|IS_DIRSYNC
c_func
(paren
id|inode
)paren
)paren
id|handle-&gt;h_sync
op_assign
l_int|1
suffix:semicolon
id|insert_inode_hash
c_func
(paren
id|inode
)paren
suffix:semicolon
id|inode-&gt;i_generation
op_assign
id|sb-&gt;u.ext3_sb.s_next_generation
op_increment
suffix:semicolon
id|ei-&gt;i_state
op_assign
id|EXT3_STATE_NEW
suffix:semicolon
id|err
op_assign
id|ext3_mark_inode_dirty
c_func
(paren
id|handle
comma
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|fail
suffix:semicolon
id|unlock_super
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|DQUOT_ALLOC_INODE
c_func
(paren
id|inode
)paren
)paren
(brace
id|DQUOT_DROP
c_func
(paren
id|inode
)paren
suffix:semicolon
id|inode-&gt;i_flags
op_or_assign
id|S_NOQUOTA
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|0
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
op_minus
id|EDQUOT
)paren
suffix:semicolon
)brace
id|ext3_debug
(paren
l_string|&quot;allocating inode %lu&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_return
id|inode
suffix:semicolon
id|fail
suffix:colon
id|ext3_std_error
c_func
(paren
id|sb
comma
id|err
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_super
c_func
(paren
id|sb
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
id|err
)paren
suffix:semicolon
)brace
multiline_comment|/* Verify that we are loading a valid orphan from disk */
DECL|function|ext3_orphan_get
r_struct
id|inode
op_star
id|ext3_orphan_get
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|ino_t
id|ino
)paren
(brace
id|ino_t
id|max_ino
op_assign
id|le32_to_cpu
c_func
(paren
id|EXT3_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_es-&gt;s_inodes_count
)paren
suffix:semicolon
r_int
r_int
id|block_group
suffix:semicolon
r_int
id|bit
suffix:semicolon
r_int
id|bitmap_nr
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Error cases - e2fsck has already cleaned up for us */
r_if
c_cond
(paren
id|ino
OG
id|max_ino
)paren
(brace
id|ext3_warning
c_func
(paren
id|sb
comma
id|__FUNCTION__
comma
l_string|&quot;bad orphan ino %ld!  e2fsck was run?&bslash;n&quot;
comma
id|ino
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|block_group
op_assign
(paren
id|ino
op_minus
l_int|1
)paren
op_div
id|EXT3_INODES_PER_GROUP
c_func
(paren
id|sb
)paren
suffix:semicolon
id|bit
op_assign
(paren
id|ino
op_minus
l_int|1
)paren
op_mod
id|EXT3_INODES_PER_GROUP
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bitmap_nr
op_assign
id|load_inode_bitmap
c_func
(paren
id|sb
comma
id|block_group
)paren
)paren
OL
l_int|0
op_logical_or
op_logical_neg
(paren
id|bh
op_assign
id|EXT3_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_inode_bitmap
(braket
id|bitmap_nr
)braket
)paren
)paren
(brace
id|ext3_warning
c_func
(paren
id|sb
comma
id|__FUNCTION__
comma
l_string|&quot;inode bitmap error for orphan %ld&bslash;n&quot;
comma
id|ino
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Having the inode bit set should be a 100% indicator that this&n;&t; * is a valid orphan (no e2fsck run on fs).  Orphans also include&n;&t; * inodes that were being truncated, so we can&squot;t check i_nlink==0.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|ext3_test_bit
c_func
(paren
id|bit
comma
id|bh-&gt;b_data
)paren
op_logical_or
op_logical_neg
(paren
id|inode
op_assign
id|iget
c_func
(paren
id|sb
comma
id|ino
)paren
)paren
op_logical_or
id|is_bad_inode
c_func
(paren
id|inode
)paren
op_logical_or
id|NEXT_ORPHAN
c_func
(paren
id|inode
)paren
OG
id|max_ino
)paren
(brace
id|ext3_warning
c_func
(paren
id|sb
comma
id|__FUNCTION__
comma
l_string|&quot;bad orphan inode %ld!  e2fsck was run?&bslash;n&quot;
comma
id|ino
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;ext3_test_bit(bit=%d, block=%ld) = %d&bslash;n&quot;
comma
id|bit
comma
id|bh-&gt;b_blocknr
comma
id|ext3_test_bit
c_func
(paren
id|bit
comma
id|bh-&gt;b_data
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;inode=%p&bslash;n&quot;
comma
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;is_bad_inode(inode)=%d&bslash;n&quot;
comma
id|is_bad_inode
c_func
(paren
id|inode
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;NEXT_ORPHAN(inode)=%d&bslash;n&quot;
comma
id|NEXT_ORPHAN
c_func
(paren
id|inode
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;max_ino=%ld&bslash;n&quot;
comma
id|max_ino
)paren
suffix:semicolon
)brace
multiline_comment|/* Avoid freeing blocks if we got a bad deleted inode */
r_if
c_cond
(paren
id|inode
op_logical_and
id|inode-&gt;i_nlink
op_eq
l_int|0
)paren
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|inode
suffix:semicolon
)brace
DECL|function|ext3_count_free_inodes
r_int
r_int
id|ext3_count_free_inodes
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
macro_line|#ifdef EXT3FS_DEBUG
r_struct
id|ext3_super_block
op_star
id|es
suffix:semicolon
r_int
r_int
id|desc_count
comma
id|bitmap_count
comma
id|x
suffix:semicolon
r_int
id|bitmap_nr
suffix:semicolon
r_struct
id|ext3_group_desc
op_star
id|gdp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|lock_super
(paren
id|sb
)paren
suffix:semicolon
id|es
op_assign
id|sb-&gt;u.ext3_sb.s_es
suffix:semicolon
id|desc_count
op_assign
l_int|0
suffix:semicolon
id|bitmap_count
op_assign
l_int|0
suffix:semicolon
id|gdp
op_assign
l_int|NULL
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
id|sb-&gt;u.ext3_sb.s_groups_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|gdp
op_assign
id|ext3_get_group_desc
(paren
id|sb
comma
id|i
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gdp
)paren
r_continue
suffix:semicolon
id|desc_count
op_add_assign
id|le16_to_cpu
c_func
(paren
id|gdp-&gt;bg_free_inodes_count
)paren
suffix:semicolon
id|bitmap_nr
op_assign
id|load_inode_bitmap
(paren
id|sb
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bitmap_nr
OL
l_int|0
)paren
r_continue
suffix:semicolon
id|x
op_assign
id|ext3_count_free
(paren
id|sb-&gt;u.ext3_sb.s_inode_bitmap
(braket
id|bitmap_nr
)braket
comma
id|EXT3_INODES_PER_GROUP
c_func
(paren
id|sb
)paren
op_div
l_int|8
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;group %d: stored = %d, counted = %lu&bslash;n&quot;
comma
id|i
comma
id|le16_to_cpu
c_func
(paren
id|gdp-&gt;bg_free_inodes_count
)paren
comma
id|x
)paren
suffix:semicolon
id|bitmap_count
op_add_assign
id|x
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;ext3_count_free_inodes: stored = %lu, computed = %lu, %lu&bslash;n&quot;
comma
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_free_inodes_count
)paren
comma
id|desc_count
comma
id|bitmap_count
)paren
suffix:semicolon
id|unlock_super
(paren
id|sb
)paren
suffix:semicolon
r_return
id|desc_count
suffix:semicolon
macro_line|#else
r_return
id|le32_to_cpu
c_func
(paren
id|sb-&gt;u.ext3_sb.s_es-&gt;s_free_inodes_count
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#ifdef CONFIG_EXT3_CHECK
multiline_comment|/* Called at mount-time, super-block is locked */
DECL|function|ext3_check_inodes_bitmap
r_void
id|ext3_check_inodes_bitmap
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|ext3_super_block
op_star
id|es
suffix:semicolon
r_int
r_int
id|desc_count
comma
id|bitmap_count
comma
id|x
suffix:semicolon
r_int
id|bitmap_nr
suffix:semicolon
r_struct
id|ext3_group_desc
op_star
id|gdp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|es
op_assign
id|sb-&gt;u.ext3_sb.s_es
suffix:semicolon
id|desc_count
op_assign
l_int|0
suffix:semicolon
id|bitmap_count
op_assign
l_int|0
suffix:semicolon
id|gdp
op_assign
l_int|NULL
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
id|sb-&gt;u.ext3_sb.s_groups_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|gdp
op_assign
id|ext3_get_group_desc
(paren
id|sb
comma
id|i
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gdp
)paren
r_continue
suffix:semicolon
id|desc_count
op_add_assign
id|le16_to_cpu
c_func
(paren
id|gdp-&gt;bg_free_inodes_count
)paren
suffix:semicolon
id|bitmap_nr
op_assign
id|load_inode_bitmap
(paren
id|sb
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bitmap_nr
OL
l_int|0
)paren
r_continue
suffix:semicolon
id|x
op_assign
id|ext3_count_free
(paren
id|sb-&gt;u.ext3_sb.s_inode_bitmap
(braket
id|bitmap_nr
)braket
comma
id|EXT3_INODES_PER_GROUP
c_func
(paren
id|sb
)paren
op_div
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|le16_to_cpu
c_func
(paren
id|gdp-&gt;bg_free_inodes_count
)paren
op_ne
id|x
)paren
id|ext3_error
(paren
id|sb
comma
l_string|&quot;ext3_check_inodes_bitmap&quot;
comma
l_string|&quot;Wrong free inodes count in group %d, &quot;
l_string|&quot;stored = %d, counted = %lu&quot;
comma
id|i
comma
id|le16_to_cpu
c_func
(paren
id|gdp-&gt;bg_free_inodes_count
)paren
comma
id|x
)paren
suffix:semicolon
id|bitmap_count
op_add_assign
id|x
suffix:semicolon
)brace
r_if
c_cond
(paren
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_free_inodes_count
)paren
op_ne
id|bitmap_count
)paren
id|ext3_error
(paren
id|sb
comma
l_string|&quot;ext3_check_inodes_bitmap&quot;
comma
l_string|&quot;Wrong free inodes count in super block, &quot;
l_string|&quot;stored = %lu, counted = %lu&quot;
comma
(paren
r_int
r_int
)paren
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_free_inodes_count
)paren
comma
id|bitmap_count
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
