multiline_comment|/*&n; * linux/arch/sh/boards/se/7300/irq.c&n; *&n; * Copyright (C) 2003 Takashi Kusuda &lt;kusuda-takashi@hitachi-ul.co.jp&gt;&n; *&n; * SH-Mobile SolutionEngine 7300 Support.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mach/se7300.h&gt;
multiline_comment|/*&n; * Initialize IRQ setting&n; */
r_void
id|__init
DECL|function|init_7300se_IRQ
id|init_7300se_IRQ
c_func
(paren
r_void
)paren
(brace
id|ctrl_outw
c_func
(paren
l_int|0x0028
comma
id|PA_EPLD_MODESET
)paren
suffix:semicolon
multiline_comment|/* mode set IRQ0,1 active low. */
id|ctrl_outw
c_func
(paren
l_int|0xa000
comma
id|INTC_ICR1
)paren
suffix:semicolon
multiline_comment|/* IRQ mode; IRQ0,1 enable.    */
id|ctrl_outw
c_func
(paren
l_int|0x0000
comma
id|PORT_PFCR
)paren
suffix:semicolon
multiline_comment|/* use F for IRQ[3:0] and SIU. */
multiline_comment|/* PC_IRQ[0-3] -&gt; IRQ0 (32) */
id|make_ipr_irq
c_func
(paren
id|IRQ0_IRQ
comma
id|IRQ0_IPR_ADDR
comma
id|IRQ0_IPR_POS
comma
l_int|0x0f
op_minus
id|IRQ0_IRQ
)paren
suffix:semicolon
multiline_comment|/* A_IRQ[0-3] -&gt; IRQ1 (33) */
id|make_ipr_irq
c_func
(paren
id|IRQ1_IRQ
comma
id|IRQ1_IPR_ADDR
comma
id|IRQ1_IPR_POS
comma
l_int|0x0f
op_minus
id|IRQ1_IRQ
)paren
suffix:semicolon
id|make_ipr_irq
c_func
(paren
id|SIOF0_IRQ
comma
id|SIOF0_IPR_ADDR
comma
id|SIOF0_IPR_POS
comma
id|SIOF0_PRIORITY
)paren
suffix:semicolon
id|make_ipr_irq
c_func
(paren
id|DMTE2_IRQ
comma
id|DMA1_IPR_ADDR
comma
id|DMA1_IPR_POS
comma
id|DMA1_PRIORITY
)paren
suffix:semicolon
id|make_ipr_irq
c_func
(paren
id|DMTE3_IRQ
comma
id|DMA1_IPR_ADDR
comma
id|DMA1_IPR_POS
comma
id|DMA1_PRIORITY
)paren
suffix:semicolon
id|make_ipr_irq
c_func
(paren
id|VIO_IRQ
comma
id|VIO_IPR_ADDR
comma
id|VIO_IPR_POS
comma
id|VIO_PRIORITY
)paren
suffix:semicolon
id|ctrl_outw
c_func
(paren
l_int|0x2000
comma
id|PA_MRSHPC
op_plus
l_int|0x0c
)paren
suffix:semicolon
multiline_comment|/* mrshpc irq enable */
)brace
eof
