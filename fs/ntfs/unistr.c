multiline_comment|/*&n; * $Id: unistr.c,v 1.4 2001/04/08 03:02:55 antona Exp $&n; *&n; * unistr.c - Unicode string handling. Part of the Linux-NTFS project.&n; *&n; * Copyright (c) 2000,2001 Anton Altaparmakov.&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be &n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty &n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS &n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &quot;unistr.h&quot;
macro_line|#include &quot;macros.h&quot;
multiline_comment|/*&n; * This is used by the name collation functions to quickly determine what&n; * characters are (in)valid.&n; */
DECL|variable|legal_ansi_char_array
r_const
id|__u8
id|legal_ansi_char_array
(braket
l_int|0x40
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x10
comma
l_int|0x17
comma
l_int|0x07
comma
l_int|0x18
comma
l_int|0x17
comma
l_int|0x17
comma
l_int|0x17
comma
l_int|0x17
comma
l_int|0x17
comma
l_int|0x17
comma
l_int|0x17
comma
l_int|0x18
comma
l_int|0x16
comma
l_int|0x16
comma
l_int|0x17
comma
l_int|0x07
comma
l_int|0x00
comma
l_int|0x17
comma
l_int|0x17
comma
l_int|0x17
comma
l_int|0x17
comma
l_int|0x17
comma
l_int|0x17
comma
l_int|0x17
comma
l_int|0x17
comma
l_int|0x17
comma
l_int|0x17
comma
l_int|0x04
comma
l_int|0x16
comma
l_int|0x18
comma
l_int|0x16
comma
l_int|0x18
comma
l_int|0x18
comma
)brace
suffix:semicolon
multiline_comment|/**&n; * ntfs_are_names_equal - compare two Unicode names for equality&n; * @s1:&t;&t;&t;name to compare to @s2&n; * @s1_len:&t;&t;length in Unicode characters of @s1&n; * @s2:&t;&t;&t;name to compare to @s1&n; * @s2_len:&t;&t;length in Unicode characters of @s2&n; * @ic:&t;&t;&t;ignore case bool&n; * @upcase:&t;&t;upcase table (only if @ic == IGNORE_CASE)&n; * @upcase_size:&t;length in Unicode characters of @upcase (if present)&n; *&n; * Compare the names @s1 and @s2 and return TRUE (1) if the names are&n; * identical, or FALSE (0) if they are not identical. If @ic is IGNORE_CASE,&n; * the @upcase table is used to performa a case insensitive comparison.&n; */
DECL|function|ntfs_are_names_equal
r_int
id|ntfs_are_names_equal
c_func
(paren
m_wchar_t
op_star
id|s1
comma
r_int
id|s1_len
comma
m_wchar_t
op_star
id|s2
comma
r_int
id|s2_len
comma
r_int
id|ic
comma
m_wchar_t
op_star
id|upcase
comma
id|__u32
id|upcase_size
)paren
(brace
r_if
c_cond
(paren
id|s1_len
op_ne
id|s2_len
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ic
)paren
r_return
id|memcmp
c_func
(paren
id|s1
comma
id|s2
comma
id|s1_len
op_lshift
l_int|1
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
r_return
id|ntfs_wcsncasecmp
c_func
(paren
id|s1
comma
id|s2
comma
id|s1_len
comma
id|upcase
comma
id|upcase_size
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
)brace
multiline_comment|/**&n; * ntfs_collate_names - collate two Unicode names&n; * @upcase:&t;upcase table (ignored if @ic is CASE_SENSITIVE)&n; * @upcase_len:&t;upcase table size (ignored if @ic is CASE_SENSITIVE)&n; * @name1:&t;first Unicode name to compare&n; * @name2:&t;second Unicode name to compare&n; * @ic:         either CASE_SENSITIVE or IGNORE_CASE&n; * @err_val:&t;if @name1 contains an invalid character return this value&n; *&n; * ntfs_collate_names collates two Unicode names and returns:&n; * &n; *  -1 if the first name collates before the second one,&n; *   0 if the names match,&n; *   1 if the second name collates before the first one, or&n; * @ec if an invalid character is encountered in @name1 during the comparison.&n; *&n; * The following characters are considered invalid: &squot;&quot;&squot;, &squot;*&squot;, &squot;&lt;&squot;, &squot;&gt;&squot; and &squot;?&squot;.&n; */
DECL|function|ntfs_collate_names
r_int
id|ntfs_collate_names
c_func
(paren
m_wchar_t
op_star
id|upcase
comma
id|__u32
id|upcase_len
comma
m_wchar_t
op_star
id|name1
comma
id|__u32
id|name1_len
comma
m_wchar_t
op_star
id|name2
comma
id|__u32
id|name2_len
comma
r_int
id|ic
comma
r_int
id|err_val
)paren
(brace
id|__u32
id|cnt
suffix:semicolon
m_wchar_t
id|c1
comma
id|c2
suffix:semicolon
r_for
c_loop
(paren
id|cnt
op_assign
l_int|0
suffix:semicolon
id|cnt
OL
id|min
c_func
(paren
r_int
r_int
comma
id|name1_len
comma
id|name2_len
)paren
suffix:semicolon
op_increment
id|cnt
)paren
(brace
id|c1
op_assign
id|le16_to_cpu
c_func
(paren
op_star
id|name1
op_increment
)paren
suffix:semicolon
id|c2
op_assign
id|le16_to_cpu
c_func
(paren
op_star
id|name2
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ic
)paren
(brace
r_if
c_cond
(paren
id|c1
OL
id|upcase_len
)paren
id|c1
op_assign
id|le16_to_cpu
c_func
(paren
id|upcase
(braket
id|c1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c2
OL
id|upcase_len
)paren
id|c2
op_assign
id|le16_to_cpu
c_func
(paren
id|upcase
(braket
id|c2
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c1
OL
l_int|64
op_logical_and
id|legal_ansi_char_array
(braket
id|c1
)braket
op_amp
l_int|8
)paren
suffix:semicolon
r_return
id|err_val
suffix:semicolon
r_if
c_cond
(paren
id|c1
OL
id|c2
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|c1
OG
id|c2
)paren
r_return
l_int|1
suffix:semicolon
op_increment
id|name1
suffix:semicolon
op_increment
id|name2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|name1_len
OL
id|name2_len
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|name1_len
op_eq
id|name2_len
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* name1_len &gt; name2_len */
id|c1
op_assign
id|le16_to_cpu
c_func
(paren
op_star
id|name1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c1
OL
l_int|64
op_logical_and
id|legal_ansi_char_array
(braket
id|c1
)braket
op_amp
l_int|8
)paren
r_return
id|err_val
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/**&n; * ntfs_wcsncasecmp - compare two little endian Unicode strings, ignoring case&n; * @s1:&t;&t;&t;first string&n; * @s2:&t;&t;&t;second string&n; * @n:&t;&t;&t;maximum unicode characters to compare&n; * @upcase:&t;&t;upcase table&n; * @upcase_size:&t;upcase table size in Unicode characters&n; *&n; * Compare the first @n characters of the Unicode strings @s1 and @s2,&n; * ignoring case. The strings in little endian format and appropriate&n; * le16_to_cpu() conversion is performed on non-little endian machines.&n; * &n; * Each character is uppercased using the @upcase table before the comparison.&n; *&n; * The function returns an integer less than, equal to, or greater than zero&n; * if @s1 (or the first @n Unicode characters thereof) is found, respectively,&n; * to be less than, to match, or be greater than @s2.&n; */
DECL|function|ntfs_wcsncasecmp
r_int
id|ntfs_wcsncasecmp
c_func
(paren
m_wchar_t
op_star
id|s1
comma
m_wchar_t
op_star
id|s2
comma
r_int
id|n
comma
m_wchar_t
op_star
id|upcase
comma
id|__u32
id|upcase_size
)paren
(brace
m_wchar_t
id|c1
comma
id|c2
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
id|n
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
(paren
id|c1
op_assign
id|le16_to_cpu
c_func
(paren
id|s1
(braket
id|i
)braket
)paren
)paren
OL
id|upcase_size
)paren
id|c1
op_assign
id|le16_to_cpu
c_func
(paren
id|upcase
(braket
id|c1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|c2
op_assign
id|le16_to_cpu
c_func
(paren
id|s2
(braket
id|i
)braket
)paren
)paren
OL
id|upcase_size
)paren
id|c2
op_assign
id|le16_to_cpu
c_func
(paren
id|upcase
(braket
id|c2
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c1
OL
id|c2
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|c1
OG
id|c2
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c1
)paren
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
