macro_line|#ifndef _ASM_IA64_DMA_H
DECL|macro|_ASM_IA64_DMA_H
mdefine_line|#define _ASM_IA64_DMA_H
multiline_comment|/*&n; * Copyright (C) 1998, 1999 Hewlett-Packard Co&n; * Copyright (C) 1998, 1999 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;&t;/* And spinlocks */
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/io.h&gt;&t;&t;/* need byte IO */
macro_line|#ifdef HAVE_REALLY_SLOW_DMA_CONTROLLER
DECL|macro|dma_outb
mdefine_line|#define dma_outb&t;outb_p
macro_line|#else
DECL|macro|dma_outb
mdefine_line|#define dma_outb&t;outb
macro_line|#endif
DECL|macro|dma_inb
mdefine_line|#define dma_inb&t;&t;inb
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS&t;8
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS&t;&t;0xffffffffUL
r_extern
id|spinlock_t
id|dma_spin_lock
suffix:semicolon
multiline_comment|/* From PCI */
macro_line|#ifdef CONFIG_PCI
r_extern
r_int
id|isa_dma_bridge_buggy
suffix:semicolon
macro_line|#else
DECL|macro|isa_dma_bridge_buggy
mdefine_line|#define isa_dma_bridge_buggy &t;(0)
macro_line|#endif
macro_line|#endif /* _ASM_IA64_DMA_H */
eof
