multiline_comment|/*&n; * linux/arch/sh/kernel/setup_sh2000.c&n; *&n; * Copyright (C) 2001  SUGIOKA Tochinobu&n; *&n; * SH-2000 Support.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/mach/sh2000.h&gt;
DECL|macro|CF_CIS_BASE
mdefine_line|#define CF_CIS_BASE&t;0xb4200000
DECL|macro|PORT_PECR
mdefine_line|#define PORT_PECR&t;0xa4000108
DECL|macro|PORT_PHCR
mdefine_line|#define PORT_PHCR&t;0xa400010E
DECL|macro|PORT_ICR1
mdefine_line|#define&t;PORT_ICR1&t;0xa4000010
DECL|macro|PORT_IRR0
mdefine_line|#define&t;PORT_IRR0&t;0xa4000004
DECL|macro|IDE_OFFSET
mdefine_line|#define IDE_OFFSET&t;0xb6200000
DECL|macro|NIC_OFFSET
mdefine_line|#define NIC_OFFSET&t;0xb6000000
DECL|macro|EXTBUS_OFFSET
mdefine_line|#define EXTBUS_OFFSET&t;0xba000000
DECL|function|get_system_type
r_const
r_char
op_star
id|get_system_type
c_func
(paren
r_void
)paren
(brace
r_return
l_string|&quot;sh2000&quot;
suffix:semicolon
)brace
DECL|function|sh2000_isa_port2addr
r_static
r_int
r_int
id|sh2000_isa_port2addr
c_func
(paren
r_int
r_int
id|offset
)paren
(brace
r_if
c_cond
(paren
(paren
id|offset
op_amp
op_complement
l_int|7
)paren
op_eq
l_int|0x1f0
op_logical_or
id|offset
op_eq
l_int|0x3f6
)paren
(brace
r_return
id|IDE_OFFSET
op_plus
id|offset
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|offset
op_amp
op_complement
l_int|0x1f
)paren
op_eq
l_int|0x300
)paren
(brace
r_return
id|NIC_OFFSET
op_plus
id|offset
suffix:semicolon
)brace
r_return
id|EXTBUS_OFFSET
op_plus
id|offset
suffix:semicolon
)brace
multiline_comment|/*&n; * The Machine Vector&n; */
DECL|variable|__initmv
r_struct
id|sh_machine_vector
id|mv_sh2000
id|__initmv
op_assign
(brace
dot
id|mv_nr_irqs
op_assign
l_int|80
comma
dot
id|mv_isa_port2addr
op_assign
id|sh2000_isa_port2addr
comma
)brace
suffix:semicolon
DECL|function|ALIAS_MV
id|ALIAS_MV
c_func
(paren
id|sh2000
)paren
multiline_comment|/*&n; * Initialize the board&n; */
r_int
id|__init
id|platform_setup
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* XXX: RTC setting comes here */
multiline_comment|/* These should be done by BIOS/IPL ... */
multiline_comment|/* Enable nCE2A, nCE2B output */
id|ctrl_outw
c_func
(paren
id|ctrl_inw
c_func
(paren
id|PORT_PECR
)paren
op_amp
op_complement
l_int|0xf00
comma
id|PORT_PECR
)paren
suffix:semicolon
multiline_comment|/* Enable the Compact Flash card, and set the level interrupt */
id|ctrl_outw
c_func
(paren
l_int|0x0042
comma
id|CF_CIS_BASE
op_plus
l_int|0x0200
)paren
suffix:semicolon
multiline_comment|/* Enable interrupt */
id|ctrl_outw
c_func
(paren
id|ctrl_inw
c_func
(paren
id|PORT_PHCR
)paren
op_amp
op_complement
l_int|0x03f3
comma
id|PORT_PHCR
)paren
suffix:semicolon
id|ctrl_outw
c_func
(paren
l_int|1
comma
id|PORT_ICR1
)paren
suffix:semicolon
id|ctrl_outw
c_func
(paren
id|ctrl_inw
c_func
(paren
id|PORT_IRR0
)paren
op_amp
op_complement
l_int|0xff3f
comma
id|PORT_IRR0
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;SH-2000 Setup...done&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
