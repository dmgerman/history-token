multiline_comment|/*&n; *  linux/include/asm-parisc/ide.h&n; *&n; *  Copyright (C) 1994-1996  Linus Torvalds &amp; authors&n; */
multiline_comment|/*&n; *  This file contains the PARISC architecture specific IDE code.&n; */
macro_line|#ifndef __ASM_PARISC_IDE_H
DECL|macro|__ASM_PARISC_IDE_H
mdefine_line|#define __ASM_PARISC_IDE_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef MAX_HWIFS
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;2
macro_line|#endif
DECL|macro|IDE_ARCH_OBSOLETE_INIT
mdefine_line|#define IDE_ARCH_OBSOLETE_INIT
DECL|macro|ide_default_io_ctl
mdefine_line|#define ide_default_io_ctl(base)&t;((base) + 0x206) /* obsolete */
DECL|macro|ide_request_irq
mdefine_line|#define ide_request_irq(irq,hand,flg,dev,id)&t;request_irq((irq),(hand),(flg),(dev),(id))
DECL|macro|ide_free_irq
mdefine_line|#define ide_free_irq(irq,dev_id)&t;&t;free_irq((irq), (dev_id))
DECL|macro|ide_check_region
mdefine_line|#define ide_check_region(from,extent)&t;&t;check_region((from), (extent))
DECL|macro|ide_request_region
mdefine_line|#define ide_request_region(from,extent,name)&t;request_region((from), (extent), (name))
DECL|macro|ide_release_region
mdefine_line|#define ide_release_region(from,extent)&t;&t;release_region((from), (extent))
multiline_comment|/* Generic I/O and MEMIO string operations.  */
DECL|macro|__ide_insw
mdefine_line|#define __ide_insw&t;insw
DECL|macro|__ide_insl
mdefine_line|#define __ide_insl&t;insl
DECL|macro|__ide_outsw
mdefine_line|#define __ide_outsw&t;outsw
DECL|macro|__ide_outsl
mdefine_line|#define __ide_outsl&t;outsl
DECL|function|__ide_mm_insw
r_static
id|__inline__
r_void
id|__ide_mm_insw
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|addr
comma
id|u32
id|count
)paren
(brace
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
op_star
(paren
id|u16
op_star
)paren
id|addr
op_assign
id|__raw_readw
c_func
(paren
id|port
)paren
suffix:semicolon
id|addr
op_add_assign
l_int|2
suffix:semicolon
)brace
)brace
DECL|function|__ide_mm_insl
r_static
id|__inline__
r_void
id|__ide_mm_insl
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|addr
comma
id|u32
id|count
)paren
(brace
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
op_star
(paren
id|u32
op_star
)paren
id|addr
op_assign
id|__raw_readl
c_func
(paren
id|port
)paren
suffix:semicolon
id|addr
op_add_assign
l_int|4
suffix:semicolon
)brace
)brace
DECL|function|__ide_mm_outsw
r_static
id|__inline__
r_void
id|__ide_mm_outsw
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|addr
comma
id|u32
id|count
)paren
(brace
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
id|__raw_writew
c_func
(paren
op_star
(paren
id|u16
op_star
)paren
id|addr
comma
id|port
)paren
suffix:semicolon
id|addr
op_add_assign
l_int|2
suffix:semicolon
)brace
)brace
DECL|function|__ide_mm_outsl
r_static
id|__inline__
r_void
id|__ide_mm_outsl
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|addr
comma
id|u32
id|count
)paren
(brace
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
id|__raw_writel
c_func
(paren
op_star
(paren
id|u32
op_star
)paren
id|addr
comma
id|port
)paren
suffix:semicolon
id|addr
op_add_assign
l_int|4
suffix:semicolon
)brace
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_PARISC_IDE_H */
eof
