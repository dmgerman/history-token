macro_line|#ifndef _ASM_M68K_ZORRO_H
DECL|macro|_ASM_M68K_ZORRO_H
mdefine_line|#define _ASM_M68K_ZORRO_H
macro_line|#include &lt;asm/raw_io.h&gt;
DECL|macro|z_readb
mdefine_line|#define z_readb raw_inb
DECL|macro|z_readw
mdefine_line|#define z_readw raw_inw
DECL|macro|z_readl
mdefine_line|#define z_readl raw_inl
DECL|macro|z_writeb
mdefine_line|#define z_writeb raw_outb
DECL|macro|z_writew
mdefine_line|#define z_writew raw_outw
DECL|macro|z_writel
mdefine_line|#define z_writel raw_outl
DECL|macro|z_memset_io
mdefine_line|#define z_memset_io(a,b,c)&t;memset((void *)(a),(b),(c))
DECL|macro|z_memcpy_fromio
mdefine_line|#define z_memcpy_fromio(a,b,c)&t;memcpy((a),(void *)(b),(c))
DECL|macro|z_memcpy_toio
mdefine_line|#define z_memcpy_toio(a,b,c)&t;memcpy((void *)(a),(b),(c))
DECL|function|z_remap_nocache_ser
r_extern
r_inline
r_void
op_star
id|z_remap_nocache_ser
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
DECL|function|z_remap_nocache_nonser
r_extern
r_inline
r_void
op_star
id|z_remap_nocache_nonser
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
DECL|function|z_remap_writethrough
r_extern
r_inline
r_void
op_star
id|z_remap_writethrough
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
DECL|function|z_remap_fullcache
r_extern
r_inline
r_void
op_star
id|z_remap_fullcache
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
DECL|macro|z_unmap
mdefine_line|#define z_unmap iounmap
DECL|macro|z_iounmap
mdefine_line|#define z_iounmap iounmap
DECL|macro|z_ioremap
mdefine_line|#define z_ioremap z_remap_nocache_ser
macro_line|#endif /* _ASM_ZORRO_H */
eof
