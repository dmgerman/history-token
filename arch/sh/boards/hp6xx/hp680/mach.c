multiline_comment|/*&n; * linux/arch/sh/boards/hp6xx/hp680/mach.c&n; *&n; * Copyright (C) 2000 Stuart Menefy (stuart.menefy@st.com)&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; * Machine vector for the HP680&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/rtc.h&gt;
macro_line|#include &lt;asm/machvec_init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hd64461/hd64461.h&gt;
macro_line|#include &lt;asm/hp6xx/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
DECL|variable|__initmv
r_struct
id|sh_machine_vector
id|mv_hp680
id|__initmv
op_assign
(brace
dot
id|mv_nr_irqs
op_assign
id|HD64461_IRQBASE
op_plus
id|HD64461_IRQ_NUM
comma
dot
id|mv_inb
op_assign
id|hd64461_inb
comma
dot
id|mv_inw
op_assign
id|hd64461_inw
comma
dot
id|mv_inl
op_assign
id|hd64461_inl
comma
dot
id|mv_outb
op_assign
id|hd64461_outb
comma
dot
id|mv_outw
op_assign
id|hd64461_outw
comma
dot
id|mv_outl
op_assign
id|hd64461_outl
comma
dot
id|mv_inb_p
op_assign
id|hd64461_inb_p
comma
dot
id|mv_inw_p
op_assign
id|hd64461_inw
comma
dot
id|mv_inl_p
op_assign
id|hd64461_inl
comma
dot
id|mv_outb_p
op_assign
id|hd64461_outb_p
comma
dot
id|mv_outw_p
op_assign
id|hd64461_outw
comma
dot
id|mv_outl_p
op_assign
id|hd64461_outl
comma
dot
id|mv_insb
op_assign
id|hd64461_insb
comma
dot
id|mv_insw
op_assign
id|hd64461_insw
comma
dot
id|mv_insl
op_assign
id|hd64461_insl
comma
dot
id|mv_outsb
op_assign
id|hd64461_outsb
comma
dot
id|mv_outsw
op_assign
id|hd64461_outsw
comma
dot
id|mv_outsl
op_assign
id|hd64461_outsl
comma
dot
id|mv_readw
op_assign
id|hd64461_readw
comma
dot
id|mv_writew
op_assign
id|hd64461_writew
comma
dot
id|mv_irq_demux
op_assign
id|hd64461_irq_demux
comma
)brace
suffix:semicolon
id|ALIAS_MV
c_func
(paren
id|hp680
)paren
eof
