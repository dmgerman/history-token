multiline_comment|/*&n; * bitext.c: kernel little helper (of bit shuffling variety).&n; *&n; * Copyright (C) 2002 Pete Zaitcev &lt;zaitcev@yahoo.com&gt;&n; *&n; * The algorithm to search a zero bit string is geared towards its application.&n; * We expect a couple of fixed sizes of requests, so a rotating counter, reset&n; * by align size, should provide fast enough search while maintaining low&n; * fragmentation.&n; */
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/bitext.h&gt;
multiline_comment|/**&n; * bit_map_string_get - find and set a bit string in bit map.&n; * @t: the bit map.&n; * @len: requested string length&n; * @align: requested alignment&n; *&n; * Returns offset in the map or -1 if out of space.&n; *&n; * Not safe to call from an interrupt (uses spin_lock).&n; */
DECL|function|bit_map_string_get
r_int
id|bit_map_string_get
c_func
(paren
r_struct
id|bit_map
op_star
id|t
comma
r_int
id|len
comma
r_int
id|align
)paren
(brace
r_int
id|offset
comma
id|count
suffix:semicolon
multiline_comment|/* siamese twins */
r_int
id|off_new
suffix:semicolon
r_int
id|align1
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|align
op_eq
l_int|0
)paren
id|align
op_assign
l_int|1
suffix:semicolon
id|align1
op_assign
id|align
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|align
op_amp
id|align1
)paren
op_ne
l_int|0
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|align
OL
l_int|0
op_logical_or
id|align
op_ge
id|t-&gt;size
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
l_int|0
op_logical_or
id|len
OG
id|t-&gt;size
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|t-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|t-&gt;last_size
)paren
id|offset
op_assign
id|t-&gt;first_free
suffix:semicolon
r_else
id|offset
op_assign
id|t-&gt;last_off
op_amp
op_complement
id|align1
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|off_new
op_assign
id|find_next_zero_bit
c_func
(paren
id|t-&gt;map
comma
id|t-&gt;size
comma
id|offset
)paren
suffix:semicolon
id|off_new
op_assign
(paren
id|off_new
op_plus
id|align1
)paren
op_amp
op_complement
id|align1
suffix:semicolon
id|count
op_add_assign
id|off_new
op_minus
id|offset
suffix:semicolon
id|offset
op_assign
id|off_new
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
id|t-&gt;size
)paren
id|offset
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
op_plus
id|len
OG
id|t-&gt;size
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|t-&gt;lock
)paren
suffix:semicolon
multiline_comment|/* P3 */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;bitmap out: size %d used %d off %d len %d align %d count %d&bslash;n&quot;
comma
id|t-&gt;size
comma
id|t-&gt;used
comma
id|offset
comma
id|len
comma
id|align
comma
id|count
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|offset
op_plus
id|len
OG
id|t-&gt;size
)paren
(brace
id|count
op_add_assign
id|t-&gt;size
op_minus
id|offset
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|test_bit
c_func
(paren
id|offset
op_plus
id|i
comma
id|t-&gt;map
)paren
op_eq
l_int|0
)paren
(brace
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|len
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
id|i
op_increment
)paren
id|__set_bit
c_func
(paren
id|offset
op_plus
id|i
comma
id|t-&gt;map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_eq
id|t-&gt;first_free
)paren
id|t-&gt;first_free
op_assign
id|find_next_zero_bit
(paren
id|t-&gt;map
comma
id|t-&gt;size
comma
id|t-&gt;first_free
op_plus
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|t-&gt;last_off
op_assign
id|offset
op_plus
id|len
)paren
op_ge
id|t-&gt;size
)paren
id|t-&gt;last_off
op_assign
l_int|0
suffix:semicolon
id|t-&gt;used
op_add_assign
id|len
suffix:semicolon
id|t-&gt;last_size
op_assign
id|len
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|t-&gt;lock
)paren
suffix:semicolon
r_return
id|offset
suffix:semicolon
)brace
)brace
id|count
op_add_assign
id|i
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|offset
op_add_assign
id|i
op_plus
l_int|1
)paren
op_ge
id|t-&gt;size
)paren
id|offset
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|bit_map_clear
r_void
id|bit_map_clear
c_func
(paren
r_struct
id|bit_map
op_star
id|t
comma
r_int
id|offset
comma
r_int
id|len
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;used
OL
id|len
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Much too late to do any good, but alas... */
id|spin_lock
c_func
(paren
op_amp
id|t-&gt;lock
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
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|offset
op_plus
id|i
comma
id|t-&gt;map
)paren
op_eq
l_int|0
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|__clear_bit
c_func
(paren
id|offset
op_plus
id|i
comma
id|t-&gt;map
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|offset
OL
id|t-&gt;first_free
)paren
id|t-&gt;first_free
op_assign
id|offset
suffix:semicolon
id|t-&gt;used
op_sub_assign
id|len
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|t-&gt;lock
)paren
suffix:semicolon
)brace
DECL|function|bit_map_init
r_void
id|bit_map_init
c_func
(paren
r_struct
id|bit_map
op_star
id|t
comma
r_int
r_int
op_star
id|map
comma
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
(paren
id|size
op_amp
l_int|07
)paren
op_ne
l_int|0
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|map
comma
l_int|0
comma
id|size
op_rshift
l_int|3
)paren
suffix:semicolon
id|memset
c_func
(paren
id|t
comma
l_int|0
comma
r_sizeof
op_star
id|t
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|t-&gt;lock
)paren
suffix:semicolon
id|t-&gt;map
op_assign
id|map
suffix:semicolon
id|t-&gt;size
op_assign
id|size
suffix:semicolon
id|t-&gt;last_size
op_assign
l_int|0
suffix:semicolon
id|t-&gt;first_free
op_assign
l_int|0
suffix:semicolon
)brace
eof
