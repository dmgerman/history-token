multiline_comment|/*&n; * linux/fs/hfs/file.c&n; *&n; * Copyright (C) 1995, 1996  Paul H. Hargrove&n; * This file may be distributed under the terms of the GNU General Public License.&n; *&n; * This file contains the file-related functions which are independent of&n; * which scheme is being used to represent forks.&n; *&n; * Based on the minix file system code, (C) 1991, 1992 by Linus Torvalds&n; *&n; * &quot;XXX&quot; in a comment is a note to myself to consider changing something.&n; *&n; * In function preconditions the term &quot;valid&quot; applied to a pointer to&n; * a structure means that the pointer is non-NULL and the structure it&n; * points to has all fields initialized to consistent values.&n; */
macro_line|#include &quot;hfs.h&quot;
macro_line|#include &lt;linux/hfs_fs_sb.h&gt;
macro_line|#include &lt;linux/hfs_fs_i.h&gt;
macro_line|#include &lt;linux/hfs_fs.h&gt;
multiline_comment|/*================ Forward declarations ================*/
r_static
id|hfs_rwret_t
id|hfs_file_read
c_func
(paren
r_struct
id|file
op_star
comma
r_char
op_star
comma
id|hfs_rwarg_t
comma
id|loff_t
op_star
)paren
suffix:semicolon
r_static
id|hfs_rwret_t
id|hfs_file_write
c_func
(paren
r_struct
id|file
op_star
comma
r_const
r_char
op_star
comma
id|hfs_rwarg_t
comma
id|loff_t
op_star
)paren
suffix:semicolon
r_static
r_void
id|hfs_file_truncate
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
multiline_comment|/*================ Global variables ================*/
DECL|variable|hfs_file_operations
r_struct
id|file_operations
id|hfs_file_operations
op_assign
(brace
id|llseek
suffix:colon
id|generic_file_llseek
comma
id|read
suffix:colon
id|hfs_file_read
comma
id|write
suffix:colon
id|hfs_file_write
comma
id|mmap
suffix:colon
id|generic_file_mmap
comma
id|fsync
suffix:colon
id|file_fsync
comma
)brace
suffix:semicolon
DECL|variable|hfs_file_inode_operations
r_struct
id|inode_operations
id|hfs_file_inode_operations
op_assign
(brace
id|truncate
suffix:colon
id|hfs_file_truncate
comma
id|setattr
suffix:colon
id|hfs_notify_change
comma
)brace
suffix:semicolon
multiline_comment|/*================ Variable-like macros ================*/
multiline_comment|/* maximum number of blocks to try to read in at once */
DECL|macro|NBUF
mdefine_line|#define NBUF 32
multiline_comment|/*================ File-local functions ================*/
multiline_comment|/*&n; * hfs_getblk()&n; *&n; * Given an hfs_fork and a block number return the buffer_head for&n; * that block from the fork.  If &squot;create&squot; is non-zero then allocate&n; * the necessary block(s) to the fork.&n; */
DECL|function|hfs_getblk
r_struct
id|buffer_head
op_star
id|hfs_getblk
c_func
(paren
r_struct
id|hfs_fork
op_star
id|fork
comma
r_int
id|block
comma
r_int
id|create
)paren
(brace
r_int
id|tmp
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
op_assign
id|fork-&gt;entry-&gt;mdb-&gt;sys_mdb
suffix:semicolon
id|tmp
op_assign
id|hfs_extent_map
c_func
(paren
id|fork
comma
id|block
comma
id|create
)paren
suffix:semicolon
r_if
c_cond
(paren
id|create
)paren
(brace
multiline_comment|/* If writing the block, then we have exclusive access&n;&t;&t;   to the file until we return, so it can&squot;t have moved.&n;&t;&t;*/
r_if
c_cond
(paren
id|tmp
)paren
(brace
id|hfs_cat_mark_dirty
c_func
(paren
id|fork-&gt;entry
)paren
suffix:semicolon
r_return
id|sb_getblk
c_func
(paren
id|sb
comma
id|tmp
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* If reading the block, then retry since the&n;&t;&t;   location on disk could have changed while&n;&t;&t;   we waited on the I/O in getblk to complete.&n;&t;&t;*/
r_do
(brace
r_struct
id|buffer_head
op_star
id|bh
op_assign
id|sb_getblk
c_func
(paren
id|sb
comma
id|tmp
)paren
suffix:semicolon
r_int
id|tmp2
op_assign
id|hfs_extent_map
c_func
(paren
id|fork
comma
id|block
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp2
op_eq
id|tmp
)paren
(brace
r_return
id|bh
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* The block moved or no longer exists. */
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|tmp
op_assign
id|tmp2
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|tmp
op_ne
l_int|0
)paren
suffix:semicolon
multiline_comment|/* The block no longer exists. */
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * hfs_get_block&n; *&n; * This is the hfs_get_block() field in the inode_operations structure for&n; * &quot;regular&quot; (non-header) files.  The purpose is to translate an inode&n; * and a block number within the corresponding file into a physical&n; * block number.  This function just calls hfs_extent_map() to do the&n; * real work and then stuffs the appropriate info into the buffer_head.&n; */
DECL|function|hfs_get_block
r_int
id|hfs_get_block
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
id|bh_result
comma
r_int
id|create
)paren
(brace
r_int
r_int
id|phys
suffix:semicolon
id|phys
op_assign
id|hfs_extent_map
c_func
(paren
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|fork
comma
id|iblock
comma
id|create
)paren
suffix:semicolon
r_if
c_cond
(paren
id|phys
)paren
(brace
id|bh_result-&gt;b_dev
op_assign
id|inode-&gt;i_dev
suffix:semicolon
id|bh_result-&gt;b_blocknr
op_assign
id|phys
suffix:semicolon
id|bh_result-&gt;b_state
op_or_assign
(paren
l_int|1UL
op_lshift
id|BH_Mapped
)paren
suffix:semicolon
r_if
c_cond
(paren
id|create
)paren
id|bh_result-&gt;b_state
op_or_assign
(paren
l_int|1UL
op_lshift
id|BH_New
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|create
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* we tried to add stuff, but we couldn&squot;t. send back an out-of-space&n;&t; * error. */
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_file_read()&n; *&n; * This is the read field in the inode_operations structure for&n; * &quot;regular&quot; (non-header) files.  The purpose is to transfer up to&n; * &squot;count&squot; bytes from the file corresponding to &squot;inode&squot;, beginning at&n; * &squot;filp-&gt;offset&squot; bytes into the file.&t;The data is transferred to&n; * user-space at the address &squot;buf&squot;.  Returns the number of bytes&n; * successfully transferred.  This function checks the arguments, does&n; * some setup and then calls hfs_do_read() to do the actual transfer.  */
DECL|function|hfs_file_read
r_static
id|hfs_rwret_t
id|hfs_file_read
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_char
op_star
id|buf
comma
id|hfs_rwarg_t
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|hfs_s32
id|read
comma
id|left
comma
id|pos
comma
id|size
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_file_read: mode = %07o&bslash;n&quot;
comma
id|inode-&gt;i_mode
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|pos
op_assign
op_star
id|ppos
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_ge
id|HFS_FORK_MAX
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|size
op_assign
id|inode-&gt;i_size
suffix:semicolon
r_if
c_cond
(paren
id|pos
OG
id|size
)paren
(brace
id|left
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|left
op_assign
id|size
op_minus
id|pos
suffix:semicolon
)brace
r_if
c_cond
(paren
id|left
OG
id|count
)paren
(brace
id|left
op_assign
id|count
suffix:semicolon
)brace
r_if
c_cond
(paren
id|left
op_le
l_int|0
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|read
op_assign
id|hfs_do_read
c_func
(paren
id|inode
comma
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|fork
comma
id|pos
comma
id|buf
comma
id|left
comma
id|filp-&gt;f_reada
op_ne
l_int|0
)paren
)paren
OG
l_int|0
)paren
(brace
op_star
id|ppos
op_add_assign
id|read
suffix:semicolon
id|filp-&gt;f_reada
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|read
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_file_write()&n; *&n; * This is the write() entry in the file_operations structure for&n; * &quot;regular&quot; files.  The purpose is to transfer up to &squot;count&squot; bytes&n; * to the file corresponding to &squot;inode&squot; beginning at offset&n; * &squot;file-&gt;f_pos&squot; from user-space at the address &squot;buf&squot;.  The return&n; * value is the number of bytes actually transferred.&n; */
DECL|function|hfs_file_write
r_static
id|hfs_rwret_t
id|hfs_file_write
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_const
r_char
op_star
id|buf
comma
id|hfs_rwarg_t
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|hfs_fork
op_star
id|fork
op_assign
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|fork
suffix:semicolon
id|hfs_s32
id|written
comma
id|pos
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_file_write: mode = %07o&bslash;n&quot;
comma
id|inode-&gt;i_mode
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|pos
op_assign
(paren
id|filp-&gt;f_flags
op_amp
id|O_APPEND
)paren
ques
c_cond
id|inode-&gt;i_size
suffix:colon
op_star
id|ppos
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_ge
id|HFS_FORK_MAX
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
OG
id|HFS_FORK_MAX
)paren
(brace
id|count
op_assign
id|HFS_FORK_MAX
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|written
op_assign
id|hfs_do_write
c_func
(paren
id|inode
comma
id|fork
comma
id|pos
comma
id|buf
comma
id|count
)paren
)paren
OG
l_int|0
)paren
id|pos
op_add_assign
id|written
suffix:semicolon
op_star
id|ppos
op_assign
id|pos
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ppos
OG
id|inode-&gt;i_size
)paren
(brace
id|inode-&gt;i_size
op_assign
op_star
id|ppos
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_return
id|written
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_file_truncate()&n; *&n; * This is the truncate() entry in the file_operations structure for&n; * &quot;regular&quot; files.  The purpose is to change the length of the file&n; * corresponding to the given inode.  Changes can either lengthen or&n; * shorten the file.&n; */
DECL|function|hfs_file_truncate
r_static
r_void
id|hfs_file_truncate
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|hfs_fork
op_star
id|fork
op_assign
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|fork
suffix:semicolon
id|fork-&gt;lsize
op_assign
id|inode-&gt;i_size
suffix:semicolon
id|hfs_extent_adj
c_func
(paren
id|fork
)paren
suffix:semicolon
id|hfs_cat_mark_dirty
c_func
(paren
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|entry
)paren
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|fork-&gt;lsize
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
id|fork-&gt;psize
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * xlate_to_user()&n; *&n; * Like copy_to_user() while translating CR-&gt;NL.&n; */
DECL|function|xlate_to_user
r_static
r_inline
r_void
id|xlate_to_user
c_func
(paren
r_char
op_star
id|buf
comma
r_const
r_char
op_star
id|data
comma
r_int
id|count
)paren
(brace
r_char
id|ch
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
id|ch
op_assign
op_star
(paren
id|data
op_increment
)paren
suffix:semicolon
id|put_user
c_func
(paren
(paren
id|ch
op_eq
l_char|&squot;&bslash;r&squot;
)paren
ques
c_cond
l_char|&squot;&bslash;n&squot;
suffix:colon
id|ch
comma
id|buf
op_increment
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * xlate_from_user()&n; *&n; * Like copy_from_user() while translating NL-&gt;CR;&n; */
DECL|function|xlate_from_user
r_static
r_inline
r_int
id|xlate_from_user
c_func
(paren
r_char
op_star
id|data
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
id|i
suffix:semicolon
id|i
op_assign
id|copy_from_user
c_func
(paren
id|data
comma
id|buf
comma
id|count
)paren
suffix:semicolon
id|count
op_sub_assign
id|i
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
r_if
c_cond
(paren
op_star
id|data
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
op_star
id|data
op_assign
l_char|&squot;&bslash;r&squot;
suffix:semicolon
)brace
op_increment
id|data
suffix:semicolon
)brace
r_return
id|i
suffix:semicolon
)brace
multiline_comment|/*================ Global functions ================*/
multiline_comment|/*&n; * hfs_do_read()&n; *&n; * This function transfers actual data from disk to user-space memory,&n; * returning the number of bytes successfully transferred.  &squot;fork&squot; tells&n; * which file on the disk to read from.  &squot;pos&squot; gives the offset into&n; * the Linux file at which to begin the transfer.  Note that this will&n; * differ from &squot;filp-&gt;offset&squot; in the case of an AppleDouble header file&n; * due to the block of metadata at the beginning of the file, which has&n; * no corresponding place in the HFS file.  &squot;count&squot; tells how many&n; * bytes to transfer.  &squot;buf&squot; gives an address in user-space to transfer&n; * the data to.&n; * &n; * This is based on Linus&squot;s minix_file_read().&n; * It has been changed to take into account that HFS files have no holes.&n; */
DECL|function|hfs_do_read
id|hfs_s32
id|hfs_do_read
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|hfs_fork
op_star
id|fork
comma
id|hfs_u32
id|pos
comma
r_char
op_star
id|buf
comma
id|hfs_u32
id|count
comma
r_int
id|reada
)paren
(brace
id|kdev_t
id|dev
op_assign
id|inode-&gt;i_dev
suffix:semicolon
id|hfs_s32
id|size
comma
id|chars
comma
id|offset
comma
id|block
comma
id|blocks
comma
id|read
op_assign
l_int|0
suffix:semicolon
r_int
id|bhrequest
comma
id|uptodate
suffix:semicolon
r_int
id|convert
op_assign
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|convert
suffix:semicolon
r_struct
id|buffer_head
op_star
op_star
id|bhb
comma
op_star
op_star
id|bhe
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bhreq
(braket
id|NBUF
)braket
suffix:semicolon
r_struct
id|buffer_head
op_star
id|buflist
(braket
id|NBUF
)braket
suffix:semicolon
multiline_comment|/* split &squot;pos&squot; in to block and (byte) offset components */
id|block
op_assign
id|pos
op_rshift
id|HFS_SECTOR_SIZE_BITS
suffix:semicolon
id|offset
op_assign
id|pos
op_amp
(paren
id|HFS_SECTOR_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* compute the logical size of the fork in blocks */
id|size
op_assign
(paren
id|fork-&gt;lsize
op_plus
(paren
id|HFS_SECTOR_SIZE
op_minus
l_int|1
)paren
)paren
op_rshift
id|HFS_SECTOR_SIZE_BITS
suffix:semicolon
multiline_comment|/* compute the number of physical blocks to be transferred */
id|blocks
op_assign
(paren
id|count
op_plus
id|offset
op_plus
id|HFS_SECTOR_SIZE
op_minus
l_int|1
)paren
op_rshift
id|HFS_SECTOR_SIZE_BITS
suffix:semicolon
id|bhb
op_assign
id|bhe
op_assign
id|buflist
suffix:semicolon
r_if
c_cond
(paren
id|reada
)paren
(brace
r_if
c_cond
(paren
id|blocks
OL
id|read_ahead
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
op_div
(paren
id|HFS_SECTOR_SIZE
op_rshift
l_int|9
)paren
)paren
(brace
id|blocks
op_assign
id|read_ahead
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
op_div
(paren
id|HFS_SECTOR_SIZE
op_rshift
l_int|9
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|block
op_plus
id|blocks
OG
id|size
)paren
(brace
id|blocks
op_assign
id|size
op_minus
id|block
suffix:semicolon
)brace
)brace
multiline_comment|/* We do this in a two stage process.  We first try and&n;&t;   request as many blocks as we can, then we wait for the&n;&t;   first one to complete, and then we try and wrap up as many&n;&t;   as are actually done.&n;&t;   &n;&t;   This routine is optimized to make maximum use of the&n;&t;   various buffers and caches. */
r_do
(brace
id|bhrequest
op_assign
l_int|0
suffix:semicolon
id|uptodate
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|blocks
)paren
(brace
op_decrement
id|blocks
suffix:semicolon
op_star
id|bhb
op_assign
id|hfs_getblk
c_func
(paren
id|fork
comma
id|block
op_increment
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|bhb
)paren
)paren
(brace
multiline_comment|/* Since there are no holes in HFS files&n;&t;&t;&t;&t;   we must have encountered an error.&n;&t;&t;&t;&t;   So, stop adding blocks to the queue. */
id|blocks
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|buffer_uptodate
c_func
(paren
op_star
id|bhb
)paren
)paren
(brace
id|uptodate
op_assign
l_int|0
suffix:semicolon
id|bhreq
(braket
id|bhrequest
op_increment
)braket
op_assign
op_star
id|bhb
suffix:semicolon
)brace
r_if
c_cond
(paren
op_increment
id|bhb
op_eq
op_amp
id|buflist
(braket
id|NBUF
)braket
)paren
(brace
id|bhb
op_assign
id|buflist
suffix:semicolon
)brace
multiline_comment|/* If the block we have on hand is uptodate,&n;&t;&t;&t;   go ahead and complete processing. */
r_if
c_cond
(paren
id|uptodate
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bhb
op_eq
id|bhe
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* If the only block in the queue is bad then quit */
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|bhe
)paren
)paren
(brace
r_break
suffix:semicolon
)brace
multiline_comment|/* Now request them all */
r_if
c_cond
(paren
id|bhrequest
)paren
(brace
id|ll_rw_block
c_func
(paren
id|READ
comma
id|bhrequest
comma
id|bhreq
)paren
suffix:semicolon
)brace
r_do
(brace
multiline_comment|/* Finish off all I/O that has actually completed */
r_char
op_star
id|p
suffix:semicolon
id|wait_on_buffer
c_func
(paren
op_star
id|bhe
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer_uptodate
c_func
(paren
op_star
id|bhe
)paren
)paren
(brace
multiline_comment|/* read error? */
id|brelse
c_func
(paren
op_star
id|bhe
)paren
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|bhe
op_eq
op_amp
id|buflist
(braket
id|NBUF
)braket
)paren
(brace
id|bhe
op_assign
id|buflist
suffix:semicolon
)brace
id|count
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
OL
id|HFS_SECTOR_SIZE
op_minus
id|offset
)paren
(brace
id|chars
op_assign
id|count
suffix:semicolon
)brace
r_else
(brace
id|chars
op_assign
id|HFS_SECTOR_SIZE
op_minus
id|offset
suffix:semicolon
)brace
id|p
op_assign
(paren
op_star
id|bhe
)paren
op_member_access_from_pointer
id|b_data
op_plus
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|convert
)paren
(brace
id|xlate_to_user
c_func
(paren
id|buf
comma
id|p
comma
id|chars
)paren
suffix:semicolon
)brace
r_else
(brace
id|chars
op_sub_assign
id|copy_to_user
c_func
(paren
id|buf
comma
id|p
comma
id|chars
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|chars
)paren
(brace
id|brelse
c_func
(paren
op_star
id|bhe
)paren
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|read
)paren
id|read
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|brelse
c_func
(paren
op_star
id|bhe
)paren
suffix:semicolon
id|count
op_sub_assign
id|chars
suffix:semicolon
id|buf
op_add_assign
id|chars
suffix:semicolon
id|read
op_add_assign
id|chars
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|bhe
op_eq
op_amp
id|buflist
(braket
id|NBUF
)braket
)paren
(brace
id|bhe
op_assign
id|buflist
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|count
op_logical_and
(paren
id|bhe
op_ne
id|bhb
)paren
op_logical_and
op_logical_neg
id|buffer_locked
c_func
(paren
op_star
id|bhe
)paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
)paren
suffix:semicolon
multiline_comment|/* Release the read-ahead blocks */
r_while
c_loop
(paren
id|bhe
op_ne
id|bhb
)paren
(brace
id|brelse
c_func
(paren
op_star
id|bhe
)paren
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|bhe
op_eq
op_amp
id|buflist
(braket
id|NBUF
)braket
)paren
(brace
id|bhe
op_assign
id|buflist
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|read
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
id|read
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_do_write()&n; *&n; * This function transfers actual data from user-space memory to disk,&n; * returning the number of bytes successfully transferred.  &squot;fork&squot; tells&n; * which file on the disk to write to.  &squot;pos&squot; gives the offset into&n; * the Linux file at which to begin the transfer.  Note that this will&n; * differ from &squot;filp-&gt;offset&squot; in the case of an AppleDouble header file&n; * due to the block of metadata at the beginning of the file, which has&n; * no corresponding place in the HFS file.  &squot;count&squot; tells how many&n; * bytes to transfer.  &squot;buf&squot; gives an address in user-space to transfer&n; * the data from.&n; * &n; * This is just a minor edit of Linus&squot;s minix_file_write().&n; */
DECL|function|hfs_do_write
id|hfs_s32
id|hfs_do_write
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|hfs_fork
op_star
id|fork
comma
id|hfs_u32
id|pos
comma
r_const
r_char
op_star
id|buf
comma
id|hfs_u32
id|count
)paren
(brace
id|hfs_s32
id|written
comma
id|c
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_int
id|convert
op_assign
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|convert
suffix:semicolon
id|written
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|written
OL
id|count
)paren
(brace
id|bh
op_assign
id|hfs_getblk
c_func
(paren
id|fork
comma
id|pos
op_div
id|HFS_SECTOR_SIZE
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
r_if
c_cond
(paren
op_logical_neg
id|written
)paren
(brace
id|written
op_assign
op_minus
id|ENOSPC
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|c
op_assign
id|HFS_SECTOR_SIZE
op_minus
(paren
id|pos
op_mod
id|HFS_SECTOR_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
OG
id|count
op_minus
id|written
)paren
(brace
id|c
op_assign
id|count
op_minus
id|written
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
op_ne
id|HFS_SECTOR_SIZE
op_logical_and
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
(brace
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
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
(brace
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
id|written
)paren
(brace
id|written
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
id|p
op_assign
(paren
id|pos
op_mod
id|HFS_SECTOR_SIZE
)paren
op_plus
id|bh-&gt;b_data
suffix:semicolon
id|c
op_sub_assign
id|convert
ques
c_cond
id|xlate_from_user
c_func
(paren
id|p
comma
id|buf
comma
id|c
)paren
suffix:colon
id|copy_from_user
c_func
(paren
id|p
comma
id|buf
comma
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
(brace
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
id|written
)paren
id|written
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|pos
op_add_assign
id|c
suffix:semicolon
id|written
op_add_assign
id|c
suffix:semicolon
id|buf
op_add_assign
id|c
suffix:semicolon
id|mark_buffer_uptodate
c_func
(paren
id|bh
comma
l_int|1
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
)brace
r_if
c_cond
(paren
id|written
OG
l_int|0
)paren
(brace
r_struct
id|hfs_cat_entry
op_star
id|entry
op_assign
id|fork-&gt;entry
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
r_if
c_cond
(paren
id|pos
OG
id|fork-&gt;lsize
)paren
(brace
id|fork-&gt;lsize
op_assign
id|pos
suffix:semicolon
)brace
id|entry-&gt;modify_date
op_assign
id|hfs_u_to_mtime
c_func
(paren
id|CURRENT_TIME
)paren
suffix:semicolon
id|hfs_cat_mark_dirty
c_func
(paren
id|entry
)paren
suffix:semicolon
)brace
r_return
id|written
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_file_fix_mode()&n; *&n; * Fixes up the permissions on a file after changing the write-inhibit bit.&n; */
DECL|function|hfs_file_fix_mode
r_void
id|hfs_file_fix_mode
c_func
(paren
r_struct
id|hfs_cat_entry
op_star
id|entry
)paren
(brace
r_struct
id|dentry
op_star
op_star
id|de
op_assign
id|entry-&gt;sys_entry
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;u.file.flags
op_amp
id|HFS_FIL_LOCK
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
l_int|4
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|de
(braket
id|i
)braket
)paren
(brace
id|de
(braket
id|i
)braket
op_member_access_from_pointer
id|d_inode-&gt;i_mode
op_and_assign
op_complement
id|S_IWUGO
suffix:semicolon
)brace
)brace
)brace
r_else
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
l_int|4
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|de
(braket
id|i
)braket
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|de
(braket
id|i
)braket
op_member_access_from_pointer
id|d_inode
suffix:semicolon
id|inode-&gt;i_mode
op_or_assign
id|S_IWUGO
suffix:semicolon
id|inode-&gt;i_mode
op_and_assign
op_complement
id|HFS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|s_umask
suffix:semicolon
)brace
)brace
)brace
)brace
eof
