multiline_comment|/* $Id: unaligned.c,v 1.23 2001/12/21 00:54:31 davem Exp $&n; * unaligned.c: Unaligned load/store trap handling with special&n; *              cases for the kernel to do them more quickly.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1996 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
multiline_comment|/* #define DEBUG_MNA */
DECL|enum|direction
r_enum
id|direction
(brace
DECL|enumerator|load
id|load
comma
multiline_comment|/* ld, ldd, ldh, ldsh */
DECL|enumerator|store
id|store
comma
multiline_comment|/* st, std, sth, stsh */
DECL|enumerator|both
id|both
comma
multiline_comment|/* Swap, ldstub, etc. */
DECL|enumerator|fpload
id|fpload
comma
DECL|enumerator|fpstore
id|fpstore
comma
DECL|enumerator|invalid
id|invalid
comma
)brace
suffix:semicolon
macro_line|#ifdef DEBUG_MNA
DECL|variable|dirstrings
r_static
r_char
op_star
id|dirstrings
(braket
)braket
op_assign
(brace
l_string|&quot;load&quot;
comma
l_string|&quot;store&quot;
comma
l_string|&quot;both&quot;
comma
l_string|&quot;fpload&quot;
comma
l_string|&quot;fpstore&quot;
comma
l_string|&quot;invalid&quot;
)brace
suffix:semicolon
macro_line|#endif
DECL|function|decode_direction
r_static
r_inline
r_enum
id|direction
id|decode_direction
c_func
(paren
r_int
r_int
id|insn
)paren
(brace
r_int
r_int
id|tmp
op_assign
(paren
id|insn
op_rshift
l_int|21
)paren
op_amp
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
(brace
r_return
id|load
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
(paren
id|insn
op_rshift
l_int|19
)paren
op_amp
l_int|0x3f
)paren
op_eq
l_int|15
)paren
(brace
r_return
id|both
suffix:semicolon
)brace
r_else
r_return
id|store
suffix:semicolon
)brace
)brace
multiline_comment|/* 8 = double-word, 4 = word, 2 = half-word */
DECL|function|decode_access_size
r_static
r_inline
r_int
id|decode_access_size
c_func
(paren
r_int
r_int
id|insn
)paren
(brace
id|insn
op_assign
(paren
id|insn
op_rshift
l_int|19
)paren
op_amp
l_int|3
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|insn
)paren
(brace
r_return
l_int|4
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|insn
op_eq
l_int|3
)paren
(brace
r_return
l_int|8
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|insn
op_eq
l_int|2
)paren
(brace
r_return
l_int|2
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;Impossible unaligned trap. insn=%08x&bslash;n&quot;
comma
id|insn
)paren
suffix:semicolon
id|die_if_kernel
c_func
(paren
l_string|&quot;Byte sized unaligned access?!?!&quot;
comma
id|current-&gt;thread.kregs
)paren
suffix:semicolon
r_return
l_int|4
suffix:semicolon
multiline_comment|/* just to keep gcc happy. */
)brace
)brace
multiline_comment|/* 0x400000 = signed, 0 = unsigned */
DECL|function|decode_signedness
r_static
r_inline
r_int
id|decode_signedness
c_func
(paren
r_int
r_int
id|insn
)paren
(brace
r_return
(paren
id|insn
op_amp
l_int|0x400000
)paren
suffix:semicolon
)brace
DECL|function|maybe_flush_windows
r_static
r_inline
r_void
id|maybe_flush_windows
c_func
(paren
r_int
r_int
id|rs1
comma
r_int
r_int
id|rs2
comma
r_int
r_int
id|rd
)paren
(brace
r_if
c_cond
(paren
id|rs2
op_ge
l_int|16
op_logical_or
id|rs1
op_ge
l_int|16
op_logical_or
id|rd
op_ge
l_int|16
)paren
(brace
multiline_comment|/* Wheee... */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;save %sp, -0x40, %sp&bslash;n&bslash;t&quot;
l_string|&quot;save %sp, -0x40, %sp&bslash;n&bslash;t&quot;
l_string|&quot;save %sp, -0x40, %sp&bslash;n&bslash;t&quot;
l_string|&quot;save %sp, -0x40, %sp&bslash;n&bslash;t&quot;
l_string|&quot;save %sp, -0x40, %sp&bslash;n&bslash;t&quot;
l_string|&quot;save %sp, -0x40, %sp&bslash;n&bslash;t&quot;
l_string|&quot;save %sp, -0x40, %sp&bslash;n&bslash;t&quot;
l_string|&quot;restore; restore; restore; restore;&bslash;n&bslash;t&quot;
l_string|&quot;restore; restore; restore;&bslash;n&bslash;t&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|sign_extend_imm13
r_static
r_inline
r_int
id|sign_extend_imm13
c_func
(paren
r_int
id|imm
)paren
(brace
r_return
id|imm
op_lshift
l_int|19
op_rshift
l_int|19
suffix:semicolon
)brace
DECL|function|fetch_reg
r_static
r_inline
r_int
r_int
id|fetch_reg
c_func
(paren
r_int
r_int
id|reg
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|reg_window
op_star
id|win
suffix:semicolon
r_if
c_cond
(paren
id|reg
OL
l_int|16
)paren
(brace
r_return
(paren
op_logical_neg
id|reg
ques
c_cond
l_int|0
suffix:colon
id|regs-&gt;u_regs
(braket
id|reg
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* Ho hum, the slightly complicated case. */
id|win
op_assign
(paren
r_struct
id|reg_window
op_star
)paren
id|regs-&gt;u_regs
(braket
id|UREG_FP
)braket
suffix:semicolon
r_return
id|win-&gt;locals
(braket
id|reg
op_minus
l_int|16
)braket
suffix:semicolon
multiline_comment|/* yes, I know what this does... */
)brace
DECL|function|safe_fetch_reg
r_static
r_inline
r_int
r_int
id|safe_fetch_reg
c_func
(paren
r_int
r_int
id|reg
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|reg_window
id|__user
op_star
id|win
suffix:semicolon
r_int
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|reg
OL
l_int|16
)paren
r_return
(paren
op_logical_neg
id|reg
ques
c_cond
l_int|0
suffix:colon
id|regs-&gt;u_regs
(braket
id|reg
)braket
)paren
suffix:semicolon
multiline_comment|/* Ho hum, the slightly complicated case. */
id|win
op_assign
(paren
r_struct
id|reg_window
id|__user
op_star
)paren
id|regs-&gt;u_regs
(braket
id|UREG_FP
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|win
op_amp
l_int|3
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|ret
comma
op_amp
id|win-&gt;locals
(braket
id|reg
op_minus
l_int|16
)braket
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|fetch_reg_addr
r_static
r_inline
r_int
r_int
op_star
id|fetch_reg_addr
c_func
(paren
r_int
r_int
id|reg
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|reg_window
op_star
id|win
suffix:semicolon
r_if
c_cond
(paren
id|reg
OL
l_int|16
)paren
(brace
r_return
op_amp
id|regs-&gt;u_regs
(braket
id|reg
)braket
suffix:semicolon
)brace
id|win
op_assign
(paren
r_struct
id|reg_window
op_star
)paren
id|regs-&gt;u_regs
(braket
id|UREG_FP
)braket
suffix:semicolon
r_return
op_amp
id|win-&gt;locals
(braket
id|reg
op_minus
l_int|16
)braket
suffix:semicolon
)brace
DECL|function|compute_effective_address
r_static
r_inline
r_int
r_int
id|compute_effective_address
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|insn
)paren
(brace
r_int
r_int
id|rs1
op_assign
(paren
id|insn
op_rshift
l_int|14
)paren
op_amp
l_int|0x1f
suffix:semicolon
r_int
r_int
id|rs2
op_assign
id|insn
op_amp
l_int|0x1f
suffix:semicolon
r_int
r_int
id|rd
op_assign
(paren
id|insn
op_rshift
l_int|25
)paren
op_amp
l_int|0x1f
suffix:semicolon
r_if
c_cond
(paren
id|insn
op_amp
l_int|0x2000
)paren
(brace
id|maybe_flush_windows
c_func
(paren
id|rs1
comma
l_int|0
comma
id|rd
)paren
suffix:semicolon
r_return
(paren
id|fetch_reg
c_func
(paren
id|rs1
comma
id|regs
)paren
op_plus
id|sign_extend_imm13
c_func
(paren
id|insn
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|maybe_flush_windows
c_func
(paren
id|rs1
comma
id|rs2
comma
id|rd
)paren
suffix:semicolon
r_return
(paren
id|fetch_reg
c_func
(paren
id|rs1
comma
id|regs
)paren
op_plus
id|fetch_reg
c_func
(paren
id|rs2
comma
id|regs
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|safe_compute_effective_address
r_static
r_inline
r_int
r_int
id|safe_compute_effective_address
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|insn
)paren
(brace
r_int
r_int
id|rs1
op_assign
(paren
id|insn
op_rshift
l_int|14
)paren
op_amp
l_int|0x1f
suffix:semicolon
r_int
r_int
id|rs2
op_assign
id|insn
op_amp
l_int|0x1f
suffix:semicolon
r_int
r_int
id|rd
op_assign
(paren
id|insn
op_rshift
l_int|25
)paren
op_amp
l_int|0x1f
suffix:semicolon
r_if
c_cond
(paren
id|insn
op_amp
l_int|0x2000
)paren
(brace
id|maybe_flush_windows
c_func
(paren
id|rs1
comma
l_int|0
comma
id|rd
)paren
suffix:semicolon
r_return
(paren
id|safe_fetch_reg
c_func
(paren
id|rs1
comma
id|regs
)paren
op_plus
id|sign_extend_imm13
c_func
(paren
id|insn
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|maybe_flush_windows
c_func
(paren
id|rs1
comma
id|rs2
comma
id|rd
)paren
suffix:semicolon
r_return
(paren
id|safe_fetch_reg
c_func
(paren
id|rs1
comma
id|regs
)paren
op_plus
id|safe_fetch_reg
c_func
(paren
id|rs2
comma
id|regs
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* This is just to make gcc think panic does return... */
DECL|function|unaligned_panic
r_static
r_void
id|unaligned_panic
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|panic
c_func
(paren
id|str
)paren
suffix:semicolon
)brace
DECL|macro|do_integer_load
mdefine_line|#define do_integer_load(dest_reg, size, saddr, is_signed, errh) ({&t;&t;&bslash;&n;__asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;cmp&t;%1, 8&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;be&t;9f&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot; cmp&t;%1, 4&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;be&t;6f&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;4:&bslash;t&quot;&t;&quot; ldub&t;[%2], %%l1&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;5:&bslash;t&quot;&t;&quot;ldub&t;[%2 + 1], %%l2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;sll&t;%%l1, 8, %%l1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;tst&t;%3&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;be&t;3f&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot; add&t;%%l1, %%l2, %%l1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;sll&t;%%l1, 16, %%l1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;sra&t;%%l1, 16, %%l1&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;3:&bslash;t&quot;&t;&quot;b&t;0f&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot; st&t;%%l1, [%0]&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;6:&bslash;t&quot;&t;&quot;ldub&t;[%2 + 1], %%l2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;sll&t;%%l1, 24, %%l1&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;7:&bslash;t&quot;&t;&quot;ldub&t;[%2 + 2], %%g7&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;sll&t;%%l2, 16, %%l2&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;8:&bslash;t&quot;&t;&quot;ldub&t;[%2 + 3], %%g1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;sll&t;%%g7, 8, %%g7&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;or&t;%%l1, %%l2, %%l1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;or&t;%%g7, %%g1, %%g7&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;or&t;%%l1, %%g7, %%l1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;b&t;0f&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot; st&t;%%l1, [%0]&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;9:&bslash;t&quot;&t;&quot;ldub&t;[%2], %%l1&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;10:&bslash;t&quot;&t;&quot;ldub&t;[%2 + 1], %%l2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;sll&t;%%l1, 24, %%l1&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;11:&bslash;t&quot;&t;&quot;ldub&t;[%2 + 2], %%g7&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;sll&t;%%l2, 16, %%l2&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;12:&bslash;t&quot;&t;&quot;ldub&t;[%2 + 3], %%g1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;sll&t;%%g7, 8, %%g7&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;or&t;%%l1, %%l2, %%l1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;or&t;%%g7, %%g1, %%g7&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;or&t;%%l1, %%g7, %%g7&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;13:&bslash;t&quot;&t;&quot;ldub&t;[%2 + 4], %%l1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;st&t;%%g7, [%0]&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;14:&bslash;t&quot;&t;&quot;ldub&t;[%2 + 5], %%l2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;sll&t;%%l1, 24, %%l1&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;15:&bslash;t&quot;&t;&quot;ldub&t;[%2 + 6], %%g7&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;sll&t;%%l2, 16, %%l2&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;16:&bslash;t&quot;&t;&quot;ldub&t;[%2 + 7], %%g1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;sll&t;%%g7, 8, %%g7&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;or&t;%%l1, %%l2, %%l1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;or&t;%%g7, %%g1, %%g7&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;or&t;%%l1, %%g7, %%g7&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;st&t;%%g7, [%0 + 4]&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;0:&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,#alloc&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;4b, &quot; #errh &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;5b, &quot; #errh &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;6b, &quot; #errh &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;7b, &quot; #errh &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;8b, &quot; #errh &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;9b, &quot; #errh &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;10b, &quot; #errh &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;11b, &quot; #errh &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;12b, &quot; #errh &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;13b, &quot; #errh &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;14b, &quot; #errh &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;15b, &quot; #errh &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;16b, &quot; #errh &quot;&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: : &quot;r&quot; (dest_reg), &quot;r&quot; (size), &quot;r&quot; (saddr), &quot;r&quot; (is_signed)&t;&t;&bslash;&n;&t;: &quot;l1&quot;, &quot;l2&quot;, &quot;g7&quot;, &quot;g1&quot;, &quot;cc&quot;);&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|store_common
mdefine_line|#define store_common(dst_addr, size, src_val, errh) ({&t;&t;&t;&t;&bslash;&n;__asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ld&t;[%2], %%l1&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;cmp&t;%1, 2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;be&t;2f&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot; cmp&t;%1, 4&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;be&t;1f&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot; srl&t;%%l1, 24, %%l2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;srl&t;%%l1, 16, %%g7&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;4:&bslash;t&quot;&t;&quot;stb&t;%%l2, [%0]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;srl&t;%%l1, 8, %%l2&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;5:&bslash;t&quot;&t;&quot;stb&t;%%g7, [%0 + 1]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ld&t;[%2 + 4], %%g7&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;6:&bslash;t&quot;&t;&quot;stb&t;%%l2, [%0 + 2]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;srl&t;%%g7, 24, %%l2&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;7:&bslash;t&quot;&t;&quot;stb&t;%%l1, [%0 + 3]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;srl&t;%%g7, 16, %%l1&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;8:&bslash;t&quot;&t;&quot;stb&t;%%l2, [%0 + 4]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;srl&t;%%g7, 8, %%l2&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;9:&bslash;t&quot;&t;&quot;stb&t;%%l1, [%0 + 5]&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;10:&bslash;t&quot;&t;&quot;stb&t;%%l2, [%0 + 6]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;b&t;0f&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;11:&bslash;t&quot;&t;&quot; stb&t;%%g7, [%0 + 7]&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;1:&bslash;t&quot;&t;&quot;srl&t;%%l1, 16, %%g7&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;12:&bslash;t&quot;&t;&quot;stb&t;%%l2, [%0]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;srl&t;%%l1, 8, %%l2&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;13:&bslash;t&quot;&t;&quot;stb&t;%%g7, [%0 + 1]&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;14:&bslash;t&quot;&t;&quot;stb&t;%%l2, [%0 + 2]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;b&t;0f&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;15:&bslash;t&quot;&t;&quot; stb&t;%%l1, [%0 + 3]&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;2:&bslash;t&quot;&t;&quot;srl&t;%%l1, 8, %%l2&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;16:&bslash;t&quot;&t;&quot;stb&t;%%l2, [%0]&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;17:&bslash;t&quot;&t;&quot;stb&t;%%l1, [%0 + 1]&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;0:&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,#alloc&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;4b, &quot; #errh &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;5b, &quot; #errh &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;6b, &quot; #errh &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;7b, &quot; #errh &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;8b, &quot; #errh &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;9b, &quot; #errh &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;10b, &quot; #errh &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;11b, &quot; #errh &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;12b, &quot; #errh &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;13b, &quot; #errh &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;14b, &quot; #errh &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;15b, &quot; #errh &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;16b, &quot; #errh &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;17b, &quot; #errh &quot;&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: : &quot;r&quot; (dst_addr), &quot;r&quot; (size), &quot;r&quot; (src_val)&t;&t;&t;&t;&bslash;&n;&t;: &quot;l1&quot;, &quot;l2&quot;, &quot;g7&quot;, &quot;g1&quot;, &quot;cc&quot;);&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|do_integer_store
mdefine_line|#define do_integer_store(reg_num, size, dst_addr, regs, errh) ({&t;&t;&bslash;&n;&t;unsigned long *src_val;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;static unsigned long zero[2] = { 0, };&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (reg_num) src_val = fetch_reg_addr(reg_num, regs);&t;&t;&t;&bslash;&n;&t;else {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;src_val = &amp;zero[0];&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (size == 8)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;zero[1] = fetch_reg(1, regs);&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;store_common(dst_addr, size, src_val, errh);&t;&t;&t;&t;&bslash;&n;})
r_extern
r_void
id|smp_capture
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|smp_release
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|do_atomic
mdefine_line|#define do_atomic(srcdest_reg, mem, errh) ({&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long flags, tmp;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;smp_capture();&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;local_irq_save(flags);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;tmp = *srcdest_reg;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do_integer_load(srcdest_reg, 4, mem, 0, errh);&t;&t;&t;&t;&bslash;&n;&t;store_common(mem, 4, &amp;tmp, errh);&t;&t;&t;&t;&t;&bslash;&n;&t;local_irq_restore(flags);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;smp_release();&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|function|advance
r_static
r_inline
r_void
id|advance
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|regs-&gt;pc
op_assign
id|regs-&gt;npc
suffix:semicolon
id|regs-&gt;npc
op_add_assign
l_int|4
suffix:semicolon
)brace
DECL|function|floating_point_load_or_store_p
r_static
r_inline
r_int
id|floating_point_load_or_store_p
c_func
(paren
r_int
r_int
id|insn
)paren
(brace
r_return
(paren
id|insn
op_rshift
l_int|24
)paren
op_amp
l_int|1
suffix:semicolon
)brace
DECL|function|ok_for_kernel
r_static
r_inline
r_int
id|ok_for_kernel
c_func
(paren
r_int
r_int
id|insn
)paren
(brace
r_return
op_logical_neg
id|floating_point_load_or_store_p
c_func
(paren
id|insn
)paren
suffix:semicolon
)brace
r_void
id|kernel_mna_trap_fault
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|insn
)paren
id|__asm__
(paren
l_string|&quot;kernel_mna_trap_fault&quot;
)paren
suffix:semicolon
DECL|function|kernel_mna_trap_fault
r_void
id|kernel_mna_trap_fault
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|insn
)paren
(brace
r_int
r_int
id|g2
op_assign
id|regs-&gt;u_regs
(braket
id|UREG_G2
)braket
suffix:semicolon
r_int
r_int
id|fixup
op_assign
id|search_extables_range
c_func
(paren
id|regs-&gt;pc
comma
op_amp
id|g2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fixup
)paren
(brace
r_int
r_int
id|address
op_assign
id|compute_effective_address
c_func
(paren
id|regs
comma
id|insn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|address
OL
id|PAGE_SIZE
)paren
(brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;Unable to handle kernel NULL pointer dereference in mna handler&quot;
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;Unable to handle kernel paging request in mna handler&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot; at virtual address %08lx&bslash;n&quot;
comma
id|address
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;current-&gt;{mm,active_mm}-&gt;context = %08lx&bslash;n&quot;
comma
(paren
id|current-&gt;mm
ques
c_cond
id|current-&gt;mm-&gt;context
suffix:colon
id|current-&gt;active_mm-&gt;context
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;current-&gt;{mm,active_mm}-&gt;pgd = %08lx&bslash;n&quot;
comma
(paren
id|current-&gt;mm
ques
c_cond
(paren
r_int
r_int
)paren
id|current-&gt;mm-&gt;pgd
suffix:colon
(paren
r_int
r_int
)paren
id|current-&gt;active_mm-&gt;pgd
)paren
)paren
suffix:semicolon
id|die_if_kernel
c_func
(paren
l_string|&quot;Oops&quot;
comma
id|regs
)paren
suffix:semicolon
multiline_comment|/* Not reached */
)brace
id|regs-&gt;pc
op_assign
id|fixup
suffix:semicolon
id|regs-&gt;npc
op_assign
id|regs-&gt;pc
op_plus
l_int|4
suffix:semicolon
id|regs-&gt;u_regs
(braket
id|UREG_G2
)braket
op_assign
id|g2
suffix:semicolon
)brace
DECL|function|kernel_unaligned_trap
id|asmlinkage
r_void
id|kernel_unaligned_trap
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|insn
)paren
(brace
r_enum
id|direction
id|dir
op_assign
id|decode_direction
c_func
(paren
id|insn
)paren
suffix:semicolon
r_int
id|size
op_assign
id|decode_access_size
c_func
(paren
id|insn
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ok_for_kernel
c_func
(paren
id|insn
)paren
op_logical_or
id|dir
op_eq
id|both
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Unsupported unaligned load/store trap for kernel at &lt;%08lx&gt;.&bslash;n&quot;
comma
id|regs-&gt;pc
)paren
suffix:semicolon
id|unaligned_panic
c_func
(paren
l_string|&quot;Wheee. Kernel does fpu/atomic unaligned load/store.&quot;
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;&bslash;n&quot;
l_string|&quot;kernel_unaligned_trap_fault:&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;%0, %%o0&bslash;n&bslash;t&quot;
l_string|&quot;call&t;kernel_mna_trap_fault&bslash;n&bslash;t&quot;
l_string|&quot; mov&t;%1, %%o1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|regs
)paren
comma
l_string|&quot;r&quot;
(paren
id|insn
)paren
suffix:colon
l_string|&quot;o0&quot;
comma
l_string|&quot;o1&quot;
comma
l_string|&quot;o2&quot;
comma
l_string|&quot;o3&quot;
comma
l_string|&quot;o4&quot;
comma
l_string|&quot;o5&quot;
comma
l_string|&quot;o7&quot;
comma
l_string|&quot;g1&quot;
comma
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
comma
l_string|&quot;g4&quot;
comma
l_string|&quot;g5&quot;
comma
l_string|&quot;g7&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
id|addr
op_assign
id|compute_effective_address
c_func
(paren
id|regs
comma
id|insn
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_MNA
id|printk
c_func
(paren
l_string|&quot;KMNA: pc=%08lx [dir=%s addr=%08lx size=%d] retpc[%08lx]&bslash;n&quot;
comma
id|regs-&gt;pc
comma
id|dirstrings
(braket
id|dir
)braket
comma
id|addr
comma
id|size
comma
id|regs-&gt;u_regs
(braket
id|UREG_RETPC
)braket
)paren
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
id|dir
)paren
(brace
r_case
id|load
suffix:colon
id|do_integer_load
c_func
(paren
id|fetch_reg_addr
c_func
(paren
(paren
(paren
id|insn
op_rshift
l_int|25
)paren
op_amp
l_int|0x1f
)paren
comma
id|regs
)paren
comma
id|size
comma
(paren
r_int
r_int
op_star
)paren
id|addr
comma
id|decode_signedness
c_func
(paren
id|insn
)paren
comma
id|kernel_unaligned_trap_fault
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|store
suffix:colon
id|do_integer_store
c_func
(paren
(paren
(paren
id|insn
op_rshift
l_int|25
)paren
op_amp
l_int|0x1f
)paren
comma
id|size
comma
(paren
r_int
r_int
op_star
)paren
id|addr
comma
id|regs
comma
id|kernel_unaligned_trap_fault
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#if 0 /* unsupported */
r_case
id|both
suffix:colon
id|do_atomic
c_func
(paren
id|fetch_reg_addr
c_func
(paren
(paren
(paren
id|insn
op_rshift
l_int|25
)paren
op_amp
l_int|0x1f
)paren
comma
id|regs
)paren
comma
(paren
r_int
r_int
op_star
)paren
id|addr
comma
id|kernel_unaligned_trap_fault
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;Impossible kernel unaligned trap.&quot;
)paren
suffix:semicolon
multiline_comment|/* Not reached... */
)brace
id|advance
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
)brace
DECL|function|ok_for_user
r_static
r_inline
r_int
id|ok_for_user
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|insn
comma
r_enum
id|direction
id|dir
)paren
(brace
r_int
r_int
id|reg
suffix:semicolon
r_int
id|retval
comma
id|check
op_assign
(paren
id|dir
op_eq
id|load
)paren
ques
c_cond
id|VERIFY_READ
suffix:colon
id|VERIFY_WRITE
suffix:semicolon
r_int
id|size
op_assign
(paren
(paren
id|insn
op_rshift
l_int|19
)paren
op_amp
l_int|3
)paren
op_eq
l_int|3
ques
c_cond
l_int|8
suffix:colon
l_int|4
suffix:semicolon
r_if
c_cond
(paren
(paren
id|regs-&gt;pc
op_or
id|regs-&gt;npc
)paren
op_amp
l_int|3
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Must verify_area() in all the necessary places. */
DECL|macro|WINREG_ADDR
mdefine_line|#define WINREG_ADDR(regnum) &bslash;&n;&t;((void __user *)(((unsigned long *)regs-&gt;u_regs[UREG_FP])+(regnum)))
id|retval
op_assign
l_int|0
suffix:semicolon
id|reg
op_assign
(paren
id|insn
op_rshift
l_int|25
)paren
op_amp
l_int|0x1f
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_ge
l_int|16
)paren
(brace
id|retval
op_assign
id|verify_area
c_func
(paren
id|check
comma
id|WINREG_ADDR
c_func
(paren
id|reg
op_minus
l_int|16
)paren
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
)brace
id|reg
op_assign
(paren
id|insn
op_rshift
l_int|14
)paren
op_amp
l_int|0x1f
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_ge
l_int|16
)paren
(brace
id|retval
op_assign
id|verify_area
c_func
(paren
id|check
comma
id|WINREG_ADDR
c_func
(paren
id|reg
op_minus
l_int|16
)paren
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|insn
op_amp
l_int|0x2000
)paren
)paren
(brace
id|reg
op_assign
(paren
id|insn
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_ge
l_int|16
)paren
(brace
id|retval
op_assign
id|verify_area
c_func
(paren
id|check
comma
id|WINREG_ADDR
c_func
(paren
id|reg
op_minus
l_int|16
)paren
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
)brace
)brace
r_return
id|retval
suffix:semicolon
DECL|macro|WINREG_ADDR
macro_line|#undef WINREG_ADDR
)brace
r_void
id|user_mna_trap_fault
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|insn
)paren
id|__asm__
(paren
l_string|&quot;user_mna_trap_fault&quot;
)paren
suffix:semicolon
DECL|function|user_mna_trap_fault
r_void
id|user_mna_trap_fault
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|insn
)paren
(brace
id|siginfo_t
id|info
suffix:semicolon
id|info.si_signo
op_assign
id|SIGBUS
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_code
op_assign
id|BUS_ADRALN
suffix:semicolon
id|info.si_addr
op_assign
(paren
r_void
op_star
)paren
id|safe_compute_effective_address
c_func
(paren
id|regs
comma
id|insn
)paren
suffix:semicolon
id|info.si_trapno
op_assign
l_int|0
suffix:semicolon
id|send_sig_info
c_func
(paren
id|SIGBUS
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
)brace
DECL|function|user_unaligned_trap
id|asmlinkage
r_void
id|user_unaligned_trap
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|insn
)paren
(brace
r_enum
id|direction
id|dir
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|current-&gt;thread.flags
op_amp
id|SPARC_FLAG_UNALIGNED
)paren
op_logical_or
(paren
(paren
(paren
id|insn
op_rshift
l_int|30
)paren
op_amp
l_int|3
)paren
op_ne
l_int|3
)paren
)paren
(brace
r_goto
id|kill_user
suffix:semicolon
)brace
id|dir
op_assign
id|decode_direction
c_func
(paren
id|insn
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ok_for_user
c_func
(paren
id|regs
comma
id|insn
comma
id|dir
)paren
)paren
(brace
r_goto
id|kill_user
suffix:semicolon
)brace
r_else
(brace
r_int
id|size
op_assign
id|decode_access_size
c_func
(paren
id|insn
)paren
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|floating_point_load_or_store_p
c_func
(paren
id|insn
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;User FPU load/store unaligned unsupported.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|kill_user
suffix:semicolon
)brace
id|addr
op_assign
id|compute_effective_address
c_func
(paren
id|regs
comma
id|insn
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|dir
)paren
(brace
r_case
id|load
suffix:colon
id|do_integer_load
c_func
(paren
id|fetch_reg_addr
c_func
(paren
(paren
(paren
id|insn
op_rshift
l_int|25
)paren
op_amp
l_int|0x1f
)paren
comma
id|regs
)paren
comma
id|size
comma
(paren
r_int
r_int
op_star
)paren
id|addr
comma
id|decode_signedness
c_func
(paren
id|insn
)paren
comma
id|user_unaligned_trap_fault
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|store
suffix:colon
id|do_integer_store
c_func
(paren
(paren
(paren
id|insn
op_rshift
l_int|25
)paren
op_amp
l_int|0x1f
)paren
comma
id|size
comma
(paren
r_int
r_int
op_star
)paren
id|addr
comma
id|regs
comma
id|user_unaligned_trap_fault
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|both
suffix:colon
macro_line|#if 0 /* unsupported */
id|do_atomic
c_func
(paren
id|fetch_reg_addr
c_func
(paren
(paren
(paren
id|insn
op_rshift
l_int|25
)paren
op_amp
l_int|0x1f
)paren
comma
id|regs
)paren
comma
(paren
r_int
r_int
op_star
)paren
id|addr
comma
id|user_unaligned_trap_fault
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/*&n;&t;&t;&t; * This was supported in 2.4. However, we question&n;&t;&t;&t; * the value of SWAP instruction across word boundaries.&n;&t;&t;&t; */
id|printk
c_func
(paren
l_string|&quot;Unaligned SWAP unsupported.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|kill_user
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_default
suffix:colon
id|unaligned_panic
c_func
(paren
l_string|&quot;Impossible user unaligned trap.&quot;
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;&bslash;n&quot;
l_string|&quot;user_unaligned_trap_fault:&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;%0, %%o0&bslash;n&bslash;t&quot;
l_string|&quot;call&t;user_mna_trap_fault&bslash;n&bslash;t&quot;
l_string|&quot; mov&t;%1, %%o1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|regs
)paren
comma
l_string|&quot;r&quot;
(paren
id|insn
)paren
suffix:colon
l_string|&quot;o0&quot;
comma
l_string|&quot;o1&quot;
comma
l_string|&quot;o2&quot;
comma
l_string|&quot;o3&quot;
comma
l_string|&quot;o4&quot;
comma
l_string|&quot;o5&quot;
comma
l_string|&quot;o7&quot;
comma
l_string|&quot;g1&quot;
comma
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
comma
l_string|&quot;g4&quot;
comma
l_string|&quot;g5&quot;
comma
l_string|&quot;g7&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|advance
c_func
(paren
id|regs
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|kill_user
suffix:colon
id|user_mna_trap_fault
c_func
(paren
id|regs
comma
id|insn
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
eof
