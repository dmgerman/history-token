multiline_comment|/*&n; *&t;Access to VGA videoram&n; *&n; *&t;(c) 1998 Martin Mares &lt;mj@ucw.cz&gt;&n; */
macro_line|#ifndef _LINUX_ASM_VGA_H_
DECL|macro|_LINUX_ASM_VGA_H_
mdefine_line|#define _LINUX_ASM_VGA_H_
macro_line|#include &lt;asm/types.h&gt;
DECL|macro|VT_BUF_HAVE_RW
mdefine_line|#define VT_BUF_HAVE_RW
DECL|macro|scr_writew
macro_line|#undef scr_writew
DECL|macro|scr_readw
macro_line|#undef scr_readw
DECL|function|scr_writew
r_static
r_inline
r_void
id|scr_writew
c_func
(paren
id|u16
id|val
comma
id|u16
op_star
id|addr
)paren
(brace
id|BUG_ON
c_func
(paren
(paren
r_int
)paren
id|addr
op_ge
l_int|0
)paren
suffix:semicolon
op_star
id|addr
op_assign
id|val
suffix:semicolon
)brace
DECL|function|scr_readw
r_static
r_inline
id|u16
id|scr_readw
c_func
(paren
r_const
id|u16
op_star
id|addr
)paren
(brace
id|BUG_ON
c_func
(paren
(paren
r_int
)paren
id|addr
op_ge
l_int|0
)paren
suffix:semicolon
r_return
op_star
id|addr
suffix:semicolon
)brace
DECL|macro|VGA_MAP_MEM
mdefine_line|#define VGA_MAP_MEM(x) (x)
macro_line|#endif
eof
