multiline_comment|/*&n; *   Copyright (C) International Business Machines Corp., 2000-2004&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &quot;jfs_incore.h&quot;
macro_line|#include &quot;jfs_filsys.h&quot;
macro_line|#include &quot;jfs_unicode.h&quot;
macro_line|#include &quot;jfs_debug.h&quot;
multiline_comment|/*&n; * NAME:&t;jfs_strfromUCS()&n; *&n; * FUNCTION:&t;Convert little-endian unicode string to character string&n; *&n; */
DECL|function|jfs_strfromUCS_le
r_int
id|jfs_strfromUCS_le
c_func
(paren
r_char
op_star
id|to
comma
r_const
id|__le16
op_star
id|from
comma
r_int
id|len
comma
r_struct
id|nls_table
op_star
id|codepage
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|outlen
op_assign
l_int|0
suffix:semicolon
r_static
r_int
id|warn_again
op_assign
l_int|5
suffix:semicolon
multiline_comment|/* Only warn up to 5 times total */
r_int
id|warn
op_assign
op_logical_neg
op_logical_neg
id|warn_again
suffix:semicolon
multiline_comment|/* once per string */
r_if
c_cond
(paren
id|codepage
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|i
OL
id|len
)paren
op_logical_and
id|from
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|charlen
suffix:semicolon
id|charlen
op_assign
id|codepage
op_member_access_from_pointer
id|uni2char
c_func
(paren
id|le16_to_cpu
c_func
(paren
id|from
(braket
id|i
)braket
)paren
comma
op_amp
id|to
(braket
id|outlen
)braket
comma
id|NLS_MAX_CHARSET_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|charlen
OG
l_int|0
)paren
id|outlen
op_add_assign
id|charlen
suffix:semicolon
r_else
id|to
(braket
id|outlen
op_increment
)braket
op_assign
l_char|&squot;?&squot;
suffix:semicolon
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
(paren
id|i
OL
id|len
)paren
op_logical_and
id|from
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|le16_to_cpu
c_func
(paren
id|from
(braket
id|i
)braket
)paren
op_amp
l_int|0xff00
)paren
(brace
r_if
c_cond
(paren
id|warn
)paren
(brace
id|warn
op_decrement
suffix:semicolon
id|warn_again
op_decrement
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;non-latin1 character 0x%x found in JFS file name&bslash;n&quot;
comma
id|le16_to_cpu
c_func
(paren
id|from
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;mount with iocharset=utf8 to access&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|to
(braket
id|i
)braket
op_assign
l_char|&squot;?&squot;
suffix:semicolon
)brace
r_else
id|to
(braket
id|i
)braket
op_assign
(paren
r_char
)paren
(paren
id|le16_to_cpu
c_func
(paren
id|from
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
)brace
id|outlen
op_assign
id|i
suffix:semicolon
)brace
id|to
(braket
id|outlen
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|outlen
suffix:semicolon
)brace
multiline_comment|/*&n; * NAME:&t;jfs_strtoUCS()&n; *&n; * FUNCTION:&t;Convert character string to unicode string&n; *&n; */
DECL|function|jfs_strtoUCS
r_static
r_int
id|jfs_strtoUCS
c_func
(paren
m_wchar_t
op_star
id|to
comma
r_const
r_int
r_char
op_star
id|from
comma
r_int
id|len
comma
r_struct
id|nls_table
op_star
id|codepage
)paren
(brace
r_int
id|charlen
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|codepage
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|len
op_logical_and
op_star
id|from
suffix:semicolon
id|i
op_increment
comma
id|from
op_add_assign
id|charlen
comma
id|len
op_sub_assign
id|charlen
)paren
(brace
id|charlen
op_assign
id|codepage
op_member_access_from_pointer
id|char2uni
c_func
(paren
id|from
comma
id|len
comma
op_amp
id|to
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|charlen
OL
l_int|1
)paren
(brace
id|jfs_err
c_func
(paren
l_string|&quot;jfs_strtoUCS: char2uni returned %d.&quot;
comma
id|charlen
)paren
suffix:semicolon
id|jfs_err
c_func
(paren
l_string|&quot;charset = %s, char = 0x%x&quot;
comma
id|codepage-&gt;charset
comma
op_star
id|from
)paren
suffix:semicolon
r_return
id|charlen
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
(paren
id|i
OL
id|len
)paren
op_logical_and
id|from
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
id|to
(braket
id|i
)braket
op_assign
(paren
m_wchar_t
)paren
id|from
(braket
id|i
)braket
suffix:semicolon
)brace
id|to
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
multiline_comment|/*&n; * NAME:&t;get_UCSname()&n; *&n; * FUNCTION:&t;Allocate and translate to unicode string&n; *&n; */
DECL|function|get_UCSname
r_int
id|get_UCSname
c_func
(paren
r_struct
id|component_name
op_star
id|uniName
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_struct
id|nls_table
op_star
id|nls_tab
op_assign
id|JFS_SBI
c_func
(paren
id|dentry-&gt;d_sb
)paren
op_member_access_from_pointer
id|nls_tab
suffix:semicolon
r_int
id|length
op_assign
id|dentry-&gt;d_name.len
suffix:semicolon
r_if
c_cond
(paren
id|length
OG
id|JFS_NAME_MAX
)paren
r_return
op_minus
id|ENAMETOOLONG
suffix:semicolon
id|uniName-&gt;name
op_assign
id|kmalloc
c_func
(paren
(paren
id|length
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
m_wchar_t
)paren
comma
id|GFP_NOFS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|uniName-&gt;name
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOSPC
suffix:semicolon
id|uniName-&gt;namlen
op_assign
id|jfs_strtoUCS
c_func
(paren
id|uniName-&gt;name
comma
id|dentry-&gt;d_name.name
comma
id|length
comma
id|nls_tab
)paren
suffix:semicolon
r_if
c_cond
(paren
id|uniName-&gt;namlen
OL
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|uniName-&gt;name
)paren
suffix:semicolon
r_return
id|uniName-&gt;namlen
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
