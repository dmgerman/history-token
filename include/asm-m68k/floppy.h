multiline_comment|/*&n; * Implementation independent bits of the Floppy driver.&n; *&n; * much of this file is derived from what was originally the Q40 floppy driver.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1999, 2000, 2001&n; *&n; * Sun3x support added 2/4/2000 Sam Creasey (sammy@sammy.net)&n; *&n; */
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
id|asmlinkage
r_void
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
suffix:semicolon
multiline_comment|/* constants... */
DECL|macro|MAX_DMA_ADDRESS
macro_line|#undef MAX_DMA_ADDRESS
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS   0x00  /* nothing like that */
multiline_comment|/*&n; * Again, the CMOS information doesn&squot;t work on m68k..&n; */
DECL|macro|FLOPPY0_TYPE
mdefine_line|#define FLOPPY0_TYPE (MACH_IS_Q40 ? 6 : 4)
DECL|macro|FLOPPY1_TYPE
mdefine_line|#define FLOPPY1_TYPE 0
DECL|macro|FLOPPY_MOTOR_MASK
mdefine_line|#define FLOPPY_MOTOR_MASK 0xf0
multiline_comment|/* basically PC init + set use_virtual_dma */
DECL|macro|FDC1
mdefine_line|#define  FDC1 m68k_floppy_init()
DECL|macro|N_FDC
mdefine_line|#define N_FDC 1
DECL|macro|N_DRIVE
mdefine_line|#define N_DRIVE 8
multiline_comment|/* vdma globals adapted from asm-i386/floppy.h */
DECL|variable|virtual_dma_count
r_static
r_int
id|virtual_dma_count
op_assign
l_int|0
suffix:semicolon
DECL|variable|virtual_dma_residue
r_static
r_int
id|virtual_dma_residue
op_assign
l_int|0
suffix:semicolon
DECL|variable|virtual_dma_addr
r_static
r_char
op_star
id|virtual_dma_addr
op_assign
l_int|0
suffix:semicolon
DECL|variable|virtual_dma_mode
r_static
r_int
id|virtual_dma_mode
op_assign
l_int|0
suffix:semicolon
DECL|variable|doing_pdma
r_static
r_int
id|doing_pdma
op_assign
l_int|0
suffix:semicolon
macro_line|#include &lt;asm/sun3xflop.h&gt;
r_extern
id|spinlock_t
id|dma_spin_lock
suffix:semicolon
DECL|function|claim_dma_lock
r_static
id|__inline__
r_int
r_int
id|claim_dma_lock
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dma_spin_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|flags
suffix:semicolon
)brace
DECL|function|release_dma_lock
r_static
id|__inline__
r_void
id|release_dma_lock
c_func
(paren
r_int
r_int
id|flags
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dma_spin_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|fd_inb
r_static
id|__inline__
r_int
r_char
id|fd_inb
c_func
(paren
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|MACH_IS_Q40
)paren
(brace
r_return
id|inb_p
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|MACH_IS_SUN3X
)paren
(brace
r_return
id|sun3x_82072_fd_inb
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
)brace
DECL|function|fd_outb
r_static
id|__inline__
r_void
id|fd_outb
c_func
(paren
r_int
r_char
id|value
comma
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|MACH_IS_Q40
)paren
(brace
id|outb_p
c_func
(paren
id|value
comma
id|port
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|MACH_IS_SUN3X
)paren
(brace
id|sun3x_82072_fd_outb
c_func
(paren
id|value
comma
id|port
)paren
suffix:semicolon
)brace
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
id|MACH_IS_Q40
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
id|floppy_hardint
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|MACH_IS_SUN3X
)paren
(brace
r_return
id|sun3xflop_request_irq
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|fd_free_irq
r_static
r_void
id|fd_free_irq
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|MACH_IS_Q40
)paren
(brace
id|free_irq
c_func
(paren
id|FLOPPY_IRQ
comma
id|floppy_hardint
)paren
suffix:semicolon
)brace
)brace
DECL|macro|fd_request_dma
mdefine_line|#define fd_request_dma()        vdma_request_dma(FLOPPY_DMA,&quot;floppy&quot;)
DECL|macro|fd_get_dma_residue
mdefine_line|#define fd_get_dma_residue()    vdma_get_dma_residue(FLOPPY_DMA)
DECL|macro|fd_dma_mem_alloc
mdefine_line|#define fd_dma_mem_alloc(size)&t;vdma_mem_alloc(size)
DECL|macro|fd_dma_setup
mdefine_line|#define fd_dma_setup(addr, size, mode, io) vdma_dma_setup(addr, size, mode, io)
DECL|macro|fd_enable_irq
mdefine_line|#define fd_enable_irq()           /* nothing... */
DECL|macro|fd_disable_irq
mdefine_line|#define fd_disable_irq()          /* nothing... */
DECL|macro|fd_free_dma
mdefine_line|#define fd_free_dma()             /* nothing */
multiline_comment|/* No 64k boundary crossing problems on Q40 - no DMA at all */
DECL|macro|CROSS_64KB
mdefine_line|#define CROSS_64KB(a,s) (0)
DECL|macro|DMA_MODE_READ
mdefine_line|#define DMA_MODE_READ  0x44    /* i386 look-alike */
DECL|macro|DMA_MODE_WRITE
mdefine_line|#define DMA_MODE_WRITE 0x48
DECL|function|m68k_floppy_init
r_static
r_int
id|m68k_floppy_init
c_func
(paren
r_void
)paren
(brace
id|use_virtual_dma
op_assign
l_int|1
suffix:semicolon
id|can_use_virtual_dma
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|MACH_IS_Q40
)paren
r_return
l_int|0x3f0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|MACH_IS_SUN3X
)paren
(brace
r_return
id|sun3xflop_init
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
r_return
op_minus
l_int|1
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
DECL|macro|fd_dma_mem_free
mdefine_line|#define fd_dma_mem_free(addr,size) _fd_dma_mem_free(addr, size)
multiline_comment|/* choose_dma_mode ???*/
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
(paren
id|MACH_IS_Q40
ques
c_cond
id|io
suffix:colon
l_int|0
)paren
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
DECL|function|fd_disable_dma
r_static
r_void
id|fd_disable_dma
c_func
(paren
r_void
)paren
(brace
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
multiline_comment|/* this is the only truly Q40 specific function */
DECL|function|floppy_hardint
id|asmlinkage
r_void
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
DECL|macro|NO_FLOPPY_ASSEMBLER
mdefine_line|#define NO_FLOPPY_ASSEMBLER
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
(brace
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
suffix:semicolon
)brace
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
multiline_comment|/* serve 1st byte fast: */
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
)brace
DECL|macro|EXTRA_FLOPPY_PARAMS
mdefine_line|#define EXTRA_FLOPPY_PARAMS
eof
