macro_line|#ifndef _ASM_PPC_ZORRO_H
DECL|macro|_ASM_PPC_ZORRO_H
mdefine_line|#define _ASM_PPC_ZORRO_H
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|z_readb
mdefine_line|#define z_readb in_8
DECL|macro|z_readw
mdefine_line|#define z_readw in_be16
DECL|macro|z_readl
mdefine_line|#define z_readl in_be32
DECL|macro|z_writeb
mdefine_line|#define z_writeb(val, port) out_8((port), (val))
DECL|macro|z_writew
mdefine_line|#define z_writew(val, port) out_be16((port), (val))
DECL|macro|z_writel
mdefine_line|#define z_writel(val, port) out_be32((port), (val))
DECL|macro|z_memset_io
mdefine_line|#define z_memset_io(a,b,c)&t;memset((void *)(a),(b),(c))
DECL|macro|z_memcpy_fromio
mdefine_line|#define z_memcpy_fromio(a,b,c)&t;memcpy((a),(void *)(b),(c))
DECL|macro|z_memcpy_toio
mdefine_line|#define z_memcpy_toio(a,b,c)&t;memcpy((void *)(a),(b),(c))
r_extern
r_void
op_star
id|__ioremap
c_func
(paren
r_int
r_int
id|address
comma
r_int
r_int
id|size
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
r_extern
r_void
op_star
id|ioremap
c_func
(paren
r_int
r_int
id|address
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|iounmap
c_func
(paren
r_void
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_void
op_star
id|__ioremap
c_func
(paren
r_int
r_int
id|address
comma
r_int
r_int
id|size
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
DECL|macro|z_ioremap
mdefine_line|#define z_ioremap ioremap
DECL|macro|z_iounmap
mdefine_line|#define z_iounmap iounmap
macro_line|#endif /* _ASM_ZORRO_H */
eof
