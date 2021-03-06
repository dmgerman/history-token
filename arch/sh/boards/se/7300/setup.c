multiline_comment|/*&n; * linux/arch/sh/boards/se/7300/setup.c&n; *&n; * Copyright (C) 2003 Takashi Kusuda &lt;kusuda-takashi@hitachi-ul.co.jp&gt;&n; *&n; * SH-Mobile SolutionEngine 7300 Support.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/machvec_init.h&gt;
macro_line|#include &lt;asm/mach/io.h&gt;
r_void
id|heartbeat_7300se
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|init_7300se_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
r_const
r_char
op_star
DECL|function|get_system_type
id|get_system_type
c_func
(paren
r_void
)paren
(brace
r_return
l_string|&quot;SolutionEngine 7300&quot;
suffix:semicolon
)brace
multiline_comment|/*&n; * The Machine Vector&n; */
DECL|variable|__initmv
r_struct
id|sh_machine_vector
id|mv_7300se
id|__initmv
op_assign
(brace
dot
id|mv_nr_irqs
op_assign
l_int|109
comma
dot
id|mv_inb
op_assign
id|sh7300se_inb
comma
dot
id|mv_inw
op_assign
id|sh7300se_inw
comma
dot
id|mv_inl
op_assign
id|sh7300se_inl
comma
dot
id|mv_outb
op_assign
id|sh7300se_outb
comma
dot
id|mv_outw
op_assign
id|sh7300se_outw
comma
dot
id|mv_outl
op_assign
id|sh7300se_outl
comma
dot
id|mv_inb_p
op_assign
id|sh7300se_inb_p
comma
dot
id|mv_inw_p
op_assign
id|sh7300se_inw
comma
dot
id|mv_inl_p
op_assign
id|sh7300se_inl
comma
dot
id|mv_outb_p
op_assign
id|sh7300se_outb_p
comma
dot
id|mv_outw_p
op_assign
id|sh7300se_outw
comma
dot
id|mv_outl_p
op_assign
id|sh7300se_outl
comma
dot
id|mv_insb
op_assign
id|sh7300se_insb
comma
dot
id|mv_insw
op_assign
id|sh7300se_insw
comma
dot
id|mv_insl
op_assign
id|sh7300se_insl
comma
dot
id|mv_outsb
op_assign
id|sh7300se_outsb
comma
dot
id|mv_outsw
op_assign
id|sh7300se_outsw
comma
dot
id|mv_outsl
op_assign
id|sh7300se_outsl
comma
dot
id|mv_init_irq
op_assign
id|init_7300se_IRQ
comma
macro_line|#ifdef CONFIG_HEARTBEAT
dot
id|mv_heartbeat
op_assign
id|heartbeat_7300se
comma
macro_line|#endif
)brace
suffix:semicolon
id|ALIAS_MV
c_func
(paren
l_int|7300
id|se
)paren
multiline_comment|/*&n; * Initialize the board&n; */
r_void
id|__init
DECL|function|platform_setup
id|platform_setup
c_func
(paren
r_void
)paren
(brace
)brace
eof
