multiline_comment|/*&n; *  linux/include/asm-arm/floppy.h&n; *&n; *  Copyright (C) 1996-2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Note that we don&squot;t touch FLOPPY_DMA nor FLOPPY_IRQ here&n; */
macro_line|#ifndef __ASM_ARM_FLOPPY_H
DECL|macro|__ASM_ARM_FLOPPY_H
mdefine_line|#define __ASM_ARM_FLOPPY_H
macro_line|#if 0
macro_line|#include &lt;asm/arch/floppy.h&gt;
macro_line|#endif
DECL|macro|fd_outb
mdefine_line|#define fd_outb(val,port)&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if ((port) == FD_DOR)&t;&t;&bslash;&n;&t;&t;&t;fd_setdor((val));&t;&bslash;&n;&t;&t;else&t;&t;&t;&t;&bslash;&n;&t;&t;&t;outb((val),(port));&t;&bslash;&n;&t;} while(0)
DECL|macro|fd_inb
mdefine_line|#define fd_inb(port)&t;&t;inb((port))
DECL|macro|fd_request_irq
mdefine_line|#define fd_request_irq()&t;request_irq(IRQ_FLOPPYDISK,floppy_interrupt,&bslash;&n;&t;&t;&t;&t;&t;SA_INTERRUPT|SA_SAMPLE_RANDOM,&quot;floppy&quot;,NULL)
DECL|macro|fd_free_irq
mdefine_line|#define fd_free_irq()&t;&t;free_irq(IRQ_FLOPPYDISK,NULL)
DECL|macro|fd_disable_irq
mdefine_line|#define fd_disable_irq()&t;disable_irq(IRQ_FLOPPYDISK)
DECL|macro|fd_enable_irq
mdefine_line|#define fd_enable_irq()&t;&t;enable_irq(IRQ_FLOPPYDISK)
DECL|macro|fd_request_dma
mdefine_line|#define fd_request_dma()&t;request_dma(DMA_FLOPPY,&quot;floppy&quot;)
DECL|macro|fd_free_dma
mdefine_line|#define fd_free_dma()&t;&t;free_dma(DMA_FLOPPY)
DECL|macro|fd_disable_dma
mdefine_line|#define fd_disable_dma()&t;disable_dma(DMA_FLOPPY)
DECL|macro|fd_enable_dma
mdefine_line|#define fd_enable_dma()&t;&t;enable_dma(DMA_FLOPPY)
DECL|macro|fd_clear_dma_ff
mdefine_line|#define fd_clear_dma_ff()&t;clear_dma_ff(DMA_FLOPPY)
DECL|macro|fd_set_dma_mode
mdefine_line|#define fd_set_dma_mode(mode)&t;set_dma_mode(DMA_FLOPPY, (mode))
DECL|macro|fd_set_dma_addr
mdefine_line|#define fd_set_dma_addr(addr)&t;set_dma_addr(DMA_FLOPPY, virt_to_bus((addr)))
DECL|macro|fd_set_dma_count
mdefine_line|#define fd_set_dma_count(len)&t;set_dma_count(DMA_FLOPPY, (len))
DECL|macro|fd_cacheflush
mdefine_line|#define fd_cacheflush(addr,sz)
multiline_comment|/* need to clean up dma.h */
DECL|macro|DMA_FLOPPYDISK
mdefine_line|#define DMA_FLOPPYDISK&t;&t;DMA_FLOPPY
multiline_comment|/* Floppy_selects is the list of DOR&squot;s to select drive fd&n; *&n; * On initialisation, the floppy list is scanned, and the drives allocated&n; * in the order that they are found.  This is done by seeking the drive&n; * to a non-zero track, and then restoring it to track 0.  If an error occurs,&n; * then there is no floppy drive present.       [to be put back in again]&n; */
DECL|variable|floppy_selects
r_static
r_int
r_char
id|floppy_selects
(braket
l_int|2
)braket
(braket
l_int|4
)braket
op_assign
(brace
(brace
l_int|0x10
comma
l_int|0x21
comma
l_int|0x23
comma
l_int|0x33
)brace
comma
(brace
l_int|0x10
comma
l_int|0x21
comma
l_int|0x23
comma
l_int|0x33
)brace
)brace
suffix:semicolon
DECL|macro|fd_setdor
mdefine_line|#define fd_setdor(dor)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int new_dor = (dor);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (new_dor &amp; 0xf0)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;new_dor = (new_dor &amp; 0x0c) | floppy_selects[fdc][new_dor &amp; 3];&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;new_dor &amp;= 0x0c;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;outb(new_dor, FD_DOR);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * Someday, we&squot;ll automatically detect which drives are present...&n; */
DECL|function|fd_scandrives
r_static
r_inline
r_void
id|fd_scandrives
(paren
r_void
)paren
(brace
macro_line|#if 0
r_int
id|floppy
comma
id|drive_count
suffix:semicolon
id|fd_disable_irq
c_func
(paren
)paren
suffix:semicolon
id|raw_cmd
op_assign
op_amp
id|default_raw_cmd
suffix:semicolon
id|raw_cmd-&gt;flags
op_assign
id|FD_RAW_SPIN
op_or
id|FD_RAW_NEED_SEEK
suffix:semicolon
id|raw_cmd-&gt;track
op_assign
l_int|0
suffix:semicolon
id|raw_cmd-&gt;rate
op_assign
ques
c_cond
suffix:semicolon
id|drive_count
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|floppy
op_assign
l_int|0
suffix:semicolon
id|floppy
OL
l_int|4
suffix:semicolon
id|floppy
op_increment
)paren
(brace
id|current_drive
op_assign
id|drive_count
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Turn on floppy motor&n;&t;&t; */
r_if
c_cond
(paren
id|start_motor
c_func
(paren
id|redo_fd_request
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Set up FDC&n;&t;&t; */
id|fdc_specify
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Tell FDC to recalibrate&n;&t;&t; */
id|output_byte
c_func
(paren
id|FD_RECALIBRATE
)paren
suffix:semicolon
id|LAST_OUT
c_func
(paren
id|UNIT
c_func
(paren
id|floppy
)paren
)paren
suffix:semicolon
multiline_comment|/* wait for command to complete */
r_if
c_cond
(paren
op_logical_neg
id|successful
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|drive_count
suffix:semicolon
id|i
OL
l_int|3
suffix:semicolon
id|i
op_decrement
)paren
id|floppy_selects
(braket
id|fdc
)braket
(braket
id|i
)braket
op_assign
id|floppy_selects
(braket
id|fdc
)braket
(braket
id|i
op_plus
l_int|1
)braket
suffix:semicolon
id|floppy_selects
(braket
id|fdc
)braket
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
id|floppy
op_sub_assign
l_int|1
suffix:semicolon
)brace
r_else
id|drive_count
op_increment
suffix:semicolon
)brace
macro_line|#else
id|floppy_selects
(braket
l_int|0
)braket
(braket
l_int|0
)braket
op_assign
l_int|0x10
suffix:semicolon
id|floppy_selects
(braket
l_int|0
)braket
(braket
l_int|1
)braket
op_assign
l_int|0x21
suffix:semicolon
id|floppy_selects
(braket
l_int|0
)braket
(braket
l_int|2
)braket
op_assign
l_int|0x23
suffix:semicolon
id|floppy_selects
(braket
l_int|0
)braket
(braket
l_int|3
)braket
op_assign
l_int|0x33
suffix:semicolon
macro_line|#endif
)brace
DECL|macro|FDC1
mdefine_line|#define FDC1 (0x3f0)
DECL|macro|FLOPPY0_TYPE
mdefine_line|#define FLOPPY0_TYPE 4
DECL|macro|FLOPPY1_TYPE
mdefine_line|#define FLOPPY1_TYPE 4
DECL|macro|N_FDC
mdefine_line|#define N_FDC 1
DECL|macro|N_DRIVE
mdefine_line|#define N_DRIVE 4
DECL|macro|FLOPPY_MOTOR_MASK
mdefine_line|#define FLOPPY_MOTOR_MASK 0xf0
DECL|macro|CROSS_64KB
mdefine_line|#define CROSS_64KB(a,s) (0)
multiline_comment|/*&n; * This allows people to reverse the order of&n; * fd0 and fd1, in case their hardware is&n; * strangely connected (as some RiscPCs&n; * and A5000s seem to be).&n; */
DECL|function|driveswap
r_static
r_void
id|driveswap
c_func
(paren
r_int
op_star
id|ints
comma
r_int
id|dummy
comma
r_int
id|dummy2
)paren
(brace
id|floppy_selects
(braket
l_int|0
)braket
(braket
l_int|0
)braket
op_xor_assign
id|floppy_selects
(braket
l_int|0
)braket
(braket
l_int|1
)braket
suffix:semicolon
id|floppy_selects
(braket
l_int|0
)braket
(braket
l_int|1
)braket
op_xor_assign
id|floppy_selects
(braket
l_int|0
)braket
(braket
l_int|0
)braket
suffix:semicolon
id|floppy_selects
(braket
l_int|0
)braket
(braket
l_int|0
)braket
op_xor_assign
id|floppy_selects
(braket
l_int|0
)braket
(braket
l_int|1
)braket
suffix:semicolon
)brace
DECL|macro|EXTRA_FLOPPY_PARAMS
mdefine_line|#define EXTRA_FLOPPY_PARAMS ,{ &quot;driveswap&quot;, &amp;driveswap, NULL, 0, 0 }
macro_line|#endif
eof
