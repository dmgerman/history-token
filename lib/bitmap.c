multiline_comment|/*&n; * lib/bitmap.c&n; * Helper functions for bitmap.h.&n; *&n; * This source code is licensed under the GNU General Public License,&n; * Version 2.  See the file COPYING for more details.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/bitmap.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/*&n; * bitmaps provide an array of bits, implemented using an an&n; * array of unsigned longs.  The number of valid bits in a&n; * given bitmap need not be an exact multiple of BITS_PER_LONG.&n; *&n; * The possible unused bits in the last, partially used word&n; * of a bitmap are &squot;don&squot;t care&squot;.  The implementation makes&n; * no particular effort to keep them zero.  It ensures that&n; * their value will not affect the results of any operation.&n; * The bitmap operations that return Boolean (bitmap_empty,&n; * for example) or scalar (bitmap_weight, for example) results&n; * carefully filter out these unused bits from impacting their&n; * results.&n; *&n; * These operations actually hold to a slightly stronger rule:&n; * if you don&squot;t input any bitmaps to these ops that have some&n; * unused bits set, then they won&squot;t output any set unused bits&n; * in output bitmaps.&n; */
DECL|function|bitmap_empty
r_int
id|bitmap_empty
c_func
(paren
r_const
r_int
r_int
op_star
id|bitmap
comma
r_int
id|bits
)paren
(brace
r_int
id|k
comma
id|lim
op_assign
id|bits
op_div
id|BITS_PER_LONG
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|lim
suffix:semicolon
op_increment
id|k
)paren
r_if
c_cond
(paren
id|bitmap
(braket
id|k
)braket
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|bits
op_mod
id|BITS_PER_LONG
)paren
r_if
c_cond
(paren
id|bitmap
(braket
id|k
)braket
op_amp
(paren
(paren
l_int|1UL
op_lshift
(paren
id|bits
op_mod
id|BITS_PER_LONG
)paren
)paren
op_minus
l_int|1
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|bitmap_empty
id|EXPORT_SYMBOL
c_func
(paren
id|bitmap_empty
)paren
suffix:semicolon
DECL|function|bitmap_full
r_int
id|bitmap_full
c_func
(paren
r_const
r_int
r_int
op_star
id|bitmap
comma
r_int
id|bits
)paren
(brace
r_int
id|k
comma
id|lim
op_assign
id|bits
op_div
id|BITS_PER_LONG
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|lim
suffix:semicolon
op_increment
id|k
)paren
r_if
c_cond
(paren
op_complement
id|bitmap
(braket
id|k
)braket
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|bits
op_mod
id|BITS_PER_LONG
)paren
r_if
c_cond
(paren
op_complement
id|bitmap
(braket
id|k
)braket
op_amp
(paren
(paren
l_int|1UL
op_lshift
(paren
id|bits
op_mod
id|BITS_PER_LONG
)paren
)paren
op_minus
l_int|1
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|bitmap_full
id|EXPORT_SYMBOL
c_func
(paren
id|bitmap_full
)paren
suffix:semicolon
DECL|function|bitmap_equal
r_int
id|bitmap_equal
c_func
(paren
r_const
r_int
r_int
op_star
id|bitmap1
comma
r_const
r_int
r_int
op_star
id|bitmap2
comma
r_int
id|bits
)paren
(brace
r_int
id|k
comma
id|lim
op_assign
id|bits
op_div
id|BITS_PER_LONG
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|lim
suffix:semicolon
op_increment
id|k
)paren
r_if
c_cond
(paren
id|bitmap1
(braket
id|k
)braket
op_ne
id|bitmap2
(braket
id|k
)braket
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|bits
op_mod
id|BITS_PER_LONG
)paren
r_if
c_cond
(paren
(paren
id|bitmap1
(braket
id|k
)braket
op_xor
id|bitmap2
(braket
id|k
)braket
)paren
op_amp
(paren
(paren
l_int|1UL
op_lshift
(paren
id|bits
op_mod
id|BITS_PER_LONG
)paren
)paren
op_minus
l_int|1
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|bitmap_equal
id|EXPORT_SYMBOL
c_func
(paren
id|bitmap_equal
)paren
suffix:semicolon
DECL|function|bitmap_complement
r_void
id|bitmap_complement
c_func
(paren
r_int
r_int
op_star
id|dst
comma
r_const
r_int
r_int
op_star
id|src
comma
r_int
id|bits
)paren
(brace
r_int
id|k
comma
id|lim
op_assign
id|bits
op_div
id|BITS_PER_LONG
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|lim
suffix:semicolon
op_increment
id|k
)paren
id|dst
(braket
id|k
)braket
op_assign
op_complement
id|src
(braket
id|k
)braket
suffix:semicolon
r_if
c_cond
(paren
id|bits
op_mod
id|BITS_PER_LONG
)paren
id|dst
(braket
id|k
)braket
op_assign
op_complement
id|src
(braket
id|k
)braket
op_amp
(paren
(paren
l_int|1UL
op_lshift
(paren
id|bits
op_mod
id|BITS_PER_LONG
)paren
)paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
DECL|variable|bitmap_complement
id|EXPORT_SYMBOL
c_func
(paren
id|bitmap_complement
)paren
suffix:semicolon
multiline_comment|/*&n; * bitmap_shift_right - logical right shift of the bits in a bitmap&n; *   @dst - destination bitmap&n; *   @src - source bitmap&n; *   @nbits - shift by this many bits&n; *   @bits - bitmap size, in bits&n; *&n; * Shifting right (dividing) means moving bits in the MS -&gt; LS bit&n; * direction.  Zeros are fed into the vacated MS positions and the&n; * LS bits shifted off the bottom are lost.&n; */
DECL|function|bitmap_shift_right
r_void
id|bitmap_shift_right
c_func
(paren
r_int
r_int
op_star
id|dst
comma
r_const
r_int
r_int
op_star
id|src
comma
r_int
id|shift
comma
r_int
id|bits
)paren
(brace
r_int
id|k
comma
id|lim
op_assign
id|BITS_TO_LONGS
c_func
(paren
id|bits
)paren
comma
id|left
op_assign
id|bits
op_mod
id|BITS_PER_LONG
suffix:semicolon
r_int
id|off
op_assign
id|shift
op_div
id|BITS_PER_LONG
comma
id|rem
op_assign
id|shift
op_mod
id|BITS_PER_LONG
suffix:semicolon
r_int
r_int
id|mask
op_assign
(paren
l_int|1UL
op_lshift
id|left
)paren
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|off
op_plus
id|k
OL
id|lim
suffix:semicolon
op_increment
id|k
)paren
(brace
r_int
r_int
id|upper
comma
id|lower
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If shift is not word aligned, take lower rem bits of&n;&t;&t; * word above and make them the top rem bits of result.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|rem
op_logical_or
id|off
op_plus
id|k
op_plus
l_int|1
op_ge
id|lim
)paren
id|upper
op_assign
l_int|0
suffix:semicolon
r_else
(brace
id|upper
op_assign
id|src
(braket
id|off
op_plus
id|k
op_plus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|off
op_plus
id|k
op_plus
l_int|1
op_eq
id|lim
op_minus
l_int|1
op_logical_and
id|left
)paren
id|upper
op_and_assign
id|mask
suffix:semicolon
)brace
id|lower
op_assign
id|src
(braket
id|off
op_plus
id|k
)braket
suffix:semicolon
r_if
c_cond
(paren
id|left
op_logical_and
id|off
op_plus
id|k
op_eq
id|lim
op_minus
l_int|1
)paren
id|lower
op_and_assign
id|mask
suffix:semicolon
id|dst
(braket
id|k
)braket
op_assign
id|upper
op_lshift
(paren
id|BITS_PER_LONG
op_minus
id|rem
)paren
op_or
id|lower
op_rshift
id|rem
suffix:semicolon
r_if
c_cond
(paren
id|left
op_logical_and
id|k
op_eq
id|lim
op_minus
l_int|1
)paren
id|dst
(braket
id|k
)braket
op_and_assign
id|mask
suffix:semicolon
)brace
r_if
c_cond
(paren
id|off
)paren
id|memset
c_func
(paren
op_amp
id|dst
(braket
id|lim
op_minus
id|off
)braket
comma
l_int|0
comma
id|off
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
)brace
DECL|variable|bitmap_shift_right
id|EXPORT_SYMBOL
c_func
(paren
id|bitmap_shift_right
)paren
suffix:semicolon
multiline_comment|/*&n; * bitmap_shift_left - logical left shift of the bits in a bitmap&n; *   @dst - destination bitmap&n; *   @src - source bitmap&n; *   @nbits - shift by this many bits&n; *   @bits - bitmap size, in bits&n; *&n; * Shifting left (multiplying) means moving bits in the LS -&gt; MS&n; * direction.  Zeros are fed into the vacated LS bit positions&n; * and those MS bits shifted off the top are lost.&n; */
DECL|function|bitmap_shift_left
r_void
id|bitmap_shift_left
c_func
(paren
r_int
r_int
op_star
id|dst
comma
r_const
r_int
r_int
op_star
id|src
comma
r_int
id|shift
comma
r_int
id|bits
)paren
(brace
r_int
id|k
comma
id|lim
op_assign
id|BITS_TO_LONGS
c_func
(paren
id|bits
)paren
comma
id|left
op_assign
id|bits
op_mod
id|BITS_PER_LONG
suffix:semicolon
r_int
id|off
op_assign
id|shift
op_div
id|BITS_PER_LONG
comma
id|rem
op_assign
id|shift
op_mod
id|BITS_PER_LONG
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
id|lim
op_minus
id|off
op_minus
l_int|1
suffix:semicolon
id|k
op_ge
l_int|0
suffix:semicolon
op_decrement
id|k
)paren
(brace
r_int
r_int
id|upper
comma
id|lower
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If shift is not word aligned, take upper rem bits of&n;&t;&t; * word below and make them the bottom rem bits of result.&n;&t;&t; */
r_if
c_cond
(paren
id|rem
op_logical_and
id|k
OG
l_int|0
)paren
id|lower
op_assign
id|src
(braket
id|k
op_minus
l_int|1
)braket
suffix:semicolon
r_else
id|lower
op_assign
l_int|0
suffix:semicolon
id|upper
op_assign
id|src
(braket
id|k
)braket
suffix:semicolon
r_if
c_cond
(paren
id|left
op_logical_and
id|k
op_eq
id|lim
op_minus
l_int|1
)paren
id|upper
op_and_assign
(paren
l_int|1UL
op_lshift
id|left
)paren
op_minus
l_int|1
suffix:semicolon
id|dst
(braket
id|k
op_plus
id|off
)braket
op_assign
id|lower
op_rshift
(paren
id|BITS_PER_LONG
op_minus
id|rem
)paren
op_or
id|upper
op_lshift
id|rem
suffix:semicolon
r_if
c_cond
(paren
id|left
op_logical_and
id|k
op_plus
id|off
op_eq
id|lim
op_minus
l_int|1
)paren
id|dst
(braket
id|k
op_plus
id|off
)braket
op_and_assign
(paren
l_int|1UL
op_lshift
id|left
)paren
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|off
)paren
id|memset
c_func
(paren
id|dst
comma
l_int|0
comma
id|off
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
)brace
DECL|variable|bitmap_shift_left
id|EXPORT_SYMBOL
c_func
(paren
id|bitmap_shift_left
)paren
suffix:semicolon
DECL|function|bitmap_and
r_void
id|bitmap_and
c_func
(paren
r_int
r_int
op_star
id|dst
comma
r_const
r_int
r_int
op_star
id|bitmap1
comma
r_const
r_int
r_int
op_star
id|bitmap2
comma
r_int
id|bits
)paren
(brace
r_int
id|k
suffix:semicolon
r_int
id|nr
op_assign
id|BITS_TO_LONGS
c_func
(paren
id|bits
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|nr
suffix:semicolon
id|k
op_increment
)paren
id|dst
(braket
id|k
)braket
op_assign
id|bitmap1
(braket
id|k
)braket
op_amp
id|bitmap2
(braket
id|k
)braket
suffix:semicolon
)brace
DECL|variable|bitmap_and
id|EXPORT_SYMBOL
c_func
(paren
id|bitmap_and
)paren
suffix:semicolon
DECL|function|bitmap_or
r_void
id|bitmap_or
c_func
(paren
r_int
r_int
op_star
id|dst
comma
r_const
r_int
r_int
op_star
id|bitmap1
comma
r_const
r_int
r_int
op_star
id|bitmap2
comma
r_int
id|bits
)paren
(brace
r_int
id|k
suffix:semicolon
r_int
id|nr
op_assign
id|BITS_TO_LONGS
c_func
(paren
id|bits
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|nr
suffix:semicolon
id|k
op_increment
)paren
id|dst
(braket
id|k
)braket
op_assign
id|bitmap1
(braket
id|k
)braket
op_or
id|bitmap2
(braket
id|k
)braket
suffix:semicolon
)brace
DECL|variable|bitmap_or
id|EXPORT_SYMBOL
c_func
(paren
id|bitmap_or
)paren
suffix:semicolon
DECL|function|bitmap_xor
r_void
id|bitmap_xor
c_func
(paren
r_int
r_int
op_star
id|dst
comma
r_const
r_int
r_int
op_star
id|bitmap1
comma
r_const
r_int
r_int
op_star
id|bitmap2
comma
r_int
id|bits
)paren
(brace
r_int
id|k
suffix:semicolon
r_int
id|nr
op_assign
id|BITS_TO_LONGS
c_func
(paren
id|bits
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|nr
suffix:semicolon
id|k
op_increment
)paren
id|dst
(braket
id|k
)braket
op_assign
id|bitmap1
(braket
id|k
)braket
op_xor
id|bitmap2
(braket
id|k
)braket
suffix:semicolon
)brace
DECL|variable|bitmap_xor
id|EXPORT_SYMBOL
c_func
(paren
id|bitmap_xor
)paren
suffix:semicolon
DECL|function|bitmap_andnot
r_void
id|bitmap_andnot
c_func
(paren
r_int
r_int
op_star
id|dst
comma
r_const
r_int
r_int
op_star
id|bitmap1
comma
r_const
r_int
r_int
op_star
id|bitmap2
comma
r_int
id|bits
)paren
(brace
r_int
id|k
suffix:semicolon
r_int
id|nr
op_assign
id|BITS_TO_LONGS
c_func
(paren
id|bits
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|nr
suffix:semicolon
id|k
op_increment
)paren
id|dst
(braket
id|k
)braket
op_assign
id|bitmap1
(braket
id|k
)braket
op_amp
op_complement
id|bitmap2
(braket
id|k
)braket
suffix:semicolon
)brace
DECL|variable|bitmap_andnot
id|EXPORT_SYMBOL
c_func
(paren
id|bitmap_andnot
)paren
suffix:semicolon
DECL|function|bitmap_intersects
r_int
id|bitmap_intersects
c_func
(paren
r_const
r_int
r_int
op_star
id|bitmap1
comma
r_const
r_int
r_int
op_star
id|bitmap2
comma
r_int
id|bits
)paren
(brace
r_int
id|k
comma
id|lim
op_assign
id|bits
op_div
id|BITS_PER_LONG
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|lim
suffix:semicolon
op_increment
id|k
)paren
r_if
c_cond
(paren
id|bitmap1
(braket
id|k
)braket
op_amp
id|bitmap2
(braket
id|k
)braket
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|bits
op_mod
id|BITS_PER_LONG
)paren
r_if
c_cond
(paren
(paren
id|bitmap1
(braket
id|k
)braket
op_amp
id|bitmap2
(braket
id|k
)braket
)paren
op_amp
(paren
(paren
l_int|1UL
op_lshift
(paren
id|bits
op_mod
id|BITS_PER_LONG
)paren
)paren
op_minus
l_int|1
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|bitmap_intersects
id|EXPORT_SYMBOL
c_func
(paren
id|bitmap_intersects
)paren
suffix:semicolon
DECL|function|bitmap_subset
r_int
id|bitmap_subset
c_func
(paren
r_const
r_int
r_int
op_star
id|bitmap1
comma
r_const
r_int
r_int
op_star
id|bitmap2
comma
r_int
id|bits
)paren
(brace
r_int
id|k
comma
id|lim
op_assign
id|bits
op_div
id|BITS_PER_LONG
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|lim
suffix:semicolon
op_increment
id|k
)paren
r_if
c_cond
(paren
id|bitmap1
(braket
id|k
)braket
op_amp
op_complement
id|bitmap2
(braket
id|k
)braket
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|bits
op_mod
id|BITS_PER_LONG
)paren
r_if
c_cond
(paren
(paren
id|bitmap1
(braket
id|k
)braket
op_amp
op_complement
id|bitmap2
(braket
id|k
)braket
)paren
op_amp
(paren
(paren
l_int|1UL
op_lshift
(paren
id|bits
op_mod
id|BITS_PER_LONG
)paren
)paren
op_minus
l_int|1
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|bitmap_subset
id|EXPORT_SYMBOL
c_func
(paren
id|bitmap_subset
)paren
suffix:semicolon
macro_line|#if BITS_PER_LONG == 32
DECL|function|bitmap_weight
r_int
id|bitmap_weight
c_func
(paren
r_const
r_int
r_int
op_star
id|bitmap
comma
r_int
id|bits
)paren
(brace
r_int
id|k
comma
id|w
op_assign
l_int|0
comma
id|lim
op_assign
id|bits
op_div
id|BITS_PER_LONG
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|lim
suffix:semicolon
id|k
op_increment
)paren
id|w
op_add_assign
id|hweight32
c_func
(paren
id|bitmap
(braket
id|k
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bits
op_mod
id|BITS_PER_LONG
)paren
id|w
op_add_assign
id|hweight32
c_func
(paren
id|bitmap
(braket
id|k
)braket
op_amp
(paren
(paren
l_int|1UL
op_lshift
(paren
id|bits
op_mod
id|BITS_PER_LONG
)paren
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_return
id|w
suffix:semicolon
)brace
macro_line|#else
DECL|function|bitmap_weight
r_int
id|bitmap_weight
c_func
(paren
r_const
r_int
r_int
op_star
id|bitmap
comma
r_int
id|bits
)paren
(brace
r_int
id|k
comma
id|w
op_assign
l_int|0
comma
id|lim
op_assign
id|bits
op_div
id|BITS_PER_LONG
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|lim
suffix:semicolon
id|k
op_increment
)paren
id|w
op_add_assign
id|hweight64
c_func
(paren
id|bitmap
(braket
id|k
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bits
op_mod
id|BITS_PER_LONG
)paren
id|w
op_add_assign
id|hweight64
c_func
(paren
id|bitmap
(braket
id|k
)braket
op_amp
(paren
(paren
l_int|1UL
op_lshift
(paren
id|bits
op_mod
id|BITS_PER_LONG
)paren
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_return
id|w
suffix:semicolon
)brace
macro_line|#endif
DECL|variable|bitmap_weight
id|EXPORT_SYMBOL
c_func
(paren
id|bitmap_weight
)paren
suffix:semicolon
multiline_comment|/*&n; * Bitmap printing &amp; parsing functions: first version by Bill Irwin,&n; * second version by Paul Jackson, third by Joe Korty.&n; */
DECL|macro|CHUNKSZ
mdefine_line|#define CHUNKSZ&t;&t;&t;&t;32
DECL|macro|nbits_to_hold_value
mdefine_line|#define nbits_to_hold_value(val)&t;fls(val)
DECL|macro|roundup_power2
mdefine_line|#define roundup_power2(val,modulus)&t;(((val) + (modulus) - 1) &amp; ~((modulus) - 1))
DECL|macro|unhex
mdefine_line|#define unhex(c)&t;&t;&t;(isdigit(c) ? (c - &squot;0&squot;) : (toupper(c) - &squot;A&squot; + 10))
multiline_comment|/**&n; * bitmap_scnprintf - convert bitmap to an ASCII hex string.&n; * @buf: byte buffer into which string is placed&n; * @buflen: reserved size of @buf, in bytes&n; * @maskp: pointer to bitmap to convert&n; * @nmaskbits: size of bitmap, in bits&n; *&n; * Exactly @nmaskbits bits are displayed.  Hex digits are grouped into&n; * comma-separated sets of eight digits per set.&n; */
DECL|function|bitmap_scnprintf
r_int
id|bitmap_scnprintf
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
id|nmaskbits
)paren
(brace
r_int
id|i
comma
id|word
comma
id|bit
comma
id|len
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|val
suffix:semicolon
r_const
r_char
op_star
id|sep
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_int
id|chunksz
suffix:semicolon
id|u32
id|chunkmask
suffix:semicolon
id|chunksz
op_assign
id|nmaskbits
op_amp
(paren
id|CHUNKSZ
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chunksz
op_eq
l_int|0
)paren
id|chunksz
op_assign
id|CHUNKSZ
suffix:semicolon
id|i
op_assign
id|roundup_power2
c_func
(paren
id|nmaskbits
comma
id|CHUNKSZ
)paren
op_minus
id|CHUNKSZ
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_sub_assign
id|CHUNKSZ
)paren
(brace
id|chunkmask
op_assign
(paren
(paren
l_int|1ULL
op_lshift
id|chunksz
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|word
op_assign
id|i
op_div
id|BITS_PER_LONG
suffix:semicolon
id|bit
op_assign
id|i
op_mod
id|BITS_PER_LONG
suffix:semicolon
id|val
op_assign
(paren
id|maskp
(braket
id|word
)braket
op_rshift
id|bit
)paren
op_amp
id|chunkmask
suffix:semicolon
id|len
op_add_assign
id|scnprintf
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
l_string|&quot;%s%0*lx&quot;
comma
id|sep
comma
(paren
id|chunksz
op_plus
l_int|3
)paren
op_div
l_int|4
comma
id|val
)paren
suffix:semicolon
id|chunksz
op_assign
id|CHUNKSZ
suffix:semicolon
id|sep
op_assign
l_string|&quot;,&quot;
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
DECL|variable|bitmap_scnprintf
id|EXPORT_SYMBOL
c_func
(paren
id|bitmap_scnprintf
)paren
suffix:semicolon
multiline_comment|/**&n; * bitmap_parse - convert an ASCII hex string into a bitmap.&n; * @buf: pointer to buffer in user space containing string.&n; * @buflen: buffer size in bytes.  If string is smaller than this&n; *    then it must be terminated with a &bslash;0.&n; * @maskp: pointer to bitmap array that will contain result.&n; * @nmaskbits: size of bitmap, in bits.&n; *&n; * Commas group hex digits into chunks.  Each chunk defines exactly 32&n; * bits of the resultant bitmask.  No chunk may specify a value larger&n; * than 32 bits (-EOVERFLOW), and if a chunk specifies a smaller value&n; * then leading 0-bits are prepended.  -EINVAL is returned for illegal&n; * characters and for grouping errors such as &quot;1,,5&quot;, &quot;,44&quot;, &quot;,&quot; and &quot;&quot;.&n; * Leading and trailing whitespace accepted, but not embedded whitespace.&n; */
DECL|function|bitmap_parse
r_int
id|bitmap_parse
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
id|nmaskbits
)paren
(brace
r_int
id|c
comma
id|old_c
comma
id|totaldigits
comma
id|ndigits
comma
id|nchunks
comma
id|nbits
suffix:semicolon
id|u32
id|chunk
suffix:semicolon
id|bitmap_zero
c_func
(paren
id|maskp
comma
id|nmaskbits
)paren
suffix:semicolon
id|nchunks
op_assign
id|nbits
op_assign
id|totaldigits
op_assign
id|c
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|chunk
op_assign
id|ndigits
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Get the next chunk of the bitmap */
r_while
c_loop
(paren
id|ubuflen
)paren
(brace
id|old_c
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|c
comma
id|ubuf
op_increment
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|ubuflen
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|isspace
c_func
(paren
id|c
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * If the last character was a space and the current&n;&t;&t;&t; * character isn&squot;t &squot;&bslash;0&squot;, we&squot;ve got embedded whitespace.&n;&t;&t;&t; * This is a no-no, so throw an error.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|totaldigits
op_logical_and
id|c
op_logical_and
id|isspace
c_func
(paren
id|old_c
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* A &squot;&bslash;0&squot; or a &squot;,&squot; signal the end of the chunk */
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;0&squot;
op_logical_or
id|c
op_eq
l_char|&squot;,&squot;
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|isxdigit
c_func
(paren
id|c
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Make sure there are at least 4 free bits in &squot;chunk&squot;.&n;&t;&t;&t; * If not, this hexdigit will overflow &squot;chunk&squot;, so&n;&t;&t;&t; * throw an error.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|chunk
op_amp
op_complement
(paren
(paren
l_int|1UL
op_lshift
(paren
id|CHUNKSZ
op_minus
l_int|4
)paren
)paren
op_minus
l_int|1
)paren
)paren
r_return
op_minus
id|EOVERFLOW
suffix:semicolon
id|chunk
op_assign
(paren
id|chunk
op_lshift
l_int|4
)paren
op_or
id|unhex
c_func
(paren
id|c
)paren
suffix:semicolon
id|ndigits
op_increment
suffix:semicolon
id|totaldigits
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ndigits
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|nchunks
op_eq
l_int|0
op_logical_and
id|chunk
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
id|bitmap_shift_left
c_func
(paren
id|maskp
comma
id|maskp
comma
id|CHUNKSZ
comma
id|nmaskbits
)paren
suffix:semicolon
op_star
id|maskp
op_or_assign
id|chunk
suffix:semicolon
id|nchunks
op_increment
suffix:semicolon
id|nbits
op_add_assign
(paren
id|nchunks
op_eq
l_int|1
)paren
ques
c_cond
id|nbits_to_hold_value
c_func
(paren
id|chunk
)paren
suffix:colon
id|CHUNKSZ
suffix:semicolon
r_if
c_cond
(paren
id|nbits
OG
id|nmaskbits
)paren
r_return
op_minus
id|EOVERFLOW
suffix:semicolon
)brace
r_while
c_loop
(paren
id|ubuflen
op_logical_and
id|c
op_eq
l_char|&squot;,&squot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|bitmap_parse
id|EXPORT_SYMBOL
c_func
(paren
id|bitmap_parse
)paren
suffix:semicolon
eof
