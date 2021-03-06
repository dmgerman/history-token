multiline_comment|/*&n; * mem_op.h&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dahinds@users.sourceforge.net&gt;.  Portions created by David A. Hinds&n; * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; * (C) 1999             David A. Hinds&n; */
macro_line|#ifndef _LINUX_MEM_OP_H
DECL|macro|_LINUX_MEM_OP_H
mdefine_line|#define _LINUX_MEM_OP_H
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/*&n;   If UNSAFE_MEMCPY is defined, we use the (optimized) system routines&n;   to copy between a card and kernel memory.  These routines do 32-bit&n;   operations which may not work with all PCMCIA controllers.  The&n;   safe versions defined here will do only 8-bit and 16-bit accesses.&n;*/
macro_line|#ifdef UNSAFE_MEMCPY
DECL|macro|copy_from_pc
mdefine_line|#define copy_from_pc memcpy_fromio
DECL|macro|copy_to_pc
mdefine_line|#define copy_to_pc memcpy_toio
DECL|function|copy_pc_to_user
r_static
r_inline
r_void
id|copy_pc_to_user
c_func
(paren
r_void
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
r_int
id|n
)paren
(brace
r_int
id|odd
op_assign
(paren
id|n
op_amp
l_int|3
)paren
suffix:semicolon
id|n
op_sub_assign
id|odd
suffix:semicolon
r_while
c_loop
(paren
id|n
)paren
(brace
id|put_user
c_func
(paren
id|__raw_readl
c_func
(paren
id|from
)paren
comma
(paren
r_int
op_star
)paren
id|to
)paren
suffix:semicolon
(paren
r_char
op_star
)paren
id|from
op_add_assign
l_int|4
suffix:semicolon
(paren
r_char
op_star
)paren
id|to
op_add_assign
l_int|4
suffix:semicolon
id|n
op_sub_assign
l_int|4
suffix:semicolon
)brace
r_while
c_loop
(paren
id|odd
op_decrement
)paren
id|put_user
c_func
(paren
id|readb
c_func
(paren
(paren
r_char
op_star
)paren
id|from
op_increment
)paren
comma
(paren
r_char
op_star
)paren
id|to
op_increment
)paren
suffix:semicolon
)brace
DECL|function|copy_user_to_pc
r_static
r_inline
r_void
id|copy_user_to_pc
c_func
(paren
r_void
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
r_int
id|n
)paren
(brace
r_int
id|l
suffix:semicolon
r_char
id|c
suffix:semicolon
r_int
id|odd
op_assign
(paren
id|n
op_amp
l_int|3
)paren
suffix:semicolon
id|n
op_sub_assign
id|odd
suffix:semicolon
r_while
c_loop
(paren
id|n
)paren
(brace
id|get_user
c_func
(paren
id|l
comma
(paren
r_int
op_star
)paren
id|from
)paren
suffix:semicolon
id|__raw_writel
c_func
(paren
id|l
comma
id|to
)paren
suffix:semicolon
(paren
r_char
op_star
)paren
id|to
op_add_assign
l_int|4
suffix:semicolon
(paren
r_char
op_star
)paren
id|from
op_add_assign
l_int|4
suffix:semicolon
id|n
op_sub_assign
l_int|4
suffix:semicolon
)brace
r_while
c_loop
(paren
id|odd
op_decrement
)paren
(brace
id|get_user
c_func
(paren
id|c
comma
(paren
r_char
op_star
)paren
id|from
op_increment
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|c
comma
(paren
r_char
op_star
)paren
id|to
op_increment
)paren
suffix:semicolon
)brace
)brace
macro_line|#else /* UNSAFE_MEMCPY */
DECL|function|copy_from_pc
r_static
r_inline
r_void
id|copy_from_pc
c_func
(paren
r_void
op_star
id|to
comma
r_void
id|__iomem
op_star
id|from
comma
r_int
id|n
)paren
(brace
id|__u16
op_star
id|t
op_assign
id|to
suffix:semicolon
id|__u16
id|__iomem
op_star
id|f
op_assign
id|from
suffix:semicolon
r_int
id|odd
op_assign
(paren
id|n
op_amp
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|n
op_rshift_assign
l_int|1
suffix:semicolon
id|n
suffix:semicolon
id|n
op_decrement
)paren
op_star
id|t
op_increment
op_assign
id|__raw_readw
c_func
(paren
id|f
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|odd
)paren
op_star
(paren
id|__u8
op_star
)paren
id|t
op_assign
id|readb
c_func
(paren
id|f
)paren
suffix:semicolon
)brace
DECL|function|copy_to_pc
r_static
r_inline
r_void
id|copy_to_pc
c_func
(paren
r_void
id|__iomem
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
r_int
id|n
)paren
(brace
id|__u16
id|__iomem
op_star
id|t
op_assign
id|to
suffix:semicolon
r_const
id|__u16
op_star
id|f
op_assign
id|from
suffix:semicolon
r_int
id|odd
op_assign
(paren
id|n
op_amp
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|n
op_rshift_assign
l_int|1
suffix:semicolon
id|n
suffix:semicolon
id|n
op_decrement
)paren
id|__raw_writew
c_func
(paren
op_star
id|f
op_increment
comma
id|t
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|odd
)paren
id|writeb
c_func
(paren
op_star
(paren
id|__u8
op_star
)paren
id|f
comma
id|t
)paren
suffix:semicolon
)brace
DECL|function|copy_pc_to_user
r_static
r_inline
r_void
id|copy_pc_to_user
c_func
(paren
r_void
id|__user
op_star
id|to
comma
r_void
id|__iomem
op_star
id|from
comma
r_int
id|n
)paren
(brace
id|__u16
id|__user
op_star
id|t
op_assign
id|to
suffix:semicolon
id|__u16
id|__iomem
op_star
id|f
op_assign
id|from
suffix:semicolon
r_int
id|odd
op_assign
(paren
id|n
op_amp
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|n
op_rshift_assign
l_int|1
suffix:semicolon
id|n
suffix:semicolon
id|n
op_decrement
)paren
id|put_user
c_func
(paren
id|__raw_readw
c_func
(paren
id|f
op_increment
)paren
comma
id|t
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|odd
)paren
id|put_user
c_func
(paren
id|readb
c_func
(paren
id|f
)paren
comma
(paren
r_char
id|__user
op_star
)paren
id|t
)paren
suffix:semicolon
)brace
DECL|function|copy_user_to_pc
r_static
r_inline
r_void
id|copy_user_to_pc
c_func
(paren
r_void
id|__iomem
op_star
id|to
comma
r_void
id|__user
op_star
id|from
comma
r_int
id|n
)paren
(brace
id|__u16
id|__user
op_star
id|f
op_assign
id|from
suffix:semicolon
id|__u16
id|__iomem
op_star
id|t
op_assign
id|to
suffix:semicolon
r_int
id|s
suffix:semicolon
r_char
id|c
suffix:semicolon
r_int
id|odd
op_assign
(paren
id|n
op_amp
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|n
op_rshift_assign
l_int|1
suffix:semicolon
id|n
suffix:semicolon
id|n
op_decrement
)paren
(brace
id|get_user
c_func
(paren
id|s
comma
id|f
op_increment
)paren
suffix:semicolon
id|__raw_writew
c_func
(paren
id|s
comma
id|t
op_increment
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|odd
)paren
(brace
id|get_user
c_func
(paren
id|c
comma
(paren
r_char
id|__user
op_star
)paren
id|f
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|c
comma
id|t
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* UNSAFE_MEMCPY */
macro_line|#endif /* _LINUX_MEM_OP_H */
eof
