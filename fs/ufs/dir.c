multiline_comment|/*&n; *  linux/fs/ufs/ufs_dir.c&n; *&n; * Copyright (C) 1996&n; * Adrian Rodriguez (adrian@franklins-tower.rutgers.edu)&n; * Laboratory for Computer Science Research Computing Facility&n; * Rutgers, The State University of New Jersey&n; *&n; * swab support by Francois-Rene Rideau &lt;fare@tunes.org&gt; 19970406&n; *&n; * 4.4BSD (FreeBSD) support added on February 1st 1998 by&n; * Niels Kristian Bech Jensen &lt;nkbj@image.dk&gt; partially based&n; * on code by Martin von Loewis &lt;martin@mira.isdn.cs.tu-berlin.de&gt;.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ufs_fs.h&gt;
macro_line|#include &quot;swab.h&quot;
macro_line|#include &quot;util.h&quot;
DECL|macro|UFS_DIR_DEBUG
macro_line|#undef UFS_DIR_DEBUG
macro_line|#ifdef UFS_DIR_DEBUG
DECL|macro|UFSD
mdefine_line|#define UFSD(x) printk(&quot;(%s, %d), %s: &quot;, __FILE__, __LINE__, __FUNCTION__); printk x;
macro_line|#else
DECL|macro|UFSD
mdefine_line|#define UFSD(x)
macro_line|#endif
multiline_comment|/*&n; * NOTE! unlike strncmp, ufs_match returns 1 for success, 0 for failure.&n; *&n; * len &lt;= UFS_MAXNAMLEN and de != NULL are guaranteed by caller.&n; */
DECL|function|ufs_match
r_static
r_inline
r_int
id|ufs_match
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|len
comma
r_const
r_char
op_star
r_const
id|name
comma
r_struct
id|ufs_dir_entry
op_star
id|de
)paren
(brace
r_if
c_cond
(paren
id|len
op_ne
id|ufs_get_de_namlen
c_func
(paren
id|sb
comma
id|de
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|de-&gt;d_ino
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_logical_neg
id|memcmp
c_func
(paren
id|name
comma
id|de-&gt;d_name
comma
id|len
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is blatantly stolen from ext2fs&n; */
r_static
r_int
DECL|function|ufs_readdir
id|ufs_readdir
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
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|offset
comma
id|lblk
comma
id|blk
suffix:semicolon
r_int
id|i
comma
id|stored
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|ufs_dir_entry
op_star
id|de
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_int
id|de_reclen
suffix:semicolon
r_int
id|flags
suffix:semicolon
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
id|flags
op_assign
id|sb-&gt;u.ufs_sb.s_flags
suffix:semicolon
id|UFSD
c_func
(paren
(paren
l_string|&quot;ENTER, ino %lu  f_pos %lu&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
(paren
r_int
r_int
)paren
id|filp-&gt;f_pos
)paren
)paren
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
id|lblk
op_assign
(paren
id|filp-&gt;f_pos
)paren
op_rshift
id|sb-&gt;s_blocksize_bits
suffix:semicolon
id|blk
op_assign
id|ufs_frag_map
c_func
(paren
id|inode
comma
id|lblk
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|blk
op_logical_or
op_logical_neg
(paren
id|bh
op_assign
id|bread
(paren
id|sb-&gt;s_dev
comma
id|blk
comma
id|sb-&gt;s_blocksize
)paren
)paren
)paren
(brace
multiline_comment|/* XXX - error - skip to the next block */
id|printk
c_func
(paren
l_string|&quot;ufs_readdir: &quot;
l_string|&quot;dir inode %lu has a hole at offset %lu&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
(paren
r_int
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
id|ufs_dir_entry
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
id|i
)paren
suffix:semicolon
multiline_comment|/* It&squot;s too expensive to do a full&n;&t;&t;&t;&t; * dirent test each time round this&n;&t;&t;&t;&t; * loop, but we do have to test at&n;&t;&t;&t;&t; * least that it is non-zero.  A&n;&t;&t;&t;&t; * failure will be detected in the&n;&t;&t;&t;&t; * dirent test below. */
id|de_reclen
op_assign
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|de-&gt;d_reclen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|de_reclen
OL
l_int|1
)paren
r_break
suffix:semicolon
id|i
op_add_assign
id|de_reclen
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
id|ufs_dir_entry
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
id|offset
)paren
suffix:semicolon
multiline_comment|/* XXX - put in a real ufs_check_dir_entry() */
r_if
c_cond
(paren
(paren
id|de-&gt;d_reclen
op_eq
l_int|0
)paren
op_logical_or
(paren
id|ufs_get_de_namlen
c_func
(paren
id|sb
comma
id|de
)paren
op_eq
l_int|0
)paren
)paren
(brace
id|filp-&gt;f_pos
op_assign
(paren
id|filp-&gt;f_pos
op_amp
(paren
id|sb-&gt;s_blocksize
op_minus
l_int|1
)paren
)paren
op_plus
id|sb-&gt;s_blocksize
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|stored
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ufs_check_dir_entry
(paren
l_string|&quot;ufs_readdir&quot;
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
multiline_comment|/* On error, skip the f_pos to the&n;&t;&t;&t;&t;   next block. */
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
r_return
id|stored
suffix:semicolon
)brace
id|offset
op_add_assign
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|de-&gt;d_reclen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|de-&gt;d_ino
)paren
(brace
multiline_comment|/* We might block in the next section&n;&t;&t;&t;&t; * if the data destination is&n;&t;&t;&t;&t; * currently swapped out.  So, use a&n;&t;&t;&t;&t; * version stamp to detect whether or&n;&t;&t;&t;&t; * not the directory has been modified&n;&t;&t;&t;&t; * during the copy operation. */
r_int
r_int
id|version
op_assign
id|filp-&gt;f_version
suffix:semicolon
r_int
r_char
id|d_type
op_assign
id|DT_UNKNOWN
suffix:semicolon
id|UFSD
c_func
(paren
(paren
l_string|&quot;filldir(%s,%u)&bslash;n&quot;
comma
id|de-&gt;d_name
comma
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|de-&gt;d_ino
)paren
)paren
)paren
id|UFSD
c_func
(paren
(paren
l_string|&quot;namlen %u&bslash;n&quot;
comma
id|ufs_get_de_namlen
c_func
(paren
id|sb
comma
id|de
)paren
)paren
)paren
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|UFS_DE_MASK
)paren
op_eq
id|UFS_DE_44BSD
)paren
id|d_type
op_assign
id|de-&gt;d_u.d_44.d_type
suffix:semicolon
id|error
op_assign
id|filldir
c_func
(paren
id|dirent
comma
id|de-&gt;d_name
comma
id|ufs_get_de_namlen
c_func
(paren
id|sb
comma
id|de
)paren
comma
id|filp-&gt;f_pos
comma
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|de-&gt;d_ino
)paren
comma
id|d_type
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
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|de-&gt;d_reclen
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
id|UPDATE_ATIME
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * define how far ahead to read directories while searching them.&n; */
DECL|macro|NAMEI_RA_CHUNKS
mdefine_line|#define NAMEI_RA_CHUNKS  2
DECL|macro|NAMEI_RA_BLOCKS
mdefine_line|#define NAMEI_RA_BLOCKS  4
DECL|macro|NAMEI_RA_SIZE
mdefine_line|#define NAMEI_RA_SIZE        (NAMEI_RA_CHUNKS * NAMEI_RA_BLOCKS)
DECL|macro|NAMEI_RA_INDEX
mdefine_line|#define NAMEI_RA_INDEX(c,b)  (((c) * NAMEI_RA_BLOCKS) + (b))
multiline_comment|/*&n; *&t;ufs_find_entry()&n; *&n; * finds an entry in the specified directory with the wanted name. It&n; * returns the cache buffer in which the entry was found, and the entry&n; * itself (as a parameter - res_bh). It does NOT read the inode of the&n; * entry - you&squot;ll have to do that yourself if you want to.&n; */
DECL|function|ufs_find_entry
r_struct
id|ufs_dir_entry
op_star
id|ufs_find_entry
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|buffer_head
op_star
op_star
id|res_bh
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
id|bh_use
(braket
id|NAMEI_RA_SIZE
)braket
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh_read
(braket
id|NAMEI_RA_SIZE
)braket
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
r_int
id|block
comma
id|toread
comma
id|i
comma
id|err
suffix:semicolon
r_struct
id|inode
op_star
id|dir
op_assign
id|dentry-&gt;d_parent-&gt;d_inode
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
id|dentry-&gt;d_name.name
suffix:semicolon
r_int
id|namelen
op_assign
id|dentry-&gt;d_name.len
suffix:semicolon
id|UFSD
c_func
(paren
(paren
l_string|&quot;ENTER, dir_ino %lu, name %s, namlen %u&bslash;n&quot;
comma
id|dir-&gt;i_ino
comma
id|name
comma
id|namelen
)paren
)paren
op_star
id|res_bh
op_assign
l_int|NULL
suffix:semicolon
id|sb
op_assign
id|dir-&gt;i_sb
suffix:semicolon
r_if
c_cond
(paren
id|namelen
OG
id|UFS_MAXNAMLEN
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
(paren
id|bh_use
comma
l_int|0
comma
r_sizeof
(paren
id|bh_use
)paren
)paren
suffix:semicolon
id|toread
op_assign
l_int|0
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
id|NAMEI_RA_SIZE
suffix:semicolon
op_increment
id|block
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_if
c_cond
(paren
(paren
id|block
op_lshift
id|sb-&gt;s_blocksize_bits
)paren
op_ge
id|dir-&gt;i_size
)paren
r_break
suffix:semicolon
id|bh
op_assign
id|ufs_getfrag
(paren
id|dir
comma
id|block
comma
l_int|0
comma
op_amp
id|err
)paren
suffix:semicolon
id|bh_use
(braket
id|block
)braket
op_assign
id|bh
suffix:semicolon
r_if
c_cond
(paren
id|bh
op_logical_and
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
id|bh_read
(braket
id|toread
op_increment
)braket
op_assign
id|bh
suffix:semicolon
)brace
r_for
c_loop
(paren
id|block
op_assign
l_int|0
comma
id|offset
op_assign
l_int|0
suffix:semicolon
id|offset
OL
id|dir-&gt;i_size
suffix:semicolon
id|block
op_increment
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|ufs_dir_entry
op_star
id|de
suffix:semicolon
r_char
op_star
id|dlimit
suffix:semicolon
r_if
c_cond
(paren
(paren
id|block
op_mod
id|NAMEI_RA_BLOCKS
)paren
op_eq
l_int|0
op_logical_and
id|toread
)paren
(brace
id|ll_rw_block
(paren
id|READ
comma
id|toread
comma
id|bh_read
)paren
suffix:semicolon
id|toread
op_assign
l_int|0
suffix:semicolon
)brace
id|bh
op_assign
id|bh_use
(braket
id|block
op_mod
id|NAMEI_RA_SIZE
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|ufs_error
(paren
id|sb
comma
l_string|&quot;ufs_find_entry&quot;
comma
l_string|&quot;directory #%lu contains a hole at offset %lu&quot;
comma
id|dir-&gt;i_ino
comma
id|offset
)paren
suffix:semicolon
id|offset
op_add_assign
id|sb-&gt;s_blocksize
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|wait_on_buffer
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
multiline_comment|/*&n;&t;&t;&t; * read error: all bets are off&n;&t;&t;&t; */
r_break
suffix:semicolon
)brace
id|de
op_assign
(paren
r_struct
id|ufs_dir_entry
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|dlimit
op_assign
id|bh-&gt;b_data
op_plus
id|sb-&gt;s_blocksize
suffix:semicolon
r_while
c_loop
(paren
(paren
r_char
op_star
)paren
id|de
OL
id|dlimit
op_logical_and
id|offset
OL
id|dir-&gt;i_size
)paren
(brace
multiline_comment|/* this code is executed quadratically often */
multiline_comment|/* do minimal checking by hand */
r_int
id|de_len
suffix:semicolon
r_if
c_cond
(paren
(paren
r_char
op_star
)paren
id|de
op_plus
id|namelen
op_le
id|dlimit
op_logical_and
id|ufs_match
c_func
(paren
id|sb
comma
id|namelen
comma
id|name
comma
id|de
)paren
)paren
(brace
multiline_comment|/* found a match -&n;&t;&t;&t;&t;just to be sure, do a full check */
r_if
c_cond
(paren
op_logical_neg
id|ufs_check_dir_entry
c_func
(paren
l_string|&quot;ufs_find_entry&quot;
comma
id|dir
comma
id|de
comma
id|bh
comma
id|offset
)paren
)paren
r_goto
id|failed
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
id|NAMEI_RA_SIZE
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|bh_use
(braket
id|i
)braket
op_ne
id|bh
)paren
id|brelse
(paren
id|bh_use
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
op_star
id|res_bh
op_assign
id|bh
suffix:semicolon
r_return
id|de
suffix:semicolon
)brace
multiline_comment|/* prevent looping on a bad block */
id|de_len
op_assign
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|de-&gt;d_reclen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|de_len
op_le
l_int|0
)paren
r_goto
id|failed
suffix:semicolon
id|offset
op_add_assign
id|de_len
suffix:semicolon
id|de
op_assign
(paren
r_struct
id|ufs_dir_entry
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|de
op_plus
id|de_len
)paren
suffix:semicolon
)brace
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|block
op_plus
id|NAMEI_RA_SIZE
)paren
op_lshift
id|sb-&gt;s_blocksize_bits
)paren
op_ge
id|dir-&gt;i_size
)paren
id|bh
op_assign
l_int|NULL
suffix:semicolon
r_else
id|bh
op_assign
id|ufs_getfrag
(paren
id|dir
comma
id|block
op_plus
id|NAMEI_RA_SIZE
comma
l_int|0
comma
op_amp
id|err
)paren
suffix:semicolon
id|bh_use
(braket
id|block
op_mod
id|NAMEI_RA_SIZE
)braket
op_assign
id|bh
suffix:semicolon
r_if
c_cond
(paren
id|bh
op_logical_and
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
id|bh_read
(braket
id|toread
op_increment
)braket
op_assign
id|bh
suffix:semicolon
)brace
id|failed
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
id|NAMEI_RA_SIZE
suffix:semicolon
op_increment
id|i
)paren
id|brelse
(paren
id|bh_use
(braket
id|i
)braket
)paren
suffix:semicolon
id|UFSD
c_func
(paren
(paren
l_string|&quot;EXIT&bslash;n&quot;
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|ufs_check_dir_entry
r_int
id|ufs_check_dir_entry
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
id|ufs_dir_entry
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
r_struct
id|super_block
op_star
id|sb
op_assign
id|dir-&gt;i_sb
suffix:semicolon
r_const
r_char
op_star
id|error_msg
op_assign
l_int|NULL
suffix:semicolon
r_int
id|rlen
op_assign
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|de-&gt;d_reclen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rlen
OL
id|UFS_DIR_REC_LEN
c_func
(paren
l_int|1
)paren
)paren
id|error_msg
op_assign
l_string|&quot;reclen is smaller than minimal&quot;
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
l_string|&quot;reclen % 4 != 0&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rlen
OL
id|UFS_DIR_REC_LEN
c_func
(paren
id|ufs_get_de_namlen
c_func
(paren
id|sb
comma
id|de
)paren
)paren
)paren
id|error_msg
op_assign
l_string|&quot;reclen is too small for namlen&quot;
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
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|de-&gt;d_ino
)paren
OG
(paren
id|sb-&gt;u.ufs_sb.s_uspi-&gt;s_ipg
op_star
id|sb-&gt;u.ufs_sb.s_uspi-&gt;s_ncg
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
id|ufs_error
(paren
id|sb
comma
id|function
comma
l_string|&quot;bad entry in directory #%lu, size %Lu: %s - &quot;
l_string|&quot;offset=%lu, inode=%lu, reclen=%d, namlen=%d&quot;
comma
id|dir-&gt;i_ino
comma
id|dir-&gt;i_size
comma
id|error_msg
comma
id|offset
comma
(paren
r_int
r_int
)paren
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|de-&gt;d_ino
)paren
comma
id|rlen
comma
id|ufs_get_de_namlen
c_func
(paren
id|sb
comma
id|de
)paren
)paren
suffix:semicolon
r_return
(paren
id|error_msg
op_eq
l_int|NULL
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|ufs_dotdot
r_struct
id|ufs_dir_entry
op_star
id|ufs_dotdot
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|buffer_head
op_star
op_star
id|p
)paren
(brace
r_int
id|err
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
op_assign
id|ufs_bread
(paren
id|dir
comma
l_int|0
comma
l_int|0
comma
op_amp
id|err
)paren
suffix:semicolon
r_struct
id|ufs_dir_entry
op_star
id|res
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
(brace
id|res
op_assign
(paren
r_struct
id|ufs_dir_entry
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|res
op_assign
(paren
r_struct
id|ufs_dir_entry
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|res
op_plus
id|fs16_to_cpu
c_func
(paren
id|dir-&gt;i_sb
comma
id|res-&gt;d_reclen
)paren
)paren
suffix:semicolon
)brace
op_star
id|p
op_assign
id|bh
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|ufs_inode_by_name
id|ino_t
id|ufs_inode_by_name
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
id|ino_t
id|res
op_assign
l_int|0
suffix:semicolon
r_struct
id|ufs_dir_entry
op_star
id|de
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|de
op_assign
id|ufs_find_entry
(paren
id|dentry
comma
op_amp
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|de
)paren
(brace
id|res
op_assign
id|fs32_to_cpu
c_func
(paren
id|dir-&gt;i_sb
comma
id|de-&gt;d_ino
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
DECL|function|ufs_set_link
r_void
id|ufs_set_link
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|ufs_dir_entry
op_star
id|de
comma
r_struct
id|buffer_head
op_star
id|bh
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|dir-&gt;i_version
op_assign
op_increment
id|event
suffix:semicolon
id|de-&gt;d_ino
op_assign
id|cpu_to_fs32
c_func
(paren
id|dir-&gt;i_sb
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_SYNC
c_func
(paren
id|dir
)paren
)paren
(brace
id|ll_rw_block
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
)brace
id|brelse
(paren
id|bh
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;ufs_add_entry()&n; *&n; * adds a file entry to the specified directory, using the same&n; * semantics as ufs_find_entry(). It returns NULL if it failed.&n; */
DECL|function|ufs_add_link
r_int
id|ufs_add_link
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
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
suffix:semicolon
r_struct
id|ufs_sb_private_info
op_star
id|uspi
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
r_int
id|fragoff
suffix:semicolon
r_int
r_int
id|rec_len
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|ufs_dir_entry
op_star
id|de
comma
op_star
id|de1
suffix:semicolon
r_struct
id|inode
op_star
id|dir
op_assign
id|dentry-&gt;d_parent-&gt;d_inode
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
id|dentry-&gt;d_name.name
suffix:semicolon
r_int
id|namelen
op_assign
id|dentry-&gt;d_name.len
suffix:semicolon
r_int
id|err
suffix:semicolon
id|UFSD
c_func
(paren
(paren
l_string|&quot;ENTER, name %s, namelen %u&bslash;n&quot;
comma
id|name
comma
id|namelen
)paren
)paren
id|sb
op_assign
id|dir-&gt;i_sb
suffix:semicolon
id|uspi
op_assign
id|sb-&gt;u.ufs_sb.s_uspi
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|namelen
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|bh
op_assign
id|ufs_bread
(paren
id|dir
comma
l_int|0
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
r_return
id|err
suffix:semicolon
id|rec_len
op_assign
id|UFS_DIR_REC_LEN
c_func
(paren
id|namelen
)paren
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
id|de
op_assign
(paren
r_struct
id|ufs_dir_entry
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
(paren
r_char
op_star
)paren
id|de
op_ge
id|UFS_SECTOR_SIZE
op_plus
id|bh-&gt;b_data
)paren
(brace
id|fragoff
op_assign
id|offset
op_amp
op_complement
id|uspi-&gt;s_fmask
suffix:semicolon
r_if
c_cond
(paren
id|fragoff
op_ne
l_int|0
op_logical_and
id|fragoff
op_ne
id|UFS_SECTOR_SIZE
)paren
id|ufs_error
(paren
id|sb
comma
l_string|&quot;ufs_add_entry&quot;
comma
l_string|&quot;internal error&quot;
l_string|&quot; fragoff %u&quot;
comma
id|fragoff
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fragoff
)paren
(brace
id|brelse
(paren
id|bh
)paren
suffix:semicolon
id|bh
op_assign
id|ufs_bread
(paren
id|dir
comma
id|offset
op_rshift
id|sb-&gt;s_blocksize_bits
comma
l_int|1
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
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dir-&gt;i_size
op_le
id|offset
)paren
(brace
r_if
c_cond
(paren
id|dir-&gt;i_size
op_eq
l_int|0
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
id|de
op_assign
(paren
r_struct
id|ufs_dir_entry
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
id|fragoff
)paren
suffix:semicolon
id|de-&gt;d_ino
op_assign
l_int|0
suffix:semicolon
id|de-&gt;d_reclen
op_assign
id|cpu_to_fs16
c_func
(paren
id|sb
comma
id|UFS_SECTOR_SIZE
)paren
suffix:semicolon
id|ufs_set_de_namlen
c_func
(paren
id|sb
comma
id|de
comma
l_int|0
)paren
suffix:semicolon
id|dir-&gt;i_size
op_assign
id|offset
op_plus
id|UFS_SECTOR_SIZE
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
)paren
suffix:semicolon
)brace
r_else
(brace
id|de
op_assign
(paren
r_struct
id|ufs_dir_entry
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|ufs_check_dir_entry
(paren
l_string|&quot;ufs_add_entry&quot;
comma
id|dir
comma
id|de
comma
id|bh
comma
id|offset
)paren
)paren
(brace
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ufs_match
c_func
(paren
id|sb
comma
id|namelen
comma
id|name
comma
id|de
)paren
)paren
(brace
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_return
op_minus
id|EEXIST
suffix:semicolon
)brace
r_if
c_cond
(paren
id|de-&gt;d_ino
op_eq
l_int|0
op_logical_and
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|de-&gt;d_reclen
)paren
op_ge
id|rec_len
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|de-&gt;d_reclen
)paren
op_ge
id|UFS_DIR_REC_LEN
c_func
(paren
id|ufs_get_de_namlen
c_func
(paren
id|sb
comma
id|de
)paren
)paren
op_plus
id|rec_len
)paren
r_break
suffix:semicolon
id|offset
op_add_assign
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|de-&gt;d_reclen
)paren
suffix:semicolon
id|de
op_assign
(paren
r_struct
id|ufs_dir_entry
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|de
op_plus
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|de-&gt;d_reclen
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|de-&gt;d_ino
)paren
(brace
id|de1
op_assign
(paren
r_struct
id|ufs_dir_entry
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|de
op_plus
id|UFS_DIR_REC_LEN
c_func
(paren
id|ufs_get_de_namlen
c_func
(paren
id|sb
comma
id|de
)paren
)paren
)paren
suffix:semicolon
id|de1-&gt;d_reclen
op_assign
id|cpu_to_fs16
c_func
(paren
id|sb
comma
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|de-&gt;d_reclen
)paren
op_minus
id|UFS_DIR_REC_LEN
c_func
(paren
id|ufs_get_de_namlen
c_func
(paren
id|sb
comma
id|de
)paren
)paren
)paren
suffix:semicolon
id|de-&gt;d_reclen
op_assign
id|cpu_to_fs16
c_func
(paren
id|sb
comma
id|UFS_DIR_REC_LEN
c_func
(paren
id|ufs_get_de_namlen
c_func
(paren
id|sb
comma
id|de
)paren
)paren
)paren
suffix:semicolon
id|de
op_assign
id|de1
suffix:semicolon
)brace
id|de-&gt;d_ino
op_assign
l_int|0
suffix:semicolon
id|ufs_set_de_namlen
c_func
(paren
id|sb
comma
id|de
comma
id|namelen
)paren
suffix:semicolon
id|memcpy
(paren
id|de-&gt;d_name
comma
id|name
comma
id|namelen
op_plus
l_int|1
)paren
suffix:semicolon
id|de-&gt;d_ino
op_assign
id|cpu_to_fs32
c_func
(paren
id|sb
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|ufs_set_de_type
c_func
(paren
id|sb
comma
id|de
comma
id|inode-&gt;i_mode
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_SYNC
c_func
(paren
id|dir
)paren
)paren
(brace
id|ll_rw_block
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
(paren
id|bh
)paren
suffix:semicolon
)brace
id|brelse
(paren
id|bh
)paren
suffix:semicolon
id|dir-&gt;i_mtime
op_assign
id|dir-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|dir-&gt;i_version
op_assign
op_increment
id|event
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
)paren
suffix:semicolon
id|UFSD
c_func
(paren
(paren
l_string|&quot;EXIT&bslash;n&quot;
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * ufs_delete_entry deletes a directory entry by merging it with the&n; * previous entry.&n; */
DECL|function|ufs_delete_entry
r_int
id|ufs_delete_entry
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|ufs_dir_entry
op_star
id|dir
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_struct
id|ufs_dir_entry
op_star
id|de
comma
op_star
id|pde
suffix:semicolon
r_int
id|i
suffix:semicolon
id|UFSD
c_func
(paren
(paren
l_string|&quot;ENTER&bslash;n&quot;
)paren
)paren
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
id|pde
op_assign
l_int|NULL
suffix:semicolon
id|de
op_assign
(paren
r_struct
id|ufs_dir_entry
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|UFSD
c_func
(paren
(paren
l_string|&quot;ino %u, reclen %u, namlen %u, name %s&bslash;n&quot;
comma
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|de-&gt;d_ino
)paren
comma
id|fs16to_cpu
c_func
(paren
id|sb
comma
id|de-&gt;d_reclen
)paren
comma
id|ufs_get_de_namlen
c_func
(paren
id|sb
comma
id|de
)paren
comma
id|de-&gt;d_name
)paren
)paren
r_while
c_loop
(paren
id|i
OL
id|bh-&gt;b_size
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ufs_check_dir_entry
(paren
l_string|&quot;ufs_delete_entry&quot;
comma
id|inode
comma
id|de
comma
id|bh
comma
id|i
)paren
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|de
op_eq
id|dir
)paren
(brace
r_if
c_cond
(paren
id|pde
)paren
id|fs16_add
c_func
(paren
id|sb
comma
op_amp
id|pde-&gt;d_reclen
comma
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|dir-&gt;d_reclen
)paren
)paren
suffix:semicolon
id|dir-&gt;d_ino
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_version
op_assign
op_increment
id|event
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|inode-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_SYNC
c_func
(paren
id|inode
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
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|UFSD
c_func
(paren
(paren
l_string|&quot;EXIT&bslash;n&quot;
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
id|i
op_add_assign
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|de-&gt;d_reclen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|UFS_SECTOR_SIZE
)paren
id|pde
op_assign
l_int|NULL
suffix:semicolon
r_else
id|pde
op_assign
id|de
suffix:semicolon
id|de
op_assign
(paren
r_struct
id|ufs_dir_entry
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|de
op_plus
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|de-&gt;d_reclen
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|UFS_SECTOR_SIZE
op_logical_and
id|de-&gt;d_reclen
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
id|UFSD
c_func
(paren
(paren
l_string|&quot;EXIT&bslash;n&quot;
)paren
)paren
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
DECL|function|ufs_make_empty
r_int
id|ufs_make_empty
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|inode
op_star
id|dir
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|dir-&gt;i_sb
suffix:semicolon
r_struct
id|buffer_head
op_star
id|dir_block
suffix:semicolon
r_struct
id|ufs_dir_entry
op_star
id|de
suffix:semicolon
r_int
id|err
suffix:semicolon
id|dir_block
op_assign
id|ufs_bread
(paren
id|inode
comma
l_int|0
comma
l_int|1
comma
op_amp
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir_block
)paren
r_return
id|err
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
id|sb-&gt;s_blocksize
op_div
id|UFS_SECTOR_SIZE
suffix:semicolon
id|de
op_assign
(paren
r_struct
id|ufs_dir_entry
op_star
)paren
id|dir_block-&gt;b_data
suffix:semicolon
id|de-&gt;d_ino
op_assign
id|cpu_to_fs32
c_func
(paren
id|sb
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|ufs_set_de_type
c_func
(paren
id|sb
comma
id|de
comma
id|inode-&gt;i_mode
)paren
suffix:semicolon
id|ufs_set_de_namlen
c_func
(paren
id|sb
comma
id|de
comma
l_int|1
)paren
suffix:semicolon
id|de-&gt;d_reclen
op_assign
id|cpu_to_fs16
c_func
(paren
id|sb
comma
id|UFS_DIR_REC_LEN
c_func
(paren
l_int|1
)paren
)paren
suffix:semicolon
id|strcpy
(paren
id|de-&gt;d_name
comma
l_string|&quot;.&quot;
)paren
suffix:semicolon
id|de
op_assign
(paren
r_struct
id|ufs_dir_entry
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|de
op_plus
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|de-&gt;d_reclen
)paren
)paren
suffix:semicolon
id|de-&gt;d_ino
op_assign
id|cpu_to_fs32
c_func
(paren
id|sb
comma
id|dir-&gt;i_ino
)paren
suffix:semicolon
id|ufs_set_de_type
c_func
(paren
id|sb
comma
id|de
comma
id|dir-&gt;i_mode
)paren
suffix:semicolon
id|de-&gt;d_reclen
op_assign
id|cpu_to_fs16
c_func
(paren
id|sb
comma
id|UFS_SECTOR_SIZE
op_minus
id|UFS_DIR_REC_LEN
c_func
(paren
l_int|1
)paren
)paren
suffix:semicolon
id|ufs_set_de_namlen
c_func
(paren
id|sb
comma
id|de
comma
l_int|2
)paren
suffix:semicolon
id|strcpy
(paren
id|de-&gt;d_name
comma
l_string|&quot;..&quot;
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|dir_block
)paren
suffix:semicolon
id|brelse
(paren
id|dir_block
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * routine to check that the specified directory is empty (for rmdir)&n; */
DECL|function|ufs_empty_dir
r_int
id|ufs_empty_dir
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
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|ufs_dir_entry
op_star
id|de
comma
op_star
id|de1
suffix:semicolon
r_int
id|err
suffix:semicolon
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_size
OL
id|UFS_DIR_REC_LEN
c_func
(paren
l_int|1
)paren
op_plus
id|UFS_DIR_REC_LEN
c_func
(paren
l_int|2
)paren
op_logical_or
op_logical_neg
(paren
id|bh
op_assign
id|ufs_bread
(paren
id|inode
comma
l_int|0
comma
l_int|0
comma
op_amp
id|err
)paren
)paren
)paren
(brace
id|ufs_warning
(paren
id|inode-&gt;i_sb
comma
l_string|&quot;empty_dir&quot;
comma
l_string|&quot;bad directory (dir #%lu) - no data block&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|de
op_assign
(paren
r_struct
id|ufs_dir_entry
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|de1
op_assign
(paren
r_struct
id|ufs_dir_entry
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|de
op_plus
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|de-&gt;d_reclen
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|de-&gt;d_ino
)paren
op_ne
id|inode-&gt;i_ino
op_logical_or
id|de1-&gt;d_ino
op_eq
l_int|0
op_logical_or
id|strcmp
(paren
l_string|&quot;.&quot;
comma
id|de-&gt;d_name
)paren
op_logical_or
id|strcmp
(paren
l_string|&quot;..&quot;
comma
id|de1-&gt;d_name
)paren
)paren
(brace
id|ufs_warning
(paren
id|inode-&gt;i_sb
comma
l_string|&quot;empty_dir&quot;
comma
l_string|&quot;bad directory (dir #%lu) - no `.&squot; or `..&squot;&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|offset
op_assign
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|de-&gt;d_reclen
)paren
op_plus
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|de1-&gt;d_reclen
)paren
suffix:semicolon
id|de
op_assign
(paren
r_struct
id|ufs_dir_entry
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|de1
op_plus
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|de1-&gt;d_reclen
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|offset
OL
id|inode-&gt;i_size
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|bh
op_logical_or
(paren
r_void
op_star
)paren
id|de
op_ge
(paren
r_void
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
id|sb-&gt;s_blocksize
)paren
)paren
(brace
id|brelse
(paren
id|bh
)paren
suffix:semicolon
id|bh
op_assign
id|ufs_bread
(paren
id|inode
comma
id|offset
op_rshift
id|sb-&gt;s_blocksize_bits
comma
l_int|1
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
id|ufs_error
(paren
id|sb
comma
l_string|&quot;empty_dir&quot;
comma
l_string|&quot;directory #%lu contains a hole at offset %lu&quot;
comma
id|inode-&gt;i_ino
comma
id|offset
)paren
suffix:semicolon
id|offset
op_add_assign
id|sb-&gt;s_blocksize
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|de
op_assign
(paren
r_struct
id|ufs_dir_entry
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ufs_check_dir_entry
(paren
l_string|&quot;empty_dir&quot;
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
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|de-&gt;d_ino
)paren
(brace
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|offset
op_add_assign
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|de-&gt;d_reclen
)paren
suffix:semicolon
id|de
op_assign
(paren
r_struct
id|ufs_dir_entry
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|de
op_plus
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|de-&gt;d_reclen
)paren
)paren
suffix:semicolon
)brace
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|ufs_dir_operations
r_struct
id|file_operations
id|ufs_dir_operations
op_assign
(brace
id|read
suffix:colon
id|generic_read_dir
comma
id|readdir
suffix:colon
id|ufs_readdir
comma
id|fsync
suffix:colon
id|file_fsync
comma
)brace
suffix:semicolon
eof
