multiline_comment|/*&n; *  linux/fs/isofs/dir.c&n; *&n; *  (C) 1992, 1993, 1994  Eric Youngdale Modified for ISO 9660 filesystem.&n; *&n; *  (C) 1991  Linus Torvalds - minix filesystem&n; *&n; *  Steve Beynon&t;&t;       : Missing last directory entries fixed&n; *  (stephen@askone.demon.co.uk)      : 21st June 1996&n; * &n; *  isofs directory handling functions&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/iso_fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_static
r_int
id|isofs_readdir
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
DECL|variable|isofs_dir_operations
r_struct
id|file_operations
id|isofs_dir_operations
op_assign
(brace
id|read
suffix:colon
id|generic_read_dir
comma
id|readdir
suffix:colon
id|isofs_readdir
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * directories can handle most operations...&n; */
DECL|variable|isofs_dir_inode_operations
r_struct
id|inode_operations
id|isofs_dir_inode_operations
op_assign
(brace
id|lookup
suffix:colon
id|isofs_lookup
comma
)brace
suffix:semicolon
DECL|function|isofs_name_translate
r_int
id|isofs_name_translate
c_func
(paren
r_struct
id|iso_directory_record
op_star
id|de
comma
r_char
op_star
r_new
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_char
op_star
id|old
op_assign
id|de-&gt;name
suffix:semicolon
r_int
id|len
op_assign
id|de-&gt;name_len
(braket
l_int|0
)braket
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
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_char
id|c
op_assign
id|old
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ge
l_char|&squot;A&squot;
op_logical_and
id|c
op_le
l_char|&squot;Z&squot;
)paren
id|c
op_or_assign
l_int|0x20
suffix:semicolon
multiline_comment|/* lower case */
multiline_comment|/* Drop trailing &squot;.;1&squot; (ISO 9660:1988 7.5.1 requires period) */
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;.&squot;
op_logical_and
id|i
op_eq
id|len
op_minus
l_int|3
op_logical_and
id|old
(braket
id|i
op_plus
l_int|1
)braket
op_eq
l_char|&squot;;&squot;
op_logical_and
id|old
(braket
id|i
op_plus
l_int|2
)braket
op_eq
l_char|&squot;1&squot;
)paren
r_break
suffix:semicolon
multiline_comment|/* Drop trailing &squot;;1&squot; */
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;;&squot;
op_logical_and
id|i
op_eq
id|len
op_minus
l_int|2
op_logical_and
id|old
(braket
id|i
op_plus
l_int|1
)braket
op_eq
l_char|&squot;1&squot;
)paren
r_break
suffix:semicolon
multiline_comment|/* Convert remaining &squot;;&squot; to &squot;.&squot; */
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;;&squot;
)paren
id|c
op_assign
l_char|&squot;.&squot;
suffix:semicolon
r_new
(braket
id|i
)braket
op_assign
id|c
suffix:semicolon
)brace
r_return
id|i
suffix:semicolon
)brace
multiline_comment|/* Acorn extensions written by Matthew Wilcox &lt;willy@bofh.ai&gt; 1998 */
DECL|function|get_acorn_filename
r_int
id|get_acorn_filename
c_func
(paren
r_struct
id|iso_directory_record
op_star
id|de
comma
r_char
op_star
id|retname
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
id|std
suffix:semicolon
r_int
r_char
op_star
id|chr
suffix:semicolon
r_int
id|retnamlen
op_assign
id|isofs_name_translate
c_func
(paren
id|de
comma
id|retname
comma
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retnamlen
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|std
op_assign
r_sizeof
(paren
r_struct
id|iso_directory_record
)paren
op_plus
id|de-&gt;name_len
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|std
op_amp
l_int|1
)paren
id|std
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
(paren
(paren
r_int
r_char
op_star
)paren
id|de
)paren
op_minus
id|std
)paren
op_ne
l_int|32
)paren
r_return
id|retnamlen
suffix:semicolon
id|chr
op_assign
(paren
(paren
r_int
r_char
op_star
)paren
id|de
)paren
op_plus
id|std
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|chr
comma
l_string|&quot;ARCHIMEDES&quot;
comma
l_int|10
)paren
)paren
r_return
id|retnamlen
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|retname
op_eq
l_char|&squot;_&squot;
)paren
op_logical_and
(paren
(paren
id|chr
(braket
l_int|19
)braket
op_amp
l_int|1
)paren
op_eq
l_int|1
)paren
)paren
op_star
id|retname
op_assign
l_char|&squot;!&squot;
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|de-&gt;flags
(braket
l_int|0
)braket
op_amp
l_int|2
)paren
op_eq
l_int|0
)paren
op_logical_and
(paren
id|chr
(braket
l_int|13
)braket
op_eq
l_int|0xff
)paren
op_logical_and
(paren
(paren
id|chr
(braket
l_int|12
)braket
op_amp
l_int|0xf0
)paren
op_eq
l_int|0xf0
)paren
)paren
(brace
id|retname
(braket
id|retnamlen
)braket
op_assign
l_char|&squot;,&squot;
suffix:semicolon
id|sprintf
c_func
(paren
id|retname
op_plus
id|retnamlen
op_plus
l_int|1
comma
l_string|&quot;%3.3x&quot;
comma
(paren
(paren
id|chr
(braket
l_int|12
)braket
op_amp
l_int|0xf
)paren
op_lshift
l_int|8
)paren
op_or
id|chr
(braket
l_int|11
)braket
)paren
suffix:semicolon
id|retnamlen
op_add_assign
l_int|4
suffix:semicolon
)brace
r_return
id|retnamlen
suffix:semicolon
)brace
multiline_comment|/*&n; * This should _really_ be cleaned up some day..&n; */
DECL|function|do_isofs_readdir
r_static
r_int
id|do_isofs_readdir
c_func
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
comma
r_void
op_star
id|dirent
comma
id|filldir_t
id|filldir
comma
r_char
op_star
id|tmpname
comma
r_struct
id|iso_directory_record
op_star
id|tmpde
)paren
(brace
r_int
r_int
id|bufsize
op_assign
id|ISOFS_BUFFER_SIZE
c_func
(paren
id|inode
)paren
suffix:semicolon
r_int
r_char
id|bufbits
op_assign
id|ISOFS_BUFFER_BITS
c_func
(paren
id|inode
)paren
suffix:semicolon
r_int
r_int
id|block
comma
id|offset
suffix:semicolon
r_int
id|inode_number
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Quiet GCC */
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
r_int
id|len
suffix:semicolon
r_int
id|map
suffix:semicolon
r_int
id|high_sierra
suffix:semicolon
r_int
id|first_de
op_assign
l_int|1
suffix:semicolon
r_char
op_star
id|p
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Quiet GCC */
r_struct
id|iso_directory_record
op_star
id|de
suffix:semicolon
id|offset
op_assign
id|filp-&gt;f_pos
op_amp
(paren
id|bufsize
op_minus
l_int|1
)paren
suffix:semicolon
id|block
op_assign
id|filp-&gt;f_pos
op_rshift
id|bufbits
suffix:semicolon
id|high_sierra
op_assign
id|inode-&gt;i_sb-&gt;u.isofs_sb.s_high_sierra
suffix:semicolon
r_while
c_loop
(paren
id|filp-&gt;f_pos
OL
id|inode-&gt;i_size
)paren
(brace
r_int
id|de_len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|bh
op_assign
id|isofs_bread
c_func
(paren
id|inode
comma
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
l_int|0
suffix:semicolon
)brace
id|de
op_assign
(paren
r_struct
id|iso_directory_record
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
id|first_de
)paren
id|inode_number
op_assign
(paren
id|bh-&gt;b_blocknr
op_lshift
id|bufbits
)paren
op_plus
id|offset
suffix:semicolon
id|de_len
op_assign
op_star
(paren
r_int
r_char
op_star
)paren
id|de
suffix:semicolon
multiline_comment|/* If the length byte is zero, we should move on to the next&n;&t;&t;   CDROM sector.  If we are at the end of the directory, we&n;&t;&t;   kick out of the while loop. */
r_if
c_cond
(paren
id|de_len
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
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|filp-&gt;f_pos
op_assign
(paren
id|filp-&gt;f_pos
op_plus
id|ISOFS_BLOCK_SIZE
)paren
op_amp
op_complement
(paren
id|ISOFS_BLOCK_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|block
op_assign
id|filp-&gt;f_pos
op_rshift
id|bufbits
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|offset
op_add_assign
id|de_len
suffix:semicolon
multiline_comment|/* Make sure we have a full directory entry */
r_if
c_cond
(paren
id|offset
op_ge
id|bufsize
)paren
(brace
r_int
id|slop
op_assign
id|bufsize
op_minus
id|offset
op_plus
id|de_len
suffix:semicolon
id|memcpy
c_func
(paren
id|tmpde
comma
id|de
comma
id|slop
)paren
suffix:semicolon
id|offset
op_and_assign
id|bufsize
op_minus
l_int|1
suffix:semicolon
id|block
op_increment
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|offset
)paren
(brace
id|bh
op_assign
id|isofs_bread
c_func
(paren
id|inode
comma
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
l_int|0
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|tmpde
op_plus
id|slop
comma
id|bh-&gt;b_data
comma
id|offset
)paren
suffix:semicolon
)brace
id|de
op_assign
id|tmpde
suffix:semicolon
)brace
r_if
c_cond
(paren
id|de-&gt;flags
(braket
op_minus
id|high_sierra
)braket
op_amp
l_int|0x80
)paren
(brace
id|first_de
op_assign
l_int|0
suffix:semicolon
id|filp-&gt;f_pos
op_add_assign
id|de_len
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|first_de
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Handle the case of the &squot;.&squot; directory */
r_if
c_cond
(paren
id|de-&gt;name_len
(braket
l_int|0
)braket
op_eq
l_int|1
op_logical_and
id|de-&gt;name
(braket
l_int|0
)braket
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
l_string|&quot;.&quot;
comma
l_int|1
comma
id|filp-&gt;f_pos
comma
id|inode-&gt;i_ino
comma
id|DT_DIR
)paren
OL
l_int|0
)paren
r_break
suffix:semicolon
id|filp-&gt;f_pos
op_add_assign
id|de_len
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|len
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Handle the case of the &squot;..&squot; directory */
r_if
c_cond
(paren
id|de-&gt;name_len
(braket
l_int|0
)braket
op_eq
l_int|1
op_logical_and
id|de-&gt;name
(braket
l_int|0
)braket
op_eq
l_int|1
)paren
(brace
id|inode_number
op_assign
id|filp-&gt;f_dentry-&gt;d_parent-&gt;d_inode-&gt;i_ino
suffix:semicolon
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
l_string|&quot;..&quot;
comma
l_int|2
comma
id|filp-&gt;f_pos
comma
id|inode_number
comma
id|DT_DIR
)paren
OL
l_int|0
)paren
r_break
suffix:semicolon
id|filp-&gt;f_pos
op_add_assign
id|de_len
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* Handle everything else.  Do name translation if there&n;&t;&t;   is no Rock Ridge NM field. */
r_if
c_cond
(paren
id|inode-&gt;i_sb-&gt;u.isofs_sb.s_unhide
op_eq
l_char|&squot;n&squot;
)paren
(brace
multiline_comment|/* Do not report hidden or associated files */
r_if
c_cond
(paren
id|de-&gt;flags
(braket
op_minus
id|high_sierra
)braket
op_amp
l_int|5
)paren
(brace
id|filp-&gt;f_pos
op_add_assign
id|de_len
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
id|map
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_sb-&gt;u.isofs_sb.s_rock
)paren
(brace
id|len
op_assign
id|get_rock_ridge_filename
c_func
(paren
id|de
comma
id|tmpname
comma
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ne
l_int|0
)paren
(brace
multiline_comment|/* may be -1 */
id|p
op_assign
id|tmpname
suffix:semicolon
id|map
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|map
)paren
(brace
macro_line|#ifdef CONFIG_JOLIET
r_if
c_cond
(paren
id|inode-&gt;i_sb-&gt;u.isofs_sb.s_joliet_level
)paren
(brace
id|len
op_assign
id|get_joliet_filename
c_func
(paren
id|de
comma
id|tmpname
comma
id|inode
)paren
suffix:semicolon
id|p
op_assign
id|tmpname
suffix:semicolon
)brace
r_else
macro_line|#endif
r_if
c_cond
(paren
id|inode-&gt;i_sb-&gt;u.isofs_sb.s_mapping
op_eq
l_char|&squot;a&squot;
)paren
(brace
id|len
op_assign
id|get_acorn_filename
c_func
(paren
id|de
comma
id|tmpname
comma
id|inode
)paren
suffix:semicolon
id|p
op_assign
id|tmpname
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|inode-&gt;i_sb-&gt;u.isofs_sb.s_mapping
op_eq
l_char|&squot;n&squot;
)paren
(brace
id|len
op_assign
id|isofs_name_translate
c_func
(paren
id|de
comma
id|tmpname
comma
id|inode
)paren
suffix:semicolon
id|p
op_assign
id|tmpname
suffix:semicolon
)brace
r_else
(brace
id|p
op_assign
id|de-&gt;name
suffix:semicolon
id|len
op_assign
id|de-&gt;name_len
(braket
l_int|0
)braket
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|len
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
id|p
comma
id|len
comma
id|filp-&gt;f_pos
comma
id|inode_number
comma
id|DT_UNKNOWN
)paren
OL
l_int|0
)paren
r_break
suffix:semicolon
)brace
id|filp-&gt;f_pos
op_add_assign
id|de_len
suffix:semicolon
r_continue
suffix:semicolon
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Handle allocation of temporary space for name translation and&n; * handling split directory entries.. The real work is done by&n; * &quot;do_isofs_readdir()&quot;.&n; */
DECL|function|isofs_readdir
r_static
r_int
id|isofs_readdir
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
id|result
suffix:semicolon
r_char
op_star
id|tmpname
suffix:semicolon
r_struct
id|iso_directory_record
op_star
id|tmpde
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|tmpname
op_assign
(paren
r_char
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmpname
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|tmpde
op_assign
(paren
r_struct
id|iso_directory_record
op_star
)paren
(paren
id|tmpname
op_plus
l_int|1024
)paren
suffix:semicolon
id|result
op_assign
id|do_isofs_readdir
c_func
(paren
id|inode
comma
id|filp
comma
id|dirent
comma
id|filldir
comma
id|tmpname
comma
id|tmpde
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|tmpname
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
eof
