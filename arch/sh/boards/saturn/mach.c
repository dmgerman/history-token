multiline_comment|/*&n; * arch/sh/boards/saturn/mach.c&n; *&n; * machvec definitions for the Sega Saturn.&n; *&n; * Copyright (C) 2002 Paul Mundt&n; * &n; * Released under the terms of the GNU GPL v2.0.&n; */
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/io_generic.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/machvec_init.h&gt;
macro_line|#include &lt;asm/rtc.h&gt;
macro_line|#include &lt;asm/saturn/io.h&gt;
multiline_comment|/*&n; * The Machine Vector&n; */
DECL|variable|__initmv
r_struct
id|sh_machine_vector
id|mv_saturn
id|__initmv
op_assign
(brace
id|mv_nr_irqs
suffix:colon
l_int|80
comma
multiline_comment|/* Fix this later */
id|mv_inb
suffix:colon
id|generic_inb
comma
id|mv_inw
suffix:colon
id|generic_inw
comma
id|mv_inl
suffix:colon
id|generic_inl
comma
id|mv_outb
suffix:colon
id|generic_outb
comma
id|mv_outw
suffix:colon
id|generic_outw
comma
id|mv_outl
suffix:colon
id|generic_outl
comma
id|mv_inb_p
suffix:colon
id|generic_inb_p
comma
id|mv_inw_p
suffix:colon
id|generic_inw_p
comma
id|mv_inl_p
suffix:colon
id|generic_inl_p
comma
id|mv_outb_p
suffix:colon
id|generic_outb_p
comma
id|mv_outw_p
suffix:colon
id|generic_outw_p
comma
id|mv_outl_p
suffix:colon
id|generic_outl_p
comma
id|mv_insb
suffix:colon
id|generic_insb
comma
id|mv_insw
suffix:colon
id|generic_insw
comma
id|mv_insl
suffix:colon
id|generic_insl
comma
id|mv_outsb
suffix:colon
id|generic_outsb
comma
id|mv_outsw
suffix:colon
id|generic_outsw
comma
id|mv_outsl
suffix:colon
id|generic_outsl
comma
id|mv_readb
suffix:colon
id|generic_readb
comma
id|mv_readw
suffix:colon
id|generic_readw
comma
id|mv_readl
suffix:colon
id|generic_readl
comma
id|mv_writeb
suffix:colon
id|generic_writeb
comma
id|mv_writew
suffix:colon
id|generic_writew
comma
id|mv_writel
suffix:colon
id|generic_writel
comma
id|mv_isa_port2addr
suffix:colon
id|saturn_isa_port2addr
comma
id|mv_irq_demux
suffix:colon
id|saturn_irq_demux
comma
id|mv_ioremap
suffix:colon
id|saturn_ioremap
comma
id|mv_iounmap
suffix:colon
id|saturn_iounmap
comma
)brace
suffix:semicolon
id|ALIAS_MV
c_func
(paren
id|saturn
)paren
eof
