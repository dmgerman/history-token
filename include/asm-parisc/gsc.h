macro_line|#ifndef ASM_PARISC_GSC_H
DECL|macro|ASM_PARISC_GSC_H
mdefine_line|#define ASM_PARISC_GSC_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/io.h&gt; /* temporary for __raw_{read,write} */
multiline_comment|/* Please, call ioremap and use {read,write}[bwl] instead.  These functions&n; * are not very fast.&n; */
DECL|macro|gsc_readb
mdefine_line|#define gsc_readb(x) __raw_readb((unsigned long)x)
DECL|macro|gsc_readw
mdefine_line|#define gsc_readw(x) __raw_readw((unsigned long)x)
DECL|macro|gsc_readl
mdefine_line|#define gsc_readl(x) __raw_readl((unsigned long)x)
DECL|macro|gsc_writeb
mdefine_line|#define gsc_writeb(x, y) __raw_writeb(x, (unsigned long)y)
DECL|macro|gsc_writew
mdefine_line|#define gsc_writew(x, y) __raw_writew(x, (unsigned long)y)
DECL|macro|gsc_writel
mdefine_line|#define gsc_writel(x, y) __raw_writel(x, (unsigned long)y)
DECL|struct|gsc_irq
r_struct
id|gsc_irq
(brace
DECL|member|txn_addr
r_int
r_int
id|txn_addr
suffix:semicolon
multiline_comment|/* IRQ &quot;target&quot; */
DECL|member|txn_data
r_int
id|txn_data
suffix:semicolon
multiline_comment|/* HW &quot;IRQ&quot; */
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* virtual IRQ */
)brace
suffix:semicolon
multiline_comment|/* PA I/O Architected devices support at least 5 bits in the EIM register. */
DECL|macro|GSC_EIM_WIDTH
mdefine_line|#define GSC_EIM_WIDTH 5
r_extern
r_int
id|gsc_alloc_irq
c_func
(paren
r_struct
id|gsc_irq
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* dev needs an irq */
r_extern
r_int
id|gsc_claim_irq
c_func
(paren
r_struct
id|gsc_irq
op_star
id|dev
comma
r_int
id|irq
)paren
suffix:semicolon
multiline_comment|/* dev needs this irq */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* LINUX_GSC_H */
eof
