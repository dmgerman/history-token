multiline_comment|/*&n; * linux/arch/sh/boards/dmida/mach.c&n; *&n; * by Greg Banks &lt;gbanks@pocketpenguins.com&gt;&n; * (c) 2000 PocketPenguins Inc&n; *&n; * Derived from mach_hp600.c, which bore the message:&n; * Copyright (C) 2000 Stuart Menefy (stuart.menefy@st.com)&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; * Machine vector for the DataMyte Industrial Digital Assistant(tm).&n; * See http://www.dmida.com&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/rtc.h&gt;
macro_line|#include &lt;asm/machvec_init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hd64465/hd64465.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
multiline_comment|/*&n; * The Machine Vector&n; */
DECL|variable|__initmv
r_struct
id|sh_machine_vector
id|mv_dmida
id|__initmv
op_assign
(brace
dot
id|mv_nr_irqs
op_assign
id|HD64465_IRQ_BASE
op_plus
id|HD64465_IRQ_NUM
comma
dot
id|mv_inb
op_assign
id|hd64465_inb
comma
dot
id|mv_inw
op_assign
id|hd64465_inw
comma
dot
id|mv_inl
op_assign
id|hd64465_inl
comma
dot
id|mv_outb
op_assign
id|hd64465_outb
comma
dot
id|mv_outw
op_assign
id|hd64465_outw
comma
dot
id|mv_outl
op_assign
id|hd64465_outl
comma
dot
id|mv_inb_p
op_assign
id|hd64465_inb_p
comma
dot
id|mv_inw_p
op_assign
id|hd64465_inw
comma
dot
id|mv_inl_p
op_assign
id|hd64465_inl
comma
dot
id|mv_outb_p
op_assign
id|hd64465_outb_p
comma
dot
id|mv_outw_p
op_assign
id|hd64465_outw
comma
dot
id|mv_outl_p
op_assign
id|hd64465_outl
comma
dot
id|mv_insb
op_assign
id|hd64465_insb
comma
dot
id|mv_insw
op_assign
id|hd64465_insw
comma
dot
id|mv_insl
op_assign
id|hd64465_insl
comma
dot
id|mv_outsb
op_assign
id|hd64465_outsb
comma
dot
id|mv_outsw
op_assign
id|hd64465_outsw
comma
dot
id|mv_outsl
op_assign
id|hd64465_outsl
comma
dot
id|mv_irq_demux
op_assign
id|hd64465_irq_demux
comma
)brace
suffix:semicolon
id|ALIAS_MV
c_func
(paren
id|dmida
)paren
eof
