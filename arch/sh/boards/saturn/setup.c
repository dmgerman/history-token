multiline_comment|/* &n; * arch/sh/boards/saturn/setup.c&n; *&n; * Hardware support for the Sega Saturn.&n; *&n; * Copyright (c) 2002 Paul Mundt&n; *&n; * Released under the terms of the GNU GPL v2.0.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/mach/io.h&gt;
r_extern
r_int
id|saturn_irq_demux
c_func
(paren
r_int
id|irq_nr
)paren
suffix:semicolon
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
l_string|&quot;Sega Saturn&quot;
suffix:semicolon
)brace
multiline_comment|/*&n; * The Machine Vector&n; */
DECL|variable|__initmv
r_struct
id|sh_machine_vector
id|mv_saturn
id|__initmv
op_assign
(brace
dot
id|mv_nr_irqs
op_assign
l_int|80
comma
multiline_comment|/* Fix this later */
dot
id|mv_isa_port2addr
op_assign
id|saturn_isa_port2addr
comma
dot
id|mv_irq_demux
op_assign
id|saturn_irq_demux
comma
dot
id|mv_ioremap
op_assign
id|saturn_ioremap
comma
dot
id|mv_iounmap
op_assign
id|saturn_iounmap
comma
)brace
suffix:semicolon
DECL|function|ALIAS_MV
id|ALIAS_MV
c_func
(paren
id|saturn
)paren
r_int
id|__init
id|platform_setup
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
eof
