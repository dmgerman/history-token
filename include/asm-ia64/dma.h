macro_line|#ifndef _ASM_IA64_DMA_H
DECL|macro|_ASM_IA64_DMA_H
mdefine_line|#define _ASM_IA64_DMA_H
multiline_comment|/*&n; * Copyright (C) 1998-2001 Hewlett-Packard Co&n; * Copyright (C) 1998-2001 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/io.h&gt;&t;&t;/* need byte IO */
r_extern
r_int
r_int
id|MAX_DMA_ADDRESS
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
r_extern
r_int
id|isa_dma_bridge_buggy
suffix:semicolon
macro_line|#else
DECL|macro|isa_dma_bridge_buggy
macro_line|# define isa_dma_bridge_buggy &t;(0)
macro_line|#endif
macro_line|#endif /* _ASM_IA64_DMA_H */
eof
