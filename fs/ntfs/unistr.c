multiline_comment|/*&n; * unistr.c - NTFS Unicode string handling. Part of the Linux-NTFS project.&n; *&n; * Copyright (c) 2001-2004 Anton Altaparmakov&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be&n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty&n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS&n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;ntfs.h&quot;
multiline_comment|/*&n; * IMPORTANT&n; * =========&n; *&n; * All these routines assume that the Unicode characters are in little endian&n; * encoding inside the strings!!!&n; */
multiline_comment|/*&n; * This is used by the name collation functions to quickly determine what&n; * characters are (in)valid.&n; */
DECL|variable|legal_ansi_char_array
r_static
r_const
id|u8
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
id|BOOL
id|ntfs_are_names_equal
c_func
(paren
r_const
id|ntfschar
op_star
id|s1
comma
r_int
id|s1_len
comma
r_const
id|ntfschar
op_star
id|s2
comma
r_int
id|s2_len
comma
r_const
id|IGNORE_CASE_BOOL
id|ic
comma
r_const
id|ntfschar
op_star
id|upcase
comma
r_const
id|u32
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
id|FALSE
suffix:semicolon
r_if
c_cond
(paren
id|ic
op_eq
id|CASE_SENSITIVE
)paren
r_return
op_logical_neg
id|ntfs_ucsncmp
c_func
(paren
id|s1
comma
id|s2
comma
id|s1_len
)paren
suffix:semicolon
r_return
op_logical_neg
id|ntfs_ucsncasecmp
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
suffix:semicolon
)brace
multiline_comment|/**&n; * ntfs_collate_names - collate two Unicode names&n; * @name1:&t;first Unicode name to compare&n; * @name2:&t;second Unicode name to compare&n; * @err_val:&t;if @name1 contains an invalid character return this value&n; * @ic:&t;&t;either CASE_SENSITIVE or IGNORE_CASE&n; * @upcase:&t;upcase table (ignored if @ic is CASE_SENSITIVE)&n; * @upcase_len:&t;upcase table size (ignored if @ic is CASE_SENSITIVE)&n; *&n; * ntfs_collate_names collates two Unicode names and returns:&n; *&n; *  -1 if the first name collates before the second one,&n; *   0 if the names match,&n; *   1 if the second name collates before the first one, or&n; * @err_val if an invalid character is found in @name1 during the comparison.&n; *&n; * The following characters are considered invalid: &squot;&quot;&squot;, &squot;*&squot;, &squot;&lt;&squot;, &squot;&gt;&squot; and &squot;?&squot;.&n; */
DECL|function|ntfs_collate_names
r_int
id|ntfs_collate_names
c_func
(paren
r_const
id|ntfschar
op_star
id|name1
comma
r_const
id|u32
id|name1_len
comma
r_const
id|ntfschar
op_star
id|name2
comma
r_const
id|u32
id|name2_len
comma
r_const
r_int
id|err_val
comma
r_const
id|IGNORE_CASE_BOOL
id|ic
comma
r_const
id|ntfschar
op_star
id|upcase
comma
r_const
id|u32
id|upcase_len
)paren
(brace
id|u32
id|cnt
comma
id|min_len
suffix:semicolon
id|u16
id|c1
comma
id|c2
suffix:semicolon
id|min_len
op_assign
id|name1_len
suffix:semicolon
r_if
c_cond
(paren
id|name1_len
OG
id|name2_len
)paren
id|min_len
op_assign
id|name2_len
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
id|min_len
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
multiline_comment|/**&n; * ntfs_ucsncmp - compare two little endian Unicode strings&n; * @s1:&t;&t;first string&n; * @s2:&t;&t;second string&n; * @n:&t;&t;maximum unicode characters to compare&n; *&n; * Compare the first @n characters of the Unicode strings @s1 and @s2,&n; * The strings in little endian format and appropriate le16_to_cpu()&n; * conversion is performed on non-little endian machines.&n; *&n; * The function returns an integer less than, equal to, or greater than zero&n; * if @s1 (or the first @n Unicode characters thereof) is found, respectively,&n; * to be less than, to match, or be greater than @s2.&n; */
DECL|function|ntfs_ucsncmp
r_int
id|ntfs_ucsncmp
c_func
(paren
r_const
id|ntfschar
op_star
id|s1
comma
r_const
id|ntfschar
op_star
id|s2
comma
r_int
id|n
)paren
(brace
id|u16
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
suffix:semicolon
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
multiline_comment|/**&n; * ntfs_ucsncasecmp - compare two little endian Unicode strings, ignoring case&n; * @s1:&t;&t;&t;first string&n; * @s2:&t;&t;&t;second string&n; * @n:&t;&t;&t;maximum unicode characters to compare&n; * @upcase:&t;&t;upcase table&n; * @upcase_size:&t;upcase table size in Unicode characters&n; *&n; * Compare the first @n characters of the Unicode strings @s1 and @s2,&n; * ignoring case. The strings in little endian format and appropriate&n; * le16_to_cpu() conversion is performed on non-little endian machines.&n; *&n; * Each character is uppercased using the @upcase table before the comparison.&n; *&n; * The function returns an integer less than, equal to, or greater than zero&n; * if @s1 (or the first @n Unicode characters thereof) is found, respectively,&n; * to be less than, to match, or be greater than @s2.&n; */
DECL|function|ntfs_ucsncasecmp
r_int
id|ntfs_ucsncasecmp
c_func
(paren
r_const
id|ntfschar
op_star
id|s1
comma
r_const
id|ntfschar
op_star
id|s2
comma
r_int
id|n
comma
r_const
id|ntfschar
op_star
id|upcase
comma
r_const
id|u32
id|upcase_size
)paren
(brace
r_int
id|i
suffix:semicolon
id|u16
id|c1
comma
id|c2
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
DECL|function|ntfs_upcase_name
r_void
id|ntfs_upcase_name
c_func
(paren
id|ntfschar
op_star
id|name
comma
id|u32
id|name_len
comma
r_const
id|ntfschar
op_star
id|upcase
comma
r_const
id|u32
id|upcase_len
)paren
(brace
id|u32
id|i
suffix:semicolon
id|u16
id|u
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
id|name_len
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
id|u
op_assign
id|le16_to_cpu
c_func
(paren
id|name
(braket
id|i
)braket
)paren
)paren
OL
id|upcase_len
)paren
id|name
(braket
id|i
)braket
op_assign
id|upcase
(braket
id|u
)braket
suffix:semicolon
)brace
DECL|function|ntfs_file_upcase_value
r_void
id|ntfs_file_upcase_value
c_func
(paren
id|FILE_NAME_ATTR
op_star
id|file_name_attr
comma
r_const
id|ntfschar
op_star
id|upcase
comma
r_const
id|u32
id|upcase_len
)paren
(brace
id|ntfs_upcase_name
c_func
(paren
(paren
id|ntfschar
op_star
)paren
op_amp
id|file_name_attr-&gt;file_name
comma
id|file_name_attr-&gt;file_name_length
comma
id|upcase
comma
id|upcase_len
)paren
suffix:semicolon
)brace
DECL|function|ntfs_file_compare_values
r_int
id|ntfs_file_compare_values
c_func
(paren
id|FILE_NAME_ATTR
op_star
id|file_name_attr1
comma
id|FILE_NAME_ATTR
op_star
id|file_name_attr2
comma
r_const
r_int
id|err_val
comma
r_const
id|IGNORE_CASE_BOOL
id|ic
comma
r_const
id|ntfschar
op_star
id|upcase
comma
r_const
id|u32
id|upcase_len
)paren
(brace
r_return
id|ntfs_collate_names
c_func
(paren
(paren
id|ntfschar
op_star
)paren
op_amp
id|file_name_attr1-&gt;file_name
comma
id|file_name_attr1-&gt;file_name_length
comma
(paren
id|ntfschar
op_star
)paren
op_amp
id|file_name_attr2-&gt;file_name
comma
id|file_name_attr2-&gt;file_name_length
comma
id|err_val
comma
id|ic
comma
id|upcase
comma
id|upcase_len
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * ntfs_nlstoucs - convert NLS string to little endian Unicode string&n; * @vol:&t;ntfs volume which we are working with&n; * @ins:&t;input NLS string buffer&n; * @ins_len:&t;length of input string in bytes&n; * @outs:&t;on return contains the allocated output Unicode string buffer&n; *&n; * Convert the input string @ins, which is in whatever format the loaded NLS&n; * map dictates, into a little endian, 2-byte Unicode string.&n; *&n; * This function allocates the string and the caller is responsible for&n; * calling kmem_cache_free(ntfs_name_cache, @outs); when finished with it.&n; *&n; * On success the function returns the number of Unicode characters written to&n; * the output string *@outs (&gt;= 0), not counting the terminating Unicode NULL&n; * character. *@outs is set to the allocated output string buffer.&n; *&n; * On error, a negative number corresponding to the error code is returned. In&n; * that case the output string is not allocated. Both *@outs and *@outs_len&n; * are then undefined.&n; *&n; * This might look a bit odd due to fast path optimization...&n; */
DECL|function|ntfs_nlstoucs
r_int
id|ntfs_nlstoucs
c_func
(paren
r_const
id|ntfs_volume
op_star
id|vol
comma
r_const
r_char
op_star
id|ins
comma
r_const
r_int
id|ins_len
comma
id|ntfschar
op_star
op_star
id|outs
)paren
(brace
r_struct
id|nls_table
op_star
id|nls
op_assign
id|vol-&gt;nls_map
suffix:semicolon
id|ntfschar
op_star
id|ucs
suffix:semicolon
m_wchar_t
id|wc
suffix:semicolon
r_int
id|i
comma
id|o
comma
id|wc_len
suffix:semicolon
multiline_comment|/* We don&squot;t trust outside sources. */
r_if
c_cond
(paren
id|ins
)paren
(brace
id|ucs
op_assign
(paren
id|ntfschar
op_star
)paren
id|kmem_cache_alloc
c_func
(paren
id|ntfs_name_cache
comma
id|SLAB_NOFS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ucs
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
id|o
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ins_len
suffix:semicolon
id|i
op_add_assign
id|wc_len
)paren
(brace
id|wc_len
op_assign
id|nls
op_member_access_from_pointer
id|char2uni
c_func
(paren
id|ins
op_plus
id|i
comma
id|ins_len
op_minus
id|i
comma
op_amp
id|wc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wc_len
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|wc
)paren
(brace
id|ucs
(braket
id|o
op_increment
)braket
op_assign
id|cpu_to_le16
c_func
(paren
id|wc
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* else (!wc) */
r_break
suffix:semicolon
)brace
multiline_comment|/* else (wc_len &lt; 0) */
r_goto
id|conversion_err
suffix:semicolon
)brace
id|ucs
(braket
id|o
)braket
op_assign
id|cpu_to_le16
c_func
(paren
l_int|0
)paren
suffix:semicolon
op_star
id|outs
op_assign
id|ucs
suffix:semicolon
r_return
id|o
suffix:semicolon
)brace
multiline_comment|/* else (!ucs) */
id|ntfs_error
c_func
(paren
id|vol-&gt;sb
comma
l_string|&quot;Failed to allocate name from &quot;
l_string|&quot;ntfs_name_cache!&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* else (!ins) */
id|ntfs_error
c_func
(paren
l_int|NULL
comma
l_string|&quot;Received NULL pointer.&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
id|conversion_err
suffix:colon
id|ntfs_error
c_func
(paren
id|vol-&gt;sb
comma
l_string|&quot;Name using character set %s contains characters &quot;
l_string|&quot;that cannot be converted to Unicode.&quot;
comma
id|nls-&gt;charset
)paren
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|ntfs_name_cache
comma
id|ucs
)paren
suffix:semicolon
r_return
op_minus
id|EILSEQ
suffix:semicolon
)brace
multiline_comment|/**&n; * ntfs_ucstonls - convert little endian Unicode string to NLS string&n; * @vol:&t;ntfs volume which we are working with&n; * @ins:&t;input Unicode string buffer&n; * @ins_len:&t;length of input string in Unicode characters&n; * @outs:&t;on return contains the (allocated) output NLS string buffer&n; * @outs_len:&t;length of output string buffer in bytes&n; *&n; * Convert the input little endian, 2-byte Unicode string @ins, of length&n; * @ins_len into the string format dictated by the loaded NLS.&n; *&n; * If *@outs is NULL, this function allocates the string and the caller is&n; * responsible for calling kfree(*@outs); when finished with it. In this case&n; * @outs_len is ignored and can be 0.&n; *&n; * On success the function returns the number of bytes written to the output&n; * string *@outs (&gt;= 0), not counting the terminating NULL byte. If the output&n; * string buffer was allocated, *@outs is set to it.&n; *&n; * On error, a negative number corresponding to the error code is returned. In&n; * that case the output string is not allocated. The contents of *@outs are&n; * then undefined.&n; *&n; * This might look a bit odd due to fast path optimization...&n; */
DECL|function|ntfs_ucstonls
r_int
id|ntfs_ucstonls
c_func
(paren
r_const
id|ntfs_volume
op_star
id|vol
comma
r_const
id|ntfschar
op_star
id|ins
comma
r_const
r_int
id|ins_len
comma
r_int
r_char
op_star
op_star
id|outs
comma
r_int
id|outs_len
)paren
(brace
r_struct
id|nls_table
op_star
id|nls
op_assign
id|vol-&gt;nls_map
suffix:semicolon
r_int
r_char
op_star
id|ns
suffix:semicolon
r_int
id|i
comma
id|o
comma
id|ns_len
comma
id|wc
suffix:semicolon
multiline_comment|/* We don&squot;t trust outside sources. */
r_if
c_cond
(paren
id|ins
)paren
(brace
id|ns
op_assign
op_star
id|outs
suffix:semicolon
id|ns_len
op_assign
id|outs_len
suffix:semicolon
r_if
c_cond
(paren
id|ns
op_logical_and
op_logical_neg
id|ns_len
)paren
(brace
id|wc
op_assign
op_minus
id|ENAMETOOLONG
suffix:semicolon
r_goto
id|conversion_err
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ns
)paren
(brace
id|ns_len
op_assign
id|ins_len
op_star
id|NLS_MAX_CHARSET_SIZE
suffix:semicolon
id|ns
op_assign
(paren
r_int
r_char
op_star
)paren
id|kmalloc
c_func
(paren
id|ns_len
op_plus
l_int|1
comma
id|GFP_NOFS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ns
)paren
r_goto
id|mem_err_out
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
id|o
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ins_len
suffix:semicolon
id|i
op_increment
)paren
(brace
id|retry
suffix:colon
id|wc
op_assign
id|nls
op_member_access_from_pointer
id|uni2char
c_func
(paren
id|le16_to_cpu
c_func
(paren
id|ins
(braket
id|i
)braket
)paren
comma
id|ns
op_plus
id|o
comma
id|ns_len
op_minus
id|o
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wc
OG
l_int|0
)paren
(brace
id|o
op_add_assign
id|wc
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|wc
)paren
r_break
suffix:semicolon
r_else
r_if
c_cond
(paren
id|wc
op_eq
op_minus
id|ENAMETOOLONG
op_logical_and
id|ns
op_ne
op_star
id|outs
)paren
(brace
r_int
r_char
op_star
id|tc
suffix:semicolon
multiline_comment|/* Grow in multiples of 64 bytes. */
id|tc
op_assign
(paren
r_int
r_char
op_star
)paren
id|kmalloc
c_func
(paren
(paren
id|ns_len
op_plus
l_int|64
)paren
op_amp
op_complement
l_int|63
comma
id|GFP_NOFS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tc
)paren
(brace
id|memcpy
c_func
(paren
id|tc
comma
id|ns
comma
id|ns_len
)paren
suffix:semicolon
id|ns_len
op_assign
(paren
(paren
id|ns_len
op_plus
l_int|64
)paren
op_amp
op_complement
l_int|63
)paren
op_minus
l_int|1
suffix:semicolon
id|kfree
c_func
(paren
id|ns
)paren
suffix:semicolon
id|ns
op_assign
id|tc
suffix:semicolon
r_goto
id|retry
suffix:semicolon
)brace
multiline_comment|/* No memory so goto conversion_error; */
)brace
multiline_comment|/* wc &lt; 0, real error. */
r_goto
id|conversion_err
suffix:semicolon
)brace
id|ns
(braket
id|o
)braket
op_assign
l_int|0
suffix:semicolon
op_star
id|outs
op_assign
id|ns
suffix:semicolon
r_return
id|o
suffix:semicolon
)brace
multiline_comment|/* else (!ins) */
id|ntfs_error
c_func
(paren
id|vol-&gt;sb
comma
l_string|&quot;Received NULL pointer.&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
id|conversion_err
suffix:colon
id|ntfs_error
c_func
(paren
id|vol-&gt;sb
comma
l_string|&quot;Unicode name contains characters that cannot be &quot;
l_string|&quot;converted to character set %s.&quot;
comma
id|nls-&gt;charset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ns
op_ne
op_star
id|outs
)paren
id|kfree
c_func
(paren
id|ns
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wc
op_ne
op_minus
id|ENAMETOOLONG
)paren
id|wc
op_assign
op_minus
id|EILSEQ
suffix:semicolon
r_return
id|wc
suffix:semicolon
id|mem_err_out
suffix:colon
id|ntfs_error
c_func
(paren
id|vol-&gt;sb
comma
l_string|&quot;Failed to allocate name!&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
eof
