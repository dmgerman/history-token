multiline_comment|/* sun3xflop.h: Sun3/80 specific parts of the floppy driver.&n; *&n; * Derived partially from asm-sparc/floppy.h, which is:&n; *     Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; *&n; * Sun3x version 2/4/2000 Sam Creasey (sammy@sammy.net)&n; */
macro_line|#ifndef __ASM_SUN3X_FLOPPY_H
DECL|macro|__ASM_SUN3X_FLOPPY_H
mdefine_line|#define __ASM_SUN3X_FLOPPY_H
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/sun3x.h&gt;
multiline_comment|/* default interrupt vector */
DECL|macro|SUN3X_FDC_IRQ
mdefine_line|#define SUN3X_FDC_IRQ 0x40
multiline_comment|/* some constants */
DECL|macro|FCR_TC
mdefine_line|#define FCR_TC 0x1
DECL|macro|FCR_EJECT
mdefine_line|#define FCR_EJECT 0x2
DECL|macro|FCR_MTRON
mdefine_line|#define FCR_MTRON 0x4
DECL|macro|FCR_DSEL1
mdefine_line|#define FCR_DSEL1 0x8
DECL|macro|FCR_DSEL0
mdefine_line|#define FCR_DSEL0 0x10
multiline_comment|/* We don&squot;t need no stinkin&squot; I/O port allocation crap. */
DECL|macro|release_region
macro_line|#undef release_region
DECL|macro|check_region
macro_line|#undef check_region
DECL|macro|request_region
macro_line|#undef request_region
DECL|macro|release_region
mdefine_line|#define release_region(X, Y)&t;do { } while(0)
DECL|macro|check_region
mdefine_line|#define check_region(X, Y)&t;(0)
DECL|macro|request_region
mdefine_line|#define request_region(X, Y, Z)&t;(1)
DECL|struct|sun3xflop_private
r_struct
id|sun3xflop_private
(brace
DECL|member|status_r
r_volatile
r_int
r_char
op_star
id|status_r
suffix:semicolon
DECL|member|data_r
r_volatile
r_int
r_char
op_star
id|data_r
suffix:semicolon
DECL|member|fcr_r
r_volatile
r_int
r_char
op_star
id|fcr_r
suffix:semicolon
DECL|member|fvr_r
r_volatile
r_int
r_char
op_star
id|fvr_r
suffix:semicolon
DECL|member|fcr
r_int
r_char
id|fcr
suffix:semicolon
DECL|variable|sun3x_fdc
)brace
id|sun3x_fdc
suffix:semicolon
multiline_comment|/* Super paranoid... */
DECL|macro|HAVE_DISABLE_HLT
macro_line|#undef HAVE_DISABLE_HLT
multiline_comment|/* Routines unique to each controller type on a Sun. */
DECL|function|sun3x_82072_fd_inb
r_static
r_int
r_char
id|sun3x_82072_fd_inb
c_func
(paren
r_int
id|port
)paren
(brace
r_static
r_int
id|once
op_assign
l_int|0
suffix:semicolon
singleline_comment|//&t;udelay(5);
r_switch
c_cond
(paren
id|port
op_amp
l_int|7
)paren
(brace
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;floppy: Asked to read unknown port %d&bslash;n&quot;
comma
id|port
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;floppy: Port bolixed.&quot;
)paren
suffix:semicolon
r_case
l_int|4
suffix:colon
multiline_comment|/* FD_STATUS */
r_return
(paren
op_star
id|sun3x_fdc.status_r
)paren
op_amp
op_complement
id|STATUS_DMA
suffix:semicolon
r_case
l_int|5
suffix:colon
multiline_comment|/* FD_DATA */
r_return
(paren
op_star
id|sun3x_fdc.data_r
)paren
suffix:semicolon
r_case
l_int|7
suffix:colon
multiline_comment|/* FD_DIR */
multiline_comment|/* ugly hack, I can&squot;t find a way to actually detect the disk */
r_if
c_cond
(paren
op_logical_neg
id|once
)paren
(brace
id|once
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0x80
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;sun_82072_fd_inb: How did I get here?&quot;
)paren
suffix:semicolon
)brace
DECL|function|sun3x_82072_fd_outb
r_static
r_void
id|sun3x_82072_fd_outb
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
singleline_comment|//&t;udelay(5);
r_switch
c_cond
(paren
id|port
op_amp
l_int|7
)paren
(brace
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;floppy: Asked to write to unknown port %d&bslash;n&quot;
comma
id|port
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;floppy: Port bolixed.&quot;
)paren
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* FD_DOR */
multiline_comment|/* Oh geese, 82072 on the Sun has no DOR register,&n;&t;&t; * so we make do with taunting the FCR.&n;&t;&t; *&n;&t;&t; * ASSUMPTIONS:  There will only ever be one floppy&n;&t;&t; *               drive attached to a Sun controller&n;&t;&t; *               and it will be at drive zero.&n;&t;&t; */
(brace
r_int
r_char
id|fcr
op_assign
id|sun3x_fdc.fcr
suffix:semicolon
r_if
c_cond
(paren
id|value
op_amp
l_int|0x10
)paren
(brace
id|fcr
op_or_assign
(paren
id|FCR_DSEL0
op_or
id|FCR_MTRON
)paren
suffix:semicolon
)brace
r_else
id|fcr
op_and_assign
op_complement
(paren
id|FCR_DSEL0
op_or
id|FCR_MTRON
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fcr
op_ne
id|sun3x_fdc.fcr
)paren
(brace
op_star
(paren
id|sun3x_fdc.fcr_r
)paren
op_assign
id|fcr
suffix:semicolon
id|sun3x_fdc.fcr
op_assign
id|fcr
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
multiline_comment|/* FD_DATA */
op_star
(paren
id|sun3x_fdc.data_r
)paren
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
multiline_comment|/* FD_DCR */
op_star
(paren
id|sun3x_fdc.status_r
)paren
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
multiline_comment|/* FD_STATUS */
op_star
(paren
id|sun3x_fdc.status_r
)paren
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|sun3xflop_hardint
id|asmlinkage
r_void
id|sun3xflop_hardint
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
singleline_comment|//&t;printk(&quot;doing pdma&bslash;n&quot;);// st %x&bslash;n&quot;, sun_fdc-&gt;status_82072);
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
multiline_comment|/*&t;&t;&t;st=fd_inb(virtual_dma_port+4) &amp; 0x80 ;  */
id|st
op_assign
op_star
(paren
id|sun3x_fdc.status_r
)paren
suffix:semicolon
multiline_comment|/*&t;&t;&t;if(st != 0xa0)                  */
multiline_comment|/*&t;&t;&t;&t;break;                  */
r_if
c_cond
(paren
(paren
id|st
op_amp
l_int|0x80
)paren
op_eq
l_int|0
)paren
(brace
id|virtual_dma_count
op_assign
id|lcount
suffix:semicolon
id|virtual_dma_addr
op_assign
id|lptr
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|st
op_amp
l_int|0x20
)paren
op_eq
l_int|0
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
multiline_comment|/*&t;&t;&t;&t;fd_outb(*lptr, virtual_dma_port+5); */
op_star
(paren
id|sun3x_fdc.data_r
)paren
op_assign
op_star
id|lptr
suffix:semicolon
)brace
r_else
multiline_comment|/*&t;&t;&t;&t;*lptr = fd_inb(virtual_dma_port+5); */
op_star
id|lptr
op_assign
op_star
(paren
id|sun3x_fdc.data_r
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
multiline_comment|/*&t;&t;st = fd_inb(virtual_dma_port+4);   */
id|st
op_assign
op_star
(paren
id|sun3x_fdc.status_r
)paren
suffix:semicolon
)brace
macro_line|#ifdef TRACE_FLPY_INT
id|calls
op_increment
suffix:semicolon
macro_line|#endif
singleline_comment|//&t;printk(&quot;st=%02x&bslash;n&quot;, st);
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
id|doing_pdma
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef TRACE_FLPY_INT
id|printk
c_func
(paren
l_string|&quot;count=%x, residue=%x calls=%d bytes=%x dma_wait=%d&bslash;n&quot;
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
DECL|function|sun3xflop_request_irq
r_static
r_int
id|sun3xflop_request_irq
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|once
op_assign
l_int|0
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|once
)paren
(brace
id|once
op_assign
l_int|1
suffix:semicolon
id|error
op_assign
id|request_irq
c_func
(paren
id|FLOPPY_IRQ
comma
id|sun3xflop_hardint
comma
id|SA_INTERRUPT
comma
l_string|&quot;floppy&quot;
comma
l_int|0
)paren
suffix:semicolon
r_return
(paren
(paren
id|error
op_eq
l_int|0
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
id|__init
id|floppy_set_flags
c_func
(paren
r_int
op_star
id|ints
comma
r_int
id|param
comma
r_int
id|param2
)paren
suffix:semicolon
DECL|function|sun3xflop_init
r_static
r_int
id|sun3xflop_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|FLOPPY_IRQ
OL
l_int|0x40
)paren
(brace
id|FLOPPY_IRQ
op_assign
id|SUN3X_FDC_IRQ
suffix:semicolon
)brace
id|sun3x_fdc.status_r
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
id|SUN3X_FDC
suffix:semicolon
id|sun3x_fdc.data_r
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
(paren
id|SUN3X_FDC
op_plus
l_int|1
)paren
suffix:semicolon
id|sun3x_fdc.fcr_r
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
id|SUN3X_FDC_FCR
suffix:semicolon
id|sun3x_fdc.fvr_r
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
id|SUN3X_FDC_FVR
suffix:semicolon
id|sun3x_fdc.fcr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Last minute sanity check... */
r_if
c_cond
(paren
op_star
id|sun3x_fdc.status_r
op_eq
l_int|0xff
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
op_star
id|sun3x_fdc.fvr_r
op_assign
id|FLOPPY_IRQ
suffix:semicolon
op_star
id|sun3x_fdc.fcr_r
op_assign
id|FCR_TC
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
op_star
id|sun3x_fdc.fcr_r
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Success... */
id|floppy_set_flags
c_func
(paren
l_int|0
comma
l_int|1
comma
id|FD_BROKEN_DCL
)paren
suffix:semicolon
singleline_comment|// I don&squot;t know how to detect this.
id|allowed_drive_mask
op_assign
l_int|0x01
suffix:semicolon
r_return
(paren
r_int
)paren
id|SUN3X_FDC
suffix:semicolon
)brace
multiline_comment|/* I&squot;m not precisely sure this eject routine works */
DECL|function|sun3x_eject
r_static
r_int
id|sun3x_eject
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|MACH_IS_SUN3X
)paren
(brace
id|sun3x_fdc.fcr
op_or_assign
(paren
id|FCR_DSEL0
op_or
id|FCR_EJECT
)paren
suffix:semicolon
op_star
(paren
id|sun3x_fdc.fcr_r
)paren
op_assign
id|sun3x_fdc.fcr
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|sun3x_fdc.fcr
op_and_assign
op_complement
(paren
id|FCR_DSEL0
op_or
id|FCR_EJECT
)paren
suffix:semicolon
op_star
(paren
id|sun3x_fdc.fcr_r
)paren
op_assign
id|sun3x_fdc.fcr
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|fd_eject
mdefine_line|#define fd_eject(drive) sun3x_eject()
macro_line|#endif /* !(__ASM_SUN3X_FLOPPY_H) */
eof
