multiline_comment|/* $Id: ide.h,v 1.21 2001/09/25 20:21:48 kanoj Exp $&n; * ide.h: Ultra/PCI specific IDE glue.&n; *&n; * Copyright (C) 1997  David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1998  Eddie C. Dost   (ecd@skynet.be)&n; */
macro_line|#ifndef _SPARC64_IDE_H
DECL|macro|_SPARC64_IDE_H
mdefine_line|#define _SPARC64_IDE_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/spitfire.h&gt;
macro_line|#ifndef MAX_HWIFS
macro_line|# ifdef CONFIG_BLK_DEV_IDEPCI
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;10
macro_line|# else
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;2
macro_line|# endif
macro_line|#endif
DECL|macro|IDE_ARCH_OBSOLETE_INIT
mdefine_line|#define IDE_ARCH_OBSOLETE_INIT
DECL|macro|ide_default_io_ctl
mdefine_line|#define ide_default_io_ctl(base)&t;((base) + 0x206) /* obsolete */
DECL|macro|__ide_insl
mdefine_line|#define __ide_insl(data_reg, buffer, wcount) &bslash;&n;&t;__ide_insw(data_reg, buffer, (wcount)&lt;&lt;1)
DECL|macro|__ide_outsl
mdefine_line|#define __ide_outsl(data_reg, buffer, wcount) &bslash;&n;&t;__ide_outsw(data_reg, buffer, (wcount)&lt;&lt;1)
multiline_comment|/* On sparc64, I/O ports and MMIO registers are accessed identically.  */
DECL|macro|__ide_mm_insw
mdefine_line|#define __ide_mm_insw&t;__ide_insw
DECL|macro|__ide_mm_insl
mdefine_line|#define __ide_mm_insl&t;__ide_insl
DECL|macro|__ide_mm_outsw
mdefine_line|#define __ide_mm_outsw&t;__ide_outsw
DECL|macro|__ide_mm_outsl
mdefine_line|#define __ide_mm_outsl&t;__ide_outsl
DECL|function|inw_be
r_static
r_inline
r_int
r_int
id|inw_be
c_func
(paren
r_void
id|__iomem
op_star
id|addr
)paren
(brace
r_int
r_int
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lduha [%1] %2, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|__ide_insw
r_static
r_inline
r_void
id|__ide_insw
c_func
(paren
r_void
id|__iomem
op_star
id|port
comma
r_void
op_star
id|dst
comma
id|u32
id|count
)paren
(brace
macro_line|#if (L1DCACHE_SIZE &gt; PAGE_SIZE)&t;&t;/* is there D$ aliasing problem */
r_int
r_int
id|end
op_assign
(paren
r_int
r_int
)paren
id|dst
op_plus
(paren
id|count
op_lshift
l_int|1
)paren
suffix:semicolon
macro_line|#endif
id|u16
op_star
id|ps
op_assign
id|dst
suffix:semicolon
id|u32
op_star
id|pi
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|u64
)paren
id|ps
)paren
op_amp
l_int|0x2
)paren
(brace
op_star
id|ps
op_increment
op_assign
id|inw_be
c_func
(paren
id|port
)paren
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
id|pi
op_assign
(paren
id|u32
op_star
)paren
id|ps
suffix:semicolon
r_while
c_loop
(paren
id|count
op_ge
l_int|2
)paren
(brace
id|u32
id|w
suffix:semicolon
id|w
op_assign
id|inw_be
c_func
(paren
id|port
)paren
op_lshift
l_int|16
suffix:semicolon
id|w
op_or_assign
id|inw_be
c_func
(paren
id|port
)paren
suffix:semicolon
op_star
id|pi
op_increment
op_assign
id|w
suffix:semicolon
id|count
op_sub_assign
l_int|2
suffix:semicolon
)brace
id|ps
op_assign
(paren
id|u16
op_star
)paren
id|pi
suffix:semicolon
r_if
c_cond
(paren
id|count
)paren
(brace
op_star
id|ps
op_increment
op_assign
id|inw_be
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
macro_line|#if (L1DCACHE_SIZE &gt; PAGE_SIZE)&t;&t;/* is there D$ aliasing problem */
id|__flush_dcache_range
c_func
(paren
(paren
r_int
r_int
)paren
id|dst
comma
id|end
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|outw_be
r_static
r_inline
r_void
id|outw_be
c_func
(paren
r_int
r_int
id|w
comma
r_void
id|__iomem
op_star
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stha %0, [%1] %2&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|w
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
)brace
DECL|function|__ide_outsw
r_static
r_inline
r_void
id|__ide_outsw
c_func
(paren
r_void
id|__iomem
op_star
id|port
comma
r_void
op_star
id|src
comma
id|u32
id|count
)paren
(brace
macro_line|#if (L1DCACHE_SIZE &gt; PAGE_SIZE)&t;&t;/* is there D$ aliasing problem */
r_int
r_int
id|end
op_assign
(paren
r_int
r_int
)paren
id|src
op_plus
(paren
id|count
op_lshift
l_int|1
)paren
suffix:semicolon
macro_line|#endif
r_const
id|u16
op_star
id|ps
op_assign
id|src
suffix:semicolon
r_const
id|u32
op_star
id|pi
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|u64
)paren
id|src
)paren
op_amp
l_int|0x2
)paren
(brace
id|outw_be
c_func
(paren
op_star
id|ps
op_increment
comma
id|port
)paren
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
id|pi
op_assign
(paren
r_const
id|u32
op_star
)paren
id|ps
suffix:semicolon
r_while
c_loop
(paren
id|count
op_ge
l_int|2
)paren
(brace
id|u32
id|w
suffix:semicolon
id|w
op_assign
op_star
id|pi
op_increment
suffix:semicolon
id|outw_be
c_func
(paren
(paren
id|w
op_rshift
l_int|16
)paren
comma
id|port
)paren
suffix:semicolon
id|outw_be
c_func
(paren
id|w
comma
id|port
)paren
suffix:semicolon
id|count
op_sub_assign
l_int|2
suffix:semicolon
)brace
id|ps
op_assign
(paren
r_const
id|u16
op_star
)paren
id|pi
suffix:semicolon
r_if
c_cond
(paren
id|count
)paren
(brace
id|outw_be
c_func
(paren
op_star
id|ps
comma
id|port
)paren
suffix:semicolon
)brace
macro_line|#if (L1DCACHE_SIZE &gt; PAGE_SIZE)&t;&t;/* is there D$ aliasing problem */
id|__flush_dcache_range
c_func
(paren
(paren
r_int
r_int
)paren
id|src
comma
id|end
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _SPARC64_IDE_H */
eof
