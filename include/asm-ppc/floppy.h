multiline_comment|/*&n; * BK Id: SCCS/s.floppy.h 1.5 05/17/01 18:14:24 cort&n; */
multiline_comment|/*&n; * Architecture specific parts of the Floppy driver&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_PPC_FLOPPY_H
DECL|macro|__ASM_PPC_FLOPPY_H
mdefine_line|#define __ASM_PPC_FLOPPY_H
DECL|macro|fd_inb
mdefine_line|#define fd_inb(port)&t;&t;&t;inb_p(port)
DECL|macro|fd_outb
mdefine_line|#define fd_outb(port,value)&t;&t;outb_p(port,value)
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
DECL|macro|fd_set_dma_addr
mdefine_line|#define fd_set_dma_addr(addr)   set_dma_addr(FLOPPY_DMA,(unsigned int)virt_to_bus(addr))
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
macro_line|#endif /* __ASM_PPC_FLOPPY_H */
macro_line|#endif /* __KERNEL__ */
eof
