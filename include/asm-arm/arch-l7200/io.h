multiline_comment|/*&n; * linux/include/asm-arm/arch-l7200/io.h&n; *&n; * Copyright (C) 2000 Steve Hill (sjhill@cotw.com)&n; *&n; * Changelog:&n; *  03-21-2000&t;SJH&t;Created from linux/include/asm-arm/arch-nexuspci/io.h&n; *  08-31-2000&t;SJH&t;Added in IO functions necessary for new drivers&n; */
macro_line|#ifndef __ASM_ARM_ARCH_IO_H
DECL|macro|__ASM_ARM_ARCH_IO_H
mdefine_line|#define __ASM_ARM_ARCH_IO_H
macro_line|#include &lt;asm/arch/hardware.h&gt;
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffffffff
multiline_comment|/*&n; * There are not real ISA nor PCI buses, so we fake it.&n; */
DECL|macro|__io_pci
mdefine_line|#define __io_pci(a)             (PCIO_BASE + (a))
DECL|macro|__mem_pci
mdefine_line|#define __mem_pci(a)            ((unsigned long)(a))
DECL|macro|__mem_isa
mdefine_line|#define __mem_isa(a)            ((unsigned long)(a))
DECL|macro|__ioaddr
mdefine_line|#define __ioaddr(p)             __io_pci(p)
multiline_comment|/*&n; * Generic virtual read/write&n; */
DECL|macro|__arch_getb
mdefine_line|#define __arch_getb(a)          (*(volatile unsigned char *)(a))
DECL|macro|__arch_getl
mdefine_line|#define __arch_getl(a)          (*(volatile unsigned int  *)(a))
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
l_string|&quot;ldr%?h    %0, [%1, #0]    @ getw&quot;
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
DECL|macro|__arch_putb
mdefine_line|#define __arch_putb(v,a)        (*(volatile unsigned char *)(a) = (v))
DECL|macro|__arch_putl
mdefine_line|#define __arch_putl(v,a)        (*(volatile unsigned int  *)(a) = (v))
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
l_string|&quot;str%?h    %0, [%1, #0]    @ putw&quot;
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
multiline_comment|/*&n; * Translated address IO functions&n; *&n; * IO address has already been translated to a virtual address&n; */
DECL|macro|outb_t
mdefine_line|#define outb_t(v,p)&t;&t;(*(volatile unsigned char *)(p) = (v))
DECL|macro|inb_t
mdefine_line|#define inb_t(p)&t;&t;(*(volatile unsigned char *)(p))
DECL|macro|outw_t
mdefine_line|#define outw_t(v,p)&t;&t;(*(volatile unsigned int *)(p) = (v))
DECL|macro|inw_t
mdefine_line|#define inw_t(p)&t;&t;(*(volatile unsigned int *)(p))
DECL|macro|outl_t
mdefine_line|#define outl_t(v,p)&t;&t;(*(volatile unsigned long *)(p) = (v))
DECL|macro|inl_t
mdefine_line|#define inl_t(p)&t;&t;(*(volatile unsigned long *)(p))
multiline_comment|/*&n; * FIXME - These are to allow for linking. On all the other&n; *         ARM platforms, the entire IO space is contiguous.&n; *         The 7200 has three separate IO spaces. The below&n; *         macros will eventually become more involved. Use&n; *         with caution and don&squot;t be surprised by kernel oopses!!!&n; */
DECL|macro|inb
mdefine_line|#define inb(p)&t;&t; &t;inb_t(p)
DECL|macro|inw
mdefine_line|#define inw(p)&t; &t;&t;inw_t(p)
DECL|macro|inl
mdefine_line|#define inl(p)&t; &t;&t;inl_t(p)
DECL|macro|outb
mdefine_line|#define outb(v,p)&t;&t;outb_t(v,p)
DECL|macro|outw
mdefine_line|#define outw(v,p)&t;&t;outw_t(v,p)
DECL|macro|outl
mdefine_line|#define outl(v,p)&t;&t;outl_t(v,p)
macro_line|#endif
eof
