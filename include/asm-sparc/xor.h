multiline_comment|/*&n; * include/asm-sparc/xor.h&n; *&n; * Optimized RAID-5 checksumming functions for 32-bit Sparc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * You should have received a copy of the GNU General Public License&n; * (for example /usr/src/linux/COPYING); if not, write to the Free&n; * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/*&n; * High speed xor_block operation for RAID4/5 utilizing the&n; * ldd/std SPARC instructions.&n; *&n; * Copyright (C) 1999 Jakub Jelinek (jj@ultra.linux.cz)&n; */
r_static
r_void
DECL|function|sparc_2
id|sparc_2
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
id|lines
op_assign
id|bytes
op_div
(paren
r_sizeof
(paren
r_int
)paren
)paren
op_div
l_int|8
suffix:semicolon
r_do
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ldd [%0 + 0x00], %%g2&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%0 + 0x08], %%g4&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%0 + 0x10], %%o0&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%0 + 0x18], %%o2&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%1 + 0x00], %%o4&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%1 + 0x08], %%l0&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%1 + 0x10], %%l2&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%1 + 0x18], %%l4&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g2, %%o4, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g3, %%o5, %%g3&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g4, %%l0, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g5, %%l1, %%g5&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o0, %%l2, %%o0&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o1, %%l3, %%o1&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o2, %%l4, %%o2&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o3, %%l5, %%o3&bslash;n&bslash;t&quot;
l_string|&quot;std %%g2, [%0 + 0x00]&bslash;n&bslash;t&quot;
l_string|&quot;std %%g4, [%0 + 0x08]&bslash;n&bslash;t&quot;
l_string|&quot;std %%o0, [%0 + 0x10]&bslash;n&bslash;t&quot;
l_string|&quot;std %%o2, [%0 + 0x18]&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|p1
)paren
comma
l_string|&quot;r&quot;
(paren
id|p2
)paren
suffix:colon
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
comma
l_string|&quot;g4&quot;
comma
l_string|&quot;g5&quot;
comma
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
l_string|&quot;l0&quot;
comma
l_string|&quot;l1&quot;
comma
l_string|&quot;l2&quot;
comma
l_string|&quot;l3&quot;
comma
l_string|&quot;l4&quot;
comma
l_string|&quot;l5&quot;
)paren
suffix:semicolon
id|p1
op_add_assign
l_int|8
suffix:semicolon
id|p2
op_add_assign
l_int|8
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|lines
OG
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|sparc_3
id|sparc_3
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
id|lines
op_assign
id|bytes
op_div
(paren
r_sizeof
(paren
r_int
)paren
)paren
op_div
l_int|8
suffix:semicolon
r_do
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ldd [%0 + 0x00], %%g2&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%0 + 0x08], %%g4&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%0 + 0x10], %%o0&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%0 + 0x18], %%o2&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%1 + 0x00], %%o4&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%1 + 0x08], %%l0&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%1 + 0x10], %%l2&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%1 + 0x18], %%l4&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g2, %%o4, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g3, %%o5, %%g3&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%2 + 0x00], %%o4&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g4, %%l0, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g5, %%l1, %%g5&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%2 + 0x08], %%l0&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o0, %%l2, %%o0&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o1, %%l3, %%o1&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%2 + 0x10], %%l2&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o2, %%l4, %%o2&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o3, %%l5, %%o3&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%2 + 0x18], %%l4&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g2, %%o4, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g3, %%o5, %%g3&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g4, %%l0, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g5, %%l1, %%g5&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o0, %%l2, %%o0&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o1, %%l3, %%o1&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o2, %%l4, %%o2&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o3, %%l5, %%o3&bslash;n&bslash;t&quot;
l_string|&quot;std %%g2, [%0 + 0x00]&bslash;n&bslash;t&quot;
l_string|&quot;std %%g4, [%0 + 0x08]&bslash;n&bslash;t&quot;
l_string|&quot;std %%o0, [%0 + 0x10]&bslash;n&bslash;t&quot;
l_string|&quot;std %%o2, [%0 + 0x18]&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|p1
)paren
comma
l_string|&quot;r&quot;
(paren
id|p2
)paren
comma
l_string|&quot;r&quot;
(paren
id|p3
)paren
suffix:colon
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
comma
l_string|&quot;g4&quot;
comma
l_string|&quot;g5&quot;
comma
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
l_string|&quot;l0&quot;
comma
l_string|&quot;l1&quot;
comma
l_string|&quot;l2&quot;
comma
l_string|&quot;l3&quot;
comma
l_string|&quot;l4&quot;
comma
l_string|&quot;l5&quot;
)paren
suffix:semicolon
id|p1
op_add_assign
l_int|8
suffix:semicolon
id|p2
op_add_assign
l_int|8
suffix:semicolon
id|p3
op_add_assign
l_int|8
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|lines
OG
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|sparc_4
id|sparc_4
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
id|lines
op_assign
id|bytes
op_div
(paren
r_sizeof
(paren
r_int
)paren
)paren
op_div
l_int|8
suffix:semicolon
r_do
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ldd [%0 + 0x00], %%g2&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%0 + 0x08], %%g4&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%0 + 0x10], %%o0&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%0 + 0x18], %%o2&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%1 + 0x00], %%o4&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%1 + 0x08], %%l0&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%1 + 0x10], %%l2&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%1 + 0x18], %%l4&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g2, %%o4, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g3, %%o5, %%g3&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%2 + 0x00], %%o4&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g4, %%l0, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g5, %%l1, %%g5&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%2 + 0x08], %%l0&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o0, %%l2, %%o0&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o1, %%l3, %%o1&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%2 + 0x10], %%l2&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o2, %%l4, %%o2&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o3, %%l5, %%o3&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%2 + 0x18], %%l4&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g2, %%o4, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g3, %%o5, %%g3&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%3 + 0x00], %%o4&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g4, %%l0, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g5, %%l1, %%g5&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%3 + 0x08], %%l0&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o0, %%l2, %%o0&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o1, %%l3, %%o1&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%3 + 0x10], %%l2&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o2, %%l4, %%o2&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o3, %%l5, %%o3&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%3 + 0x18], %%l4&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g2, %%o4, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g3, %%o5, %%g3&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g4, %%l0, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g5, %%l1, %%g5&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o0, %%l2, %%o0&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o1, %%l3, %%o1&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o2, %%l4, %%o2&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o3, %%l5, %%o3&bslash;n&bslash;t&quot;
l_string|&quot;std %%g2, [%0 + 0x00]&bslash;n&bslash;t&quot;
l_string|&quot;std %%g4, [%0 + 0x08]&bslash;n&bslash;t&quot;
l_string|&quot;std %%o0, [%0 + 0x10]&bslash;n&bslash;t&quot;
l_string|&quot;std %%o2, [%0 + 0x18]&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|p1
)paren
comma
l_string|&quot;r&quot;
(paren
id|p2
)paren
comma
l_string|&quot;r&quot;
(paren
id|p3
)paren
comma
l_string|&quot;r&quot;
(paren
id|p4
)paren
suffix:colon
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
comma
l_string|&quot;g4&quot;
comma
l_string|&quot;g5&quot;
comma
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
l_string|&quot;l0&quot;
comma
l_string|&quot;l1&quot;
comma
l_string|&quot;l2&quot;
comma
l_string|&quot;l3&quot;
comma
l_string|&quot;l4&quot;
comma
l_string|&quot;l5&quot;
)paren
suffix:semicolon
id|p1
op_add_assign
l_int|8
suffix:semicolon
id|p2
op_add_assign
l_int|8
suffix:semicolon
id|p3
op_add_assign
l_int|8
suffix:semicolon
id|p4
op_add_assign
l_int|8
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|lines
OG
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|sparc_5
id|sparc_5
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
id|lines
op_assign
id|bytes
op_div
(paren
r_sizeof
(paren
r_int
)paren
)paren
op_div
l_int|8
suffix:semicolon
r_do
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ldd [%0 + 0x00], %%g2&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%0 + 0x08], %%g4&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%0 + 0x10], %%o0&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%0 + 0x18], %%o2&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%1 + 0x00], %%o4&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%1 + 0x08], %%l0&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%1 + 0x10], %%l2&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%1 + 0x18], %%l4&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g2, %%o4, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g3, %%o5, %%g3&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%2 + 0x00], %%o4&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g4, %%l0, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g5, %%l1, %%g5&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%2 + 0x08], %%l0&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o0, %%l2, %%o0&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o1, %%l3, %%o1&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%2 + 0x10], %%l2&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o2, %%l4, %%o2&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o3, %%l5, %%o3&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%2 + 0x18], %%l4&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g2, %%o4, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g3, %%o5, %%g3&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%3 + 0x00], %%o4&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g4, %%l0, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g5, %%l1, %%g5&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%3 + 0x08], %%l0&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o0, %%l2, %%o0&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o1, %%l3, %%o1&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%3 + 0x10], %%l2&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o2, %%l4, %%o2&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o3, %%l5, %%o3&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%3 + 0x18], %%l4&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g2, %%o4, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g3, %%o5, %%g3&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%4 + 0x00], %%o4&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g4, %%l0, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g5, %%l1, %%g5&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%4 + 0x08], %%l0&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o0, %%l2, %%o0&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o1, %%l3, %%o1&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%4 + 0x10], %%l2&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o2, %%l4, %%o2&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o3, %%l5, %%o3&bslash;n&bslash;t&quot;
l_string|&quot;ldd [%4 + 0x18], %%l4&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g2, %%o4, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g3, %%o5, %%g3&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g4, %%l0, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;xor %%g5, %%l1, %%g5&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o0, %%l2, %%o0&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o1, %%l3, %%o1&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o2, %%l4, %%o2&bslash;n&bslash;t&quot;
l_string|&quot;xor %%o3, %%l5, %%o3&bslash;n&bslash;t&quot;
l_string|&quot;std %%g2, [%0 + 0x00]&bslash;n&bslash;t&quot;
l_string|&quot;std %%g4, [%0 + 0x08]&bslash;n&bslash;t&quot;
l_string|&quot;std %%o0, [%0 + 0x10]&bslash;n&bslash;t&quot;
l_string|&quot;std %%o2, [%0 + 0x18]&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|p1
)paren
comma
l_string|&quot;r&quot;
(paren
id|p2
)paren
comma
l_string|&quot;r&quot;
(paren
id|p3
)paren
comma
l_string|&quot;r&quot;
(paren
id|p4
)paren
comma
l_string|&quot;r&quot;
(paren
id|p5
)paren
suffix:colon
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
comma
l_string|&quot;g4&quot;
comma
l_string|&quot;g5&quot;
comma
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
l_string|&quot;l0&quot;
comma
l_string|&quot;l1&quot;
comma
l_string|&quot;l2&quot;
comma
l_string|&quot;l3&quot;
comma
l_string|&quot;l4&quot;
comma
l_string|&quot;l5&quot;
)paren
suffix:semicolon
id|p1
op_add_assign
l_int|8
suffix:semicolon
id|p2
op_add_assign
l_int|8
suffix:semicolon
id|p3
op_add_assign
l_int|8
suffix:semicolon
id|p4
op_add_assign
l_int|8
suffix:semicolon
id|p5
op_add_assign
l_int|8
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|lines
OG
l_int|0
)paren
suffix:semicolon
)brace
DECL|variable|xor_block_SPARC
r_static
r_struct
id|xor_block_template
id|xor_block_SPARC
op_assign
(brace
id|name
suffix:colon
l_string|&quot;SPARC&quot;
comma
id|do_2
suffix:colon
id|sparc_2
comma
id|do_3
suffix:colon
id|sparc_3
comma
id|do_4
suffix:colon
id|sparc_4
comma
id|do_5
suffix:colon
id|sparc_5
comma
)brace
suffix:semicolon
multiline_comment|/* For grins, also test the generic routines.  */
macro_line|#include &lt;asm-generic/xor.h&gt;
DECL|macro|XOR_TRY_TEMPLATES
macro_line|#undef XOR_TRY_TEMPLATES
DECL|macro|XOR_TRY_TEMPLATES
mdefine_line|#define XOR_TRY_TEMPLATES&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;xor_speed(&amp;xor_block_8regs);&t;&t;&bslash;&n;&t;&t;xor_speed(&amp;xor_block_32regs);&t;&t;&bslash;&n;&t;&t;xor_speed(&amp;xor_block_SPARC);&t;&t;&bslash;&n;&t;} while (0)
eof
