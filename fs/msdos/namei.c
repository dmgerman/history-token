multiline_comment|/*&n; *  linux/fs/msdos/namei.c&n; *&n; *  Written 1992,1993 by Werner Almesberger&n; *  Hidden files 1995 by Albert Cahalan &lt;albert@ccs.neu.edu&gt; &lt;adc@coe.neu.edu&gt;&n; *  Rewritten for constant inumbers 1999 by Al Viro&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
multiline_comment|/* MS-DOS &quot;device special files&quot; */
DECL|variable|reserved_names
r_static
r_const
r_int
r_char
op_star
id|reserved_names
(braket
)braket
op_assign
(brace
l_string|&quot;CON     &quot;
comma
l_string|&quot;PRN     &quot;
comma
l_string|&quot;NUL     &quot;
comma
l_string|&quot;AUX     &quot;
comma
l_string|&quot;LPT1    &quot;
comma
l_string|&quot;LPT2    &quot;
comma
l_string|&quot;LPT3    &quot;
comma
l_string|&quot;LPT4    &quot;
comma
l_string|&quot;COM1    &quot;
comma
l_string|&quot;COM2    &quot;
comma
l_string|&quot;COM3    &quot;
comma
l_string|&quot;COM4    &quot;
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/* Characters that are undesirable in an MS-DOS file name */
DECL|variable|bad_chars
r_static
r_int
r_char
id|bad_chars
(braket
)braket
op_assign
l_string|&quot;*?&lt;&gt;|&bslash;&quot;&quot;
suffix:semicolon
DECL|variable|bad_if_strict_pc
r_static
r_int
r_char
id|bad_if_strict_pc
(braket
)braket
op_assign
l_string|&quot;+=,; &quot;
suffix:semicolon
DECL|variable|bad_if_strict_atari
r_static
r_int
r_char
id|bad_if_strict_atari
(braket
)braket
op_assign
l_string|&quot; &quot;
suffix:semicolon
multiline_comment|/* GEMDOS is less restrictive */
DECL|macro|bad_if_strict
mdefine_line|#define&t;bad_if_strict(opts) ((opts)-&gt;atari ? bad_if_strict_atari : bad_if_strict_pc)
multiline_comment|/***** Formats an MS-DOS file name. Rejects invalid names. */
DECL|function|msdos_format_name
r_static
r_int
id|msdos_format_name
c_func
(paren
r_const
r_int
r_char
op_star
id|name
comma
r_int
id|len
comma
r_int
r_char
op_star
id|res
comma
r_struct
id|fat_mount_options
op_star
id|opts
)paren
multiline_comment|/* name is the proposed name, len is its length, res is&n;&t; * the resulting name, opts-&gt;name_check is either (r)elaxed,&n;&t; * (n)ormal or (s)trict, opts-&gt;dotsOK allows dots at the&n;&t; * beginning of name (for hidden files)&n;&t; */
(brace
r_int
r_char
op_star
id|walk
suffix:semicolon
r_const
r_int
r_char
op_star
op_star
id|reserved
suffix:semicolon
r_int
r_char
id|c
suffix:semicolon
r_int
id|space
suffix:semicolon
r_if
c_cond
(paren
id|name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
)paren
(brace
multiline_comment|/* dotfile because . and .. already done */
r_if
c_cond
(paren
id|opts-&gt;dotsOK
)paren
(brace
multiline_comment|/* Get rid of dot - test for it elsewhere */
id|name
op_increment
suffix:semicolon
id|len
op_decrement
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|opts-&gt;atari
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* disallow names that _really_ start with a dot for MS-DOS, GEMDOS does&n;&t; * not care */
id|space
op_assign
op_logical_neg
id|opts-&gt;atari
suffix:semicolon
id|c
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|walk
op_assign
id|res
suffix:semicolon
id|len
op_logical_and
id|walk
op_minus
id|res
OL
l_int|8
suffix:semicolon
id|walk
op_increment
)paren
(brace
id|c
op_assign
op_star
id|name
op_increment
suffix:semicolon
id|len
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|opts-&gt;name_check
op_ne
l_char|&squot;r&squot;
op_logical_and
id|strchr
c_func
(paren
id|bad_chars
comma
id|c
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|opts-&gt;name_check
op_eq
l_char|&squot;s&squot;
op_logical_and
id|strchr
c_func
(paren
id|bad_if_strict
c_func
(paren
id|opts
)paren
comma
id|c
)paren
)paren
r_return
op_minus
id|EINVAL
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
op_logical_and
id|opts-&gt;name_check
op_eq
l_char|&squot;s&squot;
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|c
OL
l_char|&squot; &squot;
op_logical_or
id|c
op_eq
l_char|&squot;:&squot;
op_logical_or
id|c
op_eq
l_char|&squot;&bslash;&bslash;&squot;
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*  0xE5 is legal as a first character, but we must substitute 0x05     */
multiline_comment|/*  because 0xE5 marks deleted files.  Yes, DOS really does this.       */
multiline_comment|/*  It seems that Microsoft hacked DOS to support non-US characters     */
multiline_comment|/*  after the 0xE5 character was already in use to mark deleted files.  */
r_if
c_cond
(paren
(paren
id|res
op_eq
id|walk
)paren
op_logical_and
(paren
id|c
op_eq
l_int|0xE5
)paren
)paren
(brace
id|c
op_assign
l_int|0x05
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;.&squot;
)paren
r_break
suffix:semicolon
id|space
op_assign
(paren
id|c
op_eq
l_char|&squot; &squot;
)paren
suffix:semicolon
op_star
id|walk
op_assign
(paren
op_logical_neg
id|opts-&gt;nocase
op_logical_and
id|c
op_ge
l_char|&squot;a&squot;
op_logical_and
id|c
op_le
l_char|&squot;z&squot;
)paren
ques
c_cond
id|c
op_minus
l_int|32
suffix:colon
id|c
suffix:semicolon
)brace
r_if
c_cond
(paren
id|space
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|opts-&gt;name_check
op_eq
l_char|&squot;s&squot;
op_logical_and
id|len
op_logical_and
id|c
op_ne
l_char|&squot;.&squot;
)paren
(brace
id|c
op_assign
op_star
id|name
op_increment
suffix:semicolon
id|len
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ne
l_char|&squot;.&squot;
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_while
c_loop
(paren
id|c
op_ne
l_char|&squot;.&squot;
op_logical_and
id|len
op_decrement
)paren
id|c
op_assign
op_star
id|name
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;.&squot;
)paren
(brace
r_while
c_loop
(paren
id|walk
op_minus
id|res
OL
l_int|8
)paren
op_star
id|walk
op_increment
op_assign
l_char|&squot; &squot;
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
op_logical_and
id|walk
op_minus
id|res
OL
id|MSDOS_NAME
)paren
(brace
id|c
op_assign
op_star
id|name
op_increment
suffix:semicolon
id|len
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|opts-&gt;name_check
op_ne
l_char|&squot;r&squot;
op_logical_and
id|strchr
c_func
(paren
id|bad_chars
comma
id|c
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|opts-&gt;name_check
op_eq
l_char|&squot;s&squot;
op_logical_and
id|strchr
c_func
(paren
id|bad_if_strict
c_func
(paren
id|opts
)paren
comma
id|c
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|c
OL
l_char|&squot; &squot;
op_logical_or
id|c
op_eq
l_char|&squot;:&squot;
op_logical_or
id|c
op_eq
l_char|&squot;&bslash;&bslash;&squot;
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;.&squot;
)paren
(brace
r_if
c_cond
(paren
id|opts-&gt;name_check
op_eq
l_char|&squot;s&squot;
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
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
op_logical_and
id|opts-&gt;name_check
op_eq
l_char|&squot;s&squot;
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|space
op_assign
id|c
op_eq
l_char|&squot; &squot;
suffix:semicolon
op_star
id|walk
op_increment
op_assign
(paren
op_logical_neg
id|opts-&gt;nocase
op_logical_and
id|c
op_ge
l_char|&squot;a&squot;
op_logical_and
id|c
op_le
l_char|&squot;z&squot;
)paren
ques
c_cond
id|c
op_minus
l_int|32
suffix:colon
id|c
suffix:semicolon
)brace
r_if
c_cond
(paren
id|space
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|opts-&gt;name_check
op_eq
l_char|&squot;s&squot;
op_logical_and
id|len
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_while
c_loop
(paren
id|walk
op_minus
id|res
OL
id|MSDOS_NAME
)paren
op_star
id|walk
op_increment
op_assign
l_char|&squot; &squot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opts-&gt;atari
)paren
multiline_comment|/* GEMDOS is less stupid and has no reserved names */
r_for
c_loop
(paren
id|reserved
op_assign
id|reserved_names
suffix:semicolon
op_star
id|reserved
suffix:semicolon
id|reserved
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|res
comma
op_star
id|reserved
comma
l_int|8
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/***** Locates a directory entry.  Uses unformatted name. */
DECL|function|msdos_find
r_static
r_int
id|msdos_find
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_const
r_int
r_char
op_star
id|name
comma
r_int
id|len
comma
r_struct
id|buffer_head
op_star
op_star
id|bh
comma
r_struct
id|msdos_dir_entry
op_star
op_star
id|de
comma
id|loff_t
op_star
id|i_pos
)paren
(brace
r_int
r_char
id|msdos_name
(braket
id|MSDOS_NAME
)braket
suffix:semicolon
r_char
id|dotsOK
suffix:semicolon
r_int
id|res
suffix:semicolon
id|dotsOK
op_assign
id|MSDOS_SB
c_func
(paren
id|dir-&gt;i_sb
)paren
op_member_access_from_pointer
id|options.dotsOK
suffix:semicolon
id|res
op_assign
id|msdos_format_name
c_func
(paren
id|name
comma
id|len
comma
id|msdos_name
comma
op_amp
id|MSDOS_SB
c_func
(paren
id|dir-&gt;i_sb
)paren
op_member_access_from_pointer
id|options
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
id|res
op_assign
id|fat_scan
c_func
(paren
id|dir
comma
id|msdos_name
comma
id|bh
comma
id|de
comma
id|i_pos
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
op_logical_and
id|dotsOK
)paren
(brace
r_if
c_cond
(paren
id|name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
op_star
id|de
)paren
op_member_access_from_pointer
id|attr
op_amp
id|ATTR_HIDDEN
)paren
)paren
id|res
op_assign
op_minus
id|ENOENT
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
op_star
id|de
)paren
op_member_access_from_pointer
id|attr
op_amp
id|ATTR_HIDDEN
)paren
id|res
op_assign
op_minus
id|ENOENT
suffix:semicolon
)brace
)brace
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/*&n; * Compute the hash for the msdos name corresponding to the dentry.&n; * Note: if the name is invalid, we leave the hash code unchanged so&n; * that the existing dentry can be used. The msdos fs routines will&n; * return ENOENT or EINVAL as appropriate.&n; */
DECL|function|msdos_hash
r_static
r_int
id|msdos_hash
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|qstr
op_star
id|qstr
)paren
(brace
r_struct
id|fat_mount_options
op_star
id|options
op_assign
op_amp
(paren
id|MSDOS_SB
c_func
(paren
id|dentry-&gt;d_sb
)paren
op_member_access_from_pointer
id|options
)paren
suffix:semicolon
r_int
r_char
id|msdos_name
(braket
id|MSDOS_NAME
)braket
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
id|msdos_format_name
c_func
(paren
id|qstr-&gt;name
comma
id|qstr-&gt;len
comma
id|msdos_name
comma
id|options
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|qstr-&gt;hash
op_assign
id|full_name_hash
c_func
(paren
id|msdos_name
comma
id|MSDOS_NAME
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Compare two msdos names. If either of the names are invalid,&n; * we fall back to doing the standard name comparison.&n; */
DECL|function|msdos_cmp
r_static
r_int
id|msdos_cmp
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|qstr
op_star
id|a
comma
r_struct
id|qstr
op_star
id|b
)paren
(brace
r_struct
id|fat_mount_options
op_star
id|options
op_assign
op_amp
(paren
id|MSDOS_SB
c_func
(paren
id|dentry-&gt;d_sb
)paren
op_member_access_from_pointer
id|options
)paren
suffix:semicolon
r_int
r_char
id|a_msdos_name
(braket
id|MSDOS_NAME
)braket
comma
id|b_msdos_name
(braket
id|MSDOS_NAME
)braket
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
id|msdos_format_name
c_func
(paren
id|a-&gt;name
comma
id|a-&gt;len
comma
id|a_msdos_name
comma
id|options
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|old_compare
suffix:semicolon
id|error
op_assign
id|msdos_format_name
c_func
(paren
id|b-&gt;name
comma
id|b-&gt;len
comma
id|b_msdos_name
comma
id|options
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|old_compare
suffix:semicolon
id|error
op_assign
id|memcmp
c_func
(paren
id|a_msdos_name
comma
id|b_msdos_name
comma
id|MSDOS_NAME
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
id|old_compare
suffix:colon
id|error
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|a-&gt;len
op_eq
id|b-&gt;len
)paren
id|error
op_assign
id|memcmp
c_func
(paren
id|a-&gt;name
comma
id|b-&gt;name
comma
id|a-&gt;len
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|variable|msdos_dentry_operations
r_static
r_struct
id|dentry_operations
id|msdos_dentry_operations
op_assign
(brace
dot
id|d_hash
op_assign
id|msdos_hash
comma
dot
id|d_compare
op_assign
id|msdos_cmp
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * AV. Wrappers for FAT sb operations. Is it wise?&n; */
multiline_comment|/***** Get inode using directory and name */
DECL|function|msdos_lookup
r_static
r_struct
id|dentry
op_star
id|msdos_lookup
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
comma
r_struct
id|nameidata
op_star
id|nd
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
id|inode
op_star
id|inode
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|msdos_dir_entry
op_star
id|de
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|loff_t
id|i_pos
suffix:semicolon
r_int
id|res
suffix:semicolon
id|dentry-&gt;d_op
op_assign
op_amp
id|msdos_dentry_operations
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|res
op_assign
id|msdos_find
c_func
(paren
id|dir
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
comma
op_amp
id|bh
comma
op_amp
id|de
comma
op_amp
id|i_pos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
op_eq
op_minus
id|ENOENT
)paren
r_goto
id|add
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|inode
op_assign
id|fat_build_inode
c_func
(paren
id|sb
comma
id|de
comma
id|i_pos
comma
op_amp
id|res
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_goto
id|out
suffix:semicolon
id|add
suffix:colon
id|res
op_assign
l_int|0
suffix:semicolon
id|dentry
op_assign
id|d_splice_alias
c_func
(paren
id|inode
comma
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dentry
)paren
id|dentry-&gt;d_op
op_assign
op_amp
id|msdos_dentry_operations
suffix:semicolon
id|out
suffix:colon
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
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
r_return
id|dentry
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|res
)paren
suffix:semicolon
)brace
multiline_comment|/***** Creates a directory entry (name is already formatted). */
DECL|function|msdos_add_entry
r_static
r_int
id|msdos_add_entry
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_const
r_int
r_char
op_star
id|name
comma
r_struct
id|buffer_head
op_star
op_star
id|bh
comma
r_struct
id|msdos_dir_entry
op_star
op_star
id|de
comma
id|loff_t
op_star
id|i_pos
comma
r_int
id|is_dir
comma
r_int
id|is_hid
)paren
(brace
r_int
id|res
suffix:semicolon
id|res
op_assign
id|fat_add_entries
c_func
(paren
id|dir
comma
l_int|1
comma
id|bh
comma
id|de
comma
id|i_pos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
r_return
id|res
suffix:semicolon
multiline_comment|/*&n;&t; * XXX all times should be set by caller upon successful completion.&n;&t; */
id|dir-&gt;i_ctime
op_assign
id|dir-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
op_star
id|de
)paren
op_member_access_from_pointer
id|name
comma
id|name
comma
id|MSDOS_NAME
)paren
suffix:semicolon
(paren
op_star
id|de
)paren
op_member_access_from_pointer
id|attr
op_assign
id|is_dir
ques
c_cond
id|ATTR_DIR
suffix:colon
id|ATTR_ARCH
suffix:semicolon
r_if
c_cond
(paren
id|is_hid
)paren
(paren
op_star
id|de
)paren
op_member_access_from_pointer
id|attr
op_or_assign
id|ATTR_HIDDEN
suffix:semicolon
(paren
op_star
id|de
)paren
op_member_access_from_pointer
id|start
op_assign
l_int|0
suffix:semicolon
(paren
op_star
id|de
)paren
op_member_access_from_pointer
id|starthi
op_assign
l_int|0
suffix:semicolon
id|fat_date_unix2dos
c_func
(paren
id|dir-&gt;i_mtime.tv_sec
comma
op_amp
(paren
op_star
id|de
)paren
op_member_access_from_pointer
id|time
comma
op_amp
(paren
op_star
id|de
)paren
op_member_access_from_pointer
id|date
)paren
suffix:semicolon
(paren
op_star
id|de
)paren
op_member_access_from_pointer
id|size
op_assign
l_int|0
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
op_star
id|bh
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/***** Create a file */
DECL|function|msdos_create
r_static
r_int
id|msdos_create
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
comma
r_int
id|mode
comma
r_struct
id|nameidata
op_star
id|nd
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
id|bh
suffix:semicolon
r_struct
id|msdos_dir_entry
op_star
id|de
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|loff_t
id|i_pos
suffix:semicolon
r_int
id|res
comma
id|is_hid
suffix:semicolon
r_int
r_char
id|msdos_name
(braket
id|MSDOS_NAME
)braket
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|res
op_assign
id|msdos_format_name
c_func
(paren
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
comma
id|msdos_name
comma
op_amp
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|options
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
id|is_hid
op_assign
(paren
id|dentry-&gt;d_name.name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
)paren
op_logical_and
(paren
id|msdos_name
(braket
l_int|0
)braket
op_ne
l_char|&squot;.&squot;
)paren
suffix:semicolon
multiline_comment|/* Have to do it due to foo vs. .foo conflicts */
r_if
c_cond
(paren
id|fat_scan
c_func
(paren
id|dir
comma
id|msdos_name
comma
op_amp
id|bh
comma
op_amp
id|de
comma
op_amp
id|i_pos
)paren
op_ge
l_int|0
)paren
(brace
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
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|inode
op_assign
l_int|NULL
suffix:semicolon
id|res
op_assign
id|msdos_add_entry
c_func
(paren
id|dir
comma
id|msdos_name
comma
op_amp
id|bh
comma
op_amp
id|de
comma
op_amp
id|i_pos
comma
l_int|0
comma
id|is_hid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
id|inode
op_assign
id|fat_build_inode
c_func
(paren
id|dir-&gt;i_sb
comma
id|de
comma
id|i_pos
comma
op_amp
id|res
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
op_logical_neg
id|inode
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_atime
op_assign
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
id|d_instantiate
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/***** Remove a directory */
DECL|function|msdos_rmdir
r_static
r_int
id|msdos_rmdir
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
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|loff_t
id|i_pos
suffix:semicolon
r_int
id|res
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|msdos_dir_entry
op_star
id|de
suffix:semicolon
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|res
op_assign
id|msdos_find
c_func
(paren
id|dir
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
comma
op_amp
id|bh
comma
op_amp
id|de
comma
op_amp
id|i_pos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
r_goto
id|rmdir_done
suffix:semicolon
multiline_comment|/*&n;&t; * Check whether the directory is not in use, then check&n;&t; * whether it is empty.&n;&t; */
id|res
op_assign
id|fat_dir_empty
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_goto
id|rmdir_done
suffix:semicolon
id|de-&gt;name
(braket
l_int|0
)braket
op_assign
id|DELETED_FLAG
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|fat_detach
c_func
(paren
id|inode
)paren
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|dir-&gt;i_ctime
op_assign
id|dir-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|dir-&gt;i_nlink
op_decrement
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
)paren
suffix:semicolon
id|res
op_assign
l_int|0
suffix:semicolon
id|rmdir_done
suffix:colon
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
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/***** Make a directory */
DECL|function|msdos_mkdir
r_static
r_int
id|msdos_mkdir
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
comma
r_int
id|mode
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
id|bh
suffix:semicolon
r_struct
id|msdos_dir_entry
op_star
id|de
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|res
comma
id|is_hid
suffix:semicolon
r_int
r_char
id|msdos_name
(braket
id|MSDOS_NAME
)braket
suffix:semicolon
id|loff_t
id|i_pos
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|res
op_assign
id|msdos_format_name
c_func
(paren
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
comma
id|msdos_name
comma
op_amp
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|options
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
id|is_hid
op_assign
(paren
id|dentry-&gt;d_name.name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
)paren
op_logical_and
(paren
id|msdos_name
(braket
l_int|0
)braket
op_ne
l_char|&squot;.&squot;
)paren
suffix:semicolon
multiline_comment|/* foo vs .foo situation */
r_if
c_cond
(paren
id|fat_scan
c_func
(paren
id|dir
comma
id|msdos_name
comma
op_amp
id|bh
comma
op_amp
id|de
comma
op_amp
id|i_pos
)paren
op_ge
l_int|0
)paren
r_goto
id|out_exist
suffix:semicolon
id|res
op_assign
id|msdos_add_entry
c_func
(paren
id|dir
comma
id|msdos_name
comma
op_amp
id|bh
comma
op_amp
id|de
comma
op_amp
id|i_pos
comma
l_int|1
comma
id|is_hid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_goto
id|out_unlock
suffix:semicolon
id|inode
op_assign
id|fat_build_inode
c_func
(paren
id|dir-&gt;i_sb
comma
id|de
comma
id|i_pos
comma
op_amp
id|res
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
)brace
id|res
op_assign
l_int|0
suffix:semicolon
id|dir-&gt;i_nlink
op_increment
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* no need to mark them dirty */
id|res
op_assign
id|fat_new_dir
c_func
(paren
id|inode
comma
id|dir
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_goto
id|mkdir_error
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|d_instantiate
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
id|res
op_assign
l_int|0
suffix:semicolon
id|out_unlock
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
id|mkdir_error
suffix:colon
id|inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|dir-&gt;i_ctime
op_assign
id|dir-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|dir-&gt;i_nlink
op_decrement
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
)paren
suffix:semicolon
id|de-&gt;name
(braket
l_int|0
)braket
op_assign
id|DELETED_FLAG
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
id|fat_detach
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
r_goto
id|out_unlock
suffix:semicolon
id|out_exist
suffix:colon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|res
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
)brace
multiline_comment|/***** Unlink a file */
DECL|function|msdos_unlink
r_static
r_int
id|msdos_unlink
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
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|loff_t
id|i_pos
suffix:semicolon
r_int
id|res
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|msdos_dir_entry
op_star
id|de
suffix:semicolon
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|res
op_assign
id|msdos_find
c_func
(paren
id|dir
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
comma
op_amp
id|bh
comma
op_amp
id|de
comma
op_amp
id|i_pos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
r_goto
id|unlink_done
suffix:semicolon
id|de-&gt;name
(braket
l_int|0
)braket
op_assign
id|DELETED_FLAG
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|fat_detach
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
id|inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|dir-&gt;i_ctime
op_assign
id|dir-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
)paren
suffix:semicolon
id|res
op_assign
l_int|0
suffix:semicolon
id|unlink_done
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|do_msdos_rename
r_static
r_int
id|do_msdos_rename
c_func
(paren
r_struct
id|inode
op_star
id|old_dir
comma
r_int
r_char
op_star
id|old_name
comma
r_struct
id|dentry
op_star
id|old_dentry
comma
r_struct
id|inode
op_star
id|new_dir
comma
r_int
r_char
op_star
id|new_name
comma
r_struct
id|dentry
op_star
id|new_dentry
comma
r_struct
id|buffer_head
op_star
id|old_bh
comma
r_struct
id|msdos_dir_entry
op_star
id|old_de
comma
id|loff_t
id|old_i_pos
comma
r_int
id|is_hid
)paren
(brace
r_struct
id|buffer_head
op_star
id|new_bh
op_assign
l_int|NULL
comma
op_star
id|dotdot_bh
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|msdos_dir_entry
op_star
id|new_de
comma
op_star
id|dotdot_de
suffix:semicolon
r_struct
id|inode
op_star
id|old_inode
comma
op_star
id|new_inode
suffix:semicolon
id|loff_t
id|new_i_pos
comma
id|dotdot_i_pos
suffix:semicolon
r_int
id|error
suffix:semicolon
r_int
id|is_dir
suffix:semicolon
id|old_inode
op_assign
id|old_dentry-&gt;d_inode
suffix:semicolon
id|new_inode
op_assign
id|new_dentry-&gt;d_inode
suffix:semicolon
id|is_dir
op_assign
id|S_ISDIR
c_func
(paren
id|old_inode-&gt;i_mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fat_scan
c_func
(paren
id|new_dir
comma
id|new_name
comma
op_amp
id|new_bh
comma
op_amp
id|new_de
comma
op_amp
id|new_i_pos
)paren
op_ge
l_int|0
op_logical_and
op_logical_neg
id|new_inode
)paren
r_goto
id|degenerate_case
suffix:semicolon
r_if
c_cond
(paren
id|is_dir
)paren
(brace
r_if
c_cond
(paren
id|new_inode
)paren
(brace
id|error
op_assign
id|fat_dir_empty
c_func
(paren
id|new_inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fat_scan
c_func
(paren
id|old_inode
comma
id|MSDOS_DOTDOT
comma
op_amp
id|dotdot_bh
comma
op_amp
id|dotdot_de
comma
op_amp
id|dotdot_i_pos
)paren
OL
l_int|0
)paren
(brace
id|error
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|new_bh
)paren
(brace
id|error
op_assign
id|msdos_add_entry
c_func
(paren
id|new_dir
comma
id|new_name
comma
op_amp
id|new_bh
comma
op_amp
id|new_de
comma
op_amp
id|new_i_pos
comma
id|is_dir
comma
id|is_hid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
)brace
id|new_dir-&gt;i_version
op_increment
suffix:semicolon
multiline_comment|/* There we go */
r_if
c_cond
(paren
id|new_inode
)paren
id|fat_detach
c_func
(paren
id|new_inode
)paren
suffix:semicolon
id|old_de-&gt;name
(braket
l_int|0
)braket
op_assign
id|DELETED_FLAG
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|old_bh
)paren
suffix:semicolon
id|fat_detach
c_func
(paren
id|old_inode
)paren
suffix:semicolon
id|fat_attach
c_func
(paren
id|old_inode
comma
id|new_i_pos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_hid
)paren
id|MSDOS_I
c_func
(paren
id|old_inode
)paren
op_member_access_from_pointer
id|i_attrs
op_or_assign
id|ATTR_HIDDEN
suffix:semicolon
r_else
id|MSDOS_I
c_func
(paren
id|old_inode
)paren
op_member_access_from_pointer
id|i_attrs
op_and_assign
op_complement
id|ATTR_HIDDEN
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|old_inode
)paren
suffix:semicolon
id|old_dir-&gt;i_version
op_increment
suffix:semicolon
id|old_dir-&gt;i_ctime
op_assign
id|old_dir-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|old_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_inode
)paren
(brace
id|new_inode-&gt;i_nlink
op_decrement
suffix:semicolon
id|new_inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|new_inode
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dotdot_bh
)paren
(brace
id|dotdot_de-&gt;start
op_assign
id|cpu_to_le16
c_func
(paren
id|MSDOS_I
c_func
(paren
id|new_dir
)paren
op_member_access_from_pointer
id|i_logstart
)paren
suffix:semicolon
id|dotdot_de-&gt;starthi
op_assign
id|cpu_to_le16
c_func
(paren
(paren
id|MSDOS_I
c_func
(paren
id|new_dir
)paren
op_member_access_from_pointer
id|i_logstart
)paren
op_rshift
l_int|16
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|dotdot_bh
)paren
suffix:semicolon
id|old_dir-&gt;i_nlink
op_decrement
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|old_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_inode
)paren
(brace
id|new_inode-&gt;i_nlink
op_decrement
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|new_inode
)paren
suffix:semicolon
)brace
r_else
(brace
id|new_dir-&gt;i_nlink
op_increment
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|new_dir
)paren
suffix:semicolon
)brace
)brace
id|error
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
id|brelse
c_func
(paren
id|new_bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|dotdot_bh
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
id|degenerate_case
suffix:colon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|new_de
op_ne
id|old_de
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|is_hid
)paren
id|MSDOS_I
c_func
(paren
id|old_inode
)paren
op_member_access_from_pointer
id|i_attrs
op_or_assign
id|ATTR_HIDDEN
suffix:semicolon
r_else
id|MSDOS_I
c_func
(paren
id|old_inode
)paren
op_member_access_from_pointer
id|i_attrs
op_and_assign
op_complement
id|ATTR_HIDDEN
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|old_inode
)paren
suffix:semicolon
id|old_dir-&gt;i_version
op_increment
suffix:semicolon
id|old_dir-&gt;i_ctime
op_assign
id|old_dir-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|old_dir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/***** Rename, a wrapper for rename_same_dir &amp; rename_diff_dir */
DECL|function|msdos_rename
r_static
r_int
id|msdos_rename
c_func
(paren
r_struct
id|inode
op_star
id|old_dir
comma
r_struct
id|dentry
op_star
id|old_dentry
comma
r_struct
id|inode
op_star
id|new_dir
comma
r_struct
id|dentry
op_star
id|new_dentry
)paren
(brace
r_struct
id|buffer_head
op_star
id|old_bh
suffix:semicolon
r_struct
id|msdos_dir_entry
op_star
id|old_de
suffix:semicolon
id|loff_t
id|old_i_pos
suffix:semicolon
r_int
id|error
comma
id|is_hid
comma
id|old_hid
suffix:semicolon
multiline_comment|/* if new file and old file are hidden */
r_int
r_char
id|old_msdos_name
(braket
id|MSDOS_NAME
)braket
comma
id|new_msdos_name
(braket
id|MSDOS_NAME
)braket
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|error
op_assign
id|msdos_format_name
c_func
(paren
id|old_dentry-&gt;d_name.name
comma
id|old_dentry-&gt;d_name.len
comma
id|old_msdos_name
comma
op_amp
id|MSDOS_SB
c_func
(paren
id|old_dir-&gt;i_sb
)paren
op_member_access_from_pointer
id|options
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_goto
id|rename_done
suffix:semicolon
id|error
op_assign
id|msdos_format_name
c_func
(paren
id|new_dentry-&gt;d_name.name
comma
id|new_dentry-&gt;d_name.len
comma
id|new_msdos_name
comma
op_amp
id|MSDOS_SB
c_func
(paren
id|new_dir-&gt;i_sb
)paren
op_member_access_from_pointer
id|options
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_goto
id|rename_done
suffix:semicolon
id|is_hid
op_assign
(paren
id|new_dentry-&gt;d_name.name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
)paren
op_logical_and
(paren
id|new_msdos_name
(braket
l_int|0
)braket
op_ne
l_char|&squot;.&squot;
)paren
suffix:semicolon
id|old_hid
op_assign
(paren
id|old_dentry-&gt;d_name.name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
)paren
op_logical_and
(paren
id|old_msdos_name
(braket
l_int|0
)braket
op_ne
l_char|&squot;.&squot;
)paren
suffix:semicolon
id|error
op_assign
id|fat_scan
c_func
(paren
id|old_dir
comma
id|old_msdos_name
comma
op_amp
id|old_bh
comma
op_amp
id|old_de
comma
op_amp
id|old_i_pos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_goto
id|rename_done
suffix:semicolon
id|error
op_assign
id|do_msdos_rename
c_func
(paren
id|old_dir
comma
id|old_msdos_name
comma
id|old_dentry
comma
id|new_dir
comma
id|new_msdos_name
comma
id|new_dentry
comma
id|old_bh
comma
id|old_de
comma
id|old_i_pos
comma
id|is_hid
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|old_bh
)paren
suffix:semicolon
id|rename_done
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|variable|msdos_dir_inode_operations
r_static
r_struct
id|inode_operations
id|msdos_dir_inode_operations
op_assign
(brace
dot
id|create
op_assign
id|msdos_create
comma
dot
id|lookup
op_assign
id|msdos_lookup
comma
dot
id|unlink
op_assign
id|msdos_unlink
comma
dot
id|mkdir
op_assign
id|msdos_mkdir
comma
dot
id|rmdir
op_assign
id|msdos_rmdir
comma
dot
id|rename
op_assign
id|msdos_rename
comma
dot
id|setattr
op_assign
id|fat_notify_change
comma
)brace
suffix:semicolon
DECL|function|msdos_fill_super
r_static
r_int
id|msdos_fill_super
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
r_int
id|res
suffix:semicolon
id|res
op_assign
id|fat_fill_super
c_func
(paren
id|sb
comma
id|data
comma
id|silent
comma
op_amp
id|msdos_dir_inode_operations
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_return
id|res
suffix:semicolon
id|sb-&gt;s_root-&gt;d_op
op_assign
op_amp
id|msdos_dentry_operations
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|msdos_get_sb
r_static
r_struct
id|super_block
op_star
id|msdos_get_sb
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
r_const
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
id|msdos_fill_super
)paren
suffix:semicolon
)brace
DECL|variable|msdos_fs_type
r_static
r_struct
id|file_system_type
id|msdos_fs_type
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;msdos&quot;
comma
dot
id|get_sb
op_assign
id|msdos_get_sb
comma
dot
id|kill_sb
op_assign
id|kill_block_super
comma
dot
id|fs_flags
op_assign
id|FS_REQUIRES_DEV
comma
)brace
suffix:semicolon
DECL|function|init_msdos_fs
r_static
r_int
id|__init
id|init_msdos_fs
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
id|msdos_fs_type
)paren
suffix:semicolon
)brace
DECL|function|exit_msdos_fs
r_static
r_void
id|__exit
id|exit_msdos_fs
c_func
(paren
r_void
)paren
(brace
id|unregister_filesystem
c_func
(paren
op_amp
id|msdos_fs_type
)paren
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Werner Almesberger&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MS-DOS filesystem support&quot;
)paren
suffix:semicolon
id|module_init
c_func
(paren
id|init_msdos_fs
)paren
id|module_exit
c_func
(paren
id|exit_msdos_fs
)paren
eof
