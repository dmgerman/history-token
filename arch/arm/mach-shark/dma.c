multiline_comment|/*&n; *  linux/arch/arm/mach-shark/dma.c&n; *&n; *  by Alexander Schulz &lt;aschulz@netwinder.org&gt;&n; *&n; *  derived from:&n; *  arch/arm/kernel/dma-ebsa285.c&n; *  Copyright (C) 1998 Phil Blundell&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mach/dma.h&gt;
DECL|function|arch_dma_init
r_void
id|__init
id|arch_dma_init
c_func
(paren
id|dma_t
op_star
id|dma
)paren
(brace
macro_line|#ifdef CONFIG_ISA_DMA
id|isa_init_dma
c_func
(paren
id|dma
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
