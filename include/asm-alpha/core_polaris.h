macro_line|#ifndef __ALPHA_POLARIS__H__
DECL|macro|__ALPHA_POLARIS__H__
mdefine_line|#define __ALPHA_POLARIS__H__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/compiler.h&gt;
multiline_comment|/*&n; * POLARIS is the internal name for a core logic chipset which provides&n; * memory controller and PCI access for the 21164PC chip based systems.&n; *&n; * This file is based on:&n; *&n; * Polaris System Controller&n; * Device Functional Specification&n; * 22-Jan-98&n; * Rev. 4.2&n; *&n; */
multiline_comment|/* Polaris memory regions */
DECL|macro|POLARIS_SPARSE_MEM_BASE
mdefine_line|#define POLARIS_SPARSE_MEM_BASE&t;&t;(IDENT_ADDR + 0xf800000000UL)
DECL|macro|POLARIS_DENSE_MEM_BASE
mdefine_line|#define POLARIS_DENSE_MEM_BASE&t;&t;(IDENT_ADDR + 0xf900000000UL)
DECL|macro|POLARIS_SPARSE_IO_BASE
mdefine_line|#define POLARIS_SPARSE_IO_BASE&t;&t;(IDENT_ADDR + 0xf980000000UL)
DECL|macro|POLARIS_SPARSE_CONFIG_BASE
mdefine_line|#define POLARIS_SPARSE_CONFIG_BASE&t;(IDENT_ADDR + 0xf9c0000000UL)
DECL|macro|POLARIS_IACK_BASE
mdefine_line|#define POLARIS_IACK_BASE&t;&t;(IDENT_ADDR + 0xf9f8000000UL)
DECL|macro|POLARIS_DENSE_IO_BASE
mdefine_line|#define POLARIS_DENSE_IO_BASE&t;&t;(IDENT_ADDR + 0xf9fc000000UL)
DECL|macro|POLARIS_DENSE_CONFIG_BASE
mdefine_line|#define POLARIS_DENSE_CONFIG_BASE&t;(IDENT_ADDR + 0xf9fe000000UL)
DECL|macro|POLARIS_IACK_SC
mdefine_line|#define POLARIS_IACK_SC&t;&t;&t;POLARIS_IACK_BASE
multiline_comment|/* The Polaris command/status registers live in PCI Config space for&n; * bus 0/device 0.  As such, they may be bytes, words, or doublewords.&n; */
DECL|macro|POLARIS_W_VENID
mdefine_line|#define POLARIS_W_VENID&t;&t;(POLARIS_DENSE_CONFIG_BASE)
DECL|macro|POLARIS_W_DEVID
mdefine_line|#define POLARIS_W_DEVID&t;&t;(POLARIS_DENSE_CONFIG_BASE+2)
DECL|macro|POLARIS_W_CMD
mdefine_line|#define POLARIS_W_CMD&t;&t;(POLARIS_DENSE_CONFIG_BASE+4)
DECL|macro|POLARIS_W_STATUS
mdefine_line|#define POLARIS_W_STATUS&t;(POLARIS_DENSE_CONFIG_BASE+6)
multiline_comment|/*&n; * Data structure for handling POLARIS machine checks:&n; */
DECL|struct|el_POLARIS_sysdata_mcheck
r_struct
id|el_POLARIS_sysdata_mcheck
(brace
DECL|member|psc_status
id|u_long
id|psc_status
suffix:semicolon
DECL|member|psc_pcictl0
id|u_long
id|psc_pcictl0
suffix:semicolon
DECL|member|psc_pcictl1
id|u_long
id|psc_pcictl1
suffix:semicolon
DECL|member|psc_pcictl2
id|u_long
id|psc_pcictl2
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
mdefine_line|#define __EXTERN_INLINE extern inline
DECL|macro|__IO_EXTERN_INLINE
mdefine_line|#define __IO_EXTERN_INLINE
macro_line|#endif
multiline_comment|/*&n; * I/O functions:&n; *&n; * POLARIS, the PCI/memory support chipset for the PCA56 (21164PC)&n; * processors, can use either a sparse address  mapping scheme, or the &n; * so-called byte-word PCI address space, to get at PCI memory and I/O.&n; *&n; * However, we will support only the BWX form.&n; */
multiline_comment|/*&n; * Memory functions.  Polaris allows all accesses (byte/word&n; * as well as long/quad) to be done through dense space.&n; *&n; * We will only support DENSE access via BWX insns.&n; */
DECL|function|polaris_ioportmap
id|__EXTERN_INLINE
r_void
id|__iomem
op_star
id|polaris_ioportmap
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
(paren
r_void
id|__iomem
op_star
)paren
(paren
id|addr
op_plus
id|POLARIS_DENSE_IO_BASE
)paren
suffix:semicolon
)brace
DECL|function|polaris_ioremap
id|__EXTERN_INLINE
r_void
id|__iomem
op_star
id|polaris_ioremap
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_return
(paren
r_void
id|__iomem
op_star
)paren
(paren
id|addr
op_plus
id|POLARIS_DENSE_MEM_BASE
)paren
suffix:semicolon
)brace
DECL|function|polaris_is_ioaddr
id|__EXTERN_INLINE
r_int
id|polaris_is_ioaddr
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|addr
op_ge
id|POLARIS_SPARSE_MEM_BASE
suffix:semicolon
)brace
DECL|function|polaris_is_mmio
id|__EXTERN_INLINE
r_int
id|polaris_is_mmio
c_func
(paren
r_const
r_volatile
r_void
id|__iomem
op_star
id|addr
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|addr
OL
id|POLARIS_SPARSE_IO_BASE
suffix:semicolon
)brace
DECL|macro|__IO_PREFIX
macro_line|#undef __IO_PREFIX
DECL|macro|__IO_PREFIX
mdefine_line|#define __IO_PREFIX&t;&t;polaris
DECL|macro|polaris_trivial_rw_bw
mdefine_line|#define polaris_trivial_rw_bw&t;1
DECL|macro|polaris_trivial_rw_lq
mdefine_line|#define polaris_trivial_rw_lq&t;1
DECL|macro|polaris_trivial_io_bw
mdefine_line|#define polaris_trivial_io_bw&t;1
DECL|macro|polaris_trivial_io_lq
mdefine_line|#define polaris_trivial_io_lq&t;1
DECL|macro|polaris_trivial_iounmap
mdefine_line|#define polaris_trivial_iounmap&t;1
macro_line|#include &lt;asm/io_trivial.h&gt;
macro_line|#ifdef __IO_EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
macro_line|#undef __EXTERN_INLINE
DECL|macro|__IO_EXTERN_INLINE
macro_line|#undef __IO_EXTERN_INLINE
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ALPHA_POLARIS__H__ */
eof
