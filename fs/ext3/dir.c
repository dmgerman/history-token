multiline_comment|/*&n; *  linux/fs/ext3/dir.c&n; *&n; * Copyright (C) 1992, 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  from&n; *&n; *  linux/fs/minix/dir.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  ext3 directory handling functions&n; *&n; *  Big-endian to little-endian byte-swapping/bitmaps by&n; *        David S. Miller (davem@caip.rutgers.edu), 1995&n; *&n; * Hash Tree Directory indexing (c) 2001  Daniel Phillips&n; *&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/jbd.h&gt;
macro_line|#include &lt;linux/ext3_fs.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/rbtree.h&gt;
DECL|variable|ext3_filetype_table
r_static
r_int
r_char
id|ext3_filetype_table
(braket
)braket
op_assign
(brace
id|DT_UNKNOWN
comma
id|DT_REG
comma
id|DT_DIR
comma
id|DT_CHR
comma
id|DT_BLK
comma
id|DT_FIFO
comma
id|DT_SOCK
comma
id|DT_LNK
)brace
suffix:semicolon
r_static
r_int
id|ext3_readdir
c_func
(paren
r_struct
id|file
op_star
comma
r_void
op_star
comma
id|filldir_t
)paren
suffix:semicolon
r_static
r_int
id|ext3_dx_readdir
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|dirent
comma
id|filldir_t
id|filldir
)paren
suffix:semicolon
r_static
r_int
id|ext3_release_dir
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
DECL|variable|ext3_dir_operations
r_struct
id|file_operations
id|ext3_dir_operations
op_assign
(brace
dot
id|llseek
op_assign
id|generic_file_llseek
comma
dot
id|read
op_assign
id|generic_read_dir
comma
dot
id|readdir
op_assign
id|ext3_readdir
comma
multiline_comment|/* we take BKL. needed?*/
dot
id|ioctl
op_assign
id|ext3_ioctl
comma
multiline_comment|/* BKL held */
dot
id|fsync
op_assign
id|ext3_sync_file
comma
multiline_comment|/* BKL held */
macro_line|#ifdef CONFIG_EXT3_INDEX
dot
id|release
op_assign
id|ext3_release_dir
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|function|get_dtype
r_static
r_int
r_char
id|get_dtype
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|filetype
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|EXT3_HAS_INCOMPAT_FEATURE
c_func
(paren
id|sb
comma
id|EXT3_FEATURE_INCOMPAT_FILETYPE
)paren
op_logical_or
(paren
id|filetype
op_ge
id|EXT3_FT_MAX
)paren
)paren
r_return
id|DT_UNKNOWN
suffix:semicolon
r_return
(paren
id|ext3_filetype_table
(braket
id|filetype
)braket
)paren
suffix:semicolon
)brace
DECL|function|ext3_check_dir_entry
r_int
id|ext3_check_dir_entry
(paren
r_const
r_char
op_star
id|function
comma
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|ext3_dir_entry_2
op_star
id|de
comma
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
r_int
id|offset
)paren
(brace
r_const
r_char
op_star
id|error_msg
op_assign
l_int|NULL
suffix:semicolon
r_const
r_int
id|rlen
op_assign
id|le16_to_cpu
c_func
(paren
id|de-&gt;rec_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rlen
OL
id|EXT3_DIR_REC_LEN
c_func
(paren
l_int|1
)paren
)paren
id|error_msg
op_assign
l_string|&quot;rec_len is smaller than minimal&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rlen
op_mod
l_int|4
op_ne
l_int|0
)paren
id|error_msg
op_assign
l_string|&quot;rec_len % 4 != 0&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rlen
OL
id|EXT3_DIR_REC_LEN
c_func
(paren
id|de-&gt;name_len
)paren
)paren
id|error_msg
op_assign
l_string|&quot;rec_len is too small for name_len&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
(paren
r_char
op_star
)paren
id|de
op_minus
id|bh-&gt;b_data
)paren
op_plus
id|rlen
OG
id|dir-&gt;i_sb-&gt;s_blocksize
)paren
id|error_msg
op_assign
l_string|&quot;directory entry across blocks&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|le32_to_cpu
c_func
(paren
id|de-&gt;inode
)paren
OG
id|le32_to_cpu
c_func
(paren
id|EXT3_SB
c_func
(paren
id|dir-&gt;i_sb
)paren
op_member_access_from_pointer
id|s_es-&gt;s_inodes_count
)paren
)paren
id|error_msg
op_assign
l_string|&quot;inode out of bounds&quot;
suffix:semicolon
r_if
c_cond
(paren
id|error_msg
op_ne
l_int|NULL
)paren
id|ext3_error
(paren
id|dir-&gt;i_sb
comma
id|function
comma
l_string|&quot;bad entry in directory #%lu: %s - &quot;
l_string|&quot;offset=%lu, inode=%lu, rec_len=%d, name_len=%d&quot;
comma
id|dir-&gt;i_ino
comma
id|error_msg
comma
id|offset
comma
(paren
r_int
r_int
)paren
id|le32_to_cpu
c_func
(paren
id|de-&gt;inode
)paren
comma
id|rlen
comma
id|de-&gt;name_len
)paren
suffix:semicolon
r_return
id|error_msg
op_eq
l_int|NULL
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|ext3_readdir
r_static
r_int
id|ext3_readdir
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|dirent
comma
id|filldir_t
id|filldir
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|offset
comma
id|blk
suffix:semicolon
r_int
id|i
comma
id|num
comma
id|stored
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
comma
op_star
id|tmp
comma
op_star
id|bha
(braket
l_int|16
)braket
suffix:semicolon
r_struct
id|ext3_dir_entry_2
op_star
id|de
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_int
id|err
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
macro_line|#ifdef CONFIG_EXT3_INDEX
r_if
c_cond
(paren
id|EXT3_HAS_COMPAT_FEATURE
c_func
(paren
id|inode-&gt;i_sb
comma
id|EXT3_FEATURE_COMPAT_DIR_INDEX
)paren
op_logical_and
(paren
(paren
id|EXT3_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_flags
op_amp
id|EXT3_INDEX_FL
)paren
op_logical_or
(paren
(paren
id|inode-&gt;i_size
op_rshift
id|sb-&gt;s_blocksize_bits
)paren
op_eq
l_int|1
)paren
)paren
)paren
(brace
id|err
op_assign
id|ext3_dx_readdir
c_func
(paren
id|filp
comma
id|dirent
comma
id|filldir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ne
id|ERR_BAD_DX_DIR
)paren
(brace
id|ret
op_assign
id|err
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * We don&squot;t set the inode dirty flag since it&squot;s not&n;&t;&t; * critical that it get flushed back to the disk.&n;&t;&t; */
id|EXT3_I
c_func
(paren
id|filp-&gt;f_dentry-&gt;d_inode
)paren
op_member_access_from_pointer
id|i_flags
op_and_assign
op_complement
id|EXT3_INDEX_FL
suffix:semicolon
)brace
macro_line|#endif
id|stored
op_assign
l_int|0
suffix:semicolon
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|offset
op_assign
id|filp-&gt;f_pos
op_amp
(paren
id|sb-&gt;s_blocksize
op_minus
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|error
op_logical_and
op_logical_neg
id|stored
op_logical_and
id|filp-&gt;f_pos
OL
id|inode-&gt;i_size
)paren
(brace
id|blk
op_assign
(paren
id|filp-&gt;f_pos
)paren
op_rshift
id|EXT3_BLOCK_SIZE_BITS
c_func
(paren
id|sb
)paren
suffix:semicolon
id|bh
op_assign
id|ext3_bread
c_func
(paren
l_int|NULL
comma
id|inode
comma
id|blk
comma
l_int|0
comma
op_amp
id|err
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
l_string|&quot;ext3_readdir&quot;
comma
l_string|&quot;directory #%lu contains a hole at offset %lu&quot;
comma
id|inode-&gt;i_ino
comma
(paren
r_int
r_int
)paren
id|filp-&gt;f_pos
)paren
suffix:semicolon
id|filp-&gt;f_pos
op_add_assign
id|sb-&gt;s_blocksize
op_minus
id|offset
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Do the readahead&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|offset
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|16
op_rshift
(paren
id|EXT3_BLOCK_SIZE_BITS
c_func
(paren
id|sb
)paren
op_minus
l_int|9
)paren
comma
id|num
op_assign
l_int|0
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|tmp
op_assign
id|ext3_getblk
(paren
l_int|NULL
comma
id|inode
comma
op_increment
id|blk
comma
l_int|0
comma
op_amp
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_logical_and
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|tmp
)paren
op_logical_and
op_logical_neg
id|buffer_locked
c_func
(paren
id|tmp
)paren
)paren
id|bha
(braket
id|num
op_increment
)braket
op_assign
id|tmp
suffix:semicolon
r_else
id|brelse
(paren
id|tmp
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|num
)paren
(brace
id|ll_rw_block
(paren
id|READA
comma
id|num
comma
id|bha
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
id|num
suffix:semicolon
id|i
op_increment
)paren
id|brelse
(paren
id|bha
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
id|revalidate
suffix:colon
multiline_comment|/* If the dir block has changed since the last call to&n;&t;&t; * readdir(2), then we might be pointing to an invalid&n;&t;&t; * dirent right now.  Scan from the start of the block&n;&t;&t; * to make sure. */
r_if
c_cond
(paren
id|filp-&gt;f_version
op_ne
id|inode-&gt;i_version
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|sb-&gt;s_blocksize
op_logical_and
id|i
OL
id|offset
suffix:semicolon
)paren
(brace
id|de
op_assign
(paren
r_struct
id|ext3_dir_entry_2
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
id|i
)paren
suffix:semicolon
multiline_comment|/* It&squot;s too expensive to do a full&n;&t;&t;&t;&t; * dirent test each time round this&n;&t;&t;&t;&t; * loop, but we do have to test at&n;&t;&t;&t;&t; * least that it is non-zero.  A&n;&t;&t;&t;&t; * failure will be detected in the&n;&t;&t;&t;&t; * dirent test below. */
r_if
c_cond
(paren
id|le16_to_cpu
c_func
(paren
id|de-&gt;rec_len
)paren
OL
id|EXT3_DIR_REC_LEN
c_func
(paren
l_int|1
)paren
)paren
r_break
suffix:semicolon
id|i
op_add_assign
id|le16_to_cpu
c_func
(paren
id|de-&gt;rec_len
)paren
suffix:semicolon
)brace
id|offset
op_assign
id|i
suffix:semicolon
id|filp-&gt;f_pos
op_assign
(paren
id|filp-&gt;f_pos
op_amp
op_complement
(paren
id|sb-&gt;s_blocksize
op_minus
l_int|1
)paren
)paren
op_or
id|offset
suffix:semicolon
id|filp-&gt;f_version
op_assign
id|inode-&gt;i_version
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|error
op_logical_and
id|filp-&gt;f_pos
OL
id|inode-&gt;i_size
op_logical_and
id|offset
OL
id|sb-&gt;s_blocksize
)paren
(brace
id|de
op_assign
(paren
r_struct
id|ext3_dir_entry_2
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ext3_check_dir_entry
(paren
l_string|&quot;ext3_readdir&quot;
comma
id|inode
comma
id|de
comma
id|bh
comma
id|offset
)paren
)paren
(brace
multiline_comment|/* On error, skip the f_pos to the&n;                                   next block. */
id|filp-&gt;f_pos
op_assign
(paren
id|filp-&gt;f_pos
op_or
(paren
id|sb-&gt;s_blocksize
op_minus
l_int|1
)paren
)paren
op_plus
l_int|1
suffix:semicolon
id|brelse
(paren
id|bh
)paren
suffix:semicolon
id|ret
op_assign
id|stored
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|offset
op_add_assign
id|le16_to_cpu
c_func
(paren
id|de-&gt;rec_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|le32_to_cpu
c_func
(paren
id|de-&gt;inode
)paren
)paren
(brace
multiline_comment|/* We might block in the next section&n;&t;&t;&t;&t; * if the data destination is&n;&t;&t;&t;&t; * currently swapped out.  So, use a&n;&t;&t;&t;&t; * version stamp to detect whether or&n;&t;&t;&t;&t; * not the directory has been modified&n;&t;&t;&t;&t; * during the copy operation.&n;&t;&t;&t;&t; */
r_int
r_int
id|version
op_assign
id|filp-&gt;f_version
suffix:semicolon
id|error
op_assign
id|filldir
c_func
(paren
id|dirent
comma
id|de-&gt;name
comma
id|de-&gt;name_len
comma
id|filp-&gt;f_pos
comma
id|le32_to_cpu
c_func
(paren
id|de-&gt;inode
)paren
comma
id|get_dtype
c_func
(paren
id|sb
comma
id|de-&gt;file_type
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|version
op_ne
id|filp-&gt;f_version
)paren
r_goto
id|revalidate
suffix:semicolon
id|stored
op_increment
suffix:semicolon
)brace
id|filp-&gt;f_pos
op_add_assign
id|le16_to_cpu
c_func
(paren
id|de-&gt;rec_len
)paren
suffix:semicolon
)brace
id|offset
op_assign
l_int|0
suffix:semicolon
id|brelse
(paren
id|bh
)paren
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_EXT3_INDEX
multiline_comment|/*&n; * These functions convert from the major/minor hash to an f_pos&n; * value.&n; * &n; * Currently we only use major hash numer.  This is unfortunate, but&n; * on 32-bit machines, the same VFS interface is used for lseek and&n; * llseek, so if we use the 64 bit offset, then the 32-bit versions of&n; * lseek/telldir/seekdir will blow out spectacularly, and from within&n; * the ext2 low-level routine, we don&squot;t know if we&squot;re being called by&n; * a 64-bit version of the system call or the 32-bit version of the&n; * system call.  Worse yet, NFSv2 only allows for a 32-bit readdir&n; * cookie.  Sigh.&n; */
DECL|macro|hash2pos
mdefine_line|#define hash2pos(major, minor)&t;(major &gt;&gt; 1)
DECL|macro|pos2maj_hash
mdefine_line|#define pos2maj_hash(pos)&t;((pos &lt;&lt; 1) &amp; 0xffffffff)
DECL|macro|pos2min_hash
mdefine_line|#define pos2min_hash(pos)&t;(0)
multiline_comment|/*&n; * This structure holds the nodes of the red-black tree used to store&n; * the directory entry in hash order.&n; */
DECL|struct|fname
r_struct
id|fname
(brace
DECL|member|hash
id|__u32
id|hash
suffix:semicolon
DECL|member|minor_hash
id|__u32
id|minor_hash
suffix:semicolon
DECL|member|rb_hash
r_struct
id|rb_node
id|rb_hash
suffix:semicolon
DECL|member|next
r_struct
id|fname
op_star
id|next
suffix:semicolon
DECL|member|inode
id|__u32
id|inode
suffix:semicolon
DECL|member|name_len
id|__u8
id|name_len
suffix:semicolon
DECL|member|file_type
id|__u8
id|file_type
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This functoin implements a non-recursive way of freeing all of the&n; * nodes in the red-black tree.&n; */
DECL|function|free_rb_tree_fname
r_static
r_void
id|free_rb_tree_fname
c_func
(paren
r_struct
id|rb_root
op_star
id|root
)paren
(brace
r_struct
id|rb_node
op_star
id|n
op_assign
id|root-&gt;rb_node
suffix:semicolon
r_struct
id|rb_node
op_star
id|parent
suffix:semicolon
r_struct
id|fname
op_star
id|fname
suffix:semicolon
r_while
c_loop
(paren
id|n
)paren
(brace
multiline_comment|/* Do the node&squot;s children first */
r_if
c_cond
(paren
(paren
id|n
)paren
op_member_access_from_pointer
id|rb_left
)paren
(brace
id|n
op_assign
id|n-&gt;rb_left
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|n-&gt;rb_right
)paren
(brace
id|n
op_assign
id|n-&gt;rb_right
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * The node has no children; free it, and then zero&n;&t;&t; * out parent&squot;s link to it.  Finally go to the&n;&t;&t; * beginning of the loop and try to free the parent&n;&t;&t; * node.&n;&t;&t; */
id|parent
op_assign
id|n-&gt;rb_parent
suffix:semicolon
id|fname
op_assign
id|rb_entry
c_func
(paren
id|n
comma
r_struct
id|fname
comma
id|rb_hash
)paren
suffix:semicolon
r_while
c_loop
(paren
id|fname
)paren
(brace
r_struct
id|fname
op_star
id|old
op_assign
id|fname
suffix:semicolon
id|fname
op_assign
id|fname-&gt;next
suffix:semicolon
id|kfree
(paren
id|old
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|parent
)paren
id|root-&gt;rb_node
op_assign
l_int|NULL
suffix:semicolon
r_else
r_if
c_cond
(paren
id|parent-&gt;rb_left
op_eq
id|n
)paren
id|parent-&gt;rb_left
op_assign
l_int|NULL
suffix:semicolon
r_else
r_if
c_cond
(paren
id|parent-&gt;rb_right
op_eq
id|n
)paren
id|parent-&gt;rb_right
op_assign
l_int|NULL
suffix:semicolon
id|n
op_assign
id|parent
suffix:semicolon
)brace
id|root-&gt;rb_node
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|create_dir_info
r_struct
id|dir_private_info
op_star
id|create_dir_info
c_func
(paren
id|loff_t
id|pos
)paren
(brace
r_struct
id|dir_private_info
op_star
id|p
suffix:semicolon
id|p
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|dir_private_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
l_int|NULL
suffix:semicolon
id|p-&gt;root.rb_node
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;curr_node
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;extra_fname
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;last_pos
op_assign
l_int|0
suffix:semicolon
id|p-&gt;curr_hash
op_assign
id|pos2maj_hash
c_func
(paren
id|pos
)paren
suffix:semicolon
id|p-&gt;curr_minor_hash
op_assign
id|pos2min_hash
c_func
(paren
id|pos
)paren
suffix:semicolon
id|p-&gt;next_hash
op_assign
l_int|0
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
DECL|function|ext3_htree_free_dir_info
r_void
id|ext3_htree_free_dir_info
c_func
(paren
r_struct
id|dir_private_info
op_star
id|p
)paren
(brace
id|free_rb_tree_fname
c_func
(paren
op_amp
id|p-&gt;root
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Given a directory entry, enter it into the fname rb tree.&n; */
DECL|function|ext3_htree_store_dirent
r_int
id|ext3_htree_store_dirent
c_func
(paren
r_struct
id|file
op_star
id|dir_file
comma
id|__u32
id|hash
comma
id|__u32
id|minor_hash
comma
r_struct
id|ext3_dir_entry_2
op_star
id|dirent
)paren
(brace
r_struct
id|rb_node
op_star
op_star
id|p
comma
op_star
id|parent
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|fname
op_star
id|fname
comma
op_star
id|new_fn
suffix:semicolon
r_struct
id|dir_private_info
op_star
id|info
suffix:semicolon
r_int
id|len
suffix:semicolon
id|info
op_assign
(paren
r_struct
id|dir_private_info
op_star
)paren
id|dir_file-&gt;private_data
suffix:semicolon
id|p
op_assign
op_amp
id|info-&gt;root.rb_node
suffix:semicolon
multiline_comment|/* Create and allocate the fname structure */
id|len
op_assign
r_sizeof
(paren
r_struct
id|fname
)paren
op_plus
id|dirent-&gt;name_len
op_plus
l_int|1
suffix:semicolon
id|new_fn
op_assign
id|kmalloc
c_func
(paren
id|len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_fn
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|new_fn
comma
l_int|0
comma
id|len
)paren
suffix:semicolon
id|new_fn-&gt;hash
op_assign
id|hash
suffix:semicolon
id|new_fn-&gt;minor_hash
op_assign
id|minor_hash
suffix:semicolon
id|new_fn-&gt;inode
op_assign
id|le32_to_cpu
c_func
(paren
id|dirent-&gt;inode
)paren
suffix:semicolon
id|new_fn-&gt;name_len
op_assign
id|dirent-&gt;name_len
suffix:semicolon
id|new_fn-&gt;file_type
op_assign
id|dirent-&gt;file_type
suffix:semicolon
id|memcpy
c_func
(paren
id|new_fn-&gt;name
comma
id|dirent-&gt;name
comma
id|dirent-&gt;name_len
)paren
suffix:semicolon
id|new_fn-&gt;name
(braket
id|dirent-&gt;name_len
)braket
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|p
)paren
(brace
id|parent
op_assign
op_star
id|p
suffix:semicolon
id|fname
op_assign
id|rb_entry
c_func
(paren
id|parent
comma
r_struct
id|fname
comma
id|rb_hash
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If the hash and minor hash match up, then we put&n;&t;&t; * them on a linked list.  This rarely happens...&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|new_fn-&gt;hash
op_eq
id|fname-&gt;hash
)paren
op_logical_and
(paren
id|new_fn-&gt;minor_hash
op_eq
id|fname-&gt;minor_hash
)paren
)paren
(brace
id|new_fn-&gt;next
op_assign
id|fname-&gt;next
suffix:semicolon
id|fname-&gt;next
op_assign
id|new_fn
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|new_fn-&gt;hash
OL
id|fname-&gt;hash
)paren
id|p
op_assign
op_amp
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|rb_left
suffix:semicolon
r_else
r_if
c_cond
(paren
id|new_fn-&gt;hash
OG
id|fname-&gt;hash
)paren
id|p
op_assign
op_amp
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|rb_right
suffix:semicolon
r_else
r_if
c_cond
(paren
id|new_fn-&gt;minor_hash
OL
id|fname-&gt;minor_hash
)paren
id|p
op_assign
op_amp
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|rb_left
suffix:semicolon
r_else
multiline_comment|/* if (new_fn-&gt;minor_hash &gt; fname-&gt;minor_hash) */
id|p
op_assign
op_amp
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|rb_right
suffix:semicolon
)brace
id|rb_link_node
c_func
(paren
op_amp
id|new_fn-&gt;rb_hash
comma
id|parent
comma
id|p
)paren
suffix:semicolon
id|rb_insert_color
c_func
(paren
op_amp
id|new_fn-&gt;rb_hash
comma
op_amp
id|info-&gt;root
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This is a helper function for ext3_dx_readdir.  It calls filldir&n; * for all entres on the fname linked list.  (Normally there is only&n; * one entry on the linked list, unless there are 62 bit hash collisions.)&n; */
DECL|function|call_filldir
r_static
r_int
id|call_filldir
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|dirent
comma
id|filldir_t
id|filldir
comma
r_struct
id|fname
op_star
id|fname
)paren
(brace
r_struct
id|dir_private_info
op_star
id|info
op_assign
id|filp-&gt;private_data
suffix:semicolon
id|loff_t
id|curr_pos
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_int
id|error
suffix:semicolon
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fname
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;call_filldir: called with null fname?!?&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|curr_pos
op_assign
id|hash2pos
c_func
(paren
id|fname-&gt;hash
comma
id|fname-&gt;minor_hash
)paren
suffix:semicolon
r_while
c_loop
(paren
id|fname
)paren
(brace
id|error
op_assign
id|filldir
c_func
(paren
id|dirent
comma
id|fname-&gt;name
comma
id|fname-&gt;name_len
comma
id|curr_pos
comma
id|fname-&gt;inode
comma
id|get_dtype
c_func
(paren
id|sb
comma
id|fname-&gt;file_type
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|filp-&gt;f_pos
op_assign
id|curr_pos
suffix:semicolon
id|info-&gt;extra_fname
op_assign
id|fname
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|fname
op_assign
id|fname-&gt;next
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ext3_dx_readdir
r_static
r_int
id|ext3_dx_readdir
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|dirent
comma
id|filldir_t
id|filldir
)paren
(brace
r_struct
id|dir_private_info
op_star
id|info
op_assign
id|filp-&gt;private_data
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|fname
op_star
id|fname
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
)paren
(brace
id|info
op_assign
id|create_dir_info
c_func
(paren
id|filp-&gt;f_pos
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|filp-&gt;private_data
op_assign
id|info
suffix:semicolon
)brace
r_if
c_cond
(paren
id|filp-&gt;f_pos
op_eq
id|EXT3_HTREE_EOF
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* EOF */
multiline_comment|/* Some one has messed with f_pos; reset the world */
r_if
c_cond
(paren
id|info-&gt;last_pos
op_ne
id|filp-&gt;f_pos
)paren
(brace
id|free_rb_tree_fname
c_func
(paren
op_amp
id|info-&gt;root
)paren
suffix:semicolon
id|info-&gt;curr_node
op_assign
l_int|NULL
suffix:semicolon
id|info-&gt;extra_fname
op_assign
l_int|NULL
suffix:semicolon
id|info-&gt;curr_hash
op_assign
id|pos2maj_hash
c_func
(paren
id|filp-&gt;f_pos
)paren
suffix:semicolon
id|info-&gt;curr_minor_hash
op_assign
id|pos2min_hash
c_func
(paren
id|filp-&gt;f_pos
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If there are any leftover names on the hash collision&n;&t; * chain, return them first.&n;&t; */
r_if
c_cond
(paren
id|info-&gt;extra_fname
)paren
(brace
r_if
c_cond
(paren
id|call_filldir
c_func
(paren
id|filp
comma
id|dirent
comma
id|filldir
comma
id|info-&gt;extra_fname
)paren
)paren
(brace
r_goto
id|finished
suffix:semicolon
)brace
r_else
r_goto
id|next_entry
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;curr_node
)paren
id|info-&gt;curr_node
op_assign
id|rb_first
c_func
(paren
op_amp
id|info-&gt;root
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
multiline_comment|/*&n;&t;&t; * Fill the rbtree if we have no more entries,&n;&t;&t; * or the inode has changed since we last read in the&n;&t;&t; * cached entries. &n;&t;&t; */
r_if
c_cond
(paren
(paren
op_logical_neg
id|info-&gt;curr_node
)paren
op_logical_or
(paren
id|filp-&gt;f_version
op_ne
id|inode-&gt;i_version
)paren
)paren
(brace
id|info-&gt;curr_node
op_assign
l_int|NULL
suffix:semicolon
id|free_rb_tree_fname
c_func
(paren
op_amp
id|info-&gt;root
)paren
suffix:semicolon
id|filp-&gt;f_version
op_assign
id|inode-&gt;i_version
suffix:semicolon
id|ret
op_assign
id|ext3_htree_fill_tree
c_func
(paren
id|filp
comma
id|info-&gt;curr_hash
comma
id|info-&gt;curr_minor_hash
comma
op_amp
id|info-&gt;next_hash
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
(brace
id|filp-&gt;f_pos
op_assign
id|EXT3_HTREE_EOF
suffix:semicolon
r_break
suffix:semicolon
)brace
id|info-&gt;curr_node
op_assign
id|rb_first
c_func
(paren
op_amp
id|info-&gt;root
)paren
suffix:semicolon
)brace
id|fname
op_assign
id|rb_entry
c_func
(paren
id|info-&gt;curr_node
comma
r_struct
id|fname
comma
id|rb_hash
)paren
suffix:semicolon
id|info-&gt;curr_hash
op_assign
id|fname-&gt;hash
suffix:semicolon
id|info-&gt;curr_minor_hash
op_assign
id|fname-&gt;minor_hash
suffix:semicolon
r_if
c_cond
(paren
id|call_filldir
c_func
(paren
id|filp
comma
id|dirent
comma
id|filldir
comma
id|fname
)paren
)paren
r_break
suffix:semicolon
id|next_entry
suffix:colon
id|info-&gt;curr_node
op_assign
id|rb_next
c_func
(paren
id|info-&gt;curr_node
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;curr_node
)paren
(brace
r_if
c_cond
(paren
id|info-&gt;next_hash
op_eq
op_complement
l_int|0
)paren
(brace
id|filp-&gt;f_pos
op_assign
id|EXT3_HTREE_EOF
suffix:semicolon
r_break
suffix:semicolon
)brace
id|info-&gt;curr_hash
op_assign
id|info-&gt;next_hash
suffix:semicolon
id|info-&gt;curr_minor_hash
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|finished
suffix:colon
id|info-&gt;last_pos
op_assign
id|filp-&gt;f_pos
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ext3_release_dir
r_static
r_int
id|ext3_release_dir
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_if
c_cond
(paren
id|filp-&gt;private_data
)paren
id|ext3_htree_free_dir_info
c_func
(paren
id|filp-&gt;private_data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
eof
