multiline_comment|/*&n; * Architecture specific parts of the Floppy driver&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995 - 2000 Ralf Baechle&n; */
macro_line|#ifndef _ASM_FLOPPY_H
DECL|macro|_ASM_FLOPPY_H
mdefine_line|#define _ASM_FLOPPY_H
macro_line|#include &lt;asm/bootinfo.h&gt;
DECL|struct|fd_ops
r_struct
id|fd_ops
(brace
DECL|member|fd_inb
r_int
r_char
(paren
op_star
id|fd_inb
)paren
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
DECL|member|fd_outb
r_void
(paren
op_star
id|fd_outb
)paren
(paren
r_int
r_char
id|value
comma
r_int
r_int
id|port
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * How to access the floppy DMA functions.&n;&t; */
DECL|member|fd_enable_dma
r_void
(paren
op_star
id|fd_enable_dma
)paren
(paren
r_int
id|channel
)paren
suffix:semicolon
DECL|member|fd_disable_dma
r_void
(paren
op_star
id|fd_disable_dma
)paren
(paren
r_int
id|channel
)paren
suffix:semicolon
DECL|member|fd_request_dma
r_int
(paren
op_star
id|fd_request_dma
)paren
(paren
r_int
id|channel
)paren
suffix:semicolon
DECL|member|fd_free_dma
r_void
(paren
op_star
id|fd_free_dma
)paren
(paren
r_int
id|channel
)paren
suffix:semicolon
DECL|member|fd_clear_dma_ff
r_void
(paren
op_star
id|fd_clear_dma_ff
)paren
(paren
r_int
id|channel
)paren
suffix:semicolon
DECL|member|fd_set_dma_mode
r_void
(paren
op_star
id|fd_set_dma_mode
)paren
(paren
r_int
id|channel
comma
r_char
id|mode
)paren
suffix:semicolon
DECL|member|fd_set_dma_addr
r_void
(paren
op_star
id|fd_set_dma_addr
)paren
(paren
r_int
id|channel
comma
r_int
r_int
id|a
)paren
suffix:semicolon
DECL|member|fd_set_dma_count
r_void
(paren
op_star
id|fd_set_dma_count
)paren
(paren
r_int
id|channel
comma
r_int
r_int
id|count
)paren
suffix:semicolon
DECL|member|fd_get_dma_residue
r_int
(paren
op_star
id|fd_get_dma_residue
)paren
(paren
r_int
id|channel
)paren
suffix:semicolon
DECL|member|fd_enable_irq
r_void
(paren
op_star
id|fd_enable_irq
)paren
(paren
r_int
id|irq
)paren
suffix:semicolon
DECL|member|fd_disable_irq
r_void
(paren
op_star
id|fd_disable_irq
)paren
(paren
r_int
id|irq
)paren
suffix:semicolon
DECL|member|fd_getfdaddr1
r_int
r_int
(paren
op_star
id|fd_getfdaddr1
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|fd_dma_mem_alloc
r_int
r_int
(paren
op_star
id|fd_dma_mem_alloc
)paren
(paren
r_int
r_int
id|size
)paren
suffix:semicolon
DECL|member|fd_dma_mem_free
r_void
(paren
op_star
id|fd_dma_mem_free
)paren
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|size
)paren
suffix:semicolon
DECL|member|fd_drive_type
r_int
r_int
(paren
op_star
id|fd_drive_type
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|fd_ops
op_star
id|fd_ops
suffix:semicolon
DECL|macro|fd_inb
mdefine_line|#define fd_inb(port)&t;&t;fd_ops-&gt;fd_inb(port)
DECL|macro|fd_outb
mdefine_line|#define fd_outb(value,port)&t;fd_ops-&gt;fd_outb(value,port)
DECL|macro|fd_enable_dma
mdefine_line|#define fd_enable_dma()&t;&t;fd_ops-&gt;fd_enable_dma(FLOPPY_DMA)
DECL|macro|fd_disable_dma
mdefine_line|#define fd_disable_dma()&t;fd_ops-&gt;fd_disable_dma(FLOPPY_DMA)
DECL|macro|fd_request_dma
mdefine_line|#define fd_request_dma()&t;fd_ops-&gt;fd_request_dma(FLOPPY_DMA)
DECL|macro|fd_free_dma
mdefine_line|#define fd_free_dma()&t;&t;fd_ops-&gt;fd_free_dma(FLOPPY_DMA)
DECL|macro|fd_clear_dma_ff
mdefine_line|#define fd_clear_dma_ff()&t;fd_ops-&gt;fd_clear_dma_ff(FLOPPY_DMA)
DECL|macro|fd_set_dma_mode
mdefine_line|#define fd_set_dma_mode(mode)&t;fd_ops-&gt;fd_set_dma_mode(FLOPPY_DMA, mode)
DECL|macro|fd_set_dma_addr
mdefine_line|#define fd_set_dma_addr(addr)&t;fd_ops-&gt;fd_set_dma_addr(FLOPPY_DMA, &bslash;&n;&t;&t;&t;&t;                       virt_to_bus(addr))
DECL|macro|fd_set_dma_count
mdefine_line|#define fd_set_dma_count(count)&t;fd_ops-&gt;fd_set_dma_count(FLOPPY_DMA,count)
DECL|macro|fd_get_dma_residue
mdefine_line|#define fd_get_dma_residue()&t;fd_ops-&gt;fd_get_dma_residue(FLOPPY_DMA)
DECL|macro|fd_enable_irq
mdefine_line|#define fd_enable_irq()&t;&t;fd_ops-&gt;fd_enable_irq(FLOPPY_IRQ)
DECL|macro|fd_disable_irq
mdefine_line|#define fd_disable_irq()&t;fd_ops-&gt;fd_disable_irq(FLOPPY_IRQ)
DECL|macro|fd_request_irq
mdefine_line|#define fd_request_irq()&t;request_irq(FLOPPY_IRQ, floppy_interrupt, &bslash;&n;&t;&t;&t;&t;            SA_INTERRUPT | SA_SAMPLE_RANDOM, &bslash;&n;&t;&t;&t;&t;            &quot;floppy&quot;, NULL)
DECL|macro|fd_free_irq
mdefine_line|#define fd_free_irq()&t;&t;free_irq(FLOPPY_IRQ, NULL);
DECL|macro|fd_dma_mem_alloc
mdefine_line|#define fd_dma_mem_alloc(size)&t;fd_ops-&gt;fd_dma_mem_alloc(size)
DECL|macro|fd_dma_mem_free
mdefine_line|#define fd_dma_mem_free(mem,size) fd_ops-&gt;fd_dma_mem_free(mem,size)
DECL|macro|fd_drive_type
mdefine_line|#define fd_drive_type(n)&t;fd_ops-&gt;fd_drive_type(n)
DECL|macro|fd_cacheflush
mdefine_line|#define fd_cacheflush(addr,size) dma_cache_wback_inv(addr,size)
DECL|macro|MAX_BUFFER_SECTORS
mdefine_line|#define MAX_BUFFER_SECTORS 24
multiline_comment|/*&n; * And on Mips&squot;s the CMOS info fails also ...&n; *&n; * FIXME: This information should come from the ARC configuration tree&n; *        or whereever a particular machine has stored this ...&n; */
DECL|macro|FLOPPY0_TYPE
mdefine_line|#define FLOPPY0_TYPE &t;&t;&t;fd_drive_type(0)
DECL|macro|FLOPPY1_TYPE
mdefine_line|#define FLOPPY1_TYPE&t;&t;&t;fd_drive_type(1)
DECL|macro|FDC1
mdefine_line|#define FDC1&t;&t;&t;fd_ops-&gt;fd_getfdaddr1();
multiline_comment|/*&n; * Hack: The floppy drivrer defines this, before including fdreg.h.  We use&n; * to define FDC2 only one and keep it a static variable in floppy.c.&n; */
macro_line|#ifdef FDPATCHES
DECL|variable|FDC2
r_static
r_int
id|FDC2
op_assign
op_minus
l_int|1
suffix:semicolon
macro_line|#endif
DECL|macro|N_FDC
mdefine_line|#define N_FDC 1&t;&t;&t;/* do you *really* want a second controller? */
DECL|macro|N_DRIVE
mdefine_line|#define N_DRIVE 8
DECL|macro|FLOPPY_MOTOR_MASK
mdefine_line|#define FLOPPY_MOTOR_MASK 0xf0
multiline_comment|/*&n; * The DMA channel used by the floppy controller cannot access data at&n; * addresses &gt;= 16MB&n; *&n; * Went back to the 1MB limit, as some people had problems with the floppy&n; * driver otherwise. It doesn&squot;t matter much for performance anyway, as most&n; * floppy accesses go through the track buffer.&n; *&n; * On MIPSes using vdma, this actually means that *all* transfers go thru&n; * the * track buffer since 0x1000000 is always smaller than KSEG0/1.&n; * Actually this needs to be a bit more complicated since the so much different&n; * hardware available with MIPS CPUs ...&n; */
DECL|macro|CROSS_64KB
mdefine_line|#define CROSS_64KB(a,s) ((unsigned long)(a)/K_64 != ((unsigned long)(a) + (s) - 1) / K_64)
macro_line|#endif /* _ASM_FLOPPY_H */
eof
