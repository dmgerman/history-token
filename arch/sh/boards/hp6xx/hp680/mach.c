multiline_comment|/*&n; * linux/arch/sh/boards/hp6xx/hp680/mach.c&n; *&n; * Copyright (C) 2000 Stuart Menefy (stuart.menefy@st.com)&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; * Machine vector for the HP680&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/rtc.h&gt;
macro_line|#include &lt;asm/machvec_init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hd64461/hd64461.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
DECL|variable|__initmv
r_struct
id|sh_machine_vector
id|mv_hp680
id|__initmv
op_assign
(brace
id|mv_name
suffix:colon
l_string|&quot;hp680&quot;
comma
id|mv_nr_irqs
suffix:colon
id|HD64461_IRQBASE
op_plus
id|HD64461_IRQ_NUM
comma
id|mv_inb
suffix:colon
id|hd64461_inb
comma
id|mv_inw
suffix:colon
id|hd64461_inw
comma
id|mv_inl
suffix:colon
id|hd64461_inl
comma
id|mv_outb
suffix:colon
id|hd64461_outb
comma
id|mv_outw
suffix:colon
id|hd64461_outw
comma
id|mv_outl
suffix:colon
id|hd64461_outl
comma
id|mv_inb_p
suffix:colon
id|hd64461_inb_p
comma
id|mv_inw_p
suffix:colon
id|hd64461_inw
comma
id|mv_inl_p
suffix:colon
id|hd64461_inl
comma
id|mv_outb_p
suffix:colon
id|hd64461_outb_p
comma
id|mv_outw_p
suffix:colon
id|hd64461_outw
comma
id|mv_outl_p
suffix:colon
id|hd64461_outl
comma
id|mv_insb
suffix:colon
id|hd64461_insb
comma
id|mv_insw
suffix:colon
id|hd64461_insw
comma
id|mv_insl
suffix:colon
id|hd64461_insl
comma
id|mv_outsb
suffix:colon
id|hd64461_outsb
comma
id|mv_outsw
suffix:colon
id|hd64461_outsw
comma
id|mv_outsl
suffix:colon
id|hd64461_outsl
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
id|mv_irq_demux
suffix:colon
id|hd64461_irq_demux
comma
id|mv_rtc_gettimeofday
suffix:colon
id|sh_rtc_gettimeofday
comma
id|mv_rtc_settimeofday
suffix:colon
id|sh_rtc_settimeofday
comma
)brace
suffix:semicolon
id|ALIAS_MV
c_func
(paren
id|hp680
)paren
eof
