macro_line|#ifndef _ASM_M68K_NUBUS_H
DECL|macro|_ASM_M68K_NUBUS_H
mdefine_line|#define _ASM_M68K_NUBUS_H
macro_line|#include &lt;asm/raw_io.h&gt;
DECL|macro|nubus_readb
mdefine_line|#define nubus_readb raw_inb
DECL|macro|nubus_readw
mdefine_line|#define nubus_readw raw_inw
DECL|macro|nubus_readl
mdefine_line|#define nubus_readl raw_inl
DECL|macro|nubus_writeb
mdefine_line|#define nubus_writeb raw_outb
DECL|macro|nubus_writew
mdefine_line|#define nubus_writew raw_outw
DECL|macro|nubus_writel
mdefine_line|#define nubus_writel raw_outl
DECL|macro|nubus_memset_io
mdefine_line|#define nubus_memset_io(a,b,c)&t;&t;memset((void *)(a),(b),(c))
DECL|macro|nubus_memcpy_fromio
mdefine_line|#define nubus_memcpy_fromio(a,b,c)&t;memcpy((a),(void *)(b),(c))
DECL|macro|nubus_memcpy_toio
mdefine_line|#define nubus_memcpy_toio(a,b,c)&t;memcpy((void *)(a),(b),(c))
DECL|function|nubus_remap_nocache_ser
r_extern
r_inline
r_void
op_star
id|nubus_remap_nocache_ser
c_func
(paren
r_int
r_int
id|physaddr
comma
r_int
r_int
id|size
)paren
(brace
r_return
id|__ioremap
c_func
(paren
id|physaddr
comma
id|size
comma
id|IOMAP_NOCACHE_SER
)paren
suffix:semicolon
)brace
DECL|function|nubus_remap_nocache_nonser
r_extern
r_inline
r_void
op_star
id|nubus_remap_nocache_nonser
c_func
(paren
r_int
r_int
id|physaddr
comma
r_int
r_int
id|size
)paren
(brace
r_return
id|__ioremap
c_func
(paren
id|physaddr
comma
id|size
comma
id|IOMAP_NOCACHE_NONSER
)paren
suffix:semicolon
)brace
DECL|function|nbus_remap_writethrough
r_extern
r_inline
r_void
op_star
id|nbus_remap_writethrough
c_func
(paren
r_int
r_int
id|physaddr
comma
r_int
r_int
id|size
)paren
(brace
r_return
id|__ioremap
c_func
(paren
id|physaddr
comma
id|size
comma
id|IOMAP_WRITETHROUGH
)paren
suffix:semicolon
)brace
DECL|function|nubus_remap_fullcache
r_extern
r_inline
r_void
op_star
id|nubus_remap_fullcache
c_func
(paren
r_int
r_int
id|physaddr
comma
r_int
r_int
id|size
)paren
(brace
r_return
id|__ioremap
c_func
(paren
id|physaddr
comma
id|size
comma
id|IOMAP_FULL_CACHING
)paren
suffix:semicolon
)brace
DECL|macro|nubus_unmap
mdefine_line|#define nubus_unmap iounmap
DECL|macro|nubus_iounmap
mdefine_line|#define nubus_iounmap iounmap
DECL|macro|nubus_ioremap
mdefine_line|#define nubus_ioremap nubus_remap_nocache_ser
macro_line|#endif /* _ASM_NUBUS_H */
eof
