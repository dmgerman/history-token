multiline_comment|/* $Id: setup.c,v 1.5 2003/08/04 01:51:58 lethal Exp $&n; *&n; * arch/sh/kernel/setup_cqreek.c&n; *&n; * Copyright (C) 2000  Niibe Yutaka&n; *&n; * CqREEK IDE/ISA Bridge Support.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/mach/cqreek.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/io_generic.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/rtc.h&gt;
DECL|macro|IDE_OFFSET
mdefine_line|#define IDE_OFFSET 0xA4000000UL
DECL|macro|ISA_OFFSET
mdefine_line|#define ISA_OFFSET 0xA4A00000UL
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
l_string|&quot;CqREEK&quot;
suffix:semicolon
)brace
DECL|function|cqreek_port2addr
r_static
r_int
r_int
id|cqreek_port2addr
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
l_int|0x0000
op_le
id|port
op_logical_and
id|port
op_le
l_int|0x0040
)paren
r_return
id|IDE_OFFSET
op_plus
id|port
suffix:semicolon
r_if
c_cond
(paren
(paren
l_int|0x01f0
op_le
id|port
op_logical_and
id|port
op_le
l_int|0x01f7
)paren
op_logical_or
id|port
op_eq
l_int|0x03f6
)paren
r_return
id|IDE_OFFSET
op_plus
id|port
suffix:semicolon
r_return
id|ISA_OFFSET
op_plus
id|port
suffix:semicolon
)brace
multiline_comment|/*&n; * The Machine Vector&n; */
DECL|variable|__initmv
r_struct
id|sh_machine_vector
id|mv_cqreek
id|__initmv
op_assign
(brace
macro_line|#if defined(CONFIG_CPU_SH4)
dot
id|mv_nr_irqs
op_assign
l_int|48
comma
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH7708)
dot
id|mv_nr_irqs
op_assign
l_int|32
comma
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH7709)
dot
id|mv_nr_irqs
op_assign
l_int|61
comma
macro_line|#endif
dot
id|mv_init_irq
op_assign
id|init_cqreek_IRQ
comma
dot
id|mv_isa_port2addr
op_assign
id|cqreek_port2addr
comma
)brace
suffix:semicolon
DECL|function|ALIAS_MV
id|ALIAS_MV
c_func
(paren
id|cqreek
)paren
multiline_comment|/*&n; * Initialize the board&n; */
r_void
id|__init
id|platform_setup
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* udelay is not available at setup time yet... */
DECL|macro|DELAY
mdefine_line|#define DELAY() do {for (i=0; i&lt;10000; i++) ctrl_inw(0xa0000000);} while(0)
r_if
c_cond
(paren
(paren
id|inw
(paren
id|BRIDGE_FEATURE
)paren
op_amp
l_int|1
)paren
)paren
(brace
multiline_comment|/* We have IDE interface */
id|outw_p
c_func
(paren
l_int|0
comma
id|BRIDGE_IDE_INTR_LVL
)paren
suffix:semicolon
id|outw_p
c_func
(paren
l_int|0
comma
id|BRIDGE_IDE_INTR_MASK
)paren
suffix:semicolon
id|outw_p
c_func
(paren
l_int|0
comma
id|BRIDGE_IDE_CTRL
)paren
suffix:semicolon
id|DELAY
c_func
(paren
)paren
suffix:semicolon
id|outw_p
c_func
(paren
l_int|0x8000
comma
id|BRIDGE_IDE_CTRL
)paren
suffix:semicolon
id|DELAY
c_func
(paren
)paren
suffix:semicolon
id|outw_p
c_func
(paren
l_int|0xffff
comma
id|BRIDGE_IDE_INTR_STAT
)paren
suffix:semicolon
multiline_comment|/* Clear interrupt status */
id|outw_p
c_func
(paren
l_int|0x0f
op_minus
l_int|14
comma
id|BRIDGE_IDE_INTR_LVL
)paren
suffix:semicolon
multiline_comment|/* Use 14 IPR */
id|outw_p
c_func
(paren
l_int|1
comma
id|BRIDGE_IDE_INTR_MASK
)paren
suffix:semicolon
multiline_comment|/* Enable interrupt */
id|cqreek_has_ide
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|inw
(paren
id|BRIDGE_FEATURE
)paren
op_amp
l_int|2
)paren
)paren
(brace
multiline_comment|/* We have ISA interface */
id|outw_p
c_func
(paren
l_int|0
comma
id|BRIDGE_ISA_INTR_LVL
)paren
suffix:semicolon
id|outw_p
c_func
(paren
l_int|0
comma
id|BRIDGE_ISA_INTR_MASK
)paren
suffix:semicolon
id|outw_p
c_func
(paren
l_int|0
comma
id|BRIDGE_ISA_CTRL
)paren
suffix:semicolon
id|DELAY
c_func
(paren
)paren
suffix:semicolon
id|outw_p
c_func
(paren
l_int|0x8000
comma
id|BRIDGE_ISA_CTRL
)paren
suffix:semicolon
id|DELAY
c_func
(paren
)paren
suffix:semicolon
id|outw_p
c_func
(paren
l_int|0xffff
comma
id|BRIDGE_ISA_INTR_STAT
)paren
suffix:semicolon
multiline_comment|/* Clear interrupt status */
id|outw_p
c_func
(paren
l_int|0x0f
op_minus
l_int|10
comma
id|BRIDGE_ISA_INTR_LVL
)paren
suffix:semicolon
multiline_comment|/* Use 10 IPR */
id|outw_p
c_func
(paren
l_int|0xfff8
comma
id|BRIDGE_ISA_INTR_MASK
)paren
suffix:semicolon
multiline_comment|/* Enable interrupt */
id|cqreek_has_isa
op_assign
l_int|1
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;CqREEK Setup (IDE=%d, ISA=%d)...done&bslash;n&quot;
comma
id|cqreek_has_ide
comma
id|cqreek_has_isa
)paren
suffix:semicolon
)brace
eof
