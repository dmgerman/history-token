multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/*&n; * Copyright (C) 1996 Paul Mackerras.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
multiline_comment|/*&n; * If the bitops are not inlined in bitops.h, they are defined here.&n; *  -- paulus&n; */
macro_line|#if !__INLINE_BITOPS
DECL|function|set_bit
r_void
id|set_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
(brace
r_int
r_int
id|old
suffix:semicolon
r_int
r_int
id|mask
op_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_int
r_int
op_star
id|p
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
op_plus
(paren
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|SMP_WMB
l_string|&quot;&bslash;n&bslash;&n;1:&t;lwarx&t;%0,0,%3 &bslash;n&bslash;&n;&t;or&t;%0,%0,%2 &bslash;n&quot;
id|PPC405_ERR77
c_func
(paren
l_int|0
comma
op_mod
l_int|3
)paren
l_string|&quot;&t;stwcx.&t;%0,0,%3 &bslash;n&bslash;&n;&t;bne&t;1b&quot;
id|SMP_MB
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|old
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|mask
)paren
comma
l_string|&quot;r&quot;
(paren
id|p
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
DECL|function|clear_bit
r_void
id|clear_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
(brace
r_int
r_int
id|old
suffix:semicolon
r_int
r_int
id|mask
op_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_int
r_int
op_star
id|p
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
op_plus
(paren
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|SMP_WMB
l_string|&quot;&bslash;n&bslash;&n;1:&t;lwarx&t;%0,0,%3 &bslash;n&bslash;&n;&t;andc&t;%0,%0,%2 &bslash;n&quot;
id|PPC405_ERR77
c_func
(paren
l_int|0
comma
op_mod
l_int|3
)paren
l_string|&quot;&t;stwcx.&t;%0,0,%3 &bslash;n&bslash;&n;&t;bne&t;1b&quot;
id|SMP_MB
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|old
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|mask
)paren
comma
l_string|&quot;r&quot;
(paren
id|p
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
DECL|function|change_bit
r_void
id|change_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
(brace
r_int
r_int
id|old
suffix:semicolon
r_int
r_int
id|mask
op_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_int
r_int
op_star
id|p
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
op_plus
(paren
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|SMP_WMB
l_string|&quot;&bslash;n&bslash;&n;1:&t;lwarx&t;%0,0,%3 &bslash;n&bslash;&n;&t;xor&t;%0,%0,%2 &bslash;n&quot;
id|PPC405_ERR77
c_func
(paren
l_int|0
comma
op_mod
l_int|3
)paren
l_string|&quot;&t;stwcx.&t;%0,0,%3 &bslash;n&bslash;&n;&t;bne&t;1b&quot;
id|SMP_MB
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|old
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|mask
)paren
comma
l_string|&quot;r&quot;
(paren
id|p
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
DECL|function|test_and_set_bit
r_int
id|test_and_set_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
(brace
r_int
r_int
id|old
comma
id|t
suffix:semicolon
r_int
r_int
id|mask
op_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|p
op_assign
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
)paren
op_plus
(paren
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|SMP_WMB
l_string|&quot;&bslash;n&bslash;&n;1:&t;lwarx&t;%0,0,%4 &bslash;n&bslash;&n;&t;or&t;%1,%0,%3 &bslash;n&quot;
id|PPC405_ERR77
c_func
(paren
l_int|0
comma
op_mod
l_int|4
)paren
l_string|&quot;&t;stwcx.&t;%1,0,%4 &bslash;n&bslash;&n;&t;bne&t;1b&quot;
id|SMP_MB
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|old
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|t
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|mask
)paren
comma
l_string|&quot;r&quot;
(paren
id|p
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
(paren
id|old
op_amp
id|mask
)paren
op_ne
l_int|0
suffix:semicolon
)brace
DECL|function|test_and_clear_bit
r_int
id|test_and_clear_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
(brace
r_int
r_int
id|old
comma
id|t
suffix:semicolon
r_int
r_int
id|mask
op_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|p
op_assign
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
)paren
op_plus
(paren
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|SMP_WMB
l_string|&quot;&bslash;n&bslash;&n;1:&t;lwarx&t;%0,0,%4 &bslash;n&bslash;&n;&t;andc&t;%1,%0,%3 &bslash;n&quot;
id|PPC405_ERR77
c_func
(paren
l_int|0
comma
op_mod
l_int|4
)paren
l_string|&quot;&t;stwcx.&t;%1,0,%4 &bslash;n&bslash;&n;&t;bne&t;1b&quot;
id|SMP_MB
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|old
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|t
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|mask
)paren
comma
l_string|&quot;r&quot;
(paren
id|p
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
(paren
id|old
op_amp
id|mask
)paren
op_ne
l_int|0
suffix:semicolon
)brace
DECL|function|test_and_change_bit
r_int
id|test_and_change_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
(brace
r_int
r_int
id|old
comma
id|t
suffix:semicolon
r_int
r_int
id|mask
op_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|p
op_assign
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
)paren
op_plus
(paren
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|SMP_WMB
l_string|&quot;&bslash;n&bslash;&n;1:&t;lwarx&t;%0,0,%4 &bslash;n&bslash;&n;&t;xor&t;%1,%0,%3 &bslash;n&quot;
id|PPC405_ERR77
c_func
(paren
l_int|0
comma
op_mod
l_int|4
)paren
l_string|&quot;&t;stwcx.&t;%1,0,%4 &bslash;n&bslash;&n;&t;bne&t;1b&quot;
id|SMP_MB
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|old
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|t
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|mask
)paren
comma
l_string|&quot;r&quot;
(paren
id|p
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
(paren
id|old
op_amp
id|mask
)paren
op_ne
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* !__INLINE_BITOPS */
eof
