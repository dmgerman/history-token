multiline_comment|/*&n; * Architecture specific parts of the Floppy driver&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995&n; */
macro_line|#ifndef __ASM_PPC64_FLOPPY_H
DECL|macro|__ASM_PPC64_FLOPPY_H
mdefine_line|#define __ASM_PPC64_FLOPPY_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|fd_inb
mdefine_line|#define fd_inb(port)&t;&t;&t;inb_p(port)
DECL|macro|fd_outb
mdefine_line|#define fd_outb(value,port)&t;&t;outb_p(value,port)
DECL|macro|fd_enable_dma
mdefine_line|#define fd_enable_dma()         enable_dma(FLOPPY_DMA)
DECL|macro|fd_disable_dma
mdefine_line|#define fd_disable_dma()        disable_dma(FLOPPY_DMA)
DECL|macro|fd_request_dma
mdefine_line|#define fd_request_dma()        request_dma(FLOPPY_DMA,&quot;floppy&quot;)
DECL|macro|fd_free_dma
mdefine_line|#define fd_free_dma()           free_dma(FLOPPY_DMA)
DECL|macro|fd_clear_dma_ff
mdefine_line|#define fd_clear_dma_ff()       clear_dma_ff(FLOPPY_DMA)
DECL|macro|fd_set_dma_mode
mdefine_line|#define fd_set_dma_mode(mode)   set_dma_mode(FLOPPY_DMA,mode)
DECL|macro|fd_set_dma_count
mdefine_line|#define fd_set_dma_count(count) set_dma_count(FLOPPY_DMA,count)
DECL|macro|fd_enable_irq
mdefine_line|#define fd_enable_irq()         enable_irq(FLOPPY_IRQ)
DECL|macro|fd_disable_irq
mdefine_line|#define fd_disable_irq()        disable_irq(FLOPPY_IRQ)
DECL|macro|fd_cacheflush
mdefine_line|#define fd_cacheflush(addr,size) /* nothing */
DECL|macro|fd_request_irq
mdefine_line|#define fd_request_irq()        request_irq(FLOPPY_IRQ, floppy_interrupt, &bslash;&n;&t;&t;&t;&t;&t;    SA_INTERRUPT|SA_SAMPLE_RANDOM, &bslash;&n;&t;&t;&t;&t;            &quot;floppy&quot;, NULL)
DECL|macro|fd_free_irq
mdefine_line|#define fd_free_irq()           free_irq(FLOPPY_IRQ, NULL);
macro_line|#ifdef CONFIG_PCI
macro_line|#include &lt;linux/pci.h&gt;
DECL|macro|fd_dma_setup
mdefine_line|#define fd_dma_setup(addr,size,mode,io) ppc64_fd_dma_setup(addr,size,mode,io)
r_static
id|__inline__
r_int
DECL|function|ppc64_fd_dma_setup
id|ppc64_fd_dma_setup
c_func
(paren
r_char
op_star
id|addr
comma
r_int
r_int
id|size
comma
r_int
id|mode
comma
r_int
id|io
)paren
(brace
r_static
r_int
r_int
id|prev_size
suffix:semicolon
r_static
id|dma_addr_t
id|bus_addr
op_assign
l_int|0
suffix:semicolon
r_static
r_char
op_star
id|prev_addr
suffix:semicolon
r_static
r_int
id|prev_dir
suffix:semicolon
r_int
id|dir
suffix:semicolon
id|dir
op_assign
(paren
id|mode
op_eq
id|DMA_MODE_READ
)paren
ques
c_cond
id|PCI_DMA_FROMDEVICE
suffix:colon
id|PCI_DMA_TODEVICE
suffix:semicolon
r_if
c_cond
(paren
id|bus_addr
op_logical_and
(paren
id|addr
op_ne
id|prev_addr
op_logical_or
id|size
op_ne
id|prev_size
op_logical_or
id|dir
op_ne
id|prev_dir
)paren
)paren
(brace
multiline_comment|/* different from last time -- unmap prev */
id|pci_unmap_single
c_func
(paren
l_int|NULL
comma
id|bus_addr
comma
id|prev_size
comma
id|prev_dir
)paren
suffix:semicolon
id|bus_addr
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|bus_addr
)paren
multiline_comment|/* need to map it */
(brace
id|bus_addr
op_assign
id|pci_map_single
c_func
(paren
l_int|NULL
comma
id|addr
comma
id|size
comma
id|dir
)paren
suffix:semicolon
)brace
multiline_comment|/* remember this one as prev */
id|prev_addr
op_assign
id|addr
suffix:semicolon
id|prev_size
op_assign
id|size
suffix:semicolon
id|prev_dir
op_assign
id|dir
suffix:semicolon
id|fd_clear_dma_ff
c_func
(paren
)paren
suffix:semicolon
id|fd_cacheflush
c_func
(paren
id|addr
comma
id|size
)paren
suffix:semicolon
id|fd_set_dma_mode
c_func
(paren
id|mode
)paren
suffix:semicolon
id|set_dma_addr
c_func
(paren
id|FLOPPY_DMA
comma
id|bus_addr
)paren
suffix:semicolon
id|fd_set_dma_count
c_func
(paren
id|size
)paren
suffix:semicolon
id|virtual_dma_port
op_assign
id|io
suffix:semicolon
id|fd_enable_dma
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PCI */
DECL|function|virtual_dma_init
id|__inline__
r_void
id|virtual_dma_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Nothing to do on PowerPC */
)brace
DECL|variable|FDC1
r_static
r_int
id|FDC1
op_assign
l_int|0x3f0
suffix:semicolon
DECL|variable|FDC2
r_static
r_int
id|FDC2
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n; * Again, the CMOS information not available&n; */
DECL|macro|FLOPPY0_TYPE
mdefine_line|#define FLOPPY0_TYPE 6
DECL|macro|FLOPPY1_TYPE
mdefine_line|#define FLOPPY1_TYPE 0
DECL|macro|N_FDC
mdefine_line|#define N_FDC 2&t;&t;&t;/* Don&squot;t change this! */
DECL|macro|N_DRIVE
mdefine_line|#define N_DRIVE 8
DECL|macro|FLOPPY_MOTOR_MASK
mdefine_line|#define FLOPPY_MOTOR_MASK 0xf0
multiline_comment|/*&n; * The PowerPC has no problems with floppy DMA crossing 64k borders.&n; */
DECL|macro|CROSS_64KB
mdefine_line|#define CROSS_64KB(a,s)&t;(0)
DECL|macro|EXTRA_FLOPPY_PARAMS
mdefine_line|#define EXTRA_FLOPPY_PARAMS
macro_line|#endif /* __ASM_PPC64_FLOPPY_H */
eof
