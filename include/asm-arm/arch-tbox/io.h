multiline_comment|/*&n; * linux/include/asm-arm/arch-tbox/io.h&n; *&n; * Copyright (C) 1996-1999 Russell King&n; * Copyright (C) 1998, 1999 Philip Blundell&n; *&n; */
macro_line|#ifndef __ASM_ARM_ARCH_IO_H
DECL|macro|__ASM_ARM_ARCH_IO_H
mdefine_line|#define __ASM_ARM_ARCH_IO_H
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffffffff
DECL|macro|__io
mdefine_line|#define __io(_x)&t;&t;((_x) &lt;&lt; 2)
multiline_comment|/*&n; * Generic virtual read/write&n; */
DECL|function|__arch_getw
r_static
r_inline
r_int
r_int
id|__arch_getw
c_func
(paren
r_int
r_int
id|a
)paren
(brace
r_int
r_int
id|value
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ldr%?h&t;%0, [%1, #0]&t;@ getw&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|value
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|a
)paren
)paren
suffix:semicolon
r_return
id|value
suffix:semicolon
)brace
DECL|function|__arch_putw
r_static
r_inline
r_void
id|__arch_putw
c_func
(paren
r_int
r_int
id|value
comma
r_int
r_int
id|a
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;str%?h&t;%0, [%1, #0]&t;@ putw&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|value
)paren
comma
l_string|&quot;r&quot;
(paren
id|a
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Idem, for devices on the upper byte lanes */
DECL|macro|inb_u
mdefine_line|#define inb_u(p)&t;&t;__arch_getb(__io_pc(p) + 2)
DECL|macro|inw_u
mdefine_line|#define inw_u(p)&t;&t;__arch_getw(__io_pc(p) + 2)
DECL|macro|outb_u
mdefine_line|#define outb_u(v,p)&t;&t;__arch_putb(v,__io_pc(p) + 2)
DECL|macro|outw_u
mdefine_line|#define outw_u(v,p)&t;&t;__arch_putw(v,__io_pc(p) + 2)
macro_line|#endif
eof
