macro_line|#include &lt;linux/bitmap.h&gt;
macro_line|#include &lt;linux/module.h&gt;
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
id|bitmap
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
op_increment
id|k
)paren
id|bitmap
(braket
id|k
)braket
op_assign
op_complement
id|bitmap
(braket
id|k
)braket
suffix:semicolon
)brace
DECL|variable|bitmap_complement
id|EXPORT_SYMBOL
c_func
(paren
id|bitmap_complement
)paren
suffix:semicolon
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
suffix:semicolon
id|DECLARE_BITMAP
c_func
(paren
id|__shr_tmp
comma
id|bits
)paren
suffix:semicolon
id|bitmap_clear
c_func
(paren
id|__shr_tmp
comma
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
id|bits
op_minus
id|shift
suffix:semicolon
op_increment
id|k
)paren
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|k
op_plus
id|shift
comma
id|src
)paren
)paren
id|set_bit
c_func
(paren
id|k
comma
id|__shr_tmp
)paren
suffix:semicolon
id|bitmap_copy
c_func
(paren
id|dst
comma
id|__shr_tmp
comma
id|bits
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
suffix:semicolon
id|DECLARE_BITMAP
c_func
(paren
id|__shl_tmp
comma
id|bits
)paren
suffix:semicolon
id|bitmap_clear
c_func
(paren
id|__shl_tmp
comma
id|bits
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
id|bits
suffix:semicolon
id|k
op_ge
id|shift
suffix:semicolon
op_decrement
id|k
)paren
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|k
op_minus
id|shift
comma
id|src
)paren
)paren
id|set_bit
c_func
(paren
id|k
comma
id|__shl_tmp
)paren
suffix:semicolon
id|bitmap_copy
c_func
(paren
id|dst
comma
id|__shl_tmp
comma
id|bits
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
eof
