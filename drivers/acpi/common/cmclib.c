multiline_comment|/******************************************************************************&n; *&n; * Module Name: cmclib - Local implementation of C library functions&n; * $Revision: 32 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acevents.h&quot;
macro_line|#include &quot;achware.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;acinterp.h&quot;
macro_line|#include &quot;amlcode.h&quot;
multiline_comment|/*&n; * These implementations of standard C Library routines can optionally be&n; * used if a C library is not available.  In general, they are less efficient&n; * than an inline or assembly implementation&n; */
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          MISCELLANEOUS
id|MODULE_NAME
(paren
l_string|&quot;cmclib&quot;
)paren
macro_line|#ifndef ACPI_USE_SYSTEM_CLIBRARY
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    strlen&n; *&n; * PARAMETERS:  String              - Null terminated string&n; *&n; * RETURN:      Length&n; *&n; * DESCRIPTION: Returns the length of the input string&n; *&n; ******************************************************************************/
id|NATIVE_UINT
DECL|function|acpi_cm_strlen
id|acpi_cm_strlen
(paren
r_const
id|NATIVE_CHAR
op_star
id|string
)paren
(brace
id|NATIVE_UINT
id|length
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Count the string until a null is encountered */
r_while
c_loop
(paren
op_star
id|string
)paren
(brace
id|length
op_increment
suffix:semicolon
id|string
op_increment
suffix:semicolon
)brace
r_return
(paren
id|length
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    strcpy&n; *&n; * PARAMETERS:  Dst_string      - Target of the copy&n; *              Src_string      - The source string to copy&n; *&n; * RETURN:      Dst_string&n; *&n; * DESCRIPTION: Copy a null terminated string&n; *&n; ******************************************************************************/
id|NATIVE_CHAR
op_star
DECL|function|acpi_cm_strcpy
id|acpi_cm_strcpy
(paren
id|NATIVE_CHAR
op_star
id|dst_string
comma
r_const
id|NATIVE_CHAR
op_star
id|src_string
)paren
(brace
id|NATIVE_CHAR
op_star
id|string
op_assign
id|dst_string
suffix:semicolon
multiline_comment|/* Move bytes brute force */
r_while
c_loop
(paren
op_star
id|src_string
)paren
(brace
op_star
id|string
op_assign
op_star
id|src_string
suffix:semicolon
id|string
op_increment
suffix:semicolon
id|src_string
op_increment
suffix:semicolon
)brace
multiline_comment|/* Null terminate */
op_star
id|string
op_assign
l_int|0
suffix:semicolon
r_return
(paren
id|dst_string
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    strncpy&n; *&n; * PARAMETERS:  Dst_string      - Target of the copy&n; *              Src_string      - The source string to copy&n; *              Count           - Maximum # of bytes to copy&n; *&n; * RETURN:      Dst_string&n; *&n; * DESCRIPTION: Copy a null terminated string, with a maximum length&n; *&n; ******************************************************************************/
id|NATIVE_CHAR
op_star
DECL|function|acpi_cm_strncpy
id|acpi_cm_strncpy
(paren
id|NATIVE_CHAR
op_star
id|dst_string
comma
r_const
id|NATIVE_CHAR
op_star
id|src_string
comma
id|NATIVE_UINT
id|count
)paren
(brace
id|NATIVE_CHAR
op_star
id|string
op_assign
id|dst_string
suffix:semicolon
multiline_comment|/* Copy the string */
r_for
c_loop
(paren
id|string
op_assign
id|dst_string
suffix:semicolon
id|count
op_logical_and
(paren
id|count
op_decrement
comma
(paren
op_star
id|string
op_increment
op_assign
op_star
id|src_string
op_increment
)paren
)paren
suffix:semicolon
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* Pad with nulls if necessary */
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
op_star
id|string
op_assign
l_int|0
suffix:semicolon
id|string
op_increment
suffix:semicolon
)brace
multiline_comment|/* Return original pointer */
r_return
(paren
id|dst_string
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    strcmp&n; *&n; * PARAMETERS:  String1         - First string&n; *              String2         - Second string&n; *&n; * RETURN:      Index where strings mismatched, or 0 if strings matched&n; *&n; * DESCRIPTION: Compare two null terminated strings&n; *&n; ******************************************************************************/
id|u32
DECL|function|acpi_cm_strcmp
id|acpi_cm_strcmp
(paren
r_const
id|NATIVE_CHAR
op_star
id|string1
comma
r_const
id|NATIVE_CHAR
op_star
id|string2
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
(paren
op_star
id|string1
op_eq
op_star
id|string2
)paren
suffix:semicolon
id|string2
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|string1
op_increment
)paren
(brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
r_return
(paren
(paren
r_int
r_char
)paren
op_star
id|string1
op_minus
(paren
r_int
r_char
)paren
op_star
id|string2
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    strncmp&n; *&n; * PARAMETERS:  String1         - First string&n; *              String2         - Second string&n; *              Count           - Maximum # of bytes to compare&n; *&n; * RETURN:      Index where strings mismatched, or 0 if strings matched&n; *&n; * DESCRIPTION: Compare two null terminated strings, with a maximum length&n; *&n; ******************************************************************************/
id|u32
DECL|function|acpi_cm_strncmp
id|acpi_cm_strncmp
(paren
r_const
id|NATIVE_CHAR
op_star
id|string1
comma
r_const
id|NATIVE_CHAR
op_star
id|string2
comma
id|NATIVE_UINT
id|count
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|count
op_decrement
op_logical_and
(paren
op_star
id|string1
op_eq
op_star
id|string2
)paren
suffix:semicolon
id|string2
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|string1
op_increment
)paren
(brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
r_return
(paren
(paren
id|count
op_eq
op_minus
l_int|1
)paren
ques
c_cond
l_int|0
suffix:colon
(paren
(paren
r_int
r_char
)paren
op_star
id|string1
op_minus
(paren
r_int
r_char
)paren
op_star
id|string2
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Strcat&n; *&n; * PARAMETERS:  Dst_string      - Target of the copy&n; *              Src_string      - The source string to copy&n; *&n; * RETURN:      Dst_string&n; *&n; * DESCRIPTION: Append a null terminated string to a null terminated string&n; *&n; ******************************************************************************/
id|NATIVE_CHAR
op_star
DECL|function|acpi_cm_strcat
id|acpi_cm_strcat
(paren
id|NATIVE_CHAR
op_star
id|dst_string
comma
r_const
id|NATIVE_CHAR
op_star
id|src_string
)paren
(brace
id|NATIVE_CHAR
op_star
id|string
suffix:semicolon
multiline_comment|/* Find end of the destination string */
r_for
c_loop
(paren
id|string
op_assign
id|dst_string
suffix:semicolon
op_star
id|string
op_increment
suffix:semicolon
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* Concatinate the string */
r_for
c_loop
(paren
op_decrement
id|string
suffix:semicolon
(paren
op_star
id|string
op_increment
op_assign
op_star
id|src_string
op_increment
)paren
suffix:semicolon
)paren
(brace
suffix:semicolon
)brace
r_return
(paren
id|dst_string
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    strncat&n; *&n; * PARAMETERS:  Dst_string      - Target of the copy&n; *              Src_string      - The source string to copy&n; *              Count           - Maximum # of bytes to copy&n; *&n; * RETURN:      Dst_string&n; *&n; * DESCRIPTION: Append a null terminated string to a null terminated string,&n; *              with a maximum count.&n; *&n; ******************************************************************************/
id|NATIVE_CHAR
op_star
DECL|function|acpi_cm_strncat
id|acpi_cm_strncat
(paren
id|NATIVE_CHAR
op_star
id|dst_string
comma
r_const
id|NATIVE_CHAR
op_star
id|src_string
comma
id|NATIVE_UINT
id|count
)paren
(brace
id|NATIVE_CHAR
op_star
id|string
suffix:semicolon
r_if
c_cond
(paren
id|count
)paren
(brace
multiline_comment|/* Find end of the destination string */
r_for
c_loop
(paren
id|string
op_assign
id|dst_string
suffix:semicolon
op_star
id|string
op_increment
suffix:semicolon
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* Concatinate the string */
r_for
c_loop
(paren
op_decrement
id|string
suffix:semicolon
(paren
op_star
id|string
op_increment
op_assign
op_star
id|src_string
op_increment
)paren
op_logical_and
op_decrement
id|count
suffix:semicolon
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* Null terminate if necessary */
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
(brace
op_star
id|string
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_return
(paren
id|dst_string
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    memcpy&n; *&n; * PARAMETERS:  Dest        - Target of the copy&n; *              Src         - Source buffer to copy&n; *              Count       - Number of bytes to copy&n; *&n; * RETURN:      Dest&n; *&n; * DESCRIPTION: Copy arbitrary bytes of memory&n; *&n; ******************************************************************************/
r_void
op_star
DECL|function|acpi_cm_memcpy
id|acpi_cm_memcpy
(paren
r_void
op_star
id|dest
comma
r_const
r_void
op_star
id|src
comma
id|NATIVE_UINT
id|count
)paren
(brace
id|NATIVE_CHAR
op_star
r_new
op_assign
(paren
id|NATIVE_CHAR
op_star
)paren
id|dest
suffix:semicolon
id|NATIVE_CHAR
op_star
id|old
op_assign
(paren
id|NATIVE_CHAR
op_star
)paren
id|src
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
op_star
r_new
op_assign
op_star
id|old
suffix:semicolon
r_new
op_increment
suffix:semicolon
id|old
op_increment
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
r_return
(paren
id|dest
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    memset&n; *&n; * PARAMETERS:  Dest        - Buffer to set&n; *              Value       - Value to set each byte of memory&n; *              Count       - Number of bytes to set&n; *&n; * RETURN:      Dest&n; *&n; * DESCRIPTION: Initialize a buffer to a known value.&n; *&n; ******************************************************************************/
r_void
op_star
DECL|function|acpi_cm_memset
id|acpi_cm_memset
(paren
r_void
op_star
id|dest
comma
id|NATIVE_UINT
id|value
comma
id|NATIVE_UINT
id|count
)paren
(brace
id|NATIVE_CHAR
op_star
r_new
op_assign
(paren
id|NATIVE_CHAR
op_star
)paren
id|dest
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
op_star
r_new
op_assign
(paren
r_char
)paren
id|value
suffix:semicolon
r_new
op_increment
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
r_return
(paren
id|dest
)paren
suffix:semicolon
)brace
DECL|macro|NEGATIVE
mdefine_line|#define NEGATIVE    1
DECL|macro|POSITIVE
mdefine_line|#define POSITIVE    0
DECL|macro|_ACPI_XA
mdefine_line|#define _ACPI_XA     0x00    /* extra alphabetic - not supported */
DECL|macro|_ACPI_XS
mdefine_line|#define _ACPI_XS     0x40    /* extra space */
DECL|macro|_ACPI_BB
mdefine_line|#define _ACPI_BB     0x00    /* BEL, BS, etc. - not supported */
DECL|macro|_ACPI_CN
mdefine_line|#define _ACPI_CN     0x20    /* CR, FF, HT, NL, VT */
DECL|macro|_ACPI_DI
mdefine_line|#define _ACPI_DI     0x04    /* &squot;0&squot;-&squot;9&squot; */
DECL|macro|_ACPI_LO
mdefine_line|#define _ACPI_LO     0x02    /* &squot;a&squot;-&squot;z&squot; */
DECL|macro|_ACPI_PU
mdefine_line|#define _ACPI_PU     0x10    /* punctuation */
DECL|macro|_ACPI_SP
mdefine_line|#define _ACPI_SP     0x08    /* space */
DECL|macro|_ACPI_UP
mdefine_line|#define _ACPI_UP     0x01    /* &squot;A&squot;-&squot;Z&squot; */
DECL|macro|_ACPI_XD
mdefine_line|#define _ACPI_XD     0x80    /* &squot;0&squot;-&squot;9&squot;, &squot;A&squot;-&squot;F&squot;, &squot;a&squot;-&squot;f&squot; */
DECL|variable|_acpi_ctype
r_static
r_const
id|u8
id|_acpi_ctype
(braket
l_int|257
)braket
op_assign
(brace
id|_ACPI_CN
comma
multiline_comment|/* 0x0      0.     */
id|_ACPI_CN
comma
multiline_comment|/* 0x1      1.     */
id|_ACPI_CN
comma
multiline_comment|/* 0x2      2.     */
id|_ACPI_CN
comma
multiline_comment|/* 0x3      3.     */
id|_ACPI_CN
comma
multiline_comment|/* 0x4      4.     */
id|_ACPI_CN
comma
multiline_comment|/* 0x5      5.     */
id|_ACPI_CN
comma
multiline_comment|/* 0x6      6.     */
id|_ACPI_CN
comma
multiline_comment|/* 0x7      7.     */
id|_ACPI_CN
comma
multiline_comment|/* 0x8      8.     */
id|_ACPI_CN
op_or
id|_ACPI_SP
comma
multiline_comment|/* 0x9      9.     */
id|_ACPI_CN
op_or
id|_ACPI_SP
comma
multiline_comment|/* 0xA     10.     */
id|_ACPI_CN
op_or
id|_ACPI_SP
comma
multiline_comment|/* 0xB     11.     */
id|_ACPI_CN
op_or
id|_ACPI_SP
comma
multiline_comment|/* 0xC     12.     */
id|_ACPI_CN
op_or
id|_ACPI_SP
comma
multiline_comment|/* 0xD     13.     */
id|_ACPI_CN
comma
multiline_comment|/* 0xE     14.     */
id|_ACPI_CN
comma
multiline_comment|/* 0xF     15.     */
id|_ACPI_CN
comma
multiline_comment|/* 0x10    16.     */
id|_ACPI_CN
comma
multiline_comment|/* 0x11    17.     */
id|_ACPI_CN
comma
multiline_comment|/* 0x12    18.     */
id|_ACPI_CN
comma
multiline_comment|/* 0x13    19.     */
id|_ACPI_CN
comma
multiline_comment|/* 0x14    20.     */
id|_ACPI_CN
comma
multiline_comment|/* 0x15    21.     */
id|_ACPI_CN
comma
multiline_comment|/* 0x16    22.     */
id|_ACPI_CN
comma
multiline_comment|/* 0x17    23.     */
id|_ACPI_CN
comma
multiline_comment|/* 0x18    24.     */
id|_ACPI_CN
comma
multiline_comment|/* 0x19    25.     */
id|_ACPI_CN
comma
multiline_comment|/* 0x1A    26.     */
id|_ACPI_CN
comma
multiline_comment|/* 0x1B    27.     */
id|_ACPI_CN
comma
multiline_comment|/* 0x1C    28.     */
id|_ACPI_CN
comma
multiline_comment|/* 0x1D    29.     */
id|_ACPI_CN
comma
multiline_comment|/* 0x1E    30.     */
id|_ACPI_CN
comma
multiline_comment|/* 0x1F    31.     */
id|_ACPI_XS
op_or
id|_ACPI_SP
comma
multiline_comment|/* 0x20    32. &squot; &squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x21    33. &squot;!&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x22    34. &squot;&quot;&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x23    35. &squot;#&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x24    36. &squot;$&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x25    37. &squot;%&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x26    38. &squot;&amp;&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x27    39. &squot;&squot;&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x28    40. &squot;(&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x29    41. &squot;)&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x2A    42. &squot;*&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x2B    43. &squot;+&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x2C    44. &squot;,&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x2D    45. &squot;-&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x2E    46. &squot;.&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x2F    47. &squot;/&squot; */
id|_ACPI_XD
op_or
id|_ACPI_DI
comma
multiline_comment|/* 0x30    48. &squot;0&squot; */
id|_ACPI_XD
op_or
id|_ACPI_DI
comma
multiline_comment|/* 0x31    49. &squot;1&squot; */
id|_ACPI_XD
op_or
id|_ACPI_DI
comma
multiline_comment|/* 0x32    50. &squot;2&squot; */
id|_ACPI_XD
op_or
id|_ACPI_DI
comma
multiline_comment|/* 0x33    51. &squot;3&squot; */
id|_ACPI_XD
op_or
id|_ACPI_DI
comma
multiline_comment|/* 0x34    52. &squot;4&squot; */
id|_ACPI_XD
op_or
id|_ACPI_DI
comma
multiline_comment|/* 0x35    53. &squot;5&squot; */
id|_ACPI_XD
op_or
id|_ACPI_DI
comma
multiline_comment|/* 0x36    54. &squot;6&squot; */
id|_ACPI_XD
op_or
id|_ACPI_DI
comma
multiline_comment|/* 0x37    55. &squot;7&squot; */
id|_ACPI_XD
op_or
id|_ACPI_DI
comma
multiline_comment|/* 0x38    56. &squot;8&squot; */
id|_ACPI_XD
op_or
id|_ACPI_DI
comma
multiline_comment|/* 0x39    57. &squot;9&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x3A    58. &squot;:&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x3B    59. &squot;;&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x3C    60. &squot;&lt;&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x3D    61. &squot;=&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x3E    62. &squot;&gt;&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x3F    63. &squot;?&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x40    64. &squot;@&squot; */
id|_ACPI_XD
op_or
id|_ACPI_UP
comma
multiline_comment|/* 0x41    65. &squot;A&squot; */
id|_ACPI_XD
op_or
id|_ACPI_UP
comma
multiline_comment|/* 0x42    66. &squot;B&squot; */
id|_ACPI_XD
op_or
id|_ACPI_UP
comma
multiline_comment|/* 0x43    67. &squot;C&squot; */
id|_ACPI_XD
op_or
id|_ACPI_UP
comma
multiline_comment|/* 0x44    68. &squot;D&squot; */
id|_ACPI_XD
op_or
id|_ACPI_UP
comma
multiline_comment|/* 0x45    69. &squot;E&squot; */
id|_ACPI_XD
op_or
id|_ACPI_UP
comma
multiline_comment|/* 0x46    70. &squot;F&squot; */
id|_ACPI_UP
comma
multiline_comment|/* 0x47    71. &squot;G&squot; */
id|_ACPI_UP
comma
multiline_comment|/* 0x48    72. &squot;H&squot; */
id|_ACPI_UP
comma
multiline_comment|/* 0x49    73. &squot;I&squot; */
id|_ACPI_UP
comma
multiline_comment|/* 0x4A    74. &squot;J&squot; */
id|_ACPI_UP
comma
multiline_comment|/* 0x4B    75. &squot;K&squot; */
id|_ACPI_UP
comma
multiline_comment|/* 0x4C    76. &squot;L&squot; */
id|_ACPI_UP
comma
multiline_comment|/* 0x4D    77. &squot;M&squot; */
id|_ACPI_UP
comma
multiline_comment|/* 0x4E    78. &squot;N&squot; */
id|_ACPI_UP
comma
multiline_comment|/* 0x4F    79. &squot;O&squot; */
id|_ACPI_UP
comma
multiline_comment|/* 0x50    80. &squot;P&squot; */
id|_ACPI_UP
comma
multiline_comment|/* 0x51    81. &squot;Q&squot; */
id|_ACPI_UP
comma
multiline_comment|/* 0x52    82. &squot;R&squot; */
id|_ACPI_UP
comma
multiline_comment|/* 0x53    83. &squot;S&squot; */
id|_ACPI_UP
comma
multiline_comment|/* 0x54    84. &squot;T&squot; */
id|_ACPI_UP
comma
multiline_comment|/* 0x55    85. &squot;U&squot; */
id|_ACPI_UP
comma
multiline_comment|/* 0x56    86. &squot;V&squot; */
id|_ACPI_UP
comma
multiline_comment|/* 0x57    87. &squot;W&squot; */
id|_ACPI_UP
comma
multiline_comment|/* 0x58    88. &squot;X&squot; */
id|_ACPI_UP
comma
multiline_comment|/* 0x59    89. &squot;Y&squot; */
id|_ACPI_UP
comma
multiline_comment|/* 0x5A    90. &squot;Z&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x5B    91. &squot;[&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x5C    92. &squot;&bslash;&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x5D    93. &squot;]&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x5E    94. &squot;^&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x5F    95. &squot;_&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x60    96. &squot;`&squot; */
id|_ACPI_XD
op_or
id|_ACPI_LO
comma
multiline_comment|/* 0x61    97. &squot;a&squot; */
id|_ACPI_XD
op_or
id|_ACPI_LO
comma
multiline_comment|/* 0x62    98. &squot;b&squot; */
id|_ACPI_XD
op_or
id|_ACPI_LO
comma
multiline_comment|/* 0x63    99. &squot;c&squot; */
id|_ACPI_XD
op_or
id|_ACPI_LO
comma
multiline_comment|/* 0x64   100. &squot;d&squot; */
id|_ACPI_XD
op_or
id|_ACPI_LO
comma
multiline_comment|/* 0x65   101. &squot;e&squot; */
id|_ACPI_XD
op_or
id|_ACPI_LO
comma
multiline_comment|/* 0x66   102. &squot;f&squot; */
id|_ACPI_LO
comma
multiline_comment|/* 0x67   103. &squot;g&squot; */
id|_ACPI_LO
comma
multiline_comment|/* 0x68   104. &squot;h&squot; */
id|_ACPI_LO
comma
multiline_comment|/* 0x69   105. &squot;i&squot; */
id|_ACPI_LO
comma
multiline_comment|/* 0x6A   106. &squot;j&squot; */
id|_ACPI_LO
comma
multiline_comment|/* 0x6B   107. &squot;k&squot; */
id|_ACPI_LO
comma
multiline_comment|/* 0x6C   108. &squot;l&squot; */
id|_ACPI_LO
comma
multiline_comment|/* 0x6D   109. &squot;m&squot; */
id|_ACPI_LO
comma
multiline_comment|/* 0x6E   110. &squot;n&squot; */
id|_ACPI_LO
comma
multiline_comment|/* 0x6F   111. &squot;o&squot; */
id|_ACPI_LO
comma
multiline_comment|/* 0x70   112. &squot;p&squot; */
id|_ACPI_LO
comma
multiline_comment|/* 0x71   113. &squot;q&squot; */
id|_ACPI_LO
comma
multiline_comment|/* 0x72   114. &squot;r&squot; */
id|_ACPI_LO
comma
multiline_comment|/* 0x73   115. &squot;s&squot; */
id|_ACPI_LO
comma
multiline_comment|/* 0x74   116. &squot;t&squot; */
id|_ACPI_LO
comma
multiline_comment|/* 0x75   117. &squot;u&squot; */
id|_ACPI_LO
comma
multiline_comment|/* 0x76   118. &squot;v&squot; */
id|_ACPI_LO
comma
multiline_comment|/* 0x77   119. &squot;w&squot; */
id|_ACPI_LO
comma
multiline_comment|/* 0x78   120. &squot;x&squot; */
id|_ACPI_LO
comma
multiline_comment|/* 0x79   121. &squot;y&squot; */
id|_ACPI_LO
comma
multiline_comment|/* 0x7A   122. &squot;z&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x7B   123. &squot;{&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x7C   124. &squot;|&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x7D   125. &squot;}&squot; */
id|_ACPI_PU
comma
multiline_comment|/* 0x7E   126. &squot;~&squot; */
id|_ACPI_CN
comma
multiline_comment|/* 0x7F   127.     */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0x80 to 0x8F    */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0x90 to 0x9F    */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0xA0 to 0xAF    */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0xB0 to 0xBF    */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0xC0 to 0xCF    */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0xD0 to 0xDF    */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0xE0 to 0xEF    */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
multiline_comment|/* 0xF0 to 0x100   */
)brace
suffix:semicolon
DECL|macro|IS_UPPER
mdefine_line|#define IS_UPPER(c)  (_acpi_ctype[(unsigned char)(c)] &amp; (_ACPI_UP))
DECL|macro|IS_LOWER
mdefine_line|#define IS_LOWER(c)  (_acpi_ctype[(unsigned char)(c)] &amp; (_ACPI_LO))
DECL|macro|IS_DIGIT
mdefine_line|#define IS_DIGIT(c)  (_acpi_ctype[(unsigned char)(c)] &amp; (_ACPI_DI))
DECL|macro|IS_SPACE
mdefine_line|#define IS_SPACE(c)  (_acpi_ctype[(unsigned char)(c)] &amp; (_ACPI_SP))
DECL|macro|IS_XDIGIT
mdefine_line|#define IS_XDIGIT(c) (_acpi_ctype[(unsigned char)(c)] &amp; (_ACPI_XD))
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_cm_to_upper&n; *&n; * PARAMETERS:&n; *&n; * RETURN:&n; *&n; * DESCRIPTION: Convert character to uppercase&n; *&n; ******************************************************************************/
id|u32
DECL|function|acpi_cm_to_upper
id|acpi_cm_to_upper
(paren
id|u32
id|c
)paren
(brace
r_return
(paren
id|IS_LOWER
c_func
(paren
id|c
)paren
ques
c_cond
(paren
(paren
id|c
)paren
op_minus
l_int|0x20
)paren
suffix:colon
(paren
id|c
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_cm_to_lower&n; *&n; * PARAMETERS:&n; *&n; * RETURN:&n; *&n; * DESCRIPTION: Convert character to lowercase&n; *&n; ******************************************************************************/
id|u32
DECL|function|acpi_cm_to_lower
id|acpi_cm_to_lower
(paren
id|u32
id|c
)paren
(brace
r_return
(paren
id|IS_UPPER
c_func
(paren
id|c
)paren
ques
c_cond
(paren
(paren
id|c
)paren
op_plus
l_int|0x20
)paren
suffix:colon
(paren
id|c
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    strupr&n; *&n; * PARAMETERS:  Src_string      - The source string to convert to&n; *&n; * RETURN:      Src_string&n; *&n; * DESCRIPTION: Convert string to uppercase&n; *&n; ******************************************************************************/
id|NATIVE_CHAR
op_star
DECL|function|acpi_cm_strupr
id|acpi_cm_strupr
(paren
id|NATIVE_CHAR
op_star
id|src_string
)paren
(brace
id|NATIVE_CHAR
op_star
id|string
suffix:semicolon
multiline_comment|/* Walk entire string, uppercasing the letters */
r_for
c_loop
(paren
id|string
op_assign
id|src_string
suffix:semicolon
op_star
id|string
suffix:semicolon
)paren
(brace
op_star
id|string
op_assign
(paren
r_char
)paren
id|acpi_cm_to_upper
(paren
op_star
id|string
)paren
suffix:semicolon
id|string
op_increment
suffix:semicolon
)brace
r_return
(paren
id|src_string
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    strstr&n; *&n; * PARAMETERS:  String1       -&n; *              String2&n; *&n; * RETURN:&n; *&n; * DESCRIPTION: Checks if String2 occurs in String1. This is not really a&n; *              full implementation of strstr, only sufficient for command&n; *              matching&n; *&n; ******************************************************************************/
id|NATIVE_CHAR
op_star
DECL|function|acpi_cm_strstr
id|acpi_cm_strstr
(paren
id|NATIVE_CHAR
op_star
id|string1
comma
id|NATIVE_CHAR
op_star
id|string2
)paren
(brace
id|NATIVE_CHAR
op_star
id|string
suffix:semicolon
r_if
c_cond
(paren
id|acpi_cm_strlen
(paren
id|string2
)paren
OG
id|acpi_cm_strlen
(paren
id|string1
)paren
)paren
(brace
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* Walk entire string, comparing the letters */
r_for
c_loop
(paren
id|string
op_assign
id|string1
suffix:semicolon
op_star
id|string2
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
op_star
id|string2
op_ne
op_star
id|string
)paren
(brace
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|string2
op_increment
suffix:semicolon
id|string
op_increment
suffix:semicolon
)brace
r_return
(paren
id|string1
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    strtoul&n; *&n; * PARAMETERS:  String          - Null terminated string&n; *              Terminater      - Where a pointer to the terminating byte is returned&n; *              Base            - Radix of the string&n; *&n; * RETURN:      Converted value&n; *&n; * DESCRIPTION: Convert a string into an unsigned value.&n; *&n; ******************************************************************************/
id|u32
DECL|function|acpi_cm_strtoul
id|acpi_cm_strtoul
(paren
r_const
id|NATIVE_CHAR
op_star
id|string
comma
id|NATIVE_CHAR
op_star
op_star
id|terminator
comma
id|NATIVE_UINT
id|base
)paren
(brace
id|u32
id|converted
op_assign
l_int|0
suffix:semicolon
id|u32
id|index
suffix:semicolon
id|u32
id|sign
suffix:semicolon
r_const
id|NATIVE_CHAR
op_star
id|string_start
suffix:semicolon
id|u32
id|return_value
op_assign
l_int|0
suffix:semicolon
id|ACPI_STATUS
id|status
op_assign
id|AE_OK
suffix:semicolon
multiline_comment|/*&n;&t; * Save the value of the pointer to the buffer&squot;s first&n;&t; * character, save the current errno value, and then&n;&t; * skip over any white space in the buffer:&n;&t; */
id|string_start
op_assign
id|string
suffix:semicolon
r_while
c_loop
(paren
id|IS_SPACE
(paren
op_star
id|string
)paren
op_logical_or
op_star
id|string
op_eq
l_char|&squot;&bslash;t&squot;
)paren
(brace
op_increment
id|string
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The buffer may contain an optional plus or minus sign.&n;&t; * If it does, then skip over it but remember what is was:&n;&t; */
r_if
c_cond
(paren
op_star
id|string
op_eq
l_char|&squot;-&squot;
)paren
(brace
id|sign
op_assign
id|NEGATIVE
suffix:semicolon
op_increment
id|string
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
id|string
op_eq
l_char|&squot;+&squot;
)paren
(brace
op_increment
id|string
suffix:semicolon
id|sign
op_assign
id|POSITIVE
suffix:semicolon
)brace
r_else
(brace
id|sign
op_assign
id|POSITIVE
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If the input parameter Base is zero, then we need to&n;&t; * determine if it is octal, decimal, or hexadecimal:&n;&t; */
r_if
c_cond
(paren
id|base
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_star
id|string
op_eq
l_char|&squot;0&squot;
)paren
(brace
r_if
c_cond
(paren
id|acpi_cm_to_lower
(paren
op_star
(paren
op_increment
id|string
)paren
)paren
op_eq
l_char|&squot;x&squot;
)paren
(brace
id|base
op_assign
l_int|16
suffix:semicolon
op_increment
id|string
suffix:semicolon
)brace
r_else
(brace
id|base
op_assign
l_int|8
suffix:semicolon
)brace
)brace
r_else
(brace
id|base
op_assign
l_int|10
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|base
template_param
l_int|36
)paren
(brace
multiline_comment|/*&n;&t;&t; * The specified Base parameter is not in the domain of&n;&t;&t; * this function:&n;&t;&t; */
r_goto
id|done
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * For octal and hexadecimal bases, skip over the leading&n;&t; * 0 or 0x, if they are present.&n;&t; */
r_if
c_cond
(paren
id|base
op_eq
l_int|8
op_logical_and
op_star
id|string
op_eq
l_char|&squot;0&squot;
)paren
(brace
id|string
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|base
op_eq
l_int|16
op_logical_and
op_star
id|string
op_eq
l_char|&squot;0&squot;
op_logical_and
id|acpi_cm_to_lower
(paren
op_star
(paren
op_increment
id|string
)paren
)paren
op_eq
l_char|&squot;x&squot;
)paren
(brace
id|string
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Main loop: convert the string to an unsigned long:&n;&t; */
r_while
c_loop
(paren
op_star
id|string
)paren
(brace
r_if
c_cond
(paren
id|IS_DIGIT
(paren
op_star
id|string
)paren
)paren
(brace
id|index
op_assign
op_star
id|string
op_minus
l_char|&squot;0&squot;
suffix:semicolon
)brace
r_else
(brace
id|index
op_assign
id|acpi_cm_to_upper
(paren
op_star
id|string
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_UPPER
(paren
id|index
)paren
)paren
(brace
id|index
op_assign
id|index
op_minus
l_char|&squot;A&squot;
op_plus
l_int|10
suffix:semicolon
)brace
r_else
(brace
r_goto
id|done
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|index
op_ge
id|base
)paren
(brace
r_goto
id|done
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Check to see if value is out of range:&n;&t;&t; */
r_if
c_cond
(paren
id|return_value
OG
(paren
(paren
id|ACPI_UINT32_MAX
op_minus
(paren
id|u32
)paren
id|index
)paren
op_div
(paren
id|u32
)paren
id|base
)paren
)paren
(brace
id|status
op_assign
id|AE_ERROR
suffix:semicolon
id|return_value
op_assign
l_int|0L
suffix:semicolon
multiline_comment|/* reset */
)brace
r_else
(brace
id|return_value
op_mul_assign
id|base
suffix:semicolon
id|return_value
op_add_assign
id|index
suffix:semicolon
id|converted
op_assign
l_int|1
suffix:semicolon
)brace
op_increment
id|string
suffix:semicolon
)brace
id|done
suffix:colon
multiline_comment|/*&n;&t; * If appropriate, update the caller&squot;s pointer to the next&n;&t; * unconverted character in the buffer.&n;&t; */
r_if
c_cond
(paren
id|terminator
)paren
(brace
r_if
c_cond
(paren
id|converted
op_eq
l_int|0
op_logical_and
id|return_value
op_eq
l_int|0L
op_logical_and
id|string
op_ne
l_int|NULL
)paren
(brace
op_star
id|terminator
op_assign
(paren
id|NATIVE_CHAR
op_star
)paren
id|string_start
suffix:semicolon
)brace
r_else
(brace
op_star
id|terminator
op_assign
(paren
id|NATIVE_CHAR
op_star
)paren
id|string
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|status
op_eq
id|AE_ERROR
)paren
(brace
id|return_value
op_assign
id|ACPI_UINT32_MAX
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If a minus sign was present, then &quot;the conversion is negated&quot;:&n;&t; */
r_if
c_cond
(paren
id|sign
op_eq
id|NEGATIVE
)paren
(brace
id|return_value
op_assign
(paren
id|ACPI_UINT32_MAX
op_minus
id|return_value
)paren
op_plus
l_int|1
suffix:semicolon
)brace
r_return
(paren
id|return_value
)paren
suffix:semicolon
)brace
macro_line|#endif /* ACPI_USE_SYSTEM_CLIBRARY */
eof
