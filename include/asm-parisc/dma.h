multiline_comment|/* $Id: dma.h,v 1.2 1999/04/27 00:46:18 deller Exp $&n; * linux/include/asm/dma.h: Defines for using and allocating dma channels.&n; * Written by Hennus Bergman, 1992.&n; * High DMA channel support &amp; info by Hannu Savolainen&n; * and John Boyd, Nov. 1992.&n; * (c) Copyright 2000, Grant Grundler&n; */
macro_line|#ifndef _ASM_DMA_H
DECL|macro|_ASM_DMA_H
mdefine_line|#define _ASM_DMA_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/io.h&gt;&t;&t;/* need byte IO */
macro_line|#include &lt;asm/system.h&gt;&t;
DECL|macro|dma_outb
mdefine_line|#define dma_outb&t;outb
DECL|macro|dma_inb
mdefine_line|#define dma_inb&t;&t;inb
multiline_comment|/*&n;** DMA_CHUNK_SIZE is used by the SCSI mid-layer to break up&n;** (or rather not merge) DMA&squot;s into managable chunks.&n;** On parisc, this is more of the software/tuning constraint&n;** rather than the HW. I/O MMU allocation alogorithms can be&n;** faster with smaller size is (to some degree).&n;*/
DECL|macro|DMA_CHUNK_SIZE
mdefine_line|#define DMA_CHUNK_SIZE&t;(BITS_PER_LONG*PAGE_SIZE)
multiline_comment|/* The maximum address that we can perform a DMA transfer to on this platform&n;** New dynamic DMA interfaces should obsolete this....&n;*/
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS (~0UL)
multiline_comment|/*&n;** We don&squot;t have DMA channels... well V-class does but the&n;** Dynamic DMA Mapping interface will support them... right? :^)&n;** Note: this is not relevant right now for PA-RISC, but we cannot &n;** leave this as undefined because some things (e.g. sound)&n;** won&squot;t compile :-(&n;*/
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS 8
DECL|macro|DMA_MODE_READ
mdefine_line|#define DMA_MODE_READ    1
DECL|macro|DMA_MODE_WRITE
mdefine_line|#define DMA_MODE_WRITE   2
DECL|macro|DMA_AUTOINIT
mdefine_line|#define DMA_AUTOINIT     0x10
multiline_comment|/* 8237 DMA controllers */
DECL|macro|IO_DMA1_BASE
mdefine_line|#define IO_DMA1_BASE&t;0x00&t;/* 8 bit slave DMA, channels 0..3 */
DECL|macro|IO_DMA2_BASE
mdefine_line|#define IO_DMA2_BASE&t;0xC0&t;/* 16 bit master DMA, ch 4(=slave input)..7 */
multiline_comment|/* DMA controller registers */
DECL|macro|DMA1_CMD_REG
mdefine_line|#define DMA1_CMD_REG&t;&t;0x08&t;/* command register (w) */
DECL|macro|DMA1_STAT_REG
mdefine_line|#define DMA1_STAT_REG&t;&t;0x08&t;/* status register (r) */
DECL|macro|DMA1_REQ_REG
mdefine_line|#define DMA1_REQ_REG            0x09    /* request register (w) */
DECL|macro|DMA1_MASK_REG
mdefine_line|#define DMA1_MASK_REG&t;&t;0x0A&t;/* single-channel mask (w) */
DECL|macro|DMA1_MODE_REG
mdefine_line|#define DMA1_MODE_REG&t;&t;0x0B&t;/* mode register (w) */
DECL|macro|DMA1_CLEAR_FF_REG
mdefine_line|#define DMA1_CLEAR_FF_REG&t;0x0C&t;/* clear pointer flip-flop (w) */
DECL|macro|DMA1_TEMP_REG
mdefine_line|#define DMA1_TEMP_REG           0x0D    /* Temporary Register (r) */
DECL|macro|DMA1_RESET_REG
mdefine_line|#define DMA1_RESET_REG&t;&t;0x0D&t;/* Master Clear (w) */
DECL|macro|DMA1_CLR_MASK_REG
mdefine_line|#define DMA1_CLR_MASK_REG       0x0E    /* Clear Mask */
DECL|macro|DMA1_MASK_ALL_REG
mdefine_line|#define DMA1_MASK_ALL_REG       0x0F    /* all-channels mask (w) */
DECL|macro|DMA1_EXT_MODE_REG
mdefine_line|#define DMA1_EXT_MODE_REG&t;(0x400 | DMA1_MODE_REG)
DECL|macro|DMA2_CMD_REG
mdefine_line|#define DMA2_CMD_REG&t;&t;0xD0&t;/* command register (w) */
DECL|macro|DMA2_STAT_REG
mdefine_line|#define DMA2_STAT_REG&t;&t;0xD0&t;/* status register (r) */
DECL|macro|DMA2_REQ_REG
mdefine_line|#define DMA2_REQ_REG            0xD2    /* request register (w) */
DECL|macro|DMA2_MASK_REG
mdefine_line|#define DMA2_MASK_REG&t;&t;0xD4&t;/* single-channel mask (w) */
DECL|macro|DMA2_MODE_REG
mdefine_line|#define DMA2_MODE_REG&t;&t;0xD6&t;/* mode register (w) */
DECL|macro|DMA2_CLEAR_FF_REG
mdefine_line|#define DMA2_CLEAR_FF_REG&t;0xD8&t;/* clear pointer flip-flop (w) */
DECL|macro|DMA2_TEMP_REG
mdefine_line|#define DMA2_TEMP_REG           0xDA    /* Temporary Register (r) */
DECL|macro|DMA2_RESET_REG
mdefine_line|#define DMA2_RESET_REG&t;&t;0xDA&t;/* Master Clear (w) */
DECL|macro|DMA2_CLR_MASK_REG
mdefine_line|#define DMA2_CLR_MASK_REG       0xDC    /* Clear Mask */
DECL|macro|DMA2_MASK_ALL_REG
mdefine_line|#define DMA2_MASK_ALL_REG       0xDE    /* all-channels mask (w) */
DECL|macro|DMA2_EXT_MODE_REG
mdefine_line|#define DMA2_EXT_MODE_REG&t;(0x400 | DMA2_MODE_REG)
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
multiline_comment|/* Get DMA residue count. After a DMA transfer, this&n; * should return zero. Reading this while a DMA transfer is&n; * still in progress will return unpredictable results.&n; * If called before the channel has been used, it may return 1.&n; * Otherwise, it returns the number of _bytes_ left to transfer.&n; *&n; * Assumes DMA flip-flop is clear.&n; */
DECL|function|get_dma_residue
r_static
id|__inline__
r_int
id|get_dma_residue
c_func
(paren
r_int
r_int
id|dmanr
)paren
(brace
r_int
r_int
id|io_port
op_assign
(paren
id|dmanr
op_le
l_int|3
)paren
ques
c_cond
(paren
(paren
id|dmanr
op_amp
l_int|3
)paren
op_lshift
l_int|1
)paren
op_plus
l_int|1
op_plus
id|IO_DMA1_BASE
suffix:colon
(paren
(paren
id|dmanr
op_amp
l_int|3
)paren
op_lshift
l_int|2
)paren
op_plus
l_int|2
op_plus
id|IO_DMA2_BASE
suffix:semicolon
multiline_comment|/* using short to get 16-bit wrap around */
r_int
r_int
id|count
suffix:semicolon
id|count
op_assign
l_int|1
op_plus
id|dma_inb
c_func
(paren
id|io_port
)paren
suffix:semicolon
id|count
op_add_assign
id|dma_inb
c_func
(paren
id|io_port
)paren
op_lshift
l_int|8
suffix:semicolon
r_return
(paren
id|dmanr
op_le
l_int|3
)paren
ques
c_cond
id|count
suffix:colon
(paren
id|count
op_lshift
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* enable/disable a specific DMA channel */
DECL|function|enable_dma
r_static
id|__inline__
r_void
id|enable_dma
c_func
(paren
r_int
r_int
id|dmanr
)paren
(brace
macro_line|#ifdef CONFIG_SUPERIO
r_if
c_cond
(paren
id|dmanr
op_le
l_int|3
)paren
id|dma_outb
c_func
(paren
id|dmanr
comma
id|DMA1_MASK_REG
)paren
suffix:semicolon
r_else
id|dma_outb
c_func
(paren
id|dmanr
op_amp
l_int|3
comma
id|DMA2_MASK_REG
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|disable_dma
r_static
id|__inline__
r_void
id|disable_dma
c_func
(paren
r_int
r_int
id|dmanr
)paren
(brace
macro_line|#ifdef CONFIG_SUPERIO
r_if
c_cond
(paren
id|dmanr
op_le
l_int|3
)paren
id|dma_outb
c_func
(paren
id|dmanr
op_or
l_int|4
comma
id|DMA1_MASK_REG
)paren
suffix:semicolon
r_else
id|dma_outb
c_func
(paren
(paren
id|dmanr
op_amp
l_int|3
)paren
op_or
l_int|4
comma
id|DMA2_MASK_REG
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* Clear the &squot;DMA Pointer Flip Flop&squot;.&n; * Write 0 for LSB/MSB, 1 for MSB/LSB access.&n; * Use this once to initialize the FF to a known state.&n; * After that, keep track of it. :-)&n; * --- In order to do that, the DMA routines below should ---&n; * --- only be used while holding the DMA lock ! ---&n; */
DECL|function|clear_dma_ff
r_static
id|__inline__
r_void
id|clear_dma_ff
c_func
(paren
r_int
r_int
id|dmanr
)paren
(brace
)brace
multiline_comment|/* set mode (above) for a specific DMA channel */
DECL|function|set_dma_mode
r_static
id|__inline__
r_void
id|set_dma_mode
c_func
(paren
r_int
r_int
id|dmanr
comma
r_char
id|mode
)paren
(brace
)brace
multiline_comment|/* Set only the page register bits of the transfer address.&n; * This is used for successive transfers when we know the contents of&n; * the lower 16 bits of the DMA current address register, but a 64k boundary&n; * may have been crossed.&n; */
DECL|function|set_dma_page
r_static
id|__inline__
r_void
id|set_dma_page
c_func
(paren
r_int
r_int
id|dmanr
comma
r_char
id|pagenr
)paren
(brace
)brace
multiline_comment|/* Set transfer address &amp; page bits for specific DMA channel.&n; * Assumes dma flipflop is clear.&n; */
DECL|function|set_dma_addr
r_static
id|__inline__
r_void
id|set_dma_addr
c_func
(paren
r_int
r_int
id|dmanr
comma
r_int
r_int
id|a
)paren
(brace
)brace
multiline_comment|/* Set transfer size (max 64k for DMA1..3, 128k for DMA5..7) for&n; * a specific DMA channel.&n; * You must ensure the parameters are valid.&n; * NOTE: from a manual: &quot;the number of transfers is one more&n; * than the initial word count&quot;! This is taken into account.&n; * Assumes dma flip-flop is clear.&n; * NOTE 2: &quot;count&quot; represents _bytes_ and must be even for channels 5-7.&n; */
DECL|function|set_dma_count
r_static
id|__inline__
r_void
id|set_dma_count
c_func
(paren
r_int
r_int
id|dmanr
comma
r_int
r_int
id|count
)paren
(brace
)brace
DECL|macro|free_dma
mdefine_line|#define free_dma(dmanr)
macro_line|#ifdef CONFIG_PCI
r_extern
r_int
id|isa_dma_bridge_buggy
suffix:semicolon
macro_line|#else
DECL|macro|isa_dma_bridge_buggy
mdefine_line|#define isa_dma_bridge_buggy &t;(0)
macro_line|#endif
macro_line|#endif /* _ASM_DMA_H */
eof
