multiline_comment|/*&n; *  linux/fs/hpfs/dentry.c&n; *&n; *  Mikulas Patocka (mikulas@artax.karlin.mff.cuni.cz), 1998-1999&n; *&n; *  dcache operations&n; */
macro_line|#include &quot;hpfs_fn.h&quot;
multiline_comment|/*&n; * Note: the dentry argument is the parent dentry.&n; */
DECL|function|hpfs_hash_dentry
r_int
id|hpfs_hash_dentry
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
r_int
r_int
id|hash
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|l
op_assign
id|qstr-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|l
op_eq
l_int|1
)paren
r_if
c_cond
(paren
id|qstr-&gt;name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
)paren
r_goto
id|x
suffix:semicolon
r_if
c_cond
(paren
id|l
op_eq
l_int|2
)paren
r_if
c_cond
(paren
id|qstr-&gt;name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
op_logical_or
id|qstr-&gt;name
(braket
l_int|1
)braket
op_eq
l_char|&squot;.&squot;
)paren
r_goto
id|x
suffix:semicolon
id|hpfs_adjust_length
c_func
(paren
(paren
r_char
op_star
)paren
id|qstr-&gt;name
comma
op_amp
id|l
)paren
suffix:semicolon
multiline_comment|/*if (hpfs_chk_name((char *)qstr-&gt;name,&amp;l))*/
multiline_comment|/*return -ENAMETOOLONG;*/
multiline_comment|/*return -ENOENT;*/
id|x
suffix:colon
id|hash
op_assign
id|init_name_hash
c_func
(paren
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
id|l
suffix:semicolon
id|i
op_increment
)paren
id|hash
op_assign
id|partial_name_hash
c_func
(paren
id|hpfs_upcase
c_func
(paren
id|hpfs_sb
c_func
(paren
id|dentry-&gt;d_sb
)paren
op_member_access_from_pointer
id|sb_cp_table
comma
id|qstr-&gt;name
(braket
id|i
)braket
)paren
comma
id|hash
)paren
suffix:semicolon
id|qstr-&gt;hash
op_assign
id|end_name_hash
c_func
(paren
id|hash
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hpfs_compare_dentry
r_int
id|hpfs_compare_dentry
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
r_int
id|al
op_assign
id|a-&gt;len
suffix:semicolon
r_int
id|bl
op_assign
id|b-&gt;len
suffix:semicolon
id|hpfs_adjust_length
c_func
(paren
(paren
r_char
op_star
)paren
id|a-&gt;name
comma
op_amp
id|al
)paren
suffix:semicolon
multiline_comment|/*hpfs_adjust_length((char *)b-&gt;name, &amp;bl);*/
multiline_comment|/* &squot;a&squot; is the qstr of an already existing dentry, so the name&n;&t; * must be valid. &squot;b&squot; must be validated first.&n;&t; */
r_if
c_cond
(paren
id|hpfs_chk_name
c_func
(paren
(paren
r_char
op_star
)paren
id|b-&gt;name
comma
op_amp
id|bl
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|hpfs_compare_names
c_func
(paren
id|dentry-&gt;d_sb
comma
(paren
r_char
op_star
)paren
id|a-&gt;name
comma
id|al
comma
(paren
r_char
op_star
)paren
id|b-&gt;name
comma
id|bl
comma
l_int|0
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|hpfs_dentry_operations
r_struct
id|dentry_operations
id|hpfs_dentry_operations
op_assign
(brace
id|d_hash
suffix:colon
id|hpfs_hash_dentry
comma
id|d_compare
suffix:colon
id|hpfs_compare_dentry
comma
)brace
suffix:semicolon
DECL|function|hpfs_set_dentry_operations
r_void
id|hpfs_set_dentry_operations
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
id|dentry-&gt;d_op
op_assign
op_amp
id|hpfs_dentry_operations
suffix:semicolon
)brace
eof
