multiline_comment|/*&n; *&t;Access to VGA videoram&n; *&n; *&t;(c) 1998 Martin Mares &lt;mj@ucw.cz&gt;&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_ASM_VGA_H_
DECL|macro|_LINUX_ASM_VGA_H_
mdefine_line|#define _LINUX_ASM_VGA_H_
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_VGA_CONSOLE) || defined(CONFIG_MDA_CONSOLE)
DECL|macro|VT_BUF_HAVE_RW
mdefine_line|#define VT_BUF_HAVE_RW
multiline_comment|/*&n; *  These are only needed for supporting VGA or MDA text mode, which use little&n; *  endian byte ordering.&n; *  In other cases, we can optimize by using native byte ordering and&n; *  &lt;linux/vt_buffer.h&gt; has already done the right job for us.&n; */
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
r_volatile
id|u16
op_star
id|addr
)paren
(brace
id|st_le16
c_func
(paren
id|addr
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|scr_readw
r_static
r_inline
id|u16
id|scr_readw
c_func
(paren
r_volatile
r_const
id|u16
op_star
id|addr
)paren
(brace
r_return
id|ld_le16
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|macro|VT_BUF_HAVE_MEMCPYW
mdefine_line|#define VT_BUF_HAVE_MEMCPYW
DECL|macro|scr_memcpyw
mdefine_line|#define scr_memcpyw&t;memcpy
macro_line|#endif /* !CONFIG_VGA_CONSOLE &amp;&amp; !CONFIG_MDA_CONSOLE */
r_extern
r_int
r_int
id|vgacon_remap_base
suffix:semicolon
DECL|macro|VGA_MAP_MEM
mdefine_line|#define VGA_MAP_MEM(x) ((unsigned long) ioremap((x), 0))
DECL|macro|vga_readb
mdefine_line|#define vga_readb(x) (*(x))
DECL|macro|vga_writeb
mdefine_line|#define vga_writeb(x,y) (*(y) = (x))
macro_line|#endif
eof
