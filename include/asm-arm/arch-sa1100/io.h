multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/io.h&n; *&n; * Copyright (C) 1997-1999 Russell King&n; *&n; * Modifications:&n; *  06-12-1997&t;RMK&t;Created.&n; *  07-04-1999&t;RMK&t;Major cleanup&n; */
macro_line|#ifndef __ASM_ARM_ARCH_IO_H
DECL|macro|__ASM_ARM_ARCH_IO_H
mdefine_line|#define __ASM_ARM_ARCH_IO_H
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffffffff
multiline_comment|/*&n; * We don&squot;t actually have real ISA nor PCI buses, but there is so many &n; * drivers out there that might just work if we fake them...&n; */
DECL|macro|__io_pci
mdefine_line|#define __io_pci(a)&t;&t;(PCIO_BASE + (a))
DECL|macro|__mem_pci
mdefine_line|#define __mem_pci(a)&t;&t;((unsigned long)(a))
DECL|macro|__mem_isa
mdefine_line|#define __mem_isa(a)&t;&t;((unsigned long)(a))
DECL|macro|__ioaddr
mdefine_line|#define __ioaddr(p)&t;&t;__io_pci(p)
multiline_comment|/*&n; * Generic virtual read/write&n; */
DECL|macro|__arch_getb
mdefine_line|#define __arch_getb(a)&t;&t;(*(volatile unsigned char *)(a))
DECL|macro|__arch_getl
mdefine_line|#define __arch_getl(a)&t;&t;(*(volatile unsigned int  *)(a))
DECL|function|__arch_getw
r_extern
id|__inline__
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
DECL|macro|__arch_putb
mdefine_line|#define __arch_putb(v,a)&t;(*(volatile unsigned char *)(a) = (v))
DECL|macro|__arch_putl
mdefine_line|#define __arch_putl(v,a)&t;(*(volatile unsigned int  *)(a) = (v))
DECL|function|__arch_putw
r_extern
id|__inline__
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
DECL|macro|inb
mdefine_line|#define inb(p)&t;&t;&t;__arch_getb(__io_pci(p))
DECL|macro|inw
mdefine_line|#define inw(p)&t;&t;&t;__arch_getw(__io_pci(p))
DECL|macro|inl
mdefine_line|#define inl(p)&t;&t;&t;__arch_getl(__io_pci(p))
DECL|macro|outb
mdefine_line|#define outb(v,p)&t;&t;__arch_putb(v,__io_pci(p))
DECL|macro|outw
mdefine_line|#define outw(v,p)&t;&t;__arch_putw(v,__io_pci(p))
DECL|macro|outl
mdefine_line|#define outl(v,p)&t;&t;__arch_putl(v,__io_pci(p))
DECL|macro|__arch_ioremap
mdefine_line|#define __arch_ioremap&t;&t;__ioremap
macro_line|#endif
eof
