multiline_comment|/*&n; *  linux/include/asm-arm/xor.h&n; *&n; *  Copyright (C) 2001 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;asm-generic/xor.h&gt;
DECL|macro|__XOR
mdefine_line|#define __XOR(a1, a2) a1 ^= a2
DECL|macro|GET_BLOCK_2
mdefine_line|#define GET_BLOCK_2(dst) &bslash;&n;&t;__asm__(&quot;ldmia&t;%0, {%1, %2}&quot; &bslash;&n;&t;&t;: &quot;=r&quot; (dst), &quot;=r&quot; (a1), &quot;=r&quot; (a2) &bslash;&n;&t;&t;: &quot;0&quot; (dst))
DECL|macro|GET_BLOCK_4
mdefine_line|#define GET_BLOCK_4(dst) &bslash;&n;&t;__asm__(&quot;ldmia&t;%0, {%1, %2, %3, %4}&quot; &bslash;&n;&t;&t;: &quot;=r&quot; (dst), &quot;=r&quot; (a1), &quot;=r&quot; (a2), &quot;=r&quot; (a3), &quot;=r&quot; (a4) &bslash;&n;&t;&t;: &quot;0&quot; (dst))
DECL|macro|XOR_BLOCK_2
mdefine_line|#define XOR_BLOCK_2(src) &bslash;&n;&t;__asm__(&quot;ldmia&t;%0!, {%1, %2}&quot; &bslash;&n;&t;&t;: &quot;=r&quot; (src), &quot;=r&quot; (b1), &quot;=r&quot; (b2) &bslash;&n;&t;&t;: &quot;0&quot; (src)); &bslash;&n;&t;__XOR(a1, b1); __XOR(a2, b2);
DECL|macro|XOR_BLOCK_4
mdefine_line|#define XOR_BLOCK_4(src) &bslash;&n;&t;__asm__(&quot;ldmia&t;%0!, {%1, %2, %3, %4}&quot; &bslash;&n;&t;&t;: &quot;=r&quot; (src), &quot;=r&quot; (b1), &quot;=r&quot; (b2), &quot;=r&quot; (b3), &quot;=r&quot; (b4) &bslash;&n;&t;&t;: &quot;0&quot; (src)); &bslash;&n;&t;__XOR(a1, b1); __XOR(a2, b2); __XOR(a3, b3); __XOR(a4, b4)
DECL|macro|PUT_BLOCK_2
mdefine_line|#define PUT_BLOCK_2(dst) &bslash;&n;&t;__asm__ __volatile__(&quot;stmia&t;%0!, {%2, %3}&quot; &bslash;&n;&t;&t;: &quot;=r&quot; (dst) &bslash;&n;&t;&t;: &quot;0&quot; (dst), &quot;r&quot; (a1), &quot;r&quot; (a2))
DECL|macro|PUT_BLOCK_4
mdefine_line|#define PUT_BLOCK_4(dst) &bslash;&n;&t;__asm__ __volatile__(&quot;stmia&t;%0!, {%2, %3, %4, %5}&quot; &bslash;&n;&t;&t;: &quot;=r&quot; (dst) &bslash;&n;&t;&t;: &quot;0&quot; (dst), &quot;r&quot; (a1), &quot;r&quot; (a2), &quot;r&quot; (a3), &quot;r&quot; (a4))
r_static
r_void
DECL|function|xor_arm4regs_2
id|xor_arm4regs_2
c_func
(paren
r_int
r_int
id|bytes
comma
r_int
r_int
op_star
id|p1
comma
r_int
r_int
op_star
id|p2
)paren
(brace
r_int
r_int
id|lines
op_assign
id|bytes
op_div
r_sizeof
(paren
r_int
r_int
)paren
op_div
l_int|4
suffix:semicolon
r_register
r_int
r_int
id|a1
id|__asm__
c_func
(paren
l_string|&quot;r4&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
id|a2
id|__asm__
c_func
(paren
l_string|&quot;r5&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
id|a3
id|__asm__
c_func
(paren
l_string|&quot;r6&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
id|a4
id|__asm__
c_func
(paren
l_string|&quot;r7&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
id|b1
id|__asm__
c_func
(paren
l_string|&quot;r8&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
id|b2
id|__asm__
c_func
(paren
l_string|&quot;r9&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
id|b3
id|__asm__
c_func
(paren
l_string|&quot;ip&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
id|b4
id|__asm__
c_func
(paren
l_string|&quot;lr&quot;
)paren
suffix:semicolon
r_do
(brace
id|GET_BLOCK_4
c_func
(paren
id|p1
)paren
suffix:semicolon
id|XOR_BLOCK_4
c_func
(paren
id|p2
)paren
suffix:semicolon
id|PUT_BLOCK_4
c_func
(paren
id|p1
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|lines
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|xor_arm4regs_3
id|xor_arm4regs_3
c_func
(paren
r_int
r_int
id|bytes
comma
r_int
r_int
op_star
id|p1
comma
r_int
r_int
op_star
id|p2
comma
r_int
r_int
op_star
id|p3
)paren
(brace
r_int
r_int
id|lines
op_assign
id|bytes
op_div
r_sizeof
(paren
r_int
r_int
)paren
op_div
l_int|4
suffix:semicolon
r_register
r_int
r_int
id|a1
id|__asm__
c_func
(paren
l_string|&quot;r4&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
id|a2
id|__asm__
c_func
(paren
l_string|&quot;r5&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
id|a3
id|__asm__
c_func
(paren
l_string|&quot;r6&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
id|a4
id|__asm__
c_func
(paren
l_string|&quot;r7&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
id|b1
id|__asm__
c_func
(paren
l_string|&quot;r8&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
id|b2
id|__asm__
c_func
(paren
l_string|&quot;r9&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
id|b3
id|__asm__
c_func
(paren
l_string|&quot;ip&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
id|b4
id|__asm__
c_func
(paren
l_string|&quot;lr&quot;
)paren
suffix:semicolon
r_do
(brace
id|GET_BLOCK_4
c_func
(paren
id|p1
)paren
suffix:semicolon
id|XOR_BLOCK_4
c_func
(paren
id|p2
)paren
suffix:semicolon
id|XOR_BLOCK_4
c_func
(paren
id|p3
)paren
suffix:semicolon
id|PUT_BLOCK_4
c_func
(paren
id|p1
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|lines
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|xor_arm4regs_4
id|xor_arm4regs_4
c_func
(paren
r_int
r_int
id|bytes
comma
r_int
r_int
op_star
id|p1
comma
r_int
r_int
op_star
id|p2
comma
r_int
r_int
op_star
id|p3
comma
r_int
r_int
op_star
id|p4
)paren
(brace
r_int
r_int
id|lines
op_assign
id|bytes
op_div
r_sizeof
(paren
r_int
r_int
)paren
op_div
l_int|2
suffix:semicolon
r_register
r_int
r_int
id|a1
id|__asm__
c_func
(paren
l_string|&quot;r8&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
id|a2
id|__asm__
c_func
(paren
l_string|&quot;r9&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
id|b1
id|__asm__
c_func
(paren
l_string|&quot;ip&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
id|b2
id|__asm__
c_func
(paren
l_string|&quot;lr&quot;
)paren
suffix:semicolon
r_do
(brace
id|GET_BLOCK_2
c_func
(paren
id|p1
)paren
suffix:semicolon
id|XOR_BLOCK_2
c_func
(paren
id|p2
)paren
suffix:semicolon
id|XOR_BLOCK_2
c_func
(paren
id|p3
)paren
suffix:semicolon
id|XOR_BLOCK_2
c_func
(paren
id|p4
)paren
suffix:semicolon
id|PUT_BLOCK_2
c_func
(paren
id|p1
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|lines
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|xor_arm4regs_5
id|xor_arm4regs_5
c_func
(paren
r_int
r_int
id|bytes
comma
r_int
r_int
op_star
id|p1
comma
r_int
r_int
op_star
id|p2
comma
r_int
r_int
op_star
id|p3
comma
r_int
r_int
op_star
id|p4
comma
r_int
r_int
op_star
id|p5
)paren
(brace
r_int
r_int
id|lines
op_assign
id|bytes
op_div
r_sizeof
(paren
r_int
r_int
)paren
op_div
l_int|2
suffix:semicolon
r_register
r_int
r_int
id|a1
id|__asm__
c_func
(paren
l_string|&quot;r8&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
id|a2
id|__asm__
c_func
(paren
l_string|&quot;r9&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
id|b1
id|__asm__
c_func
(paren
l_string|&quot;ip&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
id|b2
id|__asm__
c_func
(paren
l_string|&quot;lr&quot;
)paren
suffix:semicolon
r_do
(brace
id|GET_BLOCK_2
c_func
(paren
id|p1
)paren
suffix:semicolon
id|XOR_BLOCK_2
c_func
(paren
id|p2
)paren
suffix:semicolon
id|XOR_BLOCK_2
c_func
(paren
id|p3
)paren
suffix:semicolon
id|XOR_BLOCK_2
c_func
(paren
id|p4
)paren
suffix:semicolon
id|XOR_BLOCK_2
c_func
(paren
id|p5
)paren
suffix:semicolon
id|PUT_BLOCK_2
c_func
(paren
id|p1
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|lines
)paren
suffix:semicolon
)brace
DECL|variable|xor_block_arm4regs
r_static
r_struct
id|xor_block_template
id|xor_block_arm4regs
op_assign
(brace
id|name
suffix:colon
l_string|&quot;arm4regs&quot;
comma
id|do_2
suffix:colon
id|xor_arm4regs_2
comma
id|do_3
suffix:colon
id|xor_arm4regs_3
comma
id|do_4
suffix:colon
id|xor_arm4regs_4
comma
id|do_5
suffix:colon
id|xor_arm4regs_5
comma
)brace
suffix:semicolon
DECL|macro|XOR_TRY_TEMPLATES
macro_line|#undef XOR_TRY_TEMPLATES
DECL|macro|XOR_TRY_TEMPLATES
mdefine_line|#define XOR_TRY_TEMPLATES&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;xor_speed(&amp;xor_block_arm4regs);&t;&bslash;&n;&t;&t;xor_speed(&amp;xor_block_8regs);&t;&bslash;&n;&t;&t;xor_speed(&amp;xor_block_32regs);&t;&bslash;&n;&t;} while (0)
eof
