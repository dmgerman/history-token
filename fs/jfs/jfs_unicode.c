multiline_comment|/*&n; *   Copyright (c) International Business Machines Corp., 2000-2002&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &quot;jfs_types.h&quot;
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
m_wchar_t
op_star
id|from
comma
multiline_comment|/* LITTLE ENDIAN */
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
(brace
id|outlen
op_add_assign
id|charlen
suffix:semicolon
)brace
r_else
(brace
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
id|to
(braket
id|outlen
)braket
op_assign
l_int|0
suffix:semicolon
id|jEVENT
c_func
(paren
l_int|0
comma
(paren
l_string|&quot;jfs_strfromUCS returning %d - &squot;%s&squot;&bslash;n&quot;
comma
id|outlen
comma
id|to
)paren
)paren
suffix:semicolon
r_return
id|outlen
suffix:semicolon
)brace
multiline_comment|/*&n; * NAME:&t;jfs_strtoUCS()&n; *&n; * FUNCTION:&t;Convert character string to unicode string&n; *&n; */
DECL|function|jfs_strtoUCS
r_int
id|jfs_strtoUCS
c_func
(paren
m_wchar_t
op_star
id|to
comma
r_const
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
id|jEVENT
c_func
(paren
l_int|0
comma
(paren
l_string|&quot;jfs_strtoUCS - &squot;%s&squot;&bslash;n&quot;
comma
id|from
)paren
)paren
suffix:semicolon
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
id|jERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;jfs_strtoUCS: char2uni returned %d.&bslash;n&quot;
comma
id|charlen
)paren
)paren
suffix:semicolon
id|jERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;charset = %s, char = 0x%x&bslash;n&quot;
comma
id|codepage-&gt;charset
comma
(paren
r_int
r_char
)paren
op_star
id|from
)paren
)paren
suffix:semicolon
id|to
(braket
id|i
)braket
op_assign
l_int|0x003f
suffix:semicolon
multiline_comment|/* a question mark */
id|charlen
op_assign
l_int|1
suffix:semicolon
)brace
)brace
id|jEVENT
c_func
(paren
l_int|0
comma
(paren
l_string|&quot; returning %d&bslash;n&quot;
comma
id|i
)paren
)paren
suffix:semicolon
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
comma
r_struct
id|nls_table
op_star
id|nls_tab
)paren
(brace
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
r_return
l_int|0
suffix:semicolon
)brace
eof
