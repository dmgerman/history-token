multiline_comment|/*&n; * Architecture specific parts of the Floppy driver&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995&n; */
macro_line|#ifndef __ASM_X86_64_FLOPPY_H
DECL|macro|__ASM_X86_64_FLOPPY_H
mdefine_line|#define __ASM_X86_64_FLOPPY_H
macro_line|#include &lt;linux/vmalloc.h&gt;
multiline_comment|/*&n; * The DMA channel used by the floppy controller cannot access data at&n; * addresses &gt;= 16MB&n; *&n; * Went back to the 1MB limit, as some people had problems with the floppy&n; * driver otherwise. It doesn&squot;t matter much for performance anyway, as most&n; * floppy accesses go through the track buffer.&n; */
DECL|macro|_CROSS_64KB
mdefine_line|#define _CROSS_64KB(a,s,vdma) &bslash;&n;(!(vdma) &amp;&amp; ((unsigned long)(a)/K_64 != ((unsigned long)(a) + (s) - 1) / K_64))
DECL|macro|CROSS_64KB
mdefine_line|#define CROSS_64KB(a,s) _CROSS_64KB(a,s,use_virtual_dma &amp; 1)
DECL|macro|SW
mdefine_line|#define SW fd_routine[use_virtual_dma&amp;1]
DECL|macro|CSW
mdefine_line|#define CSW fd_routine[can_use_virtual_dma &amp; 1]
DECL|macro|fd_inb
mdefine_line|#define fd_inb(port)&t;&t;&t;inb_p(port)
DECL|macro|fd_outb
mdefine_line|#define fd_outb(value,port)&t;&t;outb_p(value,port)
DECL|macro|fd_request_dma
mdefine_line|#define fd_request_dma()        CSW._request_dma(FLOPPY_DMA,&quot;floppy&quot;)
DECL|macro|fd_free_dma
mdefine_line|#define fd_free_dma()           CSW._free_dma(FLOPPY_DMA)
DECL|macro|fd_enable_irq
mdefine_line|#define fd_enable_irq()         enable_irq(FLOPPY_IRQ)
DECL|macro|fd_disable_irq
mdefine_line|#define fd_disable_irq()        disable_irq(FLOPPY_IRQ)
DECL|macro|fd_free_irq
mdefine_line|#define fd_free_irq()&t;&t;free_irq(FLOPPY_IRQ, NULL)
DECL|macro|fd_get_dma_residue
mdefine_line|#define fd_get_dma_residue()    SW._get_dma_residue(FLOPPY_DMA)
DECL|macro|fd_dma_mem_alloc
mdefine_line|#define fd_dma_mem_alloc(size)&t;SW._dma_mem_alloc(size)
DECL|macro|fd_dma_setup
mdefine_line|#define fd_dma_setup(addr, size, mode, io) SW._dma_setup(addr, size, mode, io)
DECL|macro|FLOPPY_CAN_FALLBACK_ON_NODMA
mdefine_line|#define FLOPPY_CAN_FALLBACK_ON_NODMA
DECL|variable|virtual_dma_count
r_static
r_int
id|virtual_dma_count
suffix:semicolon
DECL|variable|virtual_dma_residue
r_static
r_int
id|virtual_dma_residue
suffix:semicolon
DECL|variable|virtual_dma_addr
r_static
r_char
op_star
id|virtual_dma_addr
suffix:semicolon
DECL|variable|virtual_dma_mode
r_static
r_int
id|virtual_dma_mode
suffix:semicolon
DECL|variable|doing_pdma
r_static
r_int
id|doing_pdma
suffix:semicolon
DECL|function|floppy_hardint
r_static
id|irqreturn_t
id|floppy_hardint
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_register
r_int
r_char
id|st
suffix:semicolon
DECL|macro|TRACE_FLPY_INT
macro_line|#undef TRACE_FLPY_INT
macro_line|#ifdef TRACE_FLPY_INT
r_static
r_int
id|calls
op_assign
l_int|0
suffix:semicolon
r_static
r_int
id|bytes
op_assign
l_int|0
suffix:semicolon
r_static
r_int
id|dma_wait
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|doing_pdma
)paren
r_return
id|floppy_interrupt
c_func
(paren
id|irq
comma
id|dev_id
comma
id|regs
)paren
suffix:semicolon
macro_line|#ifdef TRACE_FLPY_INT
r_if
c_cond
(paren
op_logical_neg
id|calls
)paren
(brace
id|bytes
op_assign
id|virtual_dma_count
suffix:semicolon
)brace
macro_line|#endif
(brace
r_register
r_int
id|lcount
suffix:semicolon
r_register
r_char
op_star
id|lptr
suffix:semicolon
id|st
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|lcount
op_assign
id|virtual_dma_count
comma
id|lptr
op_assign
id|virtual_dma_addr
suffix:semicolon
id|lcount
suffix:semicolon
id|lcount
op_decrement
comma
id|lptr
op_increment
)paren
(brace
id|st
op_assign
id|inb
c_func
(paren
id|virtual_dma_port
op_plus
l_int|4
)paren
op_amp
l_int|0xa0
suffix:semicolon
r_if
c_cond
(paren
id|st
op_ne
l_int|0xa0
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|virtual_dma_mode
)paren
(brace
id|outb_p
c_func
(paren
op_star
id|lptr
comma
id|virtual_dma_port
op_plus
l_int|5
)paren
suffix:semicolon
)brace
r_else
op_star
id|lptr
op_assign
id|inb_p
c_func
(paren
id|virtual_dma_port
op_plus
l_int|5
)paren
suffix:semicolon
)brace
id|virtual_dma_count
op_assign
id|lcount
suffix:semicolon
id|virtual_dma_addr
op_assign
id|lptr
suffix:semicolon
id|st
op_assign
id|inb
c_func
(paren
id|virtual_dma_port
op_plus
l_int|4
)paren
suffix:semicolon
)brace
macro_line|#ifdef TRACE_FLPY_INT
id|calls
op_increment
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|st
op_eq
l_int|0x20
)paren
(brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|st
op_amp
l_int|0x20
)paren
)paren
(brace
id|virtual_dma_residue
op_add_assign
id|virtual_dma_count
suffix:semicolon
id|virtual_dma_count
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef TRACE_FLPY_INT
id|printk
c_func
(paren
l_string|&quot;count=%x, residue=%x calls=%d bytes=%d dma_wait=%d&bslash;n&quot;
comma
id|virtual_dma_count
comma
id|virtual_dma_residue
comma
id|calls
comma
id|bytes
comma
id|dma_wait
)paren
suffix:semicolon
id|calls
op_assign
l_int|0
suffix:semicolon
id|dma_wait
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|doing_pdma
op_assign
l_int|0
suffix:semicolon
id|floppy_interrupt
c_func
(paren
id|irq
comma
id|dev_id
comma
id|regs
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
macro_line|#ifdef TRACE_FLPY_INT
r_if
c_cond
(paren
op_logical_neg
id|virtual_dma_count
)paren
(brace
id|dma_wait
op_increment
suffix:semicolon
)brace
macro_line|#endif
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|fd_disable_dma
r_static
r_void
id|fd_disable_dma
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|can_use_virtual_dma
op_amp
l_int|1
)paren
)paren
(brace
id|disable_dma
c_func
(paren
id|FLOPPY_DMA
)paren
suffix:semicolon
)brace
id|doing_pdma
op_assign
l_int|0
suffix:semicolon
id|virtual_dma_residue
op_add_assign
id|virtual_dma_count
suffix:semicolon
id|virtual_dma_count
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|vdma_request_dma
r_static
r_int
id|vdma_request_dma
c_func
(paren
r_int
r_int
id|dmanr
comma
r_const
r_char
op_star
id|device_id
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vdma_nop
r_static
r_void
id|vdma_nop
c_func
(paren
r_int
r_int
id|dummy
)paren
(brace
)brace
DECL|function|vdma_get_dma_residue
r_static
r_int
id|vdma_get_dma_residue
c_func
(paren
r_int
r_int
id|dummy
)paren
(brace
r_return
id|virtual_dma_count
op_plus
id|virtual_dma_residue
suffix:semicolon
)brace
DECL|function|fd_request_irq
r_static
r_int
id|fd_request_irq
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|can_use_virtual_dma
)paren
(brace
r_return
id|request_irq
c_func
(paren
id|FLOPPY_IRQ
comma
id|floppy_hardint
comma
id|SA_INTERRUPT
comma
l_string|&quot;floppy&quot;
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
r_return
id|request_irq
c_func
(paren
id|FLOPPY_IRQ
comma
id|floppy_interrupt
comma
id|SA_INTERRUPT
op_or
id|SA_SAMPLE_RANDOM
comma
l_string|&quot;floppy&quot;
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|dma_mem_alloc
r_static
r_int
r_int
id|dma_mem_alloc
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_return
id|__get_dma_pages
c_func
(paren
id|GFP_KERNEL
comma
id|get_order
c_func
(paren
id|size
)paren
)paren
suffix:semicolon
)brace
DECL|function|vdma_mem_alloc
r_static
r_int
r_int
id|vdma_mem_alloc
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|vmalloc
c_func
(paren
id|size
)paren
suffix:semicolon
)brace
DECL|macro|nodma_mem_alloc
mdefine_line|#define nodma_mem_alloc(size) vdma_mem_alloc(size)
DECL|function|_fd_dma_mem_free
r_static
r_void
id|_fd_dma_mem_free
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
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|addr
op_ge
(paren
r_int
r_int
)paren
id|high_memory
)paren
(brace
id|vfree
c_func
(paren
(paren
r_void
op_star
)paren
id|addr
)paren
suffix:semicolon
)brace
r_else
id|free_pages
c_func
(paren
id|addr
comma
id|get_order
c_func
(paren
id|size
)paren
)paren
suffix:semicolon
)brace
DECL|macro|fd_dma_mem_free
mdefine_line|#define fd_dma_mem_free(addr, size)  _fd_dma_mem_free(addr, size) 
DECL|function|_fd_chose_dma_mode
r_static
r_void
id|_fd_chose_dma_mode
c_func
(paren
r_char
op_star
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
id|can_use_virtual_dma
op_eq
l_int|2
)paren
(brace
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|addr
op_ge
(paren
r_int
r_int
)paren
id|high_memory
op_logical_or
id|isa_virt_to_bus
c_func
(paren
id|addr
)paren
op_ge
l_int|0x1000000
op_logical_or
id|_CROSS_64KB
c_func
(paren
id|addr
comma
id|size
comma
l_int|0
)paren
)paren
(brace
id|use_virtual_dma
op_assign
l_int|1
suffix:semicolon
)brace
r_else
id|use_virtual_dma
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|use_virtual_dma
op_assign
id|can_use_virtual_dma
op_amp
l_int|1
suffix:semicolon
)brace
)brace
DECL|macro|fd_chose_dma_mode
mdefine_line|#define fd_chose_dma_mode(addr, size) _fd_chose_dma_mode(addr, size)
DECL|function|vdma_dma_setup
r_static
r_int
id|vdma_dma_setup
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
id|doing_pdma
op_assign
l_int|1
suffix:semicolon
id|virtual_dma_port
op_assign
id|io
suffix:semicolon
id|virtual_dma_mode
op_assign
(paren
id|mode
op_eq
id|DMA_MODE_WRITE
)paren
suffix:semicolon
id|virtual_dma_addr
op_assign
id|addr
suffix:semicolon
id|virtual_dma_count
op_assign
id|size
suffix:semicolon
id|virtual_dma_residue
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hard_dma_setup
r_static
r_int
id|hard_dma_setup
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
macro_line|#ifdef FLOPPY_SANITY_CHECK
r_if
c_cond
(paren
id|CROSS_64KB
c_func
(paren
id|addr
comma
id|size
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;DMA crossing 64-K boundary %p-%p&bslash;n&quot;
comma
id|addr
comma
id|addr
op_plus
id|size
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* actual, physical DMA */
id|doing_pdma
op_assign
l_int|0
suffix:semicolon
id|clear_dma_ff
c_func
(paren
id|FLOPPY_DMA
)paren
suffix:semicolon
id|set_dma_mode
c_func
(paren
id|FLOPPY_DMA
comma
id|mode
)paren
suffix:semicolon
id|set_dma_addr
c_func
(paren
id|FLOPPY_DMA
comma
id|isa_virt_to_bus
c_func
(paren
id|addr
)paren
)paren
suffix:semicolon
id|set_dma_count
c_func
(paren
id|FLOPPY_DMA
comma
id|size
)paren
suffix:semicolon
id|enable_dma
c_func
(paren
id|FLOPPY_DMA
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|struct|fd_routine_l
r_struct
id|fd_routine_l
(brace
DECL|member|_request_dma
r_int
(paren
op_star
id|_request_dma
)paren
(paren
r_int
r_int
id|dmanr
comma
r_const
r_char
op_star
id|device_id
)paren
suffix:semicolon
DECL|member|_free_dma
r_void
(paren
op_star
id|_free_dma
)paren
(paren
r_int
r_int
id|dmanr
)paren
suffix:semicolon
DECL|member|_get_dma_residue
r_int
(paren
op_star
id|_get_dma_residue
)paren
(paren
r_int
r_int
id|dummy
)paren
suffix:semicolon
DECL|member|_dma_mem_alloc
r_int
r_int
(paren
op_star
id|_dma_mem_alloc
)paren
(paren
r_int
r_int
id|size
)paren
suffix:semicolon
DECL|member|_dma_setup
r_int
(paren
op_star
id|_dma_setup
)paren
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
suffix:semicolon
DECL|variable|fd_routine
)brace
id|fd_routine
(braket
)braket
op_assign
(brace
(brace
id|request_dma
comma
id|free_dma
comma
id|get_dma_residue
comma
id|dma_mem_alloc
comma
id|hard_dma_setup
)brace
comma
(brace
id|vdma_request_dma
comma
id|vdma_nop
comma
id|vdma_get_dma_residue
comma
id|vdma_mem_alloc
comma
id|vdma_dma_setup
)brace
)brace
suffix:semicolon
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
multiline_comment|/*&n; * Floppy types are stored in the rtc&squot;s CMOS RAM and so rtc_lock&n; * is needed to prevent corrupted CMOS RAM in case &quot;insmod floppy&quot;&n; * coincides with another rtc CMOS user.&t;&t;Paul G.&n; */
DECL|macro|FLOPPY0_TYPE
mdefine_line|#define FLOPPY0_TYPE&t;({&t;&t;&t;&t;&bslash;&n;&t;unsigned long flags;&t;&t;&t;&t;&bslash;&n;&t;unsigned char val;&t;&t;&t;&t;&bslash;&n;&t;spin_lock_irqsave(&amp;rtc_lock, flags);&t;&t;&bslash;&n;&t;val = (CMOS_READ(0x10) &gt;&gt; 4) &amp; 15;&t;&t;&bslash;&n;&t;spin_unlock_irqrestore(&amp;rtc_lock, flags);&t;&bslash;&n;&t;val;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|FLOPPY1_TYPE
mdefine_line|#define FLOPPY1_TYPE&t;({&t;&t;&t;&t;&bslash;&n;&t;unsigned long flags;&t;&t;&t;&t;&bslash;&n;&t;unsigned char val;&t;&t;&t;&t;&bslash;&n;&t;spin_lock_irqsave(&amp;rtc_lock, flags);&t;&t;&bslash;&n;&t;val = CMOS_READ(0x10) &amp; 15;&t;&t;&t;&bslash;&n;&t;spin_unlock_irqrestore(&amp;rtc_lock, flags);&t;&bslash;&n;&t;val;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|N_FDC
mdefine_line|#define N_FDC 2
DECL|macro|N_DRIVE
mdefine_line|#define N_DRIVE 8
DECL|macro|FLOPPY_MOTOR_MASK
mdefine_line|#define FLOPPY_MOTOR_MASK 0xf0
DECL|macro|AUTO_DMA
mdefine_line|#define AUTO_DMA
DECL|macro|EXTRA_FLOPPY_PARAMS
mdefine_line|#define EXTRA_FLOPPY_PARAMS
macro_line|#endif /* __ASM_X86_64_FLOPPY_H */
eof
