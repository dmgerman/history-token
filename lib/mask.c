multiline_comment|/*&n; * lib/mask.c&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2003 Silicon Graphics, Inc.  All Rights Reserved.&n; */
multiline_comment|/*&n; * Routines to manipulate multi-word bit masks, such as cpumasks.&n; *&n; * The ascii representation of multi-word bit masks displays each&n; * 32bit word in hex (not zero filled), and for masks longer than&n; * one word, uses a comma separator between words.  Words are&n; * displayed in big-endian order most significant first.  And hex&n; * digits within a word are also in big-endian order, of course.&n; *&n; * Examples:&n; *   A mask with just bit 0 set displays as &quot;1&quot;.&n; *   A mask with just bit 127 set displays as &quot;80000000,0,0,0&quot;.&n; *   A mask with just bit 64 set displays as &quot;1,0,0&quot;.&n; *   A mask with bits 0, 1, 2, 4, 8, 16, 32 and 64 set displays&n; *     as &quot;1,1,10117&quot;.  The first &quot;1&quot; is for bit 64, the second&n; *     for bit 32, the third for bit 16, and so forth, to the&n; *     &quot;7&quot;, which is for bits 2, 1 and 0.&n; *   A mask with bits 32 through 39 set displays as &quot;ff,0&quot;.&n; *&n; * The internal binary representation of masks is as one or&n; * an array of unsigned longs, perhaps wrapped in a struct for&n; * convenient use as an lvalue.  The following code doesn&squot;t know&n; * about any such struct details, relying on inline macros in&n; * files such as cpumask.h to pass in an unsigned long pointer&n; * and a length (in bytes), describing the mask contents.&n; * The 32bit words in the array are in little-endian order,&n; * low order word first.  Beware that this is the reverse order&n; * of the ascii representation.&n; *&n; * Even though the size of the input mask is provided in bytes,&n; * the following code may assume that the mask is a multiple of&n; * 32 or 64 bit words long, and ignore any fractional portion&n; * of a word at the end.  The main reason the size is passed in&n; * bytes is because it is so easy to write &squot;sizeof(somemask_t)&squot;&n; * in the macros.&n; *&n; * Masks are not a single,simple type, like classic &squot;C&squot;&n; * nul-term strings.  Rather they are a family of types, one&n; * for each different length.  Inline macros are used to pick&n; * up the actual length, where it is known to the compiler, and&n; * pass it down to these routines, which work on any specified&n; * length array of unsigned longs.  Poor man&squot;s templates.&n; *&n; * Many of the inline macros don&squot;t call into the following&n; * routines.  Some of them call into other kernel routines,&n; * such as memset(), set_bit() or ffs().  Some of them can&n; * accomplish their task right inline, such as returning the&n; * size or address of the unsigned long array, or optimized&n; * versions of the macros for the most common case of an array&n; * of a single unsigned long.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/gfp.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|MAX_HEX_PER_BYTE
mdefine_line|#define MAX_HEX_PER_BYTE 4&t;/* dont need &gt; 4 hex chars to encode byte */
DECL|macro|BASE
mdefine_line|#define BASE 16&t;&t;&t;/* masks are input in hex (base 16) */
DECL|macro|NUL
mdefine_line|#define NUL ((char)&squot;&bslash;0&squot;)&t;/* nul-terminator */
multiline_comment|/**&n; * __mask_snprintf_len - represent multi-word bit mask as string.&n; * @buf: The buffer to place the result into&n; * @buflen: The size of the buffer, including the trailing null space&n; * @maskp: Points to beginning of multi-word bit mask.&n; * @maskbytes: Number of bytes in bit mask at maskp.&n; *&n; * This routine is expected to be called from a macro such as:&n; *&n; * #define cpumask_snprintf(buf, buflen, mask) &bslash;&n; *   __mask_snprintf_len(buf, buflen, cpus_addr(mask), sizeof(mask))&n; */
DECL|function|__mask_snprintf_len
r_int
id|__mask_snprintf_len
c_func
(paren
r_char
op_star
id|buf
comma
r_int
r_int
id|buflen
comma
r_const
r_int
r_int
op_star
id|maskp
comma
r_int
r_int
id|maskbytes
)paren
(brace
id|u32
op_star
id|wordp
op_assign
(paren
id|u32
op_star
)paren
id|maskp
suffix:semicolon
r_int
id|i
op_assign
id|maskbytes
op_div
r_sizeof
(paren
id|u32
)paren
op_minus
l_int|1
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|sep
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_while
c_loop
(paren
id|i
op_ge
l_int|1
op_logical_and
id|wordp
(braket
id|i
)braket
op_eq
l_int|0
)paren
id|i
op_decrement
suffix:semicolon
r_while
c_loop
(paren
id|i
op_ge
l_int|0
)paren
(brace
id|len
op_add_assign
id|snprintf
c_func
(paren
id|buf
op_plus
id|len
comma
id|buflen
op_minus
id|len
comma
l_string|&quot;%s%x&quot;
comma
id|sep
comma
id|wordp
(braket
id|i
)braket
)paren
suffix:semicolon
id|sep
op_assign
l_string|&quot;,&quot;
suffix:semicolon
id|i
op_decrement
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/**&n; * __mask_parse_len - parse user string into maskbytes mask at maskp&n; * @ubuf: The user buffer from which to take the string&n; * @ubuflen: The size of this buffer, including the terminating char&n; * @maskp: Place resulting mask (array of unsigned longs) here&n; * @masklen: Construct mask at @maskp to have exactly @masklen bytes&n; *&n; * @masklen is a multiple of sizeof(unsigned long).  A mask of&n; * @masklen bytes is constructed starting at location @maskp.&n; * The value of this mask is specified by the user provided&n; * string starting at address @ubuf.  Only bytes in the range&n; * [@ubuf, @ubuf+@ubuflen) can be read from user space, and&n; * reading will stop after the first byte that is not a comma&n; * or valid hex digit in the characters [,0-9a-fA-F], or at&n; * the point @ubuf+@ubuflen, whichever comes first.&n; *&n; * Since the user only needs about 2.25 chars per byte to encode&n; * a mask (one char per nibble plus one comma separator or nul&n; * terminator per byte), we blow them off with -EINVAL if they&n; * claim a @ubuflen more than 4 (MAX_HEX_PER_BYTE) times maskbytes.&n; * An empty word (delimited by two consecutive commas, for example)&n; * is taken as zero.  If @buflen is zero, the entire @maskp is set&n; * to zero.&n; *&n; * If the user provides fewer comma-separated ascii words&n; * than there are 32 bit words in maskbytes, we zero fill the&n; * remaining high order words.  If they provide more, they fail&n; * with -EINVAL.  Each comma-separate ascii word is taken as&n; * a hex representation; leading zeros are ignored, and do not&n; * imply octal.  &squot;00e1&squot;, &squot;e1&squot;, &squot;00E1&squot;, &squot;E1&squot; are all the same.&n; * If user passes a word that is larger than fits in a u32,&n; * they fail with -EOVERFLOW.&n; */
DECL|function|__mask_parse_len
r_int
id|__mask_parse_len
c_func
(paren
r_const
r_char
id|__user
op_star
id|ubuf
comma
r_int
r_int
id|ubuflen
comma
r_int
r_int
op_star
id|maskp
comma
r_int
r_int
id|maskbytes
)paren
(brace
r_char
id|buf
(braket
id|maskbytes
op_star
id|MAX_HEX_PER_BYTE
op_plus
r_sizeof
(paren
id|NUL
)paren
)braket
suffix:semicolon
r_char
op_star
id|bp
op_assign
id|buf
suffix:semicolon
id|u32
op_star
id|wordp
op_assign
(paren
id|u32
op_star
)paren
id|maskp
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_if
c_cond
(paren
id|ubuflen
OG
id|maskbytes
op_star
id|MAX_HEX_PER_BYTE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|buf
comma
id|ubuf
comma
id|ubuflen
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|buf
(braket
id|ubuflen
)braket
op_assign
id|NUL
suffix:semicolon
multiline_comment|/*&n;&t; * Put the words into wordp[] in big-endian order,&n;&t; * then go back and reverse them.&n;&t; */
id|memset
c_func
(paren
id|wordp
comma
l_int|0
comma
id|maskbytes
)paren
suffix:semicolon
id|i
op_assign
id|j
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|p
op_assign
id|strsep
c_func
(paren
op_amp
id|bp
comma
l_string|&quot;,&quot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
r_int
r_int
id|t
suffix:semicolon
r_if
c_cond
(paren
id|j
op_eq
id|maskbytes
op_div
r_sizeof
(paren
id|u32
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|t
op_assign
id|simple_strtoull
c_func
(paren
id|p
comma
l_int|0
comma
id|BASE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t
op_ne
(paren
id|u32
)paren
id|t
)paren
r_return
op_minus
id|EOVERFLOW
suffix:semicolon
id|wordp
(braket
id|j
op_increment
)braket
op_assign
id|t
suffix:semicolon
)brace
op_decrement
id|j
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|j
)paren
(brace
id|u32
id|t
op_assign
id|wordp
(braket
id|i
)braket
suffix:semicolon
id|wordp
(braket
id|i
)braket
op_assign
id|wordp
(braket
id|j
)braket
suffix:semicolon
id|wordp
(braket
id|j
)braket
op_assign
id|t
suffix:semicolon
id|i
op_increment
comma
op_decrement
id|j
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
