multiline_comment|/*&n; * linux/arch/sh/stboards/mach.c&n; *&n; * Copyright (C) 2000 Stuart Menefy (stuart.menefy@st.com)&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; * Machine vector for the STMicroelectronics STB1 HARP and compatible boards&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/rtc.h&gt;
macro_line|#include &lt;asm/machvec_init.h&gt;
macro_line|#include &lt;asm/hd64465.h/io.h&gt;
macro_line|#include &lt;asm/hd64465/hd64465.h&gt;
r_void
id|setup_harp
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|init_harp_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|heartbeat_harp
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * The Machine Vector&n; */
DECL|variable|__initmv
r_struct
id|sh_machine_vector
id|mv_harp
id|__initmv
op_assign
(brace
dot
id|mv_nr_irqs
op_assign
l_int|89
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
id|mv_readb
op_assign
id|generic_readb
comma
dot
id|mv_readw
op_assign
id|generic_readw
comma
dot
id|mv_readl
op_assign
id|generic_readl
comma
dot
id|mv_writeb
op_assign
id|generic_writeb
comma
dot
id|mv_writew
op_assign
id|generic_writew
comma
dot
id|mv_writel
op_assign
id|generic_writel
comma
dot
id|mv_ioremap
op_assign
id|generic_ioremap
comma
dot
id|mv_iounmap
op_assign
id|generic_iounmap
comma
dot
id|mv_isa_port2addr
op_assign
id|hd64465_isa_port2addr
comma
macro_line|#ifdef CONFIG_PCI
dot
id|mv_init_irq
op_assign
id|init_harp_irq
comma
macro_line|#endif
macro_line|#ifdef CONFIG_HEARTBEAT
dot
id|mv_heartbeat
op_assign
id|heartbeat_harp
comma
macro_line|#endif
)brace
suffix:semicolon
id|ALIAS_MV
c_func
(paren
id|harp
)paren
eof
